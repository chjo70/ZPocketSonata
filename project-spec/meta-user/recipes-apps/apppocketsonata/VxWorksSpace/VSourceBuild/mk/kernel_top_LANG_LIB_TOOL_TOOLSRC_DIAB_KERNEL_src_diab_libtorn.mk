
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






LIBOBJS = $(LIBOBJS_dcc)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_dcc_kernel_top_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_src_diab_libtorn =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncatomic.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncmutex.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncsem.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_comljmp.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_libg.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/__diab_intrinsics_torn.o

arcmdfile_krnl_PPCE6500_common_dcc : $(LIBOBJS_krnl_PPCE6500_common_dcc_kernel_top_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_src_diab_libtorn)

LIBOBJS_krnl_PPCE6500_common_dcc_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_dcc_kernel_top_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_src_diab_libtorn)

LIBOBJS_krnl_PPCE6500_common_dcc += $(LIBOBJS_krnl_PPCE6500_common_dcc_kernel_top_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_src_diab_libtorn)

__OBJS_TO_CLEAN_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_dcc_kernel_top_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_src_diab_libtorn) $(LIBOBJS_krnl_PPCE6500_common_dcc_kernel_top_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_src_diab_libtorn:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_dcc

_DONEBASE_LIB_krnl_PPCE6500_common_dcc = TRUE

# LIBBASES += dcc

__LIBS_TO_BUILD += krnl_PPCE6500_common_dcc

__LIBS_TO_BUILD_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL += krnl_PPCE6500_common_dcc

__BUILT_LIBS += krnl_PPCE6500_common_dcc

__LIB_krnl_PPCE6500_common_dcc = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libdcc$(OPT).a libdcc$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libdcc.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_dcc

arcmdfile_krnl_PPCE6500_common_dcc :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_dcc)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc$(OPT).a : arcmdfile_krnl_PPCE6500_common_dcc
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_dcc


clean _layer_clean_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_dcc

_clean_LIB_BASE_krnl_PPCE6500_common_dcc :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc$(OPT).a


endif

ifndef _DONEBASE_LIB_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_krnl_PPCE6500_common_dcc

_DONEBASE_LIB_LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_krnl_PPCE6500_common_dcc = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerLANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_libdcc.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerLANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL_libdcc.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,LANG_LIB_TOOL_TOOLSRC_DIAB_KERNEL,libdcc.a,$(LIBOBJS_krnl_PPCE6500_common_dcc)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libdcc$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_dcc)




 

################
# rules defined locally in Makefile
##


ifneq (D:/vxWorks7/compilers/diab-5.9.6.5/PPCF/vxworks7/libtorn.a,)
 D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncatomic.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncmutex.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncsem.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_comljmp.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_libg.o : D:/vxWorks7/compilers/diab-5.9.6.5/PPCF/vxworks7/libtorn.a D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/toolsrc_diab-20.0.4.2/kernel/src/libtorn/Makefile |  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc
	@echo Wrapping $@ ...
	rm -f $@
# This just adds a symbol __object_o to object.o. We chose
# to use a one-line C fragment rather than using the linker
# to directly add a symbol because this way we don't have
# to worry about whether or not the compiler prepends an underscore.
	echo "char __$(subst +,_,$(subst -,_,$(notdir $*)))_o = 0;" > $(basename $@)_tmp_wrapper.c
	(cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc ; D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar -x D:/vxWorks7/compilers/diab-5.9.6.5/PPCF/vxworks7/libtorn.a $(patsubst _x_diab_%,%,$(notdir $@)) ; mv $(patsubst _x_diab_%,%,$(notdir $@)) $@)
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dcc -c  -tPPCE6500FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -Xc-new -Xdialect-c89   -XO -Xsize-opt  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations     -DCPU=_VX_PPCE6500 -DTOOL_FAMILY=diab -DTOOL=diab -D_WRS_KERNEL  -DINET  -D_WRS_LIB_BUILD     -D_VSB_CONFIG_FILE=\"D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/h/config/vsbConfig.h\"  -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/system -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h -D_VSB_PUBLIC_HDR_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public  -I.  $(basename $@)_tmp_wrapper.c -o $(basename $@)_tmp_obj.o
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dld -tPPCE6500FV:vxworks7 -X -r5 -r $(basename $@)_tmp_obj.o $@ -o $@_tmp
	cp $@_tmp $@
	@(if [ "diab" = "gnu" -a "ppc" = "arm" ]; then objcopyppc -R .ARM.attributes $@; fi)
	rm -f $(basename $@)_tmp_wrapper.c $(basename $@)_tmp_obj.o $@_tmp

endif # D:/vxWorks7/compilers/diab-5.9.6.5/PPCF/vxworks7/libtorn.a defined

ifneq (__diab_intrinsics_torn.o,)
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/__diab_intrinsics_torn.o :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncatomic.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncmutex.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_torn_syncsem.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_comljmp.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/_x_diab_libg.o  |  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc
	genConfig diab_intrinsics_torn _x_diab_torn_syncatomic.o _x_diab_torn_syncmutex.o _x_diab_torn_syncsem.o _x_diab_comljmp.o _x_diab_libg.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/__diab_intrinsics_torn.c
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dcc -c  -tPPCE6500FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -Xc-new -Xdialect-c89   -XO -Xsize-opt  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations     -DCPU=_VX_PPCE6500 -DTOOL_FAMILY=diab -DTOOL=diab -D_WRS_KERNEL  -DINET  -D_WRS_LIB_BUILD     -D_VSB_CONFIG_FILE=\"D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/h/config/vsbConfig.h\"  -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/system -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h -D_VSB_PUBLIC_HDR_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public  -I.  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/__diab_intrinsics_torn.c -o $@
	@(if [ "diab" = "gnu" -a "ppc" = "arm" ]; then objcopyppc -R .ARM.attributes $@; fi)
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objdcc/__diab_intrinsics_torn.c
endif


################

objs : $(LIBOBJS)
 
# this is the end of the file 
