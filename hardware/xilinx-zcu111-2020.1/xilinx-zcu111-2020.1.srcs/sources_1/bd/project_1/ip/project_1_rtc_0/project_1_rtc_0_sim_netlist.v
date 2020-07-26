// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:44 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim
//               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_rtc_0/project_1_rtc_0_sim_netlist.v
// Design      : project_1_rtc_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "project_1_rtc_0,c_counter_binary_v12_0_14,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "c_counter_binary_v12_0_14,Vivado 2020.1" *) 
(* NotValidForBitStream *)
module project_1_rtc_0
   (CLK,
    SCLR,
    Q);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk_intf, ASSOCIATED_BUSIF q_intf:thresh0_intf:l_intf:load_intf:up_intf:sinit_intf:sset_intf, ASSOCIATED_RESET SCLR, ASSOCIATED_CLKEN CE, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0" *) input CLK;
  (* x_interface_info = "xilinx.com:signal:reset:1.0 sclr_intf RST" *) (* x_interface_parameter = "XIL_INTERFACENAME sclr_intf, POLARITY ACTIVE_HIGH, INSERT_VIP 0" *) input SCLR;
  (* x_interface_info = "xilinx.com:signal:data:1.0 q_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME q_intf, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency bitwidth format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}} DATA_WIDTH 32}" *) output [31:0]Q;

  wire CLK;
  wire [31:0]Q;
  wire SCLR;
  wire NLW_U0_THRESH0_UNCONNECTED;

  (* C_AINIT_VAL = "0" *) 
  (* C_CE_OVERRIDES_SYNC = "0" *) 
  (* C_FB_LATENCY = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "1" *) 
  (* C_HAS_SINIT = "0" *) 
  (* C_HAS_SSET = "0" *) 
  (* C_IMPLEMENTATION = "0" *) 
  (* C_SCLR_OVERRIDES_SSET = "1" *) 
  (* C_SINIT_VAL = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_WIDTH = "32" *) 
  (* C_XDEVICEFAMILY = "zynquplus" *) 
  (* KEEP_HIERARCHY = "soft" *) 
  (* c_count_by = "1" *) 
  (* c_count_mode = "0" *) 
  (* c_count_to = "1" *) 
  (* c_has_load = "0" *) 
  (* c_has_thresh0 = "0" *) 
  (* c_latency = "1" *) 
  (* c_load_low = "0" *) 
  (* c_restrict_count = "0" *) 
  (* c_thresh0_value = "1" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  project_1_rtc_0_c_counter_binary_v12_0_14 U0
       (.CE(1'b1),
        .CLK(CLK),
        .L({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .LOAD(1'b0),
        .Q(Q),
        .SCLR(SCLR),
        .SINIT(1'b0),
        .SSET(1'b0),
        .THRESH0(NLW_U0_THRESH0_UNCONNECTED),
        .UP(1'b1));
endmodule

(* C_AINIT_VAL = "0" *) (* C_CE_OVERRIDES_SYNC = "0" *) (* C_COUNT_BY = "1" *) 
(* C_COUNT_MODE = "0" *) (* C_COUNT_TO = "1" *) (* C_FB_LATENCY = "0" *) 
(* C_HAS_CE = "0" *) (* C_HAS_LOAD = "0" *) (* C_HAS_SCLR = "1" *) 
(* C_HAS_SINIT = "0" *) (* C_HAS_SSET = "0" *) (* C_HAS_THRESH0 = "0" *) 
(* C_IMPLEMENTATION = "0" *) (* C_LATENCY = "1" *) (* C_LOAD_LOW = "0" *) 
(* C_RESTRICT_COUNT = "0" *) (* C_SCLR_OVERRIDES_SSET = "1" *) (* C_SINIT_VAL = "0" *) 
(* C_THRESH0_VALUE = "1" *) (* C_VERBOSITY = "0" *) (* C_WIDTH = "32" *) 
(* C_XDEVICEFAMILY = "zynquplus" *) (* ORIG_REF_NAME = "c_counter_binary_v12_0_14" *) (* downgradeipidentifiedwarnings = "yes" *) 
module project_1_rtc_0_c_counter_binary_v12_0_14
   (CLK,
    CE,
    SCLR,
    SSET,
    SINIT,
    UP,
    LOAD,
    L,
    THRESH0,
    Q);
  input CLK;
  input CE;
  input SCLR;
  input SSET;
  input SINIT;
  input UP;
  input LOAD;
  input [31:0]L;
  output THRESH0;
  output [31:0]Q;

  wire \<const1> ;
  wire CLK;
  wire [31:0]Q;
  wire SCLR;
  wire NLW_i_synth_THRESH0_UNCONNECTED;

  assign THRESH0 = \<const1> ;
  VCC VCC
       (.P(\<const1> ));
  (* C_AINIT_VAL = "0" *) 
  (* C_CE_OVERRIDES_SYNC = "0" *) 
  (* C_FB_LATENCY = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "1" *) 
  (* C_HAS_SINIT = "0" *) 
  (* C_HAS_SSET = "0" *) 
  (* C_IMPLEMENTATION = "0" *) 
  (* C_SCLR_OVERRIDES_SSET = "1" *) 
  (* C_SINIT_VAL = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_WIDTH = "32" *) 
  (* C_XDEVICEFAMILY = "zynquplus" *) 
  (* KEEP_HIERARCHY = "soft" *) 
  (* c_count_by = "1" *) 
  (* c_count_mode = "0" *) 
  (* c_count_to = "1" *) 
  (* c_has_load = "0" *) 
  (* c_has_thresh0 = "0" *) 
  (* c_latency = "1" *) 
  (* c_load_low = "0" *) 
  (* c_restrict_count = "0" *) 
  (* c_thresh0_value = "1" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  project_1_rtc_0_c_counter_binary_v12_0_14_viv i_synth
       (.CE(1'b0),
        .CLK(CLK),
        .L({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .LOAD(1'b0),
        .Q(Q),
        .SCLR(SCLR),
        .SINIT(1'b0),
        .SSET(1'b0),
        .THRESH0(NLW_i_synth_THRESH0_UNCONNECTED),
        .UP(1'b0));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2020.1"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
EJFZwtxl4g9/OL6+bopUV8BP4e67HNukCIy7Ih3E75y7soa6GhqEucPXMiOy+mJrcrNwD+HjZ0/I
BwEKIiA4mA==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
rZCGWdmPJXoOuANoS8fyUXk7SyF+uTNJL18BfeKc+fxcyRrCB++WrM02adxoUdICz4/92yY8TQgj
xyPC0eaHZcjSLepbnHHgSReIQ1PL0hmufLbye7QTD0ygUXC4MvFVY8s3KeW9cPCqOxkyCSziJQzs
J5OT9XLQno1e9rIBr9M=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
I7Zo4frj3tO6FFzeDhpSENS0yd34dQZBtiyIrI/GMASFBUeny6muOD2l0HK69ImRJIOyobvK1+9O
DhxptAc4NzRpY4xUZvr4ix1AhM1Kars1OkrQCWz4a7ciGU/XDblidF3IL0Fa7c41gHIZR9c/Usa6
XL7UEu3aSPQYbZLSDOzeao4VtSSn+dCcjsH4X8zVjSqXg8dcN3fd5C15JaMYg00F2yOFtxwWwZWq
Yvwe1q1PG/wcA1cKAOscANbj4o3O4LjfylNIB6L+Mssxosh+e0+oobWNk/ouBa4k1c3/IzXGSCAs
hEvbI+iqkWJJKZrSb9PZk7S7XSJcScrJO/DGkQ==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
DDRecdVJcCPEpbUqhuwKtKWXteF7XhGc5d+lQn2uiREzbHyuZvQ1wDwAGGrPwE75gjqc7CdHPMOY
8+3nqcEwR4Q5USgQcou3Cyc6C0TnzzDD/dLKPHDWA1s52x8Rx+LBH9WCvBpD5BKkE4o1s3rN1tL2
wTdCqzzKD8YlryKQ4U0lr2bX6Mlf4/nIt2K1eyPKbIrHIvKDThmaIF/qLnLnkE04pksWJ9Af1OVB
46iqBssrR5p6wZc241D4CqSRCRamfP/s1JrTi8bBNCcXhC0f0Aa35UAoG8vnFngHlFd3G2J88cas
Fo7UH4k1BTTfgbQ35ec0XfSbS/qQWS+EgAF+wA==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
L11p2bsABDhO9HvT3IM+HulCClFvs/UPexuAVExicKtzrLN7tNvUjSouZSn9KwAjR2hg5ZIJ23uy
1elB+eyEl65vQnoH4+s6Q5K4EIcMo5WVKfIKwgu5Q3Sg/jYW+aWT/kGuc7CazRsTxJ7XPFndpMIM
cxYWx2DLps320t+Be0c=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Uublhc2r9VmPPq1tMATsd3XJltn9QRg1/PdCtSlxgFBDDAk13md52Fz+h+DOWptR3Q4i+Sx5IhIP
QIONVNTf1DnoK/wa1lkbd1dROJam8/cZQFiIxnsnSPGXzOGoc0c04xDSCJCCDxiDMF1YTtAqt6nw
yZh1RwOhPpgwUKjeJ4o4TY6/i0xuYAYVc83O6KwI9Ywk9UsfyIQQS8UXFo8zA9eniU2n2NcyAVNj
Y8xZ9PYJfzfDo6dHWsj4Ik588uhfO/bmsf2/ZuY5HCAMQpnda9XzPkVomNjRfsUghko7KipIl2ur
aHh+4i2kI/+cHaihhw3z14aGidBkuYKaopasbA==

`pragma protect key_keyowner="Real Intent", key_keyname="RI-RSA-KEY-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
VYqlyQSuRywWcSrUprXX2UzoaWsJXTTbptzDY9ycgFR91H2uYfY43f80gn0E87Gvj90Qmn0Dl6ck
2VjO2Zn9yATmqtuzi/Etuf29dkl3uyKtk02OitZJEhD1CDyUJHDXKHkPMXOZCBU5CfkrIWw2SsSq
YuQKmvxp4BrhcwXypr+vRSsYd1liMxxuXOdBN5AIyzibGfcR4YUeOokIoP05xZoQOfPQkotMC1B6
SHVKEaBxe37YkyKAkQ0f9eKfnPPLG/G5qeLrFPAiIar0HHpOvdCOO69vi3RG1XqoxtTm/wGwRb5J
ZqzZyTn1Fm55PXyKhlElzXXAv1xPOTbkJXRZNQ==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2019_11", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
EktM4icAEVQRmfzXBBFeRr7d3ZTOU9f+J40sQAiff114nDU+fxlewcv+twlytUk9LMSR67RJlLt4
+ZBTwcuSPZ2Cvrommkp++7rNze0VCD8pSAdj4uo1ZnYWVWmPMQaRIqI88lnAzc5+T/LxEiXKn4ji
AYGs9fja4ME8C0CHbBsg+jfUryleVk1D8jEMCetM7qDx64s/7AGfwzDqMiW2DPCPLKNUsdlOlBYT
JAOnfy6deN7/o7BYxBsE1P4Pib1x1hvR8RwEm38pBOLKGade6KL/1SHmz5N1KGLPSXQXlK53RLTI
Exc4wN04Kg72tf503oGq6Vp90c5pksQ9cc0M+w==

`pragma protect key_keyowner="Metrics Technologies Inc.", key_keyname="DSim", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
qzYsaSn6YzxyfrxIwv3eyowRK7ZyzZmQHzUmV2AITf6g43c7IV/fwNBDik+XFhLScW2SxsyaGGI7
5n6kAt9uM3GerkCXA+LJQrqshcEyjuvm17vWVovBURqxhTARgZaTs5OtXdhc/wLi5e6lsdyyLtQo
bt66ubjErMgf5+tD8rpn0HkjUYmGv/MBZ0i4bGui735H12aK+wTfhGVOOiuWHCk2zCJJSx3vH4sl
dKtlpg4W0hPEM3TBPHaLnOpIDkrIUaGGN5fm6NJL6US59+Lr8/3mplbD8ld21OKzgLH+5YPRMoo4
1Pbjxkawu5Kk60AsuaR/OxngawaRMd9N4niRfQ==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
cNBf/tUNTviOnNkBQSHY2LGaeXI4Oi2L/s2Uw2qQq4oIx664c06Z3FZuFqPVqfY8f7yZepAW63uL
XE9Zd79/ges44QuTIEFbwrXUCRISTKeGE8DqhA/yY5K/1p4/xi2ChbhlFjLFqkMLbbmLtWa9C79J
XDBomYnfA1gzozNuv/XUO1F2EgKoGAoF+JIZlhEMzOlJNT9heBcmMqQJOdQFIHC5E73xltteoSbr
kACCoS9AO6XEaNfWZrw0w0YlpWd9CBzyNsF87edaUHMgryf43pUJjiPYzxvktyl+8jbLhBYUgxcT
R1LtQLwxgp3yBt5m8xMZr4BWO2OE44a0Mbkd3A==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
JIpdgddSFrjhNS6JXByt3UPlkwPMakteJKYtf/o8Ra6h57YRRvjuVcSZZWIaFI80Jl25pjEcQVNr
f39rdpkCUf2V3fe77tJLgYwKSQ9A8ix7AUGxG/C/tCKmwM7ajFrs8HJ7DVlL2q5IVlXOF1tTdMT3
F3mICET5r27zTsxL7ZtzhVXPW9yewWL2ZDM8ylIOIHkbX4niqEb8kQ5qa9GQIa8AvXr3fWOMY1ak
nCd2j2jhVIl2MlJFTFH/2LDOLETfTf2SqvbMiglnBJWGX4/VVagbDeBDPCZkAV5xlHLryAM+7wXf
6OaoekPgBNMNm216RzwTePLDxdtSKhtsrrk6hQ==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 16640)
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
