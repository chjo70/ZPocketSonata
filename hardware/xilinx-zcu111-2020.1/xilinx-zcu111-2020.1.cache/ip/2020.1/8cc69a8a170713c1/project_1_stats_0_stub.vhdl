-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
-- Date        : Thu May 28 07:48:59 2020
-- Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_stats_0_stub.vhdl
-- Design      : project_1_stats_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu28dr-ffvg1517-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    s_axi_CNTRL_AWADDR : in STD_LOGIC_VECTOR ( 6 downto 0 );
    s_axi_CNTRL_AWVALID : in STD_LOGIC;
    s_axi_CNTRL_AWREADY : out STD_LOGIC;
    s_axi_CNTRL_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CNTRL_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_CNTRL_WVALID : in STD_LOGIC;
    s_axi_CNTRL_WREADY : out STD_LOGIC;
    s_axi_CNTRL_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_CNTRL_BVALID : out STD_LOGIC;
    s_axi_CNTRL_BREADY : in STD_LOGIC;
    s_axi_CNTRL_ARADDR : in STD_LOGIC_VECTOR ( 6 downto 0 );
    s_axi_CNTRL_ARVALID : in STD_LOGIC;
    s_axi_CNTRL_ARREADY : out STD_LOGIC;
    s_axi_CNTRL_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CNTRL_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_CNTRL_RVALID : out STD_LOGIC;
    s_axi_CNTRL_RREADY : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    interrupt : out STD_LOGIC;
    cntrl_aclk : in STD_LOGIC;
    ap_rst_n_cntrl_aclk : in STD_LOGIC;
    src_data_V_V_TVALID : in STD_LOGIC;
    src_data_V_V_TREADY : out STD_LOGIC;
    src_data_V_V_TDATA : in STD_LOGIC_VECTOR ( 127 downto 0 );
    hard_data_TVALID : in STD_LOGIC;
    hard_data_TREADY : out STD_LOGIC;
    hard_data_TDATA : in STD_LOGIC_VECTOR ( 127 downto 0 );
    hard_data_TLAST : in STD_LOGIC_VECTOR ( 0 to 0 );
    error_data_TVALID : in STD_LOGIC;
    error_data_TREADY : out STD_LOGIC;
    error_data_TDATA : in STD_LOGIC_VECTOR ( 127 downto 0 );
    error_data_TLAST : in STD_LOGIC_VECTOR ( 0 to 0 );
    fe_status_V_V_TVALID : in STD_LOGIC;
    fe_status_V_V_TREADY : out STD_LOGIC;
    fe_status_V_V_TDATA : in STD_LOGIC_VECTOR ( 39 downto 0 )
  );

end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "s_axi_CNTRL_AWADDR[6:0],s_axi_CNTRL_AWVALID,s_axi_CNTRL_AWREADY,s_axi_CNTRL_WDATA[31:0],s_axi_CNTRL_WSTRB[3:0],s_axi_CNTRL_WVALID,s_axi_CNTRL_WREADY,s_axi_CNTRL_BRESP[1:0],s_axi_CNTRL_BVALID,s_axi_CNTRL_BREADY,s_axi_CNTRL_ARADDR[6:0],s_axi_CNTRL_ARVALID,s_axi_CNTRL_ARREADY,s_axi_CNTRL_RDATA[31:0],s_axi_CNTRL_RRESP[1:0],s_axi_CNTRL_RVALID,s_axi_CNTRL_RREADY,ap_clk,ap_rst_n,interrupt,cntrl_aclk,ap_rst_n_cntrl_aclk,src_data_V_V_TVALID,src_data_V_V_TREADY,src_data_V_V_TDATA[127:0],hard_data_TVALID,hard_data_TREADY,hard_data_TDATA[127:0],hard_data_TLAST[0:0],error_data_TVALID,error_data_TREADY,error_data_TDATA[127:0],error_data_TLAST[0:0],fe_status_V_V_TVALID,fe_status_V_V_TREADY,fe_status_V_V_TDATA[39:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "stats_top,Vivado 2020.1";
begin
end;
