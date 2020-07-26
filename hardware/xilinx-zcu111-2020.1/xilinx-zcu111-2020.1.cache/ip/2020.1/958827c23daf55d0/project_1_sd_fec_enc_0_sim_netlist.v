// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:40 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_sd_fec_enc_0_sim_netlist.v
// Design      : project_1_sd_fec_enc_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "project_1_sd_fec_enc_0,sd_fec_v1_1_5,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "sd_fec_v1_1_5,Vivado 2020.1" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
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
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_sd_fec_v1_1_5 inst
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
b5VKZUExktM+TGxl2Z2EOWPLHOFkY4SCtsRG/tZUhzvqmIaW2vPBY3LeU8c/FV5dYyP9c/GbswRX
0gTj9AGVmR+ii7Zh+diMRfCzK8F9RovhNnpXlt9aeONo6SH2beCnhZ1H/bCYFGx5TILzQlwKbAy6
krEy6jX0jEe75774U2FPvZKgd+IvzulEHUe/qsQPI3/1bMuhND4+dj/4dEN0ZCl5RddTDxQ1Sm5+
1RgwApfkCXSgE+DGpKN3wKj5VhBfN0JcJ0wnRF0ar0xxhwJEuTtv8wDiioQ2q4H+ixTT1M5PPEo/
KKtm1KhwZJWZSOcbberdXy/JHSYixYVcWinQng==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
eLB/N8+7FsaBmk6KvBuIhiex16QKZ3eI/Tip1fyBPsHZrirt1tzC3SxsAoWFQ15Y6EafcXkCTUW3
XUtJrVnl8VVjRO2UAzo8UdyWAa28SMfj64WSkFs7MJO4PQAg/TVxjSYq7yLaV7WXj+0AiKFDzM+5
tmoQx1KlfxvJVj0w8LhLqN1Ffls34tLzSFeOvh62oue31BCR9DF/U1QqRZX5cjQ5OnA61Y8eriuU
IzYfY/g561pNKDOuGOn5nmn6g38uWVqmkS3QQL79c+h4EPEWJTrFFUZNEAR7zRm0OAJ4AVcWyhTj
7QpZ89lzYnFyG3//y0mQREaW6Oj6S1/OWskPwQ==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 14368)
`pragma protect data_block
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
fRo6Jw==
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
