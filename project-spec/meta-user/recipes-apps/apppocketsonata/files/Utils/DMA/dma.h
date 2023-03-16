/*
 * dma.h
 *
 *  Created on: 2020. 8. 31.
 *      Author: LIGNEX1
 */

#ifndef SRC_DMA_H_
#define SRC_DMA_H_

/*****************************************************************
* dma.h
*
*  Created on: 2020. 1. 20.
*      Author: juna
******************************************************************/
//#include "../chwio.h"
//#include "../../Test/hw_interface.h"

#define _INTSAFE_H_INCLUDED_
//#include <stdint.h>

#ifndef _MSC_VER
#include <stdbool.h>
#endif


#define DMA_COUNT 1

/*****************************************************************
* Definitions
******************************************************************/
typedef enum
{
    dma_dev_1=0
} dma_dev_t;

/*****************************************************************
* Command / Status Register
******************************************************************/
typedef struct
{
	uint32_t 		rs 					: 1;
	uint32_t 		reserved0 			: 1;
	uint32_t 		reset				: 1;
	uint32_t 		key_hole			: 1;
	uint32_t 		cyclic_bd_enabled	: 1;
	uint32_t 		reserved1			: 7;
	uint32_t 		ioc_irq_en			: 1;
	uint32_t 		dly_irq_en			: 1;
	uint32_t 		err_irq_en			: 1;
	uint32_t 		reserved2			: 1;
	uint32_t 		irq_threshold		: 8;
	uint32_t 		irq_delay			: 8;
} dma_dmacr_t;

typedef struct
{
	uint32_t 		halted				: 1;
	uint32_t 		idle			 	: 1;
	uint32_t 		reserved			: 1;
	uint32_t 		sg_incld			: 1;
	uint32_t 		dma_int_err			: 1;
	uint32_t 		dma_slv_err			: 1;
	uint32_t 		dma_dec_err			: 1;
	uint32_t 		reserved0			: 1;
	uint32_t 		sg_int_err			: 1;
	uint32_t 		sg_slv_err			: 1;
	uint32_t 		sg_dec_err			: 1;
	uint32_t 		reserved1			: 1;
	uint32_t 		ioc_irq				: 1;
	uint32_t 		dly_irq				: 1;
	uint32_t 		err_irq				: 1;
	uint32_t 		reserved2			: 1;
	uint32_t 		irq_threshold_sts	: 8;
	uint32_t 		irq_delay_sts		: 8;
} dma_dmasr_t;

/*****************************************************************
* Register
******************************************************************/
typedef struct
{
	dma_dmacr_t		mm2s_dmacr;				// 	SGM	DRM
	dma_dmasr_t		mm2s_dmasr;				// 	SGM	DRM
	uint64_t		mm2s_curdesc;			// 	SGM
	uint64_t		mm2s_taildesc;			// 	SGM
	uint64_t 		mm2s_sa;				// 		DRM
	uint32_t		mm2s_reserved[2];		//
	uint32_t 		mm2s_length;			//		DRM
	uint32_t		sg_ctrl;				//			MC
	dma_dmacr_t		s2mm_dmacr;				// 	SGM	DRM
	dma_dmasr_t		s2mm_dmasr;				// 	SGM	DRM
	uint64_t		s2mm_curdesc;			//	SGM
	uint64_t		s2mm_taildesc;			//	SGM
	uint64_t 		s2mm_sa;				//		DRM
	uint32_t		s2mm_reserved[2];		//
	uint32_t 		s2mm_length;			//		DRM

} dma_reg_t;

/*****************************************************************
* Descriptor
******************************************************************/
typedef struct
{
	uint32_t		buff_len 	: 26;	// MAX 64MB
	uint32_t		uiEOF			: 1;
	uint32_t		sof			: 1;
	uint32_t		reserved	: 4;
} dma_sg_ctrl_t;

struct dma_sg_stat_t
{
	uint32_t		transferred : 26;
	uint32_t		rx_eof		: 1;
	uint32_t		rx_sof		: 1;
	uint32_t 		dma_int_err	: 1;
	uint32_t		dma_slv_err : 1;
	uint32_t 		dma_dec_err	: 1;
	uint32_t 		cmplt		: 1;
} ;

typedef struct
{
	uint64_t		next_desc;
	uint64_t		buffer_addr;
	uint32_t		reserved_0[2];
	dma_sg_ctrl_t	control;
	dma_sg_stat_t	status;
	uint32_t		app[5];
	uint32_t		reserved_1[3];
} dma_sg_desc_t;

struct dma_sg_descs_t
{
	uint32_t		uiCount;
	uint32_t		uiSize;

	dma_sg_desc_t	*item;
	xmem_t			mem;
	dma_sg_desc_t	*curr;
} ;

typedef struct
{
    //volatile dma_reg_t *pReg;
    dma_reg_t *pReg;

    dma_sg_descs_t	mm2s_desc;
    dma_sg_descs_t	s2mm_desc;

    xmem_t *pmm2s_mem;
    xmem_t *ps2mm_mem;
} dma_t;

/*****************************************************************
* macro functions
******************************************************************/
#define CALC_BLOCK_SIZE(bps, ms)	((bps/1000000)*ms)

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __DMA__

/*****************************************************************
* axi-dma functions
******************************************************************/
void dma_init(dma_dev_t dev, uint32_t mem_id);
dma_t *dma_get		(dma_dev_t dev);

void dma_mm2s_desc	(dma_dev_t dev, xmem_t *mem, uint16_t count, uint32_t block_size);
void dma_s2mm_desc	(dma_dev_t dev, xmem_t *mem, uint16_t count, uint32_t block_size);

bool dma_mm2s_start	(dma_dev_t dev, xmem_t *src, uint32_t length, bool wait_done);
bool dma_s2mm_start	(dma_dev_t dev, xmem_t *dst, uint32_t length, bool wait_done);

bool dma_mm2s_cyclic(dma_dev_t dev, xmem_t *src, uint32_t length);
bool dma_s2mm_cyclic(dma_dev_t dev, xmem_t *dst, uint32_t length);

// 20.09.02 jykim sg 모드?�서 ?�터?�트 ?�리?? ?�정 ?�수 추�?
void dma_sg_s2mm_irq_enable(dma_dev_t dev);
void dma_sg_s2mm_irq_clear(dma_dev_t dev);
void dma_s2mm_irq_clear(dma_dev_t dev);

void dma_mm2s_reset	(dma_dev_t dev);
void dma_s2mm_reset	(dma_dev_t dev);

void dma_mm2s_stop	(dma_dev_t dev);
void dma_s2mm_stop	(dma_dev_t dev);

bool dma_mm2s_done	(dma_dev_t dev);
bool dma_s2mm_done	(dma_dev_t dev);

bool dma_mm2s_busy	(dma_dev_t dev);
bool dma_s2mm_busy	(dma_dev_t dev);

dma_dmacr_t *dma_mm2s_cr(dma_dev_t dev);
dma_dmacr_t *dma_s2mm_cr(dma_dev_t dev);

dma_dmasr_t *dma_mm2s_stat(dma_dev_t dev);
dma_dmasr_t *dma_s2mm_stat(dma_dev_t dev);

bool dma_mm2s_desc_is_done( dma_dev_t dev );
bool dma_s2mm_desc_is_done( dma_dev_t dev );

void dma_mm2s_desc_next( dma_dev_t dev );
void dma_s2mm_desc_next( dma_dev_t dev );

void *dma_mm2s_get_mem( dma_dev_t dev, uint32_t *size );
void *dma_s2mm_get_mem( dma_dev_t dev, uint32_t *size );

#else

extern void dma_init(dma_dev_t dev, uint32_t mem_id);
extern void dma_s2mm_reset(dma_dev_t dev);
extern bool dma_s2mm_start(dma_dev_t dev, xmem_t *dst, uint32_t length, bool wait_done);

extern void dma_s2mm_stop(dma_dev_t dev);
extern void dma_s2mm_irq_clear(dma_dev_t dev);

#endif

#ifdef __cplusplus
}
#endif


#endif /* SRC_DMA_H_ */
