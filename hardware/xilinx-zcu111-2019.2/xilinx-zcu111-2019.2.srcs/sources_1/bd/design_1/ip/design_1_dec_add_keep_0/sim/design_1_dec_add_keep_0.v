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


// IP VLNV: xilinx.com:hls:add_keep_128:1.0
// IP Revision: 1802122325

`timescale 1ns/1ps

(* IP_DEFINITION_SOURCE = "HLS" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module design_1_dec_add_keep_0 (
  ap_clk,
  ap_rst_n,
  ctrl_V_V_TVALID,
  ctrl_V_V_TREADY,
  ctrl_V_V_TDATA,
  din_TVALID,
  din_TREADY,
  din_TDATA,
  din_TLAST,
  dout_TVALID,
  dout_TREADY,
  dout_TDATA,
  dout_TLAST,
  dout_TKEEP
);

(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF ctrl_V_V:din:dout, ASSOCIATED_RESET ap_rst_n, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAI\
N design_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *)
input wire ap_clk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *)
input wire ap_rst_n;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 ctrl_V_V TVALID" *)
input wire ctrl_V_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 ctrl_V_V TREADY" *)
output wire ctrl_V_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ctrl_V_V, TDATA_NUM_BYTES 2, TUSER_WIDTH 0, LAYERED_METADATA undef, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN design_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 ctrl_V_V TDATA" *)
input wire [15 : 0] ctrl_V_V_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 din TVALID" *)
input wire din_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 din TREADY" *)
output wire din_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 din TDATA" *)
input wire [127 : 0] din_TDATA;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME din, TDATA_NUM_BYTES 16, TUSER_WIDTH 0, LAYERED_METADATA undef, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN design_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 din TLAST" *)
input wire [0 : 0] din_TLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 dout TVALID" *)
output wire dout_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 dout TREADY" *)
input wire dout_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 dout TDATA" *)
output wire [127 : 0] dout_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 dout TLAST" *)
output wire [0 : 0] dout_TLAST;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME dout, TDATA_NUM_BYTES 16, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependency {} fo\
rmat string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 128} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} TDATA_WIDTH 128}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 1, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAI\
N design_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 dout TKEEP" *)
output wire [15 : 0] dout_TKEEP;

  add_keep_128 inst (
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .ctrl_V_V_TVALID(ctrl_V_V_TVALID),
    .ctrl_V_V_TREADY(ctrl_V_V_TREADY),
    .ctrl_V_V_TDATA(ctrl_V_V_TDATA),
    .din_TVALID(din_TVALID),
    .din_TREADY(din_TREADY),
    .din_TDATA(din_TDATA),
    .din_TLAST(din_TLAST),
    .dout_TVALID(dout_TVALID),
    .dout_TREADY(dout_TREADY),
    .dout_TDATA(dout_TDATA),
    .dout_TLAST(dout_TLAST),
    .dout_TKEEP(dout_TKEEP)
  );
endmodule
