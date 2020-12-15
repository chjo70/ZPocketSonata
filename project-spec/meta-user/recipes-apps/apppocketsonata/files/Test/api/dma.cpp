/*
 * dma.c
 *
 *  Created on: 2020. 8. 31.
 *      Author: LIGNEX1
 */

/*****************************************************************
* dma.c
*
*  Created on: 2020. 1. 20.
*      Author: juna
******************************************************************/
#include "dma.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define __DMA__

/*****************************************************************
* Definitions
******************************************************************/
#define	mem_l2p(mem, p)				((mem)->physical + ((uint64_t)(p) - (mem)->logical ))
#define	mem_p2l(mem, p)				((mem)->logical + ((uint64_t)(p) - (mem)->physical ))

/*****************************************************************
* Structure definitions
******************************************************************/
static dma_t dma[DMA_COUNT] = { 0, };

/*****************************************************************
 * Init functions
******************************************************************/

void dma_init( dma_dev_t dev, uio_dev_t uio_dev )
{
    dma[dev].pReg = (( dma_reg_t *)(uio_get_uio(uio_dev)->logical));
    printf( "dev=%d, mem=%d, dma[dev].reg=%p\n" , dev, uio_dev, (void*)(dma[dev].pReg) );
}

dma_t *dma_get( dma_dev_t dev )
{
	return &dma[dev];
}

/*****************************************************************
* Scatter-Gather Mode Descriptor functions
******************************************************************/
static
void make_desc( dma_sg_descs_t *list, xmem_t *mem, uint32_t count, uint32_t block_size )
{
	uint64_t mem_size = sizeof(dma_sg_desc_t) * count;
	list->count = count;
	list->size = block_size;
	list->mem = mem_offset( mem, (0x40 - (mem->physical & 0x3F)) & 0x3F );
	list->item = (dma_sg_desc_t *)list->mem.logical;

	memset( list->item, 0, mem_size );
}

void dma_mm2s_desc( dma_dev_t dev, xmem_t *desc, uint16_t count, uint32_t block_size )
{
    if ( dma[dev].pReg->mm2s_dmasr.sg_incld )
		make_desc( &dma[dev].mm2s_desc, desc, count, block_size );
}

void dma_s2mm_desc( dma_dev_t dev, xmem_t *desc, uint16_t count, uint32_t block_size )
{
    if ( dma[dev].pReg->s2mm_dmasr.sg_incld )
		make_desc( &dma[dev].s2mm_desc, desc, count, block_size );
}

/*****************************************************************
* User functions
******************************************************************/
static
int desc_init( dma_sg_descs_t *list, uint64_t addr, uint32_t length )
{
	if ( length > (list->size * list->count) ) return -1;

	int index = 0;
	uint64_t offset = 0;
	uint32_t size;

	memset( list->item, 0, sizeof(dma_sg_desc_t) * list->count );
	list->curr = &list->item[0];

	while ( length > 0 )
	{
		if ( index == 0 ) list->item[index].control.sof = 1;
		if ( length > list->size )
		{
			size = list->size;
			list->item[index].next_desc = mem_l2p( &list->mem, &list->item[index+1] );
		}
		else
		{
			size = length;
			list->item[index].control.eof = 1;
			list->item[index].next_desc = mem_l2p( &list->mem, &list->item[0] );
		}

		list->item[index].buffer_addr = addr + offset;
		list->item[index].control.buff_len = size;

		offset += size;
		length -= size;
		index++;
	}

	return index;
}

bool dma_mm2s_start( dma_dev_t dev, xmem_t *src, uint32_t length, bool wait_done )
{
	bool ret = true;

    if ( !dma[dev].pReg->mm2s_dmasr.sg_incld )
	{
		// Clear Interrupt
        dma[dev].pReg->mm2s_dmasr.ioc_irq = 1;
        dma[dev].pReg->mm2s_dmasr.dly_irq = 1;
        dma[dev].pReg->mm2s_dmasr.err_irq = 1;

        dma[dev].pReg->mm2s_dmacr.rs = 1;
        dma[dev].pReg->mm2s_dmacr.ioc_irq_en = 1;
        dma[dev].pReg->mm2s_sa = src->physical;
        dma[dev].pReg->mm2s_length = length;

		dma[dev].mm2s_mem = src;
	}
	else
	{
		int count = 0;
		if ( (count = desc_init( &dma[dev].mm2s_desc, src->physical, length )) > 0 )
		{
			// Clear Interrupt
            dma[dev].pReg->mm2s_dmasr.ioc_irq = 1;
            dma[dev].pReg->mm2s_dmasr.dly_irq = 1;
            dma[dev].pReg->mm2s_dmasr.err_irq = 1;

            dma[dev].pReg->mm2s_curdesc = mem_l2p( &dma[dev].mm2s_desc.mem, &dma[dev].mm2s_desc.item[0] );
            dma[dev].pReg->mm2s_dmacr.rs = 1;
            dma[dev].pReg->mm2s_dmacr.ioc_irq_en = 1;
            dma[dev].pReg->mm2s_taildesc = mem_l2p( &dma[dev].mm2s_desc.mem, &dma[dev].mm2s_desc.item[count-1] );

			dma[dev].mm2s_mem = src;
		}
		else return false;
	}

	if ( wait_done )
	{
        //__wait( dma_mm2s_done(dev), 1000000, 10, ret );
		dma_mm2s_stop(dev);
	}

	return ret;
}

bool dma_s2mm_start( dma_dev_t dev, xmem_t *dst, uint32_t length, bool wait_done )
{
    bool ret = true;

    //printf("dma_s2mm_start..\n" );
    if( dma[dev].pReg != NULL ) {
        if ( !dma[dev].pReg->s2mm_dmasr.sg_incld )
        {
            // Clear Interrupt
            dma[dev].pReg->s2mm_dmasr.ioc_irq = 1;
            dma[dev].pReg->s2mm_dmasr.dly_irq = 1;
            dma[dev].pReg->s2mm_dmasr.err_irq = 1;

            dma[dev].pReg->s2mm_dmacr.rs = 1;
            dma[dev].pReg->s2mm_dmacr.ioc_irq_en = 1;
            dma[dev].pReg->s2mm_sa = dst->physical;
            dma[dev].pReg->s2mm_length = length;

            dma[dev].ps2mm_mem = dst;
        }
        else
        {
            int count = 0;
            if ( (count = desc_init( &dma[dev].s2mm_desc, dst->physical, length )) > 0 )
            {
                // Clear Interrupt
                dma[dev].pReg->s2mm_dmasr.ioc_irq = 1;
                dma[dev].pReg->s2mm_dmasr.dly_irq = 1;
                dma[dev].pReg->s2mm_dmasr.err_irq = 1;

                dma[dev].pReg->s2mm_curdesc = mem_l2p( &dma[dev].s2mm_desc.mem, &dma[dev].s2mm_desc.item[0] );
                dma[dev].pReg->s2mm_dmacr.rs = 1;
                dma[dev].pReg->s2mm_dmacr.ioc_irq_en = 1;
                dma[dev].pReg->s2mm_taildesc = mem_l2p( &dma[dev].s2mm_desc.mem, &dma[dev].s2mm_desc.item[count-1] );

                dma[dev].ps2mm_mem = dst;
            }
            else {
                printf("error of dma_s2mm_start..\n" );
                ret = false;
            }
        }

        if ( wait_done )
        {
            //printf("dma_s2mm_stop\n" );
            //__wait( dma_s2mm_done(dev), 1000000, 10, ret );
            dma_s2mm_stop(dev);
        }
    }
    else {
        printf("error of dma_s2mm_start..\n" );
        ret = false;
    }

    return ret;
}

bool dma_mm2s_cyclic( dma_dev_t dev, xmem_t *src, uint32_t length )
{
    if ( !dma[dev].pReg->mm2s_dmasr.sg_incld ) return false;
	else
	{
		int count = 0;
		if ( (count = desc_init( &dma[dev].mm2s_desc, src->physical, length )) > 0 )
		{
            dma[dev].pReg->mm2s_curdesc = mem_l2p( &dma[dev].mm2s_desc.mem, &dma[dev].mm2s_desc.item[0] );
            dma[dev].pReg->mm2s_dmacr.cyclic_bd_enabled = 1;
            dma[dev].pReg->mm2s_dmacr.rs = 1;
            dma[dev].pReg->mm2s_taildesc = 0x10;

			dma[dev].mm2s_mem = src;
		}
		else return false;
	}

	return true;
}

bool dma_s2mm_cyclic( dma_dev_t dev, xmem_t *dst, uint32_t length )
{
    if ( !dma[dev].pReg->s2mm_dmasr.sg_incld ) return false;
	else
	{
		int count = 0;
		if ( (count = desc_init( &dma[dev].s2mm_desc, dst->physical, length )) > 0 )
		{
			// 20.09.02 jykim : ���ͷ�Ʈ ���� �������� ���� �߰�
			//  -> ���� dma_s2mm_start() �Լ����� ����
            dma[dev].pReg->s2mm_dmasr.ioc_irq = 1;
            dma[dev].pReg->s2mm_dmasr.dly_irq = 1;
            dma[dev].pReg->s2mm_dmasr.err_irq = 1;

			// �Ʒ� : ���� �̳� �ڵ�
            dma[dev].pReg->s2mm_curdesc = mem_l2p( &dma[dev].s2mm_desc.mem, &dma[dev].s2mm_desc.item[0] );
            dma[dev].pReg->s2mm_dmacr.cyclic_bd_enabled = 1;
            dma[dev].pReg->s2mm_dmacr.rs = 1;

			// 20.09.02 jykim : ���ͷ�Ʈ ���� �������� ���� �߰�
			//  -> ���� dma_s2mm_start() �Լ����� ����
            dma[dev].pReg->s2mm_dmacr.ioc_irq_en = 1;

            dma[dev].pReg->s2mm_taildesc = 0x10;

            dma[dev].ps2mm_mem = dst;
		}
		else return false;
	}

	return true;
}


// 20.09.02 jykim sg ��忡�� ���ͷ�Ʈ Ŭ����, ���� �Լ� �߰�
void dma_sg_s2mm_irq_enable(dma_dev_t dev)
{
    dma[dev].pReg->s2mm_dmasr.ioc_irq = 1;
    dma[dev].pReg->s2mm_dmasr.dly_irq = 1;
    dma[dev].pReg->s2mm_dmasr.err_irq = 1;

	// 20.09.02 jykim : ���ͷ�Ʈ ���� �������� ���� �߰�
	//  -> ���� dma_s2mm_start() �Լ����� ����
    dma[dev].pReg->s2mm_dmacr.ioc_irq_en = 1;
}

void dma_sg_s2mm_irq_clear(dma_dev_t dev)
{
    dma[dev].pReg->s2mm_dmasr.ioc_irq = 0;
    dma[dev].pReg->s2mm_dmasr.dly_irq = 0;
    dma[dev].pReg->s2mm_dmasr.err_irq = 0;

	// 20.09.02 jykim : ���ͷ�Ʈ ���� �������� ���� �߰�
	//  -> ���� dma_s2mm_start() �Լ����� ����
//	dma[dev].reg->s2mm_dmacr.ioc_irq_en = 0;
}

void dma_s2mm_irq_clear(dma_dev_t dev)
{
    //printf( "dma_s2mm_irq_clear::\n");
    dma[dev].pReg->s2mm_dmasr.ioc_irq = 0;
    dma[dev].pReg->s2mm_dmasr.dly_irq = 0;
    dma[dev].pReg->s2mm_dmasr.err_irq = 0;

	// 20.09.02 jykim : ���ͷ�Ʈ ���� �������� ���� �߰�
	//  -> ���� dma_s2mm_start() �Լ����� ����
//	dma[dev].reg->s2mm_dmacr.ioc_irq_en = 0;
}





bool dma_mm2s_desc_is_done( dma_dev_t dev )
{
	return (dma[dev].mm2s_desc.curr->status.cmplt == 1);
}

bool dma_s2mm_desc_is_done( dma_dev_t dev )
{
	return (dma[dev].s2mm_desc.curr->status.cmplt == 1);
}

void dma_mm2s_desc_next( dma_dev_t dev )
{
	dma[dev].mm2s_desc.curr->status.cmplt = 0;
	dma[dev].mm2s_desc.curr->status.transferred = 0;

	dma[dev].mm2s_desc.curr = (dma_sg_desc_t *)mem_p2l( &dma[dev].mm2s_desc.mem, dma[dev].mm2s_desc.curr->next_desc );
}

void dma_s2mm_desc_next( dma_dev_t dev )
{
	dma[dev].s2mm_desc.curr->status.cmplt = 0;
	dma[dev].s2mm_desc.curr->status.transferred = 0;

	dma[dev].s2mm_desc.curr = (dma_sg_desc_t *)mem_p2l( &dma[dev].s2mm_desc.mem, dma[dev].s2mm_desc.curr->next_desc );
}

void *dma_mm2s_get_mem( dma_dev_t dev, uint32_t *size )
{
	if (dma[dev].mm2s_desc.curr->status.cmplt == 1)
	{
		*size = dma[dev].mm2s_desc.curr->status.transferred;
		return (void *)mem_p2l( dma[dev].mm2s_mem, dma[dev].mm2s_desc.curr->buffer_addr );
	}
	else
	{
		*size = 0;
		return NULL;
	}
}

void *dma_s2mm_get_mem( dma_dev_t dev, uint32_t *size )
{
	if (dma[dev].s2mm_desc.curr->status.cmplt == 1)
	{
		*size = dma[dev].s2mm_desc.curr->status.transferred;
        return (void *)mem_p2l( dma[dev].ps2mm_mem, dma[dev].s2mm_desc.curr->buffer_addr );
	}
	else
	{
		*size = 0;
		return NULL;
	}
}

void dma_mm2s_reset(dma_dev_t dev)
{
    //printf( "dma_s2mm_reset\n");
    dma[dev].pReg->mm2s_dmacr.reset = 1;
}

void dma_s2mm_reset(dma_dev_t dev)
{
    if( dma[dev].pReg != NULL ) {
        //printf( "dma_s2mm_reset\n");
        dma[dev].pReg->s2mm_dmacr.reset = 1;
    }
    else {
        printf( "error of dma_s2mm_reset\n");
    }
}

void dma_mm2s_stop(dma_dev_t dev)
{
    dma[dev].pReg->mm2s_dmacr.rs = 0;
}

void dma_s2mm_stop(dma_dev_t dev)
{
    printf( "dma_s2mm_stop::\n");
    dma[dev].pReg->s2mm_dmacr.rs = 0;
}

bool dma_mm2s_done(dma_dev_t dev)
{
    return dma[dev].pReg->mm2s_dmasr.idle == 1;
}

bool dma_s2mm_done(dma_dev_t dev)
{
    return dma[dev].pReg->s2mm_dmasr.idle == 1;
}

bool dma_mm2s_busy(dma_dev_t dev)
{
    return dma[dev].pReg->mm2s_dmasr.idle == 0;
}

bool dma_s2mm_busy(dma_dev_t dev)
{
    return dma[dev].pReg->s2mm_dmasr.idle == 0;
}

dma_dmacr_t dma_mm2s_cr(dma_dev_t dev)
{
    return dma[dev].pReg->mm2s_dmacr;
}

dma_dmacr_t dma_s2mm_cr(dma_dev_t dev)
{
    return dma[dev].pReg->s2mm_dmacr;
}

dma_dmasr_t dma_mm2s_stat(dma_dev_t dev)
{
    return dma[dev].pReg->mm2s_dmasr;
}

dma_dmasr_t dma_s2mm_stat(dma_dev_t dev)
{
    return dma[dev].pReg->s2mm_dmasr;
}
