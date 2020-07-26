// (c) Copyright 1995-2020 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:hls:stats_top:1.0
// IP Revision: 1802121322

(* X_CORE_INFO = "stats_top,Vivado 2020.1" *)
(* CHECK_LICENSE_TYPE = "project_1_stats_0,stats_top,{}" *)
(* CORE_GENERATION_INFO = "project_1_stats_0,stats_top,{x_ipProduct=Vivado 2020.1,x_ipVendor=xilinx.com,x_ipLibrary=hls,x_ipName=stats_top,x_ipVersion=1.0,x_ipCoreRevision=1802121322,x_ipLanguage=VERILOG,x_ipSimLanguage=MIXED,C_S_AXI_CNTRL_ADDR_WIDTH=7,C_S_AXI_CNTRL_DATA_WIDTH=32}" *)
(* IP_DEFINITION_SOURCE = "HLS" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module project_1_stats_0 (
  s_axi_CNTRL_AWADDR,
  s_axi_CNTRL_AWVALID,
  s_axi_CNTRL_AWREADY,
  s_axi_CNTRL_WDATA,
  s_axi_CNTRL_WSTRB,
  s_axi_CNTRL_WVALID,
  s_axi_CNTRL_WREADY,
  s_axi_CNTRL_BRESP,
  s_axi_CNTRL_BVALID,
  s_axi_CNTRL_BREADY,
  s_axi_CNTRL_ARADDR,
  s_axi_CNTRL_ARVALID,
  s_axi_CNTRL_ARREADY,
  s_axi_CNTRL_RDATA,
  s_axi_CNTRL_RRESP,
  s_axi_CNTRL_RVALID,
  s_axi_CNTRL_RREADY,
  ap_clk,
  ap_rst_n,
  interrupt,
  cntrl_aclk,
  ap_rst_n_cntrl_aclk,
  src_data_V_V_TVALID,
  src_data_V_V_TREADY,
  src_data_V_V_TDATA,
  hard_data_TVALID,
  hard_data_TREADY,
  hard_data_TDATA,
  hard_data_TLAST,
  error_data_TVALID,
  error_data_TREADY,
  error_data_TDATA,
  error_data_TLAST,
  fe_status_V_V_TVALID,
  fe_status_V_V_TREADY,
  fe_status_V_V_TDATA
);

(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWADDR" *)
input wire [6 : 0] s_axi_CNTRL_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWVALID" *)
input wire s_axi_CNTRL_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWREADY" *)
output wire s_axi_CNTRL_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WDATA" *)
input wire [31 : 0] s_axi_CNTRL_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WSTRB" *)
input wire [3 : 0] s_axi_CNTRL_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WVALID" *)
input wire s_axi_CNTRL_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WREADY" *)
output wire s_axi_CNTRL_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BRESP" *)
output wire [1 : 0] s_axi_CNTRL_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BVALID" *)
output wire s_axi_CNTRL_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BREADY" *)
input wire s_axi_CNTRL_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARADDR" *)
input wire [6 : 0] s_axi_CNTRL_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARVALID" *)
input wire s_axi_CNTRL_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARREADY" *)
output wire s_axi_CNTRL_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RDATA" *)
output wire [31 : 0] s_axi_CNTRL_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RRESP" *)
output wire [1 : 0] s_axi_CNTRL_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RVALID" *)
output wire s_axi_CNTRL_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_CNTRL, ADDR_WIDTH 7, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 100000000, ID\
_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 8, NUM_WRITE_OUTSTANDING 8, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RREADY" *)
input wire s_axi_CNTRL_RREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF src_data_V_V:hard_data:error_data:fe_status_V_V, ASSOCIATED_RESET ap_rst_n, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 3\
00000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *)
input wire ap_clk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *)
input wire ap_rst_n;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {INTERRUPT {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, PortWidth 1" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *)
output wire interrupt;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME cntrl_aclk, ASSOCIATED_BUSIF s_axi_CNTRL, ASSOCIATED_RESET ap_rst_n_cntrl_aclk, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 100000000, FREQ_TOLERA\
NCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 cntrl_aclk CLK" *)
input wire cntrl_aclk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n_cntrl_aclk, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n_cntrl_aclk RST" *)
input wire ap_rst_n_cntrl_aclk;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 src_data_V_V TVALID" *)
input wire src_data_V_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 src_data_V_V TREADY" *)
output wire src_data_V_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME src_data_V_V, TDATA_NUM_BYTES 16, TUSER_WIDTH 0, LAYERED_METADATA undef, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 src_data_V_V TDATA" *)
input wire [127 : 0] src_data_V_V_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TVALID" *)
input wire hard_data_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TREADY" *)
output wire hard_data_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TDATA" *)
input wire [127 : 0] hard_data_TDATA;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME hard_data, TDATA_NUM_BYTES 16, TUSER_WIDTH 0, LAYERED_METADATA undef, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TLAST" *)
input wire [0 : 0] hard_data_TLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 error_data TVALID" *)
input wire error_data_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 error_data TREADY" *)
output wire error_data_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 error_data TDATA" *)
input wire [127 : 0] error_data_TDATA;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME error_data, TDATA_NUM_BYTES 16, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependency\
 {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 128} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} TDATA_WIDTH 128}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK\
_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 error_data TLAST" *)
input wire [0 : 0] error_data_TLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 fe_status_V_V TVALID" *)
input wire fe_status_V_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 fe_status_V_V TREADY" *)
output wire fe_status_V_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME fe_status_V_V, TDATA_NUM_BYTES 5, TUSER_WIDTH 0, LAYERED_METADATA undef, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 fe_status_V_V TDATA" *)
input wire [39 : 0] fe_status_V_V_TDATA;

  stats_top #(
    .C_S_AXI_CNTRL_ADDR_WIDTH(7),
    .C_S_AXI_CNTRL_DATA_WIDTH(32)
  ) inst (
    .s_axi_CNTRL_AWADDR(s_axi_CNTRL_AWADDR),
    .s_axi_CNTRL_AWVALID(s_axi_CNTRL_AWVALID),
    .s_axi_CNTRL_AWREADY(s_axi_CNTRL_AWREADY),
    .s_axi_CNTRL_WDATA(s_axi_CNTRL_WDATA),
    .s_axi_CNTRL_WSTRB(s_axi_CNTRL_WSTRB),
    .s_axi_CNTRL_WVALID(s_axi_CNTRL_WVALID),
    .s_axi_CNTRL_WREADY(s_axi_CNTRL_WREADY),
    .s_axi_CNTRL_BRESP(s_axi_CNTRL_BRESP),
    .s_axi_CNTRL_BVALID(s_axi_CNTRL_BVALID),
    .s_axi_CNTRL_BREADY(s_axi_CNTRL_BREADY),
    .s_axi_CNTRL_ARADDR(s_axi_CNTRL_ARADDR),
    .s_axi_CNTRL_ARVALID(s_axi_CNTRL_ARVALID),
    .s_axi_CNTRL_ARREADY(s_axi_CNTRL_ARREADY),
    .s_axi_CNTRL_RDATA(s_axi_CNTRL_RDATA),
    .s_axi_CNTRL_RRESP(s_axi_CNTRL_RRESP),
    .s_axi_CNTRL_RVALID(s_axi_CNTRL_RVALID),
    .s_axi_CNTRL_RREADY(s_axi_CNTRL_RREADY),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .interrupt(interrupt),
    .cntrl_aclk(cntrl_aclk),
    .ap_rst_n_cntrl_aclk(ap_rst_n_cntrl_aclk),
    .src_data_V_V_TVALID(src_data_V_V_TVALID),
    .src_data_V_V_TREADY(src_data_V_V_TREADY),
    .src_data_V_V_TDATA(src_data_V_V_TDATA),
    .hard_data_TVALID(hard_data_TVALID),
    .hard_data_TREADY(hard_data_TREADY),
    .hard_data_TDATA(hard_data_TDATA),
    .hard_data_TLAST(hard_data_TLAST),
    .error_data_TVALID(error_data_TVALID),
    .error_data_TREADY(error_data_TREADY),
    .error_data_TDATA(error_data_TDATA),
    .error_data_TLAST(error_data_TLAST),
    .fe_status_V_V_TVALID(fe_status_V_V_TVALID),
    .fe_status_V_V_TREADY(fe_status_V_V_TREADY),
    .fe_status_V_V_TDATA(fe_status_V_V_TDATA)
  );
endmodule
