
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
#	LIBDIRBASE = common/PIC
#	LIBDIRBASE = $(LIBDIRBASE_$(LIB_VARIANT))






ifeq (,)



endif


# DEP_OBJS = (DEP_OBJS)

# LIB_BASE_NAMES = d

 
_STATIC_LIBOBJS_common_PIC_d_user_static_top_LANG_LIB_CPLUS_CPLUS_USER_src_diab_libc++_basic_pic = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/delop.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/delop2.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/delop3.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/delaop.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/delaop2.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/delaop3.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/newaop.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/newaop2.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/new.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/newop.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/newop2.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/exceptio.sho D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd/nothrow.sho

_usrstarcmdfile_common_PIC_d : $(_STATIC_LIBOBJS_common_PIC_d_user_static_top_LANG_LIB_CPLUS_CPLUS_USER_src_diab_libc++_basic_pic)

_STATIC_LIBOBJS_common_PIC_d += $(_STATIC_LIBOBJS_common_PIC_d_user_static_top_LANG_LIB_CPLUS_CPLUS_USER_src_diab_libc++_basic_pic)

__OBJS_TO_CLEAN_LANG_LIB_CPLUS_CPLUS_USER += $(_STATIC_LIBOBJS_common_PIC_d_user_static_top_LANG_LIB_CPLUS_CPLUS_USER_src_diab_libc++_basic_pic)

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/libd.a : $(_STATIC_LIBOBJS_common_PIC_d_user_static_top_LANG_LIB_CPLUS_CPLUS_USER_src_diab_libc++_basic_pic)

ifndef _DONEBASE_USRST_LIB_common_PIC_d

_DONEBASE_USRST_LIB_common_PIC_d = TRUE

# LIBBASES += d

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/objd :
#	mkdir -p $@

usrstlib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/libd.a

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/libd.a : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC

__STATIC_BUILT_LIBS += common_PIC_d

__STLIB_common_PIC_d = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/libd.a

arcmdfiles : _usrstarcmdfile_common_PIC_d

_usrstarcmdfile_common_PIC_d :
	$(file >$@,$(sort $(_STATIC_LIBOBJS_common_PIC_d)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/libd.a : _usrstarcmdfile_common_PIC_d | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @_usrstarcmdfile_common_PIC_d

clean  _layer_clean_LANG_LIB_CPLUS_CPLUS_USER : _clean_USRST_LIB_BASE_common_PIC_d

_clean_USRST_LIB_BASE_common_PIC_d :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC/libd.a

endif


 

 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
