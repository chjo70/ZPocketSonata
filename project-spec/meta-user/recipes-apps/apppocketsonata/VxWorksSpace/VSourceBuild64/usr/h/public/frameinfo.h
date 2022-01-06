/*	Definition module : frameinfo.h

	Copyright 1998 Diab Data Inc, USA
	Copyright 2013-2014 Wind River Systems Inc

	Description :
	Frameinfo routines for walking and unwinding the stack.

	History :
	When	Who	What
	000724	fburton	Extracted from Java throw and made generic
*/

#ifndef D_frameinfo
#define D_frameinfo

#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "fnames.h"
#include "rta/rtaenv.h"

#ifdef	__cplusplus
#define	EXTERN_C extern "C"
#else
#define	EXTERN_C extern
#endif

/**************	Exported data, types and macros	*********/

#define	CPUINFO_ADDRESS(CPUINFO)	((struct cpu_info *)((((unsigned long)&(CPUINFO)) + CPUINFO_ALIGNMENT - 1) & (unsigned long)-CPUINFO_ALIGNMENT))

#if	defined(__ppc)

/*
 *	PowerPC specific
 *
 *	+----------------------------------------------------------------------++
 *	! adr ! vsz ! sk ! evsz ! fp ! vrsave ! vreg ! catch ! lr ! freg ! greg !
 *	!  32 !	 11 ! 1  !  1   !  1 !    1   !	5   !   1   !  1 !   5  !   5   !
 *	+----------------------------------------------------------------------+
 *	! adr !				    vsize			       ! *
 *	!  32 !				      32			       !
 *	+----------------------------------------------------------------------+
 *	! adr !			         catch table			       ! *
 *	!  32 !				      32			       !
 *	+----------------------------------------------------------------------+
 *
 *	PowerPC 64-bit
 *
 *	+---------------------------------------------------------------------------++
 *	! adr ! 0  ! vsz ! sk ! evsz ! fp ! vrsave ! vreg ! catch ! lr ! freg ! greg !
 *	!  64 !	32 !  11 ! 1  !  1   !  1 !    1   !  5   !   1   !  1 !   5  !   5  !
 *	+----------------------------------------------------------------------------+
 *	! adr !				    vsize			             ! *
 *	!  64 !				      64			             !
 *	+----------------------------------------------------------------------------+
 *	! adr !			         catch table			             ! *
 *	!  64 !				      64			             !
 *	+----------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(0)
#define	FRAME_EFSIZE(FRAME)	(0)
#define	FRAME_SKIP(FRAME)	((FRAME) & 0x100000)
/* We store vsize >> 1, not vsize >> 2 because VLE has only 2 byte aligned code addresses */
#define	FRAME_VSIZE(FRAME)	(((FRAME) >> 21) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x80000)
#define	FRAME_FP(FRAME)		((FRAME) & 0x40000)
#define	FRAME_VRSAVE(FRAME)	((FRAME) & 0x20000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x800)
#define	FRAME_LR(FRAME)		((FRAME) & 0x400)
#define	FRAME_VREG(FRAME)	(((FRAME) >> 12) & 0x1f)
#define	FRAME_FREG(FRAME)	(((FRAME) >> 5) & 0x1f)
#define	FRAME_GREG(FRAME)	((FRAME) & 0x1f)
#define	CPUINFO_ALIGNMENT	16

typedef struct { long long v; } floatreg_t;

#ifdef __EVEC__
typedef struct { 
	union {
		struct { unsigned long long v;             } v;		
#ifdef __BIG_ENDIAN__
		struct { unsigned long h; unsigned long l; } g;
#else
		struct { unsigned long l; unsigned long h; } g;
#endif
	} u;
} vectorreg_t;
#define	VREG_ADJUST	0

#define	GREGL(CPUINFOP,INDEX)	((CPUINFOP)->vreg[(INDEX)].u.g.l)
#define	GREGH(CPUINFOP,INDEX)	((CPUINFOP)->vreg[(INDEX)].u.g.h)
#define	VREG(CPUINFOP,INDEX)	((CPUINFOP)->vreg[(INDEX)].u.v.v)

#define	REG_LR(CPUINFOP)	(GREGL((CPUINFOP),0))
#define	REG_SP(CPUINFOP)	(GREGL((CPUINFOP),1))
#define	REG_PC(CPUINFOP)	(GREGL((CPUINFOP),2))
#define	REG_ARG(CPUINFOP)	(GREGL((CPUINFOP),3))
#define	REG_ARG2(CPUINFOP)	(GREGL((CPUINFOP),4))
#define	REG_FP(CPUINFOP)	(GREGL((CPUINFOP),31))


struct cpu_info {
	vectorreg_t	vreg[32-VREG_ADJUST];	/* Must be aligned on 16 */
	char		align[CPUINFO_ALIGNMENT-1];
};

#else
typedef struct { long long v[2]; } vectorreg_t;
#define	VREG_ADJUST	20

#define	REG_LR(CPUINFOP)	((CPUINFOP)->greg[0])
#define	REG_SP(CPUINFOP)	((CPUINFOP)->greg[1])
#define	REG_PC(CPUINFOP)	((CPUINFOP)->greg[2])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->greg[3])
#define	REG_ARG2(CPUINFOP)	((CPUINFOP)->greg[4])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->greg[31])

struct cpu_info {
	vectorreg_t	vreg[32-VREG_ADJUST];	/* Must be aligned on 16 */
	floatreg_t	freg[32-14];		/* Must be aligned on 8 */
	unsigned long	greg[32];
	unsigned long	vrsave;
	char		fsaved;
	char		vsaved;
	char		align[CPUINFO_ALIGNMENT-1];
};
#endif	/* __EVEC__ */



#ifdef __EVEC__
#define	SAVE_CPU_STATE(CPUINFOP)	(save_cpu64_state((CPUINFOP)->vreg))
#define	RESTORE_CPU_STATE(CPUINFOP)	(restore_cpu64_state((CPUINFOP)->vreg))

#else
#define	SAVE_CPU_STATE(CPUINFOP)	((CPUINFOP)->fsaved = (CPUINFOP)->vsaved = 0, save_cpu_state((CPUINFOP)->greg))
#define	RESTORE_CPU_STATE(CPUINFOP)	(((CPUINFOP)->fsaved ? restore_float_state((CPUINFOP)->freg) : (void)0), \
					 ((CPUINFOP)->vsaved ? restore_vector_state(&(CPUINFOP)->vrsave,(CPUINFOP)->vreg) : (void)0), \
					 restore_cpu_state((CPUINFOP)->greg))
#endif

asm volatile void save_cpu_state(unsigned long *gregp)
{
%reg gregp ; lab next
! "r0","r6"
	mr	r6,gregp
	mfspr	r0,lr
#ifdef __LP64__
	std	r0,0(r6)
	std	r1,8(r6)
	std	r14,112(r6)
	std	r15,120(r6)
	std	r16,128(r6)
	std	r17,136(r6)
	std	r18,144(r6)
	std	r19,152(r6)
	std	r20,160(r6)
	std	r21,168(r6)
	std	r22,176(r6)
	std	r23,184(r6)
	std	r24,192(r6)
	std	r25,200(r6)
	std	r26,208(r6)
	std	r27,216(r6)
	std	r28,224(r6)
	std	r29,232(r6)
	std	r30,240(r6)
	std	r31,248(r6)
#else
	stw	r0,0(r6)
	stw	r1,4(r6)
	stw	r14,56(r6)
	stw	r15,60(r6)
	stw	r16,64(r6)
	stw	r17,68(r6)
	stw	r18,72(r6)
	stw	r19,76(r6)
	stw	r20,80(r6)
	stw	r21,84(r6)
	stw	r22,88(r6)
	stw	r23,92(r6)
	stw	r24,96(r6)
	stw	r25,100(r6)
	stw	r26,104(r6)
	stw	r27,108(r6)
	stw	r28,112(r6)
	stw	r29,116(r6)
	stw	r30,120(r6)
	stw	r31,124(r6)
#endif
$$fn	0 0 0 0	/* no registers trashed by this call */
$$tl	0 0 0 0 /* no register params  for this call */
	bl	next
next:
	mfspr	r0,lr
#ifdef __LP64__
	std	r0,16(r6)
#else
	stw	r0,8(r6)
#endif
}

asm volatile void save_float_state(floatreg_t *fregp)
{
%reg fregp
! "r6"
	mr	r6,fregp
	stfd	f14,0(r6)
	stfd	f15,8(r6)
	stfd	f16,16(r6)
	stfd	f17,24(r6)
	stfd	f18,32(r6)
	stfd	f19,40(r6)
	stfd	f20,48(r6)
	stfd	f21,56(r6)
	stfd	f22,64(r6)
	stfd	f23,72(r6)
	stfd	f24,80(r6)
	stfd	f25,88(r6)
	stfd	f26,96(r6)
	stfd	f27,104(r6)
	stfd	f28,112(r6)
	stfd	f29,120(r6)
	stfd	f30,128(r6)
	stfd	f31,136(r6)
}


#ifdef __EVEC__
/*
 * Store the CPU state for a 64-bit CPU.  This will be
 * called by all PPC targets where the libraries are compiled
 * for 64-bit registers, i.e. VLE and E500, and use evstdd
 * instructions to Store the registers.  In some cases
 * the users code will be compiled for LSP, which does not
 * understand evstdd, does not really have 64-bit registers,
 * and must use regular stw instructions to store.  Use
 * the constant in misc.c to see if this is an architecture
 * that does not understand evstdd.
 *
 * When restoring using stw pay attention to endian.  There
 * is an operation that happens during frame unwinding that
 * will invert words if endian is not maintained.
 */
asm volatile void save_cpu64_state(vectorreg_t *vregp)
{
%reg vregp ; lab next1,next2,save_64bits,done
! "r0","r7"
#ifndef __RTP__        
#ifdef  __PPC_VLE__
	li	r7,0
	addi	r7,r7,__EVEC32BIT@l
	e_cmp16i	r7,0
#else
	addi	r7,r0,__EVEC32BIT@l
	cmpi	r7,0
#endif
        beq    	save_64bits 
	mr	r7,vregp
	mfspr	r0,lr
#ifdef __BIG_ENDIAN__
	stw	r0,4(r7)
	stw	r1,12(r7)
	stw	r14,116(r7)
	stw	r15,124(r7)
	stw	r16,132(r7)
	stw	r17,140(r7)
	stw	r18,148(r7)
	stw	r19,156(r7)
	stw	r20,164(r7)
	stw	r21,172(r7)
	stw	r22,180(r7)
	stw	r23,188(r7)
	stw	r24,196(r7)
	stw	r25,204(r7)
	stw	r26,212(r7)
	stw	r27,220(r7)
	stw	r28,228(r7)
	stw	r29,236(r7)
	stw	r30,244(r7)
	stw	r31,252(r7)
#else
	stw	r0,0(r7)
	stw	r1,8(r7)
	stw	r14,112(r7)
	stw	r15,120(r7)
	stw	r16,128(r7)
	stw	r17,136(r7)
	stw	r18,144(r7)
	stw	r19,152(r7)
	stw	r20,160(r7)
	stw	r21,168(r7)
	stw	r22,176(r7)
	stw	r23,184(r7)
	stw	r24,192(r7)
	stw	r25,200(r7)
	stw	r26,208(r7)
	stw	r27,216(r7)
	stw	r28,224(r7)
	stw	r29,232(r7)
	stw	r30,240(r7)
	stw	r31,248(r7)
#endif
$$fn	0 0 0 0
$$tl	0 0 0 0
$$dm	0 0 0 0
	bl	next1
next1:
	mfspr	r0,lr
#ifdef __BIG_ENDIAN__
	stw	r0,20(r7)
#else
	stw	r0,16(r7)
#endif
	b done
#endif
save_64bits:
	mr	r7,vregp
	mfspr	r0,lr
#ifdef __BIG_ENDIAN__
	stw	r0,4(r7)
	stw	r1,12(r7)
#else
	stw	r0,0(r7)
	stw	r1,8(r7)
#endif
	evstdd	r14,112(r7)
	evstdd	r15,120(r7)
	evstdd	r16,128(r7)
	evstdd	r17,136(r7)
	evstdd	r18,144(r7)
	evstdd	r19,152(r7)
	evstdd	r20,160(r7)
	evstdd	r21,168(r7)
	evstdd	r22,176(r7)
	evstdd	r23,184(r7)
	evstdd	r24,192(r7)
	evstdd	r25,200(r7)
	evstdd	r26,208(r7)
	evstdd	r27,216(r7)
	evstdd	r28,224(r7)
	evstdd	r29,232(r7)
	evstdd	r30,240(r7)
	evstdd	r31,248(r7)
$$fn	0 0 0 0
$$tl	0 0 0 0
$$dm	0 0 0 0
	bl	next2
next2:
	mfspr	r0,lr
#ifdef __BIG_ENDIAN__
	stw	r0,20(r7)
#else
	stw	r0,16(r7)
#endif
done:
}
#endif	/* __EVEC__ */


asm volatile void save_vector_state(unsigned long *vrsavep, vectorreg_t *vregp)
{
%reg vrsavep ; reg vregp
! "r0","r6"
	.opt	p=altivec
	mfspr	r0,vrsave
	stw	r0,0(vrsavep)
	mr	r6,vregp
	addi	r0,r0,0
	stvx	v20,r6,r0
	addi	r0,r0,16
	stvx	v21,r6,r0
	addi	r0,r0,32
	stvx	v22,r6,r0
	addi	r0,r0,48
	stvx	v23,r6,r0
	addi	r0,r0,64
	stvx	v24,r6,r0
	addi	r0,r0,80
	stvx	v25,r6,r0
	addi	r0,r0,96
	stvx	v26,r6,r0
	addi	r0,r0,112
	stvx	v27,r6,r0
	addi	r0,r0,128
	stvx	v28,r6,r0
	addi	r0,r0,144
	stvx	v29,r6,r0
	addi	r0,r0,160
	stvx	v30,r6,r0
	addi	r0,r0,176
	stvx	v31,r6,r0
	.opt	p=601
}

asm volatile void restore_cpu_state(unsigned long *gregp)
{
%reg gregp
! "r3","r7"
	mr	r7,gregp
#ifdef __LP64__
	ld	r14,112(r7)
	ld	r15,120(r7)
	ld	r16,128(r7)
	ld	r17,136(r7)
	ld	r18,144(r7)
	ld	r19,152(r7)
	ld	r20,160(r7)
	ld	r21,168(r7)
	ld	r22,176(r7)
	ld	r23,184(r7)
	ld	r24,192(r7)
	ld	r25,200(r7)
	ld	r26,208(r7)
	ld	r27,216(r7)
	ld	r28,224(r7)
	ld	r29,232(r7)
	ld	r30,240(r7)
	ld	r31,248(r7)
	ld	r3,16(r7)
	mtspr	lr,r3
	ld	r3,24(r7) // REG_ARG
	ld	r4,32(r7) // REG_ARG2
	ld	r1,8(r7)
#else
	lwz	r14,56(r7)
	lwz	r15,60(r7)
	lwz	r16,64(r7)
	lwz	r17,68(r7)
	lwz	r18,72(r7)
	lwz	r19,76(r7)
	lwz	r20,80(r7)
	lwz	r21,84(r7)
	lwz	r22,88(r7)
	lwz	r23,92(r7)
	lwz	r24,96(r7)
	lwz	r25,100(r7)
	lwz	r26,104(r7)
	lwz	r27,108(r7)
	lwz	r28,112(r7)
	lwz	r29,116(r7)
	lwz	r30,120(r7)
	lwz	r31,124(r7)
	lwz	r3,8(r7)
	mtspr	lr,r3
	lwz	r3,12(r7) // REG_ARG
	lwz	r4,16(r7) // REG_ARG2
	lwz	r1,4(r7)
#endif
$$bnr				/* branch does not return */
$$fn 0 0 0 0
$$tl 0xffffc008 0xffffc000 0xfff00000
$$tr 0
	b	__common_long_jmp
}

asm volatile void restore_float_state(floatreg_t *fregp)
{
%reg fregp
! "r6"
	mr	r6,fregp
	lfd	f14,0(r6)
	lfd	f15,8(r6)
	lfd	f16,16(r6)
	lfd	f17,24(r6)
	lfd	f18,32(r6)
	lfd	f19,40(r6)
	lfd	f20,48(r6)
	lfd	f21,56(r6)
	lfd	f22,64(r6)
	lfd	f23,72(r6)
	lfd	f24,80(r6)
	lfd	f25,88(r6)
	lfd	f26,96(r6)
	lfd	f27,104(r6)
	lfd	f28,112(r6)
	lfd	f29,120(r6)
	lfd	f30,128(r6)
	lfd	f31,136(r6)
}

#ifdef __EVEC__
/*
 * Restore the CPU state for a 64-bit CPU.  This will be
 * called by all PPC targets where the libraries are compiled
 * for 64-bit registers, i.e. VLE and E500, and use evldd
 * instructions to restore the registers.  In some cases
 * the users code will be compiled for LSP, which does not
 * understand evldd, does not really have 64-bit registers,
 * and must use regular lwz instructions to restore.  Use
 * the constant in misc.c to see if this is an architecture
 * that does not understand evldd.
 *
 * When restoring using lwz pay attention to endian.  There
 * is an operation that happens during frame unwinding that
 * will invert words if endian is not maintained.
 */
asm volatile void restore_cpu64_state(vectorreg_t *vregp)
{
%reg vregp ; lab restore_64bits, lab restore_done
! "r3","r7"
#ifndef	__RTP__
#ifdef	__PPC_VLE__
	li	r7,0	
	addi	r7,r7,__EVEC32BIT@l
	e_cmp16i	r7,0
#else
	addi	r7,r0,__EVEC32BIT@l
	cmpi	r7,0
#endif
	beq	restore_64bits
	mr	r7,vregp
#ifdef __BIG_ENDIAN__
	lwz 	r14,116(r7)
	lwz 	r15,124(r7)
	lwz 	r16,132(r7)
	lwz 	r17,140(r7)
	lwz 	r18,148(r7)
	lwz 	r19,156(r7)
	lwz 	r20,164(r7)
	lwz 	r21,172(r7)
	lwz 	r22,180(r7)
	lwz 	r23,188(r7)
	lwz 	r24,196(r7)
	lwz 	r25,204(r7)
	lwz 	r26,212(r7)
	lwz 	r27,220(r7)
	lwz 	r28,228(r7)
	lwz 	r29,236(r7)
	lwz 	r30,244(r7)
	lwz 	r31,252(r7)

	lwz	r3,20(r7)		/* REG_PC  */
	mtspr	lr,r3
	lwz	r3,28(r7)		/* REG_ARG */
	lwz	r4,36(r7)		/* REG_ARG2 */
	lwz	r1,12(r7)		/* REG_SP  */
#else
	lwz 	r14,112(r7)
	lwz 	r15,120(r7)
	lwz 	r16,128(r7)
	lwz 	r17,136(r7)
	lwz 	r18,144(r7)
	lwz 	r19,152(r7)
	lwz 	r20,160(r7)
	lwz 	r21,168(r7)
	lwz 	r22,176(r7)
	lwz 	r23,184(r7)
	lwz 	r24,192(r7)
	lwz 	r25,200(r7)
	lwz 	r26,208(r7)
	lwz 	r27,216(r7)
	lwz 	r28,224(r7)
	lwz 	r29,232(r7)
	lwz 	r30,240(r7)
	lwz 	r31,248(r7)
	lwz	r3,16(r7)		/* REG_PC  */

	mtspr	lr,r3
	lwz	r3,24(r7)		/* REG_ARG */
	lwz	r4,32(r7)		/* REG_ARG2 */
	lwz	r1,8(r7)		/* REG_SP  */
#endif
$$bnr					/* branch does not return */
$$fn 0 0 0 0
$$tl 0xffffc008 0xffffc000 0xfff00000
$$tr 0
 	b	__common_long_jmp
#endif
restore_64bits:
	mr	r7,vregp
	evldd 	r14,112(r7)
	evldd 	r15,120(r7)
	evldd 	r16,128(r7)
	evldd 	r17,136(r7)
	evldd 	r18,144(r7)
	evldd 	r19,152(r7)
	evldd 	r20,160(r7)
	evldd 	r21,168(r7)
	evldd 	r22,176(r7)
	evldd 	r23,184(r7)
	evldd 	r24,192(r7)
	evldd 	r25,200(r7)
	evldd 	r26,208(r7)
	evldd 	r27,216(r7)
	evldd 	r28,224(r7)
	evldd 	r29,232(r7)
	evldd 	r30,240(r7)
	evldd 	r31,248(r7)

restore_done:
#ifdef __BIG_ENDIAN__
	lwz	r3,20(r7)		/* REG_PC  */
	mtspr	lr,r3
	lwz	r3,28(r7)		/* REG_ARG */
	lwz	r4,36(r7)		/* REG_ARG2 */
	lwz	r1,12(r7)		/* REG_SP  */
#else
	lwz	r3,16(r7)		/* REG_PC  */
	mtspr	lr,r3
	lwz	r3,24(r7)		/* REG_ARG */
	lwz	r4,32(r7)		/* REG_ARG2 */
	lwz	r1,8(r7)		/* REG_SP  */
#endif
$$bnr					/* branch does not return */
$$fn 0 0 0 0
$$tl 0xffffc008 0xffffc000 0xfff00000
$$tr 0
 	b	__common_long_jmp
}
#endif  /* __EVEC__ */

asm volatile void restore_vector_state(unsigned long *vrsavep, vectorreg_t *vregp)
{
%reg vrsavep ; reg vregp
! "r0","r7"
	.opt	p=altivec
	lwz	r0,0(vrsavep)
	mtspr	vrsave,r0
	mr	r7,vregp
	addi	r0,r0,0
	lvx	v20,r7,r0
	addi	r0,r0,16
	lvx	v21,r7,r0
	addi	r0,r0,32
	lvx	v22,r7,r0
	addi	r0,r0,48
	lvx	v23,r7,r0
	addi	r0,r0,64
	lvx	v24,r7,r0
	addi	r0,r0,80
	lvx	v25,r7,r0
	addi	r0,r0,96
	lvx	v26,r7,r0
	addi	r0,r0,112
	lvx	v27,r7,r0
	addi	r0,r0,128
	lvx	v28,r7,r0
	addi	r0,r0,144
	lvx	v29,r7,r0
	addi	r0,r0,160
	lvx	v30,r7,r0
	addi	r0,r0,176
	lvx	v31,r7,r0
	.opt	p=601
}

#elif	defined(__mcore__)

/*
 *	M-CORE specific
 *
 *	+------------------------------------------------------------------------+
 *	! adr ! fsize ! vsize ! evsize ! aspill ! efsize ! catch ! fp ! lr ! reg !
 *	!  32 !	  7   !	  12  !	   1   !    4	!    1	 !   1	 !  1 !	 1 !  4	 !
 *	+------------------------------------------------------------------------+
 *	! adr !				  vsize					 ! *
 *	!  32 !				    32					 !
 *	+------------------------------------------------------------------------+
 *	! adr !				  fsize					 ! *
 *	!  32 !				    32					 !
 *	+------------------------------------------------------------------------+
 *	! adr !				catch table				 ! *
 *	!  32 !				    32					 !
 *	+------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(((FRAME) >> 25) << 3)
#define	FRAME_ASPILL(FRAME)	((((FRAME) >> 8) & 15) << 2)
#define	FRAME_EFSIZE(FRAME)	((FRAME) & 0x80)
#define	FRAME_VSIZE(FRAME)	((((FRAME) >> 13) & 0xfff) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x1000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x40)
#define	FRAME_FP(FRAME)		((FRAME) & 0x20)
#define	FRAME_LR(FRAME)		((FRAME) & 0x10)
#define	FRAME_REG(FRAME)	((FRAME) & 0x0f)
#define	CPUINFO_ALIGNMENT	4

struct cpu_info {
	unsigned long	reg[16];
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->reg[0])
#define	REG_PC(CPUINFOP)	((CPUINFOP)->reg[1])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->reg[2])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->reg[14])
#define	REG_LR(CPUINFOP)	((CPUINFOP)->reg[15])

#define	SAVE_CPU_STATE(CPUINFOP)	save_cpu_state((CPUINFOP)->reg)
#define	RESTORE_CPU_STATE(CPUINFOP)	restore_cpu_state((CPUINFOP)->reg)


asm volatile void save_cpu_state(unsigned long *regp)
{
%reg regp; lab next
	st.w	r8,(regp,32)
	st.w	r9,(regp,36)
	st.w	r10,(regp,40)
	st.w	r11,(regp,44)
	st.w	r12,(regp,48)
	st.w	r13,(regp,52)
	st.w	r14,(regp,56)
	st.w	r15,(regp,60)
	bsr	next
next:
	st.w	r0,(regp,0)
	st.w	r15,(regp,4)
}

asm volatile void restore_cpu_state(unsigned long *regp)
{
%reg regp
	mov	r3,regp
	ld.w	r8,(r3,32)
	ld.w	r9,(r3,36)
	ld.w	r10,(r3,40)
	ld.w	r11,(r3,44)
	ld.w	r12,(r3,48)
	ld.w	r13,(r3,52)
	ld.w	r14,(r3,56)
	ld.w	r15,(r3,60)
	ld.w	r2,(r3,8)
	ld.w	r1,(r3,4)
	ld.w	r0,(r3,0)
	jbr	__common_long_jmp
}

#elif	defined(__m32r__)

/*
 *	M32R specific -- same as mcore except for fsize shift count
 *
 *	+------------------------------------------------------------------------+
 *	! adr ! fsize ! vsize ! evsize ! aspill ! efsize ! catch ! fp ! lr ! reg !
 *	!  32 !	  7   !	  12  !	   1   !    4	!    1	 !   1	 !  1 !	 1 !  4	 !
 *	+------------------------------------------------------------------------+
 *	! adr !				  vsize					 ! *
 *	!  32 !				    32					 !
 *	+------------------------------------------------------------------------+
 *	! adr !				  fsize					 ! *
 *	!  32 !				    32					 !
 *	+------------------------------------------------------------------------+
 *	! adr !				catch table				 ! *
 *	!  32 !				    32					 !
 *	+------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(((FRAME) >> 25) << 2)
#define	FRAME_ASPILL(FRAME)	((((FRAME) >> 8) & 15) << 2)
#define	FRAME_EFSIZE(FRAME)	((FRAME) & 0x80)
#define	FRAME_VSIZE(FRAME)	((((FRAME) >> 13) & 0xfff) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x1000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x40)
#define	FRAME_FP(FRAME)		((FRAME) & 0x20)
#define	FRAME_LR(FRAME)		((FRAME) & 0x10)
#define	FRAME_REG(FRAME)	((FRAME) & 0x0f)
#define	CPUINFO_ALIGNMENT	4

struct cpu_info {
	unsigned long	reg[16];
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->reg[15])
#define	REG_PC(CPUINFOP)	((CPUINFOP)->reg[1])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->reg[0])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->reg[13])
#define	REG_LR(CPUINFOP)	((CPUINFOP)->reg[14])

#define	SAVE_CPU_STATE(CPUINFOP)	save_cpu_state((CPUINFOP)->reg)
#define	RESTORE_CPU_STATE(CPUINFOP)	restore_cpu_state((CPUINFOP)->reg)


asm volatile void save_cpu_state(unsigned long *regp)
{
%reg regp; lab next
	st	r8,@(32,regp)
	st	r9,@(36,regp)
	st	r10,@(40,regp)
	st	r11,@(44,regp)
	st	r12,@(48,regp)
	st	r13,@(52,regp)
	st	r14,@(56,regp)
	st	r15,@(60,regp)
	bl	next
next:
	st	r14,@(4,regp)
}

asm volatile void restore_cpu_state(unsigned long *regp)
{
%reg regp
	mv	r3,regp
	ld	r8,@(32,r3)
	ld	r9,@(36,r3)
	ld	r10,@(40,r3)
	ld	r11,@(44,r3)
	ld	r12,@(48,r3)
	ld	r13,@(52,r3)
	ld	r14,@(56,r3)
	ld	r15,@(60,r3)
	ld	r1,@(4,r3)
	ld	r0,@(0,r3)
	bra	__common_long_jmp
}

#elif defined(__sh__)

/*
 *	SH specific
 *
 *	+-------------------------------------------------------------------------------------+
 *	! adr ! fsize ! sk ! vsize ! evsize ! aspill ! efsize ! catch ! fp ! lr ! freg ! greg |
 *	!  32 !	  7   !  2 !   6   !   1    !   4    !    1   !   1   !  1 !  1 !  4   !  4   !
 *	+-------------------------------------------------------------------------------------+
 *	! adr !				  	vsize					 ! *
 *	!  32 !				    	32					 !
 *	+--------------------------------------------------------------------------------+
 *	! adr !				  	fsize					 ! *
 *	!  32 !				    	32					 !
 *	+--------------------------------------------------------------------------------+
 *	! adr !					catch table				 ! *
 *	!  32 !				    	32					 !
 *	+--------------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(((FRAME) >> 25) << 2)
#define	FRAME_ASPILL(FRAME)	((((FRAME) >> 12) & 15) << 2)
#define	FRAME_EFSIZE(FRAME)	((FRAME) & 0x800)
#define	FRAME_VSIZE(FRAME)	((((FRAME) >> 17) & 0x3f) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x10000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x400)
#define	FRAME_FP(FRAME)		((FRAME) & 0x200)
#define	FRAME_LR(FRAME)		((FRAME) & 0x100)
#define	FRAME_FREG(FRAME)	(((FRAME) >> 4) & 0x0f)
#define	FRAME_GREG(FRAME)	((FRAME) & 0x0f)
#define	CPUINFO_ALIGNMENT	4
#define	FRAME_SKIP(FRAME)	(((FRAME)  >> 23) & 0x3)

typedef struct { long v; } floatreg_t;

struct cpu_info {
	unsigned long	greg[16];
	floatreg_t	freg[16-12];
	char		fsaved;
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->greg[15])
#define	REG_PC(CPUINFOP)	((CPUINFOP)->greg[1])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->greg[0])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->greg[14])
#define	REG_LR(CPUINFOP)	((CPUINFOP)->greg[2])
#define	REG_R12(CPUINFOP)	((CPUINFOP)->greg[12])
#define	REG_R14(CPUINFOP)	((CPUINFOP)->greg[14])

#define	SAVE_CPU_STATE(CPUINFOP)	((CPUINFOP)->fsaved = 0, save_cpu_state((CPUINFOP)->greg))
#define	RESTORE_CPU_STATE(CPUINFOP)	(((CPUINFOP)->fsaved ? restore_float_state((CPUINFOP)->freg) : (void)0), \
					 restore_cpu_state((CPUINFOP)->greg))

asm volatile void save_cpu_state(unsigned long *gregp)
{
%reg gregp ; lab next
	mov.l	r8,@(32,gregp)
	mov.l	r9,@(36,gregp)
	mov.l	r10,@(40,gregp)
	mov.l	r11,@(44,gregp)
	mov.l	r12,@(48,gregp)
	mov.l	r13,@(52,gregp)
	mov.l	r14,@(56,gregp)
	mov.l	r15,@(60,gregp)
	bsr	next	
	nop
next:
	sts	pr,r3
	mov.l	r3,@(4,gregp)
}

asm volatile void save_float_state(floatreg_t *fregp)
{
%reg fregp
	fmov.s	fr12,@fregp
	add	#4,fregp
	fmov.s	fr13,@fregp
	add	#4,fregp
	fmov.s	fr14,@fregp
	add	#4,fregp
	fmov.s	fr15,@fregp
}

asm volatile void restore_cpu_state(unsigned long *gregp)
{
%reg gregp
#ifdef __SO_PICABIRTP__
	movv	___GOTT_BASE__,r12
	movv	___GOTT_INDEX__,r0
	mov.l	@r12,r12
	mov.l	@(r0,r12),r12
	movv	___common_long_jmp@got,r0
	mov.l	@(r0,r12),r1
#endif /* __SO_PICABIRTP__ */
	mov	gregp,r3
	mov.l	@(32,r3),r8
	mov.l	@(36,r3),r9
	mov.l	@(40,r3),r10
	mov.l	@(44,r3),r11
	mov.l	@(48,r3),r12
	mov.l	@(52,r3),r13
	mov.l	@(56,r3),r14
	mov.l	@(60,r3),r15
	mov.l	@(0,r3),r0
	mov.l	@(4,r3),r3
#ifndef __SO_PICABIRTP__
	movv	___common_long_jmp,r1
#endif
#ifdef __RTP__
#if 0
#
# In any shared library other than libc.so, ___common_long_jmp resolves to
# the PLT entry in the dynamic executable.
# Since the PLT uses (and therefore trashes r0), the return value passed
# from generic_throw to the catch block will be lost if it is not saved
# temporarily in another register.
# We use r2 to hold this value temporarily and it will be restored to r0
# in ___common_long_jmp before control reaches the catch block.
#
#endif
	mov	r0,r2
#endif
	jmp	@r1
	nop
}

asm volatile void restore_float_state(floatreg_t *fregp)
{
%reg fregp
	mov	fregp,r3
	fmov.s	@r3+,fr12
	fmov.s	@r3+,fr13
	fmov.s	@r3+,fr14
	fmov.s	@r3+,fr15
}

#elif	defined(__mips__)

/*
 *	MIPS specific
 *
 *	+------------------------------------------------------------------------------------+
 *	! adr ! fsize ! vsize ! ruse ! evsize ! efsize ! catch ! fp ! lr ! gregcnt ! fregcnt ! 
 *	!  32 !	  7   !	  10  !	  2  !    1   !    1   !   1   !  1 ! 1  !    4    !    4    !
 *	+------------------------------------------------------------------------------------+
 *	! adr !					   vsize				     ! *
 *	!  32 !					     32					     !
 *	+------------------------------------------------------------------------------------+
 *	! adr !					   fsize				     ! *
 *	!  32 !					     32					     !
 *	+------------------------------------------------------------------------------------+
 *	! adr !					catch table				     ! *
 *	!  32 !					     32					     !
 *	+------------------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(((FRAME) >> 25) << 3)
#define	FRAME_EFSIZE(FRAME)	((FRAME) & 0x800)
#define	FRAME_VSIZE(FRAME)	((((FRAME) >> 15) & 0x3ff) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x1000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x400)
#define	FRAME_FP(FRAME)		((FRAME) & 0x200)
#define	FRAME_LR(FRAME)		((FRAME) & 0x100)
#define	FRAME_FREG(FRAME)	((FRAME) & 0x0f)
#define	FRAME_GREG(FRAME)	(((FRAME) & 0xf0) >> 4)
#define	FRAME_RUSE(FRAME)	(((FRAME) >> 13) & 3)

#if	defined(__ABI_N32__)
#define	__HAS_ADJUSTED_FSIZE__
#endif

#if defined(__MIPS64BIT__)
#define	CPUINFO_ALIGNMENT	8
typedef unsigned long long genreg_t;
typedef struct { long long v; } floatreg_t;
#else
#define	CPUINFO_ALIGNMENT	4
typedef unsigned long genreg_t;
typedef struct { long v; } floatreg_t;
#endif

struct cpu_info {
	genreg_t	greg[32];
	floatreg_t	freg[32-20];
	char		fsaved;
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->greg[29])
#define	REG_PC(CPUINFOP)	((CPUINFOP)->greg[0])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->greg[2])
#define	REG_ARG2(CPUINFOP)	((CPUINFOP)->greg[3])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->greg[30])
#define	REG_LR(CPUINFOP)	((CPUINFOP)->greg[31])

#define	SAVE_CPU_STATE(CPUINFOP)	((CPUINFOP)->fsaved = 0, save_cpu_state((CPUINFOP)->greg))
#define	RESTORE_CPU_STATE(CPUINFOP)	(((CPUINFOP)->fsaved ? restore_float_state((CPUINFOP)->freg) : (void)0), \
					 restore_cpu_state((CPUINFOP)->greg))

asm volatile void save_cpu_state(genreg_t *gregp)
{
%reg gregp ; lab next
#if defined(__MIPS64BIT__)
	sd	$16,128(gregp)
	sd	$17,136(gregp)
	sd	$18,144(gregp)
	sd	$19,152(gregp)
	sd	$20,160(gregp)
	sd	$21,168(gregp)
	sd	$22,176(gregp)
	sd	$23,184(gregp)
	sd	$28,224(gregp)
	sd	$29,232(gregp)
	sd	$30,240(gregp)
	sd	$31,248(gregp)
#else
	sw	$16,64(gregp)
	sw	$17,68(gregp)
	sw	$18,72(gregp)
	sw	$19,76(gregp)
	sw	$20,80(gregp)
	sw	$21,84(gregp)
	sw	$22,88(gregp)
	sw	$23,92(gregp)
	sw	$28,112(gregp)
	sw	$29,116(gregp)
	sw	$30,120(gregp)
	sw	$31,124(gregp)
#endif
	bal	next
next:
#if defined(__MIPS64BIT__)
	sd	$31,0(gregp) 
#else
	sw	$31,0(gregp)
#endif
}

asm volatile void save_float_state(floatreg_t *fregp)
{
%reg fregp
#if defined(__MIPS64BIT__)
	sdc1	$f20,0(fregp)
	sdc1	$f21,8(fregp)
	sdc1	$f22,16(fregp)
	sdc1	$f23,24(fregp)
	sdc1	$f24,32(fregp)
	sdc1	$f25,40(fregp)
	sdc1	$f26,48(fregp)
	sdc1	$f27,56(fregp)
	sdc1	$f28,64(fregp)
	sdc1	$f29,72(fregp)
	sdc1	$f30,80(fregp)
	sdc1	$f31,88(fregp)
#else
	swc1	$f20,0(fregp)
	swc1	$f21,4(fregp)
	swc1	$f22,8(fregp)
	swc1	$f23,12(fregp)
	swc1	$f24,16(fregp)
	swc1	$f25,20(fregp)
	swc1	$f26,24(fregp)
	swc1	$f27,28(fregp)
	swc1	$f28,32(fregp)
	swc1	$f29,36(fregp)
	swc1	$f30,40(fregp)
	swc1	$f31,44(fregp)
#endif
}

asm volatile void restore_cpu_state(genreg_t *gregp)
{
%reg gregp
	move	$4,gregp
#ifdef	__SO_PICABIRTP__
	lui	$28,%hi(__GOTT_BASE__)
	lw	$28,%lo(__GOTT_BASE__)($28)
	lw	$28,%half(__GOTT_INDEX__)($28)
	lw	$1,%got(__common_long_jmp)($28)
#endif
#if defined(__MIPS64BIT__)
	ld	$16,128($4)
	ld	$17,136($4)
	ld	$18,144($4)
	ld	$19,152($4)
	ld	$20,160($4)
	ld	$21,168($4)
	ld	$22,176($4)
	ld	$23,184($4)
	ld	$28,224($4)
	ld	$30,240($4)
	ld	$31,248($4)
	ld	$2,16($4)
	ld	$3,24($4)
	ld	$31,0($4)
	ld	$29,232($4)
#else
	lw	$16,64($4)
	lw	$17,68($4)
	lw	$18,72($4)
	lw	$19,76($4)
	lw	$20,80($4)
	lw	$21,84($4)
	lw	$22,88($4)
	lw	$23,92($4)
	lw	$28,112($4)
	lw	$30,120($4)
	lw	$2,8($4)
	lw	$3,12($4)
	lw	$31,0($4)
	lw	$29,116($4)
#endif
#ifdef	__SO_PICABIRTP__
	jr	$1
#else
	j	__common_long_jmp
#endif
	nop
}

asm volatile void restore_float_state(floatreg_t *fregp)
{
%reg fregp
#if defined(__MIPS64BIT__)
	ldc1	$f20,0(fregp)
	ldc1	$f21,8(fregp)
	ldc1	$f22,16(fregp)
	ldc1	$f23,24(fregp)
	ldc1	$f24,32(fregp)
	ldc1	$f25,40(fregp)
	ldc1	$f26,48(fregp)
	ldc1	$f27,56(fregp)
	ldc1	$f28,64(fregp)
	ldc1	$f29,72(fregp)
	ldc1	$f30,80(fregp)
	ldc1	$f31,88(fregp)
#else
	lwc1	$f20,0(fregp)
	lwc1	$f21,4(fregp)
	lwc1	$f22,8(fregp)
	lwc1	$f23,12(fregp)
	lwc1	$f24,16(fregp)
	lwc1	$f25,20(fregp)
	lwc1	$f26,24(fregp)
	lwc1	$f27,28(fregp)
	lwc1	$f28,32(fregp)
	lwc1	$f29,36(fregp)
	lwc1	$f30,40(fregp)
	lwc1	$f31,44(fregp)
#endif
}

#elif	defined(__m68k)

/*
 *	MC68K/ColdFire specific
 *
 *	+------------------------------------------------------------------------------+
 *	! adr ! fsize ! vsize ! evsize ! efsize ! catch ! aregmask ! dregcnt ! fregcnt ! 
 *	!  32 !	  7   !	  12  !	   1   !    1	!   1	!     4	   !	3    !	  3    !
 *	+------------------------------------------------------------------------------+
 *	! adr !				      vsize				       ! *
 *	!  32 !					32				       !
 *	+------------------------------------------------------------------------------+
 *	! adr !				      fsize				       ! *
 *	!  32 !					32				       !
 *	+------------------------------------------------------------------------------+
 *	! adr !				    catch table				       ! *
 *	!  32 !					32				       !
 *	+------------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(((FRAME) >> 25) << 2)
#define	FRAME_EFSIZE(FRAME)	((FRAME) & 0x800)
#define	FRAME_VSIZE(FRAME)	((((FRAME) >> 13) & 0xfff) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x1000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x400)
#define	FRAME_AREGMASK(FRAME)	((((FRAME) >> 6) & 0xf) << 2)
#define	FRAME_DREGCNT(FRAME)	(((FRAME) >> 3) & 0x7)
#define	FRAME_FREGCNT(FRAME)	((FRAME) & 0x7)
#define	FRAME_FP(FRAME)		(1)
#define	FRAME_LR(FRAME)		(0)

#ifdef __coldfire
#define	CPUINFO_ALIGNMENT	8
typedef struct { long v[2]; } floatreg_t;
#else
#define	CPUINFO_ALIGNMENT	8
typedef struct { long v[3]; } floatreg_t;
#endif

struct cpu_info {
	floatreg_t	freg[8-2];
	unsigned long	greg[16];
	char		fsaved;
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->greg[15])
#define	REG_PC(CPUINFOP)	((CPUINFOP)->greg[8])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->greg[9])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->greg[14])
#define	REG_LR(CPUINFOP)	(0)

#define	SAVE_CPU_STATE(CPUINFOP)	((CPUINFOP)->fsaved = 0, save_cpu_state((CPUINFOP)->greg))
#define	RESTORE_CPU_STATE(CPUINFOP)	(((CPUINFOP)->fsaved ? restore_float_state((CPUINFOP)->freg) : (void)0), \
					 restore_cpu_state((CPUINFOP)->greg))

asm volatile void save_cpu_state(unsigned long *gregp)
{
%reg gregp ; lab next
	move.l	gregp,a0
	movem.l	d2/d3/d4/d5/d6/d7,8(a0)
	movem.l	a2/a3/a4/a5/a6/a7,40(a0)
	jbsr	next
next:
	move.l	(sp)+,a1
	move.l	a1,32(a0)
}

asm volatile void save_float_state(floatreg_t *fregp)
{
%reg fregp
	move.l	fregp,a0
#ifdef __coldfire
	.opt	p=coldfirebe
	fmovem	fp2/fp3/fp4/fp5/fp6/fp7,0(a0)
#elif defined(__hardfp)
	fmovem.x fp2/fp3/fp4/fp5/fp6/fp7,0(a0)
#endif
}

asm volatile void restore_cpu_state(unsigned long *gregp)
{
%reg gregp
	move.l	gregp,a0
	movem.l	8(a0),d2/d3/d4/d5/d6/d7
	movem.l	40(a0),a2/a3/a4/a5/a6
	move.l	32(a0),a1
	move.l	36(a0),d0
	move.l	60(a0),a7
	jbsr	___common_long_jmp
}

asm volatile void restore_float_state(floatreg_t *fregp)
{
%reg fregp
	move.l	fregp,a0
#ifdef __coldfire
	.opt	p=coldfirebe
	fmovem 0(a0),fp2/fp3/fp4/fp5/fp6/fp7
#elif defined(__hardfp)
	fmovem.x 0(a0),fp2/fp3/fp4/fp5/fp6/fp7
#endif
}

#elif	defined(__sparc)

/*
 *	SPARC specific
 *
 *	+----------------------------+
 *	! adr ! vsize ! save ! catch !
 *	!  32 !	  30  !	  1  !	 1   !
 *	+----------------------------+
 *	! adr !	     catch table     ! *
 *	!  32 !		  32	     !
 *	+----------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(0)
#define	FRAME_EFSIZE(FRAME)	(0)
#define	FRAME_VSIZE(FRAME)	((FRAME) & ~3)
#define	FRAME_EVSIZE(FRAME)	(0)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x1)
#define	FRAME_FP(FRAME)		(1)
#define	FRAME_LR(FRAME)		(1)
#define	CPUINFO_ALIGNMENT	16

struct cpu_info {
	unsigned long	reg[19];
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->reg[16])
#define	REG_PC(CPUINFOP)	((CPUINFOP)->reg[17])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->reg[18])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->reg[14])
#define	REG_LR(CPUINFOP)	((CPUINFOP)->reg[15])

#define	SAVE_CPU_STATE(CPUINFOP)	save_cpu_state((CPUINFOP)->reg)
#define	RESTORE_CPU_STATE(CPUINFOP)	restore_cpu_state((CPUINFOP)->reg)


asm volatile void save_cpu_state(unsigned long *regp)
{
%reg regp; lab next
	ta	3
	st	%i0,[regp+32]
	st	%i1,[regp+36]
	st	%i2,[regp+40]
	st	%i3,[regp+44]
	st	%i4,[regp+48]
	st	%i5,[regp+52]
	st	%i6,[regp+56]
	st	%i7,[regp+60]
	st	%sp,[regp+64]
	.set	noreorder
	call	next
	nop
next:
	add	%o7,8,%o1
	.set	reorder
	st	%o1,[regp+68]
}

asm volatile void restore_cpu_state(unsigned long *regp)
{
%reg regp
	mov	regp,%o2
#ifdef	__SO_PICABIRTP__
	sethi	%hi(__GOTT_BASE__),%l7
	ld		[%l7+%lo(__GOTT_BASE__)],%l7
	ld		[%l7+%lo(__GOTT_INDEX__)],%l7
	sethi	__common_long_jmp@gothi,%o4
	or		%o4,__common_long_jmp@gotlo,%o4
	ld		[%l7+%o4],%o4
#endif
	ld	[%o2+0],%l0
	ld	[%o2+4],%l1
	ld	[%o2+8],%l2
	ld	[%o2+12],%l3
	ld	[%o2+16],%l4
	ld	[%o2+20],%l5
	ld	[%o2+24],%l6
	ld	[%o2+28],%l7
	ld	[%o2+32],%i0
	ld	[%o2+36],%i1
	ld	[%o2+40],%i2
	ld	[%o2+44],%i3
	ld	[%o2+48],%i4
	ld	[%o2+52],%i5
	ld	[%o2+56],%i6
	ld	[%o2+60],%i7
	ld	[%o2+72],%o0
	ld	[%o2+68],%o1
	ld	[%o2+64],%sp
	sub	%o1,8,%o5
#ifndef	__SO_PICABIRTP__
	call	__common_long_jmp
#else
	jmpl	%o4,%g0
#endif
	nop
}

#elif	defined(__arm)

/*
 *	ARM specific
 *
 *	+-----------------------------------------------------------------------------------------------+
 *	! adr ! fsize ! sk ! neon ! vsize ! evsize ! efsize ! catch ! fp ! lr ! gregcnt!fregcnt!rsaveoff! 
 *	!  32 !	  6   ! 1  !  1   !   7   !   1    !    1   !   1   !  1 ! 1  !   4    !  4    !   4    |
 *	+-----------------------------------------------------------------------------------------------+
 *	! adr !				      vsize				                 ! *
 *	!  32 !					32				                 !
 *	+-----------------------------------------------------------------------------------------------+
 *	! adr !				      fsize				                 ! *
 *	!  32 !					32				        	 !
 *	+-----------------------------------------------------------------------------------------------+
 *	! adr !				    catch table				                 ! *
 *	!  32 !					32				                 !
 *	+-----------------------------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	(((FRAME) >> 26) << 2)
#define	FRAME_EFSIZE(FRAME)	((FRAME) & 0x8000)
#define	FRAME_NEON(FRAME)	((FRAME) & 0x1000000)
#define	FRAME_VSIZE(FRAME)	((((FRAME) >> 17) & 0x7f) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x10000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x4000)
#define	FRAME_FP(FRAME)		((FRAME) & 0x2000)
#define	FRAME_LR(FRAME)		((FRAME) & 0x1000)
#define	FRAME_RSAVEOFF(FRAME)	(((FRAME) & 0x0f)  << 1)
#define	FRAME_GREG(FRAME)	(((FRAME) & 0xf00) >> 8)
#define	FRAME_FREG(FRAME)	(((FRAME) & 0xf0)  >> 4)
#define	CPUINFO_ALIGNMENT	16

#if defined(__THUMB__) || defined(__THUMB2__)
#define	FRAME_SKIP(FRAME)	0
#else
#define	FRAME_SKIP(FRAME)	(((FRAME)  >> 25) & 0x1)
#endif

struct cpu_info {
	unsigned long	greg[16];
#if defined (__VFP__) || defined(_NEON__) || defined(__VFPv3_D32__)
	unsigned long	freg[16];	/* 8 double words registers: D8 to D15 or 16 words registers: S16 to S31*/
#if defined(_NEON__) || defined(__VFPv3_D32__)
	unsigned long long	nreg[16]; /* 16 double words registers: D16 to D31 */
#endif
#endif
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->greg[13])
#define REG_PC(CPUINFOP)	((CPUINFOP)->greg[14])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->greg[0])
#define	REG_ARG2(CPUINFOP)	((CPUINFOP)->greg[1])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->greg[11])
#define	REG_LR(CPUINFOP)	((CPUINFOP)->greg[14])
#define	REG_R9(CPUINFOP)	((CPUINFOP)->greg[9])
#define	REG_R11(CPUINFOP)	((CPUINFOP)->greg[11])

#define	SAVE_CPU_STATE(CPUINFOP)	save_cpu_state((CPUINFOP)->greg)
#define	RESTORE_CPU_STATE(CPUINFOP)	restore_cpu_state((CPUINFOP)->greg)


asm volatile void save_cpu_state(unsigned long *gregp)
{
%reg gregp ; lab next
	mov	r1,gregp
#if defined(__THUMB__) || defined(__THUMB2__)
	str	r4,[r1,#16]
	str	r5,[r1,#20]
	str	r6,[r1,#24]
	str	r7,[r1,#28]
	mov	r0,r8
	str	r0,[r1,#32]
	mov	r0,r9
	str	r0,[r1,#36]
	mov	r0,r10
	str	r0,[r1,#40]
	mov	r0,r11
	str	r0,[r1,#44]
	mov	r0,r12
	str	r0,[r1,#48]
	mov	r0,r13
$$noadjust
	str	r0,[r1,#52]
	mov	r0,r15
	str	r0,[r1,#60]				 
	ldr	r0,[r1,#0]
$$fn	0x5000	/* r12,r14 */
$$tl	0
	bl	next
$$noadjust
next:
	push {r0}
$$noadjust
	mov	r0,r14
	str	r0,[r1,#56]
	pop {r0}
$$noadjust
#else
	add	r12,r1,#16
	stmea	r12,{r4-r13}
$$noadjust
$$fn	0x5000	/* r12,r14 */
$$tl	0
	bl	next
$$noadjust
next:
	str	r14,[r1,#56]
#if defined(_NEON__) || defined(__VFPv3_D32__)
	add r12,r1,#64
	vstmia  r12!,{d8-d15}    /* save 24 double words registers: D8 to D31 */
	vstmia  r12,{d16-d31}
#elif defined(__VFP__)
	fsts	s16,[r1,#64]
	fsts	s17,[r1,#68]
	fsts	s18,[r1,#72]
	fsts	s19,[r1,#76]
	fsts	s20,[r1,#80]
	fsts	s21,[r1,#84]
	fsts	s22,[r1,#88]
	fsts	s23,[r1,#92]
	fsts	s24,[r1,#96]
	fsts	s25,[r1,#100]
	fsts	s26,[r1,#104]
	fsts	s27,[r1,#108]
	fsts	s28,[r1,#112]
	fsts	s29,[r1,#116]
	fsts	s30,[r1,#120]
	fsts	s31,[r1,#124]
#endif
#endif
}

asm volatile void restore_cpu_state(unsigned long *gregp)
{
%reg gregp
#if defined(__THUMB__) || defined(__THUMB2__)
	mov	r0,gregp
#if defined(__THUMB__)
	add	r0,#16
#else
	adds	r0,#16
#endif
	ldr	r4,[r0,#0]
	ldr	r5,[r0,#4]
	ldr	r6,[r0,#8]
	ldr	r7,[r0,#12]
	ldr	r1,[r0,#16]
	mov	r8,r1
	ldr	r1,[r0,#20]
	mov	r9,r1
	ldr	r1,[r0,#24]
	mov	r10,r1
	ldr	r1,[r0,#28]
	mov	r11,r1
	ldr	r1,[r0,#40]
	mov	r14,r1
	ldr	r1,[r0,#36]
	mov	r13,r1
$$noadjust
	sub	r0,#16
	ldr	r1,[r0,#4] // REG_ARG2
	ldr	r0,[r0,#0] // REG_ARG
	ldr     r3,=__common_long_jmp
$$bnr		/* branch does not return */
$$fn 0
$$tl 0x7ff	/* r0..r14 live into the call */
$$tr 0
	bx	r3
#else
#ifdef __SO_PICABIRTP__
	ldr	r9,=__GOTT_BASE__
	ldr	r9,[r9,#0]
	ldr	r9,[r9,#__GOTT_INDEX__]
	ldr	r2,=__common_long_jmp@got
	ldr	r2,[r2,r9]
#elif	defined(__SO_PICABILINUX__)
	ldr	r9,=_GLOBAL_OFFSET_TABLE_
	ldr	r2,=__common_long_jmp@got
	ldr	r2,[r2,r9]
#endif
	mov	r12,gregp
	ldr	r0,[r12,#0] // REG_ARG
	ldr	r1,[r12,#4] // REG_ARG2
	add	r12,r12,#16
	ldmfd	r12,{r4-r11}
	
	ldr	r14,[r12,#40]
	ldr	r13,[r12,#36]
$$noadjust

#if defined(_NEON__) || defined(__VFPv3_D32__)
    add r12,r12,#48
    vldmia  r12!,{d8-d15}    /* save 24 double words registers: D8 to D31 */
    vldmia  r12,{d16-d31}
#elif defined(__VFP__)
	sub	r12,r12,#16
	flds	s16,[r12,#64]
	flds	s17,[r12,#68]
	flds	s18,[r12,#72]
	flds	s19,[r12,#76]
	flds	s20,[r12,#80]
	flds	s21,[r12,#84]
	flds	s22,[r12,#88]
	flds	s23,[r12,#92]
	flds	s24,[r12,#96]
	flds	s25,[r12,#100]
	flds	s26,[r12,#104]
	flds	s27,[r12,#108]
	flds	s28,[r12,#112]
	flds	s29,[r12,#116]
	flds	s30,[r12,#120]
	flds	s31,[r12,#124]
#endif
$$bnr			/* branch does not return */
$$fn 0
$$tl 0x3 0xffff0000	/* r0,r1  s16..s31 */
$$tr 0
#if	defined(__SO_PICABIRTP__) || defined(__SO_PICABILINUX__)
	mov	pc,r2
#else
	b	__common_long_jmp
#endif
#endif
}

#elif	defined(__386)

/*
 *	X86 specific
 *
 *	+-----------------------------------------------------------------------------+
 *      | adr ! evsize ! efsize ! bx ! si ! di ! catch ! lr ! fp ! fsize ! vsize      !
 *      | 32  !   1    !   1    !  1 !  1 !  1 !   1   !  1 !  1 !   12  !    12      !
 *	+-----------------------------------------------------------------------------+
 *	! adr !				      vsize				      ! *
 *	!  32 !					32				      !
 *	+-----------------------------------------------------------------------------+
 *	! adr !				      fsize				      ! *
 *	!  32 !					32				      !
 *	+-----------------------------------------------------------------------------+
 *	! adr !				    catch table				      ! *
 *	!  32 !					32				      !
 *	+-----------------------------------------------------------------------------+
 */

#define	FRAME_FSIZE(FRAME)	((((FRAME) >> 12) & 0xfff) << 2)
#define	FRAME_EFSIZE(FRAME)	((FRAME) & 0x40000000)
#define	FRAME_VSIZE(FRAME)	(((FRAME)  & 0xfff) << 1)
#define	FRAME_EVSIZE(FRAME)	((FRAME) & 0x80000000)
#define	FRAME_CATCH(FRAME)	((FRAME) & 0x4000000)
#define	FRAME_LR(FRAME)		((FRAME) & 0x2000000)
#define FRAME_FP(FRAME)		((FRAME) & 0x1000000)
#define FRAME_DI(FRAME)		((FRAME) & 0x8000000)
#define FRAME_SI(FRAME)		((FRAME) & 0x10000000)
#define FRAME_BX(FRAME)		((FRAME) & 0x20000000)
#define	CPUINFO_ALIGNMENT	16

struct cpu_info {
	unsigned long	greg[8];
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_SP(CPUINFOP)	((CPUINFOP)->greg[0])
#define REG_PC(CPUINFOP)	((CPUINFOP)->greg[1])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->greg[2])
#define	REG_LR(CPUINFOP)	((CPUINFOP)->greg[3])
#define REG_SI(CPUINFOP)	((CPUINFOP)->greg[4])
#define REG_DI(CPUINFOP)	((CPUINFOP)->greg[5])
#define REG_BX(CPUINFOP)	((CPUINFOP)->greg[6])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->greg[7])

#define	SAVE_CPU_STATE(CPUINFOP)	save_cpu_state((CPUINFOP)->greg)
#define	RESTORE_CPU_STATE(CPUINFOP)	restore_cpu_state((CPUINFOP)->greg)


asm volatile void save_cpu_state(unsigned long *gregp)
{
%mem gregp ; lab next
	movl  gregp, %eax
	movl  %esp, (%eax)
        movl  %ebp, 8(%eax)
	movl  4(%ebp), %ecx
	movl  %ecx, 12(%eax)
	movl  %esi, 16(%eax)
	movl  %edi, 20(%eax)
	movl  %ebx, 24(%eax)
     	call  next
next:	 
	movl  (%esp), %ecx
	movl  %ecx, 4(%eax)
	addl  $4, %esp
}

asm volatile void restore_cpu_state(unsigned long *gregp)
{
%mem gregp ; lab next
	movl  gregp, %eax
	movl  (%eax), %esp
        movl  8(%eax), %ebp
        movl  16(%eax), %esi
        movl  20(%eax), %edi
        movl  24(%eax), %ebx
	pushl 4(%eax)
	movl  28(%eax), %eax
	jmp  __common_long_jmp
}

#elif defined(__tc)
 
/*
 *      TriCore specific
 *
 *      +----------------------------+
 *      ! adr ! vsize !fpused! catch !
 *      !  32 !   30  !   1  !   1   !
 *      +----------------------------+
 *      ! adr !      catch table     ! *
 *      !  32 !           32         !
 *      +----------------------------+
 */

#define FRAME_FSIZE(FRAME)      (0)
#define FRAME_EFSIZE(FRAME)     (0)
#define FRAME_VSIZE(FRAME)      (((FRAME) & ~3) >> 1)
#define FRAME_EVSIZE(FRAME)     (0)
#define FRAME_CATCH(FRAME)      ((FRAME) & 0x1)
#define FRAME_FP(FRAME)         ((FRAME) & 0x2)
#define FRAME_LR(FRAME)         (0)
#define CPUINFO_ALIGNMENT       4

struct  cpu_info {
        unsigned long   pcxi[1];	// 00: previous context
        unsigned long   psw;		// 04
        unsigned long   a10;		// 08: stack pointer
        unsigned long   a11;    	// 12: link register
        unsigned long   d8;		// 16
        unsigned long   d9;		// 20
        unsigned long   d10;		// 24
        unsigned long   d11;		// 28
        unsigned long   a12;		// 32
        unsigned long   a13;		// 36
        unsigned long   a14;		// 40
        unsigned long   a15;		// 44
        unsigned long   d12;		// 48
        unsigned long   d13;		// 52
        unsigned long   d14;		// 56
        unsigned long   d15;		// 60
        unsigned long   pc;		// 64
        unsigned long   a2;		// 68:	pointer arg REG_ARG ptr-to-exception-structure
        unsigned long   d3;     	// 72:	REG_ARG2 integer selector
        unsigned long   temp_lr;     	// 76
        char            align[CPUINFO_ALIGNMENT-1];
};

#define REG_SP(CPUINFOP)        ((CPUINFOP)->a10)
#define REG_PC(CPUINFOP)        ((CPUINFOP)->pc )
#define REG_ARG(CPUINFOP)       ((CPUINFOP)->a2 )
#define REG_ARG2(CPUINFOP)      ((CPUINFOP)->d3 )
#define REG_FP(CPUINFOP)        ((CPUINFOP)->a14)
#define REG_LR(CPUINFOP)        ((CPUINFOP)->a11)

#define SAVE_CPU_STATE(CPUINFOP)        save_cpu_state((CPUINFOP)->pcxi)
#define RESTORE_CPU_STATE(CPUINFOP)     restore_cpu_state((CPUINFOP)->pcxi)

asm volatile void save_cpu_state(unsigned long *regp)
{
%reg regp; lab next;
	.set	noreorder
	mov.aa	%a6,regp
        mfcr    %d0,$pcxi
	st.w    [%a6]0,%d0	// 00: pcxi = previous context
        mfcr    %d0,$psw
        st.w    [%a6]4,%d0	// 04: psw
        st.a    [%a6]8,%a10	// 08: stack pointer
$$noadjust
        st.a    [%a6]12,%a11	// 12: link register
        st.w    [%a6]16,%d8
        st.w    [%a6]20,%d9
        st.w    [%a6]24,%d10
        st.w    [%a6]28,%d11
        st.a    [%a6]32,%a12
        st.a    [%a6]36,%a13
        st.a    [%a6]40,%a14
        st.a    [%a6]44,%a15
        st.w    [%a6]48,%d12
        st.w    [%a6]52,%d13
        st.w    [%a6]56,%d14
        st.w    [%a6]60,%d15
	st.a    [%a6]76,%a11	// 76: temp_lr
$$fn 0x8000000	// %a11
$$tl 0
        jl      next
$$noadjust
next:
        st.a    [%a6]64,%a11	// 64: pc
        ld.a    %a11,[%a6]76	// 76: temp_lr
	.set	reorder
}

asm volatile void restore_cpu_state(unsigned long *regp)
{
%reg regp; lab restore_loop; lab upper_ctx; lab lower_ctx
	.set	noreorder
	mov.aa		%a4,regp

	ld.w	%d6,[%a4]
	movh.a	%a5,restore_loop@ha
	lea	%a5,[%a5]restore_loop@l

restore_loop:
	mfcr	%d7,$pcxi
	jeq	%d7,%d6,upper_ctx
	jz.t	%d7,22,lower_ctx
	mov.aa	%a11,%a5
	nop
$$tl 0x83000f0	// %a4,%a5,%a11,%d4,%d5,%d6,%d7
	ret
$$noadjust

upper_ctx:
	ld.w	%d6,[%a4]4
	mtcr	$psw,%d6
	dsync
	nop
	nop

	ld.da	%a10,[%a4]8 	
$$noadjust
	ld.da	%a12,[%a4]32
	ld.da	%a14,[%a4]40
	ld.d	%d8+,[%a4]16
	ld.d	%d10+,[%a4]24
	ld.d	%d12+,[%a4]48
	ld.d	%d14+,[%a4]56

	ld.a	%a5,[%a4]64
	ld.a	%a2,[%a4]68	// 68: REG_ARG1
	ld.w	%d3,[%a4]72	// 72: REG_ARG2
	nop
	ji	%a5		// cannot do __common_long_jmp
		                // 'ret' would corrupt csa state

lower_ctx:
	mov	%d12,%d4	// save return value
	mov	%d13,%d6	// target pcxi
	mov.aa	%a13,%a4	// jumpbuf addr
	mov.aa	%a14,%a5	// loop addr
	rslcx
	mov.aa	%a5,%a14
	mov.aa	%a4,%a13
	mov	%d6,%d13
	mov	%d4,%d12
	j	restore_loop
	.set	reorder
}

#elif	defined(__nec)

/*
//      +-------------------------------------------------------------------+
//      ! adr !  fsize ! vsize !align! evsize  !efsize ! catch ! lr ! greg  ! 
//      !  32 !      9 !    13 !   1 !      1  !     1 !     1 !  1 !    5  !    
//      +-------------------------------------------------------------------+
//      ! adr !                    vsize                                    ! *     
//      !  32 !                       32                                    !       
//      +-------------------------------------------------------------------+
//      ! adr !                    fsize                                    ! *     
//      !  32 !                       32                                    !       
//      +-------------------------------------------------------------------+
//      ! adr !                    catch                                    ! *     
//      !  32 !                       32                                    !       
//      +-------------------------------------------------------------------+
//              * - not always present.
//
//	vsize - extent of this record
//	fsize - frame size to get previous stack pointer.
*/

#define CPUINFO_ALIGNMENT       4
#define FRAME_EALIGN(FRAME)	(((FRAME) >> 9) & 0x1)
#define FRAME_EVSIZE(FRAME)	(((FRAME) >> 8) & 0x1)
#define FRAME_EFSIZE(FRAME)	(((FRAME) >> 7) & 0x1)
#define FRAME_CATCH(FRAME)	(((FRAME) >> 6) & 0x1)
#define FRAME_LR(FRAME)		(((FRAME) >> 5) & 0x1)
#define FRAME_GREG(FRAME)	(( FRAME) & 0x1f)

/* size is always even */
#define FRAME_VSIZE(FRAME)	((((FRAME)>> 9) & 0x1fff) << 1)
#define	FRAME_FSIZE(FRAME)	((((FRAME)>>24) & 0x01ff) << 1)

/* TODO: crunch out extra space */
struct cpu_info {
	unsigned long	greg[33];
	char		align[CPUINFO_ALIGNMENT];
};

#define REG_SP(CPUINFOP)	((CPUINFOP)->greg[3])
#define REG_PC(CPUINFOP)	((CPUINFOP)->greg[32])
#define REG_LR(CPUINFOP)	((CPUINFOP)->greg[31])
#define REG_ARG(CPUINFOP)	((CPUINFOP)->greg[6])
#define REG_ARG2(CPUINFOP)	((CPUINFOP)->greg[7])

#define	SAVE_CPU_STATE(CPUINFOP)	save_cpu_state((CPUINFOP)->greg)
#define	RESTORE_CPU_STATE(CPUINFOP)	restore_cpu_state((CPUINFOP)->greg)

asm volatile void save_cpu_state(unsigned long *regp)
{
%reg regp; lab next
	st.w	r3,12[regp]
	st.w	r20,80[regp]
	st.w	r21,84[regp]
	st.w	r22,88[regp]
	st.w	r23,92[regp]
	st.w	r24,96[regp]
	st.w	r25,100[regp]
	st.w	r26,104[regp]
	st.w	r27,108[regp]
	st.w	r28,112[regp]
	st.w	r29,116[regp]
	st.w	r31,124[regp]
	jarl	next,r31
next:
	st.w	r31,128[regp]	
}

asm volatile void restore_cpu_state(unsigned long *regp)
{
%reg regp;
! "r6" 
	mov	regp,r6
	ld.w	80[r6],r20
	ld.w	84[r6],r21
	ld.w	88[r6],r22
	ld.w	92[r6],r23
	ld.w	96[r6],r24
	ld.w	100[r6],r25
	ld.w	104[r6],r26
	ld.w	108[r6],r27
	ld.w	112[r6],r28
	ld.w	116[r6],r29

	ld.w	128[r6],r31	
	ld.w	12[r6],r3	/* sp       */
	ld.w	24[r6],r10	/* REG_ARG  */
	ld.w	28[r6],r11	/* REG_ARG2 */
$$bnr                          /* branch does not return */
$$fn 0 0
	jr	___common_long_jmp
}

#else

/*
 *	Exception handling not supported.
 */

#define	FRAME_FSIZE(FRAME)	(0)
#define	FRAME_EFSIZE(FRAME)	(0)
#define	FRAME_VSIZE(FRAME)	(0)
#define	FRAME_EVSIZE(FRAME)	(0)
#define	FRAME_CATCH(FRAME)	(0)
#define	FRAME_FP(FRAME)		(0)
#define	CPUINFO_ALIGNMENT	16

struct cpu_info {
	unsigned long	reg[4];
	char		align[CPUINFO_ALIGNMENT-1];
};

#define	REG_PC(CPUINFOP)	((CPUINFOP)->reg[0])
#define	REG_ARG(CPUINFOP)	((CPUINFOP)->reg[1])
#define	REG_SP(CPUINFOP)	((CPUINFOP)->reg[2])
#define	REG_FP(CPUINFOP)	((CPUINFOP)->reg[3])

#define	SAVE_CPU_STATE(CPUINFOP)	((void)0)
#define	RESTORE_CPU_STATE(CPUINFOP)	((void)0)

#endif

/**************	Exported functions **********************/

#ifndef	__HAS_ADJUSTED_FSIZE__
EXTERN_C void __frameinfo_unwind_frame(struct cpu_info *, unsigned long, unsigned long);
#else
EXTERN_C void __frameinfo_unwind_frame(struct cpu_info *, unsigned long, unsigned long, unsigned long);
#endif
EXTERN_C unsigned long *__frameinfo_find_frame(unsigned long pc);
EXTERN_C void __generic_throw(void *, void *);

#endif
