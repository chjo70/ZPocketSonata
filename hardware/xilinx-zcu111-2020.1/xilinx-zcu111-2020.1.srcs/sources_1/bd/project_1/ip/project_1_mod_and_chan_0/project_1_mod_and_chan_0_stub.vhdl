-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
-- Date        : Thu May 28 07:47:30 2020
-- Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
-- Command     : write_vhdl -force -mode synth_stub
--               /tmp/tmp.rETG9Rbw1g/temp/hwflow/hwflow_project_1/project_1.srcs/sources_1/bd/project_1/ip/project_1_mod_and_chan_0/project_1_mod_and_chan_0_stub.vhdl
-- Design      : project_1_mod_and_chan_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu28dr-ffvg1517-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity project_1_mod_and_chan_0 is
  Port ( 
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    ctrl_in_V_TVALID : in STD_LOGIC;
    ctrl_in_V_TREADY : out STD_LOGIC;
    ctrl_in_V_TDATA : in STD_LOGIC_VECTOR ( 63 downto 0 );
    ctrl_out_V_TVALID : out STD_LOGIC;
    ctrl_out_V_TREADY : in STD_LOGIC;
    ctrl_out_V_TDATA : out STD_LOGIC_VECTOR ( 63 downto 0 );
    hard_data_V_V_TVALID : in STD_LOGIC;
    hard_data_V_V_TREADY : out STD_LOGIC;
    hard_data_V_V_TDATA : in STD_LOGIC_VECTOR ( 95 downto 0 );
    chan_data_1_V_TVALID : out STD_LOGIC;
    chan_data_1_V_TREADY : in STD_LOGIC;
    chan_data_1_V_TDATA : out STD_LOGIC_VECTOR ( 39 downto 0 );
    chan_data_2_V_TVALID : out STD_LOGIC;
    chan_data_2_V_TREADY : in STD_LOGIC;
    chan_data_2_V_TDATA : out STD_LOGIC_VECTOR ( 39 downto 0 );
    chan_data_3_V_TVALID : out STD_LOGIC;
    chan_data_3_V_TREADY : in STD_LOGIC;
    chan_data_3_V_TDATA : out STD_LOGIC_VECTOR ( 39 downto 0 );
    chan_data_4_V_TVALID : out STD_LOGIC;
    chan_data_4_V_TREADY : in STD_LOGIC;
    chan_data_4_V_TDATA : out STD_LOGIC_VECTOR ( 39 downto 0 )
  );

end project_1_mod_and_chan_0;

architecture stub of project_1_mod_and_chan_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "ap_clk,ap_rst_n,ctrl_in_V_TVALID,ctrl_in_V_TREADY,ctrl_in_V_TDATA[63:0],ctrl_out_V_TVALID,ctrl_out_V_TREADY,ctrl_out_V_TDATA[63:0],hard_data_V_V_TVALID,hard_data_V_V_TREADY,hard_data_V_V_TDATA[95:0],chan_data_1_V_TVALID,chan_data_1_V_TREADY,chan_data_1_V_TDATA[39:0],chan_data_2_V_TVALID,chan_data_2_V_TREADY,chan_data_2_V_TDATA[39:0],chan_data_3_V_TVALID,chan_data_3_V_TREADY,chan_data_3_V_TDATA[39:0],chan_data_4_V_TVALID,chan_data_4_V_TREADY,chan_data_4_V_TDATA[39:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "mod_and_chan_4x,Vivado 2020.1";
begin
end;
