
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

# LIB_BASE_NAMES = HASH

 

 



_SHARED_LIBOBJS_common_HASH_user_shared_top_HASH_openssl-1_0_2_ripemd_diab = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objHASH/rmd_dgst.sho  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objHASH/rmd_one.sho

_usrsharcmdfile_common_HASH : $(_SHARED_LIBOBJS_common_HASH_user_shared_top_HASH_openssl-1_0_2_ripemd_diab)

_SHARED_LIBOBJS_common_HASH += $(_SHARED_LIBOBJS_common_HASH_user_shared_top_HASH_openssl-1_0_2_ripemd_diab)

__OBJS_TO_CLEAN_HASH += $(_SHARED_LIBOBJS_common_HASH_user_shared_top_HASH_openssl-1_0_2_ripemd_diab)

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so : $(_SHARED_LIBOBJS_common_HASH_user_shared_top_HASH_openssl-1_0_2_ripemd_diab)

ifndef _DONEBASE_USRSH_LIB_common_HASH

_DONEBASE_USRSH_LIB_common_HASH = TRUE

# LIBBASES += HASH



usrshlib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin/libHASH.so.1 D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so.1

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin/libHASH.so.1 : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin

__DIR_TARGETS += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin/libHASH.so.1 D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so.1 : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so
	cp D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so $@

# XXX HASH
# false
# 



D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common 

arcmdfiles : _usrsharcmdfile_common_HASH

_usrsharcmdfile_common_HASH :
	$(file >$@,$(sort $(_SHARED_LIBOBJS_common_HASH)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so : | usrstlib
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dplus -tPPCEH:rtp7 -Y I,+D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/c++03:D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public:D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild  -W:c++:.CPP  -Xstsw-slow -Xstmw-slow  -XO -w    -D_VX_CPU=_VX_PPCE6500 -D_VX_TOOL_FAMILY=diab -D_VX_TOOL=diab  -DOPENSSL_NO_INLINE_ASM -DOPENSSL_NO_ASM   -D_VSB_CONFIG_FILE=\"D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/h/config/vsbConfig.h\"  -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/system -ID:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public -D_VSB_PUBLIC_HDR_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public -I.  -Xpic -Xshared -Xdynamic -soname=libHASH.so.1 -o  $@ -Wl,@_usrsharcmdfile_common_HASH  -LD:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/diab/PIC -LD:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC   
	true
	true


clean _layer_clean_HASH : _clean_USRSH_LIB_BASE_common_HASH

_clean_USRSH_LIB_BASE_common_HASH :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libHASH.so

endif




 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
