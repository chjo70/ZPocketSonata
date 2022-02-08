/* pciHeaderDefs.h - PCI bus config space header definitions */

/* Copyright 1998, 2003, 2010, 2015 Wind River Systems, Inc. */

/*
modification history
--------------------
06sep16,y_y  add prefetch decode bit for prefetch window.(V7PRO-3155)
30dec15,y_y  add pcie AER register. (F4655)
07aug15,wap  Fix copyright dates
22jul15,wap  Correct spelling of PCI_CFG_SUB_VENDOR_ID
29apr10,pad  Moved extern C statement after include statements.
26jul05,mdo  Add includes for other bus technologies
23jun03,m_h  Cardbus support
04mar98,tm   adapted from pciIomapLib.h v01j
*/

#ifndef __INCpciHeaderDefsh
#define __INCpciHeaderDefsh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE


/*
 * Bus Topology Constraints
 *
 * The following defines specify, by default, the maximum number of busses,
 * devices and functions allowed by the PCI 2.1 Specification.
 *
 * NOTE: config.h MUST be included before this file if either PCI_MAX_BUS,
 * PCI_MAX_DEV, or PCI_MAX_FUNC is changed to a BSP-specific value in 
 * config.h
 *
 */

#ifndef PCI_MAX_BUS
#  define PCI_MAX_BUS   255
#endif  /* PCI_MAX_BUS */

#ifndef PCI_MAX_DEV
#  define PCI_MAX_DEV   32
#endif  /* PCI_MAX_DEV */

#ifndef PCI_MAX_FUNC
#  define PCI_MAX_FUNC  8
#endif  /* PCI_MAX_FUNC */

/* PCI Configuration mechanisms */

#define PCI_MECHANISM_0     0   /* non-std user-supplied interface */
#define PCI_MECHANISM_1     1   /* current PC-AT hardware mechanism */
#define PCI_MECHANISM_2     2   /* deprecated */

/* Configuration I/O addresses for mechanism 1 */

#define PCI_CONFIG_ADDR     0x0cf8  /* write 32 bits to set address */
#define PCI_CONFIG_DATA     0x0cfc  /* 8, 16, or 32 bit accesses */

/* Configuration I/O addresses for mechanism 2 */

#define PCI_CONFIG_CSE      0x0cf8  /* CSE register */
#define PCI_CONFIG_FORWARD  0x0cfa  /* forward register */
#define PCI_CONFIG_BASE     0xc000  /* base register */

/* PCI command bits */

#define PCI_CMD_IO_ENABLE       0x0001  /* IO access enable */
#define PCI_CMD_MEM_ENABLE      0x0002  /* memory access enable */
#define PCI_CMD_MASTER_ENABLE   0x0004  /* bus master enable */
#define PCI_CMD_MON_ENABLE      0x0008  /* monitor special cycles enable */
#define PCI_CMD_WI_ENABLE       0x0010  /* write and invalidate enable */
#define PCI_CMD_SNOOP_ENABLE    0x0020  /* palette snoop enable */
#define PCI_CMD_PERR_ENABLE     0x0040  /* parity error enable */
#define PCI_CMD_WC_ENABLE       0x0080  /* wait cycle enable */
#define PCI_CMD_SERR_ENABLE     0x0100  /* system error enable */
#define PCI_CMD_FBTB_ENABLE     0x0200  /* fast back to back enable */
#define PCI_CMD_INTX_DISABLE   0x0400  /* INx disable */

/* PCI status bits */

#define PCI_STATUS_NEW_CAP             0x0010
#define PCI_STATUS_66_MHZ              0x0020
#define PCI_STATUS_UDF                 0x0040
#define PCI_STATUS_FAST_BB             0x0080
#define PCI_STATUS_DATA_PARITY_ERR     0x0100
#define PCI_STATUS_TARGET_ABORT_GEN    0x0800
#define PCI_STATUS_TARGET_ABORT_RCV    0x1000
#define PCI_STATUS_MASTER_ABORT_RCV    0x2000
#define PCI_STATUS_ASSERT_SERR         0x4000
#define PCI_STATUS_PARITY_ERROR        0x8000

/* PCI base address mask bits */

#define PCI_MEMBASE_MASK    (~0xf)  /* mask for memory base address */
#define PCI_IOBASE_MASK     (~0x3) /* mask for IO base address */
#define PCI_BASE_IO          0x1  /* IO space indicator */
#define PCI_BASE_BELOW_1M    0x2  /* memory locate below 1MB */
#define PCI_BASE_IN_64BITS   0x4  /* memory locate anywhere in 64 bits */
#define PCI_BASE_PREFETCH    0x8  /* memory prefetchable */

/* Base Address Register Memory/IO Attribute bits */

#define PCI_BAR_SPACE_MASK  (0x01)
#define PCI_BAR_SPACE_IO    (0x01)
#define PCI_BAR_SPACE_MEM   (0x00)

#define PCI_BAR_MEM_TYPE_MASK   (0x06)
#define PCI_BAR_MEM_ADDR32      (0x00)
#define PCI_BAR_MEM_BELOW_1MB   (0x02)
#define PCI_BAR_MEM_ADDR64      (0x04)
#define PCI_BAR_MEM_RESERVED    (0x06)

#define PCI_BAR_MEM_PREF_MASK   (0x08)
#define PCI_BAR_MEM_PREFETCH    (0x08)
#define PCI_BAR_MEM_NON_PREF    (0x00)

#define PCI_BAR_ALL_MASK        (PCI_BAR_SPACE_MASK    | \
                                 PCI_BAR_MEM_TYPE_MASK | \
                                 PCI_BAR_MEM_PREF_MASK)

/* PCI header type bits */

#define PCI_HEADER_TYPE_MASK    0x7f    /* mask for header type */
#define PCI_HEADER_PCI_CARDBUS  0x02    /* PCI to CardBus bridge */
#define PCI_HEADER_PCI_PCI      0x01    /* PCI to PCI bridge */
#define PCI_HEADER_TYPE_BRIDGE  0x01    /* Header Type 1 is not only a PCI2PCI bridge */
#define PCI_HEADER_TYPE0        0x00    /* normal device header */
#define PCI_HEADER_MULTI_FUNC   0x80    /* multi function device */

/* PCI configuration device and driver */
 
#define SNOOZE_MODE             0x40    /* snooze mode */
#define SLEEP_MODE_DIS          0x00    /* sleep mode disable */

/* Standard device Type 0 configuration register offsets */
/* Note that only modulo-4 addresses are written to the address register */

#define PCI_CFG_VENDOR_ID       0x00
#define PCI_CFG_DEVICE_ID       0x02
#define PCI_CFG_COMMAND         0x04
#define PCI_CFG_STATUS          0x06
#define PCI_CFG_REVISION        0x08
#define PCI_CFG_PROGRAMMING_IF  0x09
#define PCI_CFG_SUBCLASS        0x0a
#define PCI_CFG_CLASS           0x0b
#define PCI_CFG_CACHE_LINE_SIZE 0x0c
#define PCI_CFG_LATENCY_TIMER   0x0d
#define PCI_CFG_HEADER_TYPE     0x0e
#define PCI_CFG_BIST            0x0f
#define PCI_CFG_BASE_ADDRESS_0  0x10
#define PCI_CFG_BASE_ADDRESS_1  0x14
#define PCI_CFG_BASE_ADDRESS_2  0x18
#define PCI_CFG_BASE_ADDRESS_3  0x1c
#define PCI_CFG_BASE_ADDRESS_4  0x20
#define PCI_CFG_BASE_ADDRESS_5  0x24
#define PCI_CFG_CIS             0x28
#define PCI_CFG_SUB_VENDOR_ID   0x2c
#define PCI_CFG_SUB_VENDER_ID PCI_CFG_SUB_VENDOR_ID /* backward compat */
#define PCI_CFG_SUB_SYSTEM_ID   0x2e
#define PCI_CFG_EXPANSION_ROM   0x30
#define PCI_CFG_CAP_PTR         0x34
#define PCI_CFG_RESERVED_0      0x35
#define PCI_CFG_RESERVED_1      0x38
#define PCI_CFG_DEV_INT_LINE    0x3c
#define PCI_CFG_DEV_INT_PIN     0x3d
#define PCI_CFG_MIN_GRANT       0x3e
#define PCI_CFG_MAX_LATENCY     0x3f
#define PCI_CFG_SPECIAL_USE     0x41
#define PCI_CFG_MODE            0x43

/* PCI-to-PCI bridge Type 1 configuration register offsets */
/* Note that only modulo-4 addresses are written to the address register */

#define PCI_CFG_PRIMARY_BUS     0x18
#define PCI_CFG_SECONDARY_BUS   0x19
#define PCI_CFG_SUBORDINATE_BUS 0x1a
#define PCI_CFG_SEC_LATENCY     0x1b
#define PCI_CFG_IO_BASE         0x1c
#define PCI_CFG_IO_LIMIT        0x1d
#define PCI_CFG_SEC_STATUS      0x1e
#define PCI_CFG_MEM_BASE        0x20
#define PCI_CFG_MEM_LIMIT       0x22
#   define PCI_PREF_MEM_DECODE_MASK 0xF
#   define PCI_PREF_MEM_DECODE_32   0x0
#   define PCI_PREF_MEM_DECODE_64   0x1
#define PCI_CFG_PRE_MEM_BASE    0x24
#define PCI_CFG_PRE_MEM_LIMIT   0x26
#define PCI_CFG_PRE_MEM_BASE_U  0x28
#define PCI_CFG_PRE_MEM_LIMIT_U 0x2c
#define PCI_CFG_IO_BASE_U       0x30
#define PCI_CFG_IO_LIMIT_U      0x32
#define PCI_CFG_ROM_BASE        0x38
#define PCI_CFG_BRG_INT_LINE    0x3c
#define PCI_CFG_BRG_INT_PIN     0x3d
#define PCI_CFG_BRIDGE_CONTROL  0x3e

/* PCI-to-CardBus bridge Type 2 configuration register offsets */

#define PCI_CFG_CB_CAP_PTR          0x14
/*  0x15 - reserved */
#define PCI_CFG_CB_SEC_STATUS       0x16
#define PCI_CFG_CB_PRIMARY_BUS      0x18    /* PCI bus no. */
#define PCI_CFG_CB_BUS              0x19    /* CardBus bus no */
#define PCI_CFG_CB_SUBORDINATE_BUS  0x1a    /* Subordinate bus no. */
#define PCI_CFG_CB_LATENCY_TIMER    0x1b    /* CardBus latency timer */
#define PCI_CFG_CB_MEM_BASE_0       0x1c
#define PCI_CFG_CB_MEM_LIMIT_0      0x20
#define PCI_CFG_CB_MEM_BASE_1       0x24
#define PCI_CFG_CB_MEM_LIMIT_1      0x28
#define PCI_CFG_CB_IO_BASE_0        0x2c
#define PCI_CFG_CB_IO_BASE_0_HI     0x2e
#define PCI_CFG_CB_IO_LIMIT_0       0x30
#define PCI_CFG_CB_IO_LIMIT_0_HI    0x32
#define PCI_CFG_CB_IO_BASE_1        0x34
#define PCI_CFG_CB_IO_BASE_1_HI     0x36
#define PCI_CFG_CB_IO_LIMIT_1       0x38
#define PCI_CFG_CB_IO_LIMIT_1_HI    0x3a
#define PCI_CFG_CB_BRIDGE_CONTROL   0x3e
#define PCI_CFG_CB_SUB_VENDOR_ID    0x40
#define PCI_CFG_CB_SUB_SYSTEM_ID    0x42
#define PCI_CFG_CB_16BIT_LEGACY     0x44
/* 0x48 - 0x7f are reserved */

/* PCI Bridge Control Register (0x3E) bits */

#define PCI_CFG_PARITY_ERROR        0x01    /* Enable parity detection on secondary interface */
#define PCI_CFG_SERR                0x02    /* SERR enable */
#define PCI_CFG_ISA_ENABLE          0x04    /* ISA Disable - bit set = disable */
#define PCI_CFG_VGA_ENABLE          0x08    /* Enable VGA addresses */
#define PCI_CFG_MASTER_ABORT        0x20    /* Signal master abort */
#define PCI_CFG_SEC_BUS_RESET       0x40    /* secondary bus reset */
#define PCI_CFG_FAST_BACK           0x80    /* FBB enabled on secondary */ 
#define PCI_CFG_PRI_DIS_TO          0x100   /* Primary Discard Timeout: 2^10 PCI cycles */ 
#define PCI_CFG_SEC_DIS_TO          0x200   /* 2ndary Discard Timeout: 2^10 PCI cycles */ 
#define PCI_CFG_DIS_TIMER_STAT      0x400   /* Discard Timer status */ 
#define PCI_CFG_DIS_TIMER_ENABLE    0x800   /* Discard Timer enable */ 

/* Cardbus Bridge Control Register (0x3E) bits */

#define PCI_CFG_CB_PARITY_ERROR     0x01    /* Enable parity detection on secondary interface */
#define PCI_CFG_CB_SERR             0x02    /* SERR enable */
#define PCI_CFG_CB_ISA_ENABLE       0x04    /* ISA Disable - bit set = disable */
#define PCI_CFG_CB_VGA_ENABLE       0x08    /* Enable VGA addresses */
#define PCI_CFG_CB_MASTER_ABORT     0x20    /* Signal master abort */
#define PCI_CFG_CB_RESET            0x40    /* Cardbus reset */
#define PCI_CFG_CB_16BIT_INT        0x80    /* Enable ints for 16-bit cards */
#define PCI_CFG_CB_PREFETCH0        0x0100  /* Memory 0 prefetch enable */
#define PCI_CFG_CB_PREFETCH1        0x0200  /* Memory 1 prefetch enable */
#define PCI_CFG_CB_POST_WRITES      0x0400  /* Posted Writes */ 

/* Extended Capability IDs */

#define PCI_EXT_CAP_PCI_PM      0x01
#define PCI_EXT_CAP_AGP         0x02
#define PCI_EXT_CAP_VPD         0x03
#define PCI_EXT_CAP_SLOTID      0x04
#define PCI_EXT_CAP_MSI         0x05
#define PCI_EXT_CAP_HOT_SWAP    0x06
#define PCI_EXT_CAP_PCIX        0x07
#define PCI_EXT_CAP_DBG_PORT    0x0A
#define PCI_EXT_CAP_CPCI_RES    0x0B
#define PCI_EXT_CAP_HPC         0x0C    /* Hot-Plug Ctrl */
#define PCI_EXT_CAP_EXP         0x10    /* PCI Express */
#define PCI_EXT_CAP_MSIX        0x11    /* MSI-X */
   
/* CompactPCI Hot Swap Control & Status Register (HSCSR) defines */

#define PCI_HS_CSR_RSVD0  0x01  /* Reserved */
#define PCI_HS_CSR_EIM    0x02  /* ENUM Interrupt Mask */
#define PCI_HS_CSR_RSVD2  0x04  /* Reserved */
#define PCI_HS_CSR_LOO    0x08  /* Blue LED On/Off */
#define PCI_HS_CSR_RSVD4  0x10  /* Reserved */
#define PCI_HS_CSR_RSVD5  0x20  /* Reserved */
#define PCI_HS_CSR_EXT    0x40  /* ENUM Status - EXTract */
#define PCI_HS_CSR_INS    0x80  /* ENUM Status - INSert */


/*
 * PCI classifications are composed from the concatenation of four byte-size
 * components: primary (base) class, sub-class, register interface, and
 * revision ID.  The following comprise the standard PCI classification
 * definitions.
 */

/*
 * PCI Primary (Base) Class definitions for find by class function
 * Classes 0x12 - 0xFE are reserved for future enhancements
 */

#define PCI_CLASS_PRE_PCI20     0x00
#define PCI_CLASS_MASS_STORAGE  0x01
#define PCI_CLASS_NETWORK_CTLR  0x02
#define PCI_CLASS_DISPLAY_CTLR  0x03
#define PCI_CLASS_MMEDIA_DEVICE 0x04
#define PCI_CLASS_MEM_CTLR      0x05
#define PCI_CLASS_BRIDGE_CTLR   0x06
#define PCI_CLASS_COMM_CTLR     0x07
#define PCI_CLASS_BASE_PERIPH   0x08
#define PCI_CLASS_INPUT_DEVICE  0x09
#define PCI_CLASS_DOCK_DEVICE   0x0A
#define PCI_CLASS_PROCESSOR     0x0B
#define PCI_CLASS_SERIAL_BUS    0x0C
#define PCI_CLASS_WIRELESS      0x0D
#define PCI_CLASS_INTLGNT_IO    0x0E
#define PCI_CLASS_SAT_COMM      0x0F
#define PCI_CLASS_EN_DECRYPTION 0x10
#define PCI_CLASS_DAQ_DSP       0x11
#define PCI_CLASS_UNDEFINED     0xFF


/* PCI Subclass definitions */

#define PCI_SUBCLASS_00         0x00
#define PCI_SUBCLASS_01         0x01
#define PCI_SUBCLASS_02         0x02
#define PCI_SUBCLASS_03         0x03
#define PCI_SUBCLASS_04         0x04
#define PCI_SUBCLASS_05         0x05
#define PCI_SUBCLASS_06         0x06
#define PCI_SUBCLASS_07         0x07
#define PCI_SUBCLASS_08         0x08
#define PCI_SUBCLASS_09         0x09
#define PCI_SUBCLASS_0A         0x0A
#define PCI_SUBCLASS_10         0x10
#define PCI_SUBCLASS_11         0x11
#define PCI_SUBCLASS_12         0x12
#define PCI_SUBCLASS_20         0x20
#define PCI_SUBCLASS_40         0x40
#define PCI_SUBCLASS_80         0x80

/* Base Class 00 are Rev 1.0 and are not defined here. */

/* Mass Storage subclasses - Base Class 01h */

#define PCI_SUBCLASS_MASS_SCSI      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_MASS_IDE       (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_MASS_FLOPPY    (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_MASS_IPI       (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_MASS_RAID      (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_MASS_ATA       (PCI_SUBCLASS_05)
#  define PCI_REG_IF_ATA_SNGL        0x20
#  define PCI_REG_IF_ATA_CHND        0x30
#define PCI_SUBCLASS_MASS_OTHER     (PCI_SUBCLASS_80)

/* Network subclasses - Base Class 02h */

#define PCI_SUBCLASS_NET_ETHERNET   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_NET_TOKEN_RING (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_NET_FDDI       (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_NET_ATM        (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_NET_ISDN       (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_NET_WFIP       (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_NET_PCMIG214   (PCI_SUBCLASS_06)
#define PCI_SUBCLASS_NET_OTHER      (PCI_SUBCLASS_80)

/* Display subclasses - Base Class 03h */

#define PCI_SUBCLASS_DISPLAY_VGA    (PCI_SUBCLASS_00)
#  define PCI_REG_IF_VGA_STD         0x00
#  define PCI_REG_IF_VGA_8514        0x01
#define PCI_SUBCLASS_DISPLAY_XGA    (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_DISPLAY_3D     (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_DISPLAY_OTHER  (PCI_SUBCLASS_80)

/* Multimedia subclasses  - Base Class 04h */

#define PCI_SUBCLASS_MMEDIA_VIDEO   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_MMEDIA_AUDIO   (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_MMEDIA_PHONY   (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_MMEDIA_OTHER   (PCI_SUBCLASS_80)

/* Memory subclasses - Base Class 05h */

#define PCI_SUBCLASS_MEM_RAM        (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_MEM_FLASH      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_MEM_OTHER      (PCI_SUBCLASS_80)

/* Bus Bridge Device subclasses - Base Class 06h */

#define PCI_SUBCLASS_HOST_PCI_BRIDGE    (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_ISA_BRIDGE         (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_EISA_BRIDGE        (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_MCA_BRIDGE         (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_P2P_BRIDGE         (PCI_SUBCLASS_04)
#  define PCI_REG_IF_P2P_STD             0x00
#  define PCI_REG_IF_P2P_SUB_DECODE      0x01
#define PCI_SUBCLASS_PCMCIA_BRIDGE      (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_NUBUS_BRIDGE       (PCI_SUBCLASS_06)
#define PCI_SUBCLASS_CARDBUS_BRIDGE     (PCI_SUBCLASS_07)
#define PCI_SUBCLASS_RACEWAY_BRIDGE     (PCI_SUBCLASS_08)
#  define PCI_REG_IF_RACEWAY_XPARENT     0x00
#  define PCI_REG_IF_RACEWAY_END_PNT     0x01
#define PCI_SUBCLASS_SEMI_XPARENT       (PCI_SUBCLASS_09)
#  define PCI_REG_IF_SEMI_XPARENT_PRI    0x40
#  define PCI_REG_IF_SEMI_XPARENT_SEC    0x80
#define PCI_SUBCLASS_INFINI2PCI         (PCI_SUBCLASS_0A)
#define PCI_SUBCLASS_OTHER_BRIDGE       (PCI_SUBCLASS_80)

/* Simple Communications Controller subclasses - Base Class 07h */

#define PCI_SUBCLASS_SCC_SERIAL     (PCI_SUBCLASS_00)
#  define PCI_REG_IF_SERIAL_XT       0x00
#  define PCI_REG_IF_SERIAL_16450    0x01
#  define PCI_REG_IF_SERIAL_16550    0x02
#  define PCI_REG_IF_SERIAL_16650    0x03
#  define PCI_REG_IF_SERIAL_16750    0x04
#  define PCI_REG_IF_SERIAL_16850    0x05
#  define PCI_REG_IF_SERIAL_16950    0x06
#define PCI_SUBCLASS_SCC_PARLEL     (PCI_SUBCLASS_01)
#  define PCI_REG_IF_PARLEL_XT       0x00
#  define PCI_REG_IF_PARLEL_BIDIR    0x01
#  define PCI_REG_IF_PARLEL_ECP      0x02
#  define PCI_REG_IF_PARLEL_1284CTLR 0x03
#  define PCI_REG_IF_PARLEL_1284TGT  0xFE
#define PCI_SUBCLASS_SCC_MULTI      (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_SCC_MODEM      (PCI_SUBCLASS_03)
#  define PCI_REG_IF_MODEM_GENERIC   0x00
#  define PCI_REG_IF_MODEM_16450     0x01
#  define PCI_REG_IF_MODEM_16550     0x02
#  define PCI_REG_IF_MODEM_16650     0x03
#  define PCI_REG_IF_MODEM_16750     0x04
#define PCI_SUBCLASS_SCC_GPIB       (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_SCC_SMRTCRD    (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_SCC_OTHER      (PCI_SUBCLASS_80)


/* Base System subclasses - Base Class 08h */

#define PCI_SUBCLASS_BASESYS_PIC    (PCI_SUBCLASS_00)
#  define PCI_REG_IF_PIC_GEN8259      0x00
#  define PCI_REG_IF_PIC_ISA          0x01
#  define PCI_REG_IF_PIC_EISA         0x02
#  define PCI_REG_IF_PIC_APIC         0x10
#  define PCI_REG_IF_PIC_xAPIC        0x20
#define PCI_SUBCLASS_BASESYS_DMA    (PCI_SUBCLASS_01)
#  define PCI_REG_IF_DMA_GEN8237      0x00
#  define PCI_REG_IF_DMA_ISA          0x01
#  define PCI_REG_IF_DMA_EISA         0x02
#define PCI_SUBCLASS_BASESYS_TIMER  (PCI_SUBCLASS_02)
#  define PCI_REG_IF_TIMER_GEN8254    0x00
#  define PCI_REG_IF_TIMER_ISA        0x01
#  define PCI_REG_IF_TIMER_EISA       0x02
#define PCI_SUBCLASS_BASESYS_RTC    (PCI_SUBCLASS_03)
#  define PCI_REG_IF_RTC_GENERIC      0x00
#  define PCI_REG_IF_RTC_ISA          0x01
#define PCI_SUBCLASS_BASESYS_HOTPLUG    (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_BASESYS_OTHER  (PCI_SUBCLASS_80)

/* Input Device subclasses - Base Class 09h */

#define PCI_SUBCLASS_INPUT_KEYBD    (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_INPUT_PEN      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_INPUT_MOUSE    (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_INPUT_SCANR    (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_INPUT_GAMEPORT (PCI_SUBCLASS_04)
#  define PCI_REG_IF_GAMEPORT_GENERIC     0x00
#  define PCI_REG_IF_GAMEPORT_LEGACY      0x10
#define PCI_SUBCLASS_INPUT_OTHER    (PCI_SUBCLASS_80)

/* Docking Station subclasses - Base Class 0Ah */

#define PCI_SUBCLASS_DOCSTATN_GENERIC   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_DOCSTATN_OTHER (PCI_SUBCLASS_80)

/* Processor subclasses - Base Class 0Bh */

#define PCI_SUBCLASS_PROCESSOR_386      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_PROCESSOR_486      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_PROCESSOR_PENTIUM  (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_PROCESSOR_ALPHA    (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_PROCESSOR_POWERPC  (PCI_SUBCLASS_20)
#define PCI_SUBCLASS_PROCESSOR_MIPS     (PCI_SUBCLASS_30)
#define PCI_SUBCLASS_PROCESSOR_COPROC   (PCI_SUBCLASS_40)

/* Serial bus subclasses - Base Class 0Ch */

#define PCI_SUBCLASS_SERBUS_FIREWIRE    (PCI_SUBCLASS_00)
#  define PCI_REG_IF_FIREWIRE_1394       0x00
#  define PCI_REG_IF_FIREWIRE_HCI1394    0x10
#define PCI_SUBCLASS_SERBUS_ACCESS      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_SERBUS_SSA         (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_SERBUS_USB         (PCI_SUBCLASS_03)
#  define PCI_REG_IF_USB_UHCI            0x00
#  define PCI_REG_IF_USB_OHCI            0x10
#  define PCI_REG_IF_USB_ANY             0x80
#  define PCI_REG_IF_USB_NONHOST         0xFE
#define PCI_SUBCLASS_SERBUS_FIBRE_CHAN  (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_SERBUS_SMBUS       (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_SERBUS_INFINI      (PCI_SUBCLASS_06)
#define PCI_SUBCLASS_SERBUS_IPMI        (PCI_SUBCLASS_07)
#  define PCI_REG_IF_IPMI_SMIC           0x00
#  define PCI_REG_IF_IPMI_KYBD           0x01
#  define PCI_REG_IF_IPMI_BLCK           0x02
#define PCI_SUBCLASS_SERBUS_SERCOS      (PCI_SUBCLASS_08)
#define PCI_SUBCLASS_SERBUS_CAN         (PCI_SUBCLASS_09)
#define PCI_SUBCLASS_SERBUS_OTHER       (PCI_SUBCLASS_80)

/* Wireless subclasses - Base Class 0Dh */

#define PCI_SUBCLASS_WIRELESS_IRDA      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_WIRELESS_OTHER_IR  (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_WIRELESS_RF        (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_WIRELESS_BTOOTH    (PCI_SUBCLASS_11)
#define PCI_SUBCLASS_WIRELESS_BBAND     (PCI_SUBCLASS_12)
#define PCI_SUBCLASS_WIRELESS_OTHER     (PCI_SUBCLASS_80)

/*
 * Intelligent I/O subclasses - Base Class 0Eh
 * REG_IF values greater than 0x00 are reserved for I2O
 */

#define PCI_SUBCLASS_INTELIO        (PCI_SUBCLASS_00)
#  define PCI_REG_IF_INTELIO_MSG_FIFO     0x00
#define PCI_8UBCLASS_INTELIO_OTHER  (PCI_SUBCLASS_00)

/* Satellite Device Communication subclasses - Base Class 0Fh */

#define PCI_SUBCLASS_SATCOM_TV      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_SATCOM_AUDIO   (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_SATCOM_VOICE   (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_SATCOM_DATA    (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_SATCOM_OTHER   (PCI_SUBCLASS_80)

/* Encryption/Decryption subclasses - Base Class 10h */

#define PCI_SUBCLASS_EN_DECRYP_NETWORK  (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_EN_DECRYP_ENTRTMNT (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_EN_DECRYP_OTHER    (PCI_SUBCLASS_80)

/* Data Acquisition and Signal Processing subclasses - Base Class 11h */

#define PCI_SUBCLASS_DAQ_DSP_DPIO   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_DAQ_DSP_PCTRS  (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_DAQ_DSP_COMM   (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_DAQ_DSP_MGMT   (PCI_SUBCLASS_20)
#define PCI_SUBCLASS_DAQ_DSP_OTHER  (PCI_SUBCLASS_80)

/* PCI Express Capability Register */

#define PCI_EXP_CAP_REG                0x02    /* PCI Express Cap. Reg. Offset */

#define PCI_EXP_CAP_VER                0x000f  /* PCI Express Capability Version */
    #define PCI_EXP_VER_1              0x1     /* PCI Express Version - must be 0x1 */
#define PCI_EXP_CAP_PORT_TYPE          0x00f0  /* Device Port type */
    #define  PCI_EXP_TYPE_ENDPOINT     0x0     /* Express Endpoint */
    #define  PCI_EXP_TYPE_LEG_END      0x1     /* Legacy Endpoint */
    #define  PCI_EXP_TYPE_ROOT_PORT    0x4     /* Root Port */
    #define  PCI_EXP_TYPE_UPSTREAM     0x5     /* Upstream Port */
    #define  PCI_EXP_TYPE_DOWNSTREAM   0x6     /* Downstream Port */
    #define  PCI_EXP_TYPE_EXP2PCI      0x7     /* Express-to-PCI/PCI-X Bridge */
    #define  PCI_EXP_TYPE_PCI2EXP      0x8     /* PCI/PCI-X Bridge-to-Express */
    #define  PCI_EXP_TYPE_RC_INTR_EP   0x9     /* Root Complex Integrated Endpoint */
    #define  PCI_EXP_TYPE_RC_EVEN_COLE 0xa     /* Root Complex Event Collector */

#define PCI_EXP_CAP_SLOT_ADDON         0x100   /* Slot implemented */
#define PCI_EXP_CAP_IRQ                0x3e00  /* Interrupt message no. */

/* PCI Express Device Capabilities Register */

#define PCI_EXP_DEVCAP_REG             0x04    /* PCI Express Dev. Cap. Reg. Offset */

#define  PCI_EXP_DEVCAP_PAYLOAD            0x07       /* Max_Payload_Size */
    #define  PCI_EXP_PAYLOAD_128           0x0        /* 128 bytes max */
    #define  PCI_EXP_PAYLOAD_256           0x1        /* 256 bytes max */
    #define  PCI_EXP_PAYLOAD_512           0x2        /* 512 bytes max */
    #define  PCI_EXP_PAYLOAD_1KB           0x3        /* 1K bytes max */
    #define  PCI_EXP_PAYLOAD_2KB           0x4        /* 2K bytes max */
    #define  PCI_EXP_PAYLOAD_4KB           0x5        /* 4K bytes max */
#define  PCI_EXP_DEVCAP_PHANTOM            0x18       /* Phantom functions */
    #define  PCI_EXP_PHANTOM_NOTAVAIL      0x0        /* Phantom function not available */
    #define  PCI_EXP_PHANTOM_MSB           0x1        /* Most Sig Bit of function no.*/
    #define  PCI_EXP_PHANTOM_2MSB          0x2        /* 2 Most Sig Bit of function no.*/
    #define  PCI_EXP_PHANTOM_3MSB          0x3        /* 3 Most Sig Bit of function no. */
#define  PCI_EXP_DEVCAP_EXT_TAG            0x20       /* Extended tags */
    #define  PCI_EXP_EXT_TAG_5BIT          0x0        /* 5 bit Tag */
    #define  PCI_EXP_EXT_TAG_8BIT          0x1        /* 8 bit Tag */
#define  PCI_EXP_DEVCAP_L0S                0x1c0      /* EndPt L0s Acceptable Latency */
    #define  PCI_EXP_L0S_LT_64NS           0x0        /* Less than 64ns */
    #define  PCI_EXP_L0S_64NS_to_128NS     0x1        /* 64ns to less than 128ns */
    #define  PCI_EXP_L0S_128NS_to_256NS    0x2        /* 128ns to less than 256ns */
    #define  PCI_EXP_L0S_256NS_to_512NS    0x3        /* 256ns to less than 512ns */
    #define  PCI_EXP_L0S_512NS_to_1US      0x4        /* 512ns to less than 1us */
    #define  PCI_EXP_L0S_1US_to_2US        0x5        /* 1us to less than 2us */
    #define  PCI_EXP_L0S_2US_to_4US        0x6        /* 2us to less than 4us */
    #define  PCI_EXP_L0S_GT_4US            0x7        /* Greater than 4us */
#define  PCI_EXP_DEVCAP_L1                 0xe00      /* EndPt L1 Acceptable Latency */
    #define  PCI_EXP_L1_LT_1US             0x0        /* Less than 1us */
    #define  PCI_EXP_L1_1US_to_2US         0x1        /* 1us to less than 2us */
    #define  PCI_EXP_L1_2US_to_4US         0x2        /* 2us to less than 4us */
    #define  PCI_EXP_L1_4US_to_8US         0x3        /* 4us to less than 8us */
    #define  PCI_EXP_L1_8US_to_16US        0x4        /* 8us to less than 16us */
    #define  PCI_EXP_L1_16US_to_32US       0x5        /* 16us to less than 32us */
    #define  PCI_EXP_L1_32US_to_64US       0x6        /* 32us to less than 64us */
    #define  PCI_EXP_L1_GT_64US            0x7        /* Greater than 64us */
#define  PCI_EXP_DEVCAP_ATTN_BUTTON        0x1000     /* Attention Button Present */
#define  PCI_EXP_DEVCAP_ATTN_IND           0x2000     /* Attention Indicator Present */
#define  PCI_EXP_DEVCAP_PWR_IND            0x4000     /* Power Indicator Present */
#define  PCI_EXP_DEVCAP_PWR_VAL_LIMIT      0x3fc0000  /* Captured Slot Power Limit Value */
#define  PCI_EXP_DEVCAP_PWR_SCL_LIMIT      0xc000000  /* Captured Slot Power Limit Scale */
    #define  PCI_EXP_PWR_SCL_LIMIT_ONE     0x0        /* 1.0 times */
    #define  PCI_EXP_PWR_SCL_LIMIT_10TH    0x1        /* 0.1 times */
    #define  PCI_EXP_PWR_SCL_LIMIT_100TH   0x2        /* 0.01 times */
    #define  PCI_EXP_PWR_SCL_LIMIT_1000TH  0x3        /* 0.001 times */
    /*
     * The Slot Power Limit and Slot Power Limit Scale values are either automatically set 
     * by a "Set Slot Power Limit Message" rec'd from port on downstream end, or 
     * hardwired to zero.
     *
     * To calculate Power Limit:
     *     Pwr Limit (watts) = value of Slot Power Limit x value of Slot Power Limit Scale
     */ 

#define  PCI_EXP_DEVCAP_FLV_RST           0x10000000  /* function level reset */


/* PCI Express Device Control Register */

#define PCI_EXP_DEVCTL_REG             0x08    /* PCI Express Dev. Ctrl Reg. Offset */
       
#define  PCI_EXP_DEVCTL_CERR_ENB    0x0001  /* Correctable Error Reporting En. */
#define  PCI_EXP_DEVCTL_NFERR_ENB   0x0002  /* Non-Fatal Error Reporting Enable */
#define  PCI_EXP_DEVCTL_FERR_ENB    0x0004  /* Fatal Error Reporting Enable */
#define  PCI_EXP_DEVCTL_URREP_ENB   0x0008  /* Unsupported Request Reporting En. */
#define  PCI_EXP_DEVCTL_RLX_ORD_ENB 0x0010  /* Enable relaxed ordering */
#define  PCI_EXP_DEVCTL_PAYLOAD     0x00e0  /* Max Payload Size */
    /* See Device Capabilities Register for Max Payload bit defines */
#define  PCI_EXP_DEVCTL_EXT_TAG     0x0100  /* Extended Tag Field Enable */
    /* See Device Capabilities Register for Tag Field bit defines */
#define  PCI_EXP_DEVCTL_PHANTOM     0x0200  /* Phantom Functions Enable */
    /* See Device Capabilities Register for Phantom Function bit defines */
#define  PCI_EXP_DEVCTL_AUX_PM_ENB  0x0400  /* Auxiliary Power PM Enable */
#define  PCI_EXP_DEVCTL_NOSNOOP_ENB 0x0800  /* Enable No Snoop */
#define  PCI_EXP_DEVCTL_READ_REQ    0x7000  /* Max Read Request Size */
    #define  PCI_EXP_READ_REQ_128   0x0     /* 128 bytes max */
    #define  PCI_EXP_READ_REQ_256   0x1     /* 256 bytes max */
    #define  PCI_EXP_READ_REQ_512   0x2     /* 512 bytes max */
    #define  PCI_EXP_READ_REQ_1KB   0x3     /* 1K bytes max */
    #define  PCI_EXP_READ_REQ_2KB   0x4     /* 2K bytes max */
    #define  PCI_EXP_READ_REQ_4KB   0x5     /* 4K bytes max */

#define  PCI_EXP_DEVCTL_FLV_RST    0x8000   /* function level reset */


/* PCI Express Device Status Register */

#define PCI_EXP_DEVSTA_REG          0x0A    /* PCI Express Dev. Status Reg. Offset */

#define  PCI_EXP_DEVSTA_CERR_DET    0x1    /* Correctable Error Detected RW1C */
#define  PCI_EXP_DEVSTA_NFERR_DET   0x2    /* Non-Fatal Error Detected RW1C*/
#define  PCI_EXP_DEVSTA_FERR_DET    0x4    /* Fatal Error Detected RW1C */
#define  PCI_EXP_DEVSTA_UNREQ_DET   0x8    /* Unsupported Request Detected */
#define  PCI_EXP_DEVSTA_AUXPWR_DET  0x10   /* AUX Power Detected RO */
#define  PCI_EXP_DEVSTA_TRAN_PEND   0x20   /* Transactions Pending RO */

/* PCI Express Link Capabilities Register */

#define PCI_EXP_LNKCAP_REG           0x0C    /* PCI Express Link Capab. Reg. Offset */

#define  PCI_EXP_LNKCAP_LNK_SPD         0xF         /* Max Link Speed */
    #define  PCI_EXP_LNK_SPD_2PT5GB     0x1         /* 2.5 Gb/s */
#define  PCI_EXP_LNKCAP_LNK_WDTH        0x3F0       /* Max Link Width */
    #define  PCI_EXP_LNK_WDTH_1         0x1         /* x1 */
    #define  PCI_EXP_LNK_WDTH_2         0x2         /* x2 */
    #define  PCI_EXP_LNK_WDTH_4         0x4         /* x4 */
    #define  PCI_EXP_LNK_WDTH_8         0x8         /* x8 */
    #define  PCI_EXP_LNK_WDTH_12        0xC         /* x12 */
    #define  PCI_EXP_LNK_WDTH_16        0x10        /* x16 */
    #define  PCI_EXP_LNK_WDTH_32        0x20        /* x32 */
#define  PCI_EXP_LNKCAP_ASPM            0xC00       /* Active State Mgmt Support */
    #define  PCI_EXP_ASPM_L0            0x1         /* L0s Entry Supported */
    #define  PCI_EXP_ASPM_L0_L1         0x3         /* L0s & L1s Supported */
#define  PCI_EXP_LNKCAP_L0S_LAT         0x7000      /* L0s Exit Latency */
    /* See Device Capabilities Register for L0 Latency bit defines */
#define  PCI_EXP_LNKCAP_L1_LAT          0x38000     /* L1s Exit Latency */
    /* See Device Capabilities Register for L1 Latency bit defines */
#define  PCI_EXP_LNKCAP_PORTNO          0xFF000000  /* Port Number */
    /* Port Number is assigned in HW */

/* PCI Express Link Control Register */

#define PCI_EXP_LNKCTL_REG           0x10    /* PCI Express Link Ctl. Reg. Offset */

#define PCI_EXP_LNKCTL_ASPM             0x3         /* Active State Mgmt Ctrl */
#define PCI_EXP_LNKCTL_RCB              0x8         /* Read Completion Boundary */
#define PCI_EXP_LNKCTL_LNK_DIS          0x10        /* Link Disable */
#define PCI_EXP_LNKCTL_LNK_TRAIN        0x20        /* Link Retrain; Reads 0 */
#define PCI_EXP_LNKCTL_CCC              0x40        /* Common Clk Config */
#define PCI_EXP_LNKCTL_EXT_SYNC         0x80        /* Extended Sync */

/* PCI Express Link Status Register */

#define PCI_EXP_LNKSTA_REG           0x12    /* PCI Express Link Status Reg. Offset */

#define PCI_EXP_LNKSTA_LNK_SPD          0xF         /* Link Speed */
    /* See Link Capabilities Register for Link Speed bit defines */
#define PCI_EXP_LNKSTA_LNK_WDTH         0x3F0       /* Negotiead Link Width */
    /* See Link Capabilities Register for Link Width bit defines */
#define PCI_EXP_LNKSTA_LNK_TERR         0x400       /* Link Training Error */
#define PCI_EXP_LNKSTA_LNK_TRAIN        0x800       /* Link Training */
#define PCI_EXP_LNKSTA_LNK_CLKCFG       0x1000      /* Slot Clk Config. */
#define  PCI_EXP_LNKSTA_DLLLA           0x2000          /* Data Link Layer Link Active */

/* PCI Express Slot Capabilities Register */

#define PCI_EXP_SLTCAP_REG             0x14    /* PCI Express Slot Capab. Reg. Offset */

#define PCI_EXP_SLTCAP_ATTN_BUT         0x1            /* Attention Button Present */
#define PCI_EXP_SLTCAP_PWR_CTL          0x2            /* Power Controller Present */
#define PCI_EXP_SLTCAP_MRL              0x4            /* MRL Sensor Present */
#define PCI_EXP_SLTCAP_ATTN_IND         0x8            /* Attention Indicator Present */
#define PCI_EXP_SLTCAP_PWR_IND          0x10           /* Power Indicator Present */
#define PCI_EXP_SLTCAP_HPL_SUP          0x20           /* Hot Plug Surprise */
#define PCI_EXP_SLTCAP_HPL_CAP          0x40           /* Hot Plug Capable */
#define PCI_EXP_SLTCAP_PWR_VAL_LIMIT    0x7F80         /* Slot Pwr Limit Value */
#define PCI_EXP_SLTCAP_PWR_SCL_LIMIT    0x18000        /* Slot Pwr Limit Scale */
    /* See Device Capabilities Register for Slot Power Scale bit defines */
#define PCI_EXP_SLTCAP_PHYS_SLOT        0xFFF80000     /* Physical Slot No. */
#define  PCI_EXP_SLTCAP_EIP         0x00020000              /* Electromechanical Interlock Present */
#define  PCI_EXP_SLTCAP_NCCS            0x00040000 /* No Command Completed Support */

/* PCI Express Slot Control Register */

#define PCI_EXP_SLTCTL_REG             0x18    /* PCI Express Slot Status Reg. Offset */

#define PCI_EXP_SLTCTL_ATTN_BUT_ENB     0x1            /* Attention Button Pressed Enabled */
#define PCI_EXP_SLTCTL_PWRFLT_DET_ENB   0x2            /* Power Fault Detected Enabled */
#define PCI_EXP_SLTCTL_MRLSNSR_ENB      0x4            /* MRL Sensor Changed Enabled */
#define PCI_EXP_SLTCTL_PRES_DET_ENB     0x8            /* Presence Detect Changed Enabled */
#define PCI_EXP_SLTCTL_CCMPLT_ENB       0x10           /* Command Complete Interrupt Enabled */
#define PCI_EXP_SLTCTL_HPLINT_ENB       0x20           /* Hot Plug Interrupt Enabled */
#define PCI_EXP_SLTCTL_ATTN_INDCTL      0xC0           /* Attention Indicator Control */
    #define PCI_EXP_ATTN_INDCTL_ON      0x1            /* Attention Indicator Control */
    #define PCI_EXP_ATTN_INDCTL_BLINK   0x2            /* Attention Indicator Control */
    #define PCI_EXP_ATTN_INDCTL_OFF     0x3            /* Attention Indicator Control */
#define PCI_EXP_SLTCTL_PWR_INDCTL       0x300          /* Power Indicator Control */
    #define PCI_EXP_PWR_INDCTL_ON       0x1            /* Power Indicator Control */
    #define PCI_EXP_PWR_INDCTL_BLINK    0x2            /* Power Indicator Control */
    #define PCI_EXP_PWR_INDCTL_OFF      0x3            /* Power Indicator Control */
#define PCI_EXP_SLTCTL_PWR_CTLRCTL      0x400          /* Power Controller Control */
    #define PCI_EXP_PWR_CTLRCTL_ON      0x0            /* Power Controller Control */
    #define PCI_EXP_PWR_CTLRCTL_OFF     0x1            /* Power Controller Control */
#define PCI_EXP_SLTCTL_DLINK_CHANGE_ENABLE 0x1000      /* Link Layer status change Enable */
#define PCI_EXP_SLTCTL_ELE_LOCK         0x800      /* Electromechanical Interlock */


/* PCI Express Slot Status Register */

#define PCI_EXP_SLTSTA_REG             0x1A    /* PCI Express Slot Status Reg. Offset */

#define PCI_EXP_SLTSTA_ATTN_BUT         0x1            /* Attention Button Pressed */
#define PCI_EXP_SLTSTA_PWRFLT_DET       0x2            /* Power Fault Detected */
#define PCI_EXP_SLTSTA_MRLSNSR          0x4            /* MRL Sensor Changed */
#define PCI_EXP_SLTSTA_PRES_DET         0x8            /* Presence Detect Changed */
#define PCI_EXP_SLTSTA_CCMPLT           0x10           /* Command Completed */
#define PCI_EXP_SLTSTA_MRLSNSR_STAT     0x20           /* MRL Sensor Status */
    #define PCI_EXP_MRLSNSR_STAT_CLSD   0x0            /* MRL Sensor Status */
    #define PCI_EXP_MRLSNSR_STAT_OPEN   0x1            /* MRL Sensor Status */
#define PCI_EXP_SLTSTA_PRES_DET_STAT    0x40           /* Presence Detect Status */
    #define PCI_EXP_PRES_DET_STAT_EMPTY 0x0            /* Presence Detect Status */
    #define PCI_EXP_PRES_DET_STAT_PRES  0x1            /* Presence Detect Status */

/* PCI Express Root Control Register */

#define PCI_EXP_RTCTL_REG        0x1C      /* Root Control Register */

#define  PCI_EXP_RTCTL_SECE_ENB    0x01    /* System Error on Correctable Error */
#define  PCI_EXP_RTCTL_SENFE_ENB   0x02    /* System Error on Non-Fatal Error */
#define  PCI_EXP_RTCTL_SEFE_ENB    0x04    /* System Error on Fatal Error */
#define  PCI_EXP_RTCTL_PMEI_ENB    0x08    /* PME Interrupt Enable */

/* PCI Express Root Status Register */

#define PCI_EXP_RTSTA            0x20      /* Root Status */

/* Extended Capabilities (PCI-X 2.0 and Express) */

#define PCI_EXT_CAP_ID(header)          (header & 0x0000ffff)
#define PCI_EXT_CAP_VER(header)         ((header >> 16) & 0xf)
#define PCI_EXT_CAP_NEXT(header)        ((header >> 20) & 0xffc)

/* Extended Capabilities BAR */

#define PCI_EXT_CAP_BASE        0x100

/* Extended Capabilities AER */

#define PCIE_EXT_CAP_ID_ERR         0x1
   #define PCIE_AER_UNCRERR_STATUS      0x4   /* Uncorrectable Error Status Register Offset */
   #define PCIE_AER_UNCRERR_MASK        0x8   /* Uncorrectable Error Mask Register Offset */
   #define PCIE_AER_UNCRERR_SEVERITY    0xC   /* Uncorrectable Error Severity Register Offset */
   #define PCIE_AER_CRERR_STATUS        0x10  /* Correctable Error Status Register Offset */
   #define PCIE_AER_CRERR_MASK          0x14  /* Correctable Error Mask Register Offset */
   #define PCIE_AER_CONTROL             0x18  /* Advanced Error Capabilities and Control Register Offset */
   #define PCIE_AER_HEADER_LOG          0x1C  /* Header Log Register Offset */
   #define PCIE_AER_ROOT_ERR_COMMAND    0x2C  /* Root Error Command Register Offset */
   #define PCIE_AER_ROOT_ERR_STATUS     0x30  /* Root Error Status Register Offset */
   #define PCIE_AER_ROOT_CESIR          0x34  /* Error Source Identification Register Offset */
   #define PCIE_AER_TLP_LOG             0x38  /* TLP Prefix Log Register Offset */

/* Advanced Error Reporting */

#define PCIE_AER_UNCRERR_STATUS     0x4             /* Uncorrectable Error Status */
    #define  PCI_AER_UNC_UND            0x00000001  /* Undefined */
    #define  PCI_AER_UNC_DLP            0x00000010  /* Data Link Protocol */
    #define  PCI_AER_UNC_SURPDN         0x00000020  /* Surprise Down */
    #define  PCI_AER_UNC_POISON_TLP     0x00001000  /* Poisoned TLP */
    #define  PCI_AER_UNC_FCP            0x00002000  /* Flow Control Protocol */
    #define  PCI_AER_UNC_COMP_TIME      0x00004000  /* Completion Timeout */
    #define  PCI_AER_UNC_COMP_ABORT     0x00008000  /* Completer Abort */
    #define  PCI_AER_UNC_UNX_COMP       0x00010000  /* Unexpected Completion */
    #define  PCI_AER_UNC_RX_OVER        0x00020000  /* Receiver Overflow */
    #define  PCI_AER_UNC_MALF_TLP       0x00040000  /* Malformed TLP */
    #define  PCI_AER_UNC_ECRC           0x00080000  /* ECRC Error Status */
    #define  PCI_AER_UNC_UNSUP          0x00100000  /* Unsupported Request */
    #define  PCI_AER_UNC_ACSV           0x00200000  /* ACS Violation */
    #define  PCI_AER_UNC_INTN           0x00400000  /* internal error */
    #define  PCI_AER_UNC_MCBTLP         0x00800000  /* MC blocked TLP */
    #define  PCI_AER_UNC_ATOMEG         0x01000000  /* Atomic egress blocked */
    #define  PCI_AER_UNC_TLPPRE         0x02000000  /* TLP prefix blocked */
    
#define PCIE_AER_UNCRERR_MASK       0x8             /* Uncorrectable Error Mask */
#define PCIE_AER_UNCRERR_SEVERITY   0xC             /* Uncorrectable Error Severity */

#define PCIE_AER_CRERR_STATUS       0x10            /* Correctable Error Status */
    #define  PCI_AER_COR_RCVR           0x00000001  /* Receiver Error Status */
    #define  PCI_AER_COR_BAD_TLP        0x00000040  /* Bad TLP Status */
    #define  PCI_AER_COR_BAD_DLLP       0x00000080  /* Bad DLLP Status */
    #define  PCI_AER_COR_REP_ROLL       0x00000100  /* REPLAY_NUM Rollover */
    #define  PCI_AER_COR_REP_TIMER      0x00001000  /* Replay Timer Timeout */
    #define  PCI_AER_COR_ADV_NFAT       0x00002000  /* Advisory Non-Fatal */
    #define  PCI_AER_COR_INTERNAL       0x00004000  /* Corrected Internal */
    #define  PCI_AER_COR_LOG_OVER       0x00008000  /* Header Log Overflow */
    
#define PCIE_AER_CRERR_MASK         0x14            /* Correctable Error Mask */
#define PCIE_AER_CONTROL            0x18            /* Advanced Error Capabilities */
    #define  PCI_AER_CAP_FEP(x) ((x) & 31)          /* First Error Pointer */
    #define  PCI_AER_CAP_ECRC_GENC      0x00000020  /* ECRC Generation Capable */
    #define  PCI_AER_CAP_ECRC_GENE      0x00000040  /* ECRC Generation Enable */
    #define  PCI_AER_CAP_ECRC_CHKC      0x00000080  /* ECRC Check Capable */
    #define  PCI_AER_CAP_ECRC_CHKE      0x00000100  /* ECRC Check Enable */

#define PCIE_AER_HEADER_LOG         0x1C            /* Header Log Register (16 bytes) */
#define PCIE_AER_ROOT_ERR_COMMAND   0x2C            /* Root Error Command */    
    #define PCI_AER_ROOT_CMD_COR_EN     0x00000001  /* Correctable Err Reporting Enable */
    #define PCI_AER_ROOT_CMD_NONFATAL_EN 0x00000002 /* Non-fatal Err Reporting Enable */
    #define PCI_AER_ROOT_CMD_FATAL_EN   0x00000004  /* Fatal Err Reporting Enable */

#define PCIE_AER_ROOT_ERR_STATUS    0x30
    #define PCI_AER_ROOT_COR_RCV        0x00000001  /* ERR_COR Received */
    #define PCI_AER_ROOT_MULTI_COR_RCV  0x00000002  /* Multi ERR_COR Received */
    #define PCI_AER_ROOT_UNCOR_RCV      0x00000004  /* ERR_FATAL/NONFATAL Received */
    #define PCI_AER_ROOT_MULTI_UNCOR_RCV 0x00000008 /* Multi ERR_FATAL/NONFATAL Received */
    #define PCI_AER_ROOT_FIRST_FATAL    0x00000010  /* First Fatal */
    #define PCI_AER_ROOT_NONFATAL_RCV   0x00000020  /* Non-Fatal Received */
    #define PCI_AER_ROOT_FATAL_RCV      0x00000040  /* Fatal Received */
    
#define PCIE_AER_ROOT_CESIR         0x34            /* Error Source Identification */
#define PCIE_AER_TLP_LOG            0x38            /* TLP Prefix Log Register Offset */

/* Virtual Channel Capability */

#define PCIE_EXT_CAP_ID_VC                      2
#define PCIE_EXT_CAP_ID_VC2                     9

/* Device Serial Number Capability */

#define PCIE_EXT_CAP_ID_DSN                     3

/* Root Complex Internal Link Control Capability */

#define PCIE_EXT_CAP_ID_PWR                     4

/* Root Complex Link Declaration Capability */

#define PCIE_EXT_CAP_ID_RC_LINKD                5

/* Root Complex Internal Link Control Capability */

#define PCIE_EXT_CAP_ID_RCI_LINKD               6

/* Root Complex Event Collector Endpoint Association Capability */

#define PCIE_EXT_CAP_ID_RC_ECEA                 7

/* Multi-Function Virtual Channel Capability */

#define PCIE_EXT_CAP_ID_MFVC                    8

/* RCRB Header Capability */

#define PCIE_EXT_CAP_ID_RCRB                    10

/* Vendor-Specific Capability */

#define PCIE_EXT_CAP_ID_VNDR                    11

/* ACS Extended Capability */

#define PCIE_EXT_CAP_ID_ACS                     13

/* ARI Capability */

#define PCIE_EXT_CAP_ID_ARI                     14

/* Address Translation Services */

#define PCIE_EXT_CAP_ID_ATS                     15

/* Single root input/output virtualization */

#define PCIE_EXT_CAP_ID_SRIOV                   16

/* Multicast Capability */

#define PCIE_EXT_CAP_ID_MULCAST                 18

/* Resizable BAR Capability */

#define PCIE_EXT_CAP_ID_RSIZEBAR                21

/* Dynamic Power Allocation (DPA) Capability */

#define PCIE_EXT_CAP_ID_DPA                     22

/* TPH Requester Capability */

#define PCIE_EXT_CAP_ID_TPH                     23

/* Latency Tolerance Reporting (LTR) Capability */

#define PCIE_EXT_CAP_ID_LTR                     24

/* Secondary PCI Express Extended Capability */

#define PCIE_EXT_CAP_ID_SECOND_EXT              25

/* PMUX Extended Capability */

#define PCIE_EXT_CAP_ID_PMUX                    26


/* MSI-X registers */

#define PCI_MSIX_CTL                    0x02    /* Offset of MSI-X control register */
#define PCI_MSIX_CTL_TABLE_SIZE         0x7ff
#define PCI_MSIX_CTL_FUNCTION_MASK      0x4000
#define PCI_MSIX_CTL_ENABLE             0x8000  /* MSI-X enable */

#define PCI_MSIX_TABLE                  0x04
#define PCI_MSIX_TABLE_OFFSET_MASK      0xfffffff8
#define PCI_MSIX_TABLE_BIR_MASK         0x07

#define PCI_MSIX_PBA                    0x08
#define PCI_MSIX_PBA_OFFSET_MASK        0xfffffff8
#define PCI_MSIX_PBA_BIR_MASK           0x07

/* MSI-X Table Entry Dword offset */

#define PCI_MSIX_MSG_ADDR_LOW           0x00
#define PCI_MSIX_MSG_ADDR_HIGH          0x01
#define PCI_MSIX_MSG_DATA               0x02
#define PCI_MSIX_MSG_CTRL               0x03
#define PCI_MSIX_MSG_CTRL_MASK          (1 << 0)

/* Message Signaled Interrupts registers */

/* Message Control Register */

#define PCI_MSI_CTL                     0x02    /* Offset of MSI control register */
#define PCI_MSI_CTL_ENABLE              0x01    /* MSI enable */
#define PCI_MSI_CTL_MSG_ALLOC           0x70    /* Number of Messages allocated */
#define PCI_MSI_CTL_MSG_MAX             0x0E    /* Maximum Messages Allowed */
#define PCI_MSI_CTL_64BIT               0x80    /* 64-bit addresses allowed */
#define PCI_MSI_CTL_MASK                0x100   /* Per-vector masking capable */

/* Message Address Register */

#define PCI_MSI_ADDR_LO                 0x04    /* Offset of MSI Address Lower 32 bits */
                                                /* Used for 32-bit MSI */  
#define PCI_MSI_ADDR_HI                 0x08    /* Offset of MSI Address Upper 32 bits */
                                                /* Used with 64-bit MSI */
/* Message Data Register */

#define PCI_MSI_DATA_32                 0x08    /* Offset of MSI Data Register */
                                                /* Used for 32-bit MSI */
#define PCI_MSI_DATA_64                 0x0C    /* Offset of MSI Data Register */
                                                /* Used for 64-bit MSI */
/* Message Per-Vector Mask Register */

#define PCI_MSI_MASK_32                 0x0C    /* Offset of MSI Mask Register */
                                                /* Used for 32-bit MSI */
#define PCI_MSI_MASK_64                 0x10    /* Offset of MSI Mask Register */
                                                /* Used for 64-bit MSI */

#define MSI_ENABLED (ctlReg)       (ctlReg & PCI_MSI_CTL_ENABLE)
#define ADDR_64BIT (ctlReg)        (ctlReg & PCI_MSI_CTL_64BIT)

#define MSI_ENABLE_MSG (ctlReg, msgNum) \
    ctlReg |= (((msgNum >> 1) << 4) & PCI_MSI_CTL_MESS_ALLOC);

#define MSI_ENABLE (ctlReg, msgNum) MSI_ENABLE_MSG (ctlReg, msgNum); \
    ctlReg |= PCI_MSI_FLAGS_ENABLE

#define MSI_DISABLE (ctlReg)        ctlReg &= ~PCI_MSI_CTL_ENABLE



/* PCI-X Non-Bridged Configuration Registers */

/* PCI-X Capability Command Register */

#define  PCI_X_CMD               0x02    /* Offset of PCI-X command register */
#define  PCI_X_CMD_DPERR_ENB     BIT(0)  /* Data Parity Error Recovery Enable */
#define  PCI_X_CMD_RO_ENB        BIT(1)  /* Enable Relaxed Ordering */
#define  PCI_X_CMD_MAX_READ      0xc     /* Max Memory Read Byte Count */
#define  PCI_X_CMD_MAX_SPLIT     0x70    /* Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_1   0x0     /* 1 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_2   0x1     /* 2 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_3   0x2     /* 3 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_4   0x3     /* 4 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_8   0x4     /* 8 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_12  0x5     /* 12 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_16  0x6     /* 16 Max Outstanding Split Trans. */
    #define  PCI_X_MAX_SPLIT_32  0x7     /* 32 Max Outstanding Split Trans. */


/* PCI-X Capability Status Register */

#define  PCI_X_STATUS              0x04         /* Offset of PCI-X status register */
#define  PCI_X_STATUS_FUNC_NUM     0x7          /* Function Number */
#define  PCI_X_STATUS_DEV_NUM      0xF8         /* Device Number */
#define  PCI_X_STATUS_BUS_NUM      0xFF00       /* Bus Number */
#define  PCI_X_STATUS_64BIT        0x10000      /* 64-bit device */
#define  PCI_X_STATUS_133MHZ       0x20000      /* 133 MHz Capable */
#define  PCI_X_STATUS_SCOMP_DISC   0x40000      /* Split Completion Discarded */
#define  PCI_X_STATUS_UNEX_SCOMP   0x80000      /* Unexpected Split Completion */
#define  PCI_X_STATUS_DEVCPLX      0x100000     /* Device Complexity */
#define  PCI_X_STATUS_MAX_READ     0x600000     /* Designed Max Memory Read Byte Count */
#define  PCI_X_STATUS_MAX_SPLIT    0x3800000    /* Designed Max Outstanding Split Trans. */
#define  PCI_X_STATUS_MAX_CUMRD    0x1c000000   /* Designed Max Cumulative Read Size */
#define  PCI_X_STATUS_SCOMP_ERR    0x20000000   /* Rcv'd Split Completion Error Msg */
#define  PCI_X_STATUS_266MHZ       0x40000000   /* 266 MHz capable */
#define  PCI_X_STATUS_533MHZ       0x80000000   /* 533 MHz capable */


/* PCI-X Bridged Configuration Registers */

/* PCI-X Capability Secondary Status Register */

#define  PCI_X_SECSTAT             0x02          /* Offset of PCI-X 2ndary status register */
#define  PCI_X_SECSTAT_64BIT       0x1           /* 64-bit device */
#define  PCI_X_SECSTAT_133MHZ      0x2           /* 133MHz Capable */
#define  PCI_X_SECSTAT_SCOMP_DISC  0x4           /* Split Completion Discarded */
#define  PCI_X_SECSTAT_UNEX_SCOMP  0x8           /* Unexpected Split Completion */
#define  PCI_X_SECSTAT_SCOMP_ORUN  0x10          /* Split Completion Overrun */
#define  PCI_X_SECSTAT_SCOMP_DLYD  0x20          /* Split Request Delayed */
#define  PCI_X_SECSTAT_CLKFREQ     0x1C0         /* Secondary Clock Freq. */
    
/* PCI-X Capability Primary Status Register */

#define  PCI_X_PRISTAT             0x04                     /* Offset of bridge status register */
#define  PCI_X_PRISTAT_FUNC_NUM    PCI_X_STATUS_FUNC_NUM    /* Function Number */
#define  PCI_X_PRISTAT_DEV_NUM     PCI_X_STATUS_DEV_NUM     /* Device Number */
#define  PCI_X_PRISTAT_BUS_NUM     PCI_X_STATUS_BUS_NUM     /* Bus Number */
#define  PCI_X_PRISTAT_64BIT       PCI_X_STATUS_64BIT       /* 64-bit device */
#define  PCI_X_PRISTAT_133MHZ      PCI_X_STATUS_133MHZ      /* 133 MHz capable */
#define  PCI_X_PRISTAT_SCOMP_DISC  PCI_X_STATUS_SCOMP_DISC  /* Split Completion Discarded */
#define  PCI_X_PRISTAT_UNEX_SCOMP  PCI_X_STATUS_UNEX_SCOMP  /* Unexpected Split Completion */
#define  PCI_X_PRISTAT_SCOMP_ORUN  0x100000                 /* Split Completion Overrun */
#define  PCI_X_PRISTAT_SCOMP_DLYD  0x200000                 /* Split Request Delayed */

/* PCI-X Capability Upstream Split Transaction Control Register */

#define  PCI_X_UP_SXACTION_CTRL    0x08
#define  PCI_X_UP_SXACTION_CAP     0xFF      /* Split Xaction Capacity Register RO */
#define  PCI_X_UP_SXACTION_LIMIT   0xFF00    /* Split Xaction Commit Limit Register */
    

/* PCI-X Capability Downstream Split Transaction Control Register */

#define  PCI_X_DWN_SXACTION_CTRL   0x0C
#define  PCI_X_DWN_SXACTION_CAP    PCI_X_UP_SXACTION_CAP   /* Split Xaction Capacity Reg. RO */
#define  PCI_X_DWN_SXACTION_LIMIT  PCI_X_UP_SXACTION_LIMIT /* Split Xaction Commit Limit Reg. */

/* structure for the device & bridge header */

typedef struct pciHeaderDevice
    {
    short   vendorId;   /* vendor ID */
    short   deviceId;   /* device ID */
    short   command;    /* command register */
    short   status;     /* status register */
    char    revisionId; /* revision ID */
    char    classCode;  /* class code */
    char    subClass;   /* sub class code */
    char    progIf;     /* programming interface */
    char    cacheLine;  /* cache line */
    char    latency;    /* latency time */
    char    headerType; /* header type */
    char    bist;       /* BIST */
    int     base0;      /* base address 0 */
    int     base1;      /* base address 1 */
    int     base2;      /* base address 2 */
    int     base3;      /* base address 3 */
    int     base4;      /* base address 4 */
    int     base5;      /* base address 5 */
    int     cis;        /* cardBus CIS pointer */
    short   subVendorId;    /* sub system vendor ID */
    short   subSystemId;    /* sub system ID */
    int     romBase;    /* expansion ROM base address */
    int     reserved0;  /* reserved */
    int     reserved1;  /* reserved */
    char    intLine;    /* interrupt line */
    char    intPin;     /* interrupt pin */
    char    minGrant;   /* min Grant */
    char    maxLatency; /* max Latency */
    } PCI_HEADER_DEVICE;

typedef struct pciHeaderBridge
    {
    short   vendorId;   /* vendor ID */
    short   deviceId;   /* device ID */
    short   command;    /* command register */
    short   status;     /* status register */
    char    revisionId; /* revision ID */
    char    classCode;  /* class code */
    char    subClass;   /* sub class code */
    char    progIf;     /* programming interface */
    char    cacheLine;  /* cache line */
    char    latency;    /* latency time */
    char    headerType; /* header type */
    char    bist;       /* BIST */
    int     base0;      /* base address 0 */
    int     base1;      /* base address 1 */
    char    priBus;     /* primary bus number */
    char    secBus;     /* secondary bus number */
    char    subBus;     /* subordinate bus number */
    char    secLatency; /* secondary latency timer */
    char    ioBase;     /* IO base */
    char    ioLimit;    /* IO limit */
    short   secStatus;  /* secondary status */
    short   memBase;    /* memory base */
    short   memLimit;   /* memory limit */
    short   preBase;    /* prefetchable memory base */
    short   preLimit;   /* prefetchable memory limit */
    int     preBaseUpper;   /* prefetchable memory base upper 32 bits */
    int     preLimitUpper;  /* prefetchable memory base upper 32 bits */
    short   ioBaseUpper;    /* IO base upper 16 bits */
    short   ioLimitUpper;   /* IO limit upper 16 bits */
    int     reserved;   /* reserved */
    int     romBase;    /* expansion ROM base address */
    char    intLine;    /* interrupt line */
    char    intPin;     /* interrupt pin */
    short   control;    /* bridge control */
    } PCI_HEADER_BRIDGE;

typedef struct pciHeaderCardBusBridge
    {
    short   vendorId;   /* vendor ID */
    short   deviceId;   /* device ID */
    short   command;    /* command register */
    short   status;     /* status register */
    char    revisionId; /* revision ID */
    char    classCode;  /* class code */
    char    subClass;   /* sub class code */
    char    progIf;     /* programming interface */
    char    cacheLine;  /* cache line */
    char    latency;    /* latency time */
    char    headerType; /* header type */
    char    bist;       /* BIST */
    int     base0;      /* base address 0 */
    char    capPtr;     /* capabilities pointer */
    char        reserved;   /* reserved */
    short   secStatus;  /* secondary status */
    char    priBus;     /* primary bus number */
    char    secBus;     /* secondary bus number */
    char    subBus;     /* subordinate bus number */
    char    secLatency; /* secondary latency timer */
    int     memBase0;   /* memory base 0 */
    int     memLimit0;  /* memory limit 0 */
    int     memBase1;   /* memory base 1 */
    int     memLimit1;  /* memory limit 1 */
    int     ioBase0;    /* IO base 0 */
    int     ioLimit0;   /* IO limit 0 */
    int     ioBase1;    /* IO base 1 */
    int     ioLimit1;   /* IO limit 1 */
    char    intLine;    /* interrupt line */
    char    intPin;     /* interrupt pin */
    short   control;    /* bridge control */
    short   subVendorId;    /* sub system vendor ID */
    short   subSystemId;    /* sub system ID */
    int     legacyBase; /* pccard 16-bit legacy mode base */    
    } PCI_HEADER_CB_BRIDGE;
    
#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpciHeaderDefsh */
