
#
# This file is automatically generated by mk/usr/defs.fastlibgen.mk.
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = common
#	LIBDIRBASE = $(LIBDIRBASE_$(LIB_VARIANT))






ifeq (,)



endif


# DEP_OBJS = (DEP_OBJS)

# LIB_BASE_NAMES = d

 
_STATIC_LIBOBJS_common_d_user_shared_top_LANG_LIB_TOOL_TOOLSRC_DIAB_USER_src_diab_libd = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/cppalloc.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/cxa_except_tab.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/error.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/guard.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/pure_virt.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/cxa_eh.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/rtti.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/typeinfo.o D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd/vec_newdel.o

_usrstarcmdfile_common_d : $(_STATIC_LIBOBJS_common_d_user_shared_top_LANG_LIB_TOOL_TOOLSRC_DIAB_USER_src_diab_libd)

_STATIC_LIBOBJS_common_d += $(_STATIC_LIBOBJS_common_d_user_shared_top_LANG_LIB_TOOL_TOOLSRC_DIAB_USER_src_diab_libd)

__OBJS_TO_CLEAN_LANG_LIB_TOOL_TOOLSRC_DIAB_USER += $(_STATIC_LIBOBJS_common_d_user_shared_top_LANG_LIB_TOOL_TOOLSRC_DIAB_USER_src_diab_libd)

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libd.a : $(_STATIC_LIBOBJS_common_d_user_shared_top_LANG_LIB_TOOL_TOOLSRC_DIAB_USER_src_diab_libd)

ifndef _DONEBASE_USRST_LIB_common_d

_DONEBASE_USRST_LIB_common_d = TRUE

# LIBBASES += d

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objd :
#	mkdir -p $@

usrstlib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libd.a

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libd.a : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common

__STATIC_BUILT_LIBS += common_d

__STLIB_common_d = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libd.a

arcmdfiles : _usrstarcmdfile_common_d

_usrstarcmdfile_common_d :
	$(file >$@,$(sort $(_STATIC_LIBOBJS_common_d)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libd.a : _usrstarcmdfile_common_d | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @_usrstarcmdfile_common_d

clean  _layer_clean_LANG_LIB_TOOL_TOOLSRC_DIAB_USER : _clean_USRST_LIB_BASE_common_d

_clean_USRST_LIB_BASE_common_d :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libd.a

endif


 

 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
