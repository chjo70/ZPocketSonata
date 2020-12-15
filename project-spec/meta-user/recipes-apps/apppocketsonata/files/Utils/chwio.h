#ifndef CHWIO_H
#define CHWIO_H

#include <stdint.h>
#include <pthread.h>

#define XMEM_COUNT			3
#define XUIO_COUNT			1
#define XUIO_INTR_COUNT 		1

#define NUM_OF_PDW          (100)

#define PDW_GATHER_SIZE     (sizeof(DMAPDW)*NUM_OF_PDW) //8byte*3

// REG Decoder
#define ADC_BIT_SLICE		0x7A00
#define IQ_SOURCE_SW			0x7A0C
#define DMA_BURST_SIZE		0x7B00
#define DMA_TEST_D_ON		0x7B04
#define DMA_TEST_PDW_TG		0x7B08
#define DMA_MNU_TLAST_TG		0x7B0C

#define ILA_CH_SEL1			0x7E00
#define TEST_DATA_READ		0x7F00
#define TEST_DATA_WRITE		0x7F04


// PPF Decoder
#define TIMER_nCLR			0x0000
#define COE_SEL				0x0010
#define PPF_SLICE				0x0020
#define PPF_SLICE_nCLR		0x0024
#define CFAR_nCLR				0x0030
#define CFAR_BEATN			0x0034
#define CFAR_MODE_ON			0x0038
#define AUTO_PH_DLY			0x0040
#define MNU_PH_DLY1			0x0044
#define MNU_PH_DLY2			0x0048
#define DET_THD_COR			0x0050
#define DET_THD_MAG			0x0054
#define DET_ONLY_COR			0x0058
#define CW_CHK_nCLR			0x0060
#define CW_CHK_TIME			0x0064
#define CHK_MOP_nCLR			0x0070
#define PW_AUTO_THD_MIN		0x0074
#define PW_THD_GAP			0x0078
#define PW_THD_MIN			0x007C
#define MOP_GAP				0x0080
#define MOP_DLY				0x0084
#define MOP_USING_FALSE		0x0088
#define FMOP_RANGE			0x0090
#define PMOP_RANGE			0x0094
#define FMOP_DIFF				0x0098
#define PMOP_DIFF				0x009C
#define NOMOP_DIFF			0x00A0
#define MON_CH_SEL			0x00A4
#define DF_FQ_WAIT_T			0x00A8
#define PDW_MAG_SEL			0x00C0
#define DF_WAIT_T				0x00C4
#define PDW_ALLOW_INCPL		0x00C8
#define PDW_SEL_GAP			0x1000

#define PDW_TIME_RES			7.8125
#define PDW_FREQ_RES			1.953125
#define PDW_AOA_RES			0.087890625



/*****************************************************************
* Definitions
******************************************************************/
/**
 * Description PL ������ Address Editor �� �Ҵ�� device ���� �ٷ�� ���� ����ü ����
 */
typedef enum
{
    DMA_1_MEM,
    BRAM_CTRL_0,
    BRAM_CTRL_PPFLT
} mem_dev_t;

//typedef struct
//{
//	uint64_t 	physical;
//	uint64_t 	logical;
//	uint32_t	size;
//	char		*name;
//} xmem_t;

typedef struct
{
    uint64_t 	physical;
    uint64_t 	logical;
    uint32_t	size;
    char		*name;
} xmem_t;

//************** PDW Struct **************

typedef struct
{
    uint64_t temp;
    union
    {
        uint32_t		pdw_index;
        struct
        {
            uint32_t 		index			: 16;
            uint32_t 		reserved		: 16;
        }stPdw_index;
    }uniPdw_index;

    union
    {
        uint32_t		pdw_toa_edge;
        struct
        {
            uint32_t 		toa_H			: 28;
            uint32_t 		edge			: 1;
            uint32_t 		reserved		: 3;
        }stPdw_toa_edge;
    }uniPdw_toa_edge;

    union
    {
        uint32_t		pdw_freq_toa;
        struct
        {
            uint32_t 		frequency_H	: 8;
            uint32_t 		pdw_phch		: 8;
            uint32_t		toa_L			: 16;
        }stPdw_freq_toa;
    }uniPdw_freq_toa;

    union
    {
        uint32_t		pdw_pw_freq;
        struct
        {
            uint32_t 		pulse_width	: 24;
            uint32_t 		frequency_L	: 8;
        }stPdw_pw_freq;
    }uniPdw_pw_freq;

    union
    {
        uint32_t	pdw_dir_pa;
        struct
        {
            uint32_t 		doa				: 12; // res = 0.087890625 deg
            uint32_t 		di				: 1; // '0' - Valid, '1' - invalid
            uint32_t 		reserved		: 3;
            uint32_t 		pa				: 16; // res = 0 ~ 65536 (linear scale)
        }stPdw_dir_pa;
    }uniPdw_dir_pa;
    union
        {
            uint32_t	pdw_status;
            struct
            {
                uint32_t 		cw_pulse		: 1; // '0' - pulse, '1' - CW
                uint32_t 		pmop			: 1; // '0' - No-mop, '1'-mop
                uint32_t 		fmop			: 1; // '0' - No-mop, '1'-mop
                uint32_t 		false_pdw		: 1; // '0' - ture, '1'-false
                uint32_t 		fmop_dir		: 2; // '0' - tri, '1' - up, '2' - down, '3' - unknown
                uint32_t 		reserved		: 10;
                uint32_t 		fmop_bw		: 16; // res = 3.11MHz
            }stPdw_status;
        }uniPdw_status;
} pdw_reg_t;

static xmem_t xmem[XMEM_COUNT] =
{
    { 0x70000000, 0,   0x10000000, (char *) "DMA_1_MEM" },		// DMA IQ MEM(DDR,32MB)
    { 0xA0000000, 0,   0x00008000, (char *) "BRAM_CTRL_0" },		// DMA IQ MEM(DDR,32MB)
    { 0xA0010000, 0,   0x00008000, (char *) "BRAM_CTRL_PPFLT" }		// DMA IQ MEM(DDR,32MB)
};

enum ENUM_UIO_DEV {
    REG_UIO_DMA_1 = 0
} ;

//typedef struct
//{
//	int 		fd;
//	uint64_t 	physical;
//	uint64_t 	logical;
//	uint32_t	size;
//	char		*dev;
//}xuio_t;

typedef struct
{
    int 		fd;
    uint64_t 	physical;
    uint64_t 	logical;
    uint32_t	size;
    char		*dev;
}xuio_t;

// xuio_t xuio ���� ����
// PL ������ Address Editor �� �Ҵ�� uio device ����
//  -> Memory device �� ����
// ���� uio0 ~ uio3 �� uio ����� ���ͷ�Ʈ�� ���
/*****************************************************************
* [Note]system-user.dtsi �� ���ǵ� uio �� vivado���� ������ address ���� ����
*  => �ܼ�â���� Ȯ�� ����
*  root@zynqPrj:/sys/class/uio# ls -al
total 0
drwxr-xr-x    2 root     root             0 Sep  3 22:14 .
drwxr-xr-x   53 root     root             0 Sep  3 22:14 ..
lrwxrwxrwx    1 root     root             0 Sep  3 22:14 uio0 -> ../../devices/platform/amba_pl@0/a0001000.dma/uio/uio0
lrwxrwxrwx    1 root     root             0 Sep  3 22:14 uio1 -> ../../devices/platform/amba_pl@0/a0010000.dma/uio/uio1
lrwxrwxrwx    1 root     root             0 Sep  3 22:14 uio2 -> ../../devices/platform/amba_pl@0/a0000000.dma/uio/uio2
lrwxrwxrwx    1 root     root             0 Sep  3 22:14 uio3 -> ../../devices/platform/amba_pl@0/a0011000.dma/uio/uio3
----------> ���� 4���� dma ���ͷ�Ʈ��(address �� vivado���� address editor ���� Ȯ���غ��� ��)
******************************************************************/
#define UIO_DMA_1_ADDR 0xA0080000

//static xuio_t xuio[XUIO_COUNT] =
//{
//    {-1,  UIO_DMA_1_ADDR, 0,    0x1000, (char *) "/dev/uio4" }, //DMA 0 Control Register
//};

static pthread_t 	g_pThread_ID_ISR[XUIO_INTR_COUNT];

//void reg_write_64(ui64 *logical, ui32 offset, ui32 value);
//ui64 reg_read_64(ui64 *logical, ui32 offset);
//void reg_write(uint8_t sel, uint32_t offset, uint32_t value);
uint32_t reg_read(uint8_t sel, uint32_t offset);
xmem_t *mem_get_mem(uint8_t sel);
xmem_t mem_offset(xmem_t *mem, uint32_t offset);

/**
 * @brief uio device �� xuio_t Ÿ���� ���� device �ν��Ͻ� ������ ����
 * @param sel �������� uio device �߿� ������ device ��(uio.h �� uio_dev_t ������ Ÿ��)
 * @return uio device �� xuio_t Ÿ���� ���� device �ν��Ͻ� ������ ����
 */
//xuio_t *uio_get_uio(uint8_t sel);

/**
 * @brief PL�κ��� ���ŵǴ�  GPIO ���ͷ�Ʈ��  read �Լ� wrapping �Լ�
 * @param fd GPIO file descriptor
 */
void PendingFromInterrupt(xuio_t *uio);
/**
 * @brief PL�κ��� ���ŵ�  UIO ���ͷ�Ʈ ����
 * @param uio 		UIO ����ü ������
 */
void ClearInterrupt(xuio_t *uio);

/**
 * @brief PL�κ��� ���ŵ�  UIO ���ͷ�Ʈ ��Ȱ��ȭ
 * @param uio 		UIO ����ü ������
 */
//void uio_re_enable_Interrupt(xuio_t *uio);

void hw_open(void);
void hw_close(void);

signed int startISR(void);
//static void SetInterruptRegister(void *irq_ptr);


class CHWIO
{
private :
    static xuio_t xuio[XUIO_COUNT];
    //=
    //{
    //    {-1,  UIO_DMA_1_ADDR, 0,    0x1000, (char *) "/dev/uio4" }, //DMA 0 Control Register
    //};

public:
    CHWIO();

public:
    static void OpenHW();
    static bool WriteReg( uint8_t sel, uint32_t offset, uint32_t value );
    static uint32_t ReadReg(uint8_t sel, uint32_t offset);
    static xuio_t *uio_get_uio(uint8_t sel);

    static xmem_t *mem_get_mem(uint8_t sel);
    static xmem_t mem_offset( xmem_t *mem, uint32_t offset );

    static bool PendingFromInterrupt(xuio_t *uio);
    static void ClearInterrupt(xuio_t *uio);

    static void uio_re_enable_Interrupt( ENUM_UIO_DEV enUIO );
    static void StopCollecting( ENUM_UIO_DEV enUIO );
    static void StartCollecting( ENUM_UIO_DEV enUIO );


};


#endif // CHWIO_H
