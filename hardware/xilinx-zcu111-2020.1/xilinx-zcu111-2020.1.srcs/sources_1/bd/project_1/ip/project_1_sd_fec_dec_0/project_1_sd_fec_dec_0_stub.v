// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:40 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode synth_stub
//               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_sd_fec_dec_0/project_1_sd_fec_dec_0_stub.v
// Design      : project_1_sd_fec_dec_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "sd_fec_v1_1_5,Vivado 2020.1" *)
module project_1_sd_fec_dec_0(reset_n, core_clk, s_axi_aclk, s_axi_awaddr, 
  s_axi_awvalid, s_axi_awready, s_axi_wdata, s_axi_wvalid, s_axi_wready, s_axi_bready, 
  s_axi_bvalid, s_axi_araddr, s_axi_arvalid, s_axi_arready, s_axi_rready, s_axi_rdata, 
  s_axi_rvalid, interrupt, s_axis_ctrl_aclk, s_axis_ctrl_tready, s_axis_ctrl_tvalid, 
  s_axis_ctrl_tdata, s_axis_din_aclk, s_axis_din_tready, s_axis_din_tvalid, 
  s_axis_din_tlast, s_axis_din_tdata, m_axis_status_aclk, m_axis_status_tready, 
  m_axis_status_tvalid, m_axis_status_tdata, m_axis_dout_aclk, m_axis_dout_tready, 
  m_axis_dout_tvalid, m_axis_dout_tlast, m_axis_dout_tdata)
/* synthesis syn_black_box black_box_pad_pin="reset_n,core_clk,s_axi_aclk,s_axi_awaddr[17:0],s_axi_awvalid,s_axi_awready,s_axi_wdata[31:0],s_axi_wvalid,s_axi_wready,s_axi_bready,s_axi_bvalid,s_axi_araddr[17:0],s_axi_arvalid,s_axi_arready,s_axi_rready,s_axi_rdata[31:0],s_axi_rvalid,interrupt,s_axis_ctrl_aclk,s_axis_ctrl_tready,s_axis_ctrl_tvalid,s_axis_ctrl_tdata[31:0],s_axis_din_aclk,s_axis_din_tready,s_axis_din_tvalid,s_axis_din_tlast,s_axis_din_tdata[255:0],m_axis_status_aclk,m_axis_status_tready,m_axis_status_tvalid,m_axis_status_tdata[31:0],m_axis_dout_aclk,m_axis_dout_tready,m_axis_dout_tvalid,m_axis_dout_tlast,m_axis_dout_tdata[127:0]" */;
  input reset_n;
  input core_clk;
  input s_axi_aclk;
  input [17:0]s_axi_awaddr;
  input s_axi_awvalid;
  output s_axi_awready;
  input [31:0]s_axi_wdata;
  input s_axi_wvalid;
  output s_axi_wready;
  input s_axi_bready;
  output s_axi_bvalid;
  input [17:0]s_axi_araddr;
  input s_axi_arvalid;
  output s_axi_arready;
  input s_axi_rready;
  output [31:0]s_axi_rdata;
  output s_axi_rvalid;
  output interrupt;
  input s_axis_ctrl_aclk;
  output s_axis_ctrl_tready;
  input s_axis_ctrl_tvalid;
  input [31:0]s_axis_ctrl_tdata;
  input s_axis_din_aclk;
  output s_axis_din_tready;
  input s_axis_din_tvalid;
  input s_axis_din_tlast;
  input [255:0]s_axis_din_tdata;
  input m_axis_status_aclk;
  input m_axis_status_tready;
  output m_axis_status_tvalid;
  output [31:0]m_axis_status_tdata;
  input m_axis_dout_aclk;
  input m_axis_dout_tready;
  output m_axis_dout_tvalid;
  output m_axis_dout_tlast;
  output [127:0]m_axis_dout_tdata;
endmodule
