// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:40 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim
//               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_sd_fec_dec_0/project_1_sd_fec_dec_0_sim_netlist.v
// Design      : project_1_sd_fec_dec_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "project_1_sd_fec_dec_0,sd_fec_v1_1_5,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "sd_fec_v1_1_5,Vivado 2020.1" *) 
(* NotValidForBitStream *)
module project_1_sd_fec_dec_0
   (reset_n,
    core_clk,
    s_axi_aclk,
    s_axi_awaddr,
    s_axi_awvalid,
    s_axi_awready,
    s_axi_wdata,
    s_axi_wvalid,
    s_axi_wready,
    s_axi_bready,
    s_axi_bvalid,
    s_axi_araddr,
    s_axi_arvalid,
    s_axi_arready,
    s_axi_rready,
    s_axi_rdata,
    s_axi_rvalid,
    interrupt,
    s_axis_ctrl_aclk,
    s_axis_ctrl_tready,
    s_axis_ctrl_tvalid,
    s_axis_ctrl_tdata,
    s_axis_din_aclk,
    s_axis_din_tready,
    s_axis_din_tvalid,
    s_axis_din_tlast,
    s_axis_din_tdata,
    m_axis_status_aclk,
    m_axis_status_tready,
    m_axis_status_tvalid,
    m_axis_status_tdata,
    m_axis_dout_aclk,
    m_axis_dout_tready,
    m_axis_dout_tvalid,
    m_axis_dout_tlast,
    m_axis_dout_tdata);
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 reset_n_intf RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME reset_n_intf, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input reset_n;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 clock_intf CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME clock_intf, FREQ_HZ 666666666, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input core_clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s_axi_aclk_intf CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_aclk_intf, ASSOCIATED_BUSIF S_AXI, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input s_axi_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI AWADDR" *) input [17:0]s_axi_awaddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI AWVALID" *) input s_axi_awvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI AWREADY" *) output s_axi_awready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI WDATA" *) input [31:0]s_axi_wdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI WVALID" *) input s_axi_wvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI WREADY" *) output s_axi_wready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI BREADY" *) input s_axi_bready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI BVALID" *) output s_axi_bvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI ARADDR" *) input [17:0]s_axi_araddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI ARVALID" *) input s_axi_arvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI ARREADY" *) output s_axi_arready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI RREADY" *) input s_axi_rready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI RDATA" *) output [31:0]s_axi_rdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S_AXI RVALID" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S_AXI, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 100000000, ID_WIDTH 0, ADDR_WIDTH 18, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 0, HAS_BRESP 0, HAS_RRESP 0, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 8, NUM_WRITE_OUTSTANDING 8, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) output s_axi_rvalid;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt_intf INTERRUPT" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt_intf, SENSITIVITY EDGE_RISING, PortWidth 1" *) output interrupt;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s_axis_ctrl_aclk_intf CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axis_ctrl_aclk_intf, ASSOCIATED_BUSIF S_AXIS_CTRL, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input s_axis_ctrl_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_CTRL TREADY" *) output s_axis_ctrl_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_CTRL TVALID" *) input s_axis_ctrl_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_CTRL TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S_AXIS_CTRL, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0" *) input [31:0]s_axis_ctrl_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s_axis_din_aclk_intf CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axis_din_aclk_intf, ASSOCIATED_BUSIF S_AXIS_DIN, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input s_axis_din_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_DIN TREADY" *) output s_axis_din_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_DIN TVALID" *) input s_axis_din_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_DIN TLAST" *) input s_axis_din_tlast;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_DIN TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S_AXIS_DIN, TDATA_NUM_BYTES 32, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0" *) input [255:0]s_axis_din_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 m_axis_status_aclk_intf CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axis_status_aclk_intf, ASSOCIATED_BUSIF M_AXIS_STATUS, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input m_axis_status_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 M_AXIS_STATUS TREADY" *) input m_axis_status_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 M_AXIS_STATUS TVALID" *) output m_axis_status_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 M_AXIS_STATUS TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME M_AXIS_STATUS, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0" *) output [31:0]m_axis_status_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 m_axis_dout_aclk_intf CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axis_dout_aclk_intf, ASSOCIATED_BUSIF M_AXIS_DOUT, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input m_axis_dout_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 M_AXIS_DOUT TREADY" *) input m_axis_dout_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 M_AXIS_DOUT TVALID" *) output m_axis_dout_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 M_AXIS_DOUT TLAST" *) output m_axis_dout_tlast;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 M_AXIS_DOUT TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME M_AXIS_DOUT, TDATA_NUM_BYTES 16, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0" *) output [127:0]m_axis_dout_tdata;

  wire core_clk;
  wire interrupt;
  wire m_axis_dout_aclk;
  wire [127:0]m_axis_dout_tdata;
  wire m_axis_dout_tlast;
  wire m_axis_dout_tready;
  wire m_axis_dout_tvalid;
  wire m_axis_status_aclk;
  wire [31:0]m_axis_status_tdata;
  wire m_axis_status_tready;
  wire m_axis_status_tvalid;
  wire reset_n;
  wire s_axi_aclk;
  wire [17:0]s_axi_araddr;
  wire s_axi_arready;
  wire s_axi_arvalid;
  wire [17:0]s_axi_awaddr;
  wire s_axi_awready;
  wire s_axi_awvalid;
  wire s_axi_bready;
  wire s_axi_bvalid;
  wire [31:0]s_axi_rdata;
  wire s_axi_rready;
  wire s_axi_rvalid;
  wire [31:0]s_axi_wdata;
  wire s_axi_wready;
  wire s_axi_wvalid;
  wire s_axis_ctrl_aclk;
  wire [31:0]s_axis_ctrl_tdata;
  wire s_axis_ctrl_tready;
  wire s_axis_ctrl_tvalid;
  wire s_axis_din_aclk;
  wire [255:0]s_axis_din_tdata;
  wire s_axis_din_tlast;
  wire s_axis_din_tready;
  wire s_axis_din_tvalid;
  wire NLW_inst_s_axis_din_words_tready_UNCONNECTED;
  wire NLW_inst_s_axis_dout_words_tready_UNCONNECTED;

  (* CODE_REG_FILENAME = "NO_INIT" *) 
  (* CORE_AXIS_ENABLE = "0" *) 
  (* CORE_AXIS_WIDTH = "1" *) 
  (* CORE_AXI_WR_PROTECT = "0" *) 
  (* CORE_BYPASS = "0" *) 
  (* CORE_CODE_WR_PROTECT = "0" *) 
  (* CORE_ECC_IER = "0" *) 
  (* CORE_IER = "0" *) 
  (* CORE_ORDER = "0" *) 
  (* C_CTRL_TDATA_WIDTH = "32" *) 
  (* C_ELABORATION_DIR = "./" *) 
  (* C_MODE = "LDPC_DECODE" *) 
  (* C_M_DOUT_TDATA_WIDTH = "128" *) 
  (* C_PHYSICAL_UTILIZATION = "100.000000" *) 
  (* C_SIM_DEVICE = "ULTRASCALE_PLUS" *) 
  (* C_STANDARD = "CUSTOM" *) 
  (* C_S_AXI_MODE = "0" *) 
  (* C_S_DIN_TDATA_WIDTH = "256" *) 
  (* C_S_DIN_WORDS_MODE = "0" *) 
  (* C_S_DIN_WORDS_TDATA_WIDTH = "8" *) 
  (* C_S_DIN_WORDS_VALUE = "16" *) 
  (* C_S_DOUT_WORDS_MODE = "0" *) 
  (* C_S_DOUT_WORDS_TDATA_WIDTH = "8" *) 
  (* C_S_DOUT_WORDS_VALUE = "16" *) 
  (* C_THROUGHPUT_UTILIZATION = "100.000000" *) 
  (* ENCODE = "0" *) 
  (* KEEP_HIERARCHY = "soft" *) 
  (* LA_TABLE_FILENAME = "NO_INIT" *) 
  (* MERGED_CODE_REG_SIZE = "0" *) 
  (* MERGED_FILENAME = "NO_INIT" *) 
  (* MERGED_LA_TABLE_SIZE = "0" *) 
  (* MERGED_QC_TABLE_SIZE = "0" *) 
  (* MERGED_SC_TABLE_SIZE = "0" *) 
  (* NM_NMQC_FILENAME = "NO_INIT" *) 
  (* ONLY_5G = "0" *) 
  (* QC_TABLE_FILENAME = "NO_INIT" *) 
  (* QC_TABLE_FILENAME_T = "NO_INIT" *) 
  (* SC_TABLE_FILENAME = "NO_INIT" *) 
  (* TURBO_INIT = "0" *) 
  project_1_sd_fec_dec_0_sd_fec_v1_1_5 inst
       (.core_clk(core_clk),
        .interrupt(interrupt),
        .m_axis_dout_aclk(m_axis_dout_aclk),
        .m_axis_dout_tdata(m_axis_dout_tdata),
        .m_axis_dout_tlast(m_axis_dout_tlast),
        .m_axis_dout_tready(m_axis_dout_tready),
        .m_axis_dout_tvalid(m_axis_dout_tvalid),
        .m_axis_status_aclk(m_axis_status_aclk),
        .m_axis_status_tdata(m_axis_status_tdata),
        .m_axis_status_tready(m_axis_status_tready),
        .m_axis_status_tvalid(m_axis_status_tvalid),
        .reset_n(reset_n),
        .s_axi_aclk(s_axi_aclk),
        .s_axi_araddr(s_axi_araddr),
        .s_axi_arready(s_axi_arready),
        .s_axi_arvalid(s_axi_arvalid),
        .s_axi_awaddr(s_axi_awaddr),
        .s_axi_awready(s_axi_awready),
        .s_axi_awvalid(s_axi_awvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_bvalid(s_axi_bvalid),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rready(s_axi_rready),
        .s_axi_rvalid(s_axi_rvalid),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wready(s_axi_wready),
        .s_axi_wvalid(s_axi_wvalid),
        .s_axis_ctrl_aclk(s_axis_ctrl_aclk),
        .s_axis_ctrl_tdata(s_axis_ctrl_tdata),
        .s_axis_ctrl_tready(s_axis_ctrl_tready),
        .s_axis_ctrl_tvalid(s_axis_ctrl_tvalid),
        .s_axis_din_aclk(s_axis_din_aclk),
        .s_axis_din_tdata(s_axis_din_tdata),
        .s_axis_din_tlast(s_axis_din_tlast),
        .s_axis_din_tready(s_axis_din_tready),
        .s_axis_din_tvalid(s_axis_din_tvalid),
        .s_axis_din_words_aclk(1'b0),
        .s_axis_din_words_tdata({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axis_din_words_tlast(1'b0),
        .s_axis_din_words_tready(NLW_inst_s_axis_din_words_tready_UNCONNECTED),
        .s_axis_din_words_tvalid(1'b0),
        .s_axis_dout_words_aclk(1'b0),
        .s_axis_dout_words_tdata({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axis_dout_words_tlast(1'b0),
        .s_axis_dout_words_tready(NLW_inst_s_axis_dout_words_tready_UNCONNECTED),
        .s_axis_dout_words_tvalid(1'b0));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2014"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
knvRUaG53OEbkHgE0qM5rBJnJSMrMXVD13xmdoATjS/SAAIsNV8M1QpeeBe3GVagKOrD4N1lnR1n
EflKkWMSHQ==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
RojPcTMWsSgRsNak5JGa5dj9vJNUte5RrkxJAePNErEfGK5RYXc6+sZumCjPDX5O1FKJFlQ8EAze
r/x7rvrBjoJp+qPHaNiZiujQ+rR4qDv0KdS3AuRT4s2h29EgienZ7ycxAY7tK1/4Rbvpw0WVN8yW
9vH5UVM/+VD56u4pnuI=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
C+gyiAZhhjOe24Lbw1EjjPWaKtUbVZ3/ygx/ORA++Mu17hK3Hba/mh3IPpw2kCONPtDYkHMXD2/w
+YUJ2Ew7shI0zqb0xHaFwds970chPju1lz5N1RkqSBqGcCd98lf9OS80vsbhujrRcXPv73RYHcO3
vzsUnHWDdNn2AFwAzN6EPx16EnUUqh8wq4mEolp5p5XAQsDPTo4FU1ust2VOx146aztJQBp/HVAc
7CdGfUe6dv2yHBCJsNyANw3aNGHQwp+dhfUghxXf8xK20FHcNOMMg19RTXYnREF09PIhaMtf+sSM
ci00Y/lbGsby+dh9NDJ7JfP8HokGr+hnS1wnug==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
o69lWjGawK0fBFchQnHyLKuqciS47buo45TOMD8c6njHkpFhIwkTOPzMJb4U4JwcNwLVRZdiGbkS
Pwa4dcL9BsWS2wm36RL94Uk1D1pWJgpj4Qs5SCi3b1GpCvXy62mETLLqeUWUkMnK9t5seCgaz2nK
A0QD87mQzNSwaHfTgpjnmhInh5izyMGQWtPNnnkQDn9TQjlIgwSp+AkMby11ndkO8//zQ1gnmmfb
IIU/sQHIcx4PBfW3/DpInEfJshwOURZNqIlFIVf6eXHhPFsrA/f6an/pm4h5cQ9Zcl9XRhPZEo0n
qpRh4kuaMCDzDdMxr+n1mtPzXQsE8iYEjKFDrA==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
qgMBQ1nfgOv0dSBL7RXAI54fvhKSoC/x3roBblAN315N61WAtgasZQJtZiS2ny+jSnEFSt3bpfQu
ZbMNJdZ6o1EUSWr7i4Bze2KjYB28TPScD/zCcc6BwR9IC5reCibXy8Q8HyQYAsKS5sip1zb8D565
U7ycNmROIomW5Nm0Usg=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
VDlH8ikmMNDUvJgJpQxTW/Tz47WjZuEk31YcbfRmiC0gP+zPnE56koAOPwazpduJtfKadjkfAmL3
BtyURoFW7Cyd/FmkUH2698Ta4u3vKxuQtHh6dCayupDVKbSdk508ADVxjsOYbprWPva+zNTrrmW+
Llh+xG63aiSBC+c5IuWgk1UnEKYmjVyuwU9T+P0SWPHvHNnnCWH5EOYBoJmXdTOw10hM664rTSTM
XRHJsUrwnkBKWiiqbOxY3hlu7obPeeuGvWfNv71h1aOO2IOZHOG8Tud3g/QPMEGbMYDNrv0Dmerr
QKCHU6KxiZt6Ew6vRdqIoUpHNc9UF05mXKGFig==

`pragma protect key_keyowner="Real Intent", key_keyname="RI-RSA-KEY-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
okzvWPysCwh2M+aJzvdTickbuEmDXMO8uKrB/R1NTKIB5gR4LnGAl+bdW4Au4CaA2GjmpjlzmGH1
b43pNB3pyxrT2UwcCis47UTdB9HHT1+lh+FzY3TlfDLSN/P+p7XHYe+zIamcVh8wewOWRfz0xYNY
2BAJbPxNA739NysUVoCTlUXJJFUNRRVxADNFBbJLulmf48MvHHZ9kBDD6/0v8G95wMNBZP/ytwti
T0ZdEOByJZ+og94EHsRkHspI3G36AavgacpNy4BLJFPyT9lh8MZHBj7yVvFHNBULX5ekBDz6HsqR
9lMjLuoScNNUEAHdC01cER2G4Ub1ntzeJ22ZuA==

`pragma protect key_keyowner="Metrics Technologies Inc.", key_keyname="DSim", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
pqj98eBM23R7n3NgIeCE3arVF8ov0oJ8Ff/jMpGE9AAjOhs3MKe+KEkx44yB1K365M6+VSPO0cp5
z5u0iOpts+qsMNg4ubNun8OZLbY2Y0o5Tx0Yzrcm9GqdBbt/sOmnajv59xUydRGzCodCJPMEAIQC
FZw5K9GjCb6sNJgnDuSvsDwRTyN3ADlVSRNso1RpsZjRBZtbrGTT/SLSehWs9NQ4ySqO7NpJeF2P
7LcszwpaoNtT5ZI3yXOKN4/LPO/+LzIgY6ZDcQgoG2ZURQSy9W+0GSOmXz6l3L0or5K5gs0wKqJ/
9tWeqnFPvedNth/86lt2cwKAofU52CX/jC1Dmg==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2019_11", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
hbAR+J5lHm78ZT3c0A1SW75zM5SuRhabqzkH0v0YPRG1BM0SkBqLtwTgcU9DWQV9zouculjKxT5D
bXEqDA4P7zHF50XRs+dSd27pCJImOle3Rj8e7QoE27ZPWIyR+wbUwQ7AcDhGzfp3UJ9rdWPKKVDP
CCOhmzbzSgxOSKtAeI0V9hWuTqo9rnUFi/Jx4S2F9BGP2c0ZsvK3mzcQb4owZAwjTZzY61/ekFJp
LD+08t5ny/jzCFlnIfxGZTQFTMizuy/XPOXsKwSv6Cvf0BRYngan8Icb5H4XV4atxl+R3LUEG1gw
IjXe81o3/ET9dEAVVw6s1fvtOo1ZSHo622z1Pg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
MSRWn3q2lmLEM62lV9Lirp2zyyxRqA5S30cvrriu3Ejfys/n7PPpNVc6U5cJ/CYTiXpkHyguALPy
Eg081171FKakJ2RKN95RQeuCPaWwuHjf36QYFM93SY3Ztf1DoCNOedfkJuwTAYgpBZqrtFFlO/7j
zehM2CvwE6t6gNMKqxAy4xA0b3REq/dyegEwI9bhq3ZmWpeCnKbeNuhjE0HzVcmC5EE+GY0SB/DH
PTPMtM8ZWvQ6ahmn8ElrN7dZTgl2krkmPkZ/LhivLS8u5Xg4ByWrnGYFwgcUWb2hFv77onGvcDx9
6r1ftvF2QhMJekVno5f5HsOM6fOFjm5fFVauBA==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
HR3MWEIRMqs1csS5TKiiTVUTOmZXZOQI6VE4eXh6AvF/V73x2n/G1UOgqMdOP/AxhFfG4rB2mnr6
mBbWLTlv9B1kBjNaKynMLPc8RuxsNA/bXdnHqNtT4sQ3Qc1VVS2kDKAMoaP5ODW9ylMAz06v5AsX
NKhjWbvPk4UYegwurdlvQom5GMsWUMvgKoPnEIY8JWTFDa2m3IbIDhS7K1i9SZrvuw+fx7mHXHSx
M4feqaDq9mlkI+ta+7/uXU/bQ/U71vLFgDdA4jHcbfeY8dPVLVDOehhlL/3Y6GmYrLYLhNNFPsio
dwBvgYxely1jxgR0h4HFYT2qc6DalTsMimja7w==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 13696)
`pragma protect data_block
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
KfZWMokyeVYlUEsJcbxeDA==
`pragma protect end_protected
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
