-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
-- Date        : Thu May 28 07:46:20 2020
-- Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
-- Command     : write_vhdl -force -mode funcsim -rename_top project_1_dec_op_probe_0 -prefix
--               project_1_dec_op_probe_0_ project_1_dec_ip_probe_0_sim_netlist.vhdl
-- Design      : project_1_dec_ip_probe_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu28dr-ffvg1517-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity project_1_dec_op_probe_0 is
  port (
    clk : in STD_LOGIC;
    mon_tvalid : in STD_LOGIC;
    mon_tready : in STD_LOGIC;
    mon_tlast : in STD_LOGIC;
    valid_op : out STD_LOGIC;
    ready_op : out STD_LOGIC;
    last_op : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of project_1_dec_op_probe_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of project_1_dec_op_probe_0 : entity is "project_1_dec_ip_probe_0,axis_probe,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of project_1_dec_op_probe_0 : entity is "yes";
  attribute ip_definition_source : string;
  attribute ip_definition_source of project_1_dec_op_probe_0 : entity is "package_project";
  attribute x_core_info : string;
  attribute x_core_info of project_1_dec_op_probe_0 : entity is "axis_probe,Vivado 2020.1";
end project_1_dec_op_probe_0;

architecture STRUCTURE of project_1_dec_op_probe_0 is
  signal \^mon_tlast\ : STD_LOGIC;
  signal \^mon_tready\ : STD_LOGIC;
  signal \^mon_tvalid\ : STD_LOGIC;
  attribute x_interface_info : string;
  attribute x_interface_info of clk : signal is "xilinx.com:signal:clock:1.0 clk CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of clk : signal is "XIL_INTERFACENAME clk, ASSOCIATED_BUSIF mon, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0";
  attribute x_interface_info of mon_tlast : signal is "xilinx.com:interface:axis:1.0 mon TLAST";
  attribute x_interface_info of mon_tready : signal is "xilinx.com:interface:axis:1.0 mon TREADY";
  attribute x_interface_info of mon_tvalid : signal is "xilinx.com:interface:axis:1.0 mon TVALID";
  attribute x_interface_parameter of mon_tvalid : signal is "XIL_INTERFACENAME mon, TDATA_NUM_BYTES 0, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0";
begin
  \^mon_tlast\ <= mon_tlast;
  \^mon_tready\ <= mon_tready;
  \^mon_tvalid\ <= mon_tvalid;
  last_op <= \^mon_tlast\;
  ready_op <= \^mon_tready\;
  valid_op <= \^mon_tvalid\;
end STRUCTURE;
