// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:46:43 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_data_source_0_stub.v
// Design      : project_1_data_source_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "data_source_top,Vivado 2020.1" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(s_axi_CNTRL_AWADDR, s_axi_CNTRL_AWVALID, 
  s_axi_CNTRL_AWREADY, s_axi_CNTRL_WDATA, s_axi_CNTRL_WSTRB, s_axi_CNTRL_WVALID, 
  s_axi_CNTRL_WREADY, s_axi_CNTRL_BRESP, s_axi_CNTRL_BVALID, s_axi_CNTRL_BREADY, 
  s_axi_CNTRL_ARADDR, s_axi_CNTRL_ARVALID, s_axi_CNTRL_ARREADY, s_axi_CNTRL_RDATA, 
  s_axi_CNTRL_RRESP, s_axi_CNTRL_RVALID, s_axi_CNTRL_RREADY, ap_clk, ap_rst_n, interrupt, 
  cntrl_aclk, ap_rst_n_cntrl_aclk, chan_ctrl_out_V_TVALID, chan_ctrl_out_V_TREADY, 
  chan_ctrl_out_V_TDATA, enc_ctrl_out_TVALID, enc_ctrl_out_TREADY, enc_ctrl_out_TDATA, 
  enc_ctrl_out_TLAST, enc_keep_ctrl_V_V_TVALID, enc_keep_ctrl_V_V_TREADY, 
  enc_keep_ctrl_V_V_TDATA, dec_keep_ctrl_V_V_TVALID, dec_keep_ctrl_V_V_TREADY, 
  dec_keep_ctrl_V_V_TDATA, dec_ctrl_out_TVALID, dec_ctrl_out_TREADY, dec_ctrl_out_TDATA, 
  dec_ctrl_out_TLAST, hard_data_out_TVALID, hard_data_out_TREADY, hard_data_out_TDATA, 
  hard_data_out_TLAST, hard_data_out_TKEEP)
/* synthesis syn_black_box black_box_pad_pin="s_axi_CNTRL_AWADDR[7:0],s_axi_CNTRL_AWVALID,s_axi_CNTRL_AWREADY,s_axi_CNTRL_WDATA[31:0],s_axi_CNTRL_WSTRB[3:0],s_axi_CNTRL_WVALID,s_axi_CNTRL_WREADY,s_axi_CNTRL_BRESP[1:0],s_axi_CNTRL_BVALID,s_axi_CNTRL_BREADY,s_axi_CNTRL_ARADDR[7:0],s_axi_CNTRL_ARVALID,s_axi_CNTRL_ARREADY,s_axi_CNTRL_RDATA[31:0],s_axi_CNTRL_RRESP[1:0],s_axi_CNTRL_RVALID,s_axi_CNTRL_RREADY,ap_clk,ap_rst_n,interrupt,cntrl_aclk,ap_rst_n_cntrl_aclk,chan_ctrl_out_V_TVALID,chan_ctrl_out_V_TREADY,chan_ctrl_out_V_TDATA[63:0],enc_ctrl_out_TVALID,enc_ctrl_out_TREADY,enc_ctrl_out_TDATA[39:0],enc_ctrl_out_TLAST[0:0],enc_keep_ctrl_V_V_TVALID,enc_keep_ctrl_V_V_TREADY,enc_keep_ctrl_V_V_TDATA[63:0],dec_keep_ctrl_V_V_TVALID,dec_keep_ctrl_V_V_TREADY,dec_keep_ctrl_V_V_TDATA[63:0],dec_ctrl_out_TVALID,dec_ctrl_out_TREADY,dec_ctrl_out_TDATA[39:0],dec_ctrl_out_TLAST[0:0],hard_data_out_TVALID,hard_data_out_TREADY,hard_data_out_TDATA[127:0],hard_data_out_TLAST[0:0],hard_data_out_TKEEP[15:0]" */;
  input [7:0]s_axi_CNTRL_AWADDR;
  input s_axi_CNTRL_AWVALID;
  output s_axi_CNTRL_AWREADY;
  input [31:0]s_axi_CNTRL_WDATA;
  input [3:0]s_axi_CNTRL_WSTRB;
  input s_axi_CNTRL_WVALID;
  output s_axi_CNTRL_WREADY;
  output [1:0]s_axi_CNTRL_BRESP;
  output s_axi_CNTRL_BVALID;
  input s_axi_CNTRL_BREADY;
  input [7:0]s_axi_CNTRL_ARADDR;
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
  output chan_ctrl_out_V_TVALID;
  input chan_ctrl_out_V_TREADY;
  output [63:0]chan_ctrl_out_V_TDATA;
  output enc_ctrl_out_TVALID;
  input enc_ctrl_out_TREADY;
  output [39:0]enc_ctrl_out_TDATA;
  output [0:0]enc_ctrl_out_TLAST;
  output enc_keep_ctrl_V_V_TVALID;
  input enc_keep_ctrl_V_V_TREADY;
  output [63:0]enc_keep_ctrl_V_V_TDATA;
  output dec_keep_ctrl_V_V_TVALID;
  input dec_keep_ctrl_V_V_TREADY;
  output [63:0]dec_keep_ctrl_V_V_TDATA;
  output dec_ctrl_out_TVALID;
  input dec_ctrl_out_TREADY;
  output [39:0]dec_ctrl_out_TDATA;
  output [0:0]dec_ctrl_out_TLAST;
  output hard_data_out_TVALID;
  input hard_data_out_TREADY;
  output [127:0]hard_data_out_TDATA;
  output [0:0]hard_data_out_TLAST;
  output [15:0]hard_data_out_TKEEP;
endmodule
