
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

# LIB_BASE_NAMES = rtnet

 
_STATIC_LIBOBJS_common_rtnet_user_static_top_JOBQUEUE_src_diab = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objrtnet/jobQueueLib.o

_usrstarcmdfile_common_rtnet : $(_STATIC_LIBOBJS_common_rtnet_user_static_top_JOBQUEUE_src_diab)

_STATIC_LIBOBJS_common_rtnet += $(_STATIC_LIBOBJS_common_rtnet_user_static_top_JOBQUEUE_src_diab)

__OBJS_TO_CLEAN_JOBQUEUE += $(_STATIC_LIBOBJS_common_rtnet_user_static_top_JOBQUEUE_src_diab)

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/librtnet.a : $(_STATIC_LIBOBJS_common_rtnet_user_static_top_JOBQUEUE_src_diab)

ifndef _DONEBASE_USRST_LIB_common_rtnet

_DONEBASE_USRST_LIB_common_rtnet = TRUE

# LIBBASES += rtnet

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objrtnet :
#	mkdir -p $@

usrstlib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/librtnet.a

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/librtnet.a : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common

__STATIC_BUILT_LIBS += common_rtnet

__STLIB_common_rtnet = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/librtnet.a

arcmdfiles : _usrstarcmdfile_common_rtnet

_usrstarcmdfile_common_rtnet :
	$(file >$@,$(sort $(_STATIC_LIBOBJS_common_rtnet)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/librtnet.a : _usrstarcmdfile_common_rtnet | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @_usrstarcmdfile_common_rtnet

clean  _layer_clean_JOBQUEUE : _clean_USRST_LIB_BASE_common_rtnet

_clean_USRST_LIB_BASE_common_rtnet :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/librtnet.a

endif


 

 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
