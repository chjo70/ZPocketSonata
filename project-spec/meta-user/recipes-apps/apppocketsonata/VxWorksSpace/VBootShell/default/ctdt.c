/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a C compiler to compile this file. If you    */
/*       are using GNU C++, be sure to use compile this   */
/*       file using a GNU compiler with the               */
/*       -fdollars-in-identifiers flag.                   */

#if defined(_HAVE_TOOL_XTORS)
#include <vxWorks.h>
#define _WRS_NEED_EH_FRAME
#include TOOL_HEADER (toolXtors.h)
#else

#if defined(__GNUC__)

extern void __register_frame_info (const void *, void *);
extern void *__deregister_frame_info (const void *);
extern const unsigned __EH_FRAME_BEGIN__[];
static void _STI__15_ctors ()
{
  /* This structure must approximately match that in unwind-dw2-fde.h.
     In particular it must be no smaller, and no less aligned.  */
  static struct object {
    void *pc_begin; void *tbase; void *dbase; void *u;
    unsigned long b; void *fde_end; struct object *next;
  } object;
  __register_frame_info (__EH_FRAME_BEGIN__, &object);
}

static void _STD__15_dtors ()
{
  __deregister_frame_info (__EH_FRAME_BEGIN__);
}
#else
static void _STI__15_ctors ()
{
}

static void _STD__15_dtors ()
{
}
#endif

char __dso_handle = 0;

void _STI__07__diab_atomic_init();

void _GLOBAL__I_65535_0___cxa_allocate_exception();

void _GLOBAL__I_65535_0___cxa_get_globals_fast();

void _GLOBAL__I_65535_0__Fac_tidy();

void _GLOBAL__I_65535_0__ZNSt6locale7_Locimp9_MakexlocERKSt8_LocinfoiPS0_PKS_();

void _GLOBAL__I_65535_0__ZNSt6localeC2ERKS_S1_i();

void _GLOBAL__I_65535_0__ZNSt8ios_base4Init9_Init_cntE();

extern void (*_ctors[])();
void (*_ctors[])() =
    {
    _STI__07__diab_atomic_init,
    _STI__15_ctors,
    _GLOBAL__I_65535_0___cxa_allocate_exception,
    _GLOBAL__I_65535_0___cxa_get_globals_fast,
    _GLOBAL__I_65535_0__Fac_tidy,
    _GLOBAL__I_65535_0__ZNSt6locale7_Locimp9_MakexlocERKSt8_LocinfoiPS0_PKS_,
    _GLOBAL__I_65535_0__ZNSt6localeC2ERKS_S1_i,
    _GLOBAL__I_65535_0__ZNSt8ios_base4Init9_Init_cntE,
    0
    };

void _STD__15_dtors();

void _GLOBAL__D_65535_0___gthread_key_create();

extern void (*_dtors[])();
void (*_dtors[])() =
    {
    _STD__15_dtors,
    _GLOBAL__D_65535_0___gthread_key_create,
    0
    };
#endif /* _HAVE_TOOL_XTORS */

#include <vxWorks.h>
#ifdef _WRS_CONFIG_COMPAT69
#include <config.h>
#else
#include <prjParams.h>
#endif

/* build variables */
#if defined(INCLUDE_LOADER)
#ifdef __GNUC__
__asm("	.section \".wrs_build_vars\",\"a\"");
#endif
#ifdef __DCC__
__asm("	.section \".wrs_build_vars\",\"r\"");
#endif
__asm("	.global _wrs_build_vars");
__asm("	.global _wrs_build_vars_end");
__asm("_wrs_build_vars:");
#else
#ifdef __GNUC__
__asm("	.section \".wrs_build_vars\"");
#endif
#ifdef __DCC__
__asm("	.section \".wrs_build_vars\",\"n\"");
#endif
#endif
__asm("	.ascii \"set WIND_HOME D:/vxWorks7\"");
__asm("	.byte 0");
__asm("	.ascii \"set WIND_BASE $(WIND_HOME)/vxworks-7\"");
__asm("	.byte 0");
__asm("	.ascii \"set PRJ_FULL_PATH D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VBootShell\"");
__asm("	.byte 0");
__asm("	.ascii \"set VSB_DIR D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild\"");
__asm("	.byte 0");
__asm("	.ascii \"set BSP_DIR $(PRJ_FULL_PATH)/hmt_t2080vpx3u_1_0_0_0\"");
__asm("	.byte 0");
__asm(" .ascii \"tag SMP 1\"");
__asm(" .byte 0");
__asm(" .ascii \" tag VXW7 0\"");
__asm(" .byte 0");
__asm(" .ascii \"assert $(SMP)==1\"");
__asm(" .byte 0");
__asm(" .ascii \" assert $(VXW7)==0\"");
__asm(" .byte 0");
#if defined(INCLUDE_LOADER)
__asm("_wrs_build_vars_end:");
#endif
__asm("	.ascii \"end\"");
__asm("	.byte 0");
__asm("	.previous");
