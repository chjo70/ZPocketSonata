// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:46:20 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode synth_stub -rename_top project_1_enc_op_probe_0 -prefix
//               project_1_enc_op_probe_0_ project_1_dec_ip_probe_0_stub.v
// Design      : project_1_dec_ip_probe_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "axis_probe,Vivado 2020.1" *)
module project_1_enc_op_probe_0(clk, mon_tvalid, mon_tready, mon_tlast, valid_op, 
  ready_op, last_op)
/* synthesis syn_black_box black_box_pad_pin="clk,mon_tvalid,mon_tready,mon_tlast,valid_op,ready_op,last_op" */;
  input clk;
  input mon_tvalid;
  input mon_tready;
  input mon_tlast;
  output valid_op;
  output ready_op;
  output last_op;
endmodule
