
#
# This file is automatically generated by mk/krnl/defs.fastlibgen.mk .
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = krnl/PPCE6500/common
#	LIBDIRBASE = krnl/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)






LIBOBJS = $(LIBOBJS_rqdef) $(LIBOBJS_rqsmt) $(LIBOBJS_rqfept)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_rqdef_kernel_top_CORE_KERNEL_src_diab_wind_readyq =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objrqdef/readyQDeltaLib.o 

arcmdfile_krnl_PPCE6500_common_rqdef : $(LIBOBJS_krnl_PPCE6500_common_rqdef_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

LIBOBJS_krnl_PPCE6500_common_rqdef_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_rqdef_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

LIBOBJS_krnl_PPCE6500_common_rqdef += $(LIBOBJS_krnl_PPCE6500_common_rqdef_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_rqdef_kernel_top_CORE_KERNEL_src_diab_wind_readyq) $(LIBOBJS_krnl_PPCE6500_common_rqdef_kernel_top_CORE_KERNEL_src_diab_wind_readyq:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_rqdef

_DONEBASE_LIB_krnl_PPCE6500_common_rqdef = TRUE

# LIBBASES += rqdef

__LIBS_TO_BUILD += krnl_PPCE6500_common_rqdef

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_rqdef

__BUILT_LIBS += krnl_PPCE6500_common_rqdef

__LIB_krnl_PPCE6500_common_rqdef = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objrqdef :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) librqdef$(OPT).a librqdef$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a librqdef.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_rqdef

arcmdfile_krnl_PPCE6500_common_rqdef :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_rqdef)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef$(OPT).a : arcmdfile_krnl_PPCE6500_common_rqdef
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_rqdef


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_rqdef

_clean_LIB_BASE_krnl_PPCE6500_common_rqdef :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_rqdef

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_rqdef = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_librqdef.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_librqdef.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,librqdef.a,$(LIBOBJS_krnl_PPCE6500_common_rqdef)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqdef$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_rqdef)
  
LIBOBJS_krnl_PPCE6500_common_rqsmt_kernel_top_CORE_KERNEL_src_diab_wind_readyq =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objrqsmt/readyQDeltaSmtLib.o 

arcmdfile_krnl_PPCE6500_common_rqsmt : $(LIBOBJS_krnl_PPCE6500_common_rqsmt_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

LIBOBJS_krnl_PPCE6500_common_rqsmt_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_rqsmt_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

LIBOBJS_krnl_PPCE6500_common_rqsmt += $(LIBOBJS_krnl_PPCE6500_common_rqsmt_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_rqsmt_kernel_top_CORE_KERNEL_src_diab_wind_readyq) $(LIBOBJS_krnl_PPCE6500_common_rqsmt_kernel_top_CORE_KERNEL_src_diab_wind_readyq:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_rqsmt

_DONEBASE_LIB_krnl_PPCE6500_common_rqsmt = TRUE

# LIBBASES += rqsmt

__LIBS_TO_BUILD += krnl_PPCE6500_common_rqsmt

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_rqsmt

__BUILT_LIBS += krnl_PPCE6500_common_rqsmt

__LIB_krnl_PPCE6500_common_rqsmt = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objrqsmt :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) librqsmt$(OPT).a librqsmt$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a librqsmt.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_rqsmt

arcmdfile_krnl_PPCE6500_common_rqsmt :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_rqsmt)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt$(OPT).a : arcmdfile_krnl_PPCE6500_common_rqsmt
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_rqsmt


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_rqsmt

_clean_LIB_BASE_krnl_PPCE6500_common_rqsmt :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_rqsmt

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_rqsmt = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_librqsmt.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_librqsmt.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,librqsmt.a,$(LIBOBJS_krnl_PPCE6500_common_rqsmt)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqsmt$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_rqsmt)
  
LIBOBJS_krnl_PPCE6500_common_rqfept_kernel_top_CORE_KERNEL_src_diab_wind_readyq =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objrqfept/readyQFeptLib.o 

arcmdfile_krnl_PPCE6500_common_rqfept : $(LIBOBJS_krnl_PPCE6500_common_rqfept_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

LIBOBJS_krnl_PPCE6500_common_rqfept_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_rqfept_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

LIBOBJS_krnl_PPCE6500_common_rqfept += $(LIBOBJS_krnl_PPCE6500_common_rqfept_kernel_top_CORE_KERNEL_src_diab_wind_readyq)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_rqfept_kernel_top_CORE_KERNEL_src_diab_wind_readyq) $(LIBOBJS_krnl_PPCE6500_common_rqfept_kernel_top_CORE_KERNEL_src_diab_wind_readyq:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_rqfept

_DONEBASE_LIB_krnl_PPCE6500_common_rqfept = TRUE

# LIBBASES += rqfept

__LIBS_TO_BUILD += krnl_PPCE6500_common_rqfept

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_rqfept

__BUILT_LIBS += krnl_PPCE6500_common_rqfept

__LIB_krnl_PPCE6500_common_rqfept = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objrqfept :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) librqfept$(OPT).a librqfept$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a librqfept.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_rqfept

arcmdfile_krnl_PPCE6500_common_rqfept :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_rqfept)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept$(OPT).a : arcmdfile_krnl_PPCE6500_common_rqfept
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_rqfept


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_rqfept

_clean_LIB_BASE_krnl_PPCE6500_common_rqfept :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_rqfept

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_rqfept = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_librqfept.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_librqfept.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,librqfept.a,$(LIBOBJS_krnl_PPCE6500_common_rqfept)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/librqfept$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_rqfept)


  

     

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
