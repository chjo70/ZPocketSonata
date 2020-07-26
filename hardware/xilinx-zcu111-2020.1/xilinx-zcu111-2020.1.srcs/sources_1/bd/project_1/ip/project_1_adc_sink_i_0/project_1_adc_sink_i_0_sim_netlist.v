// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:57 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim
//               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_adc_sink_i_0/project_1_adc_sink_i_0_sim_netlist.v
// Design      : project_1_adc_sink_i_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "project_1_adc_sink_i_0,exdes_rfadc_data_sink,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "module_ref" *) 
(* X_CORE_INFO = "exdes_rfadc_data_sink,Vivado 2020.1" *) 
(* NotValidForBitStream *)
module project_1_adc_sink_i_0
   (s_axi_awaddr,
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
    s00_tdata,
    s00_tvalid,
    s00_tready,
    s0_axis_clock,
    error_flag,
    done_flag,
    s_axi_aclk,
    s_axi_aresetn);
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWADDR" *) input [17:0]s_axi_awaddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWVALID" *) input s_axi_awvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWREADY" *) output s_axi_awready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WDATA" *) input [31:0]s_axi_wdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WVALID" *) input s_axi_wvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WREADY" *) output s_axi_wready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WSTRB" *) input [3:0]s_axi_wstrb;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BRESP" *) output [1:0]s_axi_bresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BVALID" *) output s_axi_bvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BREADY" *) input s_axi_bready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARADDR" *) input [17:0]s_axi_araddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARVALID" *) input s_axi_arvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARREADY" *) output s_axi_arready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RDATA" *) output [31:0]s_axi_rdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RRESP" *) output [1:0]s_axi_rresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RVALID" *) output s_axi_rvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RREADY" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 99999001, ID_WIDTH 0, ADDR_WIDTH 18, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN project_1_PS_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input s_axi_rready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 s00 TDATA" *) input [127:0]s00_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 s00 TVALID" *) input s00_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 s00 TREADY" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s00, TDATA_NUM_BYTES 16, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 100000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0" *) output s00_tready;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s0_axis_clock CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s0_axis_clock, ASSOCIATED_BUSIF s00, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input s0_axis_clock;
  output error_flag;
  output done_flag;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s_axi_aclk CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_aclk, ASSOCIATED_BUSIF s_axi, ASSOCIATED_RESET s_axi_aresetn, FREQ_HZ 99999001, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN project_1_PS_0_0_pl_clk0, INSERT_VIP 0" *) input s_axi_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 s_axi_aresetn RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_aresetn, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input s_axi_aresetn;

  wire \<const0> ;
  wire done_flag;
  wire error_flag;
  wire [127:0]s00_tdata;
  wire s00_tready;
  wire s0_axis_clock;
  wire s_axi_aclk;
  wire [17:0]s_axi_araddr;
  wire s_axi_aresetn;
  wire s_axi_arready;
  wire s_axi_arvalid;
  wire [17:0]s_axi_awaddr;
  wire s_axi_awready;
  wire s_axi_awvalid;
  wire s_axi_bready;
  wire [1:1]\^s_axi_bresp ;
  wire s_axi_bvalid;
  wire [15:0]\^s_axi_rdata ;
  wire s_axi_rready;
  wire [1:1]\^s_axi_rresp ;
  wire s_axi_rvalid;
  wire [31:0]s_axi_wdata;
  wire s_axi_wready;
  wire s_axi_wvalid;

  assign s_axi_bresp[1] = \^s_axi_bresp [1];
  assign s_axi_bresp[0] = \<const0> ;
  assign s_axi_rdata[31] = \<const0> ;
  assign s_axi_rdata[30] = \<const0> ;
  assign s_axi_rdata[29] = \<const0> ;
  assign s_axi_rdata[28] = \<const0> ;
  assign s_axi_rdata[27] = \<const0> ;
  assign s_axi_rdata[26] = \<const0> ;
  assign s_axi_rdata[25] = \<const0> ;
  assign s_axi_rdata[24] = \<const0> ;
  assign s_axi_rdata[23] = \<const0> ;
  assign s_axi_rdata[22] = \<const0> ;
  assign s_axi_rdata[21] = \<const0> ;
  assign s_axi_rdata[20] = \<const0> ;
  assign s_axi_rdata[19] = \<const0> ;
  assign s_axi_rdata[18] = \<const0> ;
  assign s_axi_rdata[17] = \<const0> ;
  assign s_axi_rdata[16] = \<const0> ;
  assign s_axi_rdata[15:0] = \^s_axi_rdata [15:0];
  assign s_axi_rresp[1] = \^s_axi_rresp [1];
  assign s_axi_rresp[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  project_1_adc_sink_i_0_exdes_rfadc_data_sink inst
       (.axi_awready_reg(s_axi_awready),
        .axi_bvalid_reg(s_axi_bvalid),
        .axi_rvalid_reg(s_axi_rvalid),
        .done_flag(done_flag),
        .error_flag(error_flag),
        .s00_tdata(s00_tdata),
        .s00_tready(s00_tready),
        .s0_axis_clock(s0_axis_clock),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_araddr(s_axi_araddr[17:2]),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_arready(s_axi_arready),
        .s_axi_arvalid(s_axi_arvalid),
        .s_axi_awaddr(s_axi_awaddr[17:2]),
        .s_axi_awvalid(s_axi_awvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_bresp(\^s_axi_bresp ),
        .s_axi_rdata(\^s_axi_rdata ),
        .s_axi_rready(s_axi_rready),
        .s_axi_rresp(\^s_axi_rresp ),
        .s_axi_wdata(s_axi_wdata[11:0]),
        .s_axi_wready(s_axi_wready),
        .s_axi_wvalid(s_axi_wvalid));
endmodule

(* ORIG_REF_NAME = "adc0_rfadc_exdes_ctrl_axi" *) 
module project_1_adc_sink_i_0_adc0_rfadc_exdes_ctrl_axi
   (slv_wren_done_pulse,
    slv_rden_r,
    adc00_ds_pulse_control_0,
    \adc03_ds_control_0_reg[1]_0 ,
    slv_rden_r_reg_0,
    \adc03_ds_inc_0_reg[11]_0 ,
    \adc03_ds_inc_0_reg[8]_0 ,
    \adc01_ds_inc_0_reg[8]_0 ,
    \adc02_ds_inc_0_reg[8]_0 ,
    \adc00_ds_inc_0_reg[8]_0 ,
    \adc03_ds_inc_0_reg[10]_0 ,
    \adc03_ds_inc_0_reg[9]_0 ,
    \adc03_ds_enable_0_reg[7]_0 ,
    \adc01_ds_inc_0_reg[7]_0 ,
    \adc01_ds_inc_0_reg[6]_0 ,
    \adc03_ds_enable_0_reg[6]_0 ,
    \adc01_ds_inc_0_reg[5]_0 ,
    \adc03_ds_enable_0_reg[5]_0 ,
    \adc01_ds_inc_0_reg[4]_0 ,
    \adc03_ds_enable_0_reg[4]_0 ,
    \adc03_ds_enable_0_reg[3]_0 ,
    \adc01_ds_inc_0_reg[3]_0 ,
    \adc01_ds_inc_0_reg[2]_0 ,
    \adc03_ds_enable_0_reg[2]_0 ,
    \adc01_ds_inc_0_reg[1]_0 ,
    \adc03_ds_enable_0_reg[1]_0 ,
    \adc01_ds_type_0_reg[1]_0 ,
    \adc01_ds_type_0_reg[3]_0 ,
    \adc02_ds_type_0_reg[3]_0 ,
    \adc03_ds_type_0_reg[3]_0 ,
    \adc03_ds_control_0_reg[0]_0 ,
    \adc00_ds_control_0_reg[1]_0 ,
    \adc01_ds_inc_0_reg[0]_0 ,
    \adc03_ds_enable_0_reg[0]_0 ,
    s00_tready,
    \adc00_ds_type_0_reg[3]_0 ,
    slv_rdata,
    s0_axis_clock,
    s_axi_aclk,
    p_0_in,
    adc0slv_rden,
    \adc03_ds_enable_0_reg[7]_1 ,
    \adc00_ds_type_0_reg[3]_1 ,
    \adc03_ds_control_0_reg[1]_1 ,
    Q,
    \slv_rdata_reg[1]_0 ,
    \axi_rresp[1]_i_2 ,
    adc_ds_slv_rden,
    \adc00_ds_enable_0_reg[0]_0 ,
    \adc03_ds_type_0_reg[0]_0 ,
    \adc01_ds_control_0_reg[0]_0 ,
    \adc01_ds_type_0_reg[0]_0 ,
    \adc01_ds_enable_0_reg[0]_0 ,
    \adc00_ds_control_0_reg[0]_0 ,
    \adc00_ds_inc_0_reg[0]_0 ,
    \adc03_ds_inc_0_reg[0]_0 ,
    \adc02_ds_type_0_reg[0]_0 ,
    \adc02_ds_inc_0_reg[0]_0 ,
    \adc02_ds_enable_0_reg[0]_0 ,
    \adc02_ds_control_0_reg[0]_0 ,
    \adc01_ds_inc_0_reg[0]_1 ,
    dest_rst,
    adc00_ds_pulse_control_0_reg_0,
    adc00_ds_pulse_control_0_reg_1,
    s_axi_wvalid,
    adc0axi_map_wready,
    E,
    s_axi_wdata,
    s_axi_aresetn,
    D,
    \slv_rdata_reg[15]_0 ,
    \slv_rdata_reg[14]_0 ,
    \slv_rdata_reg[13]_0 ,
    \slv_rdata_reg[12]_0 ,
    \slv_rdata_reg[7]_0 ,
    \slv_rdata_reg[6]_0 ,
    \slv_rdata_reg[5]_0 ,
    \slv_rdata_reg[4]_0 ,
    \slv_rdata_reg[3]_0 ,
    \slv_rdata_reg[2]_0 ,
    \slv_rdata_reg[12]_1 );
  output slv_wren_done_pulse;
  output slv_rden_r;
  output adc00_ds_pulse_control_0;
  output \adc03_ds_control_0_reg[1]_0 ;
  output slv_rden_r_reg_0;
  output \adc03_ds_inc_0_reg[11]_0 ;
  output [0:0]\adc03_ds_inc_0_reg[8]_0 ;
  output [0:0]\adc01_ds_inc_0_reg[8]_0 ;
  output [0:0]\adc02_ds_inc_0_reg[8]_0 ;
  output [8:0]\adc00_ds_inc_0_reg[8]_0 ;
  output \adc03_ds_inc_0_reg[10]_0 ;
  output \adc03_ds_inc_0_reg[9]_0 ;
  output \adc03_ds_enable_0_reg[7]_0 ;
  output \adc01_ds_inc_0_reg[7]_0 ;
  output \adc01_ds_inc_0_reg[6]_0 ;
  output \adc03_ds_enable_0_reg[6]_0 ;
  output \adc01_ds_inc_0_reg[5]_0 ;
  output \adc03_ds_enable_0_reg[5]_0 ;
  output \adc01_ds_inc_0_reg[4]_0 ;
  output \adc03_ds_enable_0_reg[4]_0 ;
  output \adc03_ds_enable_0_reg[3]_0 ;
  output \adc01_ds_inc_0_reg[3]_0 ;
  output \adc01_ds_inc_0_reg[2]_0 ;
  output \adc03_ds_enable_0_reg[2]_0 ;
  output \adc01_ds_inc_0_reg[1]_0 ;
  output \adc03_ds_enable_0_reg[1]_0 ;
  output \adc01_ds_type_0_reg[1]_0 ;
  output [2:0]\adc01_ds_type_0_reg[3]_0 ;
  output [2:0]\adc02_ds_type_0_reg[3]_0 ;
  output [2:0]\adc03_ds_type_0_reg[3]_0 ;
  output \adc03_ds_control_0_reg[0]_0 ;
  output [0:0]\adc00_ds_control_0_reg[1]_0 ;
  output \adc01_ds_inc_0_reg[0]_0 ;
  output \adc03_ds_enable_0_reg[0]_0 ;
  output s00_tready;
  output [3:0]\adc00_ds_type_0_reg[3]_0 ;
  output [15:0]slv_rdata;
  input s0_axis_clock;
  input s_axi_aclk;
  input p_0_in;
  input adc0slv_rden;
  input \adc03_ds_enable_0_reg[7]_1 ;
  input \adc00_ds_type_0_reg[3]_1 ;
  input \adc03_ds_control_0_reg[1]_1 ;
  input [5:0]Q;
  input \slv_rdata_reg[1]_0 ;
  input [0:0]\axi_rresp[1]_i_2 ;
  input adc_ds_slv_rden;
  input \adc00_ds_enable_0_reg[0]_0 ;
  input \adc03_ds_type_0_reg[0]_0 ;
  input \adc01_ds_control_0_reg[0]_0 ;
  input \adc01_ds_type_0_reg[0]_0 ;
  input \adc01_ds_enable_0_reg[0]_0 ;
  input \adc00_ds_control_0_reg[0]_0 ;
  input \adc00_ds_inc_0_reg[0]_0 ;
  input \adc03_ds_inc_0_reg[0]_0 ;
  input \adc02_ds_type_0_reg[0]_0 ;
  input \adc02_ds_inc_0_reg[0]_0 ;
  input \adc02_ds_enable_0_reg[0]_0 ;
  input \adc02_ds_control_0_reg[0]_0 ;
  input \adc01_ds_inc_0_reg[0]_1 ;
  input dest_rst;
  input adc00_ds_pulse_control_0_reg_0;
  input adc00_ds_pulse_control_0_reg_1;
  input s_axi_wvalid;
  input adc0axi_map_wready;
  input [0:0]E;
  input [11:0]s_axi_wdata;
  input s_axi_aresetn;
  input [5:0]D;
  input \slv_rdata_reg[15]_0 ;
  input \slv_rdata_reg[14]_0 ;
  input \slv_rdata_reg[13]_0 ;
  input \slv_rdata_reg[12]_0 ;
  input \slv_rdata_reg[7]_0 ;
  input \slv_rdata_reg[6]_0 ;
  input \slv_rdata_reg[5]_0 ;
  input \slv_rdata_reg[4]_0 ;
  input \slv_rdata_reg[3]_0 ;
  input \slv_rdata_reg[2]_0 ;
  input \slv_rdata_reg[12]_1 ;

  wire [5:0]D;
  wire [0:0]E;
  wire [5:0]Q;
  wire [0:0]adc00_ds_control_0;
  wire \adc00_ds_control_0_reg[0]_0 ;
  wire [0:0]\adc00_ds_control_0_reg[1]_0 ;
  wire [7:1]adc00_ds_enable_0;
  wire \adc00_ds_enable_0_reg[0]_0 ;
  wire [11:9]adc00_ds_inc_0;
  wire \adc00_ds_inc_0_reg[0]_0 ;
  wire [8:0]\adc00_ds_inc_0_reg[8]_0 ;
  wire adc00_ds_pulse_control_0;
  wire adc00_ds_pulse_control_0_reg_0;
  wire adc00_ds_pulse_control_0_reg_1;
  wire [3:0]\adc00_ds_type_0_reg[3]_0 ;
  wire \adc00_ds_type_0_reg[3]_1 ;
  wire [1:0]adc01_ds_control_0;
  wire \adc01_ds_control_0_reg[0]_0 ;
  wire [7:0]adc01_ds_enable_0;
  wire \adc01_ds_enable_0_reg[0]_0 ;
  wire [11:0]adc01_ds_inc_0;
  wire \adc01_ds_inc_0_reg[0]_0 ;
  wire \adc01_ds_inc_0_reg[0]_1 ;
  wire \adc01_ds_inc_0_reg[1]_0 ;
  wire \adc01_ds_inc_0_reg[2]_0 ;
  wire \adc01_ds_inc_0_reg[3]_0 ;
  wire \adc01_ds_inc_0_reg[4]_0 ;
  wire \adc01_ds_inc_0_reg[5]_0 ;
  wire \adc01_ds_inc_0_reg[6]_0 ;
  wire \adc01_ds_inc_0_reg[7]_0 ;
  wire [0:0]\adc01_ds_inc_0_reg[8]_0 ;
  wire [1:1]adc01_ds_type_0;
  wire \adc01_ds_type_0_reg[0]_0 ;
  wire \adc01_ds_type_0_reg[1]_0 ;
  wire [2:0]\adc01_ds_type_0_reg[3]_0 ;
  wire [1:0]adc02_ds_control_0;
  wire \adc02_ds_control_0_reg[0]_0 ;
  wire [7:0]adc02_ds_enable_0;
  wire \adc02_ds_enable_0_reg[0]_0 ;
  wire [11:0]adc02_ds_inc_0;
  wire \adc02_ds_inc_0_reg[0]_0 ;
  wire [0:0]\adc02_ds_inc_0_reg[8]_0 ;
  wire [1:1]adc02_ds_type_0;
  wire \adc02_ds_type_0_reg[0]_0 ;
  wire [2:0]\adc02_ds_type_0_reg[3]_0 ;
  wire [1:0]adc03_ds_control_0;
  wire \adc03_ds_control_0_reg[0]_0 ;
  wire \adc03_ds_control_0_reg[1]_0 ;
  wire \adc03_ds_control_0_reg[1]_1 ;
  wire [7:0]adc03_ds_enable_0;
  wire \adc03_ds_enable_0_reg[0]_0 ;
  wire \adc03_ds_enable_0_reg[1]_0 ;
  wire \adc03_ds_enable_0_reg[2]_0 ;
  wire \adc03_ds_enable_0_reg[3]_0 ;
  wire \adc03_ds_enable_0_reg[4]_0 ;
  wire \adc03_ds_enable_0_reg[5]_0 ;
  wire \adc03_ds_enable_0_reg[6]_0 ;
  wire \adc03_ds_enable_0_reg[7]_0 ;
  wire \adc03_ds_enable_0_reg[7]_1 ;
  wire [11:0]adc03_ds_inc_0;
  wire \adc03_ds_inc_0_reg[0]_0 ;
  wire \adc03_ds_inc_0_reg[10]_0 ;
  wire \adc03_ds_inc_0_reg[11]_0 ;
  wire [0:0]\adc03_ds_inc_0_reg[8]_0 ;
  wire \adc03_ds_inc_0_reg[9]_0 ;
  wire [1:1]adc03_ds_type_0;
  wire \adc03_ds_type_0_reg[0]_0 ;
  wire [2:0]\adc03_ds_type_0_reg[3]_0 ;
  wire adc0axi_map_wready;
  wire adc0slv_rden;
  wire adc_ds_slv_rden;
  wire [0:0]\axi_rresp[1]_i_2 ;
  wire clk2clk_handshake_pulse_gen_i_n_1;
  wire clk2clk_handshake_pulse_gen_i_n_10;
  wire clk2clk_handshake_pulse_gen_i_n_11;
  wire clk2clk_handshake_pulse_gen_i_n_12;
  wire clk2clk_handshake_pulse_gen_i_n_13;
  wire clk2clk_handshake_pulse_gen_i_n_14;
  wire clk2clk_handshake_pulse_gen_i_n_15;
  wire clk2clk_handshake_pulse_gen_i_n_16;
  wire clk2clk_handshake_pulse_gen_i_n_17;
  wire clk2clk_handshake_pulse_gen_i_n_18;
  wire clk2clk_handshake_pulse_gen_i_n_19;
  wire clk2clk_handshake_pulse_gen_i_n_2;
  wire clk2clk_handshake_pulse_gen_i_n_20;
  wire clk2clk_handshake_pulse_gen_i_n_3;
  wire clk2clk_handshake_pulse_gen_i_n_4;
  wire clk2clk_handshake_pulse_gen_i_n_6;
  wire clk2clk_handshake_pulse_gen_i_n_7;
  wire clk2clk_handshake_pulse_gen_i_n_8;
  wire clk2clk_handshake_pulse_gen_i_n_9;
  wire dest_rst;
  wire p_0_in;
  wire s00_tready;
  wire s0_axis_clock;
  wire s_axi_aclk;
  wire s_axi_aresetn;
  wire [11:0]s_axi_wdata;
  wire s_axi_wvalid;
  wire slv_access_valid_hold;
  wire [15:0]slv_rdata;
  wire \slv_rdata[15]_i_1_n_0 ;
  wire \slv_rdata[7]_i_1_n_0 ;
  wire \slv_rdata_reg[12]_0 ;
  wire \slv_rdata_reg[12]_1 ;
  wire \slv_rdata_reg[13]_0 ;
  wire \slv_rdata_reg[14]_0 ;
  wire \slv_rdata_reg[15]_0 ;
  wire \slv_rdata_reg[1]_0 ;
  wire \slv_rdata_reg[2]_0 ;
  wire \slv_rdata_reg[3]_0 ;
  wire \slv_rdata_reg[4]_0 ;
  wire \slv_rdata_reg[5]_0 ;
  wire \slv_rdata_reg[6]_0 ;
  wire \slv_rdata_reg[7]_0 ;
  wire slv_rden_r;
  wire slv_rden_r_reg_0;
  wire \slv_wdata_r_internal_reg_n_0_[0] ;
  wire \slv_wdata_r_internal_reg_n_0_[10] ;
  wire \slv_wdata_r_internal_reg_n_0_[11] ;
  wire \slv_wdata_r_internal_reg_n_0_[1] ;
  wire \slv_wdata_r_internal_reg_n_0_[2] ;
  wire \slv_wdata_r_internal_reg_n_0_[3] ;
  wire \slv_wdata_r_internal_reg_n_0_[4] ;
  wire \slv_wdata_r_internal_reg_n_0_[5] ;
  wire \slv_wdata_r_internal_reg_n_0_[6] ;
  wire \slv_wdata_r_internal_reg_n_0_[7] ;
  wire \slv_wdata_r_internal_reg_n_0_[8] ;
  wire \slv_wdata_r_internal_reg_n_0_[9] ;
  wire slv_wren_done_pulse;

  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_control_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc00_ds_control_0),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_control_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(\adc00_ds_control_0_reg[1]_0 ),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(s00_tready),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc00_ds_enable_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc00_ds_enable_0[2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc00_ds_enable_0[3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc00_ds_enable_0[4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc00_ds_enable_0[5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc00_ds_enable_0[6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_enable_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc00_ds_enable_0[7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[10] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc00_ds_inc_0[10]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[11] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc00_ds_inc_0[11]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[8] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(\adc00_ds_inc_0_reg[8]_0 [8]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_inc_0_reg[9] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc00_ds_inc_0[9]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    adc00_ds_pulse_control_0_reg
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(clk2clk_handshake_pulse_gen_i_n_19),
        .Q(adc00_ds_pulse_control_0),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_type_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(\adc00_ds_type_0_reg[3]_0 [0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_type_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(\adc00_ds_type_0_reg[3]_0 [1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_type_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc00_ds_type_0_reg[3]_0 [2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc00_ds_type_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc00_ds_type_0_reg[3]_0 [3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_control_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc01_ds_control_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_control_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc01_ds_control_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc01_ds_enable_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc01_ds_enable_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc01_ds_enable_0[2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc01_ds_enable_0[3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc01_ds_enable_0[4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc01_ds_enable_0[5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc01_ds_enable_0[6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_enable_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc01_ds_enable_0[7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc01_ds_inc_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[10] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc01_ds_inc_0[10]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[11] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc01_ds_inc_0[11]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc01_ds_inc_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc01_ds_inc_0[2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc01_ds_inc_0[3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc01_ds_inc_0[4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc01_ds_inc_0[5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc01_ds_inc_0[6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc01_ds_inc_0[7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[8] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(\adc01_ds_inc_0_reg[8]_0 ),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_inc_0_reg[9] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_18),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc01_ds_inc_0[9]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_type_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(\adc01_ds_type_0_reg[3]_0 [0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_type_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc01_ds_type_0),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_type_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc01_ds_type_0_reg[3]_0 [1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc01_ds_type_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc01_ds_type_0_reg[3]_0 [2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_control_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc02_ds_control_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_control_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc02_ds_control_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc02_ds_enable_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc02_ds_enable_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc02_ds_enable_0[2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc02_ds_enable_0[3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc02_ds_enable_0[4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc02_ds_enable_0[5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc02_ds_enable_0[6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_enable_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc02_ds_enable_0[7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc02_ds_inc_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[10] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc02_ds_inc_0[10]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[11] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc02_ds_inc_0[11]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc02_ds_inc_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc02_ds_inc_0[2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc02_ds_inc_0[3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc02_ds_inc_0[4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc02_ds_inc_0[5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc02_ds_inc_0[6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc02_ds_inc_0[7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[8] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(\adc02_ds_inc_0_reg[8]_0 ),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_inc_0_reg[9] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc02_ds_inc_0[9]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_type_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(\adc02_ds_type_0_reg[3]_0 [0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_type_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc02_ds_type_0),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_type_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc02_ds_type_0_reg[3]_0 [1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc02_ds_type_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc02_ds_type_0_reg[3]_0 [2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_control_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc03_ds_control_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_control_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc03_ds_control_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc03_ds_enable_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc03_ds_enable_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc03_ds_enable_0[2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc03_ds_enable_0[3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc03_ds_enable_0[4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc03_ds_enable_0[5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc03_ds_enable_0[6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_enable_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc03_ds_enable_0[7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc03_ds_inc_0[0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[10] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc03_ds_inc_0[10]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[11] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc03_ds_inc_0[11]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc03_ds_inc_0[1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc03_ds_inc_0[2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc03_ds_inc_0[3]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[4] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc03_ds_inc_0[4]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[5] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc03_ds_inc_0[5]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[6] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc03_ds_inc_0[6]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[7] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc03_ds_inc_0[7]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[8] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(\adc03_ds_inc_0_reg[8]_0 ),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_inc_0_reg[9] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc03_ds_inc_0[9]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_type_0_reg[0] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(\adc03_ds_type_0_reg[3]_0 [0]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_type_0_reg[1] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc03_ds_type_0),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_type_0_reg[2] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc03_ds_type_0_reg[3]_0 [1]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  FDRE #(
    .INIT(1'b0)) 
    \adc03_ds_type_0_reg[3] 
       (.C(s0_axis_clock),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc03_ds_type_0_reg[3]_0 [2]),
        .R(clk2clk_handshake_pulse_gen_i_n_1));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__1 clk2clk_handshake_pulse_gen_i
       (.E(clk2clk_handshake_pulse_gen_i_n_2),
        .Q(\slv_wdata_r_internal_reg_n_0_[0] ),
        .SR(clk2clk_handshake_pulse_gen_i_n_1),
        .\adc00_ds_control_0_reg[0] (\adc00_ds_control_0_reg[0]_0 ),
        .\adc00_ds_enable_0_reg[0] (\adc00_ds_enable_0_reg[0]_0 ),
        .\adc00_ds_inc_0_reg[0] (\adc00_ds_inc_0_reg[0]_0 ),
        .adc00_ds_pulse_control_0(adc00_ds_pulse_control_0),
        .adc00_ds_pulse_control_0_reg(adc00_ds_pulse_control_0_reg_0),
        .adc00_ds_pulse_control_0_reg_0(Q[0]),
        .adc00_ds_pulse_control_0_reg_1(adc00_ds_pulse_control_0_reg_1),
        .\adc00_ds_type_0_reg[3] (\adc00_ds_type_0_reg[3]_1 ),
        .\adc01_ds_control_0_reg[0] (\adc01_ds_control_0_reg[0]_0 ),
        .\adc01_ds_enable_0_reg[0] (\adc01_ds_enable_0_reg[0]_0 ),
        .\adc01_ds_inc_0_reg[0] (\adc01_ds_inc_0_reg[0]_1 ),
        .\adc01_ds_type_0_reg[0] (\adc01_ds_type_0_reg[0]_0 ),
        .\adc02_ds_control_0_reg[0] (\adc02_ds_control_0_reg[0]_0 ),
        .\adc02_ds_enable_0_reg[0] (\adc02_ds_enable_0_reg[0]_0 ),
        .\adc02_ds_inc_0_reg[0] (\adc02_ds_inc_0_reg[0]_0 ),
        .\adc02_ds_type_0_reg[0] (\adc02_ds_type_0_reg[0]_0 ),
        .\adc03_ds_control_0_reg[1] (\adc03_ds_control_0_reg[1]_1 ),
        .\adc03_ds_enable_0_reg[7] (\adc03_ds_enable_0_reg[7]_1 ),
        .\adc03_ds_inc_0_reg[0] (\adc03_ds_inc_0_reg[0]_0 ),
        .\adc03_ds_type_0_reg[0] (\adc03_ds_type_0_reg[0]_0 ),
        .adc0axi_map_wready(adc0axi_map_wready),
        .adc0slv_rden(adc0slv_rden),
        .adc_ds_slv_rden(adc_ds_slv_rden),
        .\axi_rresp[1]_i_2 (\axi_rresp[1]_i_2 ),
        .dest_rst(dest_rst),
        .p_0_in(p_0_in),
        .s0_axis_clock(s0_axis_clock),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_rden_r),
        .slv_rden_r_reg(clk2clk_handshake_pulse_gen_i_n_3),
        .slv_rden_r_reg_0(clk2clk_handshake_pulse_gen_i_n_4),
        .slv_rden_r_reg_1(slv_rden_r_reg_0),
        .slv_rden_r_reg_10(clk2clk_handshake_pulse_gen_i_n_14),
        .slv_rden_r_reg_11(clk2clk_handshake_pulse_gen_i_n_15),
        .slv_rden_r_reg_12(clk2clk_handshake_pulse_gen_i_n_16),
        .slv_rden_r_reg_13(clk2clk_handshake_pulse_gen_i_n_17),
        .slv_rden_r_reg_14(clk2clk_handshake_pulse_gen_i_n_18),
        .slv_rden_r_reg_2(clk2clk_handshake_pulse_gen_i_n_6),
        .slv_rden_r_reg_3(clk2clk_handshake_pulse_gen_i_n_7),
        .slv_rden_r_reg_4(clk2clk_handshake_pulse_gen_i_n_8),
        .slv_rden_r_reg_5(clk2clk_handshake_pulse_gen_i_n_9),
        .slv_rden_r_reg_6(clk2clk_handshake_pulse_gen_i_n_10),
        .slv_rden_r_reg_7(clk2clk_handshake_pulse_gen_i_n_11),
        .slv_rden_r_reg_8(clk2clk_handshake_pulse_gen_i_n_12),
        .slv_rden_r_reg_9(clk2clk_handshake_pulse_gen_i_n_13),
        .\slv_wdata_r_internal_reg[0] (clk2clk_handshake_pulse_gen_i_n_19),
        .slv_wren_done_pulse(slv_wren_done_pulse),
        .src_in(slv_access_valid_hold),
        .\syncstages_ff_reg[4] (clk2clk_handshake_pulse_gen_i_n_20));
  FDRE slv_access_valid_hold_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk2clk_handshake_pulse_gen_i_n_20),
        .Q(slv_access_valid_hold),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_10 
       (.I0(adc03_ds_enable_0[0]),
        .I1(adc01_ds_enable_0[0]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[0]),
        .I4(Q[3]),
        .I5(s00_tready),
        .O(\adc03_ds_enable_0_reg[0]_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[0]_i_12 
       (.I0(adc01_ds_inc_0[0]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[0]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[0]),
        .O(\adc01_ds_inc_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_8 
       (.I0(adc03_ds_control_0[0]),
        .I1(adc01_ds_control_0[0]),
        .I2(Q[2]),
        .I3(adc02_ds_control_0[0]),
        .I4(Q[3]),
        .I5(adc00_ds_control_0),
        .O(\adc03_ds_control_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[10]_i_3 
       (.I0(adc03_ds_inc_0[10]),
        .I1(adc01_ds_inc_0[10]),
        .I2(Q[2]),
        .I3(adc02_ds_inc_0[10]),
        .I4(Q[3]),
        .I5(adc00_ds_inc_0[10]),
        .O(\adc03_ds_inc_0_reg[10]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[11]_i_6 
       (.I0(adc03_ds_inc_0[11]),
        .I1(adc01_ds_inc_0[11]),
        .I2(Q[2]),
        .I3(adc02_ds_inc_0[11]),
        .I4(Q[3]),
        .I5(adc00_ds_inc_0[11]),
        .O(\adc03_ds_inc_0_reg[11]_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFE00000000)) 
    \slv_rdata[15]_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[5]),
        .I3(Q[4]),
        .I4(\slv_rdata_reg[12]_1 ),
        .I5(s_axi_aresetn),
        .O(\slv_rdata[15]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[1]_i_11 
       (.I0(adc01_ds_inc_0[1]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[1]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[1]),
        .O(\adc01_ds_inc_0_reg[1]_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[1]_i_14 
       (.I0(adc01_ds_type_0),
        .I1(Q[3]),
        .I2(adc02_ds_type_0),
        .I3(Q[2]),
        .I4(adc03_ds_type_0),
        .O(\adc01_ds_type_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'h470047CCFFFFFFFF)) 
    \slv_rdata[1]_i_4__2 
       (.I0(adc03_ds_control_0[1]),
        .I1(Q[2]),
        .I2(adc02_ds_control_0[1]),
        .I3(Q[3]),
        .I4(adc01_ds_control_0[1]),
        .I5(\slv_rdata_reg[1]_0 ),
        .O(\adc03_ds_control_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_8 
       (.I0(adc03_ds_enable_0[1]),
        .I1(adc01_ds_enable_0[1]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[1]),
        .I4(Q[3]),
        .I5(adc00_ds_enable_0[1]),
        .O(\adc03_ds_enable_0_reg[1]_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[2]_i_8 
       (.I0(adc01_ds_inc_0[2]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[2]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[2]),
        .O(\adc01_ds_inc_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[2]_i_9 
       (.I0(adc03_ds_enable_0[2]),
        .I1(adc01_ds_enable_0[2]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[2]),
        .I4(Q[3]),
        .I5(adc00_ds_enable_0[2]),
        .O(\adc03_ds_enable_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_7 
       (.I0(adc03_ds_enable_0[3]),
        .I1(adc01_ds_enable_0[3]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[3]),
        .I4(Q[3]),
        .I5(adc00_ds_enable_0[3]),
        .O(\adc03_ds_enable_0_reg[3]_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[3]_i_9__0 
       (.I0(adc01_ds_inc_0[3]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[3]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[3]),
        .O(\adc01_ds_inc_0_reg[3]_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[4]_i_7 
       (.I0(adc01_ds_inc_0[4]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[4]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[4]),
        .O(\adc01_ds_inc_0_reg[4]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[4]_i_8 
       (.I0(adc03_ds_enable_0[4]),
        .I1(adc01_ds_enable_0[4]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[4]),
        .I4(Q[3]),
        .I5(adc00_ds_enable_0[4]),
        .O(\adc03_ds_enable_0_reg[4]_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[5]_i_7 
       (.I0(adc01_ds_inc_0[5]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[5]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[5]),
        .O(\adc01_ds_inc_0_reg[5]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[5]_i_8 
       (.I0(adc03_ds_enable_0[5]),
        .I1(adc01_ds_enable_0[5]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[5]),
        .I4(Q[3]),
        .I5(adc00_ds_enable_0[5]),
        .O(\adc03_ds_enable_0_reg[5]_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[6]_i_7 
       (.I0(adc01_ds_inc_0[6]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[6]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[6]),
        .O(\adc01_ds_inc_0_reg[6]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[6]_i_8 
       (.I0(adc03_ds_enable_0[6]),
        .I1(adc01_ds_enable_0[6]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[6]),
        .I4(Q[3]),
        .I5(adc00_ds_enable_0[6]),
        .O(\adc03_ds_enable_0_reg[6]_0 ));
  LUT3 #(
    .INIT(8'hE0)) 
    \slv_rdata[7]_i_1 
       (.I0(Q[5]),
        .I1(Q[4]),
        .I2(s_axi_aresetn),
        .O(\slv_rdata[7]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h110CDD0C)) 
    \slv_rdata[7]_i_11 
       (.I0(adc01_ds_inc_0[7]),
        .I1(Q[3]),
        .I2(adc02_ds_inc_0[7]),
        .I3(Q[2]),
        .I4(adc03_ds_inc_0[7]),
        .O(\adc01_ds_inc_0_reg[7]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[7]_i_9 
       (.I0(adc03_ds_enable_0[7]),
        .I1(adc01_ds_enable_0[7]),
        .I2(Q[2]),
        .I3(adc02_ds_enable_0[7]),
        .I4(Q[3]),
        .I5(adc00_ds_enable_0[7]),
        .O(\adc03_ds_enable_0_reg[7]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[9]_i_3 
       (.I0(adc03_ds_inc_0[9]),
        .I1(adc01_ds_inc_0[9]),
        .I2(Q[2]),
        .I3(adc02_ds_inc_0[9]),
        .I4(Q[3]),
        .I5(adc00_ds_inc_0[9]),
        .O(\adc03_ds_inc_0_reg[9]_0 ));
  FDRE \slv_rdata_reg[0] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[0]),
        .Q(slv_rdata[0]),
        .R(1'b0));
  FDRE \slv_rdata_reg[10] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[4]),
        .Q(slv_rdata[10]),
        .R(1'b0));
  FDRE \slv_rdata_reg[11] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[5]),
        .Q(slv_rdata[11]),
        .R(1'b0));
  FDRE \slv_rdata_reg[12] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[12]_0 ),
        .Q(slv_rdata[12]),
        .R(\slv_rdata[15]_i_1_n_0 ));
  FDRE \slv_rdata_reg[13] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[13]_0 ),
        .Q(slv_rdata[13]),
        .R(\slv_rdata[15]_i_1_n_0 ));
  FDRE \slv_rdata_reg[14] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[14]_0 ),
        .Q(slv_rdata[14]),
        .R(\slv_rdata[15]_i_1_n_0 ));
  FDRE \slv_rdata_reg[15] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[15]_0 ),
        .Q(slv_rdata[15]),
        .R(\slv_rdata[15]_i_1_n_0 ));
  FDRE \slv_rdata_reg[1] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[1]),
        .Q(slv_rdata[1]),
        .R(1'b0));
  FDRE \slv_rdata_reg[2] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[2]_0 ),
        .Q(slv_rdata[2]),
        .R(\slv_rdata[7]_i_1_n_0 ));
  FDRE \slv_rdata_reg[3] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[3]_0 ),
        .Q(slv_rdata[3]),
        .R(\slv_rdata[7]_i_1_n_0 ));
  FDRE \slv_rdata_reg[4] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[4]_0 ),
        .Q(slv_rdata[4]),
        .R(\slv_rdata[7]_i_1_n_0 ));
  FDRE \slv_rdata_reg[5] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[5]_0 ),
        .Q(slv_rdata[5]),
        .R(\slv_rdata[7]_i_1_n_0 ));
  FDRE \slv_rdata_reg[6] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[6]_0 ),
        .Q(slv_rdata[6]),
        .R(\slv_rdata[7]_i_1_n_0 ));
  FDRE \slv_rdata_reg[7] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata_reg[7]_0 ),
        .Q(slv_rdata[7]),
        .R(\slv_rdata[7]_i_1_n_0 ));
  FDRE \slv_rdata_reg[8] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[2]),
        .Q(slv_rdata[8]),
        .R(1'b0));
  FDRE \slv_rdata_reg[9] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[3]),
        .Q(slv_rdata[9]),
        .R(1'b0));
  FDRE slv_rden_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(adc0slv_rden),
        .Q(slv_rden_r),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[0] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[0]),
        .Q(\slv_wdata_r_internal_reg_n_0_[0] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[10] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[10]),
        .Q(\slv_wdata_r_internal_reg_n_0_[10] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[11] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[11]),
        .Q(\slv_wdata_r_internal_reg_n_0_[11] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[1] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[1]),
        .Q(\slv_wdata_r_internal_reg_n_0_[1] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[2] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[2]),
        .Q(\slv_wdata_r_internal_reg_n_0_[2] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[3] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[3]),
        .Q(\slv_wdata_r_internal_reg_n_0_[3] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[4] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[4]),
        .Q(\slv_wdata_r_internal_reg_n_0_[4] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[5] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[5]),
        .Q(\slv_wdata_r_internal_reg_n_0_[5] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[6] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[6]),
        .Q(\slv_wdata_r_internal_reg_n_0_[6] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[7] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[7]),
        .Q(\slv_wdata_r_internal_reg_n_0_[7] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[8] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[8]),
        .Q(\slv_wdata_r_internal_reg_n_0_[8] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[9] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[9]),
        .Q(\slv_wdata_r_internal_reg_n_0_[9] ),
        .R(p_0_in));
endmodule

(* ORIG_REF_NAME = "adc1_rfadc_exdes_ctrl_axi" *) 
module project_1_adc_sink_i_0_adc1_rfadc_exdes_ctrl_axi
   (slv_wren_done_pulse,
    slv_rden_r,
    slv_rden_r_reg_0,
    \adc13_ds_inc_0_reg[8]_0 ,
    \adc13_ds_inc_0_reg[7]_0 ,
    \adc13_ds_inc_0_reg[6]_0 ,
    \adc13_ds_inc_0_reg[5]_0 ,
    \adc13_ds_inc_0_reg[4]_0 ,
    \adc13_ds_inc_0_reg[3]_0 ,
    \adc13_ds_inc_0_reg[2]_0 ,
    \adc13_ds_type_0_reg[2]_0 ,
    \adc13_ds_type_0_reg[3]_0 ,
    \adc11_ds_type_0_reg[3]_0 ,
    \adc12_ds_type_0_reg[3]_0 ,
    \adc10_ds_type_0_reg[3]_0 ,
    \adc13_ds_inc_0_reg[1]_0 ,
    \adc13_ds_control_0_reg[1]_0 ,
    \adc13_ds_enable_0_reg[1]_0 ,
    \adc13_ds_enable_0_reg[7]_0 ,
    \adc11_ds_enable_0_reg[7]_0 ,
    \adc12_ds_enable_0_reg[7]_0 ,
    \adc10_ds_enable_0_reg[7]_0 ,
    \adc13_ds_type_0_reg[1]_0 ,
    \adc13_ds_enable_0_reg[0]_0 ,
    \adc13_ds_type_0_reg[0]_0 ,
    \adc13_ds_inc_0_reg[0]_0 ,
    \adc13_ds_control_0_reg[0]_0 ,
    \slv_rdata_reg[8]_0 ,
    \slv_rdata_reg[11]_0 ,
    \slv_addr_reg[6] ,
    \slv_rdata_reg[10]_0 ,
    \slv_rdata_reg[9]_0 ,
    s_axi_aclk,
    p_0_in,
    adc1slv_rden,
    \adc10_ds_enable_0_reg[0]_0 ,
    \adc13_ds_type_0_reg[0]_1 ,
    \adc13_ds_enable_0_reg[0]_1 ,
    slv_wren_done_pulse_0,
    slv_rden_r_1,
    s_axi_wvalid,
    adc_ds_axi_map_wready,
    \adc11_ds_control_0_reg[0]_0 ,
    \adc11_ds_type_0_reg[0]_0 ,
    \adc11_ds_enable_0_reg[0]_0 ,
    \adc10_ds_type_0_reg[0]_0 ,
    \adc10_ds_control_0_reg[0]_0 ,
    \adc10_ds_inc_0_reg[0]_0 ,
    \adc13_ds_inc_0_reg[0]_1 ,
    \adc13_ds_control_0_reg[0]_1 ,
    \adc12_ds_type_0_reg[0]_0 ,
    \adc12_ds_inc_0_reg[0]_0 ,
    \adc12_ds_enable_0_reg[0]_0 ,
    \adc12_ds_control_0_reg[0]_0 ,
    \adc11_ds_inc_0_reg[0]_0 ,
    Q,
    adc1axi_map_wready,
    E,
    s_axi_wdata,
    s_axi_aresetn,
    D,
    \slv_rdata_reg[11]_1 );
  output slv_wren_done_pulse;
  output slv_rden_r;
  output slv_rden_r_reg_0;
  output \adc13_ds_inc_0_reg[8]_0 ;
  output \adc13_ds_inc_0_reg[7]_0 ;
  output \adc13_ds_inc_0_reg[6]_0 ;
  output \adc13_ds_inc_0_reg[5]_0 ;
  output \adc13_ds_inc_0_reg[4]_0 ;
  output \adc13_ds_inc_0_reg[3]_0 ;
  output \adc13_ds_inc_0_reg[2]_0 ;
  output \adc13_ds_type_0_reg[2]_0 ;
  output [0:0]\adc13_ds_type_0_reg[3]_0 ;
  output [0:0]\adc11_ds_type_0_reg[3]_0 ;
  output [0:0]\adc12_ds_type_0_reg[3]_0 ;
  output [0:0]\adc10_ds_type_0_reg[3]_0 ;
  output \adc13_ds_inc_0_reg[1]_0 ;
  output \adc13_ds_control_0_reg[1]_0 ;
  output \adc13_ds_enable_0_reg[1]_0 ;
  output [5:0]\adc13_ds_enable_0_reg[7]_0 ;
  output [5:0]\adc11_ds_enable_0_reg[7]_0 ;
  output [5:0]\adc12_ds_enable_0_reg[7]_0 ;
  output [5:0]\adc10_ds_enable_0_reg[7]_0 ;
  output \adc13_ds_type_0_reg[1]_0 ;
  output \adc13_ds_enable_0_reg[0]_0 ;
  output \adc13_ds_type_0_reg[0]_0 ;
  output \adc13_ds_inc_0_reg[0]_0 ;
  output \adc13_ds_control_0_reg[0]_0 ;
  output [8:0]\slv_rdata_reg[8]_0 ;
  output \slv_rdata_reg[11]_0 ;
  output \slv_addr_reg[6] ;
  output \slv_rdata_reg[10]_0 ;
  output \slv_rdata_reg[9]_0 ;
  input s_axi_aclk;
  input p_0_in;
  input adc1slv_rden;
  input \adc10_ds_enable_0_reg[0]_0 ;
  input \adc13_ds_type_0_reg[0]_1 ;
  input \adc13_ds_enable_0_reg[0]_1 ;
  input slv_wren_done_pulse_0;
  input slv_rden_r_1;
  input s_axi_wvalid;
  input adc_ds_axi_map_wready;
  input \adc11_ds_control_0_reg[0]_0 ;
  input \adc11_ds_type_0_reg[0]_0 ;
  input \adc11_ds_enable_0_reg[0]_0 ;
  input \adc10_ds_type_0_reg[0]_0 ;
  input \adc10_ds_control_0_reg[0]_0 ;
  input \adc10_ds_inc_0_reg[0]_0 ;
  input \adc13_ds_inc_0_reg[0]_1 ;
  input \adc13_ds_control_0_reg[0]_1 ;
  input \adc12_ds_type_0_reg[0]_0 ;
  input \adc12_ds_inc_0_reg[0]_0 ;
  input \adc12_ds_enable_0_reg[0]_0 ;
  input \adc12_ds_control_0_reg[0]_0 ;
  input \adc11_ds_inc_0_reg[0]_0 ;
  input [5:0]Q;
  input adc1axi_map_wready;
  input [0:0]E;
  input [11:0]s_axi_wdata;
  input s_axi_aresetn;
  input [8:0]D;
  input \slv_rdata_reg[11]_1 ;

  wire [8:0]D;
  wire [0:0]E;
  wire [5:0]Q;
  wire [1:0]adc10_ds_control_0;
  wire \adc10_ds_control_0_reg[0]_0 ;
  wire [1:0]adc10_ds_enable_0;
  wire \adc10_ds_enable_0_reg[0]_0 ;
  wire [5:0]\adc10_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc10_ds_inc_0;
  wire \adc10_ds_inc_0_reg[0]_0 ;
  wire [2:0]adc10_ds_type_0;
  wire \adc10_ds_type_0_reg[0]_0 ;
  wire [0:0]\adc10_ds_type_0_reg[3]_0 ;
  wire [1:0]adc11_ds_control_0;
  wire \adc11_ds_control_0_reg[0]_0 ;
  wire [1:0]adc11_ds_enable_0;
  wire \adc11_ds_enable_0_reg[0]_0 ;
  wire [5:0]\adc11_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc11_ds_inc_0;
  wire \adc11_ds_inc_0_reg[0]_0 ;
  wire [2:0]adc11_ds_type_0;
  wire \adc11_ds_type_0_reg[0]_0 ;
  wire [0:0]\adc11_ds_type_0_reg[3]_0 ;
  wire [1:0]adc12_ds_control_0;
  wire \adc12_ds_control_0_reg[0]_0 ;
  wire [1:0]adc12_ds_enable_0;
  wire \adc12_ds_enable_0_reg[0]_0 ;
  wire [5:0]\adc12_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc12_ds_inc_0;
  wire \adc12_ds_inc_0_reg[0]_0 ;
  wire [2:0]adc12_ds_type_0;
  wire \adc12_ds_type_0_reg[0]_0 ;
  wire [0:0]\adc12_ds_type_0_reg[3]_0 ;
  wire [1:0]adc13_ds_control_0;
  wire \adc13_ds_control_0_reg[0]_0 ;
  wire \adc13_ds_control_0_reg[0]_1 ;
  wire \adc13_ds_control_0_reg[1]_0 ;
  wire [1:0]adc13_ds_enable_0;
  wire \adc13_ds_enable_0_reg[0]_0 ;
  wire \adc13_ds_enable_0_reg[0]_1 ;
  wire \adc13_ds_enable_0_reg[1]_0 ;
  wire [5:0]\adc13_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc13_ds_inc_0;
  wire \adc13_ds_inc_0_reg[0]_0 ;
  wire \adc13_ds_inc_0_reg[0]_1 ;
  wire \adc13_ds_inc_0_reg[1]_0 ;
  wire \adc13_ds_inc_0_reg[2]_0 ;
  wire \adc13_ds_inc_0_reg[3]_0 ;
  wire \adc13_ds_inc_0_reg[4]_0 ;
  wire \adc13_ds_inc_0_reg[5]_0 ;
  wire \adc13_ds_inc_0_reg[6]_0 ;
  wire \adc13_ds_inc_0_reg[7]_0 ;
  wire \adc13_ds_inc_0_reg[8]_0 ;
  wire [2:0]adc13_ds_type_0;
  wire \adc13_ds_type_0_reg[0]_0 ;
  wire \adc13_ds_type_0_reg[0]_1 ;
  wire \adc13_ds_type_0_reg[1]_0 ;
  wire \adc13_ds_type_0_reg[2]_0 ;
  wire [0:0]\adc13_ds_type_0_reg[3]_0 ;
  wire adc1axi_map_wready;
  wire adc1slv_rden;
  wire adc_ds_axi_map_wready;
  wire clk2clk_handshake_pulse_gen_i_n_1;
  wire clk2clk_handshake_pulse_gen_i_n_10;
  wire clk2clk_handshake_pulse_gen_i_n_11;
  wire clk2clk_handshake_pulse_gen_i_n_12;
  wire clk2clk_handshake_pulse_gen_i_n_13;
  wire clk2clk_handshake_pulse_gen_i_n_14;
  wire clk2clk_handshake_pulse_gen_i_n_15;
  wire clk2clk_handshake_pulse_gen_i_n_16;
  wire clk2clk_handshake_pulse_gen_i_n_17;
  wire clk2clk_handshake_pulse_gen_i_n_18;
  wire clk2clk_handshake_pulse_gen_i_n_2;
  wire clk2clk_handshake_pulse_gen_i_n_3;
  wire clk2clk_handshake_pulse_gen_i_n_5;
  wire clk2clk_handshake_pulse_gen_i_n_6;
  wire clk2clk_handshake_pulse_gen_i_n_7;
  wire clk2clk_handshake_pulse_gen_i_n_8;
  wire clk2clk_handshake_pulse_gen_i_n_9;
  wire p_0_in;
  wire s_axi_aclk;
  wire s_axi_aresetn;
  wire [11:0]s_axi_wdata;
  wire s_axi_wvalid;
  wire slv_access_valid_hold;
  wire \slv_addr_reg[6] ;
  wire \slv_rdata[10]_i_1__0_n_0 ;
  wire \slv_rdata[11]_i_2_n_0 ;
  wire \slv_rdata[9]_i_1__0_n_0 ;
  wire \slv_rdata_reg[10]_0 ;
  wire \slv_rdata_reg[11]_0 ;
  wire \slv_rdata_reg[11]_1 ;
  wire [8:0]\slv_rdata_reg[8]_0 ;
  wire \slv_rdata_reg[9]_0 ;
  wire slv_rden_r;
  wire slv_rden_r_1;
  wire slv_rden_r_reg_0;
  wire \slv_wdata_r_internal_reg_n_0_[0] ;
  wire \slv_wdata_r_internal_reg_n_0_[10] ;
  wire \slv_wdata_r_internal_reg_n_0_[11] ;
  wire \slv_wdata_r_internal_reg_n_0_[1] ;
  wire \slv_wdata_r_internal_reg_n_0_[2] ;
  wire \slv_wdata_r_internal_reg_n_0_[3] ;
  wire \slv_wdata_r_internal_reg_n_0_[4] ;
  wire \slv_wdata_r_internal_reg_n_0_[5] ;
  wire \slv_wdata_r_internal_reg_n_0_[6] ;
  wire \slv_wdata_r_internal_reg_n_0_[7] ;
  wire \slv_wdata_r_internal_reg_n_0_[8] ;
  wire \slv_wdata_r_internal_reg_n_0_[9] ;
  wire slv_wren_done_pulse;
  wire slv_wren_done_pulse_0;

  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc10_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc10_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc10_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc10_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc10_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc10_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc10_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc10_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc10_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_1),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc10_ds_enable_0_reg[7]_0 [5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc10_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc10_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc10_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc10_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc10_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc10_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc10_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc10_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc10_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc10_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc10_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc10_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc10_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc10_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc10_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc10_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc10_ds_type_0_reg[3]_0 ),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_5),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc11_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_5),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc11_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc11_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc11_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc11_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc11_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc11_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc11_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc11_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc11_ds_enable_0_reg[7]_0 [5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc11_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc11_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc11_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc11_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc11_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc11_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc11_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc11_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc11_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc11_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc11_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc11_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc11_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc11_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc11_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc11_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc11_ds_type_0_reg[3]_0 ),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc12_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc12_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc12_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc12_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc12_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc12_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc12_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc12_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc12_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc12_ds_enable_0_reg[7]_0 [5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc12_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc12_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc12_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc12_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc12_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc12_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc12_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc12_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc12_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc12_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc12_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc12_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc12_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc12_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc12_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc12_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc12_ds_type_0_reg[3]_0 ),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc13_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc13_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc13_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc13_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc13_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc13_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc13_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc13_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc13_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc13_ds_enable_0_reg[7]_0 [5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc13_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc13_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc13_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc13_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc13_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc13_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc13_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc13_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc13_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc13_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc13_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc13_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc13_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc13_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc13_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc13_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(\adc13_ds_type_0_reg[3]_0 ),
        .R(p_0_in));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__2 clk2clk_handshake_pulse_gen_i
       (.E(clk2clk_handshake_pulse_gen_i_n_1),
        .\adc10_ds_control_0_reg[0] (\adc10_ds_control_0_reg[0]_0 ),
        .\adc10_ds_enable_0_reg[0] (\adc10_ds_enable_0_reg[0]_0 ),
        .\adc10_ds_inc_0_reg[0] (\adc10_ds_inc_0_reg[0]_0 ),
        .\adc10_ds_type_0_reg[0] (\adc10_ds_type_0_reg[0]_0 ),
        .\adc11_ds_control_0_reg[0] (\adc11_ds_control_0_reg[0]_0 ),
        .\adc11_ds_enable_0_reg[0] (\adc11_ds_enable_0_reg[0]_0 ),
        .\adc11_ds_inc_0_reg[0] (\adc11_ds_inc_0_reg[0]_0 ),
        .\adc11_ds_type_0_reg[0] (\adc11_ds_type_0_reg[0]_0 ),
        .\adc12_ds_control_0_reg[0] (\adc12_ds_control_0_reg[0]_0 ),
        .\adc12_ds_enable_0_reg[0] (\adc12_ds_enable_0_reg[0]_0 ),
        .\adc12_ds_inc_0_reg[0] (\adc12_ds_inc_0_reg[0]_0 ),
        .\adc12_ds_type_0_reg[0] (\adc12_ds_type_0_reg[0]_0 ),
        .\adc13_ds_control_0_reg[0] (\adc13_ds_control_0_reg[0]_1 ),
        .\adc13_ds_enable_0_reg[0] (\adc13_ds_enable_0_reg[0]_1 ),
        .\adc13_ds_inc_0_reg[0] (\adc13_ds_inc_0_reg[0]_1 ),
        .\adc13_ds_type_0_reg[0] (\adc13_ds_type_0_reg[0]_1 ),
        .adc1axi_map_wready(adc1axi_map_wready),
        .adc1slv_rden(adc1slv_rden),
        .adc_ds_axi_map_wready(adc_ds_axi_map_wready),
        .clk2_valid_pulse_reg_0(clk2clk_handshake_pulse_gen_i_n_2),
        .clk2_valid_pulse_reg_1(clk2clk_handshake_pulse_gen_i_n_3),
        .clk2_valid_pulse_reg_10(clk2clk_handshake_pulse_gen_i_n_13),
        .clk2_valid_pulse_reg_11(clk2clk_handshake_pulse_gen_i_n_14),
        .clk2_valid_pulse_reg_12(clk2clk_handshake_pulse_gen_i_n_15),
        .clk2_valid_pulse_reg_13(clk2clk_handshake_pulse_gen_i_n_16),
        .clk2_valid_pulse_reg_14(clk2clk_handshake_pulse_gen_i_n_17),
        .clk2_valid_pulse_reg_2(clk2clk_handshake_pulse_gen_i_n_5),
        .clk2_valid_pulse_reg_3(clk2clk_handshake_pulse_gen_i_n_6),
        .clk2_valid_pulse_reg_4(clk2clk_handshake_pulse_gen_i_n_7),
        .clk2_valid_pulse_reg_5(clk2clk_handshake_pulse_gen_i_n_8),
        .clk2_valid_pulse_reg_6(clk2clk_handshake_pulse_gen_i_n_9),
        .clk2_valid_pulse_reg_7(clk2clk_handshake_pulse_gen_i_n_10),
        .clk2_valid_pulse_reg_8(clk2clk_handshake_pulse_gen_i_n_11),
        .clk2_valid_pulse_reg_9(clk2clk_handshake_pulse_gen_i_n_12),
        .p_0_in(p_0_in),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_rden_r),
        .slv_rden_r_1(slv_rden_r_1),
        .slv_rden_r_reg(slv_rden_r_reg_0),
        .slv_wren_done_pulse(slv_wren_done_pulse),
        .slv_wren_done_pulse_0(slv_wren_done_pulse_0),
        .src_in(slv_access_valid_hold),
        .\syncstages_ff_reg[4] (clk2clk_handshake_pulse_gen_i_n_18));
  FDRE slv_access_valid_hold_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk2clk_handshake_pulse_gen_i_n_18),
        .Q(slv_access_valid_hold),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_3__0 
       (.I0(adc13_ds_type_0[0]),
        .I1(adc11_ds_type_0[0]),
        .I2(Q[4]),
        .I3(adc12_ds_type_0[0]),
        .I4(Q[5]),
        .I5(adc10_ds_type_0[0]),
        .O(\adc13_ds_type_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_4__0 
       (.I0(adc13_ds_enable_0[0]),
        .I1(adc11_ds_enable_0[0]),
        .I2(Q[4]),
        .I3(adc12_ds_enable_0[0]),
        .I4(Q[5]),
        .I5(adc10_ds_enable_0[0]),
        .O(\adc13_ds_enable_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_5__0 
       (.I0(adc13_ds_inc_0[0]),
        .I1(adc11_ds_inc_0[0]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[0]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[0]),
        .O(\adc13_ds_inc_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_6__0 
       (.I0(adc13_ds_control_0[0]),
        .I1(adc11_ds_control_0[0]),
        .I2(Q[4]),
        .I3(adc12_ds_control_0[0]),
        .I4(Q[5]),
        .I5(adc10_ds_control_0[0]),
        .O(\adc13_ds_control_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[10]_i_1__0 
       (.I0(adc13_ds_inc_0[10]),
        .I1(adc11_ds_inc_0[10]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[10]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[10]),
        .O(\slv_rdata[10]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFDFFFF00000000)) 
    \slv_rdata[11]_i_1 
       (.I0(\slv_rdata_reg[11]_1 ),
        .I1(Q[3]),
        .I2(Q[2]),
        .I3(Q[1]),
        .I4(Q[0]),
        .I5(s_axi_aresetn),
        .O(\slv_addr_reg[6] ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[11]_i_2 
       (.I0(adc13_ds_inc_0[11]),
        .I1(adc11_ds_inc_0[11]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[11]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[11]),
        .O(\slv_rdata[11]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_2__2 
       (.I0(adc13_ds_type_0[1]),
        .I1(adc11_ds_type_0[1]),
        .I2(Q[4]),
        .I3(adc12_ds_type_0[1]),
        .I4(Q[5]),
        .I5(adc10_ds_type_0[1]),
        .O(\adc13_ds_type_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_3__0 
       (.I0(adc13_ds_enable_0[1]),
        .I1(adc11_ds_enable_0[1]),
        .I2(Q[4]),
        .I3(adc12_ds_enable_0[1]),
        .I4(Q[5]),
        .I5(adc10_ds_enable_0[1]),
        .O(\adc13_ds_enable_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_6__0 
       (.I0(adc13_ds_inc_0[1]),
        .I1(adc11_ds_inc_0[1]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[1]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[1]),
        .O(\adc13_ds_inc_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_7__0 
       (.I0(adc13_ds_control_0[1]),
        .I1(adc11_ds_control_0[1]),
        .I2(Q[4]),
        .I3(adc12_ds_control_0[1]),
        .I4(Q[5]),
        .I5(adc10_ds_control_0[1]),
        .O(\adc13_ds_control_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[2]_i_3__0 
       (.I0(adc13_ds_type_0[2]),
        .I1(adc11_ds_type_0[2]),
        .I2(Q[4]),
        .I3(adc12_ds_type_0[2]),
        .I4(Q[5]),
        .I5(adc10_ds_type_0[2]),
        .O(\adc13_ds_type_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[2]_i_4__0 
       (.I0(adc13_ds_inc_0[2]),
        .I1(adc11_ds_inc_0[2]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[2]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[2]),
        .O(\adc13_ds_inc_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_7__0 
       (.I0(adc13_ds_inc_0[3]),
        .I1(adc11_ds_inc_0[3]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[3]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[3]),
        .O(\adc13_ds_inc_0_reg[3]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[4]_i_2__0 
       (.I0(adc13_ds_inc_0[4]),
        .I1(adc11_ds_inc_0[4]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[4]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[4]),
        .O(\adc13_ds_inc_0_reg[4]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[5]_i_2__0 
       (.I0(adc13_ds_inc_0[5]),
        .I1(adc11_ds_inc_0[5]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[5]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[5]),
        .O(\adc13_ds_inc_0_reg[5]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[6]_i_2__0 
       (.I0(adc13_ds_inc_0[6]),
        .I1(adc11_ds_inc_0[6]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[6]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[6]),
        .O(\adc13_ds_inc_0_reg[6]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[7]_i_2 
       (.I0(adc13_ds_inc_0[7]),
        .I1(adc11_ds_inc_0[7]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[7]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[7]),
        .O(\adc13_ds_inc_0_reg[7]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[8]_i_2 
       (.I0(adc13_ds_inc_0[8]),
        .I1(adc11_ds_inc_0[8]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[8]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[8]),
        .O(\adc13_ds_inc_0_reg[8]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[9]_i_1__0 
       (.I0(adc13_ds_inc_0[9]),
        .I1(adc11_ds_inc_0[9]),
        .I2(Q[4]),
        .I3(adc12_ds_inc_0[9]),
        .I4(Q[5]),
        .I5(adc10_ds_inc_0[9]),
        .O(\slv_rdata[9]_i_1__0_n_0 ));
  FDRE \slv_rdata_reg[0] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[0]),
        .Q(\slv_rdata_reg[8]_0 [0]),
        .R(1'b0));
  FDRE \slv_rdata_reg[10] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[10]_i_1__0_n_0 ),
        .Q(\slv_rdata_reg[10]_0 ),
        .R(\slv_addr_reg[6] ));
  FDRE \slv_rdata_reg[11] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[11]_i_2_n_0 ),
        .Q(\slv_rdata_reg[11]_0 ),
        .R(\slv_addr_reg[6] ));
  FDRE \slv_rdata_reg[1] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[1]),
        .Q(\slv_rdata_reg[8]_0 [1]),
        .R(1'b0));
  FDRE \slv_rdata_reg[2] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[2]),
        .Q(\slv_rdata_reg[8]_0 [2]),
        .R(1'b0));
  FDRE \slv_rdata_reg[3] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[3]),
        .Q(\slv_rdata_reg[8]_0 [3]),
        .R(1'b0));
  FDRE \slv_rdata_reg[4] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[4]),
        .Q(\slv_rdata_reg[8]_0 [4]),
        .R(1'b0));
  FDRE \slv_rdata_reg[5] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[5]),
        .Q(\slv_rdata_reg[8]_0 [5]),
        .R(1'b0));
  FDRE \slv_rdata_reg[6] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[6]),
        .Q(\slv_rdata_reg[8]_0 [6]),
        .R(1'b0));
  FDRE \slv_rdata_reg[7] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[7]),
        .Q(\slv_rdata_reg[8]_0 [7]),
        .R(1'b0));
  FDRE \slv_rdata_reg[8] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[8]),
        .Q(\slv_rdata_reg[8]_0 [8]),
        .R(1'b0));
  FDRE \slv_rdata_reg[9] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[9]_i_1__0_n_0 ),
        .Q(\slv_rdata_reg[9]_0 ),
        .R(\slv_addr_reg[6] ));
  FDRE slv_rden_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(adc1slv_rden),
        .Q(slv_rden_r),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[0] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[0]),
        .Q(\slv_wdata_r_internal_reg_n_0_[0] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[10] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[10]),
        .Q(\slv_wdata_r_internal_reg_n_0_[10] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[11] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[11]),
        .Q(\slv_wdata_r_internal_reg_n_0_[11] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[1] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[1]),
        .Q(\slv_wdata_r_internal_reg_n_0_[1] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[2] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[2]),
        .Q(\slv_wdata_r_internal_reg_n_0_[2] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[3] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[3]),
        .Q(\slv_wdata_r_internal_reg_n_0_[3] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[4] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[4]),
        .Q(\slv_wdata_r_internal_reg_n_0_[4] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[5] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[5]),
        .Q(\slv_wdata_r_internal_reg_n_0_[5] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[6] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[6]),
        .Q(\slv_wdata_r_internal_reg_n_0_[6] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[7] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[7]),
        .Q(\slv_wdata_r_internal_reg_n_0_[7] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[8] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[8]),
        .Q(\slv_wdata_r_internal_reg_n_0_[8] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[9] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[9]),
        .Q(\slv_wdata_r_internal_reg_n_0_[9] ),
        .R(p_0_in));
endmodule

(* ORIG_REF_NAME = "adc2_rfadc_exdes_ctrl_axi" *) 
module project_1_adc_sink_i_0_adc2_rfadc_exdes_ctrl_axi
   (slv_wren_done_pulse,
    slv_rden_r,
    slv_rden_r_reg_0,
    \slv_addr_reg[2] ,
    \adc23_ds_inc_0_reg[8]_0 ,
    \adc23_ds_inc_0_reg[7]_0 ,
    \adc23_ds_inc_0_reg[6]_0 ,
    \adc23_ds_inc_0_reg[5]_0 ,
    \adc23_ds_inc_0_reg[4]_0 ,
    \adc23_ds_enable_0_reg[7]_0 ,
    \adc21_ds_enable_0_reg[7]_0 ,
    \adc22_ds_enable_0_reg[7]_0 ,
    \adc20_ds_enable_0_reg[7]_0 ,
    \adc23_ds_inc_0_reg[2]_0 ,
    \adc23_ds_type_0_reg[2]_0 ,
    \adc23_ds_enable_0_reg[1]_0 ,
    \adc23_ds_type_0_reg[1]_0 ,
    \adc23_ds_control_0_reg[1]_0 ,
    \adc23_ds_inc_0_reg[1]_0 ,
    \adc23_ds_enable_0_reg[0]_0 ,
    \adc23_ds_type_0_reg[0]_0 ,
    \adc23_ds_inc_0_reg[0]_0 ,
    \adc23_ds_control_0_reg[0]_0 ,
    \slv_rdata_reg[8]_0 ,
    \slv_rdata_reg[11]_0 ,
    \slv_rdata_reg[10]_0 ,
    \slv_rdata_reg[9]_0 ,
    s_axi_aclk,
    p_0_in,
    adc2slv_rden,
    Q,
    slv_rden_r_0,
    slv_wren_done_pulse_1,
    \adc20_ds_enable_0_reg[0]_0 ,
    \adc23_ds_type_0_reg[0]_1 ,
    \adc23_ds_enable_0_reg[0]_1 ,
    \adc21_ds_control_0_reg[0]_0 ,
    \adc21_ds_type_0_reg[0]_0 ,
    \adc21_ds_enable_0_reg[0]_0 ,
    \adc20_ds_type_0_reg[0]_0 ,
    \adc20_ds_control_0_reg[0]_0 ,
    \adc20_ds_inc_0_reg[0]_0 ,
    \adc23_ds_inc_0_reg[0]_1 ,
    \adc23_ds_control_0_reg[0]_1 ,
    \adc22_ds_type_0_reg[0]_0 ,
    \adc22_ds_inc_0_reg[0]_0 ,
    \adc22_ds_enable_0_reg[0]_0 ,
    \adc22_ds_control_0_reg[0]_0 ,
    \adc21_ds_inc_0_reg[0]_0 ,
    \slv_rdata_reg[11]_1 ,
    s_axi_wvalid,
    adc2axi_map_wready,
    E,
    s_axi_wdata,
    s_axi_aresetn,
    D,
    \slv_rdata_reg[11]_2 );
  output slv_wren_done_pulse;
  output slv_rden_r;
  output slv_rden_r_reg_0;
  output \slv_addr_reg[2] ;
  output \adc23_ds_inc_0_reg[8]_0 ;
  output \adc23_ds_inc_0_reg[7]_0 ;
  output \adc23_ds_inc_0_reg[6]_0 ;
  output \adc23_ds_inc_0_reg[5]_0 ;
  output \adc23_ds_inc_0_reg[4]_0 ;
  output [4:0]\adc23_ds_enable_0_reg[7]_0 ;
  output [4:0]\adc21_ds_enable_0_reg[7]_0 ;
  output [4:0]\adc22_ds_enable_0_reg[7]_0 ;
  output [4:0]\adc20_ds_enable_0_reg[7]_0 ;
  output \adc23_ds_inc_0_reg[2]_0 ;
  output \adc23_ds_type_0_reg[2]_0 ;
  output \adc23_ds_enable_0_reg[1]_0 ;
  output \adc23_ds_type_0_reg[1]_0 ;
  output \adc23_ds_control_0_reg[1]_0 ;
  output \adc23_ds_inc_0_reg[1]_0 ;
  output \adc23_ds_enable_0_reg[0]_0 ;
  output \adc23_ds_type_0_reg[0]_0 ;
  output \adc23_ds_inc_0_reg[0]_0 ;
  output \adc23_ds_control_0_reg[0]_0 ;
  output [8:0]\slv_rdata_reg[8]_0 ;
  output \slv_rdata_reg[11]_0 ;
  output \slv_rdata_reg[10]_0 ;
  output \slv_rdata_reg[9]_0 ;
  input s_axi_aclk;
  input p_0_in;
  input adc2slv_rden;
  input [0:0]Q;
  input slv_rden_r_0;
  input slv_wren_done_pulse_1;
  input \adc20_ds_enable_0_reg[0]_0 ;
  input \adc23_ds_type_0_reg[0]_1 ;
  input \adc23_ds_enable_0_reg[0]_1 ;
  input \adc21_ds_control_0_reg[0]_0 ;
  input \adc21_ds_type_0_reg[0]_0 ;
  input \adc21_ds_enable_0_reg[0]_0 ;
  input \adc20_ds_type_0_reg[0]_0 ;
  input \adc20_ds_control_0_reg[0]_0 ;
  input \adc20_ds_inc_0_reg[0]_0 ;
  input \adc23_ds_inc_0_reg[0]_1 ;
  input \adc23_ds_control_0_reg[0]_1 ;
  input \adc22_ds_type_0_reg[0]_0 ;
  input \adc22_ds_inc_0_reg[0]_0 ;
  input \adc22_ds_enable_0_reg[0]_0 ;
  input \adc22_ds_control_0_reg[0]_0 ;
  input \adc21_ds_inc_0_reg[0]_0 ;
  input [4:0]\slv_rdata_reg[11]_1 ;
  input s_axi_wvalid;
  input adc2axi_map_wready;
  input [0:0]E;
  input [11:0]s_axi_wdata;
  input s_axi_aresetn;
  input [8:0]D;
  input \slv_rdata_reg[11]_2 ;

  wire [8:0]D;
  wire [0:0]E;
  wire [0:0]Q;
  wire [1:0]adc20_ds_control_0;
  wire \adc20_ds_control_0_reg[0]_0 ;
  wire [3:0]adc20_ds_enable_0;
  wire \adc20_ds_enable_0_reg[0]_0 ;
  wire [4:0]\adc20_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc20_ds_inc_0;
  wire \adc20_ds_inc_0_reg[0]_0 ;
  wire [3:0]adc20_ds_type_0;
  wire \adc20_ds_type_0_reg[0]_0 ;
  wire [1:0]adc21_ds_control_0;
  wire \adc21_ds_control_0_reg[0]_0 ;
  wire [3:0]adc21_ds_enable_0;
  wire \adc21_ds_enable_0_reg[0]_0 ;
  wire [4:0]\adc21_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc21_ds_inc_0;
  wire \adc21_ds_inc_0_reg[0]_0 ;
  wire [3:0]adc21_ds_type_0;
  wire \adc21_ds_type_0_reg[0]_0 ;
  wire [1:0]adc22_ds_control_0;
  wire \adc22_ds_control_0_reg[0]_0 ;
  wire [3:0]adc22_ds_enable_0;
  wire \adc22_ds_enable_0_reg[0]_0 ;
  wire [4:0]\adc22_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc22_ds_inc_0;
  wire \adc22_ds_inc_0_reg[0]_0 ;
  wire [3:0]adc22_ds_type_0;
  wire \adc22_ds_type_0_reg[0]_0 ;
  wire [1:0]adc23_ds_control_0;
  wire \adc23_ds_control_0_reg[0]_0 ;
  wire \adc23_ds_control_0_reg[0]_1 ;
  wire \adc23_ds_control_0_reg[1]_0 ;
  wire [3:0]adc23_ds_enable_0;
  wire \adc23_ds_enable_0_reg[0]_0 ;
  wire \adc23_ds_enable_0_reg[0]_1 ;
  wire \adc23_ds_enable_0_reg[1]_0 ;
  wire [4:0]\adc23_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc23_ds_inc_0;
  wire \adc23_ds_inc_0_reg[0]_0 ;
  wire \adc23_ds_inc_0_reg[0]_1 ;
  wire \adc23_ds_inc_0_reg[1]_0 ;
  wire \adc23_ds_inc_0_reg[2]_0 ;
  wire \adc23_ds_inc_0_reg[4]_0 ;
  wire \adc23_ds_inc_0_reg[5]_0 ;
  wire \adc23_ds_inc_0_reg[6]_0 ;
  wire \adc23_ds_inc_0_reg[7]_0 ;
  wire \adc23_ds_inc_0_reg[8]_0 ;
  wire [3:0]adc23_ds_type_0;
  wire \adc23_ds_type_0_reg[0]_0 ;
  wire \adc23_ds_type_0_reg[0]_1 ;
  wire \adc23_ds_type_0_reg[1]_0 ;
  wire \adc23_ds_type_0_reg[2]_0 ;
  wire adc2axi_map_wready;
  wire adc2slv_rden;
  wire clk2clk_handshake_pulse_gen_i_n_10;
  wire clk2clk_handshake_pulse_gen_i_n_11;
  wire clk2clk_handshake_pulse_gen_i_n_12;
  wire clk2clk_handshake_pulse_gen_i_n_13;
  wire clk2clk_handshake_pulse_gen_i_n_14;
  wire clk2clk_handshake_pulse_gen_i_n_15;
  wire clk2clk_handshake_pulse_gen_i_n_16;
  wire clk2clk_handshake_pulse_gen_i_n_17;
  wire clk2clk_handshake_pulse_gen_i_n_18;
  wire clk2clk_handshake_pulse_gen_i_n_2;
  wire clk2clk_handshake_pulse_gen_i_n_3;
  wire clk2clk_handshake_pulse_gen_i_n_4;
  wire clk2clk_handshake_pulse_gen_i_n_5;
  wire clk2clk_handshake_pulse_gen_i_n_6;
  wire clk2clk_handshake_pulse_gen_i_n_7;
  wire clk2clk_handshake_pulse_gen_i_n_8;
  wire clk2clk_handshake_pulse_gen_i_n_9;
  wire p_0_in;
  wire s_axi_aclk;
  wire s_axi_aresetn;
  wire [11:0]s_axi_wdata;
  wire s_axi_wvalid;
  wire slv_access_valid_hold;
  wire \slv_addr_reg[2] ;
  wire \slv_rdata[10]_i_1__1_n_0 ;
  wire \slv_rdata[11]_i_1__0_n_0 ;
  wire \slv_rdata[3]_i_3__1_n_0 ;
  wire \slv_rdata[3]_i_4__1_n_0 ;
  wire \slv_rdata[3]_i_5__1_n_0 ;
  wire \slv_rdata[9]_i_1__1_n_0 ;
  wire \slv_rdata_reg[10]_0 ;
  wire \slv_rdata_reg[11]_0 ;
  wire [4:0]\slv_rdata_reg[11]_1 ;
  wire \slv_rdata_reg[11]_2 ;
  wire [8:0]\slv_rdata_reg[8]_0 ;
  wire \slv_rdata_reg[9]_0 ;
  wire slv_rden_r;
  wire slv_rden_r_0;
  wire slv_rden_r_reg_0;
  wire \slv_wdata_r_internal_reg_n_0_[0] ;
  wire \slv_wdata_r_internal_reg_n_0_[10] ;
  wire \slv_wdata_r_internal_reg_n_0_[11] ;
  wire \slv_wdata_r_internal_reg_n_0_[1] ;
  wire \slv_wdata_r_internal_reg_n_0_[2] ;
  wire \slv_wdata_r_internal_reg_n_0_[3] ;
  wire \slv_wdata_r_internal_reg_n_0_[4] ;
  wire \slv_wdata_r_internal_reg_n_0_[5] ;
  wire \slv_wdata_r_internal_reg_n_0_[6] ;
  wire \slv_wdata_r_internal_reg_n_0_[7] ;
  wire \slv_wdata_r_internal_reg_n_0_[8] ;
  wire \slv_wdata_r_internal_reg_n_0_[9] ;
  wire slv_wren_done_pulse;
  wire slv_wren_done_pulse_1;

  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc20_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc20_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc20_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc20_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc20_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc20_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc20_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc20_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc20_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc20_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc20_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc20_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc20_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc20_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc20_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc20_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc20_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc20_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc20_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc20_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc20_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc20_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc20_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc20_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc20_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc20_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc20_ds_type_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_5),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc21_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_5),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc21_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc21_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc21_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc21_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc21_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc21_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc21_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc21_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc21_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc21_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc21_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc21_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc21_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc21_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc21_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc21_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc21_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc21_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc21_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc21_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc21_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc21_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc21_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc21_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc21_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc21_ds_type_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc22_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc22_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc22_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc22_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc22_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc22_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc22_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc22_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc22_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc22_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc22_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc22_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc22_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc22_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc22_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc22_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc22_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc22_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc22_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc22_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc22_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc22_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc22_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc22_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc22_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc22_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc22_ds_type_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc23_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc23_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc23_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc23_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc23_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc23_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc23_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc23_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc23_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc23_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc23_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc23_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc23_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc23_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc23_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc23_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc23_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc23_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc23_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc23_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc23_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc23_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc23_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc23_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc23_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc23_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc23_ds_type_0[3]),
        .R(p_0_in));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__3 clk2clk_handshake_pulse_gen_i
       (.E(clk2clk_handshake_pulse_gen_i_n_2),
        .Q(Q),
        .\adc20_ds_control_0_reg[0] (\adc20_ds_control_0_reg[0]_0 ),
        .\adc20_ds_enable_0_reg[0] (\adc20_ds_enable_0_reg[0]_0 ),
        .\adc20_ds_inc_0_reg[0] (\adc20_ds_inc_0_reg[0]_0 ),
        .\adc20_ds_type_0_reg[0] (\adc20_ds_type_0_reg[0]_0 ),
        .\adc21_ds_control_0_reg[0] (\adc21_ds_control_0_reg[0]_0 ),
        .\adc21_ds_enable_0_reg[0] (\adc21_ds_enable_0_reg[0]_0 ),
        .\adc21_ds_inc_0_reg[0] (\adc21_ds_inc_0_reg[0]_0 ),
        .\adc21_ds_type_0_reg[0] (\adc21_ds_type_0_reg[0]_0 ),
        .\adc22_ds_control_0_reg[0] (\adc22_ds_control_0_reg[0]_0 ),
        .\adc22_ds_enable_0_reg[0] (\adc22_ds_enable_0_reg[0]_0 ),
        .\adc22_ds_inc_0_reg[0] (\adc22_ds_inc_0_reg[0]_0 ),
        .\adc22_ds_type_0_reg[0] (\adc22_ds_type_0_reg[0]_0 ),
        .\adc23_ds_control_0_reg[0] (\adc23_ds_control_0_reg[0]_1 ),
        .\adc23_ds_enable_0_reg[0] (\adc23_ds_enable_0_reg[0]_1 ),
        .\adc23_ds_inc_0_reg[0] (\adc23_ds_inc_0_reg[0]_1 ),
        .\adc23_ds_type_0_reg[0] (\adc23_ds_type_0_reg[0]_1 ),
        .adc2axi_map_wready(adc2axi_map_wready),
        .adc2slv_rden(adc2slv_rden),
        .clk2_valid_pulse_reg_0(clk2clk_handshake_pulse_gen_i_n_3),
        .clk2_valid_pulse_reg_1(clk2clk_handshake_pulse_gen_i_n_4),
        .clk2_valid_pulse_reg_10(clk2clk_handshake_pulse_gen_i_n_13),
        .clk2_valid_pulse_reg_11(clk2clk_handshake_pulse_gen_i_n_14),
        .clk2_valid_pulse_reg_12(clk2clk_handshake_pulse_gen_i_n_15),
        .clk2_valid_pulse_reg_13(clk2clk_handshake_pulse_gen_i_n_16),
        .clk2_valid_pulse_reg_14(clk2clk_handshake_pulse_gen_i_n_17),
        .clk2_valid_pulse_reg_2(clk2clk_handshake_pulse_gen_i_n_5),
        .clk2_valid_pulse_reg_3(clk2clk_handshake_pulse_gen_i_n_6),
        .clk2_valid_pulse_reg_4(clk2clk_handshake_pulse_gen_i_n_7),
        .clk2_valid_pulse_reg_5(clk2clk_handshake_pulse_gen_i_n_8),
        .clk2_valid_pulse_reg_6(clk2clk_handshake_pulse_gen_i_n_9),
        .clk2_valid_pulse_reg_7(clk2clk_handshake_pulse_gen_i_n_10),
        .clk2_valid_pulse_reg_8(clk2clk_handshake_pulse_gen_i_n_11),
        .clk2_valid_pulse_reg_9(clk2clk_handshake_pulse_gen_i_n_12),
        .p_0_in(p_0_in),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_rden_r),
        .slv_rden_r_0(slv_rden_r_0),
        .slv_rden_r_reg(slv_rden_r_reg_0),
        .slv_wren_done_pulse(slv_wren_done_pulse),
        .slv_wren_done_pulse_1(slv_wren_done_pulse_1),
        .src_in(slv_access_valid_hold),
        .\syncstages_ff_reg[4] (clk2clk_handshake_pulse_gen_i_n_18));
  FDRE slv_access_valid_hold_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk2clk_handshake_pulse_gen_i_n_18),
        .Q(slv_access_valid_hold),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_3__1 
       (.I0(adc23_ds_type_0[0]),
        .I1(adc21_ds_type_0[0]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_type_0[0]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_type_0[0]),
        .O(\adc23_ds_type_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_4__1 
       (.I0(adc23_ds_enable_0[0]),
        .I1(adc21_ds_enable_0[0]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_enable_0[0]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_enable_0[0]),
        .O(\adc23_ds_enable_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_5__1 
       (.I0(adc23_ds_inc_0[0]),
        .I1(adc21_ds_inc_0[0]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[0]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[0]),
        .O(\adc23_ds_inc_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_6__1 
       (.I0(adc23_ds_control_0[0]),
        .I1(adc21_ds_control_0[0]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_control_0[0]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_control_0[0]),
        .O(\adc23_ds_control_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[10]_i_1__1 
       (.I0(adc23_ds_inc_0[10]),
        .I1(adc21_ds_inc_0[10]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[10]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[10]),
        .O(\slv_rdata[10]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[11]_i_1__0 
       (.I0(adc23_ds_inc_0[11]),
        .I1(adc21_ds_inc_0[11]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[11]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[11]),
        .O(\slv_rdata[11]_i_1__0_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_3__1 
       (.I0(adc23_ds_type_0[1]),
        .I1(adc21_ds_type_0[1]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_type_0[1]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_type_0[1]),
        .O(\adc23_ds_type_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_4__0 
       (.I0(adc23_ds_enable_0[1]),
        .I1(adc21_ds_enable_0[1]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_enable_0[1]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_enable_0[1]),
        .O(\adc23_ds_enable_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_5__0 
       (.I0(adc23_ds_control_0[1]),
        .I1(adc21_ds_control_0[1]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_control_0[1]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_control_0[1]),
        .O(\adc23_ds_control_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_6__1 
       (.I0(adc23_ds_inc_0[1]),
        .I1(adc21_ds_inc_0[1]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[1]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[1]),
        .O(\adc23_ds_inc_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[2]_i_3__1 
       (.I0(adc23_ds_type_0[2]),
        .I1(adc21_ds_type_0[2]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_type_0[2]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_type_0[2]),
        .O(\adc23_ds_type_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[2]_i_4__1 
       (.I0(adc23_ds_inc_0[2]),
        .I1(adc21_ds_inc_0[2]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[2]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[2]),
        .O(\adc23_ds_inc_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hFFFFCF44FFFFCF77)) 
    \slv_rdata[3]_i_2__1 
       (.I0(\slv_rdata[3]_i_3__1_n_0 ),
        .I1(\slv_rdata_reg[11]_1 [0]),
        .I2(\slv_rdata[3]_i_4__1_n_0 ),
        .I3(\slv_rdata_reg[11]_1 [1]),
        .I4(\slv_rdata_reg[11]_1 [2]),
        .I5(\slv_rdata[3]_i_5__1_n_0 ),
        .O(\slv_addr_reg[2] ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_3__1 
       (.I0(adc23_ds_inc_0[3]),
        .I1(adc21_ds_inc_0[3]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[3]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[3]),
        .O(\slv_rdata[3]_i_3__1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_4__1 
       (.I0(adc23_ds_type_0[3]),
        .I1(adc21_ds_type_0[3]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_type_0[3]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_type_0[3]),
        .O(\slv_rdata[3]_i_4__1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_5__1 
       (.I0(adc23_ds_enable_0[3]),
        .I1(adc21_ds_enable_0[3]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_enable_0[3]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_enable_0[3]),
        .O(\slv_rdata[3]_i_5__1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[4]_i_2__1 
       (.I0(adc23_ds_inc_0[4]),
        .I1(adc21_ds_inc_0[4]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[4]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[4]),
        .O(\adc23_ds_inc_0_reg[4]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[5]_i_2__1 
       (.I0(adc23_ds_inc_0[5]),
        .I1(adc21_ds_inc_0[5]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[5]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[5]),
        .O(\adc23_ds_inc_0_reg[5]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[6]_i_2__1 
       (.I0(adc23_ds_inc_0[6]),
        .I1(adc21_ds_inc_0[6]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[6]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[6]),
        .O(\adc23_ds_inc_0_reg[6]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[7]_i_2__0 
       (.I0(adc23_ds_inc_0[7]),
        .I1(adc21_ds_inc_0[7]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[7]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[7]),
        .O(\adc23_ds_inc_0_reg[7]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[8]_i_2__0 
       (.I0(adc23_ds_inc_0[8]),
        .I1(adc21_ds_inc_0[8]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[8]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[8]),
        .O(\adc23_ds_inc_0_reg[8]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[9]_i_1__1 
       (.I0(adc23_ds_inc_0[9]),
        .I1(adc21_ds_inc_0[9]),
        .I2(\slv_rdata_reg[11]_1 [3]),
        .I3(adc22_ds_inc_0[9]),
        .I4(\slv_rdata_reg[11]_1 [4]),
        .I5(adc20_ds_inc_0[9]),
        .O(\slv_rdata[9]_i_1__1_n_0 ));
  FDRE \slv_rdata_reg[0] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[0]),
        .Q(\slv_rdata_reg[8]_0 [0]),
        .R(1'b0));
  FDRE \slv_rdata_reg[10] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[10]_i_1__1_n_0 ),
        .Q(\slv_rdata_reg[10]_0 ),
        .R(\slv_rdata_reg[11]_2 ));
  FDRE \slv_rdata_reg[11] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[11]_i_1__0_n_0 ),
        .Q(\slv_rdata_reg[11]_0 ),
        .R(\slv_rdata_reg[11]_2 ));
  FDRE \slv_rdata_reg[1] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[1]),
        .Q(\slv_rdata_reg[8]_0 [1]),
        .R(1'b0));
  FDRE \slv_rdata_reg[2] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[2]),
        .Q(\slv_rdata_reg[8]_0 [2]),
        .R(1'b0));
  FDRE \slv_rdata_reg[3] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[3]),
        .Q(\slv_rdata_reg[8]_0 [3]),
        .R(1'b0));
  FDRE \slv_rdata_reg[4] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[4]),
        .Q(\slv_rdata_reg[8]_0 [4]),
        .R(1'b0));
  FDRE \slv_rdata_reg[5] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[5]),
        .Q(\slv_rdata_reg[8]_0 [5]),
        .R(1'b0));
  FDRE \slv_rdata_reg[6] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[6]),
        .Q(\slv_rdata_reg[8]_0 [6]),
        .R(1'b0));
  FDRE \slv_rdata_reg[7] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[7]),
        .Q(\slv_rdata_reg[8]_0 [7]),
        .R(1'b0));
  FDRE \slv_rdata_reg[8] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[8]),
        .Q(\slv_rdata_reg[8]_0 [8]),
        .R(1'b0));
  FDRE \slv_rdata_reg[9] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[9]_i_1__1_n_0 ),
        .Q(\slv_rdata_reg[9]_0 ),
        .R(\slv_rdata_reg[11]_2 ));
  FDRE slv_rden_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(adc2slv_rden),
        .Q(slv_rden_r),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[0] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[0]),
        .Q(\slv_wdata_r_internal_reg_n_0_[0] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[10] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[10]),
        .Q(\slv_wdata_r_internal_reg_n_0_[10] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[11] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[11]),
        .Q(\slv_wdata_r_internal_reg_n_0_[11] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[1] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[1]),
        .Q(\slv_wdata_r_internal_reg_n_0_[1] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[2] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[2]),
        .Q(\slv_wdata_r_internal_reg_n_0_[2] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[3] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[3]),
        .Q(\slv_wdata_r_internal_reg_n_0_[3] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[4] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[4]),
        .Q(\slv_wdata_r_internal_reg_n_0_[4] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[5] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[5]),
        .Q(\slv_wdata_r_internal_reg_n_0_[5] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[6] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[6]),
        .Q(\slv_wdata_r_internal_reg_n_0_[6] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[7] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[7]),
        .Q(\slv_wdata_r_internal_reg_n_0_[7] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[8] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[8]),
        .Q(\slv_wdata_r_internal_reg_n_0_[8] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[9] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[9]),
        .Q(\slv_wdata_r_internal_reg_n_0_[9] ),
        .R(p_0_in));
endmodule

(* ORIG_REF_NAME = "adc3_rfadc_exdes_ctrl_axi" *) 
module project_1_adc_sink_i_0_adc3_rfadc_exdes_ctrl_axi
   (p_0_in,
    slv_wren_done_pulse,
    slv_rden_r,
    \slv_rdata_reg[0]_0 ,
    \slv_addr_reg[3] ,
    clk1_ready_pulse_reg,
    \adc33_ds_inc_0_reg[8]_0 ,
    \adc33_ds_inc_0_reg[7]_0 ,
    \adc33_ds_inc_0_reg[6]_0 ,
    \adc33_ds_inc_0_reg[5]_0 ,
    \adc33_ds_inc_0_reg[4]_0 ,
    \adc33_ds_enable_0_reg[7]_0 ,
    \adc31_ds_enable_0_reg[7]_0 ,
    \adc32_ds_enable_0_reg[7]_0 ,
    \adc30_ds_enable_0_reg[7]_0 ,
    \adc33_ds_inc_0_reg[2]_0 ,
    \adc33_ds_type_0_reg[2]_0 ,
    \adc33_ds_enable_0_reg[1]_0 ,
    \adc33_ds_type_0_reg[1]_0 ,
    \adc33_ds_inc_0_reg[1]_0 ,
    \adc33_ds_control_0_reg[1]_0 ,
    \adc33_ds_enable_0_reg[0]_0 ,
    \adc33_ds_type_0_reg[0]_0 ,
    \adc33_ds_control_0_reg[0]_0 ,
    \adc33_ds_inc_0_reg[0]_0 ,
    \slv_rdata_reg[8]_0 ,
    \slv_rdata_reg[11]_0 ,
    \slv_rdata_reg[10]_0 ,
    \slv_rdata_reg[9]_0 ,
    s_axi_aclk,
    adc3slv_rden,
    \axi_rdata_reg[0] ,
    Q,
    \adc30_ds_enable_0_reg[0]_0 ,
    \adc33_ds_type_0_reg[0]_1 ,
    \adc33_ds_enable_0_reg[0]_1 ,
    \adc31_ds_control_0_reg[0]_0 ,
    \adc31_ds_type_0_reg[0]_0 ,
    \adc31_ds_enable_0_reg[0]_0 ,
    \adc30_ds_type_0_reg[0]_0 ,
    \adc30_ds_control_0_reg[0]_0 ,
    \adc30_ds_inc_0_reg[0]_0 ,
    \adc33_ds_inc_0_reg[0]_1 ,
    \adc33_ds_control_0_reg[0]_1 ,
    \adc32_ds_type_0_reg[0]_0 ,
    \adc32_ds_inc_0_reg[0]_0 ,
    \adc32_ds_enable_0_reg[0]_0 ,
    \adc32_ds_control_0_reg[0]_0 ,
    \adc31_ds_inc_0_reg[0]_0 ,
    s_axi_aresetn,
    slv_rden_r_0,
    slv_wren_done_pulse_1,
    s_axi_wvalid,
    adc3axi_map_wready,
    E,
    s_axi_wdata,
    D,
    \slv_rdata_reg[11]_1 );
  output p_0_in;
  output slv_wren_done_pulse;
  output slv_rden_r;
  output \slv_rdata_reg[0]_0 ;
  output \slv_addr_reg[3] ;
  output clk1_ready_pulse_reg;
  output \adc33_ds_inc_0_reg[8]_0 ;
  output \adc33_ds_inc_0_reg[7]_0 ;
  output \adc33_ds_inc_0_reg[6]_0 ;
  output \adc33_ds_inc_0_reg[5]_0 ;
  output \adc33_ds_inc_0_reg[4]_0 ;
  output [4:0]\adc33_ds_enable_0_reg[7]_0 ;
  output [4:0]\adc31_ds_enable_0_reg[7]_0 ;
  output [4:0]\adc32_ds_enable_0_reg[7]_0 ;
  output [4:0]\adc30_ds_enable_0_reg[7]_0 ;
  output \adc33_ds_inc_0_reg[2]_0 ;
  output \adc33_ds_type_0_reg[2]_0 ;
  output \adc33_ds_enable_0_reg[1]_0 ;
  output \adc33_ds_type_0_reg[1]_0 ;
  output \adc33_ds_inc_0_reg[1]_0 ;
  output \adc33_ds_control_0_reg[1]_0 ;
  output \adc33_ds_enable_0_reg[0]_0 ;
  output \adc33_ds_type_0_reg[0]_0 ;
  output \adc33_ds_control_0_reg[0]_0 ;
  output \adc33_ds_inc_0_reg[0]_0 ;
  output [7:0]\slv_rdata_reg[8]_0 ;
  output \slv_rdata_reg[11]_0 ;
  output \slv_rdata_reg[10]_0 ;
  output \slv_rdata_reg[9]_0 ;
  input s_axi_aclk;
  input adc3slv_rden;
  input \axi_rdata_reg[0] ;
  input [4:0]Q;
  input \adc30_ds_enable_0_reg[0]_0 ;
  input \adc33_ds_type_0_reg[0]_1 ;
  input \adc33_ds_enable_0_reg[0]_1 ;
  input \adc31_ds_control_0_reg[0]_0 ;
  input \adc31_ds_type_0_reg[0]_0 ;
  input \adc31_ds_enable_0_reg[0]_0 ;
  input \adc30_ds_type_0_reg[0]_0 ;
  input \adc30_ds_control_0_reg[0]_0 ;
  input \adc30_ds_inc_0_reg[0]_0 ;
  input \adc33_ds_inc_0_reg[0]_1 ;
  input \adc33_ds_control_0_reg[0]_1 ;
  input \adc32_ds_type_0_reg[0]_0 ;
  input \adc32_ds_inc_0_reg[0]_0 ;
  input \adc32_ds_enable_0_reg[0]_0 ;
  input \adc32_ds_control_0_reg[0]_0 ;
  input \adc31_ds_inc_0_reg[0]_0 ;
  input s_axi_aresetn;
  input slv_rden_r_0;
  input slv_wren_done_pulse_1;
  input s_axi_wvalid;
  input adc3axi_map_wready;
  input [0:0]E;
  input [11:0]s_axi_wdata;
  input [8:0]D;
  input \slv_rdata_reg[11]_1 ;

  wire [8:0]D;
  wire [0:0]E;
  wire [4:0]Q;
  wire [1:0]adc30_ds_control_0;
  wire \adc30_ds_control_0_reg[0]_0 ;
  wire [3:0]adc30_ds_enable_0;
  wire \adc30_ds_enable_0_reg[0]_0 ;
  wire [4:0]\adc30_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc30_ds_inc_0;
  wire \adc30_ds_inc_0_reg[0]_0 ;
  wire [3:0]adc30_ds_type_0;
  wire \adc30_ds_type_0_reg[0]_0 ;
  wire [1:0]adc31_ds_control_0;
  wire \adc31_ds_control_0_reg[0]_0 ;
  wire [3:0]adc31_ds_enable_0;
  wire \adc31_ds_enable_0_reg[0]_0 ;
  wire [4:0]\adc31_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc31_ds_inc_0;
  wire \adc31_ds_inc_0_reg[0]_0 ;
  wire [3:0]adc31_ds_type_0;
  wire \adc31_ds_type_0_reg[0]_0 ;
  wire [1:0]adc32_ds_control_0;
  wire \adc32_ds_control_0_reg[0]_0 ;
  wire [3:0]adc32_ds_enable_0;
  wire \adc32_ds_enable_0_reg[0]_0 ;
  wire [4:0]\adc32_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc32_ds_inc_0;
  wire \adc32_ds_inc_0_reg[0]_0 ;
  wire [3:0]adc32_ds_type_0;
  wire \adc32_ds_type_0_reg[0]_0 ;
  wire [1:0]adc33_ds_control_0;
  wire \adc33_ds_control_0_reg[0]_0 ;
  wire \adc33_ds_control_0_reg[0]_1 ;
  wire \adc33_ds_control_0_reg[1]_0 ;
  wire [3:0]adc33_ds_enable_0;
  wire \adc33_ds_enable_0_reg[0]_0 ;
  wire \adc33_ds_enable_0_reg[0]_1 ;
  wire \adc33_ds_enable_0_reg[1]_0 ;
  wire [4:0]\adc33_ds_enable_0_reg[7]_0 ;
  wire [11:0]adc33_ds_inc_0;
  wire \adc33_ds_inc_0_reg[0]_0 ;
  wire \adc33_ds_inc_0_reg[0]_1 ;
  wire \adc33_ds_inc_0_reg[1]_0 ;
  wire \adc33_ds_inc_0_reg[2]_0 ;
  wire \adc33_ds_inc_0_reg[4]_0 ;
  wire \adc33_ds_inc_0_reg[5]_0 ;
  wire \adc33_ds_inc_0_reg[6]_0 ;
  wire \adc33_ds_inc_0_reg[7]_0 ;
  wire \adc33_ds_inc_0_reg[8]_0 ;
  wire [3:0]adc33_ds_type_0;
  wire \adc33_ds_type_0_reg[0]_0 ;
  wire \adc33_ds_type_0_reg[0]_1 ;
  wire \adc33_ds_type_0_reg[1]_0 ;
  wire \adc33_ds_type_0_reg[2]_0 ;
  wire adc3axi_map_wready;
  wire adc3slv_rden;
  wire \axi_rdata_reg[0] ;
  wire clk1_ready_pulse_reg;
  wire clk2clk_handshake_pulse_gen_i_n_10;
  wire clk2clk_handshake_pulse_gen_i_n_11;
  wire clk2clk_handshake_pulse_gen_i_n_12;
  wire clk2clk_handshake_pulse_gen_i_n_13;
  wire clk2clk_handshake_pulse_gen_i_n_14;
  wire clk2clk_handshake_pulse_gen_i_n_15;
  wire clk2clk_handshake_pulse_gen_i_n_16;
  wire clk2clk_handshake_pulse_gen_i_n_17;
  wire clk2clk_handshake_pulse_gen_i_n_19;
  wire clk2clk_handshake_pulse_gen_i_n_2;
  wire clk2clk_handshake_pulse_gen_i_n_3;
  wire clk2clk_handshake_pulse_gen_i_n_4;
  wire clk2clk_handshake_pulse_gen_i_n_5;
  wire clk2clk_handshake_pulse_gen_i_n_6;
  wire clk2clk_handshake_pulse_gen_i_n_7;
  wire clk2clk_handshake_pulse_gen_i_n_8;
  wire clk2clk_handshake_pulse_gen_i_n_9;
  wire p_0_in;
  wire s_axi_aclk;
  wire s_axi_aresetn;
  wire [11:0]s_axi_wdata;
  wire s_axi_wvalid;
  wire slv_access_valid_hold;
  wire \slv_addr_reg[3] ;
  wire \slv_rdata[10]_i_1__2_n_0 ;
  wire \slv_rdata[11]_i_1__1_n_0 ;
  wire \slv_rdata[3]_i_3__2_n_0 ;
  wire \slv_rdata[3]_i_4__2_n_0 ;
  wire \slv_rdata[3]_i_5__2_n_0 ;
  wire \slv_rdata[9]_i_1__2_n_0 ;
  wire \slv_rdata_reg[0]_0 ;
  wire \slv_rdata_reg[10]_0 ;
  wire \slv_rdata_reg[11]_0 ;
  wire \slv_rdata_reg[11]_1 ;
  wire [7:0]\slv_rdata_reg[8]_0 ;
  wire \slv_rdata_reg[9]_0 ;
  wire \slv_rdata_reg_n_0_[0] ;
  wire slv_rden_r;
  wire slv_rden_r_0;
  wire \slv_wdata_r_internal_reg_n_0_[0] ;
  wire \slv_wdata_r_internal_reg_n_0_[10] ;
  wire \slv_wdata_r_internal_reg_n_0_[11] ;
  wire \slv_wdata_r_internal_reg_n_0_[1] ;
  wire \slv_wdata_r_internal_reg_n_0_[2] ;
  wire \slv_wdata_r_internal_reg_n_0_[3] ;
  wire \slv_wdata_r_internal_reg_n_0_[4] ;
  wire \slv_wdata_r_internal_reg_n_0_[5] ;
  wire \slv_wdata_r_internal_reg_n_0_[6] ;
  wire \slv_wdata_r_internal_reg_n_0_[7] ;
  wire \slv_wdata_r_internal_reg_n_0_[8] ;
  wire \slv_wdata_r_internal_reg_n_0_[9] ;
  wire slv_wren_done_pulse;
  wire slv_wren_done_pulse_1;

  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc30_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_9),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc30_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc30_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc30_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc30_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc30_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc30_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc30_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc30_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_2),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc30_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc30_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc30_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc30_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc30_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc30_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc30_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc30_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc30_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc30_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc30_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc30_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_10),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc30_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc30_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc30_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc30_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc30_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_8),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc30_ds_type_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_5),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc31_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_5),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc31_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc31_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc31_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc31_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc31_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc31_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc31_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc31_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_7),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc31_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc31_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc31_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc31_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc31_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc31_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc31_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc31_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc31_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc31_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc31_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc31_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_17),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc31_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc31_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc31_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc31_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc31_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_6),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc31_ds_type_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc32_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_16),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc32_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc32_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc32_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc32_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc32_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc32_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc32_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc32_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_15),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc32_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc32_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc32_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc32_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc32_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc32_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc32_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc32_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc32_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc32_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc32_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc32_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_14),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc32_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc32_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc32_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc32_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc32_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_13),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc32_ds_type_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_control_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc33_ds_control_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_control_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_12),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc33_ds_control_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc33_ds_enable_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc33_ds_enable_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(\adc33_ds_enable_0_reg[7]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc33_ds_enable_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(\adc33_ds_enable_0_reg[7]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(\adc33_ds_enable_0_reg[7]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(\adc33_ds_enable_0_reg[7]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_enable_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_4),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(\adc33_ds_enable_0_reg[7]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc33_ds_inc_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[10] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[10] ),
        .Q(adc33_ds_inc_0[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[11] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[11] ),
        .Q(adc33_ds_inc_0[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc33_ds_inc_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc33_ds_inc_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc33_ds_inc_0[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[4] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[4] ),
        .Q(adc33_ds_inc_0[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[5] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[5] ),
        .Q(adc33_ds_inc_0[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[6] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[6] ),
        .Q(adc33_ds_inc_0[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[7] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[7] ),
        .Q(adc33_ds_inc_0[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[8] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[8] ),
        .Q(adc33_ds_inc_0[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_inc_0_reg[9] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_11),
        .D(\slv_wdata_r_internal_reg_n_0_[9] ),
        .Q(adc33_ds_inc_0[9]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_type_0_reg[0] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[0] ),
        .Q(adc33_ds_type_0[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_type_0_reg[1] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[1] ),
        .Q(adc33_ds_type_0[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_type_0_reg[2] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[2] ),
        .Q(adc33_ds_type_0[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \adc33_ds_type_0_reg[3] 
       (.C(s_axi_aclk),
        .CE(clk2clk_handshake_pulse_gen_i_n_3),
        .D(\slv_wdata_r_internal_reg_n_0_[3] ),
        .Q(adc33_ds_type_0[3]),
        .R(p_0_in));
  LUT2 #(
    .INIT(4'h2)) 
    \axi_rdata[0]_i_2 
       (.I0(\slv_rdata_reg_n_0_[0] ),
        .I1(\axi_rdata_reg[0] ),
        .O(\slv_rdata_reg[0]_0 ));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen clk2clk_handshake_pulse_gen_i
       (.E(clk2clk_handshake_pulse_gen_i_n_2),
        .SR(p_0_in),
        .\adc30_ds_control_0_reg[0] (\adc30_ds_control_0_reg[0]_0 ),
        .\adc30_ds_enable_0_reg[0] (\adc30_ds_enable_0_reg[0]_0 ),
        .\adc30_ds_inc_0_reg[0] (\adc30_ds_inc_0_reg[0]_0 ),
        .\adc30_ds_type_0_reg[0] (\adc30_ds_type_0_reg[0]_0 ),
        .\adc31_ds_control_0_reg[0] (\adc31_ds_control_0_reg[0]_0 ),
        .\adc31_ds_enable_0_reg[0] (\adc31_ds_enable_0_reg[0]_0 ),
        .\adc31_ds_inc_0_reg[0] (\adc31_ds_inc_0_reg[0]_0 ),
        .\adc31_ds_type_0_reg[0] (\adc31_ds_type_0_reg[0]_0 ),
        .\adc32_ds_control_0_reg[0] (\adc32_ds_control_0_reg[0]_0 ),
        .\adc32_ds_enable_0_reg[0] (\adc32_ds_enable_0_reg[0]_0 ),
        .\adc32_ds_inc_0_reg[0] (\adc32_ds_inc_0_reg[0]_0 ),
        .\adc32_ds_type_0_reg[0] (\adc32_ds_type_0_reg[0]_0 ),
        .\adc33_ds_control_0_reg[0] (\adc33_ds_control_0_reg[0]_1 ),
        .\adc33_ds_enable_0_reg[0] (\adc33_ds_enable_0_reg[0]_1 ),
        .\adc33_ds_inc_0_reg[0] (\adc33_ds_inc_0_reg[0]_1 ),
        .\adc33_ds_type_0_reg[0] (\adc33_ds_type_0_reg[0]_1 ),
        .adc3axi_map_wready(adc3axi_map_wready),
        .adc3slv_rden(adc3slv_rden),
        .clk1_ready_pulse_reg_0(clk1_ready_pulse_reg),
        .clk2_valid_pulse_reg_0(clk2clk_handshake_pulse_gen_i_n_3),
        .clk2_valid_pulse_reg_1(clk2clk_handshake_pulse_gen_i_n_4),
        .clk2_valid_pulse_reg_10(clk2clk_handshake_pulse_gen_i_n_13),
        .clk2_valid_pulse_reg_11(clk2clk_handshake_pulse_gen_i_n_14),
        .clk2_valid_pulse_reg_12(clk2clk_handshake_pulse_gen_i_n_15),
        .clk2_valid_pulse_reg_13(clk2clk_handshake_pulse_gen_i_n_16),
        .clk2_valid_pulse_reg_14(clk2clk_handshake_pulse_gen_i_n_17),
        .clk2_valid_pulse_reg_2(clk2clk_handshake_pulse_gen_i_n_5),
        .clk2_valid_pulse_reg_3(clk2clk_handshake_pulse_gen_i_n_6),
        .clk2_valid_pulse_reg_4(clk2clk_handshake_pulse_gen_i_n_7),
        .clk2_valid_pulse_reg_5(clk2clk_handshake_pulse_gen_i_n_8),
        .clk2_valid_pulse_reg_6(clk2clk_handshake_pulse_gen_i_n_9),
        .clk2_valid_pulse_reg_7(clk2clk_handshake_pulse_gen_i_n_10),
        .clk2_valid_pulse_reg_8(clk2clk_handshake_pulse_gen_i_n_11),
        .clk2_valid_pulse_reg_9(clk2clk_handshake_pulse_gen_i_n_12),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_rden_r),
        .slv_rden_r_0(slv_rden_r_0),
        .slv_wren_done_pulse(slv_wren_done_pulse),
        .slv_wren_done_pulse_1(slv_wren_done_pulse_1),
        .src_in(slv_access_valid_hold),
        .\syncstages_ff_reg[4] (clk2clk_handshake_pulse_gen_i_n_19));
  FDRE slv_access_valid_hold_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk2clk_handshake_pulse_gen_i_n_19),
        .Q(slv_access_valid_hold),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_3__2 
       (.I0(adc33_ds_type_0[0]),
        .I1(adc31_ds_type_0[0]),
        .I2(Q[3]),
        .I3(adc32_ds_type_0[0]),
        .I4(Q[4]),
        .I5(adc30_ds_type_0[0]),
        .O(\adc33_ds_type_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_4__2 
       (.I0(adc33_ds_enable_0[0]),
        .I1(adc31_ds_enable_0[0]),
        .I2(Q[3]),
        .I3(adc32_ds_enable_0[0]),
        .I4(Q[4]),
        .I5(adc30_ds_enable_0[0]),
        .O(\adc33_ds_enable_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_5__2 
       (.I0(adc33_ds_control_0[0]),
        .I1(adc31_ds_control_0[0]),
        .I2(Q[3]),
        .I3(adc32_ds_control_0[0]),
        .I4(Q[4]),
        .I5(adc30_ds_control_0[0]),
        .O(\adc33_ds_control_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[0]_i_6__2 
       (.I0(adc33_ds_inc_0[0]),
        .I1(adc31_ds_inc_0[0]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[0]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[0]),
        .O(\adc33_ds_inc_0_reg[0]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[10]_i_1__2 
       (.I0(adc33_ds_inc_0[10]),
        .I1(adc31_ds_inc_0[10]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[10]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[10]),
        .O(\slv_rdata[10]_i_1__2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[11]_i_1__1 
       (.I0(adc33_ds_inc_0[11]),
        .I1(adc31_ds_inc_0[11]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[11]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[11]),
        .O(\slv_rdata[11]_i_1__1_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_3__2 
       (.I0(adc33_ds_type_0[1]),
        .I1(adc31_ds_type_0[1]),
        .I2(Q[3]),
        .I3(adc32_ds_type_0[1]),
        .I4(Q[4]),
        .I5(adc30_ds_type_0[1]),
        .O(\adc33_ds_type_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_4__1 
       (.I0(adc33_ds_enable_0[1]),
        .I1(adc31_ds_enable_0[1]),
        .I2(Q[3]),
        .I3(adc32_ds_enable_0[1]),
        .I4(Q[4]),
        .I5(adc30_ds_enable_0[1]),
        .O(\adc33_ds_enable_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_5__1 
       (.I0(adc33_ds_inc_0[1]),
        .I1(adc31_ds_inc_0[1]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[1]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[1]),
        .O(\adc33_ds_inc_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[1]_i_6__2 
       (.I0(adc33_ds_control_0[1]),
        .I1(adc31_ds_control_0[1]),
        .I2(Q[3]),
        .I3(adc32_ds_control_0[1]),
        .I4(Q[4]),
        .I5(adc30_ds_control_0[1]),
        .O(\adc33_ds_control_0_reg[1]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[2]_i_3__2 
       (.I0(adc33_ds_type_0[2]),
        .I1(adc31_ds_type_0[2]),
        .I2(Q[3]),
        .I3(adc32_ds_type_0[2]),
        .I4(Q[4]),
        .I5(adc30_ds_type_0[2]),
        .O(\adc33_ds_type_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[2]_i_4__2 
       (.I0(adc33_ds_inc_0[2]),
        .I1(adc31_ds_inc_0[2]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[2]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[2]),
        .O(\adc33_ds_inc_0_reg[2]_0 ));
  LUT6 #(
    .INIT(64'hFFFFF530FFFFF53F)) 
    \slv_rdata[3]_i_2 
       (.I0(\slv_rdata[3]_i_3__2_n_0 ),
        .I1(\slv_rdata[3]_i_4__2_n_0 ),
        .I2(Q[1]),
        .I3(Q[0]),
        .I4(Q[2]),
        .I5(\slv_rdata[3]_i_5__2_n_0 ),
        .O(\slv_addr_reg[3] ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_3__2 
       (.I0(adc33_ds_inc_0[3]),
        .I1(adc31_ds_inc_0[3]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[3]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[3]),
        .O(\slv_rdata[3]_i_3__2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_4__2 
       (.I0(adc33_ds_type_0[3]),
        .I1(adc31_ds_type_0[3]),
        .I2(Q[3]),
        .I3(adc32_ds_type_0[3]),
        .I4(Q[4]),
        .I5(adc30_ds_type_0[3]),
        .O(\slv_rdata[3]_i_4__2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[3]_i_5__2 
       (.I0(adc33_ds_enable_0[3]),
        .I1(adc31_ds_enable_0[3]),
        .I2(Q[3]),
        .I3(adc32_ds_enable_0[3]),
        .I4(Q[4]),
        .I5(adc30_ds_enable_0[3]),
        .O(\slv_rdata[3]_i_5__2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[4]_i_2__2 
       (.I0(adc33_ds_inc_0[4]),
        .I1(adc31_ds_inc_0[4]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[4]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[4]),
        .O(\adc33_ds_inc_0_reg[4]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[5]_i_2__2 
       (.I0(adc33_ds_inc_0[5]),
        .I1(adc31_ds_inc_0[5]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[5]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[5]),
        .O(\adc33_ds_inc_0_reg[5]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[6]_i_2__2 
       (.I0(adc33_ds_inc_0[6]),
        .I1(adc31_ds_inc_0[6]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[6]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[6]),
        .O(\adc33_ds_inc_0_reg[6]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[7]_i_2__1 
       (.I0(adc33_ds_inc_0[7]),
        .I1(adc31_ds_inc_0[7]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[7]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[7]),
        .O(\adc33_ds_inc_0_reg[7]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[8]_i_2__1 
       (.I0(adc33_ds_inc_0[8]),
        .I1(adc31_ds_inc_0[8]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[8]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[8]),
        .O(\adc33_ds_inc_0_reg[8]_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[9]_i_1__2 
       (.I0(adc33_ds_inc_0[9]),
        .I1(adc31_ds_inc_0[9]),
        .I2(Q[3]),
        .I3(adc32_ds_inc_0[9]),
        .I4(Q[4]),
        .I5(adc30_ds_inc_0[9]),
        .O(\slv_rdata[9]_i_1__2_n_0 ));
  FDRE \slv_rdata_reg[0] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[0]),
        .Q(\slv_rdata_reg_n_0_[0] ),
        .R(1'b0));
  FDRE \slv_rdata_reg[10] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[10]_i_1__2_n_0 ),
        .Q(\slv_rdata_reg[10]_0 ),
        .R(\slv_rdata_reg[11]_1 ));
  FDRE \slv_rdata_reg[11] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[11]_i_1__1_n_0 ),
        .Q(\slv_rdata_reg[11]_0 ),
        .R(\slv_rdata_reg[11]_1 ));
  FDRE \slv_rdata_reg[1] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[1]),
        .Q(\slv_rdata_reg[8]_0 [0]),
        .R(1'b0));
  FDRE \slv_rdata_reg[2] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[2]),
        .Q(\slv_rdata_reg[8]_0 [1]),
        .R(1'b0));
  FDRE \slv_rdata_reg[3] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[3]),
        .Q(\slv_rdata_reg[8]_0 [2]),
        .R(1'b0));
  FDRE \slv_rdata_reg[4] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[4]),
        .Q(\slv_rdata_reg[8]_0 [3]),
        .R(1'b0));
  FDRE \slv_rdata_reg[5] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[5]),
        .Q(\slv_rdata_reg[8]_0 [4]),
        .R(1'b0));
  FDRE \slv_rdata_reg[6] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[6]),
        .Q(\slv_rdata_reg[8]_0 [5]),
        .R(1'b0));
  FDRE \slv_rdata_reg[7] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[7]),
        .Q(\slv_rdata_reg[8]_0 [6]),
        .R(1'b0));
  FDRE \slv_rdata_reg[8] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(D[8]),
        .Q(\slv_rdata_reg[8]_0 [7]),
        .R(1'b0));
  FDRE \slv_rdata_reg[9] 
       (.C(s_axi_aclk),
        .CE(s_axi_aresetn),
        .D(\slv_rdata[9]_i_1__2_n_0 ),
        .Q(\slv_rdata_reg[9]_0 ),
        .R(\slv_rdata_reg[11]_1 ));
  FDRE slv_rden_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(adc3slv_rden),
        .Q(slv_rden_r),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[0] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[0]),
        .Q(\slv_wdata_r_internal_reg_n_0_[0] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[10] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[10]),
        .Q(\slv_wdata_r_internal_reg_n_0_[10] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[11] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[11]),
        .Q(\slv_wdata_r_internal_reg_n_0_[11] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[1] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[1]),
        .Q(\slv_wdata_r_internal_reg_n_0_[1] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[2] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[2]),
        .Q(\slv_wdata_r_internal_reg_n_0_[2] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[3] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[3]),
        .Q(\slv_wdata_r_internal_reg_n_0_[3] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[4] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[4]),
        .Q(\slv_wdata_r_internal_reg_n_0_[4] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[5] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[5]),
        .Q(\slv_wdata_r_internal_reg_n_0_[5] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[6] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[6]),
        .Q(\slv_wdata_r_internal_reg_n_0_[6] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[7] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[7]),
        .Q(\slv_wdata_r_internal_reg_n_0_[7] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[8] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[8]),
        .Q(\slv_wdata_r_internal_reg_n_0_[8] ),
        .R(p_0_in));
  FDRE \slv_wdata_r_internal_reg[9] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[9]),
        .Q(\slv_wdata_r_internal_reg_n_0_[9] ),
        .R(p_0_in));
endmodule

(* ORIG_REF_NAME = "adc_exdes_cfg" *) 
module project_1_adc_sink_i_0_adc_exdes_cfg
   (enable,
    timeout_enable,
    enable_reg_0,
    \timeout_value_reg[11]_0 ,
    p_0_in,
    enable_reg_1,
    s_axi_aclk,
    timeout_enable_reg_0,
    done_flag,
    Q,
    E,
    s_axi_wdata);
  output enable;
  output timeout_enable;
  output enable_reg_0;
  output [11:0]\timeout_value_reg[11]_0 ;
  input p_0_in;
  input enable_reg_1;
  input s_axi_aclk;
  input timeout_enable_reg_0;
  input done_flag;
  input [1:0]Q;
  input [0:0]E;
  input [11:0]s_axi_wdata;

  wire [0:0]E;
  wire [1:0]Q;
  wire done_flag;
  wire enable;
  wire enable_reg_0;
  wire enable_reg_1;
  wire p_0_in;
  wire s_axi_aclk;
  wire [11:0]s_axi_wdata;
  wire timeout_enable;
  wire timeout_enable_reg_0;
  wire [11:0]\timeout_value_reg[11]_0 ;

  LUT4 #(
    .INIT(16'h88A8)) 
    done_flag_i_1
       (.I0(enable),
        .I1(done_flag),
        .I2(Q[0]),
        .I3(Q[1]),
        .O(enable_reg_0));
  FDRE #(
    .INIT(1'b0)) 
    enable_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(enable_reg_1),
        .Q(enable),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    timeout_enable_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(timeout_enable_reg_0),
        .Q(timeout_enable),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[0] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[0]),
        .Q(\timeout_value_reg[11]_0 [0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[10] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[10]),
        .Q(\timeout_value_reg[11]_0 [10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[11] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[11]),
        .Q(\timeout_value_reg[11]_0 [11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[1] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[1]),
        .Q(\timeout_value_reg[11]_0 [1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[2] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[2]),
        .Q(\timeout_value_reg[11]_0 [2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[3] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[3]),
        .Q(\timeout_value_reg[11]_0 [3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[4] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[4]),
        .Q(\timeout_value_reg[11]_0 [4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[5] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[5]),
        .Q(\timeout_value_reg[11]_0 [5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[6] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[6]),
        .Q(\timeout_value_reg[11]_0 [6]),
        .R(p_0_in));
  FDSE #(
    .INIT(1'b1)) 
    \timeout_value_reg[7] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[7]),
        .Q(\timeout_value_reg[11]_0 [7]),
        .S(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[8] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[8]),
        .Q(\timeout_value_reg[11]_0 [8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \timeout_value_reg[9] 
       (.C(s_axi_aclk),
        .CE(E),
        .D(s_axi_wdata[9]),
        .Q(\timeout_value_reg[11]_0 [9]),
        .R(p_0_in));
endmodule

(* ORIG_REF_NAME = "exdes_rfadc_data_sink" *) 
module project_1_adc_sink_i_0_exdes_rfadc_data_sink
   (axi_awready_reg,
    s_axi_arready,
    axi_rvalid_reg,
    s_axi_wready,
    error_flag,
    s00_tready,
    s_axi_rdata,
    done_flag,
    axi_bvalid_reg,
    s_axi_bresp,
    s_axi_rresp,
    s_axi_arvalid,
    s_axi_awvalid,
    s_axi_aresetn,
    s_axi_araddr,
    s00_tdata,
    s0_axis_clock,
    s_axi_aclk,
    s_axi_wdata,
    s_axi_awaddr,
    s_axi_wvalid,
    s_axi_rready,
    s_axi_bready);
  output axi_awready_reg;
  output s_axi_arready;
  output axi_rvalid_reg;
  output s_axi_wready;
  output error_flag;
  output s00_tready;
  output [15:0]s_axi_rdata;
  output done_flag;
  output axi_bvalid_reg;
  output [0:0]s_axi_bresp;
  output [0:0]s_axi_rresp;
  input s_axi_arvalid;
  input s_axi_awvalid;
  input s_axi_aresetn;
  input [15:0]s_axi_araddr;
  input [127:0]s00_tdata;
  input s0_axis_clock;
  input s_axi_aclk;
  input [11:0]s_axi_wdata;
  input [15:0]s_axi_awaddr;
  input s_axi_wvalid;
  input s_axi_rready;
  input s_axi_bready;

  wire adc00_ds_pulse_control_0;
  wire axi_awready_reg;
  wire axi_bvalid_reg;
  wire axi_rvalid_reg;
  wire axis_resetn_rt_0;
  wire done_bus_rt_0;
  wire [1:0]done_delay;
  wire done_flag;
  wire error_bus_rt_0;
  wire error_flag;
  wire rfadc_exdes_ctrl_i_n_8;
  wire [7:0]s00_ds_inc;
  wire s00_ds_status;
  wire [127:0]s00_tdata;
  wire s00_tready;
  wire s0_axis_clock;
  wire s_axi_aclk;
  wire [15:0]s_axi_araddr;
  wire s_axi_aresetn;
  wire s_axi_arready;
  wire s_axi_arvalid;
  wire [15:0]s_axi_awaddr;
  wire s_axi_awvalid;
  wire s_axi_bready;
  wire [0:0]s_axi_bresp;
  wire [15:0]s_axi_rdata;
  wire s_axi_rready;
  wire [0:0]s_axi_rresp;
  wire [11:0]s_axi_wdata;
  wire s_axi_wready;
  wire s_axi_wvalid;

  (* DEF_VAL = "1'b0" *) 
  (* DEST_SYNC_FF = "5" *) 
  (* INIT = "0" *) 
  (* INIT_SYNC_FF = "1" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SYNC_RST" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_sync_rst cdc_arstn_0i
       (.dest_clk(s0_axis_clock),
        .dest_rst(axis_resetn_rt_0),
        .src_rst(s_axi_aresetn));
  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__11 cdc_done_0i
       (.dest_clk(s_axi_aclk),
        .dest_out(done_bus_rt_0),
        .src_clk(1'b0),
        .src_in(1'b0));
  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__10 cdc_error_0i
       (.dest_clk(s_axi_aclk),
        .dest_out(error_bus_rt_0),
        .src_clk(1'b0),
        .src_in(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \done_delay_reg[0] 
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(done_bus_rt_0),
        .Q(done_delay[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b1)) 
    \done_delay_reg[1] 
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(done_delay[0]),
        .Q(done_delay[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    done_flag_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(rfadc_exdes_ctrl_i_n_8),
        .Q(done_flag),
        .R(1'b0));
  project_1_adc_sink_i_0_xpm_mem_ds_dataCap ds_slice_00
       (.Q(s00_ds_inc),
        .adc00_ds_pulse_control_0(adc00_ds_pulse_control_0),
        .s00_ds_status(s00_ds_status),
        .s00_tdata(s00_tdata),
        .s0_axis_clock(s0_axis_clock));
  FDRE #(
    .INIT(1'b0)) 
    error_flag_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(error_bus_rt_0),
        .Q(error_flag),
        .R(1'b0));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl rfadc_exdes_ctrl_i
       (.D(done_bus_rt_0),
        .Q(done_delay),
        .\adc00_ds_inc_0_reg[7] (s00_ds_inc),
        .adc00_ds_pulse_control_0(adc00_ds_pulse_control_0),
        .axi_arready_reg(s_axi_arready),
        .axi_awready_reg(axi_awready_reg),
        .axi_bvalid_reg(axi_bvalid_reg),
        .axi_rvalid_reg(axi_rvalid_reg),
        .axi_wr_access_reg(s_axi_wready),
        .dest_out(error_bus_rt_0),
        .dest_rst(axis_resetn_rt_0),
        .done_flag(done_flag),
        .enable_reg(rfadc_exdes_ctrl_i_n_8),
        .error_flag(error_flag),
        .s00_ds_status(s00_ds_status),
        .s00_tdata(s00_tdata),
        .s00_tready(s00_tready),
        .s0_axis_clock(s0_axis_clock),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_araddr(s_axi_araddr),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_arvalid(s_axi_arvalid),
        .s_axi_awaddr(s_axi_awaddr),
        .s_axi_awvalid(s_axi_awvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_bresp(s_axi_bresp),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rready(s_axi_rready),
        .s_axi_rresp(s_axi_rresp),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wvalid(s_axi_wvalid));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl
   (axi_wr_access_reg,
    axi_arready_reg,
    adc00_ds_pulse_control_0,
    axi_rvalid_reg,
    axi_bvalid_reg,
    axi_awready_reg,
    s_axi_bresp,
    s_axi_rresp,
    enable_reg,
    \adc00_ds_inc_0_reg[7] ,
    s00_tready,
    s_axi_rdata,
    s0_axis_clock,
    s_axi_aclk,
    s_axi_arvalid,
    s_axi_awvalid,
    s_axi_aresetn,
    s_axi_araddr,
    s00_tdata,
    done_flag,
    Q,
    s_axi_awaddr,
    dest_out,
    D,
    s_axi_wvalid,
    s_axi_rready,
    s_axi_bready,
    error_flag,
    s00_ds_status,
    dest_rst,
    s_axi_wdata);
  output axi_wr_access_reg;
  output axi_arready_reg;
  output adc00_ds_pulse_control_0;
  output axi_rvalid_reg;
  output axi_bvalid_reg;
  output axi_awready_reg;
  output [0:0]s_axi_bresp;
  output [0:0]s_axi_rresp;
  output enable_reg;
  output [7:0]\adc00_ds_inc_0_reg[7] ;
  output s00_tready;
  output [15:0]s_axi_rdata;
  input s0_axis_clock;
  input s_axi_aclk;
  input s_axi_arvalid;
  input s_axi_awvalid;
  input s_axi_aresetn;
  input [15:0]s_axi_araddr;
  input [127:0]s00_tdata;
  input done_flag;
  input [1:0]Q;
  input [15:0]s_axi_awaddr;
  input dest_out;
  input [0:0]D;
  input s_axi_wvalid;
  input s_axi_rready;
  input s_axi_bready;
  input error_flag;
  input s00_ds_status;
  input dest_rst;
  input [11:0]s_axi_wdata;

  wire [0:0]D;
  wire [1:0]Q;
  wire [1:1]adc00_ds_control_0;
  wire [8:8]adc00_ds_inc_0;
  wire [7:0]\adc00_ds_inc_0_reg[7] ;
  wire adc00_ds_pulse_control_0;
  wire [3:0]adc00_ds_type_0;
  wire [8:8]adc01_ds_inc_0;
  wire [3:0]adc01_ds_type_0;
  wire [8:8]adc02_ds_inc_0;
  wire [3:0]adc02_ds_type_0;
  wire [8:8]adc03_ds_inc_0;
  wire [3:0]adc03_ds_type_0;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_18;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_19;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_20;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_21;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_22;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_23;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_24;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_25;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_26;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_27;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_28;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_29;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_3;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_30;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_31;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_32;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_33;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_34;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_4;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_44;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_46;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_47;
  wire adc0_rfadc_exdes_ctrl_axi_i_n_5;
  wire adc0axi_map_wready;
  wire adc0slv_rden;
  wire [7:2]adc10_ds_enable_0;
  wire [3:3]adc10_ds_type_0;
  wire [7:2]adc11_ds_enable_0;
  wire [3:3]adc11_ds_type_0;
  wire [7:2]adc12_ds_enable_0;
  wire [3:3]adc12_ds_type_0;
  wire [7:2]adc13_ds_enable_0;
  wire [3:3]adc13_ds_type_0;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_10;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_15;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_16;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_17;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_2;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_3;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_4;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_42;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_43;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_44;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_45;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_46;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_47;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_48;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_49;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_5;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_50;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_51;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_52;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_53;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_54;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_55;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_56;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_57;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_58;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_59;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_6;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_7;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_8;
  wire adc1_rfadc_exdes_ctrl_axi_i_n_9;
  wire adc1axi_map_wready;
  wire adc1slv_rden;
  wire [7:2]adc20_ds_enable_0;
  wire [7:2]adc21_ds_enable_0;
  wire [7:2]adc22_ds_enable_0;
  wire [7:2]adc23_ds_enable_0;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_2;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_29;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_3;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_30;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_31;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_32;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_33;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_34;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_35;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_36;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_37;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_38;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_39;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_4;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_40;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_41;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_42;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_43;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_44;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_45;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_46;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_47;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_48;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_49;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_5;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_50;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_6;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_7;
  wire adc2_rfadc_exdes_ctrl_axi_i_n_8;
  wire adc2axi_map_wready;
  wire adc2slv_rden;
  wire [7:2]adc30_ds_enable_0;
  wire [7:2]adc31_ds_enable_0;
  wire [7:2]adc32_ds_enable_0;
  wire [7:2]adc33_ds_enable_0;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_10;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_3;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_31;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_32;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_33;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_34;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_35;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_36;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_37;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_38;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_39;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_4;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_40;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_41;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_42;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_43;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_44;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_45;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_46;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_47;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_48;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_49;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_5;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_50;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_51;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_6;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_7;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_8;
  wire adc3_rfadc_exdes_ctrl_axi_i_n_9;
  wire adc3axi_map_wready;
  wire adc3slv_rden;
  wire adc_ds_axi_map_wready;
  wire adc_ds_slv_rden;
  wire axi_arready_reg;
  wire axi_awready_reg;
  wire axi_bvalid_reg;
  wire axi_register_if_i_n_17;
  wire axi_register_if_i_n_19;
  wire axi_register_if_i_n_20;
  wire axi_register_if_i_n_21;
  wire axi_register_if_i_n_22;
  wire axi_register_if_i_n_23;
  wire axi_register_if_i_n_24;
  wire axi_register_if_i_n_28;
  wire axi_register_if_i_n_29;
  wire axi_register_if_i_n_30;
  wire axi_register_if_i_n_31;
  wire axi_register_if_i_n_32;
  wire axi_register_if_i_n_33;
  wire axi_register_if_i_n_34;
  wire axi_register_if_i_n_35;
  wire axi_register_if_i_n_36;
  wire axi_register_if_i_n_37;
  wire axi_register_if_i_n_38;
  wire axi_register_if_i_n_39;
  wire axi_register_if_i_n_40;
  wire axi_register_if_i_n_41;
  wire axi_register_if_i_n_42;
  wire axi_register_if_i_n_43;
  wire axi_register_if_i_n_44;
  wire axi_register_if_i_n_45;
  wire axi_register_if_i_n_46;
  wire axi_register_if_i_n_47;
  wire axi_register_if_i_n_48;
  wire axi_register_if_i_n_49;
  wire axi_register_if_i_n_50;
  wire axi_register_if_i_n_51;
  wire axi_register_if_i_n_52;
  wire axi_register_if_i_n_53;
  wire axi_register_if_i_n_54;
  wire axi_register_if_i_n_55;
  wire axi_register_if_i_n_56;
  wire axi_register_if_i_n_57;
  wire axi_register_if_i_n_58;
  wire axi_register_if_i_n_59;
  wire axi_register_if_i_n_60;
  wire axi_register_if_i_n_61;
  wire axi_register_if_i_n_62;
  wire axi_register_if_i_n_63;
  wire axi_register_if_i_n_64;
  wire axi_register_if_i_n_65;
  wire axi_register_if_i_n_66;
  wire axi_register_if_i_n_67;
  wire axi_register_if_i_n_68;
  wire axi_register_if_i_n_69;
  wire axi_register_if_i_n_70;
  wire axi_register_if_i_n_71;
  wire axi_register_if_i_n_72;
  wire axi_register_if_i_n_73;
  wire axi_register_if_i_n_74;
  wire axi_register_if_i_n_75;
  wire axi_register_if_i_n_76;
  wire axi_register_if_i_n_77;
  wire axi_register_if_i_n_78;
  wire axi_register_if_i_n_79;
  wire axi_register_if_i_n_80;
  wire axi_register_if_i_n_81;
  wire axi_register_if_i_n_82;
  wire axi_register_if_i_n_83;
  wire axi_register_if_i_n_84;
  wire axi_register_if_i_n_85;
  wire axi_register_if_i_n_86;
  wire axi_register_if_i_n_87;
  wire axi_register_if_i_n_88;
  wire axi_register_if_i_n_89;
  wire axi_register_if_i_n_90;
  wire axi_register_if_i_n_91;
  wire axi_register_if_i_n_92;
  wire axi_register_if_i_n_93;
  wire axi_register_if_i_n_94;
  wire axi_register_if_i_n_95;
  wire axi_register_if_i_n_96;
  wire axi_register_if_i_n_97;
  wire axi_register_if_i_n_98;
  wire axi_register_if_i_n_99;
  wire axi_rvalid_reg;
  wire axi_wr_access_reg;
  wire dest_out;
  wire dest_rst;
  wire done_flag;
  wire enable;
  wire enable_reg;
  wire error_flag;
  wire p_0_in;
  wire p_0_in0;
  wire s00_ds_status;
  wire [127:0]s00_tdata;
  wire s00_tready;
  wire s0_axis_clock;
  wire s_axi_aclk;
  wire [15:0]s_axi_araddr;
  wire s_axi_aresetn;
  wire s_axi_arvalid;
  wire [15:0]s_axi_awaddr;
  wire s_axi_awvalid;
  wire s_axi_bready;
  wire [0:0]s_axi_bresp;
  wire [15:0]s_axi_rdata;
  wire s_axi_rready;
  wire [0:0]s_axi_rresp;
  wire [11:0]s_axi_wdata;
  wire s_axi_wvalid;
  wire [4:2]slv_addr;
  wire [15:0]slv_rdata;
  wire slv_rden_r;
  wire slv_rden_r_0;
  wire slv_rden_r_2;
  wire slv_rden_r_4;
  wire slv_wren_done_pulse;
  wire slv_wren_done_pulse_1;
  wire slv_wren_done_pulse_3;
  wire slv_wren_done_pulse_5;
  wire timeout_enable;
  wire [11:0]timeout_value;

  project_1_adc_sink_i_0_adc0_rfadc_exdes_ctrl_axi adc0_rfadc_exdes_ctrl_axi_i
       (.D({axi_register_if_i_n_80,axi_register_if_i_n_81,axi_register_if_i_n_82,axi_register_if_i_n_83,axi_register_if_i_n_84,axi_register_if_i_n_85}),
        .E(axi_register_if_i_n_90),
        .Q({p_0_in0,axi_register_if_i_n_19,axi_register_if_i_n_20,axi_register_if_i_n_21,axi_register_if_i_n_22,axi_register_if_i_n_24}),
        .\adc00_ds_control_0_reg[0]_0 (axi_register_if_i_n_71),
        .\adc00_ds_control_0_reg[1]_0 (adc00_ds_control_0),
        .\adc00_ds_enable_0_reg[0]_0 (axi_register_if_i_n_65),
        .\adc00_ds_inc_0_reg[0]_0 (axi_register_if_i_n_72),
        .\adc00_ds_inc_0_reg[8]_0 ({adc00_ds_inc_0,\adc00_ds_inc_0_reg[7] }),
        .adc00_ds_pulse_control_0(adc00_ds_pulse_control_0),
        .adc00_ds_pulse_control_0_reg_0(axi_register_if_i_n_36),
        .adc00_ds_pulse_control_0_reg_1(axi_register_if_i_n_88),
        .\adc00_ds_type_0_reg[3]_0 (adc00_ds_type_0),
        .\adc00_ds_type_0_reg[3]_1 (axi_register_if_i_n_70),
        .\adc01_ds_control_0_reg[0]_0 (axi_register_if_i_n_69),
        .\adc01_ds_enable_0_reg[0]_0 (axi_register_if_i_n_29),
        .\adc01_ds_inc_0_reg[0]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_46),
        .\adc01_ds_inc_0_reg[0]_1 (axi_register_if_i_n_87),
        .\adc01_ds_inc_0_reg[1]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_32),
        .\adc01_ds_inc_0_reg[2]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_30),
        .\adc01_ds_inc_0_reg[3]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_29),
        .\adc01_ds_inc_0_reg[4]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_26),
        .\adc01_ds_inc_0_reg[5]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_24),
        .\adc01_ds_inc_0_reg[6]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_22),
        .\adc01_ds_inc_0_reg[7]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_21),
        .\adc01_ds_inc_0_reg[8]_0 (adc01_ds_inc_0),
        .\adc01_ds_type_0_reg[0]_0 (axi_register_if_i_n_28),
        .\adc01_ds_type_0_reg[1]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_34),
        .\adc01_ds_type_0_reg[3]_0 ({adc01_ds_type_0[3:2],adc01_ds_type_0[0]}),
        .\adc02_ds_control_0_reg[0]_0 (axi_register_if_i_n_78),
        .\adc02_ds_enable_0_reg[0]_0 (axi_register_if_i_n_77),
        .\adc02_ds_inc_0_reg[0]_0 (axi_register_if_i_n_76),
        .\adc02_ds_inc_0_reg[8]_0 (adc02_ds_inc_0),
        .\adc02_ds_type_0_reg[0]_0 (axi_register_if_i_n_75),
        .\adc02_ds_type_0_reg[3]_0 ({adc02_ds_type_0[3:2],adc02_ds_type_0[0]}),
        .\adc03_ds_control_0_reg[0]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_44),
        .\adc03_ds_control_0_reg[1]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_3),
        .\adc03_ds_control_0_reg[1]_1 (axi_register_if_i_n_74),
        .\adc03_ds_enable_0_reg[0]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_47),
        .\adc03_ds_enable_0_reg[1]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_33),
        .\adc03_ds_enable_0_reg[2]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_31),
        .\adc03_ds_enable_0_reg[3]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_28),
        .\adc03_ds_enable_0_reg[4]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_27),
        .\adc03_ds_enable_0_reg[5]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_25),
        .\adc03_ds_enable_0_reg[6]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_23),
        .\adc03_ds_enable_0_reg[7]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_20),
        .\adc03_ds_enable_0_reg[7]_1 (axi_register_if_i_n_67),
        .\adc03_ds_inc_0_reg[0]_0 (axi_register_if_i_n_73),
        .\adc03_ds_inc_0_reg[10]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_18),
        .\adc03_ds_inc_0_reg[11]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_5),
        .\adc03_ds_inc_0_reg[8]_0 (adc03_ds_inc_0),
        .\adc03_ds_inc_0_reg[9]_0 (adc0_rfadc_exdes_ctrl_axi_i_n_19),
        .\adc03_ds_type_0_reg[0]_0 (axi_register_if_i_n_66),
        .\adc03_ds_type_0_reg[3]_0 ({adc03_ds_type_0[3:2],adc03_ds_type_0[0]}),
        .adc0axi_map_wready(adc0axi_map_wready),
        .adc0slv_rden(adc0slv_rden),
        .adc_ds_slv_rden(adc_ds_slv_rden),
        .\axi_rresp[1]_i_2 (axi_register_if_i_n_17),
        .dest_rst(dest_rst),
        .p_0_in(p_0_in),
        .s00_tready(s00_tready),
        .s0_axis_clock(s0_axis_clock),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_rdata(slv_rdata),
        .\slv_rdata_reg[12]_0 (axi_register_if_i_n_97),
        .\slv_rdata_reg[12]_1 (axi_register_if_i_n_86),
        .\slv_rdata_reg[13]_0 (axi_register_if_i_n_96),
        .\slv_rdata_reg[14]_0 (axi_register_if_i_n_95),
        .\slv_rdata_reg[15]_0 (axi_register_if_i_n_94),
        .\slv_rdata_reg[1]_0 (axi_register_if_i_n_89),
        .\slv_rdata_reg[2]_0 (axi_register_if_i_n_33),
        .\slv_rdata_reg[3]_0 (axi_register_if_i_n_34),
        .\slv_rdata_reg[4]_0 (axi_register_if_i_n_32),
        .\slv_rdata_reg[5]_0 (axi_register_if_i_n_31),
        .\slv_rdata_reg[6]_0 (axi_register_if_i_n_30),
        .\slv_rdata_reg[7]_0 (axi_register_if_i_n_35),
        .slv_rden_r(slv_rden_r),
        .slv_rden_r_reg_0(adc0_rfadc_exdes_ctrl_axi_i_n_4),
        .slv_wren_done_pulse(slv_wren_done_pulse));
  project_1_adc_sink_i_0_adc1_rfadc_exdes_ctrl_axi adc1_rfadc_exdes_ctrl_axi_i
       (.D({axi_register_if_i_n_38,axi_register_if_i_n_39,axi_register_if_i_n_40,axi_register_if_i_n_41,axi_register_if_i_n_42,axi_register_if_i_n_43,axi_register_if_i_n_44,axi_register_if_i_n_45,axi_register_if_i_n_46}),
        .E(axi_register_if_i_n_91),
        .Q({axi_register_if_i_n_20,axi_register_if_i_n_21,axi_register_if_i_n_23,slv_addr}),
        .\adc10_ds_control_0_reg[0]_0 (axi_register_if_i_n_71),
        .\adc10_ds_enable_0_reg[0]_0 (axi_register_if_i_n_65),
        .\adc10_ds_enable_0_reg[7]_0 (adc10_ds_enable_0),
        .\adc10_ds_inc_0_reg[0]_0 (axi_register_if_i_n_72),
        .\adc10_ds_type_0_reg[0]_0 (axi_register_if_i_n_70),
        .\adc10_ds_type_0_reg[3]_0 (adc10_ds_type_0),
        .\adc11_ds_control_0_reg[0]_0 (axi_register_if_i_n_69),
        .\adc11_ds_enable_0_reg[0]_0 (axi_register_if_i_n_29),
        .\adc11_ds_enable_0_reg[7]_0 (adc11_ds_enable_0),
        .\adc11_ds_inc_0_reg[0]_0 (axi_register_if_i_n_87),
        .\adc11_ds_type_0_reg[0]_0 (axi_register_if_i_n_28),
        .\adc11_ds_type_0_reg[3]_0 (adc11_ds_type_0),
        .\adc12_ds_control_0_reg[0]_0 (axi_register_if_i_n_78),
        .\adc12_ds_enable_0_reg[0]_0 (axi_register_if_i_n_77),
        .\adc12_ds_enable_0_reg[7]_0 (adc12_ds_enable_0),
        .\adc12_ds_inc_0_reg[0]_0 (axi_register_if_i_n_76),
        .\adc12_ds_type_0_reg[0]_0 (axi_register_if_i_n_75),
        .\adc12_ds_type_0_reg[3]_0 (adc12_ds_type_0),
        .\adc13_ds_control_0_reg[0]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_46),
        .\adc13_ds_control_0_reg[0]_1 (axi_register_if_i_n_74),
        .\adc13_ds_control_0_reg[1]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_16),
        .\adc13_ds_enable_0_reg[0]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_43),
        .\adc13_ds_enable_0_reg[0]_1 (axi_register_if_i_n_67),
        .\adc13_ds_enable_0_reg[1]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_17),
        .\adc13_ds_enable_0_reg[7]_0 (adc13_ds_enable_0),
        .\adc13_ds_inc_0_reg[0]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_45),
        .\adc13_ds_inc_0_reg[0]_1 (axi_register_if_i_n_73),
        .\adc13_ds_inc_0_reg[1]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_15),
        .\adc13_ds_inc_0_reg[2]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_9),
        .\adc13_ds_inc_0_reg[3]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_8),
        .\adc13_ds_inc_0_reg[4]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_7),
        .\adc13_ds_inc_0_reg[5]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_6),
        .\adc13_ds_inc_0_reg[6]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_5),
        .\adc13_ds_inc_0_reg[7]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_4),
        .\adc13_ds_inc_0_reg[8]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_3),
        .\adc13_ds_type_0_reg[0]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_44),
        .\adc13_ds_type_0_reg[0]_1 (axi_register_if_i_n_66),
        .\adc13_ds_type_0_reg[1]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_42),
        .\adc13_ds_type_0_reg[2]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_10),
        .\adc13_ds_type_0_reg[3]_0 (adc13_ds_type_0),
        .adc1axi_map_wready(adc1axi_map_wready),
        .adc1slv_rden(adc1slv_rden),
        .adc_ds_axi_map_wready(adc_ds_axi_map_wready),
        .p_0_in(p_0_in),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wvalid(s_axi_wvalid),
        .\slv_addr_reg[6] (adc1_rfadc_exdes_ctrl_axi_i_n_57),
        .\slv_rdata_reg[10]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_58),
        .\slv_rdata_reg[11]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_56),
        .\slv_rdata_reg[11]_1 (axi_register_if_i_n_79),
        .\slv_rdata_reg[8]_0 ({adc1_rfadc_exdes_ctrl_axi_i_n_47,adc1_rfadc_exdes_ctrl_axi_i_n_48,adc1_rfadc_exdes_ctrl_axi_i_n_49,adc1_rfadc_exdes_ctrl_axi_i_n_50,adc1_rfadc_exdes_ctrl_axi_i_n_51,adc1_rfadc_exdes_ctrl_axi_i_n_52,adc1_rfadc_exdes_ctrl_axi_i_n_53,adc1_rfadc_exdes_ctrl_axi_i_n_54,adc1_rfadc_exdes_ctrl_axi_i_n_55}),
        .\slv_rdata_reg[9]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_59),
        .slv_rden_r(slv_rden_r_0),
        .slv_rden_r_1(slv_rden_r),
        .slv_rden_r_reg_0(adc1_rfadc_exdes_ctrl_axi_i_n_2),
        .slv_wren_done_pulse(slv_wren_done_pulse_1),
        .slv_wren_done_pulse_0(slv_wren_done_pulse));
  project_1_adc_sink_i_0_adc2_rfadc_exdes_ctrl_axi adc2_rfadc_exdes_ctrl_axi_i
       (.D({axi_register_if_i_n_47,axi_register_if_i_n_48,axi_register_if_i_n_49,axi_register_if_i_n_50,axi_register_if_i_n_51,axi_register_if_i_n_52,axi_register_if_i_n_53,axi_register_if_i_n_54,axi_register_if_i_n_55}),
        .E(axi_register_if_i_n_92),
        .Q(axi_register_if_i_n_17),
        .\adc20_ds_control_0_reg[0]_0 (axi_register_if_i_n_71),
        .\adc20_ds_enable_0_reg[0]_0 (axi_register_if_i_n_65),
        .\adc20_ds_enable_0_reg[7]_0 ({adc20_ds_enable_0[7:4],adc20_ds_enable_0[2]}),
        .\adc20_ds_inc_0_reg[0]_0 (axi_register_if_i_n_72),
        .\adc20_ds_type_0_reg[0]_0 (axi_register_if_i_n_70),
        .\adc21_ds_control_0_reg[0]_0 (axi_register_if_i_n_69),
        .\adc21_ds_enable_0_reg[0]_0 (axi_register_if_i_n_29),
        .\adc21_ds_enable_0_reg[7]_0 ({adc21_ds_enable_0[7:4],adc21_ds_enable_0[2]}),
        .\adc21_ds_inc_0_reg[0]_0 (axi_register_if_i_n_87),
        .\adc21_ds_type_0_reg[0]_0 (axi_register_if_i_n_28),
        .\adc22_ds_control_0_reg[0]_0 (axi_register_if_i_n_78),
        .\adc22_ds_enable_0_reg[0]_0 (axi_register_if_i_n_77),
        .\adc22_ds_enable_0_reg[7]_0 ({adc22_ds_enable_0[7:4],adc22_ds_enable_0[2]}),
        .\adc22_ds_inc_0_reg[0]_0 (axi_register_if_i_n_76),
        .\adc22_ds_type_0_reg[0]_0 (axi_register_if_i_n_75),
        .\adc23_ds_control_0_reg[0]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_38),
        .\adc23_ds_control_0_reg[0]_1 (axi_register_if_i_n_74),
        .\adc23_ds_control_0_reg[1]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_33),
        .\adc23_ds_enable_0_reg[0]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_35),
        .\adc23_ds_enable_0_reg[0]_1 (axi_register_if_i_n_67),
        .\adc23_ds_enable_0_reg[1]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_31),
        .\adc23_ds_enable_0_reg[7]_0 ({adc23_ds_enable_0[7:4],adc23_ds_enable_0[2]}),
        .\adc23_ds_inc_0_reg[0]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_37),
        .\adc23_ds_inc_0_reg[0]_1 (axi_register_if_i_n_73),
        .\adc23_ds_inc_0_reg[1]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_34),
        .\adc23_ds_inc_0_reg[2]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_29),
        .\adc23_ds_inc_0_reg[4]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_8),
        .\adc23_ds_inc_0_reg[5]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_7),
        .\adc23_ds_inc_0_reg[6]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_6),
        .\adc23_ds_inc_0_reg[7]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_5),
        .\adc23_ds_inc_0_reg[8]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_4),
        .\adc23_ds_type_0_reg[0]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_36),
        .\adc23_ds_type_0_reg[0]_1 (axi_register_if_i_n_66),
        .\adc23_ds_type_0_reg[1]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_32),
        .\adc23_ds_type_0_reg[2]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_30),
        .adc2axi_map_wready(adc2axi_map_wready),
        .adc2slv_rden(adc2slv_rden),
        .p_0_in(p_0_in),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wvalid(s_axi_wvalid),
        .\slv_addr_reg[2] (adc2_rfadc_exdes_ctrl_axi_i_n_3),
        .\slv_rdata_reg[10]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_49),
        .\slv_rdata_reg[11]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_48),
        .\slv_rdata_reg[11]_1 ({axi_register_if_i_n_20,axi_register_if_i_n_21,slv_addr}),
        .\slv_rdata_reg[11]_2 (adc1_rfadc_exdes_ctrl_axi_i_n_57),
        .\slv_rdata_reg[8]_0 ({adc2_rfadc_exdes_ctrl_axi_i_n_39,adc2_rfadc_exdes_ctrl_axi_i_n_40,adc2_rfadc_exdes_ctrl_axi_i_n_41,adc2_rfadc_exdes_ctrl_axi_i_n_42,adc2_rfadc_exdes_ctrl_axi_i_n_43,adc2_rfadc_exdes_ctrl_axi_i_n_44,adc2_rfadc_exdes_ctrl_axi_i_n_45,adc2_rfadc_exdes_ctrl_axi_i_n_46,adc2_rfadc_exdes_ctrl_axi_i_n_47}),
        .\slv_rdata_reg[9]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_50),
        .slv_rden_r(slv_rden_r_2),
        .slv_rden_r_0(slv_rden_r_0),
        .slv_rden_r_reg_0(adc2_rfadc_exdes_ctrl_axi_i_n_2),
        .slv_wren_done_pulse(slv_wren_done_pulse_3),
        .slv_wren_done_pulse_1(slv_wren_done_pulse_1));
  project_1_adc_sink_i_0_adc3_rfadc_exdes_ctrl_axi adc3_rfadc_exdes_ctrl_axi_i
       (.D({axi_register_if_i_n_56,axi_register_if_i_n_57,axi_register_if_i_n_58,axi_register_if_i_n_59,axi_register_if_i_n_60,axi_register_if_i_n_61,axi_register_if_i_n_62,axi_register_if_i_n_63,axi_register_if_i_n_64}),
        .E(axi_register_if_i_n_93),
        .Q({axi_register_if_i_n_20,axi_register_if_i_n_21,slv_addr}),
        .\adc30_ds_control_0_reg[0]_0 (axi_register_if_i_n_71),
        .\adc30_ds_enable_0_reg[0]_0 (axi_register_if_i_n_65),
        .\adc30_ds_enable_0_reg[7]_0 ({adc30_ds_enable_0[7:4],adc30_ds_enable_0[2]}),
        .\adc30_ds_inc_0_reg[0]_0 (axi_register_if_i_n_72),
        .\adc30_ds_type_0_reg[0]_0 (axi_register_if_i_n_70),
        .\adc31_ds_control_0_reg[0]_0 (axi_register_if_i_n_69),
        .\adc31_ds_enable_0_reg[0]_0 (axi_register_if_i_n_29),
        .\adc31_ds_enable_0_reg[7]_0 ({adc31_ds_enable_0[7:4],adc31_ds_enable_0[2]}),
        .\adc31_ds_inc_0_reg[0]_0 (axi_register_if_i_n_87),
        .\adc31_ds_type_0_reg[0]_0 (axi_register_if_i_n_28),
        .\adc32_ds_control_0_reg[0]_0 (axi_register_if_i_n_78),
        .\adc32_ds_enable_0_reg[0]_0 (axi_register_if_i_n_77),
        .\adc32_ds_enable_0_reg[7]_0 ({adc32_ds_enable_0[7:4],adc32_ds_enable_0[2]}),
        .\adc32_ds_inc_0_reg[0]_0 (axi_register_if_i_n_76),
        .\adc32_ds_type_0_reg[0]_0 (axi_register_if_i_n_75),
        .\adc33_ds_control_0_reg[0]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_39),
        .\adc33_ds_control_0_reg[0]_1 (axi_register_if_i_n_74),
        .\adc33_ds_control_0_reg[1]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_36),
        .\adc33_ds_enable_0_reg[0]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_37),
        .\adc33_ds_enable_0_reg[0]_1 (axi_register_if_i_n_67),
        .\adc33_ds_enable_0_reg[1]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_33),
        .\adc33_ds_enable_0_reg[7]_0 ({adc33_ds_enable_0[7:4],adc33_ds_enable_0[2]}),
        .\adc33_ds_inc_0_reg[0]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_40),
        .\adc33_ds_inc_0_reg[0]_1 (axi_register_if_i_n_73),
        .\adc33_ds_inc_0_reg[1]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_35),
        .\adc33_ds_inc_0_reg[2]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_31),
        .\adc33_ds_inc_0_reg[4]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_10),
        .\adc33_ds_inc_0_reg[5]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_9),
        .\adc33_ds_inc_0_reg[6]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_8),
        .\adc33_ds_inc_0_reg[7]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_7),
        .\adc33_ds_inc_0_reg[8]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_6),
        .\adc33_ds_type_0_reg[0]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_38),
        .\adc33_ds_type_0_reg[0]_1 (axi_register_if_i_n_66),
        .\adc33_ds_type_0_reg[1]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_34),
        .\adc33_ds_type_0_reg[2]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_32),
        .adc3axi_map_wready(adc3axi_map_wready),
        .adc3slv_rden(adc3slv_rden),
        .\axi_rdata_reg[0] (axi_register_if_i_n_37),
        .clk1_ready_pulse_reg(adc3_rfadc_exdes_ctrl_axi_i_n_5),
        .p_0_in(p_0_in),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wvalid(s_axi_wvalid),
        .\slv_addr_reg[3] (adc3_rfadc_exdes_ctrl_axi_i_n_4),
        .\slv_rdata_reg[0]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_3),
        .\slv_rdata_reg[10]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_50),
        .\slv_rdata_reg[11]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_49),
        .\slv_rdata_reg[11]_1 (adc1_rfadc_exdes_ctrl_axi_i_n_57),
        .\slv_rdata_reg[8]_0 ({adc3_rfadc_exdes_ctrl_axi_i_n_41,adc3_rfadc_exdes_ctrl_axi_i_n_42,adc3_rfadc_exdes_ctrl_axi_i_n_43,adc3_rfadc_exdes_ctrl_axi_i_n_44,adc3_rfadc_exdes_ctrl_axi_i_n_45,adc3_rfadc_exdes_ctrl_axi_i_n_46,adc3_rfadc_exdes_ctrl_axi_i_n_47,adc3_rfadc_exdes_ctrl_axi_i_n_48}),
        .\slv_rdata_reg[9]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_51),
        .slv_rden_r(slv_rden_r_4),
        .slv_rden_r_0(slv_rden_r_2),
        .slv_wren_done_pulse(slv_wren_done_pulse_5),
        .slv_wren_done_pulse_1(slv_wren_done_pulse_3));
  project_1_adc_sink_i_0_adc_exdes_cfg adc_exdes_cfg_i
       (.E(axi_register_if_i_n_68),
        .Q(Q),
        .done_flag(done_flag),
        .enable(enable),
        .enable_reg_0(enable_reg),
        .enable_reg_1(axi_register_if_i_n_98),
        .p_0_in(p_0_in),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wdata(s_axi_wdata),
        .timeout_enable(timeout_enable),
        .timeout_enable_reg_0(axi_register_if_i_n_99),
        .\timeout_value_reg[11]_0 (timeout_value));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_axi axi_register_if_i
       (.D(D),
        .E(axi_register_if_i_n_68),
        .Q(axi_register_if_i_n_17),
        .adc0axi_map_wready(adc0axi_map_wready),
        .adc0slv_rden(adc0slv_rden),
        .adc1axi_map_wready(adc1axi_map_wready),
        .adc1slv_rden(adc1slv_rden),
        .adc2axi_map_wready(adc2axi_map_wready),
        .adc2slv_rden(adc2slv_rden),
        .adc2slv_rden_reg_0(adc2_rfadc_exdes_ctrl_axi_i_n_2),
        .adc2slv_rden_reg_1(adc0_rfadc_exdes_ctrl_axi_i_n_4),
        .adc3axi_map_wready(adc3axi_map_wready),
        .adc3slv_rden(adc3slv_rden),
        .adc_ds_axi_map_wready(adc_ds_axi_map_wready),
        .adc_ds_slv_rden(adc_ds_slv_rden),
        .axi_arready_reg_0(axi_arready_reg),
        .axi_awready_reg_0(axi_awready_reg),
        .\axi_bresp_reg[1]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_2),
        .\axi_bresp_reg[1]_1 (adc3_rfadc_exdes_ctrl_axi_i_n_5),
        .axi_bvalid_reg_0(axi_bvalid_reg),
        .\axi_rdata[8]_i_2_0 ({adc2_rfadc_exdes_ctrl_axi_i_n_39,adc2_rfadc_exdes_ctrl_axi_i_n_40,adc2_rfadc_exdes_ctrl_axi_i_n_41,adc2_rfadc_exdes_ctrl_axi_i_n_42,adc2_rfadc_exdes_ctrl_axi_i_n_43,adc2_rfadc_exdes_ctrl_axi_i_n_44,adc2_rfadc_exdes_ctrl_axi_i_n_45,adc2_rfadc_exdes_ctrl_axi_i_n_46,adc2_rfadc_exdes_ctrl_axi_i_n_47}),
        .\axi_rdata[8]_i_2_1 ({adc1_rfadc_exdes_ctrl_axi_i_n_47,adc1_rfadc_exdes_ctrl_axi_i_n_48,adc1_rfadc_exdes_ctrl_axi_i_n_49,adc1_rfadc_exdes_ctrl_axi_i_n_50,adc1_rfadc_exdes_ctrl_axi_i_n_51,adc1_rfadc_exdes_ctrl_axi_i_n_52,adc1_rfadc_exdes_ctrl_axi_i_n_53,adc1_rfadc_exdes_ctrl_axi_i_n_54,adc1_rfadc_exdes_ctrl_axi_i_n_55}),
        .\axi_rdata_reg[0]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_3),
        .\axi_rdata_reg[10]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_50),
        .\axi_rdata_reg[10]_1 (adc2_rfadc_exdes_ctrl_axi_i_n_49),
        .\axi_rdata_reg[10]_2 (adc1_rfadc_exdes_ctrl_axi_i_n_58),
        .\axi_rdata_reg[11]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_49),
        .\axi_rdata_reg[11]_1 (timeout_value),
        .\axi_rdata_reg[11]_2 (adc2_rfadc_exdes_ctrl_axi_i_n_48),
        .\axi_rdata_reg[11]_3 (adc1_rfadc_exdes_ctrl_axi_i_n_56),
        .\axi_rdata_reg[8]_0 ({adc3_rfadc_exdes_ctrl_axi_i_n_41,adc3_rfadc_exdes_ctrl_axi_i_n_42,adc3_rfadc_exdes_ctrl_axi_i_n_43,adc3_rfadc_exdes_ctrl_axi_i_n_44,adc3_rfadc_exdes_ctrl_axi_i_n_45,adc3_rfadc_exdes_ctrl_axi_i_n_46,adc3_rfadc_exdes_ctrl_axi_i_n_47,adc3_rfadc_exdes_ctrl_axi_i_n_48}),
        .\axi_rdata_reg[9]_0 (adc3_rfadc_exdes_ctrl_axi_i_n_51),
        .\axi_rdata_reg[9]_1 (adc2_rfadc_exdes_ctrl_axi_i_n_50),
        .\axi_rdata_reg[9]_2 (adc1_rfadc_exdes_ctrl_axi_i_n_59),
        .axi_rvalid_reg_0(axi_rvalid_reg),
        .axi_wr_access_reg_0(axi_wr_access_reg),
        .dest_out(dest_out),
        .enable(enable),
        .error_flag(error_flag),
        .p_0_in(p_0_in),
        .s00_ds_status(s00_ds_status),
        .s00_tdata(s00_tdata),
        .s00_tdata_50_sp_1(axi_register_if_i_n_33),
        .s00_tdata_52_sp_1(axi_register_if_i_n_32),
        .s00_tdata_53_sp_1(axi_register_if_i_n_31),
        .s00_tdata_54_sp_1(axi_register_if_i_n_30),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_araddr(s_axi_araddr),
        .s_axi_aresetn(s_axi_aresetn),
        .s_axi_arvalid(s_axi_arvalid),
        .s_axi_awaddr(s_axi_awaddr),
        .s_axi_awvalid(s_axi_awvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_bresp(s_axi_bresp),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rready(s_axi_rready),
        .s_axi_rresp(s_axi_rresp),
        .s_axi_wdata(s_axi_wdata[0]),
        .\s_axi_wdata[0]_0 (axi_register_if_i_n_99),
        .s_axi_wdata_0_sp_1(axi_register_if_i_n_98),
        .s_axi_wvalid(s_axi_wvalid),
        .\slv_addr_reg[11]_0 ({p_0_in0,axi_register_if_i_n_19,axi_register_if_i_n_20,axi_register_if_i_n_21,axi_register_if_i_n_22,axi_register_if_i_n_23,axi_register_if_i_n_24,slv_addr}),
        .\slv_addr_reg[2]_0 (axi_register_if_i_n_28),
        .\slv_addr_reg[2]_1 (axi_register_if_i_n_29),
        .\slv_addr_reg[2]_10 (axi_register_if_i_n_96),
        .\slv_addr_reg[2]_11 (axi_register_if_i_n_97),
        .\slv_addr_reg[2]_2 ({axi_register_if_i_n_38,axi_register_if_i_n_39,axi_register_if_i_n_40,axi_register_if_i_n_41,axi_register_if_i_n_42,axi_register_if_i_n_43,axi_register_if_i_n_44,axi_register_if_i_n_45,axi_register_if_i_n_46}),
        .\slv_addr_reg[2]_3 ({axi_register_if_i_n_47,axi_register_if_i_n_48,axi_register_if_i_n_49,axi_register_if_i_n_50,axi_register_if_i_n_51,axi_register_if_i_n_52,axi_register_if_i_n_53,axi_register_if_i_n_54,axi_register_if_i_n_55}),
        .\slv_addr_reg[2]_4 ({axi_register_if_i_n_56,axi_register_if_i_n_57,axi_register_if_i_n_58,axi_register_if_i_n_59,axi_register_if_i_n_60,axi_register_if_i_n_61,axi_register_if_i_n_62,axi_register_if_i_n_63,axi_register_if_i_n_64}),
        .\slv_addr_reg[2]_5 (axi_register_if_i_n_73),
        .\slv_addr_reg[2]_6 (axi_register_if_i_n_76),
        .\slv_addr_reg[2]_7 (axi_register_if_i_n_88),
        .\slv_addr_reg[2]_8 (axi_register_if_i_n_94),
        .\slv_addr_reg[2]_9 (axi_register_if_i_n_95),
        .\slv_addr_reg[3]_0 (axi_register_if_i_n_67),
        .\slv_addr_reg[3]_1 (axi_register_if_i_n_74),
        .\slv_addr_reg[3]_2 (axi_register_if_i_n_78),
        .\slv_addr_reg[3]_3 (axi_register_if_i_n_89),
        .\slv_addr_reg[4]_0 ({axi_register_if_i_n_80,axi_register_if_i_n_81,axi_register_if_i_n_82,axi_register_if_i_n_83,axi_register_if_i_n_84,axi_register_if_i_n_85}),
        .\slv_addr_reg[4]_1 (axi_register_if_i_n_87),
        .\slv_addr_reg[5]_0 (axi_register_if_i_n_34),
        .\slv_addr_reg[5]_1 (axi_register_if_i_n_35),
        .\slv_addr_reg[5]_2 (axi_register_if_i_n_75),
        .\slv_addr_reg[5]_3 (axi_register_if_i_n_79),
        .\slv_addr_reg[6]_0 (axi_register_if_i_n_65),
        .\slv_addr_reg[6]_1 (axi_register_if_i_n_70),
        .\slv_addr_reg[6]_2 (axi_register_if_i_n_71),
        .\slv_addr_reg[6]_3 (axi_register_if_i_n_72),
        .\slv_addr_reg[6]_4 (axi_register_if_i_n_77),
        .\slv_addr_reg[6]_5 (axi_register_if_i_n_86),
        .\slv_addr_reg[8]_0 (axi_register_if_i_n_36),
        .\slv_addr_reg[8]_1 (axi_register_if_i_n_66),
        .\slv_addr_reg[8]_2 (axi_register_if_i_n_69),
        .\slv_rd_addr_reg[5]_0 (axi_register_if_i_n_37),
        .slv_rdata(slv_rdata),
        .\slv_rdata[3]_i_5_0 (adc13_ds_type_0),
        .\slv_rdata[3]_i_5_1 (adc11_ds_type_0),
        .\slv_rdata[8]_i_3_0 (adc03_ds_inc_0),
        .\slv_rdata[8]_i_3_1 (adc01_ds_inc_0),
        .\slv_rdata_reg[0] (adc1_rfadc_exdes_ctrl_axi_i_n_44),
        .\slv_rdata_reg[0]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_43),
        .\slv_rdata_reg[0]_1 (adc1_rfadc_exdes_ctrl_axi_i_n_45),
        .\slv_rdata_reg[0]_10 (adc3_rfadc_exdes_ctrl_axi_i_n_40),
        .\slv_rdata_reg[0]_11 (adc0_rfadc_exdes_ctrl_axi_i_n_47),
        .\slv_rdata_reg[0]_12 (adc0_rfadc_exdes_ctrl_axi_i_n_44),
        .\slv_rdata_reg[0]_13 (adc0_rfadc_exdes_ctrl_axi_i_n_46),
        .\slv_rdata_reg[0]_2 (adc1_rfadc_exdes_ctrl_axi_i_n_46),
        .\slv_rdata_reg[0]_3 (adc2_rfadc_exdes_ctrl_axi_i_n_36),
        .\slv_rdata_reg[0]_4 (adc2_rfadc_exdes_ctrl_axi_i_n_35),
        .\slv_rdata_reg[0]_5 (adc2_rfadc_exdes_ctrl_axi_i_n_37),
        .\slv_rdata_reg[0]_6 (adc2_rfadc_exdes_ctrl_axi_i_n_38),
        .\slv_rdata_reg[0]_7 (adc3_rfadc_exdes_ctrl_axi_i_n_38),
        .\slv_rdata_reg[0]_8 (adc3_rfadc_exdes_ctrl_axi_i_n_37),
        .\slv_rdata_reg[0]_9 (adc3_rfadc_exdes_ctrl_axi_i_n_39),
        .\slv_rdata_reg[10] (adc0_rfadc_exdes_ctrl_axi_i_n_18),
        .\slv_rdata_reg[11] (adc0_rfadc_exdes_ctrl_axi_i_n_5),
        .\slv_rdata_reg[1] (adc1_rfadc_exdes_ctrl_axi_i_n_42),
        .\slv_rdata_reg[1]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_17),
        .\slv_rdata_reg[1]_1 (adc1_rfadc_exdes_ctrl_axi_i_n_15),
        .\slv_rdata_reg[1]_10 (adc3_rfadc_exdes_ctrl_axi_i_n_36),
        .\slv_rdata_reg[1]_11 (adc0_rfadc_exdes_ctrl_axi_i_n_3),
        .\slv_rdata_reg[1]_12 (adc0_rfadc_exdes_ctrl_axi_i_n_33),
        .\slv_rdata_reg[1]_13 (adc0_rfadc_exdes_ctrl_axi_i_n_34),
        .\slv_rdata_reg[1]_14 (adc00_ds_control_0),
        .\slv_rdata_reg[1]_15 (adc0_rfadc_exdes_ctrl_axi_i_n_32),
        .\slv_rdata_reg[1]_2 (adc1_rfadc_exdes_ctrl_axi_i_n_16),
        .\slv_rdata_reg[1]_3 (adc2_rfadc_exdes_ctrl_axi_i_n_32),
        .\slv_rdata_reg[1]_4 (adc2_rfadc_exdes_ctrl_axi_i_n_31),
        .\slv_rdata_reg[1]_5 (adc2_rfadc_exdes_ctrl_axi_i_n_33),
        .\slv_rdata_reg[1]_6 (adc2_rfadc_exdes_ctrl_axi_i_n_34),
        .\slv_rdata_reg[1]_7 (adc3_rfadc_exdes_ctrl_axi_i_n_34),
        .\slv_rdata_reg[1]_8 (adc3_rfadc_exdes_ctrl_axi_i_n_33),
        .\slv_rdata_reg[1]_9 (adc3_rfadc_exdes_ctrl_axi_i_n_35),
        .\slv_rdata_reg[2] (adc1_rfadc_exdes_ctrl_axi_i_n_10),
        .\slv_rdata_reg[2]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_9),
        .\slv_rdata_reg[2]_1 (adc2_rfadc_exdes_ctrl_axi_i_n_30),
        .\slv_rdata_reg[2]_2 (adc2_rfadc_exdes_ctrl_axi_i_n_29),
        .\slv_rdata_reg[2]_3 (adc3_rfadc_exdes_ctrl_axi_i_n_32),
        .\slv_rdata_reg[2]_4 (adc3_rfadc_exdes_ctrl_axi_i_n_31),
        .\slv_rdata_reg[2]_5 (adc0_rfadc_exdes_ctrl_axi_i_n_30),
        .\slv_rdata_reg[2]_6 (adc0_rfadc_exdes_ctrl_axi_i_n_31),
        .\slv_rdata_reg[3] (adc3_rfadc_exdes_ctrl_axi_i_n_4),
        .\slv_rdata_reg[3]_0 (adc1_rfadc_exdes_ctrl_axi_i_n_8),
        .\slv_rdata_reg[3]_1 (adc2_rfadc_exdes_ctrl_axi_i_n_3),
        .\slv_rdata_reg[3]_2 ({adc03_ds_type_0[3:2],adc03_ds_type_0[0]}),
        .\slv_rdata_reg[3]_3 ({adc02_ds_type_0[3:2],adc02_ds_type_0[0]}),
        .\slv_rdata_reg[3]_4 ({adc01_ds_type_0[3:2],adc01_ds_type_0[0]}),
        .\slv_rdata_reg[3]_5 (adc12_ds_type_0),
        .\slv_rdata_reg[3]_6 (adc10_ds_type_0),
        .\slv_rdata_reg[3]_7 (adc0_rfadc_exdes_ctrl_axi_i_n_29),
        .\slv_rdata_reg[3]_8 (adc00_ds_type_0),
        .\slv_rdata_reg[3]_9 (adc0_rfadc_exdes_ctrl_axi_i_n_28),
        .\slv_rdata_reg[4] (adc1_rfadc_exdes_ctrl_axi_i_n_7),
        .\slv_rdata_reg[4]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_8),
        .\slv_rdata_reg[4]_1 (adc3_rfadc_exdes_ctrl_axi_i_n_10),
        .\slv_rdata_reg[4]_2 (adc0_rfadc_exdes_ctrl_axi_i_n_26),
        .\slv_rdata_reg[4]_3 (adc0_rfadc_exdes_ctrl_axi_i_n_27),
        .\slv_rdata_reg[5] (adc1_rfadc_exdes_ctrl_axi_i_n_6),
        .\slv_rdata_reg[5]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_7),
        .\slv_rdata_reg[5]_1 (adc3_rfadc_exdes_ctrl_axi_i_n_9),
        .\slv_rdata_reg[5]_2 (adc0_rfadc_exdes_ctrl_axi_i_n_24),
        .\slv_rdata_reg[5]_3 (adc0_rfadc_exdes_ctrl_axi_i_n_25),
        .\slv_rdata_reg[6] (adc1_rfadc_exdes_ctrl_axi_i_n_5),
        .\slv_rdata_reg[6]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_6),
        .\slv_rdata_reg[6]_1 (adc3_rfadc_exdes_ctrl_axi_i_n_8),
        .\slv_rdata_reg[6]_2 (adc0_rfadc_exdes_ctrl_axi_i_n_22),
        .\slv_rdata_reg[6]_3 (adc0_rfadc_exdes_ctrl_axi_i_n_23),
        .\slv_rdata_reg[7] (adc13_ds_enable_0),
        .\slv_rdata_reg[7]_0 (adc11_ds_enable_0),
        .\slv_rdata_reg[7]_1 ({adc23_ds_enable_0[7:4],adc23_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_10 (adc12_ds_enable_0),
        .\slv_rdata_reg[7]_11 (adc1_rfadc_exdes_ctrl_axi_i_n_4),
        .\slv_rdata_reg[7]_12 (adc2_rfadc_exdes_ctrl_axi_i_n_5),
        .\slv_rdata_reg[7]_13 (adc3_rfadc_exdes_ctrl_axi_i_n_7),
        .\slv_rdata_reg[7]_14 (adc0_rfadc_exdes_ctrl_axi_i_n_21),
        .\slv_rdata_reg[7]_15 (adc0_rfadc_exdes_ctrl_axi_i_n_20),
        .\slv_rdata_reg[7]_2 ({adc21_ds_enable_0[7:4],adc21_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_3 ({adc22_ds_enable_0[7:4],adc22_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_4 ({adc20_ds_enable_0[7:4],adc20_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_5 ({adc33_ds_enable_0[7:4],adc33_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_6 ({adc31_ds_enable_0[7:4],adc31_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_7 ({adc32_ds_enable_0[7:4],adc32_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_8 ({adc30_ds_enable_0[7:4],adc30_ds_enable_0[2]}),
        .\slv_rdata_reg[7]_9 (adc10_ds_enable_0),
        .\slv_rdata_reg[8] (adc3_rfadc_exdes_ctrl_axi_i_n_6),
        .\slv_rdata_reg[8]_0 (adc2_rfadc_exdes_ctrl_axi_i_n_4),
        .\slv_rdata_reg[8]_1 (adc1_rfadc_exdes_ctrl_axi_i_n_3),
        .\slv_rdata_reg[8]_2 ({adc00_ds_inc_0,\adc00_ds_inc_0_reg[7] }),
        .\slv_rdata_reg[8]_3 (adc02_ds_inc_0),
        .\slv_rdata_reg[9] (adc0_rfadc_exdes_ctrl_axi_i_n_19),
        .slv_rden_r(slv_rden_r_4),
        .slv_rden_r_0(slv_rden_r),
        .slv_rden_r_1(slv_rden_r_0),
        .slv_rden_r_2(slv_rden_r_2),
        .slv_rden_r_reg(axi_register_if_i_n_90),
        .slv_rden_r_reg_0(axi_register_if_i_n_91),
        .slv_rden_r_reg_1(axi_register_if_i_n_92),
        .slv_rden_r_reg_2(axi_register_if_i_n_93),
        .slv_wren_done_pulse(slv_wren_done_pulse_5),
        .timeout_enable(timeout_enable));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_axi" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_axi
   (adc_ds_slv_rden,
    adc2axi_map_wready,
    adc_ds_axi_map_wready,
    adc0axi_map_wready,
    adc1axi_map_wready,
    adc3axi_map_wready,
    axi_wr_access_reg_0,
    axi_arready_reg_0,
    adc0slv_rden,
    adc1slv_rden,
    adc2slv_rden,
    adc3slv_rden,
    axi_rvalid_reg_0,
    axi_bvalid_reg_0,
    axi_awready_reg_0,
    s_axi_bresp,
    s_axi_rresp,
    Q,
    \slv_addr_reg[11]_0 ,
    \slv_addr_reg[2]_0 ,
    \slv_addr_reg[2]_1 ,
    s00_tdata_54_sp_1,
    s00_tdata_53_sp_1,
    s00_tdata_52_sp_1,
    s00_tdata_50_sp_1,
    \slv_addr_reg[5]_0 ,
    \slv_addr_reg[5]_1 ,
    \slv_addr_reg[8]_0 ,
    \slv_rd_addr_reg[5]_0 ,
    \slv_addr_reg[2]_2 ,
    \slv_addr_reg[2]_3 ,
    \slv_addr_reg[2]_4 ,
    \slv_addr_reg[6]_0 ,
    \slv_addr_reg[8]_1 ,
    \slv_addr_reg[3]_0 ,
    E,
    \slv_addr_reg[8]_2 ,
    \slv_addr_reg[6]_1 ,
    \slv_addr_reg[6]_2 ,
    \slv_addr_reg[6]_3 ,
    \slv_addr_reg[2]_5 ,
    \slv_addr_reg[3]_1 ,
    \slv_addr_reg[5]_2 ,
    \slv_addr_reg[2]_6 ,
    \slv_addr_reg[6]_4 ,
    \slv_addr_reg[3]_2 ,
    \slv_addr_reg[5]_3 ,
    \slv_addr_reg[4]_0 ,
    \slv_addr_reg[6]_5 ,
    \slv_addr_reg[4]_1 ,
    \slv_addr_reg[2]_7 ,
    \slv_addr_reg[3]_3 ,
    slv_rden_r_reg,
    slv_rden_r_reg_0,
    slv_rden_r_reg_1,
    slv_rden_r_reg_2,
    \slv_addr_reg[2]_8 ,
    \slv_addr_reg[2]_9 ,
    \slv_addr_reg[2]_10 ,
    \slv_addr_reg[2]_11 ,
    s_axi_wdata_0_sp_1,
    \s_axi_wdata[0]_0 ,
    s_axi_rdata,
    s_axi_aclk,
    p_0_in,
    s_axi_arvalid,
    s_axi_awvalid,
    \axi_rdata_reg[9]_0 ,
    \axi_rdata_reg[10]_0 ,
    \axi_rdata_reg[11]_0 ,
    s_axi_aresetn,
    \slv_rdata_reg[7] ,
    \slv_rdata_reg[7]_0 ,
    \slv_rdata_reg[7]_1 ,
    \slv_rdata_reg[7]_2 ,
    \slv_rdata_reg[7]_3 ,
    \slv_rdata_reg[7]_4 ,
    \slv_rdata_reg[7]_5 ,
    \slv_rdata_reg[7]_6 ,
    \slv_rdata_reg[7]_7 ,
    \slv_rdata_reg[7]_8 ,
    s_axi_araddr,
    s00_tdata,
    \slv_rdata_reg[7]_9 ,
    \slv_rdata_reg[7]_10 ,
    s_axi_awaddr,
    \axi_rdata_reg[11]_1 ,
    \axi_rdata_reg[0]_0 ,
    dest_out,
    D,
    \axi_rdata_reg[8]_0 ,
    s_axi_wvalid,
    adc2slv_rden_reg_0,
    adc2slv_rden_reg_1,
    slv_wren_done_pulse,
    slv_rden_r,
    slv_rdata,
    s_axi_rready,
    s_axi_bready,
    timeout_enable,
    \slv_rdata_reg[7]_11 ,
    \slv_rdata_reg[6] ,
    \slv_rdata_reg[5] ,
    \slv_rdata_reg[4] ,
    \slv_rdata_reg[7]_12 ,
    \slv_rdata_reg[6]_0 ,
    \slv_rdata_reg[5]_0 ,
    \slv_rdata_reg[4]_0 ,
    \slv_rdata_reg[7]_13 ,
    \slv_rdata_reg[6]_1 ,
    \slv_rdata_reg[5]_1 ,
    \slv_rdata_reg[4]_1 ,
    \slv_rdata_reg[3] ,
    \slv_rdata_reg[3]_0 ,
    \axi_bresp_reg[1]_0 ,
    \axi_bresp_reg[1]_1 ,
    \slv_rdata_reg[1] ,
    \slv_rdata_reg[1]_0 ,
    \slv_rdata_reg[1]_1 ,
    \slv_rdata_reg[1]_2 ,
    \slv_rdata_reg[0] ,
    \slv_rdata_reg[0]_0 ,
    \slv_rdata_reg[0]_1 ,
    \slv_rdata_reg[0]_2 ,
    \slv_rdata_reg[1]_3 ,
    \slv_rdata_reg[1]_4 ,
    \slv_rdata_reg[1]_5 ,
    \slv_rdata_reg[1]_6 ,
    \slv_rdata_reg[0]_3 ,
    \slv_rdata_reg[0]_4 ,
    \slv_rdata_reg[0]_5 ,
    \slv_rdata_reg[0]_6 ,
    \slv_rdata_reg[1]_7 ,
    \slv_rdata_reg[1]_8 ,
    \slv_rdata_reg[1]_9 ,
    \slv_rdata_reg[1]_10 ,
    \slv_rdata_reg[0]_7 ,
    \slv_rdata_reg[0]_8 ,
    \slv_rdata_reg[0]_9 ,
    \slv_rdata_reg[0]_10 ,
    \slv_rdata_reg[8] ,
    \slv_rdata_reg[8]_0 ,
    \slv_rdata_reg[8]_1 ,
    \slv_rdata_reg[1]_11 ,
    \slv_rdata_reg[9] ,
    \slv_rdata_reg[10] ,
    \slv_rdata_reg[11] ,
    \slv_rdata_reg[2] ,
    \slv_rdata_reg[2]_0 ,
    \slv_rdata_reg[2]_1 ,
    \slv_rdata_reg[2]_2 ,
    \slv_rdata_reg[2]_3 ,
    \slv_rdata_reg[2]_4 ,
    \slv_rdata_reg[3]_1 ,
    \slv_rdata_reg[0]_11 ,
    \slv_rdata_reg[1]_12 ,
    error_flag,
    enable,
    \slv_rdata_reg[3]_2 ,
    \slv_rdata_reg[3]_3 ,
    \slv_rdata_reg[3]_4 ,
    \slv_rdata_reg[1]_13 ,
    \slv_rdata_reg[0]_12 ,
    \slv_rdata_reg[3]_5 ,
    \slv_rdata_reg[3]_6 ,
    \slv_rdata[3]_i_5_0 ,
    \slv_rdata[3]_i_5_1 ,
    \slv_rdata_reg[8]_2 ,
    \slv_rdata_reg[2]_5 ,
    \slv_rdata_reg[3]_7 ,
    \slv_rdata_reg[4]_2 ,
    \slv_rdata_reg[5]_2 ,
    \slv_rdata_reg[6]_2 ,
    \slv_rdata_reg[7]_14 ,
    \slv_rdata_reg[0]_13 ,
    \slv_rdata_reg[3]_8 ,
    \slv_rdata_reg[1]_14 ,
    \slv_rdata_reg[1]_15 ,
    \slv_rdata_reg[2]_6 ,
    \slv_rdata_reg[3]_9 ,
    \slv_rdata_reg[4]_3 ,
    \slv_rdata_reg[5]_3 ,
    \slv_rdata_reg[6]_3 ,
    \slv_rdata_reg[7]_15 ,
    slv_rden_r_0,
    slv_rden_r_1,
    slv_rden_r_2,
    \axi_rdata[8]_i_2_0 ,
    \axi_rdata[8]_i_2_1 ,
    \axi_rdata_reg[9]_1 ,
    \axi_rdata_reg[9]_2 ,
    \axi_rdata_reg[10]_1 ,
    \axi_rdata_reg[10]_2 ,
    \axi_rdata_reg[11]_2 ,
    \axi_rdata_reg[11]_3 ,
    s00_ds_status,
    \slv_rdata_reg[8]_3 ,
    \slv_rdata[8]_i_3_0 ,
    \slv_rdata[8]_i_3_1 ,
    s_axi_wdata);
  output adc_ds_slv_rden;
  output adc2axi_map_wready;
  output adc_ds_axi_map_wready;
  output adc0axi_map_wready;
  output adc1axi_map_wready;
  output adc3axi_map_wready;
  output axi_wr_access_reg_0;
  output axi_arready_reg_0;
  output adc0slv_rden;
  output adc1slv_rden;
  output adc2slv_rden;
  output adc3slv_rden;
  output axi_rvalid_reg_0;
  output axi_bvalid_reg_0;
  output axi_awready_reg_0;
  output [0:0]s_axi_bresp;
  output [0:0]s_axi_rresp;
  output [0:0]Q;
  output [9:0]\slv_addr_reg[11]_0 ;
  output \slv_addr_reg[2]_0 ;
  output \slv_addr_reg[2]_1 ;
  output s00_tdata_54_sp_1;
  output s00_tdata_53_sp_1;
  output s00_tdata_52_sp_1;
  output s00_tdata_50_sp_1;
  output \slv_addr_reg[5]_0 ;
  output \slv_addr_reg[5]_1 ;
  output \slv_addr_reg[8]_0 ;
  output \slv_rd_addr_reg[5]_0 ;
  output [8:0]\slv_addr_reg[2]_2 ;
  output [8:0]\slv_addr_reg[2]_3 ;
  output [8:0]\slv_addr_reg[2]_4 ;
  output \slv_addr_reg[6]_0 ;
  output \slv_addr_reg[8]_1 ;
  output \slv_addr_reg[3]_0 ;
  output [0:0]E;
  output \slv_addr_reg[8]_2 ;
  output \slv_addr_reg[6]_1 ;
  output \slv_addr_reg[6]_2 ;
  output \slv_addr_reg[6]_3 ;
  output \slv_addr_reg[2]_5 ;
  output \slv_addr_reg[3]_1 ;
  output \slv_addr_reg[5]_2 ;
  output \slv_addr_reg[2]_6 ;
  output \slv_addr_reg[6]_4 ;
  output \slv_addr_reg[3]_2 ;
  output \slv_addr_reg[5]_3 ;
  output [5:0]\slv_addr_reg[4]_0 ;
  output \slv_addr_reg[6]_5 ;
  output \slv_addr_reg[4]_1 ;
  output \slv_addr_reg[2]_7 ;
  output \slv_addr_reg[3]_3 ;
  output [0:0]slv_rden_r_reg;
  output [0:0]slv_rden_r_reg_0;
  output [0:0]slv_rden_r_reg_1;
  output [0:0]slv_rden_r_reg_2;
  output \slv_addr_reg[2]_8 ;
  output \slv_addr_reg[2]_9 ;
  output \slv_addr_reg[2]_10 ;
  output \slv_addr_reg[2]_11 ;
  output s_axi_wdata_0_sp_1;
  output \s_axi_wdata[0]_0 ;
  output [15:0]s_axi_rdata;
  input s_axi_aclk;
  input p_0_in;
  input s_axi_arvalid;
  input s_axi_awvalid;
  input \axi_rdata_reg[9]_0 ;
  input \axi_rdata_reg[10]_0 ;
  input \axi_rdata_reg[11]_0 ;
  input s_axi_aresetn;
  input [5:0]\slv_rdata_reg[7] ;
  input [5:0]\slv_rdata_reg[7]_0 ;
  input [4:0]\slv_rdata_reg[7]_1 ;
  input [4:0]\slv_rdata_reg[7]_2 ;
  input [4:0]\slv_rdata_reg[7]_3 ;
  input [4:0]\slv_rdata_reg[7]_4 ;
  input [4:0]\slv_rdata_reg[7]_5 ;
  input [4:0]\slv_rdata_reg[7]_6 ;
  input [4:0]\slv_rdata_reg[7]_7 ;
  input [4:0]\slv_rdata_reg[7]_8 ;
  input [15:0]s_axi_araddr;
  input [127:0]s00_tdata;
  input [5:0]\slv_rdata_reg[7]_9 ;
  input [5:0]\slv_rdata_reg[7]_10 ;
  input [15:0]s_axi_awaddr;
  input [11:0]\axi_rdata_reg[11]_1 ;
  input \axi_rdata_reg[0]_0 ;
  input dest_out;
  input [0:0]D;
  input [7:0]\axi_rdata_reg[8]_0 ;
  input s_axi_wvalid;
  input adc2slv_rden_reg_0;
  input adc2slv_rden_reg_1;
  input slv_wren_done_pulse;
  input slv_rden_r;
  input [15:0]slv_rdata;
  input s_axi_rready;
  input s_axi_bready;
  input timeout_enable;
  input \slv_rdata_reg[7]_11 ;
  input \slv_rdata_reg[6] ;
  input \slv_rdata_reg[5] ;
  input \slv_rdata_reg[4] ;
  input \slv_rdata_reg[7]_12 ;
  input \slv_rdata_reg[6]_0 ;
  input \slv_rdata_reg[5]_0 ;
  input \slv_rdata_reg[4]_0 ;
  input \slv_rdata_reg[7]_13 ;
  input \slv_rdata_reg[6]_1 ;
  input \slv_rdata_reg[5]_1 ;
  input \slv_rdata_reg[4]_1 ;
  input \slv_rdata_reg[3] ;
  input \slv_rdata_reg[3]_0 ;
  input \axi_bresp_reg[1]_0 ;
  input \axi_bresp_reg[1]_1 ;
  input \slv_rdata_reg[1] ;
  input \slv_rdata_reg[1]_0 ;
  input \slv_rdata_reg[1]_1 ;
  input \slv_rdata_reg[1]_2 ;
  input \slv_rdata_reg[0] ;
  input \slv_rdata_reg[0]_0 ;
  input \slv_rdata_reg[0]_1 ;
  input \slv_rdata_reg[0]_2 ;
  input \slv_rdata_reg[1]_3 ;
  input \slv_rdata_reg[1]_4 ;
  input \slv_rdata_reg[1]_5 ;
  input \slv_rdata_reg[1]_6 ;
  input \slv_rdata_reg[0]_3 ;
  input \slv_rdata_reg[0]_4 ;
  input \slv_rdata_reg[0]_5 ;
  input \slv_rdata_reg[0]_6 ;
  input \slv_rdata_reg[1]_7 ;
  input \slv_rdata_reg[1]_8 ;
  input \slv_rdata_reg[1]_9 ;
  input \slv_rdata_reg[1]_10 ;
  input \slv_rdata_reg[0]_7 ;
  input \slv_rdata_reg[0]_8 ;
  input \slv_rdata_reg[0]_9 ;
  input \slv_rdata_reg[0]_10 ;
  input \slv_rdata_reg[8] ;
  input \slv_rdata_reg[8]_0 ;
  input \slv_rdata_reg[8]_1 ;
  input \slv_rdata_reg[1]_11 ;
  input \slv_rdata_reg[9] ;
  input \slv_rdata_reg[10] ;
  input \slv_rdata_reg[11] ;
  input \slv_rdata_reg[2] ;
  input \slv_rdata_reg[2]_0 ;
  input \slv_rdata_reg[2]_1 ;
  input \slv_rdata_reg[2]_2 ;
  input \slv_rdata_reg[2]_3 ;
  input \slv_rdata_reg[2]_4 ;
  input \slv_rdata_reg[3]_1 ;
  input \slv_rdata_reg[0]_11 ;
  input \slv_rdata_reg[1]_12 ;
  input error_flag;
  input enable;
  input [2:0]\slv_rdata_reg[3]_2 ;
  input [2:0]\slv_rdata_reg[3]_3 ;
  input [2:0]\slv_rdata_reg[3]_4 ;
  input \slv_rdata_reg[1]_13 ;
  input \slv_rdata_reg[0]_12 ;
  input [0:0]\slv_rdata_reg[3]_5 ;
  input [0:0]\slv_rdata_reg[3]_6 ;
  input [0:0]\slv_rdata[3]_i_5_0 ;
  input [0:0]\slv_rdata[3]_i_5_1 ;
  input [8:0]\slv_rdata_reg[8]_2 ;
  input \slv_rdata_reg[2]_5 ;
  input \slv_rdata_reg[3]_7 ;
  input \slv_rdata_reg[4]_2 ;
  input \slv_rdata_reg[5]_2 ;
  input \slv_rdata_reg[6]_2 ;
  input \slv_rdata_reg[7]_14 ;
  input \slv_rdata_reg[0]_13 ;
  input [3:0]\slv_rdata_reg[3]_8 ;
  input [0:0]\slv_rdata_reg[1]_14 ;
  input \slv_rdata_reg[1]_15 ;
  input \slv_rdata_reg[2]_6 ;
  input \slv_rdata_reg[3]_9 ;
  input \slv_rdata_reg[4]_3 ;
  input \slv_rdata_reg[5]_3 ;
  input \slv_rdata_reg[6]_3 ;
  input \slv_rdata_reg[7]_15 ;
  input slv_rden_r_0;
  input slv_rden_r_1;
  input slv_rden_r_2;
  input [8:0]\axi_rdata[8]_i_2_0 ;
  input [8:0]\axi_rdata[8]_i_2_1 ;
  input \axi_rdata_reg[9]_1 ;
  input \axi_rdata_reg[9]_2 ;
  input \axi_rdata_reg[10]_1 ;
  input \axi_rdata_reg[10]_2 ;
  input \axi_rdata_reg[11]_2 ;
  input \axi_rdata_reg[11]_3 ;
  input s00_ds_status;
  input [0:0]\slv_rdata_reg[8]_3 ;
  input [0:0]\slv_rdata[8]_i_3_0 ;
  input [0:0]\slv_rdata[8]_i_3_1 ;
  input [0:0]s_axi_wdata;

  wire [0:0]D;
  wire [0:0]E;
  wire [0:0]Q;
  wire \adc01_ds_control_0[1]_i_3_n_0 ;
  wire \adc01_ds_enable_0[7]_i_3_n_0 ;
  wire \adc01_ds_enable_0[7]_i_4_n_0 ;
  wire \adc01_ds_type_0[3]_i_3_n_0 ;
  wire \adc02_ds_enable_0[7]_i_3_n_0 ;
  wire \adc02_ds_inc_0[11]_i_3_n_0 ;
  wire \adc02_ds_inc_0[11]_i_4_n_0 ;
  wire \adc02_ds_type_0[3]_i_3_n_0 ;
  wire \adc03_ds_control_0[1]_i_3_n_0 ;
  wire \adc03_ds_enable_0[7]_i_3_n_0 ;
  wire adc0axi_map_wready;
  wire adc0axi_map_wready0;
  wire adc0slv_rden;
  wire adc0slv_rden_i_1_n_0;
  wire adc1axi_map_wready;
  wire adc1axi_map_wready0;
  wire adc1slv_rden;
  wire adc1slv_rden_i_1_n_0;
  wire adc2axi_map_wready;
  wire adc2axi_map_wready0;
  wire adc2slv_rden;
  wire adc2slv_rden_i_1_n_0;
  wire adc2slv_rden_reg_0;
  wire adc2slv_rden_reg_1;
  wire adc3axi_map_wready;
  wire adc3axi_map_wready0;
  wire adc3axi_map_wready_i_2_n_0;
  wire adc3slv_rden;
  wire adc3slv_rden_i_1_n_0;
  wire adc_ds_axi_map_wready;
  wire adc_ds_axi_map_wready0;
  wire adc_ds_slv_rden;
  wire adc_ds_slv_rden_i_1_n_0;
  wire adc_ds_slv_rden_i_3_n_0;
  wire axi_arready0;
  wire axi_arready_reg_0;
  wire axi_awready19_in;
  wire axi_awready_i_2_n_0;
  wire axi_awready_reg_0;
  wire \axi_bresp[1]_i_1_n_0 ;
  wire \axi_bresp[1]_i_5_n_0 ;
  wire \axi_bresp_reg[1]_0 ;
  wire \axi_bresp_reg[1]_1 ;
  wire axi_bvalid0;
  wire axi_bvalid_i_1_n_0;
  wire axi_bvalid_reg_0;
  wire \axi_rdata[0]_i_1_n_0 ;
  wire \axi_rdata[0]_i_3_n_0 ;
  wire \axi_rdata[0]_i_4_n_0 ;
  wire \axi_rdata[0]_i_5_n_0 ;
  wire \axi_rdata[0]_i_6_n_0 ;
  wire \axi_rdata[0]_i_7_n_0 ;
  wire \axi_rdata[0]_i_8_n_0 ;
  wire \axi_rdata[0]_i_9_n_0 ;
  wire \axi_rdata[10]_i_1_n_0 ;
  wire \axi_rdata[10]_i_2_n_0 ;
  wire \axi_rdata[10]_i_3_n_0 ;
  wire \axi_rdata[11]_i_1_n_0 ;
  wire \axi_rdata[11]_i_2_n_0 ;
  wire \axi_rdata[11]_i_3_n_0 ;
  wire \axi_rdata[11]_i_4_n_0 ;
  wire \axi_rdata[11]_i_5_n_0 ;
  wire \axi_rdata[11]_i_6_n_0 ;
  wire \axi_rdata[12]_i_1_n_0 ;
  wire \axi_rdata[13]_i_1_n_0 ;
  wire \axi_rdata[14]_i_1_n_0 ;
  wire \axi_rdata[15]_i_1_n_0 ;
  wire \axi_rdata[15]_i_2_n_0 ;
  wire \axi_rdata[15]_i_3_n_0 ;
  wire \axi_rdata[15]_i_4_n_0 ;
  wire \axi_rdata[1]_i_1_n_0 ;
  wire \axi_rdata[1]_i_2_n_0 ;
  wire \axi_rdata[1]_i_3_n_0 ;
  wire \axi_rdata[2]_i_1_n_0 ;
  wire \axi_rdata[2]_i_2_n_0 ;
  wire \axi_rdata[2]_i_3_n_0 ;
  wire \axi_rdata[3]_i_1_n_0 ;
  wire \axi_rdata[3]_i_2_n_0 ;
  wire \axi_rdata[3]_i_3_n_0 ;
  wire \axi_rdata[4]_i_1_n_0 ;
  wire \axi_rdata[4]_i_2_n_0 ;
  wire \axi_rdata[4]_i_3_n_0 ;
  wire \axi_rdata[5]_i_1_n_0 ;
  wire \axi_rdata[5]_i_2_n_0 ;
  wire \axi_rdata[5]_i_3_n_0 ;
  wire \axi_rdata[6]_i_1_n_0 ;
  wire \axi_rdata[6]_i_2_n_0 ;
  wire \axi_rdata[6]_i_3_n_0 ;
  wire \axi_rdata[7]_i_1_n_0 ;
  wire \axi_rdata[7]_i_2_n_0 ;
  wire \axi_rdata[7]_i_3_n_0 ;
  wire \axi_rdata[8]_i_1_n_0 ;
  wire [8:0]\axi_rdata[8]_i_2_0 ;
  wire [8:0]\axi_rdata[8]_i_2_1 ;
  wire \axi_rdata[8]_i_2_n_0 ;
  wire \axi_rdata[8]_i_3_n_0 ;
  wire \axi_rdata[8]_i_4_n_0 ;
  wire \axi_rdata[9]_i_1_n_0 ;
  wire \axi_rdata[9]_i_2_n_0 ;
  wire \axi_rdata[9]_i_3_n_0 ;
  wire \axi_rdata_reg[0]_0 ;
  wire \axi_rdata_reg[10]_0 ;
  wire \axi_rdata_reg[10]_1 ;
  wire \axi_rdata_reg[10]_2 ;
  wire \axi_rdata_reg[11]_0 ;
  wire [11:0]\axi_rdata_reg[11]_1 ;
  wire \axi_rdata_reg[11]_2 ;
  wire \axi_rdata_reg[11]_3 ;
  wire [7:0]\axi_rdata_reg[8]_0 ;
  wire \axi_rdata_reg[9]_0 ;
  wire \axi_rdata_reg[9]_1 ;
  wire \axi_rdata_reg[9]_2 ;
  wire \axi_rresp[1]_i_1_n_0 ;
  wire \axi_rresp[1]_i_2_n_0 ;
  wire \axi_rresp[1]_i_5_n_0 ;
  wire axi_rvalid_i_1_n_0;
  wire axi_rvalid_reg_0;
  wire axi_wr_access0;
  wire axi_wr_access_reg_0;
  wire dest_out;
  wire enable;
  wire enable_i_2_n_0;
  wire error_flag;
  wire load_timeout_timer0;
  wire p_0_in;
  wire [12:0]p_2_in;
  wire read_in_progress;
  wire read_in_progress_i_1_n_0;
  wire read_in_progress_i_2_n_0;
  wire s00_ds_status;
  wire [127:0]s00_tdata;
  wire s00_tdata_50_sn_1;
  wire s00_tdata_52_sn_1;
  wire s00_tdata_53_sn_1;
  wire s00_tdata_54_sn_1;
  wire s_axi_aclk;
  wire [15:0]s_axi_araddr;
  wire s_axi_aresetn;
  wire s_axi_arvalid;
  wire [15:0]s_axi_awaddr;
  wire s_axi_awvalid;
  wire s_axi_bready;
  wire [0:0]s_axi_bresp;
  wire [15:0]s_axi_rdata;
  wire s_axi_rready;
  wire [0:0]s_axi_rresp;
  wire [0:0]s_axi_wdata;
  wire \s_axi_wdata[0]_0 ;
  wire s_axi_wdata_0_sn_1;
  wire s_axi_wvalid;
  wire \slv_addr[10]_i_1_n_0 ;
  wire \slv_addr[11]_i_1_n_0 ;
  wire \slv_addr[2]_i_1_n_0 ;
  wire \slv_addr[3]_i_1_n_0 ;
  wire \slv_addr[4]_i_1_n_0 ;
  wire \slv_addr[5]_i_1_n_0 ;
  wire \slv_addr[6]_i_1_n_0 ;
  wire \slv_addr[7]_i_1_n_0 ;
  wire \slv_addr[8]_i_1_n_0 ;
  wire \slv_addr[9]_i_1_n_0 ;
  wire [9:0]\slv_addr_reg[11]_0 ;
  wire \slv_addr_reg[2]_0 ;
  wire \slv_addr_reg[2]_1 ;
  wire \slv_addr_reg[2]_10 ;
  wire \slv_addr_reg[2]_11 ;
  wire [8:0]\slv_addr_reg[2]_2 ;
  wire [8:0]\slv_addr_reg[2]_3 ;
  wire [8:0]\slv_addr_reg[2]_4 ;
  wire \slv_addr_reg[2]_5 ;
  wire \slv_addr_reg[2]_6 ;
  wire \slv_addr_reg[2]_7 ;
  wire \slv_addr_reg[2]_8 ;
  wire \slv_addr_reg[2]_9 ;
  wire \slv_addr_reg[3]_0 ;
  wire \slv_addr_reg[3]_1 ;
  wire \slv_addr_reg[3]_2 ;
  wire \slv_addr_reg[3]_3 ;
  wire [5:0]\slv_addr_reg[4]_0 ;
  wire \slv_addr_reg[4]_1 ;
  wire \slv_addr_reg[5]_0 ;
  wire \slv_addr_reg[5]_1 ;
  wire \slv_addr_reg[5]_2 ;
  wire \slv_addr_reg[5]_3 ;
  wire \slv_addr_reg[6]_0 ;
  wire \slv_addr_reg[6]_1 ;
  wire \slv_addr_reg[6]_2 ;
  wire \slv_addr_reg[6]_3 ;
  wire \slv_addr_reg[6]_4 ;
  wire \slv_addr_reg[6]_5 ;
  wire \slv_addr_reg[8]_0 ;
  wire \slv_addr_reg[8]_1 ;
  wire \slv_addr_reg[8]_2 ;
  wire \slv_rd_addr[0]_i_1_n_0 ;
  wire \slv_rd_addr[1]_i_1_n_0 ;
  wire \slv_rd_addr[2]_i_1_n_0 ;
  wire \slv_rd_addr[3]_i_1_n_0 ;
  wire \slv_rd_addr[4]_i_1_n_0 ;
  wire \slv_rd_addr[5]_i_1_n_0 ;
  wire \slv_rd_addr[5]_i_2_n_0 ;
  wire \slv_rd_addr_reg[5]_0 ;
  wire \slv_rd_addr_reg_n_0_[1] ;
  wire \slv_rd_addr_reg_n_0_[2] ;
  wire \slv_rd_addr_reg_n_0_[3] ;
  wire \slv_rd_addr_reg_n_0_[4] ;
  wire \slv_rd_addr_reg_n_0_[5] ;
  wire [15:0]slv_rdata;
  wire \slv_rdata[0]_i_11_n_0 ;
  wire \slv_rdata[0]_i_2__0_n_0 ;
  wire \slv_rdata[0]_i_2__1_n_0 ;
  wire \slv_rdata[0]_i_2__2_n_0 ;
  wire \slv_rdata[0]_i_2_n_0 ;
  wire \slv_rdata[0]_i_3_n_0 ;
  wire \slv_rdata[0]_i_4_n_0 ;
  wire \slv_rdata[0]_i_5_n_0 ;
  wire \slv_rdata[0]_i_6_n_0 ;
  wire \slv_rdata[0]_i_7_n_0 ;
  wire \slv_rdata[0]_i_9_n_0 ;
  wire \slv_rdata[10]_i_6_n_0 ;
  wire \slv_rdata[10]_i_7_n_0 ;
  wire \slv_rdata[10]_i_8_n_0 ;
  wire \slv_rdata[10]_i_9_n_0 ;
  wire \slv_rdata[11]_i_10_n_0 ;
  wire \slv_rdata[11]_i_11_n_0 ;
  wire \slv_rdata[11]_i_12_n_0 ;
  wire \slv_rdata[11]_i_5_n_0 ;
  wire \slv_rdata[11]_i_9_n_0 ;
  wire \slv_rdata[12]_i_2_n_0 ;
  wire \slv_rdata[12]_i_3_n_0 ;
  wire \slv_rdata[13]_i_2_n_0 ;
  wire \slv_rdata[13]_i_3_n_0 ;
  wire \slv_rdata[14]_i_2_n_0 ;
  wire \slv_rdata[14]_i_3_n_0 ;
  wire \slv_rdata[15]_i_3_n_0 ;
  wire \slv_rdata[15]_i_4_n_0 ;
  wire \slv_rdata[1]_i_10_n_0 ;
  wire \slv_rdata[1]_i_13_n_0 ;
  wire \slv_rdata[1]_i_2__0_n_0 ;
  wire \slv_rdata[1]_i_2__1_n_0 ;
  wire \slv_rdata[1]_i_2_n_0 ;
  wire \slv_rdata[1]_i_3_n_0 ;
  wire \slv_rdata[1]_i_4_n_0 ;
  wire \slv_rdata[1]_i_5__2_n_0 ;
  wire \slv_rdata[1]_i_5_n_0 ;
  wire \slv_rdata[1]_i_6_n_0 ;
  wire \slv_rdata[1]_i_7_n_0 ;
  wire \slv_rdata[1]_i_9_n_0 ;
  wire \slv_rdata[2]_i_2__0_n_0 ;
  wire \slv_rdata[2]_i_2__1_n_0 ;
  wire \slv_rdata[2]_i_2__2_n_0 ;
  wire \slv_rdata[2]_i_2_n_0 ;
  wire \slv_rdata[2]_i_3_n_0 ;
  wire \slv_rdata[2]_i_4_n_0 ;
  wire \slv_rdata[2]_i_5__0_n_0 ;
  wire \slv_rdata[2]_i_5__1_n_0 ;
  wire \slv_rdata[2]_i_5__2_n_0 ;
  wire \slv_rdata[2]_i_5_n_0 ;
  wire \slv_rdata[2]_i_6__0_n_0 ;
  wire \slv_rdata[2]_i_6_n_0 ;
  wire \slv_rdata[2]_i_7_n_0 ;
  wire \slv_rdata[3]_i_10_n_0 ;
  wire \slv_rdata[3]_i_2__0_n_0 ;
  wire \slv_rdata[3]_i_2__2_n_0 ;
  wire \slv_rdata[3]_i_3__0_n_0 ;
  wire \slv_rdata[3]_i_3_n_0 ;
  wire \slv_rdata[3]_i_4__0_n_0 ;
  wire \slv_rdata[3]_i_4_n_0 ;
  wire [0:0]\slv_rdata[3]_i_5_0 ;
  wire [0:0]\slv_rdata[3]_i_5_1 ;
  wire \slv_rdata[3]_i_5__0_n_0 ;
  wire \slv_rdata[3]_i_5_n_0 ;
  wire \slv_rdata[3]_i_6__0_n_0 ;
  wire \slv_rdata[3]_i_6_n_0 ;
  wire \slv_rdata[3]_i_8__0_n_0 ;
  wire \slv_rdata[3]_i_8_n_0 ;
  wire \slv_rdata[3]_i_9_n_0 ;
  wire \slv_rdata[4]_i_2_n_0 ;
  wire \slv_rdata[4]_i_3__0_n_0 ;
  wire \slv_rdata[4]_i_3__1_n_0 ;
  wire \slv_rdata[4]_i_3__2_n_0 ;
  wire \slv_rdata[4]_i_3_n_0 ;
  wire \slv_rdata[4]_i_4__0_n_0 ;
  wire \slv_rdata[4]_i_4__1_n_0 ;
  wire \slv_rdata[4]_i_4__2_n_0 ;
  wire \slv_rdata[4]_i_4_n_0 ;
  wire \slv_rdata[4]_i_5_n_0 ;
  wire \slv_rdata[4]_i_6_n_0 ;
  wire \slv_rdata[5]_i_2_n_0 ;
  wire \slv_rdata[5]_i_3__0_n_0 ;
  wire \slv_rdata[5]_i_3__1_n_0 ;
  wire \slv_rdata[5]_i_3__2_n_0 ;
  wire \slv_rdata[5]_i_3_n_0 ;
  wire \slv_rdata[5]_i_4__0_n_0 ;
  wire \slv_rdata[5]_i_4__1_n_0 ;
  wire \slv_rdata[5]_i_4__2_n_0 ;
  wire \slv_rdata[5]_i_4_n_0 ;
  wire \slv_rdata[5]_i_5_n_0 ;
  wire \slv_rdata[5]_i_6_n_0 ;
  wire \slv_rdata[6]_i_2_n_0 ;
  wire \slv_rdata[6]_i_3__0_n_0 ;
  wire \slv_rdata[6]_i_3__1_n_0 ;
  wire \slv_rdata[6]_i_3__2_n_0 ;
  wire \slv_rdata[6]_i_3_n_0 ;
  wire \slv_rdata[6]_i_4__0_n_0 ;
  wire \slv_rdata[6]_i_4__1_n_0 ;
  wire \slv_rdata[6]_i_4__2_n_0 ;
  wire \slv_rdata[6]_i_4_n_0 ;
  wire \slv_rdata[6]_i_5_n_0 ;
  wire \slv_rdata[6]_i_6_n_0 ;
  wire \slv_rdata[7]_i_10_n_0 ;
  wire \slv_rdata[7]_i_12_n_0 ;
  wire \slv_rdata[7]_i_3__0_n_0 ;
  wire \slv_rdata[7]_i_3__1_n_0 ;
  wire \slv_rdata[7]_i_3__2_n_0 ;
  wire \slv_rdata[7]_i_3_n_0 ;
  wire \slv_rdata[7]_i_4__0_n_0 ;
  wire \slv_rdata[7]_i_4__1_n_0 ;
  wire \slv_rdata[7]_i_4__2_n_0 ;
  wire \slv_rdata[7]_i_4_n_0 ;
  wire \slv_rdata[7]_i_5_n_0 ;
  wire \slv_rdata[7]_i_6_n_0 ;
  wire \slv_rdata[7]_i_7_n_0 ;
  wire \slv_rdata[7]_i_8_n_0 ;
  wire \slv_rdata[8]_i_10_n_0 ;
  wire \slv_rdata[8]_i_11_n_0 ;
  wire [0:0]\slv_rdata[8]_i_3_0 ;
  wire [0:0]\slv_rdata[8]_i_3_1 ;
  wire \slv_rdata[8]_i_3_n_0 ;
  wire \slv_rdata[8]_i_4_n_0 ;
  wire \slv_rdata[8]_i_7_n_0 ;
  wire \slv_rdata[8]_i_8_n_0 ;
  wire \slv_rdata[8]_i_9_n_0 ;
  wire \slv_rdata[9]_i_6_n_0 ;
  wire \slv_rdata[9]_i_7_n_0 ;
  wire \slv_rdata[9]_i_8_n_0 ;
  wire \slv_rdata[9]_i_9_n_0 ;
  wire \slv_rdata_reg[0] ;
  wire \slv_rdata_reg[0]_0 ;
  wire \slv_rdata_reg[0]_1 ;
  wire \slv_rdata_reg[0]_10 ;
  wire \slv_rdata_reg[0]_11 ;
  wire \slv_rdata_reg[0]_12 ;
  wire \slv_rdata_reg[0]_13 ;
  wire \slv_rdata_reg[0]_2 ;
  wire \slv_rdata_reg[0]_3 ;
  wire \slv_rdata_reg[0]_4 ;
  wire \slv_rdata_reg[0]_5 ;
  wire \slv_rdata_reg[0]_6 ;
  wire \slv_rdata_reg[0]_7 ;
  wire \slv_rdata_reg[0]_8 ;
  wire \slv_rdata_reg[0]_9 ;
  wire \slv_rdata_reg[10] ;
  wire \slv_rdata_reg[10]_i_2_n_0 ;
  wire \slv_rdata_reg[10]_i_4_n_0 ;
  wire \slv_rdata_reg[10]_i_5_n_0 ;
  wire \slv_rdata_reg[11] ;
  wire \slv_rdata_reg[11]_i_2_n_0 ;
  wire \slv_rdata_reg[11]_i_7_n_0 ;
  wire \slv_rdata_reg[11]_i_8_n_0 ;
  wire \slv_rdata_reg[1] ;
  wire \slv_rdata_reg[1]_0 ;
  wire \slv_rdata_reg[1]_1 ;
  wire \slv_rdata_reg[1]_10 ;
  wire \slv_rdata_reg[1]_11 ;
  wire \slv_rdata_reg[1]_12 ;
  wire \slv_rdata_reg[1]_13 ;
  wire [0:0]\slv_rdata_reg[1]_14 ;
  wire \slv_rdata_reg[1]_15 ;
  wire \slv_rdata_reg[1]_2 ;
  wire \slv_rdata_reg[1]_3 ;
  wire \slv_rdata_reg[1]_4 ;
  wire \slv_rdata_reg[1]_5 ;
  wire \slv_rdata_reg[1]_6 ;
  wire \slv_rdata_reg[1]_7 ;
  wire \slv_rdata_reg[1]_8 ;
  wire \slv_rdata_reg[1]_9 ;
  wire \slv_rdata_reg[2] ;
  wire \slv_rdata_reg[2]_0 ;
  wire \slv_rdata_reg[2]_1 ;
  wire \slv_rdata_reg[2]_2 ;
  wire \slv_rdata_reg[2]_3 ;
  wire \slv_rdata_reg[2]_4 ;
  wire \slv_rdata_reg[2]_5 ;
  wire \slv_rdata_reg[2]_6 ;
  wire \slv_rdata_reg[3] ;
  wire \slv_rdata_reg[3]_0 ;
  wire \slv_rdata_reg[3]_1 ;
  wire [2:0]\slv_rdata_reg[3]_2 ;
  wire [2:0]\slv_rdata_reg[3]_3 ;
  wire [2:0]\slv_rdata_reg[3]_4 ;
  wire [0:0]\slv_rdata_reg[3]_5 ;
  wire [0:0]\slv_rdata_reg[3]_6 ;
  wire \slv_rdata_reg[3]_7 ;
  wire [3:0]\slv_rdata_reg[3]_8 ;
  wire \slv_rdata_reg[3]_9 ;
  wire \slv_rdata_reg[4] ;
  wire \slv_rdata_reg[4]_0 ;
  wire \slv_rdata_reg[4]_1 ;
  wire \slv_rdata_reg[4]_2 ;
  wire \slv_rdata_reg[4]_3 ;
  wire \slv_rdata_reg[5] ;
  wire \slv_rdata_reg[5]_0 ;
  wire \slv_rdata_reg[5]_1 ;
  wire \slv_rdata_reg[5]_2 ;
  wire \slv_rdata_reg[5]_3 ;
  wire \slv_rdata_reg[6] ;
  wire \slv_rdata_reg[6]_0 ;
  wire \slv_rdata_reg[6]_1 ;
  wire \slv_rdata_reg[6]_2 ;
  wire \slv_rdata_reg[6]_3 ;
  wire [5:0]\slv_rdata_reg[7] ;
  wire [5:0]\slv_rdata_reg[7]_0 ;
  wire [4:0]\slv_rdata_reg[7]_1 ;
  wire [5:0]\slv_rdata_reg[7]_10 ;
  wire \slv_rdata_reg[7]_11 ;
  wire \slv_rdata_reg[7]_12 ;
  wire \slv_rdata_reg[7]_13 ;
  wire \slv_rdata_reg[7]_14 ;
  wire \slv_rdata_reg[7]_15 ;
  wire [4:0]\slv_rdata_reg[7]_2 ;
  wire [4:0]\slv_rdata_reg[7]_3 ;
  wire [4:0]\slv_rdata_reg[7]_4 ;
  wire [4:0]\slv_rdata_reg[7]_5 ;
  wire [4:0]\slv_rdata_reg[7]_6 ;
  wire [4:0]\slv_rdata_reg[7]_7 ;
  wire [4:0]\slv_rdata_reg[7]_8 ;
  wire [5:0]\slv_rdata_reg[7]_9 ;
  wire \slv_rdata_reg[8] ;
  wire \slv_rdata_reg[8]_0 ;
  wire \slv_rdata_reg[8]_1 ;
  wire [8:0]\slv_rdata_reg[8]_2 ;
  wire [0:0]\slv_rdata_reg[8]_3 ;
  wire \slv_rdata_reg[8]_i_2_n_0 ;
  wire \slv_rdata_reg[8]_i_5_n_0 ;
  wire \slv_rdata_reg[8]_i_6_n_0 ;
  wire \slv_rdata_reg[9] ;
  wire \slv_rdata_reg[9]_i_2_n_0 ;
  wire \slv_rdata_reg[9]_i_4_n_0 ;
  wire \slv_rdata_reg[9]_i_5_n_0 ;
  wire slv_rden_r;
  wire slv_rden_r_0;
  wire slv_rden_r_1;
  wire slv_rden_r_2;
  wire [0:0]slv_rden_r_reg;
  wire [0:0]slv_rden_r_reg_0;
  wire [0:0]slv_rden_r_reg_1;
  wire [0:0]slv_rden_r_reg_2;
  wire slv_reg_rden;
  wire slv_reg_rden0;
  wire slv_reg_rden_i_1_n_0;
  wire slv_wren_done_pulse;
  wire timeout;
  wire timeout_enable;
  wire timeout_enable_i_2_n_0;
  wire \timeout_timer_count[10]_i_2_n_0 ;
  wire \timeout_timer_count[12]_i_1_n_0 ;
  wire \timeout_timer_count[12]_i_2_n_0 ;
  wire \timeout_timer_count[12]_i_4_n_0 ;
  wire \timeout_timer_count[12]_i_5_n_0 ;
  wire \timeout_timer_count[12]_i_6_n_0 ;
  wire \timeout_timer_count[12]_i_7_n_0 ;
  wire \timeout_timer_count[12]_i_8_n_0 ;
  wire \timeout_timer_count[4]_i_2_n_0 ;
  wire \timeout_timer_count[5]_i_2_n_0 ;
  wire \timeout_timer_count[8]_i_2_n_0 ;
  wire \timeout_timer_count[9]_i_2_n_0 ;
  wire \timeout_timer_count_reg_n_0_[0] ;
  wire \timeout_timer_count_reg_n_0_[10] ;
  wire \timeout_timer_count_reg_n_0_[11] ;
  wire \timeout_timer_count_reg_n_0_[1] ;
  wire \timeout_timer_count_reg_n_0_[2] ;
  wire \timeout_timer_count_reg_n_0_[3] ;
  wire \timeout_timer_count_reg_n_0_[4] ;
  wire \timeout_timer_count_reg_n_0_[5] ;
  wire \timeout_timer_count_reg_n_0_[6] ;
  wire \timeout_timer_count_reg_n_0_[7] ;
  wire \timeout_timer_count_reg_n_0_[8] ;
  wire \timeout_timer_count_reg_n_0_[9] ;
  wire \timeout_value[11]_i_2_n_0 ;
  wire valid_waddr_i_1_n_0;
  wire valid_waddr_i_2_n_0;
  wire valid_waddr_i_3_n_0;
  wire valid_waddr_i_4_n_0;
  wire valid_waddr_reg_n_0;
  wire write_in_progress;
  wire write_in_progress_i_1_n_0;
  wire write_in_progress_i_2_n_0;

  assign s00_tdata_50_sp_1 = s00_tdata_50_sn_1;
  assign s00_tdata_52_sp_1 = s00_tdata_52_sn_1;
  assign s00_tdata_53_sp_1 = s00_tdata_53_sn_1;
  assign s00_tdata_54_sp_1 = s00_tdata_54_sn_1;
  assign s_axi_wdata_0_sp_1 = s_axi_wdata_0_sn_1;
  LUT6 #(
    .INIT(64'h0000000000001000)) 
    \adc00_ds_control_0[1]_i_2 
       (.I0(\slv_addr_reg[8]_0 ),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_addr_reg[11]_0 [0]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_addr_reg[6]_2 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \adc00_ds_enable_0[0]_i_3 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [3]),
        .I2(\slv_addr_reg[8]_0 ),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_addr_reg[6]_0 ));
  LUT6 #(
    .INIT(64'h0000000000000100)) 
    \adc00_ds_inc_0[11]_i_2 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [3]),
        .I2(\slv_addr_reg[8]_0 ),
        .I3(\slv_addr_reg[11]_0 [0]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_addr_reg[6]_3 ));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    adc00_ds_pulse_control_0_i_2
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_addr_reg[11]_0 [5]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_addr_reg[11]_0 [8]),
        .I4(\slv_addr_reg[11]_0 [9]),
        .O(\slv_addr_reg[8]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT4 #(
    .INIT(16'hFFEF)) 
    adc00_ds_pulse_control_0_i_4
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_addr_reg[2]_7 ));
  LUT6 #(
    .INIT(64'h0000000100000000)) 
    \adc00_ds_type_0[3]_i_2 
       (.I0(\slv_addr_reg[8]_0 ),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_addr_reg[11]_0 [3]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_addr_reg[6]_1 ));
  LUT6 #(
    .INIT(64'h0040000000000000)) 
    \adc01_ds_control_0[1]_i_2 
       (.I0(\adc01_ds_enable_0[7]_i_4_n_0 ),
        .I1(\adc01_ds_control_0[1]_i_3_n_0 ),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_addr_reg[11]_0 [3]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_addr_reg[8]_2 ));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \adc01_ds_control_0[1]_i_3 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .O(\adc01_ds_control_0[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000200)) 
    \adc01_ds_enable_0[7]_i_2 
       (.I0(\adc01_ds_enable_0[7]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [0]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\adc01_ds_enable_0[7]_i_4_n_0 ),
        .O(\slv_addr_reg[2]_1 ));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \adc01_ds_enable_0[7]_i_3 
       (.I0(\slv_addr_reg[11]_0 [1]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .O(\adc01_ds_enable_0[7]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair42" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \adc01_ds_enable_0[7]_i_4 
       (.I0(\slv_addr_reg[11]_0 [9]),
        .I1(\slv_addr_reg[11]_0 [8]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_addr_reg[11]_0 [5]),
        .O(\adc01_ds_enable_0[7]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h0000020000000000)) 
    \adc01_ds_inc_0[11]_i_2 
       (.I0(\slv_rdata[3]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_addr_reg[11]_0 [0]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_addr_reg[11]_0 [6]),
        .O(\slv_addr_reg[4]_1 ));
  LUT6 #(
    .INIT(64'h0000000000000200)) 
    \adc01_ds_type_0[3]_i_2 
       (.I0(\adc01_ds_type_0[3]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [0]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\adc01_ds_enable_0[7]_i_4_n_0 ),
        .O(\slv_addr_reg[2]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \adc01_ds_type_0[3]_i_3 
       (.I0(\slv_addr_reg[11]_0 [1]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .O(\adc01_ds_type_0[3]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000004000000000)) 
    \adc02_ds_control_0[1]_i_2 
       (.I0(\adc02_ds_enable_0[7]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [0]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_addr_reg[11]_0 [5]),
        .I5(\adc01_ds_control_0[1]_i_3_n_0 ),
        .O(\slv_addr_reg[3]_2 ));
  LUT6 #(
    .INIT(64'h0000000000010000)) 
    \adc02_ds_enable_0[7]_i_2 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [0]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\adc01_ds_enable_0[7]_i_3_n_0 ),
        .I5(\adc02_ds_enable_0[7]_i_3_n_0 ),
        .O(\slv_addr_reg[6]_4 ));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT4 #(
    .INIT(16'hFFEF)) 
    \adc02_ds_enable_0[7]_i_3 
       (.I0(\slv_addr_reg[11]_0 [9]),
        .I1(\slv_addr_reg[11]_0 [8]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_addr_reg[11]_0 [3]),
        .O(\adc02_ds_enable_0[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000080)) 
    \adc02_ds_inc_0[11]_i_2 
       (.I0(\adc02_ds_inc_0[11]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [0]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_addr_reg[11]_0 [1]),
        .I4(\slv_addr_reg[11]_0 [4]),
        .I5(\adc02_ds_inc_0[11]_i_4_n_0 ),
        .O(\slv_addr_reg[2]_6 ));
  (* SOFT_HLUTNM = "soft_lutpair65" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \adc02_ds_inc_0[11]_i_3 
       (.I0(\slv_addr_reg[11]_0 [9]),
        .I1(\slv_addr_reg[11]_0 [8]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [3]),
        .O(\adc02_ds_inc_0[11]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \adc02_ds_inc_0[11]_i_4 
       (.I0(\slv_addr_reg[11]_0 [5]),
        .I1(\slv_addr_reg[11]_0 [6]),
        .O(\adc02_ds_inc_0[11]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h0000000001000000)) 
    \adc02_ds_type_0[3]_i_2 
       (.I0(\slv_addr_reg[11]_0 [3]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\axi_rdata[15]_i_4_n_0 ),
        .I3(\slv_addr_reg[11]_0 [7]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\adc02_ds_type_0[3]_i_3_n_0 ),
        .O(\slv_addr_reg[5]_2 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \adc02_ds_type_0[3]_i_3 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_addr_reg[11]_0 [5]),
        .I2(\slv_addr_reg[11]_0 [0]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\adc02_ds_type_0[3]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT5 #(
    .INIT(32'h00000008)) 
    \adc03_ds_control_0[1]_i_2 
       (.I0(\slv_addr_reg[11]_0 [1]),
        .I1(\slv_addr_reg[11]_0 [0]),
        .I2(\slv_addr_reg[11]_0 [3]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(\adc03_ds_control_0[1]_i_3_n_0 ),
        .O(\slv_addr_reg[3]_1 ));
  LUT6 #(
    .INIT(64'hFFFEFFFFFFFFFFFF)) 
    \adc03_ds_control_0[1]_i_3 
       (.I0(\slv_addr_reg[11]_0 [5]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_addr_reg[11]_0 [8]),
        .I3(\slv_addr_reg[11]_0 [9]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_addr_reg[11]_0 [6]),
        .O(\adc03_ds_control_0[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000000010000000)) 
    \adc03_ds_enable_0[7]_i_2 
       (.I0(\slv_addr_reg[11]_0 [1]),
        .I1(\slv_addr_reg[11]_0 [3]),
        .I2(\slv_rdata[3]_i_2__0_n_0 ),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\adc03_ds_enable_0[7]_i_3_n_0 ),
        .O(\slv_addr_reg[3]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    \adc03_ds_enable_0[7]_i_3 
       (.I0(\slv_addr_reg[11]_0 [9]),
        .I1(\slv_addr_reg[11]_0 [8]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [5]),
        .O(\adc03_ds_enable_0[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h0000400000000000)) 
    \adc03_ds_inc_0[11]_i_2 
       (.I0(\adc03_ds_enable_0[7]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [0]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\adc01_ds_enable_0[7]_i_3_n_0 ),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\slv_addr_reg[11]_0 [6]),
        .O(\slv_addr_reg[2]_5 ));
  LUT6 #(
    .INIT(64'h0400000000000000)) 
    \adc03_ds_type_0[3]_i_2 
       (.I0(\adc03_ds_enable_0[7]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [6]),
        .I2(\slv_addr_reg[11]_0 [3]),
        .I3(\slv_rdata[3]_i_2__0_n_0 ),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_addr_reg[8]_1 ));
  LUT6 #(
    .INIT(64'h0000000000008000)) 
    adc0axi_map_wready_i_1
       (.I0(valid_waddr_reg_n_0),
        .I1(s_axi_wvalid),
        .I2(\axi_rdata[15]_i_2_n_0 ),
        .I3(Q),
        .I4(\slv_rd_addr_reg_n_0_[1] ),
        .I5(adc0axi_map_wready),
        .O(adc0axi_map_wready0));
  FDRE adc0axi_map_wready_reg
       (.C(s_axi_aclk),
        .CE(axi_awready19_in),
        .D(adc0axi_map_wready0),
        .Q(adc0axi_map_wready),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'h0000000000010000)) 
    adc0slv_rden_i_1
       (.I0(s_axi_araddr[14]),
        .I1(s_axi_araddr[13]),
        .I2(s_axi_araddr[15]),
        .I3(s_axi_araddr[11]),
        .I4(s_axi_araddr[10]),
        .I5(s_axi_araddr[12]),
        .O(adc0slv_rden_i_1_n_0));
  FDRE adc0slv_rden_reg
       (.C(s_axi_aclk),
        .CE(slv_reg_rden0),
        .D(adc0slv_rden_i_1_n_0),
        .Q(adc0slv_rden),
        .R(adc_ds_slv_rden_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000000800000)) 
    adc1axi_map_wready_i_1
       (.I0(valid_waddr_reg_n_0),
        .I1(s_axi_wvalid),
        .I2(\axi_rdata[15]_i_2_n_0 ),
        .I3(Q),
        .I4(\slv_rd_addr_reg_n_0_[1] ),
        .I5(adc1axi_map_wready),
        .O(adc1axi_map_wready0));
  FDRE adc1axi_map_wready_reg
       (.C(s_axi_aclk),
        .CE(axi_awready19_in),
        .D(adc1axi_map_wready0),
        .Q(adc1axi_map_wready),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'h0000000000000010)) 
    adc1slv_rden_i_1
       (.I0(s_axi_araddr[10]),
        .I1(s_axi_araddr[12]),
        .I2(s_axi_araddr[11]),
        .I3(s_axi_araddr[14]),
        .I4(s_axi_araddr[13]),
        .I5(s_axi_araddr[15]),
        .O(adc1slv_rden_i_1_n_0));
  FDRE adc1slv_rden_reg
       (.C(s_axi_aclk),
        .CE(slv_reg_rden0),
        .D(adc1slv_rden_i_1_n_0),
        .Q(adc1slv_rden),
        .R(adc_ds_slv_rden_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    adc2axi_map_wready_i_1
       (.I0(valid_waddr_reg_n_0),
        .I1(s_axi_wvalid),
        .I2(\axi_rdata[15]_i_2_n_0 ),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(Q),
        .I5(adc2axi_map_wready),
        .O(adc2axi_map_wready0));
  FDRE adc2axi_map_wready_reg
       (.C(s_axi_aclk),
        .CE(axi_awready19_in),
        .D(adc2axi_map_wready0),
        .Q(adc2axi_map_wready),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'h0000000000000020)) 
    adc2slv_rden_i_1
       (.I0(s_axi_araddr[10]),
        .I1(s_axi_araddr[12]),
        .I2(s_axi_araddr[11]),
        .I3(s_axi_araddr[14]),
        .I4(s_axi_araddr[13]),
        .I5(s_axi_araddr[15]),
        .O(adc2slv_rden_i_1_n_0));
  FDRE adc2slv_rden_reg
       (.C(s_axi_aclk),
        .CE(slv_reg_rden0),
        .D(adc2slv_rden_i_1_n_0),
        .Q(adc2slv_rden),
        .R(adc_ds_slv_rden_i_1_n_0));
  LUT6 #(
    .INIT(64'h0400000000000000)) 
    adc3axi_map_wready_i_1
       (.I0(adc3axi_map_wready_i_2_n_0),
        .I1(\slv_rd_addr_reg_n_0_[2] ),
        .I2(adc3axi_map_wready),
        .I3(s_axi_wvalid),
        .I4(valid_waddr_reg_n_0),
        .I5(\axi_rdata[8]_i_3_n_0 ),
        .O(adc3axi_map_wready0));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT2 #(
    .INIT(4'hE)) 
    adc3axi_map_wready_i_2
       (.I0(\slv_rd_addr_reg_n_0_[1] ),
        .I1(Q),
        .O(adc3axi_map_wready_i_2_n_0));
  FDRE adc3axi_map_wready_reg
       (.C(s_axi_aclk),
        .CE(axi_awready19_in),
        .D(adc3axi_map_wready0),
        .Q(adc3axi_map_wready),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    adc3slv_rden_i_1
       (.I0(s_axi_araddr[12]),
        .I1(s_axi_araddr[11]),
        .I2(s_axi_araddr[15]),
        .I3(s_axi_araddr[13]),
        .I4(s_axi_araddr[14]),
        .I5(s_axi_araddr[10]),
        .O(adc3slv_rden_i_1_n_0));
  FDRE adc3slv_rden_reg
       (.C(s_axi_aclk),
        .CE(slv_reg_rden0),
        .D(adc3slv_rden_i_1_n_0),
        .Q(adc3slv_rden),
        .R(adc_ds_slv_rden_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000000000080)) 
    adc_ds_axi_map_wready_i_1
       (.I0(valid_waddr_reg_n_0),
        .I1(s_axi_wvalid),
        .I2(\axi_rdata[15]_i_2_n_0 ),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(Q),
        .I5(adc_ds_axi_map_wready),
        .O(adc_ds_axi_map_wready0));
  FDRE adc_ds_axi_map_wready_reg
       (.C(s_axi_aclk),
        .CE(axi_awready19_in),
        .D(adc_ds_axi_map_wready0),
        .Q(adc_ds_axi_map_wready),
        .R(p_0_in));
  LUT5 #(
    .INIT(32'hF700FFFF)) 
    adc_ds_slv_rden_i_1
       (.I0(axi_arready_reg_0),
        .I1(s_axi_arvalid),
        .I2(axi_rvalid_reg_0),
        .I3(\axi_rresp[1]_i_2_n_0 ),
        .I4(s_axi_aresetn),
        .O(adc_ds_slv_rden_i_1_n_0));
  LUT3 #(
    .INIT(8'h08)) 
    adc_ds_slv_rden_i_2
       (.I0(axi_arready_reg_0),
        .I1(s_axi_arvalid),
        .I2(axi_rvalid_reg_0),
        .O(slv_reg_rden0));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    adc_ds_slv_rden_i_3
       (.I0(s_axi_araddr[12]),
        .I1(s_axi_araddr[11]),
        .I2(s_axi_araddr[15]),
        .I3(s_axi_araddr[13]),
        .I4(s_axi_araddr[14]),
        .I5(s_axi_araddr[10]),
        .O(adc_ds_slv_rden_i_3_n_0));
  FDRE adc_ds_slv_rden_reg
       (.C(s_axi_aclk),
        .CE(slv_reg_rden0),
        .D(adc_ds_slv_rden_i_3_n_0),
        .Q(adc_ds_slv_rden),
        .R(adc_ds_slv_rden_i_1_n_0));
  LUT4 #(
    .INIT(16'h0004)) 
    axi_arready_i_1
       (.I0(read_in_progress),
        .I1(s_axi_arvalid),
        .I2(write_in_progress),
        .I3(axi_arready_reg_0),
        .O(axi_arready0));
  FDRE #(
    .INIT(1'b0)) 
    axi_arready_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_arready0),
        .Q(axi_arready_reg_0),
        .R(p_0_in));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT5 #(
    .INIT(32'hFFF00004)) 
    axi_awready_i_2
       (.I0(valid_waddr_reg_n_0),
        .I1(s_axi_awvalid),
        .I2(read_in_progress),
        .I3(s_axi_arvalid),
        .I4(axi_awready_reg_0),
        .O(axi_awready_i_2_n_0));
  FDRE #(
    .INIT(1'b0)) 
    axi_awready_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_awready_i_2_n_0),
        .Q(axi_awready_reg_0),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'h8BBB000088880000)) 
    \axi_bresp[1]_i_1 
       (.I0(timeout),
        .I1(axi_bvalid0),
        .I2(axi_bvalid_reg_0),
        .I3(s_axi_bready),
        .I4(s_axi_aresetn),
        .I5(s_axi_bresp),
        .O(\axi_bresp[1]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFF454545)) 
    \axi_bresp[1]_i_2 
       (.I0(axi_bvalid_reg_0),
        .I1(\axi_bresp_reg[1]_0 ),
        .I2(\axi_bresp_reg[1]_1 ),
        .I3(timeout),
        .I4(write_in_progress),
        .I5(\axi_bresp[1]_i_5_n_0 ),
        .O(axi_bvalid0));
  LUT6 #(
    .INIT(64'h0000000100000000)) 
    \axi_bresp[1]_i_5 
       (.I0(adc3axi_map_wready),
        .I1(adc1axi_map_wready),
        .I2(adc0axi_map_wready),
        .I3(adc2axi_map_wready),
        .I4(adc_ds_axi_map_wready),
        .I5(axi_wr_access_reg_0),
        .O(\axi_bresp[1]_i_5_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \axi_bresp_reg[1] 
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(\axi_bresp[1]_i_1_n_0 ),
        .Q(s_axi_bresp),
        .R(1'b0));
  LUT3 #(
    .INIT(8'hF4)) 
    axi_bvalid_i_1
       (.I0(s_axi_bready),
        .I1(axi_bvalid_reg_0),
        .I2(axi_bvalid0),
        .O(axi_bvalid_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    axi_bvalid_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_bvalid_i_1_n_0),
        .Q(axi_bvalid_reg_0),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'hFFFFAAABAAAAAAAA)) 
    \axi_rdata[0]_i_1 
       (.I0(\axi_rdata_reg[0]_0 ),
        .I1(\axi_rdata[0]_i_3_n_0 ),
        .I2(\axi_rdata[0]_i_4_n_0 ),
        .I3(\axi_rdata[0]_i_5_n_0 ),
        .I4(\axi_rdata[0]_i_6_n_0 ),
        .I5(\axi_rdata[15]_i_2_n_0 ),
        .O(\axi_rdata[0]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h404000C0)) 
    \axi_rdata[0]_i_3 
       (.I0(enable),
        .I1(\axi_rdata[0]_i_7_n_0 ),
        .I2(\axi_rdata[0]_i_8_n_0 ),
        .I3(timeout_enable),
        .I4(\axi_rdata[0]_i_9_n_0 ),
        .O(\axi_rdata[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hEEEEEEEFEFEEEFEF)) 
    \axi_rdata[0]_i_4 
       (.I0(\slv_addr_reg[8]_0 ),
        .I1(adc3axi_map_wready_i_2_n_0),
        .I2(\axi_rdata[0]_i_8_n_0 ),
        .I3(\axi_rdata[0]_i_9_n_0 ),
        .I4(dest_out),
        .I5(D),
        .O(\axi_rdata[0]_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h000057DF)) 
    \axi_rdata[0]_i_5 
       (.I0(\axi_rdata[0]_i_8_n_0 ),
        .I1(\axi_rdata[0]_i_9_n_0 ),
        .I2(error_flag),
        .I3(\axi_rdata_reg[11]_1 [0]),
        .I4(\axi_rdata[0]_i_7_n_0 ),
        .O(\axi_rdata[0]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[0]_i_6 
       (.I0(\axi_rdata[8]_i_2_0 [0]),
        .I1(slv_rdata[0]),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(Q),
        .I4(\axi_rdata[8]_i_2_1 [0]),
        .O(\axi_rdata[0]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT5 #(
    .INIT(32'h01000111)) 
    \axi_rdata[0]_i_7 
       (.I0(\slv_addr_reg[11]_0 [3]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\axi_rdata[0]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT5 #(
    .INIT(32'h01001101)) 
    \axi_rdata[0]_i_8 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_addr_reg[11]_0 [3]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .O(\axi_rdata[0]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT5 #(
    .INIT(32'hFFEFFCFF)) 
    \axi_rdata[0]_i_9 
       (.I0(\slv_addr_reg[11]_0 [3]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\axi_rdata[0]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h00000000AABABBBB)) 
    \axi_rdata[10]_i_1 
       (.I0(\axi_rdata[10]_i_2_n_0 ),
        .I1(\axi_rdata[11]_i_5_n_0 ),
        .I2(\axi_rdata_reg[11]_1 [10]),
        .I3(\axi_rdata[11]_i_4_n_0 ),
        .I4(\axi_rdata[11]_i_3_n_0 ),
        .I5(\axi_rdata[10]_i_3_n_0 ),
        .O(\axi_rdata[10]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hEEFCFFCCEEFCCCCC)) 
    \axi_rdata[10]_i_2 
       (.I0(\axi_rdata_reg[10]_1 ),
        .I1(\slv_rd_addr_reg_n_0_[2] ),
        .I2(slv_rdata[10]),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(Q),
        .I5(\axi_rdata_reg[10]_2 ),
        .O(\axi_rdata[10]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFD00FFFF)) 
    \axi_rdata[10]_i_3 
       (.I0(\axi_rdata_reg[10]_0 ),
        .I1(Q),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(\slv_rd_addr_reg_n_0_[2] ),
        .I4(\axi_rdata[8]_i_3_n_0 ),
        .O(\axi_rdata[10]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'h00000000AAAABBFB)) 
    \axi_rdata[11]_i_1 
       (.I0(\axi_rdata[11]_i_2_n_0 ),
        .I1(\axi_rdata[11]_i_3_n_0 ),
        .I2(\axi_rdata_reg[11]_1 [11]),
        .I3(\axi_rdata[11]_i_4_n_0 ),
        .I4(\axi_rdata[11]_i_5_n_0 ),
        .I5(\axi_rdata[11]_i_6_n_0 ),
        .O(\axi_rdata[11]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hEEFCFFCCEEFCCCCC)) 
    \axi_rdata[11]_i_2 
       (.I0(\axi_rdata_reg[11]_2 ),
        .I1(\slv_rd_addr_reg_n_0_[2] ),
        .I2(slv_rdata[11]),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(Q),
        .I5(\axi_rdata_reg[11]_3 ),
        .O(\axi_rdata[11]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair41" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFD)) 
    \axi_rdata[11]_i_3 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [3]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\axi_rdata[11]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair48" *) 
  LUT5 #(
    .INIT(32'hFFFFFFBF)) 
    \axi_rdata[11]_i_4 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .O(\axi_rdata[11]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \axi_rdata[11]_i_5 
       (.I0(Q),
        .I1(\slv_rd_addr_reg_n_0_[1] ),
        .I2(\axi_rdata[15]_i_4_n_0 ),
        .I3(\slv_addr_reg[11]_0 [7]),
        .I4(\slv_addr_reg[11]_0 [5]),
        .I5(\slv_addr_reg[11]_0 [6]),
        .O(\axi_rdata[11]_i_5_n_0 ));
  LUT5 #(
    .INIT(32'hFD00FFFF)) 
    \axi_rdata[11]_i_6 
       (.I0(\axi_rdata_reg[11]_0 ),
        .I1(Q),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(\slv_rd_addr_reg_n_0_[2] ),
        .I4(\axi_rdata[8]_i_3_n_0 ),
        .O(\axi_rdata[11]_i_6_n_0 ));
  LUT5 #(
    .INIT(32'h44404040)) 
    \axi_rdata[12]_i_1 
       (.I0(\slv_rd_addr_reg_n_0_[1] ),
        .I1(\axi_rdata[15]_i_2_n_0 ),
        .I2(\axi_rdata[15]_i_3_n_0 ),
        .I3(Q),
        .I4(slv_rdata[12]),
        .O(\axi_rdata[12]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h44404040)) 
    \axi_rdata[13]_i_1 
       (.I0(\slv_rd_addr_reg_n_0_[1] ),
        .I1(\axi_rdata[15]_i_2_n_0 ),
        .I2(\axi_rdata[15]_i_3_n_0 ),
        .I3(Q),
        .I4(slv_rdata[13]),
        .O(\axi_rdata[13]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h44404040)) 
    \axi_rdata[14]_i_1 
       (.I0(\slv_rd_addr_reg_n_0_[1] ),
        .I1(\axi_rdata[15]_i_2_n_0 ),
        .I2(\axi_rdata[15]_i_3_n_0 ),
        .I3(Q),
        .I4(slv_rdata[14]),
        .O(\axi_rdata[14]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h44404040)) 
    \axi_rdata[15]_i_1 
       (.I0(\slv_rd_addr_reg_n_0_[1] ),
        .I1(\axi_rdata[15]_i_2_n_0 ),
        .I2(\axi_rdata[15]_i_3_n_0 ),
        .I3(Q),
        .I4(slv_rdata[15]),
        .O(\axi_rdata[15]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \axi_rdata[15]_i_2 
       (.I0(\slv_rd_addr_reg_n_0_[5] ),
        .I1(\slv_rd_addr_reg_n_0_[4] ),
        .I2(\slv_rd_addr_reg_n_0_[3] ),
        .I3(\slv_rd_addr_reg_n_0_[2] ),
        .O(\axi_rdata[15]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \axi_rdata[15]_i_3 
       (.I0(\axi_rdata[11]_i_3_n_0 ),
        .I1(\slv_addr_reg[11]_0 [6]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .I3(\slv_addr_reg[11]_0 [7]),
        .I4(\axi_rdata[15]_i_4_n_0 ),
        .I5(Q),
        .O(\axi_rdata[15]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair64" *) 
  LUT2 #(
    .INIT(4'hE)) 
    \axi_rdata[15]_i_4 
       (.I0(\slv_addr_reg[11]_0 [8]),
        .I1(\slv_addr_reg[11]_0 [9]),
        .O(\axi_rdata[15]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF444F44444444)) 
    \axi_rdata[1]_i_1 
       (.I0(\slv_rd_addr_reg[5]_0 ),
        .I1(\axi_rdata_reg[8]_0 [0]),
        .I2(\axi_rdata[1]_i_2_n_0 ),
        .I3(\axi_rdata[11]_i_5_n_0 ),
        .I4(\axi_rdata[1]_i_3_n_0 ),
        .I5(\axi_rdata[15]_i_2_n_0 ),
        .O(\axi_rdata[1]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEBFFFFFFEFF)) 
    \axi_rdata[1]_i_2 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\axi_rdata_reg[11]_1 [1]),
        .O(\axi_rdata[1]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[1]_i_3 
       (.I0(\axi_rdata[8]_i_2_0 [1]),
        .I1(\axi_rdata[8]_i_2_1 [1]),
        .I2(Q),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(slv_rdata[1]),
        .O(\axi_rdata[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF444F44444444)) 
    \axi_rdata[2]_i_1 
       (.I0(\slv_rd_addr_reg[5]_0 ),
        .I1(\axi_rdata_reg[8]_0 [1]),
        .I2(\axi_rdata[2]_i_2_n_0 ),
        .I3(\axi_rdata[11]_i_5_n_0 ),
        .I4(\axi_rdata[2]_i_3_n_0 ),
        .I5(\axi_rdata[15]_i_2_n_0 ),
        .O(\axi_rdata[2]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEBFFFFFFEFF)) 
    \axi_rdata[2]_i_2 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\axi_rdata_reg[11]_1 [2]),
        .O(\axi_rdata[2]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[2]_i_3 
       (.I0(\axi_rdata[8]_i_2_0 [2]),
        .I1(\axi_rdata[8]_i_2_1 [2]),
        .I2(Q),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(slv_rdata[2]),
        .O(\axi_rdata[2]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF444F44444444)) 
    \axi_rdata[3]_i_1 
       (.I0(\slv_rd_addr_reg[5]_0 ),
        .I1(\axi_rdata_reg[8]_0 [2]),
        .I2(\axi_rdata[3]_i_2_n_0 ),
        .I3(\axi_rdata[11]_i_5_n_0 ),
        .I4(\axi_rdata[3]_i_3_n_0 ),
        .I5(\axi_rdata[15]_i_2_n_0 ),
        .O(\axi_rdata[3]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEBFFFFFFEFF)) 
    \axi_rdata[3]_i_2 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\axi_rdata_reg[11]_1 [3]),
        .O(\axi_rdata[3]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[3]_i_3 
       (.I0(\axi_rdata[8]_i_2_0 [3]),
        .I1(slv_rdata[3]),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(Q),
        .I4(\axi_rdata[8]_i_2_1 [3]),
        .O(\axi_rdata[3]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF444F44444444)) 
    \axi_rdata[4]_i_1 
       (.I0(\slv_rd_addr_reg[5]_0 ),
        .I1(\axi_rdata_reg[8]_0 [3]),
        .I2(\axi_rdata[4]_i_2_n_0 ),
        .I3(\axi_rdata[11]_i_5_n_0 ),
        .I4(\axi_rdata[4]_i_3_n_0 ),
        .I5(\axi_rdata[15]_i_2_n_0 ),
        .O(\axi_rdata[4]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEBFFFFFFEFF)) 
    \axi_rdata[4]_i_2 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\axi_rdata_reg[11]_1 [4]),
        .O(\axi_rdata[4]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[4]_i_3 
       (.I0(\axi_rdata[8]_i_2_0 [4]),
        .I1(\axi_rdata[8]_i_2_1 [4]),
        .I2(Q),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(slv_rdata[4]),
        .O(\axi_rdata[4]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF444F44444444)) 
    \axi_rdata[5]_i_1 
       (.I0(\slv_rd_addr_reg[5]_0 ),
        .I1(\axi_rdata_reg[8]_0 [4]),
        .I2(\axi_rdata[5]_i_2_n_0 ),
        .I3(\axi_rdata[11]_i_5_n_0 ),
        .I4(\axi_rdata[5]_i_3_n_0 ),
        .I5(\axi_rdata[15]_i_2_n_0 ),
        .O(\axi_rdata[5]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEBFFFFFFEFF)) 
    \axi_rdata[5]_i_2 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\axi_rdata_reg[11]_1 [5]),
        .O(\axi_rdata[5]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[5]_i_3 
       (.I0(\axi_rdata[8]_i_2_0 [5]),
        .I1(slv_rdata[5]),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(Q),
        .I4(\axi_rdata[8]_i_2_1 [5]),
        .O(\axi_rdata[5]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFF444F44444444)) 
    \axi_rdata[6]_i_1 
       (.I0(\slv_rd_addr_reg[5]_0 ),
        .I1(\axi_rdata_reg[8]_0 [5]),
        .I2(\axi_rdata[6]_i_2_n_0 ),
        .I3(\axi_rdata[11]_i_5_n_0 ),
        .I4(\axi_rdata[6]_i_3_n_0 ),
        .I5(\axi_rdata[15]_i_2_n_0 ),
        .O(\axi_rdata[6]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEBFFFFFFEFF)) 
    \axi_rdata[6]_i_2 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\axi_rdata_reg[11]_1 [6]),
        .O(\axi_rdata[6]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[6]_i_3 
       (.I0(\axi_rdata[8]_i_2_0 [6]),
        .I1(\axi_rdata[8]_i_2_1 [6]),
        .I2(Q),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(slv_rdata[6]),
        .O(\axi_rdata[6]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hF100FFFFF100F100)) 
    \axi_rdata[7]_i_1 
       (.I0(\axi_rdata[7]_i_2_n_0 ),
        .I1(\axi_rdata[11]_i_5_n_0 ),
        .I2(\axi_rdata[7]_i_3_n_0 ),
        .I3(\axi_rdata[15]_i_2_n_0 ),
        .I4(\slv_rd_addr_reg[5]_0 ),
        .I5(\axi_rdata_reg[8]_0 [6]),
        .O(\axi_rdata[7]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFEBFFFFFFEFF)) 
    \axi_rdata[7]_i_2 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\axi_rdata_reg[11]_1 [7]),
        .O(\axi_rdata[7]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[7]_i_3 
       (.I0(\axi_rdata[8]_i_2_0 [7]),
        .I1(\axi_rdata[8]_i_2_1 [7]),
        .I2(Q),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(slv_rdata[7]),
        .O(\axi_rdata[7]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFEFFFFFFFF)) 
    \axi_rdata[7]_i_4 
       (.I0(\slv_rd_addr_reg_n_0_[5] ),
        .I1(\slv_rd_addr_reg_n_0_[4] ),
        .I2(\slv_rd_addr_reg_n_0_[3] ),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(Q),
        .I5(\slv_rd_addr_reg_n_0_[2] ),
        .O(\slv_rd_addr_reg[5]_0 ));
  LUT6 #(
    .INIT(64'h0202000000FF0000)) 
    \axi_rdata[8]_i_1 
       (.I0(\axi_rdata_reg[8]_0 [7]),
        .I1(\slv_rd_addr_reg_n_0_[1] ),
        .I2(Q),
        .I3(\axi_rdata[8]_i_2_n_0 ),
        .I4(\axi_rdata[8]_i_3_n_0 ),
        .I5(\slv_rd_addr_reg_n_0_[2] ),
        .O(\axi_rdata[8]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00000000FFFFFF8A)) 
    \axi_rdata[8]_i_2 
       (.I0(\axi_rdata[11]_i_3_n_0 ),
        .I1(\axi_rdata[11]_i_4_n_0 ),
        .I2(\axi_rdata_reg[11]_1 [8]),
        .I3(adc3axi_map_wready_i_2_n_0),
        .I4(\slv_addr_reg[8]_0 ),
        .I5(\axi_rdata[8]_i_4_n_0 ),
        .O(\axi_rdata[8]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair61" *) 
  LUT3 #(
    .INIT(8'h01)) 
    \axi_rdata[8]_i_3 
       (.I0(\slv_rd_addr_reg_n_0_[3] ),
        .I1(\slv_rd_addr_reg_n_0_[4] ),
        .I2(\slv_rd_addr_reg_n_0_[5] ),
        .O(\axi_rdata[8]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hACF0AC00)) 
    \axi_rdata[8]_i_4 
       (.I0(\axi_rdata[8]_i_2_0 [8]),
        .I1(\axi_rdata[8]_i_2_1 [8]),
        .I2(Q),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(slv_rdata[8]),
        .O(\axi_rdata[8]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h00000000AABABBBB)) 
    \axi_rdata[9]_i_1 
       (.I0(\axi_rdata[9]_i_2_n_0 ),
        .I1(\axi_rdata[11]_i_5_n_0 ),
        .I2(\axi_rdata_reg[11]_1 [9]),
        .I3(\axi_rdata[11]_i_4_n_0 ),
        .I4(\axi_rdata[11]_i_3_n_0 ),
        .I5(\axi_rdata[9]_i_3_n_0 ),
        .O(\axi_rdata[9]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hEEFCFFCCEEFCCCCC)) 
    \axi_rdata[9]_i_2 
       (.I0(\axi_rdata_reg[9]_1 ),
        .I1(\slv_rd_addr_reg_n_0_[2] ),
        .I2(slv_rdata[9]),
        .I3(\slv_rd_addr_reg_n_0_[1] ),
        .I4(Q),
        .I5(\axi_rdata_reg[9]_2 ),
        .O(\axi_rdata[9]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair40" *) 
  LUT5 #(
    .INIT(32'hFD00FFFF)) 
    \axi_rdata[9]_i_3 
       (.I0(\axi_rdata_reg[9]_0 ),
        .I1(Q),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(\slv_rd_addr_reg_n_0_[2] ),
        .I4(\axi_rdata[8]_i_3_n_0 ),
        .O(\axi_rdata[9]_i_3_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[0] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[0]_i_1_n_0 ),
        .Q(s_axi_rdata[0]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[10] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[10]_i_1_n_0 ),
        .Q(s_axi_rdata[10]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[11] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[11]_i_1_n_0 ),
        .Q(s_axi_rdata[11]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[12] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[12]_i_1_n_0 ),
        .Q(s_axi_rdata[12]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[13] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[13]_i_1_n_0 ),
        .Q(s_axi_rdata[13]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[14] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[14]_i_1_n_0 ),
        .Q(s_axi_rdata[14]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[15] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[15]_i_1_n_0 ),
        .Q(s_axi_rdata[15]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[1] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[1]_i_1_n_0 ),
        .Q(s_axi_rdata[1]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[2] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[2]_i_1_n_0 ),
        .Q(s_axi_rdata[2]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[3] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[3]_i_1_n_0 ),
        .Q(s_axi_rdata[3]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[4] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[4]_i_1_n_0 ),
        .Q(s_axi_rdata[4]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[5] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[5]_i_1_n_0 ),
        .Q(s_axi_rdata[5]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[6] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[6]_i_1_n_0 ),
        .Q(s_axi_rdata[6]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[7] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[7]_i_1_n_0 ),
        .Q(s_axi_rdata[7]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[8] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[8]_i_1_n_0 ),
        .Q(s_axi_rdata[8]),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rdata_reg[9] 
       (.C(s_axi_aclk),
        .CE(slv_reg_rden),
        .D(\axi_rdata[9]_i_1_n_0 ),
        .Q(s_axi_rdata[9]),
        .R(p_0_in));
  LUT5 #(
    .INIT(32'hFFDF00C0)) 
    \axi_rresp[1]_i_1 
       (.I0(\axi_rresp[1]_i_2_n_0 ),
        .I1(timeout),
        .I2(read_in_progress),
        .I3(axi_rvalid_reg_0),
        .I4(s_axi_rresp),
        .O(\axi_rresp[1]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hEFEA0000FFFFFFFF)) 
    \axi_rresp[1]_i_2 
       (.I0(\slv_rd_addr_reg_n_0_[2] ),
        .I1(adc2slv_rden_reg_0),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(adc2slv_rden_reg_1),
        .I4(\axi_rresp[1]_i_5_n_0 ),
        .I5(\axi_rdata[8]_i_3_n_0 ),
        .O(\axi_rresp[1]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hFFF8FFFF)) 
    \axi_rresp[1]_i_5 
       (.I0(slv_wren_done_pulse),
        .I1(slv_rden_r),
        .I2(\slv_rd_addr_reg_n_0_[1] ),
        .I3(Q),
        .I4(\slv_rd_addr_reg_n_0_[2] ),
        .O(\axi_rresp[1]_i_5_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \axi_rresp_reg[1] 
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(\axi_rresp[1]_i_1_n_0 ),
        .Q(s_axi_rresp),
        .R(p_0_in));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT5 #(
    .INIT(32'h74747444)) 
    axi_rvalid_i_1
       (.I0(s_axi_rready),
        .I1(axi_rvalid_reg_0),
        .I2(read_in_progress),
        .I3(timeout),
        .I4(\axi_rresp[1]_i_2_n_0 ),
        .O(axi_rvalid_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    axi_rvalid_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_rvalid_i_1_n_0),
        .Q(axi_rvalid_reg_0),
        .R(p_0_in));
  LUT1 #(
    .INIT(2'h1)) 
    axi_wr_access_i_1
       (.I0(s_axi_arvalid),
        .O(axi_awready19_in));
  LUT3 #(
    .INIT(8'h40)) 
    axi_wr_access_i_2
       (.I0(axi_wr_access_reg_0),
        .I1(s_axi_wvalid),
        .I2(valid_waddr_reg_n_0),
        .O(axi_wr_access0));
  FDRE #(
    .INIT(1'b0)) 
    axi_wr_access_reg
       (.C(s_axi_aclk),
        .CE(axi_awready19_in),
        .D(axi_wr_access0),
        .Q(axi_wr_access_reg_0),
        .R(p_0_in));
  LUT6 #(
    .INIT(64'hFFFFFFFE00000002)) 
    enable_i_1
       (.I0(s_axi_wdata),
        .I1(enable_i_2_n_0),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [0]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(enable),
        .O(s_axi_wdata_0_sn_1));
  LUT5 #(
    .INIT(32'hFEFFFFFF)) 
    enable_i_2
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [3]),
        .I2(\slv_addr_reg[8]_0 ),
        .I3(adc_ds_axi_map_wready),
        .I4(s_axi_wvalid),
        .O(enable_i_2_n_0));
  LUT6 #(
    .INIT(64'h0000000044444000)) 
    read_in_progress_i_1
       (.I0(timeout),
        .I1(s_axi_aresetn),
        .I2(axi_arready_reg_0),
        .I3(s_axi_arvalid),
        .I4(read_in_progress),
        .I5(read_in_progress_i_2_n_0),
        .O(read_in_progress_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair54" *) 
  LUT2 #(
    .INIT(4'h8)) 
    read_in_progress_i_2
       (.I0(axi_rvalid_reg_0),
        .I1(s_axi_rready),
        .O(read_in_progress_i_2_n_0));
  FDRE read_in_progress_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(read_in_progress_i_1_n_0),
        .Q(read_in_progress),
        .R(1'b0));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[10]_i_1 
       (.I0(s_axi_araddr[8]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[8]),
        .O(\slv_addr[10]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[11]_i_1 
       (.I0(s_axi_araddr[9]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[9]),
        .O(\slv_addr[11]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[2]_i_1 
       (.I0(s_axi_araddr[0]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[0]),
        .O(\slv_addr[2]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[3]_i_1 
       (.I0(s_axi_araddr[1]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[1]),
        .O(\slv_addr[3]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[4]_i_1 
       (.I0(s_axi_araddr[2]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[2]),
        .O(\slv_addr[4]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[5]_i_1 
       (.I0(s_axi_araddr[3]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[3]),
        .O(\slv_addr[5]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[6]_i_1 
       (.I0(s_axi_araddr[4]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[4]),
        .O(\slv_addr[6]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[7]_i_1 
       (.I0(s_axi_araddr[5]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[5]),
        .O(\slv_addr[7]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[8]_i_1 
       (.I0(s_axi_araddr[6]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[6]),
        .O(\slv_addr[8]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_addr[9]_i_1 
       (.I0(s_axi_araddr[7]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[7]),
        .O(\slv_addr[9]_i_1_n_0 ));
  FDRE \slv_addr_reg[10] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[10]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [8]),
        .R(p_0_in));
  FDRE \slv_addr_reg[11] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[11]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [9]),
        .R(p_0_in));
  FDRE \slv_addr_reg[2] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[2]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [0]),
        .R(p_0_in));
  FDRE \slv_addr_reg[3] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[3]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [1]),
        .R(p_0_in));
  FDRE \slv_addr_reg[4] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[4]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [2]),
        .R(p_0_in));
  FDRE \slv_addr_reg[5] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[5]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [3]),
        .R(p_0_in));
  FDRE \slv_addr_reg[6] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[6]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [4]),
        .R(p_0_in));
  FDRE \slv_addr_reg[7] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[7]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [5]),
        .R(p_0_in));
  FDRE \slv_addr_reg[8] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[8]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [6]),
        .R(p_0_in));
  FDRE \slv_addr_reg[9] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_addr[9]_i_1_n_0 ),
        .Q(\slv_addr_reg[11]_0 [7]),
        .R(p_0_in));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_rd_addr[0]_i_1 
       (.I0(s_axi_araddr[10]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[10]),
        .O(\slv_rd_addr[0]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_rd_addr[1]_i_1 
       (.I0(s_axi_araddr[11]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[11]),
        .O(\slv_rd_addr[1]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_rd_addr[2]_i_1 
       (.I0(s_axi_araddr[12]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[12]),
        .O(\slv_rd_addr[2]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_rd_addr[3]_i_1 
       (.I0(s_axi_araddr[13]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[13]),
        .O(\slv_rd_addr[3]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_rd_addr[4]_i_1 
       (.I0(s_axi_araddr[14]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[14]),
        .O(\slv_rd_addr[4]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h04550404)) 
    \slv_rd_addr[5]_i_1 
       (.I0(valid_waddr_reg_n_0),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(axi_awready_reg_0),
        .I4(s_axi_awvalid),
        .O(\slv_rd_addr[5]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFB08)) 
    \slv_rd_addr[5]_i_2 
       (.I0(s_axi_araddr[15]),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .I3(s_axi_awaddr[15]),
        .O(\slv_rd_addr[5]_i_2_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \slv_rd_addr_reg[0] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_rd_addr[0]_i_1_n_0 ),
        .Q(Q),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \slv_rd_addr_reg[1] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_rd_addr[1]_i_1_n_0 ),
        .Q(\slv_rd_addr_reg_n_0_[1] ),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \slv_rd_addr_reg[2] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_rd_addr[2]_i_1_n_0 ),
        .Q(\slv_rd_addr_reg_n_0_[2] ),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \slv_rd_addr_reg[3] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_rd_addr[3]_i_1_n_0 ),
        .Q(\slv_rd_addr_reg_n_0_[3] ),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \slv_rd_addr_reg[4] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_rd_addr[4]_i_1_n_0 ),
        .Q(\slv_rd_addr_reg_n_0_[4] ),
        .R(p_0_in));
  FDRE #(
    .INIT(1'b0)) 
    \slv_rd_addr_reg[5] 
       (.C(s_axi_aclk),
        .CE(\slv_rd_addr[5]_i_1_n_0 ),
        .D(\slv_rd_addr[5]_i_2_n_0 ),
        .Q(\slv_rd_addr_reg_n_0_[5] ),
        .R(p_0_in));
  LUT5 #(
    .INIT(32'hAAAA8A80)) 
    \slv_rdata[0]_i_1 
       (.I0(\slv_rdata[0]_i_2_n_0 ),
        .I1(\slv_rdata_reg[0] ),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_rdata_reg[0]_0 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\slv_addr_reg[2]_2 [0]));
  LUT6 #(
    .INIT(64'h020200000000FFFC)) 
    \slv_rdata[0]_i_11 
       (.I0(s00_tdata[80]),
        .I1(\slv_addr_reg[11]_0 [7]),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[8]_2 [0]),
        .I4(\slv_addr_reg[11]_0 [4]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[0]_i_11_n_0 ));
  LUT5 #(
    .INIT(32'hAAAA8A80)) 
    \slv_rdata[0]_i_1__0 
       (.I0(\slv_rdata[0]_i_2__0_n_0 ),
        .I1(\slv_rdata_reg[0]_3 ),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_rdata_reg[0]_4 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\slv_addr_reg[2]_3 [0]));
  LUT5 #(
    .INIT(32'hAAAA8A80)) 
    \slv_rdata[0]_i_1__1 
       (.I0(\slv_rdata[0]_i_2__1_n_0 ),
        .I1(\slv_rdata_reg[0]_7 ),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_rdata_reg[0]_8 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\slv_addr_reg[2]_4 [0]));
  LUT6 #(
    .INIT(64'hAAAAAAAA8A88AAAA)) 
    \slv_rdata[0]_i_1__2 
       (.I0(\slv_addr_reg[5]_3 ),
        .I1(\slv_rdata[0]_i_2__2_n_0 ),
        .I2(\slv_rdata[0]_i_3_n_0 ),
        .I3(\slv_rdata[0]_i_4_n_0 ),
        .I4(\slv_rdata[0]_i_5_n_0 ),
        .I5(\slv_rdata[0]_i_6_n_0 ),
        .O(\slv_addr_reg[4]_0 [0]));
  LUT6 #(
    .INIT(64'h0A08AAAA0200AAAA)) 
    \slv_rdata[0]_i_2 
       (.I0(\slv_rdata[1]_i_5__2_n_0 ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata_reg[0]_1 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_rdata_reg[0]_2 ),
        .O(\slv_rdata[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0A08AAAA0200AAAA)) 
    \slv_rdata[0]_i_2__0 
       (.I0(\slv_rdata[1]_i_5__2_n_0 ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata_reg[0]_5 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_rdata_reg[0]_6 ),
        .O(\slv_rdata[0]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'h0A02AAAA0800AAAA)) 
    \slv_rdata[0]_i_2__1 
       (.I0(\slv_rdata[1]_i_5__2_n_0 ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata_reg[0]_9 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_rdata_reg[0]_10 ),
        .O(\slv_rdata[0]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hAAAA8A888A888A88)) 
    \slv_rdata[0]_i_2__2 
       (.I0(\slv_addr_reg[3]_3 ),
        .I1(\slv_rdata[0]_i_7_n_0 ),
        .I2(\slv_rdata[1]_i_10_n_0 ),
        .I3(s00_tdata[48]),
        .I4(\adc01_ds_control_0[1]_i_3_n_0 ),
        .I5(\slv_rdata_reg[0]_12 ),
        .O(\slv_rdata[0]_i_2__2_n_0 ));
  LUT6 #(
    .INIT(64'hBABFAAAABABFFAFA)) 
    \slv_rdata[0]_i_3 
       (.I0(\slv_rdata[0]_i_9_n_0 ),
        .I1(\slv_rdata_reg[3]_2 [0]),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[3]_3 [0]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_rdata_reg[3]_4 [0]),
        .O(\slv_rdata[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hE3E0030323200303)) 
    \slv_rdata[0]_i_4 
       (.I0(s00_tdata[32]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_rdata_reg[3]_8 [0]),
        .I4(\slv_rdata[8]_i_4_n_0 ),
        .I5(s00_tdata[96]),
        .O(\slv_rdata[0]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h5F5F57F7FFFF57F7)) 
    \slv_rdata[0]_i_5 
       (.I0(\slv_rdata[1]_i_7_n_0 ),
        .I1(\slv_rdata_reg[0]_11 ),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(s00_tdata[0]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[64]),
        .O(\slv_rdata[0]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h000000AE00000000)) 
    \slv_rdata[0]_i_6 
       (.I0(\slv_rdata[0]_i_11_n_0 ),
        .I1(s00_tdata[16]),
        .I2(\slv_rdata[1]_i_10_n_0 ),
        .I3(\slv_rdata_reg[0]_13 ),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_addr_reg[11]_0 [0]),
        .O(\slv_rdata[0]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h000000E200000000)) 
    \slv_rdata[0]_i_7 
       (.I0(s00_ds_status),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(s00_tdata[112]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[0]_i_7_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair43" *) 
  LUT2 #(
    .INIT(4'hB)) 
    \slv_rdata[0]_i_9 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[0]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h222200002A222A22)) 
    \slv_rdata[10]_i_1 
       (.I0(\slv_rdata_reg[10]_i_2_n_0 ),
        .I1(\slv_addr_reg[6]_5 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata_reg[10] ),
        .I4(\slv_addr_reg[5]_3 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[4]_0 [4]));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[10]_i_6 
       (.I0(s00_tdata[10]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[42]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[10]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[10]_i_7 
       (.I0(s00_tdata[74]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[106]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[10]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[10]_i_8 
       (.I0(s00_tdata[26]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[58]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[10]_i_8_n_0 ));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[10]_i_9 
       (.I0(s00_tdata[90]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[122]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[10]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h080A08AA080A080A)) 
    \slv_rdata[11]_i_1 
       (.I0(\slv_rdata_reg[11]_i_2_n_0 ),
        .I1(\slv_addr_reg[5]_3 ),
        .I2(\slv_addr_reg[6]_5 ),
        .I3(\slv_rdata[11]_i_5_n_0 ),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(\slv_rdata_reg[11] ),
        .O(\slv_addr_reg[4]_0 [5]));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[11]_i_10 
       (.I0(s00_tdata[75]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[107]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[11]_i_10_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[11]_i_11 
       (.I0(s00_tdata[27]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[59]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[11]_i_11_n_0 ));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[11]_i_12 
       (.I0(s00_tdata[91]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[123]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[11]_i_12_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT4 #(
    .INIT(16'h0001)) 
    \slv_rdata[11]_i_3 
       (.I0(\slv_addr_reg[11]_0 [3]),
        .I1(\slv_addr_reg[11]_0 [5]),
        .I2(\slv_addr_reg[11]_0 [9]),
        .I3(\slv_addr_reg[11]_0 [8]),
        .O(\slv_addr_reg[5]_3 ));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT3 #(
    .INIT(8'hFD)) 
    \slv_rdata[11]_i_4 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [7]),
        .I2(\slv_addr_reg[11]_0 [6]),
        .O(\slv_addr_reg[6]_5 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \slv_rdata[11]_i_5 
       (.I0(\slv_addr_reg[11]_0 [1]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_addr_reg[11]_0 [8]),
        .I3(\slv_addr_reg[11]_0 [9]),
        .I4(\slv_addr_reg[11]_0 [5]),
        .I5(\slv_addr_reg[11]_0 [3]),
        .O(\slv_rdata[11]_i_5_n_0 ));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[11]_i_9 
       (.I0(s00_tdata[11]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[43]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[11]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[12]_i_2 
       (.I0(s00_tdata[108]),
        .I1(s00_tdata[44]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[76]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[12]),
        .O(\slv_rdata[12]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[12]_i_3 
       (.I0(s00_tdata[124]),
        .I1(s00_tdata[60]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[92]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[28]),
        .O(\slv_rdata[12]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[13]_i_2 
       (.I0(s00_tdata[109]),
        .I1(s00_tdata[45]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[77]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[13]),
        .O(\slv_rdata[13]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[13]_i_3 
       (.I0(s00_tdata[125]),
        .I1(s00_tdata[61]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[93]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[29]),
        .O(\slv_rdata[13]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[14]_i_2 
       (.I0(s00_tdata[110]),
        .I1(s00_tdata[46]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[78]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[14]),
        .O(\slv_rdata[14]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[14]_i_3 
       (.I0(s00_tdata[126]),
        .I1(s00_tdata[62]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[94]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[30]),
        .O(\slv_rdata[14]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[15]_i_3 
       (.I0(s00_tdata[111]),
        .I1(s00_tdata[47]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[79]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[15]),
        .O(\slv_rdata[15]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \slv_rdata[15]_i_4 
       (.I0(s00_tdata[127]),
        .I1(s00_tdata[63]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(s00_tdata[95]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(s00_tdata[31]),
        .O(\slv_rdata[15]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT5 #(
    .INIT(32'h0000FFB8)) 
    \slv_rdata[1]_i_1 
       (.I0(\slv_rdata_reg[1] ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_rdata_reg[1]_0 ),
        .I3(\slv_addr_reg[11]_0 [0]),
        .I4(\slv_rdata[1]_i_4_n_0 ),
        .O(\slv_addr_reg[2]_2 [1]));
  LUT4 #(
    .INIT(16'hFEFF)) 
    \slv_rdata[1]_i_10 
       (.I0(\slv_addr_reg[11]_0 [2]),
        .I1(\slv_addr_reg[11]_0 [6]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[1]_i_10_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair44" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \slv_rdata[1]_i_12 
       (.I0(\slv_addr_reg[11]_0 [1]),
        .I1(\slv_addr_reg[11]_0 [0]),
        .O(\slv_addr_reg[3]_3 ));
  LUT6 #(
    .INIT(64'h020200000000FFFC)) 
    \slv_rdata[1]_i_13 
       (.I0(s00_tdata[97]),
        .I1(\slv_addr_reg[11]_0 [7]),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[3]_8 [1]),
        .I4(\slv_addr_reg[11]_0 [4]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[1]_i_13_n_0 ));
  LUT5 #(
    .INIT(32'hAAAA8A80)) 
    \slv_rdata[1]_i_1__0 
       (.I0(\slv_rdata[1]_i_2_n_0 ),
        .I1(\slv_rdata_reg[1]_3 ),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_rdata_reg[1]_4 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\slv_addr_reg[2]_3 [1]));
  LUT5 #(
    .INIT(32'hAAAA8A80)) 
    \slv_rdata[1]_i_1__1 
       (.I0(\slv_rdata[1]_i_2__0_n_0 ),
        .I1(\slv_rdata_reg[1]_7 ),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_rdata_reg[1]_8 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .O(\slv_addr_reg[2]_4 [1]));
  LUT6 #(
    .INIT(64'hAAAAAAAAA8A8A8AA)) 
    \slv_rdata[1]_i_1__2 
       (.I0(\slv_addr_reg[5]_3 ),
        .I1(\slv_rdata[1]_i_2__1_n_0 ),
        .I2(\slv_rdata[1]_i_3_n_0 ),
        .I3(\slv_rdata_reg[1]_11 ),
        .I4(\slv_rdata[1]_i_5_n_0 ),
        .I5(\slv_rdata[1]_i_6_n_0 ),
        .O(\slv_addr_reg[4]_0 [1]));
  LUT6 #(
    .INIT(64'h0A02AAAA0800AAAA)) 
    \slv_rdata[1]_i_2 
       (.I0(\slv_rdata[1]_i_5__2_n_0 ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata_reg[1]_5 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_rdata_reg[1]_6 ),
        .O(\slv_rdata[1]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0A08AAAA0200AAAA)) 
    \slv_rdata[1]_i_2__0 
       (.I0(\slv_rdata[1]_i_5__2_n_0 ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata_reg[1]_9 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_rdata_reg[1]_10 ),
        .O(\slv_rdata[1]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'h8A0A800A8A008000)) 
    \slv_rdata[1]_i_2__1 
       (.I0(\slv_rdata[1]_i_7_n_0 ),
        .I1(s00_tdata[65]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(s00_tdata[1]),
        .I5(\slv_rdata_reg[1]_12 ),
        .O(\slv_rdata[1]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'h000000AE00000000)) 
    \slv_rdata[1]_i_3 
       (.I0(\slv_rdata[1]_i_9_n_0 ),
        .I1(s00_tdata[17]),
        .I2(\slv_rdata[1]_i_10_n_0 ),
        .I3(\slv_rdata_reg[1]_15 ),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_addr_reg[11]_0 [0]),
        .O(\slv_rdata[1]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hDDDFFDFF55555555)) 
    \slv_rdata[1]_i_4 
       (.I0(\slv_rdata[1]_i_5__2_n_0 ),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_rdata_reg[1]_1 ),
        .I4(\slv_rdata_reg[1]_2 ),
        .I5(\slv_addr_reg[11]_0 [0]),
        .O(\slv_rdata[1]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'h1C1FFCFCDCDFFCFC)) 
    \slv_rdata[1]_i_5 
       (.I0(s00_tdata[49]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_rdata_reg[1]_14 ),
        .I4(\slv_rdata[8]_i_4_n_0 ),
        .I5(s00_tdata[113]),
        .O(\slv_rdata[1]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \slv_rdata[1]_i_5__2 
       (.I0(\slv_addr_reg[11]_0 [8]),
        .I1(\slv_addr_reg[11]_0 [9]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .I3(\slv_addr_reg[11]_0 [3]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[1]_i_5__2_n_0 ));
  LUT6 #(
    .INIT(64'h000000AE00000000)) 
    \slv_rdata[1]_i_6 
       (.I0(\slv_rdata[1]_i_13_n_0 ),
        .I1(s00_tdata[33]),
        .I2(\slv_rdata[1]_i_10_n_0 ),
        .I3(\slv_rdata_reg[1]_13 ),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[1]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair47" *) 
  LUT5 #(
    .INIT(32'h00000057)) 
    \slv_rdata[1]_i_7 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [6]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_addr_reg[11]_0 [0]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[1]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h020200000000FFFC)) 
    \slv_rdata[1]_i_9 
       (.I0(s00_tdata[81]),
        .I1(\slv_addr_reg[11]_0 [7]),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[8]_2 [1]),
        .I4(\slv_addr_reg[11]_0 [4]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[1]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h1055FFFF10551055)) 
    \slv_rdata[2]_i_1 
       (.I0(\slv_rdata[2]_i_2_n_0 ),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_rdata_reg[2] ),
        .I3(\slv_addr_reg[11]_0 [1]),
        .I4(\slv_rdata[3]_i_6_n_0 ),
        .I5(\slv_rdata_reg[2]_0 ),
        .O(\slv_addr_reg[2]_2 [2]));
  LUT6 #(
    .INIT(64'h1055FFFF10551055)) 
    \slv_rdata[2]_i_1__0 
       (.I0(\slv_rdata[2]_i_2__0_n_0 ),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_rdata_reg[2]_1 ),
        .I3(\slv_addr_reg[11]_0 [1]),
        .I4(\slv_rdata[3]_i_6_n_0 ),
        .I5(\slv_rdata_reg[2]_2 ),
        .O(\slv_addr_reg[2]_3 [2]));
  LUT6 #(
    .INIT(64'h1055FFFF10551055)) 
    \slv_rdata[2]_i_1__1 
       (.I0(\slv_rdata[2]_i_2__1_n_0 ),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_rdata_reg[2]_3 ),
        .I3(\slv_addr_reg[11]_0 [1]),
        .I4(\slv_rdata[3]_i_6_n_0 ),
        .I5(\slv_rdata_reg[2]_4 ),
        .O(\slv_addr_reg[2]_4 [2]));
  LUT6 #(
    .INIT(64'h22F222F2FFFF22F2)) 
    \slv_rdata[2]_i_1__2 
       (.I0(\slv_rdata[2]_i_2__2_n_0 ),
        .I1(\slv_rdata[2]_i_3_n_0 ),
        .I2(\slv_rdata[2]_i_4_n_0 ),
        .I3(\slv_rdata[2]_i_5_n_0 ),
        .I4(\slv_rdata[7]_i_3_n_0 ),
        .I5(\slv_rdata[2]_i_6_n_0 ),
        .O(s00_tdata_50_sn_1));
  LUT6 #(
    .INIT(64'hFFFFFFFF44455545)) 
    \slv_rdata[2]_i_2 
       (.I0(\slv_rdata[2]_i_5__0_n_0 ),
        .I1(\slv_addr_reg[11]_0 [6]),
        .I2(\slv_rdata_reg[7]_9 [0]),
        .I3(\slv_addr_reg[11]_0 [7]),
        .I4(\slv_rdata_reg[7]_10 [0]),
        .I5(\slv_rdata[2]_i_6__0_n_0 ),
        .O(\slv_rdata[2]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hBABABABBBBBBBABB)) 
    \slv_rdata[2]_i_2__0 
       (.I0(\slv_rdata[2]_i_6__0_n_0 ),
        .I1(\slv_rdata[2]_i_5__1_n_0 ),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[7]_4 [0]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_rdata_reg[7]_3 [0]),
        .O(\slv_rdata[2]_i_2__0_n_0 ));
  LUT6 #(
    .INIT(64'hABABABBBBBBBABBB)) 
    \slv_rdata[2]_i_2__1 
       (.I0(\slv_rdata[2]_i_6__0_n_0 ),
        .I1(\slv_rdata[2]_i_5__2_n_0 ),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[7]_6 [0]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_rdata_reg[7]_5 [0]),
        .O(\slv_rdata[2]_i_2__1_n_0 ));
  LUT6 #(
    .INIT(64'hE200FFFFE2000000)) 
    \slv_rdata[2]_i_2__2 
       (.I0(s00_tdata[50]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[114]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_rdata[2]_i_7_n_0 ),
        .O(\slv_rdata[2]_i_2__2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF23EE)) 
    \slv_rdata[2]_i_3 
       (.I0(\slv_addr_reg[11]_0 [2]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_rdata_reg[8]_2 [2]),
        .I3(\slv_rdata[8]_i_4_n_0 ),
        .I4(\slv_rdata_reg[2]_5 ),
        .I5(\slv_rdata[7]_i_10_n_0 ),
        .O(\slv_rdata[2]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hE3E0030323200303)) 
    \slv_rdata[2]_i_4 
       (.I0(s00_tdata[34]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_rdata_reg[3]_8 [2]),
        .I4(\slv_rdata[8]_i_4_n_0 ),
        .I5(s00_tdata[98]),
        .O(\slv_rdata[2]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hBABFAAAABABFFAFA)) 
    \slv_rdata[2]_i_5 
       (.I0(\slv_rdata[3]_i_8_n_0 ),
        .I1(\slv_rdata_reg[3]_2 [1]),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[3]_3 [1]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_rdata_reg[3]_4 [1]),
        .O(\slv_rdata[2]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[2]_i_5__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7] [0]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_0 [0]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[2]_i_5__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[2]_i_5__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_1 [0]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_2 [0]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[2]_i_5__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF4540)) 
    \slv_rdata[2]_i_5__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_7 [0]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_8 [0]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[2]_i_5__2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair51" *) 
  LUT5 #(
    .INIT(32'h0035F035)) 
    \slv_rdata[2]_i_6 
       (.I0(\slv_rdata_reg[2]_6 ),
        .I1(s00_tdata[2]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(s00_tdata[66]),
        .O(\slv_rdata[2]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \slv_rdata[2]_i_6__0 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_addr_reg[11]_0 [3]),
        .I3(\slv_addr_reg[11]_0 [5]),
        .I4(\slv_addr_reg[11]_0 [9]),
        .I5(\slv_addr_reg[11]_0 [8]),
        .O(\slv_rdata[2]_i_6__0_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[2]_i_7 
       (.I0(s00_tdata[18]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[82]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[2]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \slv_rdata[3]_i_1 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [3]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .I3(\slv_addr_reg[11]_0 [9]),
        .I4(\slv_addr_reg[11]_0 [8]),
        .I5(\slv_rdata_reg[3] ),
        .O(\slv_addr_reg[2]_4 [3]));
  LUT4 #(
    .INIT(16'h02A2)) 
    \slv_rdata[3]_i_10 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(s00_tdata[19]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(s00_tdata[83]),
        .O(\slv_rdata[3]_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h8880FFFF88808880)) 
    \slv_rdata[3]_i_1__0 
       (.I0(\slv_rdata[3]_i_2__0_n_0 ),
        .I1(\slv_rdata[3]_i_3_n_0 ),
        .I2(\slv_rdata[3]_i_4__0_n_0 ),
        .I3(\slv_rdata[3]_i_5_n_0 ),
        .I4(\slv_rdata[3]_i_6_n_0 ),
        .I5(\slv_rdata_reg[3]_0 ),
        .O(\slv_addr_reg[2]_2 [3]));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \slv_rdata[3]_i_1__1 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(\slv_addr_reg[11]_0 [3]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .I3(\slv_addr_reg[11]_0 [9]),
        .I4(\slv_addr_reg[11]_0 [8]),
        .I5(\slv_rdata_reg[3]_1 ),
        .O(\slv_addr_reg[2]_3 [3]));
  LUT6 #(
    .INIT(64'h22F222F222F2FFFF)) 
    \slv_rdata[3]_i_1__2 
       (.I0(\slv_rdata[7]_i_3_n_0 ),
        .I1(\slv_rdata[3]_i_2__2_n_0 ),
        .I2(\slv_rdata[3]_i_3__0_n_0 ),
        .I3(\slv_rdata[3]_i_4_n_0 ),
        .I4(\slv_rdata[3]_i_5__0_n_0 ),
        .I5(\slv_rdata[3]_i_6__0_n_0 ),
        .O(\slv_addr_reg[5]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair49" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \slv_rdata[3]_i_2__0 
       (.I0(\slv_addr_reg[11]_0 [2]),
        .I1(\slv_addr_reg[11]_0 [0]),
        .O(\slv_rdata[3]_i_2__0_n_0 ));
  LUT5 #(
    .INIT(32'h03F5F3F5)) 
    \slv_rdata[3]_i_2__2 
       (.I0(\slv_rdata_reg[3]_9 ),
        .I1(s00_tdata[3]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(s00_tdata[67]),
        .O(\slv_rdata[3]_i_2__2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair46" *) 
  LUT5 #(
    .INIT(32'h00000001)) 
    \slv_rdata[3]_i_3 
       (.I0(\slv_addr_reg[11]_0 [8]),
        .I1(\slv_addr_reg[11]_0 [9]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .I3(\slv_addr_reg[11]_0 [3]),
        .I4(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[3]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hE3E0030323200303)) 
    \slv_rdata[3]_i_3__0 
       (.I0(s00_tdata[35]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_rdata_reg[3]_8 [3]),
        .I4(\slv_rdata[8]_i_4_n_0 ),
        .I5(s00_tdata[99]),
        .O(\slv_rdata[3]_i_3__0_n_0 ));
  LUT6 #(
    .INIT(64'hBABFAAAABABFFAFA)) 
    \slv_rdata[3]_i_4 
       (.I0(\slv_rdata[3]_i_8_n_0 ),
        .I1(\slv_rdata_reg[3]_2 [2]),
        .I2(\slv_addr_reg[11]_0 [6]),
        .I3(\slv_rdata_reg[3]_3 [2]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .I5(\slv_rdata_reg[3]_4 [2]),
        .O(\slv_rdata[3]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT5 #(
    .INIT(32'h0000FFB8)) 
    \slv_rdata[3]_i_4__0 
       (.I0(\slv_rdata_reg[7]_10 [1]),
        .I1(\slv_addr_reg[11]_0 [7]),
        .I2(\slv_rdata_reg[7]_9 [1]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_rdata[3]_i_8__0_n_0 ),
        .O(\slv_rdata[3]_i_4__0_n_0 ));
  LUT5 #(
    .INIT(32'h0000FFB8)) 
    \slv_rdata[3]_i_5 
       (.I0(\slv_rdata_reg[3]_5 ),
        .I1(\slv_addr_reg[11]_0 [7]),
        .I2(\slv_rdata_reg[3]_6 ),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_rdata[3]_i_9_n_0 ),
        .O(\slv_rdata[3]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBFFBBAE)) 
    \slv_rdata[3]_i_5__0 
       (.I0(\slv_rdata_reg[3]_7 ),
        .I1(\slv_rdata[8]_i_4_n_0 ),
        .I2(\slv_rdata_reg[8]_2 [3]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(\slv_rdata[7]_i_10_n_0 ),
        .O(\slv_rdata[3]_i_5__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair45" *) 
  LUT5 #(
    .INIT(32'hFFFDFFFF)) 
    \slv_rdata[3]_i_6 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[5]_3 ),
        .O(\slv_rdata[3]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h57F7FFFF57F70000)) 
    \slv_rdata[3]_i_6__0 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(s00_tdata[51]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(s00_tdata[115]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_rdata[3]_i_10_n_0 ),
        .O(\slv_rdata[3]_i_6__0_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT4 #(
    .INIT(16'hFFFD)) 
    \slv_rdata[3]_i_8 
       (.I0(\slv_addr_reg[11]_0 [1]),
        .I1(\slv_addr_reg[11]_0 [0]),
        .I2(\slv_addr_reg[11]_0 [3]),
        .I3(\slv_addr_reg[11]_0 [5]),
        .O(\slv_rdata[3]_i_8_n_0 ));
  LUT5 #(
    .INIT(32'hFFFF3500)) 
    \slv_rdata[3]_i_8__0 
       (.I0(\slv_rdata_reg[7]_0 [1]),
        .I1(\slv_rdata_reg[7] [1]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[3]_i_8__0_n_0 ));
  LUT5 #(
    .INIT(32'h77333F33)) 
    \slv_rdata[3]_i_9 
       (.I0(\slv_rdata[3]_i_5_0 ),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_rdata[3]_i_5_1 ),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_addr_reg[11]_0 [7]),
        .O(\slv_rdata[3]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[4]_i_1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[4] ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[4]_i_3__1_n_0 ),
        .I4(\slv_rdata[4]_i_4__0_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_2 [4]));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[4]_i_1__0 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[4]_0 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[4]_i_3__0_n_0 ),
        .I4(\slv_rdata[4]_i_4__1_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_3 [4]));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[4]_i_1__1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[4]_1 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[4]_i_3__2_n_0 ),
        .I4(\slv_rdata[4]_i_4__2_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_4 [4]));
  LUT6 #(
    .INIT(64'hF222F222FFFFF222)) 
    \slv_rdata[4]_i_1__2 
       (.I0(\slv_rdata[4]_i_2_n_0 ),
        .I1(\slv_rdata[4]_i_3_n_0 ),
        .I2(\slv_rdata[7]_i_6_n_0 ),
        .I3(\slv_rdata[4]_i_4_n_0 ),
        .I4(\slv_rdata[7]_i_3_n_0 ),
        .I5(\slv_rdata[4]_i_5_n_0 ),
        .O(s00_tdata_52_sn_1));
  LUT6 #(
    .INIT(64'hE200FFFFE2000000)) 
    \slv_rdata[4]_i_2 
       (.I0(s00_tdata[52]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[116]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_rdata[4]_i_6_n_0 ),
        .O(\slv_rdata[4]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFBBFFBBAE)) 
    \slv_rdata[4]_i_3 
       (.I0(\slv_rdata_reg[4]_2 ),
        .I1(\slv_rdata[8]_i_4_n_0 ),
        .I2(\slv_rdata_reg[8]_2 [4]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [2]),
        .I5(\slv_rdata[7]_i_10_n_0 ),
        .O(\slv_rdata[4]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'h57F7)) 
    \slv_rdata[4]_i_3__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_2 [1]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_1 [1]),
        .O(\slv_rdata[4]_i_3__0_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[4]_i_3__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_9 [2]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_10 [2]),
        .O(\slv_rdata[4]_i_3__1_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[4]_i_3__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_8 [1]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_7 [1]),
        .O(\slv_rdata[4]_i_3__2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \slv_rdata[4]_i_4 
       (.I0(s00_tdata[100]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[36]),
        .O(\slv_rdata[4]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[4]_i_4__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7] [2]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_0 [2]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[4]_i_4__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF4540)) 
    \slv_rdata[4]_i_4__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_3 [1]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_4 [1]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[4]_i_4__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[4]_i_4__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_5 [1]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_6 [1]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[4]_i_4__2_n_0 ));
  LUT5 #(
    .INIT(32'h0035F035)) 
    \slv_rdata[4]_i_5 
       (.I0(\slv_rdata_reg[4]_3 ),
        .I1(s00_tdata[4]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(s00_tdata[68]),
        .O(\slv_rdata[4]_i_5_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[4]_i_6 
       (.I0(s00_tdata[20]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[84]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[4]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[5]_i_1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[5] ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[5]_i_3__0_n_0 ),
        .I4(\slv_rdata[5]_i_4__0_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_2 [5]));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[5]_i_1__0 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[5]_0 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[5]_i_3__1_n_0 ),
        .I4(\slv_rdata[5]_i_4__1_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_3 [5]));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[5]_i_1__1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[5]_1 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[5]_i_3__2_n_0 ),
        .I4(\slv_rdata[5]_i_4__2_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_4 [5]));
  LUT6 #(
    .INIT(64'hF222F222FFFFF222)) 
    \slv_rdata[5]_i_1__2 
       (.I0(\slv_rdata[5]_i_2_n_0 ),
        .I1(\slv_rdata[5]_i_3_n_0 ),
        .I2(\slv_rdata[7]_i_6_n_0 ),
        .I3(\slv_rdata[5]_i_4_n_0 ),
        .I4(\slv_rdata[7]_i_3_n_0 ),
        .I5(\slv_rdata[5]_i_5_n_0 ),
        .O(s00_tdata_53_sn_1));
  LUT6 #(
    .INIT(64'hE200FFFFE2000000)) 
    \slv_rdata[5]_i_2 
       (.I0(s00_tdata[53]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[117]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_rdata[5]_i_6_n_0 ),
        .O(\slv_rdata[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF23EE)) 
    \slv_rdata[5]_i_3 
       (.I0(\slv_addr_reg[11]_0 [2]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_rdata_reg[8]_2 [5]),
        .I3(\slv_rdata[8]_i_4_n_0 ),
        .I4(\slv_rdata_reg[5]_2 ),
        .I5(\slv_rdata[7]_i_10_n_0 ),
        .O(\slv_rdata[5]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[5]_i_3__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_9 [3]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_10 [3]),
        .O(\slv_rdata[5]_i_3__0_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[5]_i_3__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_4 [2]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_3 [2]),
        .O(\slv_rdata[5]_i_3__1_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[5]_i_3__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_8 [2]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_7 [2]),
        .O(\slv_rdata[5]_i_3__2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair69" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \slv_rdata[5]_i_4 
       (.I0(s00_tdata[101]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[37]),
        .O(\slv_rdata[5]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[5]_i_4__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7] [3]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_0 [3]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[5]_i_4__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[5]_i_4__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_1 [2]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_2 [2]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[5]_i_4__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[5]_i_4__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_5 [2]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_6 [2]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[5]_i_4__2_n_0 ));
  LUT5 #(
    .INIT(32'h0035F035)) 
    \slv_rdata[5]_i_5 
       (.I0(\slv_rdata_reg[5]_3 ),
        .I1(s00_tdata[5]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(s00_tdata[69]),
        .O(\slv_rdata[5]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair58" *) 
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[5]_i_6 
       (.I0(s00_tdata[21]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[85]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[5]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[6]_i_1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[6] ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[6]_i_3__0_n_0 ),
        .I4(\slv_rdata[6]_i_4__0_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_2 [6]));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[6]_i_1__0 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[6]_0 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[6]_i_3__1_n_0 ),
        .I4(\slv_rdata[6]_i_4__1_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_3 [6]));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[6]_i_1__1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[6]_1 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[6]_i_3__2_n_0 ),
        .I4(\slv_rdata[6]_i_4__2_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_4 [6]));
  LUT6 #(
    .INIT(64'h22F222F2FFFF22F2)) 
    \slv_rdata[6]_i_1__2 
       (.I0(\slv_rdata[6]_i_2_n_0 ),
        .I1(\slv_rdata[6]_i_3_n_0 ),
        .I2(\slv_rdata[7]_i_6_n_0 ),
        .I3(\slv_rdata[6]_i_4_n_0 ),
        .I4(\slv_rdata[7]_i_3_n_0 ),
        .I5(\slv_rdata[6]_i_5_n_0 ),
        .O(s00_tdata_54_sn_1));
  LUT6 #(
    .INIT(64'hE200FFFFE2000000)) 
    \slv_rdata[6]_i_2 
       (.I0(s00_tdata[54]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[118]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_rdata[6]_i_6_n_0 ),
        .O(\slv_rdata[6]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF23EE)) 
    \slv_rdata[6]_i_3 
       (.I0(\slv_addr_reg[11]_0 [2]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_rdata_reg[8]_2 [6]),
        .I3(\slv_rdata[8]_i_4_n_0 ),
        .I4(\slv_rdata_reg[6]_2 ),
        .I5(\slv_rdata[7]_i_10_n_0 ),
        .O(\slv_rdata[6]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[6]_i_3__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_9 [4]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_10 [4]),
        .O(\slv_rdata[6]_i_3__0_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[6]_i_3__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_4 [3]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_3 [3]),
        .O(\slv_rdata[6]_i_3__1_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[6]_i_3__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_8 [3]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_7 [3]),
        .O(\slv_rdata[6]_i_3__2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'h35)) 
    \slv_rdata[6]_i_4 
       (.I0(s00_tdata[38]),
        .I1(s00_tdata[102]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[6]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[6]_i_4__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7] [4]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_0 [4]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[6]_i_4__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[6]_i_4__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_1 [3]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_2 [3]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[6]_i_4__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[6]_i_4__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_5 [3]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_6 [3]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[6]_i_4__2_n_0 ));
  LUT5 #(
    .INIT(32'h0035F035)) 
    \slv_rdata[6]_i_5 
       (.I0(\slv_rdata_reg[6]_3 ),
        .I1(s00_tdata[6]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(s00_tdata[70]),
        .O(\slv_rdata[6]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair57" *) 
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[6]_i_6 
       (.I0(s00_tdata[22]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[86]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[6]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[7]_i_1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[7]_11 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[7]_i_3__0_n_0 ),
        .I4(\slv_rdata[7]_i_4__0_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_2 [7]));
  (* SOFT_HLUTNM = "soft_lutpair66" *) 
  LUT3 #(
    .INIT(8'hFD)) 
    \slv_rdata[7]_i_10 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [3]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .O(\slv_rdata[7]_i_10_n_0 ));
  LUT4 #(
    .INIT(16'h02A2)) 
    \slv_rdata[7]_i_12 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(s00_tdata[23]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(s00_tdata[87]),
        .O(\slv_rdata[7]_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[7]_i_1__0 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[7]_12 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[7]_i_3__1_n_0 ),
        .I4(\slv_rdata[7]_i_4__1_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_3 [7]));
  LUT6 #(
    .INIT(64'h000000005D5D005D)) 
    \slv_rdata[7]_i_1__1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_rdata_reg[7]_13 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata[7]_i_3__2_n_0 ),
        .I4(\slv_rdata[7]_i_4__2_n_0 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[2]_4 [7]));
  LUT6 #(
    .INIT(64'hF222F222F222FFFF)) 
    \slv_rdata[7]_i_2__2 
       (.I0(\slv_rdata[7]_i_3_n_0 ),
        .I1(\slv_rdata[7]_i_4_n_0 ),
        .I2(\slv_rdata[7]_i_5_n_0 ),
        .I3(\slv_rdata[7]_i_6_n_0 ),
        .I4(\slv_rdata[7]_i_7_n_0 ),
        .I5(\slv_rdata[7]_i_8_n_0 ),
        .O(\slv_addr_reg[5]_1 ));
  LUT6 #(
    .INIT(64'h0001000000010001)) 
    \slv_rdata[7]_i_3 
       (.I0(\slv_addr_reg[11]_0 [3]),
        .I1(\slv_addr_reg[11]_0 [5]),
        .I2(\slv_addr_reg[11]_0 [1]),
        .I3(\slv_addr_reg[11]_0 [0]),
        .I4(\slv_rdata[8]_i_4_n_0 ),
        .I5(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[7]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair59" *) 
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[7]_i_3__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_9 [5]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_10 [5]),
        .O(\slv_rdata[7]_i_3__0_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[7]_i_3__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_4 [4]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_3 [4]),
        .O(\slv_rdata[7]_i_3__1_n_0 ));
  LUT4 #(
    .INIT(16'hABFB)) 
    \slv_rdata[7]_i_3__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_8 [4]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_7 [4]),
        .O(\slv_rdata[7]_i_3__2_n_0 ));
  LUT5 #(
    .INIT(32'h0035F035)) 
    \slv_rdata[7]_i_4 
       (.I0(\slv_rdata_reg[7]_15 ),
        .I1(s00_tdata[7]),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(s00_tdata[71]),
        .O(\slv_rdata[7]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[7]_i_4__0 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7] [5]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_0 [5]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[7]_i_4__0_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[7]_i_4__1 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_1 [4]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_2 [4]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[7]_i_4__1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF8A80)) 
    \slv_rdata[7]_i_4__2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_rdata_reg[7]_5 [4]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\slv_rdata_reg[7]_6 [4]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[7]_i_4__2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair68" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \slv_rdata[7]_i_5 
       (.I0(s00_tdata[103]),
        .I1(\slv_addr_reg[11]_0 [2]),
        .I2(s00_tdata[39]),
        .O(\slv_rdata[7]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0000000800000000)) 
    \slv_rdata[7]_i_6 
       (.I0(\slv_rdata[8]_i_4_n_0 ),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_addr_reg[11]_0 [5]),
        .I3(\slv_addr_reg[11]_0 [3]),
        .I4(\slv_addr_reg[11]_0 [0]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_rdata[7]_i_6_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF23EE)) 
    \slv_rdata[7]_i_7 
       (.I0(\slv_addr_reg[11]_0 [2]),
        .I1(\slv_addr_reg[11]_0 [4]),
        .I2(\slv_rdata_reg[8]_2 [7]),
        .I3(\slv_rdata[8]_i_4_n_0 ),
        .I4(\slv_rdata[7]_i_10_n_0 ),
        .I5(\slv_rdata_reg[7]_14 ),
        .O(\slv_rdata[7]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h57F7FFFF57F70000)) 
    \slv_rdata[7]_i_8 
       (.I0(\slv_addr_reg[11]_0 [4]),
        .I1(s00_tdata[55]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(s00_tdata[119]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_rdata[7]_i_12_n_0 ),
        .O(\slv_rdata[7]_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h0012000000100000)) 
    \slv_rdata[8]_i_1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[5]_3 ),
        .I5(\slv_rdata_reg[8] ),
        .O(\slv_addr_reg[2]_4 [8]));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[8]_i_10 
       (.I0(s00_tdata[24]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[56]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[8]_i_10_n_0 ));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[8]_i_11 
       (.I0(s00_tdata[88]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[120]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[8]_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h0012000000100000)) 
    \slv_rdata[8]_i_1__0 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[5]_3 ),
        .I5(\slv_rdata_reg[8]_0 ),
        .O(\slv_addr_reg[2]_3 [8]));
  LUT6 #(
    .INIT(64'h0012000000100000)) 
    \slv_rdata[8]_i_1__1 
       (.I0(\slv_addr_reg[11]_0 [0]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .I4(\slv_addr_reg[5]_3 ),
        .I5(\slv_rdata_reg[8]_1 ),
        .O(\slv_addr_reg[2]_2 [8]));
  LUT6 #(
    .INIT(64'h2000000020002200)) 
    \slv_rdata[8]_i_1__2 
       (.I0(\slv_rdata_reg[8]_i_2_n_0 ),
        .I1(\slv_rdata[8]_i_3_n_0 ),
        .I2(\slv_rdata[8]_i_4_n_0 ),
        .I3(\slv_addr_reg[5]_3 ),
        .I4(\slv_addr_reg[11]_0 [4]),
        .I5(\slv_addr_reg[11]_0 [1]),
        .O(\slv_addr_reg[4]_0 [2]));
  LUT5 #(
    .INIT(32'h0000FF47)) 
    \slv_rdata[8]_i_3 
       (.I0(\slv_rdata_reg[8]_3 ),
        .I1(\slv_addr_reg[11]_0 [7]),
        .I2(\slv_rdata_reg[8]_2 [8]),
        .I3(\slv_addr_reg[11]_0 [6]),
        .I4(\slv_rdata[8]_i_7_n_0 ),
        .O(\slv_rdata[8]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair50" *) 
  LUT2 #(
    .INIT(4'h1)) 
    \slv_rdata[8]_i_4 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_addr_reg[11]_0 [7]),
        .O(\slv_rdata[8]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFAACC00F0)) 
    \slv_rdata[8]_i_7 
       (.I0(\slv_rdata[8]_i_3_0 ),
        .I1(\slv_rdata[8]_i_3_1 ),
        .I2(\slv_addr_reg[11]_0 [4]),
        .I3(\slv_addr_reg[11]_0 [7]),
        .I4(\slv_addr_reg[11]_0 [6]),
        .I5(\slv_addr_reg[11]_0 [2]),
        .O(\slv_rdata[8]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[8]_i_8 
       (.I0(s00_tdata[8]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[40]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[8]_i_8_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[8]_i_9 
       (.I0(s00_tdata[72]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[104]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[8]_i_9_n_0 ));
  LUT6 #(
    .INIT(64'h222200002A222A22)) 
    \slv_rdata[9]_i_1 
       (.I0(\slv_rdata_reg[9]_i_2_n_0 ),
        .I1(\slv_addr_reg[6]_5 ),
        .I2(\slv_addr_reg[11]_0 [2]),
        .I3(\slv_rdata_reg[9] ),
        .I4(\slv_addr_reg[5]_3 ),
        .I5(\slv_rdata[11]_i_5_n_0 ),
        .O(\slv_addr_reg[4]_0 [3]));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[9]_i_6 
       (.I0(s00_tdata[9]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[41]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[9]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[9]_i_7 
       (.I0(s00_tdata[73]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[105]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[9]_i_7_n_0 ));
  LUT4 #(
    .INIT(16'hE2FF)) 
    \slv_rdata[9]_i_8 
       (.I0(s00_tdata[25]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[57]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[9]_i_8_n_0 ));
  LUT4 #(
    .INIT(16'hE200)) 
    \slv_rdata[9]_i_9 
       (.I0(s00_tdata[89]),
        .I1(\slv_addr_reg[11]_0 [1]),
        .I2(s00_tdata[121]),
        .I3(\slv_addr_reg[11]_0 [4]),
        .O(\slv_rdata[9]_i_9_n_0 ));
  MUXF8 \slv_rdata_reg[10]_i_2 
       (.I0(\slv_rdata_reg[10]_i_4_n_0 ),
        .I1(\slv_rdata_reg[10]_i_5_n_0 ),
        .O(\slv_rdata_reg[10]_i_2_n_0 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF7 \slv_rdata_reg[10]_i_4 
       (.I0(\slv_rdata[10]_i_6_n_0 ),
        .I1(\slv_rdata[10]_i_7_n_0 ),
        .O(\slv_rdata_reg[10]_i_4_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  MUXF7 \slv_rdata_reg[10]_i_5 
       (.I0(\slv_rdata[10]_i_8_n_0 ),
        .I1(\slv_rdata[10]_i_9_n_0 ),
        .O(\slv_rdata_reg[10]_i_5_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  MUXF8 \slv_rdata_reg[11]_i_2 
       (.I0(\slv_rdata_reg[11]_i_7_n_0 ),
        .I1(\slv_rdata_reg[11]_i_8_n_0 ),
        .O(\slv_rdata_reg[11]_i_2_n_0 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF7 \slv_rdata_reg[11]_i_7 
       (.I0(\slv_rdata[11]_i_9_n_0 ),
        .I1(\slv_rdata[11]_i_10_n_0 ),
        .O(\slv_rdata_reg[11]_i_7_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  MUXF7 \slv_rdata_reg[11]_i_8 
       (.I0(\slv_rdata[11]_i_11_n_0 ),
        .I1(\slv_rdata[11]_i_12_n_0 ),
        .O(\slv_rdata_reg[11]_i_8_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  MUXF7 \slv_rdata_reg[12]_i_1 
       (.I0(\slv_rdata[12]_i_2_n_0 ),
        .I1(\slv_rdata[12]_i_3_n_0 ),
        .O(\slv_addr_reg[2]_11 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF7 \slv_rdata_reg[13]_i_1 
       (.I0(\slv_rdata[13]_i_2_n_0 ),
        .I1(\slv_rdata[13]_i_3_n_0 ),
        .O(\slv_addr_reg[2]_10 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF7 \slv_rdata_reg[14]_i_1 
       (.I0(\slv_rdata[14]_i_2_n_0 ),
        .I1(\slv_rdata[14]_i_3_n_0 ),
        .O(\slv_addr_reg[2]_9 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF7 \slv_rdata_reg[15]_i_2 
       (.I0(\slv_rdata[15]_i_3_n_0 ),
        .I1(\slv_rdata[15]_i_4_n_0 ),
        .O(\slv_addr_reg[2]_8 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF8 \slv_rdata_reg[8]_i_2 
       (.I0(\slv_rdata_reg[8]_i_5_n_0 ),
        .I1(\slv_rdata_reg[8]_i_6_n_0 ),
        .O(\slv_rdata_reg[8]_i_2_n_0 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF7 \slv_rdata_reg[8]_i_5 
       (.I0(\slv_rdata[8]_i_8_n_0 ),
        .I1(\slv_rdata[8]_i_9_n_0 ),
        .O(\slv_rdata_reg[8]_i_5_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  MUXF7 \slv_rdata_reg[8]_i_6 
       (.I0(\slv_rdata[8]_i_10_n_0 ),
        .I1(\slv_rdata[8]_i_11_n_0 ),
        .O(\slv_rdata_reg[8]_i_6_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  MUXF8 \slv_rdata_reg[9]_i_2 
       (.I0(\slv_rdata_reg[9]_i_4_n_0 ),
        .I1(\slv_rdata_reg[9]_i_5_n_0 ),
        .O(\slv_rdata_reg[9]_i_2_n_0 ),
        .S(\slv_addr_reg[11]_0 [0]));
  MUXF7 \slv_rdata_reg[9]_i_4 
       (.I0(\slv_rdata[9]_i_6_n_0 ),
        .I1(\slv_rdata[9]_i_7_n_0 ),
        .O(\slv_rdata_reg[9]_i_4_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  MUXF7 \slv_rdata_reg[9]_i_5 
       (.I0(\slv_rdata[9]_i_8_n_0 ),
        .I1(\slv_rdata[9]_i_9_n_0 ),
        .O(\slv_rdata_reg[9]_i_5_n_0 ),
        .S(\slv_addr_reg[11]_0 [2]));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT5 #(
    .INIT(32'h75553000)) 
    slv_reg_rden_i_1
       (.I0(\axi_rresp[1]_i_2_n_0 ),
        .I1(axi_rvalid_reg_0),
        .I2(s_axi_arvalid),
        .I3(axi_arready_reg_0),
        .I4(slv_reg_rden),
        .O(slv_reg_rden_i_1_n_0));
  FDRE slv_reg_rden_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(slv_reg_rden_i_1_n_0),
        .Q(slv_reg_rden),
        .R(p_0_in));
  LUT4 #(
    .INIT(16'hF444)) 
    \slv_wdata_r_internal[11]_i_1 
       (.I0(slv_rden_r_0),
        .I1(adc0slv_rden),
        .I2(adc0axi_map_wready),
        .I3(s_axi_wvalid),
        .O(slv_rden_r_reg));
  LUT4 #(
    .INIT(16'hF444)) 
    \slv_wdata_r_internal[11]_i_1__0 
       (.I0(slv_rden_r_1),
        .I1(adc1slv_rden),
        .I2(adc1axi_map_wready),
        .I3(s_axi_wvalid),
        .O(slv_rden_r_reg_0));
  LUT4 #(
    .INIT(16'hF444)) 
    \slv_wdata_r_internal[11]_i_1__1 
       (.I0(slv_rden_r_2),
        .I1(adc2slv_rden),
        .I2(adc2axi_map_wready),
        .I3(s_axi_wvalid),
        .O(slv_rden_r_reg_1));
  LUT4 #(
    .INIT(16'hF444)) 
    \slv_wdata_r_internal[11]_i_1__2 
       (.I0(slv_rden_r),
        .I1(adc3slv_rden),
        .I2(adc3axi_map_wready),
        .I3(s_axi_wvalid),
        .O(slv_rden_r_reg_2));
  LUT5 #(
    .INIT(32'hFFFB0008)) 
    timeout_enable_i_1
       (.I0(s_axi_wdata),
        .I1(timeout_enable_i_2_n_0),
        .I2(\slv_addr_reg[11]_0 [0]),
        .I3(\slv_addr_reg[11]_0 [1]),
        .I4(timeout_enable),
        .O(\s_axi_wdata[0]_0 ));
  LUT6 #(
    .INIT(64'h0000000000000080)) 
    timeout_enable_i_2
       (.I0(\slv_addr_reg[11]_0 [2]),
        .I1(s_axi_wvalid),
        .I2(adc_ds_axi_map_wready),
        .I3(\slv_addr_reg[8]_0 ),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\slv_addr_reg[11]_0 [4]),
        .O(timeout_enable_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT3 #(
    .INIT(8'h47)) 
    \timeout_timer_count[0]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [0]),
        .I1(\timeout_timer_count[12]_i_5_n_0 ),
        .I2(\timeout_timer_count_reg_n_0_[0] ),
        .O(p_2_in[0]));
  LUT4 #(
    .INIT(16'h4774)) 
    \timeout_timer_count[10]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [10]),
        .I1(\timeout_timer_count[12]_i_5_n_0 ),
        .I2(\timeout_timer_count_reg_n_0_[10] ),
        .I3(\timeout_timer_count[10]_i_2_n_0 ),
        .O(p_2_in[10]));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT5 #(
    .INIT(32'h00800000)) 
    \timeout_timer_count[10]_i_2 
       (.I0(\timeout_timer_count_reg_n_0_[9] ),
        .I1(\timeout_timer_count_reg_n_0_[7] ),
        .I2(\timeout_timer_count_reg_n_0_[6] ),
        .I3(\timeout_timer_count[8]_i_2_n_0 ),
        .I4(\timeout_timer_count_reg_n_0_[8] ),
        .O(\timeout_timer_count[10]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT4 #(
    .INIT(16'h4774)) 
    \timeout_timer_count[11]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [11]),
        .I1(\timeout_timer_count[12]_i_5_n_0 ),
        .I2(\timeout_timer_count_reg_n_0_[11] ),
        .I3(\timeout_timer_count[12]_i_6_n_0 ),
        .O(p_2_in[11]));
  LUT6 #(
    .INIT(64'hFFFFF8FFF8FFF8FF)) 
    \timeout_timer_count[12]_i_1 
       (.I0(s_axi_rready),
        .I1(axi_rvalid_reg_0),
        .I2(timeout),
        .I3(s_axi_aresetn),
        .I4(axi_bvalid_reg_0),
        .I5(s_axi_bready),
        .O(\timeout_timer_count[12]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'hE)) 
    \timeout_timer_count[12]_i_2 
       (.I0(\timeout_timer_count[12]_i_4_n_0 ),
        .I1(\timeout_timer_count[12]_i_5_n_0 ),
        .O(\timeout_timer_count[12]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair63" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \timeout_timer_count[12]_i_3 
       (.I0(\timeout_timer_count_reg_n_0_[11] ),
        .I1(\timeout_timer_count[12]_i_6_n_0 ),
        .I2(\timeout_timer_count[12]_i_5_n_0 ),
        .O(p_2_in[12]));
  LUT6 #(
    .INIT(64'hAAAAAAA8AAAAAAAA)) 
    \timeout_timer_count[12]_i_4 
       (.I0(timeout_enable),
        .I1(\timeout_timer_count_reg_n_0_[2] ),
        .I2(\timeout_timer_count_reg_n_0_[7] ),
        .I3(\timeout_timer_count_reg_n_0_[9] ),
        .I4(\timeout_timer_count[12]_i_7_n_0 ),
        .I5(\timeout_timer_count[12]_i_8_n_0 ),
        .O(\timeout_timer_count[12]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hAAAAA888A888A888)) 
    \timeout_timer_count[12]_i_5 
       (.I0(timeout_enable),
        .I1(load_timeout_timer0),
        .I2(s_axi_awvalid),
        .I3(axi_awready_reg_0),
        .I4(axi_wr_access_reg_0),
        .I5(s_axi_wvalid),
        .O(\timeout_timer_count[12]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h0800000000000000)) 
    \timeout_timer_count[12]_i_6 
       (.I0(\timeout_timer_count_reg_n_0_[10] ),
        .I1(\timeout_timer_count_reg_n_0_[8] ),
        .I2(\timeout_timer_count[8]_i_2_n_0 ),
        .I3(\timeout_timer_count_reg_n_0_[6] ),
        .I4(\timeout_timer_count_reg_n_0_[7] ),
        .I5(\timeout_timer_count_reg_n_0_[9] ),
        .O(\timeout_timer_count[12]_i_6_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \timeout_timer_count[12]_i_7 
       (.I0(\timeout_timer_count_reg_n_0_[11] ),
        .I1(\timeout_timer_count_reg_n_0_[10] ),
        .I2(\timeout_timer_count_reg_n_0_[5] ),
        .I3(\timeout_timer_count_reg_n_0_[3] ),
        .O(\timeout_timer_count[12]_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \timeout_timer_count[12]_i_8 
       (.I0(\timeout_timer_count_reg_n_0_[1] ),
        .I1(\timeout_timer_count_reg_n_0_[0] ),
        .I2(timeout),
        .I3(\timeout_timer_count_reg_n_0_[8] ),
        .I4(\timeout_timer_count_reg_n_0_[4] ),
        .I5(\timeout_timer_count_reg_n_0_[6] ),
        .O(\timeout_timer_count[12]_i_8_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair56" *) 
  LUT2 #(
    .INIT(4'h8)) 
    \timeout_timer_count[12]_i_9 
       (.I0(s_axi_arvalid),
        .I1(axi_arready_reg_0),
        .O(load_timeout_timer0));
  (* SOFT_HLUTNM = "soft_lutpair62" *) 
  LUT4 #(
    .INIT(16'h4774)) 
    \timeout_timer_count[1]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [1]),
        .I1(\timeout_timer_count[12]_i_5_n_0 ),
        .I2(\timeout_timer_count_reg_n_0_[0] ),
        .I3(\timeout_timer_count_reg_n_0_[1] ),
        .O(p_2_in[1]));
  LUT5 #(
    .INIT(32'h55553CCC)) 
    \timeout_timer_count[2]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [2]),
        .I1(\timeout_timer_count_reg_n_0_[2] ),
        .I2(\timeout_timer_count_reg_n_0_[1] ),
        .I3(\timeout_timer_count_reg_n_0_[0] ),
        .I4(\timeout_timer_count[12]_i_5_n_0 ),
        .O(p_2_in[2]));
  LUT6 #(
    .INIT(64'h555555553CCCCCCC)) 
    \timeout_timer_count[3]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [3]),
        .I1(\timeout_timer_count_reg_n_0_[3] ),
        .I2(\timeout_timer_count_reg_n_0_[2] ),
        .I3(\timeout_timer_count_reg_n_0_[0] ),
        .I4(\timeout_timer_count_reg_n_0_[1] ),
        .I5(\timeout_timer_count[12]_i_5_n_0 ),
        .O(p_2_in[3]));
  LUT4 #(
    .INIT(16'h55C3)) 
    \timeout_timer_count[4]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [4]),
        .I1(\timeout_timer_count_reg_n_0_[4] ),
        .I2(\timeout_timer_count[4]_i_2_n_0 ),
        .I3(\timeout_timer_count[12]_i_5_n_0 ),
        .O(p_2_in[4]));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT4 #(
    .INIT(16'h7FFF)) 
    \timeout_timer_count[4]_i_2 
       (.I0(\timeout_timer_count_reg_n_0_[2] ),
        .I1(\timeout_timer_count_reg_n_0_[0] ),
        .I2(\timeout_timer_count_reg_n_0_[1] ),
        .I3(\timeout_timer_count_reg_n_0_[3] ),
        .O(\timeout_timer_count[4]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h55C3)) 
    \timeout_timer_count[5]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [5]),
        .I1(\timeout_timer_count_reg_n_0_[5] ),
        .I2(\timeout_timer_count[5]_i_2_n_0 ),
        .I3(\timeout_timer_count[12]_i_5_n_0 ),
        .O(p_2_in[5]));
  (* SOFT_HLUTNM = "soft_lutpair53" *) 
  LUT5 #(
    .INIT(32'h7FFFFFFF)) 
    \timeout_timer_count[5]_i_2 
       (.I0(\timeout_timer_count_reg_n_0_[3] ),
        .I1(\timeout_timer_count_reg_n_0_[1] ),
        .I2(\timeout_timer_count_reg_n_0_[0] ),
        .I3(\timeout_timer_count_reg_n_0_[2] ),
        .I4(\timeout_timer_count_reg_n_0_[4] ),
        .O(\timeout_timer_count[5]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h55C3)) 
    \timeout_timer_count[6]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [6]),
        .I1(\timeout_timer_count_reg_n_0_[6] ),
        .I2(\timeout_timer_count[8]_i_2_n_0 ),
        .I3(\timeout_timer_count[12]_i_5_n_0 ),
        .O(p_2_in[6]));
  LUT5 #(
    .INIT(32'h5555CC3C)) 
    \timeout_timer_count[7]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [7]),
        .I1(\timeout_timer_count_reg_n_0_[7] ),
        .I2(\timeout_timer_count_reg_n_0_[6] ),
        .I3(\timeout_timer_count[8]_i_2_n_0 ),
        .I4(\timeout_timer_count[12]_i_5_n_0 ),
        .O(p_2_in[7]));
  LUT6 #(
    .INIT(64'h7447747474747474)) 
    \timeout_timer_count[8]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [8]),
        .I1(\timeout_timer_count[12]_i_5_n_0 ),
        .I2(\timeout_timer_count_reg_n_0_[8] ),
        .I3(\timeout_timer_count[8]_i_2_n_0 ),
        .I4(\timeout_timer_count_reg_n_0_[6] ),
        .I5(\timeout_timer_count_reg_n_0_[7] ),
        .O(p_2_in[8]));
  LUT6 #(
    .INIT(64'h7FFFFFFFFFFFFFFF)) 
    \timeout_timer_count[8]_i_2 
       (.I0(\timeout_timer_count_reg_n_0_[4] ),
        .I1(\timeout_timer_count_reg_n_0_[2] ),
        .I2(\timeout_timer_count_reg_n_0_[0] ),
        .I3(\timeout_timer_count_reg_n_0_[1] ),
        .I4(\timeout_timer_count_reg_n_0_[3] ),
        .I5(\timeout_timer_count_reg_n_0_[5] ),
        .O(\timeout_timer_count[8]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h4774)) 
    \timeout_timer_count[9]_i_1 
       (.I0(\axi_rdata_reg[11]_1 [9]),
        .I1(\timeout_timer_count[12]_i_5_n_0 ),
        .I2(\timeout_timer_count_reg_n_0_[9] ),
        .I3(\timeout_timer_count[9]_i_2_n_0 ),
        .O(p_2_in[9]));
  (* SOFT_HLUTNM = "soft_lutpair52" *) 
  LUT4 #(
    .INIT(16'h2000)) 
    \timeout_timer_count[9]_i_2 
       (.I0(\timeout_timer_count_reg_n_0_[8] ),
        .I1(\timeout_timer_count[8]_i_2_n_0 ),
        .I2(\timeout_timer_count_reg_n_0_[6] ),
        .I3(\timeout_timer_count_reg_n_0_[7] ),
        .O(\timeout_timer_count[9]_i_2_n_0 ));
  FDRE \timeout_timer_count_reg[0] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[0]),
        .Q(\timeout_timer_count_reg_n_0_[0] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[10] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[10]),
        .Q(\timeout_timer_count_reg_n_0_[10] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[11] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[11]),
        .Q(\timeout_timer_count_reg_n_0_[11] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[12] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[12]),
        .Q(timeout),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[1] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[1]),
        .Q(\timeout_timer_count_reg_n_0_[1] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[2] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[2]),
        .Q(\timeout_timer_count_reg_n_0_[2] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[3] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[3]),
        .Q(\timeout_timer_count_reg_n_0_[3] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[4] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[4]),
        .Q(\timeout_timer_count_reg_n_0_[4] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[5] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[5]),
        .Q(\timeout_timer_count_reg_n_0_[5] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[6] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[6]),
        .Q(\timeout_timer_count_reg_n_0_[6] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[7] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[7]),
        .Q(\timeout_timer_count_reg_n_0_[7] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[8] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[8]),
        .Q(\timeout_timer_count_reg_n_0_[8] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  FDRE \timeout_timer_count_reg[9] 
       (.C(s_axi_aclk),
        .CE(\timeout_timer_count[12]_i_2_n_0 ),
        .D(p_2_in[9]),
        .Q(\timeout_timer_count_reg_n_0_[9] ),
        .R(\timeout_timer_count[12]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000080000000)) 
    \timeout_value[11]_i_1 
       (.I0(\timeout_value[11]_i_2_n_0 ),
        .I1(adc_ds_axi_map_wready),
        .I2(s_axi_wvalid),
        .I3(\slv_addr_reg[11]_0 [2]),
        .I4(\slv_addr_reg[11]_0 [1]),
        .I5(\slv_addr_reg[11]_0 [0]),
        .O(E));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \timeout_value[11]_i_2 
       (.I0(\slv_addr_reg[11]_0 [6]),
        .I1(\slv_addr_reg[11]_0 [5]),
        .I2(\slv_addr_reg[11]_0 [7]),
        .I3(\axi_rdata[15]_i_4_n_0 ),
        .I4(\slv_addr_reg[11]_0 [3]),
        .I5(\slv_addr_reg[11]_0 [4]),
        .O(\timeout_value[11]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hF1F1000100000000)) 
    valid_waddr_i_1
       (.I0(timeout),
        .I1(valid_waddr_i_2_n_0),
        .I2(valid_waddr_i_3_n_0),
        .I3(valid_waddr_i_4_n_0),
        .I4(valid_waddr_reg_n_0),
        .I5(s_axi_aresetn),
        .O(valid_waddr_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT2 #(
    .INIT(4'h8)) 
    valid_waddr_i_2
       (.I0(axi_bvalid_reg_0),
        .I1(s_axi_bready),
        .O(valid_waddr_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair60" *) 
  LUT3 #(
    .INIT(8'h54)) 
    valid_waddr_i_3
       (.I0(timeout),
        .I1(s_axi_arvalid),
        .I2(read_in_progress),
        .O(valid_waddr_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair55" *) 
  LUT2 #(
    .INIT(4'hB)) 
    valid_waddr_i_4
       (.I0(axi_awready_reg_0),
        .I1(s_axi_awvalid),
        .O(valid_waddr_i_4_n_0));
  FDRE #(
    .INIT(1'b0)) 
    valid_waddr_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(valid_waddr_i_1_n_0),
        .Q(valid_waddr_reg_n_0),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h00000000FFFFF888)) 
    write_in_progress_i_1
       (.I0(s_axi_awvalid),
        .I1(axi_awready_reg_0),
        .I2(axi_wr_access_reg_0),
        .I3(s_axi_wvalid),
        .I4(write_in_progress),
        .I5(write_in_progress_i_2_n_0),
        .O(write_in_progress_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair67" *) 
  LUT4 #(
    .INIT(16'hFF8F)) 
    write_in_progress_i_2
       (.I0(s_axi_bready),
        .I1(axi_bvalid_reg_0),
        .I2(s_axi_aresetn),
        .I3(timeout),
        .O(write_in_progress_i_2_n_0));
  FDRE write_in_progress_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(write_in_progress_i_1_n_0),
        .Q(write_in_progress),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_hshk_pls_gen" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen
   (SR,
    slv_wren_done_pulse,
    E,
    clk2_valid_pulse_reg_0,
    clk2_valid_pulse_reg_1,
    clk2_valid_pulse_reg_2,
    clk2_valid_pulse_reg_3,
    clk2_valid_pulse_reg_4,
    clk2_valid_pulse_reg_5,
    clk2_valid_pulse_reg_6,
    clk2_valid_pulse_reg_7,
    clk2_valid_pulse_reg_8,
    clk2_valid_pulse_reg_9,
    clk2_valid_pulse_reg_10,
    clk2_valid_pulse_reg_11,
    clk2_valid_pulse_reg_12,
    clk2_valid_pulse_reg_13,
    clk2_valid_pulse_reg_14,
    clk1_ready_pulse_reg_0,
    \syncstages_ff_reg[4] ,
    src_in,
    s_axi_aclk,
    \adc30_ds_enable_0_reg[0] ,
    slv_access_valid_hold_reg,
    \adc33_ds_type_0_reg[0] ,
    \adc33_ds_enable_0_reg[0] ,
    \adc31_ds_control_0_reg[0] ,
    \adc31_ds_type_0_reg[0] ,
    \adc31_ds_enable_0_reg[0] ,
    \adc30_ds_type_0_reg[0] ,
    \adc30_ds_control_0_reg[0] ,
    \adc30_ds_inc_0_reg[0] ,
    \adc33_ds_inc_0_reg[0] ,
    \adc33_ds_control_0_reg[0] ,
    \adc32_ds_type_0_reg[0] ,
    \adc32_ds_inc_0_reg[0] ,
    \adc32_ds_enable_0_reg[0] ,
    \adc32_ds_control_0_reg[0] ,
    \adc31_ds_inc_0_reg[0] ,
    s_axi_aresetn,
    slv_rden_r_0,
    slv_wren_done_pulse_1,
    s_axi_wvalid,
    adc3axi_map_wready,
    adc3slv_rden);
  output [0:0]SR;
  output slv_wren_done_pulse;
  output [0:0]E;
  output [0:0]clk2_valid_pulse_reg_0;
  output [0:0]clk2_valid_pulse_reg_1;
  output [0:0]clk2_valid_pulse_reg_2;
  output [0:0]clk2_valid_pulse_reg_3;
  output [0:0]clk2_valid_pulse_reg_4;
  output [0:0]clk2_valid_pulse_reg_5;
  output [0:0]clk2_valid_pulse_reg_6;
  output [0:0]clk2_valid_pulse_reg_7;
  output [0:0]clk2_valid_pulse_reg_8;
  output [0:0]clk2_valid_pulse_reg_9;
  output [0:0]clk2_valid_pulse_reg_10;
  output [0:0]clk2_valid_pulse_reg_11;
  output [0:0]clk2_valid_pulse_reg_12;
  output [0:0]clk2_valid_pulse_reg_13;
  output [0:0]clk2_valid_pulse_reg_14;
  output clk1_ready_pulse_reg_0;
  output \syncstages_ff_reg[4] ;
  input src_in;
  input s_axi_aclk;
  input \adc30_ds_enable_0_reg[0] ;
  input slv_access_valid_hold_reg;
  input \adc33_ds_type_0_reg[0] ;
  input \adc33_ds_enable_0_reg[0] ;
  input \adc31_ds_control_0_reg[0] ;
  input \adc31_ds_type_0_reg[0] ;
  input \adc31_ds_enable_0_reg[0] ;
  input \adc30_ds_type_0_reg[0] ;
  input \adc30_ds_control_0_reg[0] ;
  input \adc30_ds_inc_0_reg[0] ;
  input \adc33_ds_inc_0_reg[0] ;
  input \adc33_ds_control_0_reg[0] ;
  input \adc32_ds_type_0_reg[0] ;
  input \adc32_ds_inc_0_reg[0] ;
  input \adc32_ds_enable_0_reg[0] ;
  input \adc32_ds_control_0_reg[0] ;
  input \adc31_ds_inc_0_reg[0] ;
  input s_axi_aresetn;
  input slv_rden_r_0;
  input slv_wren_done_pulse_1;
  input s_axi_wvalid;
  input adc3axi_map_wready;
  input adc3slv_rden;

  wire [0:0]E;
  wire [0:0]SR;
  wire \adc30_ds_control_0_reg[0] ;
  wire \adc30_ds_enable_0_reg[0] ;
  wire \adc30_ds_inc_0_reg[0] ;
  wire \adc30_ds_type_0_reg[0] ;
  wire \adc31_ds_control_0_reg[0] ;
  wire \adc31_ds_enable_0_reg[0] ;
  wire \adc31_ds_inc_0_reg[0] ;
  wire \adc31_ds_type_0_reg[0] ;
  wire \adc32_ds_control_0_reg[0] ;
  wire \adc32_ds_enable_0_reg[0] ;
  wire \adc32_ds_inc_0_reg[0] ;
  wire \adc32_ds_type_0_reg[0] ;
  wire \adc33_ds_control_0_reg[0] ;
  wire \adc33_ds_enable_0_reg[0] ;
  wire \adc33_ds_inc_0_reg[0] ;
  wire \adc33_ds_type_0_reg[0] ;
  wire adc3axi_map_wready;
  wire adc3slv_rden;
  wire axi_2_drp_valid_i_n_0;
  wire axi_2_drp_valid_i_n_2;
  wire clk1_ready_pulse0;
  wire clk1_ready_pulse_reg_0;
  wire clk1_ready_sync_r;
  wire clk2_ready;
  wire clk2_valid_pulse0;
  wire [0:0]clk2_valid_pulse_reg_0;
  wire [0:0]clk2_valid_pulse_reg_1;
  wire [0:0]clk2_valid_pulse_reg_10;
  wire [0:0]clk2_valid_pulse_reg_11;
  wire [0:0]clk2_valid_pulse_reg_12;
  wire [0:0]clk2_valid_pulse_reg_13;
  wire [0:0]clk2_valid_pulse_reg_14;
  wire [0:0]clk2_valid_pulse_reg_2;
  wire [0:0]clk2_valid_pulse_reg_3;
  wire [0:0]clk2_valid_pulse_reg_4;
  wire [0:0]clk2_valid_pulse_reg_5;
  wire [0:0]clk2_valid_pulse_reg_6;
  wire [0:0]clk2_valid_pulse_reg_7;
  wire [0:0]clk2_valid_pulse_reg_8;
  wire [0:0]clk2_valid_pulse_reg_9;
  wire clk2_valid_sync_r;
  wire s_axi_aclk;
  wire s_axi_aresetn;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire slv_rden_r_0;
  wire slv_wren_clear;
  wire slv_wren_clk2;
  wire slv_wren_done_pulse;
  wire slv_wren_done_pulse_1;
  wire src_in;
  wire \syncstages_ff_reg[4] ;

  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc30_ds_control_0[1]_i_1 
       (.I0(\adc30_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_6));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc30_ds_enable_0[7]_i_1 
       (.I0(\adc30_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc30_ds_inc_0[11]_i_1 
       (.I0(\adc30_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_7));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc30_ds_type_0[3]_i_1 
       (.I0(\adc30_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_5));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc31_ds_control_0[1]_i_1 
       (.I0(\adc31_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_2));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc31_ds_enable_0[7]_i_1 
       (.I0(\adc31_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_4));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc31_ds_inc_0[11]_i_1 
       (.I0(\adc31_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_14));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc31_ds_type_0[3]_i_1 
       (.I0(\adc31_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_3));
  (* SOFT_HLUTNM = "soft_lutpair39" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc32_ds_control_0[1]_i_1 
       (.I0(\adc32_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_13));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc32_ds_enable_0[7]_i_1 
       (.I0(\adc32_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_12));
  (* SOFT_HLUTNM = "soft_lutpair38" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc32_ds_inc_0[11]_i_1 
       (.I0(\adc32_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_11));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc32_ds_type_0[3]_i_1 
       (.I0(\adc32_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_10));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc33_ds_control_0[1]_i_1 
       (.I0(\adc33_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_9));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc33_ds_enable_0[7]_i_1 
       (.I0(\adc33_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_1));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc33_ds_inc_0[11]_i_1 
       (.I0(\adc33_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_8));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc33_ds_type_0[3]_i_1 
       (.I0(\adc33_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_0));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__7 axi_2_drp_valid_i
       (.clk2_ready_reg(clk2_ready),
        .clk2_valid_pulse0(clk2_valid_pulse0),
        .clk2_valid_pulse_reg(axi_2_drp_valid_i_n_2),
        .clk2_valid_sync_r(clk2_valid_sync_r),
        .dest_out(axi_2_drp_valid_i_n_0),
        .s_axi_aclk(s_axi_aclk),
        .slv_wren_clk2(slv_wren_clk2),
        .src_in(src_in));
  LUT1 #(
    .INIT(2'h1)) 
    axi_awready_i_1
       (.I0(s_axi_aresetn),
        .O(SR));
  LUT4 #(
    .INIT(16'hD0DD)) 
    \axi_bresp[1]_i_4 
       (.I0(slv_wren_done_pulse),
        .I1(slv_access_valid_hold_reg),
        .I2(slv_rden_r_0),
        .I3(slv_wren_done_pulse_1),
        .O(clk1_ready_pulse_reg_0));
  FDRE clk1_ready_pulse_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk1_ready_pulse0),
        .Q(slv_wren_done_pulse),
        .R(SR));
  FDRE clk1_ready_sync_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(slv_wren_clear),
        .Q(clk1_ready_sync_r),
        .R(SR));
  FDRE clk2_ready_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_2),
        .Q(clk2_ready),
        .R(SR));
  FDRE clk2_valid_pulse_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk2_valid_pulse0),
        .Q(slv_wren_clk2),
        .R(SR));
  FDRE clk2_valid_sync_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_0),
        .Q(clk2_valid_sync_r),
        .R(SR));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync drp_2_axi_in_progress_i
       (.adc3axi_map_wready(adc3axi_map_wready),
        .adc3slv_rden(adc3slv_rden),
        .clk1_ready_pulse0(clk1_ready_pulse0),
        .clk1_ready_sync_r(clk1_ready_sync_r),
        .dest_out(slv_wren_clear),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_access_valid_hold_reg),
        .src_in(src_in),
        .\syncstages_ff_reg[0] (clk2_ready),
        .\syncstages_ff_reg[4] (\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_hshk_pls_gen" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__1
   (slv_wren_done_pulse,
    SR,
    E,
    slv_rden_r_reg,
    slv_rden_r_reg_0,
    slv_rden_r_reg_1,
    slv_rden_r_reg_2,
    slv_rden_r_reg_3,
    slv_rden_r_reg_4,
    slv_rden_r_reg_5,
    slv_rden_r_reg_6,
    slv_rden_r_reg_7,
    slv_rden_r_reg_8,
    slv_rden_r_reg_9,
    slv_rden_r_reg_10,
    slv_rden_r_reg_11,
    slv_rden_r_reg_12,
    slv_rden_r_reg_13,
    slv_rden_r_reg_14,
    \slv_wdata_r_internal_reg[0] ,
    \syncstages_ff_reg[4] ,
    src_in,
    s0_axis_clock,
    s_axi_aclk,
    p_0_in,
    \adc03_ds_enable_0_reg[7] ,
    slv_access_valid_hold_reg,
    \adc00_ds_type_0_reg[3] ,
    \adc03_ds_control_0_reg[1] ,
    \axi_rresp[1]_i_2 ,
    adc_ds_slv_rden,
    \adc00_ds_enable_0_reg[0] ,
    \adc03_ds_type_0_reg[0] ,
    \adc01_ds_control_0_reg[0] ,
    \adc01_ds_type_0_reg[0] ,
    \adc01_ds_enable_0_reg[0] ,
    \adc00_ds_control_0_reg[0] ,
    \adc00_ds_inc_0_reg[0] ,
    \adc03_ds_inc_0_reg[0] ,
    \adc02_ds_type_0_reg[0] ,
    \adc02_ds_inc_0_reg[0] ,
    \adc02_ds_enable_0_reg[0] ,
    \adc02_ds_control_0_reg[0] ,
    \adc01_ds_inc_0_reg[0] ,
    dest_rst,
    Q,
    adc00_ds_pulse_control_0_reg,
    adc00_ds_pulse_control_0_reg_0,
    adc00_ds_pulse_control_0_reg_1,
    adc00_ds_pulse_control_0,
    s_axi_wvalid,
    adc0axi_map_wready,
    adc0slv_rden);
  output slv_wren_done_pulse;
  output [0:0]SR;
  output [0:0]E;
  output [0:0]slv_rden_r_reg;
  output [0:0]slv_rden_r_reg_0;
  output slv_rden_r_reg_1;
  output [0:0]slv_rden_r_reg_2;
  output [0:0]slv_rden_r_reg_3;
  output [0:0]slv_rden_r_reg_4;
  output [0:0]slv_rden_r_reg_5;
  output [0:0]slv_rden_r_reg_6;
  output [0:0]slv_rden_r_reg_7;
  output [0:0]slv_rden_r_reg_8;
  output [0:0]slv_rden_r_reg_9;
  output [0:0]slv_rden_r_reg_10;
  output [0:0]slv_rden_r_reg_11;
  output [0:0]slv_rden_r_reg_12;
  output [0:0]slv_rden_r_reg_13;
  output [0:0]slv_rden_r_reg_14;
  output \slv_wdata_r_internal_reg[0] ;
  output \syncstages_ff_reg[4] ;
  input src_in;
  input s0_axis_clock;
  input s_axi_aclk;
  input p_0_in;
  input \adc03_ds_enable_0_reg[7] ;
  input slv_access_valid_hold_reg;
  input \adc00_ds_type_0_reg[3] ;
  input \adc03_ds_control_0_reg[1] ;
  input [0:0]\axi_rresp[1]_i_2 ;
  input adc_ds_slv_rden;
  input \adc00_ds_enable_0_reg[0] ;
  input \adc03_ds_type_0_reg[0] ;
  input \adc01_ds_control_0_reg[0] ;
  input \adc01_ds_type_0_reg[0] ;
  input \adc01_ds_enable_0_reg[0] ;
  input \adc00_ds_control_0_reg[0] ;
  input \adc00_ds_inc_0_reg[0] ;
  input \adc03_ds_inc_0_reg[0] ;
  input \adc02_ds_type_0_reg[0] ;
  input \adc02_ds_inc_0_reg[0] ;
  input \adc02_ds_enable_0_reg[0] ;
  input \adc02_ds_control_0_reg[0] ;
  input \adc01_ds_inc_0_reg[0] ;
  input dest_rst;
  input [0:0]Q;
  input adc00_ds_pulse_control_0_reg;
  input [0:0]adc00_ds_pulse_control_0_reg_0;
  input adc00_ds_pulse_control_0_reg_1;
  input adc00_ds_pulse_control_0;
  input s_axi_wvalid;
  input adc0axi_map_wready;
  input adc0slv_rden;

  wire [0:0]E;
  wire [0:0]Q;
  wire [0:0]SR;
  wire \adc00_ds_control_0_reg[0] ;
  wire \adc00_ds_enable_0_reg[0] ;
  wire \adc00_ds_inc_0_reg[0] ;
  wire adc00_ds_pulse_control_0;
  wire adc00_ds_pulse_control_0_i_3_n_0;
  wire adc00_ds_pulse_control_0_reg;
  wire [0:0]adc00_ds_pulse_control_0_reg_0;
  wire adc00_ds_pulse_control_0_reg_1;
  wire \adc00_ds_type_0_reg[3] ;
  wire \adc01_ds_control_0_reg[0] ;
  wire \adc01_ds_enable_0_reg[0] ;
  wire \adc01_ds_inc_0_reg[0] ;
  wire \adc01_ds_type_0_reg[0] ;
  wire \adc02_ds_control_0_reg[0] ;
  wire \adc02_ds_enable_0_reg[0] ;
  wire \adc02_ds_inc_0_reg[0] ;
  wire \adc02_ds_type_0_reg[0] ;
  wire \adc03_ds_control_0_reg[1] ;
  wire \adc03_ds_enable_0_reg[7] ;
  wire \adc03_ds_inc_0_reg[0] ;
  wire \adc03_ds_type_0_reg[0] ;
  wire adc0axi_map_wready;
  wire adc0slv_rden;
  wire adc_ds_slv_rden;
  wire axi_2_drp_valid_i_n_0;
  wire axi_2_drp_valid_i_n_2;
  wire [0:0]\axi_rresp[1]_i_2 ;
  wire clk1_ready_pulse0;
  wire clk1_ready_sync_r;
  wire clk2_ready;
  wire clk2_valid_pulse0;
  wire clk2_valid_sync_r;
  wire dest_rst;
  wire p_0_in;
  wire s0_axis_clock;
  wire s_axi_aclk;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire [0:0]slv_rden_r_reg;
  wire [0:0]slv_rden_r_reg_0;
  wire slv_rden_r_reg_1;
  wire [0:0]slv_rden_r_reg_10;
  wire [0:0]slv_rden_r_reg_11;
  wire [0:0]slv_rden_r_reg_12;
  wire [0:0]slv_rden_r_reg_13;
  wire [0:0]slv_rden_r_reg_14;
  wire [0:0]slv_rden_r_reg_2;
  wire [0:0]slv_rden_r_reg_3;
  wire [0:0]slv_rden_r_reg_4;
  wire [0:0]slv_rden_r_reg_5;
  wire [0:0]slv_rden_r_reg_6;
  wire [0:0]slv_rden_r_reg_7;
  wire [0:0]slv_rden_r_reg_8;
  wire [0:0]slv_rden_r_reg_9;
  wire \slv_wdata_r_internal_reg[0] ;
  wire slv_wren_clear;
  wire slv_wren_clk2;
  wire slv_wren_done_pulse;
  wire src_in;
  wire \syncstages_ff_reg[4] ;

  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc00_ds_control_0[1]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc00_ds_control_0_reg[0] ),
        .O(slv_rden_r_reg_7));
  LUT1 #(
    .INIT(2'h1)) 
    \adc00_ds_enable_0[0]_i_1 
       (.I0(dest_rst),
        .O(SR));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'h20)) 
    \adc00_ds_enable_0[0]_i_2 
       (.I0(\adc00_ds_enable_0_reg[0] ),
        .I1(slv_access_valid_hold_reg),
        .I2(slv_wren_clk2),
        .O(slv_rden_r_reg_2));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc00_ds_inc_0[11]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc00_ds_inc_0_reg[0] ),
        .O(slv_rden_r_reg_8));
  LUT6 #(
    .INIT(64'hFFFFFEFF00000200)) 
    adc00_ds_pulse_control_0_i_1
       (.I0(Q),
        .I1(adc00_ds_pulse_control_0_reg),
        .I2(adc00_ds_pulse_control_0_reg_0),
        .I3(adc00_ds_pulse_control_0_i_3_n_0),
        .I4(adc00_ds_pulse_control_0_reg_1),
        .I5(adc00_ds_pulse_control_0),
        .O(\slv_wdata_r_internal_reg[0] ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT2 #(
    .INIT(4'h2)) 
    adc00_ds_pulse_control_0_i_3
       (.I0(slv_wren_clk2),
        .I1(slv_access_valid_hold_reg),
        .O(adc00_ds_pulse_control_0_i_3_n_0));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'h20)) 
    \adc00_ds_type_0[3]_i_1 
       (.I0(\adc00_ds_type_0_reg[3] ),
        .I1(slv_access_valid_hold_reg),
        .I2(slv_wren_clk2),
        .O(slv_rden_r_reg));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc01_ds_control_0[1]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc01_ds_control_0_reg[0] ),
        .O(slv_rden_r_reg_4));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc01_ds_enable_0[7]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc01_ds_enable_0_reg[0] ),
        .O(slv_rden_r_reg_6));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc01_ds_inc_0[11]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc01_ds_inc_0_reg[0] ),
        .O(slv_rden_r_reg_14));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc01_ds_type_0[3]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc01_ds_type_0_reg[0] ),
        .O(slv_rden_r_reg_5));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc02_ds_control_0[1]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc02_ds_control_0_reg[0] ),
        .O(slv_rden_r_reg_13));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc02_ds_enable_0[7]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc02_ds_enable_0_reg[0] ),
        .O(slv_rden_r_reg_12));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc02_ds_inc_0[11]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc02_ds_inc_0_reg[0] ),
        .O(slv_rden_r_reg_11));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc02_ds_type_0[3]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc02_ds_type_0_reg[0] ),
        .O(slv_rden_r_reg_10));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'h20)) 
    \adc03_ds_control_0[1]_i_1 
       (.I0(\adc03_ds_control_0_reg[1] ),
        .I1(slv_access_valid_hold_reg),
        .I2(slv_wren_clk2),
        .O(slv_rden_r_reg_0));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'h20)) 
    \adc03_ds_enable_0[7]_i_1 
       (.I0(\adc03_ds_enable_0_reg[7] ),
        .I1(slv_access_valid_hold_reg),
        .I2(slv_wren_clk2),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc03_ds_inc_0[11]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc03_ds_inc_0_reg[0] ),
        .O(slv_rden_r_reg_9));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \adc03_ds_type_0[3]_i_1 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_clk2),
        .I2(\adc03_ds_type_0_reg[0] ),
        .O(slv_rden_r_reg_3));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__1 axi_2_drp_valid_i
       (.clk2_ready_reg(clk2_ready),
        .clk2_valid_pulse0(clk2_valid_pulse0),
        .clk2_valid_pulse_reg(axi_2_drp_valid_i_n_2),
        .clk2_valid_sync_r(clk2_valid_sync_r),
        .dest_out(axi_2_drp_valid_i_n_0),
        .s0_axis_clock(s0_axis_clock),
        .slv_wren_clk2(slv_wren_clk2),
        .src_in(src_in));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'h8F80)) 
    \axi_rresp[1]_i_4 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_done_pulse),
        .I2(\axi_rresp[1]_i_2 ),
        .I3(adc_ds_slv_rden),
        .O(slv_rden_r_reg_1));
  FDRE clk1_ready_pulse_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk1_ready_pulse0),
        .Q(slv_wren_done_pulse),
        .R(p_0_in));
  FDRE clk1_ready_sync_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(slv_wren_clear),
        .Q(clk1_ready_sync_r),
        .R(p_0_in));
  FDRE clk2_ready_reg
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_2),
        .Q(clk2_ready),
        .R(SR));
  FDRE clk2_valid_pulse_reg
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(clk2_valid_pulse0),
        .Q(slv_wren_clk2),
        .R(SR));
  FDRE clk2_valid_sync_r_reg
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_0),
        .Q(clk2_valid_sync_r),
        .R(SR));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__2 drp_2_axi_in_progress_i
       (.adc0axi_map_wready(adc0axi_map_wready),
        .adc0slv_rden(adc0slv_rden),
        .clk1_ready_pulse0(clk1_ready_pulse0),
        .clk1_ready_sync_r(clk1_ready_sync_r),
        .dest_out(slv_wren_clear),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_access_valid_hold_reg),
        .src_in(src_in),
        .\syncstages_ff_reg[0] (clk2_ready),
        .\syncstages_ff_reg[4] (\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_hshk_pls_gen" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__2
   (slv_wren_done_pulse,
    E,
    clk2_valid_pulse_reg_0,
    clk2_valid_pulse_reg_1,
    slv_rden_r_reg,
    clk2_valid_pulse_reg_2,
    clk2_valid_pulse_reg_3,
    clk2_valid_pulse_reg_4,
    clk2_valid_pulse_reg_5,
    clk2_valid_pulse_reg_6,
    clk2_valid_pulse_reg_7,
    clk2_valid_pulse_reg_8,
    clk2_valid_pulse_reg_9,
    clk2_valid_pulse_reg_10,
    clk2_valid_pulse_reg_11,
    clk2_valid_pulse_reg_12,
    clk2_valid_pulse_reg_13,
    clk2_valid_pulse_reg_14,
    \syncstages_ff_reg[4] ,
    src_in,
    s_axi_aclk,
    p_0_in,
    \adc10_ds_enable_0_reg[0] ,
    slv_access_valid_hold_reg,
    \adc13_ds_type_0_reg[0] ,
    \adc13_ds_enable_0_reg[0] ,
    slv_wren_done_pulse_0,
    slv_rden_r_1,
    s_axi_wvalid,
    adc_ds_axi_map_wready,
    \adc11_ds_control_0_reg[0] ,
    \adc11_ds_type_0_reg[0] ,
    \adc11_ds_enable_0_reg[0] ,
    \adc10_ds_type_0_reg[0] ,
    \adc10_ds_control_0_reg[0] ,
    \adc10_ds_inc_0_reg[0] ,
    \adc13_ds_inc_0_reg[0] ,
    \adc13_ds_control_0_reg[0] ,
    \adc12_ds_type_0_reg[0] ,
    \adc12_ds_inc_0_reg[0] ,
    \adc12_ds_enable_0_reg[0] ,
    \adc12_ds_control_0_reg[0] ,
    \adc11_ds_inc_0_reg[0] ,
    adc1axi_map_wready,
    adc1slv_rden);
  output slv_wren_done_pulse;
  output [0:0]E;
  output [0:0]clk2_valid_pulse_reg_0;
  output [0:0]clk2_valid_pulse_reg_1;
  output slv_rden_r_reg;
  output [0:0]clk2_valid_pulse_reg_2;
  output [0:0]clk2_valid_pulse_reg_3;
  output [0:0]clk2_valid_pulse_reg_4;
  output [0:0]clk2_valid_pulse_reg_5;
  output [0:0]clk2_valid_pulse_reg_6;
  output [0:0]clk2_valid_pulse_reg_7;
  output [0:0]clk2_valid_pulse_reg_8;
  output [0:0]clk2_valid_pulse_reg_9;
  output [0:0]clk2_valid_pulse_reg_10;
  output [0:0]clk2_valid_pulse_reg_11;
  output [0:0]clk2_valid_pulse_reg_12;
  output [0:0]clk2_valid_pulse_reg_13;
  output [0:0]clk2_valid_pulse_reg_14;
  output \syncstages_ff_reg[4] ;
  input src_in;
  input s_axi_aclk;
  input p_0_in;
  input \adc10_ds_enable_0_reg[0] ;
  input slv_access_valid_hold_reg;
  input \adc13_ds_type_0_reg[0] ;
  input \adc13_ds_enable_0_reg[0] ;
  input slv_wren_done_pulse_0;
  input slv_rden_r_1;
  input s_axi_wvalid;
  input adc_ds_axi_map_wready;
  input \adc11_ds_control_0_reg[0] ;
  input \adc11_ds_type_0_reg[0] ;
  input \adc11_ds_enable_0_reg[0] ;
  input \adc10_ds_type_0_reg[0] ;
  input \adc10_ds_control_0_reg[0] ;
  input \adc10_ds_inc_0_reg[0] ;
  input \adc13_ds_inc_0_reg[0] ;
  input \adc13_ds_control_0_reg[0] ;
  input \adc12_ds_type_0_reg[0] ;
  input \adc12_ds_inc_0_reg[0] ;
  input \adc12_ds_enable_0_reg[0] ;
  input \adc12_ds_control_0_reg[0] ;
  input \adc11_ds_inc_0_reg[0] ;
  input adc1axi_map_wready;
  input adc1slv_rden;

  wire [0:0]E;
  wire \adc10_ds_control_0_reg[0] ;
  wire \adc10_ds_enable_0_reg[0] ;
  wire \adc10_ds_inc_0_reg[0] ;
  wire \adc10_ds_type_0_reg[0] ;
  wire \adc11_ds_control_0_reg[0] ;
  wire \adc11_ds_enable_0_reg[0] ;
  wire \adc11_ds_inc_0_reg[0] ;
  wire \adc11_ds_type_0_reg[0] ;
  wire \adc12_ds_control_0_reg[0] ;
  wire \adc12_ds_enable_0_reg[0] ;
  wire \adc12_ds_inc_0_reg[0] ;
  wire \adc12_ds_type_0_reg[0] ;
  wire \adc13_ds_control_0_reg[0] ;
  wire \adc13_ds_enable_0_reg[0] ;
  wire \adc13_ds_inc_0_reg[0] ;
  wire \adc13_ds_type_0_reg[0] ;
  wire adc1axi_map_wready;
  wire adc1slv_rden;
  wire adc_ds_axi_map_wready;
  wire axi_2_drp_valid_i_n_0;
  wire axi_2_drp_valid_i_n_2;
  wire clk1_ready_pulse0;
  wire clk1_ready_sync_r;
  wire clk2_ready;
  wire clk2_valid_pulse0;
  wire [0:0]clk2_valid_pulse_reg_0;
  wire [0:0]clk2_valid_pulse_reg_1;
  wire [0:0]clk2_valid_pulse_reg_10;
  wire [0:0]clk2_valid_pulse_reg_11;
  wire [0:0]clk2_valid_pulse_reg_12;
  wire [0:0]clk2_valid_pulse_reg_13;
  wire [0:0]clk2_valid_pulse_reg_14;
  wire [0:0]clk2_valid_pulse_reg_2;
  wire [0:0]clk2_valid_pulse_reg_3;
  wire [0:0]clk2_valid_pulse_reg_4;
  wire [0:0]clk2_valid_pulse_reg_5;
  wire [0:0]clk2_valid_pulse_reg_6;
  wire [0:0]clk2_valid_pulse_reg_7;
  wire [0:0]clk2_valid_pulse_reg_8;
  wire [0:0]clk2_valid_pulse_reg_9;
  wire clk2_valid_sync_r;
  wire p_0_in;
  wire s_axi_aclk;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire slv_rden_r_1;
  wire slv_rden_r_reg;
  wire slv_wren_clear;
  wire slv_wren_clk2;
  wire slv_wren_done_pulse;
  wire slv_wren_done_pulse_0;
  wire src_in;
  wire \syncstages_ff_reg[4] ;

  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc10_ds_control_0[1]_i_1 
       (.I0(\adc10_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_6));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc10_ds_enable_0[7]_i_1 
       (.I0(\adc10_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc10_ds_inc_0[11]_i_1 
       (.I0(\adc10_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_7));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc10_ds_type_0[3]_i_1 
       (.I0(\adc10_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_5));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc11_ds_control_0[1]_i_1 
       (.I0(\adc11_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_2));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc11_ds_enable_0[7]_i_1 
       (.I0(\adc11_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_4));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc11_ds_inc_0[11]_i_1 
       (.I0(\adc11_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_14));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc11_ds_type_0[3]_i_1 
       (.I0(\adc11_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_3));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc12_ds_control_0[1]_i_1 
       (.I0(\adc12_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_13));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc12_ds_enable_0[7]_i_1 
       (.I0(\adc12_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_12));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc12_ds_inc_0[11]_i_1 
       (.I0(\adc12_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_11));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc12_ds_type_0[3]_i_1 
       (.I0(\adc12_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_10));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc13_ds_control_0[1]_i_1 
       (.I0(\adc13_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_9));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc13_ds_enable_0[7]_i_1 
       (.I0(\adc13_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_1));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc13_ds_inc_0[11]_i_1 
       (.I0(\adc13_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_8));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc13_ds_type_0[3]_i_1 
       (.I0(\adc13_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_0));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__3 axi_2_drp_valid_i
       (.clk2_ready_reg(clk2_ready),
        .clk2_valid_pulse0(clk2_valid_pulse0),
        .clk2_valid_pulse_reg(axi_2_drp_valid_i_n_2),
        .clk2_valid_sync_r(clk2_valid_sync_r),
        .dest_out(axi_2_drp_valid_i_n_0),
        .s_axi_aclk(s_axi_aclk),
        .slv_wren_clk2(slv_wren_clk2),
        .src_in(src_in));
  LUT6 #(
    .INIT(64'hFFFF44F444F444F4)) 
    \axi_bresp[1]_i_3 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_done_pulse),
        .I2(slv_wren_done_pulse_0),
        .I3(slv_rden_r_1),
        .I4(s_axi_wvalid),
        .I5(adc_ds_axi_map_wready),
        .O(slv_rden_r_reg));
  FDRE clk1_ready_pulse_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk1_ready_pulse0),
        .Q(slv_wren_done_pulse),
        .R(p_0_in));
  FDRE clk1_ready_sync_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(slv_wren_clear),
        .Q(clk1_ready_sync_r),
        .R(p_0_in));
  FDRE clk2_ready_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_2),
        .Q(clk2_ready),
        .R(p_0_in));
  FDRE clk2_valid_pulse_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk2_valid_pulse0),
        .Q(slv_wren_clk2),
        .R(p_0_in));
  FDRE clk2_valid_sync_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_0),
        .Q(clk2_valid_sync_r),
        .R(p_0_in));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__4 drp_2_axi_in_progress_i
       (.adc1axi_map_wready(adc1axi_map_wready),
        .adc1slv_rden(adc1slv_rden),
        .clk1_ready_pulse0(clk1_ready_pulse0),
        .clk1_ready_sync_r(clk1_ready_sync_r),
        .dest_out(slv_wren_clear),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_access_valid_hold_reg),
        .src_in(src_in),
        .\syncstages_ff_reg[0] (clk2_ready),
        .\syncstages_ff_reg[4] (\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_hshk_pls_gen" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__3
   (slv_wren_done_pulse,
    slv_rden_r_reg,
    E,
    clk2_valid_pulse_reg_0,
    clk2_valid_pulse_reg_1,
    clk2_valid_pulse_reg_2,
    clk2_valid_pulse_reg_3,
    clk2_valid_pulse_reg_4,
    clk2_valid_pulse_reg_5,
    clk2_valid_pulse_reg_6,
    clk2_valid_pulse_reg_7,
    clk2_valid_pulse_reg_8,
    clk2_valid_pulse_reg_9,
    clk2_valid_pulse_reg_10,
    clk2_valid_pulse_reg_11,
    clk2_valid_pulse_reg_12,
    clk2_valid_pulse_reg_13,
    clk2_valid_pulse_reg_14,
    \syncstages_ff_reg[4] ,
    src_in,
    s_axi_aclk,
    p_0_in,
    slv_access_valid_hold_reg,
    Q,
    slv_rden_r_0,
    slv_wren_done_pulse_1,
    \adc20_ds_enable_0_reg[0] ,
    \adc23_ds_type_0_reg[0] ,
    \adc23_ds_enable_0_reg[0] ,
    \adc21_ds_control_0_reg[0] ,
    \adc21_ds_type_0_reg[0] ,
    \adc21_ds_enable_0_reg[0] ,
    \adc20_ds_type_0_reg[0] ,
    \adc20_ds_control_0_reg[0] ,
    \adc20_ds_inc_0_reg[0] ,
    \adc23_ds_inc_0_reg[0] ,
    \adc23_ds_control_0_reg[0] ,
    \adc22_ds_type_0_reg[0] ,
    \adc22_ds_inc_0_reg[0] ,
    \adc22_ds_enable_0_reg[0] ,
    \adc22_ds_control_0_reg[0] ,
    \adc21_ds_inc_0_reg[0] ,
    s_axi_wvalid,
    adc2axi_map_wready,
    adc2slv_rden);
  output slv_wren_done_pulse;
  output slv_rden_r_reg;
  output [0:0]E;
  output [0:0]clk2_valid_pulse_reg_0;
  output [0:0]clk2_valid_pulse_reg_1;
  output [0:0]clk2_valid_pulse_reg_2;
  output [0:0]clk2_valid_pulse_reg_3;
  output [0:0]clk2_valid_pulse_reg_4;
  output [0:0]clk2_valid_pulse_reg_5;
  output [0:0]clk2_valid_pulse_reg_6;
  output [0:0]clk2_valid_pulse_reg_7;
  output [0:0]clk2_valid_pulse_reg_8;
  output [0:0]clk2_valid_pulse_reg_9;
  output [0:0]clk2_valid_pulse_reg_10;
  output [0:0]clk2_valid_pulse_reg_11;
  output [0:0]clk2_valid_pulse_reg_12;
  output [0:0]clk2_valid_pulse_reg_13;
  output [0:0]clk2_valid_pulse_reg_14;
  output \syncstages_ff_reg[4] ;
  input src_in;
  input s_axi_aclk;
  input p_0_in;
  input slv_access_valid_hold_reg;
  input [0:0]Q;
  input slv_rden_r_0;
  input slv_wren_done_pulse_1;
  input \adc20_ds_enable_0_reg[0] ;
  input \adc23_ds_type_0_reg[0] ;
  input \adc23_ds_enable_0_reg[0] ;
  input \adc21_ds_control_0_reg[0] ;
  input \adc21_ds_type_0_reg[0] ;
  input \adc21_ds_enable_0_reg[0] ;
  input \adc20_ds_type_0_reg[0] ;
  input \adc20_ds_control_0_reg[0] ;
  input \adc20_ds_inc_0_reg[0] ;
  input \adc23_ds_inc_0_reg[0] ;
  input \adc23_ds_control_0_reg[0] ;
  input \adc22_ds_type_0_reg[0] ;
  input \adc22_ds_inc_0_reg[0] ;
  input \adc22_ds_enable_0_reg[0] ;
  input \adc22_ds_control_0_reg[0] ;
  input \adc21_ds_inc_0_reg[0] ;
  input s_axi_wvalid;
  input adc2axi_map_wready;
  input adc2slv_rden;

  wire [0:0]E;
  wire [0:0]Q;
  wire \adc20_ds_control_0_reg[0] ;
  wire \adc20_ds_enable_0_reg[0] ;
  wire \adc20_ds_inc_0_reg[0] ;
  wire \adc20_ds_type_0_reg[0] ;
  wire \adc21_ds_control_0_reg[0] ;
  wire \adc21_ds_enable_0_reg[0] ;
  wire \adc21_ds_inc_0_reg[0] ;
  wire \adc21_ds_type_0_reg[0] ;
  wire \adc22_ds_control_0_reg[0] ;
  wire \adc22_ds_enable_0_reg[0] ;
  wire \adc22_ds_inc_0_reg[0] ;
  wire \adc22_ds_type_0_reg[0] ;
  wire \adc23_ds_control_0_reg[0] ;
  wire \adc23_ds_enable_0_reg[0] ;
  wire \adc23_ds_inc_0_reg[0] ;
  wire \adc23_ds_type_0_reg[0] ;
  wire adc2axi_map_wready;
  wire adc2slv_rden;
  wire axi_2_drp_valid_i_n_0;
  wire axi_2_drp_valid_i_n_2;
  wire clk1_ready_pulse0;
  wire clk1_ready_sync_r;
  wire clk2_ready;
  wire clk2_valid_pulse0;
  wire [0:0]clk2_valid_pulse_reg_0;
  wire [0:0]clk2_valid_pulse_reg_1;
  wire [0:0]clk2_valid_pulse_reg_10;
  wire [0:0]clk2_valid_pulse_reg_11;
  wire [0:0]clk2_valid_pulse_reg_12;
  wire [0:0]clk2_valid_pulse_reg_13;
  wire [0:0]clk2_valid_pulse_reg_14;
  wire [0:0]clk2_valid_pulse_reg_2;
  wire [0:0]clk2_valid_pulse_reg_3;
  wire [0:0]clk2_valid_pulse_reg_4;
  wire [0:0]clk2_valid_pulse_reg_5;
  wire [0:0]clk2_valid_pulse_reg_6;
  wire [0:0]clk2_valid_pulse_reg_7;
  wire [0:0]clk2_valid_pulse_reg_8;
  wire [0:0]clk2_valid_pulse_reg_9;
  wire clk2_valid_sync_r;
  wire p_0_in;
  wire s_axi_aclk;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire slv_rden_r_0;
  wire slv_rden_r_reg;
  wire slv_wren_clear;
  wire slv_wren_clk2;
  wire slv_wren_done_pulse;
  wire slv_wren_done_pulse_1;
  wire src_in;
  wire \syncstages_ff_reg[4] ;

  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc20_ds_control_0[1]_i_1 
       (.I0(\adc20_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_6));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc20_ds_enable_0[7]_i_1 
       (.I0(\adc20_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(E));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc20_ds_inc_0[11]_i_1 
       (.I0(\adc20_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_7));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc20_ds_type_0[3]_i_1 
       (.I0(\adc20_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_5));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc21_ds_control_0[1]_i_1 
       (.I0(\adc21_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_2));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc21_ds_enable_0[7]_i_1 
       (.I0(\adc21_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_4));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc21_ds_inc_0[11]_i_1 
       (.I0(\adc21_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_14));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc21_ds_type_0[3]_i_1 
       (.I0(\adc21_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_3));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc22_ds_control_0[1]_i_1 
       (.I0(\adc22_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_13));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc22_ds_enable_0[7]_i_1 
       (.I0(\adc22_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_12));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc22_ds_inc_0[11]_i_1 
       (.I0(\adc22_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_11));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc22_ds_type_0[3]_i_1 
       (.I0(\adc22_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_10));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc23_ds_control_0[1]_i_1 
       (.I0(\adc23_ds_control_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_9));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc23_ds_enable_0[7]_i_1 
       (.I0(\adc23_ds_enable_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_1));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc23_ds_inc_0[11]_i_1 
       (.I0(\adc23_ds_inc_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_8));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'h08)) 
    \adc23_ds_type_0[3]_i_1 
       (.I0(\adc23_ds_type_0_reg[0] ),
        .I1(slv_wren_clk2),
        .I2(slv_access_valid_hold_reg),
        .O(clk2_valid_pulse_reg_0));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__5 axi_2_drp_valid_i
       (.clk2_ready_reg(clk2_ready),
        .clk2_valid_pulse0(clk2_valid_pulse0),
        .clk2_valid_pulse_reg(axi_2_drp_valid_i_n_2),
        .clk2_valid_sync_r(clk2_valid_sync_r),
        .dest_out(axi_2_drp_valid_i_n_0),
        .s_axi_aclk(s_axi_aclk),
        .slv_wren_clk2(slv_wren_clk2),
        .src_in(src_in));
  LUT5 #(
    .INIT(32'h8F808080)) 
    \axi_rresp[1]_i_3 
       (.I0(slv_access_valid_hold_reg),
        .I1(slv_wren_done_pulse),
        .I2(Q),
        .I3(slv_rden_r_0),
        .I4(slv_wren_done_pulse_1),
        .O(slv_rden_r_reg));
  FDRE clk1_ready_pulse_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk1_ready_pulse0),
        .Q(slv_wren_done_pulse),
        .R(p_0_in));
  FDRE clk1_ready_sync_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(slv_wren_clear),
        .Q(clk1_ready_sync_r),
        .R(p_0_in));
  FDRE clk2_ready_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_2),
        .Q(clk2_ready),
        .R(p_0_in));
  FDRE clk2_valid_pulse_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(clk2_valid_pulse0),
        .Q(slv_wren_clk2),
        .R(p_0_in));
  FDRE clk2_valid_sync_r_reg
       (.C(s_axi_aclk),
        .CE(1'b1),
        .D(axi_2_drp_valid_i_n_0),
        .Q(clk2_valid_sync_r),
        .R(p_0_in));
  project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__6 drp_2_axi_in_progress_i
       (.adc2axi_map_wready(adc2axi_map_wready),
        .adc2slv_rden(adc2slv_rden),
        .clk1_ready_pulse0(clk1_ready_pulse0),
        .clk1_ready_sync_r(clk1_ready_sync_r),
        .dest_out(slv_wren_clear),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_wvalid(s_axi_wvalid),
        .slv_access_valid_hold_reg(slv_access_valid_hold_reg),
        .src_in(src_in),
        .\syncstages_ff_reg[0] (clk2_ready),
        .\syncstages_ff_reg[4] (\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync
   (dest_out,
    clk1_ready_pulse0,
    \syncstages_ff_reg[4] ,
    \syncstages_ff_reg[0] ,
    s_axi_aclk,
    clk1_ready_sync_r,
    s_axi_wvalid,
    adc3axi_map_wready,
    adc3slv_rden,
    slv_access_valid_hold_reg,
    src_in);
  output dest_out;
  output clk1_ready_pulse0;
  output \syncstages_ff_reg[4] ;
  input \syncstages_ff_reg[0] ;
  input s_axi_aclk;
  input clk1_ready_sync_r;
  input s_axi_wvalid;
  input adc3axi_map_wready;
  input adc3slv_rden;
  input slv_access_valid_hold_reg;
  input src_in;

  wire adc3axi_map_wready;
  wire adc3slv_rden;
  wire clk1_ready_pulse0;
  wire clk1_ready_sync_r;
  wire dest_out;
  wire s_axi_aclk;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire src_in;
  wire \syncstages_ff_reg[0] ;
  wire \syncstages_ff_reg[4] ;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single cdc_i
       (.dest_clk(s_axi_aclk),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(\syncstages_ff_reg[0] ));
  LUT2 #(
    .INIT(4'h2)) 
    clk1_ready_pulse_i_1__2
       (.I0(clk1_ready_sync_r),
        .I1(dest_out),
        .O(clk1_ready_pulse0));
  LUT6 #(
    .INIT(64'hD5D5FFD5C0C0FFC0)) 
    slv_access_valid_hold_i_1__2
       (.I0(dest_out),
        .I1(s_axi_wvalid),
        .I2(adc3axi_map_wready),
        .I3(adc3slv_rden),
        .I4(slv_access_valid_hold_reg),
        .I5(src_in),
        .O(\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__1
   (dest_out,
    clk2_valid_pulse0,
    clk2_valid_pulse_reg,
    src_in,
    s0_axis_clock,
    clk2_valid_sync_r,
    slv_wren_clk2,
    clk2_ready_reg);
  output dest_out;
  output clk2_valid_pulse0;
  output clk2_valid_pulse_reg;
  input src_in;
  input s0_axis_clock;
  input clk2_valid_sync_r;
  input slv_wren_clk2;
  input clk2_ready_reg;

  wire clk2_ready_reg;
  wire clk2_valid_pulse0;
  wire clk2_valid_pulse_reg;
  wire clk2_valid_sync_r;
  wire dest_out;
  wire s0_axis_clock;
  wire slv_wren_clk2;
  wire src_in;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__12 cdc_i
       (.dest_clk(s0_axis_clock),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(src_in));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'hEA)) 
    clk2_ready_i_1
       (.I0(slv_wren_clk2),
        .I1(dest_out),
        .I2(clk2_ready_reg),
        .O(clk2_valid_pulse_reg));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h2)) 
    clk2_valid_pulse_i_1
       (.I0(dest_out),
        .I1(clk2_valid_sync_r),
        .O(clk2_valid_pulse0));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__2
   (dest_out,
    clk1_ready_pulse0,
    \syncstages_ff_reg[4] ,
    \syncstages_ff_reg[0] ,
    s_axi_aclk,
    clk1_ready_sync_r,
    s_axi_wvalid,
    adc0axi_map_wready,
    adc0slv_rden,
    slv_access_valid_hold_reg,
    src_in);
  output dest_out;
  output clk1_ready_pulse0;
  output \syncstages_ff_reg[4] ;
  input \syncstages_ff_reg[0] ;
  input s_axi_aclk;
  input clk1_ready_sync_r;
  input s_axi_wvalid;
  input adc0axi_map_wready;
  input adc0slv_rden;
  input slv_access_valid_hold_reg;
  input src_in;

  wire adc0axi_map_wready;
  wire adc0slv_rden;
  wire clk1_ready_pulse0;
  wire clk1_ready_sync_r;
  wire dest_out;
  wire s_axi_aclk;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire src_in;
  wire \syncstages_ff_reg[0] ;
  wire \syncstages_ff_reg[4] ;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__13 cdc_i
       (.dest_clk(s_axi_aclk),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(\syncstages_ff_reg[0] ));
  LUT2 #(
    .INIT(4'h2)) 
    clk1_ready_pulse_i_1
       (.I0(clk1_ready_sync_r),
        .I1(dest_out),
        .O(clk1_ready_pulse0));
  LUT6 #(
    .INIT(64'hD5D5FFD5C0C0FFC0)) 
    slv_access_valid_hold_i_1
       (.I0(dest_out),
        .I1(s_axi_wvalid),
        .I2(adc0axi_map_wready),
        .I3(adc0slv_rden),
        .I4(slv_access_valid_hold_reg),
        .I5(src_in),
        .O(\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__3
   (dest_out,
    clk2_valid_pulse0,
    clk2_valid_pulse_reg,
    src_in,
    s_axi_aclk,
    clk2_valid_sync_r,
    slv_wren_clk2,
    clk2_ready_reg);
  output dest_out;
  output clk2_valid_pulse0;
  output clk2_valid_pulse_reg;
  input src_in;
  input s_axi_aclk;
  input clk2_valid_sync_r;
  input slv_wren_clk2;
  input clk2_ready_reg;

  wire clk2_ready_reg;
  wire clk2_valid_pulse0;
  wire clk2_valid_pulse_reg;
  wire clk2_valid_sync_r;
  wire dest_out;
  wire s_axi_aclk;
  wire slv_wren_clk2;
  wire src_in;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__14 cdc_i
       (.dest_clk(s_axi_aclk),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(src_in));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hEA)) 
    clk2_ready_i_1__0
       (.I0(slv_wren_clk2),
        .I1(dest_out),
        .I2(clk2_ready_reg),
        .O(clk2_valid_pulse_reg));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT2 #(
    .INIT(4'h2)) 
    clk2_valid_pulse_i_1__0
       (.I0(dest_out),
        .I1(clk2_valid_sync_r),
        .O(clk2_valid_pulse0));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__4
   (dest_out,
    clk1_ready_pulse0,
    \syncstages_ff_reg[4] ,
    \syncstages_ff_reg[0] ,
    s_axi_aclk,
    clk1_ready_sync_r,
    s_axi_wvalid,
    adc1axi_map_wready,
    adc1slv_rden,
    slv_access_valid_hold_reg,
    src_in);
  output dest_out;
  output clk1_ready_pulse0;
  output \syncstages_ff_reg[4] ;
  input \syncstages_ff_reg[0] ;
  input s_axi_aclk;
  input clk1_ready_sync_r;
  input s_axi_wvalid;
  input adc1axi_map_wready;
  input adc1slv_rden;
  input slv_access_valid_hold_reg;
  input src_in;

  wire adc1axi_map_wready;
  wire adc1slv_rden;
  wire clk1_ready_pulse0;
  wire clk1_ready_sync_r;
  wire dest_out;
  wire s_axi_aclk;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire src_in;
  wire \syncstages_ff_reg[0] ;
  wire \syncstages_ff_reg[4] ;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__15 cdc_i
       (.dest_clk(s_axi_aclk),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(\syncstages_ff_reg[0] ));
  LUT2 #(
    .INIT(4'h2)) 
    clk1_ready_pulse_i_1__0
       (.I0(clk1_ready_sync_r),
        .I1(dest_out),
        .O(clk1_ready_pulse0));
  LUT6 #(
    .INIT(64'hD5D5FFD5C0C0FFC0)) 
    slv_access_valid_hold_i_1__0
       (.I0(dest_out),
        .I1(s_axi_wvalid),
        .I2(adc1axi_map_wready),
        .I3(adc1slv_rden),
        .I4(slv_access_valid_hold_reg),
        .I5(src_in),
        .O(\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__5
   (dest_out,
    clk2_valid_pulse0,
    clk2_valid_pulse_reg,
    src_in,
    s_axi_aclk,
    clk2_valid_sync_r,
    slv_wren_clk2,
    clk2_ready_reg);
  output dest_out;
  output clk2_valid_pulse0;
  output clk2_valid_pulse_reg;
  input src_in;
  input s_axi_aclk;
  input clk2_valid_sync_r;
  input slv_wren_clk2;
  input clk2_ready_reg;

  wire clk2_ready_reg;
  wire clk2_valid_pulse0;
  wire clk2_valid_pulse_reg;
  wire clk2_valid_sync_r;
  wire dest_out;
  wire s_axi_aclk;
  wire slv_wren_clk2;
  wire src_in;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__16 cdc_i
       (.dest_clk(s_axi_aclk),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(src_in));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hEA)) 
    clk2_ready_i_1__1
       (.I0(slv_wren_clk2),
        .I1(dest_out),
        .I2(clk2_ready_reg),
        .O(clk2_valid_pulse_reg));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT2 #(
    .INIT(4'h2)) 
    clk2_valid_pulse_i_1__1
       (.I0(dest_out),
        .I1(clk2_valid_sync_r),
        .O(clk2_valid_pulse0));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__6
   (dest_out,
    clk1_ready_pulse0,
    \syncstages_ff_reg[4] ,
    \syncstages_ff_reg[0] ,
    s_axi_aclk,
    clk1_ready_sync_r,
    s_axi_wvalid,
    adc2axi_map_wready,
    adc2slv_rden,
    slv_access_valid_hold_reg,
    src_in);
  output dest_out;
  output clk1_ready_pulse0;
  output \syncstages_ff_reg[4] ;
  input \syncstages_ff_reg[0] ;
  input s_axi_aclk;
  input clk1_ready_sync_r;
  input s_axi_wvalid;
  input adc2axi_map_wready;
  input adc2slv_rden;
  input slv_access_valid_hold_reg;
  input src_in;

  wire adc2axi_map_wready;
  wire adc2slv_rden;
  wire clk1_ready_pulse0;
  wire clk1_ready_sync_r;
  wire dest_out;
  wire s_axi_aclk;
  wire s_axi_wvalid;
  wire slv_access_valid_hold_reg;
  wire src_in;
  wire \syncstages_ff_reg[0] ;
  wire \syncstages_ff_reg[4] ;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__17 cdc_i
       (.dest_clk(s_axi_aclk),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(\syncstages_ff_reg[0] ));
  LUT2 #(
    .INIT(4'h2)) 
    clk1_ready_pulse_i_1__1
       (.I0(clk1_ready_sync_r),
        .I1(dest_out),
        .O(clk1_ready_pulse0));
  LUT6 #(
    .INIT(64'hD5D5FFD5C0C0FFC0)) 
    slv_access_valid_hold_i_1__1
       (.I0(dest_out),
        .I1(s_axi_wvalid),
        .I2(adc2axi_map_wready),
        .I3(adc2slv_rden),
        .I4(slv_access_valid_hold_reg),
        .I5(src_in),
        .O(\syncstages_ff_reg[4] ));
endmodule

(* ORIG_REF_NAME = "rfadc_exdes_ctrl_sync" *) 
module project_1_adc_sink_i_0_rfadc_exdes_ctrl_sync__xdcDup__7
   (dest_out,
    clk2_valid_pulse0,
    clk2_valid_pulse_reg,
    src_in,
    s_axi_aclk,
    clk2_valid_sync_r,
    slv_wren_clk2,
    clk2_ready_reg);
  output dest_out;
  output clk2_valid_pulse0;
  output clk2_valid_pulse_reg;
  input src_in;
  input s_axi_aclk;
  input clk2_valid_sync_r;
  input slv_wren_clk2;
  input clk2_ready_reg;

  wire clk2_ready_reg;
  wire clk2_valid_pulse0;
  wire clk2_valid_pulse_reg;
  wire clk2_valid_sync_r;
  wire dest_out;
  wire s_axi_aclk;
  wire slv_wren_clk2;
  wire src_in;

  (* DEST_SYNC_FF = "5" *) 
  (* INIT_SYNC_FF = "0" *) 
  (* KEEP_HIERARCHY = "true" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* SRC_INPUT_REG = "0" *) 
  (* VERSION = "0" *) 
  (* XPM_CDC = "SINGLE" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_cdc_single__18 cdc_i
       (.dest_clk(s_axi_aclk),
        .dest_out(dest_out),
        .src_clk(1'b0),
        .src_in(src_in));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hEA)) 
    clk2_ready_i_1__2
       (.I0(slv_wren_clk2),
        .I1(dest_out),
        .I2(clk2_ready_reg),
        .O(clk2_valid_pulse_reg));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT2 #(
    .INIT(4'h2)) 
    clk2_valid_pulse_i_1__2
       (.I0(dest_out),
        .I1(clk2_valid_sync_r),
        .O(clk2_valid_pulse0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__10
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__11
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__12
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__13
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__14
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__15
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__16
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__17
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEST_SYNC_FF = "5" *) (* INIT_SYNC_FF = "0" *) (* ORIG_REF_NAME = "xpm_cdc_single" *) 
(* SIM_ASSERT_CHK = "0" *) (* SRC_INPUT_REG = "0" *) (* VERSION = "0" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) (* xpm_cdc = "SINGLE" *) 
module project_1_adc_sink_i_0_xpm_cdc_single__18
   (src_clk,
    src_in,
    dest_clk,
    dest_out);
  input src_clk;
  input src_in;
  input dest_clk;
  output dest_out;

  wire dest_clk;
  wire src_in;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SINGLE" *) wire [4:0]syncstages_ff;

  assign dest_out = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_in),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SINGLE" *) 
  FDRE \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* DEF_VAL = "1'b0" *) (* DEST_SYNC_FF = "5" *) (* INIT = "0" *) 
(* INIT_SYNC_FF = "1" *) (* ORIG_REF_NAME = "xpm_cdc_sync_rst" *) (* SIM_ASSERT_CHK = "0" *) 
(* VERSION = "0" *) (* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "true" *) 
(* xpm_cdc = "SYNC_RST" *) 
module project_1_adc_sink_i_0_xpm_cdc_sync_rst
   (src_rst,
    dest_clk,
    dest_rst);
  input src_rst;
  input dest_clk;
  output dest_rst;

  wire dest_clk;
  wire src_rst;
  (* RTL_KEEP = "true" *) (* async_reg = "true" *) (* xpm_cdc = "SYNC_RST" *) wire [4:0]syncstages_ff;

  assign dest_rst = syncstages_ff[4];
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SYNC_RST" *) 
  FDRE #(
    .INIT(1'b0)) 
    \syncstages_ff_reg[0] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(src_rst),
        .Q(syncstages_ff[0]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SYNC_RST" *) 
  FDRE #(
    .INIT(1'b0)) 
    \syncstages_ff_reg[1] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[0]),
        .Q(syncstages_ff[1]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SYNC_RST" *) 
  FDRE #(
    .INIT(1'b0)) 
    \syncstages_ff_reg[2] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[1]),
        .Q(syncstages_ff[2]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SYNC_RST" *) 
  FDRE #(
    .INIT(1'b0)) 
    \syncstages_ff_reg[3] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[2]),
        .Q(syncstages_ff[3]),
        .R(1'b0));
  (* ASYNC_REG *) 
  (* KEEP = "true" *) 
  (* XPM_CDC = "SYNC_RST" *) 
  FDRE #(
    .INIT(1'b0)) 
    \syncstages_ff_reg[4] 
       (.C(dest_clk),
        .CE(1'b1),
        .D(syncstages_ff[3]),
        .Q(syncstages_ff[4]),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "xpm_mem_ds_dataCap" *) 
module project_1_adc_sink_i_0_xpm_mem_ds_dataCap
   (s00_ds_status,
    s0_axis_clock,
    Q,
    adc00_ds_pulse_control_0,
    s00_tdata);
  output s00_ds_status;
  input s0_axis_clock;
  input [7:0]Q;
  input adc00_ds_pulse_control_0;
  input [127:0]s00_tdata;

  wire [7:0]Q;
  wire adc00_ds_pulse_control_0;
  wire [7:0]addra_reg;
  wire clear;
  wire [127:0]dina;
  wire [7:0]p_0_in__0;
  wire s00_ds_status;
  wire [127:0]s00_tdata;
  wire s0_axis_clock;
  wire wea0;
  wire wea_i_2_n_0;

  LUT1 #(
    .INIT(2'h1)) 
    \addra[0]_i_1 
       (.I0(addra_reg[0]),
        .O(p_0_in__0[0]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \addra[1]_i_1 
       (.I0(addra_reg[0]),
        .I1(addra_reg[1]),
        .O(p_0_in__0[1]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \addra[2]_i_1 
       (.I0(addra_reg[2]),
        .I1(addra_reg[1]),
        .I2(addra_reg[0]),
        .O(p_0_in__0[2]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \addra[3]_i_1 
       (.I0(addra_reg[3]),
        .I1(addra_reg[0]),
        .I2(addra_reg[1]),
        .I3(addra_reg[2]),
        .O(p_0_in__0[3]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \addra[4]_i_1 
       (.I0(addra_reg[4]),
        .I1(addra_reg[2]),
        .I2(addra_reg[1]),
        .I3(addra_reg[0]),
        .I4(addra_reg[3]),
        .O(p_0_in__0[4]));
  LUT6 #(
    .INIT(64'h6AAAAAAAAAAAAAAA)) 
    \addra[5]_i_1 
       (.I0(addra_reg[5]),
        .I1(addra_reg[3]),
        .I2(addra_reg[0]),
        .I3(addra_reg[1]),
        .I4(addra_reg[2]),
        .I5(addra_reg[4]),
        .O(p_0_in__0[5]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \addra[6]_i_1 
       (.I0(addra_reg[6]),
        .I1(wea_i_2_n_0),
        .O(p_0_in__0[6]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \addra[7]_i_1 
       (.I0(addra_reg[7]),
        .I1(wea_i_2_n_0),
        .I2(addra_reg[6]),
        .O(p_0_in__0[7]));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[0] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[0]),
        .Q(addra_reg[0]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[1] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[1]),
        .Q(addra_reg[1]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[2] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[2]),
        .Q(addra_reg[2]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[3] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[3]),
        .Q(addra_reg[3]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[4] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[4]),
        .Q(addra_reg[4]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[5] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[5]),
        .Q(addra_reg[5]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[6] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[6]),
        .Q(addra_reg[6]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \addra_reg[7] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(p_0_in__0[7]),
        .Q(addra_reg[7]),
        .R(clear));
  LUT1 #(
    .INIT(2'h1)) 
    \dina[127]_i_1 
       (.I0(s00_ds_status),
        .O(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[0] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[0]),
        .Q(dina[0]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[100] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[100]),
        .Q(dina[100]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[101] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[101]),
        .Q(dina[101]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[102] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[102]),
        .Q(dina[102]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[103] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[103]),
        .Q(dina[103]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[104] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[104]),
        .Q(dina[104]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[105] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[105]),
        .Q(dina[105]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[106] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[106]),
        .Q(dina[106]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[107] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[107]),
        .Q(dina[107]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[108] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[108]),
        .Q(dina[108]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[109] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[109]),
        .Q(dina[109]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[10] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[10]),
        .Q(dina[10]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[110] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[110]),
        .Q(dina[110]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[111] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[111]),
        .Q(dina[111]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[112] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[112]),
        .Q(dina[112]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[113] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[113]),
        .Q(dina[113]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[114] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[114]),
        .Q(dina[114]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[115] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[115]),
        .Q(dina[115]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[116] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[116]),
        .Q(dina[116]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[117] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[117]),
        .Q(dina[117]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[118] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[118]),
        .Q(dina[118]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[119] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[119]),
        .Q(dina[119]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[11] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[11]),
        .Q(dina[11]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[120] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[120]),
        .Q(dina[120]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[121] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[121]),
        .Q(dina[121]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[122] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[122]),
        .Q(dina[122]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[123] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[123]),
        .Q(dina[123]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[124] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[124]),
        .Q(dina[124]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[125] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[125]),
        .Q(dina[125]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[126] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[126]),
        .Q(dina[126]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[127] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[127]),
        .Q(dina[127]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[12] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[12]),
        .Q(dina[12]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[13] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[13]),
        .Q(dina[13]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[14] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[14]),
        .Q(dina[14]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[15] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[15]),
        .Q(dina[15]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[16] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[16]),
        .Q(dina[16]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[17] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[17]),
        .Q(dina[17]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[18] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[18]),
        .Q(dina[18]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[19] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[19]),
        .Q(dina[19]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[1] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[1]),
        .Q(dina[1]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[20] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[20]),
        .Q(dina[20]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[21] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[21]),
        .Q(dina[21]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[22] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[22]),
        .Q(dina[22]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[23] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[23]),
        .Q(dina[23]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[24] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[24]),
        .Q(dina[24]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[25] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[25]),
        .Q(dina[25]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[26] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[26]),
        .Q(dina[26]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[27] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[27]),
        .Q(dina[27]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[28] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[28]),
        .Q(dina[28]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[29] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[29]),
        .Q(dina[29]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[2] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[2]),
        .Q(dina[2]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[30] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[30]),
        .Q(dina[30]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[31] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[31]),
        .Q(dina[31]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[32] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[32]),
        .Q(dina[32]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[33] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[33]),
        .Q(dina[33]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[34] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[34]),
        .Q(dina[34]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[35] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[35]),
        .Q(dina[35]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[36] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[36]),
        .Q(dina[36]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[37] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[37]),
        .Q(dina[37]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[38] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[38]),
        .Q(dina[38]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[39] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[39]),
        .Q(dina[39]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[3] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[3]),
        .Q(dina[3]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[40] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[40]),
        .Q(dina[40]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[41] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[41]),
        .Q(dina[41]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[42] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[42]),
        .Q(dina[42]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[43] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[43]),
        .Q(dina[43]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[44] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[44]),
        .Q(dina[44]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[45] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[45]),
        .Q(dina[45]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[46] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[46]),
        .Q(dina[46]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[47] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[47]),
        .Q(dina[47]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[48] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[48]),
        .Q(dina[48]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[49] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[49]),
        .Q(dina[49]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[4] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[4]),
        .Q(dina[4]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[50] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[50]),
        .Q(dina[50]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[51] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[51]),
        .Q(dina[51]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[52] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[52]),
        .Q(dina[52]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[53] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[53]),
        .Q(dina[53]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[54] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[54]),
        .Q(dina[54]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[55] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[55]),
        .Q(dina[55]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[56] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[56]),
        .Q(dina[56]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[57] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[57]),
        .Q(dina[57]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[58] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[58]),
        .Q(dina[58]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[59] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[59]),
        .Q(dina[59]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[5] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[5]),
        .Q(dina[5]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[60] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[60]),
        .Q(dina[60]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[61] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[61]),
        .Q(dina[61]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[62] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[62]),
        .Q(dina[62]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[63] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[63]),
        .Q(dina[63]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[64] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[64]),
        .Q(dina[64]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[65] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[65]),
        .Q(dina[65]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[66] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[66]),
        .Q(dina[66]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[67] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[67]),
        .Q(dina[67]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[68] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[68]),
        .Q(dina[68]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[69] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[69]),
        .Q(dina[69]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[6] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[6]),
        .Q(dina[6]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[70] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[70]),
        .Q(dina[70]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[71] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[71]),
        .Q(dina[71]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[72] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[72]),
        .Q(dina[72]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[73] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[73]),
        .Q(dina[73]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[74] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[74]),
        .Q(dina[74]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[75] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[75]),
        .Q(dina[75]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[76] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[76]),
        .Q(dina[76]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[77] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[77]),
        .Q(dina[77]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[78] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[78]),
        .Q(dina[78]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[79] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[79]),
        .Q(dina[79]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[7] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[7]),
        .Q(dina[7]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[80] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[80]),
        .Q(dina[80]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[81] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[81]),
        .Q(dina[81]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[82] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[82]),
        .Q(dina[82]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[83] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[83]),
        .Q(dina[83]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[84] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[84]),
        .Q(dina[84]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[85] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[85]),
        .Q(dina[85]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[86] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[86]),
        .Q(dina[86]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[87] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[87]),
        .Q(dina[87]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[88] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[88]),
        .Q(dina[88]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[89] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[89]),
        .Q(dina[89]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[8] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[8]),
        .Q(dina[8]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[90] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[90]),
        .Q(dina[90]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[91] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[91]),
        .Q(dina[91]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[92] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[92]),
        .Q(dina[92]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[93] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[93]),
        .Q(dina[93]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[94] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[94]),
        .Q(dina[94]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[95] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[95]),
        .Q(dina[95]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[96] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[96]),
        .Q(dina[96]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[97] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[97]),
        .Q(dina[97]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[98] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[98]),
        .Q(dina[98]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[99] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[99]),
        .Q(dina[99]),
        .R(clear));
  FDRE #(
    .INIT(1'b0)) 
    \dina_reg[9] 
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(s00_tdata[9]),
        .Q(dina[9]),
        .R(clear));
  LUT5 #(
    .INIT(32'h7FFF7F00)) 
    wea_i_1
       (.I0(addra_reg[7]),
        .I1(wea_i_2_n_0),
        .I2(addra_reg[6]),
        .I3(s00_ds_status),
        .I4(adc00_ds_pulse_control_0),
        .O(wea0));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    wea_i_2
       (.I0(addra_reg[5]),
        .I1(addra_reg[3]),
        .I2(addra_reg[0]),
        .I3(addra_reg[1]),
        .I4(addra_reg[2]),
        .I5(addra_reg[4]),
        .O(wea_i_2_n_0));
  FDRE #(
    .INIT(1'b0)) 
    wea_reg
       (.C(s0_axis_clock),
        .CE(1'b1),
        .D(wea0),
        .Q(s00_ds_status),
        .R(1'b0));
  project_1_adc_sink_i_0_xpm_mem_ds_wrap2 xpm_mem_ds_wrap2_i
       (.Q(addra_reg),
        .\gen_wr_a.gen_word_narrow.mem_reg_1 (dina),
        .\gen_wr_a.gen_word_narrow.mem_reg_1_0 (Q),
        .s0_axis_clock(s0_axis_clock),
        .wea(s00_ds_status));
endmodule

(* ORIG_REF_NAME = "xpm_mem_ds_sdpram_wrap" *) 
module project_1_adc_sink_i_0_xpm_mem_ds_sdpram_wrap
   (s0_axis_clock,
    wea,
    Q,
    \gen_wr_a.gen_word_narrow.mem_reg_1 ,
    \gen_wr_a.gen_word_narrow.mem_reg_1_0 );
  input s0_axis_clock;
  input [0:0]wea;
  input [7:0]Q;
  input [127:0]\gen_wr_a.gen_word_narrow.mem_reg_1 ;
  input [7:0]\gen_wr_a.gen_word_narrow.mem_reg_1_0 ;

  wire [7:0]Q;
  wire [127:0]\gen_wr_a.gen_word_narrow.mem_reg_1 ;
  wire [7:0]\gen_wr_a.gen_word_narrow.mem_reg_1_0 ;
  wire s0_axis_clock;
  wire [0:0]wea;
  wire xpm_memory_sdpram_inst_n_0;
  wire xpm_memory_sdpram_inst_n_1;
  wire xpm_memory_sdpram_inst_n_10;
  wire xpm_memory_sdpram_inst_n_100;
  wire xpm_memory_sdpram_inst_n_101;
  wire xpm_memory_sdpram_inst_n_102;
  wire xpm_memory_sdpram_inst_n_103;
  wire xpm_memory_sdpram_inst_n_104;
  wire xpm_memory_sdpram_inst_n_105;
  wire xpm_memory_sdpram_inst_n_106;
  wire xpm_memory_sdpram_inst_n_107;
  wire xpm_memory_sdpram_inst_n_108;
  wire xpm_memory_sdpram_inst_n_109;
  wire xpm_memory_sdpram_inst_n_11;
  wire xpm_memory_sdpram_inst_n_110;
  wire xpm_memory_sdpram_inst_n_111;
  wire xpm_memory_sdpram_inst_n_112;
  wire xpm_memory_sdpram_inst_n_113;
  wire xpm_memory_sdpram_inst_n_114;
  wire xpm_memory_sdpram_inst_n_115;
  wire xpm_memory_sdpram_inst_n_116;
  wire xpm_memory_sdpram_inst_n_117;
  wire xpm_memory_sdpram_inst_n_118;
  wire xpm_memory_sdpram_inst_n_119;
  wire xpm_memory_sdpram_inst_n_12;
  wire xpm_memory_sdpram_inst_n_120;
  wire xpm_memory_sdpram_inst_n_121;
  wire xpm_memory_sdpram_inst_n_122;
  wire xpm_memory_sdpram_inst_n_123;
  wire xpm_memory_sdpram_inst_n_124;
  wire xpm_memory_sdpram_inst_n_125;
  wire xpm_memory_sdpram_inst_n_126;
  wire xpm_memory_sdpram_inst_n_127;
  wire xpm_memory_sdpram_inst_n_13;
  wire xpm_memory_sdpram_inst_n_14;
  wire xpm_memory_sdpram_inst_n_15;
  wire xpm_memory_sdpram_inst_n_16;
  wire xpm_memory_sdpram_inst_n_17;
  wire xpm_memory_sdpram_inst_n_18;
  wire xpm_memory_sdpram_inst_n_19;
  wire xpm_memory_sdpram_inst_n_2;
  wire xpm_memory_sdpram_inst_n_20;
  wire xpm_memory_sdpram_inst_n_21;
  wire xpm_memory_sdpram_inst_n_22;
  wire xpm_memory_sdpram_inst_n_23;
  wire xpm_memory_sdpram_inst_n_24;
  wire xpm_memory_sdpram_inst_n_25;
  wire xpm_memory_sdpram_inst_n_26;
  wire xpm_memory_sdpram_inst_n_27;
  wire xpm_memory_sdpram_inst_n_28;
  wire xpm_memory_sdpram_inst_n_29;
  wire xpm_memory_sdpram_inst_n_3;
  wire xpm_memory_sdpram_inst_n_30;
  wire xpm_memory_sdpram_inst_n_31;
  wire xpm_memory_sdpram_inst_n_32;
  wire xpm_memory_sdpram_inst_n_33;
  wire xpm_memory_sdpram_inst_n_34;
  wire xpm_memory_sdpram_inst_n_35;
  wire xpm_memory_sdpram_inst_n_36;
  wire xpm_memory_sdpram_inst_n_37;
  wire xpm_memory_sdpram_inst_n_38;
  wire xpm_memory_sdpram_inst_n_39;
  wire xpm_memory_sdpram_inst_n_4;
  wire xpm_memory_sdpram_inst_n_40;
  wire xpm_memory_sdpram_inst_n_41;
  wire xpm_memory_sdpram_inst_n_42;
  wire xpm_memory_sdpram_inst_n_43;
  wire xpm_memory_sdpram_inst_n_44;
  wire xpm_memory_sdpram_inst_n_45;
  wire xpm_memory_sdpram_inst_n_46;
  wire xpm_memory_sdpram_inst_n_47;
  wire xpm_memory_sdpram_inst_n_48;
  wire xpm_memory_sdpram_inst_n_49;
  wire xpm_memory_sdpram_inst_n_5;
  wire xpm_memory_sdpram_inst_n_50;
  wire xpm_memory_sdpram_inst_n_51;
  wire xpm_memory_sdpram_inst_n_52;
  wire xpm_memory_sdpram_inst_n_53;
  wire xpm_memory_sdpram_inst_n_54;
  wire xpm_memory_sdpram_inst_n_55;
  wire xpm_memory_sdpram_inst_n_56;
  wire xpm_memory_sdpram_inst_n_57;
  wire xpm_memory_sdpram_inst_n_58;
  wire xpm_memory_sdpram_inst_n_59;
  wire xpm_memory_sdpram_inst_n_6;
  wire xpm_memory_sdpram_inst_n_60;
  wire xpm_memory_sdpram_inst_n_61;
  wire xpm_memory_sdpram_inst_n_62;
  wire xpm_memory_sdpram_inst_n_63;
  wire xpm_memory_sdpram_inst_n_64;
  wire xpm_memory_sdpram_inst_n_65;
  wire xpm_memory_sdpram_inst_n_66;
  wire xpm_memory_sdpram_inst_n_67;
  wire xpm_memory_sdpram_inst_n_68;
  wire xpm_memory_sdpram_inst_n_69;
  wire xpm_memory_sdpram_inst_n_7;
  wire xpm_memory_sdpram_inst_n_70;
  wire xpm_memory_sdpram_inst_n_71;
  wire xpm_memory_sdpram_inst_n_72;
  wire xpm_memory_sdpram_inst_n_73;
  wire xpm_memory_sdpram_inst_n_74;
  wire xpm_memory_sdpram_inst_n_75;
  wire xpm_memory_sdpram_inst_n_76;
  wire xpm_memory_sdpram_inst_n_77;
  wire xpm_memory_sdpram_inst_n_78;
  wire xpm_memory_sdpram_inst_n_79;
  wire xpm_memory_sdpram_inst_n_8;
  wire xpm_memory_sdpram_inst_n_80;
  wire xpm_memory_sdpram_inst_n_81;
  wire xpm_memory_sdpram_inst_n_82;
  wire xpm_memory_sdpram_inst_n_83;
  wire xpm_memory_sdpram_inst_n_84;
  wire xpm_memory_sdpram_inst_n_85;
  wire xpm_memory_sdpram_inst_n_86;
  wire xpm_memory_sdpram_inst_n_87;
  wire xpm_memory_sdpram_inst_n_88;
  wire xpm_memory_sdpram_inst_n_89;
  wire xpm_memory_sdpram_inst_n_9;
  wire xpm_memory_sdpram_inst_n_90;
  wire xpm_memory_sdpram_inst_n_91;
  wire xpm_memory_sdpram_inst_n_92;
  wire xpm_memory_sdpram_inst_n_93;
  wire xpm_memory_sdpram_inst_n_94;
  wire xpm_memory_sdpram_inst_n_95;
  wire xpm_memory_sdpram_inst_n_96;
  wire xpm_memory_sdpram_inst_n_97;
  wire xpm_memory_sdpram_inst_n_98;
  wire xpm_memory_sdpram_inst_n_99;
  wire NLW_xpm_memory_sdpram_inst_dbiterrb_UNCONNECTED;
  wire NLW_xpm_memory_sdpram_inst_sbiterrb_UNCONNECTED;

  (* ADDR_WIDTH_A = "8" *) 
  (* ADDR_WIDTH_B = "8" *) 
  (* AUTO_SLEEP_TIME = "0" *) 
  (* BYTE_WRITE_WIDTH_A = "128" *) 
  (* CASCADE_HEIGHT = "0" *) 
  (* CLOCKING_MODE = "common_clock" *) 
  (* ECC_MODE = "no_ecc" *) 
  (* MEMORY_INIT_FILE = "none" *) 
  (* MEMORY_INIT_PARAM = "" *) 
  (* MEMORY_OPTIMIZATION = "true" *) 
  (* MEMORY_PRIMITIVE = "auto" *) 
  (* MEMORY_SIZE = "32768" *) 
  (* MESSAGE_CONTROL = "0" *) 
  (* P_CLOCKING_MODE = "0" *) 
  (* P_ECC_MODE = "0" *) 
  (* P_MEMORY_OPTIMIZATION = "1" *) 
  (* P_MEMORY_PRIMITIVE = "0" *) 
  (* P_WAKEUP_TIME = "0" *) 
  (* P_WRITE_MODE_B = "2" *) 
  (* READ_DATA_WIDTH_B = "128" *) 
  (* READ_LATENCY_B = "2" *) 
  (* READ_RESET_VALUE_B = "0" *) 
  (* RST_MODE_A = "SYNC" *) 
  (* RST_MODE_B = "SYNC" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* USE_EMBEDDED_CONSTRAINT = "0" *) 
  (* USE_MEM_INIT = "1" *) 
  (* USE_MEM_INIT_MMI = "0" *) 
  (* WAKEUP_TIME = "disable_sleep" *) 
  (* WRITE_DATA_WIDTH_A = "128" *) 
  (* WRITE_MODE_B = "no_change" *) 
  (* WRITE_PROTECT = "1" *) 
  (* XPM_MODULE = "TRUE" *) 
  project_1_adc_sink_i_0_xpm_memory_sdpram xpm_memory_sdpram_inst
       (.addra(Q),
        .addrb(\gen_wr_a.gen_word_narrow.mem_reg_1_0 ),
        .clka(s0_axis_clock),
        .clkb(s0_axis_clock),
        .dbiterrb(NLW_xpm_memory_sdpram_inst_dbiterrb_UNCONNECTED),
        .dina(\gen_wr_a.gen_word_narrow.mem_reg_1 ),
        .doutb({xpm_memory_sdpram_inst_n_0,xpm_memory_sdpram_inst_n_1,xpm_memory_sdpram_inst_n_2,xpm_memory_sdpram_inst_n_3,xpm_memory_sdpram_inst_n_4,xpm_memory_sdpram_inst_n_5,xpm_memory_sdpram_inst_n_6,xpm_memory_sdpram_inst_n_7,xpm_memory_sdpram_inst_n_8,xpm_memory_sdpram_inst_n_9,xpm_memory_sdpram_inst_n_10,xpm_memory_sdpram_inst_n_11,xpm_memory_sdpram_inst_n_12,xpm_memory_sdpram_inst_n_13,xpm_memory_sdpram_inst_n_14,xpm_memory_sdpram_inst_n_15,xpm_memory_sdpram_inst_n_16,xpm_memory_sdpram_inst_n_17,xpm_memory_sdpram_inst_n_18,xpm_memory_sdpram_inst_n_19,xpm_memory_sdpram_inst_n_20,xpm_memory_sdpram_inst_n_21,xpm_memory_sdpram_inst_n_22,xpm_memory_sdpram_inst_n_23,xpm_memory_sdpram_inst_n_24,xpm_memory_sdpram_inst_n_25,xpm_memory_sdpram_inst_n_26,xpm_memory_sdpram_inst_n_27,xpm_memory_sdpram_inst_n_28,xpm_memory_sdpram_inst_n_29,xpm_memory_sdpram_inst_n_30,xpm_memory_sdpram_inst_n_31,xpm_memory_sdpram_inst_n_32,xpm_memory_sdpram_inst_n_33,xpm_memory_sdpram_inst_n_34,xpm_memory_sdpram_inst_n_35,xpm_memory_sdpram_inst_n_36,xpm_memory_sdpram_inst_n_37,xpm_memory_sdpram_inst_n_38,xpm_memory_sdpram_inst_n_39,xpm_memory_sdpram_inst_n_40,xpm_memory_sdpram_inst_n_41,xpm_memory_sdpram_inst_n_42,xpm_memory_sdpram_inst_n_43,xpm_memory_sdpram_inst_n_44,xpm_memory_sdpram_inst_n_45,xpm_memory_sdpram_inst_n_46,xpm_memory_sdpram_inst_n_47,xpm_memory_sdpram_inst_n_48,xpm_memory_sdpram_inst_n_49,xpm_memory_sdpram_inst_n_50,xpm_memory_sdpram_inst_n_51,xpm_memory_sdpram_inst_n_52,xpm_memory_sdpram_inst_n_53,xpm_memory_sdpram_inst_n_54,xpm_memory_sdpram_inst_n_55,xpm_memory_sdpram_inst_n_56,xpm_memory_sdpram_inst_n_57,xpm_memory_sdpram_inst_n_58,xpm_memory_sdpram_inst_n_59,xpm_memory_sdpram_inst_n_60,xpm_memory_sdpram_inst_n_61,xpm_memory_sdpram_inst_n_62,xpm_memory_sdpram_inst_n_63,xpm_memory_sdpram_inst_n_64,xpm_memory_sdpram_inst_n_65,xpm_memory_sdpram_inst_n_66,xpm_memory_sdpram_inst_n_67,xpm_memory_sdpram_inst_n_68,xpm_memory_sdpram_inst_n_69,xpm_memory_sdpram_inst_n_70,xpm_memory_sdpram_inst_n_71,xpm_memory_sdpram_inst_n_72,xpm_memory_sdpram_inst_n_73,xpm_memory_sdpram_inst_n_74,xpm_memory_sdpram_inst_n_75,xpm_memory_sdpram_inst_n_76,xpm_memory_sdpram_inst_n_77,xpm_memory_sdpram_inst_n_78,xpm_memory_sdpram_inst_n_79,xpm_memory_sdpram_inst_n_80,xpm_memory_sdpram_inst_n_81,xpm_memory_sdpram_inst_n_82,xpm_memory_sdpram_inst_n_83,xpm_memory_sdpram_inst_n_84,xpm_memory_sdpram_inst_n_85,xpm_memory_sdpram_inst_n_86,xpm_memory_sdpram_inst_n_87,xpm_memory_sdpram_inst_n_88,xpm_memory_sdpram_inst_n_89,xpm_memory_sdpram_inst_n_90,xpm_memory_sdpram_inst_n_91,xpm_memory_sdpram_inst_n_92,xpm_memory_sdpram_inst_n_93,xpm_memory_sdpram_inst_n_94,xpm_memory_sdpram_inst_n_95,xpm_memory_sdpram_inst_n_96,xpm_memory_sdpram_inst_n_97,xpm_memory_sdpram_inst_n_98,xpm_memory_sdpram_inst_n_99,xpm_memory_sdpram_inst_n_100,xpm_memory_sdpram_inst_n_101,xpm_memory_sdpram_inst_n_102,xpm_memory_sdpram_inst_n_103,xpm_memory_sdpram_inst_n_104,xpm_memory_sdpram_inst_n_105,xpm_memory_sdpram_inst_n_106,xpm_memory_sdpram_inst_n_107,xpm_memory_sdpram_inst_n_108,xpm_memory_sdpram_inst_n_109,xpm_memory_sdpram_inst_n_110,xpm_memory_sdpram_inst_n_111,xpm_memory_sdpram_inst_n_112,xpm_memory_sdpram_inst_n_113,xpm_memory_sdpram_inst_n_114,xpm_memory_sdpram_inst_n_115,xpm_memory_sdpram_inst_n_116,xpm_memory_sdpram_inst_n_117,xpm_memory_sdpram_inst_n_118,xpm_memory_sdpram_inst_n_119,xpm_memory_sdpram_inst_n_120,xpm_memory_sdpram_inst_n_121,xpm_memory_sdpram_inst_n_122,xpm_memory_sdpram_inst_n_123,xpm_memory_sdpram_inst_n_124,xpm_memory_sdpram_inst_n_125,xpm_memory_sdpram_inst_n_126,xpm_memory_sdpram_inst_n_127}),
        .ena(1'b1),
        .enb(1'b1),
        .injectdbiterra(1'b0),
        .injectsbiterra(1'b0),
        .regceb(1'b1),
        .rstb(1'b0),
        .sbiterrb(NLW_xpm_memory_sdpram_inst_sbiterrb_UNCONNECTED),
        .sleep(1'b0),
        .wea(wea));
endmodule

(* ORIG_REF_NAME = "xpm_mem_ds_wrap2" *) 
module project_1_adc_sink_i_0_xpm_mem_ds_wrap2
   (s0_axis_clock,
    wea,
    Q,
    \gen_wr_a.gen_word_narrow.mem_reg_1 ,
    \gen_wr_a.gen_word_narrow.mem_reg_1_0 );
  input s0_axis_clock;
  input [0:0]wea;
  input [7:0]Q;
  input [127:0]\gen_wr_a.gen_word_narrow.mem_reg_1 ;
  input [7:0]\gen_wr_a.gen_word_narrow.mem_reg_1_0 ;

  wire [7:0]Q;
  wire [127:0]\gen_wr_a.gen_word_narrow.mem_reg_1 ;
  wire [7:0]\gen_wr_a.gen_word_narrow.mem_reg_1_0 ;
  wire s0_axis_clock;
  wire [0:0]wea;

  project_1_adc_sink_i_0_xpm_mem_ds_sdpram_wrap xpm_mem_ds_sdpram_wrap_i
       (.Q(Q),
        .\gen_wr_a.gen_word_narrow.mem_reg_1 (\gen_wr_a.gen_word_narrow.mem_reg_1 ),
        .\gen_wr_a.gen_word_narrow.mem_reg_1_0 (\gen_wr_a.gen_word_narrow.mem_reg_1_0 ),
        .s0_axis_clock(s0_axis_clock),
        .wea(wea));
endmodule

(* ADDR_WIDTH_A = "8" *) (* ADDR_WIDTH_B = "8" *) (* AUTO_SLEEP_TIME = "0" *) 
(* BYTE_WRITE_WIDTH_A = "128" *) (* BYTE_WRITE_WIDTH_B = "128" *) (* CASCADE_HEIGHT = "0" *) 
(* CLOCKING_MODE = "0" *) (* ECC_MODE = "0" *) (* MAX_NUM_CHAR = "0" *) 
(* MEMORY_INIT_FILE = "none" *) (* MEMORY_INIT_PARAM = "" *) (* MEMORY_OPTIMIZATION = "true" *) 
(* MEMORY_PRIMITIVE = "0" *) (* MEMORY_SIZE = "32768" *) (* MEMORY_TYPE = "1" *) 
(* MESSAGE_CONTROL = "0" *) (* NUM_CHAR_LOC = "0" *) (* ORIG_REF_NAME = "xpm_memory_base" *) 
(* P_ECC_MODE = "no_ecc" *) (* P_ENABLE_BYTE_WRITE_A = "0" *) (* P_ENABLE_BYTE_WRITE_B = "0" *) 
(* P_MAX_DEPTH_DATA = "256" *) (* P_MEMORY_OPT = "yes" *) (* P_MEMORY_PRIMITIVE = "auto" *) 
(* P_MIN_WIDTH_DATA = "128" *) (* P_MIN_WIDTH_DATA_A = "128" *) (* P_MIN_WIDTH_DATA_B = "128" *) 
(* P_MIN_WIDTH_DATA_ECC = "128" *) (* P_MIN_WIDTH_DATA_LDW = "4" *) (* P_MIN_WIDTH_DATA_SHFT = "128" *) 
(* P_NUM_COLS_WRITE_A = "1" *) (* P_NUM_COLS_WRITE_B = "1" *) (* P_NUM_ROWS_READ_A = "1" *) 
(* P_NUM_ROWS_READ_B = "1" *) (* P_NUM_ROWS_WRITE_A = "1" *) (* P_NUM_ROWS_WRITE_B = "1" *) 
(* P_SDP_WRITE_MODE = "yes" *) (* P_WIDTH_ADDR_LSB_READ_A = "0" *) (* P_WIDTH_ADDR_LSB_READ_B = "0" *) 
(* P_WIDTH_ADDR_LSB_WRITE_A = "0" *) (* P_WIDTH_ADDR_LSB_WRITE_B = "0" *) (* P_WIDTH_ADDR_READ_A = "8" *) 
(* P_WIDTH_ADDR_READ_B = "8" *) (* P_WIDTH_ADDR_WRITE_A = "8" *) (* P_WIDTH_ADDR_WRITE_B = "8" *) 
(* P_WIDTH_COL_WRITE_A = "128" *) (* P_WIDTH_COL_WRITE_B = "128" *) (* READ_DATA_WIDTH_A = "128" *) 
(* READ_DATA_WIDTH_B = "128" *) (* READ_LATENCY_A = "2" *) (* READ_LATENCY_B = "2" *) 
(* READ_RESET_VALUE_A = "0" *) (* READ_RESET_VALUE_B = "0" *) (* RST_MODE_A = "SYNC" *) 
(* RST_MODE_B = "SYNC" *) (* SIM_ASSERT_CHK = "0" *) (* USE_EMBEDDED_CONSTRAINT = "0" *) 
(* USE_MEM_INIT = "1" *) (* USE_MEM_INIT_MMI = "0" *) (* VERSION = "0" *) 
(* WAKEUP_TIME = "0" *) (* WRITE_DATA_WIDTH_A = "128" *) (* WRITE_DATA_WIDTH_B = "128" *) 
(* WRITE_MODE_A = "2" *) (* WRITE_MODE_B = "2" *) (* WRITE_PROTECT = "1" *) 
(* XPM_MODULE = "TRUE" *) (* keep_hierarchy = "soft" *) (* rsta_loop_iter = "128" *) 
(* rstb_loop_iter = "128" *) 
module project_1_adc_sink_i_0_xpm_memory_base
   (sleep,
    clka,
    rsta,
    ena,
    regcea,
    wea,
    addra,
    dina,
    injectsbiterra,
    injectdbiterra,
    douta,
    sbiterra,
    dbiterra,
    clkb,
    rstb,
    enb,
    regceb,
    web,
    addrb,
    dinb,
    injectsbiterrb,
    injectdbiterrb,
    doutb,
    sbiterrb,
    dbiterrb);
  input sleep;
  input clka;
  input rsta;
  input ena;
  input regcea;
  input [0:0]wea;
  input [7:0]addra;
  input [127:0]dina;
  input injectsbiterra;
  input injectdbiterra;
  output [127:0]douta;
  output sbiterra;
  output dbiterra;
  input clkb;
  input rstb;
  input enb;
  input regceb;
  input [0:0]web;
  input [7:0]addrb;
  input [127:0]dinb;
  input injectsbiterrb;
  input injectdbiterrb;
  output [127:0]doutb;
  output sbiterrb;
  output dbiterrb;

  wire \<const0> ;
  wire [7:0]addra;
  wire [7:0]addrb;
  wire clka;
  wire [127:0]dina;
  wire [127:0]doutb;
  wire enb;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_100 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_101 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_102 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_103 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_104 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_105 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_106 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_107 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_108 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_109 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_110 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_111 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_112 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_113 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_114 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_115 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_116 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_117 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_118 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_119 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_120 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_121 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_122 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_123 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_124 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_125 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_126 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_127 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_128 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_129 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_130 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_131 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_140 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_141 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_142 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_143 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_144 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_145 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_146 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_147 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_68 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_69 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_70 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_71 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_72 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_73 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_74 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_75 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_76 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_77 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_78 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_79 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_80 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_81 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_82 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_83 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_84 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_85 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_86 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_87 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_88 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_89 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_90 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_91 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_92 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_93 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_94 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_95 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_96 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_97 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_98 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_0_n_99 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_108 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_109 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_110 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_111 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_112 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_113 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_114 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_115 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_116 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_117 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_118 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_119 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_120 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_121 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_122 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_123 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_124 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_125 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_126 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_127 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_128 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_129 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_130 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_131 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_68 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_69 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_70 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_71 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_72 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_73 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_74 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_75 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_76 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_77 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_78 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_79 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_80 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_81 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_82 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_83 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_84 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_85 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_86 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_87 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_88 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_89 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_90 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_91 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_92 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_93 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_94 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_95 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_96 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_97 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_98 ;
  wire \gen_wr_a.gen_word_narrow.mem_reg_1_n_99 ;
  wire regceb;
  wire sleep;
  wire [0:0]wea;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTDBITERR_UNCONNECTED ;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTSBITERR_UNCONNECTED ;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_DBITERR_UNCONNECTED ;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_SBITERR_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINA_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINB_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPA_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPB_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTA_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTB_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPA_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPB_UNCONNECTED ;
  wire [7:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_ECCPARITY_UNCONNECTED ;
  wire [8:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_RDADDRECC_UNCONNECTED ;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTDBITERR_UNCONNECTED ;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTSBITERR_UNCONNECTED ;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DBITERR_UNCONNECTED ;
  wire \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_SBITERR_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINA_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINB_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPA_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPB_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTA_UNCONNECTED ;
  wire [31:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTB_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPA_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPB_UNCONNECTED ;
  wire [31:24]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTBDOUT_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPADOUTP_UNCONNECTED ;
  wire [3:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPBDOUTP_UNCONNECTED ;
  wire [7:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_ECCPARITY_UNCONNECTED ;
  wire [8:0]\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_RDADDRECC_UNCONNECTED ;

  assign dbiterra = \<const0> ;
  assign dbiterrb = \<const0> ;
  assign douta[127] = \<const0> ;
  assign douta[126] = \<const0> ;
  assign douta[125] = \<const0> ;
  assign douta[124] = \<const0> ;
  assign douta[123] = \<const0> ;
  assign douta[122] = \<const0> ;
  assign douta[121] = \<const0> ;
  assign douta[120] = \<const0> ;
  assign douta[119] = \<const0> ;
  assign douta[118] = \<const0> ;
  assign douta[117] = \<const0> ;
  assign douta[116] = \<const0> ;
  assign douta[115] = \<const0> ;
  assign douta[114] = \<const0> ;
  assign douta[113] = \<const0> ;
  assign douta[112] = \<const0> ;
  assign douta[111] = \<const0> ;
  assign douta[110] = \<const0> ;
  assign douta[109] = \<const0> ;
  assign douta[108] = \<const0> ;
  assign douta[107] = \<const0> ;
  assign douta[106] = \<const0> ;
  assign douta[105] = \<const0> ;
  assign douta[104] = \<const0> ;
  assign douta[103] = \<const0> ;
  assign douta[102] = \<const0> ;
  assign douta[101] = \<const0> ;
  assign douta[100] = \<const0> ;
  assign douta[99] = \<const0> ;
  assign douta[98] = \<const0> ;
  assign douta[97] = \<const0> ;
  assign douta[96] = \<const0> ;
  assign douta[95] = \<const0> ;
  assign douta[94] = \<const0> ;
  assign douta[93] = \<const0> ;
  assign douta[92] = \<const0> ;
  assign douta[91] = \<const0> ;
  assign douta[90] = \<const0> ;
  assign douta[89] = \<const0> ;
  assign douta[88] = \<const0> ;
  assign douta[87] = \<const0> ;
  assign douta[86] = \<const0> ;
  assign douta[85] = \<const0> ;
  assign douta[84] = \<const0> ;
  assign douta[83] = \<const0> ;
  assign douta[82] = \<const0> ;
  assign douta[81] = \<const0> ;
  assign douta[80] = \<const0> ;
  assign douta[79] = \<const0> ;
  assign douta[78] = \<const0> ;
  assign douta[77] = \<const0> ;
  assign douta[76] = \<const0> ;
  assign douta[75] = \<const0> ;
  assign douta[74] = \<const0> ;
  assign douta[73] = \<const0> ;
  assign douta[72] = \<const0> ;
  assign douta[71] = \<const0> ;
  assign douta[70] = \<const0> ;
  assign douta[69] = \<const0> ;
  assign douta[68] = \<const0> ;
  assign douta[67] = \<const0> ;
  assign douta[66] = \<const0> ;
  assign douta[65] = \<const0> ;
  assign douta[64] = \<const0> ;
  assign douta[63] = \<const0> ;
  assign douta[62] = \<const0> ;
  assign douta[61] = \<const0> ;
  assign douta[60] = \<const0> ;
  assign douta[59] = \<const0> ;
  assign douta[58] = \<const0> ;
  assign douta[57] = \<const0> ;
  assign douta[56] = \<const0> ;
  assign douta[55] = \<const0> ;
  assign douta[54] = \<const0> ;
  assign douta[53] = \<const0> ;
  assign douta[52] = \<const0> ;
  assign douta[51] = \<const0> ;
  assign douta[50] = \<const0> ;
  assign douta[49] = \<const0> ;
  assign douta[48] = \<const0> ;
  assign douta[47] = \<const0> ;
  assign douta[46] = \<const0> ;
  assign douta[45] = \<const0> ;
  assign douta[44] = \<const0> ;
  assign douta[43] = \<const0> ;
  assign douta[42] = \<const0> ;
  assign douta[41] = \<const0> ;
  assign douta[40] = \<const0> ;
  assign douta[39] = \<const0> ;
  assign douta[38] = \<const0> ;
  assign douta[37] = \<const0> ;
  assign douta[36] = \<const0> ;
  assign douta[35] = \<const0> ;
  assign douta[34] = \<const0> ;
  assign douta[33] = \<const0> ;
  assign douta[32] = \<const0> ;
  assign douta[31] = \<const0> ;
  assign douta[30] = \<const0> ;
  assign douta[29] = \<const0> ;
  assign douta[28] = \<const0> ;
  assign douta[27] = \<const0> ;
  assign douta[26] = \<const0> ;
  assign douta[25] = \<const0> ;
  assign douta[24] = \<const0> ;
  assign douta[23] = \<const0> ;
  assign douta[22] = \<const0> ;
  assign douta[21] = \<const0> ;
  assign douta[20] = \<const0> ;
  assign douta[19] = \<const0> ;
  assign douta[18] = \<const0> ;
  assign douta[17] = \<const0> ;
  assign douta[16] = \<const0> ;
  assign douta[15] = \<const0> ;
  assign douta[14] = \<const0> ;
  assign douta[13] = \<const0> ;
  assign douta[12] = \<const0> ;
  assign douta[11] = \<const0> ;
  assign douta[10] = \<const0> ;
  assign douta[9] = \<const0> ;
  assign douta[8] = \<const0> ;
  assign douta[7] = \<const0> ;
  assign douta[6] = \<const0> ;
  assign douta[5] = \<const0> ;
  assign douta[4] = \<const0> ;
  assign douta[3] = \<const0> ;
  assign douta[2] = \<const0> ;
  assign douta[1] = \<const0> ;
  assign douta[0] = \<const0> ;
  assign sbiterra = \<const0> ;
  assign sbiterrb = \<const0> ;
  GND GND
       (.G(\<const0> ));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][0] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_99 ),
        .Q(doutb[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][100] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_71 ),
        .Q(doutb[100]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][101] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_70 ),
        .Q(doutb[101]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][102] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_69 ),
        .Q(doutb[102]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][103] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_68 ),
        .Q(doutb[103]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][104] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_131 ),
        .Q(doutb[104]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][105] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_130 ),
        .Q(doutb[105]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][106] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_129 ),
        .Q(doutb[106]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][107] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_128 ),
        .Q(doutb[107]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][108] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_127 ),
        .Q(doutb[108]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][109] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_126 ),
        .Q(doutb[109]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][10] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_89 ),
        .Q(doutb[10]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][110] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_125 ),
        .Q(doutb[110]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][111] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_124 ),
        .Q(doutb[111]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][112] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_123 ),
        .Q(doutb[112]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][113] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_122 ),
        .Q(doutb[113]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][114] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_121 ),
        .Q(doutb[114]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][115] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_120 ),
        .Q(doutb[115]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][116] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_119 ),
        .Q(doutb[116]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][117] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_118 ),
        .Q(doutb[117]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][118] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_117 ),
        .Q(doutb[118]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][119] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_116 ),
        .Q(doutb[119]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][11] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_88 ),
        .Q(doutb[11]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][120] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_115 ),
        .Q(doutb[120]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][121] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_114 ),
        .Q(doutb[121]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][122] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_113 ),
        .Q(doutb[122]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][123] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_112 ),
        .Q(doutb[123]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][124] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_111 ),
        .Q(doutb[124]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][125] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_110 ),
        .Q(doutb[125]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][126] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_109 ),
        .Q(doutb[126]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][127] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_108 ),
        .Q(doutb[127]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][12] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_87 ),
        .Q(doutb[12]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][13] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_86 ),
        .Q(doutb[13]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][14] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_85 ),
        .Q(doutb[14]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][15] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_84 ),
        .Q(doutb[15]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][16] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_83 ),
        .Q(doutb[16]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][17] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_82 ),
        .Q(doutb[17]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][18] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_81 ),
        .Q(doutb[18]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][19] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_80 ),
        .Q(doutb[19]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][1] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_98 ),
        .Q(doutb[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][20] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_79 ),
        .Q(doutb[20]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][21] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_78 ),
        .Q(doutb[21]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][22] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_77 ),
        .Q(doutb[22]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][23] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_76 ),
        .Q(doutb[23]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][24] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_75 ),
        .Q(doutb[24]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][25] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_74 ),
        .Q(doutb[25]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][26] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_73 ),
        .Q(doutb[26]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][27] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_72 ),
        .Q(doutb[27]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][28] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_71 ),
        .Q(doutb[28]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][29] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_70 ),
        .Q(doutb[29]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][2] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_97 ),
        .Q(doutb[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][30] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_69 ),
        .Q(doutb[30]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][31] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_68 ),
        .Q(doutb[31]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][32] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_131 ),
        .Q(doutb[32]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][33] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_130 ),
        .Q(doutb[33]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][34] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_129 ),
        .Q(doutb[34]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][35] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_128 ),
        .Q(doutb[35]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][36] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_127 ),
        .Q(doutb[36]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][37] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_126 ),
        .Q(doutb[37]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][38] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_125 ),
        .Q(doutb[38]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][39] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_124 ),
        .Q(doutb[39]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][3] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_96 ),
        .Q(doutb[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][40] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_123 ),
        .Q(doutb[40]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][41] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_122 ),
        .Q(doutb[41]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][42] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_121 ),
        .Q(doutb[42]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][43] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_120 ),
        .Q(doutb[43]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][44] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_119 ),
        .Q(doutb[44]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][45] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_118 ),
        .Q(doutb[45]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][46] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_117 ),
        .Q(doutb[46]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][47] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_116 ),
        .Q(doutb[47]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][48] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_115 ),
        .Q(doutb[48]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][49] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_114 ),
        .Q(doutb[49]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][4] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_95 ),
        .Q(doutb[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][50] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_113 ),
        .Q(doutb[50]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][51] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_112 ),
        .Q(doutb[51]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][52] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_111 ),
        .Q(doutb[52]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][53] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_110 ),
        .Q(doutb[53]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][54] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_109 ),
        .Q(doutb[54]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][55] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_108 ),
        .Q(doutb[55]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][56] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_107 ),
        .Q(doutb[56]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][57] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_106 ),
        .Q(doutb[57]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][58] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_105 ),
        .Q(doutb[58]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][59] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_104 ),
        .Q(doutb[59]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][5] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_94 ),
        .Q(doutb[5]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][60] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_103 ),
        .Q(doutb[60]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][61] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_102 ),
        .Q(doutb[61]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][62] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_101 ),
        .Q(doutb[62]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][63] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_100 ),
        .Q(doutb[63]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][64] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_143 ),
        .Q(doutb[64]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][65] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_142 ),
        .Q(doutb[65]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][66] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_141 ),
        .Q(doutb[66]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][67] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_140 ),
        .Q(doutb[67]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][68] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_147 ),
        .Q(doutb[68]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][69] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_146 ),
        .Q(doutb[69]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][6] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_93 ),
        .Q(doutb[6]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][70] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_145 ),
        .Q(doutb[70]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][71] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_144 ),
        .Q(doutb[71]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][72] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_99 ),
        .Q(doutb[72]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][73] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_98 ),
        .Q(doutb[73]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][74] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_97 ),
        .Q(doutb[74]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][75] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_96 ),
        .Q(doutb[75]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][76] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_95 ),
        .Q(doutb[76]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][77] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_94 ),
        .Q(doutb[77]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][78] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_93 ),
        .Q(doutb[78]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][79] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_92 ),
        .Q(doutb[79]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][7] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_92 ),
        .Q(doutb[7]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][80] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_91 ),
        .Q(doutb[80]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][81] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_90 ),
        .Q(doutb[81]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][82] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_89 ),
        .Q(doutb[82]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][83] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_88 ),
        .Q(doutb[83]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][84] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_87 ),
        .Q(doutb[84]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][85] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_86 ),
        .Q(doutb[85]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][86] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_85 ),
        .Q(doutb[86]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][87] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_84 ),
        .Q(doutb[87]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][88] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_83 ),
        .Q(doutb[88]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][89] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_82 ),
        .Q(doutb[89]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][8] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_91 ),
        .Q(doutb[8]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][90] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_81 ),
        .Q(doutb[90]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][91] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_80 ),
        .Q(doutb[91]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][92] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_79 ),
        .Q(doutb[92]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][93] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_78 ),
        .Q(doutb[93]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][94] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_77 ),
        .Q(doutb[94]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][95] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_76 ),
        .Q(doutb[95]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][96] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_75 ),
        .Q(doutb[96]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][97] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_74 ),
        .Q(doutb[97]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][98] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_73 ),
        .Q(doutb[98]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][99] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_1_n_72 ),
        .Q(doutb[99]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][9] 
       (.C(clka),
        .CE(regceb),
        .D(\gen_wr_a.gen_word_narrow.mem_reg_0_n_90 ),
        .Q(doutb[9]),
        .R(1'b0));
  (* \MEM.PORTA.ADDRESS_BEGIN  = "0" *) 
  (* \MEM.PORTA.ADDRESS_END  = "511" *) 
  (* \MEM.PORTA.DATA_BIT_LAYOUT  = "p8_d64" *) 
  (* \MEM.PORTA.DATA_LSB  = "0" *) 
  (* \MEM.PORTA.DATA_MSB  = "71" *) 
  (* \MEM.PORTB.ADDRESS_BEGIN  = "0" *) 
  (* \MEM.PORTB.ADDRESS_END  = "511" *) 
  (* \MEM.PORTB.DATA_BIT_LAYOUT  = "p8_d64" *) 
  (* \MEM.PORTB.DATA_LSB  = "0" *) 
  (* \MEM.PORTB.DATA_MSB  = "71" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-6 {cell *THIS*}}" *) 
  (* RDADDR_COLLISION_HWCONFIG = "DELAYED_WRITE" *) 
  (* RTL_RAM_BITS = "32768" *) 
  (* RTL_RAM_NAME = "gen_wr_a.gen_word_narrow.mem" *) 
  (* RTL_RAM_TYPE = "RAM_SDP" *) 
  (* bram_addr_begin = "0" *) 
  (* bram_addr_end = "511" *) 
  (* bram_slice_begin = "0" *) 
  (* bram_slice_end = "71" *) 
  (* ram_addr_begin = "0" *) 
  (* ram_addr_end = "511" *) 
  (* ram_offset = "0" *) 
  (* ram_slice_begin = "0" *) 
  (* ram_slice_end = "71" *) 
  RAMB36E2 #(
    .CASCADE_ORDER_A("NONE"),
    .CASCADE_ORDER_B("NONE"),
    .CLOCK_DOMAINS("COMMON"),
    .DOA_REG(0),
    .DOB_REG(0),
    .ENADDRENA("FALSE"),
    .ENADDRENB("FALSE"),
    .EN_ECC_PIPE("FALSE"),
    .EN_ECC_READ("FALSE"),
    .EN_ECC_WRITE("FALSE"),
    .INITP_00(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_01(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_02(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_03(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_04(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_05(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_06(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_07(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_08(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_09(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_00(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_01(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_02(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_03(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_04(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_05(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_06(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_07(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_08(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_09(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_10(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_11(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_12(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_13(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_14(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_15(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_16(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_17(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_18(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_19(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_20(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_21(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_22(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_23(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_24(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_25(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_26(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_27(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_28(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_29(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_30(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_31(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_32(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_33(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_34(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_35(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_36(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_37(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_38(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_39(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_40(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_41(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_42(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_43(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_44(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_45(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_46(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_47(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_48(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_49(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_50(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_51(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_52(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_53(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_54(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_55(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_56(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_57(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_58(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_59(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_60(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_61(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_62(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_63(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_64(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_65(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_66(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_67(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_68(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_69(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_70(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_71(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_72(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_73(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_74(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_75(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_76(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_77(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_78(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_79(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_A(36'h000000000),
    .INIT_B(36'h000000000),
    .INIT_FILE("NONE"),
    .RDADDRCHANGEA("FALSE"),
    .RDADDRCHANGEB("FALSE"),
    .READ_WIDTH_A(72),
    .READ_WIDTH_B(0),
    .RSTREG_PRIORITY_A("RSTREG"),
    .RSTREG_PRIORITY_B("RSTREG"),
    .SIM_COLLISION_CHECK("ALL"),
    .SLEEP_ASYNC("FALSE"),
    .SRVAL_A(36'h000000000),
    .SRVAL_B(36'h000000000),
    .WRITE_MODE_A("READ_FIRST"),
    .WRITE_MODE_B("READ_FIRST"),
    .WRITE_WIDTH_A(0),
    .WRITE_WIDTH_B(72)) 
    \gen_wr_a.gen_word_narrow.mem_reg_0 
       (.ADDRARDADDR({1'b0,addrb,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1}),
        .ADDRBWRADDR({1'b0,addra,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1}),
        .ADDRENA(1'b0),
        .ADDRENB(1'b0),
        .CASDIMUXA(1'b0),
        .CASDIMUXB(1'b0),
        .CASDINA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINA_UNCONNECTED [31:0]),
        .CASDINB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINB_UNCONNECTED [31:0]),
        .CASDINPA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPA_UNCONNECTED [3:0]),
        .CASDINPB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPB_UNCONNECTED [3:0]),
        .CASDOMUXA(1'b0),
        .CASDOMUXB(1'b0),
        .CASDOMUXEN_A(1'b1),
        .CASDOMUXEN_B(1'b1),
        .CASDOUTA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTA_UNCONNECTED [31:0]),
        .CASDOUTB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTB_UNCONNECTED [31:0]),
        .CASDOUTPA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPA_UNCONNECTED [3:0]),
        .CASDOUTPB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPB_UNCONNECTED [3:0]),
        .CASINDBITERR(1'b0),
        .CASINSBITERR(1'b0),
        .CASOREGIMUXA(1'b0),
        .CASOREGIMUXB(1'b0),
        .CASOREGIMUXEN_A(1'b1),
        .CASOREGIMUXEN_B(1'b1),
        .CASOUTDBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTDBITERR_UNCONNECTED ),
        .CASOUTSBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTSBITERR_UNCONNECTED ),
        .CLKARDCLK(clka),
        .CLKBWRCLK(clka),
        .DBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_DBITERR_UNCONNECTED ),
        .DINADIN(dina[31:0]),
        .DINBDIN(dina[63:32]),
        .DINPADINP(dina[67:64]),
        .DINPBDINP(dina[71:68]),
        .DOUTADOUT({\gen_wr_a.gen_word_narrow.mem_reg_0_n_68 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_69 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_70 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_71 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_72 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_73 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_74 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_75 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_76 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_77 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_78 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_79 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_80 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_81 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_82 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_83 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_84 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_85 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_86 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_87 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_88 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_89 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_90 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_91 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_92 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_93 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_94 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_95 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_96 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_97 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_98 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_99 }),
        .DOUTBDOUT({\gen_wr_a.gen_word_narrow.mem_reg_0_n_100 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_101 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_102 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_103 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_104 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_105 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_106 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_107 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_108 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_109 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_110 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_111 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_112 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_113 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_114 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_115 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_116 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_117 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_118 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_119 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_120 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_121 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_122 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_123 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_124 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_125 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_126 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_127 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_128 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_129 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_130 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_131 }),
        .DOUTPADOUTP({\gen_wr_a.gen_word_narrow.mem_reg_0_n_140 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_141 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_142 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_143 }),
        .DOUTPBDOUTP({\gen_wr_a.gen_word_narrow.mem_reg_0_n_144 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_145 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_146 ,\gen_wr_a.gen_word_narrow.mem_reg_0_n_147 }),
        .ECCPARITY(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_ECCPARITY_UNCONNECTED [7:0]),
        .ECCPIPECE(1'b1),
        .ENARDEN(enb),
        .ENBWREN(1'b1),
        .INJECTDBITERR(1'b0),
        .INJECTSBITERR(1'b0),
        .RDADDRECC(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_RDADDRECC_UNCONNECTED [8:0]),
        .REGCEAREGCE(1'b1),
        .REGCEB(1'b1),
        .RSTRAMARSTRAM(1'b0),
        .RSTRAMB(1'b0),
        .RSTREGARSTREG(1'b0),
        .RSTREGB(1'b0),
        .SBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_0_SBITERR_UNCONNECTED ),
        .SLEEP(1'b0),
        .WEA({1'b0,1'b0,1'b0,1'b0}),
        .WEBWE({wea,wea,wea,wea,wea,wea,wea,wea}));
  (* \MEM.PORTA.ADDRESS_BEGIN  = "0" *) 
  (* \MEM.PORTA.ADDRESS_END  = "511" *) 
  (* \MEM.PORTA.DATA_BIT_LAYOUT  = "p0_d56" *) 
  (* \MEM.PORTA.DATA_LSB  = "72" *) 
  (* \MEM.PORTA.DATA_MSB  = "127" *) 
  (* \MEM.PORTB.ADDRESS_BEGIN  = "0" *) 
  (* \MEM.PORTB.ADDRESS_END  = "511" *) 
  (* \MEM.PORTB.DATA_BIT_LAYOUT  = "p0_d56" *) 
  (* \MEM.PORTB.DATA_LSB  = "72" *) 
  (* \MEM.PORTB.DATA_MSB  = "127" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-6 {cell *THIS*}}" *) 
  (* RDADDR_COLLISION_HWCONFIG = "DELAYED_WRITE" *) 
  (* RTL_RAM_BITS = "32768" *) 
  (* RTL_RAM_NAME = "gen_wr_a.gen_word_narrow.mem" *) 
  (* RTL_RAM_TYPE = "RAM_SDP" *) 
  (* bram_addr_begin = "0" *) 
  (* bram_addr_end = "511" *) 
  (* bram_slice_begin = "72" *) 
  (* bram_slice_end = "127" *) 
  (* ram_addr_begin = "0" *) 
  (* ram_addr_end = "511" *) 
  (* ram_offset = "0" *) 
  (* ram_slice_begin = "72" *) 
  (* ram_slice_end = "127" *) 
  RAMB36E2 #(
    .CASCADE_ORDER_A("NONE"),
    .CASCADE_ORDER_B("NONE"),
    .CLOCK_DOMAINS("COMMON"),
    .DOA_REG(0),
    .DOB_REG(0),
    .ENADDRENA("FALSE"),
    .ENADDRENB("FALSE"),
    .EN_ECC_PIPE("FALSE"),
    .EN_ECC_READ("FALSE"),
    .EN_ECC_WRITE("FALSE"),
    .INITP_00(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_01(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_02(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_03(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_04(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_05(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_06(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_07(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_08(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_09(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INITP_0F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_00(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_01(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_02(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_03(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_04(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_05(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_06(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_07(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_08(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_09(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_0F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_10(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_11(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_12(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_13(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_14(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_15(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_16(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_17(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_18(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_19(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_1F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_20(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_21(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_22(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_23(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_24(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_25(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_26(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_27(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_28(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_29(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_2F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_30(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_31(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_32(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_33(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_34(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_35(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_36(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_37(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_38(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_39(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_3F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_40(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_41(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_42(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_43(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_44(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_45(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_46(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_47(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_48(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_49(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_4F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_50(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_51(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_52(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_53(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_54(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_55(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_56(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_57(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_58(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_59(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_5F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_60(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_61(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_62(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_63(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_64(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_65(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_66(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_67(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_68(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_69(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_6F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_70(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_71(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_72(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_73(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_74(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_75(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_76(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_77(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_78(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_79(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7A(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7B(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7C(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7D(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7E(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_7F(256'h0000000000000000000000000000000000000000000000000000000000000000),
    .INIT_A(36'h000000000),
    .INIT_B(36'h000000000),
    .INIT_FILE("NONE"),
    .RDADDRCHANGEA("FALSE"),
    .RDADDRCHANGEB("FALSE"),
    .READ_WIDTH_A(72),
    .READ_WIDTH_B(0),
    .RSTREG_PRIORITY_A("RSTREG"),
    .RSTREG_PRIORITY_B("RSTREG"),
    .SIM_COLLISION_CHECK("ALL"),
    .SLEEP_ASYNC("FALSE"),
    .SRVAL_A(36'h000000000),
    .SRVAL_B(36'h000000000),
    .WRITE_MODE_A("READ_FIRST"),
    .WRITE_MODE_B("READ_FIRST"),
    .WRITE_WIDTH_A(0),
    .WRITE_WIDTH_B(72)) 
    \gen_wr_a.gen_word_narrow.mem_reg_1 
       (.ADDRARDADDR({1'b0,addrb,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1}),
        .ADDRBWRADDR({1'b0,addra,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1}),
        .ADDRENA(1'b0),
        .ADDRENB(1'b0),
        .CASDIMUXA(1'b0),
        .CASDIMUXB(1'b0),
        .CASDINA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINA_UNCONNECTED [31:0]),
        .CASDINB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINB_UNCONNECTED [31:0]),
        .CASDINPA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPA_UNCONNECTED [3:0]),
        .CASDINPB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPB_UNCONNECTED [3:0]),
        .CASDOMUXA(1'b0),
        .CASDOMUXB(1'b0),
        .CASDOMUXEN_A(1'b1),
        .CASDOMUXEN_B(1'b1),
        .CASDOUTA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTA_UNCONNECTED [31:0]),
        .CASDOUTB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTB_UNCONNECTED [31:0]),
        .CASDOUTPA(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPA_UNCONNECTED [3:0]),
        .CASDOUTPB(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPB_UNCONNECTED [3:0]),
        .CASINDBITERR(1'b0),
        .CASINSBITERR(1'b0),
        .CASOREGIMUXA(1'b0),
        .CASOREGIMUXB(1'b0),
        .CASOREGIMUXEN_A(1'b1),
        .CASOREGIMUXEN_B(1'b1),
        .CASOUTDBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTDBITERR_UNCONNECTED ),
        .CASOUTSBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTSBITERR_UNCONNECTED ),
        .CLKARDCLK(clka),
        .CLKBWRCLK(clka),
        .DBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DBITERR_UNCONNECTED ),
        .DINADIN(dina[103:72]),
        .DINBDIN({1'b1,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1,1'b1,dina[127:104]}),
        .DINPADINP({1'b1,1'b1,1'b1,1'b1}),
        .DINPBDINP({1'b1,1'b1,1'b1,1'b1}),
        .DOUTADOUT({\gen_wr_a.gen_word_narrow.mem_reg_1_n_68 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_69 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_70 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_71 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_72 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_73 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_74 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_75 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_76 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_77 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_78 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_79 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_80 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_81 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_82 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_83 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_84 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_85 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_86 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_87 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_88 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_89 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_90 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_91 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_92 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_93 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_94 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_95 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_96 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_97 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_98 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_99 }),
        .DOUTBDOUT({\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTBDOUT_UNCONNECTED [31:24],\gen_wr_a.gen_word_narrow.mem_reg_1_n_108 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_109 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_110 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_111 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_112 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_113 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_114 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_115 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_116 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_117 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_118 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_119 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_120 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_121 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_122 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_123 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_124 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_125 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_126 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_127 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_128 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_129 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_130 ,\gen_wr_a.gen_word_narrow.mem_reg_1_n_131 }),
        .DOUTPADOUTP(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPADOUTP_UNCONNECTED [3:0]),
        .DOUTPBDOUTP(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPBDOUTP_UNCONNECTED [3:0]),
        .ECCPARITY(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_ECCPARITY_UNCONNECTED [7:0]),
        .ECCPIPECE(1'b1),
        .ENARDEN(enb),
        .ENBWREN(1'b1),
        .INJECTDBITERR(1'b0),
        .INJECTSBITERR(1'b0),
        .RDADDRECC(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_RDADDRECC_UNCONNECTED [8:0]),
        .REGCEAREGCE(1'b1),
        .REGCEB(1'b1),
        .RSTRAMARSTRAM(1'b0),
        .RSTRAMB(1'b0),
        .RSTREGARSTREG(1'b0),
        .RSTREGB(1'b0),
        .SBITERR(\NLW_gen_wr_a.gen_word_narrow.mem_reg_1_SBITERR_UNCONNECTED ),
        .SLEEP(1'b0),
        .WEA({1'b0,1'b0,1'b0,1'b0}),
        .WEBWE({wea,wea,wea,wea,wea,wea,wea,wea}));
endmodule

(* ADDR_WIDTH_A = "8" *) (* ADDR_WIDTH_B = "8" *) (* AUTO_SLEEP_TIME = "0" *) 
(* BYTE_WRITE_WIDTH_A = "128" *) (* CASCADE_HEIGHT = "0" *) (* CLOCKING_MODE = "common_clock" *) 
(* ECC_MODE = "no_ecc" *) (* MEMORY_INIT_FILE = "none" *) (* MEMORY_INIT_PARAM = "" *) 
(* MEMORY_OPTIMIZATION = "true" *) (* MEMORY_PRIMITIVE = "auto" *) (* MEMORY_SIZE = "32768" *) 
(* MESSAGE_CONTROL = "0" *) (* ORIG_REF_NAME = "xpm_memory_sdpram" *) (* P_CLOCKING_MODE = "0" *) 
(* P_ECC_MODE = "0" *) (* P_MEMORY_OPTIMIZATION = "1" *) (* P_MEMORY_PRIMITIVE = "0" *) 
(* P_WAKEUP_TIME = "0" *) (* P_WRITE_MODE_B = "2" *) (* READ_DATA_WIDTH_B = "128" *) 
(* READ_LATENCY_B = "2" *) (* READ_RESET_VALUE_B = "0" *) (* RST_MODE_A = "SYNC" *) 
(* RST_MODE_B = "SYNC" *) (* SIM_ASSERT_CHK = "0" *) (* USE_EMBEDDED_CONSTRAINT = "0" *) 
(* USE_MEM_INIT = "1" *) (* USE_MEM_INIT_MMI = "0" *) (* WAKEUP_TIME = "disable_sleep" *) 
(* WRITE_DATA_WIDTH_A = "128" *) (* WRITE_MODE_B = "no_change" *) (* WRITE_PROTECT = "1" *) 
(* XPM_MODULE = "TRUE" *) 
module project_1_adc_sink_i_0_xpm_memory_sdpram
   (sleep,
    clka,
    ena,
    wea,
    addra,
    dina,
    injectsbiterra,
    injectdbiterra,
    clkb,
    rstb,
    enb,
    regceb,
    addrb,
    doutb,
    sbiterrb,
    dbiterrb);
  input sleep;
  input clka;
  input ena;
  input [0:0]wea;
  input [7:0]addra;
  input [127:0]dina;
  input injectsbiterra;
  input injectdbiterra;
  input clkb;
  input rstb;
  input enb;
  input regceb;
  input [7:0]addrb;
  output [127:0]doutb;
  output sbiterrb;
  output dbiterrb;

  wire \<const0> ;
  wire [7:0]addra;
  wire [7:0]addrb;
  wire clka;
  wire [127:0]dina;
  wire [127:0]doutb;
  wire enb;
  wire regceb;
  wire sleep;
  wire [0:0]wea;
  wire NLW_xpm_memory_base_inst_dbiterra_UNCONNECTED;
  wire NLW_xpm_memory_base_inst_dbiterrb_UNCONNECTED;
  wire NLW_xpm_memory_base_inst_sbiterra_UNCONNECTED;
  wire NLW_xpm_memory_base_inst_sbiterrb_UNCONNECTED;
  wire [127:0]NLW_xpm_memory_base_inst_douta_UNCONNECTED;

  assign dbiterrb = \<const0> ;
  assign sbiterrb = \<const0> ;
  GND GND
       (.G(\<const0> ));
  (* ADDR_WIDTH_A = "8" *) 
  (* ADDR_WIDTH_B = "8" *) 
  (* AUTO_SLEEP_TIME = "0" *) 
  (* BYTE_WRITE_WIDTH_A = "128" *) 
  (* BYTE_WRITE_WIDTH_B = "128" *) 
  (* CASCADE_HEIGHT = "0" *) 
  (* CLOCKING_MODE = "0" *) 
  (* ECC_MODE = "0" *) 
  (* KEEP_HIERARCHY = "soft" *) 
  (* MAX_NUM_CHAR = "0" *) 
  (* \MEM.ADDRESS_SPACE  *) 
  (* \MEM.ADDRESS_SPACE_BEGIN  = "0" *) 
  (* \MEM.ADDRESS_SPACE_DATA_LSB  = "0" *) 
  (* \MEM.ADDRESS_SPACE_DATA_MSB  = "127" *) 
  (* \MEM.ADDRESS_SPACE_END  = "511" *) 
  (* \MEM.CORE_MEMORY_WIDTH  = "128" *) 
  (* MEMORY_INIT_FILE = "none" *) 
  (* MEMORY_INIT_PARAM = "" *) 
  (* MEMORY_OPTIMIZATION = "true" *) 
  (* MEMORY_PRIMITIVE = "0" *) 
  (* MEMORY_SIZE = "32768" *) 
  (* MEMORY_TYPE = "1" *) 
  (* MESSAGE_CONTROL = "0" *) 
  (* NUM_CHAR_LOC = "0" *) 
  (* P_ECC_MODE = "no_ecc" *) 
  (* P_ENABLE_BYTE_WRITE_A = "0" *) 
  (* P_ENABLE_BYTE_WRITE_B = "0" *) 
  (* P_MAX_DEPTH_DATA = "256" *) 
  (* P_MEMORY_OPT = "yes" *) 
  (* P_MEMORY_PRIMITIVE = "auto" *) 
  (* P_MIN_WIDTH_DATA = "128" *) 
  (* P_MIN_WIDTH_DATA_A = "128" *) 
  (* P_MIN_WIDTH_DATA_B = "128" *) 
  (* P_MIN_WIDTH_DATA_ECC = "128" *) 
  (* P_MIN_WIDTH_DATA_LDW = "4" *) 
  (* P_MIN_WIDTH_DATA_SHFT = "128" *) 
  (* P_NUM_COLS_WRITE_A = "1" *) 
  (* P_NUM_COLS_WRITE_B = "1" *) 
  (* P_NUM_ROWS_READ_A = "1" *) 
  (* P_NUM_ROWS_READ_B = "1" *) 
  (* P_NUM_ROWS_WRITE_A = "1" *) 
  (* P_NUM_ROWS_WRITE_B = "1" *) 
  (* P_SDP_WRITE_MODE = "yes" *) 
  (* P_WIDTH_ADDR_LSB_READ_A = "0" *) 
  (* P_WIDTH_ADDR_LSB_READ_B = "0" *) 
  (* P_WIDTH_ADDR_LSB_WRITE_A = "0" *) 
  (* P_WIDTH_ADDR_LSB_WRITE_B = "0" *) 
  (* P_WIDTH_ADDR_READ_A = "8" *) 
  (* P_WIDTH_ADDR_READ_B = "8" *) 
  (* P_WIDTH_ADDR_WRITE_A = "8" *) 
  (* P_WIDTH_ADDR_WRITE_B = "8" *) 
  (* P_WIDTH_COL_WRITE_A = "128" *) 
  (* P_WIDTH_COL_WRITE_B = "128" *) 
  (* READ_DATA_WIDTH_A = "128" *) 
  (* READ_DATA_WIDTH_B = "128" *) 
  (* READ_LATENCY_A = "2" *) 
  (* READ_LATENCY_B = "2" *) 
  (* READ_RESET_VALUE_A = "0" *) 
  (* READ_RESET_VALUE_B = "0" *) 
  (* RST_MODE_A = "SYNC" *) 
  (* RST_MODE_B = "SYNC" *) 
  (* SIM_ASSERT_CHK = "0" *) 
  (* USE_EMBEDDED_CONSTRAINT = "0" *) 
  (* USE_MEM_INIT = "1" *) 
  (* USE_MEM_INIT_MMI = "0" *) 
  (* VERSION = "0" *) 
  (* WAKEUP_TIME = "0" *) 
  (* WRITE_DATA_WIDTH_A = "128" *) 
  (* WRITE_DATA_WIDTH_B = "128" *) 
  (* WRITE_MODE_A = "2" *) 
  (* WRITE_MODE_B = "2" *) 
  (* WRITE_PROTECT = "1" *) 
  (* XPM_MODULE = "TRUE" *) 
  (* rsta_loop_iter = "128" *) 
  (* rstb_loop_iter = "128" *) 
  project_1_adc_sink_i_0_xpm_memory_base xpm_memory_base_inst
       (.addra(addra),
        .addrb(addrb),
        .clka(clka),
        .clkb(1'b0),
        .dbiterra(NLW_xpm_memory_base_inst_dbiterra_UNCONNECTED),
        .dbiterrb(NLW_xpm_memory_base_inst_dbiterrb_UNCONNECTED),
        .dina(dina),
        .dinb({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .douta(NLW_xpm_memory_base_inst_douta_UNCONNECTED[127:0]),
        .doutb(doutb),
        .ena(1'b0),
        .enb(enb),
        .injectdbiterra(1'b0),
        .injectdbiterrb(1'b0),
        .injectsbiterra(1'b0),
        .injectsbiterrb(1'b0),
        .regcea(1'b0),
        .regceb(regceb),
        .rsta(1'b0),
        .rstb(1'b0),
        .sbiterra(NLW_xpm_memory_base_inst_sbiterra_UNCONNECTED),
        .sbiterrb(NLW_xpm_memory_base_inst_sbiterrb_UNCONNECTED),
        .sleep(sleep),
        .wea(wea),
        .web(1'b0));
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
