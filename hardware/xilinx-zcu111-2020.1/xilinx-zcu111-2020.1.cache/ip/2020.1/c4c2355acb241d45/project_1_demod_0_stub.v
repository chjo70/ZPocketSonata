// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:27 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_demod_0_stub.v
// Design      : project_1_demod_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "demod_4x,Vivado 2020.1" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(ap_clk, ap_rst_n, ctrl_in_V_TVALID, 
  ctrl_in_V_TREADY, ctrl_in_V_TDATA, chan_data_1_V_TVALID, chan_data_1_V_TREADY, 
  chan_data_1_V_TDATA, chan_data_2_V_TVALID, chan_data_2_V_TREADY, chan_data_2_V_TDATA, 
  chan_data_3_V_TVALID, chan_data_3_V_TREADY, chan_data_3_V_TDATA, chan_data_4_V_TVALID, 
  chan_data_4_V_TREADY, chan_data_4_V_TDATA, soft_data_TVALID, soft_data_TREADY, 
  soft_data_TDATA, soft_data_TLAST, soft_data_TKEEP, hard_data_TVALID, hard_data_TREADY, 
  hard_data_TDATA, hard_data_TLAST)
/* synthesis syn_black_box black_box_pad_pin="ap_clk,ap_rst_n,ctrl_in_V_TVALID,ctrl_in_V_TREADY,ctrl_in_V_TDATA[63:0],chan_data_1_V_TVALID,chan_data_1_V_TREADY,chan_data_1_V_TDATA[39:0],chan_data_2_V_TVALID,chan_data_2_V_TREADY,chan_data_2_V_TDATA[39:0],chan_data_3_V_TVALID,chan_data_3_V_TREADY,chan_data_3_V_TDATA[39:0],chan_data_4_V_TVALID,chan_data_4_V_TREADY,chan_data_4_V_TDATA[39:0],soft_data_TVALID,soft_data_TREADY,soft_data_TDATA[191:0],soft_data_TLAST[0:0],soft_data_TKEEP[23:0],hard_data_TVALID,hard_data_TREADY,hard_data_TDATA[127:0],hard_data_TLAST[0:0]" */;
  input ap_clk;
  input ap_rst_n;
  input ctrl_in_V_TVALID;
  output ctrl_in_V_TREADY;
  input [63:0]ctrl_in_V_TDATA;
  input chan_data_1_V_TVALID;
  output chan_data_1_V_TREADY;
  input [39:0]chan_data_1_V_TDATA;
  input chan_data_2_V_TVALID;
  output chan_data_2_V_TREADY;
  input [39:0]chan_data_2_V_TDATA;
  input chan_data_3_V_TVALID;
  output chan_data_3_V_TREADY;
  input [39:0]chan_data_3_V_TDATA;
  input chan_data_4_V_TVALID;
  output chan_data_4_V_TREADY;
  input [39:0]chan_data_4_V_TDATA;
  output soft_data_TVALID;
  input soft_data_TREADY;
  output [191:0]soft_data_TDATA;
  output [0:0]soft_data_TLAST;
  output [23:0]soft_data_TKEEP;
  output hard_data_TVALID;
  input hard_data_TREADY;
  output [127:0]hard_data_TDATA;
  output [0:0]hard_data_TLAST;
endmodule
