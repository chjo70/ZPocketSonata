 
/* this file is generated by defs.fastlibgen.mk __tmpl_layercd */

Layer Layer::FS_ROMFS {

LIBRARIES += libfsRomfs.a

OBJECTS libfsRomfs.a::romfs.o libfsRomfs.a::romfsDrv.o libfsRomfs.a::romfsLib.o

}


ObjectFile libfsRomfs.a::romfs.o { 
	PATH krnl/PPCE6500/common/objfsRomfs/
}
 
ObjectFile libfsRomfs.a::romfsDrv.o { 
	PATH krnl/PPCE6500/common/objfsRomfs/
}
 
ObjectFile libfsRomfs.a::romfsLib.o { 
	PATH krnl/PPCE6500/common/objfsRomfs/
}



