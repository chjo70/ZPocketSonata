
#
# This file is automatically generated by mk/usr/defs.fastlibgen.mk.
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
#	CPU : PPCE6500
#	TOOL : gnu
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = common
#	LIBDIRBASE = $(LIBDIRBASE_$(LIB_VARIANT))






ifeq (,)



endif


# DEP_OBJS = (DEP_OBJS)

# LIB_BASE_NAMES = c

 

 



_SHARED_LIBOBJS_common_c_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu_libc_pic = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/unwind-c.sho D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/unwind-sjlj.sho D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/unwind-dw2.sho D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/unwind-dw2-fde.sho

_usrsharcmdfile_common_c : $(_SHARED_LIBOBJS_common_c_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu_libc_pic)

_SHARED_LIBOBJS_common_c += $(_SHARED_LIBOBJS_common_c_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu_libc_pic)

__OBJS_TO_CLEAN_LANG_LIB_TOOL_TOOLSRC_GNU_USER += $(_SHARED_LIBOBJS_common_c_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu_libc_pic)

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so : $(_SHARED_LIBOBJS_common_c_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu_libc_pic)

ifndef _DONEBASE_USRSH_LIB_common_c

_DONEBASE_USRSH_LIB_common_c = TRUE

# LIBBASES += c



usrshlib : /libc.so.1 D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so.1

/libc.so.1 : | 

__DIR_TARGETS +=  

/libc.so.1 D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so.1 : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so
	cp D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so $@

# XXX c
# 
# 



D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so : | D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common 

arcmdfiles : _usrsharcmdfile_common_c

_usrsharcmdfile_common_c :
	$(file >$@,$(sort $(_SHARED_LIBOBJS_common_c)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so : | usrstlib
	D:/vxWorks7/compilers/gnu-4.8.1.10/x86-win32/bin/c++ppc -fno-builtin -fstrength-reduce -mstrict-align -mregnames -mhard-float -fno-implicit-fp -D_WRS_HARDWARE_FP -mrtp -fno-strict-aliasing -D_C99 -D_HAS_C9X -std=c99 -fasm -fno-implicit-fp  -O2 -Wall     -D_VX_CPU=_VX_PPCE6500 -D_VX_TOOL_FAMILY=gnu -D_VX_TOOL=gnu     -D_VSB_CONFIG_FILE=\"D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/h/config/vsbConfig.h\"  -ID:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h -isystemD:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h -isystemD:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/system -isystemD:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public -D_VSB_PUBLIC_HDR_DIR=D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public -I.  -fpic -D__SO_PICABILINUX__  -shared -Wl,-soname,libc.so.1 -o  $@ -Wl,@_usrsharcmdfile_common_c  -LD:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/gnu/PIC -LD:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC   
	true
	true


clean _layer_clean_LANG_LIB_TOOL_TOOLSRC_GNU_USER : _clean_USRSH_LIB_BASE_common_c

_clean_USRSH_LIB_BASE_common_c :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.so

endif




 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
