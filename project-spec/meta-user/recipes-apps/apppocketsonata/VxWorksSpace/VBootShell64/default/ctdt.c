/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a C compiler to compile this file. If you    */
/*       are using GNU C++, be sure to use compile this   */
/*       file using a GNU compiler with the               */
/*       -fdollars-in-identifiers flag.                   */

#if defined(_HAVE_TOOL_XTORS)
#include <vxWorks.h>
#include TOOL_HEADER (toolXtors.h)
#else
char __dso_handle = 0;

void _STI__07__diab_atomic_init();

void _STI__15__frameinfo_add();

extern void (*_ctors[])();
void (*_ctors[])() =
    {
    _STI__07__diab_atomic_init,
    _STI__15__frameinfo_add,
    0
    };

void _STD__15__frameinfo_add();

extern void (*_dtors[])();
void (*_dtors[])() =
    {
    _STD__15__frameinfo_add,
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
__asm("	.ascii \"set PRJ_FULL_PATH D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VBootShell64\"");
__asm("	.byte 0");
__asm("	.ascii \"set VSB_DIR D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64\"");
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
