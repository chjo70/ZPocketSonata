// (c) Copyright 1995-2019 Xilinx, Inc. All rights reserved.
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


// IP VLNV: xilinx.com:module_ref:exdes_rfdac_src:1.0
// IP Revision: 1

`timescale 1ns/1ps

(* IP_DEFINITION_SOURCE = "module_ref" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module design_1_dac_source_i_0 (
  s_axi_awaddr,
  s_axi_awvalid,
  s_axi_awready,
  s_axi_wdata,
  s_axi_wvalid,
  s_axi_wready,
  s_axi_wstrb,
  s_axi_bresp,
  s_axi_bvalid,
  s_axi_bready,
  s_axi_araddr,
  s_axi_arvalid,
  s_axi_arready,
  s_axi_rdata,
  s_axi_rresp,
  s_axi_rvalid,
  s_axi_rready,
  m00_tdata,
  m00_tvalid,
  m00_tready,
  m0_axis_clock,
  s_axi_aclk,
  s_axi_aresetn
);

(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWADDR" *)
input wire [17 : 0] s_axi_awaddr;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWVALID" *)
input wire s_axi_awvalid;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWREADY" *)
output wire s_axi_awready;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WDATA" *)
input wire [31 : 0] s_axi_wdata;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WVALID" *)
input wire s_axi_wvalid;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WREADY" *)
output wire s_axi_wready;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WSTRB" *)
input wire [3 : 0] s_axi_wstrb;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BRESP" *)
output wire [1 : 0] s_axi_bresp;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BVALID" *)
output wire s_axi_bvalid;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BREADY" *)
input wire s_axi_bready;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARADDR" *)
input wire [17 : 0] s_axi_araddr;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARVALID" *)
input wire s_axi_arvalid;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARREADY" *)
output wire s_axi_arready;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RDATA" *)
output wire [31 : 0] s_axi_rdata;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RRESP" *)
output wire [1 : 0] s_axi_rresp;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RVALID" *)
output wire s_axi_rvalid;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 99999001, ID_WIDTH 0, ADDR_WIDTH 18, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN design_1_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, N\
UM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RREADY" *)
input wire s_axi_rready;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m00 TDATA" *)
output wire [255 : 0] m00_tdata;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m00 TVALID" *)
output wire m00_tvalid;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m00, TDATA_NUM_BYTES 32, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 100000000, PHASE 0.0, CLK_DOMAIN design_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m00 TREADY" *)
input wire m00_tready;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m0_axis_clock, ASSOCIATED_BUSIF m00, FREQ_HZ 100000000, PHASE 0.0, CLK_DOMAIN design_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 m0_axis_clock CLK" *)
input wire m0_axis_clock;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_aclk, ASSOCIATED_BUSIF s_axi, ASSOCIATED_RESET s_axi_aresetn, FREQ_HZ 99999001, PHASE 0.000, CLK_DOMAIN design_1_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s_axi_aclk CLK" *)
input wire s_axi_aclk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_aresetn, POLARITY ACTIVE_LOW, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 s_axi_aresetn RST" *)
input wire s_axi_aresetn;

  exdes_rfdac_src #(
    .enable_override(1'B1),
    .default_signal_type(4'B0100),
    .initial_interword_offset(1)
  ) inst (
    .s_axi_awaddr(s_axi_awaddr),
    .s_axi_awvalid(s_axi_awvalid),
    .s_axi_awready(s_axi_awready),
    .s_axi_wdata(s_axi_wdata),
    .s_axi_wvalid(s_axi_wvalid),
    .s_axi_wready(s_axi_wready),
    .s_axi_wstrb(s_axi_wstrb),
    .s_axi_bresp(s_axi_bresp),
    .s_axi_bvalid(s_axi_bvalid),
    .s_axi_bready(s_axi_bready),
    .s_axi_araddr(s_axi_araddr),
    .s_axi_arvalid(s_axi_arvalid),
    .s_axi_arready(s_axi_arready),
    .s_axi_rdata(s_axi_rdata),
    .s_axi_rresp(s_axi_rresp),
    .s_axi_rvalid(s_axi_rvalid),
    .s_axi_rready(s_axi_rready),
    .m00_tdata(m00_tdata),
    .m00_tvalid(m00_tvalid),
    .m00_tready(m00_tready),
    .m0_axis_clock(m0_axis_clock),
    .s_axi_aclk(s_axi_aclk),
    .s_axi_aresetn(s_axi_aresetn)
  );
endmodule
