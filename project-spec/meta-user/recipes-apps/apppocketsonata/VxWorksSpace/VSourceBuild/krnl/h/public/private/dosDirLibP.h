/* dosDirLibP.h - private header of directory handler */

/* Copyright 1998-2001, 2004, 2006-2007, 2009-2010 Wind River Systems, Inc. */

/*
modification history
-------------------- 
01l,29apr10,pad  Moved extern C statement after include statements.
01k,15mar10,yjl  modify START_CLUST_ENCODE for removing warning
01j,05aug09,yjl  adapt for 64bit 
01i,29jun07,act  WIND00096598: rename can detach directories
01h,30nov06,pcm  changed DISK to HOST macros to function calls
01g,18apr04,act  add DOS_DEL_SUBST (0xe5 <=> 0x05 in file names);
		 get rid of DIRENT_PTR (different in old vs VFAT dirs);
		 change VFAT-specific data and identify them by name
01f,20sep01,jkf  SPR#69031, common code for both AE & 5.x.
01e,29feb00,jkf  T3 changes
01d,31jul99,jkf  T2 merge, tidiness & spelling.
01c,22nov98,vld  fields <rootNSec> and <rootStartSec> moved from
		 DOS_DIR_PDESCR structure to structure DOS_DIR_DESC
		 in dosFsLibP.h header
01b,02jul98,lrn  doc review
01a,18jan98,vld	 written,
*/

#ifndef __INCdosDirLibP
#define __INCdosDirLibP

#include "vxWorks.h"
#include "semLib.h"
#include "dosFsLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DOS_VX_LONG_NAME_LEN	40	/* length of vxWorks proprietary */
					/* long filename */
#define DOS_VFAT_NAME_LEN	255	/* max W-95 style name length */

/* standard directory entry */

#define DOS_DIRENT_STD_LEN	32	/* standard directory entry size */

#define DOS_RESERVED_LEN        10      /* reserved bytes in regular dir ent */
					/* fully used by VFAT aliases */

#define DOS_STDNAME_LEN		8       /* length of filename */
					/* (no extension) */
#define DOS_STDEXT_LEN		3       /* length of filename extension */
#define DOS_ATTRIB_OFF		(DOS_STDNAME_LEN+DOS_STDEXT_LEN)
#define DOS_NAME_CASE_OFF	(DOS_ATTRIB_OFF+1)
#define DOS_CREAT_MS_OFF	(DOS_NAME_CASE_OFF+1)
#define DOS_CREAT_TIME_OFF	(DOS_CREAT_MS_OFF+1)
#define DOS_CREAT_DATE_OFF	(DOS_CREAT_TIME_OFF+2)
#define DOS_LAST_ACCESS_TIME_OFF	((u_char) NONE)
#define DOS_LAST_ACCESS_DATE_OFF	(DOS_CREAT_DATE_OFF+2)
#define DOS_EXT_START_CLUST_OFF	(DOS_LAST_ACCESS_DATE_OFF+2)
#define DOS_MODIF_TIME_OFF	(DOS_EXT_START_CLUST_OFF+2)
#define DOS_MODIF_DATE_OFF	(DOS_MODIF_TIME_OFF+2)
#define DOS_START_CLUST_OFF	(DOS_MODIF_DATE_OFF+2)
#define DOS_FILE_SIZE_OFF	(DOS_START_CLUST_OFF+2)
#define DOS_EXT_FILE_SIZE_OFF	((u_char) NONE)
#define DOS_EXT_FILE_SIZE_LEN	((u_char) NONE)

/* vxWorks proprietary long names' directory entry */

#define DOS_VX_DIRENT_LEN	64

#define DOS_VX_NAME_LEN		DOS_VX_LONG_NAME_LEN
#define DOS_VX_EXT_LEN		0	/* (no extension) */
#define DOS_VX_CREAT_TIME_OFF	(DOS_VX_NAME_LEN+DOS_VX_EXT_LEN)
#define DOS_VX_CREAT_DATE_OFF	(DOS_VX_CREAT_TIME_OFF+2)
#define DOS_VX_LAST_ACCESS_TIME_OFF	(DOS_VX_CREAT_DATE_OFF+2)
#define DOS_VX_LAST_ACCESS_DATE_OFF	(DOS_VX_LAST_ACCESS_TIME_OFF+2)
#define DOS_VX_EXT_START_CLUST_OFF	(DOS_VX_LAST_ACCESS_DATE_OFF+2)
#define DOS_VX_EXT_FILE_SIZE_OFF	(DOS_VX_EXT_START_CLUST_OFF+2)
#define DOS_VX_EXT_FILE_SIZE_LEN	2
#define DOS_VX_RESERVED_LEN	1 /* 13 -4 cr t/d -4 acc t/d -2 st cl - */
				  /* DOS_VX_EXT_FILE_SIZE_LEN */
#define DOS_VX_ATTRIB_OFF	(DOS_VX_EXT_FILE_SIZE_OFF+	\
				 DOS_VX_EXT_FILE_SIZE_LEN+	\
				 DOS_VX_RESERVED_LEN)
#define DOS_VX_MODIF_TIME_OFF	(DOS_VX_ATTRIB_OFF+1)
#define DOS_VX_MODIF_DATE_OFF	(DOS_VX_MODIF_TIME_OFF+2)
#define DOS_VX_START_CLUST_OFF	(DOS_VX_MODIF_DATE_OFF+2)
#define DOS_VX_FILE_SIZE_OFF	(DOS_VX_START_CLUST_OFF+2)

/* special values */

#define ROOT_DIRENT	NULL	/* root directory does not */
				/* have its own entry */
/* special characters */

#define LAST_DIRENT	EOS
#define INVALID_CHAR	'|'
#define ZERO_C          '0' 
#define TILDA		'~'
#define DOS_DEL_MARK	0xe5	/* dir entry deleted marker */
#define	DOS_DEL_SUBST	0x05	/* value substituted for DEL_MARK */

/* special function argument value */

/* #define DH_VOL_LAB	(-1) */
#define DH_VOL_LAB	0xFFFFFFFF

/* macros */

#define START_CLUST_DECODE( pVolDesc, pDeDesc, pDirEnt )		\
	(dosfsDiskToHost16 ((uint8_t *)(pDirEnt) +			\
		            (pDeDesc)->startClustOff) + 		\
    	  (((pVolDesc)->fatType == FAT32)?				\
	   (dosfsDiskToHost16 ((uint8_t *)(pDirEnt) +			\
			       (pDeDesc)->extStartClustOff) << 16) : 0))

#define START_CLUST_ENCODE( pDeDesc, clust, pDirEnt )			\
	{								\
	dosfsHostToDisk16 (((uint16_t)(clust)),					\
    		       (uint8_t *)(pDirEnt) + (pDeDesc)->startClustOff ); \
	dosfsHostToDisk16 ((uint16_t)((clust) >> 16),				\
    		       (uint8_t *)(pDirEnt) +				\
		       (pDeDesc)->extStartClustOff );			\
	}

#ifdef SIZE64	/* 64-bit file sizes,  defined in dosFsLibP.h */
#define EXT_SIZE_DECODE( pDeDesc, pDirEnt )			\
        ( (fsize_t)(dosfsDiskToHost32 ((uint8_t  *)(pDirEnt) +	\
			            (pDeDesc)->extSizeOff ) &	\
	             ( ~((UINT32)(-1)<<				\
			 ((pDeDesc)->extSizeLen * 8)) ) ) << 32 )

#define EXT_SIZE_ENCODE( pDeDesc, pDirEnt, size )		\
	{							\
    	UINT32 sa, sb = ((UINT32)(size>>32));			\
    	dosfsHostToDisk32 ( sb, (uint8_t *) &sa );		\
    	bcopy( (char *)&sa,					\
		(char *)(pDirEnt) + (pDeDesc)->extSizeOff,	\
		(pDeDesc)->extSizeLen );			\
	}
#else /* ! SIZE64 */
#define EXT_SIZE_DECODE( pDeDesc, pDirEnt )		0
#define EXT_SIZE_ENCODE( pDeDesc, pDirEnt, size )		\
	bzero( (char *)(pDirEnt) + (pDeDesc)->extSizeOff,	\
	       (pDeDesc)->extSizeLen );
#endif /* SIZE64 */

/* typedefs */

typedef struct DIRENT_DESCR	/* details of directory entry */
    {
    u_char	dirEntSize,
    		nameLen,
    		extLen,
    		atrribOff,
    		creatTimeOff,
    		creatDateOff,
    		modifTimeOff,
    		modifDateOff,
    		accessTimeOff,
    		accessDateOff,
    		startClustOff,
    		extStartClustOff, /* 2 most signif. bytes of */
				  /* 32-bit FAT entry */
    		sizeOff,
    		extSizeOff,	/* n most signif. bytes of */
				/* 64-bit file size */
    		extSizeLen;	/* number of  most signif. bytes of */
				/* 64-bit file size */
    } DIRENT_DESCR;

typedef DIRENT_DESCR *	DIRENT_DESCR_ID;
typedef enum { STDDOS=0, VXLONG=1, VFAT=2 } NAME_STYLE;
typedef struct DOS_DIR_PDESCR	/* directory handler's part of */
				/* volume descriptor */
    {
    DOS_DIR_DESC	dirDesc;	/* API functions */
    void *		vfatSpace;	/* extra space for VFAT code */
    SEM_ID		vfatSem;	/* semaphore for VFAT code */
    NAME_STYLE	nameStyle;	/* name style */
    DIRENT_DESCR	deDesc;	/* volume directory entry structure */
    
    /* root directory descriptor */
    
    UINT32	rootStartClust;	/* root directory start cluster number: */
    				/* 0 for FAT12/FAT16; */
    				/* some value for FAT32 */
    u_int	rootMaxEntries;	/* max number of entries in root */
    				/* value from boot sector for */
    				/* FAT12/FAT16; 0xffffffff for FAT32 */
    time_t	rootModifTime;	/* root directory last modification time */
				/* ( last entry creation time ) */
    } DOS_DIR_PDESCR;
typedef DOS_DIR_PDESCR *	DOS_DIR_PDESCR_ID;

#ifdef __cplusplus
    }
#endif

#endif /* __INCdosDirLibP */

