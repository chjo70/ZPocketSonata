// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:39 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_sd_fec_dec_0_sim_netlist.v
// Design      : project_1_sd_fec_dec_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "project_1_sd_fec_dec_0,sd_fec_v1_1_5,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "sd_fec_v1_1_5,Vivado 2020.1" *) 
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
PISqyosnZFbvhfWa/nlE36pFZGhTaSMcRPwHY4i7kzanH2s2urdMRdjyGflq5IqU9CbFxt4XgGy2
tZk7FbMKphYWNnH2l45IkQqWuVwllAcIqNct202Nt0lDh5em4OcKQxb7g26jM2gwtE+uydRQkl09
c75GZ+cxgX1LdMLGt14XJziI/qKaBCKjPNG73WIlGFGF1IlM9SyN1kRc+gxf9yiCL5NO5x97l/bv
6qjMxeEiS+nRwUnIt3X9egy0x3uFgVS19+jcae+oaPGhVDacOGTsk8fRmGUPnqHRmgqj+FDriE77
+y+lvxcUJm+uKu+ef06HRvRLO+jigFEdMucYRw==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
62bW8+awg3M250pedSsrACbanPP/FhRmErcxGimVX2qRWTj8gn0i6W4q65UavhPLg+r4fB+cigsy
CgsaStSYtYUE/QM7fFfsB/wlgoIF1wxg7z/gc7mve7zITfxW2TijcEdV61TuDyzl2FFO8622+ABc
wqc7f7zEmFQ0B2t/FZhQr8qe80MxiL2kSVP0VRPEOiofK7q78NglET8n4FxVek/zyIN0Dg2Emp2G
5UKfP4qrxcdh1Hxe0Yt+NhT3XBjmk7IbShBjxt0mIwBmGT+SzKJGXkuwCN4gb5Fjfjsb+4GIZB+p
i88CqRj8JQgB4onaQ801xQ32ZARegBgjGLRqhA==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 13664)
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
