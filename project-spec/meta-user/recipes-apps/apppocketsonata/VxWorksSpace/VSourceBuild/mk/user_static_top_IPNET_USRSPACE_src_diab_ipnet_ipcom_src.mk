
#
# This file is automatically generated by mk/usr/defs.fastlibgen.mk.
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
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

# LIB_BASE_NAMES = net

 
_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_ipnet_ipcom_src = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_sock2.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_inet_ntop.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_inet_pton.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_getservby.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_getinfo.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_getinfo2.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_ifaddrs.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_malloc.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet/ipcom_errno.o

_usrstarcmdfile_common_net : $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_ipnet_ipcom_src)

_STATIC_LIBOBJS_common_net += $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_ipnet_ipcom_src)

__OBJS_TO_CLEAN_IPNET_USRSPACE += $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_ipnet_ipcom_src)

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a : $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_ipnet_ipcom_src)

ifndef _DONEBASE_USRST_LIB_common_net

_DONEBASE_USRST_LIB_common_net = TRUE

# LIBBASES += net

# D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objnet :
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
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @_usrstarcmdfile_common_net

clean  _layer_clean_IPNET_USRSPACE : _clean_USRST_LIB_BASE_common_net

_clean_USRST_LIB_BASE_common_net :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libnet.a

endif


 

 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
