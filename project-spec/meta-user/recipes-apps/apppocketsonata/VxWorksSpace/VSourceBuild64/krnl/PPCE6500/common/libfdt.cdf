Symbol fdt_check_header {
}
Symbol .TOC. {
}
Symbol fdt_offset_ptr {
}
Symbol fdt_next_tag {
}
Symbol _fdt_check_node_offset {
}
Symbol _fdt_check_prop_offset {
}
Symbol fdt_next_node {
}
Symbol fdt_first_subnode {
}
Symbol fdt_next_subnode {
}
Symbol _fdt_find_string {
}
Symbol strlen {
}
Symbol memcmp {
}
Symbol fdt_move {
}
Symbol memmove {
}
Symbol memchr {
}
Symbol fdt_string {
}
Symbol fdt_get_mem_rsv {
}
Symbol fdt_num_mem_rsv {
}
Symbol fdt_subnode_offset_namelen {
}
Symbol fdt_subnode_offset {
}
Symbol fdt_first_property_offset {
}
Symbol fdt_next_property_offset {
}
Symbol fdt_get_property_by_offset {
}
Symbol fdt_get_property_namelen {
}
Symbol fdt_getprop_namelen {
}
Symbol fdt_get_alias_namelen {
}
Symbol fdt_path_offset {
}
Symbol strchr {
}
Symbol fdt_get_name {
}
Symbol fdt_get_property {
}
Symbol fdt_getprop_by_offset {
}
Symbol fdt_getprop {
}
Symbol fdt_get_phandle {
}
Symbol fdt_get_alias {
}
Symbol fdt_get_path {
}
Symbol memcpy {
}
Symbol fdt_supernode_atdepth_offset {
}
Symbol fdt_node_depth {
}
Symbol fdt_parent_offset {
}
Symbol fdt_node_offset_by_prop_value {
}
Symbol fdt_node_offset_by_phandle {
}
Symbol fdt_stringlist_contains {
}
Symbol fdt_node_check_compatible {
}
Symbol fdt_node_offset_by_compatible {
}
Symbol fdt_add_mem_rsv {
}
Symbol fdt_del_mem_rsv {
}
Symbol fdt_set_name {
}
Symbol fdt_setprop {
}
Symbol fdt_appendprop {
}
Symbol fdt_delprop {
}
Symbol fdt_add_subnode_namelen {
}
Symbol memset {
}
Symbol fdt_add_subnode {
}
Symbol fdt_del_node {
}
Symbol _fdt_node_end_offset {
}
Symbol fdt_open_into {
}
Symbol fdt_pack {
}
Symbol fdt_setprop_inplace {
}
Symbol fdt_nop_property {
}
Symbol fdt_nop_node {
}
Symbol fdt_create_empty_tree {
}
Symbol fdt_create {
}
Symbol fdt_finish_reservemap {
}
Symbol fdt_begin_node {
}
Symbol fdt_end_node {
}
Symbol fdt_finish {
}
Symbol fdt_add_reservemap_entry {
}
Symbol fdt_property {
}
Symbol fdt_strerror {
}
Symbol isprint {
}
Symbol printf {
}
Symbol fdt_dump {
}
Symbol vxFdtLibInit {
}
Symbol vxFdt16ToCpu {
}
Symbol vxCpuToFdt16 {
}
Symbol vxFdt32ToCpu {
}
Symbol vxCpuToFdt32 {
}
Symbol vxFdt64ToCpu {
}
Symbol vxCpuToFdt64 {
}
Symbol vxFdtPathOffset {
}
Symbol vxFdtNextNode {
}
Symbol vxFdtParentOffset {
}
Symbol vxFdtFirstSubnode {
}
Symbol vxFdtNextSubnode {
}
Symbol vxFdtPropGet {
}
Symbol vxFdtFirstPropGet {
}
Symbol vxFdtNextPropGet {
}
Symbol vxFdtGetName {
}
Symbol vxFdtIsEnabled {
}
Symbol strncmp {
}
Symbol vxFdtDisable {
}
Symbol vxFdtNodeOffsetByPhandle {
}
Symbol vxFdtNodeOffsetByCompatible {
}
Symbol vxFdtNodeCheckCompatible {
}
Symbol vxFdtCellGet {
}
Symbol vxFdtDefRegGet {
}
Symbol vxFdtStdoutGet {
}
Symbol vxFdtPhysMemInfoGet {
}
Symbol vxFdtBootargsGet {
}
Symbol strncpy {
}
Symbol vxFdtDtbAddressGet {
}
Symbol vxFdtCpuAvail {
}
Symbol strcmp {
}
Symbol vxFdtCpuInfoGet {
}
Symbol vxFdtDelNode {
}
Symbol vxFdtPropSet {
}
Symbol vxFdtShowInit {
}
Symbol vxFdtDtbDump {
}
ObjectFile libfdt.a::fdt.o {
	NAME Object file fdt.o from archive libfdt.a
	EXPORTS fdt_check_header fdt_offset_ptr fdt_next_tag _fdt_check_node_offset _fdt_check_prop_offset fdt_next_node fdt_first_subnode fdt_next_subnode _fdt_find_string fdt_move
	IMPORTS .TOC. strlen memcmp memmove
	DECLARES 
	USES 
}
Module fdt.o {
	OBJECT += libfdt.a::fdt.o
}
ObjectFile libfdt.a::fdt_ro.o {
	NAME Object file fdt_ro.o from archive libfdt.a
	EXPORTS fdt_string fdt_get_mem_rsv fdt_num_mem_rsv fdt_subnode_offset_namelen fdt_subnode_offset fdt_first_property_offset fdt_next_property_offset fdt_get_property_by_offset fdt_get_property_namelen fdt_getprop_namelen fdt_get_alias_namelen fdt_path_offset fdt_get_name fdt_get_property fdt_getprop_by_offset fdt_getprop fdt_get_phandle fdt_get_alias fdt_get_path fdt_supernode_atdepth_offset fdt_node_depth fdt_parent_offset fdt_node_offset_by_prop_value fdt_node_offset_by_phandle fdt_stringlist_contains fdt_node_check_compatible fdt_node_offset_by_compatible
	IMPORTS .TOC. fdt_offset_ptr memcmp memchr strlen fdt_check_header fdt_next_tag fdt_next_node _fdt_check_node_offset _fdt_check_prop_offset strchr memcpy
	DECLARES 
	USES 
}
Module fdt_ro.o {
	OBJECT += libfdt.a::fdt_ro.o
}
ObjectFile libfdt.a::fdt_rw.o {
	NAME Object file fdt_rw.o from archive libfdt.a
	EXPORTS fdt_add_mem_rsv fdt_del_mem_rsv fdt_set_name fdt_setprop fdt_appendprop fdt_delprop fdt_add_subnode_namelen fdt_add_subnode fdt_del_node fdt_open_into fdt_pack
	IMPORTS .TOC. fdt_check_header memmove strlen _fdt_find_string memcpy fdt_num_mem_rsv fdt_get_property _fdt_check_node_offset fdt_get_name fdt_subnode_offset_namelen fdt_next_tag memset _fdt_node_end_offset fdt_move
	DECLARES 
	USES 
}
Module fdt_rw.o {
	OBJECT += libfdt.a::fdt_rw.o
}
ObjectFile libfdt.a::fdt_wip.o {
	NAME Object file fdt_wip.o from archive libfdt.a
	EXPORTS fdt_setprop_inplace fdt_nop_property _fdt_node_end_offset fdt_nop_node
	IMPORTS .TOC. fdt_getprop memcpy fdt_get_property fdt_next_node fdt_offset_ptr
	DECLARES 
	USES 
}
Module fdt_wip.o {
	OBJECT += libfdt.a::fdt_wip.o
}
ObjectFile libfdt.a::fdt_empty_tree.o {
	NAME Object file fdt_empty_tree.o from archive libfdt.a
	EXPORTS fdt_create_empty_tree
	IMPORTS .TOC. fdt_create fdt_finish_reservemap fdt_begin_node fdt_end_node fdt_finish fdt_open_into
	DECLARES 
	USES 
}
Module fdt_empty_tree.o {
	OBJECT += libfdt.a::fdt_empty_tree.o
}
ObjectFile libfdt.a::fdt_sw.o {
	NAME Object file fdt_sw.o from archive libfdt.a
	EXPORTS fdt_create fdt_add_reservemap_entry fdt_finish_reservemap fdt_begin_node fdt_end_node fdt_property fdt_finish
	IMPORTS .TOC. memset strlen memcpy _fdt_find_string memmove fdt_next_tag
	DECLARES 
	USES 
}
Module fdt_sw.o {
	OBJECT += libfdt.a::fdt_sw.o
}
ObjectFile libfdt.a::fdt_strerror.o {
	NAME Object file fdt_strerror.o from archive libfdt.a
	EXPORTS fdt_strerror
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fdt_strerror.o {
	OBJECT += libfdt.a::fdt_strerror.o
}
ObjectFile libfdt.a::fdt_show.o {
	NAME Object file fdt_show.o from archive libfdt.a
	EXPORTS fdt_dump
	IMPORTS .TOC. isprint printf fdt_check_header fdt_path_offset fdt_next_tag fdt_get_name fdt_offset_ptr fdt_string fdt_strerror
	DECLARES 
	USES 
}
Module fdt_show.o {
	OBJECT += libfdt.a::fdt_show.o
}
ObjectFile libfdt.a::vxFdtLib.o {
	NAME Object file vxFdtLib.o from archive libfdt.a
	EXPORTS vxFdtLibInit vxFdt16ToCpu vxCpuToFdt16 vxFdt32ToCpu vxCpuToFdt32 vxFdt64ToCpu vxCpuToFdt64 vxFdtPathOffset vxFdtNextNode vxFdtParentOffset vxFdtFirstSubnode vxFdtNextSubnode vxFdtPropGet vxFdtFirstPropGet vxFdtNextPropGet vxFdtGetName vxFdtIsEnabled vxFdtDisable vxFdtNodeOffsetByPhandle vxFdtNodeOffsetByCompatible vxFdtNodeCheckCompatible vxFdtCellGet vxFdtDefRegGet vxFdtStdoutGet vxFdtPhysMemInfoGet vxFdtBootargsGet vxFdtDtbAddressGet
	IMPORTS .TOC. fdt_open_into fdt_path_offset fdt_next_node fdt_parent_offset fdt_first_subnode fdt_next_subnode fdt_getprop fdt_first_property_offset fdt_getprop_by_offset fdt_next_property_offset fdt_get_name strncmp fdt_nop_node fdt_node_offset_by_phandle fdt_node_offset_by_compatible fdt_node_check_compatible strncpy
	DECLARES 
	USES 
}
Module vxFdtLib.o {
	OBJECT += libfdt.a::vxFdtLib.o
}
ObjectFile libfdt.a::vxFdtCpu.o {
	NAME Object file vxFdtCpu.o from archive libfdt.a
	EXPORTS vxFdtCpuAvail vxFdtCpuInfoGet
	IMPORTS .TOC. vxFdtPathOffset vxFdtNextNode vxFdtPropGet strcmp vxFdtFirstSubnode vxFdtNextSubnode
	DECLARES 
	USES 
}
Module vxFdtCpu.o {
	OBJECT += libfdt.a::vxFdtCpu.o
}
ObjectFile libfdt.a::vxFdtRwLib.o {
	NAME Object file vxFdtRwLib.o from archive libfdt.a
	EXPORTS vxFdtDelNode vxFdtPropSet
	IMPORTS .TOC. vxFdtDtbAddressGet fdt_del_node fdt_setprop
	DECLARES 
	USES 
}
Module vxFdtRwLib.o {
	OBJECT += libfdt.a::vxFdtRwLib.o
}
ObjectFile libfdt.a::vxFdtShow.o {
	NAME Object file vxFdtShow.o from archive libfdt.a
	EXPORTS vxFdtShowInit vxFdtDtbDump
	IMPORTS .TOC. vxFdtDtbAddressGet fdt_dump
	DECLARES 
	USES 
}
Module vxFdtShow.o {
	OBJECT += libfdt.a::vxFdtShow.o
}
Library libfdt.a {
	MODULES libfdt.a::fdt.o libfdt.a::fdt_ro.o libfdt.a::fdt_rw.o libfdt.a::fdt_wip.o libfdt.a::fdt_empty_tree.o libfdt.a::fdt_sw.o libfdt.a::fdt_strerror.o libfdt.a::fdt_show.o libfdt.a::vxFdtLib.o libfdt.a::vxFdtCpu.o libfdt.a::vxFdtRwLib.o libfdt.a::vxFdtShow.o
}
Symbol fdt_check_header {
}
Symbol .TOC. {
}
Symbol fdt_offset_ptr {
}
Symbol fdt_next_tag {
}
Symbol _fdt_check_node_offset {
}
Symbol _fdt_check_prop_offset {
}
Symbol fdt_next_node {
}
Symbol fdt_first_subnode {
}
Symbol fdt_next_subnode {
}
Symbol _fdt_find_string {
}
Symbol strlen {
}
Symbol memcmp {
}
Symbol fdt_move {
}
Symbol memmove {
}
Symbol memchr {
}
Symbol fdt_string {
}
Symbol fdt_get_mem_rsv {
}
Symbol fdt_num_mem_rsv {
}
Symbol fdt_subnode_offset_namelen {
}
Symbol fdt_subnode_offset {
}
Symbol fdt_first_property_offset {
}
Symbol fdt_next_property_offset {
}
Symbol fdt_get_property_by_offset {
}
Symbol fdt_get_property_namelen {
}
Symbol fdt_getprop_namelen {
}
Symbol fdt_get_alias_namelen {
}
Symbol fdt_path_offset {
}
Symbol strchr {
}
Symbol fdt_get_name {
}
Symbol fdt_get_property {
}
Symbol fdt_getprop_by_offset {
}
Symbol fdt_getprop {
}
Symbol fdt_get_phandle {
}
Symbol fdt_get_alias {
}
Symbol fdt_get_path {
}
Symbol memcpy {
}
Symbol fdt_supernode_atdepth_offset {
}
Symbol fdt_node_depth {
}
Symbol fdt_parent_offset {
}
Symbol fdt_node_offset_by_prop_value {
}
Symbol fdt_node_offset_by_phandle {
}
Symbol fdt_stringlist_contains {
}
Symbol fdt_node_check_compatible {
}
Symbol fdt_node_offset_by_compatible {
}
Symbol fdt_add_mem_rsv {
}
Symbol fdt_del_mem_rsv {
}
Symbol fdt_set_name {
}
Symbol fdt_setprop {
}
Symbol fdt_appendprop {
}
Symbol fdt_delprop {
}
Symbol fdt_add_subnode_namelen {
}
Symbol memset {
}
Symbol fdt_add_subnode {
}
Symbol fdt_del_node {
}
Symbol _fdt_node_end_offset {
}
Symbol fdt_open_into {
}
Symbol fdt_pack {
}
Symbol fdt_setprop_inplace {
}
Symbol fdt_nop_property {
}
Symbol fdt_nop_node {
}
Symbol fdt_create_empty_tree {
}
Symbol fdt_create {
}
Symbol fdt_finish_reservemap {
}
Symbol fdt_begin_node {
}
Symbol fdt_end_node {
}
Symbol fdt_finish {
}
Symbol fdt_add_reservemap_entry {
}
Symbol fdt_property {
}
Symbol fdt_strerror {
}
Symbol isprint {
}
Symbol printf {
}
Symbol fdt_dump {
}
Symbol vxFdtLibInit {
}
Symbol vxFdt16ToCpu {
}
Symbol vxCpuToFdt16 {
}
Symbol vxFdt32ToCpu {
}
Symbol vxCpuToFdt32 {
}
Symbol vxFdt64ToCpu {
}
Symbol vxCpuToFdt64 {
}
Symbol vxFdtPathOffset {
}
Symbol vxFdtNextNode {
}
Symbol vxFdtParentOffset {
}
Symbol vxFdtFirstSubnode {
}
Symbol vxFdtNextSubnode {
}
Symbol vxFdtPropGet {
}
Symbol vxFdtFirstPropGet {
}
Symbol vxFdtNextPropGet {
}
Symbol vxFdtGetName {
}
Symbol vxFdtIsEnabled {
}
Symbol strncmp {
}
Symbol vxFdtDisable {
}
Symbol vxFdtNodeOffsetByPhandle {
}
Symbol vxFdtNodeOffsetByCompatible {
}
Symbol vxFdtNodeCheckCompatible {
}
Symbol vxFdtCellGet {
}
Symbol vxFdtDefRegGet {
}
Symbol vxFdtStdoutGet {
}
Symbol vxFdtPhysMemInfoGet {
}
Symbol vxFdtBootargsGet {
}
Symbol strncpy {
}
Symbol vxFdtDtbAddressGet {
}
Symbol vxFdtCpuAvail {
}
Symbol strcmp {
}
Symbol vxFdtCpuInfoGet {
}
Symbol vxFdtDelNode {
}
Symbol vxFdtPropSet {
}
Symbol vxFdtShowInit {
}
Symbol vxFdtDtbDump {
}
ObjectFile libfdt.a::fdt.o {
	NAME Object file fdt.o from archive libfdt.a
	EXPORTS fdt_check_header fdt_offset_ptr fdt_next_tag _fdt_check_node_offset _fdt_check_prop_offset fdt_next_node fdt_first_subnode fdt_next_subnode _fdt_find_string fdt_move
	IMPORTS .TOC. strlen memcmp memmove
	DECLARES 
	USES 
}
Module fdt.o {
	OBJECT += libfdt.a::fdt.o
}
ObjectFile libfdt.a::fdt_ro.o {
	NAME Object file fdt_ro.o from archive libfdt.a
	EXPORTS fdt_string fdt_get_mem_rsv fdt_num_mem_rsv fdt_subnode_offset_namelen fdt_subnode_offset fdt_first_property_offset fdt_next_property_offset fdt_get_property_by_offset fdt_get_property_namelen fdt_getprop_namelen fdt_get_alias_namelen fdt_path_offset fdt_get_name fdt_get_property fdt_getprop_by_offset fdt_getprop fdt_get_phandle fdt_get_alias fdt_get_path fdt_supernode_atdepth_offset fdt_node_depth fdt_parent_offset fdt_node_offset_by_prop_value fdt_node_offset_by_phandle fdt_stringlist_contains fdt_node_check_compatible fdt_node_offset_by_compatible
	IMPORTS .TOC. fdt_offset_ptr memcmp memchr strlen fdt_check_header fdt_next_tag fdt_next_node _fdt_check_node_offset _fdt_check_prop_offset strchr memcpy
	DECLARES 
	USES 
}
Module fdt_ro.o {
	OBJECT += libfdt.a::fdt_ro.o
}
ObjectFile libfdt.a::fdt_rw.o {
	NAME Object file fdt_rw.o from archive libfdt.a
	EXPORTS fdt_add_mem_rsv fdt_del_mem_rsv fdt_set_name fdt_setprop fdt_appendprop fdt_delprop fdt_add_subnode_namelen fdt_add_subnode fdt_del_node fdt_open_into fdt_pack
	IMPORTS .TOC. fdt_check_header memmove strlen _fdt_find_string memcpy fdt_num_mem_rsv fdt_get_property _fdt_check_node_offset fdt_get_name fdt_subnode_offset_namelen fdt_next_tag memset _fdt_node_end_offset fdt_move
	DECLARES 
	USES 
}
Module fdt_rw.o {
	OBJECT += libfdt.a::fdt_rw.o
}
ObjectFile libfdt.a::fdt_wip.o {
	NAME Object file fdt_wip.o from archive libfdt.a
	EXPORTS fdt_setprop_inplace fdt_nop_property _fdt_node_end_offset fdt_nop_node
	IMPORTS .TOC. fdt_getprop memcpy fdt_get_property fdt_next_node fdt_offset_ptr
	DECLARES 
	USES 
}
Module fdt_wip.o {
	OBJECT += libfdt.a::fdt_wip.o
}
ObjectFile libfdt.a::fdt_empty_tree.o {
	NAME Object file fdt_empty_tree.o from archive libfdt.a
	EXPORTS fdt_create_empty_tree
	IMPORTS .TOC. fdt_create fdt_finish_reservemap fdt_begin_node fdt_end_node fdt_finish fdt_open_into
	DECLARES 
	USES 
}
Module fdt_empty_tree.o {
	OBJECT += libfdt.a::fdt_empty_tree.o
}
ObjectFile libfdt.a::fdt_sw.o {
	NAME Object file fdt_sw.o from archive libfdt.a
	EXPORTS fdt_create fdt_add_reservemap_entry fdt_finish_reservemap fdt_begin_node fdt_end_node fdt_property fdt_finish
	IMPORTS .TOC. memset strlen memcpy _fdt_find_string memmove fdt_next_tag
	DECLARES 
	USES 
}
Module fdt_sw.o {
	OBJECT += libfdt.a::fdt_sw.o
}
ObjectFile libfdt.a::fdt_strerror.o {
	NAME Object file fdt_strerror.o from archive libfdt.a
	EXPORTS fdt_strerror
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fdt_strerror.o {
	OBJECT += libfdt.a::fdt_strerror.o
}
ObjectFile libfdt.a::fdt_show.o {
	NAME Object file fdt_show.o from archive libfdt.a
	EXPORTS fdt_dump
	IMPORTS .TOC. isprint printf fdt_check_header fdt_path_offset fdt_next_tag fdt_get_name fdt_offset_ptr fdt_string fdt_strerror
	DECLARES 
	USES 
}
Module fdt_show.o {
	OBJECT += libfdt.a::fdt_show.o
}
ObjectFile libfdt.a::vxFdtLib.o {
	NAME Object file vxFdtLib.o from archive libfdt.a
	EXPORTS vxFdtLibInit vxFdt16ToCpu vxCpuToFdt16 vxFdt32ToCpu vxCpuToFdt32 vxFdt64ToCpu vxCpuToFdt64 vxFdtPathOffset vxFdtNextNode vxFdtParentOffset vxFdtFirstSubnode vxFdtNextSubnode vxFdtPropGet vxFdtFirstPropGet vxFdtNextPropGet vxFdtGetName vxFdtIsEnabled vxFdtDisable vxFdtNodeOffsetByPhandle vxFdtNodeOffsetByCompatible vxFdtNodeCheckCompatible vxFdtCellGet vxFdtDefRegGet vxFdtStdoutGet vxFdtPhysMemInfoGet vxFdtBootargsGet vxFdtDtbAddressGet
	IMPORTS .TOC. fdt_open_into fdt_path_offset fdt_next_node fdt_parent_offset fdt_first_subnode fdt_next_subnode fdt_getprop fdt_first_property_offset fdt_getprop_by_offset fdt_next_property_offset fdt_get_name strncmp fdt_nop_node fdt_node_offset_by_phandle fdt_node_offset_by_compatible fdt_node_check_compatible strncpy
	DECLARES 
	USES 
}
Module vxFdtLib.o {
	OBJECT += libfdt.a::vxFdtLib.o
}
ObjectFile libfdt.a::vxFdtCpu.o {
	NAME Object file vxFdtCpu.o from archive libfdt.a
	EXPORTS vxFdtCpuAvail vxFdtCpuInfoGet
	IMPORTS .TOC. vxFdtPathOffset vxFdtNextNode vxFdtPropGet strcmp vxFdtFirstSubnode vxFdtNextSubnode
	DECLARES 
	USES 
}
Module vxFdtCpu.o {
	OBJECT += libfdt.a::vxFdtCpu.o
}
ObjectFile libfdt.a::vxFdtRwLib.o {
	NAME Object file vxFdtRwLib.o from archive libfdt.a
	EXPORTS vxFdtDelNode vxFdtPropSet
	IMPORTS .TOC. vxFdtDtbAddressGet fdt_del_node fdt_setprop
	DECLARES 
	USES 
}
Module vxFdtRwLib.o {
	OBJECT += libfdt.a::vxFdtRwLib.o
}
ObjectFile libfdt.a::vxFdtShow.o {
	NAME Object file vxFdtShow.o from archive libfdt.a
	EXPORTS vxFdtShowInit vxFdtDtbDump
	IMPORTS .TOC. vxFdtDtbAddressGet fdt_dump
	DECLARES 
	USES 
}
Module vxFdtShow.o {
	OBJECT += libfdt.a::vxFdtShow.o
}
Library libfdt.a {
	MODULES libfdt.a::fdt.o libfdt.a::fdt_ro.o libfdt.a::fdt_rw.o libfdt.a::fdt_wip.o libfdt.a::fdt_empty_tree.o libfdt.a::fdt_sw.o libfdt.a::fdt_strerror.o libfdt.a::fdt_show.o libfdt.a::vxFdtLib.o libfdt.a::vxFdtCpu.o libfdt.a::vxFdtRwLib.o libfdt.a::vxFdtShow.o
}
Symbol fdt_check_header {
}
Symbol .TOC. {
}
Symbol fdt_offset_ptr {
}
Symbol fdt_next_tag {
}
Symbol _fdt_check_node_offset {
}
Symbol _fdt_check_prop_offset {
}
Symbol fdt_next_node {
}
Symbol fdt_first_subnode {
}
Symbol fdt_next_subnode {
}
Symbol _fdt_find_string {
}
Symbol strlen {
}
Symbol memcmp {
}
Symbol fdt_move {
}
Symbol memmove {
}
Symbol memchr {
}
Symbol fdt_string {
}
Symbol fdt_get_mem_rsv {
}
Symbol fdt_num_mem_rsv {
}
Symbol fdt_subnode_offset_namelen {
}
Symbol fdt_subnode_offset {
}
Symbol fdt_first_property_offset {
}
Symbol fdt_next_property_offset {
}
Symbol fdt_get_property_by_offset {
}
Symbol fdt_get_property_namelen {
}
Symbol fdt_getprop_namelen {
}
Symbol fdt_get_alias_namelen {
}
Symbol fdt_path_offset {
}
Symbol strchr {
}
Symbol fdt_get_name {
}
Symbol fdt_get_property {
}
Symbol fdt_getprop_by_offset {
}
Symbol fdt_getprop {
}
Symbol fdt_get_phandle {
}
Symbol fdt_get_alias {
}
Symbol fdt_get_path {
}
Symbol memcpy {
}
Symbol fdt_supernode_atdepth_offset {
}
Symbol fdt_node_depth {
}
Symbol fdt_parent_offset {
}
Symbol fdt_node_offset_by_prop_value {
}
Symbol fdt_node_offset_by_phandle {
}
Symbol fdt_stringlist_contains {
}
Symbol fdt_node_check_compatible {
}
Symbol fdt_node_offset_by_compatible {
}
Symbol fdt_add_mem_rsv {
}
Symbol fdt_del_mem_rsv {
}
Symbol fdt_set_name {
}
Symbol fdt_setprop {
}
Symbol fdt_appendprop {
}
Symbol fdt_delprop {
}
Symbol fdt_add_subnode_namelen {
}
Symbol memset {
}
Symbol fdt_add_subnode {
}
Symbol fdt_del_node {
}
Symbol _fdt_node_end_offset {
}
Symbol fdt_open_into {
}
Symbol fdt_pack {
}
Symbol fdt_setprop_inplace {
}
Symbol fdt_nop_property {
}
Symbol fdt_nop_node {
}
Symbol fdt_create_empty_tree {
}
Symbol fdt_create {
}
Symbol fdt_finish_reservemap {
}
Symbol fdt_begin_node {
}
Symbol fdt_end_node {
}
Symbol fdt_finish {
}
Symbol fdt_add_reservemap_entry {
}
Symbol fdt_property {
}
Symbol fdt_strerror {
}
Symbol isprint {
}
Symbol printf {
}
Symbol fdt_dump {
}
Symbol vxFdtLibInit {
}
Symbol vxFdt16ToCpu {
}
Symbol vxCpuToFdt16 {
}
Symbol vxFdt32ToCpu {
}
Symbol vxCpuToFdt32 {
}
Symbol vxFdt64ToCpu {
}
Symbol vxCpuToFdt64 {
}
Symbol vxFdtPathOffset {
}
Symbol vxFdtNextNode {
}
Symbol vxFdtParentOffset {
}
Symbol vxFdtFirstSubnode {
}
Symbol vxFdtNextSubnode {
}
Symbol vxFdtPropGet {
}
Symbol vxFdtFirstPropGet {
}
Symbol vxFdtNextPropGet {
}
Symbol vxFdtGetName {
}
Symbol vxFdtIsEnabled {
}
Symbol strncmp {
}
Symbol vxFdtDisable {
}
Symbol vxFdtNodeOffsetByPhandle {
}
Symbol vxFdtNodeOffsetByCompatible {
}
Symbol vxFdtNodeCheckCompatible {
}
Symbol vxFdtCellGet {
}
Symbol vxFdtDefRegGet {
}
Symbol vxFdtStdoutGet {
}
Symbol vxFdtPhysMemInfoGet {
}
Symbol vxFdtBootargsGet {
}
Symbol strncpy {
}
Symbol vxFdtDtbAddressGet {
}
Symbol vxFdtCpuAvail {
}
Symbol strcmp {
}
Symbol vxFdtCpuInfoGet {
}
Symbol vxFdtDelNode {
}
Symbol vxFdtPropSet {
}
Symbol vxFdtShowInit {
}
Symbol vxFdtDtbDump {
}
ObjectFile libfdt.a::fdt.o {
	NAME Object file fdt.o from archive libfdt.a
	EXPORTS fdt_check_header fdt_offset_ptr fdt_next_tag _fdt_check_node_offset _fdt_check_prop_offset fdt_next_node fdt_first_subnode fdt_next_subnode _fdt_find_string fdt_move
	IMPORTS .TOC. strlen memcmp memmove
	DECLARES 
	USES 
}
Module fdt.o {
	OBJECT += libfdt.a::fdt.o
}
ObjectFile libfdt.a::fdt_ro.o {
	NAME Object file fdt_ro.o from archive libfdt.a
	EXPORTS fdt_string fdt_get_mem_rsv fdt_num_mem_rsv fdt_subnode_offset_namelen fdt_subnode_offset fdt_first_property_offset fdt_next_property_offset fdt_get_property_by_offset fdt_get_property_namelen fdt_getprop_namelen fdt_get_alias_namelen fdt_path_offset fdt_get_name fdt_get_property fdt_getprop_by_offset fdt_getprop fdt_get_phandle fdt_get_alias fdt_get_path fdt_supernode_atdepth_offset fdt_node_depth fdt_parent_offset fdt_node_offset_by_prop_value fdt_node_offset_by_phandle fdt_stringlist_contains fdt_node_check_compatible fdt_node_offset_by_compatible
	IMPORTS .TOC. fdt_offset_ptr memcmp memchr strlen fdt_check_header fdt_next_tag fdt_next_node _fdt_check_node_offset _fdt_check_prop_offset strchr memcpy
	DECLARES 
	USES 
}
Module fdt_ro.o {
	OBJECT += libfdt.a::fdt_ro.o
}
ObjectFile libfdt.a::fdt_rw.o {
	NAME Object file fdt_rw.o from archive libfdt.a
	EXPORTS fdt_add_mem_rsv fdt_del_mem_rsv fdt_set_name fdt_setprop fdt_appendprop fdt_delprop fdt_add_subnode_namelen fdt_add_subnode fdt_del_node fdt_open_into fdt_pack
	IMPORTS .TOC. fdt_check_header memmove strlen _fdt_find_string memcpy fdt_num_mem_rsv fdt_get_property _fdt_check_node_offset fdt_get_name fdt_subnode_offset_namelen fdt_next_tag memset _fdt_node_end_offset fdt_move
	DECLARES 
	USES 
}
Module fdt_rw.o {
	OBJECT += libfdt.a::fdt_rw.o
}
ObjectFile libfdt.a::fdt_wip.o {
	NAME Object file fdt_wip.o from archive libfdt.a
	EXPORTS fdt_setprop_inplace fdt_nop_property _fdt_node_end_offset fdt_nop_node
	IMPORTS .TOC. fdt_getprop memcpy fdt_get_property fdt_next_node fdt_offset_ptr
	DECLARES 
	USES 
}
Module fdt_wip.o {
	OBJECT += libfdt.a::fdt_wip.o
}
ObjectFile libfdt.a::fdt_empty_tree.o {
	NAME Object file fdt_empty_tree.o from archive libfdt.a
	EXPORTS fdt_create_empty_tree
	IMPORTS .TOC. fdt_create fdt_finish_reservemap fdt_begin_node fdt_end_node fdt_finish fdt_open_into
	DECLARES 
	USES 
}
Module fdt_empty_tree.o {
	OBJECT += libfdt.a::fdt_empty_tree.o
}
ObjectFile libfdt.a::fdt_sw.o {
	NAME Object file fdt_sw.o from archive libfdt.a
	EXPORTS fdt_create fdt_add_reservemap_entry fdt_finish_reservemap fdt_begin_node fdt_end_node fdt_property fdt_finish
	IMPORTS .TOC. memset strlen memcpy _fdt_find_string memmove fdt_next_tag
	DECLARES 
	USES 
}
Module fdt_sw.o {
	OBJECT += libfdt.a::fdt_sw.o
}
ObjectFile libfdt.a::fdt_strerror.o {
	NAME Object file fdt_strerror.o from archive libfdt.a
	EXPORTS fdt_strerror
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fdt_strerror.o {
	OBJECT += libfdt.a::fdt_strerror.o
}
ObjectFile libfdt.a::fdt_show.o {
	NAME Object file fdt_show.o from archive libfdt.a
	EXPORTS fdt_dump
	IMPORTS .TOC. isprint printf fdt_check_header fdt_path_offset fdt_next_tag fdt_get_name fdt_offset_ptr fdt_string fdt_strerror
	DECLARES 
	USES 
}
Module fdt_show.o {
	OBJECT += libfdt.a::fdt_show.o
}
ObjectFile libfdt.a::vxFdtLib.o {
	NAME Object file vxFdtLib.o from archive libfdt.a
	EXPORTS vxFdtLibInit vxFdt16ToCpu vxCpuToFdt16 vxFdt32ToCpu vxCpuToFdt32 vxFdt64ToCpu vxCpuToFdt64 vxFdtPathOffset vxFdtNextNode vxFdtParentOffset vxFdtFirstSubnode vxFdtNextSubnode vxFdtPropGet vxFdtFirstPropGet vxFdtNextPropGet vxFdtGetName vxFdtIsEnabled vxFdtDisable vxFdtNodeOffsetByPhandle vxFdtNodeOffsetByCompatible vxFdtNodeCheckCompatible vxFdtCellGet vxFdtDefRegGet vxFdtStdoutGet vxFdtPhysMemInfoGet vxFdtBootargsGet vxFdtDtbAddressGet
	IMPORTS .TOC. fdt_open_into fdt_path_offset fdt_next_node fdt_parent_offset fdt_first_subnode fdt_next_subnode fdt_getprop fdt_first_property_offset fdt_getprop_by_offset fdt_next_property_offset fdt_get_name strncmp fdt_nop_node fdt_node_offset_by_phandle fdt_node_offset_by_compatible fdt_node_check_compatible strncpy
	DECLARES 
	USES 
}
Module vxFdtLib.o {
	OBJECT += libfdt.a::vxFdtLib.o
}
ObjectFile libfdt.a::vxFdtCpu.o {
	NAME Object file vxFdtCpu.o from archive libfdt.a
	EXPORTS vxFdtCpuAvail vxFdtCpuInfoGet
	IMPORTS .TOC. vxFdtPathOffset vxFdtNextNode vxFdtPropGet strcmp vxFdtFirstSubnode vxFdtNextSubnode
	DECLARES 
	USES 
}
Module vxFdtCpu.o {
	OBJECT += libfdt.a::vxFdtCpu.o
}
ObjectFile libfdt.a::vxFdtRwLib.o {
	NAME Object file vxFdtRwLib.o from archive libfdt.a
	EXPORTS vxFdtDelNode vxFdtPropSet
	IMPORTS .TOC. vxFdtDtbAddressGet fdt_del_node fdt_setprop
	DECLARES 
	USES 
}
Module vxFdtRwLib.o {
	OBJECT += libfdt.a::vxFdtRwLib.o
}
ObjectFile libfdt.a::vxFdtShow.o {
	NAME Object file vxFdtShow.o from archive libfdt.a
	EXPORTS vxFdtShowInit vxFdtDtbDump
	IMPORTS .TOC. vxFdtDtbAddressGet fdt_dump
	DECLARES 
	USES 
}
Module vxFdtShow.o {
	OBJECT += libfdt.a::vxFdtShow.o
}
Library libfdt.a {
	MODULES libfdt.a::fdt.o libfdt.a::fdt_ro.o libfdt.a::fdt_rw.o libfdt.a::fdt_wip.o libfdt.a::fdt_empty_tree.o libfdt.a::fdt_sw.o libfdt.a::fdt_strerror.o libfdt.a::fdt_show.o libfdt.a::vxFdtLib.o libfdt.a::vxFdtCpu.o libfdt.a::vxFdtRwLib.o libfdt.a::vxFdtShow.o
}
