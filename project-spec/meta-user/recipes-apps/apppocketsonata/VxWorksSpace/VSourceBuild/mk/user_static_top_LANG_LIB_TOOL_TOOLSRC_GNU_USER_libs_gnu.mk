
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
#	LIBDIRBASE = $(TOOL_COMMON_DIR)$(LIB_DIR_TAG)






ifeq (,)



endif


# DEP_OBJS = (DEP_OBJS)

# LIB_BASE_NAMES = net dsi

 
_STATIC_LIBOBJS_common_net_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu = 

_usrstarcmdfile_common_net : $(_STATIC_LIBOBJS_common_net_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

_STATIC_LIBOBJS_common_net += $(_STATIC_LIBOBJS_common_net_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

__OBJS_TO_CLEAN_LANG_LIB_TOOL_TOOLSRC_GNU_USER += $(_STATIC_LIBOBJS_common_net_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a : $(_STATIC_LIBOBJS_common_net_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

ifndef _DONEBASE_USRST_LIB_common_net

_DONEBASE_USRST_LIB_common_net = TRUE

# LIBBASES += net

# D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/obj :
#	mkdir -p $@

usrstlib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a : | D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common

__STATIC_BUILT_LIBS += common_net

__STLIB_common_net = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a

arcmdfiles : _usrstarcmdfile_common_net

_usrstarcmdfile_common_net :
	$(file >$@,$(sort $(_STATIC_LIBOBJS_common_net)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a : _usrstarcmdfile_common_net | D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common
	D:/vxWorks7/compilers/gnu-4.8.1.10/x86-win32/bin/arppc crusv $@ @_usrstarcmdfile_common_net

clean  _layer_clean_LANG_LIB_TOOL_TOOLSRC_GNU_USER : _clean_USRST_LIB_BASE_common_net

_clean_USRST_LIB_BASE_common_net :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a

endif
  
_STATIC_LIBOBJS_common_dsi_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu = 

_usrstarcmdfile_common_dsi : $(_STATIC_LIBOBJS_common_dsi_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

_STATIC_LIBOBJS_common_dsi += $(_STATIC_LIBOBJS_common_dsi_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

__OBJS_TO_CLEAN_LANG_LIB_TOOL_TOOLSRC_GNU_USER += $(_STATIC_LIBOBJS_common_dsi_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libdsi.a : $(_STATIC_LIBOBJS_common_dsi_user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu)

ifndef _DONEBASE_USRST_LIB_common_dsi

_DONEBASE_USRST_LIB_common_dsi = TRUE

# LIBBASES += dsi

# D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/obj :
#	mkdir -p $@

usrstlib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libdsi.a

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libdsi.a : | D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common

__STATIC_BUILT_LIBS += common_dsi

__STLIB_common_dsi = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libdsi.a

arcmdfiles : _usrstarcmdfile_common_dsi

_usrstarcmdfile_common_dsi :
	$(file >$@,$(sort $(_STATIC_LIBOBJS_common_dsi)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libdsi.a : _usrstarcmdfile_common_dsi | D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common
	D:/vxWorks7/compilers/gnu-4.8.1.10/x86-win32/bin/arppc crusv $@ @_usrstarcmdfile_common_dsi

clean  _layer_clean_LANG_LIB_TOOL_TOOLSRC_GNU_USER : _clean_USRST_LIB_BASE_common_dsi

_clean_USRST_LIB_BASE_common_dsi :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libdsi.a

endif

 
   

   

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
