
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






LIBOBJS = $(LIBOBJS_HASH)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_HASH_kernel_top_HASH_openssl-1_0_2_md5_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objHASH/md5_dgst.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objHASH/md5_one.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objHASH/md5_dgst.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objHASH/md5_one.o 

arcmdfile_krnl_PPCE6500_common_HASH : $(LIBOBJS_krnl_PPCE6500_common_HASH_kernel_top_HASH_openssl-1_0_2_md5_diab)

LIBOBJS_krnl_PPCE6500_common_HASH_HASH += $(LIBOBJS_krnl_PPCE6500_common_HASH_kernel_top_HASH_openssl-1_0_2_md5_diab)

LIBOBJS_krnl_PPCE6500_common_HASH += $(LIBOBJS_krnl_PPCE6500_common_HASH_kernel_top_HASH_openssl-1_0_2_md5_diab)

__OBJS_TO_CLEAN_HASH += $(LIBOBJS_krnl_PPCE6500_common_HASH_kernel_top_HASH_openssl-1_0_2_md5_diab) $(LIBOBJS_krnl_PPCE6500_common_HASH_kernel_top_HASH_openssl-1_0_2_md5_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_HASH

_DONEBASE_LIB_krnl_PPCE6500_common_HASH = TRUE

# LIBBASES += HASH

__LIBS_TO_BUILD += krnl_PPCE6500_common_HASH

__LIBS_TO_BUILD_HASH += krnl_PPCE6500_common_HASH

__BUILT_LIBS += krnl_PPCE6500_common_HASH

__LIB_krnl_PPCE6500_common_HASH = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objHASH :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libHASH$(OPT).a libHASH$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libHASH.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_HASH

arcmdfile_krnl_PPCE6500_common_HASH :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_HASH)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH$(OPT).a : arcmdfile_krnl_PPCE6500_common_HASH
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_HASH


clean _layer_clean_HASH : _clean_LIB_BASE_krnl_PPCE6500_common_HASH

_clean_LIB_BASE_krnl_PPCE6500_common_HASH :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH$(OPT).a


endif

ifndef _DONEBASE_LIB_HASH_krnl_PPCE6500_common_HASH

_DONEBASE_LIB_HASH_krnl_PPCE6500_common_HASH = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerHASH_libHASH.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerHASH_libHASH.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,HASH,libHASH.a,$(LIBOBJS_krnl_PPCE6500_common_HASH)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libHASH$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_HASH)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
