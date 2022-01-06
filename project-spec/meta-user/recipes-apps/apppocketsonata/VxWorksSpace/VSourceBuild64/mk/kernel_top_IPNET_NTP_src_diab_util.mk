
#
# This file is automatically generated by mk/krnl/defs.fastlibgen.mk .
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = krnl/PPCE6500/common
#	LIBDIRBASE = krnl/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)






LIBOBJS = $(LIBOBJS_NTP)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_NTP_kernel_top_IPNET_NTP_src_diab_util =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objNTP/ntp-keygen.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objNTP/ntp-keygen.o 

arcmdfile_krnl_PPCE6500_common_NTP : $(LIBOBJS_krnl_PPCE6500_common_NTP_kernel_top_IPNET_NTP_src_diab_util)

LIBOBJS_krnl_PPCE6500_common_NTP_IPNET_NTP += $(LIBOBJS_krnl_PPCE6500_common_NTP_kernel_top_IPNET_NTP_src_diab_util)

LIBOBJS_krnl_PPCE6500_common_NTP += $(LIBOBJS_krnl_PPCE6500_common_NTP_kernel_top_IPNET_NTP_src_diab_util)

__OBJS_TO_CLEAN_IPNET_NTP += $(LIBOBJS_krnl_PPCE6500_common_NTP_kernel_top_IPNET_NTP_src_diab_util) $(LIBOBJS_krnl_PPCE6500_common_NTP_kernel_top_IPNET_NTP_src_diab_util:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_NTP

_DONEBASE_LIB_krnl_PPCE6500_common_NTP = TRUE

# LIBBASES += NTP

__LIBS_TO_BUILD += krnl_PPCE6500_common_NTP

__LIBS_TO_BUILD_IPNET_NTP += krnl_PPCE6500_common_NTP

__BUILT_LIBS += krnl_PPCE6500_common_NTP

__LIB_krnl_PPCE6500_common_NTP = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objNTP :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libNTP$(OPT).a libNTP$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libNTP.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_NTP

arcmdfile_krnl_PPCE6500_common_NTP :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_NTP)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP$(OPT).a : arcmdfile_krnl_PPCE6500_common_NTP
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_NTP


clean _layer_clean_IPNET_NTP : _clean_LIB_BASE_krnl_PPCE6500_common_NTP

_clean_LIB_BASE_krnl_PPCE6500_common_NTP :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP$(OPT).a


endif

ifndef _DONEBASE_LIB_IPNET_NTP_krnl_PPCE6500_common_NTP

_DONEBASE_LIB_IPNET_NTP_krnl_PPCE6500_common_NTP = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerIPNET_NTP_libNTP.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerIPNET_NTP_libNTP.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,IPNET_NTP,libNTP.a,$(LIBOBJS_krnl_PPCE6500_common_NTP)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libNTP$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_NTP)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
