/* vxbBusType.h - VxBus bus header file */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,wap  Have VXB_BUSID_MATCH() test for null bustype strings
08may15,wap  Implement new bus type mechanism to try and break
             unwanted linker dependencies between modules (F3973)
30apr14,l_z  modify the root and none busId for LP64. (US37630)
17jul13,l_z  Created
*/

#ifndef _INC_VXBBUSTYPE_H
#define _INC_VXBBUSTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/* BUS type ID */

typedef char * VXB_BUSTYPE_ID;

typedef struct vxbBusType
    {
    SL_NODE	vxbNode;
    char *	vxbBusName;
    char *	vxbBusDesc;
    } VXB_BUSTYPE;

#define BUSTYPE_DECL(NAME)
#define BUSTYPE_ID(NAME)	((VXB_BUSTYPE_ID)(#NAME))

#ifdef LKM
#define BUSTYPE_DEF(NAME, STRING)   \
VXB_BUSTYPE NAME##_desc =           \
    {                               \
        { NULL }, #NAME, STRING     \
    };                              \
void vxLkmInit ()                   \
    {                               \
    vxbClassAdd (&NAME##_desc);     \
    }
#else
#define BUSTYPE_DEF(NAME, STRING)   \
VXB_BUSTYPE NAME##_desc =           \
    {                               \
        { NULL }, #NAME, STRING     \
    };                              \
DATA_SET(bustype, 0, NAME##_desc);
#endif

/* Test for equality */

#define VXB_BUSID_MATCH(x, y)		\
	((x != VXB_BUSID_NONE) &&	\
	(y != VXB_BUSID_NONE) &&	\
	(strcmp (x, y) == 0))

/* vxbDriver->busID */

#define VXB_BUSID_ROOT		("root") /* Root of the tree (VxBus V6) */
#define VXB_BUSID_NONE		((VXB_BUSTYPE_ID)(NULL))

/* Nexux bus declaration */

BUSTYPE_DECL(vxbNexusBus);
#define VXB_BUSID_NEXUS		BUSTYPE_ID(vxbNexusBus) /* Nexus class device */


#ifdef __cplusplus
}
#endif

#endif /* _INC_VXBBUSTYPE_H */
