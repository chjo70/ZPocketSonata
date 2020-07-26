// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:46:26 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_dec_ip_mon_0_sim_netlist.v
// Design      : project_1_dec_ip_mon_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* C_S_AXI_CNTRL_ADDR_WIDTH = "6" *) (* C_S_AXI_CNTRL_DATA_WIDTH = "32" *) (* C_S_AXI_CNTRL_WSTRB_WIDTH = "4" *) 
(* C_S_AXI_DATA_WIDTH = "32" *) (* C_S_AXI_WSTRB_WIDTH = "4" *) (* ap_ST_fsm_state1 = "3'b001" *) 
(* ap_ST_fsm_state2 = "3'b010" *) (* ap_ST_fsm_state3 = "3'b100" *) (* hls_module = "yes" *) 
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_monitor
   (ap_clk,
    ap_rst_n,
    rtc_V,
    tvalid_V,
    tready_V,
    tlast_V,
    s_axi_CNTRL_AWVALID,
    s_axi_CNTRL_AWREADY,
    s_axi_CNTRL_AWADDR,
    s_axi_CNTRL_WVALID,
    s_axi_CNTRL_WREADY,
    s_axi_CNTRL_WDATA,
    s_axi_CNTRL_WSTRB,
    s_axi_CNTRL_ARVALID,
    s_axi_CNTRL_ARREADY,
    s_axi_CNTRL_ARADDR,
    s_axi_CNTRL_RVALID,
    s_axi_CNTRL_RREADY,
    s_axi_CNTRL_RDATA,
    s_axi_CNTRL_RRESP,
    s_axi_CNTRL_BVALID,
    s_axi_CNTRL_BREADY,
    s_axi_CNTRL_BRESP,
    interrupt,
    cntrl_aclk,
    ap_rst_n_cntrl_aclk);
  input ap_clk;
  input ap_rst_n;
  input [31:0]rtc_V;
  input [0:0]tvalid_V;
  input [0:0]tready_V;
  input [0:0]tlast_V;
  input s_axi_CNTRL_AWVALID;
  output s_axi_CNTRL_AWREADY;
  input [5:0]s_axi_CNTRL_AWADDR;
  input s_axi_CNTRL_WVALID;
  output s_axi_CNTRL_WREADY;
  input [31:0]s_axi_CNTRL_WDATA;
  input [3:0]s_axi_CNTRL_WSTRB;
  input s_axi_CNTRL_ARVALID;
  output s_axi_CNTRL_ARREADY;
  input [5:0]s_axi_CNTRL_ARADDR;
  output s_axi_CNTRL_RVALID;
  input s_axi_CNTRL_RREADY;
  output [31:0]s_axi_CNTRL_RDATA;
  output [1:0]s_axi_CNTRL_RRESP;
  output s_axi_CNTRL_BVALID;
  input s_axi_CNTRL_BREADY;
  output [1:0]s_axi_CNTRL_BRESP;
  output interrupt;
  input cntrl_aclk;
  input ap_rst_n_cntrl_aclk;

  wire \<const0> ;
  wire \ap_CS_fsm[2]_i_10_n_0 ;
  wire \ap_CS_fsm[2]_i_11_n_0 ;
  wire \ap_CS_fsm[2]_i_12_n_0 ;
  wire \ap_CS_fsm[2]_i_13_n_0 ;
  wire \ap_CS_fsm[2]_i_14_n_0 ;
  wire \ap_CS_fsm[2]_i_4_n_0 ;
  wire \ap_CS_fsm[2]_i_5_n_0 ;
  wire \ap_CS_fsm[2]_i_6_n_0 ;
  wire \ap_CS_fsm[2]_i_7_n_0 ;
  wire \ap_CS_fsm[2]_i_8_n_0 ;
  wire \ap_CS_fsm[2]_i_9_n_0 ;
  wire \ap_CS_fsm_reg[2]_i_2_n_5 ;
  wire \ap_CS_fsm_reg[2]_i_2_n_6 ;
  wire \ap_CS_fsm_reg[2]_i_2_n_7 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_0 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_1 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_2 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_3 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_4 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_5 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_6 ;
  wire \ap_CS_fsm_reg[2]_i_3_n_7 ;
  wire \ap_CS_fsm_reg_n_0_[0] ;
  wire ap_CS_fsm_state2;
  wire ap_CS_fsm_state3;
  wire [2:0]ap_NS_fsm;
  wire ap_NS_fsm11_out;
  wire ap_clk;
  wire ap_rst_n;
  wire ap_rst_n_cntrl_aclk;
  wire ap_rst_n_inv;
  wire cntrl_aclk;
  wire [31:0]first_V_preg;
  wire first_V_preg1;
  wire interrupt;
  wire monitor_CNTRL_s_axi_U_n_11;
  wire monitor_CNTRL_s_axi_U_n_6;
  wire [31:0]num_blocks_V;
  wire [31:0]num_blocks_V_read_reg_237;
  wire p_s_fu_60;
  wire [31:0]rtc_V;
  wire [5:0]s_axi_CNTRL_ARADDR;
  wire s_axi_CNTRL_ARREADY;
  wire s_axi_CNTRL_ARVALID;
  wire [5:0]s_axi_CNTRL_AWADDR;
  wire s_axi_CNTRL_AWREADY;
  wire s_axi_CNTRL_AWVALID;
  wire s_axi_CNTRL_BREADY;
  wire s_axi_CNTRL_BVALID;
  wire [31:0]s_axi_CNTRL_RDATA;
  wire s_axi_CNTRL_RREADY;
  wire s_axi_CNTRL_RVALID;
  wire [31:0]s_axi_CNTRL_WDATA;
  wire s_axi_CNTRL_WREADY;
  wire [3:0]s_axi_CNTRL_WSTRB;
  wire s_axi_CNTRL_WVALID;
  wire t_V_1_fu_68;
  wire t_V_1_fu_680;
  wire \t_V_1_fu_68[0]_i_3_n_0 ;
  wire [31:0]t_V_1_fu_68_reg;
  wire \t_V_1_fu_68_reg[0]_i_2_n_0 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_1 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_10 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_11 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_12 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_13 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_14 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_15 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_2 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_3 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_4 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_5 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_6 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_7 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_8 ;
  wire \t_V_1_fu_68_reg[0]_i_2_n_9 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_0 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_1 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_10 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_11 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_12 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_13 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_14 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_15 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_2 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_3 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_4 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_5 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_6 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_7 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_8 ;
  wire \t_V_1_fu_68_reg[16]_i_1_n_9 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_1 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_10 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_11 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_12 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_13 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_14 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_15 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_2 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_3 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_4 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_5 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_6 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_7 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_8 ;
  wire \t_V_1_fu_68_reg[24]_i_1_n_9 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_0 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_1 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_10 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_11 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_12 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_13 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_14 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_15 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_2 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_3 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_4 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_5 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_6 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_7 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_8 ;
  wire \t_V_1_fu_68_reg[8]_i_1_n_9 ;
  wire t_V_reg_124;
  wire \t_V_reg_124[0]_i_4_n_0 ;
  wire [31:0]t_V_reg_124_reg;
  wire \t_V_reg_124_reg[0]_i_3_n_0 ;
  wire \t_V_reg_124_reg[0]_i_3_n_1 ;
  wire \t_V_reg_124_reg[0]_i_3_n_10 ;
  wire \t_V_reg_124_reg[0]_i_3_n_11 ;
  wire \t_V_reg_124_reg[0]_i_3_n_12 ;
  wire \t_V_reg_124_reg[0]_i_3_n_13 ;
  wire \t_V_reg_124_reg[0]_i_3_n_14 ;
  wire \t_V_reg_124_reg[0]_i_3_n_15 ;
  wire \t_V_reg_124_reg[0]_i_3_n_2 ;
  wire \t_V_reg_124_reg[0]_i_3_n_3 ;
  wire \t_V_reg_124_reg[0]_i_3_n_4 ;
  wire \t_V_reg_124_reg[0]_i_3_n_5 ;
  wire \t_V_reg_124_reg[0]_i_3_n_6 ;
  wire \t_V_reg_124_reg[0]_i_3_n_7 ;
  wire \t_V_reg_124_reg[0]_i_3_n_8 ;
  wire \t_V_reg_124_reg[0]_i_3_n_9 ;
  wire \t_V_reg_124_reg[16]_i_1_n_0 ;
  wire \t_V_reg_124_reg[16]_i_1_n_1 ;
  wire \t_V_reg_124_reg[16]_i_1_n_10 ;
  wire \t_V_reg_124_reg[16]_i_1_n_11 ;
  wire \t_V_reg_124_reg[16]_i_1_n_12 ;
  wire \t_V_reg_124_reg[16]_i_1_n_13 ;
  wire \t_V_reg_124_reg[16]_i_1_n_14 ;
  wire \t_V_reg_124_reg[16]_i_1_n_15 ;
  wire \t_V_reg_124_reg[16]_i_1_n_2 ;
  wire \t_V_reg_124_reg[16]_i_1_n_3 ;
  wire \t_V_reg_124_reg[16]_i_1_n_4 ;
  wire \t_V_reg_124_reg[16]_i_1_n_5 ;
  wire \t_V_reg_124_reg[16]_i_1_n_6 ;
  wire \t_V_reg_124_reg[16]_i_1_n_7 ;
  wire \t_V_reg_124_reg[16]_i_1_n_8 ;
  wire \t_V_reg_124_reg[16]_i_1_n_9 ;
  wire \t_V_reg_124_reg[24]_i_1_n_1 ;
  wire \t_V_reg_124_reg[24]_i_1_n_10 ;
  wire \t_V_reg_124_reg[24]_i_1_n_11 ;
  wire \t_V_reg_124_reg[24]_i_1_n_12 ;
  wire \t_V_reg_124_reg[24]_i_1_n_13 ;
  wire \t_V_reg_124_reg[24]_i_1_n_14 ;
  wire \t_V_reg_124_reg[24]_i_1_n_15 ;
  wire \t_V_reg_124_reg[24]_i_1_n_2 ;
  wire \t_V_reg_124_reg[24]_i_1_n_3 ;
  wire \t_V_reg_124_reg[24]_i_1_n_4 ;
  wire \t_V_reg_124_reg[24]_i_1_n_5 ;
  wire \t_V_reg_124_reg[24]_i_1_n_6 ;
  wire \t_V_reg_124_reg[24]_i_1_n_7 ;
  wire \t_V_reg_124_reg[24]_i_1_n_8 ;
  wire \t_V_reg_124_reg[24]_i_1_n_9 ;
  wire \t_V_reg_124_reg[8]_i_1_n_0 ;
  wire \t_V_reg_124_reg[8]_i_1_n_1 ;
  wire \t_V_reg_124_reg[8]_i_1_n_10 ;
  wire \t_V_reg_124_reg[8]_i_1_n_11 ;
  wire \t_V_reg_124_reg[8]_i_1_n_12 ;
  wire \t_V_reg_124_reg[8]_i_1_n_13 ;
  wire \t_V_reg_124_reg[8]_i_1_n_14 ;
  wire \t_V_reg_124_reg[8]_i_1_n_15 ;
  wire \t_V_reg_124_reg[8]_i_1_n_2 ;
  wire \t_V_reg_124_reg[8]_i_1_n_3 ;
  wire \t_V_reg_124_reg[8]_i_1_n_4 ;
  wire \t_V_reg_124_reg[8]_i_1_n_5 ;
  wire \t_V_reg_124_reg[8]_i_1_n_6 ;
  wire \t_V_reg_124_reg[8]_i_1_n_7 ;
  wire \t_V_reg_124_reg[8]_i_1_n_8 ;
  wire \t_V_reg_124_reg[8]_i_1_n_9 ;
  wire [31:0]time_stamp_V_1_fu_64;
  wire [0:0]tlast_V;
  wire [0:0]tready_V;
  wire [0:0]tvalid_V;
  wire [7:3]\NLW_ap_CS_fsm_reg[2]_i_2_CO_UNCONNECTED ;
  wire [7:0]\NLW_ap_CS_fsm_reg[2]_i_2_O_UNCONNECTED ;
  wire [7:0]\NLW_ap_CS_fsm_reg[2]_i_3_O_UNCONNECTED ;
  wire [7:7]\NLW_t_V_1_fu_68_reg[24]_i_1_CO_UNCONNECTED ;
  wire [7:7]\NLW_t_V_reg_124_reg[24]_i_1_CO_UNCONNECTED ;

  assign s_axi_CNTRL_BRESP[1] = \<const0> ;
  assign s_axi_CNTRL_BRESP[0] = \<const0> ;
  assign s_axi_CNTRL_RRESP[1] = \<const0> ;
  assign s_axi_CNTRL_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  LUT2 #(
    .INIT(4'h8)) 
    \ap_CS_fsm[2]_i_1 
       (.I0(\ap_CS_fsm_reg[2]_i_2_n_5 ),
        .I1(ap_CS_fsm_state2),
        .O(ap_NS_fsm[2]));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_10 
       (.I0(t_V_1_fu_68_reg[12]),
        .I1(num_blocks_V_read_reg_237[12]),
        .I2(num_blocks_V_read_reg_237[14]),
        .I3(t_V_1_fu_68_reg[14]),
        .I4(num_blocks_V_read_reg_237[13]),
        .I5(t_V_1_fu_68_reg[13]),
        .O(\ap_CS_fsm[2]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_11 
       (.I0(t_V_1_fu_68_reg[9]),
        .I1(num_blocks_V_read_reg_237[9]),
        .I2(num_blocks_V_read_reg_237[11]),
        .I3(t_V_1_fu_68_reg[11]),
        .I4(num_blocks_V_read_reg_237[10]),
        .I5(t_V_1_fu_68_reg[10]),
        .O(\ap_CS_fsm[2]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_12 
       (.I0(t_V_1_fu_68_reg[6]),
        .I1(num_blocks_V_read_reg_237[6]),
        .I2(num_blocks_V_read_reg_237[8]),
        .I3(t_V_1_fu_68_reg[8]),
        .I4(num_blocks_V_read_reg_237[7]),
        .I5(t_V_1_fu_68_reg[7]),
        .O(\ap_CS_fsm[2]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_13 
       (.I0(t_V_1_fu_68_reg[3]),
        .I1(num_blocks_V_read_reg_237[3]),
        .I2(num_blocks_V_read_reg_237[5]),
        .I3(t_V_1_fu_68_reg[5]),
        .I4(num_blocks_V_read_reg_237[4]),
        .I5(t_V_1_fu_68_reg[4]),
        .O(\ap_CS_fsm[2]_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_14 
       (.I0(t_V_1_fu_68_reg[0]),
        .I1(num_blocks_V_read_reg_237[0]),
        .I2(num_blocks_V_read_reg_237[2]),
        .I3(t_V_1_fu_68_reg[2]),
        .I4(num_blocks_V_read_reg_237[1]),
        .I5(t_V_1_fu_68_reg[1]),
        .O(\ap_CS_fsm[2]_i_14_n_0 ));
  LUT4 #(
    .INIT(16'h9009)) 
    \ap_CS_fsm[2]_i_4 
       (.I0(t_V_1_fu_68_reg[30]),
        .I1(num_blocks_V_read_reg_237[30]),
        .I2(t_V_1_fu_68_reg[31]),
        .I3(num_blocks_V_read_reg_237[31]),
        .O(\ap_CS_fsm[2]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_5 
       (.I0(t_V_1_fu_68_reg[27]),
        .I1(num_blocks_V_read_reg_237[27]),
        .I2(num_blocks_V_read_reg_237[29]),
        .I3(t_V_1_fu_68_reg[29]),
        .I4(num_blocks_V_read_reg_237[28]),
        .I5(t_V_1_fu_68_reg[28]),
        .O(\ap_CS_fsm[2]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_6 
       (.I0(t_V_1_fu_68_reg[24]),
        .I1(num_blocks_V_read_reg_237[24]),
        .I2(num_blocks_V_read_reg_237[26]),
        .I3(t_V_1_fu_68_reg[26]),
        .I4(num_blocks_V_read_reg_237[25]),
        .I5(t_V_1_fu_68_reg[25]),
        .O(\ap_CS_fsm[2]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_7 
       (.I0(t_V_1_fu_68_reg[21]),
        .I1(num_blocks_V_read_reg_237[21]),
        .I2(num_blocks_V_read_reg_237[23]),
        .I3(t_V_1_fu_68_reg[23]),
        .I4(num_blocks_V_read_reg_237[22]),
        .I5(t_V_1_fu_68_reg[22]),
        .O(\ap_CS_fsm[2]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_8 
       (.I0(t_V_1_fu_68_reg[18]),
        .I1(num_blocks_V_read_reg_237[18]),
        .I2(num_blocks_V_read_reg_237[20]),
        .I3(t_V_1_fu_68_reg[20]),
        .I4(num_blocks_V_read_reg_237[19]),
        .I5(t_V_1_fu_68_reg[19]),
        .O(\ap_CS_fsm[2]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h9009000000009009)) 
    \ap_CS_fsm[2]_i_9 
       (.I0(t_V_1_fu_68_reg[15]),
        .I1(num_blocks_V_read_reg_237[15]),
        .I2(num_blocks_V_read_reg_237[17]),
        .I3(t_V_1_fu_68_reg[17]),
        .I4(num_blocks_V_read_reg_237[16]),
        .I5(t_V_1_fu_68_reg[16]),
        .O(\ap_CS_fsm[2]_i_9_n_0 ));
  (* FSM_ENCODING = "none" *) 
  FDSE #(
    .INIT(1'b1)) 
    \ap_CS_fsm_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_NS_fsm[0]),
        .Q(\ap_CS_fsm_reg_n_0_[0] ),
        .S(ap_rst_n_inv));
  (* FSM_ENCODING = "none" *) 
  FDRE #(
    .INIT(1'b0)) 
    \ap_CS_fsm_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_NS_fsm[1]),
        .Q(ap_CS_fsm_state2),
        .R(ap_rst_n_inv));
  (* FSM_ENCODING = "none" *) 
  FDRE #(
    .INIT(1'b0)) 
    \ap_CS_fsm_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_NS_fsm[2]),
        .Q(ap_CS_fsm_state3),
        .R(ap_rst_n_inv));
  CARRY8 \ap_CS_fsm_reg[2]_i_2 
       (.CI(\ap_CS_fsm_reg[2]_i_3_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_ap_CS_fsm_reg[2]_i_2_CO_UNCONNECTED [7:3],\ap_CS_fsm_reg[2]_i_2_n_5 ,\ap_CS_fsm_reg[2]_i_2_n_6 ,\ap_CS_fsm_reg[2]_i_2_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(\NLW_ap_CS_fsm_reg[2]_i_2_O_UNCONNECTED [7:0]),
        .S({1'b0,1'b0,1'b0,1'b0,1'b0,\ap_CS_fsm[2]_i_4_n_0 ,\ap_CS_fsm[2]_i_5_n_0 ,\ap_CS_fsm[2]_i_6_n_0 }));
  CARRY8 \ap_CS_fsm_reg[2]_i_3 
       (.CI(1'b1),
        .CI_TOP(1'b0),
        .CO({\ap_CS_fsm_reg[2]_i_3_n_0 ,\ap_CS_fsm_reg[2]_i_3_n_1 ,\ap_CS_fsm_reg[2]_i_3_n_2 ,\ap_CS_fsm_reg[2]_i_3_n_3 ,\ap_CS_fsm_reg[2]_i_3_n_4 ,\ap_CS_fsm_reg[2]_i_3_n_5 ,\ap_CS_fsm_reg[2]_i_3_n_6 ,\ap_CS_fsm_reg[2]_i_3_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O(\NLW_ap_CS_fsm_reg[2]_i_3_O_UNCONNECTED [7:0]),
        .S({\ap_CS_fsm[2]_i_7_n_0 ,\ap_CS_fsm[2]_i_8_n_0 ,\ap_CS_fsm[2]_i_9_n_0 ,\ap_CS_fsm[2]_i_10_n_0 ,\ap_CS_fsm[2]_i_11_n_0 ,\ap_CS_fsm[2]_i_12_n_0 ,\ap_CS_fsm[2]_i_13_n_0 ,\ap_CS_fsm[2]_i_14_n_0 }));
  LUT6 #(
    .INIT(64'h4000000000000000)) 
    \first_V_preg[31]_i_1 
       (.I0(\ap_CS_fsm_reg[2]_i_2_n_5 ),
        .I1(ap_CS_fsm_state2),
        .I2(tready_V),
        .I3(tvalid_V),
        .I4(tlast_V),
        .I5(p_s_fu_60),
        .O(first_V_preg1));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[0] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[0]),
        .Q(first_V_preg[0]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[10] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[10]),
        .Q(first_V_preg[10]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[11] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[11]),
        .Q(first_V_preg[11]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[12] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[12]),
        .Q(first_V_preg[12]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[13] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[13]),
        .Q(first_V_preg[13]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[14] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[14]),
        .Q(first_V_preg[14]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[15] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[15]),
        .Q(first_V_preg[15]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[16] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[16]),
        .Q(first_V_preg[16]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[17] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[17]),
        .Q(first_V_preg[17]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[18] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[18]),
        .Q(first_V_preg[18]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[19] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[19]),
        .Q(first_V_preg[19]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[1] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[1]),
        .Q(first_V_preg[1]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[20] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[20]),
        .Q(first_V_preg[20]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[21] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[21]),
        .Q(first_V_preg[21]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[22] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[22]),
        .Q(first_V_preg[22]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[23] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[23]),
        .Q(first_V_preg[23]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[24] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[24]),
        .Q(first_V_preg[24]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[25] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[25]),
        .Q(first_V_preg[25]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[26] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[26]),
        .Q(first_V_preg[26]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[27] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[27]),
        .Q(first_V_preg[27]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[28] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[28]),
        .Q(first_V_preg[28]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[29] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[29]),
        .Q(first_V_preg[29]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[2] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[2]),
        .Q(first_V_preg[2]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[30] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[30]),
        .Q(first_V_preg[30]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[31] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[31]),
        .Q(first_V_preg[31]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[3] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[3]),
        .Q(first_V_preg[3]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[4] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[4]),
        .Q(first_V_preg[4]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[5] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[5]),
        .Q(first_V_preg[5]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[6] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[6]),
        .Q(first_V_preg[6]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[7] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[7]),
        .Q(first_V_preg[7]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[8] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[8]),
        .Q(first_V_preg[8]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \first_V_preg_reg[9] 
       (.C(ap_clk),
        .CE(first_V_preg1),
        .D(rtc_V[9]),
        .Q(first_V_preg[9]),
        .R(ap_rst_n_inv));
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_monitor_CNTRL_s_axi monitor_CNTRL_s_axi_U
       (.CO(\ap_CS_fsm_reg[2]_i_2_n_5 ),
        .D(ap_NS_fsm[1:0]),
        .E(ap_NS_fsm11_out),
        .\FSM_onehot_rstate_reg[1]_0 (s_axi_CNTRL_ARREADY),
        .\FSM_onehot_wstate_reg[1]_0 (s_axi_CNTRL_AWREADY),
        .\FSM_onehot_wstate_reg[2]_0 (s_axi_CNTRL_WREADY),
        .Q({ap_CS_fsm_state3,ap_CS_fsm_state2,\ap_CS_fsm_reg_n_0_[0] }),
        .\ap_CS_fsm_reg[0] (monitor_CNTRL_s_axi_U_n_6),
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_rst_n_cntrl_aclk(ap_rst_n_cntrl_aclk),
        .ap_rst_n_inv(ap_rst_n_inv),
        .cntrl_aclk(cntrl_aclk),
        .first_V_preg(first_V_preg),
        .int_ap_start_reg_0(monitor_CNTRL_s_axi_U_n_11),
        .\int_last_V_reg[31]_0 (time_stamp_V_1_fu_64),
        .\int_num_blocks_V_reg[31]_0 (num_blocks_V),
        .\int_stalled_V_reg[31]_0 (t_V_reg_124_reg),
        .interrupt(interrupt),
        .p_s_fu_60(p_s_fu_60),
        .rtc_V(rtc_V),
        .s_axi_CNTRL_ARADDR(s_axi_CNTRL_ARADDR),
        .s_axi_CNTRL_ARVALID(s_axi_CNTRL_ARVALID),
        .s_axi_CNTRL_AWADDR(s_axi_CNTRL_AWADDR),
        .s_axi_CNTRL_AWVALID(s_axi_CNTRL_AWVALID),
        .s_axi_CNTRL_BREADY(s_axi_CNTRL_BREADY),
        .s_axi_CNTRL_BVALID(s_axi_CNTRL_BVALID),
        .s_axi_CNTRL_RDATA(s_axi_CNTRL_RDATA),
        .s_axi_CNTRL_RREADY(s_axi_CNTRL_RREADY),
        .s_axi_CNTRL_RVALID(s_axi_CNTRL_RVALID),
        .s_axi_CNTRL_WDATA(s_axi_CNTRL_WDATA),
        .s_axi_CNTRL_WSTRB(s_axi_CNTRL_WSTRB),
        .s_axi_CNTRL_WVALID(s_axi_CNTRL_WVALID),
        .t_V_1_fu_68(t_V_1_fu_68),
        .tlast_V(tlast_V),
        .tready_V(tready_V),
        .tvalid_V(tvalid_V));
  FDRE \num_blocks_V_read_reg_237_reg[0] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[0]),
        .Q(num_blocks_V_read_reg_237[0]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[10] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[10]),
        .Q(num_blocks_V_read_reg_237[10]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[11] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[11]),
        .Q(num_blocks_V_read_reg_237[11]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[12] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[12]),
        .Q(num_blocks_V_read_reg_237[12]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[13] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[13]),
        .Q(num_blocks_V_read_reg_237[13]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[14] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[14]),
        .Q(num_blocks_V_read_reg_237[14]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[15] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[15]),
        .Q(num_blocks_V_read_reg_237[15]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[16] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[16]),
        .Q(num_blocks_V_read_reg_237[16]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[17] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[17]),
        .Q(num_blocks_V_read_reg_237[17]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[18] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[18]),
        .Q(num_blocks_V_read_reg_237[18]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[19] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[19]),
        .Q(num_blocks_V_read_reg_237[19]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[1] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[1]),
        .Q(num_blocks_V_read_reg_237[1]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[20] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[20]),
        .Q(num_blocks_V_read_reg_237[20]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[21] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[21]),
        .Q(num_blocks_V_read_reg_237[21]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[22] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[22]),
        .Q(num_blocks_V_read_reg_237[22]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[23] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[23]),
        .Q(num_blocks_V_read_reg_237[23]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[24] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[24]),
        .Q(num_blocks_V_read_reg_237[24]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[25] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[25]),
        .Q(num_blocks_V_read_reg_237[25]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[26] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[26]),
        .Q(num_blocks_V_read_reg_237[26]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[27] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[27]),
        .Q(num_blocks_V_read_reg_237[27]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[28] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[28]),
        .Q(num_blocks_V_read_reg_237[28]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[29] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[29]),
        .Q(num_blocks_V_read_reg_237[29]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[2] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[2]),
        .Q(num_blocks_V_read_reg_237[2]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[30] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[30]),
        .Q(num_blocks_V_read_reg_237[30]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[31] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[31]),
        .Q(num_blocks_V_read_reg_237[31]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[3] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[3]),
        .Q(num_blocks_V_read_reg_237[3]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[4] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[4]),
        .Q(num_blocks_V_read_reg_237[4]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[5] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[5]),
        .Q(num_blocks_V_read_reg_237[5]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[6] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[6]),
        .Q(num_blocks_V_read_reg_237[6]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[7] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[7]),
        .Q(num_blocks_V_read_reg_237[7]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[8] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[8]),
        .Q(num_blocks_V_read_reg_237[8]),
        .R(1'b0));
  FDRE \num_blocks_V_read_reg_237_reg[9] 
       (.C(ap_clk),
        .CE(ap_NS_fsm11_out),
        .D(num_blocks_V[9]),
        .Q(num_blocks_V_read_reg_237[9]),
        .R(1'b0));
  FDRE \p_s_fu_60_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(monitor_CNTRL_s_axi_U_n_11),
        .Q(p_s_fu_60),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \t_V_1_fu_68[0]_i_3 
       (.I0(t_V_1_fu_68_reg[0]),
        .O(\t_V_1_fu_68[0]_i_3_n_0 ));
  FDRE \t_V_1_fu_68_reg[0] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_15 ),
        .Q(t_V_1_fu_68_reg[0]),
        .R(t_V_1_fu_68));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_1_fu_68_reg[0]_i_2 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\t_V_1_fu_68_reg[0]_i_2_n_0 ,\t_V_1_fu_68_reg[0]_i_2_n_1 ,\t_V_1_fu_68_reg[0]_i_2_n_2 ,\t_V_1_fu_68_reg[0]_i_2_n_3 ,\t_V_1_fu_68_reg[0]_i_2_n_4 ,\t_V_1_fu_68_reg[0]_i_2_n_5 ,\t_V_1_fu_68_reg[0]_i_2_n_6 ,\t_V_1_fu_68_reg[0]_i_2_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1}),
        .O({\t_V_1_fu_68_reg[0]_i_2_n_8 ,\t_V_1_fu_68_reg[0]_i_2_n_9 ,\t_V_1_fu_68_reg[0]_i_2_n_10 ,\t_V_1_fu_68_reg[0]_i_2_n_11 ,\t_V_1_fu_68_reg[0]_i_2_n_12 ,\t_V_1_fu_68_reg[0]_i_2_n_13 ,\t_V_1_fu_68_reg[0]_i_2_n_14 ,\t_V_1_fu_68_reg[0]_i_2_n_15 }),
        .S({t_V_1_fu_68_reg[7:1],\t_V_1_fu_68[0]_i_3_n_0 }));
  FDRE \t_V_1_fu_68_reg[10] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_13 ),
        .Q(t_V_1_fu_68_reg[10]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[11] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_12 ),
        .Q(t_V_1_fu_68_reg[11]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[12] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_11 ),
        .Q(t_V_1_fu_68_reg[12]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[13] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_10 ),
        .Q(t_V_1_fu_68_reg[13]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[14] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_9 ),
        .Q(t_V_1_fu_68_reg[14]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[15] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_8 ),
        .Q(t_V_1_fu_68_reg[15]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[16] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_15 ),
        .Q(t_V_1_fu_68_reg[16]),
        .R(t_V_1_fu_68));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_1_fu_68_reg[16]_i_1 
       (.CI(\t_V_1_fu_68_reg[8]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\t_V_1_fu_68_reg[16]_i_1_n_0 ,\t_V_1_fu_68_reg[16]_i_1_n_1 ,\t_V_1_fu_68_reg[16]_i_1_n_2 ,\t_V_1_fu_68_reg[16]_i_1_n_3 ,\t_V_1_fu_68_reg[16]_i_1_n_4 ,\t_V_1_fu_68_reg[16]_i_1_n_5 ,\t_V_1_fu_68_reg[16]_i_1_n_6 ,\t_V_1_fu_68_reg[16]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\t_V_1_fu_68_reg[16]_i_1_n_8 ,\t_V_1_fu_68_reg[16]_i_1_n_9 ,\t_V_1_fu_68_reg[16]_i_1_n_10 ,\t_V_1_fu_68_reg[16]_i_1_n_11 ,\t_V_1_fu_68_reg[16]_i_1_n_12 ,\t_V_1_fu_68_reg[16]_i_1_n_13 ,\t_V_1_fu_68_reg[16]_i_1_n_14 ,\t_V_1_fu_68_reg[16]_i_1_n_15 }),
        .S(t_V_1_fu_68_reg[23:16]));
  FDRE \t_V_1_fu_68_reg[17] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_14 ),
        .Q(t_V_1_fu_68_reg[17]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[18] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_13 ),
        .Q(t_V_1_fu_68_reg[18]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[19] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_12 ),
        .Q(t_V_1_fu_68_reg[19]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[1] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_14 ),
        .Q(t_V_1_fu_68_reg[1]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[20] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_11 ),
        .Q(t_V_1_fu_68_reg[20]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[21] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_10 ),
        .Q(t_V_1_fu_68_reg[21]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[22] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_9 ),
        .Q(t_V_1_fu_68_reg[22]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[23] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[16]_i_1_n_8 ),
        .Q(t_V_1_fu_68_reg[23]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[24] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_15 ),
        .Q(t_V_1_fu_68_reg[24]),
        .R(t_V_1_fu_68));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_1_fu_68_reg[24]_i_1 
       (.CI(\t_V_1_fu_68_reg[16]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_t_V_1_fu_68_reg[24]_i_1_CO_UNCONNECTED [7],\t_V_1_fu_68_reg[24]_i_1_n_1 ,\t_V_1_fu_68_reg[24]_i_1_n_2 ,\t_V_1_fu_68_reg[24]_i_1_n_3 ,\t_V_1_fu_68_reg[24]_i_1_n_4 ,\t_V_1_fu_68_reg[24]_i_1_n_5 ,\t_V_1_fu_68_reg[24]_i_1_n_6 ,\t_V_1_fu_68_reg[24]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\t_V_1_fu_68_reg[24]_i_1_n_8 ,\t_V_1_fu_68_reg[24]_i_1_n_9 ,\t_V_1_fu_68_reg[24]_i_1_n_10 ,\t_V_1_fu_68_reg[24]_i_1_n_11 ,\t_V_1_fu_68_reg[24]_i_1_n_12 ,\t_V_1_fu_68_reg[24]_i_1_n_13 ,\t_V_1_fu_68_reg[24]_i_1_n_14 ,\t_V_1_fu_68_reg[24]_i_1_n_15 }),
        .S(t_V_1_fu_68_reg[31:24]));
  FDRE \t_V_1_fu_68_reg[25] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_14 ),
        .Q(t_V_1_fu_68_reg[25]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[26] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_13 ),
        .Q(t_V_1_fu_68_reg[26]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[27] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_12 ),
        .Q(t_V_1_fu_68_reg[27]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[28] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_11 ),
        .Q(t_V_1_fu_68_reg[28]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[29] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_10 ),
        .Q(t_V_1_fu_68_reg[29]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[2] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_13 ),
        .Q(t_V_1_fu_68_reg[2]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[30] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_9 ),
        .Q(t_V_1_fu_68_reg[30]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[31] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[24]_i_1_n_8 ),
        .Q(t_V_1_fu_68_reg[31]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[3] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_12 ),
        .Q(t_V_1_fu_68_reg[3]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[4] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_11 ),
        .Q(t_V_1_fu_68_reg[4]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[5] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_10 ),
        .Q(t_V_1_fu_68_reg[5]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[6] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_9 ),
        .Q(t_V_1_fu_68_reg[6]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[7] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[0]_i_2_n_8 ),
        .Q(t_V_1_fu_68_reg[7]),
        .R(t_V_1_fu_68));
  FDRE \t_V_1_fu_68_reg[8] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_15 ),
        .Q(t_V_1_fu_68_reg[8]),
        .R(t_V_1_fu_68));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_1_fu_68_reg[8]_i_1 
       (.CI(\t_V_1_fu_68_reg[0]_i_2_n_0 ),
        .CI_TOP(1'b0),
        .CO({\t_V_1_fu_68_reg[8]_i_1_n_0 ,\t_V_1_fu_68_reg[8]_i_1_n_1 ,\t_V_1_fu_68_reg[8]_i_1_n_2 ,\t_V_1_fu_68_reg[8]_i_1_n_3 ,\t_V_1_fu_68_reg[8]_i_1_n_4 ,\t_V_1_fu_68_reg[8]_i_1_n_5 ,\t_V_1_fu_68_reg[8]_i_1_n_6 ,\t_V_1_fu_68_reg[8]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\t_V_1_fu_68_reg[8]_i_1_n_8 ,\t_V_1_fu_68_reg[8]_i_1_n_9 ,\t_V_1_fu_68_reg[8]_i_1_n_10 ,\t_V_1_fu_68_reg[8]_i_1_n_11 ,\t_V_1_fu_68_reg[8]_i_1_n_12 ,\t_V_1_fu_68_reg[8]_i_1_n_13 ,\t_V_1_fu_68_reg[8]_i_1_n_14 ,\t_V_1_fu_68_reg[8]_i_1_n_15 }),
        .S(t_V_1_fu_68_reg[15:8]));
  FDRE \t_V_1_fu_68_reg[9] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(\t_V_1_fu_68_reg[8]_i_1_n_14 ),
        .Q(t_V_1_fu_68_reg[9]),
        .R(t_V_1_fu_68));
  LUT4 #(
    .INIT(16'h0400)) 
    \t_V_reg_124[0]_i_2 
       (.I0(\ap_CS_fsm_reg[2]_i_2_n_5 ),
        .I1(ap_CS_fsm_state2),
        .I2(tready_V),
        .I3(tvalid_V),
        .O(t_V_reg_124));
  LUT1 #(
    .INIT(2'h1)) 
    \t_V_reg_124[0]_i_4 
       (.I0(t_V_reg_124_reg[0]),
        .O(\t_V_reg_124[0]_i_4_n_0 ));
  FDRE \t_V_reg_124_reg[0] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_15 ),
        .Q(t_V_reg_124_reg[0]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_reg_124_reg[0]_i_3 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\t_V_reg_124_reg[0]_i_3_n_0 ,\t_V_reg_124_reg[0]_i_3_n_1 ,\t_V_reg_124_reg[0]_i_3_n_2 ,\t_V_reg_124_reg[0]_i_3_n_3 ,\t_V_reg_124_reg[0]_i_3_n_4 ,\t_V_reg_124_reg[0]_i_3_n_5 ,\t_V_reg_124_reg[0]_i_3_n_6 ,\t_V_reg_124_reg[0]_i_3_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1}),
        .O({\t_V_reg_124_reg[0]_i_3_n_8 ,\t_V_reg_124_reg[0]_i_3_n_9 ,\t_V_reg_124_reg[0]_i_3_n_10 ,\t_V_reg_124_reg[0]_i_3_n_11 ,\t_V_reg_124_reg[0]_i_3_n_12 ,\t_V_reg_124_reg[0]_i_3_n_13 ,\t_V_reg_124_reg[0]_i_3_n_14 ,\t_V_reg_124_reg[0]_i_3_n_15 }),
        .S({t_V_reg_124_reg[7:1],\t_V_reg_124[0]_i_4_n_0 }));
  FDRE \t_V_reg_124_reg[10] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_13 ),
        .Q(t_V_reg_124_reg[10]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[11] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_12 ),
        .Q(t_V_reg_124_reg[11]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[12] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_11 ),
        .Q(t_V_reg_124_reg[12]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[13] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_10 ),
        .Q(t_V_reg_124_reg[13]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[14] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_9 ),
        .Q(t_V_reg_124_reg[14]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[15] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_8 ),
        .Q(t_V_reg_124_reg[15]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[16] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_15 ),
        .Q(t_V_reg_124_reg[16]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_reg_124_reg[16]_i_1 
       (.CI(\t_V_reg_124_reg[8]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\t_V_reg_124_reg[16]_i_1_n_0 ,\t_V_reg_124_reg[16]_i_1_n_1 ,\t_V_reg_124_reg[16]_i_1_n_2 ,\t_V_reg_124_reg[16]_i_1_n_3 ,\t_V_reg_124_reg[16]_i_1_n_4 ,\t_V_reg_124_reg[16]_i_1_n_5 ,\t_V_reg_124_reg[16]_i_1_n_6 ,\t_V_reg_124_reg[16]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\t_V_reg_124_reg[16]_i_1_n_8 ,\t_V_reg_124_reg[16]_i_1_n_9 ,\t_V_reg_124_reg[16]_i_1_n_10 ,\t_V_reg_124_reg[16]_i_1_n_11 ,\t_V_reg_124_reg[16]_i_1_n_12 ,\t_V_reg_124_reg[16]_i_1_n_13 ,\t_V_reg_124_reg[16]_i_1_n_14 ,\t_V_reg_124_reg[16]_i_1_n_15 }),
        .S(t_V_reg_124_reg[23:16]));
  FDRE \t_V_reg_124_reg[17] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_14 ),
        .Q(t_V_reg_124_reg[17]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[18] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_13 ),
        .Q(t_V_reg_124_reg[18]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[19] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_12 ),
        .Q(t_V_reg_124_reg[19]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[1] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_14 ),
        .Q(t_V_reg_124_reg[1]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[20] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_11 ),
        .Q(t_V_reg_124_reg[20]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[21] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_10 ),
        .Q(t_V_reg_124_reg[21]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[22] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_9 ),
        .Q(t_V_reg_124_reg[22]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[23] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[16]_i_1_n_8 ),
        .Q(t_V_reg_124_reg[23]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[24] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_15 ),
        .Q(t_V_reg_124_reg[24]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_reg_124_reg[24]_i_1 
       (.CI(\t_V_reg_124_reg[16]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_t_V_reg_124_reg[24]_i_1_CO_UNCONNECTED [7],\t_V_reg_124_reg[24]_i_1_n_1 ,\t_V_reg_124_reg[24]_i_1_n_2 ,\t_V_reg_124_reg[24]_i_1_n_3 ,\t_V_reg_124_reg[24]_i_1_n_4 ,\t_V_reg_124_reg[24]_i_1_n_5 ,\t_V_reg_124_reg[24]_i_1_n_6 ,\t_V_reg_124_reg[24]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\t_V_reg_124_reg[24]_i_1_n_8 ,\t_V_reg_124_reg[24]_i_1_n_9 ,\t_V_reg_124_reg[24]_i_1_n_10 ,\t_V_reg_124_reg[24]_i_1_n_11 ,\t_V_reg_124_reg[24]_i_1_n_12 ,\t_V_reg_124_reg[24]_i_1_n_13 ,\t_V_reg_124_reg[24]_i_1_n_14 ,\t_V_reg_124_reg[24]_i_1_n_15 }),
        .S(t_V_reg_124_reg[31:24]));
  FDRE \t_V_reg_124_reg[25] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_14 ),
        .Q(t_V_reg_124_reg[25]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[26] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_13 ),
        .Q(t_V_reg_124_reg[26]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[27] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_12 ),
        .Q(t_V_reg_124_reg[27]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[28] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_11 ),
        .Q(t_V_reg_124_reg[28]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[29] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_10 ),
        .Q(t_V_reg_124_reg[29]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[2] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_13 ),
        .Q(t_V_reg_124_reg[2]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[30] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_9 ),
        .Q(t_V_reg_124_reg[30]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[31] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[24]_i_1_n_8 ),
        .Q(t_V_reg_124_reg[31]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[3] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_12 ),
        .Q(t_V_reg_124_reg[3]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[4] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_11 ),
        .Q(t_V_reg_124_reg[4]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[5] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_10 ),
        .Q(t_V_reg_124_reg[5]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[6] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_9 ),
        .Q(t_V_reg_124_reg[6]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[7] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[0]_i_3_n_8 ),
        .Q(t_V_reg_124_reg[7]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  FDRE \t_V_reg_124_reg[8] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_15 ),
        .Q(t_V_reg_124_reg[8]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  (* ADDER_THRESHOLD = "16" *) 
  CARRY8 \t_V_reg_124_reg[8]_i_1 
       (.CI(\t_V_reg_124_reg[0]_i_3_n_0 ),
        .CI_TOP(1'b0),
        .CO({\t_V_reg_124_reg[8]_i_1_n_0 ,\t_V_reg_124_reg[8]_i_1_n_1 ,\t_V_reg_124_reg[8]_i_1_n_2 ,\t_V_reg_124_reg[8]_i_1_n_3 ,\t_V_reg_124_reg[8]_i_1_n_4 ,\t_V_reg_124_reg[8]_i_1_n_5 ,\t_V_reg_124_reg[8]_i_1_n_6 ,\t_V_reg_124_reg[8]_i_1_n_7 }),
        .DI({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .O({\t_V_reg_124_reg[8]_i_1_n_8 ,\t_V_reg_124_reg[8]_i_1_n_9 ,\t_V_reg_124_reg[8]_i_1_n_10 ,\t_V_reg_124_reg[8]_i_1_n_11 ,\t_V_reg_124_reg[8]_i_1_n_12 ,\t_V_reg_124_reg[8]_i_1_n_13 ,\t_V_reg_124_reg[8]_i_1_n_14 ,\t_V_reg_124_reg[8]_i_1_n_15 }),
        .S(t_V_reg_124_reg[15:8]));
  FDRE \t_V_reg_124_reg[9] 
       (.C(ap_clk),
        .CE(t_V_reg_124),
        .D(\t_V_reg_124_reg[8]_i_1_n_14 ),
        .Q(t_V_reg_124_reg[9]),
        .R(monitor_CNTRL_s_axi_U_n_6));
  LUT5 #(
    .INIT(32'h40000000)) 
    \time_stamp_V_1_fu_64[31]_i_1 
       (.I0(\ap_CS_fsm_reg[2]_i_2_n_5 ),
        .I1(ap_CS_fsm_state2),
        .I2(tlast_V),
        .I3(tvalid_V),
        .I4(tready_V),
        .O(t_V_1_fu_680));
  FDRE \time_stamp_V_1_fu_64_reg[0] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[0]),
        .Q(time_stamp_V_1_fu_64[0]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[10] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[10]),
        .Q(time_stamp_V_1_fu_64[10]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[11] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[11]),
        .Q(time_stamp_V_1_fu_64[11]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[12] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[12]),
        .Q(time_stamp_V_1_fu_64[12]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[13] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[13]),
        .Q(time_stamp_V_1_fu_64[13]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[14] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[14]),
        .Q(time_stamp_V_1_fu_64[14]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[15] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[15]),
        .Q(time_stamp_V_1_fu_64[15]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[16] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[16]),
        .Q(time_stamp_V_1_fu_64[16]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[17] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[17]),
        .Q(time_stamp_V_1_fu_64[17]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[18] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[18]),
        .Q(time_stamp_V_1_fu_64[18]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[19] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[19]),
        .Q(time_stamp_V_1_fu_64[19]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[1] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[1]),
        .Q(time_stamp_V_1_fu_64[1]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[20] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[20]),
        .Q(time_stamp_V_1_fu_64[20]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[21] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[21]),
        .Q(time_stamp_V_1_fu_64[21]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[22] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[22]),
        .Q(time_stamp_V_1_fu_64[22]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[23] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[23]),
        .Q(time_stamp_V_1_fu_64[23]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[24] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[24]),
        .Q(time_stamp_V_1_fu_64[24]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[25] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[25]),
        .Q(time_stamp_V_1_fu_64[25]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[26] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[26]),
        .Q(time_stamp_V_1_fu_64[26]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[27] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[27]),
        .Q(time_stamp_V_1_fu_64[27]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[28] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[28]),
        .Q(time_stamp_V_1_fu_64[28]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[29] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[29]),
        .Q(time_stamp_V_1_fu_64[29]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[2] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[2]),
        .Q(time_stamp_V_1_fu_64[2]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[30] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[30]),
        .Q(time_stamp_V_1_fu_64[30]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[31] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[31]),
        .Q(time_stamp_V_1_fu_64[31]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[3] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[3]),
        .Q(time_stamp_V_1_fu_64[3]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[4] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[4]),
        .Q(time_stamp_V_1_fu_64[4]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[5] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[5]),
        .Q(time_stamp_V_1_fu_64[5]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[6] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[6]),
        .Q(time_stamp_V_1_fu_64[6]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[7] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[7]),
        .Q(time_stamp_V_1_fu_64[7]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[8] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[8]),
        .Q(time_stamp_V_1_fu_64[8]),
        .R(1'b0));
  FDRE \time_stamp_V_1_fu_64_reg[9] 
       (.C(ap_clk),
        .CE(t_V_1_fu_680),
        .D(rtc_V[9]),
        .Q(time_stamp_V_1_fu_64[9]),
        .R(1'b0));
endmodule

module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_monitor_CNTRL_s_axi
   (ap_rst_n_inv,
    \FSM_onehot_rstate_reg[1]_0 ,
    s_axi_CNTRL_RVALID,
    \FSM_onehot_wstate_reg[1]_0 ,
    \FSM_onehot_wstate_reg[2]_0 ,
    interrupt,
    \ap_CS_fsm_reg[0] ,
    t_V_1_fu_68,
    E,
    D,
    int_ap_start_reg_0,
    s_axi_CNTRL_BVALID,
    \int_num_blocks_V_reg[31]_0 ,
    s_axi_CNTRL_RDATA,
    ap_clk,
    Q,
    s_axi_CNTRL_ARVALID,
    s_axi_CNTRL_RREADY,
    s_axi_CNTRL_ARADDR,
    s_axi_CNTRL_AWVALID,
    s_axi_CNTRL_WDATA,
    s_axi_CNTRL_WSTRB,
    s_axi_CNTRL_WVALID,
    CO,
    tready_V,
    tvalid_V,
    tlast_V,
    p_s_fu_60,
    s_axi_CNTRL_BREADY,
    rtc_V,
    first_V_preg,
    ap_rst_n_cntrl_aclk,
    ap_rst_n,
    cntrl_aclk,
    s_axi_CNTRL_AWADDR,
    \int_last_V_reg[31]_0 ,
    \int_stalled_V_reg[31]_0 );
  output ap_rst_n_inv;
  output \FSM_onehot_rstate_reg[1]_0 ;
  output s_axi_CNTRL_RVALID;
  output \FSM_onehot_wstate_reg[1]_0 ;
  output \FSM_onehot_wstate_reg[2]_0 ;
  output interrupt;
  output \ap_CS_fsm_reg[0] ;
  output t_V_1_fu_68;
  output [0:0]E;
  output [1:0]D;
  output int_ap_start_reg_0;
  output s_axi_CNTRL_BVALID;
  output [31:0]\int_num_blocks_V_reg[31]_0 ;
  output [31:0]s_axi_CNTRL_RDATA;
  input ap_clk;
  input [2:0]Q;
  input s_axi_CNTRL_ARVALID;
  input s_axi_CNTRL_RREADY;
  input [5:0]s_axi_CNTRL_ARADDR;
  input s_axi_CNTRL_AWVALID;
  input [31:0]s_axi_CNTRL_WDATA;
  input [3:0]s_axi_CNTRL_WSTRB;
  input s_axi_CNTRL_WVALID;
  input [0:0]CO;
  input [0:0]tready_V;
  input [0:0]tvalid_V;
  input [0:0]tlast_V;
  input p_s_fu_60;
  input s_axi_CNTRL_BREADY;
  input [31:0]rtc_V;
  input [31:0]first_V_preg;
  input ap_rst_n_cntrl_aclk;
  input ap_rst_n;
  input cntrl_aclk;
  input [5:0]s_axi_CNTRL_AWADDR;
  input [31:0]\int_last_V_reg[31]_0 ;
  input [31:0]\int_stalled_V_reg[31]_0 ;

  wire [0:0]CO;
  wire [1:0]D;
  wire [0:0]E;
  wire \FSM_onehot_rstate[1]_i_1_n_0 ;
  wire \FSM_onehot_rstate[2]_i_1_n_0 ;
  wire \FSM_onehot_rstate_reg[1]_0 ;
  wire \FSM_onehot_wstate[1]_i_2_n_0 ;
  wire \FSM_onehot_wstate[2]_i_1_n_0 ;
  wire \FSM_onehot_wstate[3]_i_1_n_0 ;
  wire \FSM_onehot_wstate_reg[1]_0 ;
  wire \FSM_onehot_wstate_reg[2]_0 ;
  wire [2:0]Q;
  wire \ap_CS_fsm_reg[0] ;
  wire ap_clk;
  wire ap_done_ext;
  wire ap_done_get;
  wire ap_idle;
  wire ap_rst_n;
  wire ap_rst_n_cntrl_aclk;
  wire ap_rst_n_cntrl_aclk_inv;
  wire ap_rst_n_inv;
  wire ap_start;
  wire ap_start_mask;
  wire ap_start_mask_i_3_n_0;
  wire ap_start_set;
  wire ar_hs;
  wire cntrl_aclk;
  wire [31:0]first_V;
  wire [31:0]first_V_preg;
  wire int_ap_done;
  wire int_ap_done_i_1_n_0;
  wire int_ap_idle;
  wire int_ap_ready;
  wire int_ap_start0;
  wire int_ap_start_i_1_n_0;
  wire int_ap_start_reg_0;
  wire int_auto_restart;
  wire int_auto_restart_i_1_n_0;
  wire [31:0]int_first_V;
  wire int_gie;
  wire int_gie_i_1_n_0;
  wire int_ier0;
  wire \int_ier_reg_n_0_[0] ;
  wire \int_isr[0]_i_1_n_0 ;
  wire \int_isr[1]_i_1_n_0 ;
  wire int_isr_reg02_out;
  wire \int_isr_reg_n_0_[0] ;
  wire [31:0]int_last_V;
  wire [31:0]\int_last_V_reg[31]_0 ;
  wire \int_num_blocks_V[0]_i_1_n_0 ;
  wire \int_num_blocks_V[10]_i_1_n_0 ;
  wire \int_num_blocks_V[11]_i_1_n_0 ;
  wire \int_num_blocks_V[12]_i_1_n_0 ;
  wire \int_num_blocks_V[13]_i_1_n_0 ;
  wire \int_num_blocks_V[14]_i_1_n_0 ;
  wire \int_num_blocks_V[15]_i_1_n_0 ;
  wire \int_num_blocks_V[16]_i_1_n_0 ;
  wire \int_num_blocks_V[17]_i_1_n_0 ;
  wire \int_num_blocks_V[18]_i_1_n_0 ;
  wire \int_num_blocks_V[19]_i_1_n_0 ;
  wire \int_num_blocks_V[1]_i_1_n_0 ;
  wire \int_num_blocks_V[20]_i_1_n_0 ;
  wire \int_num_blocks_V[21]_i_1_n_0 ;
  wire \int_num_blocks_V[22]_i_1_n_0 ;
  wire \int_num_blocks_V[23]_i_1_n_0 ;
  wire \int_num_blocks_V[24]_i_1_n_0 ;
  wire \int_num_blocks_V[25]_i_1_n_0 ;
  wire \int_num_blocks_V[26]_i_1_n_0 ;
  wire \int_num_blocks_V[27]_i_1_n_0 ;
  wire \int_num_blocks_V[28]_i_1_n_0 ;
  wire \int_num_blocks_V[29]_i_1_n_0 ;
  wire \int_num_blocks_V[2]_i_1_n_0 ;
  wire \int_num_blocks_V[30]_i_1_n_0 ;
  wire \int_num_blocks_V[31]_i_1_n_0 ;
  wire \int_num_blocks_V[31]_i_2_n_0 ;
  wire \int_num_blocks_V[31]_i_3_n_0 ;
  wire \int_num_blocks_V[3]_i_1_n_0 ;
  wire \int_num_blocks_V[4]_i_1_n_0 ;
  wire \int_num_blocks_V[5]_i_1_n_0 ;
  wire \int_num_blocks_V[6]_i_1_n_0 ;
  wire \int_num_blocks_V[7]_i_1_n_0 ;
  wire \int_num_blocks_V[8]_i_1_n_0 ;
  wire \int_num_blocks_V[9]_i_1_n_0 ;
  wire [31:0]\int_num_blocks_V_reg[31]_0 ;
  wire [31:0]int_stalled_V;
  wire [31:0]\int_stalled_V_reg[31]_0 ;
  wire interrupt;
  wire isr_mask;
  wire isr_toggle;
  wire p_0_in;
  wire p_1_in;
  wire p_2_in;
  wire p_s_fu_60;
  wire [7:2]rdata;
  wire \rdata[0]_i_1_n_0 ;
  wire \rdata[0]_i_3_n_0 ;
  wire \rdata[0]_i_4_n_0 ;
  wire \rdata[0]_i_5_n_0 ;
  wire \rdata[10]_i_1_n_0 ;
  wire \rdata[11]_i_1_n_0 ;
  wire \rdata[12]_i_1_n_0 ;
  wire \rdata[13]_i_1_n_0 ;
  wire \rdata[14]_i_1_n_0 ;
  wire \rdata[15]_i_1_n_0 ;
  wire \rdata[16]_i_1_n_0 ;
  wire \rdata[17]_i_1_n_0 ;
  wire \rdata[18]_i_1_n_0 ;
  wire \rdata[19]_i_1_n_0 ;
  wire \rdata[1]_i_1_n_0 ;
  wire \rdata[1]_i_3_n_0 ;
  wire \rdata[1]_i_4_n_0 ;
  wire \rdata[1]_i_5_n_0 ;
  wire \rdata[1]_i_6_n_0 ;
  wire \rdata[20]_i_1_n_0 ;
  wire \rdata[21]_i_1_n_0 ;
  wire \rdata[22]_i_1_n_0 ;
  wire \rdata[23]_i_1_n_0 ;
  wire \rdata[24]_i_1_n_0 ;
  wire \rdata[25]_i_1_n_0 ;
  wire \rdata[26]_i_1_n_0 ;
  wire \rdata[27]_i_1_n_0 ;
  wire \rdata[28]_i_1_n_0 ;
  wire \rdata[29]_i_1_n_0 ;
  wire \rdata[2]_i_2_n_0 ;
  wire \rdata[2]_i_3_n_0 ;
  wire \rdata[30]_i_1_n_0 ;
  wire \rdata[31]_i_1_n_0 ;
  wire \rdata[31]_i_3_n_0 ;
  wire \rdata[3]_i_2_n_0 ;
  wire \rdata[3]_i_3_n_0 ;
  wire \rdata[4]_i_1_n_0 ;
  wire \rdata[5]_i_1_n_0 ;
  wire \rdata[6]_i_1_n_0 ;
  wire \rdata[7]_i_2_n_0 ;
  wire \rdata[7]_i_3_n_0 ;
  wire \rdata[8]_i_1_n_0 ;
  wire \rdata[9]_i_1_n_0 ;
  wire \rdata_reg[0]_i_2_n_0 ;
  wire \rdata_reg[1]_i_2_n_0 ;
  wire [31:0]rtc_V;
  wire [5:0]s_axi_CNTRL_ARADDR;
  wire s_axi_CNTRL_ARVALID;
  wire [5:0]s_axi_CNTRL_AWADDR;
  wire s_axi_CNTRL_AWVALID;
  wire s_axi_CNTRL_BREADY;
  wire s_axi_CNTRL_BVALID;
  wire [31:0]s_axi_CNTRL_RDATA;
  wire s_axi_CNTRL_RREADY;
  wire s_axi_CNTRL_RVALID;
  wire [31:0]s_axi_CNTRL_WDATA;
  wire [3:0]s_axi_CNTRL_WSTRB;
  wire s_axi_CNTRL_WVALID;
  wire t_V_1_fu_68;
  wire [0:0]tlast_V;
  wire [0:0]tready_V;
  wire [0:0]tvalid_V;
  wire waddr;
  wire \waddr_reg_n_0_[0] ;
  wire \waddr_reg_n_0_[1] ;
  wire \waddr_reg_n_0_[2] ;
  wire \waddr_reg_n_0_[3] ;
  wire \waddr_reg_n_0_[4] ;
  wire \waddr_reg_n_0_[5] ;

  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT4 #(
    .INIT(16'hF747)) 
    \FSM_onehot_rstate[1]_i_1 
       (.I0(s_axi_CNTRL_ARVALID),
        .I1(\FSM_onehot_rstate_reg[1]_0 ),
        .I2(s_axi_CNTRL_RVALID),
        .I3(s_axi_CNTRL_RREADY),
        .O(\FSM_onehot_rstate[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_rstate[2]_i_1 
       (.I0(s_axi_CNTRL_ARVALID),
        .I1(\FSM_onehot_rstate_reg[1]_0 ),
        .I2(s_axi_CNTRL_RREADY),
        .I3(s_axi_CNTRL_RVALID),
        .O(\FSM_onehot_rstate[2]_i_1_n_0 ));
  (* FSM_ENCODED_STATES = "RDIDLE:010,RDDATA:100,iSTATE:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_rstate_reg[1] 
       (.C(cntrl_aclk),
        .CE(1'b1),
        .D(\FSM_onehot_rstate[1]_i_1_n_0 ),
        .Q(\FSM_onehot_rstate_reg[1]_0 ),
        .R(ap_rst_n_inv));
  (* FSM_ENCODED_STATES = "RDIDLE:010,RDDATA:100,iSTATE:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_rstate_reg[2] 
       (.C(cntrl_aclk),
        .CE(1'b1),
        .D(\FSM_onehot_rstate[2]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RVALID),
        .R(ap_rst_n_inv));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_wstate[1]_i_1 
       (.I0(ap_rst_n),
        .O(ap_rst_n_inv));
  LUT5 #(
    .INIT(32'h888BFF8B)) 
    \FSM_onehot_wstate[1]_i_2 
       (.I0(s_axi_CNTRL_BREADY),
        .I1(s_axi_CNTRL_BVALID),
        .I2(\FSM_onehot_wstate_reg[2]_0 ),
        .I3(\FSM_onehot_wstate_reg[1]_0 ),
        .I4(s_axi_CNTRL_AWVALID),
        .O(\FSM_onehot_wstate[1]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_wstate[2]_i_1 
       (.I0(s_axi_CNTRL_AWVALID),
        .I1(\FSM_onehot_wstate_reg[1]_0 ),
        .I2(s_axi_CNTRL_WVALID),
        .I3(\FSM_onehot_wstate_reg[2]_0 ),
        .O(\FSM_onehot_wstate[2]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_wstate[3]_i_1 
       (.I0(s_axi_CNTRL_WVALID),
        .I1(\FSM_onehot_wstate_reg[2]_0 ),
        .I2(s_axi_CNTRL_BREADY),
        .I3(s_axi_CNTRL_BVALID),
        .O(\FSM_onehot_wstate[3]_i_1_n_0 ));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[1] 
       (.C(cntrl_aclk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[1]_i_2_n_0 ),
        .Q(\FSM_onehot_wstate_reg[1]_0 ),
        .R(ap_rst_n_inv));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[2] 
       (.C(cntrl_aclk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[2]_i_1_n_0 ),
        .Q(\FSM_onehot_wstate_reg[2]_0 ),
        .R(ap_rst_n_inv));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[3] 
       (.C(cntrl_aclk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[3]_i_1_n_0 ),
        .Q(s_axi_CNTRL_BVALID),
        .R(ap_rst_n_inv));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'h4555)) 
    \ap_CS_fsm[0]_i_1 
       (.I0(Q[1]),
        .I1(Q[2]),
        .I2(ap_start),
        .I3(Q[0]),
        .O(D[0]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'hDDC0)) 
    \ap_CS_fsm[1]_i_1 
       (.I0(CO),
        .I1(Q[0]),
        .I2(ap_start),
        .I3(Q[1]),
        .O(D[1]));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    ap_done_ext_i_1
       (.I0(ar_hs),
        .I1(s_axi_CNTRL_ARADDR[2]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\rdata[1]_i_4_n_0 ),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(s_axi_CNTRL_ARADDR[5]),
        .O(ap_done_get));
  FDRE ap_done_ext_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_done_get),
        .Q(ap_done_ext),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT1 #(
    .INIT(2'h1)) 
    ap_start_mask_i_1
       (.I0(ap_rst_n_cntrl_aclk),
        .O(ap_rst_n_cntrl_aclk_inv));
  LUT5 #(
    .INIT(32'h00200000)) 
    ap_start_mask_i_2
       (.I0(s_axi_CNTRL_WSTRB[0]),
        .I1(\waddr_reg_n_0_[3] ),
        .I2(ap_start_mask_i_3_n_0),
        .I3(\waddr_reg_n_0_[2] ),
        .I4(s_axi_CNTRL_WDATA[0]),
        .O(ap_start_set));
  LUT6 #(
    .INIT(64'h0000000000001000)) 
    ap_start_mask_i_3
       (.I0(\waddr_reg_n_0_[4] ),
        .I1(\waddr_reg_n_0_[1] ),
        .I2(\FSM_onehot_wstate_reg[2]_0 ),
        .I3(s_axi_CNTRL_WVALID),
        .I4(\waddr_reg_n_0_[5] ),
        .I5(\waddr_reg_n_0_[0] ),
        .O(ap_start_mask_i_3_n_0));
  FDRE ap_start_mask_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_start_set),
        .Q(ap_start_mask),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT4 #(
    .INIT(16'hEFAA)) 
    int_ap_done_i_1
       (.I0(Q[2]),
        .I1(ap_done_get),
        .I2(ap_done_ext),
        .I3(int_ap_done),
        .O(int_ap_done_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_done_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ap_done_i_1_n_0),
        .Q(int_ap_done),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT2 #(
    .INIT(4'h2)) 
    int_ap_idle_i_1
       (.I0(Q[0]),
        .I1(ap_start),
        .O(ap_idle));
  FDRE int_ap_idle_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_idle),
        .Q(int_ap_idle),
        .R(ap_rst_n_inv));
  FDRE int_ap_ready_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(Q[2]),
        .Q(int_ap_ready),
        .R(ap_rst_n_inv));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'hFBF8)) 
    int_ap_start_i_1
       (.I0(int_auto_restart),
        .I1(Q[2]),
        .I2(int_ap_start0),
        .I3(ap_start),
        .O(int_ap_start_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000000200000)) 
    int_ap_start_i_2
       (.I0(s_axi_CNTRL_WDATA[0]),
        .I1(\waddr_reg_n_0_[2] ),
        .I2(ap_start_mask_i_3_n_0),
        .I3(\waddr_reg_n_0_[3] ),
        .I4(s_axi_CNTRL_WSTRB[0]),
        .I5(ap_start_mask),
        .O(int_ap_start0));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_start_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ap_start_i_1_n_0),
        .Q(ap_start),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT6 #(
    .INIT(64'hFFEFFFFF00200000)) 
    int_auto_restart_i_1
       (.I0(s_axi_CNTRL_WDATA[7]),
        .I1(\waddr_reg_n_0_[2] ),
        .I2(ap_start_mask_i_3_n_0),
        .I3(\waddr_reg_n_0_[3] ),
        .I4(s_axi_CNTRL_WSTRB[0]),
        .I5(int_auto_restart),
        .O(int_auto_restart_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_auto_restart_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_auto_restart_i_1_n_0),
        .Q(int_auto_restart),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[0]_i_1 
       (.I0(rtc_V[0]),
        .I1(first_V_preg[0]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[0]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[10]_i_1 
       (.I0(rtc_V[10]),
        .I1(first_V_preg[10]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[10]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[11]_i_1 
       (.I0(rtc_V[11]),
        .I1(first_V_preg[11]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[11]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[12]_i_1 
       (.I0(rtc_V[12]),
        .I1(first_V_preg[12]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[12]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[13]_i_1 
       (.I0(rtc_V[13]),
        .I1(first_V_preg[13]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[13]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[14]_i_1 
       (.I0(rtc_V[14]),
        .I1(first_V_preg[14]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[14]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[15]_i_1 
       (.I0(rtc_V[15]),
        .I1(first_V_preg[15]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[15]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[16]_i_1 
       (.I0(rtc_V[16]),
        .I1(first_V_preg[16]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[16]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[17]_i_1 
       (.I0(rtc_V[17]),
        .I1(first_V_preg[17]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[17]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[18]_i_1 
       (.I0(rtc_V[18]),
        .I1(first_V_preg[18]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[18]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[19]_i_1 
       (.I0(rtc_V[19]),
        .I1(first_V_preg[19]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[19]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[1]_i_1 
       (.I0(rtc_V[1]),
        .I1(first_V_preg[1]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[1]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[20]_i_1 
       (.I0(rtc_V[20]),
        .I1(first_V_preg[20]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[20]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[21]_i_1 
       (.I0(rtc_V[21]),
        .I1(first_V_preg[21]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[21]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[22]_i_1 
       (.I0(rtc_V[22]),
        .I1(first_V_preg[22]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[22]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[23]_i_1 
       (.I0(rtc_V[23]),
        .I1(first_V_preg[23]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[23]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[24]_i_1 
       (.I0(rtc_V[24]),
        .I1(first_V_preg[24]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[24]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[25]_i_1 
       (.I0(rtc_V[25]),
        .I1(first_V_preg[25]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[25]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[26]_i_1 
       (.I0(rtc_V[26]),
        .I1(first_V_preg[26]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[26]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[27]_i_1 
       (.I0(rtc_V[27]),
        .I1(first_V_preg[27]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[27]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[28]_i_1 
       (.I0(rtc_V[28]),
        .I1(first_V_preg[28]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[28]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[29]_i_1 
       (.I0(rtc_V[29]),
        .I1(first_V_preg[29]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[29]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[2]_i_1 
       (.I0(rtc_V[2]),
        .I1(first_V_preg[2]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[2]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[30]_i_1 
       (.I0(rtc_V[30]),
        .I1(first_V_preg[30]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[30]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[31]_i_1 
       (.I0(rtc_V[31]),
        .I1(first_V_preg[31]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[31]));
  LUT3 #(
    .INIT(8'h80)) 
    \int_first_V[31]_i_2 
       (.I0(tready_V),
        .I1(tvalid_V),
        .I2(tlast_V),
        .O(p_2_in));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[3]_i_1 
       (.I0(rtc_V[3]),
        .I1(first_V_preg[3]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[3]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[4]_i_1 
       (.I0(rtc_V[4]),
        .I1(first_V_preg[4]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[4]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[5]_i_1 
       (.I0(rtc_V[5]),
        .I1(first_V_preg[5]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[5]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[6]_i_1 
       (.I0(rtc_V[6]),
        .I1(first_V_preg[6]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[6]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[7]_i_1 
       (.I0(rtc_V[7]),
        .I1(first_V_preg[7]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[7]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[8]_i_1 
       (.I0(rtc_V[8]),
        .I1(first_V_preg[8]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[8]));
  LUT6 #(
    .INIT(64'hCACCCCCCCCCCCCCC)) 
    \int_first_V[9]_i_1 
       (.I0(rtc_V[9]),
        .I1(first_V_preg[9]),
        .I2(CO),
        .I3(Q[1]),
        .I4(p_2_in),
        .I5(p_s_fu_60),
        .O(first_V[9]));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[0]),
        .Q(int_first_V[0]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[10] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[10]),
        .Q(int_first_V[10]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[11] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[11]),
        .Q(int_first_V[11]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[12] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[12]),
        .Q(int_first_V[12]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[13] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[13]),
        .Q(int_first_V[13]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[14] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[14]),
        .Q(int_first_V[14]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[15] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[15]),
        .Q(int_first_V[15]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[16] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[16]),
        .Q(int_first_V[16]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[17] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[17]),
        .Q(int_first_V[17]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[18] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[18]),
        .Q(int_first_V[18]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[19] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[19]),
        .Q(int_first_V[19]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[1]),
        .Q(int_first_V[1]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[20] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[20]),
        .Q(int_first_V[20]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[21] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[21]),
        .Q(int_first_V[21]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[22] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[22]),
        .Q(int_first_V[22]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[23] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[23]),
        .Q(int_first_V[23]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[24] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[24]),
        .Q(int_first_V[24]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[25] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[25]),
        .Q(int_first_V[25]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[26] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[26]),
        .Q(int_first_V[26]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[27] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[27]),
        .Q(int_first_V[27]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[28] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[28]),
        .Q(int_first_V[28]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[29] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[29]),
        .Q(int_first_V[29]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[2]),
        .Q(int_first_V[2]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[30] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[30]),
        .Q(int_first_V[30]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[31] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[31]),
        .Q(int_first_V[31]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[3] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[3]),
        .Q(int_first_V[3]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[4] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[4]),
        .Q(int_first_V[4]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[5] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[5]),
        .Q(int_first_V[5]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[6] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[6]),
        .Q(int_first_V[6]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[7] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[7]),
        .Q(int_first_V[7]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[8] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[8]),
        .Q(int_first_V[8]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_first_V_reg[9] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(first_V[9]),
        .Q(int_first_V[9]),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT6 #(
    .INIT(64'hFBFFFFFF08000000)) 
    int_gie_i_1
       (.I0(s_axi_CNTRL_WDATA[0]),
        .I1(ap_start_mask_i_3_n_0),
        .I2(\waddr_reg_n_0_[3] ),
        .I3(\waddr_reg_n_0_[2] ),
        .I4(s_axi_CNTRL_WSTRB[0]),
        .I5(int_gie),
        .O(int_gie_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_gie_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_gie_i_1_n_0),
        .Q(int_gie),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT4 #(
    .INIT(16'h4000)) 
    \int_ier[1]_i_1 
       (.I0(\waddr_reg_n_0_[2] ),
        .I1(\waddr_reg_n_0_[3] ),
        .I2(ap_start_mask_i_3_n_0),
        .I3(s_axi_CNTRL_WSTRB[0]),
        .O(int_ier0));
  FDRE #(
    .INIT(1'b0)) 
    \int_ier_reg[0] 
       (.C(ap_clk),
        .CE(int_ier0),
        .D(s_axi_CNTRL_WDATA[0]),
        .Q(\int_ier_reg_n_0_[0] ),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_ier_reg[1] 
       (.C(ap_clk),
        .CE(int_ier0),
        .D(s_axi_CNTRL_WDATA[1]),
        .Q(p_0_in),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT5 #(
    .INIT(32'hF777F888)) 
    \int_isr[0]_i_1 
       (.I0(s_axi_CNTRL_WDATA[0]),
        .I1(int_isr_reg02_out),
        .I2(Q[2]),
        .I3(\int_ier_reg_n_0_[0] ),
        .I4(\int_isr_reg_n_0_[0] ),
        .O(\int_isr[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00008000)) 
    \int_isr[0]_i_2 
       (.I0(s_axi_CNTRL_WSTRB[0]),
        .I1(\waddr_reg_n_0_[2] ),
        .I2(ap_start_mask_i_3_n_0),
        .I3(\waddr_reg_n_0_[3] ),
        .I4(isr_mask),
        .O(int_isr_reg02_out));
  LUT5 #(
    .INIT(32'hF777F888)) 
    \int_isr[1]_i_1 
       (.I0(s_axi_CNTRL_WDATA[1]),
        .I1(int_isr_reg02_out),
        .I2(Q[2]),
        .I3(p_0_in),
        .I4(p_1_in),
        .O(\int_isr[1]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \int_isr_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_isr[0]_i_1_n_0 ),
        .Q(\int_isr_reg_n_0_[0] ),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_isr_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_isr[1]_i_1_n_0 ),
        .Q(p_1_in),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [0]),
        .Q(int_last_V[0]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[10] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [10]),
        .Q(int_last_V[10]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[11] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [11]),
        .Q(int_last_V[11]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[12] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [12]),
        .Q(int_last_V[12]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[13] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [13]),
        .Q(int_last_V[13]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[14] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [14]),
        .Q(int_last_V[14]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[15] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [15]),
        .Q(int_last_V[15]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[16] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [16]),
        .Q(int_last_V[16]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[17] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [17]),
        .Q(int_last_V[17]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[18] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [18]),
        .Q(int_last_V[18]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[19] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [19]),
        .Q(int_last_V[19]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [1]),
        .Q(int_last_V[1]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[20] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [20]),
        .Q(int_last_V[20]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[21] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [21]),
        .Q(int_last_V[21]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[22] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [22]),
        .Q(int_last_V[22]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[23] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [23]),
        .Q(int_last_V[23]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[24] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [24]),
        .Q(int_last_V[24]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[25] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [25]),
        .Q(int_last_V[25]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[26] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [26]),
        .Q(int_last_V[26]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[27] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [27]),
        .Q(int_last_V[27]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[28] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [28]),
        .Q(int_last_V[28]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[29] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [29]),
        .Q(int_last_V[29]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [2]),
        .Q(int_last_V[2]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[30] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [30]),
        .Q(int_last_V[30]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[31] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [31]),
        .Q(int_last_V[31]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[3] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [3]),
        .Q(int_last_V[3]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[4] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [4]),
        .Q(int_last_V[4]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[5] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [5]),
        .Q(int_last_V[5]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[6] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [6]),
        .Q(int_last_V[6]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[7] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [7]),
        .Q(int_last_V[7]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[8] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [8]),
        .Q(int_last_V[8]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_last_V_reg[9] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_last_V_reg[31]_0 [9]),
        .Q(int_last_V[9]),
        .R(ap_rst_n_cntrl_aclk_inv));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[0]_i_1 
       (.I0(s_axi_CNTRL_WDATA[0]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [0]),
        .O(\int_num_blocks_V[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[10]_i_1 
       (.I0(s_axi_CNTRL_WDATA[10]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [10]),
        .O(\int_num_blocks_V[10]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[11]_i_1 
       (.I0(s_axi_CNTRL_WDATA[11]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [11]),
        .O(\int_num_blocks_V[11]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[12]_i_1 
       (.I0(s_axi_CNTRL_WDATA[12]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [12]),
        .O(\int_num_blocks_V[12]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[13]_i_1 
       (.I0(s_axi_CNTRL_WDATA[13]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [13]),
        .O(\int_num_blocks_V[13]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[14]_i_1 
       (.I0(s_axi_CNTRL_WDATA[14]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [14]),
        .O(\int_num_blocks_V[14]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[15]_i_1 
       (.I0(s_axi_CNTRL_WDATA[15]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [15]),
        .O(\int_num_blocks_V[15]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[16]_i_1 
       (.I0(s_axi_CNTRL_WDATA[16]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [16]),
        .O(\int_num_blocks_V[16]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[17]_i_1 
       (.I0(s_axi_CNTRL_WDATA[17]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [17]),
        .O(\int_num_blocks_V[17]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[18]_i_1 
       (.I0(s_axi_CNTRL_WDATA[18]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [18]),
        .O(\int_num_blocks_V[18]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[19]_i_1 
       (.I0(s_axi_CNTRL_WDATA[19]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [19]),
        .O(\int_num_blocks_V[19]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[1]_i_1 
       (.I0(s_axi_CNTRL_WDATA[1]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [1]),
        .O(\int_num_blocks_V[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[20]_i_1 
       (.I0(s_axi_CNTRL_WDATA[20]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [20]),
        .O(\int_num_blocks_V[20]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[21]_i_1 
       (.I0(s_axi_CNTRL_WDATA[21]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [21]),
        .O(\int_num_blocks_V[21]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[22]_i_1 
       (.I0(s_axi_CNTRL_WDATA[22]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [22]),
        .O(\int_num_blocks_V[22]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[23]_i_1 
       (.I0(s_axi_CNTRL_WDATA[23]),
        .I1(s_axi_CNTRL_WSTRB[2]),
        .I2(\int_num_blocks_V_reg[31]_0 [23]),
        .O(\int_num_blocks_V[23]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[24]_i_1 
       (.I0(s_axi_CNTRL_WDATA[24]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [24]),
        .O(\int_num_blocks_V[24]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[25]_i_1 
       (.I0(s_axi_CNTRL_WDATA[25]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [25]),
        .O(\int_num_blocks_V[25]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[26]_i_1 
       (.I0(s_axi_CNTRL_WDATA[26]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [26]),
        .O(\int_num_blocks_V[26]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[27]_i_1 
       (.I0(s_axi_CNTRL_WDATA[27]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [27]),
        .O(\int_num_blocks_V[27]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[28]_i_1 
       (.I0(s_axi_CNTRL_WDATA[28]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [28]),
        .O(\int_num_blocks_V[28]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[29]_i_1 
       (.I0(s_axi_CNTRL_WDATA[29]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [29]),
        .O(\int_num_blocks_V[29]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[2]_i_1 
       (.I0(s_axi_CNTRL_WDATA[2]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [2]),
        .O(\int_num_blocks_V[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[30]_i_1 
       (.I0(s_axi_CNTRL_WDATA[30]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [30]),
        .O(\int_num_blocks_V[30]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0010)) 
    \int_num_blocks_V[31]_i_1 
       (.I0(\waddr_reg_n_0_[3] ),
        .I1(\waddr_reg_n_0_[2] ),
        .I2(\waddr_reg_n_0_[4] ),
        .I3(\int_num_blocks_V[31]_i_3_n_0 ),
        .O(\int_num_blocks_V[31]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[31]_i_2 
       (.I0(s_axi_CNTRL_WDATA[31]),
        .I1(s_axi_CNTRL_WSTRB[3]),
        .I2(\int_num_blocks_V_reg[31]_0 [31]),
        .O(\int_num_blocks_V[31]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFFFEFFF)) 
    \int_num_blocks_V[31]_i_3 
       (.I0(\waddr_reg_n_0_[0] ),
        .I1(\waddr_reg_n_0_[5] ),
        .I2(s_axi_CNTRL_WVALID),
        .I3(\FSM_onehot_wstate_reg[2]_0 ),
        .I4(\waddr_reg_n_0_[1] ),
        .O(\int_num_blocks_V[31]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[3]_i_1 
       (.I0(s_axi_CNTRL_WDATA[3]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [3]),
        .O(\int_num_blocks_V[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[4]_i_1 
       (.I0(s_axi_CNTRL_WDATA[4]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [4]),
        .O(\int_num_blocks_V[4]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[5]_i_1 
       (.I0(s_axi_CNTRL_WDATA[5]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [5]),
        .O(\int_num_blocks_V[5]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[6]_i_1 
       (.I0(s_axi_CNTRL_WDATA[6]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [6]),
        .O(\int_num_blocks_V[6]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[7]_i_1 
       (.I0(s_axi_CNTRL_WDATA[7]),
        .I1(s_axi_CNTRL_WSTRB[0]),
        .I2(\int_num_blocks_V_reg[31]_0 [7]),
        .O(\int_num_blocks_V[7]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[8]_i_1 
       (.I0(s_axi_CNTRL_WDATA[8]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [8]),
        .O(\int_num_blocks_V[8]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_num_blocks_V[9]_i_1 
       (.I0(s_axi_CNTRL_WDATA[9]),
        .I1(s_axi_CNTRL_WSTRB[1]),
        .I2(\int_num_blocks_V_reg[31]_0 [9]),
        .O(\int_num_blocks_V[9]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[0] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[0]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [0]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[10] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[10]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [10]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[11] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[11]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [11]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[12] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[12]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [12]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[13] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[13]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [13]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[14] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[14]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [14]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[15] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[15]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [15]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[16] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[16]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [16]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[17] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[17]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [17]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[18] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[18]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [18]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[19] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[19]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [19]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[1] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[1]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [1]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[20] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[20]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [20]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[21] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[21]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [21]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[22] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[22]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [22]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[23] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[23]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [23]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[24] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[24]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [24]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[25] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[25]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [25]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[26] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[26]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [26]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[27] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[27]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [27]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[28] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[28]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [28]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[29] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[29]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [29]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[2] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[2]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [2]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[30] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[30]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [30]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[31] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[31]_i_2_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [31]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[3] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[3]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [3]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[4] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[4]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [4]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[5] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[5]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [5]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[6] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[6]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [6]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[7] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[7]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [7]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[8] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[8]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [8]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_num_blocks_V_reg[9] 
       (.C(ap_clk),
        .CE(\int_num_blocks_V[31]_i_1_n_0 ),
        .D(\int_num_blocks_V[9]_i_1_n_0 ),
        .Q(\int_num_blocks_V_reg[31]_0 [9]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [0]),
        .Q(int_stalled_V[0]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[10] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [10]),
        .Q(int_stalled_V[10]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[11] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [11]),
        .Q(int_stalled_V[11]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[12] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [12]),
        .Q(int_stalled_V[12]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[13] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [13]),
        .Q(int_stalled_V[13]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[14] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [14]),
        .Q(int_stalled_V[14]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[15] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [15]),
        .Q(int_stalled_V[15]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[16] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [16]),
        .Q(int_stalled_V[16]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[17] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [17]),
        .Q(int_stalled_V[17]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[18] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [18]),
        .Q(int_stalled_V[18]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[19] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [19]),
        .Q(int_stalled_V[19]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [1]),
        .Q(int_stalled_V[1]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[20] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [20]),
        .Q(int_stalled_V[20]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[21] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [21]),
        .Q(int_stalled_V[21]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[22] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [22]),
        .Q(int_stalled_V[22]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[23] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [23]),
        .Q(int_stalled_V[23]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[24] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [24]),
        .Q(int_stalled_V[24]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[25] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [25]),
        .Q(int_stalled_V[25]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[26] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [26]),
        .Q(int_stalled_V[26]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[27] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [27]),
        .Q(int_stalled_V[27]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[28] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [28]),
        .Q(int_stalled_V[28]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[29] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [29]),
        .Q(int_stalled_V[29]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [2]),
        .Q(int_stalled_V[2]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[30] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [30]),
        .Q(int_stalled_V[30]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[31] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [31]),
        .Q(int_stalled_V[31]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[3] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [3]),
        .Q(int_stalled_V[3]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[4] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [4]),
        .Q(int_stalled_V[4]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[5] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [5]),
        .Q(int_stalled_V[5]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[6] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [6]),
        .Q(int_stalled_V[6]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[7] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [7]),
        .Q(int_stalled_V[7]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[8] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [8]),
        .Q(int_stalled_V[8]),
        .R(ap_rst_n_cntrl_aclk_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_stalled_V_reg[9] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_stalled_V_reg[31]_0 [9]),
        .Q(int_stalled_V[9]),
        .R(ap_rst_n_cntrl_aclk_inv));
  LUT3 #(
    .INIT(8'hA8)) 
    interrupt_INST_0
       (.I0(int_gie),
        .I1(p_1_in),
        .I2(\int_isr_reg_n_0_[0] ),
        .O(interrupt));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'h8000)) 
    isr_mask_i_1
       (.I0(\waddr_reg_n_0_[3] ),
        .I1(ap_start_mask_i_3_n_0),
        .I2(\waddr_reg_n_0_[2] ),
        .I3(s_axi_CNTRL_WSTRB[0]),
        .O(isr_toggle));
  FDRE isr_mask_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(isr_toggle),
        .Q(isr_mask),
        .R(ap_rst_n_cntrl_aclk_inv));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \num_blocks_V_read_reg_237[31]_i_1 
       (.I0(ap_start),
        .I1(Q[0]),
        .O(E));
  LUT6 #(
    .INIT(64'hF8F8F8F808F8F8F8)) 
    \p_s_fu_60[0]_i_1 
       (.I0(ap_start),
        .I1(Q[0]),
        .I2(p_s_fu_60),
        .I3(p_2_in),
        .I4(Q[1]),
        .I5(CO),
        .O(int_ap_start_reg_0));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h000000E2)) 
    \rdata[0]_i_1 
       (.I0(\rdata_reg[0]_i_2_n_0 ),
        .I1(s_axi_CNTRL_ARADDR[2]),
        .I2(\rdata[0]_i_3_n_0 ),
        .I3(s_axi_CNTRL_ARADDR[0]),
        .I4(s_axi_CNTRL_ARADDR[1]),
        .O(\rdata[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h11100010)) 
    \rdata[0]_i_3 
       (.I0(s_axi_CNTRL_ARADDR[5]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_gie),
        .I3(s_axi_CNTRL_ARADDR[3]),
        .I4(\int_isr_reg_n_0_[0] ),
        .O(\rdata[0]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[0]_i_4 
       (.I0(\int_num_blocks_V_reg[31]_0 [0]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_last_V[0]),
        .I3(s_axi_CNTRL_ARADDR[5]),
        .I4(ap_start),
        .O(\rdata[0]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[0]_i_5 
       (.I0(int_first_V[0]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_stalled_V[0]),
        .I3(s_axi_CNTRL_ARADDR[5]),
        .I4(\int_ier_reg_n_0_[0] ),
        .O(\rdata[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[10]_i_1 
       (.I0(int_first_V[10]),
        .I1(int_stalled_V[10]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [10]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[10]),
        .O(\rdata[10]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[11]_i_1 
       (.I0(int_first_V[11]),
        .I1(int_stalled_V[11]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [11]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[11]),
        .O(\rdata[11]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[12]_i_1 
       (.I0(int_first_V[12]),
        .I1(int_stalled_V[12]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [12]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[12]),
        .O(\rdata[12]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[13]_i_1 
       (.I0(int_first_V[13]),
        .I1(int_stalled_V[13]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [13]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[13]),
        .O(\rdata[13]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[14]_i_1 
       (.I0(int_first_V[14]),
        .I1(int_stalled_V[14]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [14]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[14]),
        .O(\rdata[14]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[15]_i_1 
       (.I0(int_first_V[15]),
        .I1(int_stalled_V[15]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [15]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[15]),
        .O(\rdata[15]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[16]_i_1 
       (.I0(int_first_V[16]),
        .I1(int_stalled_V[16]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [16]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[16]),
        .O(\rdata[16]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[17]_i_1 
       (.I0(int_first_V[17]),
        .I1(int_stalled_V[17]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [17]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[17]),
        .O(\rdata[17]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[18]_i_1 
       (.I0(int_first_V[18]),
        .I1(int_stalled_V[18]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [18]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[18]),
        .O(\rdata[18]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[19]_i_1 
       (.I0(int_first_V[19]),
        .I1(int_stalled_V[19]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [19]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[19]),
        .O(\rdata[19]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h000000002222E222)) 
    \rdata[1]_i_1 
       (.I0(\rdata_reg[1]_i_2_n_0 ),
        .I1(s_axi_CNTRL_ARADDR[2]),
        .I2(p_1_in),
        .I3(s_axi_CNTRL_ARADDR[3]),
        .I4(\rdata[1]_i_3_n_0 ),
        .I5(\rdata[1]_i_4_n_0 ),
        .O(\rdata[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \rdata[1]_i_3 
       (.I0(s_axi_CNTRL_ARADDR[5]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .O(\rdata[1]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \rdata[1]_i_4 
       (.I0(s_axi_CNTRL_ARADDR[1]),
        .I1(s_axi_CNTRL_ARADDR[0]),
        .O(\rdata[1]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[1]_i_5 
       (.I0(\int_num_blocks_V_reg[31]_0 [1]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_last_V[1]),
        .I3(s_axi_CNTRL_ARADDR[5]),
        .I4(int_ap_done),
        .O(\rdata[1]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[1]_i_6 
       (.I0(int_first_V[1]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_stalled_V[1]),
        .I3(s_axi_CNTRL_ARADDR[5]),
        .I4(p_0_in),
        .O(\rdata[1]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[20]_i_1 
       (.I0(int_first_V[20]),
        .I1(int_stalled_V[20]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [20]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[20]),
        .O(\rdata[20]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[21]_i_1 
       (.I0(int_first_V[21]),
        .I1(int_stalled_V[21]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [21]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[21]),
        .O(\rdata[21]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[22]_i_1 
       (.I0(int_first_V[22]),
        .I1(int_stalled_V[22]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [22]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[22]),
        .O(\rdata[22]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[23]_i_1 
       (.I0(int_first_V[23]),
        .I1(int_stalled_V[23]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [23]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[23]),
        .O(\rdata[23]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[24]_i_1 
       (.I0(int_first_V[24]),
        .I1(int_stalled_V[24]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [24]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[24]),
        .O(\rdata[24]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[25]_i_1 
       (.I0(int_first_V[25]),
        .I1(int_stalled_V[25]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [25]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[25]),
        .O(\rdata[25]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[26]_i_1 
       (.I0(int_first_V[26]),
        .I1(int_stalled_V[26]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [26]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[26]),
        .O(\rdata[26]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[27]_i_1 
       (.I0(int_first_V[27]),
        .I1(int_stalled_V[27]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [27]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[27]),
        .O(\rdata[27]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[28]_i_1 
       (.I0(int_first_V[28]),
        .I1(int_stalled_V[28]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [28]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[28]),
        .O(\rdata[28]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[29]_i_1 
       (.I0(int_first_V[29]),
        .I1(int_stalled_V[29]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [29]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[29]),
        .O(\rdata[29]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0101010000000100)) 
    \rdata[2]_i_1 
       (.I0(s_axi_CNTRL_ARADDR[1]),
        .I1(s_axi_CNTRL_ARADDR[0]),
        .I2(s_axi_CNTRL_ARADDR[2]),
        .I3(\rdata[2]_i_2_n_0 ),
        .I4(s_axi_CNTRL_ARADDR[3]),
        .I5(\rdata[2]_i_3_n_0 ),
        .O(rdata[2]));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[2]_i_2 
       (.I0(\int_num_blocks_V_reg[31]_0 [2]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_last_V[2]),
        .I3(s_axi_CNTRL_ARADDR[5]),
        .I4(int_ap_idle),
        .O(\rdata[2]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h3808)) 
    \rdata[2]_i_3 
       (.I0(int_first_V[2]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(s_axi_CNTRL_ARADDR[5]),
        .I3(int_stalled_V[2]),
        .O(\rdata[2]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[30]_i_1 
       (.I0(int_first_V[30]),
        .I1(int_stalled_V[30]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [30]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[30]),
        .O(\rdata[30]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAAAAAAA88A)) 
    \rdata[31]_i_1 
       (.I0(ar_hs),
        .I1(s_axi_CNTRL_ARADDR[1]),
        .I2(s_axi_CNTRL_ARADDR[5]),
        .I3(s_axi_CNTRL_ARADDR[4]),
        .I4(s_axi_CNTRL_ARADDR[0]),
        .I5(s_axi_CNTRL_ARADDR[2]),
        .O(\rdata[31]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \rdata[31]_i_2 
       (.I0(s_axi_CNTRL_ARVALID),
        .I1(\FSM_onehot_rstate_reg[1]_0 ),
        .O(ar_hs));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[31]_i_3 
       (.I0(int_first_V[31]),
        .I1(int_stalled_V[31]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [31]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[31]),
        .O(\rdata[31]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0101010000000100)) 
    \rdata[3]_i_1 
       (.I0(s_axi_CNTRL_ARADDR[1]),
        .I1(s_axi_CNTRL_ARADDR[0]),
        .I2(s_axi_CNTRL_ARADDR[2]),
        .I3(\rdata[3]_i_2_n_0 ),
        .I4(s_axi_CNTRL_ARADDR[3]),
        .I5(\rdata[3]_i_3_n_0 ),
        .O(rdata[3]));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[3]_i_2 
       (.I0(\int_num_blocks_V_reg[31]_0 [3]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_last_V[3]),
        .I3(s_axi_CNTRL_ARADDR[5]),
        .I4(int_ap_ready),
        .O(\rdata[3]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h3808)) 
    \rdata[3]_i_3 
       (.I0(int_first_V[3]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(s_axi_CNTRL_ARADDR[5]),
        .I3(int_stalled_V[3]),
        .O(\rdata[3]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[4]_i_1 
       (.I0(int_first_V[4]),
        .I1(int_stalled_V[4]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [4]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[4]),
        .O(\rdata[4]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[5]_i_1 
       (.I0(int_first_V[5]),
        .I1(int_stalled_V[5]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [5]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[5]),
        .O(\rdata[5]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[6]_i_1 
       (.I0(int_first_V[6]),
        .I1(int_stalled_V[6]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [6]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[6]),
        .O(\rdata[6]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0101010000000100)) 
    \rdata[7]_i_1 
       (.I0(s_axi_CNTRL_ARADDR[1]),
        .I1(s_axi_CNTRL_ARADDR[0]),
        .I2(s_axi_CNTRL_ARADDR[2]),
        .I3(\rdata[7]_i_2_n_0 ),
        .I4(s_axi_CNTRL_ARADDR[3]),
        .I5(\rdata[7]_i_3_n_0 ),
        .O(rdata[7]));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[7]_i_2 
       (.I0(\int_num_blocks_V_reg[31]_0 [7]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(int_last_V[7]),
        .I3(s_axi_CNTRL_ARADDR[5]),
        .I4(int_auto_restart),
        .O(\rdata[7]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h3808)) 
    \rdata[7]_i_3 
       (.I0(int_first_V[7]),
        .I1(s_axi_CNTRL_ARADDR[4]),
        .I2(s_axi_CNTRL_ARADDR[5]),
        .I3(int_stalled_V[7]),
        .O(\rdata[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[8]_i_1 
       (.I0(int_first_V[8]),
        .I1(int_stalled_V[8]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [8]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[8]),
        .O(\rdata[8]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[9]_i_1 
       (.I0(int_first_V[9]),
        .I1(int_stalled_V[9]),
        .I2(s_axi_CNTRL_ARADDR[3]),
        .I3(\int_num_blocks_V_reg[31]_0 [9]),
        .I4(s_axi_CNTRL_ARADDR[4]),
        .I5(int_last_V[9]),
        .O(\rdata[9]_i_1_n_0 ));
  FDRE \rdata_reg[0] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[0]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[0]),
        .R(1'b0));
  MUXF7 \rdata_reg[0]_i_2 
       (.I0(\rdata[0]_i_4_n_0 ),
        .I1(\rdata[0]_i_5_n_0 ),
        .O(\rdata_reg[0]_i_2_n_0 ),
        .S(s_axi_CNTRL_ARADDR[3]));
  FDRE \rdata_reg[10] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[10]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[10]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[11] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[11]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[11]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[12] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[12]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[12]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[13] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[13]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[13]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[14] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[14]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[14]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[15] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[15]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[15]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[16] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[16]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[16]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[17] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[17]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[17]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[18] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[18]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[18]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[19] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[19]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[19]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[1] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[1]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[1]),
        .R(1'b0));
  MUXF7 \rdata_reg[1]_i_2 
       (.I0(\rdata[1]_i_5_n_0 ),
        .I1(\rdata[1]_i_6_n_0 ),
        .O(\rdata_reg[1]_i_2_n_0 ),
        .S(s_axi_CNTRL_ARADDR[3]));
  FDRE \rdata_reg[20] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[20]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[20]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[21] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[21]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[21]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[22] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[22]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[22]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[23] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[23]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[23]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[24] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[24]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[24]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[25] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[25]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[25]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[26] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[26]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[26]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[27] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[27]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[27]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[28] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[28]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[28]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[29] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[29]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[29]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[2] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(rdata[2]),
        .Q(s_axi_CNTRL_RDATA[2]),
        .R(1'b0));
  FDRE \rdata_reg[30] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[30]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[30]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[31] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[31]_i_3_n_0 ),
        .Q(s_axi_CNTRL_RDATA[31]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[3] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(rdata[3]),
        .Q(s_axi_CNTRL_RDATA[3]),
        .R(1'b0));
  FDRE \rdata_reg[4] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[4]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[4]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[5] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[5]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[5]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[6] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[6]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[6]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[7] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(rdata[7]),
        .Q(s_axi_CNTRL_RDATA[7]),
        .R(1'b0));
  FDRE \rdata_reg[8] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[8]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[8]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[9] 
       (.C(cntrl_aclk),
        .CE(ar_hs),
        .D(\rdata[9]_i_1_n_0 ),
        .Q(s_axi_CNTRL_RDATA[9]),
        .R(\rdata[31]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAAAAA2AAAAAAA)) 
    \t_V_1_fu_68[0]_i_1 
       (.I0(E),
        .I1(tready_V),
        .I2(tvalid_V),
        .I3(tlast_V),
        .I4(Q[1]),
        .I5(CO),
        .O(t_V_1_fu_68));
  LUT4 #(
    .INIT(16'h8088)) 
    \t_V_reg_124[0]_i_1 
       (.I0(Q[0]),
        .I1(ap_start),
        .I2(CO),
        .I3(Q[1]),
        .O(\ap_CS_fsm_reg[0] ));
  LUT2 #(
    .INIT(4'h8)) 
    \waddr[5]_i_1 
       (.I0(s_axi_CNTRL_AWVALID),
        .I1(\FSM_onehot_wstate_reg[1]_0 ),
        .O(waddr));
  FDRE \waddr_reg[0] 
       (.C(cntrl_aclk),
        .CE(waddr),
        .D(s_axi_CNTRL_AWADDR[0]),
        .Q(\waddr_reg_n_0_[0] ),
        .R(1'b0));
  FDRE \waddr_reg[1] 
       (.C(cntrl_aclk),
        .CE(waddr),
        .D(s_axi_CNTRL_AWADDR[1]),
        .Q(\waddr_reg_n_0_[1] ),
        .R(1'b0));
  FDRE \waddr_reg[2] 
       (.C(cntrl_aclk),
        .CE(waddr),
        .D(s_axi_CNTRL_AWADDR[2]),
        .Q(\waddr_reg_n_0_[2] ),
        .R(1'b0));
  FDRE \waddr_reg[3] 
       (.C(cntrl_aclk),
        .CE(waddr),
        .D(s_axi_CNTRL_AWADDR[3]),
        .Q(\waddr_reg_n_0_[3] ),
        .R(1'b0));
  FDRE \waddr_reg[4] 
       (.C(cntrl_aclk),
        .CE(waddr),
        .D(s_axi_CNTRL_AWADDR[4]),
        .Q(\waddr_reg_n_0_[4] ),
        .R(1'b0));
  FDRE \waddr_reg[5] 
       (.C(cntrl_aclk),
        .CE(waddr),
        .D(s_axi_CNTRL_AWADDR[5]),
        .Q(\waddr_reg_n_0_[5] ),
        .R(1'b0));
endmodule

(* CHECK_LICENSE_TYPE = "project_1_dec_ip_mon_0,monitor,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "HLS" *) 
(* X_CORE_INFO = "monitor,Vivado 2020.1" *) (* hls_module = "yes" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
   (s_axi_CNTRL_AWADDR,
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
    rtc_V,
    tvalid_V,
    tready_V,
    tlast_V);
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWADDR" *) input [5:0]s_axi_CNTRL_AWADDR;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWVALID" *) input s_axi_CNTRL_AWVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWREADY" *) output s_axi_CNTRL_AWREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WDATA" *) input [31:0]s_axi_CNTRL_WDATA;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WSTRB" *) input [3:0]s_axi_CNTRL_WSTRB;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WVALID" *) input s_axi_CNTRL_WVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WREADY" *) output s_axi_CNTRL_WREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BRESP" *) output [1:0]s_axi_CNTRL_BRESP;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BVALID" *) output s_axi_CNTRL_BVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BREADY" *) input s_axi_CNTRL_BREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARADDR" *) input [5:0]s_axi_CNTRL_ARADDR;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARVALID" *) input s_axi_CNTRL_ARVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARREADY" *) output s_axi_CNTRL_ARREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RDATA" *) output [31:0]s_axi_CNTRL_RDATA;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RRESP" *) output [1:0]s_axi_CNTRL_RRESP;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RVALID" *) output s_axi_CNTRL_RVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RREADY" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_CNTRL, ADDR_WIDTH 6, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input s_axi_CNTRL_RREADY;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_RESET ap_rst_n, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input ap_clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0" *) input ap_rst_n;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {INTERRUPT {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, PortWidth 1" *) output interrupt;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 cntrl_aclk CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME cntrl_aclk, ASSOCIATED_BUSIF s_axi_CNTRL, ASSOCIATED_RESET ap_rst_n_cntrl_aclk, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input cntrl_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n_cntrl_aclk RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n_cntrl_aclk, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0" *) input ap_rst_n_cntrl_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 rtc_V DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME rtc_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}" *) input [31:0]rtc_V;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 tvalid_V DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME tvalid_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}" *) input [0:0]tvalid_V;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 tready_V DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME tready_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}" *) input [0:0]tready_V;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 tlast_V DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME tlast_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}" *) input [0:0]tlast_V;

  wire ap_clk;
  wire ap_rst_n;
  wire ap_rst_n_cntrl_aclk;
  wire cntrl_aclk;
  wire interrupt;
  wire [31:0]rtc_V;
  wire [5:0]s_axi_CNTRL_ARADDR;
  wire s_axi_CNTRL_ARREADY;
  wire s_axi_CNTRL_ARVALID;
  wire [5:0]s_axi_CNTRL_AWADDR;
  wire s_axi_CNTRL_AWREADY;
  wire s_axi_CNTRL_AWVALID;
  wire s_axi_CNTRL_BREADY;
  wire [1:0]s_axi_CNTRL_BRESP;
  wire s_axi_CNTRL_BVALID;
  wire [31:0]s_axi_CNTRL_RDATA;
  wire s_axi_CNTRL_RREADY;
  wire [1:0]s_axi_CNTRL_RRESP;
  wire s_axi_CNTRL_RVALID;
  wire [31:0]s_axi_CNTRL_WDATA;
  wire s_axi_CNTRL_WREADY;
  wire [3:0]s_axi_CNTRL_WSTRB;
  wire s_axi_CNTRL_WVALID;
  wire [0:0]tlast_V;
  wire [0:0]tready_V;
  wire [0:0]tvalid_V;

  (* C_S_AXI_CNTRL_ADDR_WIDTH = "6" *) 
  (* C_S_AXI_CNTRL_DATA_WIDTH = "32" *) 
  (* C_S_AXI_CNTRL_WSTRB_WIDTH = "4" *) 
  (* C_S_AXI_DATA_WIDTH = "32" *) 
  (* C_S_AXI_WSTRB_WIDTH = "4" *) 
  (* ap_ST_fsm_state1 = "3'b001" *) 
  (* ap_ST_fsm_state2 = "3'b010" *) 
  (* ap_ST_fsm_state3 = "3'b100" *) 
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_monitor inst
       (.ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_rst_n_cntrl_aclk(ap_rst_n_cntrl_aclk),
        .cntrl_aclk(cntrl_aclk),
        .interrupt(interrupt),
        .rtc_V(rtc_V),
        .s_axi_CNTRL_ARADDR(s_axi_CNTRL_ARADDR),
        .s_axi_CNTRL_ARREADY(s_axi_CNTRL_ARREADY),
        .s_axi_CNTRL_ARVALID(s_axi_CNTRL_ARVALID),
        .s_axi_CNTRL_AWADDR(s_axi_CNTRL_AWADDR),
        .s_axi_CNTRL_AWREADY(s_axi_CNTRL_AWREADY),
        .s_axi_CNTRL_AWVALID(s_axi_CNTRL_AWVALID),
        .s_axi_CNTRL_BREADY(s_axi_CNTRL_BREADY),
        .s_axi_CNTRL_BRESP(s_axi_CNTRL_BRESP),
        .s_axi_CNTRL_BVALID(s_axi_CNTRL_BVALID),
        .s_axi_CNTRL_RDATA(s_axi_CNTRL_RDATA),
        .s_axi_CNTRL_RREADY(s_axi_CNTRL_RREADY),
        .s_axi_CNTRL_RRESP(s_axi_CNTRL_RRESP),
        .s_axi_CNTRL_RVALID(s_axi_CNTRL_RVALID),
        .s_axi_CNTRL_WDATA(s_axi_CNTRL_WDATA),
        .s_axi_CNTRL_WREADY(s_axi_CNTRL_WREADY),
        .s_axi_CNTRL_WSTRB(s_axi_CNTRL_WSTRB),
        .s_axi_CNTRL_WVALID(s_axi_CNTRL_WVALID),
        .tlast_V(tlast_V),
        .tready_V(tready_V),
        .tvalid_V(tvalid_V));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
