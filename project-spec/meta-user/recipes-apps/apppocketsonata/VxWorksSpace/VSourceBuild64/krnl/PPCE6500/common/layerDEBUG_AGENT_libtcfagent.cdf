 
/* this file is generated by defs.fastlibgen.mk __tmpl_layercd */

Layer Layer::DEBUG_AGENT {

LIBRARIES += libtcfagent.a

OBJECTS libtcfagent.a::hostFsLib.o libtcfagent.a::hostFsLib.o libtcfagent.a::cpudefs-mdep.o libtcfagent.a::disassembler-powerpc.o libtcfagent.a::inputbuf.o libtcfagent.a::timed_event_queue.o libtcfagent.a::peer.o libtcfagent.a::proxy.o libtcfagent.a::channel_lws.o libtcfagent.a::base64.o libtcfagent.a::cache.o libtcfagent.a::json.o libtcfagent.a::events.o libtcfagent.a::channel_pipe.o libtcfagent.a::ip_ifc.o libtcfagent.a::cpudefs.o libtcfagent.a::context.o libtcfagent.a::myalloc.o libtcfagent.a::plugins.o libtcfagent.a::outputbuf.o libtcfagent.a::funccall.o libtcfagent.a::client.o libtcfagent.a::waitpid.o libtcfagent.a::channel_tcp.o libtcfagent.a::sigsets.o libtcfagent.a::asyncreq.o libtcfagent.a::context-dispatcher.o libtcfagent.a::channel.o libtcfagent.a::protocol.o libtcfagent.a::streams.o libtcfagent.a::shutdown.o libtcfagent.a::trace.o libtcfagent.a::event_queue.o libtcfagent.a::exceptions.o libtcfagent.a::signames.o libtcfagent.a::errors.o libtcfagent.a::runctrl.o libtcfagent.a::symbols_proxy.o libtcfagent.a::symbols_mux.o libtcfagent.a::linenumbers_proxy.o libtcfagent.a::linenumbers_mux.o libtcfagent.a::portforward_service.o libtcfagent.a::memoryservice.o libtcfagent.a::dwarfreloc.o libtcfagent.a::memorymap.o libtcfagent.a::dwarfecomp.o libtcfagent.a::portforward_proxy.o libtcfagent.a::symbols.o libtcfagent.a::symbols_win32.o libtcfagent.a::terminals.o libtcfagent.a::linenumbers_win32.o libtcfagent.a::registers.o libtcfagent.a::diagnostics.o libtcfagent.a::profiler_sst.o libtcfagent.a::funccall.o libtcfagent.a::disassembly.o libtcfagent.a::dwarfexpr.o libtcfagent.a::streamsservice.o libtcfagent.a::stacktrace.o libtcfagent.a::dwarfcache.o libtcfagent.a::dwarfio.o libtcfagent.a::discovery.o libtcfagent.a::linenumbers_elf.o libtcfagent.a::breakpoints.o libtcfagent.a::vm.o libtcfagent.a::elf-loader.o libtcfagent.a::dprintf.o libtcfagent.a::tcf_elf.o libtcfagent.a::discovery_udp.o libtcfagent.a::symbols_common.o libtcfagent.a::dwarfframe.o libtcfagent.a::profiler.o libtcfagent.a::linenumbers.o libtcfagent.a::symbols_elf.o libtcfagent.a::contextquery.o libtcfagent.a::filesystem.o libtcfagent.a::elf-symbols.o libtcfagent.a::pathmap.o libtcfagent.a::gdb-rsp.o libtcfagent.a::main_log.o libtcfagent.a::main_lua.o libtcfagent.a::server.o libtcfagent.a::main_client.o libtcfagent.a::framework.o libtcfagent.a::main.o libtcfagent.a::test.o libtcfagent.a::main_va.o libtcfagent.a::services.o libtcfagent.a::cmdline.o libtcfagent.a::logfilter.o libtcfagent.a::main_reg.o libtcfagent.a::context-vxworks.o libtcfagent.a::vxworks-rtp-funcbind.o libtcfagent.a::myalloc-vxworks.o libtcfagent.a::vxworks-funcbind.o libtcfagent.a::vxworks_elf_utils.o libtcfagent.a::worker-module.o libtcfagent.a::WR_LivePatch_proxy.o libtcfagent.a::WR_HostFs.o libtcfagent.a::WR_FileSystem_proxy.o libtcfagent.a::sysmon.o libtcfagent.a::WR_Module.o libtcfagent.a::runctrl-ext.o libtcfagent.a::processes.o libtcfagent.a::WR_SymbolsList_proxy.o libtcfagent.a::profiler_spy.o libtcfagent.a::patch_linenumbers_elf.o libtcfagent.a::expressions.o libtcfagent.a::mdep.o libtcfagent.a::c_ppc_crawl.o libtcfagent.a::ppc_crawl_lib.o libtcfagent.a::module_patch_ppc.o libtcfagent.a::adapter_craw_lib.o libtcfagent.a::c_stack_crawl.o libtcfagent.a::stackcrawl.o libtcfagent.a::c_crawl_lib.o libtcfagent.a::common_crawl_lib.o libtcfagent.a::tcfLib.o libtcfagent.a::cpudefs-mdep.o libtcfagent.a::disassembler-powerpc.o libtcfagent.a::inputbuf.o libtcfagent.a::timed_event_queue.o libtcfagent.a::peer.o libtcfagent.a::proxy.o libtcfagent.a::channel_lws.o libtcfagent.a::base64.o libtcfagent.a::cache.o libtcfagent.a::json.o libtcfagent.a::events.o libtcfagent.a::channel_pipe.o libtcfagent.a::ip_ifc.o libtcfagent.a::cpudefs.o libtcfagent.a::context.o libtcfagent.a::myalloc.o libtcfagent.a::plugins.o libtcfagent.a::outputbuf.o libtcfagent.a::funccall.o libtcfagent.a::client.o libtcfagent.a::waitpid.o libtcfagent.a::channel_tcp.o libtcfagent.a::sigsets.o libtcfagent.a::asyncreq.o libtcfagent.a::context-dispatcher.o libtcfagent.a::channel.o libtcfagent.a::protocol.o libtcfagent.a::streams.o libtcfagent.a::shutdown.o libtcfagent.a::trace.o libtcfagent.a::event_queue.o libtcfagent.a::exceptions.o libtcfagent.a::signames.o libtcfagent.a::errors.o libtcfagent.a::runctrl.o libtcfagent.a::symbols_proxy.o libtcfagent.a::symbols_mux.o libtcfagent.a::linenumbers_proxy.o libtcfagent.a::linenumbers_mux.o libtcfagent.a::portforward_service.o libtcfagent.a::memoryservice.o libtcfagent.a::dwarfreloc.o libtcfagent.a::memorymap.o libtcfagent.a::dwarfecomp.o libtcfagent.a::portforward_proxy.o libtcfagent.a::symbols.o libtcfagent.a::symbols_win32.o libtcfagent.a::terminals.o libtcfagent.a::linenumbers_win32.o libtcfagent.a::registers.o libtcfagent.a::diagnostics.o libtcfagent.a::profiler_sst.o libtcfagent.a::funccall.o libtcfagent.a::disassembly.o libtcfagent.a::dwarfexpr.o libtcfagent.a::streamsservice.o libtcfagent.a::stacktrace.o libtcfagent.a::dwarfcache.o libtcfagent.a::dwarfio.o libtcfagent.a::discovery.o libtcfagent.a::linenumbers_elf.o libtcfagent.a::breakpoints.o libtcfagent.a::vm.o libtcfagent.a::elf-loader.o libtcfagent.a::dprintf.o libtcfagent.a::tcf_elf.o libtcfagent.a::discovery_udp.o libtcfagent.a::symbols_common.o libtcfagent.a::dwarfframe.o libtcfagent.a::profiler.o libtcfagent.a::linenumbers.o libtcfagent.a::symbols_elf.o libtcfagent.a::contextquery.o libtcfagent.a::filesystem.o libtcfagent.a::elf-symbols.o libtcfagent.a::pathmap.o libtcfagent.a::gdb-rsp.o libtcfagent.a::main_log.o libtcfagent.a::main_lua.o libtcfagent.a::server.o libtcfagent.a::main_client.o libtcfagent.a::framework.o libtcfagent.a::main.o libtcfagent.a::test.o libtcfagent.a::main_va.o libtcfagent.a::services.o libtcfagent.a::cmdline.o libtcfagent.a::logfilter.o libtcfagent.a::main_reg.o libtcfagent.a::context-vxworks.o libtcfagent.a::vxworks-rtp-funcbind.o libtcfagent.a::myalloc-vxworks.o libtcfagent.a::vxworks-funcbind.o libtcfagent.a::vxworks_elf_utils.o libtcfagent.a::worker-module.o libtcfagent.a::WR_LivePatch_proxy.o libtcfagent.a::WR_HostFs.o libtcfagent.a::WR_FileSystem_proxy.o libtcfagent.a::sysmon.o libtcfagent.a::WR_Module.o libtcfagent.a::runctrl-ext.o libtcfagent.a::processes.o libtcfagent.a::WR_SymbolsList_proxy.o libtcfagent.a::profiler_spy.o libtcfagent.a::patch_linenumbers_elf.o libtcfagent.a::expressions.o libtcfagent.a::mdep.o libtcfagent.a::c_ppc_crawl.o libtcfagent.a::ppc_crawl_lib.o libtcfagent.a::module_patch_ppc.o libtcfagent.a::adapter_craw_lib.o libtcfagent.a::c_stack_crawl.o libtcfagent.a::stackcrawl.o libtcfagent.a::c_crawl_lib.o libtcfagent.a::common_crawl_lib.o libtcfagent.a::tcfLib.o

}


ObjectFile libtcfagent.a::hostFsLib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::hostFsLib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cpudefs-mdep.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::disassembler-powerpc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::inputbuf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::timed_event_queue.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::peer.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel_lws.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::base64.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cache.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::json.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::events.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel_pipe.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::ip_ifc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cpudefs.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::context.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::myalloc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::plugins.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::outputbuf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::funccall.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::client.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::waitpid.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel_tcp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::sigsets.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::asyncreq.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::context-dispatcher.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::protocol.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::streams.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::shutdown.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::trace.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::event_queue.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::exceptions.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::signames.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::errors.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::runctrl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_mux.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_mux.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::portforward_service.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::memoryservice.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfreloc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::memorymap.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfecomp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::portforward_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_win32.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::terminals.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_win32.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::registers.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::diagnostics.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::profiler_sst.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::funccall.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::disassembly.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfexpr.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::streamsservice.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::stacktrace.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfcache.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfio.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::discovery.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::breakpoints.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vm.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::elf-loader.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dprintf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::tcf_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::discovery_udp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_common.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfframe.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::profiler.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::contextquery.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::filesystem.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::elf-symbols.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::pathmap.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::gdb-rsp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_log.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_lua.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::server.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_client.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::framework.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::test.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_va.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::services.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cmdline.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::logfilter.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_reg.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::context-vxworks.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vxworks-rtp-funcbind.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::myalloc-vxworks.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vxworks-funcbind.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vxworks_elf_utils.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::worker-module.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_LivePatch_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_HostFs.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_FileSystem_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::sysmon.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_Module.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::runctrl-ext.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::processes.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_SymbolsList_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::profiler_spy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::patch_linenumbers_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::expressions.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::mdep.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::c_ppc_crawl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::ppc_crawl_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::module_patch_ppc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::adapter_craw_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::c_stack_crawl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::stackcrawl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::c_crawl_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::common_crawl_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::tcfLib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cpudefs-mdep.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::disassembler-powerpc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::inputbuf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::timed_event_queue.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::peer.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel_lws.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::base64.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cache.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::json.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::events.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel_pipe.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::ip_ifc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cpudefs.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::context.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::myalloc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::plugins.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::outputbuf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::funccall.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::client.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::waitpid.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel_tcp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::sigsets.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::asyncreq.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::context-dispatcher.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::channel.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::protocol.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::streams.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::shutdown.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::trace.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::event_queue.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::exceptions.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::signames.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::errors.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::runctrl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_mux.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_mux.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::portforward_service.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::memoryservice.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfreloc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::memorymap.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfecomp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::portforward_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_win32.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::terminals.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_win32.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::registers.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::diagnostics.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::profiler_sst.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::funccall.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::disassembly.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfexpr.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::streamsservice.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::stacktrace.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfcache.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfio.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::discovery.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::breakpoints.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vm.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::elf-loader.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dprintf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::tcf_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::discovery_udp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_common.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::dwarfframe.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::profiler.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::linenumbers.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::symbols_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::contextquery.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::filesystem.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::elf-symbols.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::pathmap.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::gdb-rsp.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_log.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_lua.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::server.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_client.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::framework.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::test.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_va.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::services.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::cmdline.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::logfilter.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::main_reg.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::context-vxworks.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vxworks-rtp-funcbind.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::myalloc-vxworks.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vxworks-funcbind.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::vxworks_elf_utils.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::worker-module.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_LivePatch_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_HostFs.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_FileSystem_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::sysmon.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_Module.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::runctrl-ext.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::processes.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::WR_SymbolsList_proxy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::profiler_spy.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::patch_linenumbers_elf.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::expressions.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::mdep.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::c_ppc_crawl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::ppc_crawl_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::module_patch_ppc.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::adapter_craw_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::c_stack_crawl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::stackcrawl.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::c_crawl_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::common_crawl_lib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}
 
ObjectFile libtcfagent.a::tcfLib.o { 
	PATH krnl/PPCE6500/common/objtcfagent/
}



