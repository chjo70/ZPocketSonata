// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:49:01 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode synth_stub
//               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_stats_0/project_1_stats_0_stub.v
// Design      : project_1_stats_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "stats_top,Vivado 2020.1" *)
module project_1_stats_0(s_axi_CNTRL_AWADDR, s_axi_CNTRL_AWVALID, 
  s_axi_CNTRL_AWREADY, s_axi_CNTRL_WDATA, s_axi_CNTRL_WSTRB, s_axi_CNTRL_WVALID, 
  s_axi_CNTRL_WREADY, s_axi_CNTRL_BRESP, s_axi_CNTRL_BVALID, s_axi_CNTRL_BREADY, 
  s_axi_CNTRL_ARADDR, s_axi_CNTRL_ARVALID, s_axi_CNTRL_ARREADY, s_axi_CNTRL_RDATA, 
  s_axi_CNTRL_RRESP, s_axi_CNTRL_RVALID, s_axi_CNTRL_RREADY, ap_clk, ap_rst_n, interrupt, 
  cntrl_aclk, ap_rst_n_cntrl_aclk, src_data_V_V_TVALID, src_data_V_V_TREADY, 
  src_data_V_V_TDATA, hard_data_TVALID, hard_data_TREADY, hard_data_TDATA, hard_data_TLAST, 
  error_data_TVALID, error_data_TREADY, error_data_TDATA, error_data_TLAST, 
  fe_status_V_V_TVALID, fe_status_V_V_TREADY, fe_status_V_V_TDATA)
/* synthesis syn_black_box black_box_pad_pin="s_axi_CNTRL_AWADDR[6:0],s_axi_CNTRL_AWVALID,s_axi_CNTRL_AWREADY,s_axi_CNTRL_WDATA[31:0],s_axi_CNTRL_WSTRB[3:0],s_axi_CNTRL_WVALID,s_axi_CNTRL_WREADY,s_axi_CNTRL_BRESP[1:0],s_axi_CNTRL_BVALID,s_axi_CNTRL_BREADY,s_axi_CNTRL_ARADDR[6:0],s_axi_CNTRL_ARVALID,s_axi_CNTRL_ARREADY,s_axi_CNTRL_RDATA[31:0],s_axi_CNTRL_RRESP[1:0],s_axi_CNTRL_RVALID,s_axi_CNTRL_RREADY,ap_clk,ap_rst_n,interrupt,cntrl_aclk,ap_rst_n_cntrl_aclk,src_data_V_V_TVALID,src_data_V_V_TREADY,src_data_V_V_TDATA[127:0],hard_data_TVALID,hard_data_TREADY,hard_data_TDATA[127:0],hard_data_TLAST[0:0],error_data_TVALID,error_data_TREADY,error_data_TDATA[127:0],error_data_TLAST[0:0],fe_status_V_V_TVALID,fe_status_V_V_TREADY,fe_status_V_V_TDATA[39:0]" */;
  input [6:0]s_axi_CNTRL_AWADDR;
  input s_axi_CNTRL_AWVALID;
  output s_axi_CNTRL_AWREADY;
  input [31:0]s_axi_CNTRL_WDATA;
  input [3:0]s_axi_CNTRL_WSTRB;
  input s_axi_CNTRL_WVALID;
  output s_axi_CNTRL_WREADY;
  output [1:0]s_axi_CNTRL_BRESP;
  output s_axi_CNTRL_BVALID;
  input s_axi_CNTRL_BREADY;
  input [6:0]s_axi_CNTRL_ARADDR;
  input s_axi_CNTRL_ARVALID;
  output s_axi_CNTRL_ARREADY;
  output [31:0]s_axi_CNTRL_RDATA;
  output [1:0]s_axi_CNTRL_RRESP;
  output s_axi_CNTRL_RVALID;
  input s_axi_CNTRL_RREADY;
  input ap_clk;
  input ap_rst_n;
  output interrupt;
  input cntrl_aclk;
  input ap_rst_n_cntrl_aclk;
  input src_data_V_V_TVALID;
  output src_data_V_V_TREADY;
  input [127:0]src_data_V_V_TDATA;
  input hard_data_TVALID;
  output hard_data_TREADY;
  input [127:0]hard_data_TDATA;
  input [0:0]hard_data_TLAST;
  input error_data_TVALID;
  output error_data_TREADY;
  input [127:0]error_data_TDATA;
  input [0:0]error_data_TLAST;
  input fe_status_V_V_TVALID;
  output fe_status_V_V_TREADY;
  input [39:0]fe_status_V_V_TDATA;
endmodule
