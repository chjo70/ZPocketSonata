 
/* this file is generated by defs.fastlibgen.mk __tmpl_layercd */

Layer Layer::STACKTRACE {

LIBRARIES += libstacktrace.a

OBJECTS libstacktrace.a::context_memtest.o libstacktrace.a::context.o libstacktrace.a::context_region.o libstacktrace.a::ppc_os.o libstacktrace.a::ppc_crawl.o libstacktrace.a::memory_map_vx.o libstacktrace.a::memory_map_module_vx.o libstacktrace.a::memory_map_shd_vx.o

}


ObjectFile libstacktrace.a::context_memtest.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}
 
ObjectFile libstacktrace.a::context.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}
 
ObjectFile libstacktrace.a::context_region.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}
 
ObjectFile libstacktrace.a::ppc_os.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}
 
ObjectFile libstacktrace.a::ppc_crawl.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}
 
ObjectFile libstacktrace.a::memory_map_vx.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}
 
ObjectFile libstacktrace.a::memory_map_module_vx.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}
 
ObjectFile libstacktrace.a::memory_map_shd_vx.o { 
	PATH krnl/PPCE6500/common/objstacktrace/
}


