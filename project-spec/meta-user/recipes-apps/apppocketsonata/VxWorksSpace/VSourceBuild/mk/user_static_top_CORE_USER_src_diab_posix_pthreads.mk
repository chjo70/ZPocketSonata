
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
#	LIBDIRBASE = $(TOOL_COMMON_DIR)$(LIB_DIR_TAG)






ifeq (,)



endif


# DEP_OBJS = (DEP_OBJS)

# LIB_BASE_NAMES = c

 
_STATIC_LIBOBJS_common_c_user_static_top_CORE_USER_src_diab_posix_pthreads = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/pthreadFuncBind.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/pthreadLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/schedPxLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc/pthreadRwLocks.o

_usrstarcmdfile_common_c : $(_STATIC_LIBOBJS_common_c_user_static_top_CORE_USER_src_diab_posix_pthreads)

_STATIC_LIBOBJS_common_c += $(_STATIC_LIBOBJS_common_c_user_static_top_CORE_USER_src_diab_posix_pthreads)

__OBJS_TO_CLEAN_CORE_USER += $(_STATIC_LIBOBJS_common_c_user_static_top_CORE_USER_src_diab_posix_pthreads)

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.a : $(_STATIC_LIBOBJS_common_c_user_static_top_CORE_USER_src_diab_posix_pthreads)

ifndef _DONEBASE_USRST_LIB_common_c

_DONEBASE_USRST_LIB_common_c = TRUE

# LIBBASES += c

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objc :
#	mkdir -p $@

usrstlib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.a

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.a : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common

__STATIC_BUILT_LIBS += common_c

__STLIB_common_c = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.a

arcmdfiles : _usrstarcmdfile_common_c

_usrstarcmdfile_common_c :
	$(file >$@,$(sort $(_STATIC_LIBOBJS_common_c)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.a : _usrstarcmdfile_common_c | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @_usrstarcmdfile_common_c

clean  _layer_clean_CORE_USER : _clean_USRST_LIB_BASE_common_c

_clean_USRST_LIB_BASE_common_c :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libc.a

endif


 

 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
