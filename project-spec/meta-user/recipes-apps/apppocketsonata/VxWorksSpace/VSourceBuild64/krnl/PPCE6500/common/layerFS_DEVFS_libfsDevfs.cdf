 
/* this file is generated by defs.fastlibgen.mk __tmpl_layercd */

Layer Layer::FS_DEVFS {

LIBRARIES += libfsDevfs.a

OBJECTS libfsDevfs.a::rawFsLib.o libfsDevfs.a::rawFsLib.o

}


ObjectFile libfsDevfs.a::rawFsLib.o { 
	PATH krnl/PPCE6500/common/objfsDevfs/
}
 
ObjectFile libfsDevfs.a::rawFsLib.o { 
	PATH krnl/PPCE6500/common/objfsDevfs/
}


