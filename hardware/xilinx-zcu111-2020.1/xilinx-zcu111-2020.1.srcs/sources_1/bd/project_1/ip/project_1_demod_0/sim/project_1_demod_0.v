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


// IP VLNV: xilinx.com:hls:demod_4x:1.0
// IP Revision: 1802122229

`timescale 1ns/1ps

(* IP_DEFINITION_SOURCE = "HLS" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module project_1_demod_0 (
  ap_clk,
  ap_rst_n,
  ctrl_in_V_TVALID,
  ctrl_in_V_TREADY,
  ctrl_in_V_TDATA,
  chan_data_1_V_TVALID,
  chan_data_1_V_TREADY,
  chan_data_1_V_TDATA,
  chan_data_2_V_TVALID,
  chan_data_2_V_TREADY,
  chan_data_2_V_TDATA,
  chan_data_3_V_TVALID,
  chan_data_3_V_TREADY,
  chan_data_3_V_TDATA,
  chan_data_4_V_TVALID,
  chan_data_4_V_TREADY,
  chan_data_4_V_TDATA,
  soft_data_TVALID,
  soft_data_TREADY,
  soft_data_TDATA,
  soft_data_TLAST,
  soft_data_TKEEP,
  hard_data_TVALID,
  hard_data_TREADY,
  hard_data_TDATA,
  hard_data_TLAST
);

(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF ctrl_in_V:chan_data_1_V:chan_data_2_V:chan_data_3_V:chan_data_4_V:soft_data:hard_data, ASSOCIATED_RESET ap_rst_n, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum\
 {} maximum {}} value 0}}}}, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *)
input wire ap_clk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *)
input wire ap_rst_n;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 ctrl_in_V TVALID" *)
input wire ctrl_in_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 ctrl_in_V TREADY" *)
output wire ctrl_in_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ctrl_in_V, TDATA_NUM_BYTES 8, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependency {\
} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 58} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} struct {field_fec_type {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value fec_type} enabled {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true} datatype {name {at\
tribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} field_mod_type {name {attribs {resolve_type immediate dependency {} format string minimum {} m\
aximum {}} value mod_type} enabled {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 3} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} integer {signed {attribs {resolve_type immediate dependency {\
} format bool minimum {} maximum {}} value false}}}} field_skip_chan {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value skip_chan} enabled {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {at\
tribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 4} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} field_snr {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value snr} enabled {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {\
} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 17} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 5} real {fixed {fractwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 11} signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}}}} field_inv_sigma_sq {name {attribs {resolve_type immed\
iate dependency {} format string minimum {} maximum {}} value inv_sigma_sq} enabled {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 17} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 22} real {fixe\
d {fractwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 10} signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}} field_block_symbls {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value block_symbls} enabled {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true} datatype {name {attribs {resolve_type immediate dependenc\
y {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 14} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 39} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} field_block_rem {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value block_rem} enabled \
{attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 5} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 53} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {\
}} value false}}}}}}} TDATA_WIDTH 64}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 ctrl_in_V TDATA" *)
input wire [63 : 0] ctrl_in_V_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_1_V TVALID" *)
input wire chan_data_1_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_1_V TREADY" *)
output wire chan_data_1_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME chan_data_1_V, TDATA_NUM_BYTES 5, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependen\
cy {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 38} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} complex {bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} stride {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} real {fixed {fractwidth {attribs {re\
solve_type immediate dependency {} format long minimum {} maximum {}} value 14} signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}} realfirst {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}}} TDATA_WIDTH 40}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_1_V TDATA" *)
input wire [39 : 0] chan_data_1_V_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_2_V TVALID" *)
input wire chan_data_2_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_2_V TREADY" *)
output wire chan_data_2_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME chan_data_2_V, TDATA_NUM_BYTES 5, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependen\
cy {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 38} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} complex {bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} stride {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} real {fixed {fractwidth {attribs {re\
solve_type immediate dependency {} format long minimum {} maximum {}} value 14} signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}} realfirst {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}}} TDATA_WIDTH 40}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_2_V TDATA" *)
input wire [39 : 0] chan_data_2_V_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_3_V TVALID" *)
input wire chan_data_3_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_3_V TREADY" *)
output wire chan_data_3_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME chan_data_3_V, TDATA_NUM_BYTES 5, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependen\
cy {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 38} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} complex {bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} stride {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} real {fixed {fractwidth {attribs {re\
solve_type immediate dependency {} format long minimum {} maximum {}} value 14} signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}} realfirst {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}}} TDATA_WIDTH 40}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_3_V TDATA" *)
input wire [39 : 0] chan_data_3_V_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_4_V TVALID" *)
input wire chan_data_4_V_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_4_V TREADY" *)
output wire chan_data_4_V_TREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME chan_data_4_V, TDATA_NUM_BYTES 5, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependen\
cy {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 38} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} complex {bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} stride {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 19} real {fixed {fractwidth {attribs {re\
solve_type immediate dependency {} format long minimum {} maximum {}} value 14} signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}} realfirst {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}}} TDATA_WIDTH 40}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 chan_data_4_V TDATA" *)
input wire [39 : 0] chan_data_4_V_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 soft_data TVALID" *)
output wire soft_data_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 soft_data TREADY" *)
input wire soft_data_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 soft_data TDATA" *)
output wire [191 : 0] soft_data_TDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 soft_data TLAST" *)
output wire [0 : 0] soft_data_TLAST;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME soft_data, TDATA_NUM_BYTES 24, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependency \
{} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 192} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} TDATA_WIDTH 192}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 1, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_\
DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 soft_data TKEEP" *)
output wire [23 : 0] soft_data_TKEEP;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TVALID" *)
output wire hard_data_TVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TREADY" *)
input wire hard_data_TREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TDATA" *)
output wire [127 : 0] hard_data_TDATA;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME hard_data, TDATA_NUM_BYTES 16, TUSER_WIDTH 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA {datatype {name {attribs {resolve_type immediate dependency \
{} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 128} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} TDATA_WIDTH 128}, TDEST_WIDTH 0, TID_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_\
DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 hard_data TLAST" *)
output wire [0 : 0] hard_data_TLAST;

  demod_4x inst (
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .ctrl_in_V_TVALID(ctrl_in_V_TVALID),
    .ctrl_in_V_TREADY(ctrl_in_V_TREADY),
    .ctrl_in_V_TDATA(ctrl_in_V_TDATA),
    .chan_data_1_V_TVALID(chan_data_1_V_TVALID),
    .chan_data_1_V_TREADY(chan_data_1_V_TREADY),
    .chan_data_1_V_TDATA(chan_data_1_V_TDATA),
    .chan_data_2_V_TVALID(chan_data_2_V_TVALID),
    .chan_data_2_V_TREADY(chan_data_2_V_TREADY),
    .chan_data_2_V_TDATA(chan_data_2_V_TDATA),
    .chan_data_3_V_TVALID(chan_data_3_V_TVALID),
    .chan_data_3_V_TREADY(chan_data_3_V_TREADY),
    .chan_data_3_V_TDATA(chan_data_3_V_TDATA),
    .chan_data_4_V_TVALID(chan_data_4_V_TVALID),
    .chan_data_4_V_TREADY(chan_data_4_V_TREADY),
    .chan_data_4_V_TDATA(chan_data_4_V_TDATA),
    .soft_data_TVALID(soft_data_TVALID),
    .soft_data_TREADY(soft_data_TREADY),
    .soft_data_TDATA(soft_data_TDATA),
    .soft_data_TLAST(soft_data_TLAST),
    .soft_data_TKEEP(soft_data_TKEEP),
    .hard_data_TVALID(hard_data_TVALID),
    .hard_data_TREADY(hard_data_TREADY),
    .hard_data_TDATA(hard_data_TDATA),
    .hard_data_TLAST(hard_data_TLAST)
  );
endmodule
