 
/* this file is generated by defs.fastlibgen.mk __tmpl_layercd */

Layer Layer::CORE_KERNEL {

LIBRARIES += libpxsig.a

OBJECTS libpxsig.a::sigFuncBind.o libpxsig.a::rtpSigLib.o libpxsig.a::rtpSigScLib.o libpxsig.a::sigeventLib.o libpxsig.a::sigLib.o

}


ObjectFile libpxsig.a::sigFuncBind.o { 
	PATH krnl/PPCE6500/common/objpxsig/
}
 
ObjectFile libpxsig.a::rtpSigLib.o { 
	PATH krnl/PPCE6500/common/objpxsig/
}
 
ObjectFile libpxsig.a::rtpSigScLib.o { 
	PATH krnl/PPCE6500/common/objpxsig/
}
 
ObjectFile libpxsig.a::sigeventLib.o { 
	PATH krnl/PPCE6500/common/objpxsig/
}
 
ObjectFile libpxsig.a::sigLib.o { 
	PATH krnl/PPCE6500/common/objpxsig/
}



