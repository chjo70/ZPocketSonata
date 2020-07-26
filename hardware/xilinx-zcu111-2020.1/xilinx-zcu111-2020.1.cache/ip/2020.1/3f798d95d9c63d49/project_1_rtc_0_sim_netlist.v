// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
// Date        : Thu May 28 07:48:43 2020
// Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_rtc_0_sim_netlist.v
// Design      : project_1_rtc_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu28dr-ffvg1517-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "project_1_rtc_0,c_counter_binary_v12_0_14,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "c_counter_binary_v12_0_14,Vivado 2020.1" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
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
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_c_counter_binary_v12_0_14 U0
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
(* C_XDEVICEFAMILY = "zynquplus" *) (* downgradeipidentifiedwarnings = "yes" *) 
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_c_counter_binary_v12_0_14
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
  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_c_counter_binary_v12_0_14_viv i_synth
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
XLdhdgPvAWJ8HsKNoDVTTHlQh89J3jESMSw2Ly3RmmKJJzTc1C5Gxtd8Ps0rPPwgCQy/t6fLv34H
E5m6YnRYnGiHG6NDA5U6DuLuSPDGly1Bc6wvDpztdKfPhfGaY2vXhA/NwtUef8bhFq5xXU2k1K6Q
iFmmy/h2OxPNGcqr2gTXP4UWMMQiCTqYbefkVRBb3Zb9FT4Or0dyHSgkGeMo28AQGaMnSwDjQl/8
Su1ngqDJRgEVxLTxClfoMljzfYl2u3rcyF0mqEWqLcW4wew15vZ1iqcz2BXyYsv9lDgGwQx15l5A
t+D2YHDeXAdtp0iauiEO51tORCYydJdFv+B5Bg==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
OaHPsaN/ZxPq1jK6U4JcWzqdrxYCuBnXzX/Ovfgb7yPi8LjsTvgzhfinnn6frYaAEC12r7ZzWSH5
xFEeTCydUgH2g04DF5dyquJR0CQvSVgZF4UsZf8t5QMRvNO3hxrd8NpuEpEB8i7Xer3fLE/u90yV
908BsVpIPDRuOf85VYfPtW6lDtvsOeC1q+kW5ZNNnR96XYoiEKjFlKJgfKbBOjxm6UA9dM03NDU2
SmHB9tnIsjkmukccz4sQ7B2SohbLsU2x9YqBvJBOBmuTi8Z6jSndtmttafM/m39iGn/X5UK5Y6R/
BhBg/9tDGiU8/TdVu5IiyGfd+3GKxFZ3++TCQw==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 16592)
`pragma protect data_block
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
plSsNkc=
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
