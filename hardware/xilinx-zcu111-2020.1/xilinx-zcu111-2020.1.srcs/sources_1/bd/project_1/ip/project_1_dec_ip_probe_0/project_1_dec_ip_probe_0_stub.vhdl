-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
-- Date        : Thu May 28 07:46:21 2020
-- Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
-- Command     : write_vhdl -force -mode synth_stub
--               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_dec_ip_probe_0/project_1_dec_ip_probe_0_stub.vhdl
-- Design      : project_1_dec_ip_probe_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu28dr-ffvg1517-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity project_1_dec_ip_probe_0 is
  Port ( 
    clk : in STD_LOGIC;
    mon_tvalid : in STD_LOGIC;
    mon_tready : in STD_LOGIC;
    mon_tlast : in STD_LOGIC;
    valid_op : out STD_LOGIC;
    ready_op : out STD_LOGIC;
    last_op : out STD_LOGIC
  );

end project_1_dec_ip_probe_0;

architecture stub of project_1_dec_ip_probe_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk,mon_tvalid,mon_tready,mon_tlast,valid_op,ready_op,last_op";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "axis_probe,Vivado 2020.1";
begin
end;
