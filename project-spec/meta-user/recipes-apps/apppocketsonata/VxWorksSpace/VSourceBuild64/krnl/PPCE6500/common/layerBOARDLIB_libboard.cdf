 
/* this file is generated by defs.fastlibgen.mk __tmpl_layercd */

Layer Layer::BOARDLIB {

LIBRARIES += libboard.a

OBJECTS libboard.a::boardLib.o libboard.a::warmBootLib.o

}


ObjectFile libboard.a::boardLib.o { 
	PATH krnl/PPCE6500/common/objboard/
}
 
ObjectFile libboard.a::warmBootLib.o { 
	PATH krnl/PPCE6500/common/objboard/
}


