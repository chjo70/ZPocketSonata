
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

# LIB_BASE_NAMES = OPENSSL

 

 



_SHARED_LIBOBJS_common_OPENSSL_user_shared_top_HASH_openssl-1_0_2_whrlpool_diab = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objOPENSSL/wp_dgst.sho  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/objOPENSSL/wp_block.sho

_usrsharcmdfile_common_OPENSSL : $(_SHARED_LIBOBJS_common_OPENSSL_user_shared_top_HASH_openssl-1_0_2_whrlpool_diab)

_SHARED_LIBOBJS_common_OPENSSL += $(_SHARED_LIBOBJS_common_OPENSSL_user_shared_top_HASH_openssl-1_0_2_whrlpool_diab)

__OBJS_TO_CLEAN_HASH += $(_SHARED_LIBOBJS_common_OPENSSL_user_shared_top_HASH_openssl-1_0_2_whrlpool_diab)

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so : $(_SHARED_LIBOBJS_common_OPENSSL_user_shared_top_HASH_openssl-1_0_2_whrlpool_diab)

ifndef _DONEBASE_USRSH_LIB_common_OPENSSL

_DONEBASE_USRSH_LIB_common_OPENSSL = TRUE

# LIBBASES += OPENSSL



usrshlib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin/libOPENSSL.so.1 D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so.1

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin/libOPENSSL.so.1 : | D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin

__DIR_TARGETS += D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/root/diab/bin/libOPENSSL.so.1 D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so.1 : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so
	cp D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so $@

# XXX OPENSSL
# false
# 



D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so : | D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common 

arcmdfiles : _usrsharcmdfile_common_OPENSSL

_usrsharcmdfile_common_OPENSSL :
	$(file >$@,$(sort $(_SHARED_LIBOBJS_common_OPENSSL)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so : | usrstlib
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dplus -tPPCEH:rtp7 -Y I,+D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/c++03:D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public:D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild  -W:c++:.CPP  -Xstsw-slow -Xstmw-slow  -XO -w    -D_VX_CPU=_VX_PPCE6500 -D_VX_TOOL_FAMILY=diab -D_VX_TOOL=diab  -DOPENSSL_NO_INLINE_ASM -DOPENSSL_NO_ASM   -D_VSB_CONFIG_FILE=\"D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/h/config/vsbConfig.h\"  -ID:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h -ID:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h -ID:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/system -ID:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public -D_VSB_PUBLIC_HDR_DIR=D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public -I.  -Xpic -Xshared -Xdynamic -soname=libOPENSSL.so.1 -o  $@ -Wl,@_usrsharcmdfile_common_OPENSSL  -LD:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/diab/PIC -LD:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/PIC   
	true
	true


clean _layer_clean_HASH : _clean_USRSH_LIB_BASE_common_OPENSSL

_clean_USRSH_LIB_BASE_common_OPENSSL :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/lib/common/libOPENSSL.so

endif




 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
