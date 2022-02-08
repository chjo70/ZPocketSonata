
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






LIBOBJS = $(LIBOBJS_fsVfs)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_fsVfs_kernel_top_FS_VFS_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/bufSubr.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/mountSubr.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/vnodeAff.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/vnodeLockf.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/vnodeSubr.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/bufSubr.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/mountSubr.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/vnodeAff.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/vnodeLockf.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs/vnodeSubr.o 

arcmdfile_krnl_PPCE6500_common_fsVfs : $(LIBOBJS_krnl_PPCE6500_common_fsVfs_kernel_top_FS_VFS_src_diab)

LIBOBJS_krnl_PPCE6500_common_fsVfs_FS_VFS += $(LIBOBJS_krnl_PPCE6500_common_fsVfs_kernel_top_FS_VFS_src_diab)

LIBOBJS_krnl_PPCE6500_common_fsVfs += $(LIBOBJS_krnl_PPCE6500_common_fsVfs_kernel_top_FS_VFS_src_diab)

__OBJS_TO_CLEAN_FS_VFS += $(LIBOBJS_krnl_PPCE6500_common_fsVfs_kernel_top_FS_VFS_src_diab) $(LIBOBJS_krnl_PPCE6500_common_fsVfs_kernel_top_FS_VFS_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_fsVfs

_DONEBASE_LIB_krnl_PPCE6500_common_fsVfs = TRUE

# LIBBASES += fsVfs

__LIBS_TO_BUILD += krnl_PPCE6500_common_fsVfs

__LIBS_TO_BUILD_FS_VFS += krnl_PPCE6500_common_fsVfs

__BUILT_LIBS += krnl_PPCE6500_common_fsVfs

__LIB_krnl_PPCE6500_common_fsVfs = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsVfs :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libfsVfs$(OPT).a libfsVfs$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libfsVfs.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_fsVfs

arcmdfile_krnl_PPCE6500_common_fsVfs :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_fsVfs)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs$(OPT).a : arcmdfile_krnl_PPCE6500_common_fsVfs
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_fsVfs


clean _layer_clean_FS_VFS : _clean_LIB_BASE_krnl_PPCE6500_common_fsVfs

_clean_LIB_BASE_krnl_PPCE6500_common_fsVfs :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs$(OPT).a


endif

ifndef _DONEBASE_LIB_FS_VFS_krnl_PPCE6500_common_fsVfs

_DONEBASE_LIB_FS_VFS_krnl_PPCE6500_common_fsVfs = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerFS_VFS_libfsVfs.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerFS_VFS_libfsVfs.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,FS_VFS,libfsVfs.a,$(LIBOBJS_krnl_PPCE6500_common_fsVfs)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsVfs$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_fsVfs)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
