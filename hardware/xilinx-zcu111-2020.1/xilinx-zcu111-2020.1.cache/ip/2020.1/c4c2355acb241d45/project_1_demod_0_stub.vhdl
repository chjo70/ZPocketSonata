-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
-- Date        : Thu May 28 07:48:27 2020
-- Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_demod_0_stub.vhdl
-- Design      : project_1_demod_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu28dr-ffvg1517-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    ctrl_in_V_TVALID : in STD_LOGIC;
    ctrl_in_V_TREADY : out STD_LOGIC;
    ctrl_in_V_TDATA : in STD_LOGIC_VECTOR ( 63 downto 0 );
    chan_data_1_V_TVALID : in STD_LOGIC;
    chan_data_1_V_TREADY : out STD_LOGIC;
    chan_data_1_V_TDATA : in STD_LOGIC_VECTOR ( 39 downto 0 );
    chan_data_2_V_TVALID : in STD_LOGIC;
    chan_data_2_V_TREADY : out STD_LOGIC;
    chan_data_2_V_TDATA : in STD_LOGIC_VECTOR ( 39 downto 0 );
    chan_data_3_V_TVALID : in STD_LOGIC;
    chan_data_3_V_TREADY : out STD_LOGIC;
    chan_data_3_V_TDATA : in STD_LOGIC_VECTOR ( 39 downto 0 );
    chan_data_4_V_TVALID : in STD_LOGIC;
    chan_data_4_V_TREADY : out STD_LOGIC;
    chan_data_4_V_TDATA : in STD_LOGIC_VECTOR ( 39 downto 0 );
    soft_data_TVALID : out STD_LOGIC;
    soft_data_TREADY : in STD_LOGIC;
    soft_data_TDATA : out STD_LOGIC_VECTOR ( 191 downto 0 );
    soft_data_TLAST : out STD_LOGIC_VECTOR ( 0 to 0 );
    soft_data_TKEEP : out STD_LOGIC_VECTOR ( 23 downto 0 );
    hard_data_TVALID : out STD_LOGIC;
    hard_data_TREADY : in STD_LOGIC;
    hard_data_TDATA : out STD_LOGIC_VECTOR ( 127 downto 0 );
    hard_data_TLAST : out STD_LOGIC_VECTOR ( 0 to 0 )
  );

end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "ap_clk,ap_rst_n,ctrl_in_V_TVALID,ctrl_in_V_TREADY,ctrl_in_V_TDATA[63:0],chan_data_1_V_TVALID,chan_data_1_V_TREADY,chan_data_1_V_TDATA[39:0],chan_data_2_V_TVALID,chan_data_2_V_TREADY,chan_data_2_V_TDATA[39:0],chan_data_3_V_TVALID,chan_data_3_V_TREADY,chan_data_3_V_TDATA[39:0],chan_data_4_V_TVALID,chan_data_4_V_TREADY,chan_data_4_V_TDATA[39:0],soft_data_TVALID,soft_data_TREADY,soft_data_TDATA[191:0],soft_data_TLAST[0:0],soft_data_TKEEP[23:0],hard_data_TVALID,hard_data_TREADY,hard_data_TDATA[127:0],hard_data_TLAST[0:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "demod_4x,Vivado 2020.1";
begin
end;
