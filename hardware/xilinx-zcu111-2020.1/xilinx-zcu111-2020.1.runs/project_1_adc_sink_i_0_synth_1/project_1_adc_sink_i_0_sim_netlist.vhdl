-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
-- Date        : Thu May 28 07:48:56 2020
-- Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ project_1_adc_sink_i_0_sim_netlist.vhdl
-- Design      : project_1_adc_sink_i_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu28dr-ffvg1517-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc_exdes_cfg is
  port (
    enable : out STD_LOGIC;
    timeout_enable : out STD_LOGIC;
    enable_reg_0 : out STD_LOGIC;
    \timeout_value_reg[11]_0\ : out STD_LOGIC_VECTOR ( 11 downto 0 );
    p_0_in : in STD_LOGIC;
    enable_reg_1 : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    timeout_enable_reg_0 : in STD_LOGIC;
    done_flag : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 1 downto 0 );
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wdata : in STD_LOGIC_VECTOR ( 11 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc_exdes_cfg;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc_exdes_cfg is
  signal \^enable\ : STD_LOGIC;
begin
  enable <= \^enable\;
done_flag_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"88A8"
    )
        port map (
      I0 => \^enable\,
      I1 => done_flag,
      I2 => Q(0),
      I3 => Q(1),
      O => enable_reg_0
    );
enable_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => enable_reg_1,
      Q => \^enable\,
      R => p_0_in
    );
timeout_enable_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => timeout_enable_reg_0,
      Q => timeout_enable,
      R => p_0_in
    );
\timeout_value_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(0),
      Q => \timeout_value_reg[11]_0\(0),
      R => p_0_in
    );
\timeout_value_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(10),
      Q => \timeout_value_reg[11]_0\(10),
      R => p_0_in
    );
\timeout_value_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(11),
      Q => \timeout_value_reg[11]_0\(11),
      R => p_0_in
    );
\timeout_value_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(1),
      Q => \timeout_value_reg[11]_0\(1),
      R => p_0_in
    );
\timeout_value_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(2),
      Q => \timeout_value_reg[11]_0\(2),
      R => p_0_in
    );
\timeout_value_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(3),
      Q => \timeout_value_reg[11]_0\(3),
      R => p_0_in
    );
\timeout_value_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(4),
      Q => \timeout_value_reg[11]_0\(4),
      R => p_0_in
    );
\timeout_value_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(5),
      Q => \timeout_value_reg[11]_0\(5),
      R => p_0_in
    );
\timeout_value_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(6),
      Q => \timeout_value_reg[11]_0\(6),
      R => p_0_in
    );
\timeout_value_reg[7]\: unisim.vcomponents.FDSE
    generic map(
      INIT => '1'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(7),
      Q => \timeout_value_reg[11]_0\(7),
      S => p_0_in
    );
\timeout_value_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(8),
      Q => \timeout_value_reg[11]_0\(8),
      R => p_0_in
    );
\timeout_value_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(9),
      Q => \timeout_value_reg[11]_0\(9),
      R => p_0_in
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_axi is
  port (
    adc_ds_slv_rden : out STD_LOGIC;
    adc2axi_map_wready : out STD_LOGIC;
    adc_ds_axi_map_wready : out STD_LOGIC;
    adc0axi_map_wready : out STD_LOGIC;
    adc1axi_map_wready : out STD_LOGIC;
    adc3axi_map_wready : out STD_LOGIC;
    axi_wr_access_reg_0 : out STD_LOGIC;
    axi_arready_reg_0 : out STD_LOGIC;
    adc0slv_rden : out STD_LOGIC;
    adc1slv_rden : out STD_LOGIC;
    adc2slv_rden : out STD_LOGIC;
    adc3slv_rden : out STD_LOGIC;
    axi_rvalid_reg_0 : out STD_LOGIC;
    axi_bvalid_reg_0 : out STD_LOGIC;
    axi_awready_reg_0 : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 0 to 0 );
    Q : out STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_addr_reg[11]_0\ : out STD_LOGIC_VECTOR ( 9 downto 0 );
    \slv_addr_reg[2]_0\ : out STD_LOGIC;
    \slv_addr_reg[2]_1\ : out STD_LOGIC;
    s00_tdata_54_sp_1 : out STD_LOGIC;
    s00_tdata_53_sp_1 : out STD_LOGIC;
    s00_tdata_52_sp_1 : out STD_LOGIC;
    s00_tdata_50_sp_1 : out STD_LOGIC;
    \slv_addr_reg[5]_0\ : out STD_LOGIC;
    \slv_addr_reg[5]_1\ : out STD_LOGIC;
    \slv_addr_reg[8]_0\ : out STD_LOGIC;
    \slv_rd_addr_reg[5]_0\ : out STD_LOGIC;
    \slv_addr_reg[2]_2\ : out STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_addr_reg[2]_3\ : out STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_addr_reg[2]_4\ : out STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_addr_reg[6]_0\ : out STD_LOGIC;
    \slv_addr_reg[8]_1\ : out STD_LOGIC;
    \slv_addr_reg[3]_0\ : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_addr_reg[8]_2\ : out STD_LOGIC;
    \slv_addr_reg[6]_1\ : out STD_LOGIC;
    \slv_addr_reg[6]_2\ : out STD_LOGIC;
    \slv_addr_reg[6]_3\ : out STD_LOGIC;
    \slv_addr_reg[2]_5\ : out STD_LOGIC;
    \slv_addr_reg[3]_1\ : out STD_LOGIC;
    \slv_addr_reg[5]_2\ : out STD_LOGIC;
    \slv_addr_reg[2]_6\ : out STD_LOGIC;
    \slv_addr_reg[6]_4\ : out STD_LOGIC;
    \slv_addr_reg[3]_2\ : out STD_LOGIC;
    \slv_addr_reg[5]_3\ : out STD_LOGIC;
    \slv_addr_reg[4]_0\ : out STD_LOGIC_VECTOR ( 5 downto 0 );
    \slv_addr_reg[6]_5\ : out STD_LOGIC;
    \slv_addr_reg[4]_1\ : out STD_LOGIC;
    \slv_addr_reg[2]_7\ : out STD_LOGIC;
    \slv_addr_reg[3]_3\ : out STD_LOGIC;
    slv_rden_r_reg : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_addr_reg[2]_8\ : out STD_LOGIC;
    \slv_addr_reg[2]_9\ : out STD_LOGIC;
    \slv_addr_reg[2]_10\ : out STD_LOGIC;
    \slv_addr_reg[2]_11\ : out STD_LOGIC;
    s_axi_wdata_0_sp_1 : out STD_LOGIC;
    \s_axi_wdata[0]_0\ : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 15 downto 0 );
    s_axi_aclk : in STD_LOGIC;
    p_0_in : in STD_LOGIC;
    s_axi_arvalid : in STD_LOGIC;
    s_axi_awvalid : in STD_LOGIC;
    \axi_rdata_reg[9]_0\ : in STD_LOGIC;
    \axi_rdata_reg[10]_0\ : in STD_LOGIC;
    \axi_rdata_reg[11]_0\ : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    \slv_rdata_reg[7]\ : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \slv_rdata_reg[7]_0\ : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \slv_rdata_reg[7]_1\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \slv_rdata_reg[7]_2\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \slv_rdata_reg[7]_3\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \slv_rdata_reg[7]_4\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \slv_rdata_reg[7]_5\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \slv_rdata_reg[7]_6\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \slv_rdata_reg[7]_7\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \slv_rdata_reg[7]_8\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s00_tdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    \slv_rdata_reg[7]_9\ : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \slv_rdata_reg[7]_10\ : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    \axi_rdata_reg[11]_1\ : in STD_LOGIC_VECTOR ( 11 downto 0 );
    \axi_rdata_reg[0]_0\ : in STD_LOGIC;
    dest_out : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 0 to 0 );
    \axi_rdata_reg[8]_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    adc2slv_rden_reg_0 : in STD_LOGIC;
    adc2slv_rden_reg_1 : in STD_LOGIC;
    slv_wren_done_pulse : in STD_LOGIC;
    slv_rden_r : in STD_LOGIC;
    slv_rdata : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s_axi_rready : in STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    timeout_enable : in STD_LOGIC;
    \slv_rdata_reg[7]_11\ : in STD_LOGIC;
    \slv_rdata_reg[6]\ : in STD_LOGIC;
    \slv_rdata_reg[5]\ : in STD_LOGIC;
    \slv_rdata_reg[4]\ : in STD_LOGIC;
    \slv_rdata_reg[7]_12\ : in STD_LOGIC;
    \slv_rdata_reg[6]_0\ : in STD_LOGIC;
    \slv_rdata_reg[5]_0\ : in STD_LOGIC;
    \slv_rdata_reg[4]_0\ : in STD_LOGIC;
    \slv_rdata_reg[7]_13\ : in STD_LOGIC;
    \slv_rdata_reg[6]_1\ : in STD_LOGIC;
    \slv_rdata_reg[5]_1\ : in STD_LOGIC;
    \slv_rdata_reg[4]_1\ : in STD_LOGIC;
    \slv_rdata_reg[3]\ : in STD_LOGIC;
    \slv_rdata_reg[3]_0\ : in STD_LOGIC;
    \axi_bresp_reg[1]_0\ : in STD_LOGIC;
    \axi_bresp_reg[1]_1\ : in STD_LOGIC;
    \slv_rdata_reg[1]\ : in STD_LOGIC;
    \slv_rdata_reg[1]_0\ : in STD_LOGIC;
    \slv_rdata_reg[1]_1\ : in STD_LOGIC;
    \slv_rdata_reg[1]_2\ : in STD_LOGIC;
    \slv_rdata_reg[0]\ : in STD_LOGIC;
    \slv_rdata_reg[0]_0\ : in STD_LOGIC;
    \slv_rdata_reg[0]_1\ : in STD_LOGIC;
    \slv_rdata_reg[0]_2\ : in STD_LOGIC;
    \slv_rdata_reg[1]_3\ : in STD_LOGIC;
    \slv_rdata_reg[1]_4\ : in STD_LOGIC;
    \slv_rdata_reg[1]_5\ : in STD_LOGIC;
    \slv_rdata_reg[1]_6\ : in STD_LOGIC;
    \slv_rdata_reg[0]_3\ : in STD_LOGIC;
    \slv_rdata_reg[0]_4\ : in STD_LOGIC;
    \slv_rdata_reg[0]_5\ : in STD_LOGIC;
    \slv_rdata_reg[0]_6\ : in STD_LOGIC;
    \slv_rdata_reg[1]_7\ : in STD_LOGIC;
    \slv_rdata_reg[1]_8\ : in STD_LOGIC;
    \slv_rdata_reg[1]_9\ : in STD_LOGIC;
    \slv_rdata_reg[1]_10\ : in STD_LOGIC;
    \slv_rdata_reg[0]_7\ : in STD_LOGIC;
    \slv_rdata_reg[0]_8\ : in STD_LOGIC;
    \slv_rdata_reg[0]_9\ : in STD_LOGIC;
    \slv_rdata_reg[0]_10\ : in STD_LOGIC;
    \slv_rdata_reg[8]\ : in STD_LOGIC;
    \slv_rdata_reg[8]_0\ : in STD_LOGIC;
    \slv_rdata_reg[8]_1\ : in STD_LOGIC;
    \slv_rdata_reg[1]_11\ : in STD_LOGIC;
    \slv_rdata_reg[9]\ : in STD_LOGIC;
    \slv_rdata_reg[10]\ : in STD_LOGIC;
    \slv_rdata_reg[11]\ : in STD_LOGIC;
    \slv_rdata_reg[2]\ : in STD_LOGIC;
    \slv_rdata_reg[2]_0\ : in STD_LOGIC;
    \slv_rdata_reg[2]_1\ : in STD_LOGIC;
    \slv_rdata_reg[2]_2\ : in STD_LOGIC;
    \slv_rdata_reg[2]_3\ : in STD_LOGIC;
    \slv_rdata_reg[2]_4\ : in STD_LOGIC;
    \slv_rdata_reg[3]_1\ : in STD_LOGIC;
    \slv_rdata_reg[0]_11\ : in STD_LOGIC;
    \slv_rdata_reg[1]_12\ : in STD_LOGIC;
    error_flag : in STD_LOGIC;
    enable : in STD_LOGIC;
    \slv_rdata_reg[3]_2\ : in STD_LOGIC_VECTOR ( 2 downto 0 );
    \slv_rdata_reg[3]_3\ : in STD_LOGIC_VECTOR ( 2 downto 0 );
    \slv_rdata_reg[3]_4\ : in STD_LOGIC_VECTOR ( 2 downto 0 );
    \slv_rdata_reg[1]_13\ : in STD_LOGIC;
    \slv_rdata_reg[0]_12\ : in STD_LOGIC;
    \slv_rdata_reg[3]_5\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_rdata_reg[3]_6\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_rdata[3]_i_5_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_rdata[3]_i_5_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_rdata_reg[8]_2\ : in STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_rdata_reg[2]_5\ : in STD_LOGIC;
    \slv_rdata_reg[3]_7\ : in STD_LOGIC;
    \slv_rdata_reg[4]_2\ : in STD_LOGIC;
    \slv_rdata_reg[5]_2\ : in STD_LOGIC;
    \slv_rdata_reg[6]_2\ : in STD_LOGIC;
    \slv_rdata_reg[7]_14\ : in STD_LOGIC;
    \slv_rdata_reg[0]_13\ : in STD_LOGIC;
    \slv_rdata_reg[3]_8\ : in STD_LOGIC_VECTOR ( 3 downto 0 );
    \slv_rdata_reg[1]_14\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_rdata_reg[1]_15\ : in STD_LOGIC;
    \slv_rdata_reg[2]_6\ : in STD_LOGIC;
    \slv_rdata_reg[3]_9\ : in STD_LOGIC;
    \slv_rdata_reg[4]_3\ : in STD_LOGIC;
    \slv_rdata_reg[5]_3\ : in STD_LOGIC;
    \slv_rdata_reg[6]_3\ : in STD_LOGIC;
    \slv_rdata_reg[7]_15\ : in STD_LOGIC;
    slv_rden_r_0 : in STD_LOGIC;
    slv_rden_r_1 : in STD_LOGIC;
    slv_rden_r_2 : in STD_LOGIC;
    \axi_rdata[8]_i_2_0\ : in STD_LOGIC_VECTOR ( 8 downto 0 );
    \axi_rdata[8]_i_2_1\ : in STD_LOGIC_VECTOR ( 8 downto 0 );
    \axi_rdata_reg[9]_1\ : in STD_LOGIC;
    \axi_rdata_reg[9]_2\ : in STD_LOGIC;
    \axi_rdata_reg[10]_1\ : in STD_LOGIC;
    \axi_rdata_reg[10]_2\ : in STD_LOGIC;
    \axi_rdata_reg[11]_2\ : in STD_LOGIC;
    \axi_rdata_reg[11]_3\ : in STD_LOGIC;
    s00_ds_status : in STD_LOGIC;
    \slv_rdata_reg[8]_3\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_rdata[8]_i_3_0\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_rdata[8]_i_3_1\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wdata : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_axi;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_axi is
  signal \^q\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \adc01_ds_control_0[1]_i_3_n_0\ : STD_LOGIC;
  signal \adc01_ds_enable_0[7]_i_3_n_0\ : STD_LOGIC;
  signal \adc01_ds_enable_0[7]_i_4_n_0\ : STD_LOGIC;
  signal \adc01_ds_type_0[3]_i_3_n_0\ : STD_LOGIC;
  signal \adc02_ds_enable_0[7]_i_3_n_0\ : STD_LOGIC;
  signal \adc02_ds_inc_0[11]_i_3_n_0\ : STD_LOGIC;
  signal \adc02_ds_inc_0[11]_i_4_n_0\ : STD_LOGIC;
  signal \adc02_ds_type_0[3]_i_3_n_0\ : STD_LOGIC;
  signal \adc03_ds_control_0[1]_i_3_n_0\ : STD_LOGIC;
  signal \adc03_ds_enable_0[7]_i_3_n_0\ : STD_LOGIC;
  signal \^adc0axi_map_wready\ : STD_LOGIC;
  signal adc0axi_map_wready0 : STD_LOGIC;
  signal \^adc0slv_rden\ : STD_LOGIC;
  signal adc0slv_rden_i_1_n_0 : STD_LOGIC;
  signal \^adc1axi_map_wready\ : STD_LOGIC;
  signal adc1axi_map_wready0 : STD_LOGIC;
  signal \^adc1slv_rden\ : STD_LOGIC;
  signal adc1slv_rden_i_1_n_0 : STD_LOGIC;
  signal \^adc2axi_map_wready\ : STD_LOGIC;
  signal adc2axi_map_wready0 : STD_LOGIC;
  signal \^adc2slv_rden\ : STD_LOGIC;
  signal adc2slv_rden_i_1_n_0 : STD_LOGIC;
  signal \^adc3axi_map_wready\ : STD_LOGIC;
  signal adc3axi_map_wready0 : STD_LOGIC;
  signal adc3axi_map_wready_i_2_n_0 : STD_LOGIC;
  signal \^adc3slv_rden\ : STD_LOGIC;
  signal adc3slv_rden_i_1_n_0 : STD_LOGIC;
  signal \^adc_ds_axi_map_wready\ : STD_LOGIC;
  signal adc_ds_axi_map_wready0 : STD_LOGIC;
  signal adc_ds_slv_rden_i_1_n_0 : STD_LOGIC;
  signal adc_ds_slv_rden_i_3_n_0 : STD_LOGIC;
  signal axi_arready0 : STD_LOGIC;
  signal \^axi_arready_reg_0\ : STD_LOGIC;
  signal axi_awready19_in : STD_LOGIC;
  signal axi_awready_i_2_n_0 : STD_LOGIC;
  signal \^axi_awready_reg_0\ : STD_LOGIC;
  signal \axi_bresp[1]_i_1_n_0\ : STD_LOGIC;
  signal \axi_bresp[1]_i_5_n_0\ : STD_LOGIC;
  signal axi_bvalid0 : STD_LOGIC;
  signal axi_bvalid_i_1_n_0 : STD_LOGIC;
  signal \^axi_bvalid_reg_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_6_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_7_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_8_n_0\ : STD_LOGIC;
  signal \axi_rdata[0]_i_9_n_0\ : STD_LOGIC;
  signal \axi_rdata[10]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[10]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[10]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_5_n_0\ : STD_LOGIC;
  signal \axi_rdata[11]_i_6_n_0\ : STD_LOGIC;
  signal \axi_rdata[12]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[13]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[14]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[15]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[1]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[1]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[1]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[2]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[2]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[2]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[3]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[3]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[3]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[4]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[4]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[4]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[5]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[5]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[5]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[6]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[6]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[6]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[7]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[7]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[7]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rdata[8]_i_4_n_0\ : STD_LOGIC;
  signal \axi_rdata[9]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rdata[9]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rdata[9]_i_3_n_0\ : STD_LOGIC;
  signal \axi_rresp[1]_i_1_n_0\ : STD_LOGIC;
  signal \axi_rresp[1]_i_2_n_0\ : STD_LOGIC;
  signal \axi_rresp[1]_i_5_n_0\ : STD_LOGIC;
  signal axi_rvalid_i_1_n_0 : STD_LOGIC;
  signal \^axi_rvalid_reg_0\ : STD_LOGIC;
  signal axi_wr_access0 : STD_LOGIC;
  signal \^axi_wr_access_reg_0\ : STD_LOGIC;
  signal enable_i_2_n_0 : STD_LOGIC;
  signal load_timeout_timer0 : STD_LOGIC;
  signal p_2_in : STD_LOGIC_VECTOR ( 12 downto 0 );
  signal read_in_progress : STD_LOGIC;
  signal read_in_progress_i_1_n_0 : STD_LOGIC;
  signal read_in_progress_i_2_n_0 : STD_LOGIC;
  signal s00_tdata_50_sn_1 : STD_LOGIC;
  signal s00_tdata_52_sn_1 : STD_LOGIC;
  signal s00_tdata_53_sn_1 : STD_LOGIC;
  signal s00_tdata_54_sn_1 : STD_LOGIC;
  signal \^s_axi_bresp\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \^s_axi_rresp\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal s_axi_wdata_0_sn_1 : STD_LOGIC;
  signal \slv_addr[10]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[11]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[2]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[3]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[4]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[5]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[6]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[7]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[8]_i_1_n_0\ : STD_LOGIC;
  signal \slv_addr[9]_i_1_n_0\ : STD_LOGIC;
  signal \^slv_addr_reg[11]_0\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \^slv_addr_reg[3]_3\ : STD_LOGIC;
  signal \^slv_addr_reg[5]_3\ : STD_LOGIC;
  signal \^slv_addr_reg[6]_5\ : STD_LOGIC;
  signal \^slv_addr_reg[8]_0\ : STD_LOGIC;
  signal \slv_rd_addr[0]_i_1_n_0\ : STD_LOGIC;
  signal \slv_rd_addr[1]_i_1_n_0\ : STD_LOGIC;
  signal \slv_rd_addr[2]_i_1_n_0\ : STD_LOGIC;
  signal \slv_rd_addr[3]_i_1_n_0\ : STD_LOGIC;
  signal \slv_rd_addr[4]_i_1_n_0\ : STD_LOGIC;
  signal \slv_rd_addr[5]_i_1_n_0\ : STD_LOGIC;
  signal \slv_rd_addr[5]_i_2_n_0\ : STD_LOGIC;
  signal \^slv_rd_addr_reg[5]_0\ : STD_LOGIC;
  signal \slv_rd_addr_reg_n_0_[1]\ : STD_LOGIC;
  signal \slv_rd_addr_reg_n_0_[2]\ : STD_LOGIC;
  signal \slv_rd_addr_reg_n_0_[3]\ : STD_LOGIC;
  signal \slv_rd_addr_reg_n_0_[4]\ : STD_LOGIC;
  signal \slv_rd_addr_reg_n_0_[5]\ : STD_LOGIC;
  signal \slv_rdata[0]_i_11_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_2__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_2__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_2__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata[0]_i_9_n_0\ : STD_LOGIC;
  signal \slv_rdata[10]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[10]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata[10]_i_8_n_0\ : STD_LOGIC;
  signal \slv_rdata[10]_i_9_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_10_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_11_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_12_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_9_n_0\ : STD_LOGIC;
  signal \slv_rdata[12]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[12]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[13]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[13]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[14]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[14]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[15]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[15]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_10_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_13_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_2__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_2__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_5__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata[1]_i_9_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_2__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_2__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_2__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_5__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_5__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_5__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_6__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[2]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_10_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_2__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_2__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_3__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_4__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_5__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_6__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_8__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_8_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_9_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_3__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_3__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_3__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_4__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_4__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_4__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[4]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_3__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_3__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_3__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_4__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_4__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_4__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[5]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_3__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_3__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_3__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_4__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_4__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_4__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[6]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_10_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_12_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_3__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_3__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_3__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_4__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_4__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_4__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_8_n_0\ : STD_LOGIC;
  signal \slv_rdata[8]_i_10_n_0\ : STD_LOGIC;
  signal \slv_rdata[8]_i_11_n_0\ : STD_LOGIC;
  signal \slv_rdata[8]_i_3_n_0\ : STD_LOGIC;
  signal \slv_rdata[8]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata[8]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata[8]_i_8_n_0\ : STD_LOGIC;
  signal \slv_rdata[8]_i_9_n_0\ : STD_LOGIC;
  signal \slv_rdata[9]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata[9]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata[9]_i_8_n_0\ : STD_LOGIC;
  signal \slv_rdata[9]_i_9_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[10]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[10]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[10]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[11]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[11]_i_7_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[11]_i_8_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[8]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[8]_i_5_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[8]_i_6_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[9]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[9]_i_4_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg[9]_i_5_n_0\ : STD_LOGIC;
  signal slv_reg_rden : STD_LOGIC;
  signal slv_reg_rden0 : STD_LOGIC;
  signal slv_reg_rden_i_1_n_0 : STD_LOGIC;
  signal timeout : STD_LOGIC;
  signal timeout_enable_i_2_n_0 : STD_LOGIC;
  signal \timeout_timer_count[10]_i_2_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[12]_i_1_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[12]_i_2_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[12]_i_4_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[12]_i_5_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[12]_i_6_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[12]_i_7_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[12]_i_8_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[4]_i_2_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[5]_i_2_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[8]_i_2_n_0\ : STD_LOGIC;
  signal \timeout_timer_count[9]_i_2_n_0\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[0]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[10]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[11]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[1]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[2]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[3]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[4]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[5]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[6]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[7]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[8]\ : STD_LOGIC;
  signal \timeout_timer_count_reg_n_0_[9]\ : STD_LOGIC;
  signal \timeout_value[11]_i_2_n_0\ : STD_LOGIC;
  signal valid_waddr_i_1_n_0 : STD_LOGIC;
  signal valid_waddr_i_2_n_0 : STD_LOGIC;
  signal valid_waddr_i_3_n_0 : STD_LOGIC;
  signal valid_waddr_i_4_n_0 : STD_LOGIC;
  signal valid_waddr_reg_n_0 : STD_LOGIC;
  signal write_in_progress : STD_LOGIC;
  signal write_in_progress_i_1_n_0 : STD_LOGIC;
  signal write_in_progress_i_2_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of adc00_ds_pulse_control_0_i_2 : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of adc00_ds_pulse_control_0_i_4 : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \adc01_ds_control_0[1]_i_3\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \adc01_ds_enable_0[7]_i_3\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \adc01_ds_enable_0[7]_i_4\ : label is "soft_lutpair42";
  attribute SOFT_HLUTNM of \adc01_ds_type_0[3]_i_3\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \adc02_ds_enable_0[7]_i_3\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \adc02_ds_inc_0[11]_i_3\ : label is "soft_lutpair65";
  attribute SOFT_HLUTNM of \adc02_ds_inc_0[11]_i_4\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \adc03_ds_control_0[1]_i_2\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \adc03_ds_enable_0[7]_i_3\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of adc3axi_map_wready_i_2 : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of axi_awready_i_2 : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of \axi_rdata[0]_i_7\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \axi_rdata[0]_i_8\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \axi_rdata[0]_i_9\ : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of \axi_rdata[11]_i_3\ : label is "soft_lutpair41";
  attribute SOFT_HLUTNM of \axi_rdata[11]_i_4\ : label is "soft_lutpair48";
  attribute SOFT_HLUTNM of \axi_rdata[15]_i_2\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \axi_rdata[15]_i_4\ : label is "soft_lutpair64";
  attribute SOFT_HLUTNM of \axi_rdata[8]_i_3\ : label is "soft_lutpair61";
  attribute SOFT_HLUTNM of \axi_rdata[9]_i_3\ : label is "soft_lutpair40";
  attribute SOFT_HLUTNM of axi_rvalid_i_1 : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of read_in_progress_i_2 : label is "soft_lutpair54";
  attribute SOFT_HLUTNM of \slv_addr[2]_i_1\ : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of \slv_rdata[0]_i_9\ : label is "soft_lutpair43";
  attribute SOFT_HLUTNM of \slv_rdata[11]_i_3\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of \slv_rdata[11]_i_4\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \slv_rdata[1]_i_1\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \slv_rdata[1]_i_12\ : label is "soft_lutpair44";
  attribute SOFT_HLUTNM of \slv_rdata[1]_i_7\ : label is "soft_lutpair47";
  attribute SOFT_HLUTNM of \slv_rdata[2]_i_6\ : label is "soft_lutpair51";
  attribute SOFT_HLUTNM of \slv_rdata[3]_i_2__0\ : label is "soft_lutpair49";
  attribute SOFT_HLUTNM of \slv_rdata[3]_i_3\ : label is "soft_lutpair46";
  attribute SOFT_HLUTNM of \slv_rdata[3]_i_4__0\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of \slv_rdata[3]_i_6\ : label is "soft_lutpair45";
  attribute SOFT_HLUTNM of \slv_rdata[3]_i_8\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \slv_rdata[4]_i_4\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \slv_rdata[5]_i_4\ : label is "soft_lutpair69";
  attribute SOFT_HLUTNM of \slv_rdata[5]_i_6\ : label is "soft_lutpair58";
  attribute SOFT_HLUTNM of \slv_rdata[6]_i_4\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \slv_rdata[6]_i_6\ : label is "soft_lutpair57";
  attribute SOFT_HLUTNM of \slv_rdata[7]_i_10\ : label is "soft_lutpair66";
  attribute SOFT_HLUTNM of \slv_rdata[7]_i_3__0\ : label is "soft_lutpair59";
  attribute SOFT_HLUTNM of \slv_rdata[7]_i_5\ : label is "soft_lutpair68";
  attribute SOFT_HLUTNM of \slv_rdata[8]_i_4\ : label is "soft_lutpair50";
  attribute SOFT_HLUTNM of slv_reg_rden_i_1 : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \timeout_timer_count[0]_i_1\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \timeout_timer_count[10]_i_2\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of \timeout_timer_count[11]_i_1\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \timeout_timer_count[12]_i_3\ : label is "soft_lutpair63";
  attribute SOFT_HLUTNM of \timeout_timer_count[12]_i_9\ : label is "soft_lutpair56";
  attribute SOFT_HLUTNM of \timeout_timer_count[1]_i_1\ : label is "soft_lutpair62";
  attribute SOFT_HLUTNM of \timeout_timer_count[4]_i_2\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \timeout_timer_count[5]_i_2\ : label is "soft_lutpair53";
  attribute SOFT_HLUTNM of \timeout_timer_count[9]_i_2\ : label is "soft_lutpair52";
  attribute SOFT_HLUTNM of valid_waddr_i_2 : label is "soft_lutpair67";
  attribute SOFT_HLUTNM of valid_waddr_i_3 : label is "soft_lutpair60";
  attribute SOFT_HLUTNM of valid_waddr_i_4 : label is "soft_lutpair55";
  attribute SOFT_HLUTNM of write_in_progress_i_2 : label is "soft_lutpair67";
begin
  Q(0) <= \^q\(0);
  adc0axi_map_wready <= \^adc0axi_map_wready\;
  adc0slv_rden <= \^adc0slv_rden\;
  adc1axi_map_wready <= \^adc1axi_map_wready\;
  adc1slv_rden <= \^adc1slv_rden\;
  adc2axi_map_wready <= \^adc2axi_map_wready\;
  adc2slv_rden <= \^adc2slv_rden\;
  adc3axi_map_wready <= \^adc3axi_map_wready\;
  adc3slv_rden <= \^adc3slv_rden\;
  adc_ds_axi_map_wready <= \^adc_ds_axi_map_wready\;
  axi_arready_reg_0 <= \^axi_arready_reg_0\;
  axi_awready_reg_0 <= \^axi_awready_reg_0\;
  axi_bvalid_reg_0 <= \^axi_bvalid_reg_0\;
  axi_rvalid_reg_0 <= \^axi_rvalid_reg_0\;
  axi_wr_access_reg_0 <= \^axi_wr_access_reg_0\;
  s00_tdata_50_sp_1 <= s00_tdata_50_sn_1;
  s00_tdata_52_sp_1 <= s00_tdata_52_sn_1;
  s00_tdata_53_sp_1 <= s00_tdata_53_sn_1;
  s00_tdata_54_sp_1 <= s00_tdata_54_sn_1;
  s_axi_bresp(0) <= \^s_axi_bresp\(0);
  s_axi_rresp(0) <= \^s_axi_rresp\(0);
  s_axi_wdata_0_sp_1 <= s_axi_wdata_0_sn_1;
  \slv_addr_reg[11]_0\(9 downto 0) <= \^slv_addr_reg[11]_0\(9 downto 0);
  \slv_addr_reg[3]_3\ <= \^slv_addr_reg[3]_3\;
  \slv_addr_reg[5]_3\ <= \^slv_addr_reg[5]_3\;
  \slv_addr_reg[6]_5\ <= \^slv_addr_reg[6]_5\;
  \slv_addr_reg[8]_0\ <= \^slv_addr_reg[8]_0\;
  \slv_rd_addr_reg[5]_0\ <= \^slv_rd_addr_reg[5]_0\;
\adc00_ds_control_0[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000001000"
    )
        port map (
      I0 => \^slv_addr_reg[8]_0\,
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \^slv_addr_reg[11]_0\(0),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_addr_reg[6]_2\
    );
\adc00_ds_enable_0[0]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(3),
      I2 => \^slv_addr_reg[8]_0\,
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_addr_reg[6]_0\
    );
\adc00_ds_inc_0[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000100"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(3),
      I2 => \^slv_addr_reg[8]_0\,
      I3 => \^slv_addr_reg[11]_0\(0),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_addr_reg[6]_3\
    );
adc00_ds_pulse_control_0_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \^slv_addr_reg[11]_0\(5),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \^slv_addr_reg[11]_0\(8),
      I4 => \^slv_addr_reg[11]_0\(9),
      O => \^slv_addr_reg[8]_0\
    );
adc00_ds_pulse_control_0_i_4: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFEF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_addr_reg[2]_7\
    );
\adc00_ds_type_0[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000100000000"
    )
        port map (
      I0 => \^slv_addr_reg[8]_0\,
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \^slv_addr_reg[11]_0\(3),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_addr_reg[6]_1\
    );
\adc01_ds_control_0[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0040000000000000"
    )
        port map (
      I0 => \adc01_ds_enable_0[7]_i_4_n_0\,
      I1 => \adc01_ds_control_0[1]_i_3_n_0\,
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \^slv_addr_reg[11]_0\(3),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_addr_reg[8]_2\
    );
\adc01_ds_control_0[1]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(2),
      O => \adc01_ds_control_0[1]_i_3_n_0\
    );
\adc01_ds_enable_0[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000200"
    )
        port map (
      I0 => \adc01_ds_enable_0[7]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(0),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \adc01_ds_enable_0[7]_i_4_n_0\,
      O => \slv_addr_reg[2]_1\
    );
\adc01_ds_enable_0[7]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(1),
      I1 => \^slv_addr_reg[11]_0\(2),
      O => \adc01_ds_enable_0[7]_i_3_n_0\
    );
\adc01_ds_enable_0[7]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(9),
      I1 => \^slv_addr_reg[11]_0\(8),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \^slv_addr_reg[11]_0\(5),
      O => \adc01_ds_enable_0[7]_i_4_n_0\
    );
\adc01_ds_inc_0[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000020000000000"
    )
        port map (
      I0 => \slv_rdata[3]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \^slv_addr_reg[11]_0\(0),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \^slv_addr_reg[11]_0\(6),
      O => \slv_addr_reg[4]_1\
    );
\adc01_ds_type_0[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000200"
    )
        port map (
      I0 => \adc01_ds_type_0[3]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(0),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \adc01_ds_enable_0[7]_i_4_n_0\,
      O => \slv_addr_reg[2]_0\
    );
\adc01_ds_type_0[3]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(1),
      I1 => \^slv_addr_reg[11]_0\(2),
      O => \adc01_ds_type_0[3]_i_3_n_0\
    );
\adc02_ds_control_0[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000004000000000"
    )
        port map (
      I0 => \adc02_ds_enable_0[7]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(0),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \^slv_addr_reg[11]_0\(5),
      I5 => \adc01_ds_control_0[1]_i_3_n_0\,
      O => \slv_addr_reg[3]_2\
    );
\adc02_ds_enable_0[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000010000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(0),
      I2 => \^slv_addr_reg[11]_0\(5),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \adc01_ds_enable_0[7]_i_3_n_0\,
      I5 => \adc02_ds_enable_0[7]_i_3_n_0\,
      O => \slv_addr_reg[6]_4\
    );
\adc02_ds_enable_0[7]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFEF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(9),
      I1 => \^slv_addr_reg[11]_0\(8),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \^slv_addr_reg[11]_0\(3),
      O => \adc02_ds_enable_0[7]_i_3_n_0\
    );
\adc02_ds_inc_0[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000080"
    )
        port map (
      I0 => \adc02_ds_inc_0[11]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(0),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \^slv_addr_reg[11]_0\(1),
      I4 => \^slv_addr_reg[11]_0\(4),
      I5 => \adc02_ds_inc_0[11]_i_4_n_0\,
      O => \slv_addr_reg[2]_6\
    );
\adc02_ds_inc_0[11]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(9),
      I1 => \^slv_addr_reg[11]_0\(8),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(3),
      O => \adc02_ds_inc_0[11]_i_3_n_0\
    );
\adc02_ds_inc_0[11]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(5),
      I1 => \^slv_addr_reg[11]_0\(6),
      O => \adc02_ds_inc_0[11]_i_4_n_0\
    );
\adc02_ds_type_0[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000001000000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(3),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \axi_rdata[15]_i_4_n_0\,
      I3 => \^slv_addr_reg[11]_0\(7),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \adc02_ds_type_0[3]_i_3_n_0\,
      O => \slv_addr_reg[5]_2\
    );
\adc02_ds_type_0[3]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \^slv_addr_reg[11]_0\(5),
      I2 => \^slv_addr_reg[11]_0\(0),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \adc02_ds_type_0[3]_i_3_n_0\
    );
\adc03_ds_control_0[1]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000008"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(1),
      I1 => \^slv_addr_reg[11]_0\(0),
      I2 => \^slv_addr_reg[11]_0\(3),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => \adc03_ds_control_0[1]_i_3_n_0\,
      O => \slv_addr_reg[3]_1\
    );
\adc03_ds_control_0[1]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFEFFFFFFFFFFFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(5),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \^slv_addr_reg[11]_0\(8),
      I3 => \^slv_addr_reg[11]_0\(9),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \^slv_addr_reg[11]_0\(6),
      O => \adc03_ds_control_0[1]_i_3_n_0\
    );
\adc03_ds_enable_0[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000010000000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(1),
      I1 => \^slv_addr_reg[11]_0\(3),
      I2 => \slv_rdata[3]_i_2__0_n_0\,
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \adc03_ds_enable_0[7]_i_3_n_0\,
      O => \slv_addr_reg[3]_0\
    );
\adc03_ds_enable_0[7]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(9),
      I1 => \^slv_addr_reg[11]_0\(8),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(5),
      O => \adc03_ds_enable_0[7]_i_3_n_0\
    );
\adc03_ds_inc_0[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000400000000000"
    )
        port map (
      I0 => \adc03_ds_enable_0[7]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(0),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \adc01_ds_enable_0[7]_i_3_n_0\,
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \^slv_addr_reg[11]_0\(6),
      O => \slv_addr_reg[2]_5\
    );
\adc03_ds_type_0[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0400000000000000"
    )
        port map (
      I0 => \adc03_ds_enable_0[7]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(6),
      I2 => \^slv_addr_reg[11]_0\(3),
      I3 => \slv_rdata[3]_i_2__0_n_0\,
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_addr_reg[8]_1\
    );
adc0axi_map_wready_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => valid_waddr_reg_n_0,
      I1 => s_axi_wvalid,
      I2 => \axi_rdata[15]_i_2_n_0\,
      I3 => \^q\(0),
      I4 => \slv_rd_addr_reg_n_0_[1]\,
      I5 => \^adc0axi_map_wready\,
      O => adc0axi_map_wready0
    );
adc0axi_map_wready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => axi_awready19_in,
      D => adc0axi_map_wready0,
      Q => \^adc0axi_map_wready\,
      R => p_0_in
    );
adc0slv_rden_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000010000"
    )
        port map (
      I0 => s_axi_araddr(14),
      I1 => s_axi_araddr(13),
      I2 => s_axi_araddr(15),
      I3 => s_axi_araddr(11),
      I4 => s_axi_araddr(10),
      I5 => s_axi_araddr(12),
      O => adc0slv_rden_i_1_n_0
    );
adc0slv_rden_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => slv_reg_rden0,
      D => adc0slv_rden_i_1_n_0,
      Q => \^adc0slv_rden\,
      R => adc_ds_slv_rden_i_1_n_0
    );
adc1axi_map_wready_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000800000"
    )
        port map (
      I0 => valid_waddr_reg_n_0,
      I1 => s_axi_wvalid,
      I2 => \axi_rdata[15]_i_2_n_0\,
      I3 => \^q\(0),
      I4 => \slv_rd_addr_reg_n_0_[1]\,
      I5 => \^adc1axi_map_wready\,
      O => adc1axi_map_wready0
    );
adc1axi_map_wready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => axi_awready19_in,
      D => adc1axi_map_wready0,
      Q => \^adc1axi_map_wready\,
      R => p_0_in
    );
adc1slv_rden_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000010"
    )
        port map (
      I0 => s_axi_araddr(10),
      I1 => s_axi_araddr(12),
      I2 => s_axi_araddr(11),
      I3 => s_axi_araddr(14),
      I4 => s_axi_araddr(13),
      I5 => s_axi_araddr(15),
      O => adc1slv_rden_i_1_n_0
    );
adc1slv_rden_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => slv_reg_rden0,
      D => adc1slv_rden_i_1_n_0,
      Q => \^adc1slv_rden\,
      R => adc_ds_slv_rden_i_1_n_0
    );
adc2axi_map_wready_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => valid_waddr_reg_n_0,
      I1 => s_axi_wvalid,
      I2 => \axi_rdata[15]_i_2_n_0\,
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => \^q\(0),
      I5 => \^adc2axi_map_wready\,
      O => adc2axi_map_wready0
    );
adc2axi_map_wready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => axi_awready19_in,
      D => adc2axi_map_wready0,
      Q => \^adc2axi_map_wready\,
      R => p_0_in
    );
adc2slv_rden_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000020"
    )
        port map (
      I0 => s_axi_araddr(10),
      I1 => s_axi_araddr(12),
      I2 => s_axi_araddr(11),
      I3 => s_axi_araddr(14),
      I4 => s_axi_araddr(13),
      I5 => s_axi_araddr(15),
      O => adc2slv_rden_i_1_n_0
    );
adc2slv_rden_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => slv_reg_rden0,
      D => adc2slv_rden_i_1_n_0,
      Q => \^adc2slv_rden\,
      R => adc_ds_slv_rden_i_1_n_0
    );
adc3axi_map_wready_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0400000000000000"
    )
        port map (
      I0 => adc3axi_map_wready_i_2_n_0,
      I1 => \slv_rd_addr_reg_n_0_[2]\,
      I2 => \^adc3axi_map_wready\,
      I3 => s_axi_wvalid,
      I4 => valid_waddr_reg_n_0,
      I5 => \axi_rdata[8]_i_3_n_0\,
      O => adc3axi_map_wready0
    );
adc3axi_map_wready_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[1]\,
      I1 => \^q\(0),
      O => adc3axi_map_wready_i_2_n_0
    );
adc3axi_map_wready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => axi_awready19_in,
      D => adc3axi_map_wready0,
      Q => \^adc3axi_map_wready\,
      R => p_0_in
    );
adc3slv_rden_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000002"
    )
        port map (
      I0 => s_axi_araddr(12),
      I1 => s_axi_araddr(11),
      I2 => s_axi_araddr(15),
      I3 => s_axi_araddr(13),
      I4 => s_axi_araddr(14),
      I5 => s_axi_araddr(10),
      O => adc3slv_rden_i_1_n_0
    );
adc3slv_rden_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => slv_reg_rden0,
      D => adc3slv_rden_i_1_n_0,
      Q => \^adc3slv_rden\,
      R => adc_ds_slv_rden_i_1_n_0
    );
adc_ds_axi_map_wready_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000080"
    )
        port map (
      I0 => valid_waddr_reg_n_0,
      I1 => s_axi_wvalid,
      I2 => \axi_rdata[15]_i_2_n_0\,
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => \^q\(0),
      I5 => \^adc_ds_axi_map_wready\,
      O => adc_ds_axi_map_wready0
    );
adc_ds_axi_map_wready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => axi_awready19_in,
      D => adc_ds_axi_map_wready0,
      Q => \^adc_ds_axi_map_wready\,
      R => p_0_in
    );
adc_ds_slv_rden_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F700FFFF"
    )
        port map (
      I0 => \^axi_arready_reg_0\,
      I1 => s_axi_arvalid,
      I2 => \^axi_rvalid_reg_0\,
      I3 => \axi_rresp[1]_i_2_n_0\,
      I4 => s_axi_aresetn,
      O => adc_ds_slv_rden_i_1_n_0
    );
adc_ds_slv_rden_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \^axi_arready_reg_0\,
      I1 => s_axi_arvalid,
      I2 => \^axi_rvalid_reg_0\,
      O => slv_reg_rden0
    );
adc_ds_slv_rden_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => s_axi_araddr(12),
      I1 => s_axi_araddr(11),
      I2 => s_axi_araddr(15),
      I3 => s_axi_araddr(13),
      I4 => s_axi_araddr(14),
      I5 => s_axi_araddr(10),
      O => adc_ds_slv_rden_i_3_n_0
    );
adc_ds_slv_rden_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => slv_reg_rden0,
      D => adc_ds_slv_rden_i_3_n_0,
      Q => adc_ds_slv_rden,
      R => adc_ds_slv_rden_i_1_n_0
    );
axi_arready_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0004"
    )
        port map (
      I0 => read_in_progress,
      I1 => s_axi_arvalid,
      I2 => write_in_progress,
      I3 => \^axi_arready_reg_0\,
      O => axi_arready0
    );
axi_arready_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_arready0,
      Q => \^axi_arready_reg_0\,
      R => p_0_in
    );
axi_awready_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFF00004"
    )
        port map (
      I0 => valid_waddr_reg_n_0,
      I1 => s_axi_awvalid,
      I2 => read_in_progress,
      I3 => s_axi_arvalid,
      I4 => \^axi_awready_reg_0\,
      O => axi_awready_i_2_n_0
    );
axi_awready_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_awready_i_2_n_0,
      Q => \^axi_awready_reg_0\,
      R => p_0_in
    );
\axi_bresp[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8BBB000088880000"
    )
        port map (
      I0 => timeout,
      I1 => axi_bvalid0,
      I2 => \^axi_bvalid_reg_0\,
      I3 => s_axi_bready,
      I4 => s_axi_aresetn,
      I5 => \^s_axi_bresp\(0),
      O => \axi_bresp[1]_i_1_n_0\
    );
\axi_bresp[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFF454545"
    )
        port map (
      I0 => \^axi_bvalid_reg_0\,
      I1 => \axi_bresp_reg[1]_0\,
      I2 => \axi_bresp_reg[1]_1\,
      I3 => timeout,
      I4 => write_in_progress,
      I5 => \axi_bresp[1]_i_5_n_0\,
      O => axi_bvalid0
    );
\axi_bresp[1]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000100000000"
    )
        port map (
      I0 => \^adc3axi_map_wready\,
      I1 => \^adc1axi_map_wready\,
      I2 => \^adc0axi_map_wready\,
      I3 => \^adc2axi_map_wready\,
      I4 => \^adc_ds_axi_map_wready\,
      I5 => \^axi_wr_access_reg_0\,
      O => \axi_bresp[1]_i_5_n_0\
    );
\axi_bresp_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \axi_bresp[1]_i_1_n_0\,
      Q => \^s_axi_bresp\(0),
      R => '0'
    );
axi_bvalid_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"F4"
    )
        port map (
      I0 => s_axi_bready,
      I1 => \^axi_bvalid_reg_0\,
      I2 => axi_bvalid0,
      O => axi_bvalid_i_1_n_0
    );
axi_bvalid_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_bvalid_i_1_n_0,
      Q => \^axi_bvalid_reg_0\,
      R => p_0_in
    );
\axi_rdata[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFAAABAAAAAAAA"
    )
        port map (
      I0 => \axi_rdata_reg[0]_0\,
      I1 => \axi_rdata[0]_i_3_n_0\,
      I2 => \axi_rdata[0]_i_4_n_0\,
      I3 => \axi_rdata[0]_i_5_n_0\,
      I4 => \axi_rdata[0]_i_6_n_0\,
      I5 => \axi_rdata[15]_i_2_n_0\,
      O => \axi_rdata[0]_i_1_n_0\
    );
\axi_rdata[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"404000C0"
    )
        port map (
      I0 => enable,
      I1 => \axi_rdata[0]_i_7_n_0\,
      I2 => \axi_rdata[0]_i_8_n_0\,
      I3 => timeout_enable,
      I4 => \axi_rdata[0]_i_9_n_0\,
      O => \axi_rdata[0]_i_3_n_0\
    );
\axi_rdata[0]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EEEEEEEFEFEEEFEF"
    )
        port map (
      I0 => \^slv_addr_reg[8]_0\,
      I1 => adc3axi_map_wready_i_2_n_0,
      I2 => \axi_rdata[0]_i_8_n_0\,
      I3 => \axi_rdata[0]_i_9_n_0\,
      I4 => dest_out,
      I5 => D(0),
      O => \axi_rdata[0]_i_4_n_0\
    );
\axi_rdata[0]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000057DF"
    )
        port map (
      I0 => \axi_rdata[0]_i_8_n_0\,
      I1 => \axi_rdata[0]_i_9_n_0\,
      I2 => error_flag,
      I3 => \axi_rdata_reg[11]_1\(0),
      I4 => \axi_rdata[0]_i_7_n_0\,
      O => \axi_rdata[0]_i_5_n_0\
    );
\axi_rdata[0]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(0),
      I1 => slv_rdata(0),
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => \^q\(0),
      I4 => \axi_rdata[8]_i_2_1\(0),
      O => \axi_rdata[0]_i_6_n_0\
    );
\axi_rdata[0]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"01000111"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(3),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \axi_rdata[0]_i_7_n_0\
    );
\axi_rdata[0]_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"01001101"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \^slv_addr_reg[11]_0\(3),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => \^slv_addr_reg[11]_0\(1),
      O => \axi_rdata[0]_i_8_n_0\
    );
\axi_rdata[0]_i_9\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFEFFCFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(3),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \axi_rdata[0]_i_9_n_0\
    );
\axi_rdata[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000AABABBBB"
    )
        port map (
      I0 => \axi_rdata[10]_i_2_n_0\,
      I1 => \axi_rdata[11]_i_5_n_0\,
      I2 => \axi_rdata_reg[11]_1\(10),
      I3 => \axi_rdata[11]_i_4_n_0\,
      I4 => \axi_rdata[11]_i_3_n_0\,
      I5 => \axi_rdata[10]_i_3_n_0\,
      O => \axi_rdata[10]_i_1_n_0\
    );
\axi_rdata[10]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EEFCFFCCEEFCCCCC"
    )
        port map (
      I0 => \axi_rdata_reg[10]_1\,
      I1 => \slv_rd_addr_reg_n_0_[2]\,
      I2 => slv_rdata(10),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => \^q\(0),
      I5 => \axi_rdata_reg[10]_2\,
      O => \axi_rdata[10]_i_2_n_0\
    );
\axi_rdata[10]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FD00FFFF"
    )
        port map (
      I0 => \axi_rdata_reg[10]_0\,
      I1 => \^q\(0),
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => \slv_rd_addr_reg_n_0_[2]\,
      I4 => \axi_rdata[8]_i_3_n_0\,
      O => \axi_rdata[10]_i_3_n_0\
    );
\axi_rdata[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000AAAABBFB"
    )
        port map (
      I0 => \axi_rdata[11]_i_2_n_0\,
      I1 => \axi_rdata[11]_i_3_n_0\,
      I2 => \axi_rdata_reg[11]_1\(11),
      I3 => \axi_rdata[11]_i_4_n_0\,
      I4 => \axi_rdata[11]_i_5_n_0\,
      I5 => \axi_rdata[11]_i_6_n_0\,
      O => \axi_rdata[11]_i_1_n_0\
    );
\axi_rdata[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EEFCFFCCEEFCCCCC"
    )
        port map (
      I0 => \axi_rdata_reg[11]_2\,
      I1 => \slv_rd_addr_reg_n_0_[2]\,
      I2 => slv_rdata(11),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => \^q\(0),
      I5 => \axi_rdata_reg[11]_3\,
      O => \axi_rdata[11]_i_2_n_0\
    );
\axi_rdata[11]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFD"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(3),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \axi_rdata[11]_i_3_n_0\
    );
\axi_rdata[11]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFBF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      O => \axi_rdata[11]_i_4_n_0\
    );
\axi_rdata[11]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \^q\(0),
      I1 => \slv_rd_addr_reg_n_0_[1]\,
      I2 => \axi_rdata[15]_i_4_n_0\,
      I3 => \^slv_addr_reg[11]_0\(7),
      I4 => \^slv_addr_reg[11]_0\(5),
      I5 => \^slv_addr_reg[11]_0\(6),
      O => \axi_rdata[11]_i_5_n_0\
    );
\axi_rdata[11]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FD00FFFF"
    )
        port map (
      I0 => \axi_rdata_reg[11]_0\,
      I1 => \^q\(0),
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => \slv_rd_addr_reg_n_0_[2]\,
      I4 => \axi_rdata[8]_i_3_n_0\,
      O => \axi_rdata[11]_i_6_n_0\
    );
\axi_rdata[12]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"44404040"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[1]\,
      I1 => \axi_rdata[15]_i_2_n_0\,
      I2 => \axi_rdata[15]_i_3_n_0\,
      I3 => \^q\(0),
      I4 => slv_rdata(12),
      O => \axi_rdata[12]_i_1_n_0\
    );
\axi_rdata[13]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"44404040"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[1]\,
      I1 => \axi_rdata[15]_i_2_n_0\,
      I2 => \axi_rdata[15]_i_3_n_0\,
      I3 => \^q\(0),
      I4 => slv_rdata(13),
      O => \axi_rdata[13]_i_1_n_0\
    );
\axi_rdata[14]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"44404040"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[1]\,
      I1 => \axi_rdata[15]_i_2_n_0\,
      I2 => \axi_rdata[15]_i_3_n_0\,
      I3 => \^q\(0),
      I4 => slv_rdata(14),
      O => \axi_rdata[14]_i_1_n_0\
    );
\axi_rdata[15]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"44404040"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[1]\,
      I1 => \axi_rdata[15]_i_2_n_0\,
      I2 => \axi_rdata[15]_i_3_n_0\,
      I3 => \^q\(0),
      I4 => slv_rdata(15),
      O => \axi_rdata[15]_i_1_n_0\
    );
\axi_rdata[15]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[5]\,
      I1 => \slv_rd_addr_reg_n_0_[4]\,
      I2 => \slv_rd_addr_reg_n_0_[3]\,
      I3 => \slv_rd_addr_reg_n_0_[2]\,
      O => \axi_rdata[15]_i_2_n_0\
    );
\axi_rdata[15]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \axi_rdata[11]_i_3_n_0\,
      I1 => \^slv_addr_reg[11]_0\(6),
      I2 => \^slv_addr_reg[11]_0\(5),
      I3 => \^slv_addr_reg[11]_0\(7),
      I4 => \axi_rdata[15]_i_4_n_0\,
      I5 => \^q\(0),
      O => \axi_rdata[15]_i_3_n_0\
    );
\axi_rdata[15]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(8),
      I1 => \^slv_addr_reg[11]_0\(9),
      O => \axi_rdata[15]_i_4_n_0\
    );
\axi_rdata[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF444F44444444"
    )
        port map (
      I0 => \^slv_rd_addr_reg[5]_0\,
      I1 => \axi_rdata_reg[8]_0\(0),
      I2 => \axi_rdata[1]_i_2_n_0\,
      I3 => \axi_rdata[11]_i_5_n_0\,
      I4 => \axi_rdata[1]_i_3_n_0\,
      I5 => \axi_rdata[15]_i_2_n_0\,
      O => \axi_rdata[1]_i_1_n_0\
    );
\axi_rdata[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEBFFFFFFEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \axi_rdata_reg[11]_1\(1),
      O => \axi_rdata[1]_i_2_n_0\
    );
\axi_rdata[1]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(1),
      I1 => \axi_rdata[8]_i_2_1\(1),
      I2 => \^q\(0),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => slv_rdata(1),
      O => \axi_rdata[1]_i_3_n_0\
    );
\axi_rdata[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF444F44444444"
    )
        port map (
      I0 => \^slv_rd_addr_reg[5]_0\,
      I1 => \axi_rdata_reg[8]_0\(1),
      I2 => \axi_rdata[2]_i_2_n_0\,
      I3 => \axi_rdata[11]_i_5_n_0\,
      I4 => \axi_rdata[2]_i_3_n_0\,
      I5 => \axi_rdata[15]_i_2_n_0\,
      O => \axi_rdata[2]_i_1_n_0\
    );
\axi_rdata[2]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEBFFFFFFEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \axi_rdata_reg[11]_1\(2),
      O => \axi_rdata[2]_i_2_n_0\
    );
\axi_rdata[2]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(2),
      I1 => \axi_rdata[8]_i_2_1\(2),
      I2 => \^q\(0),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => slv_rdata(2),
      O => \axi_rdata[2]_i_3_n_0\
    );
\axi_rdata[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF444F44444444"
    )
        port map (
      I0 => \^slv_rd_addr_reg[5]_0\,
      I1 => \axi_rdata_reg[8]_0\(2),
      I2 => \axi_rdata[3]_i_2_n_0\,
      I3 => \axi_rdata[11]_i_5_n_0\,
      I4 => \axi_rdata[3]_i_3_n_0\,
      I5 => \axi_rdata[15]_i_2_n_0\,
      O => \axi_rdata[3]_i_1_n_0\
    );
\axi_rdata[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEBFFFFFFEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \axi_rdata_reg[11]_1\(3),
      O => \axi_rdata[3]_i_2_n_0\
    );
\axi_rdata[3]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(3),
      I1 => slv_rdata(3),
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => \^q\(0),
      I4 => \axi_rdata[8]_i_2_1\(3),
      O => \axi_rdata[3]_i_3_n_0\
    );
\axi_rdata[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF444F44444444"
    )
        port map (
      I0 => \^slv_rd_addr_reg[5]_0\,
      I1 => \axi_rdata_reg[8]_0\(3),
      I2 => \axi_rdata[4]_i_2_n_0\,
      I3 => \axi_rdata[11]_i_5_n_0\,
      I4 => \axi_rdata[4]_i_3_n_0\,
      I5 => \axi_rdata[15]_i_2_n_0\,
      O => \axi_rdata[4]_i_1_n_0\
    );
\axi_rdata[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEBFFFFFFEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \axi_rdata_reg[11]_1\(4),
      O => \axi_rdata[4]_i_2_n_0\
    );
\axi_rdata[4]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(4),
      I1 => \axi_rdata[8]_i_2_1\(4),
      I2 => \^q\(0),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => slv_rdata(4),
      O => \axi_rdata[4]_i_3_n_0\
    );
\axi_rdata[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF444F44444444"
    )
        port map (
      I0 => \^slv_rd_addr_reg[5]_0\,
      I1 => \axi_rdata_reg[8]_0\(4),
      I2 => \axi_rdata[5]_i_2_n_0\,
      I3 => \axi_rdata[11]_i_5_n_0\,
      I4 => \axi_rdata[5]_i_3_n_0\,
      I5 => \axi_rdata[15]_i_2_n_0\,
      O => \axi_rdata[5]_i_1_n_0\
    );
\axi_rdata[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEBFFFFFFEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \axi_rdata_reg[11]_1\(5),
      O => \axi_rdata[5]_i_2_n_0\
    );
\axi_rdata[5]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(5),
      I1 => slv_rdata(5),
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => \^q\(0),
      I4 => \axi_rdata[8]_i_2_1\(5),
      O => \axi_rdata[5]_i_3_n_0\
    );
\axi_rdata[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF444F44444444"
    )
        port map (
      I0 => \^slv_rd_addr_reg[5]_0\,
      I1 => \axi_rdata_reg[8]_0\(5),
      I2 => \axi_rdata[6]_i_2_n_0\,
      I3 => \axi_rdata[11]_i_5_n_0\,
      I4 => \axi_rdata[6]_i_3_n_0\,
      I5 => \axi_rdata[15]_i_2_n_0\,
      O => \axi_rdata[6]_i_1_n_0\
    );
\axi_rdata[6]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEBFFFFFFEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \axi_rdata_reg[11]_1\(6),
      O => \axi_rdata[6]_i_2_n_0\
    );
\axi_rdata[6]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(6),
      I1 => \axi_rdata[8]_i_2_1\(6),
      I2 => \^q\(0),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => slv_rdata(6),
      O => \axi_rdata[6]_i_3_n_0\
    );
\axi_rdata[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F100FFFFF100F100"
    )
        port map (
      I0 => \axi_rdata[7]_i_2_n_0\,
      I1 => \axi_rdata[11]_i_5_n_0\,
      I2 => \axi_rdata[7]_i_3_n_0\,
      I3 => \axi_rdata[15]_i_2_n_0\,
      I4 => \^slv_rd_addr_reg[5]_0\,
      I5 => \axi_rdata_reg[8]_0\(6),
      O => \axi_rdata[7]_i_1_n_0\
    );
\axi_rdata[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEBFFFFFFEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \axi_rdata_reg[11]_1\(7),
      O => \axi_rdata[7]_i_2_n_0\
    );
\axi_rdata[7]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(7),
      I1 => \axi_rdata[8]_i_2_1\(7),
      I2 => \^q\(0),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => slv_rdata(7),
      O => \axi_rdata[7]_i_3_n_0\
    );
\axi_rdata[7]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFEFFFFFFFF"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[5]\,
      I1 => \slv_rd_addr_reg_n_0_[4]\,
      I2 => \slv_rd_addr_reg_n_0_[3]\,
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => \^q\(0),
      I5 => \slv_rd_addr_reg_n_0_[2]\,
      O => \^slv_rd_addr_reg[5]_0\
    );
\axi_rdata[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0202000000FF0000"
    )
        port map (
      I0 => \axi_rdata_reg[8]_0\(7),
      I1 => \slv_rd_addr_reg_n_0_[1]\,
      I2 => \^q\(0),
      I3 => \axi_rdata[8]_i_2_n_0\,
      I4 => \axi_rdata[8]_i_3_n_0\,
      I5 => \slv_rd_addr_reg_n_0_[2]\,
      O => \axi_rdata[8]_i_1_n_0\
    );
\axi_rdata[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000FFFFFF8A"
    )
        port map (
      I0 => \axi_rdata[11]_i_3_n_0\,
      I1 => \axi_rdata[11]_i_4_n_0\,
      I2 => \axi_rdata_reg[11]_1\(8),
      I3 => adc3axi_map_wready_i_2_n_0,
      I4 => \^slv_addr_reg[8]_0\,
      I5 => \axi_rdata[8]_i_4_n_0\,
      O => \axi_rdata[8]_i_2_n_0\
    );
\axi_rdata[8]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"01"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[3]\,
      I1 => \slv_rd_addr_reg_n_0_[4]\,
      I2 => \slv_rd_addr_reg_n_0_[5]\,
      O => \axi_rdata[8]_i_3_n_0\
    );
\axi_rdata[8]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"ACF0AC00"
    )
        port map (
      I0 => \axi_rdata[8]_i_2_0\(8),
      I1 => \axi_rdata[8]_i_2_1\(8),
      I2 => \^q\(0),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => slv_rdata(8),
      O => \axi_rdata[8]_i_4_n_0\
    );
\axi_rdata[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000AABABBBB"
    )
        port map (
      I0 => \axi_rdata[9]_i_2_n_0\,
      I1 => \axi_rdata[11]_i_5_n_0\,
      I2 => \axi_rdata_reg[11]_1\(9),
      I3 => \axi_rdata[11]_i_4_n_0\,
      I4 => \axi_rdata[11]_i_3_n_0\,
      I5 => \axi_rdata[9]_i_3_n_0\,
      O => \axi_rdata[9]_i_1_n_0\
    );
\axi_rdata[9]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EEFCFFCCEEFCCCCC"
    )
        port map (
      I0 => \axi_rdata_reg[9]_1\,
      I1 => \slv_rd_addr_reg_n_0_[2]\,
      I2 => slv_rdata(9),
      I3 => \slv_rd_addr_reg_n_0_[1]\,
      I4 => \^q\(0),
      I5 => \axi_rdata_reg[9]_2\,
      O => \axi_rdata[9]_i_2_n_0\
    );
\axi_rdata[9]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FD00FFFF"
    )
        port map (
      I0 => \axi_rdata_reg[9]_0\,
      I1 => \^q\(0),
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => \slv_rd_addr_reg_n_0_[2]\,
      I4 => \axi_rdata[8]_i_3_n_0\,
      O => \axi_rdata[9]_i_3_n_0\
    );
\axi_rdata_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[0]_i_1_n_0\,
      Q => s_axi_rdata(0),
      R => p_0_in
    );
\axi_rdata_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[10]_i_1_n_0\,
      Q => s_axi_rdata(10),
      R => p_0_in
    );
\axi_rdata_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[11]_i_1_n_0\,
      Q => s_axi_rdata(11),
      R => p_0_in
    );
\axi_rdata_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[12]_i_1_n_0\,
      Q => s_axi_rdata(12),
      R => p_0_in
    );
\axi_rdata_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[13]_i_1_n_0\,
      Q => s_axi_rdata(13),
      R => p_0_in
    );
\axi_rdata_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[14]_i_1_n_0\,
      Q => s_axi_rdata(14),
      R => p_0_in
    );
\axi_rdata_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[15]_i_1_n_0\,
      Q => s_axi_rdata(15),
      R => p_0_in
    );
\axi_rdata_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[1]_i_1_n_0\,
      Q => s_axi_rdata(1),
      R => p_0_in
    );
\axi_rdata_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[2]_i_1_n_0\,
      Q => s_axi_rdata(2),
      R => p_0_in
    );
\axi_rdata_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[3]_i_1_n_0\,
      Q => s_axi_rdata(3),
      R => p_0_in
    );
\axi_rdata_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[4]_i_1_n_0\,
      Q => s_axi_rdata(4),
      R => p_0_in
    );
\axi_rdata_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[5]_i_1_n_0\,
      Q => s_axi_rdata(5),
      R => p_0_in
    );
\axi_rdata_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[6]_i_1_n_0\,
      Q => s_axi_rdata(6),
      R => p_0_in
    );
\axi_rdata_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[7]_i_1_n_0\,
      Q => s_axi_rdata(7),
      R => p_0_in
    );
\axi_rdata_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[8]_i_1_n_0\,
      Q => s_axi_rdata(8),
      R => p_0_in
    );
\axi_rdata_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => slv_reg_rden,
      D => \axi_rdata[9]_i_1_n_0\,
      Q => s_axi_rdata(9),
      R => p_0_in
    );
\axi_rresp[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFDF00C0"
    )
        port map (
      I0 => \axi_rresp[1]_i_2_n_0\,
      I1 => timeout,
      I2 => read_in_progress,
      I3 => \^axi_rvalid_reg_0\,
      I4 => \^s_axi_rresp\(0),
      O => \axi_rresp[1]_i_1_n_0\
    );
\axi_rresp[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFEA0000FFFFFFFF"
    )
        port map (
      I0 => \slv_rd_addr_reg_n_0_[2]\,
      I1 => adc2slv_rden_reg_0,
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => adc2slv_rden_reg_1,
      I4 => \axi_rresp[1]_i_5_n_0\,
      I5 => \axi_rdata[8]_i_3_n_0\,
      O => \axi_rresp[1]_i_2_n_0\
    );
\axi_rresp[1]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFF8FFFF"
    )
        port map (
      I0 => slv_wren_done_pulse,
      I1 => slv_rden_r,
      I2 => \slv_rd_addr_reg_n_0_[1]\,
      I3 => \^q\(0),
      I4 => \slv_rd_addr_reg_n_0_[2]\,
      O => \axi_rresp[1]_i_5_n_0\
    );
\axi_rresp_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \axi_rresp[1]_i_1_n_0\,
      Q => \^s_axi_rresp\(0),
      R => p_0_in
    );
axi_rvalid_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"74747444"
    )
        port map (
      I0 => s_axi_rready,
      I1 => \^axi_rvalid_reg_0\,
      I2 => read_in_progress,
      I3 => timeout,
      I4 => \axi_rresp[1]_i_2_n_0\,
      O => axi_rvalid_i_1_n_0
    );
axi_rvalid_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_rvalid_i_1_n_0,
      Q => \^axi_rvalid_reg_0\,
      R => p_0_in
    );
axi_wr_access_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => s_axi_arvalid,
      O => axi_awready19_in
    );
axi_wr_access_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => \^axi_wr_access_reg_0\,
      I1 => s_axi_wvalid,
      I2 => valid_waddr_reg_n_0,
      O => axi_wr_access0
    );
axi_wr_access_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => axi_awready19_in,
      D => axi_wr_access0,
      Q => \^axi_wr_access_reg_0\,
      R => p_0_in
    );
enable_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFE00000002"
    )
        port map (
      I0 => s_axi_wdata(0),
      I1 => enable_i_2_n_0,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(0),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => enable,
      O => s_axi_wdata_0_sn_1
    );
enable_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEFFFFFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(3),
      I2 => \^slv_addr_reg[8]_0\,
      I3 => \^adc_ds_axi_map_wready\,
      I4 => s_axi_wvalid,
      O => enable_i_2_n_0
    );
read_in_progress_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000044444000"
    )
        port map (
      I0 => timeout,
      I1 => s_axi_aresetn,
      I2 => \^axi_arready_reg_0\,
      I3 => s_axi_arvalid,
      I4 => read_in_progress,
      I5 => read_in_progress_i_2_n_0,
      O => read_in_progress_i_1_n_0
    );
read_in_progress_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^axi_rvalid_reg_0\,
      I1 => s_axi_rready,
      O => read_in_progress_i_2_n_0
    );
read_in_progress_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => read_in_progress_i_1_n_0,
      Q => read_in_progress,
      R => '0'
    );
\slv_addr[10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(8),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(8),
      O => \slv_addr[10]_i_1_n_0\
    );
\slv_addr[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(9),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(9),
      O => \slv_addr[11]_i_1_n_0\
    );
\slv_addr[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(0),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(0),
      O => \slv_addr[2]_i_1_n_0\
    );
\slv_addr[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(1),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(1),
      O => \slv_addr[3]_i_1_n_0\
    );
\slv_addr[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(2),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(2),
      O => \slv_addr[4]_i_1_n_0\
    );
\slv_addr[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(3),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(3),
      O => \slv_addr[5]_i_1_n_0\
    );
\slv_addr[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(4),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(4),
      O => \slv_addr[6]_i_1_n_0\
    );
\slv_addr[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(5),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(5),
      O => \slv_addr[7]_i_1_n_0\
    );
\slv_addr[8]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(6),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(6),
      O => \slv_addr[8]_i_1_n_0\
    );
\slv_addr[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(7),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(7),
      O => \slv_addr[9]_i_1_n_0\
    );
\slv_addr_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[10]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(8),
      R => p_0_in
    );
\slv_addr_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[11]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(9),
      R => p_0_in
    );
\slv_addr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[2]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(0),
      R => p_0_in
    );
\slv_addr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[3]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(1),
      R => p_0_in
    );
\slv_addr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[4]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(2),
      R => p_0_in
    );
\slv_addr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[5]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(3),
      R => p_0_in
    );
\slv_addr_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[6]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(4),
      R => p_0_in
    );
\slv_addr_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[7]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(5),
      R => p_0_in
    );
\slv_addr_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[8]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(6),
      R => p_0_in
    );
\slv_addr_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_addr[9]_i_1_n_0\,
      Q => \^slv_addr_reg[11]_0\(7),
      R => p_0_in
    );
\slv_rd_addr[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(10),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(10),
      O => \slv_rd_addr[0]_i_1_n_0\
    );
\slv_rd_addr[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(11),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(11),
      O => \slv_rd_addr[1]_i_1_n_0\
    );
\slv_rd_addr[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(12),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(12),
      O => \slv_rd_addr[2]_i_1_n_0\
    );
\slv_rd_addr[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(13),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(13),
      O => \slv_rd_addr[3]_i_1_n_0\
    );
\slv_rd_addr[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(14),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(14),
      O => \slv_rd_addr[4]_i_1_n_0\
    );
\slv_rd_addr[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"04550404"
    )
        port map (
      I0 => valid_waddr_reg_n_0,
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => \^axi_awready_reg_0\,
      I4 => s_axi_awvalid,
      O => \slv_rd_addr[5]_i_1_n_0\
    );
\slv_rd_addr[5]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s_axi_araddr(15),
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      I3 => s_axi_awaddr(15),
      O => \slv_rd_addr[5]_i_2_n_0\
    );
\slv_rd_addr_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_rd_addr[0]_i_1_n_0\,
      Q => \^q\(0),
      R => p_0_in
    );
\slv_rd_addr_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_rd_addr[1]_i_1_n_0\,
      Q => \slv_rd_addr_reg_n_0_[1]\,
      R => p_0_in
    );
\slv_rd_addr_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_rd_addr[2]_i_1_n_0\,
      Q => \slv_rd_addr_reg_n_0_[2]\,
      R => p_0_in
    );
\slv_rd_addr_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_rd_addr[3]_i_1_n_0\,
      Q => \slv_rd_addr_reg_n_0_[3]\,
      R => p_0_in
    );
\slv_rd_addr_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_rd_addr[4]_i_1_n_0\,
      Q => \slv_rd_addr_reg_n_0_[4]\,
      R => p_0_in
    );
\slv_rd_addr_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => \slv_rd_addr[5]_i_1_n_0\,
      D => \slv_rd_addr[5]_i_2_n_0\,
      Q => \slv_rd_addr_reg_n_0_[5]\,
      R => p_0_in
    );
\slv_rdata[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAA8A80"
    )
        port map (
      I0 => \slv_rdata[0]_i_2_n_0\,
      I1 => \slv_rdata_reg[0]\,
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \slv_rdata_reg[0]_0\,
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \slv_addr_reg[2]_2\(0)
    );
\slv_rdata[0]_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020200000000FFFC"
    )
        port map (
      I0 => s00_tdata(80),
      I1 => \^slv_addr_reg[11]_0\(7),
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[8]_2\(0),
      I4 => \^slv_addr_reg[11]_0\(4),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[0]_i_11_n_0\
    );
\slv_rdata[0]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAA8A80"
    )
        port map (
      I0 => \slv_rdata[0]_i_2__0_n_0\,
      I1 => \slv_rdata_reg[0]_3\,
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \slv_rdata_reg[0]_4\,
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \slv_addr_reg[2]_3\(0)
    );
\slv_rdata[0]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAA8A80"
    )
        port map (
      I0 => \slv_rdata[0]_i_2__1_n_0\,
      I1 => \slv_rdata_reg[0]_7\,
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \slv_rdata_reg[0]_8\,
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \slv_addr_reg[2]_4\(0)
    );
\slv_rdata[0]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAAAAA8A88AAAA"
    )
        port map (
      I0 => \^slv_addr_reg[5]_3\,
      I1 => \slv_rdata[0]_i_2__2_n_0\,
      I2 => \slv_rdata[0]_i_3_n_0\,
      I3 => \slv_rdata[0]_i_4_n_0\,
      I4 => \slv_rdata[0]_i_5_n_0\,
      I5 => \slv_rdata[0]_i_6_n_0\,
      O => \slv_addr_reg[4]_0\(0)
    );
\slv_rdata[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0A08AAAA0200AAAA"
    )
        port map (
      I0 => \slv_rdata[1]_i_5__2_n_0\,
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata_reg[0]_1\,
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \slv_rdata_reg[0]_2\,
      O => \slv_rdata[0]_i_2_n_0\
    );
\slv_rdata[0]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0A08AAAA0200AAAA"
    )
        port map (
      I0 => \slv_rdata[1]_i_5__2_n_0\,
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata_reg[0]_5\,
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \slv_rdata_reg[0]_6\,
      O => \slv_rdata[0]_i_2__0_n_0\
    );
\slv_rdata[0]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0A02AAAA0800AAAA"
    )
        port map (
      I0 => \slv_rdata[1]_i_5__2_n_0\,
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata_reg[0]_9\,
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \slv_rdata_reg[0]_10\,
      O => \slv_rdata[0]_i_2__1_n_0\
    );
\slv_rdata[0]_i_2__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAA8A888A888A88"
    )
        port map (
      I0 => \^slv_addr_reg[3]_3\,
      I1 => \slv_rdata[0]_i_7_n_0\,
      I2 => \slv_rdata[1]_i_10_n_0\,
      I3 => s00_tdata(48),
      I4 => \adc01_ds_control_0[1]_i_3_n_0\,
      I5 => \slv_rdata_reg[0]_12\,
      O => \slv_rdata[0]_i_2__2_n_0\
    );
\slv_rdata[0]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BABFAAAABABFFAFA"
    )
        port map (
      I0 => \slv_rdata[0]_i_9_n_0\,
      I1 => \slv_rdata_reg[3]_2\(0),
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[3]_3\(0),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \slv_rdata_reg[3]_4\(0),
      O => \slv_rdata[0]_i_3_n_0\
    );
\slv_rdata[0]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E3E0030323200303"
    )
        port map (
      I0 => s00_tdata(32),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \slv_rdata_reg[3]_8\(0),
      I4 => \slv_rdata[8]_i_4_n_0\,
      I5 => s00_tdata(96),
      O => \slv_rdata[0]_i_4_n_0\
    );
\slv_rdata[0]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"5F5F57F7FFFF57F7"
    )
        port map (
      I0 => \slv_rdata[1]_i_7_n_0\,
      I1 => \slv_rdata_reg[0]_11\,
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => s00_tdata(0),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(64),
      O => \slv_rdata[0]_i_5_n_0\
    );
\slv_rdata[0]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000AE00000000"
    )
        port map (
      I0 => \slv_rdata[0]_i_11_n_0\,
      I1 => s00_tdata(16),
      I2 => \slv_rdata[1]_i_10_n_0\,
      I3 => \slv_rdata_reg[0]_13\,
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \^slv_addr_reg[11]_0\(0),
      O => \slv_rdata[0]_i_6_n_0\
    );
\slv_rdata[0]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000E200000000"
    )
        port map (
      I0 => s00_ds_status,
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => s00_tdata(112),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[0]_i_7_n_0\
    );
\slv_rdata[0]_i_9\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[0]_i_9_n_0\
    );
\slv_rdata[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222200002A222A22"
    )
        port map (
      I0 => \slv_rdata_reg[10]_i_2_n_0\,
      I1 => \^slv_addr_reg[6]_5\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata_reg[10]\,
      I4 => \^slv_addr_reg[5]_3\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[4]_0\(4)
    );
\slv_rdata[10]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(10),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(42),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[10]_i_6_n_0\
    );
\slv_rdata[10]_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(74),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(106),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[10]_i_7_n_0\
    );
\slv_rdata[10]_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(26),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(58),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[10]_i_8_n_0\
    );
\slv_rdata[10]_i_9\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(90),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(122),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[10]_i_9_n_0\
    );
\slv_rdata[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"080A08AA080A080A"
    )
        port map (
      I0 => \slv_rdata_reg[11]_i_2_n_0\,
      I1 => \^slv_addr_reg[5]_3\,
      I2 => \^slv_addr_reg[6]_5\,
      I3 => \slv_rdata[11]_i_5_n_0\,
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => \slv_rdata_reg[11]\,
      O => \slv_addr_reg[4]_0\(5)
    );
\slv_rdata[11]_i_10\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(75),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(107),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[11]_i_10_n_0\
    );
\slv_rdata[11]_i_11\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(27),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(59),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[11]_i_11_n_0\
    );
\slv_rdata[11]_i_12\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(91),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(123),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[11]_i_12_n_0\
    );
\slv_rdata[11]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(3),
      I1 => \^slv_addr_reg[11]_0\(5),
      I2 => \^slv_addr_reg[11]_0\(9),
      I3 => \^slv_addr_reg[11]_0\(8),
      O => \^slv_addr_reg[5]_3\
    );
\slv_rdata[11]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FD"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(7),
      I2 => \^slv_addr_reg[11]_0\(6),
      O => \^slv_addr_reg[6]_5\
    );
\slv_rdata[11]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(1),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \^slv_addr_reg[11]_0\(8),
      I3 => \^slv_addr_reg[11]_0\(9),
      I4 => \^slv_addr_reg[11]_0\(5),
      I5 => \^slv_addr_reg[11]_0\(3),
      O => \slv_rdata[11]_i_5_n_0\
    );
\slv_rdata[11]_i_9\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(11),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(43),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[11]_i_9_n_0\
    );
\slv_rdata[12]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(108),
      I1 => s00_tdata(44),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(76),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(12),
      O => \slv_rdata[12]_i_2_n_0\
    );
\slv_rdata[12]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(124),
      I1 => s00_tdata(60),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(92),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(28),
      O => \slv_rdata[12]_i_3_n_0\
    );
\slv_rdata[13]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(109),
      I1 => s00_tdata(45),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(77),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(13),
      O => \slv_rdata[13]_i_2_n_0\
    );
\slv_rdata[13]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(125),
      I1 => s00_tdata(61),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(93),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(29),
      O => \slv_rdata[13]_i_3_n_0\
    );
\slv_rdata[14]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(110),
      I1 => s00_tdata(46),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(78),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(14),
      O => \slv_rdata[14]_i_2_n_0\
    );
\slv_rdata[14]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(126),
      I1 => s00_tdata(62),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(94),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(30),
      O => \slv_rdata[14]_i_3_n_0\
    );
\slv_rdata[15]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(111),
      I1 => s00_tdata(47),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(79),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(15),
      O => \slv_rdata[15]_i_3_n_0\
    );
\slv_rdata[15]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => s00_tdata(127),
      I1 => s00_tdata(63),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => s00_tdata(95),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => s00_tdata(31),
      O => \slv_rdata[15]_i_4_n_0\
    );
\slv_rdata[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000FFB8"
    )
        port map (
      I0 => \slv_rdata_reg[1]\,
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \slv_rdata_reg[1]_0\,
      I3 => \^slv_addr_reg[11]_0\(0),
      I4 => \slv_rdata[1]_i_4_n_0\,
      O => \slv_addr_reg[2]_2\(1)
    );
\slv_rdata[1]_i_10\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FEFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(2),
      I1 => \^slv_addr_reg[11]_0\(6),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[1]_i_10_n_0\
    );
\slv_rdata[1]_i_12\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(1),
      I1 => \^slv_addr_reg[11]_0\(0),
      O => \^slv_addr_reg[3]_3\
    );
\slv_rdata[1]_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020200000000FFFC"
    )
        port map (
      I0 => s00_tdata(97),
      I1 => \^slv_addr_reg[11]_0\(7),
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[3]_8\(1),
      I4 => \^slv_addr_reg[11]_0\(4),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[1]_i_13_n_0\
    );
\slv_rdata[1]_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAA8A80"
    )
        port map (
      I0 => \slv_rdata[1]_i_2_n_0\,
      I1 => \slv_rdata_reg[1]_3\,
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \slv_rdata_reg[1]_4\,
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \slv_addr_reg[2]_3\(1)
    );
\slv_rdata[1]_i_1__1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AAAA8A80"
    )
        port map (
      I0 => \slv_rdata[1]_i_2__0_n_0\,
      I1 => \slv_rdata_reg[1]_7\,
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \slv_rdata_reg[1]_8\,
      I4 => \^slv_addr_reg[11]_0\(0),
      O => \slv_addr_reg[2]_4\(1)
    );
\slv_rdata[1]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAAAAAA8A8A8AA"
    )
        port map (
      I0 => \^slv_addr_reg[5]_3\,
      I1 => \slv_rdata[1]_i_2__1_n_0\,
      I2 => \slv_rdata[1]_i_3_n_0\,
      I3 => \slv_rdata_reg[1]_11\,
      I4 => \slv_rdata[1]_i_5_n_0\,
      I5 => \slv_rdata[1]_i_6_n_0\,
      O => \slv_addr_reg[4]_0\(1)
    );
\slv_rdata[1]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0A02AAAA0800AAAA"
    )
        port map (
      I0 => \slv_rdata[1]_i_5__2_n_0\,
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata_reg[1]_5\,
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \slv_rdata_reg[1]_6\,
      O => \slv_rdata[1]_i_2_n_0\
    );
\slv_rdata[1]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0A08AAAA0200AAAA"
    )
        port map (
      I0 => \slv_rdata[1]_i_5__2_n_0\,
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata_reg[1]_9\,
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \slv_rdata_reg[1]_10\,
      O => \slv_rdata[1]_i_2__0_n_0\
    );
\slv_rdata[1]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8A0A800A8A008000"
    )
        port map (
      I0 => \slv_rdata[1]_i_7_n_0\,
      I1 => s00_tdata(65),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => s00_tdata(1),
      I5 => \slv_rdata_reg[1]_12\,
      O => \slv_rdata[1]_i_2__1_n_0\
    );
\slv_rdata[1]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000AE00000000"
    )
        port map (
      I0 => \slv_rdata[1]_i_9_n_0\,
      I1 => s00_tdata(17),
      I2 => \slv_rdata[1]_i_10_n_0\,
      I3 => \slv_rdata_reg[1]_15\,
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \^slv_addr_reg[11]_0\(0),
      O => \slv_rdata[1]_i_3_n_0\
    );
\slv_rdata[1]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"DDDFFDFF55555555"
    )
        port map (
      I0 => \slv_rdata[1]_i_5__2_n_0\,
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \slv_rdata_reg[1]_1\,
      I4 => \slv_rdata_reg[1]_2\,
      I5 => \^slv_addr_reg[11]_0\(0),
      O => \slv_rdata[1]_i_4_n_0\
    );
\slv_rdata[1]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"1C1FFCFCDCDFFCFC"
    )
        port map (
      I0 => s00_tdata(49),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \slv_rdata_reg[1]_14\(0),
      I4 => \slv_rdata[8]_i_4_n_0\,
      I5 => s00_tdata(113),
      O => \slv_rdata[1]_i_5_n_0\
    );
\slv_rdata[1]_i_5__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(8),
      I1 => \^slv_addr_reg[11]_0\(9),
      I2 => \^slv_addr_reg[11]_0\(5),
      I3 => \^slv_addr_reg[11]_0\(3),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[1]_i_5__2_n_0\
    );
\slv_rdata[1]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000AE00000000"
    )
        port map (
      I0 => \slv_rdata[1]_i_13_n_0\,
      I1 => s00_tdata(33),
      I2 => \slv_rdata[1]_i_10_n_0\,
      I3 => \slv_rdata_reg[1]_13\,
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[1]_i_6_n_0\
    );
\slv_rdata[1]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000057"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(6),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \^slv_addr_reg[11]_0\(0),
      I4 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[1]_i_7_n_0\
    );
\slv_rdata[1]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"020200000000FFFC"
    )
        port map (
      I0 => s00_tdata(81),
      I1 => \^slv_addr_reg[11]_0\(7),
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[8]_2\(1),
      I4 => \^slv_addr_reg[11]_0\(4),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[1]_i_9_n_0\
    );
\slv_rdata[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"1055FFFF10551055"
    )
        port map (
      I0 => \slv_rdata[2]_i_2_n_0\,
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \slv_rdata_reg[2]\,
      I3 => \^slv_addr_reg[11]_0\(1),
      I4 => \slv_rdata[3]_i_6_n_0\,
      I5 => \slv_rdata_reg[2]_0\,
      O => \slv_addr_reg[2]_2\(2)
    );
\slv_rdata[2]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"1055FFFF10551055"
    )
        port map (
      I0 => \slv_rdata[2]_i_2__0_n_0\,
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \slv_rdata_reg[2]_1\,
      I3 => \^slv_addr_reg[11]_0\(1),
      I4 => \slv_rdata[3]_i_6_n_0\,
      I5 => \slv_rdata_reg[2]_2\,
      O => \slv_addr_reg[2]_3\(2)
    );
\slv_rdata[2]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"1055FFFF10551055"
    )
        port map (
      I0 => \slv_rdata[2]_i_2__1_n_0\,
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \slv_rdata_reg[2]_3\,
      I3 => \^slv_addr_reg[11]_0\(1),
      I4 => \slv_rdata[3]_i_6_n_0\,
      I5 => \slv_rdata_reg[2]_4\,
      O => \slv_addr_reg[2]_4\(2)
    );
\slv_rdata[2]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22F222F2FFFF22F2"
    )
        port map (
      I0 => \slv_rdata[2]_i_2__2_n_0\,
      I1 => \slv_rdata[2]_i_3_n_0\,
      I2 => \slv_rdata[2]_i_4_n_0\,
      I3 => \slv_rdata[2]_i_5_n_0\,
      I4 => \slv_rdata[7]_i_3_n_0\,
      I5 => \slv_rdata[2]_i_6_n_0\,
      O => s00_tdata_50_sn_1
    );
\slv_rdata[2]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF44455545"
    )
        port map (
      I0 => \slv_rdata[2]_i_5__0_n_0\,
      I1 => \^slv_addr_reg[11]_0\(6),
      I2 => \slv_rdata_reg[7]_9\(0),
      I3 => \^slv_addr_reg[11]_0\(7),
      I4 => \slv_rdata_reg[7]_10\(0),
      I5 => \slv_rdata[2]_i_6__0_n_0\,
      O => \slv_rdata[2]_i_2_n_0\
    );
\slv_rdata[2]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BABABABBBBBBBABB"
    )
        port map (
      I0 => \slv_rdata[2]_i_6__0_n_0\,
      I1 => \slv_rdata[2]_i_5__1_n_0\,
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[7]_4\(0),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \slv_rdata_reg[7]_3\(0),
      O => \slv_rdata[2]_i_2__0_n_0\
    );
\slv_rdata[2]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"ABABABBBBBBBABBB"
    )
        port map (
      I0 => \slv_rdata[2]_i_6__0_n_0\,
      I1 => \slv_rdata[2]_i_5__2_n_0\,
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[7]_6\(0),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \slv_rdata_reg[7]_5\(0),
      O => \slv_rdata[2]_i_2__1_n_0\
    );
\slv_rdata[2]_i_2__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E200FFFFE2000000"
    )
        port map (
      I0 => s00_tdata(50),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(114),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \slv_rdata[2]_i_7_n_0\,
      O => \slv_rdata[2]_i_2__2_n_0\
    );
\slv_rdata[2]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF23EE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(2),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \slv_rdata_reg[8]_2\(2),
      I3 => \slv_rdata[8]_i_4_n_0\,
      I4 => \slv_rdata_reg[2]_5\,
      I5 => \slv_rdata[7]_i_10_n_0\,
      O => \slv_rdata[2]_i_3_n_0\
    );
\slv_rdata[2]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E3E0030323200303"
    )
        port map (
      I0 => s00_tdata(34),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \slv_rdata_reg[3]_8\(2),
      I4 => \slv_rdata[8]_i_4_n_0\,
      I5 => s00_tdata(98),
      O => \slv_rdata[2]_i_4_n_0\
    );
\slv_rdata[2]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BABFAAAABABFFAFA"
    )
        port map (
      I0 => \slv_rdata[3]_i_8_n_0\,
      I1 => \slv_rdata_reg[3]_2\(1),
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[3]_3\(1),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \slv_rdata_reg[3]_4\(1),
      O => \slv_rdata[2]_i_5_n_0\
    );
\slv_rdata[2]_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]\(0),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_0\(0),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[2]_i_5__0_n_0\
    );
\slv_rdata[2]_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_1\(0),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_2\(0),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[2]_i_5__1_n_0\
    );
\slv_rdata[2]_i_5__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF4540"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_7\(0),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_8\(0),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[2]_i_5__2_n_0\
    );
\slv_rdata[2]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0035F035"
    )
        port map (
      I0 => \slv_rdata_reg[2]_6\,
      I1 => s00_tdata(2),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => s00_tdata(66),
      O => \slv_rdata[2]_i_6_n_0\
    );
\slv_rdata[2]_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \^slv_addr_reg[11]_0\(3),
      I3 => \^slv_addr_reg[11]_0\(5),
      I4 => \^slv_addr_reg[11]_0\(9),
      I5 => \^slv_addr_reg[11]_0\(8),
      O => \slv_rdata[2]_i_6__0_n_0\
    );
\slv_rdata[2]_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(18),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(82),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[2]_i_7_n_0\
    );
\slv_rdata[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(3),
      I2 => \^slv_addr_reg[11]_0\(5),
      I3 => \^slv_addr_reg[11]_0\(9),
      I4 => \^slv_addr_reg[11]_0\(8),
      I5 => \slv_rdata_reg[3]\,
      O => \slv_addr_reg[2]_4\(3)
    );
\slv_rdata[3]_i_10\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"02A2"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => s00_tdata(19),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => s00_tdata(83),
      O => \slv_rdata[3]_i_10_n_0\
    );
\slv_rdata[3]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8880FFFF88808880"
    )
        port map (
      I0 => \slv_rdata[3]_i_2__0_n_0\,
      I1 => \slv_rdata[3]_i_3_n_0\,
      I2 => \slv_rdata[3]_i_4__0_n_0\,
      I3 => \slv_rdata[3]_i_5_n_0\,
      I4 => \slv_rdata[3]_i_6_n_0\,
      I5 => \slv_rdata_reg[3]_0\,
      O => \slv_addr_reg[2]_2\(3)
    );
\slv_rdata[3]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => \^slv_addr_reg[11]_0\(3),
      I2 => \^slv_addr_reg[11]_0\(5),
      I3 => \^slv_addr_reg[11]_0\(9),
      I4 => \^slv_addr_reg[11]_0\(8),
      I5 => \slv_rdata_reg[3]_1\,
      O => \slv_addr_reg[2]_3\(3)
    );
\slv_rdata[3]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22F222F222F2FFFF"
    )
        port map (
      I0 => \slv_rdata[7]_i_3_n_0\,
      I1 => \slv_rdata[3]_i_2__2_n_0\,
      I2 => \slv_rdata[3]_i_3__0_n_0\,
      I3 => \slv_rdata[3]_i_4_n_0\,
      I4 => \slv_rdata[3]_i_5__0_n_0\,
      I5 => \slv_rdata[3]_i_6__0_n_0\,
      O => \slv_addr_reg[5]_0\
    );
\slv_rdata[3]_i_2__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(2),
      I1 => \^slv_addr_reg[11]_0\(0),
      O => \slv_rdata[3]_i_2__0_n_0\
    );
\slv_rdata[3]_i_2__2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"03F5F3F5"
    )
        port map (
      I0 => \slv_rdata_reg[3]_9\,
      I1 => s00_tdata(3),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => s00_tdata(67),
      O => \slv_rdata[3]_i_2__2_n_0\
    );
\slv_rdata[3]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(8),
      I1 => \^slv_addr_reg[11]_0\(9),
      I2 => \^slv_addr_reg[11]_0\(5),
      I3 => \^slv_addr_reg[11]_0\(3),
      I4 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[3]_i_3_n_0\
    );
\slv_rdata[3]_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E3E0030323200303"
    )
        port map (
      I0 => s00_tdata(35),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \slv_rdata_reg[3]_8\(3),
      I4 => \slv_rdata[8]_i_4_n_0\,
      I5 => s00_tdata(99),
      O => \slv_rdata[3]_i_3__0_n_0\
    );
\slv_rdata[3]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BABFAAAABABFFAFA"
    )
        port map (
      I0 => \slv_rdata[3]_i_8_n_0\,
      I1 => \slv_rdata_reg[3]_2\(2),
      I2 => \^slv_addr_reg[11]_0\(6),
      I3 => \slv_rdata_reg[3]_3\(2),
      I4 => \^slv_addr_reg[11]_0\(7),
      I5 => \slv_rdata_reg[3]_4\(2),
      O => \slv_rdata[3]_i_4_n_0\
    );
\slv_rdata[3]_i_4__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000FFB8"
    )
        port map (
      I0 => \slv_rdata_reg[7]_10\(1),
      I1 => \^slv_addr_reg[11]_0\(7),
      I2 => \slv_rdata_reg[7]_9\(1),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \slv_rdata[3]_i_8__0_n_0\,
      O => \slv_rdata[3]_i_4__0_n_0\
    );
\slv_rdata[3]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000FFB8"
    )
        port map (
      I0 => \slv_rdata_reg[3]_5\(0),
      I1 => \^slv_addr_reg[11]_0\(7),
      I2 => \slv_rdata_reg[3]_6\(0),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \slv_rdata[3]_i_9_n_0\,
      O => \slv_rdata[3]_i_5_n_0\
    );
\slv_rdata[3]_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFBBFFBBAE"
    )
        port map (
      I0 => \slv_rdata_reg[3]_7\,
      I1 => \slv_rdata[8]_i_4_n_0\,
      I2 => \slv_rdata_reg[8]_2\(3),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => \slv_rdata[7]_i_10_n_0\,
      O => \slv_rdata[3]_i_5__0_n_0\
    );
\slv_rdata[3]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFDFFFF"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[5]_3\,
      O => \slv_rdata[3]_i_6_n_0\
    );
\slv_rdata[3]_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"57F7FFFF57F70000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => s00_tdata(51),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => s00_tdata(115),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \slv_rdata[3]_i_10_n_0\,
      O => \slv_rdata[3]_i_6__0_n_0\
    );
\slv_rdata[3]_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFD"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(1),
      I1 => \^slv_addr_reg[11]_0\(0),
      I2 => \^slv_addr_reg[11]_0\(3),
      I3 => \^slv_addr_reg[11]_0\(5),
      O => \slv_rdata[3]_i_8_n_0\
    );
\slv_rdata[3]_i_8__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF3500"
    )
        port map (
      I0 => \slv_rdata_reg[7]_0\(1),
      I1 => \slv_rdata_reg[7]\(1),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[3]_i_8__0_n_0\
    );
\slv_rdata[3]_i_9\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"77333F33"
    )
        port map (
      I0 => \slv_rdata[3]_i_5_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \slv_rdata[3]_i_5_1\(0),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \^slv_addr_reg[11]_0\(7),
      O => \slv_rdata[3]_i_9_n_0\
    );
\slv_rdata[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[4]\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[4]_i_3__1_n_0\,
      I4 => \slv_rdata[4]_i_4__0_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_2\(4)
    );
\slv_rdata[4]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[4]_0\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[4]_i_3__0_n_0\,
      I4 => \slv_rdata[4]_i_4__1_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_3\(4)
    );
\slv_rdata[4]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[4]_1\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[4]_i_3__2_n_0\,
      I4 => \slv_rdata[4]_i_4__2_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_4\(4)
    );
\slv_rdata[4]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F222F222FFFFF222"
    )
        port map (
      I0 => \slv_rdata[4]_i_2_n_0\,
      I1 => \slv_rdata[4]_i_3_n_0\,
      I2 => \slv_rdata[7]_i_6_n_0\,
      I3 => \slv_rdata[4]_i_4_n_0\,
      I4 => \slv_rdata[7]_i_3_n_0\,
      I5 => \slv_rdata[4]_i_5_n_0\,
      O => s00_tdata_52_sn_1
    );
\slv_rdata[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E200FFFFE2000000"
    )
        port map (
      I0 => s00_tdata(52),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(116),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \slv_rdata[4]_i_6_n_0\,
      O => \slv_rdata[4]_i_2_n_0\
    );
\slv_rdata[4]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFBBFFBBAE"
    )
        port map (
      I0 => \slv_rdata_reg[4]_2\,
      I1 => \slv_rdata[8]_i_4_n_0\,
      I2 => \slv_rdata_reg[8]_2\(4),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(2),
      I5 => \slv_rdata[7]_i_10_n_0\,
      O => \slv_rdata[4]_i_3_n_0\
    );
\slv_rdata[4]_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"57F7"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_2\(1),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_1\(1),
      O => \slv_rdata[4]_i_3__0_n_0\
    );
\slv_rdata[4]_i_3__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_9\(2),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_10\(2),
      O => \slv_rdata[4]_i_3__1_n_0\
    );
\slv_rdata[4]_i_3__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_8\(1),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_7\(1),
      O => \slv_rdata[4]_i_3__2_n_0\
    );
\slv_rdata[4]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s00_tdata(100),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(36),
      O => \slv_rdata[4]_i_4_n_0\
    );
\slv_rdata[4]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]\(2),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_0\(2),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[4]_i_4__0_n_0\
    );
\slv_rdata[4]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF4540"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_3\(1),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_4\(1),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[4]_i_4__1_n_0\
    );
\slv_rdata[4]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_5\(1),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_6\(1),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[4]_i_4__2_n_0\
    );
\slv_rdata[4]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0035F035"
    )
        port map (
      I0 => \slv_rdata_reg[4]_3\,
      I1 => s00_tdata(4),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => s00_tdata(68),
      O => \slv_rdata[4]_i_5_n_0\
    );
\slv_rdata[4]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(20),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(84),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[4]_i_6_n_0\
    );
\slv_rdata[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[5]\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[5]_i_3__0_n_0\,
      I4 => \slv_rdata[5]_i_4__0_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_2\(5)
    );
\slv_rdata[5]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[5]_0\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[5]_i_3__1_n_0\,
      I4 => \slv_rdata[5]_i_4__1_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_3\(5)
    );
\slv_rdata[5]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[5]_1\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[5]_i_3__2_n_0\,
      I4 => \slv_rdata[5]_i_4__2_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_4\(5)
    );
\slv_rdata[5]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F222F222FFFFF222"
    )
        port map (
      I0 => \slv_rdata[5]_i_2_n_0\,
      I1 => \slv_rdata[5]_i_3_n_0\,
      I2 => \slv_rdata[7]_i_6_n_0\,
      I3 => \slv_rdata[5]_i_4_n_0\,
      I4 => \slv_rdata[7]_i_3_n_0\,
      I5 => \slv_rdata[5]_i_5_n_0\,
      O => s00_tdata_53_sn_1
    );
\slv_rdata[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E200FFFFE2000000"
    )
        port map (
      I0 => s00_tdata(53),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(117),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \slv_rdata[5]_i_6_n_0\,
      O => \slv_rdata[5]_i_2_n_0\
    );
\slv_rdata[5]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF23EE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(2),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \slv_rdata_reg[8]_2\(5),
      I3 => \slv_rdata[8]_i_4_n_0\,
      I4 => \slv_rdata_reg[5]_2\,
      I5 => \slv_rdata[7]_i_10_n_0\,
      O => \slv_rdata[5]_i_3_n_0\
    );
\slv_rdata[5]_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_9\(3),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_10\(3),
      O => \slv_rdata[5]_i_3__0_n_0\
    );
\slv_rdata[5]_i_3__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_4\(2),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_3\(2),
      O => \slv_rdata[5]_i_3__1_n_0\
    );
\slv_rdata[5]_i_3__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_8\(2),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_7\(2),
      O => \slv_rdata[5]_i_3__2_n_0\
    );
\slv_rdata[5]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s00_tdata(101),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(37),
      O => \slv_rdata[5]_i_4_n_0\
    );
\slv_rdata[5]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]\(3),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_0\(3),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[5]_i_4__0_n_0\
    );
\slv_rdata[5]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_1\(2),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_2\(2),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[5]_i_4__1_n_0\
    );
\slv_rdata[5]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_5\(2),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_6\(2),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[5]_i_4__2_n_0\
    );
\slv_rdata[5]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0035F035"
    )
        port map (
      I0 => \slv_rdata_reg[5]_3\,
      I1 => s00_tdata(5),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => s00_tdata(69),
      O => \slv_rdata[5]_i_5_n_0\
    );
\slv_rdata[5]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(21),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(85),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[5]_i_6_n_0\
    );
\slv_rdata[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[6]\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[6]_i_3__0_n_0\,
      I4 => \slv_rdata[6]_i_4__0_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_2\(6)
    );
\slv_rdata[6]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[6]_0\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[6]_i_3__1_n_0\,
      I4 => \slv_rdata[6]_i_4__1_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_3\(6)
    );
\slv_rdata[6]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[6]_1\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[6]_i_3__2_n_0\,
      I4 => \slv_rdata[6]_i_4__2_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_4\(6)
    );
\slv_rdata[6]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"22F222F2FFFF22F2"
    )
        port map (
      I0 => \slv_rdata[6]_i_2_n_0\,
      I1 => \slv_rdata[6]_i_3_n_0\,
      I2 => \slv_rdata[7]_i_6_n_0\,
      I3 => \slv_rdata[6]_i_4_n_0\,
      I4 => \slv_rdata[7]_i_3_n_0\,
      I5 => \slv_rdata[6]_i_5_n_0\,
      O => s00_tdata_54_sn_1
    );
\slv_rdata[6]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"E200FFFFE2000000"
    )
        port map (
      I0 => s00_tdata(54),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(118),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \slv_rdata[6]_i_6_n_0\,
      O => \slv_rdata[6]_i_2_n_0\
    );
\slv_rdata[6]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF23EE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(2),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \slv_rdata_reg[8]_2\(6),
      I3 => \slv_rdata[8]_i_4_n_0\,
      I4 => \slv_rdata_reg[6]_2\,
      I5 => \slv_rdata[7]_i_10_n_0\,
      O => \slv_rdata[6]_i_3_n_0\
    );
\slv_rdata[6]_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_9\(4),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_10\(4),
      O => \slv_rdata[6]_i_3__0_n_0\
    );
\slv_rdata[6]_i_3__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_4\(3),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_3\(3),
      O => \slv_rdata[6]_i_3__1_n_0\
    );
\slv_rdata[6]_i_3__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_8\(3),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_7\(3),
      O => \slv_rdata[6]_i_3__2_n_0\
    );
\slv_rdata[6]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"35"
    )
        port map (
      I0 => s00_tdata(38),
      I1 => s00_tdata(102),
      I2 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[6]_i_4_n_0\
    );
\slv_rdata[6]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]\(4),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_0\(4),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[6]_i_4__0_n_0\
    );
\slv_rdata[6]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_1\(3),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_2\(3),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[6]_i_4__1_n_0\
    );
\slv_rdata[6]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_5\(3),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_6\(3),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[6]_i_4__2_n_0\
    );
\slv_rdata[6]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0035F035"
    )
        port map (
      I0 => \slv_rdata_reg[6]_3\,
      I1 => s00_tdata(6),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => s00_tdata(70),
      O => \slv_rdata[6]_i_5_n_0\
    );
\slv_rdata[6]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(22),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(86),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[6]_i_6_n_0\
    );
\slv_rdata[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[7]_11\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[7]_i_3__0_n_0\,
      I4 => \slv_rdata[7]_i_4__0_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_2\(7)
    );
\slv_rdata[7]_i_10\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"FD"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(3),
      I2 => \^slv_addr_reg[11]_0\(5),
      O => \slv_rdata[7]_i_10_n_0\
    );
\slv_rdata[7]_i_12\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"02A2"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => s00_tdata(23),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => s00_tdata(87),
      O => \slv_rdata[7]_i_12_n_0\
    );
\slv_rdata[7]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[7]_12\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[7]_i_3__1_n_0\,
      I4 => \slv_rdata[7]_i_4__1_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_3\(7)
    );
\slv_rdata[7]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000005D5D005D"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \slv_rdata_reg[7]_13\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata[7]_i_3__2_n_0\,
      I4 => \slv_rdata[7]_i_4__2_n_0\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[2]_4\(7)
    );
\slv_rdata[7]_i_2__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F222F222F222FFFF"
    )
        port map (
      I0 => \slv_rdata[7]_i_3_n_0\,
      I1 => \slv_rdata[7]_i_4_n_0\,
      I2 => \slv_rdata[7]_i_5_n_0\,
      I3 => \slv_rdata[7]_i_6_n_0\,
      I4 => \slv_rdata[7]_i_7_n_0\,
      I5 => \slv_rdata[7]_i_8_n_0\,
      O => \slv_addr_reg[5]_1\
    );
\slv_rdata[7]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0001000000010001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(3),
      I1 => \^slv_addr_reg[11]_0\(5),
      I2 => \^slv_addr_reg[11]_0\(1),
      I3 => \^slv_addr_reg[11]_0\(0),
      I4 => \slv_rdata[8]_i_4_n_0\,
      I5 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[7]_i_3_n_0\
    );
\slv_rdata[7]_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_9\(5),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_10\(5),
      O => \slv_rdata[7]_i_3__0_n_0\
    );
\slv_rdata[7]_i_3__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_4\(4),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_3\(4),
      O => \slv_rdata[7]_i_3__1_n_0\
    );
\slv_rdata[7]_i_3__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"ABFB"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_8\(4),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_7\(4),
      O => \slv_rdata[7]_i_3__2_n_0\
    );
\slv_rdata[7]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0035F035"
    )
        port map (
      I0 => \slv_rdata_reg[7]_15\,
      I1 => s00_tdata(7),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => s00_tdata(71),
      O => \slv_rdata[7]_i_4_n_0\
    );
\slv_rdata[7]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]\(5),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_0\(5),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[7]_i_4__0_n_0\
    );
\slv_rdata[7]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_1\(4),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_2\(4),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[7]_i_4__1_n_0\
    );
\slv_rdata[7]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF8A80"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \slv_rdata_reg[7]_5\(4),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \slv_rdata_reg[7]_6\(4),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[7]_i_4__2_n_0\
    );
\slv_rdata[7]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s00_tdata(103),
      I1 => \^slv_addr_reg[11]_0\(2),
      I2 => s00_tdata(39),
      O => \slv_rdata[7]_i_5_n_0\
    );
\slv_rdata[7]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000800000000"
    )
        port map (
      I0 => \slv_rdata[8]_i_4_n_0\,
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \^slv_addr_reg[11]_0\(5),
      I3 => \^slv_addr_reg[11]_0\(3),
      I4 => \^slv_addr_reg[11]_0\(0),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_rdata[7]_i_6_n_0\
    );
\slv_rdata[7]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF23EE"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(2),
      I1 => \^slv_addr_reg[11]_0\(4),
      I2 => \slv_rdata_reg[8]_2\(7),
      I3 => \slv_rdata[8]_i_4_n_0\,
      I4 => \slv_rdata[7]_i_10_n_0\,
      I5 => \slv_rdata_reg[7]_14\,
      O => \slv_rdata[7]_i_7_n_0\
    );
\slv_rdata[7]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"57F7FFFF57F70000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(4),
      I1 => s00_tdata(55),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => s00_tdata(119),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \slv_rdata[7]_i_12_n_0\,
      O => \slv_rdata[7]_i_8_n_0\
    );
\slv_rdata[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0012000000100000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[5]_3\,
      I5 => \slv_rdata_reg[8]\,
      O => \slv_addr_reg[2]_4\(8)
    );
\slv_rdata[8]_i_10\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(24),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(56),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[8]_i_10_n_0\
    );
\slv_rdata[8]_i_11\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(88),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(120),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[8]_i_11_n_0\
    );
\slv_rdata[8]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0012000000100000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[5]_3\,
      I5 => \slv_rdata_reg[8]_0\,
      O => \slv_addr_reg[2]_3\(8)
    );
\slv_rdata[8]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0012000000100000"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(0),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \^slv_addr_reg[11]_0\(4),
      I4 => \^slv_addr_reg[5]_3\,
      I5 => \slv_rdata_reg[8]_1\,
      O => \slv_addr_reg[2]_2\(8)
    );
\slv_rdata[8]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"2000000020002200"
    )
        port map (
      I0 => \slv_rdata_reg[8]_i_2_n_0\,
      I1 => \slv_rdata[8]_i_3_n_0\,
      I2 => \slv_rdata[8]_i_4_n_0\,
      I3 => \^slv_addr_reg[5]_3\,
      I4 => \^slv_addr_reg[11]_0\(4),
      I5 => \^slv_addr_reg[11]_0\(1),
      O => \slv_addr_reg[4]_0\(2)
    );
\slv_rdata[8]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000FF47"
    )
        port map (
      I0 => \slv_rdata_reg[8]_3\(0),
      I1 => \^slv_addr_reg[11]_0\(7),
      I2 => \slv_rdata_reg[8]_2\(8),
      I3 => \^slv_addr_reg[11]_0\(6),
      I4 => \slv_rdata[8]_i_7_n_0\,
      O => \slv_rdata[8]_i_3_n_0\
    );
\slv_rdata[8]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \^slv_addr_reg[11]_0\(7),
      O => \slv_rdata[8]_i_4_n_0\
    );
\slv_rdata[8]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFAACC00F0"
    )
        port map (
      I0 => \slv_rdata[8]_i_3_0\(0),
      I1 => \slv_rdata[8]_i_3_1\(0),
      I2 => \^slv_addr_reg[11]_0\(4),
      I3 => \^slv_addr_reg[11]_0\(7),
      I4 => \^slv_addr_reg[11]_0\(6),
      I5 => \^slv_addr_reg[11]_0\(2),
      O => \slv_rdata[8]_i_7_n_0\
    );
\slv_rdata[8]_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(8),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(40),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[8]_i_8_n_0\
    );
\slv_rdata[8]_i_9\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(72),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(104),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[8]_i_9_n_0\
    );
\slv_rdata[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"222200002A222A22"
    )
        port map (
      I0 => \slv_rdata_reg[9]_i_2_n_0\,
      I1 => \^slv_addr_reg[6]_5\,
      I2 => \^slv_addr_reg[11]_0\(2),
      I3 => \slv_rdata_reg[9]\,
      I4 => \^slv_addr_reg[5]_3\,
      I5 => \slv_rdata[11]_i_5_n_0\,
      O => \slv_addr_reg[4]_0\(3)
    );
\slv_rdata[9]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(9),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(41),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[9]_i_6_n_0\
    );
\slv_rdata[9]_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(73),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(105),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[9]_i_7_n_0\
    );
\slv_rdata[9]_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E2FF"
    )
        port map (
      I0 => s00_tdata(25),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(57),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[9]_i_8_n_0\
    );
\slv_rdata[9]_i_9\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"E200"
    )
        port map (
      I0 => s00_tdata(89),
      I1 => \^slv_addr_reg[11]_0\(1),
      I2 => s00_tdata(121),
      I3 => \^slv_addr_reg[11]_0\(4),
      O => \slv_rdata[9]_i_9_n_0\
    );
\slv_rdata_reg[10]_i_2\: unisim.vcomponents.MUXF8
     port map (
      I0 => \slv_rdata_reg[10]_i_4_n_0\,
      I1 => \slv_rdata_reg[10]_i_5_n_0\,
      O => \slv_rdata_reg[10]_i_2_n_0\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[10]_i_4\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[10]_i_6_n_0\,
      I1 => \slv_rdata[10]_i_7_n_0\,
      O => \slv_rdata_reg[10]_i_4_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
\slv_rdata_reg[10]_i_5\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[10]_i_8_n_0\,
      I1 => \slv_rdata[10]_i_9_n_0\,
      O => \slv_rdata_reg[10]_i_5_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
\slv_rdata_reg[11]_i_2\: unisim.vcomponents.MUXF8
     port map (
      I0 => \slv_rdata_reg[11]_i_7_n_0\,
      I1 => \slv_rdata_reg[11]_i_8_n_0\,
      O => \slv_rdata_reg[11]_i_2_n_0\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[11]_i_7\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[11]_i_9_n_0\,
      I1 => \slv_rdata[11]_i_10_n_0\,
      O => \slv_rdata_reg[11]_i_7_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
\slv_rdata_reg[11]_i_8\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[11]_i_11_n_0\,
      I1 => \slv_rdata[11]_i_12_n_0\,
      O => \slv_rdata_reg[11]_i_8_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
\slv_rdata_reg[12]_i_1\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[12]_i_2_n_0\,
      I1 => \slv_rdata[12]_i_3_n_0\,
      O => \slv_addr_reg[2]_11\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[13]_i_1\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[13]_i_2_n_0\,
      I1 => \slv_rdata[13]_i_3_n_0\,
      O => \slv_addr_reg[2]_10\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[14]_i_1\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[14]_i_2_n_0\,
      I1 => \slv_rdata[14]_i_3_n_0\,
      O => \slv_addr_reg[2]_9\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[15]_i_2\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[15]_i_3_n_0\,
      I1 => \slv_rdata[15]_i_4_n_0\,
      O => \slv_addr_reg[2]_8\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[8]_i_2\: unisim.vcomponents.MUXF8
     port map (
      I0 => \slv_rdata_reg[8]_i_5_n_0\,
      I1 => \slv_rdata_reg[8]_i_6_n_0\,
      O => \slv_rdata_reg[8]_i_2_n_0\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[8]_i_5\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[8]_i_8_n_0\,
      I1 => \slv_rdata[8]_i_9_n_0\,
      O => \slv_rdata_reg[8]_i_5_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
\slv_rdata_reg[8]_i_6\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[8]_i_10_n_0\,
      I1 => \slv_rdata[8]_i_11_n_0\,
      O => \slv_rdata_reg[8]_i_6_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
\slv_rdata_reg[9]_i_2\: unisim.vcomponents.MUXF8
     port map (
      I0 => \slv_rdata_reg[9]_i_4_n_0\,
      I1 => \slv_rdata_reg[9]_i_5_n_0\,
      O => \slv_rdata_reg[9]_i_2_n_0\,
      S => \^slv_addr_reg[11]_0\(0)
    );
\slv_rdata_reg[9]_i_4\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[9]_i_6_n_0\,
      I1 => \slv_rdata[9]_i_7_n_0\,
      O => \slv_rdata_reg[9]_i_4_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
\slv_rdata_reg[9]_i_5\: unisim.vcomponents.MUXF7
     port map (
      I0 => \slv_rdata[9]_i_8_n_0\,
      I1 => \slv_rdata[9]_i_9_n_0\,
      O => \slv_rdata_reg[9]_i_5_n_0\,
      S => \^slv_addr_reg[11]_0\(2)
    );
slv_reg_rden_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"75553000"
    )
        port map (
      I0 => \axi_rresp[1]_i_2_n_0\,
      I1 => \^axi_rvalid_reg_0\,
      I2 => s_axi_arvalid,
      I3 => \^axi_arready_reg_0\,
      I4 => slv_reg_rden,
      O => slv_reg_rden_i_1_n_0
    );
slv_reg_rden_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => slv_reg_rden_i_1_n_0,
      Q => slv_reg_rden,
      R => p_0_in
    );
\slv_wdata_r_internal[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F444"
    )
        port map (
      I0 => slv_rden_r_0,
      I1 => \^adc0slv_rden\,
      I2 => \^adc0axi_map_wready\,
      I3 => s_axi_wvalid,
      O => slv_rden_r_reg(0)
    );
\slv_wdata_r_internal[11]_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F444"
    )
        port map (
      I0 => slv_rden_r_1,
      I1 => \^adc1slv_rden\,
      I2 => \^adc1axi_map_wready\,
      I3 => s_axi_wvalid,
      O => slv_rden_r_reg_0(0)
    );
\slv_wdata_r_internal[11]_i_1__1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F444"
    )
        port map (
      I0 => slv_rden_r_2,
      I1 => \^adc2slv_rden\,
      I2 => \^adc2axi_map_wready\,
      I3 => s_axi_wvalid,
      O => slv_rden_r_reg_1(0)
    );
\slv_wdata_r_internal[11]_i_1__2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F444"
    )
        port map (
      I0 => slv_rden_r,
      I1 => \^adc3slv_rden\,
      I2 => \^adc3axi_map_wready\,
      I3 => s_axi_wvalid,
      O => slv_rden_r_reg_2(0)
    );
timeout_enable_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFB0008"
    )
        port map (
      I0 => s_axi_wdata(0),
      I1 => timeout_enable_i_2_n_0,
      I2 => \^slv_addr_reg[11]_0\(0),
      I3 => \^slv_addr_reg[11]_0\(1),
      I4 => timeout_enable,
      O => \s_axi_wdata[0]_0\
    );
timeout_enable_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000080"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(2),
      I1 => s_axi_wvalid,
      I2 => \^adc_ds_axi_map_wready\,
      I3 => \^slv_addr_reg[8]_0\,
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \^slv_addr_reg[11]_0\(4),
      O => timeout_enable_i_2_n_0
    );
\timeout_timer_count[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"47"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(0),
      I1 => \timeout_timer_count[12]_i_5_n_0\,
      I2 => \timeout_timer_count_reg_n_0_[0]\,
      O => p_2_in(0)
    );
\timeout_timer_count[10]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4774"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(10),
      I1 => \timeout_timer_count[12]_i_5_n_0\,
      I2 => \timeout_timer_count_reg_n_0_[10]\,
      I3 => \timeout_timer_count[10]_i_2_n_0\,
      O => p_2_in(10)
    );
\timeout_timer_count[10]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00800000"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[9]\,
      I1 => \timeout_timer_count_reg_n_0_[7]\,
      I2 => \timeout_timer_count_reg_n_0_[6]\,
      I3 => \timeout_timer_count[8]_i_2_n_0\,
      I4 => \timeout_timer_count_reg_n_0_[8]\,
      O => \timeout_timer_count[10]_i_2_n_0\
    );
\timeout_timer_count[11]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4774"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(11),
      I1 => \timeout_timer_count[12]_i_5_n_0\,
      I2 => \timeout_timer_count_reg_n_0_[11]\,
      I3 => \timeout_timer_count[12]_i_6_n_0\,
      O => p_2_in(11)
    );
\timeout_timer_count[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF8FFF8FFF8FF"
    )
        port map (
      I0 => s_axi_rready,
      I1 => \^axi_rvalid_reg_0\,
      I2 => timeout,
      I3 => s_axi_aresetn,
      I4 => \^axi_bvalid_reg_0\,
      I5 => s_axi_bready,
      O => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count[12]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => \timeout_timer_count[12]_i_4_n_0\,
      I1 => \timeout_timer_count[12]_i_5_n_0\,
      O => \timeout_timer_count[12]_i_2_n_0\
    );
\timeout_timer_count[12]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[11]\,
      I1 => \timeout_timer_count[12]_i_6_n_0\,
      I2 => \timeout_timer_count[12]_i_5_n_0\,
      O => p_2_in(12)
    );
\timeout_timer_count[12]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAAAA8AAAAAAAA"
    )
        port map (
      I0 => timeout_enable,
      I1 => \timeout_timer_count_reg_n_0_[2]\,
      I2 => \timeout_timer_count_reg_n_0_[7]\,
      I3 => \timeout_timer_count_reg_n_0_[9]\,
      I4 => \timeout_timer_count[12]_i_7_n_0\,
      I5 => \timeout_timer_count[12]_i_8_n_0\,
      O => \timeout_timer_count[12]_i_4_n_0\
    );
\timeout_timer_count[12]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAA888A888A888"
    )
        port map (
      I0 => timeout_enable,
      I1 => load_timeout_timer0,
      I2 => s_axi_awvalid,
      I3 => \^axi_awready_reg_0\,
      I4 => \^axi_wr_access_reg_0\,
      I5 => s_axi_wvalid,
      O => \timeout_timer_count[12]_i_5_n_0\
    );
\timeout_timer_count[12]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0800000000000000"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[10]\,
      I1 => \timeout_timer_count_reg_n_0_[8]\,
      I2 => \timeout_timer_count[8]_i_2_n_0\,
      I3 => \timeout_timer_count_reg_n_0_[6]\,
      I4 => \timeout_timer_count_reg_n_0_[7]\,
      I5 => \timeout_timer_count_reg_n_0_[9]\,
      O => \timeout_timer_count[12]_i_6_n_0\
    );
\timeout_timer_count[12]_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[11]\,
      I1 => \timeout_timer_count_reg_n_0_[10]\,
      I2 => \timeout_timer_count_reg_n_0_[5]\,
      I3 => \timeout_timer_count_reg_n_0_[3]\,
      O => \timeout_timer_count[12]_i_7_n_0\
    );
\timeout_timer_count[12]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[1]\,
      I1 => \timeout_timer_count_reg_n_0_[0]\,
      I2 => timeout,
      I3 => \timeout_timer_count_reg_n_0_[8]\,
      I4 => \timeout_timer_count_reg_n_0_[4]\,
      I5 => \timeout_timer_count_reg_n_0_[6]\,
      O => \timeout_timer_count[12]_i_8_n_0\
    );
\timeout_timer_count[12]_i_9\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => s_axi_arvalid,
      I1 => \^axi_arready_reg_0\,
      O => load_timeout_timer0
    );
\timeout_timer_count[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4774"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(1),
      I1 => \timeout_timer_count[12]_i_5_n_0\,
      I2 => \timeout_timer_count_reg_n_0_[0]\,
      I3 => \timeout_timer_count_reg_n_0_[1]\,
      O => p_2_in(1)
    );
\timeout_timer_count[2]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"55553CCC"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(2),
      I1 => \timeout_timer_count_reg_n_0_[2]\,
      I2 => \timeout_timer_count_reg_n_0_[1]\,
      I3 => \timeout_timer_count_reg_n_0_[0]\,
      I4 => \timeout_timer_count[12]_i_5_n_0\,
      O => p_2_in(2)
    );
\timeout_timer_count[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"555555553CCCCCCC"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(3),
      I1 => \timeout_timer_count_reg_n_0_[3]\,
      I2 => \timeout_timer_count_reg_n_0_[2]\,
      I3 => \timeout_timer_count_reg_n_0_[0]\,
      I4 => \timeout_timer_count_reg_n_0_[1]\,
      I5 => \timeout_timer_count[12]_i_5_n_0\,
      O => p_2_in(3)
    );
\timeout_timer_count[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"55C3"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(4),
      I1 => \timeout_timer_count_reg_n_0_[4]\,
      I2 => \timeout_timer_count[4]_i_2_n_0\,
      I3 => \timeout_timer_count[12]_i_5_n_0\,
      O => p_2_in(4)
    );
\timeout_timer_count[4]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7FFF"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[2]\,
      I1 => \timeout_timer_count_reg_n_0_[0]\,
      I2 => \timeout_timer_count_reg_n_0_[1]\,
      I3 => \timeout_timer_count_reg_n_0_[3]\,
      O => \timeout_timer_count[4]_i_2_n_0\
    );
\timeout_timer_count[5]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"55C3"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(5),
      I1 => \timeout_timer_count_reg_n_0_[5]\,
      I2 => \timeout_timer_count[5]_i_2_n_0\,
      I3 => \timeout_timer_count[12]_i_5_n_0\,
      O => p_2_in(5)
    );
\timeout_timer_count[5]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7FFFFFFF"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[3]\,
      I1 => \timeout_timer_count_reg_n_0_[1]\,
      I2 => \timeout_timer_count_reg_n_0_[0]\,
      I3 => \timeout_timer_count_reg_n_0_[2]\,
      I4 => \timeout_timer_count_reg_n_0_[4]\,
      O => \timeout_timer_count[5]_i_2_n_0\
    );
\timeout_timer_count[6]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"55C3"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(6),
      I1 => \timeout_timer_count_reg_n_0_[6]\,
      I2 => \timeout_timer_count[8]_i_2_n_0\,
      I3 => \timeout_timer_count[12]_i_5_n_0\,
      O => p_2_in(6)
    );
\timeout_timer_count[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"5555CC3C"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(7),
      I1 => \timeout_timer_count_reg_n_0_[7]\,
      I2 => \timeout_timer_count_reg_n_0_[6]\,
      I3 => \timeout_timer_count[8]_i_2_n_0\,
      I4 => \timeout_timer_count[12]_i_5_n_0\,
      O => p_2_in(7)
    );
\timeout_timer_count[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7447747474747474"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(8),
      I1 => \timeout_timer_count[12]_i_5_n_0\,
      I2 => \timeout_timer_count_reg_n_0_[8]\,
      I3 => \timeout_timer_count[8]_i_2_n_0\,
      I4 => \timeout_timer_count_reg_n_0_[6]\,
      I5 => \timeout_timer_count_reg_n_0_[7]\,
      O => p_2_in(8)
    );
\timeout_timer_count[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFFFFFFFFFF"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[4]\,
      I1 => \timeout_timer_count_reg_n_0_[2]\,
      I2 => \timeout_timer_count_reg_n_0_[0]\,
      I3 => \timeout_timer_count_reg_n_0_[1]\,
      I4 => \timeout_timer_count_reg_n_0_[3]\,
      I5 => \timeout_timer_count_reg_n_0_[5]\,
      O => \timeout_timer_count[8]_i_2_n_0\
    );
\timeout_timer_count[9]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4774"
    )
        port map (
      I0 => \axi_rdata_reg[11]_1\(9),
      I1 => \timeout_timer_count[12]_i_5_n_0\,
      I2 => \timeout_timer_count_reg_n_0_[9]\,
      I3 => \timeout_timer_count[9]_i_2_n_0\,
      O => p_2_in(9)
    );
\timeout_timer_count[9]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2000"
    )
        port map (
      I0 => \timeout_timer_count_reg_n_0_[8]\,
      I1 => \timeout_timer_count[8]_i_2_n_0\,
      I2 => \timeout_timer_count_reg_n_0_[6]\,
      I3 => \timeout_timer_count_reg_n_0_[7]\,
      O => \timeout_timer_count[9]_i_2_n_0\
    );
\timeout_timer_count_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(0),
      Q => \timeout_timer_count_reg_n_0_[0]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(10),
      Q => \timeout_timer_count_reg_n_0_[10]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(11),
      Q => \timeout_timer_count_reg_n_0_[11]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(12),
      Q => timeout,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(1),
      Q => \timeout_timer_count_reg_n_0_[1]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(2),
      Q => \timeout_timer_count_reg_n_0_[2]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(3),
      Q => \timeout_timer_count_reg_n_0_[3]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(4),
      Q => \timeout_timer_count_reg_n_0_[4]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(5),
      Q => \timeout_timer_count_reg_n_0_[5]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(6),
      Q => \timeout_timer_count_reg_n_0_[6]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(7),
      Q => \timeout_timer_count_reg_n_0_[7]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(8),
      Q => \timeout_timer_count_reg_n_0_[8]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_timer_count_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => \timeout_timer_count[12]_i_2_n_0\,
      D => p_2_in(9),
      Q => \timeout_timer_count_reg_n_0_[9]\,
      R => \timeout_timer_count[12]_i_1_n_0\
    );
\timeout_value[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000080000000"
    )
        port map (
      I0 => \timeout_value[11]_i_2_n_0\,
      I1 => \^adc_ds_axi_map_wready\,
      I2 => s_axi_wvalid,
      I3 => \^slv_addr_reg[11]_0\(2),
      I4 => \^slv_addr_reg[11]_0\(1),
      I5 => \^slv_addr_reg[11]_0\(0),
      O => E(0)
    );
\timeout_value[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \^slv_addr_reg[11]_0\(6),
      I1 => \^slv_addr_reg[11]_0\(5),
      I2 => \^slv_addr_reg[11]_0\(7),
      I3 => \axi_rdata[15]_i_4_n_0\,
      I4 => \^slv_addr_reg[11]_0\(3),
      I5 => \^slv_addr_reg[11]_0\(4),
      O => \timeout_value[11]_i_2_n_0\
    );
valid_waddr_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F1F1000100000000"
    )
        port map (
      I0 => timeout,
      I1 => valid_waddr_i_2_n_0,
      I2 => valid_waddr_i_3_n_0,
      I3 => valid_waddr_i_4_n_0,
      I4 => valid_waddr_reg_n_0,
      I5 => s_axi_aresetn,
      O => valid_waddr_i_1_n_0
    );
valid_waddr_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^axi_bvalid_reg_0\,
      I1 => s_axi_bready,
      O => valid_waddr_i_2_n_0
    );
valid_waddr_i_3: unisim.vcomponents.LUT3
    generic map(
      INIT => X"54"
    )
        port map (
      I0 => timeout,
      I1 => s_axi_arvalid,
      I2 => read_in_progress,
      O => valid_waddr_i_3_n_0
    );
valid_waddr_i_4: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^axi_awready_reg_0\,
      I1 => s_axi_awvalid,
      O => valid_waddr_i_4_n_0
    );
valid_waddr_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => valid_waddr_i_1_n_0,
      Q => valid_waddr_reg_n_0,
      R => '0'
    );
write_in_progress_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000FFFFF888"
    )
        port map (
      I0 => s_axi_awvalid,
      I1 => \^axi_awready_reg_0\,
      I2 => \^axi_wr_access_reg_0\,
      I3 => s_axi_wvalid,
      I4 => write_in_progress,
      I5 => write_in_progress_i_2_n_0,
      O => write_in_progress_i_1_n_0
    );
write_in_progress_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FF8F"
    )
        port map (
      I0 => s_axi_bready,
      I1 => \^axi_bvalid_reg_0\,
      I2 => s_axi_aresetn,
      I3 => timeout,
      O => write_in_progress_i_2_n_0
    );
write_in_progress_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => write_in_progress_i_1_n_0,
      Q => write_in_progress,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is 0;
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single : entity is "SINGLE";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ is
  port (
    src_clk : in STD_LOGIC;
    src_in : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_out : out STD_LOGIC
  );
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is 0;
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is "xpm_cdc_single";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ : entity is "SINGLE";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\ is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SINGLE";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SINGLE";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SINGLE";
begin
  dest_out <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => src_in,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst is
  port (
    src_rst : in STD_LOGIC;
    dest_clk : in STD_LOGIC;
    dest_rst : out STD_LOGIC
  );
  attribute DEF_VAL : string;
  attribute DEF_VAL of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is "1'b0";
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is 5;
  attribute INIT : string;
  attribute INIT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is "0";
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is 1;
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is 0;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is "true";
  attribute xpm_cdc : string;
  attribute xpm_cdc of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst : entity is "SYNC_RST";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst is
  signal syncstages_ff : STD_LOGIC_VECTOR ( 4 downto 0 );
  attribute RTL_KEEP : string;
  attribute RTL_KEEP of syncstages_ff : signal is "true";
  attribute async_reg : string;
  attribute async_reg of syncstages_ff : signal is "true";
  attribute xpm_cdc of syncstages_ff : signal is "SYNC_RST";
  attribute ASYNC_REG_boolean : boolean;
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[0]\ : label is std.standard.true;
  attribute KEEP : string;
  attribute KEEP of \syncstages_ff_reg[0]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[0]\ : label is "SYNC_RST";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[1]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[1]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[1]\ : label is "SYNC_RST";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[2]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[2]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[2]\ : label is "SYNC_RST";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[3]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[3]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[3]\ : label is "SYNC_RST";
  attribute ASYNC_REG_boolean of \syncstages_ff_reg[4]\ : label is std.standard.true;
  attribute KEEP of \syncstages_ff_reg[4]\ : label is "true";
  attribute XPM_CDC of \syncstages_ff_reg[4]\ : label is "SYNC_RST";
begin
  dest_rst <= syncstages_ff(4);
\syncstages_ff_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => dest_clk,
      CE => '1',
      D => src_rst,
      Q => syncstages_ff(0),
      R => '0'
    );
\syncstages_ff_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(0),
      Q => syncstages_ff(1),
      R => '0'
    );
\syncstages_ff_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(1),
      Q => syncstages_ff(2),
      R => '0'
    );
\syncstages_ff_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(2),
      Q => syncstages_ff(3),
      R => '0'
    );
\syncstages_ff_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => dest_clk,
      CE => '1',
      D => syncstages_ff(3),
      Q => syncstages_ff(4),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base is
  port (
    sleep : in STD_LOGIC;
    clka : in STD_LOGIC;
    rsta : in STD_LOGIC;
    ena : in STD_LOGIC;
    regcea : in STD_LOGIC;
    wea : in STD_LOGIC_VECTOR ( 0 to 0 );
    addra : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dina : in STD_LOGIC_VECTOR ( 127 downto 0 );
    injectsbiterra : in STD_LOGIC;
    injectdbiterra : in STD_LOGIC;
    douta : out STD_LOGIC_VECTOR ( 127 downto 0 );
    sbiterra : out STD_LOGIC;
    dbiterra : out STD_LOGIC;
    clkb : in STD_LOGIC;
    rstb : in STD_LOGIC;
    enb : in STD_LOGIC;
    regceb : in STD_LOGIC;
    web : in STD_LOGIC_VECTOR ( 0 to 0 );
    addrb : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dinb : in STD_LOGIC_VECTOR ( 127 downto 0 );
    injectsbiterrb : in STD_LOGIC;
    injectdbiterrb : in STD_LOGIC;
    doutb : out STD_LOGIC_VECTOR ( 127 downto 0 );
    sbiterrb : out STD_LOGIC;
    dbiterrb : out STD_LOGIC
  );
  attribute ADDR_WIDTH_A : integer;
  attribute ADDR_WIDTH_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 8;
  attribute ADDR_WIDTH_B : integer;
  attribute ADDR_WIDTH_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 8;
  attribute AUTO_SLEEP_TIME : integer;
  attribute AUTO_SLEEP_TIME of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute BYTE_WRITE_WIDTH_A : integer;
  attribute BYTE_WRITE_WIDTH_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute BYTE_WRITE_WIDTH_B : integer;
  attribute BYTE_WRITE_WIDTH_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute CASCADE_HEIGHT : integer;
  attribute CASCADE_HEIGHT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute CLOCKING_MODE : integer;
  attribute CLOCKING_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute ECC_MODE : integer;
  attribute ECC_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute MAX_NUM_CHAR : integer;
  attribute MAX_NUM_CHAR of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute MEMORY_INIT_FILE : string;
  attribute MEMORY_INIT_FILE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "none";
  attribute MEMORY_INIT_PARAM : string;
  attribute MEMORY_INIT_PARAM of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "";
  attribute MEMORY_OPTIMIZATION : string;
  attribute MEMORY_OPTIMIZATION of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "true";
  attribute MEMORY_PRIMITIVE : integer;
  attribute MEMORY_PRIMITIVE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute MEMORY_SIZE : integer;
  attribute MEMORY_SIZE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 32768;
  attribute MEMORY_TYPE : integer;
  attribute MEMORY_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute MESSAGE_CONTROL : integer;
  attribute MESSAGE_CONTROL of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute NUM_CHAR_LOC : integer;
  attribute NUM_CHAR_LOC of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute P_ECC_MODE : string;
  attribute P_ECC_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "no_ecc";
  attribute P_ENABLE_BYTE_WRITE_A : integer;
  attribute P_ENABLE_BYTE_WRITE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute P_ENABLE_BYTE_WRITE_B : integer;
  attribute P_ENABLE_BYTE_WRITE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute P_MAX_DEPTH_DATA : integer;
  attribute P_MAX_DEPTH_DATA of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 256;
  attribute P_MEMORY_OPT : string;
  attribute P_MEMORY_OPT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "yes";
  attribute P_MEMORY_PRIMITIVE : string;
  attribute P_MEMORY_PRIMITIVE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "auto";
  attribute P_MIN_WIDTH_DATA : integer;
  attribute P_MIN_WIDTH_DATA of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute P_MIN_WIDTH_DATA_A : integer;
  attribute P_MIN_WIDTH_DATA_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute P_MIN_WIDTH_DATA_B : integer;
  attribute P_MIN_WIDTH_DATA_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute P_MIN_WIDTH_DATA_ECC : integer;
  attribute P_MIN_WIDTH_DATA_ECC of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute P_MIN_WIDTH_DATA_LDW : integer;
  attribute P_MIN_WIDTH_DATA_LDW of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 4;
  attribute P_MIN_WIDTH_DATA_SHFT : integer;
  attribute P_MIN_WIDTH_DATA_SHFT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute P_NUM_COLS_WRITE_A : integer;
  attribute P_NUM_COLS_WRITE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute P_NUM_COLS_WRITE_B : integer;
  attribute P_NUM_COLS_WRITE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute P_NUM_ROWS_READ_A : integer;
  attribute P_NUM_ROWS_READ_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute P_NUM_ROWS_READ_B : integer;
  attribute P_NUM_ROWS_READ_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute P_NUM_ROWS_WRITE_A : integer;
  attribute P_NUM_ROWS_WRITE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute P_NUM_ROWS_WRITE_B : integer;
  attribute P_NUM_ROWS_WRITE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute P_SDP_WRITE_MODE : string;
  attribute P_SDP_WRITE_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "yes";
  attribute P_WIDTH_ADDR_LSB_READ_A : integer;
  attribute P_WIDTH_ADDR_LSB_READ_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute P_WIDTH_ADDR_LSB_READ_B : integer;
  attribute P_WIDTH_ADDR_LSB_READ_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute P_WIDTH_ADDR_LSB_WRITE_A : integer;
  attribute P_WIDTH_ADDR_LSB_WRITE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute P_WIDTH_ADDR_LSB_WRITE_B : integer;
  attribute P_WIDTH_ADDR_LSB_WRITE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute P_WIDTH_ADDR_READ_A : integer;
  attribute P_WIDTH_ADDR_READ_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 8;
  attribute P_WIDTH_ADDR_READ_B : integer;
  attribute P_WIDTH_ADDR_READ_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 8;
  attribute P_WIDTH_ADDR_WRITE_A : integer;
  attribute P_WIDTH_ADDR_WRITE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 8;
  attribute P_WIDTH_ADDR_WRITE_B : integer;
  attribute P_WIDTH_ADDR_WRITE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 8;
  attribute P_WIDTH_COL_WRITE_A : integer;
  attribute P_WIDTH_COL_WRITE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute P_WIDTH_COL_WRITE_B : integer;
  attribute P_WIDTH_COL_WRITE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute READ_DATA_WIDTH_A : integer;
  attribute READ_DATA_WIDTH_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute READ_DATA_WIDTH_B : integer;
  attribute READ_DATA_WIDTH_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute READ_LATENCY_A : integer;
  attribute READ_LATENCY_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 2;
  attribute READ_LATENCY_B : integer;
  attribute READ_LATENCY_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 2;
  attribute READ_RESET_VALUE_A : string;
  attribute READ_RESET_VALUE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "0";
  attribute READ_RESET_VALUE_B : string;
  attribute READ_RESET_VALUE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "0";
  attribute RST_MODE_A : string;
  attribute RST_MODE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "SYNC";
  attribute RST_MODE_B : string;
  attribute RST_MODE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "SYNC";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute USE_EMBEDDED_CONSTRAINT : integer;
  attribute USE_EMBEDDED_CONSTRAINT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute USE_MEM_INIT : integer;
  attribute USE_MEM_INIT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute USE_MEM_INIT_MMI : integer;
  attribute USE_MEM_INIT_MMI of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute VERSION : integer;
  attribute VERSION of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute WAKEUP_TIME : integer;
  attribute WAKEUP_TIME of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 0;
  attribute WRITE_DATA_WIDTH_A : integer;
  attribute WRITE_DATA_WIDTH_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute WRITE_DATA_WIDTH_B : integer;
  attribute WRITE_DATA_WIDTH_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute WRITE_MODE_A : integer;
  attribute WRITE_MODE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 2;
  attribute WRITE_MODE_B : integer;
  attribute WRITE_MODE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 2;
  attribute WRITE_PROTECT : integer;
  attribute WRITE_PROTECT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 1;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "TRUE";
  attribute keep_hierarchy : string;
  attribute keep_hierarchy of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is "soft";
  attribute rsta_loop_iter : integer;
  attribute rsta_loop_iter of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
  attribute rstb_loop_iter : integer;
  attribute rstb_loop_iter of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base : entity is 128;
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base is
  signal \<const0>\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_100\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_101\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_102\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_103\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_104\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_105\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_106\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_107\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_108\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_109\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_110\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_111\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_112\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_113\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_114\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_115\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_116\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_117\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_118\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_119\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_120\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_121\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_122\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_123\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_124\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_125\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_126\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_127\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_128\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_129\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_130\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_131\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_140\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_141\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_142\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_143\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_144\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_145\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_146\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_147\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_68\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_69\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_70\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_71\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_72\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_73\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_74\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_75\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_76\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_77\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_78\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_79\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_80\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_81\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_82\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_83\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_84\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_85\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_86\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_87\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_88\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_89\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_90\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_91\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_92\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_93\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_94\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_95\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_96\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_97\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_98\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_0_n_99\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_108\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_109\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_110\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_111\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_112\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_113\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_114\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_115\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_116\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_117\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_118\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_119\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_120\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_121\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_122\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_123\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_124\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_125\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_126\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_127\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_128\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_129\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_130\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_131\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_68\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_69\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_70\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_71\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_72\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_73\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_74\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_75\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_76\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_77\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_78\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_79\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_80\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_81\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_82\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_83\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_84\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_85\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_86\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_87\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_88\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_89\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_90\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_91\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_92\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_93\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_94\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_95\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_96\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_97\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_98\ : STD_LOGIC;
  signal \gen_wr_a.gen_word_narrow.mem_reg_1_n_99\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTDBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTSBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_DBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_SBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_ECCPARITY_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_RDADDRECC_UNCONNECTED\ : STD_LOGIC_VECTOR ( 8 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTDBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTSBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_SBITERR_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPA_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPB_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTBDOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 31 downto 24 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPADOUTP_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPBDOUTP_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_ECCPARITY_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_RDADDRECC_UNCONNECTED\ : STD_LOGIC_VECTOR ( 8 downto 0 );
  attribute \MEM.PORTA.ADDRESS_BEGIN\ : integer;
  attribute \MEM.PORTA.ADDRESS_BEGIN\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute \MEM.PORTA.ADDRESS_END\ : integer;
  attribute \MEM.PORTA.ADDRESS_END\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 511;
  attribute \MEM.PORTA.DATA_BIT_LAYOUT\ : string;
  attribute \MEM.PORTA.DATA_BIT_LAYOUT\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is "p8_d64";
  attribute \MEM.PORTA.DATA_LSB\ : integer;
  attribute \MEM.PORTA.DATA_LSB\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute \MEM.PORTA.DATA_MSB\ : integer;
  attribute \MEM.PORTA.DATA_MSB\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 71;
  attribute \MEM.PORTB.ADDRESS_BEGIN\ : integer;
  attribute \MEM.PORTB.ADDRESS_BEGIN\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute \MEM.PORTB.ADDRESS_END\ : integer;
  attribute \MEM.PORTB.ADDRESS_END\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 511;
  attribute \MEM.PORTB.DATA_BIT_LAYOUT\ : string;
  attribute \MEM.PORTB.DATA_BIT_LAYOUT\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is "p8_d64";
  attribute \MEM.PORTB.DATA_LSB\ : integer;
  attribute \MEM.PORTB.DATA_LSB\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute \MEM.PORTB.DATA_MSB\ : integer;
  attribute \MEM.PORTB.DATA_MSB\ of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 71;
  attribute METHODOLOGY_DRC_VIOS : string;
  attribute METHODOLOGY_DRC_VIOS of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is "{SYNTH-6 {cell *THIS*}}";
  attribute RDADDR_COLLISION_HWCONFIG : string;
  attribute RDADDR_COLLISION_HWCONFIG of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is "DELAYED_WRITE";
  attribute RTL_RAM_BITS : integer;
  attribute RTL_RAM_BITS of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 32768;
  attribute RTL_RAM_NAME : string;
  attribute RTL_RAM_NAME of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is "gen_wr_a.gen_word_narrow.mem";
  attribute RTL_RAM_TYPE : string;
  attribute RTL_RAM_TYPE of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is "RAM_SDP";
  attribute bram_addr_begin : integer;
  attribute bram_addr_begin of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute bram_addr_end : integer;
  attribute bram_addr_end of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 511;
  attribute bram_slice_begin : integer;
  attribute bram_slice_begin of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute bram_slice_end : integer;
  attribute bram_slice_end of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 71;
  attribute ram_addr_begin : integer;
  attribute ram_addr_begin of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute ram_addr_end : integer;
  attribute ram_addr_end of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 511;
  attribute ram_offset : integer;
  attribute ram_offset of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute ram_slice_begin : integer;
  attribute ram_slice_begin of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 0;
  attribute ram_slice_end : integer;
  attribute ram_slice_end of \gen_wr_a.gen_word_narrow.mem_reg_0\ : label is 71;
  attribute \MEM.PORTA.ADDRESS_BEGIN\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 0;
  attribute \MEM.PORTA.ADDRESS_END\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 511;
  attribute \MEM.PORTA.DATA_BIT_LAYOUT\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is "p0_d56";
  attribute \MEM.PORTA.DATA_LSB\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 72;
  attribute \MEM.PORTA.DATA_MSB\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 127;
  attribute \MEM.PORTB.ADDRESS_BEGIN\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 0;
  attribute \MEM.PORTB.ADDRESS_END\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 511;
  attribute \MEM.PORTB.DATA_BIT_LAYOUT\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is "p0_d56";
  attribute \MEM.PORTB.DATA_LSB\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 72;
  attribute \MEM.PORTB.DATA_MSB\ of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 127;
  attribute METHODOLOGY_DRC_VIOS of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is "{SYNTH-6 {cell *THIS*}}";
  attribute RDADDR_COLLISION_HWCONFIG of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is "DELAYED_WRITE";
  attribute RTL_RAM_BITS of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 32768;
  attribute RTL_RAM_NAME of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is "gen_wr_a.gen_word_narrow.mem";
  attribute RTL_RAM_TYPE of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is "RAM_SDP";
  attribute bram_addr_begin of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 0;
  attribute bram_addr_end of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 511;
  attribute bram_slice_begin of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 72;
  attribute bram_slice_end of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 127;
  attribute ram_addr_begin of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 0;
  attribute ram_addr_end of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 511;
  attribute ram_offset of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 0;
  attribute ram_slice_begin of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 72;
  attribute ram_slice_end of \gen_wr_a.gen_word_narrow.mem_reg_1\ : label is 127;
begin
  dbiterra <= \<const0>\;
  dbiterrb <= \<const0>\;
  douta(127) <= \<const0>\;
  douta(126) <= \<const0>\;
  douta(125) <= \<const0>\;
  douta(124) <= \<const0>\;
  douta(123) <= \<const0>\;
  douta(122) <= \<const0>\;
  douta(121) <= \<const0>\;
  douta(120) <= \<const0>\;
  douta(119) <= \<const0>\;
  douta(118) <= \<const0>\;
  douta(117) <= \<const0>\;
  douta(116) <= \<const0>\;
  douta(115) <= \<const0>\;
  douta(114) <= \<const0>\;
  douta(113) <= \<const0>\;
  douta(112) <= \<const0>\;
  douta(111) <= \<const0>\;
  douta(110) <= \<const0>\;
  douta(109) <= \<const0>\;
  douta(108) <= \<const0>\;
  douta(107) <= \<const0>\;
  douta(106) <= \<const0>\;
  douta(105) <= \<const0>\;
  douta(104) <= \<const0>\;
  douta(103) <= \<const0>\;
  douta(102) <= \<const0>\;
  douta(101) <= \<const0>\;
  douta(100) <= \<const0>\;
  douta(99) <= \<const0>\;
  douta(98) <= \<const0>\;
  douta(97) <= \<const0>\;
  douta(96) <= \<const0>\;
  douta(95) <= \<const0>\;
  douta(94) <= \<const0>\;
  douta(93) <= \<const0>\;
  douta(92) <= \<const0>\;
  douta(91) <= \<const0>\;
  douta(90) <= \<const0>\;
  douta(89) <= \<const0>\;
  douta(88) <= \<const0>\;
  douta(87) <= \<const0>\;
  douta(86) <= \<const0>\;
  douta(85) <= \<const0>\;
  douta(84) <= \<const0>\;
  douta(83) <= \<const0>\;
  douta(82) <= \<const0>\;
  douta(81) <= \<const0>\;
  douta(80) <= \<const0>\;
  douta(79) <= \<const0>\;
  douta(78) <= \<const0>\;
  douta(77) <= \<const0>\;
  douta(76) <= \<const0>\;
  douta(75) <= \<const0>\;
  douta(74) <= \<const0>\;
  douta(73) <= \<const0>\;
  douta(72) <= \<const0>\;
  douta(71) <= \<const0>\;
  douta(70) <= \<const0>\;
  douta(69) <= \<const0>\;
  douta(68) <= \<const0>\;
  douta(67) <= \<const0>\;
  douta(66) <= \<const0>\;
  douta(65) <= \<const0>\;
  douta(64) <= \<const0>\;
  douta(63) <= \<const0>\;
  douta(62) <= \<const0>\;
  douta(61) <= \<const0>\;
  douta(60) <= \<const0>\;
  douta(59) <= \<const0>\;
  douta(58) <= \<const0>\;
  douta(57) <= \<const0>\;
  douta(56) <= \<const0>\;
  douta(55) <= \<const0>\;
  douta(54) <= \<const0>\;
  douta(53) <= \<const0>\;
  douta(52) <= \<const0>\;
  douta(51) <= \<const0>\;
  douta(50) <= \<const0>\;
  douta(49) <= \<const0>\;
  douta(48) <= \<const0>\;
  douta(47) <= \<const0>\;
  douta(46) <= \<const0>\;
  douta(45) <= \<const0>\;
  douta(44) <= \<const0>\;
  douta(43) <= \<const0>\;
  douta(42) <= \<const0>\;
  douta(41) <= \<const0>\;
  douta(40) <= \<const0>\;
  douta(39) <= \<const0>\;
  douta(38) <= \<const0>\;
  douta(37) <= \<const0>\;
  douta(36) <= \<const0>\;
  douta(35) <= \<const0>\;
  douta(34) <= \<const0>\;
  douta(33) <= \<const0>\;
  douta(32) <= \<const0>\;
  douta(31) <= \<const0>\;
  douta(30) <= \<const0>\;
  douta(29) <= \<const0>\;
  douta(28) <= \<const0>\;
  douta(27) <= \<const0>\;
  douta(26) <= \<const0>\;
  douta(25) <= \<const0>\;
  douta(24) <= \<const0>\;
  douta(23) <= \<const0>\;
  douta(22) <= \<const0>\;
  douta(21) <= \<const0>\;
  douta(20) <= \<const0>\;
  douta(19) <= \<const0>\;
  douta(18) <= \<const0>\;
  douta(17) <= \<const0>\;
  douta(16) <= \<const0>\;
  douta(15) <= \<const0>\;
  douta(14) <= \<const0>\;
  douta(13) <= \<const0>\;
  douta(12) <= \<const0>\;
  douta(11) <= \<const0>\;
  douta(10) <= \<const0>\;
  douta(9) <= \<const0>\;
  douta(8) <= \<const0>\;
  douta(7) <= \<const0>\;
  douta(6) <= \<const0>\;
  douta(5) <= \<const0>\;
  douta(4) <= \<const0>\;
  douta(3) <= \<const0>\;
  douta(2) <= \<const0>\;
  douta(1) <= \<const0>\;
  douta(0) <= \<const0>\;
  sbiterra <= \<const0>\;
  sbiterrb <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_99\,
      Q => doutb(0),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][100]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_71\,
      Q => doutb(100),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][101]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_70\,
      Q => doutb(101),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][102]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_69\,
      Q => doutb(102),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][103]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_68\,
      Q => doutb(103),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][104]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_131\,
      Q => doutb(104),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][105]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_130\,
      Q => doutb(105),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][106]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_129\,
      Q => doutb(106),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][107]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_128\,
      Q => doutb(107),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][108]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_127\,
      Q => doutb(108),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][109]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_126\,
      Q => doutb(109),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_89\,
      Q => doutb(10),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][110]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_125\,
      Q => doutb(110),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][111]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_124\,
      Q => doutb(111),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][112]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_123\,
      Q => doutb(112),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][113]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_122\,
      Q => doutb(113),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][114]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_121\,
      Q => doutb(114),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][115]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_120\,
      Q => doutb(115),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][116]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_119\,
      Q => doutb(116),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][117]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_118\,
      Q => doutb(117),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][118]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_117\,
      Q => doutb(118),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][119]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_116\,
      Q => doutb(119),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_88\,
      Q => doutb(11),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][120]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_115\,
      Q => doutb(120),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][121]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_114\,
      Q => doutb(121),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][122]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_113\,
      Q => doutb(122),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][123]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_112\,
      Q => doutb(123),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][124]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_111\,
      Q => doutb(124),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][125]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_110\,
      Q => doutb(125),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][126]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_109\,
      Q => doutb(126),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][127]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_108\,
      Q => doutb(127),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_87\,
      Q => doutb(12),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_86\,
      Q => doutb(13),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_85\,
      Q => doutb(14),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_84\,
      Q => doutb(15),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_83\,
      Q => doutb(16),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_82\,
      Q => doutb(17),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_81\,
      Q => doutb(18),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_80\,
      Q => doutb(19),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_98\,
      Q => doutb(1),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_79\,
      Q => doutb(20),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_78\,
      Q => doutb(21),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_77\,
      Q => doutb(22),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_76\,
      Q => doutb(23),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_75\,
      Q => doutb(24),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_74\,
      Q => doutb(25),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_73\,
      Q => doutb(26),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_72\,
      Q => doutb(27),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_71\,
      Q => doutb(28),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_70\,
      Q => doutb(29),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_97\,
      Q => doutb(2),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_69\,
      Q => doutb(30),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_68\,
      Q => doutb(31),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][32]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_131\,
      Q => doutb(32),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][33]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_130\,
      Q => doutb(33),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][34]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_129\,
      Q => doutb(34),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][35]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_128\,
      Q => doutb(35),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][36]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_127\,
      Q => doutb(36),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][37]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_126\,
      Q => doutb(37),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][38]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_125\,
      Q => doutb(38),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][39]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_124\,
      Q => doutb(39),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_96\,
      Q => doutb(3),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][40]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_123\,
      Q => doutb(40),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][41]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_122\,
      Q => doutb(41),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][42]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_121\,
      Q => doutb(42),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][43]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_120\,
      Q => doutb(43),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][44]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_119\,
      Q => doutb(44),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][45]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_118\,
      Q => doutb(45),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][46]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_117\,
      Q => doutb(46),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][47]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_116\,
      Q => doutb(47),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][48]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_115\,
      Q => doutb(48),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][49]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_114\,
      Q => doutb(49),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_95\,
      Q => doutb(4),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][50]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_113\,
      Q => doutb(50),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][51]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_112\,
      Q => doutb(51),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][52]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_111\,
      Q => doutb(52),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][53]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_110\,
      Q => doutb(53),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][54]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_109\,
      Q => doutb(54),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][55]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_108\,
      Q => doutb(55),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][56]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_107\,
      Q => doutb(56),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][57]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_106\,
      Q => doutb(57),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][58]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_105\,
      Q => doutb(58),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][59]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_104\,
      Q => doutb(59),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_94\,
      Q => doutb(5),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][60]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_103\,
      Q => doutb(60),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][61]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_102\,
      Q => doutb(61),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][62]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_101\,
      Q => doutb(62),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][63]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_100\,
      Q => doutb(63),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][64]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_143\,
      Q => doutb(64),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][65]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_142\,
      Q => doutb(65),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][66]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_141\,
      Q => doutb(66),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][67]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_140\,
      Q => doutb(67),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][68]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_147\,
      Q => doutb(68),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][69]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_146\,
      Q => doutb(69),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_93\,
      Q => doutb(6),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][70]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_145\,
      Q => doutb(70),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][71]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_144\,
      Q => doutb(71),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][72]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_99\,
      Q => doutb(72),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][73]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_98\,
      Q => doutb(73),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][74]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_97\,
      Q => doutb(74),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][75]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_96\,
      Q => doutb(75),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][76]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_95\,
      Q => doutb(76),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][77]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_94\,
      Q => doutb(77),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][78]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_93\,
      Q => doutb(78),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][79]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_92\,
      Q => doutb(79),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_92\,
      Q => doutb(7),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][80]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_91\,
      Q => doutb(80),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][81]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_90\,
      Q => doutb(81),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][82]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_89\,
      Q => doutb(82),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][83]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_88\,
      Q => doutb(83),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][84]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_87\,
      Q => doutb(84),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][85]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_86\,
      Q => doutb(85),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][86]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_85\,
      Q => doutb(86),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][87]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_84\,
      Q => doutb(87),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][88]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_83\,
      Q => doutb(88),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][89]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_82\,
      Q => doutb(89),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_91\,
      Q => doutb(8),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][90]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_81\,
      Q => doutb(90),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][91]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_80\,
      Q => doutb(91),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][92]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_79\,
      Q => doutb(92),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][93]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_78\,
      Q => doutb(93),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][94]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_77\,
      Q => doutb(94),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][95]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_76\,
      Q => doutb(95),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][96]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_75\,
      Q => doutb(96),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][97]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_74\,
      Q => doutb(97),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][98]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_73\,
      Q => doutb(98),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][99]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_1_n_72\,
      Q => doutb(99),
      R => '0'
    );
\gen_rd_b.gen_doutb_pipe.doutb_pipe_reg[0][9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => clka,
      CE => regceb,
      D => \gen_wr_a.gen_word_narrow.mem_reg_0_n_90\,
      Q => doutb(9),
      R => '0'
    );
\gen_wr_a.gen_word_narrow.mem_reg_0\: unisim.vcomponents.RAMB36E2
    generic map(
      CASCADE_ORDER_A => "NONE",
      CASCADE_ORDER_B => "NONE",
      CLOCK_DOMAINS => "COMMON",
      DOA_REG => 0,
      DOB_REG => 0,
      ENADDRENA => "FALSE",
      ENADDRENB => "FALSE",
      EN_ECC_PIPE => "FALSE",
      EN_ECC_READ => "FALSE",
      EN_ECC_WRITE => "FALSE",
      INITP_00 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_01 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_02 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_03 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_04 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_05 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_06 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_07 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_08 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_09 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_00 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_01 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_02 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_03 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_04 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_05 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_06 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_07 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_08 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_09 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_10 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_11 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_12 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_13 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_14 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_15 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_16 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_17 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_18 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_19 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_20 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_21 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_22 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_23 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_24 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_25 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_26 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_27 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_28 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_29 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_30 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_31 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_32 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_33 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_34 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_35 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_36 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_37 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_38 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_39 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_40 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_41 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_42 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_43 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_44 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_45 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_46 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_47 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_48 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_49 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_50 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_51 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_52 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_53 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_54 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_55 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_56 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_57 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_58 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_59 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_60 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_61 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_62 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_63 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_64 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_65 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_66 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_67 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_68 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_69 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_70 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_71 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_72 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_73 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_74 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_75 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_76 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_77 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_78 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_79 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_A => X"000000000",
      INIT_B => X"000000000",
      INIT_FILE => "NONE",
      RDADDRCHANGEA => "FALSE",
      RDADDRCHANGEB => "FALSE",
      READ_WIDTH_A => 72,
      READ_WIDTH_B => 0,
      RSTREG_PRIORITY_A => "RSTREG",
      RSTREG_PRIORITY_B => "RSTREG",
      SIM_COLLISION_CHECK => "ALL",
      SLEEP_ASYNC => "FALSE",
      SRVAL_A => X"000000000",
      SRVAL_B => X"000000000",
      WRITE_MODE_A => "READ_FIRST",
      WRITE_MODE_B => "READ_FIRST",
      WRITE_WIDTH_A => 0,
      WRITE_WIDTH_B => 72
    )
        port map (
      ADDRARDADDR(14) => '0',
      ADDRARDADDR(13 downto 6) => addrb(7 downto 0),
      ADDRARDADDR(5 downto 0) => B"111111",
      ADDRBWRADDR(14) => '0',
      ADDRBWRADDR(13 downto 6) => addra(7 downto 0),
      ADDRBWRADDR(5 downto 0) => B"111111",
      ADDRENA => '0',
      ADDRENB => '0',
      CASDIMUXA => '0',
      CASDIMUXB => '0',
      CASDINA(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINA_UNCONNECTED\(31 downto 0),
      CASDINB(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINB_UNCONNECTED\(31 downto 0),
      CASDINPA(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPA_UNCONNECTED\(3 downto 0),
      CASDINPB(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDINPB_UNCONNECTED\(3 downto 0),
      CASDOMUXA => '0',
      CASDOMUXB => '0',
      CASDOMUXEN_A => '1',
      CASDOMUXEN_B => '1',
      CASDOUTA(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTA_UNCONNECTED\(31 downto 0),
      CASDOUTB(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTB_UNCONNECTED\(31 downto 0),
      CASDOUTPA(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPA_UNCONNECTED\(3 downto 0),
      CASDOUTPB(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASDOUTPB_UNCONNECTED\(3 downto 0),
      CASINDBITERR => '0',
      CASINSBITERR => '0',
      CASOREGIMUXA => '0',
      CASOREGIMUXB => '0',
      CASOREGIMUXEN_A => '1',
      CASOREGIMUXEN_B => '1',
      CASOUTDBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTDBITERR_UNCONNECTED\,
      CASOUTSBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_CASOUTSBITERR_UNCONNECTED\,
      CLKARDCLK => clka,
      CLKBWRCLK => clka,
      DBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_DBITERR_UNCONNECTED\,
      DINADIN(31 downto 0) => dina(31 downto 0),
      DINBDIN(31 downto 0) => dina(63 downto 32),
      DINPADINP(3 downto 0) => dina(67 downto 64),
      DINPBDINP(3 downto 0) => dina(71 downto 68),
      DOUTADOUT(31) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_68\,
      DOUTADOUT(30) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_69\,
      DOUTADOUT(29) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_70\,
      DOUTADOUT(28) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_71\,
      DOUTADOUT(27) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_72\,
      DOUTADOUT(26) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_73\,
      DOUTADOUT(25) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_74\,
      DOUTADOUT(24) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_75\,
      DOUTADOUT(23) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_76\,
      DOUTADOUT(22) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_77\,
      DOUTADOUT(21) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_78\,
      DOUTADOUT(20) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_79\,
      DOUTADOUT(19) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_80\,
      DOUTADOUT(18) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_81\,
      DOUTADOUT(17) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_82\,
      DOUTADOUT(16) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_83\,
      DOUTADOUT(15) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_84\,
      DOUTADOUT(14) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_85\,
      DOUTADOUT(13) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_86\,
      DOUTADOUT(12) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_87\,
      DOUTADOUT(11) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_88\,
      DOUTADOUT(10) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_89\,
      DOUTADOUT(9) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_90\,
      DOUTADOUT(8) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_91\,
      DOUTADOUT(7) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_92\,
      DOUTADOUT(6) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_93\,
      DOUTADOUT(5) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_94\,
      DOUTADOUT(4) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_95\,
      DOUTADOUT(3) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_96\,
      DOUTADOUT(2) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_97\,
      DOUTADOUT(1) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_98\,
      DOUTADOUT(0) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_99\,
      DOUTBDOUT(31) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_100\,
      DOUTBDOUT(30) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_101\,
      DOUTBDOUT(29) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_102\,
      DOUTBDOUT(28) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_103\,
      DOUTBDOUT(27) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_104\,
      DOUTBDOUT(26) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_105\,
      DOUTBDOUT(25) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_106\,
      DOUTBDOUT(24) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_107\,
      DOUTBDOUT(23) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_108\,
      DOUTBDOUT(22) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_109\,
      DOUTBDOUT(21) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_110\,
      DOUTBDOUT(20) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_111\,
      DOUTBDOUT(19) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_112\,
      DOUTBDOUT(18) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_113\,
      DOUTBDOUT(17) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_114\,
      DOUTBDOUT(16) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_115\,
      DOUTBDOUT(15) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_116\,
      DOUTBDOUT(14) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_117\,
      DOUTBDOUT(13) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_118\,
      DOUTBDOUT(12) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_119\,
      DOUTBDOUT(11) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_120\,
      DOUTBDOUT(10) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_121\,
      DOUTBDOUT(9) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_122\,
      DOUTBDOUT(8) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_123\,
      DOUTBDOUT(7) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_124\,
      DOUTBDOUT(6) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_125\,
      DOUTBDOUT(5) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_126\,
      DOUTBDOUT(4) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_127\,
      DOUTBDOUT(3) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_128\,
      DOUTBDOUT(2) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_129\,
      DOUTBDOUT(1) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_130\,
      DOUTBDOUT(0) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_131\,
      DOUTPADOUTP(3) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_140\,
      DOUTPADOUTP(2) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_141\,
      DOUTPADOUTP(1) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_142\,
      DOUTPADOUTP(0) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_143\,
      DOUTPBDOUTP(3) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_144\,
      DOUTPBDOUTP(2) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_145\,
      DOUTPBDOUTP(1) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_146\,
      DOUTPBDOUTP(0) => \gen_wr_a.gen_word_narrow.mem_reg_0_n_147\,
      ECCPARITY(7 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_ECCPARITY_UNCONNECTED\(7 downto 0),
      ECCPIPECE => '1',
      ENARDEN => enb,
      ENBWREN => '1',
      INJECTDBITERR => '0',
      INJECTSBITERR => '0',
      RDADDRECC(8 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_RDADDRECC_UNCONNECTED\(8 downto 0),
      REGCEAREGCE => '1',
      REGCEB => '1',
      RSTRAMARSTRAM => '0',
      RSTRAMB => '0',
      RSTREGARSTREG => '0',
      RSTREGB => '0',
      SBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_0_SBITERR_UNCONNECTED\,
      SLEEP => '0',
      WEA(3 downto 0) => B"0000",
      WEBWE(7) => wea(0),
      WEBWE(6) => wea(0),
      WEBWE(5) => wea(0),
      WEBWE(4) => wea(0),
      WEBWE(3) => wea(0),
      WEBWE(2) => wea(0),
      WEBWE(1) => wea(0),
      WEBWE(0) => wea(0)
    );
\gen_wr_a.gen_word_narrow.mem_reg_1\: unisim.vcomponents.RAMB36E2
    generic map(
      CASCADE_ORDER_A => "NONE",
      CASCADE_ORDER_B => "NONE",
      CLOCK_DOMAINS => "COMMON",
      DOA_REG => 0,
      DOB_REG => 0,
      ENADDRENA => "FALSE",
      ENADDRENB => "FALSE",
      EN_ECC_PIPE => "FALSE",
      EN_ECC_READ => "FALSE",
      EN_ECC_WRITE => "FALSE",
      INITP_00 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_01 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_02 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_03 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_04 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_05 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_06 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_07 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_08 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_09 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INITP_0F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_00 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_01 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_02 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_03 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_04 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_05 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_06 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_07 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_08 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_09 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_0F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_10 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_11 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_12 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_13 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_14 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_15 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_16 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_17 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_18 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_19 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_1F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_20 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_21 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_22 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_23 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_24 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_25 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_26 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_27 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_28 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_29 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_2F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_30 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_31 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_32 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_33 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_34 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_35 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_36 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_37 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_38 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_39 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_3F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_40 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_41 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_42 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_43 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_44 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_45 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_46 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_47 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_48 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_49 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_4F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_50 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_51 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_52 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_53 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_54 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_55 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_56 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_57 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_58 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_59 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_5F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_60 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_61 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_62 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_63 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_64 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_65 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_66 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_67 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_68 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_69 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_6F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_70 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_71 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_72 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_73 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_74 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_75 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_76 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_77 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_78 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_79 => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7A => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7B => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7C => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7D => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7E => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_7F => X"0000000000000000000000000000000000000000000000000000000000000000",
      INIT_A => X"000000000",
      INIT_B => X"000000000",
      INIT_FILE => "NONE",
      RDADDRCHANGEA => "FALSE",
      RDADDRCHANGEB => "FALSE",
      READ_WIDTH_A => 72,
      READ_WIDTH_B => 0,
      RSTREG_PRIORITY_A => "RSTREG",
      RSTREG_PRIORITY_B => "RSTREG",
      SIM_COLLISION_CHECK => "ALL",
      SLEEP_ASYNC => "FALSE",
      SRVAL_A => X"000000000",
      SRVAL_B => X"000000000",
      WRITE_MODE_A => "READ_FIRST",
      WRITE_MODE_B => "READ_FIRST",
      WRITE_WIDTH_A => 0,
      WRITE_WIDTH_B => 72
    )
        port map (
      ADDRARDADDR(14) => '0',
      ADDRARDADDR(13 downto 6) => addrb(7 downto 0),
      ADDRARDADDR(5 downto 0) => B"111111",
      ADDRBWRADDR(14) => '0',
      ADDRBWRADDR(13 downto 6) => addra(7 downto 0),
      ADDRBWRADDR(5 downto 0) => B"111111",
      ADDRENA => '0',
      ADDRENB => '0',
      CASDIMUXA => '0',
      CASDIMUXB => '0',
      CASDINA(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINA_UNCONNECTED\(31 downto 0),
      CASDINB(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINB_UNCONNECTED\(31 downto 0),
      CASDINPA(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPA_UNCONNECTED\(3 downto 0),
      CASDINPB(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDINPB_UNCONNECTED\(3 downto 0),
      CASDOMUXA => '0',
      CASDOMUXB => '0',
      CASDOMUXEN_A => '1',
      CASDOMUXEN_B => '1',
      CASDOUTA(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTA_UNCONNECTED\(31 downto 0),
      CASDOUTB(31 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTB_UNCONNECTED\(31 downto 0),
      CASDOUTPA(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPA_UNCONNECTED\(3 downto 0),
      CASDOUTPB(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASDOUTPB_UNCONNECTED\(3 downto 0),
      CASINDBITERR => '0',
      CASINSBITERR => '0',
      CASOREGIMUXA => '0',
      CASOREGIMUXB => '0',
      CASOREGIMUXEN_A => '1',
      CASOREGIMUXEN_B => '1',
      CASOUTDBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTDBITERR_UNCONNECTED\,
      CASOUTSBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_CASOUTSBITERR_UNCONNECTED\,
      CLKARDCLK => clka,
      CLKBWRCLK => clka,
      DBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DBITERR_UNCONNECTED\,
      DINADIN(31 downto 0) => dina(103 downto 72),
      DINBDIN(31 downto 24) => B"11111111",
      DINBDIN(23 downto 0) => dina(127 downto 104),
      DINPADINP(3 downto 0) => B"1111",
      DINPBDINP(3 downto 0) => B"1111",
      DOUTADOUT(31) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_68\,
      DOUTADOUT(30) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_69\,
      DOUTADOUT(29) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_70\,
      DOUTADOUT(28) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_71\,
      DOUTADOUT(27) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_72\,
      DOUTADOUT(26) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_73\,
      DOUTADOUT(25) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_74\,
      DOUTADOUT(24) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_75\,
      DOUTADOUT(23) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_76\,
      DOUTADOUT(22) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_77\,
      DOUTADOUT(21) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_78\,
      DOUTADOUT(20) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_79\,
      DOUTADOUT(19) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_80\,
      DOUTADOUT(18) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_81\,
      DOUTADOUT(17) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_82\,
      DOUTADOUT(16) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_83\,
      DOUTADOUT(15) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_84\,
      DOUTADOUT(14) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_85\,
      DOUTADOUT(13) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_86\,
      DOUTADOUT(12) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_87\,
      DOUTADOUT(11) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_88\,
      DOUTADOUT(10) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_89\,
      DOUTADOUT(9) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_90\,
      DOUTADOUT(8) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_91\,
      DOUTADOUT(7) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_92\,
      DOUTADOUT(6) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_93\,
      DOUTADOUT(5) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_94\,
      DOUTADOUT(4) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_95\,
      DOUTADOUT(3) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_96\,
      DOUTADOUT(2) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_97\,
      DOUTADOUT(1) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_98\,
      DOUTADOUT(0) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_99\,
      DOUTBDOUT(31 downto 24) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTBDOUT_UNCONNECTED\(31 downto 24),
      DOUTBDOUT(23) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_108\,
      DOUTBDOUT(22) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_109\,
      DOUTBDOUT(21) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_110\,
      DOUTBDOUT(20) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_111\,
      DOUTBDOUT(19) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_112\,
      DOUTBDOUT(18) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_113\,
      DOUTBDOUT(17) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_114\,
      DOUTBDOUT(16) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_115\,
      DOUTBDOUT(15) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_116\,
      DOUTBDOUT(14) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_117\,
      DOUTBDOUT(13) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_118\,
      DOUTBDOUT(12) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_119\,
      DOUTBDOUT(11) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_120\,
      DOUTBDOUT(10) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_121\,
      DOUTBDOUT(9) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_122\,
      DOUTBDOUT(8) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_123\,
      DOUTBDOUT(7) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_124\,
      DOUTBDOUT(6) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_125\,
      DOUTBDOUT(5) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_126\,
      DOUTBDOUT(4) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_127\,
      DOUTBDOUT(3) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_128\,
      DOUTBDOUT(2) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_129\,
      DOUTBDOUT(1) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_130\,
      DOUTBDOUT(0) => \gen_wr_a.gen_word_narrow.mem_reg_1_n_131\,
      DOUTPADOUTP(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPADOUTP_UNCONNECTED\(3 downto 0),
      DOUTPBDOUTP(3 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_DOUTPBDOUTP_UNCONNECTED\(3 downto 0),
      ECCPARITY(7 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_ECCPARITY_UNCONNECTED\(7 downto 0),
      ECCPIPECE => '1',
      ENARDEN => enb,
      ENBWREN => '1',
      INJECTDBITERR => '0',
      INJECTSBITERR => '0',
      RDADDRECC(8 downto 0) => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_RDADDRECC_UNCONNECTED\(8 downto 0),
      REGCEAREGCE => '1',
      REGCEB => '1',
      RSTRAMARSTRAM => '0',
      RSTRAMB => '0',
      RSTREGARSTREG => '0',
      RSTREGB => '0',
      SBITERR => \NLW_gen_wr_a.gen_word_narrow.mem_reg_1_SBITERR_UNCONNECTED\,
      SLEEP => '0',
      WEA(3 downto 0) => B"0000",
      WEBWE(7) => wea(0),
      WEBWE(6) => wea(0),
      WEBWE(5) => wea(0),
      WEBWE(4) => wea(0),
      WEBWE(3) => wea(0),
      WEBWE(2) => wea(0),
      WEBWE(1) => wea(0),
      WEBWE(0) => wea(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync is
  port (
    dest_out : out STD_LOGIC;
    clk1_ready_pulse0 : out STD_LOGIC;
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    \syncstages_ff_reg[0]\ : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    clk1_ready_sync_r : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc3axi_map_wready : in STD_LOGIC;
    adc3slv_rden : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    src_in : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single
     port map (
      dest_clk => s_axi_aclk,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => \syncstages_ff_reg[0]\
    );
\clk1_ready_pulse_i_1__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => clk1_ready_sync_r,
      I1 => \^dest_out\,
      O => clk1_ready_pulse0
    );
\slv_access_valid_hold_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"D5D5FFD5C0C0FFC0"
    )
        port map (
      I0 => \^dest_out\,
      I1 => s_axi_wvalid,
      I2 => adc3axi_map_wready,
      I3 => adc3slv_rden,
      I4 => slv_access_valid_hold_reg,
      I5 => src_in,
      O => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__1\ is
  port (
    dest_out : out STD_LOGIC;
    clk2_valid_pulse0 : out STD_LOGIC;
    clk2_valid_pulse_reg : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s0_axis_clock : in STD_LOGIC;
    clk2_valid_sync_r : in STD_LOGIC;
    slv_wren_clk2 : in STD_LOGIC;
    clk2_ready_reg : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__1\ : entity is "rfadc_exdes_ctrl_sync";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__1\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__1\ is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of clk2_ready_i_1 : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of clk2_valid_pulse_i_1 : label is "soft_lutpair3";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__12\
     port map (
      dest_clk => s0_axis_clock,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => src_in
    );
clk2_ready_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EA"
    )
        port map (
      I0 => slv_wren_clk2,
      I1 => \^dest_out\,
      I2 => clk2_ready_reg,
      O => clk2_valid_pulse_reg
    );
clk2_valid_pulse_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^dest_out\,
      I1 => clk2_valid_sync_r,
      O => clk2_valid_pulse0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__2\ is
  port (
    dest_out : out STD_LOGIC;
    clk1_ready_pulse0 : out STD_LOGIC;
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    \syncstages_ff_reg[0]\ : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    clk1_ready_sync_r : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc0axi_map_wready : in STD_LOGIC;
    adc0slv_rden : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    src_in : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__2\ : entity is "rfadc_exdes_ctrl_sync";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__2\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__2\ is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__13\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => \syncstages_ff_reg[0]\
    );
clk1_ready_pulse_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => clk1_ready_sync_r,
      I1 => \^dest_out\,
      O => clk1_ready_pulse0
    );
slv_access_valid_hold_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"D5D5FFD5C0C0FFC0"
    )
        port map (
      I0 => \^dest_out\,
      I1 => s_axi_wvalid,
      I2 => adc0axi_map_wready,
      I3 => adc0slv_rden,
      I4 => slv_access_valid_hold_reg,
      I5 => src_in,
      O => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__3\ is
  port (
    dest_out : out STD_LOGIC;
    clk2_valid_pulse0 : out STD_LOGIC;
    clk2_valid_pulse_reg : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    clk2_valid_sync_r : in STD_LOGIC;
    slv_wren_clk2 : in STD_LOGIC;
    clk2_ready_reg : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__3\ : entity is "rfadc_exdes_ctrl_sync";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__3\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__3\ is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \clk2_ready_i_1__0\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \clk2_valid_pulse_i_1__0\ : label is "soft_lutpair13";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__14\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => src_in
    );
\clk2_ready_i_1__0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EA"
    )
        port map (
      I0 => slv_wren_clk2,
      I1 => \^dest_out\,
      I2 => clk2_ready_reg,
      O => clk2_valid_pulse_reg
    );
\clk2_valid_pulse_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^dest_out\,
      I1 => clk2_valid_sync_r,
      O => clk2_valid_pulse0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__4\ is
  port (
    dest_out : out STD_LOGIC;
    clk1_ready_pulse0 : out STD_LOGIC;
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    \syncstages_ff_reg[0]\ : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    clk1_ready_sync_r : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc1axi_map_wready : in STD_LOGIC;
    adc1slv_rden : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    src_in : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__4\ : entity is "rfadc_exdes_ctrl_sync";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__4\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__4\ is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__15\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => \syncstages_ff_reg[0]\
    );
\clk1_ready_pulse_i_1__0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => clk1_ready_sync_r,
      I1 => \^dest_out\,
      O => clk1_ready_pulse0
    );
\slv_access_valid_hold_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"D5D5FFD5C0C0FFC0"
    )
        port map (
      I0 => \^dest_out\,
      I1 => s_axi_wvalid,
      I2 => adc1axi_map_wready,
      I3 => adc1slv_rden,
      I4 => slv_access_valid_hold_reg,
      I5 => src_in,
      O => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__5\ is
  port (
    dest_out : out STD_LOGIC;
    clk2_valid_pulse0 : out STD_LOGIC;
    clk2_valid_pulse_reg : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    clk2_valid_sync_r : in STD_LOGIC;
    slv_wren_clk2 : in STD_LOGIC;
    clk2_ready_reg : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__5\ : entity is "rfadc_exdes_ctrl_sync";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__5\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__5\ is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \clk2_ready_i_1__1\ : label is "soft_lutpair22";
  attribute SOFT_HLUTNM of \clk2_valid_pulse_i_1__1\ : label is "soft_lutpair22";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__16\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => src_in
    );
\clk2_ready_i_1__1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EA"
    )
        port map (
      I0 => slv_wren_clk2,
      I1 => \^dest_out\,
      I2 => clk2_ready_reg,
      O => clk2_valid_pulse_reg
    );
\clk2_valid_pulse_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^dest_out\,
      I1 => clk2_valid_sync_r,
      O => clk2_valid_pulse0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__6\ is
  port (
    dest_out : out STD_LOGIC;
    clk1_ready_pulse0 : out STD_LOGIC;
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    \syncstages_ff_reg[0]\ : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    clk1_ready_sync_r : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc2axi_map_wready : in STD_LOGIC;
    adc2slv_rden : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    src_in : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__6\ : entity is "rfadc_exdes_ctrl_sync";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__6\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__6\ is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__17\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => \syncstages_ff_reg[0]\
    );
\clk1_ready_pulse_i_1__1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => clk1_ready_sync_r,
      I1 => \^dest_out\,
      O => clk1_ready_pulse0
    );
\slv_access_valid_hold_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"D5D5FFD5C0C0FFC0"
    )
        port map (
      I0 => \^dest_out\,
      I1 => s_axi_wvalid,
      I2 => adc2axi_map_wready,
      I3 => adc2slv_rden,
      I4 => slv_access_valid_hold_reg,
      I5 => src_in,
      O => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__7\ is
  port (
    dest_out : out STD_LOGIC;
    clk2_valid_pulse0 : out STD_LOGIC;
    clk2_valid_pulse_reg : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    clk2_valid_sync_r : in STD_LOGIC;
    slv_wren_clk2 : in STD_LOGIC;
    clk2_ready_reg : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__7\ : entity is "rfadc_exdes_ctrl_sync";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__7\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__7\ is
  signal \^dest_out\ : STD_LOGIC;
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_i : label is 5;
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_i : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_i : label is "SINGLE";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_i : label is "TRUE";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \clk2_ready_i_1__2\ : label is "soft_lutpair31";
  attribute SOFT_HLUTNM of \clk2_valid_pulse_i_1__2\ : label is "soft_lutpair31";
begin
  dest_out <= \^dest_out\;
cdc_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__18\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => \^dest_out\,
      src_clk => '0',
      src_in => src_in
    );
\clk2_ready_i_1__2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"EA"
    )
        port map (
      I0 => slv_wren_clk2,
      I1 => \^dest_out\,
      I2 => clk2_ready_reg,
      O => clk2_valid_pulse_reg
    );
\clk2_valid_pulse_i_1__2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^dest_out\,
      I1 => clk2_valid_sync_r,
      O => clk2_valid_pulse0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram is
  port (
    sleep : in STD_LOGIC;
    clka : in STD_LOGIC;
    ena : in STD_LOGIC;
    wea : in STD_LOGIC_VECTOR ( 0 to 0 );
    addra : in STD_LOGIC_VECTOR ( 7 downto 0 );
    dina : in STD_LOGIC_VECTOR ( 127 downto 0 );
    injectsbiterra : in STD_LOGIC;
    injectdbiterra : in STD_LOGIC;
    clkb : in STD_LOGIC;
    rstb : in STD_LOGIC;
    enb : in STD_LOGIC;
    regceb : in STD_LOGIC;
    addrb : in STD_LOGIC_VECTOR ( 7 downto 0 );
    doutb : out STD_LOGIC_VECTOR ( 127 downto 0 );
    sbiterrb : out STD_LOGIC;
    dbiterrb : out STD_LOGIC
  );
  attribute ADDR_WIDTH_A : integer;
  attribute ADDR_WIDTH_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 8;
  attribute ADDR_WIDTH_B : integer;
  attribute ADDR_WIDTH_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 8;
  attribute AUTO_SLEEP_TIME : integer;
  attribute AUTO_SLEEP_TIME of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute BYTE_WRITE_WIDTH_A : integer;
  attribute BYTE_WRITE_WIDTH_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 128;
  attribute CASCADE_HEIGHT : integer;
  attribute CASCADE_HEIGHT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute CLOCKING_MODE : string;
  attribute CLOCKING_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "common_clock";
  attribute ECC_MODE : string;
  attribute ECC_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "no_ecc";
  attribute MEMORY_INIT_FILE : string;
  attribute MEMORY_INIT_FILE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "none";
  attribute MEMORY_INIT_PARAM : string;
  attribute MEMORY_INIT_PARAM of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "";
  attribute MEMORY_OPTIMIZATION : string;
  attribute MEMORY_OPTIMIZATION of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "true";
  attribute MEMORY_PRIMITIVE : string;
  attribute MEMORY_PRIMITIVE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "auto";
  attribute MEMORY_SIZE : integer;
  attribute MEMORY_SIZE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 32768;
  attribute MESSAGE_CONTROL : integer;
  attribute MESSAGE_CONTROL of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute P_CLOCKING_MODE : integer;
  attribute P_CLOCKING_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute P_ECC_MODE : integer;
  attribute P_ECC_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute P_MEMORY_OPTIMIZATION : integer;
  attribute P_MEMORY_OPTIMIZATION of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 1;
  attribute P_MEMORY_PRIMITIVE : integer;
  attribute P_MEMORY_PRIMITIVE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute P_WAKEUP_TIME : integer;
  attribute P_WAKEUP_TIME of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute P_WRITE_MODE_B : integer;
  attribute P_WRITE_MODE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 2;
  attribute READ_DATA_WIDTH_B : integer;
  attribute READ_DATA_WIDTH_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 128;
  attribute READ_LATENCY_B : integer;
  attribute READ_LATENCY_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 2;
  attribute READ_RESET_VALUE_B : string;
  attribute READ_RESET_VALUE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "0";
  attribute RST_MODE_A : string;
  attribute RST_MODE_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "SYNC";
  attribute RST_MODE_B : string;
  attribute RST_MODE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "SYNC";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute USE_EMBEDDED_CONSTRAINT : integer;
  attribute USE_EMBEDDED_CONSTRAINT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute USE_MEM_INIT : integer;
  attribute USE_MEM_INIT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 1;
  attribute USE_MEM_INIT_MMI : integer;
  attribute USE_MEM_INIT_MMI of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 0;
  attribute WAKEUP_TIME : string;
  attribute WAKEUP_TIME of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "disable_sleep";
  attribute WRITE_DATA_WIDTH_A : integer;
  attribute WRITE_DATA_WIDTH_A of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 128;
  attribute WRITE_MODE_B : string;
  attribute WRITE_MODE_B of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "no_change";
  attribute WRITE_PROTECT : integer;
  attribute WRITE_PROTECT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is 1;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram : entity is "TRUE";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram is
  signal \<const0>\ : STD_LOGIC;
  signal NLW_xpm_memory_base_inst_dbiterra_UNCONNECTED : STD_LOGIC;
  signal NLW_xpm_memory_base_inst_dbiterrb_UNCONNECTED : STD_LOGIC;
  signal NLW_xpm_memory_base_inst_sbiterra_UNCONNECTED : STD_LOGIC;
  signal NLW_xpm_memory_base_inst_sbiterrb_UNCONNECTED : STD_LOGIC;
  signal NLW_xpm_memory_base_inst_douta_UNCONNECTED : STD_LOGIC_VECTOR ( 127 downto 0 );
  attribute ADDR_WIDTH_A of xpm_memory_base_inst : label is 8;
  attribute ADDR_WIDTH_B of xpm_memory_base_inst : label is 8;
  attribute AUTO_SLEEP_TIME of xpm_memory_base_inst : label is 0;
  attribute BYTE_WRITE_WIDTH_A of xpm_memory_base_inst : label is 128;
  attribute BYTE_WRITE_WIDTH_B : integer;
  attribute BYTE_WRITE_WIDTH_B of xpm_memory_base_inst : label is 128;
  attribute CASCADE_HEIGHT of xpm_memory_base_inst : label is 0;
  attribute CLOCKING_MODE_integer : integer;
  attribute CLOCKING_MODE_integer of xpm_memory_base_inst : label is 0;
  attribute ECC_MODE_integer : integer;
  attribute ECC_MODE_integer of xpm_memory_base_inst : label is 0;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of xpm_memory_base_inst : label is "soft";
  attribute MAX_NUM_CHAR : integer;
  attribute MAX_NUM_CHAR of xpm_memory_base_inst : label is 0;
  attribute \MEM.ADDRESS_SPACE\ : boolean;
  attribute \MEM.ADDRESS_SPACE\ of xpm_memory_base_inst : label is std.standard.true;
  attribute \MEM.ADDRESS_SPACE_BEGIN\ : integer;
  attribute \MEM.ADDRESS_SPACE_BEGIN\ of xpm_memory_base_inst : label is 0;
  attribute \MEM.ADDRESS_SPACE_DATA_LSB\ : integer;
  attribute \MEM.ADDRESS_SPACE_DATA_LSB\ of xpm_memory_base_inst : label is 0;
  attribute \MEM.ADDRESS_SPACE_DATA_MSB\ : integer;
  attribute \MEM.ADDRESS_SPACE_DATA_MSB\ of xpm_memory_base_inst : label is 127;
  attribute \MEM.ADDRESS_SPACE_END\ : integer;
  attribute \MEM.ADDRESS_SPACE_END\ of xpm_memory_base_inst : label is 511;
  attribute \MEM.CORE_MEMORY_WIDTH\ : integer;
  attribute \MEM.CORE_MEMORY_WIDTH\ of xpm_memory_base_inst : label is 128;
  attribute MEMORY_INIT_FILE of xpm_memory_base_inst : label is "none";
  attribute MEMORY_INIT_PARAM of xpm_memory_base_inst : label is "";
  attribute MEMORY_OPTIMIZATION of xpm_memory_base_inst : label is "true";
  attribute MEMORY_PRIMITIVE_integer : integer;
  attribute MEMORY_PRIMITIVE_integer of xpm_memory_base_inst : label is 0;
  attribute MEMORY_SIZE of xpm_memory_base_inst : label is 32768;
  attribute MEMORY_TYPE : integer;
  attribute MEMORY_TYPE of xpm_memory_base_inst : label is 1;
  attribute MESSAGE_CONTROL of xpm_memory_base_inst : label is 0;
  attribute NUM_CHAR_LOC : integer;
  attribute NUM_CHAR_LOC of xpm_memory_base_inst : label is 0;
  attribute P_ECC_MODE_string : string;
  attribute P_ECC_MODE_string of xpm_memory_base_inst : label is "no_ecc";
  attribute P_ENABLE_BYTE_WRITE_A : integer;
  attribute P_ENABLE_BYTE_WRITE_A of xpm_memory_base_inst : label is 0;
  attribute P_ENABLE_BYTE_WRITE_B : integer;
  attribute P_ENABLE_BYTE_WRITE_B of xpm_memory_base_inst : label is 0;
  attribute P_MAX_DEPTH_DATA : integer;
  attribute P_MAX_DEPTH_DATA of xpm_memory_base_inst : label is 256;
  attribute P_MEMORY_OPT : string;
  attribute P_MEMORY_OPT of xpm_memory_base_inst : label is "yes";
  attribute P_MEMORY_PRIMITIVE_string : string;
  attribute P_MEMORY_PRIMITIVE_string of xpm_memory_base_inst : label is "auto";
  attribute P_MIN_WIDTH_DATA : integer;
  attribute P_MIN_WIDTH_DATA of xpm_memory_base_inst : label is 128;
  attribute P_MIN_WIDTH_DATA_A : integer;
  attribute P_MIN_WIDTH_DATA_A of xpm_memory_base_inst : label is 128;
  attribute P_MIN_WIDTH_DATA_B : integer;
  attribute P_MIN_WIDTH_DATA_B of xpm_memory_base_inst : label is 128;
  attribute P_MIN_WIDTH_DATA_ECC : integer;
  attribute P_MIN_WIDTH_DATA_ECC of xpm_memory_base_inst : label is 128;
  attribute P_MIN_WIDTH_DATA_LDW : integer;
  attribute P_MIN_WIDTH_DATA_LDW of xpm_memory_base_inst : label is 4;
  attribute P_MIN_WIDTH_DATA_SHFT : integer;
  attribute P_MIN_WIDTH_DATA_SHFT of xpm_memory_base_inst : label is 128;
  attribute P_NUM_COLS_WRITE_A : integer;
  attribute P_NUM_COLS_WRITE_A of xpm_memory_base_inst : label is 1;
  attribute P_NUM_COLS_WRITE_B : integer;
  attribute P_NUM_COLS_WRITE_B of xpm_memory_base_inst : label is 1;
  attribute P_NUM_ROWS_READ_A : integer;
  attribute P_NUM_ROWS_READ_A of xpm_memory_base_inst : label is 1;
  attribute P_NUM_ROWS_READ_B : integer;
  attribute P_NUM_ROWS_READ_B of xpm_memory_base_inst : label is 1;
  attribute P_NUM_ROWS_WRITE_A : integer;
  attribute P_NUM_ROWS_WRITE_A of xpm_memory_base_inst : label is 1;
  attribute P_NUM_ROWS_WRITE_B : integer;
  attribute P_NUM_ROWS_WRITE_B of xpm_memory_base_inst : label is 1;
  attribute P_SDP_WRITE_MODE : string;
  attribute P_SDP_WRITE_MODE of xpm_memory_base_inst : label is "yes";
  attribute P_WIDTH_ADDR_LSB_READ_A : integer;
  attribute P_WIDTH_ADDR_LSB_READ_A of xpm_memory_base_inst : label is 0;
  attribute P_WIDTH_ADDR_LSB_READ_B : integer;
  attribute P_WIDTH_ADDR_LSB_READ_B of xpm_memory_base_inst : label is 0;
  attribute P_WIDTH_ADDR_LSB_WRITE_A : integer;
  attribute P_WIDTH_ADDR_LSB_WRITE_A of xpm_memory_base_inst : label is 0;
  attribute P_WIDTH_ADDR_LSB_WRITE_B : integer;
  attribute P_WIDTH_ADDR_LSB_WRITE_B of xpm_memory_base_inst : label is 0;
  attribute P_WIDTH_ADDR_READ_A : integer;
  attribute P_WIDTH_ADDR_READ_A of xpm_memory_base_inst : label is 8;
  attribute P_WIDTH_ADDR_READ_B : integer;
  attribute P_WIDTH_ADDR_READ_B of xpm_memory_base_inst : label is 8;
  attribute P_WIDTH_ADDR_WRITE_A : integer;
  attribute P_WIDTH_ADDR_WRITE_A of xpm_memory_base_inst : label is 8;
  attribute P_WIDTH_ADDR_WRITE_B : integer;
  attribute P_WIDTH_ADDR_WRITE_B of xpm_memory_base_inst : label is 8;
  attribute P_WIDTH_COL_WRITE_A : integer;
  attribute P_WIDTH_COL_WRITE_A of xpm_memory_base_inst : label is 128;
  attribute P_WIDTH_COL_WRITE_B : integer;
  attribute P_WIDTH_COL_WRITE_B of xpm_memory_base_inst : label is 128;
  attribute READ_DATA_WIDTH_A : integer;
  attribute READ_DATA_WIDTH_A of xpm_memory_base_inst : label is 128;
  attribute READ_DATA_WIDTH_B of xpm_memory_base_inst : label is 128;
  attribute READ_LATENCY_A : integer;
  attribute READ_LATENCY_A of xpm_memory_base_inst : label is 2;
  attribute READ_LATENCY_B of xpm_memory_base_inst : label is 2;
  attribute READ_RESET_VALUE_A : string;
  attribute READ_RESET_VALUE_A of xpm_memory_base_inst : label is "0";
  attribute READ_RESET_VALUE_B of xpm_memory_base_inst : label is "0";
  attribute RST_MODE_A of xpm_memory_base_inst : label is "SYNC";
  attribute RST_MODE_B of xpm_memory_base_inst : label is "SYNC";
  attribute SIM_ASSERT_CHK of xpm_memory_base_inst : label is 0;
  attribute USE_EMBEDDED_CONSTRAINT of xpm_memory_base_inst : label is 0;
  attribute USE_MEM_INIT of xpm_memory_base_inst : label is 1;
  attribute USE_MEM_INIT_MMI of xpm_memory_base_inst : label is 0;
  attribute VERSION : integer;
  attribute VERSION of xpm_memory_base_inst : label is 0;
  attribute WAKEUP_TIME_integer : integer;
  attribute WAKEUP_TIME_integer of xpm_memory_base_inst : label is 0;
  attribute WRITE_DATA_WIDTH_A of xpm_memory_base_inst : label is 128;
  attribute WRITE_DATA_WIDTH_B : integer;
  attribute WRITE_DATA_WIDTH_B of xpm_memory_base_inst : label is 128;
  attribute WRITE_MODE_A : integer;
  attribute WRITE_MODE_A of xpm_memory_base_inst : label is 2;
  attribute WRITE_MODE_B_integer : integer;
  attribute WRITE_MODE_B_integer of xpm_memory_base_inst : label is 2;
  attribute WRITE_PROTECT of xpm_memory_base_inst : label is 1;
  attribute XPM_MODULE of xpm_memory_base_inst : label is "TRUE";
  attribute rsta_loop_iter : integer;
  attribute rsta_loop_iter of xpm_memory_base_inst : label is 128;
  attribute rstb_loop_iter : integer;
  attribute rstb_loop_iter of xpm_memory_base_inst : label is 128;
begin
  dbiterrb <= \<const0>\;
  sbiterrb <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
xpm_memory_base_inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_base
     port map (
      addra(7 downto 0) => addra(7 downto 0),
      addrb(7 downto 0) => addrb(7 downto 0),
      clka => clka,
      clkb => '0',
      dbiterra => NLW_xpm_memory_base_inst_dbiterra_UNCONNECTED,
      dbiterrb => NLW_xpm_memory_base_inst_dbiterrb_UNCONNECTED,
      dina(127 downto 0) => dina(127 downto 0),
      dinb(127 downto 0) => B"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
      douta(127 downto 0) => NLW_xpm_memory_base_inst_douta_UNCONNECTED(127 downto 0),
      doutb(127 downto 0) => doutb(127 downto 0),
      ena => '0',
      enb => enb,
      injectdbiterra => '0',
      injectdbiterrb => '0',
      injectsbiterra => '0',
      injectsbiterrb => '0',
      regcea => '0',
      regceb => regceb,
      rsta => '0',
      rstb => '0',
      sbiterra => NLW_xpm_memory_base_inst_sbiterra_UNCONNECTED,
      sbiterrb => NLW_xpm_memory_base_inst_sbiterrb_UNCONNECTED,
      sleep => sleep,
      wea(0) => wea(0),
      web(0) => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen is
  port (
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_wren_done_pulse : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_6 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_7 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_8 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_9 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_10 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_11 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_12 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_13 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_14 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk1_ready_pulse_reg_0 : out STD_LOGIC;
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    \adc30_ds_enable_0_reg[0]\ : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    \adc33_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc33_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc31_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc31_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc31_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc30_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc30_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc30_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc33_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc33_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc32_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc32_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc32_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc32_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc31_ds_inc_0_reg[0]\ : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    slv_rden_r_0 : in STD_LOGIC;
    slv_wren_done_pulse_1 : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc3axi_map_wready : in STD_LOGIC;
    adc3slv_rden : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen is
  signal \^sr\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal axi_2_drp_valid_i_n_0 : STD_LOGIC;
  signal axi_2_drp_valid_i_n_2 : STD_LOGIC;
  signal clk1_ready_pulse0 : STD_LOGIC;
  signal clk1_ready_sync_r : STD_LOGIC;
  signal clk2_ready : STD_LOGIC;
  signal clk2_valid_pulse0 : STD_LOGIC;
  signal clk2_valid_sync_r : STD_LOGIC;
  signal slv_wren_clear : STD_LOGIC;
  signal slv_wren_clk2 : STD_LOGIC;
  signal \^slv_wren_done_pulse\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \adc30_ds_control_0[1]_i_1\ : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of \adc30_ds_enable_0[7]_i_1\ : label is "soft_lutpair32";
  attribute SOFT_HLUTNM of \adc30_ds_inc_0[11]_i_1\ : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of \adc30_ds_type_0[3]_i_1\ : label is "soft_lutpair35";
  attribute SOFT_HLUTNM of \adc31_ds_control_0[1]_i_1\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \adc31_ds_enable_0[7]_i_1\ : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of \adc31_ds_inc_0[11]_i_1\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \adc31_ds_type_0[3]_i_1\ : label is "soft_lutpair34";
  attribute SOFT_HLUTNM of \adc32_ds_control_0[1]_i_1\ : label is "soft_lutpair39";
  attribute SOFT_HLUTNM of \adc32_ds_enable_0[7]_i_1\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \adc32_ds_inc_0[11]_i_1\ : label is "soft_lutpair38";
  attribute SOFT_HLUTNM of \adc32_ds_type_0[3]_i_1\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \adc33_ds_control_0[1]_i_1\ : label is "soft_lutpair37";
  attribute SOFT_HLUTNM of \adc33_ds_enable_0[7]_i_1\ : label is "soft_lutpair33";
  attribute SOFT_HLUTNM of \adc33_ds_inc_0[11]_i_1\ : label is "soft_lutpair36";
  attribute SOFT_HLUTNM of \adc33_ds_type_0[3]_i_1\ : label is "soft_lutpair32";
begin
  SR(0) <= \^sr\(0);
  slv_wren_done_pulse <= \^slv_wren_done_pulse\;
\adc30_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc30_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_6(0)
    );
\adc30_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc30_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => E(0)
    );
\adc30_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc30_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_7(0)
    );
\adc30_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc30_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_5(0)
    );
\adc31_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc31_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_2(0)
    );
\adc31_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc31_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_4(0)
    );
\adc31_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc31_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_14(0)
    );
\adc31_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc31_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_3(0)
    );
\adc32_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc32_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_13(0)
    );
\adc32_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc32_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_12(0)
    );
\adc32_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc32_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_11(0)
    );
\adc32_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc32_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_10(0)
    );
\adc33_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc33_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_9(0)
    );
\adc33_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc33_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_1(0)
    );
\adc33_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc33_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_8(0)
    );
\adc33_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc33_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_0(0)
    );
axi_2_drp_valid_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__7\
     port map (
      clk2_ready_reg => clk2_ready,
      clk2_valid_pulse0 => clk2_valid_pulse0,
      clk2_valid_pulse_reg => axi_2_drp_valid_i_n_2,
      clk2_valid_sync_r => clk2_valid_sync_r,
      dest_out => axi_2_drp_valid_i_n_0,
      s_axi_aclk => s_axi_aclk,
      slv_wren_clk2 => slv_wren_clk2,
      src_in => src_in
    );
axi_awready_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => s_axi_aresetn,
      O => \^sr\(0)
    );
\axi_bresp[1]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"D0DD"
    )
        port map (
      I0 => \^slv_wren_done_pulse\,
      I1 => slv_access_valid_hold_reg,
      I2 => slv_rden_r_0,
      I3 => slv_wren_done_pulse_1,
      O => clk1_ready_pulse_reg_0
    );
clk1_ready_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk1_ready_pulse0,
      Q => \^slv_wren_done_pulse\,
      R => \^sr\(0)
    );
clk1_ready_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => slv_wren_clear,
      Q => clk1_ready_sync_r,
      R => \^sr\(0)
    );
clk2_ready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_2_drp_valid_i_n_2,
      Q => clk2_ready,
      R => \^sr\(0)
    );
clk2_valid_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk2_valid_pulse0,
      Q => slv_wren_clk2,
      R => \^sr\(0)
    );
clk2_valid_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_2_drp_valid_i_n_0,
      Q => clk2_valid_sync_r,
      R => \^sr\(0)
    );
drp_2_axi_in_progress_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync
     port map (
      adc3axi_map_wready => adc3axi_map_wready,
      adc3slv_rden => adc3slv_rden,
      clk1_ready_pulse0 => clk1_ready_pulse0,
      clk1_ready_sync_r => clk1_ready_sync_r,
      dest_out => slv_wren_clear,
      s_axi_aclk => s_axi_aclk,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => slv_access_valid_hold_reg,
      src_in => src_in,
      \syncstages_ff_reg[0]\ => clk2_ready,
      \syncstages_ff_reg[4]\ => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__1\ is
  port (
    slv_wren_done_pulse : out STD_LOGIC;
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_1 : out STD_LOGIC;
    slv_rden_r_reg_2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_6 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_7 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_8 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_9 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_10 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_11 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_12 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_13 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg_14 : out STD_LOGIC_VECTOR ( 0 to 0 );
    \slv_wdata_r_internal_reg[0]\ : out STD_LOGIC;
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s0_axis_clock : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    p_0_in : in STD_LOGIC;
    \adc03_ds_enable_0_reg[7]\ : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    \adc00_ds_type_0_reg[3]\ : in STD_LOGIC;
    \adc03_ds_control_0_reg[1]\ : in STD_LOGIC;
    \axi_rresp[1]_i_2\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    adc_ds_slv_rden : in STD_LOGIC;
    \adc00_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc03_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc01_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc01_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc01_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc00_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc00_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc03_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc02_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc02_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc02_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc02_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc01_ds_inc_0_reg[0]\ : in STD_LOGIC;
    dest_rst : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 0 to 0 );
    adc00_ds_pulse_control_0_reg : in STD_LOGIC;
    adc00_ds_pulse_control_0_reg_0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    adc00_ds_pulse_control_0_reg_1 : in STD_LOGIC;
    adc00_ds_pulse_control_0 : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc0axi_map_wready : in STD_LOGIC;
    adc0slv_rden : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__1\ : entity is "rfadc_exdes_ctrl_hshk_pls_gen";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__1\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__1\ is
  signal \^sr\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal adc00_ds_pulse_control_0_i_3_n_0 : STD_LOGIC;
  signal axi_2_drp_valid_i_n_0 : STD_LOGIC;
  signal axi_2_drp_valid_i_n_2 : STD_LOGIC;
  signal clk1_ready_pulse0 : STD_LOGIC;
  signal clk1_ready_sync_r : STD_LOGIC;
  signal clk2_ready : STD_LOGIC;
  signal clk2_valid_pulse0 : STD_LOGIC;
  signal clk2_valid_sync_r : STD_LOGIC;
  signal slv_wren_clear : STD_LOGIC;
  signal slv_wren_clk2 : STD_LOGIC;
  signal \^slv_wren_done_pulse\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \adc00_ds_control_0[1]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \adc00_ds_enable_0[0]_i_2\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \adc00_ds_inc_0[11]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of adc00_ds_pulse_control_0_i_3 : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \adc00_ds_type_0[3]_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \adc01_ds_control_0[1]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \adc01_ds_enable_0[7]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \adc01_ds_inc_0[11]_i_1\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \adc01_ds_type_0[3]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \adc02_ds_control_0[1]_i_1\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \adc02_ds_enable_0[7]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \adc02_ds_inc_0[11]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \adc02_ds_type_0[3]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \adc03_ds_control_0[1]_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \adc03_ds_enable_0[7]_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \adc03_ds_inc_0[11]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \adc03_ds_type_0[3]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \axi_rresp[1]_i_4\ : label is "soft_lutpair4";
begin
  SR(0) <= \^sr\(0);
  slv_wren_done_pulse <= \^slv_wren_done_pulse\;
\adc00_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc00_ds_control_0_reg[0]\,
      O => slv_rden_r_reg_7(0)
    );
\adc00_ds_enable_0[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => dest_rst,
      O => \^sr\(0)
    );
\adc00_ds_enable_0[0]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"20"
    )
        port map (
      I0 => \adc00_ds_enable_0_reg[0]\,
      I1 => slv_access_valid_hold_reg,
      I2 => slv_wren_clk2,
      O => slv_rden_r_reg_2(0)
    );
\adc00_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc00_ds_inc_0_reg[0]\,
      O => slv_rden_r_reg_8(0)
    );
adc00_ds_pulse_control_0_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFEFF00000200"
    )
        port map (
      I0 => Q(0),
      I1 => adc00_ds_pulse_control_0_reg,
      I2 => adc00_ds_pulse_control_0_reg_0(0),
      I3 => adc00_ds_pulse_control_0_i_3_n_0,
      I4 => adc00_ds_pulse_control_0_reg_1,
      I5 => adc00_ds_pulse_control_0,
      O => \slv_wdata_r_internal_reg[0]\
    );
adc00_ds_pulse_control_0_i_3: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => slv_wren_clk2,
      I1 => slv_access_valid_hold_reg,
      O => adc00_ds_pulse_control_0_i_3_n_0
    );
\adc00_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"20"
    )
        port map (
      I0 => \adc00_ds_type_0_reg[3]\,
      I1 => slv_access_valid_hold_reg,
      I2 => slv_wren_clk2,
      O => slv_rden_r_reg(0)
    );
\adc01_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc01_ds_control_0_reg[0]\,
      O => slv_rden_r_reg_4(0)
    );
\adc01_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc01_ds_enable_0_reg[0]\,
      O => slv_rden_r_reg_6(0)
    );
\adc01_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc01_ds_inc_0_reg[0]\,
      O => slv_rden_r_reg_14(0)
    );
\adc01_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc01_ds_type_0_reg[0]\,
      O => slv_rden_r_reg_5(0)
    );
\adc02_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc02_ds_control_0_reg[0]\,
      O => slv_rden_r_reg_13(0)
    );
\adc02_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc02_ds_enable_0_reg[0]\,
      O => slv_rden_r_reg_12(0)
    );
\adc02_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc02_ds_inc_0_reg[0]\,
      O => slv_rden_r_reg_11(0)
    );
\adc02_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc02_ds_type_0_reg[0]\,
      O => slv_rden_r_reg_10(0)
    );
\adc03_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"20"
    )
        port map (
      I0 => \adc03_ds_control_0_reg[1]\,
      I1 => slv_access_valid_hold_reg,
      I2 => slv_wren_clk2,
      O => slv_rden_r_reg_0(0)
    );
\adc03_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"20"
    )
        port map (
      I0 => \adc03_ds_enable_0_reg[7]\,
      I1 => slv_access_valid_hold_reg,
      I2 => slv_wren_clk2,
      O => E(0)
    );
\adc03_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc03_ds_inc_0_reg[0]\,
      O => slv_rden_r_reg_9(0)
    );
\adc03_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => slv_wren_clk2,
      I2 => \adc03_ds_type_0_reg[0]\,
      O => slv_rden_r_reg_3(0)
    );
axi_2_drp_valid_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__1\
     port map (
      clk2_ready_reg => clk2_ready,
      clk2_valid_pulse0 => clk2_valid_pulse0,
      clk2_valid_pulse_reg => axi_2_drp_valid_i_n_2,
      clk2_valid_sync_r => clk2_valid_sync_r,
      dest_out => axi_2_drp_valid_i_n_0,
      s0_axis_clock => s0_axis_clock,
      slv_wren_clk2 => slv_wren_clk2,
      src_in => src_in
    );
\axi_rresp[1]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F80"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => \^slv_wren_done_pulse\,
      I2 => \axi_rresp[1]_i_2\(0),
      I3 => adc_ds_slv_rden,
      O => slv_rden_r_reg_1
    );
clk1_ready_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk1_ready_pulse0,
      Q => \^slv_wren_done_pulse\,
      R => p_0_in
    );
clk1_ready_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => slv_wren_clear,
      Q => clk1_ready_sync_r,
      R => p_0_in
    );
clk2_ready_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axis_clock,
      CE => '1',
      D => axi_2_drp_valid_i_n_2,
      Q => clk2_ready,
      R => \^sr\(0)
    );
clk2_valid_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axis_clock,
      CE => '1',
      D => clk2_valid_pulse0,
      Q => slv_wren_clk2,
      R => \^sr\(0)
    );
clk2_valid_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axis_clock,
      CE => '1',
      D => axi_2_drp_valid_i_n_0,
      Q => clk2_valid_sync_r,
      R => \^sr\(0)
    );
drp_2_axi_in_progress_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__2\
     port map (
      adc0axi_map_wready => adc0axi_map_wready,
      adc0slv_rden => adc0slv_rden,
      clk1_ready_pulse0 => clk1_ready_pulse0,
      clk1_ready_sync_r => clk1_ready_sync_r,
      dest_out => slv_wren_clear,
      s_axi_aclk => s_axi_aclk,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => slv_access_valid_hold_reg,
      src_in => src_in,
      \syncstages_ff_reg[0]\ => clk2_ready,
      \syncstages_ff_reg[4]\ => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__2\ is
  port (
    slv_wren_done_pulse : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_reg : out STD_LOGIC;
    clk2_valid_pulse_reg_2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_6 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_7 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_8 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_9 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_10 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_11 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_12 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_13 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_14 : out STD_LOGIC_VECTOR ( 0 to 0 );
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    p_0_in : in STD_LOGIC;
    \adc10_ds_enable_0_reg[0]\ : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    \adc13_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc13_ds_enable_0_reg[0]\ : in STD_LOGIC;
    slv_wren_done_pulse_0 : in STD_LOGIC;
    slv_rden_r_1 : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc_ds_axi_map_wready : in STD_LOGIC;
    \adc11_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc11_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc11_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc10_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc10_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc10_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc13_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc13_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc12_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc12_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc12_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc12_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc11_ds_inc_0_reg[0]\ : in STD_LOGIC;
    adc1axi_map_wready : in STD_LOGIC;
    adc1slv_rden : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__2\ : entity is "rfadc_exdes_ctrl_hshk_pls_gen";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__2\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__2\ is
  signal axi_2_drp_valid_i_n_0 : STD_LOGIC;
  signal axi_2_drp_valid_i_n_2 : STD_LOGIC;
  signal clk1_ready_pulse0 : STD_LOGIC;
  signal clk1_ready_sync_r : STD_LOGIC;
  signal clk2_ready : STD_LOGIC;
  signal clk2_valid_pulse0 : STD_LOGIC;
  signal clk2_valid_sync_r : STD_LOGIC;
  signal slv_wren_clear : STD_LOGIC;
  signal slv_wren_clk2 : STD_LOGIC;
  signal \^slv_wren_done_pulse\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \adc10_ds_control_0[1]_i_1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \adc10_ds_enable_0[7]_i_1\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \adc10_ds_inc_0[11]_i_1\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \adc10_ds_type_0[3]_i_1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \adc11_ds_control_0[1]_i_1\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \adc11_ds_enable_0[7]_i_1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \adc11_ds_inc_0[11]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \adc11_ds_type_0[3]_i_1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \adc12_ds_control_0[1]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \adc12_ds_enable_0[7]_i_1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \adc12_ds_inc_0[11]_i_1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \adc12_ds_type_0[3]_i_1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \adc13_ds_control_0[1]_i_1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \adc13_ds_enable_0[7]_i_1\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \adc13_ds_inc_0[11]_i_1\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \adc13_ds_type_0[3]_i_1\ : label is "soft_lutpair14";
begin
  slv_wren_done_pulse <= \^slv_wren_done_pulse\;
\adc10_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc10_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_6(0)
    );
\adc10_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc10_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => E(0)
    );
\adc10_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc10_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_7(0)
    );
\adc10_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc10_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_5(0)
    );
\adc11_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc11_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_2(0)
    );
\adc11_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc11_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_4(0)
    );
\adc11_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc11_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_14(0)
    );
\adc11_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc11_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_3(0)
    );
\adc12_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc12_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_13(0)
    );
\adc12_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc12_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_12(0)
    );
\adc12_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc12_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_11(0)
    );
\adc12_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc12_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_10(0)
    );
\adc13_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc13_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_9(0)
    );
\adc13_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc13_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_1(0)
    );
\adc13_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc13_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_8(0)
    );
\adc13_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc13_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_0(0)
    );
axi_2_drp_valid_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__3\
     port map (
      clk2_ready_reg => clk2_ready,
      clk2_valid_pulse0 => clk2_valid_pulse0,
      clk2_valid_pulse_reg => axi_2_drp_valid_i_n_2,
      clk2_valid_sync_r => clk2_valid_sync_r,
      dest_out => axi_2_drp_valid_i_n_0,
      s_axi_aclk => s_axi_aclk,
      slv_wren_clk2 => slv_wren_clk2,
      src_in => src_in
    );
\axi_bresp[1]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF44F444F444F4"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => \^slv_wren_done_pulse\,
      I2 => slv_wren_done_pulse_0,
      I3 => slv_rden_r_1,
      I4 => s_axi_wvalid,
      I5 => adc_ds_axi_map_wready,
      O => slv_rden_r_reg
    );
clk1_ready_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk1_ready_pulse0,
      Q => \^slv_wren_done_pulse\,
      R => p_0_in
    );
clk1_ready_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => slv_wren_clear,
      Q => clk1_ready_sync_r,
      R => p_0_in
    );
clk2_ready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_2_drp_valid_i_n_2,
      Q => clk2_ready,
      R => p_0_in
    );
clk2_valid_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk2_valid_pulse0,
      Q => slv_wren_clk2,
      R => p_0_in
    );
clk2_valid_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_2_drp_valid_i_n_0,
      Q => clk2_valid_sync_r,
      R => p_0_in
    );
drp_2_axi_in_progress_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__4\
     port map (
      adc1axi_map_wready => adc1axi_map_wready,
      adc1slv_rden => adc1slv_rden,
      clk1_ready_pulse0 => clk1_ready_pulse0,
      clk1_ready_sync_r => clk1_ready_sync_r,
      dest_out => slv_wren_clear,
      s_axi_aclk => s_axi_aclk,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => slv_access_valid_hold_reg,
      src_in => src_in,
      \syncstages_ff_reg[0]\ => clk2_ready,
      \syncstages_ff_reg[4]\ => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__3\ is
  port (
    slv_wren_done_pulse : out STD_LOGIC;
    slv_rden_r_reg : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_6 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_7 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_8 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_9 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_10 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_11 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_12 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_13 : out STD_LOGIC_VECTOR ( 0 to 0 );
    clk2_valid_pulse_reg_14 : out STD_LOGIC_VECTOR ( 0 to 0 );
    \syncstages_ff_reg[4]\ : out STD_LOGIC;
    src_in : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    p_0_in : in STD_LOGIC;
    slv_access_valid_hold_reg : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_0 : in STD_LOGIC;
    slv_wren_done_pulse_1 : in STD_LOGIC;
    \adc20_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc23_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc23_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc21_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc21_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc21_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc20_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc20_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc20_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc23_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc23_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc22_ds_type_0_reg[0]\ : in STD_LOGIC;
    \adc22_ds_inc_0_reg[0]\ : in STD_LOGIC;
    \adc22_ds_enable_0_reg[0]\ : in STD_LOGIC;
    \adc22_ds_control_0_reg[0]\ : in STD_LOGIC;
    \adc21_ds_inc_0_reg[0]\ : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc2axi_map_wready : in STD_LOGIC;
    adc2slv_rden : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__3\ : entity is "rfadc_exdes_ctrl_hshk_pls_gen";
end \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__3\;

architecture STRUCTURE of \decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__3\ is
  signal axi_2_drp_valid_i_n_0 : STD_LOGIC;
  signal axi_2_drp_valid_i_n_2 : STD_LOGIC;
  signal clk1_ready_pulse0 : STD_LOGIC;
  signal clk1_ready_sync_r : STD_LOGIC;
  signal clk2_ready : STD_LOGIC;
  signal clk2_valid_pulse0 : STD_LOGIC;
  signal clk2_valid_sync_r : STD_LOGIC;
  signal slv_wren_clear : STD_LOGIC;
  signal slv_wren_clk2 : STD_LOGIC;
  signal \^slv_wren_done_pulse\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \adc20_ds_control_0[1]_i_1\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \adc20_ds_enable_0[7]_i_1\ : label is "soft_lutpair23";
  attribute SOFT_HLUTNM of \adc20_ds_inc_0[11]_i_1\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \adc20_ds_type_0[3]_i_1\ : label is "soft_lutpair26";
  attribute SOFT_HLUTNM of \adc21_ds_control_0[1]_i_1\ : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of \adc21_ds_enable_0[7]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \adc21_ds_inc_0[11]_i_1\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \adc21_ds_type_0[3]_i_1\ : label is "soft_lutpair25";
  attribute SOFT_HLUTNM of \adc22_ds_control_0[1]_i_1\ : label is "soft_lutpair30";
  attribute SOFT_HLUTNM of \adc22_ds_enable_0[7]_i_1\ : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of \adc22_ds_inc_0[11]_i_1\ : label is "soft_lutpair29";
  attribute SOFT_HLUTNM of \adc22_ds_type_0[3]_i_1\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \adc23_ds_control_0[1]_i_1\ : label is "soft_lutpair28";
  attribute SOFT_HLUTNM of \adc23_ds_enable_0[7]_i_1\ : label is "soft_lutpair24";
  attribute SOFT_HLUTNM of \adc23_ds_inc_0[11]_i_1\ : label is "soft_lutpair27";
  attribute SOFT_HLUTNM of \adc23_ds_type_0[3]_i_1\ : label is "soft_lutpair23";
begin
  slv_wren_done_pulse <= \^slv_wren_done_pulse\;
\adc20_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc20_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_6(0)
    );
\adc20_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc20_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => E(0)
    );
\adc20_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc20_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_7(0)
    );
\adc20_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc20_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_5(0)
    );
\adc21_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc21_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_2(0)
    );
\adc21_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc21_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_4(0)
    );
\adc21_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc21_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_14(0)
    );
\adc21_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc21_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_3(0)
    );
\adc22_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc22_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_13(0)
    );
\adc22_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc22_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_12(0)
    );
\adc22_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc22_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_11(0)
    );
\adc22_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc22_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_10(0)
    );
\adc23_ds_control_0[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc23_ds_control_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_9(0)
    );
\adc23_ds_enable_0[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc23_ds_enable_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_1(0)
    );
\adc23_ds_inc_0[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc23_ds_inc_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_8(0)
    );
\adc23_ds_type_0[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => \adc23_ds_type_0_reg[0]\,
      I1 => slv_wren_clk2,
      I2 => slv_access_valid_hold_reg,
      O => clk2_valid_pulse_reg_0(0)
    );
axi_2_drp_valid_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__5\
     port map (
      clk2_ready_reg => clk2_ready,
      clk2_valid_pulse0 => clk2_valid_pulse0,
      clk2_valid_pulse_reg => axi_2_drp_valid_i_n_2,
      clk2_valid_sync_r => clk2_valid_sync_r,
      dest_out => axi_2_drp_valid_i_n_0,
      s_axi_aclk => s_axi_aclk,
      slv_wren_clk2 => slv_wren_clk2,
      src_in => src_in
    );
\axi_rresp[1]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"8F808080"
    )
        port map (
      I0 => slv_access_valid_hold_reg,
      I1 => \^slv_wren_done_pulse\,
      I2 => Q(0),
      I3 => slv_rden_r_0,
      I4 => slv_wren_done_pulse_1,
      O => slv_rden_r_reg
    );
clk1_ready_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk1_ready_pulse0,
      Q => \^slv_wren_done_pulse\,
      R => p_0_in
    );
clk1_ready_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => slv_wren_clear,
      Q => clk1_ready_sync_r,
      R => p_0_in
    );
clk2_ready_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_2_drp_valid_i_n_2,
      Q => clk2_ready,
      R => p_0_in
    );
clk2_valid_pulse_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk2_valid_pulse0,
      Q => slv_wren_clk2,
      R => p_0_in
    );
clk2_valid_sync_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_2_drp_valid_i_n_0,
      Q => clk2_valid_sync_r,
      R => p_0_in
    );
drp_2_axi_in_progress_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_sync__xdcDup__6\
     port map (
      adc2axi_map_wready => adc2axi_map_wready,
      adc2slv_rden => adc2slv_rden,
      clk1_ready_pulse0 => clk1_ready_pulse0,
      clk1_ready_sync_r => clk1_ready_sync_r,
      dest_out => slv_wren_clear,
      s_axi_aclk => s_axi_aclk,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => slv_access_valid_hold_reg,
      src_in => src_in,
      \syncstages_ff_reg[0]\ => clk2_ready,
      \syncstages_ff_reg[4]\ => \syncstages_ff_reg[4]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_sdpram_wrap is
  port (
    s0_axis_clock : in STD_LOGIC;
    wea : in STD_LOGIC_VECTOR ( 0 to 0 );
    Q : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \gen_wr_a.gen_word_narrow.mem_reg_1\ : in STD_LOGIC_VECTOR ( 127 downto 0 );
    \gen_wr_a.gen_word_narrow.mem_reg_1_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_sdpram_wrap;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_sdpram_wrap is
  signal xpm_memory_sdpram_inst_n_0 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_1 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_10 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_100 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_101 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_102 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_103 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_104 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_105 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_106 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_107 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_108 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_109 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_11 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_110 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_111 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_112 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_113 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_114 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_115 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_116 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_117 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_118 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_119 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_12 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_120 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_121 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_122 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_123 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_124 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_125 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_126 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_127 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_13 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_14 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_15 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_16 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_17 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_18 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_19 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_2 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_20 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_21 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_22 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_23 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_24 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_25 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_26 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_27 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_28 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_29 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_3 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_30 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_31 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_32 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_33 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_34 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_35 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_36 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_37 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_38 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_39 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_4 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_40 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_41 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_42 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_43 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_44 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_45 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_46 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_47 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_48 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_49 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_5 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_50 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_51 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_52 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_53 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_54 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_55 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_56 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_57 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_58 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_59 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_6 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_60 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_61 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_62 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_63 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_64 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_65 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_66 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_67 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_68 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_69 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_7 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_70 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_71 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_72 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_73 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_74 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_75 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_76 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_77 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_78 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_79 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_8 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_80 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_81 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_82 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_83 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_84 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_85 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_86 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_87 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_88 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_89 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_9 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_90 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_91 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_92 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_93 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_94 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_95 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_96 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_97 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_98 : STD_LOGIC;
  signal xpm_memory_sdpram_inst_n_99 : STD_LOGIC;
  signal NLW_xpm_memory_sdpram_inst_dbiterrb_UNCONNECTED : STD_LOGIC;
  signal NLW_xpm_memory_sdpram_inst_sbiterrb_UNCONNECTED : STD_LOGIC;
  attribute ADDR_WIDTH_A : integer;
  attribute ADDR_WIDTH_A of xpm_memory_sdpram_inst : label is 8;
  attribute ADDR_WIDTH_B : integer;
  attribute ADDR_WIDTH_B of xpm_memory_sdpram_inst : label is 8;
  attribute AUTO_SLEEP_TIME : integer;
  attribute AUTO_SLEEP_TIME of xpm_memory_sdpram_inst : label is 0;
  attribute BYTE_WRITE_WIDTH_A : integer;
  attribute BYTE_WRITE_WIDTH_A of xpm_memory_sdpram_inst : label is 128;
  attribute CASCADE_HEIGHT : integer;
  attribute CASCADE_HEIGHT of xpm_memory_sdpram_inst : label is 0;
  attribute CLOCKING_MODE : string;
  attribute CLOCKING_MODE of xpm_memory_sdpram_inst : label is "common_clock";
  attribute ECC_MODE : string;
  attribute ECC_MODE of xpm_memory_sdpram_inst : label is "no_ecc";
  attribute MEMORY_INIT_FILE : string;
  attribute MEMORY_INIT_FILE of xpm_memory_sdpram_inst : label is "none";
  attribute MEMORY_INIT_PARAM : string;
  attribute MEMORY_INIT_PARAM of xpm_memory_sdpram_inst : label is "";
  attribute MEMORY_OPTIMIZATION : string;
  attribute MEMORY_OPTIMIZATION of xpm_memory_sdpram_inst : label is "true";
  attribute MEMORY_PRIMITIVE : string;
  attribute MEMORY_PRIMITIVE of xpm_memory_sdpram_inst : label is "auto";
  attribute MEMORY_SIZE : integer;
  attribute MEMORY_SIZE of xpm_memory_sdpram_inst : label is 32768;
  attribute MESSAGE_CONTROL : integer;
  attribute MESSAGE_CONTROL of xpm_memory_sdpram_inst : label is 0;
  attribute P_CLOCKING_MODE : integer;
  attribute P_CLOCKING_MODE of xpm_memory_sdpram_inst : label is 0;
  attribute P_ECC_MODE : integer;
  attribute P_ECC_MODE of xpm_memory_sdpram_inst : label is 0;
  attribute P_MEMORY_OPTIMIZATION : integer;
  attribute P_MEMORY_OPTIMIZATION of xpm_memory_sdpram_inst : label is 1;
  attribute P_MEMORY_PRIMITIVE : integer;
  attribute P_MEMORY_PRIMITIVE of xpm_memory_sdpram_inst : label is 0;
  attribute P_WAKEUP_TIME : integer;
  attribute P_WAKEUP_TIME of xpm_memory_sdpram_inst : label is 0;
  attribute P_WRITE_MODE_B : integer;
  attribute P_WRITE_MODE_B of xpm_memory_sdpram_inst : label is 2;
  attribute READ_DATA_WIDTH_B : integer;
  attribute READ_DATA_WIDTH_B of xpm_memory_sdpram_inst : label is 128;
  attribute READ_LATENCY_B : integer;
  attribute READ_LATENCY_B of xpm_memory_sdpram_inst : label is 2;
  attribute READ_RESET_VALUE_B : string;
  attribute READ_RESET_VALUE_B of xpm_memory_sdpram_inst : label is "0";
  attribute RST_MODE_A : string;
  attribute RST_MODE_A of xpm_memory_sdpram_inst : label is "SYNC";
  attribute RST_MODE_B : string;
  attribute RST_MODE_B of xpm_memory_sdpram_inst : label is "SYNC";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of xpm_memory_sdpram_inst : label is 0;
  attribute USE_EMBEDDED_CONSTRAINT : integer;
  attribute USE_EMBEDDED_CONSTRAINT of xpm_memory_sdpram_inst : label is 0;
  attribute USE_MEM_INIT : integer;
  attribute USE_MEM_INIT of xpm_memory_sdpram_inst : label is 1;
  attribute USE_MEM_INIT_MMI : integer;
  attribute USE_MEM_INIT_MMI of xpm_memory_sdpram_inst : label is 0;
  attribute WAKEUP_TIME : string;
  attribute WAKEUP_TIME of xpm_memory_sdpram_inst : label is "disable_sleep";
  attribute WRITE_DATA_WIDTH_A : integer;
  attribute WRITE_DATA_WIDTH_A of xpm_memory_sdpram_inst : label is 128;
  attribute WRITE_MODE_B : string;
  attribute WRITE_MODE_B of xpm_memory_sdpram_inst : label is "no_change";
  attribute WRITE_PROTECT : integer;
  attribute WRITE_PROTECT of xpm_memory_sdpram_inst : label is 1;
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of xpm_memory_sdpram_inst : label is "TRUE";
begin
xpm_memory_sdpram_inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_memory_sdpram
     port map (
      addra(7 downto 0) => Q(7 downto 0),
      addrb(7 downto 0) => \gen_wr_a.gen_word_narrow.mem_reg_1_0\(7 downto 0),
      clka => s0_axis_clock,
      clkb => s0_axis_clock,
      dbiterrb => NLW_xpm_memory_sdpram_inst_dbiterrb_UNCONNECTED,
      dina(127 downto 0) => \gen_wr_a.gen_word_narrow.mem_reg_1\(127 downto 0),
      doutb(127) => xpm_memory_sdpram_inst_n_0,
      doutb(126) => xpm_memory_sdpram_inst_n_1,
      doutb(125) => xpm_memory_sdpram_inst_n_2,
      doutb(124) => xpm_memory_sdpram_inst_n_3,
      doutb(123) => xpm_memory_sdpram_inst_n_4,
      doutb(122) => xpm_memory_sdpram_inst_n_5,
      doutb(121) => xpm_memory_sdpram_inst_n_6,
      doutb(120) => xpm_memory_sdpram_inst_n_7,
      doutb(119) => xpm_memory_sdpram_inst_n_8,
      doutb(118) => xpm_memory_sdpram_inst_n_9,
      doutb(117) => xpm_memory_sdpram_inst_n_10,
      doutb(116) => xpm_memory_sdpram_inst_n_11,
      doutb(115) => xpm_memory_sdpram_inst_n_12,
      doutb(114) => xpm_memory_sdpram_inst_n_13,
      doutb(113) => xpm_memory_sdpram_inst_n_14,
      doutb(112) => xpm_memory_sdpram_inst_n_15,
      doutb(111) => xpm_memory_sdpram_inst_n_16,
      doutb(110) => xpm_memory_sdpram_inst_n_17,
      doutb(109) => xpm_memory_sdpram_inst_n_18,
      doutb(108) => xpm_memory_sdpram_inst_n_19,
      doutb(107) => xpm_memory_sdpram_inst_n_20,
      doutb(106) => xpm_memory_sdpram_inst_n_21,
      doutb(105) => xpm_memory_sdpram_inst_n_22,
      doutb(104) => xpm_memory_sdpram_inst_n_23,
      doutb(103) => xpm_memory_sdpram_inst_n_24,
      doutb(102) => xpm_memory_sdpram_inst_n_25,
      doutb(101) => xpm_memory_sdpram_inst_n_26,
      doutb(100) => xpm_memory_sdpram_inst_n_27,
      doutb(99) => xpm_memory_sdpram_inst_n_28,
      doutb(98) => xpm_memory_sdpram_inst_n_29,
      doutb(97) => xpm_memory_sdpram_inst_n_30,
      doutb(96) => xpm_memory_sdpram_inst_n_31,
      doutb(95) => xpm_memory_sdpram_inst_n_32,
      doutb(94) => xpm_memory_sdpram_inst_n_33,
      doutb(93) => xpm_memory_sdpram_inst_n_34,
      doutb(92) => xpm_memory_sdpram_inst_n_35,
      doutb(91) => xpm_memory_sdpram_inst_n_36,
      doutb(90) => xpm_memory_sdpram_inst_n_37,
      doutb(89) => xpm_memory_sdpram_inst_n_38,
      doutb(88) => xpm_memory_sdpram_inst_n_39,
      doutb(87) => xpm_memory_sdpram_inst_n_40,
      doutb(86) => xpm_memory_sdpram_inst_n_41,
      doutb(85) => xpm_memory_sdpram_inst_n_42,
      doutb(84) => xpm_memory_sdpram_inst_n_43,
      doutb(83) => xpm_memory_sdpram_inst_n_44,
      doutb(82) => xpm_memory_sdpram_inst_n_45,
      doutb(81) => xpm_memory_sdpram_inst_n_46,
      doutb(80) => xpm_memory_sdpram_inst_n_47,
      doutb(79) => xpm_memory_sdpram_inst_n_48,
      doutb(78) => xpm_memory_sdpram_inst_n_49,
      doutb(77) => xpm_memory_sdpram_inst_n_50,
      doutb(76) => xpm_memory_sdpram_inst_n_51,
      doutb(75) => xpm_memory_sdpram_inst_n_52,
      doutb(74) => xpm_memory_sdpram_inst_n_53,
      doutb(73) => xpm_memory_sdpram_inst_n_54,
      doutb(72) => xpm_memory_sdpram_inst_n_55,
      doutb(71) => xpm_memory_sdpram_inst_n_56,
      doutb(70) => xpm_memory_sdpram_inst_n_57,
      doutb(69) => xpm_memory_sdpram_inst_n_58,
      doutb(68) => xpm_memory_sdpram_inst_n_59,
      doutb(67) => xpm_memory_sdpram_inst_n_60,
      doutb(66) => xpm_memory_sdpram_inst_n_61,
      doutb(65) => xpm_memory_sdpram_inst_n_62,
      doutb(64) => xpm_memory_sdpram_inst_n_63,
      doutb(63) => xpm_memory_sdpram_inst_n_64,
      doutb(62) => xpm_memory_sdpram_inst_n_65,
      doutb(61) => xpm_memory_sdpram_inst_n_66,
      doutb(60) => xpm_memory_sdpram_inst_n_67,
      doutb(59) => xpm_memory_sdpram_inst_n_68,
      doutb(58) => xpm_memory_sdpram_inst_n_69,
      doutb(57) => xpm_memory_sdpram_inst_n_70,
      doutb(56) => xpm_memory_sdpram_inst_n_71,
      doutb(55) => xpm_memory_sdpram_inst_n_72,
      doutb(54) => xpm_memory_sdpram_inst_n_73,
      doutb(53) => xpm_memory_sdpram_inst_n_74,
      doutb(52) => xpm_memory_sdpram_inst_n_75,
      doutb(51) => xpm_memory_sdpram_inst_n_76,
      doutb(50) => xpm_memory_sdpram_inst_n_77,
      doutb(49) => xpm_memory_sdpram_inst_n_78,
      doutb(48) => xpm_memory_sdpram_inst_n_79,
      doutb(47) => xpm_memory_sdpram_inst_n_80,
      doutb(46) => xpm_memory_sdpram_inst_n_81,
      doutb(45) => xpm_memory_sdpram_inst_n_82,
      doutb(44) => xpm_memory_sdpram_inst_n_83,
      doutb(43) => xpm_memory_sdpram_inst_n_84,
      doutb(42) => xpm_memory_sdpram_inst_n_85,
      doutb(41) => xpm_memory_sdpram_inst_n_86,
      doutb(40) => xpm_memory_sdpram_inst_n_87,
      doutb(39) => xpm_memory_sdpram_inst_n_88,
      doutb(38) => xpm_memory_sdpram_inst_n_89,
      doutb(37) => xpm_memory_sdpram_inst_n_90,
      doutb(36) => xpm_memory_sdpram_inst_n_91,
      doutb(35) => xpm_memory_sdpram_inst_n_92,
      doutb(34) => xpm_memory_sdpram_inst_n_93,
      doutb(33) => xpm_memory_sdpram_inst_n_94,
      doutb(32) => xpm_memory_sdpram_inst_n_95,
      doutb(31) => xpm_memory_sdpram_inst_n_96,
      doutb(30) => xpm_memory_sdpram_inst_n_97,
      doutb(29) => xpm_memory_sdpram_inst_n_98,
      doutb(28) => xpm_memory_sdpram_inst_n_99,
      doutb(27) => xpm_memory_sdpram_inst_n_100,
      doutb(26) => xpm_memory_sdpram_inst_n_101,
      doutb(25) => xpm_memory_sdpram_inst_n_102,
      doutb(24) => xpm_memory_sdpram_inst_n_103,
      doutb(23) => xpm_memory_sdpram_inst_n_104,
      doutb(22) => xpm_memory_sdpram_inst_n_105,
      doutb(21) => xpm_memory_sdpram_inst_n_106,
      doutb(20) => xpm_memory_sdpram_inst_n_107,
      doutb(19) => xpm_memory_sdpram_inst_n_108,
      doutb(18) => xpm_memory_sdpram_inst_n_109,
      doutb(17) => xpm_memory_sdpram_inst_n_110,
      doutb(16) => xpm_memory_sdpram_inst_n_111,
      doutb(15) => xpm_memory_sdpram_inst_n_112,
      doutb(14) => xpm_memory_sdpram_inst_n_113,
      doutb(13) => xpm_memory_sdpram_inst_n_114,
      doutb(12) => xpm_memory_sdpram_inst_n_115,
      doutb(11) => xpm_memory_sdpram_inst_n_116,
      doutb(10) => xpm_memory_sdpram_inst_n_117,
      doutb(9) => xpm_memory_sdpram_inst_n_118,
      doutb(8) => xpm_memory_sdpram_inst_n_119,
      doutb(7) => xpm_memory_sdpram_inst_n_120,
      doutb(6) => xpm_memory_sdpram_inst_n_121,
      doutb(5) => xpm_memory_sdpram_inst_n_122,
      doutb(4) => xpm_memory_sdpram_inst_n_123,
      doutb(3) => xpm_memory_sdpram_inst_n_124,
      doutb(2) => xpm_memory_sdpram_inst_n_125,
      doutb(1) => xpm_memory_sdpram_inst_n_126,
      doutb(0) => xpm_memory_sdpram_inst_n_127,
      ena => '1',
      enb => '1',
      injectdbiterra => '0',
      injectsbiterra => '0',
      regceb => '1',
      rstb => '0',
      sbiterrb => NLW_xpm_memory_sdpram_inst_sbiterrb_UNCONNECTED,
      sleep => '0',
      wea(0) => wea(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc0_rfadc_exdes_ctrl_axi is
  port (
    slv_wren_done_pulse : out STD_LOGIC;
    slv_rden_r : out STD_LOGIC;
    adc00_ds_pulse_control_0 : out STD_LOGIC;
    \adc03_ds_control_0_reg[1]_0\ : out STD_LOGIC;
    slv_rden_r_reg_0 : out STD_LOGIC;
    \adc03_ds_inc_0_reg[11]_0\ : out STD_LOGIC;
    \adc03_ds_inc_0_reg[8]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc01_ds_inc_0_reg[8]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc02_ds_inc_0_reg[8]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc00_ds_inc_0_reg[8]_0\ : out STD_LOGIC_VECTOR ( 8 downto 0 );
    \adc03_ds_inc_0_reg[10]_0\ : out STD_LOGIC;
    \adc03_ds_inc_0_reg[9]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[7]_0\ : out STD_LOGIC;
    \adc01_ds_inc_0_reg[7]_0\ : out STD_LOGIC;
    \adc01_ds_inc_0_reg[6]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[6]_0\ : out STD_LOGIC;
    \adc01_ds_inc_0_reg[5]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[5]_0\ : out STD_LOGIC;
    \adc01_ds_inc_0_reg[4]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[4]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[3]_0\ : out STD_LOGIC;
    \adc01_ds_inc_0_reg[3]_0\ : out STD_LOGIC;
    \adc01_ds_inc_0_reg[2]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[2]_0\ : out STD_LOGIC;
    \adc01_ds_inc_0_reg[1]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[1]_0\ : out STD_LOGIC;
    \adc01_ds_type_0_reg[1]_0\ : out STD_LOGIC;
    \adc01_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 2 downto 0 );
    \adc02_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 2 downto 0 );
    \adc03_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 2 downto 0 );
    \adc03_ds_control_0_reg[0]_0\ : out STD_LOGIC;
    \adc00_ds_control_0_reg[1]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc01_ds_inc_0_reg[0]_0\ : out STD_LOGIC;
    \adc03_ds_enable_0_reg[0]_0\ : out STD_LOGIC;
    s00_tready : out STD_LOGIC;
    \adc00_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 3 downto 0 );
    slv_rdata : out STD_LOGIC_VECTOR ( 15 downto 0 );
    s0_axis_clock : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    p_0_in : in STD_LOGIC;
    adc0slv_rden : in STD_LOGIC;
    \adc03_ds_enable_0_reg[7]_1\ : in STD_LOGIC;
    \adc00_ds_type_0_reg[3]_1\ : in STD_LOGIC;
    \adc03_ds_control_0_reg[1]_1\ : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \slv_rdata_reg[1]_0\ : in STD_LOGIC;
    \axi_rresp[1]_i_2\ : in STD_LOGIC_VECTOR ( 0 to 0 );
    adc_ds_slv_rden : in STD_LOGIC;
    \adc00_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc03_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc01_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc01_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc01_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc00_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc00_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc03_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc02_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc02_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc02_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc02_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc01_ds_inc_0_reg[0]_1\ : in STD_LOGIC;
    dest_rst : in STD_LOGIC;
    adc00_ds_pulse_control_0_reg_0 : in STD_LOGIC;
    adc00_ds_pulse_control_0_reg_1 : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc0axi_map_wready : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wdata : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_aresetn : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \slv_rdata_reg[15]_0\ : in STD_LOGIC;
    \slv_rdata_reg[14]_0\ : in STD_LOGIC;
    \slv_rdata_reg[13]_0\ : in STD_LOGIC;
    \slv_rdata_reg[12]_0\ : in STD_LOGIC;
    \slv_rdata_reg[7]_0\ : in STD_LOGIC;
    \slv_rdata_reg[6]_0\ : in STD_LOGIC;
    \slv_rdata_reg[5]_0\ : in STD_LOGIC;
    \slv_rdata_reg[4]_0\ : in STD_LOGIC;
    \slv_rdata_reg[3]_0\ : in STD_LOGIC;
    \slv_rdata_reg[2]_0\ : in STD_LOGIC;
    \slv_rdata_reg[12]_1\ : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc0_rfadc_exdes_ctrl_axi;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc0_rfadc_exdes_ctrl_axi is
  signal adc00_ds_control_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal adc00_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 1 );
  signal adc00_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 9 );
  signal \^adc00_ds_pulse_control_0\ : STD_LOGIC;
  signal adc01_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc01_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal adc01_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc01_ds_type_0 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal adc02_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc02_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal adc02_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc02_ds_type_0 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal adc03_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc03_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal adc03_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc03_ds_type_0 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal clk2clk_handshake_pulse_gen_i_n_1 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_10 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_11 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_12 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_13 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_14 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_15 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_16 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_17 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_18 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_19 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_2 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_20 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_3 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_4 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_6 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_7 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_8 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_9 : STD_LOGIC;
  signal \^s00_tready\ : STD_LOGIC;
  signal slv_access_valid_hold : STD_LOGIC;
  signal \slv_rdata[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_rdata[7]_i_1_n_0\ : STD_LOGIC;
  signal \^slv_rden_r\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[0]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[10]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[11]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[1]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[2]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[3]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[4]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[5]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[6]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[7]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[8]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[9]\ : STD_LOGIC;
begin
  adc00_ds_pulse_control_0 <= \^adc00_ds_pulse_control_0\;
  s00_tready <= \^s00_tready\;
  slv_rden_r <= \^slv_rden_r\;
\adc00_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc00_ds_control_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => \adc00_ds_control_0_reg[1]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => \^s00_tready\,
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc00_ds_enable_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc00_ds_enable_0(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc00_ds_enable_0(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc00_ds_enable_0(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc00_ds_enable_0(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc00_ds_enable_0(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc00_ds_enable_0(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc00_ds_inc_0(10),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc00_ds_inc_0(11),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => \adc00_ds_inc_0_reg[8]_0\(8),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc00_ds_inc_0(9),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
adc00_ds_pulse_control_0_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => clk2clk_handshake_pulse_gen_i_n_19,
      Q => \^adc00_ds_pulse_control_0\,
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => \adc00_ds_type_0_reg[3]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => \adc00_ds_type_0_reg[3]_0\(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc00_ds_type_0_reg[3]_0\(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc00_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc00_ds_type_0_reg[3]_0\(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc01_ds_control_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc01_ds_control_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc01_ds_enable_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc01_ds_enable_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc01_ds_enable_0(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc01_ds_enable_0(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc01_ds_enable_0(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc01_ds_enable_0(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc01_ds_enable_0(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc01_ds_enable_0(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc01_ds_inc_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc01_ds_inc_0(10),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc01_ds_inc_0(11),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc01_ds_inc_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc01_ds_inc_0(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc01_ds_inc_0(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc01_ds_inc_0(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc01_ds_inc_0(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc01_ds_inc_0(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc01_ds_inc_0(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => \adc01_ds_inc_0_reg[8]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_18,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc01_ds_inc_0(9),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => \adc01_ds_type_0_reg[3]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc01_ds_type_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc01_ds_type_0_reg[3]_0\(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc01_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc01_ds_type_0_reg[3]_0\(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc02_ds_control_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc02_ds_control_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc02_ds_enable_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc02_ds_enable_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc02_ds_enable_0(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc02_ds_enable_0(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc02_ds_enable_0(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc02_ds_enable_0(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc02_ds_enable_0(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc02_ds_enable_0(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc02_ds_inc_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc02_ds_inc_0(10),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc02_ds_inc_0(11),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc02_ds_inc_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc02_ds_inc_0(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc02_ds_inc_0(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc02_ds_inc_0(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc02_ds_inc_0(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc02_ds_inc_0(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc02_ds_inc_0(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => \adc02_ds_inc_0_reg[8]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc02_ds_inc_0(9),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => \adc02_ds_type_0_reg[3]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc02_ds_type_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc02_ds_type_0_reg[3]_0\(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc02_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc02_ds_type_0_reg[3]_0\(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc03_ds_control_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc03_ds_control_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc03_ds_enable_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc03_ds_enable_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc03_ds_enable_0(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc03_ds_enable_0(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc03_ds_enable_0(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc03_ds_enable_0(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc03_ds_enable_0(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc03_ds_enable_0(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc03_ds_inc_0(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc03_ds_inc_0(10),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc03_ds_inc_0(11),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc03_ds_inc_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc03_ds_inc_0(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc03_ds_inc_0(3),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc03_ds_inc_0(4),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc03_ds_inc_0(5),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc03_ds_inc_0(6),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc03_ds_inc_0(7),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => \adc03_ds_inc_0_reg[8]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc03_ds_inc_0(9),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => \adc03_ds_type_0_reg[3]_0\(0),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc03_ds_type_0(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc03_ds_type_0_reg[3]_0\(1),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
\adc03_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc03_ds_type_0_reg[3]_0\(2),
      R => clk2clk_handshake_pulse_gen_i_n_1
    );
clk2clk_handshake_pulse_gen_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__1\
     port map (
      E(0) => clk2clk_handshake_pulse_gen_i_n_2,
      Q(0) => \slv_wdata_r_internal_reg_n_0_[0]\,
      SR(0) => clk2clk_handshake_pulse_gen_i_n_1,
      \adc00_ds_control_0_reg[0]\ => \adc00_ds_control_0_reg[0]_0\,
      \adc00_ds_enable_0_reg[0]\ => \adc00_ds_enable_0_reg[0]_0\,
      \adc00_ds_inc_0_reg[0]\ => \adc00_ds_inc_0_reg[0]_0\,
      adc00_ds_pulse_control_0 => \^adc00_ds_pulse_control_0\,
      adc00_ds_pulse_control_0_reg => adc00_ds_pulse_control_0_reg_0,
      adc00_ds_pulse_control_0_reg_0(0) => Q(0),
      adc00_ds_pulse_control_0_reg_1 => adc00_ds_pulse_control_0_reg_1,
      \adc00_ds_type_0_reg[3]\ => \adc00_ds_type_0_reg[3]_1\,
      \adc01_ds_control_0_reg[0]\ => \adc01_ds_control_0_reg[0]_0\,
      \adc01_ds_enable_0_reg[0]\ => \adc01_ds_enable_0_reg[0]_0\,
      \adc01_ds_inc_0_reg[0]\ => \adc01_ds_inc_0_reg[0]_1\,
      \adc01_ds_type_0_reg[0]\ => \adc01_ds_type_0_reg[0]_0\,
      \adc02_ds_control_0_reg[0]\ => \adc02_ds_control_0_reg[0]_0\,
      \adc02_ds_enable_0_reg[0]\ => \adc02_ds_enable_0_reg[0]_0\,
      \adc02_ds_inc_0_reg[0]\ => \adc02_ds_inc_0_reg[0]_0\,
      \adc02_ds_type_0_reg[0]\ => \adc02_ds_type_0_reg[0]_0\,
      \adc03_ds_control_0_reg[1]\ => \adc03_ds_control_0_reg[1]_1\,
      \adc03_ds_enable_0_reg[7]\ => \adc03_ds_enable_0_reg[7]_1\,
      \adc03_ds_inc_0_reg[0]\ => \adc03_ds_inc_0_reg[0]_0\,
      \adc03_ds_type_0_reg[0]\ => \adc03_ds_type_0_reg[0]_0\,
      adc0axi_map_wready => adc0axi_map_wready,
      adc0slv_rden => adc0slv_rden,
      adc_ds_slv_rden => adc_ds_slv_rden,
      \axi_rresp[1]_i_2\(0) => \axi_rresp[1]_i_2\(0),
      dest_rst => dest_rst,
      p_0_in => p_0_in,
      s0_axis_clock => s0_axis_clock,
      s_axi_aclk => s_axi_aclk,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => \^slv_rden_r\,
      slv_rden_r_reg(0) => clk2clk_handshake_pulse_gen_i_n_3,
      slv_rden_r_reg_0(0) => clk2clk_handshake_pulse_gen_i_n_4,
      slv_rden_r_reg_1 => slv_rden_r_reg_0,
      slv_rden_r_reg_10(0) => clk2clk_handshake_pulse_gen_i_n_14,
      slv_rden_r_reg_11(0) => clk2clk_handshake_pulse_gen_i_n_15,
      slv_rden_r_reg_12(0) => clk2clk_handshake_pulse_gen_i_n_16,
      slv_rden_r_reg_13(0) => clk2clk_handshake_pulse_gen_i_n_17,
      slv_rden_r_reg_14(0) => clk2clk_handshake_pulse_gen_i_n_18,
      slv_rden_r_reg_2(0) => clk2clk_handshake_pulse_gen_i_n_6,
      slv_rden_r_reg_3(0) => clk2clk_handshake_pulse_gen_i_n_7,
      slv_rden_r_reg_4(0) => clk2clk_handshake_pulse_gen_i_n_8,
      slv_rden_r_reg_5(0) => clk2clk_handshake_pulse_gen_i_n_9,
      slv_rden_r_reg_6(0) => clk2clk_handshake_pulse_gen_i_n_10,
      slv_rden_r_reg_7(0) => clk2clk_handshake_pulse_gen_i_n_11,
      slv_rden_r_reg_8(0) => clk2clk_handshake_pulse_gen_i_n_12,
      slv_rden_r_reg_9(0) => clk2clk_handshake_pulse_gen_i_n_13,
      \slv_wdata_r_internal_reg[0]\ => clk2clk_handshake_pulse_gen_i_n_19,
      slv_wren_done_pulse => slv_wren_done_pulse,
      src_in => slv_access_valid_hold,
      \syncstages_ff_reg[4]\ => clk2clk_handshake_pulse_gen_i_n_20
    );
slv_access_valid_hold_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk2clk_handshake_pulse_gen_i_n_20,
      Q => slv_access_valid_hold,
      R => p_0_in
    );
\slv_rdata[0]_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(0),
      I1 => adc01_ds_enable_0(0),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(0),
      I4 => Q(3),
      I5 => \^s00_tready\,
      O => \adc03_ds_enable_0_reg[0]_0\
    );
\slv_rdata[0]_i_12\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(0),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(0),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(0),
      O => \adc01_ds_inc_0_reg[0]_0\
    );
\slv_rdata[0]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_control_0(0),
      I1 => adc01_ds_control_0(0),
      I2 => Q(2),
      I3 => adc02_ds_control_0(0),
      I4 => Q(3),
      I5 => adc00_ds_control_0(0),
      O => \adc03_ds_control_0_reg[0]_0\
    );
\slv_rdata[10]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_inc_0(10),
      I1 => adc01_ds_inc_0(10),
      I2 => Q(2),
      I3 => adc02_ds_inc_0(10),
      I4 => Q(3),
      I5 => adc00_ds_inc_0(10),
      O => \adc03_ds_inc_0_reg[10]_0\
    );
\slv_rdata[11]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_inc_0(11),
      I1 => adc01_ds_inc_0(11),
      I2 => Q(2),
      I3 => adc02_ds_inc_0(11),
      I4 => Q(3),
      I5 => adc00_ds_inc_0(11),
      O => \adc03_ds_inc_0_reg[11]_0\
    );
\slv_rdata[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFE00000000"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      I2 => Q(5),
      I3 => Q(4),
      I4 => \slv_rdata_reg[12]_1\,
      I5 => s_axi_aresetn,
      O => \slv_rdata[15]_i_1_n_0\
    );
\slv_rdata[1]_i_11\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(1),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(1),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(1),
      O => \adc01_ds_inc_0_reg[1]_0\
    );
\slv_rdata[1]_i_14\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_type_0(1),
      I1 => Q(3),
      I2 => adc02_ds_type_0(1),
      I3 => Q(2),
      I4 => adc03_ds_type_0(1),
      O => \adc01_ds_type_0_reg[1]_0\
    );
\slv_rdata[1]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"470047CCFFFFFFFF"
    )
        port map (
      I0 => adc03_ds_control_0(1),
      I1 => Q(2),
      I2 => adc02_ds_control_0(1),
      I3 => Q(3),
      I4 => adc01_ds_control_0(1),
      I5 => \slv_rdata_reg[1]_0\,
      O => \adc03_ds_control_0_reg[1]_0\
    );
\slv_rdata[1]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(1),
      I1 => adc01_ds_enable_0(1),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(1),
      I4 => Q(3),
      I5 => adc00_ds_enable_0(1),
      O => \adc03_ds_enable_0_reg[1]_0\
    );
\slv_rdata[2]_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(2),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(2),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(2),
      O => \adc01_ds_inc_0_reg[2]_0\
    );
\slv_rdata[2]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(2),
      I1 => adc01_ds_enable_0(2),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(2),
      I4 => Q(3),
      I5 => adc00_ds_enable_0(2),
      O => \adc03_ds_enable_0_reg[2]_0\
    );
\slv_rdata[3]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(3),
      I1 => adc01_ds_enable_0(3),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(3),
      I4 => Q(3),
      I5 => adc00_ds_enable_0(3),
      O => \adc03_ds_enable_0_reg[3]_0\
    );
\slv_rdata[3]_i_9__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(3),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(3),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(3),
      O => \adc01_ds_inc_0_reg[3]_0\
    );
\slv_rdata[4]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(4),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(4),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(4),
      O => \adc01_ds_inc_0_reg[4]_0\
    );
\slv_rdata[4]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(4),
      I1 => adc01_ds_enable_0(4),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(4),
      I4 => Q(3),
      I5 => adc00_ds_enable_0(4),
      O => \adc03_ds_enable_0_reg[4]_0\
    );
\slv_rdata[5]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(5),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(5),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(5),
      O => \adc01_ds_inc_0_reg[5]_0\
    );
\slv_rdata[5]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(5),
      I1 => adc01_ds_enable_0(5),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(5),
      I4 => Q(3),
      I5 => adc00_ds_enable_0(5),
      O => \adc03_ds_enable_0_reg[5]_0\
    );
\slv_rdata[6]_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(6),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(6),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(6),
      O => \adc01_ds_inc_0_reg[6]_0\
    );
\slv_rdata[6]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(6),
      I1 => adc01_ds_enable_0(6),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(6),
      I4 => Q(3),
      I5 => adc00_ds_enable_0(6),
      O => \adc03_ds_enable_0_reg[6]_0\
    );
\slv_rdata[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"E0"
    )
        port map (
      I0 => Q(5),
      I1 => Q(4),
      I2 => s_axi_aresetn,
      O => \slv_rdata[7]_i_1_n_0\
    );
\slv_rdata[7]_i_11\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"110CDD0C"
    )
        port map (
      I0 => adc01_ds_inc_0(7),
      I1 => Q(3),
      I2 => adc02_ds_inc_0(7),
      I3 => Q(2),
      I4 => adc03_ds_inc_0(7),
      O => \adc01_ds_inc_0_reg[7]_0\
    );
\slv_rdata[7]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_enable_0(7),
      I1 => adc01_ds_enable_0(7),
      I2 => Q(2),
      I3 => adc02_ds_enable_0(7),
      I4 => Q(3),
      I5 => adc00_ds_enable_0(7),
      O => \adc03_ds_enable_0_reg[7]_0\
    );
\slv_rdata[9]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc03_ds_inc_0(9),
      I1 => adc01_ds_inc_0(9),
      I2 => Q(2),
      I3 => adc02_ds_inc_0(9),
      I4 => Q(3),
      I5 => adc00_ds_inc_0(9),
      O => \adc03_ds_inc_0_reg[9]_0\
    );
\slv_rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(0),
      Q => slv_rdata(0),
      R => '0'
    );
\slv_rdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(4),
      Q => slv_rdata(10),
      R => '0'
    );
\slv_rdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(5),
      Q => slv_rdata(11),
      R => '0'
    );
\slv_rdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[12]_0\,
      Q => slv_rdata(12),
      R => \slv_rdata[15]_i_1_n_0\
    );
\slv_rdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[13]_0\,
      Q => slv_rdata(13),
      R => \slv_rdata[15]_i_1_n_0\
    );
\slv_rdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[14]_0\,
      Q => slv_rdata(14),
      R => \slv_rdata[15]_i_1_n_0\
    );
\slv_rdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[15]_0\,
      Q => slv_rdata(15),
      R => \slv_rdata[15]_i_1_n_0\
    );
\slv_rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(1),
      Q => slv_rdata(1),
      R => '0'
    );
\slv_rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[2]_0\,
      Q => slv_rdata(2),
      R => \slv_rdata[7]_i_1_n_0\
    );
\slv_rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[3]_0\,
      Q => slv_rdata(3),
      R => \slv_rdata[7]_i_1_n_0\
    );
\slv_rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[4]_0\,
      Q => slv_rdata(4),
      R => \slv_rdata[7]_i_1_n_0\
    );
\slv_rdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[5]_0\,
      Q => slv_rdata(5),
      R => \slv_rdata[7]_i_1_n_0\
    );
\slv_rdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[6]_0\,
      Q => slv_rdata(6),
      R => \slv_rdata[7]_i_1_n_0\
    );
\slv_rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata_reg[7]_0\,
      Q => slv_rdata(7),
      R => \slv_rdata[7]_i_1_n_0\
    );
\slv_rdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(2),
      Q => slv_rdata(8),
      R => '0'
    );
\slv_rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(3),
      Q => slv_rdata(9),
      R => '0'
    );
slv_rden_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => adc0slv_rden,
      Q => \^slv_rden_r\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(0),
      Q => \slv_wdata_r_internal_reg_n_0_[0]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(10),
      Q => \slv_wdata_r_internal_reg_n_0_[10]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(11),
      Q => \slv_wdata_r_internal_reg_n_0_[11]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(1),
      Q => \slv_wdata_r_internal_reg_n_0_[1]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(2),
      Q => \slv_wdata_r_internal_reg_n_0_[2]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(3),
      Q => \slv_wdata_r_internal_reg_n_0_[3]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(4),
      Q => \slv_wdata_r_internal_reg_n_0_[4]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(5),
      Q => \slv_wdata_r_internal_reg_n_0_[5]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(6),
      Q => \slv_wdata_r_internal_reg_n_0_[6]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(7),
      Q => \slv_wdata_r_internal_reg_n_0_[7]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(8),
      Q => \slv_wdata_r_internal_reg_n_0_[8]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(9),
      Q => \slv_wdata_r_internal_reg_n_0_[9]\,
      R => p_0_in
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc1_rfadc_exdes_ctrl_axi is
  port (
    slv_wren_done_pulse : out STD_LOGIC;
    slv_rden_r : out STD_LOGIC;
    slv_rden_r_reg_0 : out STD_LOGIC;
    \adc13_ds_inc_0_reg[8]_0\ : out STD_LOGIC;
    \adc13_ds_inc_0_reg[7]_0\ : out STD_LOGIC;
    \adc13_ds_inc_0_reg[6]_0\ : out STD_LOGIC;
    \adc13_ds_inc_0_reg[5]_0\ : out STD_LOGIC;
    \adc13_ds_inc_0_reg[4]_0\ : out STD_LOGIC;
    \adc13_ds_inc_0_reg[3]_0\ : out STD_LOGIC;
    \adc13_ds_inc_0_reg[2]_0\ : out STD_LOGIC;
    \adc13_ds_type_0_reg[2]_0\ : out STD_LOGIC;
    \adc13_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc11_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc12_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc10_ds_type_0_reg[3]_0\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \adc13_ds_inc_0_reg[1]_0\ : out STD_LOGIC;
    \adc13_ds_control_0_reg[1]_0\ : out STD_LOGIC;
    \adc13_ds_enable_0_reg[1]_0\ : out STD_LOGIC;
    \adc13_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 5 downto 0 );
    \adc11_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 5 downto 0 );
    \adc12_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 5 downto 0 );
    \adc10_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 5 downto 0 );
    \adc13_ds_type_0_reg[1]_0\ : out STD_LOGIC;
    \adc13_ds_enable_0_reg[0]_0\ : out STD_LOGIC;
    \adc13_ds_type_0_reg[0]_0\ : out STD_LOGIC;
    \adc13_ds_inc_0_reg[0]_0\ : out STD_LOGIC;
    \adc13_ds_control_0_reg[0]_0\ : out STD_LOGIC;
    \slv_rdata_reg[8]_0\ : out STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_rdata_reg[11]_0\ : out STD_LOGIC;
    \slv_addr_reg[6]\ : out STD_LOGIC;
    \slv_rdata_reg[10]_0\ : out STD_LOGIC;
    \slv_rdata_reg[9]_0\ : out STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    p_0_in : in STD_LOGIC;
    adc1slv_rden : in STD_LOGIC;
    \adc10_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc13_ds_type_0_reg[0]_1\ : in STD_LOGIC;
    \adc13_ds_enable_0_reg[0]_1\ : in STD_LOGIC;
    slv_wren_done_pulse_0 : in STD_LOGIC;
    slv_rden_r_1 : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc_ds_axi_map_wready : in STD_LOGIC;
    \adc11_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc11_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc11_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc10_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc10_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc10_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc13_ds_inc_0_reg[0]_1\ : in STD_LOGIC;
    \adc13_ds_control_0_reg[0]_1\ : in STD_LOGIC;
    \adc12_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc12_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc12_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc12_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc11_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 5 downto 0 );
    adc1axi_map_wready : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wdata : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_aresetn : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_rdata_reg[11]_1\ : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc1_rfadc_exdes_ctrl_axi;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc1_rfadc_exdes_ctrl_axi is
  signal adc10_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc10_ds_enable_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc10_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc10_ds_type_0 : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal adc11_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc11_ds_enable_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc11_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc11_ds_type_0 : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal adc12_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc12_ds_enable_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc12_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc12_ds_type_0 : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal adc13_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc13_ds_enable_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc13_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc13_ds_type_0 : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal clk2clk_handshake_pulse_gen_i_n_1 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_10 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_11 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_12 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_13 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_14 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_15 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_16 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_17 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_18 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_2 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_3 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_5 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_6 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_7 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_8 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_9 : STD_LOGIC;
  signal slv_access_valid_hold : STD_LOGIC;
  signal \^slv_addr_reg[6]\ : STD_LOGIC;
  signal \slv_rdata[10]_i_1__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_2_n_0\ : STD_LOGIC;
  signal \slv_rdata[9]_i_1__0_n_0\ : STD_LOGIC;
  signal \^slv_rden_r\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[0]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[10]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[11]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[1]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[2]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[3]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[4]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[5]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[6]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[7]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[8]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[9]\ : STD_LOGIC;
begin
  \slv_addr_reg[6]\ <= \^slv_addr_reg[6]\;
  slv_rden_r <= \^slv_rden_r\;
\adc10_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc10_ds_control_0(0),
      R => p_0_in
    );
\adc10_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc10_ds_control_0(1),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc10_ds_enable_0(0),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc10_ds_enable_0(1),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc10_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc10_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc10_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc10_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc10_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc10_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_1,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc10_ds_enable_0_reg[7]_0\(5),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc10_ds_inc_0(0),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc10_ds_inc_0(10),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc10_ds_inc_0(11),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc10_ds_inc_0(1),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc10_ds_inc_0(2),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc10_ds_inc_0(3),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc10_ds_inc_0(4),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc10_ds_inc_0(5),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc10_ds_inc_0(6),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc10_ds_inc_0(7),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc10_ds_inc_0(8),
      R => p_0_in
    );
\adc10_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc10_ds_inc_0(9),
      R => p_0_in
    );
\adc10_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc10_ds_type_0(0),
      R => p_0_in
    );
\adc10_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc10_ds_type_0(1),
      R => p_0_in
    );
\adc10_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc10_ds_type_0(2),
      R => p_0_in
    );
\adc10_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc10_ds_type_0_reg[3]_0\(0),
      R => p_0_in
    );
\adc11_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_5,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc11_ds_control_0(0),
      R => p_0_in
    );
\adc11_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_5,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc11_ds_control_0(1),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc11_ds_enable_0(0),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc11_ds_enable_0(1),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc11_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc11_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc11_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc11_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc11_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc11_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc11_ds_enable_0_reg[7]_0\(5),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc11_ds_inc_0(0),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc11_ds_inc_0(10),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc11_ds_inc_0(11),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc11_ds_inc_0(1),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc11_ds_inc_0(2),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc11_ds_inc_0(3),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc11_ds_inc_0(4),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc11_ds_inc_0(5),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc11_ds_inc_0(6),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc11_ds_inc_0(7),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc11_ds_inc_0(8),
      R => p_0_in
    );
\adc11_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc11_ds_inc_0(9),
      R => p_0_in
    );
\adc11_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc11_ds_type_0(0),
      R => p_0_in
    );
\adc11_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc11_ds_type_0(1),
      R => p_0_in
    );
\adc11_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc11_ds_type_0(2),
      R => p_0_in
    );
\adc11_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc11_ds_type_0_reg[3]_0\(0),
      R => p_0_in
    );
\adc12_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc12_ds_control_0(0),
      R => p_0_in
    );
\adc12_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc12_ds_control_0(1),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc12_ds_enable_0(0),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc12_ds_enable_0(1),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc12_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc12_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc12_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc12_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc12_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc12_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc12_ds_enable_0_reg[7]_0\(5),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc12_ds_inc_0(0),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc12_ds_inc_0(10),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc12_ds_inc_0(11),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc12_ds_inc_0(1),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc12_ds_inc_0(2),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc12_ds_inc_0(3),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc12_ds_inc_0(4),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc12_ds_inc_0(5),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc12_ds_inc_0(6),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc12_ds_inc_0(7),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc12_ds_inc_0(8),
      R => p_0_in
    );
\adc12_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc12_ds_inc_0(9),
      R => p_0_in
    );
\adc12_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc12_ds_type_0(0),
      R => p_0_in
    );
\adc12_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc12_ds_type_0(1),
      R => p_0_in
    );
\adc12_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc12_ds_type_0(2),
      R => p_0_in
    );
\adc12_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc12_ds_type_0_reg[3]_0\(0),
      R => p_0_in
    );
\adc13_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc13_ds_control_0(0),
      R => p_0_in
    );
\adc13_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc13_ds_control_0(1),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc13_ds_enable_0(0),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc13_ds_enable_0(1),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc13_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc13_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc13_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc13_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc13_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc13_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc13_ds_enable_0_reg[7]_0\(5),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc13_ds_inc_0(0),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc13_ds_inc_0(10),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc13_ds_inc_0(11),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc13_ds_inc_0(1),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc13_ds_inc_0(2),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc13_ds_inc_0(3),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc13_ds_inc_0(4),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc13_ds_inc_0(5),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc13_ds_inc_0(6),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc13_ds_inc_0(7),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc13_ds_inc_0(8),
      R => p_0_in
    );
\adc13_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc13_ds_inc_0(9),
      R => p_0_in
    );
\adc13_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc13_ds_type_0(0),
      R => p_0_in
    );
\adc13_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc13_ds_type_0(1),
      R => p_0_in
    );
\adc13_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc13_ds_type_0(2),
      R => p_0_in
    );
\adc13_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => \adc13_ds_type_0_reg[3]_0\(0),
      R => p_0_in
    );
clk2clk_handshake_pulse_gen_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__2\
     port map (
      E(0) => clk2clk_handshake_pulse_gen_i_n_1,
      \adc10_ds_control_0_reg[0]\ => \adc10_ds_control_0_reg[0]_0\,
      \adc10_ds_enable_0_reg[0]\ => \adc10_ds_enable_0_reg[0]_0\,
      \adc10_ds_inc_0_reg[0]\ => \adc10_ds_inc_0_reg[0]_0\,
      \adc10_ds_type_0_reg[0]\ => \adc10_ds_type_0_reg[0]_0\,
      \adc11_ds_control_0_reg[0]\ => \adc11_ds_control_0_reg[0]_0\,
      \adc11_ds_enable_0_reg[0]\ => \adc11_ds_enable_0_reg[0]_0\,
      \adc11_ds_inc_0_reg[0]\ => \adc11_ds_inc_0_reg[0]_0\,
      \adc11_ds_type_0_reg[0]\ => \adc11_ds_type_0_reg[0]_0\,
      \adc12_ds_control_0_reg[0]\ => \adc12_ds_control_0_reg[0]_0\,
      \adc12_ds_enable_0_reg[0]\ => \adc12_ds_enable_0_reg[0]_0\,
      \adc12_ds_inc_0_reg[0]\ => \adc12_ds_inc_0_reg[0]_0\,
      \adc12_ds_type_0_reg[0]\ => \adc12_ds_type_0_reg[0]_0\,
      \adc13_ds_control_0_reg[0]\ => \adc13_ds_control_0_reg[0]_1\,
      \adc13_ds_enable_0_reg[0]\ => \adc13_ds_enable_0_reg[0]_1\,
      \adc13_ds_inc_0_reg[0]\ => \adc13_ds_inc_0_reg[0]_1\,
      \adc13_ds_type_0_reg[0]\ => \adc13_ds_type_0_reg[0]_1\,
      adc1axi_map_wready => adc1axi_map_wready,
      adc1slv_rden => adc1slv_rden,
      adc_ds_axi_map_wready => adc_ds_axi_map_wready,
      clk2_valid_pulse_reg_0(0) => clk2clk_handshake_pulse_gen_i_n_2,
      clk2_valid_pulse_reg_1(0) => clk2clk_handshake_pulse_gen_i_n_3,
      clk2_valid_pulse_reg_10(0) => clk2clk_handshake_pulse_gen_i_n_13,
      clk2_valid_pulse_reg_11(0) => clk2clk_handshake_pulse_gen_i_n_14,
      clk2_valid_pulse_reg_12(0) => clk2clk_handshake_pulse_gen_i_n_15,
      clk2_valid_pulse_reg_13(0) => clk2clk_handshake_pulse_gen_i_n_16,
      clk2_valid_pulse_reg_14(0) => clk2clk_handshake_pulse_gen_i_n_17,
      clk2_valid_pulse_reg_2(0) => clk2clk_handshake_pulse_gen_i_n_5,
      clk2_valid_pulse_reg_3(0) => clk2clk_handshake_pulse_gen_i_n_6,
      clk2_valid_pulse_reg_4(0) => clk2clk_handshake_pulse_gen_i_n_7,
      clk2_valid_pulse_reg_5(0) => clk2clk_handshake_pulse_gen_i_n_8,
      clk2_valid_pulse_reg_6(0) => clk2clk_handshake_pulse_gen_i_n_9,
      clk2_valid_pulse_reg_7(0) => clk2clk_handshake_pulse_gen_i_n_10,
      clk2_valid_pulse_reg_8(0) => clk2clk_handshake_pulse_gen_i_n_11,
      clk2_valid_pulse_reg_9(0) => clk2clk_handshake_pulse_gen_i_n_12,
      p_0_in => p_0_in,
      s_axi_aclk => s_axi_aclk,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => \^slv_rden_r\,
      slv_rden_r_1 => slv_rden_r_1,
      slv_rden_r_reg => slv_rden_r_reg_0,
      slv_wren_done_pulse => slv_wren_done_pulse,
      slv_wren_done_pulse_0 => slv_wren_done_pulse_0,
      src_in => slv_access_valid_hold,
      \syncstages_ff_reg[4]\ => clk2clk_handshake_pulse_gen_i_n_18
    );
slv_access_valid_hold_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk2clk_handshake_pulse_gen_i_n_18,
      Q => slv_access_valid_hold,
      R => p_0_in
    );
\slv_rdata[0]_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_type_0(0),
      I1 => adc11_ds_type_0(0),
      I2 => Q(4),
      I3 => adc12_ds_type_0(0),
      I4 => Q(5),
      I5 => adc10_ds_type_0(0),
      O => \adc13_ds_type_0_reg[0]_0\
    );
\slv_rdata[0]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_enable_0(0),
      I1 => adc11_ds_enable_0(0),
      I2 => Q(4),
      I3 => adc12_ds_enable_0(0),
      I4 => Q(5),
      I5 => adc10_ds_enable_0(0),
      O => \adc13_ds_enable_0_reg[0]_0\
    );
\slv_rdata[0]_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(0),
      I1 => adc11_ds_inc_0(0),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(0),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(0),
      O => \adc13_ds_inc_0_reg[0]_0\
    );
\slv_rdata[0]_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_control_0(0),
      I1 => adc11_ds_control_0(0),
      I2 => Q(4),
      I3 => adc12_ds_control_0(0),
      I4 => Q(5),
      I5 => adc10_ds_control_0(0),
      O => \adc13_ds_control_0_reg[0]_0\
    );
\slv_rdata[10]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(10),
      I1 => adc11_ds_inc_0(10),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(10),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(10),
      O => \slv_rdata[10]_i_1__0_n_0\
    );
\slv_rdata[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFDFFFF00000000"
    )
        port map (
      I0 => \slv_rdata_reg[11]_1\,
      I1 => Q(3),
      I2 => Q(2),
      I3 => Q(1),
      I4 => Q(0),
      I5 => s_axi_aresetn,
      O => \^slv_addr_reg[6]\
    );
\slv_rdata[11]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(11),
      I1 => adc11_ds_inc_0(11),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(11),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(11),
      O => \slv_rdata[11]_i_2_n_0\
    );
\slv_rdata[1]_i_2__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_type_0(1),
      I1 => adc11_ds_type_0(1),
      I2 => Q(4),
      I3 => adc12_ds_type_0(1),
      I4 => Q(5),
      I5 => adc10_ds_type_0(1),
      O => \adc13_ds_type_0_reg[1]_0\
    );
\slv_rdata[1]_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_enable_0(1),
      I1 => adc11_ds_enable_0(1),
      I2 => Q(4),
      I3 => adc12_ds_enable_0(1),
      I4 => Q(5),
      I5 => adc10_ds_enable_0(1),
      O => \adc13_ds_enable_0_reg[1]_0\
    );
\slv_rdata[1]_i_6__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(1),
      I1 => adc11_ds_inc_0(1),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(1),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(1),
      O => \adc13_ds_inc_0_reg[1]_0\
    );
\slv_rdata[1]_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_control_0(1),
      I1 => adc11_ds_control_0(1),
      I2 => Q(4),
      I3 => adc12_ds_control_0(1),
      I4 => Q(5),
      I5 => adc10_ds_control_0(1),
      O => \adc13_ds_control_0_reg[1]_0\
    );
\slv_rdata[2]_i_3__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_type_0(2),
      I1 => adc11_ds_type_0(2),
      I2 => Q(4),
      I3 => adc12_ds_type_0(2),
      I4 => Q(5),
      I5 => adc10_ds_type_0(2),
      O => \adc13_ds_type_0_reg[2]_0\
    );
\slv_rdata[2]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(2),
      I1 => adc11_ds_inc_0(2),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(2),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(2),
      O => \adc13_ds_inc_0_reg[2]_0\
    );
\slv_rdata[3]_i_7__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(3),
      I1 => adc11_ds_inc_0(3),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(3),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(3),
      O => \adc13_ds_inc_0_reg[3]_0\
    );
\slv_rdata[4]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(4),
      I1 => adc11_ds_inc_0(4),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(4),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(4),
      O => \adc13_ds_inc_0_reg[4]_0\
    );
\slv_rdata[5]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(5),
      I1 => adc11_ds_inc_0(5),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(5),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(5),
      O => \adc13_ds_inc_0_reg[5]_0\
    );
\slv_rdata[6]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(6),
      I1 => adc11_ds_inc_0(6),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(6),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(6),
      O => \adc13_ds_inc_0_reg[6]_0\
    );
\slv_rdata[7]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(7),
      I1 => adc11_ds_inc_0(7),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(7),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(7),
      O => \adc13_ds_inc_0_reg[7]_0\
    );
\slv_rdata[8]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(8),
      I1 => adc11_ds_inc_0(8),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(8),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(8),
      O => \adc13_ds_inc_0_reg[8]_0\
    );
\slv_rdata[9]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc13_ds_inc_0(9),
      I1 => adc11_ds_inc_0(9),
      I2 => Q(4),
      I3 => adc12_ds_inc_0(9),
      I4 => Q(5),
      I5 => adc10_ds_inc_0(9),
      O => \slv_rdata[9]_i_1__0_n_0\
    );
\slv_rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(0),
      Q => \slv_rdata_reg[8]_0\(0),
      R => '0'
    );
\slv_rdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[10]_i_1__0_n_0\,
      Q => \slv_rdata_reg[10]_0\,
      R => \^slv_addr_reg[6]\
    );
\slv_rdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[11]_i_2_n_0\,
      Q => \slv_rdata_reg[11]_0\,
      R => \^slv_addr_reg[6]\
    );
\slv_rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(1),
      Q => \slv_rdata_reg[8]_0\(1),
      R => '0'
    );
\slv_rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(2),
      Q => \slv_rdata_reg[8]_0\(2),
      R => '0'
    );
\slv_rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(3),
      Q => \slv_rdata_reg[8]_0\(3),
      R => '0'
    );
\slv_rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(4),
      Q => \slv_rdata_reg[8]_0\(4),
      R => '0'
    );
\slv_rdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(5),
      Q => \slv_rdata_reg[8]_0\(5),
      R => '0'
    );
\slv_rdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(6),
      Q => \slv_rdata_reg[8]_0\(6),
      R => '0'
    );
\slv_rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(7),
      Q => \slv_rdata_reg[8]_0\(7),
      R => '0'
    );
\slv_rdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(8),
      Q => \slv_rdata_reg[8]_0\(8),
      R => '0'
    );
\slv_rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[9]_i_1__0_n_0\,
      Q => \slv_rdata_reg[9]_0\,
      R => \^slv_addr_reg[6]\
    );
slv_rden_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => adc1slv_rden,
      Q => \^slv_rden_r\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(0),
      Q => \slv_wdata_r_internal_reg_n_0_[0]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(10),
      Q => \slv_wdata_r_internal_reg_n_0_[10]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(11),
      Q => \slv_wdata_r_internal_reg_n_0_[11]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(1),
      Q => \slv_wdata_r_internal_reg_n_0_[1]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(2),
      Q => \slv_wdata_r_internal_reg_n_0_[2]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(3),
      Q => \slv_wdata_r_internal_reg_n_0_[3]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(4),
      Q => \slv_wdata_r_internal_reg_n_0_[4]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(5),
      Q => \slv_wdata_r_internal_reg_n_0_[5]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(6),
      Q => \slv_wdata_r_internal_reg_n_0_[6]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(7),
      Q => \slv_wdata_r_internal_reg_n_0_[7]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(8),
      Q => \slv_wdata_r_internal_reg_n_0_[8]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(9),
      Q => \slv_wdata_r_internal_reg_n_0_[9]\,
      R => p_0_in
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc2_rfadc_exdes_ctrl_axi is
  port (
    slv_wren_done_pulse : out STD_LOGIC;
    slv_rden_r : out STD_LOGIC;
    slv_rden_r_reg_0 : out STD_LOGIC;
    \slv_addr_reg[2]\ : out STD_LOGIC;
    \adc23_ds_inc_0_reg[8]_0\ : out STD_LOGIC;
    \adc23_ds_inc_0_reg[7]_0\ : out STD_LOGIC;
    \adc23_ds_inc_0_reg[6]_0\ : out STD_LOGIC;
    \adc23_ds_inc_0_reg[5]_0\ : out STD_LOGIC;
    \adc23_ds_inc_0_reg[4]_0\ : out STD_LOGIC;
    \adc23_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc21_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc22_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc20_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc23_ds_inc_0_reg[2]_0\ : out STD_LOGIC;
    \adc23_ds_type_0_reg[2]_0\ : out STD_LOGIC;
    \adc23_ds_enable_0_reg[1]_0\ : out STD_LOGIC;
    \adc23_ds_type_0_reg[1]_0\ : out STD_LOGIC;
    \adc23_ds_control_0_reg[1]_0\ : out STD_LOGIC;
    \adc23_ds_inc_0_reg[1]_0\ : out STD_LOGIC;
    \adc23_ds_enable_0_reg[0]_0\ : out STD_LOGIC;
    \adc23_ds_type_0_reg[0]_0\ : out STD_LOGIC;
    \adc23_ds_inc_0_reg[0]_0\ : out STD_LOGIC;
    \adc23_ds_control_0_reg[0]_0\ : out STD_LOGIC;
    \slv_rdata_reg[8]_0\ : out STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_rdata_reg[11]_0\ : out STD_LOGIC;
    \slv_rdata_reg[10]_0\ : out STD_LOGIC;
    \slv_rdata_reg[9]_0\ : out STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    p_0_in : in STD_LOGIC;
    adc2slv_rden : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 0 to 0 );
    slv_rden_r_0 : in STD_LOGIC;
    slv_wren_done_pulse_1 : in STD_LOGIC;
    \adc20_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc23_ds_type_0_reg[0]_1\ : in STD_LOGIC;
    \adc23_ds_enable_0_reg[0]_1\ : in STD_LOGIC;
    \adc21_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc21_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc21_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc20_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc20_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc20_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc23_ds_inc_0_reg[0]_1\ : in STD_LOGIC;
    \adc23_ds_control_0_reg[0]_1\ : in STD_LOGIC;
    \adc22_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc22_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc22_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc22_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc21_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \slv_rdata_reg[11]_1\ : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    adc2axi_map_wready : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wdata : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_aresetn : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_rdata_reg[11]_2\ : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc2_rfadc_exdes_ctrl_axi;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc2_rfadc_exdes_ctrl_axi is
  signal adc20_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc20_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc20_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc20_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc21_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc21_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc21_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc21_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc22_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc22_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc22_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc22_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc23_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc23_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc23_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc23_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal clk2clk_handshake_pulse_gen_i_n_10 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_11 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_12 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_13 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_14 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_15 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_16 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_17 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_18 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_2 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_3 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_4 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_5 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_6 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_7 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_8 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_9 : STD_LOGIC;
  signal slv_access_valid_hold : STD_LOGIC;
  signal \slv_rdata[10]_i_1__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_1__0_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_3__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_4__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_5__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[9]_i_1__1_n_0\ : STD_LOGIC;
  signal \^slv_rden_r\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[0]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[10]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[11]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[1]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[2]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[3]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[4]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[5]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[6]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[7]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[8]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[9]\ : STD_LOGIC;
begin
  slv_rden_r <= \^slv_rden_r\;
\adc20_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc20_ds_control_0(0),
      R => p_0_in
    );
\adc20_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc20_ds_control_0(1),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc20_ds_enable_0(0),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc20_ds_enable_0(1),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc20_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc20_ds_enable_0(3),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc20_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc20_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc20_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc20_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc20_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc20_ds_inc_0(0),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc20_ds_inc_0(10),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc20_ds_inc_0(11),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc20_ds_inc_0(1),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc20_ds_inc_0(2),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc20_ds_inc_0(3),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc20_ds_inc_0(4),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc20_ds_inc_0(5),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc20_ds_inc_0(6),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc20_ds_inc_0(7),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc20_ds_inc_0(8),
      R => p_0_in
    );
\adc20_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc20_ds_inc_0(9),
      R => p_0_in
    );
\adc20_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc20_ds_type_0(0),
      R => p_0_in
    );
\adc20_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc20_ds_type_0(1),
      R => p_0_in
    );
\adc20_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc20_ds_type_0(2),
      R => p_0_in
    );
\adc20_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc20_ds_type_0(3),
      R => p_0_in
    );
\adc21_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_5,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc21_ds_control_0(0),
      R => p_0_in
    );
\adc21_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_5,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc21_ds_control_0(1),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc21_ds_enable_0(0),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc21_ds_enable_0(1),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc21_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc21_ds_enable_0(3),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc21_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc21_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc21_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc21_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc21_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc21_ds_inc_0(0),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc21_ds_inc_0(10),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc21_ds_inc_0(11),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc21_ds_inc_0(1),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc21_ds_inc_0(2),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc21_ds_inc_0(3),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc21_ds_inc_0(4),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc21_ds_inc_0(5),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc21_ds_inc_0(6),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc21_ds_inc_0(7),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc21_ds_inc_0(8),
      R => p_0_in
    );
\adc21_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc21_ds_inc_0(9),
      R => p_0_in
    );
\adc21_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc21_ds_type_0(0),
      R => p_0_in
    );
\adc21_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc21_ds_type_0(1),
      R => p_0_in
    );
\adc21_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc21_ds_type_0(2),
      R => p_0_in
    );
\adc21_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc21_ds_type_0(3),
      R => p_0_in
    );
\adc22_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc22_ds_control_0(0),
      R => p_0_in
    );
\adc22_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc22_ds_control_0(1),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc22_ds_enable_0(0),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc22_ds_enable_0(1),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc22_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc22_ds_enable_0(3),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc22_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc22_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc22_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc22_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc22_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc22_ds_inc_0(0),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc22_ds_inc_0(10),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc22_ds_inc_0(11),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc22_ds_inc_0(1),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc22_ds_inc_0(2),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc22_ds_inc_0(3),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc22_ds_inc_0(4),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc22_ds_inc_0(5),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc22_ds_inc_0(6),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc22_ds_inc_0(7),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc22_ds_inc_0(8),
      R => p_0_in
    );
\adc22_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc22_ds_inc_0(9),
      R => p_0_in
    );
\adc22_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc22_ds_type_0(0),
      R => p_0_in
    );
\adc22_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc22_ds_type_0(1),
      R => p_0_in
    );
\adc22_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc22_ds_type_0(2),
      R => p_0_in
    );
\adc22_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc22_ds_type_0(3),
      R => p_0_in
    );
\adc23_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc23_ds_control_0(0),
      R => p_0_in
    );
\adc23_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc23_ds_control_0(1),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc23_ds_enable_0(0),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc23_ds_enable_0(1),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc23_ds_enable_0_reg[7]_0\(0),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc23_ds_enable_0(3),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc23_ds_enable_0_reg[7]_0\(1),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc23_ds_enable_0_reg[7]_0\(2),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc23_ds_enable_0_reg[7]_0\(3),
      R => p_0_in
    );
\adc23_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc23_ds_enable_0_reg[7]_0\(4),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc23_ds_inc_0(0),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc23_ds_inc_0(10),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc23_ds_inc_0(11),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc23_ds_inc_0(1),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc23_ds_inc_0(2),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc23_ds_inc_0(3),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc23_ds_inc_0(4),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc23_ds_inc_0(5),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc23_ds_inc_0(6),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc23_ds_inc_0(7),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc23_ds_inc_0(8),
      R => p_0_in
    );
\adc23_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc23_ds_inc_0(9),
      R => p_0_in
    );
\adc23_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc23_ds_type_0(0),
      R => p_0_in
    );
\adc23_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc23_ds_type_0(1),
      R => p_0_in
    );
\adc23_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc23_ds_type_0(2),
      R => p_0_in
    );
\adc23_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc23_ds_type_0(3),
      R => p_0_in
    );
clk2clk_handshake_pulse_gen_i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen__xdcDup__3\
     port map (
      E(0) => clk2clk_handshake_pulse_gen_i_n_2,
      Q(0) => Q(0),
      \adc20_ds_control_0_reg[0]\ => \adc20_ds_control_0_reg[0]_0\,
      \adc20_ds_enable_0_reg[0]\ => \adc20_ds_enable_0_reg[0]_0\,
      \adc20_ds_inc_0_reg[0]\ => \adc20_ds_inc_0_reg[0]_0\,
      \adc20_ds_type_0_reg[0]\ => \adc20_ds_type_0_reg[0]_0\,
      \adc21_ds_control_0_reg[0]\ => \adc21_ds_control_0_reg[0]_0\,
      \adc21_ds_enable_0_reg[0]\ => \adc21_ds_enable_0_reg[0]_0\,
      \adc21_ds_inc_0_reg[0]\ => \adc21_ds_inc_0_reg[0]_0\,
      \adc21_ds_type_0_reg[0]\ => \adc21_ds_type_0_reg[0]_0\,
      \adc22_ds_control_0_reg[0]\ => \adc22_ds_control_0_reg[0]_0\,
      \adc22_ds_enable_0_reg[0]\ => \adc22_ds_enable_0_reg[0]_0\,
      \adc22_ds_inc_0_reg[0]\ => \adc22_ds_inc_0_reg[0]_0\,
      \adc22_ds_type_0_reg[0]\ => \adc22_ds_type_0_reg[0]_0\,
      \adc23_ds_control_0_reg[0]\ => \adc23_ds_control_0_reg[0]_1\,
      \adc23_ds_enable_0_reg[0]\ => \adc23_ds_enable_0_reg[0]_1\,
      \adc23_ds_inc_0_reg[0]\ => \adc23_ds_inc_0_reg[0]_1\,
      \adc23_ds_type_0_reg[0]\ => \adc23_ds_type_0_reg[0]_1\,
      adc2axi_map_wready => adc2axi_map_wready,
      adc2slv_rden => adc2slv_rden,
      clk2_valid_pulse_reg_0(0) => clk2clk_handshake_pulse_gen_i_n_3,
      clk2_valid_pulse_reg_1(0) => clk2clk_handshake_pulse_gen_i_n_4,
      clk2_valid_pulse_reg_10(0) => clk2clk_handshake_pulse_gen_i_n_13,
      clk2_valid_pulse_reg_11(0) => clk2clk_handshake_pulse_gen_i_n_14,
      clk2_valid_pulse_reg_12(0) => clk2clk_handshake_pulse_gen_i_n_15,
      clk2_valid_pulse_reg_13(0) => clk2clk_handshake_pulse_gen_i_n_16,
      clk2_valid_pulse_reg_14(0) => clk2clk_handshake_pulse_gen_i_n_17,
      clk2_valid_pulse_reg_2(0) => clk2clk_handshake_pulse_gen_i_n_5,
      clk2_valid_pulse_reg_3(0) => clk2clk_handshake_pulse_gen_i_n_6,
      clk2_valid_pulse_reg_4(0) => clk2clk_handshake_pulse_gen_i_n_7,
      clk2_valid_pulse_reg_5(0) => clk2clk_handshake_pulse_gen_i_n_8,
      clk2_valid_pulse_reg_6(0) => clk2clk_handshake_pulse_gen_i_n_9,
      clk2_valid_pulse_reg_7(0) => clk2clk_handshake_pulse_gen_i_n_10,
      clk2_valid_pulse_reg_8(0) => clk2clk_handshake_pulse_gen_i_n_11,
      clk2_valid_pulse_reg_9(0) => clk2clk_handshake_pulse_gen_i_n_12,
      p_0_in => p_0_in,
      s_axi_aclk => s_axi_aclk,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => \^slv_rden_r\,
      slv_rden_r_0 => slv_rden_r_0,
      slv_rden_r_reg => slv_rden_r_reg_0,
      slv_wren_done_pulse => slv_wren_done_pulse,
      slv_wren_done_pulse_1 => slv_wren_done_pulse_1,
      src_in => slv_access_valid_hold,
      \syncstages_ff_reg[4]\ => clk2clk_handshake_pulse_gen_i_n_18
    );
slv_access_valid_hold_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk2clk_handshake_pulse_gen_i_n_18,
      Q => slv_access_valid_hold,
      R => p_0_in
    );
\slv_rdata[0]_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_type_0(0),
      I1 => adc21_ds_type_0(0),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_type_0(0),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_type_0(0),
      O => \adc23_ds_type_0_reg[0]_0\
    );
\slv_rdata[0]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_enable_0(0),
      I1 => adc21_ds_enable_0(0),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_enable_0(0),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_enable_0(0),
      O => \adc23_ds_enable_0_reg[0]_0\
    );
\slv_rdata[0]_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(0),
      I1 => adc21_ds_inc_0(0),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(0),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(0),
      O => \adc23_ds_inc_0_reg[0]_0\
    );
\slv_rdata[0]_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_control_0(0),
      I1 => adc21_ds_control_0(0),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_control_0(0),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_control_0(0),
      O => \adc23_ds_control_0_reg[0]_0\
    );
\slv_rdata[10]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(10),
      I1 => adc21_ds_inc_0(10),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(10),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(10),
      O => \slv_rdata[10]_i_1__1_n_0\
    );
\slv_rdata[11]_i_1__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(11),
      I1 => adc21_ds_inc_0(11),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(11),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(11),
      O => \slv_rdata[11]_i_1__0_n_0\
    );
\slv_rdata[1]_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_type_0(1),
      I1 => adc21_ds_type_0(1),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_type_0(1),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_type_0(1),
      O => \adc23_ds_type_0_reg[1]_0\
    );
\slv_rdata[1]_i_4__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_enable_0(1),
      I1 => adc21_ds_enable_0(1),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_enable_0(1),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_enable_0(1),
      O => \adc23_ds_enable_0_reg[1]_0\
    );
\slv_rdata[1]_i_5__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_control_0(1),
      I1 => adc21_ds_control_0(1),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_control_0(1),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_control_0(1),
      O => \adc23_ds_control_0_reg[1]_0\
    );
\slv_rdata[1]_i_6__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(1),
      I1 => adc21_ds_inc_0(1),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(1),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(1),
      O => \adc23_ds_inc_0_reg[1]_0\
    );
\slv_rdata[2]_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_type_0(2),
      I1 => adc21_ds_type_0(2),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_type_0(2),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_type_0(2),
      O => \adc23_ds_type_0_reg[2]_0\
    );
\slv_rdata[2]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(2),
      I1 => adc21_ds_inc_0(2),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(2),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(2),
      O => \adc23_ds_inc_0_reg[2]_0\
    );
\slv_rdata[3]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFCF44FFFFCF77"
    )
        port map (
      I0 => \slv_rdata[3]_i_3__1_n_0\,
      I1 => \slv_rdata_reg[11]_1\(0),
      I2 => \slv_rdata[3]_i_4__1_n_0\,
      I3 => \slv_rdata_reg[11]_1\(1),
      I4 => \slv_rdata_reg[11]_1\(2),
      I5 => \slv_rdata[3]_i_5__1_n_0\,
      O => \slv_addr_reg[2]\
    );
\slv_rdata[3]_i_3__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(3),
      I1 => adc21_ds_inc_0(3),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(3),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(3),
      O => \slv_rdata[3]_i_3__1_n_0\
    );
\slv_rdata[3]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_type_0(3),
      I1 => adc21_ds_type_0(3),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_type_0(3),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_type_0(3),
      O => \slv_rdata[3]_i_4__1_n_0\
    );
\slv_rdata[3]_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_enable_0(3),
      I1 => adc21_ds_enable_0(3),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_enable_0(3),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_enable_0(3),
      O => \slv_rdata[3]_i_5__1_n_0\
    );
\slv_rdata[4]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(4),
      I1 => adc21_ds_inc_0(4),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(4),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(4),
      O => \adc23_ds_inc_0_reg[4]_0\
    );
\slv_rdata[5]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(5),
      I1 => adc21_ds_inc_0(5),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(5),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(5),
      O => \adc23_ds_inc_0_reg[5]_0\
    );
\slv_rdata[6]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(6),
      I1 => adc21_ds_inc_0(6),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(6),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(6),
      O => \adc23_ds_inc_0_reg[6]_0\
    );
\slv_rdata[7]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(7),
      I1 => adc21_ds_inc_0(7),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(7),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(7),
      O => \adc23_ds_inc_0_reg[7]_0\
    );
\slv_rdata[8]_i_2__0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(8),
      I1 => adc21_ds_inc_0(8),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(8),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(8),
      O => \adc23_ds_inc_0_reg[8]_0\
    );
\slv_rdata[9]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc23_ds_inc_0(9),
      I1 => adc21_ds_inc_0(9),
      I2 => \slv_rdata_reg[11]_1\(3),
      I3 => adc22_ds_inc_0(9),
      I4 => \slv_rdata_reg[11]_1\(4),
      I5 => adc20_ds_inc_0(9),
      O => \slv_rdata[9]_i_1__1_n_0\
    );
\slv_rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(0),
      Q => \slv_rdata_reg[8]_0\(0),
      R => '0'
    );
\slv_rdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[10]_i_1__1_n_0\,
      Q => \slv_rdata_reg[10]_0\,
      R => \slv_rdata_reg[11]_2\
    );
\slv_rdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[11]_i_1__0_n_0\,
      Q => \slv_rdata_reg[11]_0\,
      R => \slv_rdata_reg[11]_2\
    );
\slv_rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(1),
      Q => \slv_rdata_reg[8]_0\(1),
      R => '0'
    );
\slv_rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(2),
      Q => \slv_rdata_reg[8]_0\(2),
      R => '0'
    );
\slv_rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(3),
      Q => \slv_rdata_reg[8]_0\(3),
      R => '0'
    );
\slv_rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(4),
      Q => \slv_rdata_reg[8]_0\(4),
      R => '0'
    );
\slv_rdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(5),
      Q => \slv_rdata_reg[8]_0\(5),
      R => '0'
    );
\slv_rdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(6),
      Q => \slv_rdata_reg[8]_0\(6),
      R => '0'
    );
\slv_rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(7),
      Q => \slv_rdata_reg[8]_0\(7),
      R => '0'
    );
\slv_rdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(8),
      Q => \slv_rdata_reg[8]_0\(8),
      R => '0'
    );
\slv_rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[9]_i_1__1_n_0\,
      Q => \slv_rdata_reg[9]_0\,
      R => \slv_rdata_reg[11]_2\
    );
slv_rden_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => adc2slv_rden,
      Q => \^slv_rden_r\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(0),
      Q => \slv_wdata_r_internal_reg_n_0_[0]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(10),
      Q => \slv_wdata_r_internal_reg_n_0_[10]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(11),
      Q => \slv_wdata_r_internal_reg_n_0_[11]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(1),
      Q => \slv_wdata_r_internal_reg_n_0_[1]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(2),
      Q => \slv_wdata_r_internal_reg_n_0_[2]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(3),
      Q => \slv_wdata_r_internal_reg_n_0_[3]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(4),
      Q => \slv_wdata_r_internal_reg_n_0_[4]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(5),
      Q => \slv_wdata_r_internal_reg_n_0_[5]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(6),
      Q => \slv_wdata_r_internal_reg_n_0_[6]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(7),
      Q => \slv_wdata_r_internal_reg_n_0_[7]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(8),
      Q => \slv_wdata_r_internal_reg_n_0_[8]\,
      R => p_0_in
    );
\slv_wdata_r_internal_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(9),
      Q => \slv_wdata_r_internal_reg_n_0_[9]\,
      R => p_0_in
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc3_rfadc_exdes_ctrl_axi is
  port (
    p_0_in : out STD_LOGIC;
    slv_wren_done_pulse : out STD_LOGIC;
    slv_rden_r : out STD_LOGIC;
    \slv_rdata_reg[0]_0\ : out STD_LOGIC;
    \slv_addr_reg[3]\ : out STD_LOGIC;
    clk1_ready_pulse_reg : out STD_LOGIC;
    \adc33_ds_inc_0_reg[8]_0\ : out STD_LOGIC;
    \adc33_ds_inc_0_reg[7]_0\ : out STD_LOGIC;
    \adc33_ds_inc_0_reg[6]_0\ : out STD_LOGIC;
    \adc33_ds_inc_0_reg[5]_0\ : out STD_LOGIC;
    \adc33_ds_inc_0_reg[4]_0\ : out STD_LOGIC;
    \adc33_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc31_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc32_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc30_ds_enable_0_reg[7]_0\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc33_ds_inc_0_reg[2]_0\ : out STD_LOGIC;
    \adc33_ds_type_0_reg[2]_0\ : out STD_LOGIC;
    \adc33_ds_enable_0_reg[1]_0\ : out STD_LOGIC;
    \adc33_ds_type_0_reg[1]_0\ : out STD_LOGIC;
    \adc33_ds_inc_0_reg[1]_0\ : out STD_LOGIC;
    \adc33_ds_control_0_reg[1]_0\ : out STD_LOGIC;
    \adc33_ds_enable_0_reg[0]_0\ : out STD_LOGIC;
    \adc33_ds_type_0_reg[0]_0\ : out STD_LOGIC;
    \adc33_ds_control_0_reg[0]_0\ : out STD_LOGIC;
    \adc33_ds_inc_0_reg[0]_0\ : out STD_LOGIC;
    \slv_rdata_reg[8]_0\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    \slv_rdata_reg[11]_0\ : out STD_LOGIC;
    \slv_rdata_reg[10]_0\ : out STD_LOGIC;
    \slv_rdata_reg[9]_0\ : out STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    adc3slv_rden : in STD_LOGIC;
    \axi_rdata_reg[0]\ : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \adc30_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc33_ds_type_0_reg[0]_1\ : in STD_LOGIC;
    \adc33_ds_enable_0_reg[0]_1\ : in STD_LOGIC;
    \adc31_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc31_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc31_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc30_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc30_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc30_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc33_ds_inc_0_reg[0]_1\ : in STD_LOGIC;
    \adc33_ds_control_0_reg[0]_1\ : in STD_LOGIC;
    \adc32_ds_type_0_reg[0]_0\ : in STD_LOGIC;
    \adc32_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    \adc32_ds_enable_0_reg[0]_0\ : in STD_LOGIC;
    \adc32_ds_control_0_reg[0]_0\ : in STD_LOGIC;
    \adc31_ds_inc_0_reg[0]_0\ : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    slv_rden_r_0 : in STD_LOGIC;
    slv_wren_done_pulse_1 : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    adc3axi_map_wready : in STD_LOGIC;
    E : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wdata : in STD_LOGIC_VECTOR ( 11 downto 0 );
    D : in STD_LOGIC_VECTOR ( 8 downto 0 );
    \slv_rdata_reg[11]_1\ : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc3_rfadc_exdes_ctrl_axi;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc3_rfadc_exdes_ctrl_axi is
  signal adc30_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc30_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc30_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc30_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc31_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc31_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc31_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc31_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc32_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc32_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc32_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc32_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc33_ds_control_0 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal adc33_ds_enable_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc33_ds_inc_0 : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal adc33_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal clk2clk_handshake_pulse_gen_i_n_10 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_11 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_12 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_13 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_14 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_15 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_16 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_17 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_19 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_2 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_3 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_4 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_5 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_6 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_7 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_8 : STD_LOGIC;
  signal clk2clk_handshake_pulse_gen_i_n_9 : STD_LOGIC;
  signal \^p_0_in\ : STD_LOGIC;
  signal slv_access_valid_hold : STD_LOGIC;
  signal \slv_rdata[10]_i_1__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[11]_i_1__1_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_3__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_4__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[3]_i_5__2_n_0\ : STD_LOGIC;
  signal \slv_rdata[9]_i_1__2_n_0\ : STD_LOGIC;
  signal \slv_rdata_reg_n_0_[0]\ : STD_LOGIC;
  signal \^slv_rden_r\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[0]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[10]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[11]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[1]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[2]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[3]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[4]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[5]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[6]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[7]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[8]\ : STD_LOGIC;
  signal \slv_wdata_r_internal_reg_n_0_[9]\ : STD_LOGIC;
begin
  p_0_in <= \^p_0_in\;
  slv_rden_r <= \^slv_rden_r\;
\adc30_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc30_ds_control_0(0),
      R => \^p_0_in\
    );
\adc30_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_9,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc30_ds_control_0(1),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc30_ds_enable_0(0),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc30_ds_enable_0(1),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc30_ds_enable_0_reg[7]_0\(0),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc30_ds_enable_0(3),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc30_ds_enable_0_reg[7]_0\(1),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc30_ds_enable_0_reg[7]_0\(2),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc30_ds_enable_0_reg[7]_0\(3),
      R => \^p_0_in\
    );
\adc30_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_2,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc30_ds_enable_0_reg[7]_0\(4),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc30_ds_inc_0(0),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc30_ds_inc_0(10),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc30_ds_inc_0(11),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc30_ds_inc_0(1),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc30_ds_inc_0(2),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc30_ds_inc_0(3),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc30_ds_inc_0(4),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc30_ds_inc_0(5),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc30_ds_inc_0(6),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc30_ds_inc_0(7),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc30_ds_inc_0(8),
      R => \^p_0_in\
    );
\adc30_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_10,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc30_ds_inc_0(9),
      R => \^p_0_in\
    );
\adc30_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc30_ds_type_0(0),
      R => \^p_0_in\
    );
\adc30_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc30_ds_type_0(1),
      R => \^p_0_in\
    );
\adc30_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc30_ds_type_0(2),
      R => \^p_0_in\
    );
\adc30_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_8,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc30_ds_type_0(3),
      R => \^p_0_in\
    );
\adc31_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_5,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc31_ds_control_0(0),
      R => \^p_0_in\
    );
\adc31_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_5,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc31_ds_control_0(1),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc31_ds_enable_0(0),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc31_ds_enable_0(1),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc31_ds_enable_0_reg[7]_0\(0),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc31_ds_enable_0(3),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc31_ds_enable_0_reg[7]_0\(1),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc31_ds_enable_0_reg[7]_0\(2),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc31_ds_enable_0_reg[7]_0\(3),
      R => \^p_0_in\
    );
\adc31_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_7,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc31_ds_enable_0_reg[7]_0\(4),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc31_ds_inc_0(0),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc31_ds_inc_0(10),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc31_ds_inc_0(11),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc31_ds_inc_0(1),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc31_ds_inc_0(2),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc31_ds_inc_0(3),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc31_ds_inc_0(4),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc31_ds_inc_0(5),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc31_ds_inc_0(6),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc31_ds_inc_0(7),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc31_ds_inc_0(8),
      R => \^p_0_in\
    );
\adc31_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_17,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc31_ds_inc_0(9),
      R => \^p_0_in\
    );
\adc31_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc31_ds_type_0(0),
      R => \^p_0_in\
    );
\adc31_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc31_ds_type_0(1),
      R => \^p_0_in\
    );
\adc31_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc31_ds_type_0(2),
      R => \^p_0_in\
    );
\adc31_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_6,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc31_ds_type_0(3),
      R => \^p_0_in\
    );
\adc32_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc32_ds_control_0(0),
      R => \^p_0_in\
    );
\adc32_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_16,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc32_ds_control_0(1),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc32_ds_enable_0(0),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc32_ds_enable_0(1),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc32_ds_enable_0_reg[7]_0\(0),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc32_ds_enable_0(3),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc32_ds_enable_0_reg[7]_0\(1),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc32_ds_enable_0_reg[7]_0\(2),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc32_ds_enable_0_reg[7]_0\(3),
      R => \^p_0_in\
    );
\adc32_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_15,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc32_ds_enable_0_reg[7]_0\(4),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc32_ds_inc_0(0),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc32_ds_inc_0(10),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc32_ds_inc_0(11),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc32_ds_inc_0(1),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc32_ds_inc_0(2),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc32_ds_inc_0(3),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc32_ds_inc_0(4),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc32_ds_inc_0(5),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc32_ds_inc_0(6),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc32_ds_inc_0(7),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc32_ds_inc_0(8),
      R => \^p_0_in\
    );
\adc32_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_14,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc32_ds_inc_0(9),
      R => \^p_0_in\
    );
\adc32_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc32_ds_type_0(0),
      R => \^p_0_in\
    );
\adc32_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc32_ds_type_0(1),
      R => \^p_0_in\
    );
\adc32_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc32_ds_type_0(2),
      R => \^p_0_in\
    );
\adc32_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_13,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc32_ds_type_0(3),
      R => \^p_0_in\
    );
\adc33_ds_control_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc33_ds_control_0(0),
      R => \^p_0_in\
    );
\adc33_ds_control_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_12,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc33_ds_control_0(1),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc33_ds_enable_0(0),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc33_ds_enable_0(1),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => \adc33_ds_enable_0_reg[7]_0\(0),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc33_ds_enable_0(3),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => \adc33_ds_enable_0_reg[7]_0\(1),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => \adc33_ds_enable_0_reg[7]_0\(2),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => \adc33_ds_enable_0_reg[7]_0\(3),
      R => \^p_0_in\
    );
\adc33_ds_enable_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_4,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => \adc33_ds_enable_0_reg[7]_0\(4),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc33_ds_inc_0(0),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[10]\,
      Q => adc33_ds_inc_0(10),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[11]\,
      Q => adc33_ds_inc_0(11),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc33_ds_inc_0(1),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc33_ds_inc_0(2),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc33_ds_inc_0(3),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[4]\,
      Q => adc33_ds_inc_0(4),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[5]\,
      Q => adc33_ds_inc_0(5),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[6]\,
      Q => adc33_ds_inc_0(6),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[7]\,
      Q => adc33_ds_inc_0(7),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[8]\,
      Q => adc33_ds_inc_0(8),
      R => \^p_0_in\
    );
\adc33_ds_inc_0_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_11,
      D => \slv_wdata_r_internal_reg_n_0_[9]\,
      Q => adc33_ds_inc_0(9),
      R => \^p_0_in\
    );
\adc33_ds_type_0_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[0]\,
      Q => adc33_ds_type_0(0),
      R => \^p_0_in\
    );
\adc33_ds_type_0_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[1]\,
      Q => adc33_ds_type_0(1),
      R => \^p_0_in\
    );
\adc33_ds_type_0_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[2]\,
      Q => adc33_ds_type_0(2),
      R => \^p_0_in\
    );
\adc33_ds_type_0_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => clk2clk_handshake_pulse_gen_i_n_3,
      D => \slv_wdata_r_internal_reg_n_0_[3]\,
      Q => adc33_ds_type_0(3),
      R => \^p_0_in\
    );
\axi_rdata[0]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \slv_rdata_reg_n_0_[0]\,
      I1 => \axi_rdata_reg[0]\,
      O => \slv_rdata_reg[0]_0\
    );
clk2clk_handshake_pulse_gen_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_hshk_pls_gen
     port map (
      E(0) => clk2clk_handshake_pulse_gen_i_n_2,
      SR(0) => \^p_0_in\,
      \adc30_ds_control_0_reg[0]\ => \adc30_ds_control_0_reg[0]_0\,
      \adc30_ds_enable_0_reg[0]\ => \adc30_ds_enable_0_reg[0]_0\,
      \adc30_ds_inc_0_reg[0]\ => \adc30_ds_inc_0_reg[0]_0\,
      \adc30_ds_type_0_reg[0]\ => \adc30_ds_type_0_reg[0]_0\,
      \adc31_ds_control_0_reg[0]\ => \adc31_ds_control_0_reg[0]_0\,
      \adc31_ds_enable_0_reg[0]\ => \adc31_ds_enable_0_reg[0]_0\,
      \adc31_ds_inc_0_reg[0]\ => \adc31_ds_inc_0_reg[0]_0\,
      \adc31_ds_type_0_reg[0]\ => \adc31_ds_type_0_reg[0]_0\,
      \adc32_ds_control_0_reg[0]\ => \adc32_ds_control_0_reg[0]_0\,
      \adc32_ds_enable_0_reg[0]\ => \adc32_ds_enable_0_reg[0]_0\,
      \adc32_ds_inc_0_reg[0]\ => \adc32_ds_inc_0_reg[0]_0\,
      \adc32_ds_type_0_reg[0]\ => \adc32_ds_type_0_reg[0]_0\,
      \adc33_ds_control_0_reg[0]\ => \adc33_ds_control_0_reg[0]_1\,
      \adc33_ds_enable_0_reg[0]\ => \adc33_ds_enable_0_reg[0]_1\,
      \adc33_ds_inc_0_reg[0]\ => \adc33_ds_inc_0_reg[0]_1\,
      \adc33_ds_type_0_reg[0]\ => \adc33_ds_type_0_reg[0]_1\,
      adc3axi_map_wready => adc3axi_map_wready,
      adc3slv_rden => adc3slv_rden,
      clk1_ready_pulse_reg_0 => clk1_ready_pulse_reg,
      clk2_valid_pulse_reg_0(0) => clk2clk_handshake_pulse_gen_i_n_3,
      clk2_valid_pulse_reg_1(0) => clk2clk_handshake_pulse_gen_i_n_4,
      clk2_valid_pulse_reg_10(0) => clk2clk_handshake_pulse_gen_i_n_13,
      clk2_valid_pulse_reg_11(0) => clk2clk_handshake_pulse_gen_i_n_14,
      clk2_valid_pulse_reg_12(0) => clk2clk_handshake_pulse_gen_i_n_15,
      clk2_valid_pulse_reg_13(0) => clk2clk_handshake_pulse_gen_i_n_16,
      clk2_valid_pulse_reg_14(0) => clk2clk_handshake_pulse_gen_i_n_17,
      clk2_valid_pulse_reg_2(0) => clk2clk_handshake_pulse_gen_i_n_5,
      clk2_valid_pulse_reg_3(0) => clk2clk_handshake_pulse_gen_i_n_6,
      clk2_valid_pulse_reg_4(0) => clk2clk_handshake_pulse_gen_i_n_7,
      clk2_valid_pulse_reg_5(0) => clk2clk_handshake_pulse_gen_i_n_8,
      clk2_valid_pulse_reg_6(0) => clk2clk_handshake_pulse_gen_i_n_9,
      clk2_valid_pulse_reg_7(0) => clk2clk_handshake_pulse_gen_i_n_10,
      clk2_valid_pulse_reg_8(0) => clk2clk_handshake_pulse_gen_i_n_11,
      clk2_valid_pulse_reg_9(0) => clk2clk_handshake_pulse_gen_i_n_12,
      s_axi_aclk => s_axi_aclk,
      s_axi_aresetn => s_axi_aresetn,
      s_axi_wvalid => s_axi_wvalid,
      slv_access_valid_hold_reg => \^slv_rden_r\,
      slv_rden_r_0 => slv_rden_r_0,
      slv_wren_done_pulse => slv_wren_done_pulse,
      slv_wren_done_pulse_1 => slv_wren_done_pulse_1,
      src_in => slv_access_valid_hold,
      \syncstages_ff_reg[4]\ => clk2clk_handshake_pulse_gen_i_n_19
    );
slv_access_valid_hold_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => clk2clk_handshake_pulse_gen_i_n_19,
      Q => slv_access_valid_hold,
      R => \^p_0_in\
    );
\slv_rdata[0]_i_3__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_type_0(0),
      I1 => adc31_ds_type_0(0),
      I2 => Q(3),
      I3 => adc32_ds_type_0(0),
      I4 => Q(4),
      I5 => adc30_ds_type_0(0),
      O => \adc33_ds_type_0_reg[0]_0\
    );
\slv_rdata[0]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_enable_0(0),
      I1 => adc31_ds_enable_0(0),
      I2 => Q(3),
      I3 => adc32_ds_enable_0(0),
      I4 => Q(4),
      I5 => adc30_ds_enable_0(0),
      O => \adc33_ds_enable_0_reg[0]_0\
    );
\slv_rdata[0]_i_5__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_control_0(0),
      I1 => adc31_ds_control_0(0),
      I2 => Q(3),
      I3 => adc32_ds_control_0(0),
      I4 => Q(4),
      I5 => adc30_ds_control_0(0),
      O => \adc33_ds_control_0_reg[0]_0\
    );
\slv_rdata[0]_i_6__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(0),
      I1 => adc31_ds_inc_0(0),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(0),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(0),
      O => \adc33_ds_inc_0_reg[0]_0\
    );
\slv_rdata[10]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(10),
      I1 => adc31_ds_inc_0(10),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(10),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(10),
      O => \slv_rdata[10]_i_1__2_n_0\
    );
\slv_rdata[11]_i_1__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(11),
      I1 => adc31_ds_inc_0(11),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(11),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(11),
      O => \slv_rdata[11]_i_1__1_n_0\
    );
\slv_rdata[1]_i_3__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_type_0(1),
      I1 => adc31_ds_type_0(1),
      I2 => Q(3),
      I3 => adc32_ds_type_0(1),
      I4 => Q(4),
      I5 => adc30_ds_type_0(1),
      O => \adc33_ds_type_0_reg[1]_0\
    );
\slv_rdata[1]_i_4__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_enable_0(1),
      I1 => adc31_ds_enable_0(1),
      I2 => Q(3),
      I3 => adc32_ds_enable_0(1),
      I4 => Q(4),
      I5 => adc30_ds_enable_0(1),
      O => \adc33_ds_enable_0_reg[1]_0\
    );
\slv_rdata[1]_i_5__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(1),
      I1 => adc31_ds_inc_0(1),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(1),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(1),
      O => \adc33_ds_inc_0_reg[1]_0\
    );
\slv_rdata[1]_i_6__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_control_0(1),
      I1 => adc31_ds_control_0(1),
      I2 => Q(3),
      I3 => adc32_ds_control_0(1),
      I4 => Q(4),
      I5 => adc30_ds_control_0(1),
      O => \adc33_ds_control_0_reg[1]_0\
    );
\slv_rdata[2]_i_3__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_type_0(2),
      I1 => adc31_ds_type_0(2),
      I2 => Q(3),
      I3 => adc32_ds_type_0(2),
      I4 => Q(4),
      I5 => adc30_ds_type_0(2),
      O => \adc33_ds_type_0_reg[2]_0\
    );
\slv_rdata[2]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(2),
      I1 => adc31_ds_inc_0(2),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(2),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(2),
      O => \adc33_ds_inc_0_reg[2]_0\
    );
\slv_rdata[3]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFF530FFFFF53F"
    )
        port map (
      I0 => \slv_rdata[3]_i_3__2_n_0\,
      I1 => \slv_rdata[3]_i_4__2_n_0\,
      I2 => Q(1),
      I3 => Q(0),
      I4 => Q(2),
      I5 => \slv_rdata[3]_i_5__2_n_0\,
      O => \slv_addr_reg[3]\
    );
\slv_rdata[3]_i_3__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(3),
      I1 => adc31_ds_inc_0(3),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(3),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(3),
      O => \slv_rdata[3]_i_3__2_n_0\
    );
\slv_rdata[3]_i_4__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_type_0(3),
      I1 => adc31_ds_type_0(3),
      I2 => Q(3),
      I3 => adc32_ds_type_0(3),
      I4 => Q(4),
      I5 => adc30_ds_type_0(3),
      O => \slv_rdata[3]_i_4__2_n_0\
    );
\slv_rdata[3]_i_5__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_enable_0(3),
      I1 => adc31_ds_enable_0(3),
      I2 => Q(3),
      I3 => adc32_ds_enable_0(3),
      I4 => Q(4),
      I5 => adc30_ds_enable_0(3),
      O => \slv_rdata[3]_i_5__2_n_0\
    );
\slv_rdata[4]_i_2__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(4),
      I1 => adc31_ds_inc_0(4),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(4),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(4),
      O => \adc33_ds_inc_0_reg[4]_0\
    );
\slv_rdata[5]_i_2__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(5),
      I1 => adc31_ds_inc_0(5),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(5),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(5),
      O => \adc33_ds_inc_0_reg[5]_0\
    );
\slv_rdata[6]_i_2__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(6),
      I1 => adc31_ds_inc_0(6),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(6),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(6),
      O => \adc33_ds_inc_0_reg[6]_0\
    );
\slv_rdata[7]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(7),
      I1 => adc31_ds_inc_0(7),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(7),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(7),
      O => \adc33_ds_inc_0_reg[7]_0\
    );
\slv_rdata[8]_i_2__1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(8),
      I1 => adc31_ds_inc_0(8),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(8),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(8),
      O => \adc33_ds_inc_0_reg[8]_0\
    );
\slv_rdata[9]_i_1__2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => adc33_ds_inc_0(9),
      I1 => adc31_ds_inc_0(9),
      I2 => Q(3),
      I3 => adc32_ds_inc_0(9),
      I4 => Q(4),
      I5 => adc30_ds_inc_0(9),
      O => \slv_rdata[9]_i_1__2_n_0\
    );
\slv_rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(0),
      Q => \slv_rdata_reg_n_0_[0]\,
      R => '0'
    );
\slv_rdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[10]_i_1__2_n_0\,
      Q => \slv_rdata_reg[10]_0\,
      R => \slv_rdata_reg[11]_1\
    );
\slv_rdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[11]_i_1__1_n_0\,
      Q => \slv_rdata_reg[11]_0\,
      R => \slv_rdata_reg[11]_1\
    );
\slv_rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(1),
      Q => \slv_rdata_reg[8]_0\(0),
      R => '0'
    );
\slv_rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(2),
      Q => \slv_rdata_reg[8]_0\(1),
      R => '0'
    );
\slv_rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(3),
      Q => \slv_rdata_reg[8]_0\(2),
      R => '0'
    );
\slv_rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(4),
      Q => \slv_rdata_reg[8]_0\(3),
      R => '0'
    );
\slv_rdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(5),
      Q => \slv_rdata_reg[8]_0\(4),
      R => '0'
    );
\slv_rdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(6),
      Q => \slv_rdata_reg[8]_0\(5),
      R => '0'
    );
\slv_rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(7),
      Q => \slv_rdata_reg[8]_0\(6),
      R => '0'
    );
\slv_rdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => D(8),
      Q => \slv_rdata_reg[8]_0\(7),
      R => '0'
    );
\slv_rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => s_axi_aresetn,
      D => \slv_rdata[9]_i_1__2_n_0\,
      Q => \slv_rdata_reg[9]_0\,
      R => \slv_rdata_reg[11]_1\
    );
slv_rden_r_reg: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => '1',
      D => adc3slv_rden,
      Q => \^slv_rden_r\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(0),
      Q => \slv_wdata_r_internal_reg_n_0_[0]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(10),
      Q => \slv_wdata_r_internal_reg_n_0_[10]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(11),
      Q => \slv_wdata_r_internal_reg_n_0_[11]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(1),
      Q => \slv_wdata_r_internal_reg_n_0_[1]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(2),
      Q => \slv_wdata_r_internal_reg_n_0_[2]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(3),
      Q => \slv_wdata_r_internal_reg_n_0_[3]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(4),
      Q => \slv_wdata_r_internal_reg_n_0_[4]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(5),
      Q => \slv_wdata_r_internal_reg_n_0_[5]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(6),
      Q => \slv_wdata_r_internal_reg_n_0_[6]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(7),
      Q => \slv_wdata_r_internal_reg_n_0_[7]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(8),
      Q => \slv_wdata_r_internal_reg_n_0_[8]\,
      R => \^p_0_in\
    );
\slv_wdata_r_internal_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s_axi_aclk,
      CE => E(0),
      D => s_axi_wdata(9),
      Q => \slv_wdata_r_internal_reg_n_0_[9]\,
      R => \^p_0_in\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_wrap2 is
  port (
    s0_axis_clock : in STD_LOGIC;
    wea : in STD_LOGIC_VECTOR ( 0 to 0 );
    Q : in STD_LOGIC_VECTOR ( 7 downto 0 );
    \gen_wr_a.gen_word_narrow.mem_reg_1\ : in STD_LOGIC_VECTOR ( 127 downto 0 );
    \gen_wr_a.gen_word_narrow.mem_reg_1_0\ : in STD_LOGIC_VECTOR ( 7 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_wrap2;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_wrap2 is
begin
xpm_mem_ds_sdpram_wrap_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_sdpram_wrap
     port map (
      Q(7 downto 0) => Q(7 downto 0),
      \gen_wr_a.gen_word_narrow.mem_reg_1\(127 downto 0) => \gen_wr_a.gen_word_narrow.mem_reg_1\(127 downto 0),
      \gen_wr_a.gen_word_narrow.mem_reg_1_0\(7 downto 0) => \gen_wr_a.gen_word_narrow.mem_reg_1_0\(7 downto 0),
      s0_axis_clock => s0_axis_clock,
      wea(0) => wea(0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl is
  port (
    axi_wr_access_reg : out STD_LOGIC;
    axi_arready_reg : out STD_LOGIC;
    adc00_ds_pulse_control_0 : out STD_LOGIC;
    axi_rvalid_reg : out STD_LOGIC;
    axi_bvalid_reg : out STD_LOGIC;
    axi_awready_reg : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 0 to 0 );
    enable_reg : out STD_LOGIC;
    \adc00_ds_inc_0_reg[7]\ : out STD_LOGIC_VECTOR ( 7 downto 0 );
    s00_tready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 15 downto 0 );
    s0_axis_clock : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_arvalid : in STD_LOGIC;
    s_axi_awvalid : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s00_tdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    done_flag : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    dest_out : in STD_LOGIC;
    D : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    error_flag : in STD_LOGIC;
    s00_ds_status : in STD_LOGIC;
    dest_rst : in STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 11 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl is
  signal adc00_ds_control_0 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal adc00_ds_inc_0 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal \^adc00_ds_inc_0_reg[7]\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal adc00_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc01_ds_inc_0 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal adc01_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc02_ds_inc_0 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal adc02_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc03_ds_inc_0 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal adc03_ds_type_0 : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal adc0_rfadc_exdes_ctrl_axi_i_n_18 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_19 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_20 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_21 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_22 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_23 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_24 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_25 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_26 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_27 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_28 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_29 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_3 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_30 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_31 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_32 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_33 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_34 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_4 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_44 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_46 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_47 : STD_LOGIC;
  signal adc0_rfadc_exdes_ctrl_axi_i_n_5 : STD_LOGIC;
  signal adc0axi_map_wready : STD_LOGIC;
  signal adc0slv_rden : STD_LOGIC;
  signal adc10_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc10_ds_type_0 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal adc11_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc11_ds_type_0 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal adc12_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc12_ds_type_0 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal adc13_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc13_ds_type_0 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal adc1_rfadc_exdes_ctrl_axi_i_n_10 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_15 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_16 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_17 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_2 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_3 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_4 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_42 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_43 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_44 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_45 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_46 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_47 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_48 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_49 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_5 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_50 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_51 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_52 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_53 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_54 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_55 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_56 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_57 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_58 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_59 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_6 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_7 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_8 : STD_LOGIC;
  signal adc1_rfadc_exdes_ctrl_axi_i_n_9 : STD_LOGIC;
  signal adc1axi_map_wready : STD_LOGIC;
  signal adc1slv_rden : STD_LOGIC;
  signal adc20_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc21_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc22_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc23_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc2_rfadc_exdes_ctrl_axi_i_n_2 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_29 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_3 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_30 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_31 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_32 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_33 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_34 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_35 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_36 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_37 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_38 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_39 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_4 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_40 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_41 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_42 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_43 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_44 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_45 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_46 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_47 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_48 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_49 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_5 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_50 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_6 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_7 : STD_LOGIC;
  signal adc2_rfadc_exdes_ctrl_axi_i_n_8 : STD_LOGIC;
  signal adc2axi_map_wready : STD_LOGIC;
  signal adc2slv_rden : STD_LOGIC;
  signal adc30_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc31_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc32_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc33_ds_enable_0 : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal adc3_rfadc_exdes_ctrl_axi_i_n_10 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_3 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_31 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_32 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_33 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_34 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_35 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_36 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_37 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_38 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_39 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_4 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_40 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_41 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_42 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_43 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_44 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_45 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_46 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_47 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_48 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_49 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_5 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_50 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_51 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_6 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_7 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_8 : STD_LOGIC;
  signal adc3_rfadc_exdes_ctrl_axi_i_n_9 : STD_LOGIC;
  signal adc3axi_map_wready : STD_LOGIC;
  signal adc3slv_rden : STD_LOGIC;
  signal adc_ds_axi_map_wready : STD_LOGIC;
  signal adc_ds_slv_rden : STD_LOGIC;
  signal axi_register_if_i_n_17 : STD_LOGIC;
  signal axi_register_if_i_n_19 : STD_LOGIC;
  signal axi_register_if_i_n_20 : STD_LOGIC;
  signal axi_register_if_i_n_21 : STD_LOGIC;
  signal axi_register_if_i_n_22 : STD_LOGIC;
  signal axi_register_if_i_n_23 : STD_LOGIC;
  signal axi_register_if_i_n_24 : STD_LOGIC;
  signal axi_register_if_i_n_28 : STD_LOGIC;
  signal axi_register_if_i_n_29 : STD_LOGIC;
  signal axi_register_if_i_n_30 : STD_LOGIC;
  signal axi_register_if_i_n_31 : STD_LOGIC;
  signal axi_register_if_i_n_32 : STD_LOGIC;
  signal axi_register_if_i_n_33 : STD_LOGIC;
  signal axi_register_if_i_n_34 : STD_LOGIC;
  signal axi_register_if_i_n_35 : STD_LOGIC;
  signal axi_register_if_i_n_36 : STD_LOGIC;
  signal axi_register_if_i_n_37 : STD_LOGIC;
  signal axi_register_if_i_n_38 : STD_LOGIC;
  signal axi_register_if_i_n_39 : STD_LOGIC;
  signal axi_register_if_i_n_40 : STD_LOGIC;
  signal axi_register_if_i_n_41 : STD_LOGIC;
  signal axi_register_if_i_n_42 : STD_LOGIC;
  signal axi_register_if_i_n_43 : STD_LOGIC;
  signal axi_register_if_i_n_44 : STD_LOGIC;
  signal axi_register_if_i_n_45 : STD_LOGIC;
  signal axi_register_if_i_n_46 : STD_LOGIC;
  signal axi_register_if_i_n_47 : STD_LOGIC;
  signal axi_register_if_i_n_48 : STD_LOGIC;
  signal axi_register_if_i_n_49 : STD_LOGIC;
  signal axi_register_if_i_n_50 : STD_LOGIC;
  signal axi_register_if_i_n_51 : STD_LOGIC;
  signal axi_register_if_i_n_52 : STD_LOGIC;
  signal axi_register_if_i_n_53 : STD_LOGIC;
  signal axi_register_if_i_n_54 : STD_LOGIC;
  signal axi_register_if_i_n_55 : STD_LOGIC;
  signal axi_register_if_i_n_56 : STD_LOGIC;
  signal axi_register_if_i_n_57 : STD_LOGIC;
  signal axi_register_if_i_n_58 : STD_LOGIC;
  signal axi_register_if_i_n_59 : STD_LOGIC;
  signal axi_register_if_i_n_60 : STD_LOGIC;
  signal axi_register_if_i_n_61 : STD_LOGIC;
  signal axi_register_if_i_n_62 : STD_LOGIC;
  signal axi_register_if_i_n_63 : STD_LOGIC;
  signal axi_register_if_i_n_64 : STD_LOGIC;
  signal axi_register_if_i_n_65 : STD_LOGIC;
  signal axi_register_if_i_n_66 : STD_LOGIC;
  signal axi_register_if_i_n_67 : STD_LOGIC;
  signal axi_register_if_i_n_68 : STD_LOGIC;
  signal axi_register_if_i_n_69 : STD_LOGIC;
  signal axi_register_if_i_n_70 : STD_LOGIC;
  signal axi_register_if_i_n_71 : STD_LOGIC;
  signal axi_register_if_i_n_72 : STD_LOGIC;
  signal axi_register_if_i_n_73 : STD_LOGIC;
  signal axi_register_if_i_n_74 : STD_LOGIC;
  signal axi_register_if_i_n_75 : STD_LOGIC;
  signal axi_register_if_i_n_76 : STD_LOGIC;
  signal axi_register_if_i_n_77 : STD_LOGIC;
  signal axi_register_if_i_n_78 : STD_LOGIC;
  signal axi_register_if_i_n_79 : STD_LOGIC;
  signal axi_register_if_i_n_80 : STD_LOGIC;
  signal axi_register_if_i_n_81 : STD_LOGIC;
  signal axi_register_if_i_n_82 : STD_LOGIC;
  signal axi_register_if_i_n_83 : STD_LOGIC;
  signal axi_register_if_i_n_84 : STD_LOGIC;
  signal axi_register_if_i_n_85 : STD_LOGIC;
  signal axi_register_if_i_n_86 : STD_LOGIC;
  signal axi_register_if_i_n_87 : STD_LOGIC;
  signal axi_register_if_i_n_88 : STD_LOGIC;
  signal axi_register_if_i_n_89 : STD_LOGIC;
  signal axi_register_if_i_n_90 : STD_LOGIC;
  signal axi_register_if_i_n_91 : STD_LOGIC;
  signal axi_register_if_i_n_92 : STD_LOGIC;
  signal axi_register_if_i_n_93 : STD_LOGIC;
  signal axi_register_if_i_n_94 : STD_LOGIC;
  signal axi_register_if_i_n_95 : STD_LOGIC;
  signal axi_register_if_i_n_96 : STD_LOGIC;
  signal axi_register_if_i_n_97 : STD_LOGIC;
  signal axi_register_if_i_n_98 : STD_LOGIC;
  signal axi_register_if_i_n_99 : STD_LOGIC;
  signal enable : STD_LOGIC;
  signal p_0_in : STD_LOGIC;
  signal p_0_in0 : STD_LOGIC;
  signal slv_addr : STD_LOGIC_VECTOR ( 4 downto 2 );
  signal slv_rdata : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal slv_rden_r : STD_LOGIC;
  signal slv_rden_r_0 : STD_LOGIC;
  signal slv_rden_r_2 : STD_LOGIC;
  signal slv_rden_r_4 : STD_LOGIC;
  signal slv_wren_done_pulse : STD_LOGIC;
  signal slv_wren_done_pulse_1 : STD_LOGIC;
  signal slv_wren_done_pulse_3 : STD_LOGIC;
  signal slv_wren_done_pulse_5 : STD_LOGIC;
  signal timeout_enable : STD_LOGIC;
  signal timeout_value : STD_LOGIC_VECTOR ( 11 downto 0 );
begin
  \adc00_ds_inc_0_reg[7]\(7 downto 0) <= \^adc00_ds_inc_0_reg[7]\(7 downto 0);
adc0_rfadc_exdes_ctrl_axi_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc0_rfadc_exdes_ctrl_axi
     port map (
      D(5) => axi_register_if_i_n_80,
      D(4) => axi_register_if_i_n_81,
      D(3) => axi_register_if_i_n_82,
      D(2) => axi_register_if_i_n_83,
      D(1) => axi_register_if_i_n_84,
      D(0) => axi_register_if_i_n_85,
      E(0) => axi_register_if_i_n_90,
      Q(5) => p_0_in0,
      Q(4) => axi_register_if_i_n_19,
      Q(3) => axi_register_if_i_n_20,
      Q(2) => axi_register_if_i_n_21,
      Q(1) => axi_register_if_i_n_22,
      Q(0) => axi_register_if_i_n_24,
      \adc00_ds_control_0_reg[0]_0\ => axi_register_if_i_n_71,
      \adc00_ds_control_0_reg[1]_0\(0) => adc00_ds_control_0(1),
      \adc00_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_65,
      \adc00_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_72,
      \adc00_ds_inc_0_reg[8]_0\(8) => adc00_ds_inc_0(8),
      \adc00_ds_inc_0_reg[8]_0\(7 downto 0) => \^adc00_ds_inc_0_reg[7]\(7 downto 0),
      adc00_ds_pulse_control_0 => adc00_ds_pulse_control_0,
      adc00_ds_pulse_control_0_reg_0 => axi_register_if_i_n_36,
      adc00_ds_pulse_control_0_reg_1 => axi_register_if_i_n_88,
      \adc00_ds_type_0_reg[3]_0\(3 downto 0) => adc00_ds_type_0(3 downto 0),
      \adc00_ds_type_0_reg[3]_1\ => axi_register_if_i_n_70,
      \adc01_ds_control_0_reg[0]_0\ => axi_register_if_i_n_69,
      \adc01_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_29,
      \adc01_ds_inc_0_reg[0]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_46,
      \adc01_ds_inc_0_reg[0]_1\ => axi_register_if_i_n_87,
      \adc01_ds_inc_0_reg[1]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_32,
      \adc01_ds_inc_0_reg[2]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_30,
      \adc01_ds_inc_0_reg[3]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_29,
      \adc01_ds_inc_0_reg[4]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_26,
      \adc01_ds_inc_0_reg[5]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_24,
      \adc01_ds_inc_0_reg[6]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_22,
      \adc01_ds_inc_0_reg[7]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_21,
      \adc01_ds_inc_0_reg[8]_0\(0) => adc01_ds_inc_0(8),
      \adc01_ds_type_0_reg[0]_0\ => axi_register_if_i_n_28,
      \adc01_ds_type_0_reg[1]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_34,
      \adc01_ds_type_0_reg[3]_0\(2 downto 1) => adc01_ds_type_0(3 downto 2),
      \adc01_ds_type_0_reg[3]_0\(0) => adc01_ds_type_0(0),
      \adc02_ds_control_0_reg[0]_0\ => axi_register_if_i_n_78,
      \adc02_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_77,
      \adc02_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_76,
      \adc02_ds_inc_0_reg[8]_0\(0) => adc02_ds_inc_0(8),
      \adc02_ds_type_0_reg[0]_0\ => axi_register_if_i_n_75,
      \adc02_ds_type_0_reg[3]_0\(2 downto 1) => adc02_ds_type_0(3 downto 2),
      \adc02_ds_type_0_reg[3]_0\(0) => adc02_ds_type_0(0),
      \adc03_ds_control_0_reg[0]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_44,
      \adc03_ds_control_0_reg[1]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_3,
      \adc03_ds_control_0_reg[1]_1\ => axi_register_if_i_n_74,
      \adc03_ds_enable_0_reg[0]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_47,
      \adc03_ds_enable_0_reg[1]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_33,
      \adc03_ds_enable_0_reg[2]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_31,
      \adc03_ds_enable_0_reg[3]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_28,
      \adc03_ds_enable_0_reg[4]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_27,
      \adc03_ds_enable_0_reg[5]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_25,
      \adc03_ds_enable_0_reg[6]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_23,
      \adc03_ds_enable_0_reg[7]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_20,
      \adc03_ds_enable_0_reg[7]_1\ => axi_register_if_i_n_67,
      \adc03_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_73,
      \adc03_ds_inc_0_reg[10]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_18,
      \adc03_ds_inc_0_reg[11]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_5,
      \adc03_ds_inc_0_reg[8]_0\(0) => adc03_ds_inc_0(8),
      \adc03_ds_inc_0_reg[9]_0\ => adc0_rfadc_exdes_ctrl_axi_i_n_19,
      \adc03_ds_type_0_reg[0]_0\ => axi_register_if_i_n_66,
      \adc03_ds_type_0_reg[3]_0\(2 downto 1) => adc03_ds_type_0(3 downto 2),
      \adc03_ds_type_0_reg[3]_0\(0) => adc03_ds_type_0(0),
      adc0axi_map_wready => adc0axi_map_wready,
      adc0slv_rden => adc0slv_rden,
      adc_ds_slv_rden => adc_ds_slv_rden,
      \axi_rresp[1]_i_2\(0) => axi_register_if_i_n_17,
      dest_rst => dest_rst,
      p_0_in => p_0_in,
      s00_tready => s00_tready,
      s0_axis_clock => s0_axis_clock,
      s_axi_aclk => s_axi_aclk,
      s_axi_aresetn => s_axi_aresetn,
      s_axi_wdata(11 downto 0) => s_axi_wdata(11 downto 0),
      s_axi_wvalid => s_axi_wvalid,
      slv_rdata(15 downto 0) => slv_rdata(15 downto 0),
      \slv_rdata_reg[12]_0\ => axi_register_if_i_n_97,
      \slv_rdata_reg[12]_1\ => axi_register_if_i_n_86,
      \slv_rdata_reg[13]_0\ => axi_register_if_i_n_96,
      \slv_rdata_reg[14]_0\ => axi_register_if_i_n_95,
      \slv_rdata_reg[15]_0\ => axi_register_if_i_n_94,
      \slv_rdata_reg[1]_0\ => axi_register_if_i_n_89,
      \slv_rdata_reg[2]_0\ => axi_register_if_i_n_33,
      \slv_rdata_reg[3]_0\ => axi_register_if_i_n_34,
      \slv_rdata_reg[4]_0\ => axi_register_if_i_n_32,
      \slv_rdata_reg[5]_0\ => axi_register_if_i_n_31,
      \slv_rdata_reg[6]_0\ => axi_register_if_i_n_30,
      \slv_rdata_reg[7]_0\ => axi_register_if_i_n_35,
      slv_rden_r => slv_rden_r,
      slv_rden_r_reg_0 => adc0_rfadc_exdes_ctrl_axi_i_n_4,
      slv_wren_done_pulse => slv_wren_done_pulse
    );
adc1_rfadc_exdes_ctrl_axi_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc1_rfadc_exdes_ctrl_axi
     port map (
      D(8) => axi_register_if_i_n_38,
      D(7) => axi_register_if_i_n_39,
      D(6) => axi_register_if_i_n_40,
      D(5) => axi_register_if_i_n_41,
      D(4) => axi_register_if_i_n_42,
      D(3) => axi_register_if_i_n_43,
      D(2) => axi_register_if_i_n_44,
      D(1) => axi_register_if_i_n_45,
      D(0) => axi_register_if_i_n_46,
      E(0) => axi_register_if_i_n_91,
      Q(5) => axi_register_if_i_n_20,
      Q(4) => axi_register_if_i_n_21,
      Q(3) => axi_register_if_i_n_23,
      Q(2 downto 0) => slv_addr(4 downto 2),
      \adc10_ds_control_0_reg[0]_0\ => axi_register_if_i_n_71,
      \adc10_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_65,
      \adc10_ds_enable_0_reg[7]_0\(5 downto 0) => adc10_ds_enable_0(7 downto 2),
      \adc10_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_72,
      \adc10_ds_type_0_reg[0]_0\ => axi_register_if_i_n_70,
      \adc10_ds_type_0_reg[3]_0\(0) => adc10_ds_type_0(3),
      \adc11_ds_control_0_reg[0]_0\ => axi_register_if_i_n_69,
      \adc11_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_29,
      \adc11_ds_enable_0_reg[7]_0\(5 downto 0) => adc11_ds_enable_0(7 downto 2),
      \adc11_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_87,
      \adc11_ds_type_0_reg[0]_0\ => axi_register_if_i_n_28,
      \adc11_ds_type_0_reg[3]_0\(0) => adc11_ds_type_0(3),
      \adc12_ds_control_0_reg[0]_0\ => axi_register_if_i_n_78,
      \adc12_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_77,
      \adc12_ds_enable_0_reg[7]_0\(5 downto 0) => adc12_ds_enable_0(7 downto 2),
      \adc12_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_76,
      \adc12_ds_type_0_reg[0]_0\ => axi_register_if_i_n_75,
      \adc12_ds_type_0_reg[3]_0\(0) => adc12_ds_type_0(3),
      \adc13_ds_control_0_reg[0]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_46,
      \adc13_ds_control_0_reg[0]_1\ => axi_register_if_i_n_74,
      \adc13_ds_control_0_reg[1]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_16,
      \adc13_ds_enable_0_reg[0]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_43,
      \adc13_ds_enable_0_reg[0]_1\ => axi_register_if_i_n_67,
      \adc13_ds_enable_0_reg[1]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_17,
      \adc13_ds_enable_0_reg[7]_0\(5 downto 0) => adc13_ds_enable_0(7 downto 2),
      \adc13_ds_inc_0_reg[0]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_45,
      \adc13_ds_inc_0_reg[0]_1\ => axi_register_if_i_n_73,
      \adc13_ds_inc_0_reg[1]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_15,
      \adc13_ds_inc_0_reg[2]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_9,
      \adc13_ds_inc_0_reg[3]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_8,
      \adc13_ds_inc_0_reg[4]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_7,
      \adc13_ds_inc_0_reg[5]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_6,
      \adc13_ds_inc_0_reg[6]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_5,
      \adc13_ds_inc_0_reg[7]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_4,
      \adc13_ds_inc_0_reg[8]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_3,
      \adc13_ds_type_0_reg[0]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_44,
      \adc13_ds_type_0_reg[0]_1\ => axi_register_if_i_n_66,
      \adc13_ds_type_0_reg[1]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_42,
      \adc13_ds_type_0_reg[2]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_10,
      \adc13_ds_type_0_reg[3]_0\(0) => adc13_ds_type_0(3),
      adc1axi_map_wready => adc1axi_map_wready,
      adc1slv_rden => adc1slv_rden,
      adc_ds_axi_map_wready => adc_ds_axi_map_wready,
      p_0_in => p_0_in,
      s_axi_aclk => s_axi_aclk,
      s_axi_aresetn => s_axi_aresetn,
      s_axi_wdata(11 downto 0) => s_axi_wdata(11 downto 0),
      s_axi_wvalid => s_axi_wvalid,
      \slv_addr_reg[6]\ => adc1_rfadc_exdes_ctrl_axi_i_n_57,
      \slv_rdata_reg[10]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_58,
      \slv_rdata_reg[11]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_56,
      \slv_rdata_reg[11]_1\ => axi_register_if_i_n_79,
      \slv_rdata_reg[8]_0\(8) => adc1_rfadc_exdes_ctrl_axi_i_n_47,
      \slv_rdata_reg[8]_0\(7) => adc1_rfadc_exdes_ctrl_axi_i_n_48,
      \slv_rdata_reg[8]_0\(6) => adc1_rfadc_exdes_ctrl_axi_i_n_49,
      \slv_rdata_reg[8]_0\(5) => adc1_rfadc_exdes_ctrl_axi_i_n_50,
      \slv_rdata_reg[8]_0\(4) => adc1_rfadc_exdes_ctrl_axi_i_n_51,
      \slv_rdata_reg[8]_0\(3) => adc1_rfadc_exdes_ctrl_axi_i_n_52,
      \slv_rdata_reg[8]_0\(2) => adc1_rfadc_exdes_ctrl_axi_i_n_53,
      \slv_rdata_reg[8]_0\(1) => adc1_rfadc_exdes_ctrl_axi_i_n_54,
      \slv_rdata_reg[8]_0\(0) => adc1_rfadc_exdes_ctrl_axi_i_n_55,
      \slv_rdata_reg[9]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_59,
      slv_rden_r => slv_rden_r_0,
      slv_rden_r_1 => slv_rden_r,
      slv_rden_r_reg_0 => adc1_rfadc_exdes_ctrl_axi_i_n_2,
      slv_wren_done_pulse => slv_wren_done_pulse_1,
      slv_wren_done_pulse_0 => slv_wren_done_pulse
    );
adc2_rfadc_exdes_ctrl_axi_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc2_rfadc_exdes_ctrl_axi
     port map (
      D(8) => axi_register_if_i_n_47,
      D(7) => axi_register_if_i_n_48,
      D(6) => axi_register_if_i_n_49,
      D(5) => axi_register_if_i_n_50,
      D(4) => axi_register_if_i_n_51,
      D(3) => axi_register_if_i_n_52,
      D(2) => axi_register_if_i_n_53,
      D(1) => axi_register_if_i_n_54,
      D(0) => axi_register_if_i_n_55,
      E(0) => axi_register_if_i_n_92,
      Q(0) => axi_register_if_i_n_17,
      \adc20_ds_control_0_reg[0]_0\ => axi_register_if_i_n_71,
      \adc20_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_65,
      \adc20_ds_enable_0_reg[7]_0\(4 downto 1) => adc20_ds_enable_0(7 downto 4),
      \adc20_ds_enable_0_reg[7]_0\(0) => adc20_ds_enable_0(2),
      \adc20_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_72,
      \adc20_ds_type_0_reg[0]_0\ => axi_register_if_i_n_70,
      \adc21_ds_control_0_reg[0]_0\ => axi_register_if_i_n_69,
      \adc21_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_29,
      \adc21_ds_enable_0_reg[7]_0\(4 downto 1) => adc21_ds_enable_0(7 downto 4),
      \adc21_ds_enable_0_reg[7]_0\(0) => adc21_ds_enable_0(2),
      \adc21_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_87,
      \adc21_ds_type_0_reg[0]_0\ => axi_register_if_i_n_28,
      \adc22_ds_control_0_reg[0]_0\ => axi_register_if_i_n_78,
      \adc22_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_77,
      \adc22_ds_enable_0_reg[7]_0\(4 downto 1) => adc22_ds_enable_0(7 downto 4),
      \adc22_ds_enable_0_reg[7]_0\(0) => adc22_ds_enable_0(2),
      \adc22_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_76,
      \adc22_ds_type_0_reg[0]_0\ => axi_register_if_i_n_75,
      \adc23_ds_control_0_reg[0]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_38,
      \adc23_ds_control_0_reg[0]_1\ => axi_register_if_i_n_74,
      \adc23_ds_control_0_reg[1]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_33,
      \adc23_ds_enable_0_reg[0]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_35,
      \adc23_ds_enable_0_reg[0]_1\ => axi_register_if_i_n_67,
      \adc23_ds_enable_0_reg[1]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_31,
      \adc23_ds_enable_0_reg[7]_0\(4 downto 1) => adc23_ds_enable_0(7 downto 4),
      \adc23_ds_enable_0_reg[7]_0\(0) => adc23_ds_enable_0(2),
      \adc23_ds_inc_0_reg[0]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_37,
      \adc23_ds_inc_0_reg[0]_1\ => axi_register_if_i_n_73,
      \adc23_ds_inc_0_reg[1]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_34,
      \adc23_ds_inc_0_reg[2]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_29,
      \adc23_ds_inc_0_reg[4]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_8,
      \adc23_ds_inc_0_reg[5]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_7,
      \adc23_ds_inc_0_reg[6]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_6,
      \adc23_ds_inc_0_reg[7]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_5,
      \adc23_ds_inc_0_reg[8]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_4,
      \adc23_ds_type_0_reg[0]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_36,
      \adc23_ds_type_0_reg[0]_1\ => axi_register_if_i_n_66,
      \adc23_ds_type_0_reg[1]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_32,
      \adc23_ds_type_0_reg[2]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_30,
      adc2axi_map_wready => adc2axi_map_wready,
      adc2slv_rden => adc2slv_rden,
      p_0_in => p_0_in,
      s_axi_aclk => s_axi_aclk,
      s_axi_aresetn => s_axi_aresetn,
      s_axi_wdata(11 downto 0) => s_axi_wdata(11 downto 0),
      s_axi_wvalid => s_axi_wvalid,
      \slv_addr_reg[2]\ => adc2_rfadc_exdes_ctrl_axi_i_n_3,
      \slv_rdata_reg[10]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_49,
      \slv_rdata_reg[11]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_48,
      \slv_rdata_reg[11]_1\(4) => axi_register_if_i_n_20,
      \slv_rdata_reg[11]_1\(3) => axi_register_if_i_n_21,
      \slv_rdata_reg[11]_1\(2 downto 0) => slv_addr(4 downto 2),
      \slv_rdata_reg[11]_2\ => adc1_rfadc_exdes_ctrl_axi_i_n_57,
      \slv_rdata_reg[8]_0\(8) => adc2_rfadc_exdes_ctrl_axi_i_n_39,
      \slv_rdata_reg[8]_0\(7) => adc2_rfadc_exdes_ctrl_axi_i_n_40,
      \slv_rdata_reg[8]_0\(6) => adc2_rfadc_exdes_ctrl_axi_i_n_41,
      \slv_rdata_reg[8]_0\(5) => adc2_rfadc_exdes_ctrl_axi_i_n_42,
      \slv_rdata_reg[8]_0\(4) => adc2_rfadc_exdes_ctrl_axi_i_n_43,
      \slv_rdata_reg[8]_0\(3) => adc2_rfadc_exdes_ctrl_axi_i_n_44,
      \slv_rdata_reg[8]_0\(2) => adc2_rfadc_exdes_ctrl_axi_i_n_45,
      \slv_rdata_reg[8]_0\(1) => adc2_rfadc_exdes_ctrl_axi_i_n_46,
      \slv_rdata_reg[8]_0\(0) => adc2_rfadc_exdes_ctrl_axi_i_n_47,
      \slv_rdata_reg[9]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_50,
      slv_rden_r => slv_rden_r_2,
      slv_rden_r_0 => slv_rden_r_0,
      slv_rden_r_reg_0 => adc2_rfadc_exdes_ctrl_axi_i_n_2,
      slv_wren_done_pulse => slv_wren_done_pulse_3,
      slv_wren_done_pulse_1 => slv_wren_done_pulse_1
    );
adc3_rfadc_exdes_ctrl_axi_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc3_rfadc_exdes_ctrl_axi
     port map (
      D(8) => axi_register_if_i_n_56,
      D(7) => axi_register_if_i_n_57,
      D(6) => axi_register_if_i_n_58,
      D(5) => axi_register_if_i_n_59,
      D(4) => axi_register_if_i_n_60,
      D(3) => axi_register_if_i_n_61,
      D(2) => axi_register_if_i_n_62,
      D(1) => axi_register_if_i_n_63,
      D(0) => axi_register_if_i_n_64,
      E(0) => axi_register_if_i_n_93,
      Q(4) => axi_register_if_i_n_20,
      Q(3) => axi_register_if_i_n_21,
      Q(2 downto 0) => slv_addr(4 downto 2),
      \adc30_ds_control_0_reg[0]_0\ => axi_register_if_i_n_71,
      \adc30_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_65,
      \adc30_ds_enable_0_reg[7]_0\(4 downto 1) => adc30_ds_enable_0(7 downto 4),
      \adc30_ds_enable_0_reg[7]_0\(0) => adc30_ds_enable_0(2),
      \adc30_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_72,
      \adc30_ds_type_0_reg[0]_0\ => axi_register_if_i_n_70,
      \adc31_ds_control_0_reg[0]_0\ => axi_register_if_i_n_69,
      \adc31_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_29,
      \adc31_ds_enable_0_reg[7]_0\(4 downto 1) => adc31_ds_enable_0(7 downto 4),
      \adc31_ds_enable_0_reg[7]_0\(0) => adc31_ds_enable_0(2),
      \adc31_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_87,
      \adc31_ds_type_0_reg[0]_0\ => axi_register_if_i_n_28,
      \adc32_ds_control_0_reg[0]_0\ => axi_register_if_i_n_78,
      \adc32_ds_enable_0_reg[0]_0\ => axi_register_if_i_n_77,
      \adc32_ds_enable_0_reg[7]_0\(4 downto 1) => adc32_ds_enable_0(7 downto 4),
      \adc32_ds_enable_0_reg[7]_0\(0) => adc32_ds_enable_0(2),
      \adc32_ds_inc_0_reg[0]_0\ => axi_register_if_i_n_76,
      \adc32_ds_type_0_reg[0]_0\ => axi_register_if_i_n_75,
      \adc33_ds_control_0_reg[0]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_39,
      \adc33_ds_control_0_reg[0]_1\ => axi_register_if_i_n_74,
      \adc33_ds_control_0_reg[1]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_36,
      \adc33_ds_enable_0_reg[0]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_37,
      \adc33_ds_enable_0_reg[0]_1\ => axi_register_if_i_n_67,
      \adc33_ds_enable_0_reg[1]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_33,
      \adc33_ds_enable_0_reg[7]_0\(4 downto 1) => adc33_ds_enable_0(7 downto 4),
      \adc33_ds_enable_0_reg[7]_0\(0) => adc33_ds_enable_0(2),
      \adc33_ds_inc_0_reg[0]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_40,
      \adc33_ds_inc_0_reg[0]_1\ => axi_register_if_i_n_73,
      \adc33_ds_inc_0_reg[1]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_35,
      \adc33_ds_inc_0_reg[2]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_31,
      \adc33_ds_inc_0_reg[4]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_10,
      \adc33_ds_inc_0_reg[5]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_9,
      \adc33_ds_inc_0_reg[6]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_8,
      \adc33_ds_inc_0_reg[7]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_7,
      \adc33_ds_inc_0_reg[8]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_6,
      \adc33_ds_type_0_reg[0]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_38,
      \adc33_ds_type_0_reg[0]_1\ => axi_register_if_i_n_66,
      \adc33_ds_type_0_reg[1]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_34,
      \adc33_ds_type_0_reg[2]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_32,
      adc3axi_map_wready => adc3axi_map_wready,
      adc3slv_rden => adc3slv_rden,
      \axi_rdata_reg[0]\ => axi_register_if_i_n_37,
      clk1_ready_pulse_reg => adc3_rfadc_exdes_ctrl_axi_i_n_5,
      p_0_in => p_0_in,
      s_axi_aclk => s_axi_aclk,
      s_axi_aresetn => s_axi_aresetn,
      s_axi_wdata(11 downto 0) => s_axi_wdata(11 downto 0),
      s_axi_wvalid => s_axi_wvalid,
      \slv_addr_reg[3]\ => adc3_rfadc_exdes_ctrl_axi_i_n_4,
      \slv_rdata_reg[0]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_3,
      \slv_rdata_reg[10]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_50,
      \slv_rdata_reg[11]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_49,
      \slv_rdata_reg[11]_1\ => adc1_rfadc_exdes_ctrl_axi_i_n_57,
      \slv_rdata_reg[8]_0\(7) => adc3_rfadc_exdes_ctrl_axi_i_n_41,
      \slv_rdata_reg[8]_0\(6) => adc3_rfadc_exdes_ctrl_axi_i_n_42,
      \slv_rdata_reg[8]_0\(5) => adc3_rfadc_exdes_ctrl_axi_i_n_43,
      \slv_rdata_reg[8]_0\(4) => adc3_rfadc_exdes_ctrl_axi_i_n_44,
      \slv_rdata_reg[8]_0\(3) => adc3_rfadc_exdes_ctrl_axi_i_n_45,
      \slv_rdata_reg[8]_0\(2) => adc3_rfadc_exdes_ctrl_axi_i_n_46,
      \slv_rdata_reg[8]_0\(1) => adc3_rfadc_exdes_ctrl_axi_i_n_47,
      \slv_rdata_reg[8]_0\(0) => adc3_rfadc_exdes_ctrl_axi_i_n_48,
      \slv_rdata_reg[9]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_51,
      slv_rden_r => slv_rden_r_4,
      slv_rden_r_0 => slv_rden_r_2,
      slv_wren_done_pulse => slv_wren_done_pulse_5,
      slv_wren_done_pulse_1 => slv_wren_done_pulse_3
    );
adc_exdes_cfg_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_adc_exdes_cfg
     port map (
      E(0) => axi_register_if_i_n_68,
      Q(1 downto 0) => Q(1 downto 0),
      done_flag => done_flag,
      enable => enable,
      enable_reg_0 => enable_reg,
      enable_reg_1 => axi_register_if_i_n_98,
      p_0_in => p_0_in,
      s_axi_aclk => s_axi_aclk,
      s_axi_wdata(11 downto 0) => s_axi_wdata(11 downto 0),
      timeout_enable => timeout_enable,
      timeout_enable_reg_0 => axi_register_if_i_n_99,
      \timeout_value_reg[11]_0\(11 downto 0) => timeout_value(11 downto 0)
    );
axi_register_if_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl_axi
     port map (
      D(0) => D(0),
      E(0) => axi_register_if_i_n_68,
      Q(0) => axi_register_if_i_n_17,
      adc0axi_map_wready => adc0axi_map_wready,
      adc0slv_rden => adc0slv_rden,
      adc1axi_map_wready => adc1axi_map_wready,
      adc1slv_rden => adc1slv_rden,
      adc2axi_map_wready => adc2axi_map_wready,
      adc2slv_rden => adc2slv_rden,
      adc2slv_rden_reg_0 => adc2_rfadc_exdes_ctrl_axi_i_n_2,
      adc2slv_rden_reg_1 => adc0_rfadc_exdes_ctrl_axi_i_n_4,
      adc3axi_map_wready => adc3axi_map_wready,
      adc3slv_rden => adc3slv_rden,
      adc_ds_axi_map_wready => adc_ds_axi_map_wready,
      adc_ds_slv_rden => adc_ds_slv_rden,
      axi_arready_reg_0 => axi_arready_reg,
      axi_awready_reg_0 => axi_awready_reg,
      \axi_bresp_reg[1]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_2,
      \axi_bresp_reg[1]_1\ => adc3_rfadc_exdes_ctrl_axi_i_n_5,
      axi_bvalid_reg_0 => axi_bvalid_reg,
      \axi_rdata[8]_i_2_0\(8) => adc2_rfadc_exdes_ctrl_axi_i_n_39,
      \axi_rdata[8]_i_2_0\(7) => adc2_rfadc_exdes_ctrl_axi_i_n_40,
      \axi_rdata[8]_i_2_0\(6) => adc2_rfadc_exdes_ctrl_axi_i_n_41,
      \axi_rdata[8]_i_2_0\(5) => adc2_rfadc_exdes_ctrl_axi_i_n_42,
      \axi_rdata[8]_i_2_0\(4) => adc2_rfadc_exdes_ctrl_axi_i_n_43,
      \axi_rdata[8]_i_2_0\(3) => adc2_rfadc_exdes_ctrl_axi_i_n_44,
      \axi_rdata[8]_i_2_0\(2) => adc2_rfadc_exdes_ctrl_axi_i_n_45,
      \axi_rdata[8]_i_2_0\(1) => adc2_rfadc_exdes_ctrl_axi_i_n_46,
      \axi_rdata[8]_i_2_0\(0) => adc2_rfadc_exdes_ctrl_axi_i_n_47,
      \axi_rdata[8]_i_2_1\(8) => adc1_rfadc_exdes_ctrl_axi_i_n_47,
      \axi_rdata[8]_i_2_1\(7) => adc1_rfadc_exdes_ctrl_axi_i_n_48,
      \axi_rdata[8]_i_2_1\(6) => adc1_rfadc_exdes_ctrl_axi_i_n_49,
      \axi_rdata[8]_i_2_1\(5) => adc1_rfadc_exdes_ctrl_axi_i_n_50,
      \axi_rdata[8]_i_2_1\(4) => adc1_rfadc_exdes_ctrl_axi_i_n_51,
      \axi_rdata[8]_i_2_1\(3) => adc1_rfadc_exdes_ctrl_axi_i_n_52,
      \axi_rdata[8]_i_2_1\(2) => adc1_rfadc_exdes_ctrl_axi_i_n_53,
      \axi_rdata[8]_i_2_1\(1) => adc1_rfadc_exdes_ctrl_axi_i_n_54,
      \axi_rdata[8]_i_2_1\(0) => adc1_rfadc_exdes_ctrl_axi_i_n_55,
      \axi_rdata_reg[0]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_3,
      \axi_rdata_reg[10]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_50,
      \axi_rdata_reg[10]_1\ => adc2_rfadc_exdes_ctrl_axi_i_n_49,
      \axi_rdata_reg[10]_2\ => adc1_rfadc_exdes_ctrl_axi_i_n_58,
      \axi_rdata_reg[11]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_49,
      \axi_rdata_reg[11]_1\(11 downto 0) => timeout_value(11 downto 0),
      \axi_rdata_reg[11]_2\ => adc2_rfadc_exdes_ctrl_axi_i_n_48,
      \axi_rdata_reg[11]_3\ => adc1_rfadc_exdes_ctrl_axi_i_n_56,
      \axi_rdata_reg[8]_0\(7) => adc3_rfadc_exdes_ctrl_axi_i_n_41,
      \axi_rdata_reg[8]_0\(6) => adc3_rfadc_exdes_ctrl_axi_i_n_42,
      \axi_rdata_reg[8]_0\(5) => adc3_rfadc_exdes_ctrl_axi_i_n_43,
      \axi_rdata_reg[8]_0\(4) => adc3_rfadc_exdes_ctrl_axi_i_n_44,
      \axi_rdata_reg[8]_0\(3) => adc3_rfadc_exdes_ctrl_axi_i_n_45,
      \axi_rdata_reg[8]_0\(2) => adc3_rfadc_exdes_ctrl_axi_i_n_46,
      \axi_rdata_reg[8]_0\(1) => adc3_rfadc_exdes_ctrl_axi_i_n_47,
      \axi_rdata_reg[8]_0\(0) => adc3_rfadc_exdes_ctrl_axi_i_n_48,
      \axi_rdata_reg[9]_0\ => adc3_rfadc_exdes_ctrl_axi_i_n_51,
      \axi_rdata_reg[9]_1\ => adc2_rfadc_exdes_ctrl_axi_i_n_50,
      \axi_rdata_reg[9]_2\ => adc1_rfadc_exdes_ctrl_axi_i_n_59,
      axi_rvalid_reg_0 => axi_rvalid_reg,
      axi_wr_access_reg_0 => axi_wr_access_reg,
      dest_out => dest_out,
      enable => enable,
      error_flag => error_flag,
      p_0_in => p_0_in,
      s00_ds_status => s00_ds_status,
      s00_tdata(127 downto 0) => s00_tdata(127 downto 0),
      s00_tdata_50_sp_1 => axi_register_if_i_n_33,
      s00_tdata_52_sp_1 => axi_register_if_i_n_32,
      s00_tdata_53_sp_1 => axi_register_if_i_n_31,
      s00_tdata_54_sp_1 => axi_register_if_i_n_30,
      s_axi_aclk => s_axi_aclk,
      s_axi_araddr(15 downto 0) => s_axi_araddr(15 downto 0),
      s_axi_aresetn => s_axi_aresetn,
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awaddr(15 downto 0) => s_axi_awaddr(15 downto 0),
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bready => s_axi_bready,
      s_axi_bresp(0) => s_axi_bresp(0),
      s_axi_rdata(15 downto 0) => s_axi_rdata(15 downto 0),
      s_axi_rready => s_axi_rready,
      s_axi_rresp(0) => s_axi_rresp(0),
      s_axi_wdata(0) => s_axi_wdata(0),
      \s_axi_wdata[0]_0\ => axi_register_if_i_n_99,
      s_axi_wdata_0_sp_1 => axi_register_if_i_n_98,
      s_axi_wvalid => s_axi_wvalid,
      \slv_addr_reg[11]_0\(9) => p_0_in0,
      \slv_addr_reg[11]_0\(8) => axi_register_if_i_n_19,
      \slv_addr_reg[11]_0\(7) => axi_register_if_i_n_20,
      \slv_addr_reg[11]_0\(6) => axi_register_if_i_n_21,
      \slv_addr_reg[11]_0\(5) => axi_register_if_i_n_22,
      \slv_addr_reg[11]_0\(4) => axi_register_if_i_n_23,
      \slv_addr_reg[11]_0\(3) => axi_register_if_i_n_24,
      \slv_addr_reg[11]_0\(2 downto 0) => slv_addr(4 downto 2),
      \slv_addr_reg[2]_0\ => axi_register_if_i_n_28,
      \slv_addr_reg[2]_1\ => axi_register_if_i_n_29,
      \slv_addr_reg[2]_10\ => axi_register_if_i_n_96,
      \slv_addr_reg[2]_11\ => axi_register_if_i_n_97,
      \slv_addr_reg[2]_2\(8) => axi_register_if_i_n_38,
      \slv_addr_reg[2]_2\(7) => axi_register_if_i_n_39,
      \slv_addr_reg[2]_2\(6) => axi_register_if_i_n_40,
      \slv_addr_reg[2]_2\(5) => axi_register_if_i_n_41,
      \slv_addr_reg[2]_2\(4) => axi_register_if_i_n_42,
      \slv_addr_reg[2]_2\(3) => axi_register_if_i_n_43,
      \slv_addr_reg[2]_2\(2) => axi_register_if_i_n_44,
      \slv_addr_reg[2]_2\(1) => axi_register_if_i_n_45,
      \slv_addr_reg[2]_2\(0) => axi_register_if_i_n_46,
      \slv_addr_reg[2]_3\(8) => axi_register_if_i_n_47,
      \slv_addr_reg[2]_3\(7) => axi_register_if_i_n_48,
      \slv_addr_reg[2]_3\(6) => axi_register_if_i_n_49,
      \slv_addr_reg[2]_3\(5) => axi_register_if_i_n_50,
      \slv_addr_reg[2]_3\(4) => axi_register_if_i_n_51,
      \slv_addr_reg[2]_3\(3) => axi_register_if_i_n_52,
      \slv_addr_reg[2]_3\(2) => axi_register_if_i_n_53,
      \slv_addr_reg[2]_3\(1) => axi_register_if_i_n_54,
      \slv_addr_reg[2]_3\(0) => axi_register_if_i_n_55,
      \slv_addr_reg[2]_4\(8) => axi_register_if_i_n_56,
      \slv_addr_reg[2]_4\(7) => axi_register_if_i_n_57,
      \slv_addr_reg[2]_4\(6) => axi_register_if_i_n_58,
      \slv_addr_reg[2]_4\(5) => axi_register_if_i_n_59,
      \slv_addr_reg[2]_4\(4) => axi_register_if_i_n_60,
      \slv_addr_reg[2]_4\(3) => axi_register_if_i_n_61,
      \slv_addr_reg[2]_4\(2) => axi_register_if_i_n_62,
      \slv_addr_reg[2]_4\(1) => axi_register_if_i_n_63,
      \slv_addr_reg[2]_4\(0) => axi_register_if_i_n_64,
      \slv_addr_reg[2]_5\ => axi_register_if_i_n_73,
      \slv_addr_reg[2]_6\ => axi_register_if_i_n_76,
      \slv_addr_reg[2]_7\ => axi_register_if_i_n_88,
      \slv_addr_reg[2]_8\ => axi_register_if_i_n_94,
      \slv_addr_reg[2]_9\ => axi_register_if_i_n_95,
      \slv_addr_reg[3]_0\ => axi_register_if_i_n_67,
      \slv_addr_reg[3]_1\ => axi_register_if_i_n_74,
      \slv_addr_reg[3]_2\ => axi_register_if_i_n_78,
      \slv_addr_reg[3]_3\ => axi_register_if_i_n_89,
      \slv_addr_reg[4]_0\(5) => axi_register_if_i_n_80,
      \slv_addr_reg[4]_0\(4) => axi_register_if_i_n_81,
      \slv_addr_reg[4]_0\(3) => axi_register_if_i_n_82,
      \slv_addr_reg[4]_0\(2) => axi_register_if_i_n_83,
      \slv_addr_reg[4]_0\(1) => axi_register_if_i_n_84,
      \slv_addr_reg[4]_0\(0) => axi_register_if_i_n_85,
      \slv_addr_reg[4]_1\ => axi_register_if_i_n_87,
      \slv_addr_reg[5]_0\ => axi_register_if_i_n_34,
      \slv_addr_reg[5]_1\ => axi_register_if_i_n_35,
      \slv_addr_reg[5]_2\ => axi_register_if_i_n_75,
      \slv_addr_reg[5]_3\ => axi_register_if_i_n_79,
      \slv_addr_reg[6]_0\ => axi_register_if_i_n_65,
      \slv_addr_reg[6]_1\ => axi_register_if_i_n_70,
      \slv_addr_reg[6]_2\ => axi_register_if_i_n_71,
      \slv_addr_reg[6]_3\ => axi_register_if_i_n_72,
      \slv_addr_reg[6]_4\ => axi_register_if_i_n_77,
      \slv_addr_reg[6]_5\ => axi_register_if_i_n_86,
      \slv_addr_reg[8]_0\ => axi_register_if_i_n_36,
      \slv_addr_reg[8]_1\ => axi_register_if_i_n_66,
      \slv_addr_reg[8]_2\ => axi_register_if_i_n_69,
      \slv_rd_addr_reg[5]_0\ => axi_register_if_i_n_37,
      slv_rdata(15 downto 0) => slv_rdata(15 downto 0),
      \slv_rdata[3]_i_5_0\(0) => adc13_ds_type_0(3),
      \slv_rdata[3]_i_5_1\(0) => adc11_ds_type_0(3),
      \slv_rdata[8]_i_3_0\(0) => adc03_ds_inc_0(8),
      \slv_rdata[8]_i_3_1\(0) => adc01_ds_inc_0(8),
      \slv_rdata_reg[0]\ => adc1_rfadc_exdes_ctrl_axi_i_n_44,
      \slv_rdata_reg[0]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_43,
      \slv_rdata_reg[0]_1\ => adc1_rfadc_exdes_ctrl_axi_i_n_45,
      \slv_rdata_reg[0]_10\ => adc3_rfadc_exdes_ctrl_axi_i_n_40,
      \slv_rdata_reg[0]_11\ => adc0_rfadc_exdes_ctrl_axi_i_n_47,
      \slv_rdata_reg[0]_12\ => adc0_rfadc_exdes_ctrl_axi_i_n_44,
      \slv_rdata_reg[0]_13\ => adc0_rfadc_exdes_ctrl_axi_i_n_46,
      \slv_rdata_reg[0]_2\ => adc1_rfadc_exdes_ctrl_axi_i_n_46,
      \slv_rdata_reg[0]_3\ => adc2_rfadc_exdes_ctrl_axi_i_n_36,
      \slv_rdata_reg[0]_4\ => adc2_rfadc_exdes_ctrl_axi_i_n_35,
      \slv_rdata_reg[0]_5\ => adc2_rfadc_exdes_ctrl_axi_i_n_37,
      \slv_rdata_reg[0]_6\ => adc2_rfadc_exdes_ctrl_axi_i_n_38,
      \slv_rdata_reg[0]_7\ => adc3_rfadc_exdes_ctrl_axi_i_n_38,
      \slv_rdata_reg[0]_8\ => adc3_rfadc_exdes_ctrl_axi_i_n_37,
      \slv_rdata_reg[0]_9\ => adc3_rfadc_exdes_ctrl_axi_i_n_39,
      \slv_rdata_reg[10]\ => adc0_rfadc_exdes_ctrl_axi_i_n_18,
      \slv_rdata_reg[11]\ => adc0_rfadc_exdes_ctrl_axi_i_n_5,
      \slv_rdata_reg[1]\ => adc1_rfadc_exdes_ctrl_axi_i_n_42,
      \slv_rdata_reg[1]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_17,
      \slv_rdata_reg[1]_1\ => adc1_rfadc_exdes_ctrl_axi_i_n_15,
      \slv_rdata_reg[1]_10\ => adc3_rfadc_exdes_ctrl_axi_i_n_36,
      \slv_rdata_reg[1]_11\ => adc0_rfadc_exdes_ctrl_axi_i_n_3,
      \slv_rdata_reg[1]_12\ => adc0_rfadc_exdes_ctrl_axi_i_n_33,
      \slv_rdata_reg[1]_13\ => adc0_rfadc_exdes_ctrl_axi_i_n_34,
      \slv_rdata_reg[1]_14\(0) => adc00_ds_control_0(1),
      \slv_rdata_reg[1]_15\ => adc0_rfadc_exdes_ctrl_axi_i_n_32,
      \slv_rdata_reg[1]_2\ => adc1_rfadc_exdes_ctrl_axi_i_n_16,
      \slv_rdata_reg[1]_3\ => adc2_rfadc_exdes_ctrl_axi_i_n_32,
      \slv_rdata_reg[1]_4\ => adc2_rfadc_exdes_ctrl_axi_i_n_31,
      \slv_rdata_reg[1]_5\ => adc2_rfadc_exdes_ctrl_axi_i_n_33,
      \slv_rdata_reg[1]_6\ => adc2_rfadc_exdes_ctrl_axi_i_n_34,
      \slv_rdata_reg[1]_7\ => adc3_rfadc_exdes_ctrl_axi_i_n_34,
      \slv_rdata_reg[1]_8\ => adc3_rfadc_exdes_ctrl_axi_i_n_33,
      \slv_rdata_reg[1]_9\ => adc3_rfadc_exdes_ctrl_axi_i_n_35,
      \slv_rdata_reg[2]\ => adc1_rfadc_exdes_ctrl_axi_i_n_10,
      \slv_rdata_reg[2]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_9,
      \slv_rdata_reg[2]_1\ => adc2_rfadc_exdes_ctrl_axi_i_n_30,
      \slv_rdata_reg[2]_2\ => adc2_rfadc_exdes_ctrl_axi_i_n_29,
      \slv_rdata_reg[2]_3\ => adc3_rfadc_exdes_ctrl_axi_i_n_32,
      \slv_rdata_reg[2]_4\ => adc3_rfadc_exdes_ctrl_axi_i_n_31,
      \slv_rdata_reg[2]_5\ => adc0_rfadc_exdes_ctrl_axi_i_n_30,
      \slv_rdata_reg[2]_6\ => adc0_rfadc_exdes_ctrl_axi_i_n_31,
      \slv_rdata_reg[3]\ => adc3_rfadc_exdes_ctrl_axi_i_n_4,
      \slv_rdata_reg[3]_0\ => adc1_rfadc_exdes_ctrl_axi_i_n_8,
      \slv_rdata_reg[3]_1\ => adc2_rfadc_exdes_ctrl_axi_i_n_3,
      \slv_rdata_reg[3]_2\(2 downto 1) => adc03_ds_type_0(3 downto 2),
      \slv_rdata_reg[3]_2\(0) => adc03_ds_type_0(0),
      \slv_rdata_reg[3]_3\(2 downto 1) => adc02_ds_type_0(3 downto 2),
      \slv_rdata_reg[3]_3\(0) => adc02_ds_type_0(0),
      \slv_rdata_reg[3]_4\(2 downto 1) => adc01_ds_type_0(3 downto 2),
      \slv_rdata_reg[3]_4\(0) => adc01_ds_type_0(0),
      \slv_rdata_reg[3]_5\(0) => adc12_ds_type_0(3),
      \slv_rdata_reg[3]_6\(0) => adc10_ds_type_0(3),
      \slv_rdata_reg[3]_7\ => adc0_rfadc_exdes_ctrl_axi_i_n_29,
      \slv_rdata_reg[3]_8\(3 downto 0) => adc00_ds_type_0(3 downto 0),
      \slv_rdata_reg[3]_9\ => adc0_rfadc_exdes_ctrl_axi_i_n_28,
      \slv_rdata_reg[4]\ => adc1_rfadc_exdes_ctrl_axi_i_n_7,
      \slv_rdata_reg[4]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_8,
      \slv_rdata_reg[4]_1\ => adc3_rfadc_exdes_ctrl_axi_i_n_10,
      \slv_rdata_reg[4]_2\ => adc0_rfadc_exdes_ctrl_axi_i_n_26,
      \slv_rdata_reg[4]_3\ => adc0_rfadc_exdes_ctrl_axi_i_n_27,
      \slv_rdata_reg[5]\ => adc1_rfadc_exdes_ctrl_axi_i_n_6,
      \slv_rdata_reg[5]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_7,
      \slv_rdata_reg[5]_1\ => adc3_rfadc_exdes_ctrl_axi_i_n_9,
      \slv_rdata_reg[5]_2\ => adc0_rfadc_exdes_ctrl_axi_i_n_24,
      \slv_rdata_reg[5]_3\ => adc0_rfadc_exdes_ctrl_axi_i_n_25,
      \slv_rdata_reg[6]\ => adc1_rfadc_exdes_ctrl_axi_i_n_5,
      \slv_rdata_reg[6]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_6,
      \slv_rdata_reg[6]_1\ => adc3_rfadc_exdes_ctrl_axi_i_n_8,
      \slv_rdata_reg[6]_2\ => adc0_rfadc_exdes_ctrl_axi_i_n_22,
      \slv_rdata_reg[6]_3\ => adc0_rfadc_exdes_ctrl_axi_i_n_23,
      \slv_rdata_reg[7]\(5 downto 0) => adc13_ds_enable_0(7 downto 2),
      \slv_rdata_reg[7]_0\(5 downto 0) => adc11_ds_enable_0(7 downto 2),
      \slv_rdata_reg[7]_1\(4 downto 1) => adc23_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_1\(0) => adc23_ds_enable_0(2),
      \slv_rdata_reg[7]_10\(5 downto 0) => adc12_ds_enable_0(7 downto 2),
      \slv_rdata_reg[7]_11\ => adc1_rfadc_exdes_ctrl_axi_i_n_4,
      \slv_rdata_reg[7]_12\ => adc2_rfadc_exdes_ctrl_axi_i_n_5,
      \slv_rdata_reg[7]_13\ => adc3_rfadc_exdes_ctrl_axi_i_n_7,
      \slv_rdata_reg[7]_14\ => adc0_rfadc_exdes_ctrl_axi_i_n_21,
      \slv_rdata_reg[7]_15\ => adc0_rfadc_exdes_ctrl_axi_i_n_20,
      \slv_rdata_reg[7]_2\(4 downto 1) => adc21_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_2\(0) => adc21_ds_enable_0(2),
      \slv_rdata_reg[7]_3\(4 downto 1) => adc22_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_3\(0) => adc22_ds_enable_0(2),
      \slv_rdata_reg[7]_4\(4 downto 1) => adc20_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_4\(0) => adc20_ds_enable_0(2),
      \slv_rdata_reg[7]_5\(4 downto 1) => adc33_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_5\(0) => adc33_ds_enable_0(2),
      \slv_rdata_reg[7]_6\(4 downto 1) => adc31_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_6\(0) => adc31_ds_enable_0(2),
      \slv_rdata_reg[7]_7\(4 downto 1) => adc32_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_7\(0) => adc32_ds_enable_0(2),
      \slv_rdata_reg[7]_8\(4 downto 1) => adc30_ds_enable_0(7 downto 4),
      \slv_rdata_reg[7]_8\(0) => adc30_ds_enable_0(2),
      \slv_rdata_reg[7]_9\(5 downto 0) => adc10_ds_enable_0(7 downto 2),
      \slv_rdata_reg[8]\ => adc3_rfadc_exdes_ctrl_axi_i_n_6,
      \slv_rdata_reg[8]_0\ => adc2_rfadc_exdes_ctrl_axi_i_n_4,
      \slv_rdata_reg[8]_1\ => adc1_rfadc_exdes_ctrl_axi_i_n_3,
      \slv_rdata_reg[8]_2\(8) => adc00_ds_inc_0(8),
      \slv_rdata_reg[8]_2\(7 downto 0) => \^adc00_ds_inc_0_reg[7]\(7 downto 0),
      \slv_rdata_reg[8]_3\(0) => adc02_ds_inc_0(8),
      \slv_rdata_reg[9]\ => adc0_rfadc_exdes_ctrl_axi_i_n_19,
      slv_rden_r => slv_rden_r_4,
      slv_rden_r_0 => slv_rden_r,
      slv_rden_r_1 => slv_rden_r_0,
      slv_rden_r_2 => slv_rden_r_2,
      slv_rden_r_reg(0) => axi_register_if_i_n_90,
      slv_rden_r_reg_0(0) => axi_register_if_i_n_91,
      slv_rden_r_reg_1(0) => axi_register_if_i_n_92,
      slv_rden_r_reg_2(0) => axi_register_if_i_n_93,
      slv_wren_done_pulse => slv_wren_done_pulse_5,
      timeout_enable => timeout_enable
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_dataCap is
  port (
    s00_ds_status : out STD_LOGIC;
    s0_axis_clock : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 7 downto 0 );
    adc00_ds_pulse_control_0 : in STD_LOGIC;
    s00_tdata : in STD_LOGIC_VECTOR ( 127 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_dataCap;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_dataCap is
  signal addra_reg : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal clear : STD_LOGIC;
  signal dina : STD_LOGIC_VECTOR ( 127 downto 0 );
  signal \p_0_in__0\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \^s00_ds_status\ : STD_LOGIC;
  signal wea0 : STD_LOGIC;
  signal wea_i_2_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \addra[1]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \addra[2]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \addra[3]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \addra[4]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \addra[6]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \addra[7]_i_1\ : label is "soft_lutpair2";
begin
  s00_ds_status <= \^s00_ds_status\;
\addra[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => addra_reg(0),
      O => \p_0_in__0\(0)
    );
\addra[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => addra_reg(0),
      I1 => addra_reg(1),
      O => \p_0_in__0\(1)
    );
\addra[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => addra_reg(2),
      I1 => addra_reg(1),
      I2 => addra_reg(0),
      O => \p_0_in__0\(2)
    );
\addra[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => addra_reg(3),
      I1 => addra_reg(0),
      I2 => addra_reg(1),
      I3 => addra_reg(2),
      O => \p_0_in__0\(3)
    );
\addra[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => addra_reg(4),
      I1 => addra_reg(2),
      I2 => addra_reg(1),
      I3 => addra_reg(0),
      I4 => addra_reg(3),
      O => \p_0_in__0\(4)
    );
\addra[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6AAAAAAAAAAAAAAA"
    )
        port map (
      I0 => addra_reg(5),
      I1 => addra_reg(3),
      I2 => addra_reg(0),
      I3 => addra_reg(1),
      I4 => addra_reg(2),
      I5 => addra_reg(4),
      O => \p_0_in__0\(5)
    );
\addra[6]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => addra_reg(6),
      I1 => wea_i_2_n_0,
      O => \p_0_in__0\(6)
    );
\addra[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => addra_reg(7),
      I1 => wea_i_2_n_0,
      I2 => addra_reg(6),
      O => \p_0_in__0\(7)
    );
\addra_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(0),
      Q => addra_reg(0),
      R => clear
    );
\addra_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(1),
      Q => addra_reg(1),
      R => clear
    );
\addra_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(2),
      Q => addra_reg(2),
      R => clear
    );
\addra_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(3),
      Q => addra_reg(3),
      R => clear
    );
\addra_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(4),
      Q => addra_reg(4),
      R => clear
    );
\addra_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(5),
      Q => addra_reg(5),
      R => clear
    );
\addra_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(6),
      Q => addra_reg(6),
      R => clear
    );
\addra_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => \p_0_in__0\(7),
      Q => addra_reg(7),
      R => clear
    );
\dina[127]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^s00_ds_status\,
      O => clear
    );
\dina_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(0),
      Q => dina(0),
      R => clear
    );
\dina_reg[100]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(100),
      Q => dina(100),
      R => clear
    );
\dina_reg[101]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(101),
      Q => dina(101),
      R => clear
    );
\dina_reg[102]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(102),
      Q => dina(102),
      R => clear
    );
\dina_reg[103]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(103),
      Q => dina(103),
      R => clear
    );
\dina_reg[104]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(104),
      Q => dina(104),
      R => clear
    );
\dina_reg[105]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(105),
      Q => dina(105),
      R => clear
    );
\dina_reg[106]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(106),
      Q => dina(106),
      R => clear
    );
\dina_reg[107]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(107),
      Q => dina(107),
      R => clear
    );
\dina_reg[108]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(108),
      Q => dina(108),
      R => clear
    );
\dina_reg[109]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(109),
      Q => dina(109),
      R => clear
    );
\dina_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(10),
      Q => dina(10),
      R => clear
    );
\dina_reg[110]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(110),
      Q => dina(110),
      R => clear
    );
\dina_reg[111]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(111),
      Q => dina(111),
      R => clear
    );
\dina_reg[112]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(112),
      Q => dina(112),
      R => clear
    );
\dina_reg[113]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(113),
      Q => dina(113),
      R => clear
    );
\dina_reg[114]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(114),
      Q => dina(114),
      R => clear
    );
\dina_reg[115]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(115),
      Q => dina(115),
      R => clear
    );
\dina_reg[116]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(116),
      Q => dina(116),
      R => clear
    );
\dina_reg[117]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(117),
      Q => dina(117),
      R => clear
    );
\dina_reg[118]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(118),
      Q => dina(118),
      R => clear
    );
\dina_reg[119]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(119),
      Q => dina(119),
      R => clear
    );
\dina_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(11),
      Q => dina(11),
      R => clear
    );
\dina_reg[120]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(120),
      Q => dina(120),
      R => clear
    );
\dina_reg[121]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(121),
      Q => dina(121),
      R => clear
    );
\dina_reg[122]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(122),
      Q => dina(122),
      R => clear
    );
\dina_reg[123]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(123),
      Q => dina(123),
      R => clear
    );
\dina_reg[124]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(124),
      Q => dina(124),
      R => clear
    );
\dina_reg[125]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(125),
      Q => dina(125),
      R => clear
    );
\dina_reg[126]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(126),
      Q => dina(126),
      R => clear
    );
\dina_reg[127]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(127),
      Q => dina(127),
      R => clear
    );
\dina_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(12),
      Q => dina(12),
      R => clear
    );
\dina_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(13),
      Q => dina(13),
      R => clear
    );
\dina_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(14),
      Q => dina(14),
      R => clear
    );
\dina_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(15),
      Q => dina(15),
      R => clear
    );
\dina_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(16),
      Q => dina(16),
      R => clear
    );
\dina_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(17),
      Q => dina(17),
      R => clear
    );
\dina_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(18),
      Q => dina(18),
      R => clear
    );
\dina_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(19),
      Q => dina(19),
      R => clear
    );
\dina_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(1),
      Q => dina(1),
      R => clear
    );
\dina_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(20),
      Q => dina(20),
      R => clear
    );
\dina_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(21),
      Q => dina(21),
      R => clear
    );
\dina_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(22),
      Q => dina(22),
      R => clear
    );
\dina_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(23),
      Q => dina(23),
      R => clear
    );
\dina_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(24),
      Q => dina(24),
      R => clear
    );
\dina_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(25),
      Q => dina(25),
      R => clear
    );
\dina_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(26),
      Q => dina(26),
      R => clear
    );
\dina_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(27),
      Q => dina(27),
      R => clear
    );
\dina_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(28),
      Q => dina(28),
      R => clear
    );
\dina_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(29),
      Q => dina(29),
      R => clear
    );
\dina_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(2),
      Q => dina(2),
      R => clear
    );
\dina_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(30),
      Q => dina(30),
      R => clear
    );
\dina_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(31),
      Q => dina(31),
      R => clear
    );
\dina_reg[32]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(32),
      Q => dina(32),
      R => clear
    );
\dina_reg[33]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(33),
      Q => dina(33),
      R => clear
    );
\dina_reg[34]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(34),
      Q => dina(34),
      R => clear
    );
\dina_reg[35]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(35),
      Q => dina(35),
      R => clear
    );
\dina_reg[36]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(36),
      Q => dina(36),
      R => clear
    );
\dina_reg[37]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(37),
      Q => dina(37),
      R => clear
    );
\dina_reg[38]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(38),
      Q => dina(38),
      R => clear
    );
\dina_reg[39]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(39),
      Q => dina(39),
      R => clear
    );
\dina_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(3),
      Q => dina(3),
      R => clear
    );
\dina_reg[40]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(40),
      Q => dina(40),
      R => clear
    );
\dina_reg[41]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(41),
      Q => dina(41),
      R => clear
    );
\dina_reg[42]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(42),
      Q => dina(42),
      R => clear
    );
\dina_reg[43]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(43),
      Q => dina(43),
      R => clear
    );
\dina_reg[44]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(44),
      Q => dina(44),
      R => clear
    );
\dina_reg[45]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(45),
      Q => dina(45),
      R => clear
    );
\dina_reg[46]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(46),
      Q => dina(46),
      R => clear
    );
\dina_reg[47]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(47),
      Q => dina(47),
      R => clear
    );
\dina_reg[48]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(48),
      Q => dina(48),
      R => clear
    );
\dina_reg[49]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(49),
      Q => dina(49),
      R => clear
    );
\dina_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(4),
      Q => dina(4),
      R => clear
    );
\dina_reg[50]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(50),
      Q => dina(50),
      R => clear
    );
\dina_reg[51]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(51),
      Q => dina(51),
      R => clear
    );
\dina_reg[52]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(52),
      Q => dina(52),
      R => clear
    );
\dina_reg[53]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(53),
      Q => dina(53),
      R => clear
    );
\dina_reg[54]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(54),
      Q => dina(54),
      R => clear
    );
\dina_reg[55]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(55),
      Q => dina(55),
      R => clear
    );
\dina_reg[56]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(56),
      Q => dina(56),
      R => clear
    );
\dina_reg[57]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(57),
      Q => dina(57),
      R => clear
    );
\dina_reg[58]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(58),
      Q => dina(58),
      R => clear
    );
\dina_reg[59]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(59),
      Q => dina(59),
      R => clear
    );
\dina_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(5),
      Q => dina(5),
      R => clear
    );
\dina_reg[60]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(60),
      Q => dina(60),
      R => clear
    );
\dina_reg[61]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(61),
      Q => dina(61),
      R => clear
    );
\dina_reg[62]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(62),
      Q => dina(62),
      R => clear
    );
\dina_reg[63]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(63),
      Q => dina(63),
      R => clear
    );
\dina_reg[64]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(64),
      Q => dina(64),
      R => clear
    );
\dina_reg[65]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(65),
      Q => dina(65),
      R => clear
    );
\dina_reg[66]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(66),
      Q => dina(66),
      R => clear
    );
\dina_reg[67]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(67),
      Q => dina(67),
      R => clear
    );
\dina_reg[68]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(68),
      Q => dina(68),
      R => clear
    );
\dina_reg[69]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(69),
      Q => dina(69),
      R => clear
    );
\dina_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(6),
      Q => dina(6),
      R => clear
    );
\dina_reg[70]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(70),
      Q => dina(70),
      R => clear
    );
\dina_reg[71]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(71),
      Q => dina(71),
      R => clear
    );
\dina_reg[72]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(72),
      Q => dina(72),
      R => clear
    );
\dina_reg[73]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(73),
      Q => dina(73),
      R => clear
    );
\dina_reg[74]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(74),
      Q => dina(74),
      R => clear
    );
\dina_reg[75]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(75),
      Q => dina(75),
      R => clear
    );
\dina_reg[76]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(76),
      Q => dina(76),
      R => clear
    );
\dina_reg[77]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(77),
      Q => dina(77),
      R => clear
    );
\dina_reg[78]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(78),
      Q => dina(78),
      R => clear
    );
\dina_reg[79]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(79),
      Q => dina(79),
      R => clear
    );
\dina_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(7),
      Q => dina(7),
      R => clear
    );
\dina_reg[80]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(80),
      Q => dina(80),
      R => clear
    );
\dina_reg[81]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(81),
      Q => dina(81),
      R => clear
    );
\dina_reg[82]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(82),
      Q => dina(82),
      R => clear
    );
\dina_reg[83]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(83),
      Q => dina(83),
      R => clear
    );
\dina_reg[84]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(84),
      Q => dina(84),
      R => clear
    );
\dina_reg[85]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(85),
      Q => dina(85),
      R => clear
    );
\dina_reg[86]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(86),
      Q => dina(86),
      R => clear
    );
\dina_reg[87]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(87),
      Q => dina(87),
      R => clear
    );
\dina_reg[88]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(88),
      Q => dina(88),
      R => clear
    );
\dina_reg[89]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(89),
      Q => dina(89),
      R => clear
    );
\dina_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(8),
      Q => dina(8),
      R => clear
    );
\dina_reg[90]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(90),
      Q => dina(90),
      R => clear
    );
\dina_reg[91]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(91),
      Q => dina(91),
      R => clear
    );
\dina_reg[92]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(92),
      Q => dina(92),
      R => clear
    );
\dina_reg[93]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(93),
      Q => dina(93),
      R => clear
    );
\dina_reg[94]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(94),
      Q => dina(94),
      R => clear
    );
\dina_reg[95]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(95),
      Q => dina(95),
      R => clear
    );
\dina_reg[96]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(96),
      Q => dina(96),
      R => clear
    );
\dina_reg[97]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(97),
      Q => dina(97),
      R => clear
    );
\dina_reg[98]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(98),
      Q => dina(98),
      R => clear
    );
\dina_reg[99]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(99),
      Q => dina(99),
      R => clear
    );
\dina_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => s00_tdata(9),
      Q => dina(9),
      R => clear
    );
wea_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7FFF7F00"
    )
        port map (
      I0 => addra_reg(7),
      I1 => wea_i_2_n_0,
      I2 => addra_reg(6),
      I3 => \^s00_ds_status\,
      I4 => adc00_ds_pulse_control_0,
      O => wea0
    );
wea_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => addra_reg(5),
      I1 => addra_reg(3),
      I2 => addra_reg(0),
      I3 => addra_reg(1),
      I4 => addra_reg(2),
      I5 => addra_reg(4),
      O => wea_i_2_n_0
    );
wea_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s0_axis_clock,
      CE => '1',
      D => wea0,
      Q => \^s00_ds_status\,
      R => '0'
    );
xpm_mem_ds_wrap2_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_wrap2
     port map (
      Q(7 downto 0) => addra_reg(7 downto 0),
      \gen_wr_a.gen_word_narrow.mem_reg_1\(127 downto 0) => dina(127 downto 0),
      \gen_wr_a.gen_word_narrow.mem_reg_1_0\(7 downto 0) => Q(7 downto 0),
      s0_axis_clock => s0_axis_clock,
      wea(0) => \^s00_ds_status\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_exdes_rfadc_data_sink is
  port (
    axi_awready_reg : out STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    axi_rvalid_reg : out STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    error_flag : out STD_LOGIC;
    s00_tready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 15 downto 0 );
    done_flag : out STD_LOGIC;
    axi_bvalid_reg : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_awvalid : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s00_tdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    s0_axis_clock : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 15 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    s_axi_bready : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_exdes_rfadc_data_sink;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_exdes_rfadc_data_sink is
  signal adc00_ds_pulse_control_0 : STD_LOGIC;
  signal axis_resetn_rt_0 : STD_LOGIC;
  signal done_bus_rt_0 : STD_LOGIC;
  signal done_delay : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \^done_flag\ : STD_LOGIC;
  signal error_bus_rt_0 : STD_LOGIC;
  signal \^error_flag\ : STD_LOGIC;
  signal rfadc_exdes_ctrl_i_n_8 : STD_LOGIC;
  signal s00_ds_inc : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal s00_ds_status : STD_LOGIC;
  attribute DEF_VAL : string;
  attribute DEF_VAL of cdc_arstn_0i : label is "1'b0";
  attribute DEST_SYNC_FF : integer;
  attribute DEST_SYNC_FF of cdc_arstn_0i : label is 5;
  attribute INIT : string;
  attribute INIT of cdc_arstn_0i : label is "0";
  attribute INIT_SYNC_FF : integer;
  attribute INIT_SYNC_FF of cdc_arstn_0i : label is 1;
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of cdc_arstn_0i : label is "true";
  attribute SIM_ASSERT_CHK : integer;
  attribute SIM_ASSERT_CHK of cdc_arstn_0i : label is 0;
  attribute VERSION : integer;
  attribute VERSION of cdc_arstn_0i : label is 0;
  attribute XPM_CDC : string;
  attribute XPM_CDC of cdc_arstn_0i : label is "SYNC_RST";
  attribute XPM_MODULE : string;
  attribute XPM_MODULE of cdc_arstn_0i : label is "TRUE";
  attribute DEST_SYNC_FF of cdc_done_0i : label is 5;
  attribute INIT_SYNC_FF of cdc_done_0i : label is 0;
  attribute KEEP_HIERARCHY of cdc_done_0i : label is "true";
  attribute SIM_ASSERT_CHK of cdc_done_0i : label is 0;
  attribute SRC_INPUT_REG : integer;
  attribute SRC_INPUT_REG of cdc_done_0i : label is 0;
  attribute VERSION of cdc_done_0i : label is 0;
  attribute XPM_CDC of cdc_done_0i : label is "SINGLE";
  attribute XPM_MODULE of cdc_done_0i : label is "TRUE";
  attribute DEST_SYNC_FF of cdc_error_0i : label is 5;
  attribute INIT_SYNC_FF of cdc_error_0i : label is 0;
  attribute KEEP_HIERARCHY of cdc_error_0i : label is "true";
  attribute SIM_ASSERT_CHK of cdc_error_0i : label is 0;
  attribute SRC_INPUT_REG of cdc_error_0i : label is 0;
  attribute VERSION of cdc_error_0i : label is 0;
  attribute XPM_CDC of cdc_error_0i : label is "SINGLE";
  attribute XPM_MODULE of cdc_error_0i : label is "TRUE";
begin
  done_flag <= \^done_flag\;
  error_flag <= \^error_flag\;
cdc_arstn_0i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_sync_rst
     port map (
      dest_clk => s0_axis_clock,
      dest_rst => axis_resetn_rt_0,
      src_rst => s_axi_aresetn
    );
cdc_done_0i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__11\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => done_bus_rt_0,
      src_clk => '0',
      src_in => '0'
    );
cdc_error_0i: entity work.\decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_cdc_single__10\
     port map (
      dest_clk => s_axi_aclk,
      dest_out => error_bus_rt_0,
      src_clk => '0',
      src_in => '0'
    );
\done_delay_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => done_bus_rt_0,
      Q => done_delay(0),
      R => '0'
    );
\done_delay_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => done_delay(0),
      Q => done_delay(1),
      R => '0'
    );
done_flag_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => rfadc_exdes_ctrl_i_n_8,
      Q => \^done_flag\,
      R => '0'
    );
ds_slice_00: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_xpm_mem_ds_dataCap
     port map (
      Q(7 downto 0) => s00_ds_inc(7 downto 0),
      adc00_ds_pulse_control_0 => adc00_ds_pulse_control_0,
      s00_ds_status => s00_ds_status,
      s00_tdata(127 downto 0) => s00_tdata(127 downto 0),
      s0_axis_clock => s0_axis_clock
    );
error_flag_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => error_bus_rt_0,
      Q => \^error_flag\,
      R => '0'
    );
rfadc_exdes_ctrl_i: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_rfadc_exdes_ctrl
     port map (
      D(0) => done_bus_rt_0,
      Q(1 downto 0) => done_delay(1 downto 0),
      \adc00_ds_inc_0_reg[7]\(7 downto 0) => s00_ds_inc(7 downto 0),
      adc00_ds_pulse_control_0 => adc00_ds_pulse_control_0,
      axi_arready_reg => s_axi_arready,
      axi_awready_reg => axi_awready_reg,
      axi_bvalid_reg => axi_bvalid_reg,
      axi_rvalid_reg => axi_rvalid_reg,
      axi_wr_access_reg => s_axi_wready,
      dest_out => error_bus_rt_0,
      dest_rst => axis_resetn_rt_0,
      done_flag => \^done_flag\,
      enable_reg => rfadc_exdes_ctrl_i_n_8,
      error_flag => \^error_flag\,
      s00_ds_status => s00_ds_status,
      s00_tdata(127 downto 0) => s00_tdata(127 downto 0),
      s00_tready => s00_tready,
      s0_axis_clock => s0_axis_clock,
      s_axi_aclk => s_axi_aclk,
      s_axi_araddr(15 downto 0) => s_axi_araddr(15 downto 0),
      s_axi_aresetn => s_axi_aresetn,
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awaddr(15 downto 0) => s_axi_awaddr(15 downto 0),
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bready => s_axi_bready,
      s_axi_bresp(0) => s_axi_bresp(0),
      s_axi_rdata(15 downto 0) => s_axi_rdata(15 downto 0),
      s_axi_rready => s_axi_rready,
      s_axi_rresp(0) => s_axi_rresp(0),
      s_axi_wdata(11 downto 0) => s_axi_wdata(11 downto 0),
      s_axi_wvalid => s_axi_wvalid
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 17 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 17 downto 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    s00_tdata : in STD_LOGIC_VECTOR ( 127 downto 0 );
    s00_tvalid : in STD_LOGIC;
    s00_tready : out STD_LOGIC;
    s0_axis_clock : in STD_LOGIC;
    error_flag : out STD_LOGIC;
    done_flag : out STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "project_1_adc_sink_i_0,exdes_rfadc_data_sink,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "exdes_rfadc_data_sink,Vivado 2020.1";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  signal \<const0>\ : STD_LOGIC;
  signal \^s_axi_bresp\ : STD_LOGIC_VECTOR ( 1 to 1 );
  signal \^s_axi_rdata\ : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal \^s_axi_rresp\ : STD_LOGIC_VECTOR ( 1 to 1 );
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of s00_tready : signal is "xilinx.com:interface:axis:1.0 s00 TREADY";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of s00_tready : signal is "XIL_INTERFACENAME s00, TDATA_NUM_BYTES 16, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 0, FREQ_HZ 100000000, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s00_tvalid : signal is "xilinx.com:interface:axis:1.0 s00 TVALID";
  attribute X_INTERFACE_INFO of s0_axis_clock : signal is "xilinx.com:signal:clock:1.0 s0_axis_clock CLK";
  attribute X_INTERFACE_PARAMETER of s0_axis_clock : signal is "XIL_INTERFACENAME s0_axis_clock, ASSOCIATED_BUSIF s00, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_aclk : signal is "xilinx.com:signal:clock:1.0 s_axi_aclk CLK";
  attribute X_INTERFACE_PARAMETER of s_axi_aclk : signal is "XIL_INTERFACENAME s_axi_aclk, ASSOCIATED_BUSIF s_axi, ASSOCIATED_RESET s_axi_aresetn, FREQ_HZ 99999001, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN project_1_PS_0_0_pl_clk0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_aresetn : signal is "xilinx.com:signal:reset:1.0 s_axi_aresetn RST";
  attribute X_INTERFACE_PARAMETER of s_axi_aresetn : signal is "XIL_INTERFACENAME s_axi_aresetn, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_arready : signal is "xilinx.com:interface:aximm:1.0 s_axi ARREADY";
  attribute X_INTERFACE_INFO of s_axi_arvalid : signal is "xilinx.com:interface:aximm:1.0 s_axi ARVALID";
  attribute X_INTERFACE_INFO of s_axi_awready : signal is "xilinx.com:interface:aximm:1.0 s_axi AWREADY";
  attribute X_INTERFACE_INFO of s_axi_awvalid : signal is "xilinx.com:interface:aximm:1.0 s_axi AWVALID";
  attribute X_INTERFACE_INFO of s_axi_bready : signal is "xilinx.com:interface:aximm:1.0 s_axi BREADY";
  attribute X_INTERFACE_INFO of s_axi_bvalid : signal is "xilinx.com:interface:aximm:1.0 s_axi BVALID";
  attribute X_INTERFACE_INFO of s_axi_rready : signal is "xilinx.com:interface:aximm:1.0 s_axi RREADY";
  attribute X_INTERFACE_PARAMETER of s_axi_rready : signal is "XIL_INTERFACENAME s_axi, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 99999001, ID_WIDTH 0, ADDR_WIDTH 18, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN project_1_PS_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_rvalid : signal is "xilinx.com:interface:aximm:1.0 s_axi RVALID";
  attribute X_INTERFACE_INFO of s_axi_wready : signal is "xilinx.com:interface:aximm:1.0 s_axi WREADY";
  attribute X_INTERFACE_INFO of s_axi_wvalid : signal is "xilinx.com:interface:aximm:1.0 s_axi WVALID";
  attribute X_INTERFACE_INFO of s00_tdata : signal is "xilinx.com:interface:axis:1.0 s00 TDATA";
  attribute X_INTERFACE_INFO of s_axi_araddr : signal is "xilinx.com:interface:aximm:1.0 s_axi ARADDR";
  attribute X_INTERFACE_INFO of s_axi_awaddr : signal is "xilinx.com:interface:aximm:1.0 s_axi AWADDR";
  attribute X_INTERFACE_INFO of s_axi_bresp : signal is "xilinx.com:interface:aximm:1.0 s_axi BRESP";
  attribute X_INTERFACE_INFO of s_axi_rdata : signal is "xilinx.com:interface:aximm:1.0 s_axi RDATA";
  attribute X_INTERFACE_INFO of s_axi_rresp : signal is "xilinx.com:interface:aximm:1.0 s_axi RRESP";
  attribute X_INTERFACE_INFO of s_axi_wdata : signal is "xilinx.com:interface:aximm:1.0 s_axi WDATA";
  attribute X_INTERFACE_INFO of s_axi_wstrb : signal is "xilinx.com:interface:aximm:1.0 s_axi WSTRB";
begin
  s_axi_bresp(1) <= \^s_axi_bresp\(1);
  s_axi_bresp(0) <= \<const0>\;
  s_axi_rdata(31) <= \<const0>\;
  s_axi_rdata(30) <= \<const0>\;
  s_axi_rdata(29) <= \<const0>\;
  s_axi_rdata(28) <= \<const0>\;
  s_axi_rdata(27) <= \<const0>\;
  s_axi_rdata(26) <= \<const0>\;
  s_axi_rdata(25) <= \<const0>\;
  s_axi_rdata(24) <= \<const0>\;
  s_axi_rdata(23) <= \<const0>\;
  s_axi_rdata(22) <= \<const0>\;
  s_axi_rdata(21) <= \<const0>\;
  s_axi_rdata(20) <= \<const0>\;
  s_axi_rdata(19) <= \<const0>\;
  s_axi_rdata(18) <= \<const0>\;
  s_axi_rdata(17) <= \<const0>\;
  s_axi_rdata(16) <= \<const0>\;
  s_axi_rdata(15 downto 0) <= \^s_axi_rdata\(15 downto 0);
  s_axi_rresp(1) <= \^s_axi_rresp\(1);
  s_axi_rresp(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_exdes_rfadc_data_sink
     port map (
      axi_awready_reg => s_axi_awready,
      axi_bvalid_reg => s_axi_bvalid,
      axi_rvalid_reg => s_axi_rvalid,
      done_flag => done_flag,
      error_flag => error_flag,
      s00_tdata(127 downto 0) => s00_tdata(127 downto 0),
      s00_tready => s00_tready,
      s0_axis_clock => s0_axis_clock,
      s_axi_aclk => s_axi_aclk,
      s_axi_araddr(15 downto 0) => s_axi_araddr(17 downto 2),
      s_axi_aresetn => s_axi_aresetn,
      s_axi_arready => s_axi_arready,
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awaddr(15 downto 0) => s_axi_awaddr(17 downto 2),
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bready => s_axi_bready,
      s_axi_bresp(0) => \^s_axi_bresp\(1),
      s_axi_rdata(15 downto 0) => \^s_axi_rdata\(15 downto 0),
      s_axi_rready => s_axi_rready,
      s_axi_rresp(0) => \^s_axi_rresp\(1),
      s_axi_wdata(11 downto 0) => s_axi_wdata(11 downto 0),
      s_axi_wready => s_axi_wready,
      s_axi_wvalid => s_axi_wvalid
    );
end STRUCTURE;
