// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:41 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim
//               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_sd_fec_enc_0/project_1_sd_fec_enc_0_sim_netlist.v
// Design      : project_1_sd_fec_enc_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "project_1_sd_fec_enc_0,sd_fec_v1_1_5,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "sd_fec_v1_1_5,Vivado 2020.1" *) 
(* NotValidForBitStream *)
module project_1_sd_fec_enc_0
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
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 S_AXIS_DIN TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S_AXIS_DIN, TDATA_NUM_BYTES 16, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0" *) input [127:0]s_axis_din_tdata;
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
  wire [127:0]s_axis_din_tdata;
  wire s_axis_din_tlast;
  wire s_axis_din_tready;
  wire s_axis_din_tvalid;
  wire NLW_inst_s_axis_din_words_tready_UNCONNECTED;
  wire NLW_inst_s_axis_dout_words_tready_UNCONNECTED;

  (* CODE_REG_FILENAME = "NO_INIT" *) 
  (* CORE_AXIS_ENABLE = "0" *) 
  (* CORE_AXIS_WIDTH = "0" *) 
  (* CORE_AXI_WR_PROTECT = "0" *) 
  (* CORE_BYPASS = "0" *) 
  (* CORE_CODE_WR_PROTECT = "0" *) 
  (* CORE_ECC_IER = "0" *) 
  (* CORE_IER = "0" *) 
  (* CORE_ORDER = "0" *) 
  (* C_CTRL_TDATA_WIDTH = "32" *) 
  (* C_ELABORATION_DIR = "./" *) 
  (* C_MODE = "LDPC_ENCODE" *) 
  (* C_M_DOUT_TDATA_WIDTH = "128" *) 
  (* C_PHYSICAL_UTILIZATION = "100.000000" *) 
  (* C_SIM_DEVICE = "ULTRASCALE_PLUS" *) 
  (* C_STANDARD = "CUSTOM" *) 
  (* C_S_AXI_MODE = "0" *) 
  (* C_S_DIN_TDATA_WIDTH = "128" *) 
  (* C_S_DIN_WORDS_MODE = "0" *) 
  (* C_S_DIN_WORDS_TDATA_WIDTH = "8" *) 
  (* C_S_DIN_WORDS_VALUE = "16" *) 
  (* C_S_DOUT_WORDS_MODE = "0" *) 
  (* C_S_DOUT_WORDS_TDATA_WIDTH = "8" *) 
  (* C_S_DOUT_WORDS_VALUE = "12" *) 
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
  project_1_sd_fec_enc_0_sd_fec_v1_1_5 inst
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
AOft4B5piF0dnBF9xLiz6BfGeMp2ykAIgdWfuRHPx22mYlM93mKl9W7o9a42qJcZ4VZgCoH07v7j
L4AROsNkULLcwGotzumcTnf9DkbqxfxrA4tkSMZjmLuLdhAd3mzujtnX/7DSiQf9g5FpJydrJqN8
lG4FkRiLCQKvO7rH+WAVA2YAh9CPQhsUwMFrbh4GAKl1DZN1RsCX3XvpiVdjLpURg484kG6saONk
t4HZMRMYMMmc4paW6oHWX5VxiNY9+RU+z0iX8RfbwO8lFr2JYKE+88Q+Q5ac4182WrVycYLSPxoE
7NdgDcq58+FSw9C/4/hgd2y45S+CKfgoTPBNFA==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
MLAZauWF6WzIE7GLb7hHBgti1oi4WD0ZBg0JjfwVUtp0nepUpsOc9f4P9vWbHJTxzgnypFmSRVYt
GBgxfRUzoh5qVcNEBF0CujomXy7Y5QlW+e++r28bV1i+hKFy3gxFMqEseueOIgo8/5kOn+aJJcmm
aveoYJFOBzlii5FinWyEpLbZQul9lLnU7jPSWgvFrLeq3RXl4Q74GrwADeDzwTB0iXH+jSJaE8jD
vynwHGXi9774qGprwFhkznxYOIXeiWS+1XAbIU9gSwa4MEx1atTejQ8B5gno/mUG4VuZeKnFKgGn
Fj3Jd3OfhE0j9E6TUluiCbEmUzVgTsNZYew9mA==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 14400)
`pragma protect data_block
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
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
