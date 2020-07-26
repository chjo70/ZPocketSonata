-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
-- Date        : Thu May 28 07:46:26 2020
-- Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
-- Command     : write_vhdl -force -mode funcsim -rename_top project_1_enc_ip_mon_0 -prefix
--               project_1_enc_ip_mon_0_ project_1_dec_ip_mon_0_sim_netlist.vhdl
-- Design      : project_1_dec_ip_mon_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu28dr-ffvg1517-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity project_1_enc_ip_mon_0_monitor_CNTRL_s_axi is
  port (
    ap_rst_n_inv : out STD_LOGIC;
    \FSM_onehot_rstate_reg[1]_0\ : out STD_LOGIC;
    s_axi_CNTRL_RVALID : out STD_LOGIC;
    \FSM_onehot_wstate_reg[1]_0\ : out STD_LOGIC;
    \FSM_onehot_wstate_reg[2]_0\ : out STD_LOGIC;
    interrupt : out STD_LOGIC;
    \ap_CS_fsm_reg[0]\ : out STD_LOGIC;
    t_V_1_fu_68 : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    D : out STD_LOGIC_VECTOR ( 1 downto 0 );
    int_ap_start_reg_0 : out STD_LOGIC;
    s_axi_CNTRL_BVALID : out STD_LOGIC;
    \int_num_blocks_V_reg[31]_0\ : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CNTRL_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    ap_clk : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_CNTRL_ARVALID : in STD_LOGIC;
    s_axi_CNTRL_RREADY : in STD_LOGIC;
    s_axi_CNTRL_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_CNTRL_AWVALID : in STD_LOGIC;
    s_axi_CNTRL_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CNTRL_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_CNTRL_WVALID : in STD_LOGIC;
    CO : in STD_LOGIC_VECTOR ( 0 to 0 );
    tready_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    tvalid_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    tlast_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    p_s_fu_60 : in STD_LOGIC;
    s_axi_CNTRL_BREADY : in STD_LOGIC;
    rtc_V : in STD_LOGIC_VECTOR ( 31 downto 0 );
    first_V_preg : in STD_LOGIC_VECTOR ( 31 downto 0 );
    ap_rst_n_cntrl_aclk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    cntrl_aclk : in STD_LOGIC;
    s_axi_CNTRL_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    \int_last_V_reg[31]_0\ : in STD_LOGIC_VECTOR ( 31 downto 0 );
    \int_stalled_V_reg[31]_0\ : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
end project_1_enc_ip_mon_0_monitor_CNTRL_s_axi;

architecture STRUCTURE of project_1_enc_ip_mon_0_monitor_CNTRL_s_axi is
  signal \^e\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \FSM_onehot_rstate[1]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_rstate[2]_i_1_n_0\ : STD_LOGIC;
  signal \^fsm_onehot_rstate_reg[1]_0\ : STD_LOGIC;
  signal \FSM_onehot_wstate[1]_i_2_n_0\ : STD_LOGIC;
  signal \FSM_onehot_wstate[2]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_wstate[3]_i_1_n_0\ : STD_LOGIC;
  signal \^fsm_onehot_wstate_reg[1]_0\ : STD_LOGIC;
  signal \^fsm_onehot_wstate_reg[2]_0\ : STD_LOGIC;
  signal ap_done_ext : STD_LOGIC;
  signal ap_done_get : STD_LOGIC;
  signal ap_idle : STD_LOGIC;
  signal ap_rst_n_cntrl_aclk_inv : STD_LOGIC;
  signal \^ap_rst_n_inv\ : STD_LOGIC;
  signal ap_start : STD_LOGIC;
  signal ap_start_mask : STD_LOGIC;
  signal ap_start_mask_i_3_n_0 : STD_LOGIC;
  signal ap_start_set : STD_LOGIC;
  signal ar_hs : STD_LOGIC;
  signal first_V : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal int_ap_done : STD_LOGIC;
  signal int_ap_done_i_1_n_0 : STD_LOGIC;
  signal int_ap_idle : STD_LOGIC;
  signal int_ap_ready : STD_LOGIC;
  signal int_ap_start0 : STD_LOGIC;
  signal int_ap_start_i_1_n_0 : STD_LOGIC;
  signal int_auto_restart : STD_LOGIC;
  signal int_auto_restart_i_1_n_0 : STD_LOGIC;
  signal int_first_V : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal int_gie : STD_LOGIC;
  signal int_gie_i_1_n_0 : STD_LOGIC;
  signal int_ier0 : STD_LOGIC;
  signal \int_ier_reg_n_0_[0]\ : STD_LOGIC;
  signal \int_isr[0]_i_1_n_0\ : STD_LOGIC;
  signal \int_isr[1]_i_1_n_0\ : STD_LOGIC;
  signal int_isr_reg02_out : STD_LOGIC;
  signal \int_isr_reg_n_0_[0]\ : STD_LOGIC;
  signal int_last_V : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \int_num_blocks_V[0]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[10]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[11]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[12]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[13]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[14]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[15]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[16]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[17]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[18]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[19]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[1]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[20]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[21]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[22]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[23]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[24]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[25]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[26]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[27]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[28]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[29]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[2]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[30]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[31]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[31]_i_2_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[31]_i_3_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[3]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[4]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[5]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[6]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[7]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[8]_i_1_n_0\ : STD_LOGIC;
  signal \int_num_blocks_V[9]_i_1_n_0\ : STD_LOGIC;
  signal \^int_num_blocks_v_reg[31]_0\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal int_stalled_V : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal isr_mask : STD_LOGIC;
  signal isr_toggle : STD_LOGIC;
  signal p_0_in : STD_LOGIC;
  signal p_1_in : STD_LOGIC;
  signal p_2_in : STD_LOGIC;
  signal rdata : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \rdata[0]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[0]_i_3_n_0\ : STD_LOGIC;
  signal \rdata[0]_i_4_n_0\ : STD_LOGIC;
  signal \rdata[0]_i_5_n_0\ : STD_LOGIC;
  signal \rdata[10]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[11]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[12]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[13]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[14]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[15]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[16]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[17]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[18]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[19]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[1]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[1]_i_3_n_0\ : STD_LOGIC;
  signal \rdata[1]_i_4_n_0\ : STD_LOGIC;
  signal \rdata[1]_i_5_n_0\ : STD_LOGIC;
  signal \rdata[1]_i_6_n_0\ : STD_LOGIC;
  signal \rdata[20]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[21]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[22]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[23]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[24]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[25]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[26]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[27]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[28]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[29]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[2]_i_2_n_0\ : STD_LOGIC;
  signal \rdata[2]_i_3_n_0\ : STD_LOGIC;
  signal \rdata[30]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[31]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[31]_i_3_n_0\ : STD_LOGIC;
  signal \rdata[3]_i_2_n_0\ : STD_LOGIC;
  signal \rdata[3]_i_3_n_0\ : STD_LOGIC;
  signal \rdata[4]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[5]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[6]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[7]_i_2_n_0\ : STD_LOGIC;
  signal \rdata[7]_i_3_n_0\ : STD_LOGIC;
  signal \rdata[8]_i_1_n_0\ : STD_LOGIC;
  signal \rdata[9]_i_1_n_0\ : STD_LOGIC;
  signal \rdata_reg[0]_i_2_n_0\ : STD_LOGIC;
  signal \rdata_reg[1]_i_2_n_0\ : STD_LOGIC;
  signal \^s_axi_cntrl_bvalid\ : STD_LOGIC;
  signal \^s_axi_cntrl_rvalid\ : STD_LOGIC;
  signal waddr : STD_LOGIC;
  signal \waddr_reg_n_0_[0]\ : STD_LOGIC;
  signal \waddr_reg_n_0_[1]\ : STD_LOGIC;
  signal \waddr_reg_n_0_[2]\ : STD_LOGIC;
  signal \waddr_reg_n_0_[3]\ : STD_LOGIC;
  signal \waddr_reg_n_0_[4]\ : STD_LOGIC;
  signal \waddr_reg_n_0_[5]\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \FSM_onehot_rstate[1]_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \FSM_onehot_rstate[2]_i_1\ : label is "soft_lutpair5";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_rstate_reg[1]\ : label is "RDIDLE:010,RDDATA:100,iSTATE:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_rstate_reg[2]\ : label is "RDIDLE:010,RDDATA:100,iSTATE:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_wstate_reg[1]\ : label is "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_wstate_reg[2]\ : label is "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_wstate_reg[3]\ : label is "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001";
  attribute SOFT_HLUTNM of \ap_CS_fsm[0]_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \ap_CS_fsm[1]_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of int_ap_start_i_1 : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \int_isr[0]_i_2\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \int_num_blocks_V[0]_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \int_num_blocks_V[10]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \int_num_blocks_V[11]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \int_num_blocks_V[12]_i_1\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \int_num_blocks_V[13]_i_1\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \int_num_blocks_V[14]_i_1\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \int_num_blocks_V[15]_i_1\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \int_num_blocks_V[16]_i_1\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \int_num_blocks_V[17]_i_1\ : label is "soft_lutpair14";
  attribute SOFT_HLUTNM of \int_num_blocks_V[18]_i_1\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \int_num_blocks_V[19]_i_1\ : label is "soft_lutpair15";
  attribute SOFT_HLUTNM of \int_num_blocks_V[1]_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of \int_num_blocks_V[20]_i_1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \int_num_blocks_V[21]_i_1\ : label is "soft_lutpair16";
  attribute SOFT_HLUTNM of \int_num_blocks_V[22]_i_1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \int_num_blocks_V[23]_i_1\ : label is "soft_lutpair17";
  attribute SOFT_HLUTNM of \int_num_blocks_V[24]_i_1\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \int_num_blocks_V[25]_i_1\ : label is "soft_lutpair18";
  attribute SOFT_HLUTNM of \int_num_blocks_V[26]_i_1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \int_num_blocks_V[27]_i_1\ : label is "soft_lutpair19";
  attribute SOFT_HLUTNM of \int_num_blocks_V[28]_i_1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \int_num_blocks_V[29]_i_1\ : label is "soft_lutpair20";
  attribute SOFT_HLUTNM of \int_num_blocks_V[2]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \int_num_blocks_V[30]_i_1\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \int_num_blocks_V[31]_i_2\ : label is "soft_lutpair21";
  attribute SOFT_HLUTNM of \int_num_blocks_V[3]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \int_num_blocks_V[4]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \int_num_blocks_V[5]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \int_num_blocks_V[6]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \int_num_blocks_V[7]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \int_num_blocks_V[8]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \int_num_blocks_V[9]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of isr_mask_i_1 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \num_blocks_V_read_reg_237[31]_i_1\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \rdata[0]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \rdata[0]_i_3\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \rdata[1]_i_3\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \rdata[1]_i_4\ : label is "soft_lutpair2";
begin
  E(0) <= \^e\(0);
  \FSM_onehot_rstate_reg[1]_0\ <= \^fsm_onehot_rstate_reg[1]_0\;
  \FSM_onehot_wstate_reg[1]_0\ <= \^fsm_onehot_wstate_reg[1]_0\;
  \FSM_onehot_wstate_reg[2]_0\ <= \^fsm_onehot_wstate_reg[2]_0\;
  ap_rst_n_inv <= \^ap_rst_n_inv\;
  \int_num_blocks_V_reg[31]_0\(31 downto 0) <= \^int_num_blocks_v_reg[31]_0\(31 downto 0);
  s_axi_CNTRL_BVALID <= \^s_axi_cntrl_bvalid\;
  s_axi_CNTRL_RVALID <= \^s_axi_cntrl_rvalid\;
\FSM_onehot_rstate[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"F747"
    )
        port map (
      I0 => s_axi_CNTRL_ARVALID,
      I1 => \^fsm_onehot_rstate_reg[1]_0\,
      I2 => \^s_axi_cntrl_rvalid\,
      I3 => s_axi_CNTRL_RREADY,
      O => \FSM_onehot_rstate[1]_i_1_n_0\
    );
\FSM_onehot_rstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => s_axi_CNTRL_ARVALID,
      I1 => \^fsm_onehot_rstate_reg[1]_0\,
      I2 => s_axi_CNTRL_RREADY,
      I3 => \^s_axi_cntrl_rvalid\,
      O => \FSM_onehot_rstate[2]_i_1_n_0\
    );
\FSM_onehot_rstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => cntrl_aclk,
      CE => '1',
      D => \FSM_onehot_rstate[1]_i_1_n_0\,
      Q => \^fsm_onehot_rstate_reg[1]_0\,
      R => \^ap_rst_n_inv\
    );
\FSM_onehot_rstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => cntrl_aclk,
      CE => '1',
      D => \FSM_onehot_rstate[2]_i_1_n_0\,
      Q => \^s_axi_cntrl_rvalid\,
      R => \^ap_rst_n_inv\
    );
\FSM_onehot_wstate[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => ap_rst_n,
      O => \^ap_rst_n_inv\
    );
\FSM_onehot_wstate[1]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"888BFF8B"
    )
        port map (
      I0 => s_axi_CNTRL_BREADY,
      I1 => \^s_axi_cntrl_bvalid\,
      I2 => \^fsm_onehot_wstate_reg[2]_0\,
      I3 => \^fsm_onehot_wstate_reg[1]_0\,
      I4 => s_axi_CNTRL_AWVALID,
      O => \FSM_onehot_wstate[1]_i_2_n_0\
    );
\FSM_onehot_wstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => s_axi_CNTRL_AWVALID,
      I1 => \^fsm_onehot_wstate_reg[1]_0\,
      I2 => s_axi_CNTRL_WVALID,
      I3 => \^fsm_onehot_wstate_reg[2]_0\,
      O => \FSM_onehot_wstate[2]_i_1_n_0\
    );
\FSM_onehot_wstate[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => s_axi_CNTRL_WVALID,
      I1 => \^fsm_onehot_wstate_reg[2]_0\,
      I2 => s_axi_CNTRL_BREADY,
      I3 => \^s_axi_cntrl_bvalid\,
      O => \FSM_onehot_wstate[3]_i_1_n_0\
    );
\FSM_onehot_wstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => cntrl_aclk,
      CE => '1',
      D => \FSM_onehot_wstate[1]_i_2_n_0\,
      Q => \^fsm_onehot_wstate_reg[1]_0\,
      R => \^ap_rst_n_inv\
    );
\FSM_onehot_wstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => cntrl_aclk,
      CE => '1',
      D => \FSM_onehot_wstate[2]_i_1_n_0\,
      Q => \^fsm_onehot_wstate_reg[2]_0\,
      R => \^ap_rst_n_inv\
    );
\FSM_onehot_wstate_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => cntrl_aclk,
      CE => '1',
      D => \FSM_onehot_wstate[3]_i_1_n_0\,
      Q => \^s_axi_cntrl_bvalid\,
      R => \^ap_rst_n_inv\
    );
\ap_CS_fsm[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4555"
    )
        port map (
      I0 => Q(1),
      I1 => Q(2),
      I2 => ap_start,
      I3 => Q(0),
      O => D(0)
    );
\ap_CS_fsm[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"DDC0"
    )
        port map (
      I0 => CO(0),
      I1 => Q(0),
      I2 => ap_start,
      I3 => Q(1),
      O => D(1)
    );
ap_done_ext_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000002"
    )
        port map (
      I0 => ar_hs,
      I1 => s_axi_CNTRL_ARADDR(2),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \rdata[1]_i_4_n_0\,
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => s_axi_CNTRL_ARADDR(5),
      O => ap_done_get
    );
ap_done_ext_reg: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => '1',
      D => ap_done_get,
      Q => ap_done_ext,
      R => ap_rst_n_cntrl_aclk_inv
    );
ap_start_mask_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => ap_rst_n_cntrl_aclk,
      O => ap_rst_n_cntrl_aclk_inv
    );
ap_start_mask_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00200000"
    )
        port map (
      I0 => s_axi_CNTRL_WSTRB(0),
      I1 => \waddr_reg_n_0_[3]\,
      I2 => ap_start_mask_i_3_n_0,
      I3 => \waddr_reg_n_0_[2]\,
      I4 => s_axi_CNTRL_WDATA(0),
      O => ap_start_set
    );
ap_start_mask_i_3: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000001000"
    )
        port map (
      I0 => \waddr_reg_n_0_[4]\,
      I1 => \waddr_reg_n_0_[1]\,
      I2 => \^fsm_onehot_wstate_reg[2]_0\,
      I3 => s_axi_CNTRL_WVALID,
      I4 => \waddr_reg_n_0_[5]\,
      I5 => \waddr_reg_n_0_[0]\,
      O => ap_start_mask_i_3_n_0
    );
ap_start_mask_reg: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => '1',
      D => ap_start_set,
      Q => ap_start_mask,
      R => ap_rst_n_cntrl_aclk_inv
    );
int_ap_done_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"EFAA"
    )
        port map (
      I0 => Q(2),
      I1 => ap_done_get,
      I2 => ap_done_ext,
      I3 => int_ap_done,
      O => int_ap_done_i_1_n_0
    );
int_ap_done_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_ap_done_i_1_n_0,
      Q => int_ap_done,
      R => ap_rst_n_cntrl_aclk_inv
    );
int_ap_idle_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Q(0),
      I1 => ap_start,
      O => ap_idle
    );
int_ap_idle_reg: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => '1',
      D => ap_idle,
      Q => int_ap_idle,
      R => \^ap_rst_n_inv\
    );
int_ap_ready_reg: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => '1',
      D => Q(2),
      Q => int_ap_ready,
      R => \^ap_rst_n_inv\
    );
int_ap_start_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FBF8"
    )
        port map (
      I0 => int_auto_restart,
      I1 => Q(2),
      I2 => int_ap_start0,
      I3 => ap_start,
      O => int_ap_start_i_1_n_0
    );
int_ap_start_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000200000"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(0),
      I1 => \waddr_reg_n_0_[2]\,
      I2 => ap_start_mask_i_3_n_0,
      I3 => \waddr_reg_n_0_[3]\,
      I4 => s_axi_CNTRL_WSTRB(0),
      I5 => ap_start_mask,
      O => int_ap_start0
    );
int_ap_start_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_ap_start_i_1_n_0,
      Q => ap_start,
      R => ap_rst_n_cntrl_aclk_inv
    );
int_auto_restart_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFEFFFFF00200000"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(7),
      I1 => \waddr_reg_n_0_[2]\,
      I2 => ap_start_mask_i_3_n_0,
      I3 => \waddr_reg_n_0_[3]\,
      I4 => s_axi_CNTRL_WSTRB(0),
      I5 => int_auto_restart,
      O => int_auto_restart_i_1_n_0
    );
int_auto_restart_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_auto_restart_i_1_n_0,
      Q => int_auto_restart,
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(0),
      I1 => first_V_preg(0),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(0)
    );
\int_first_V[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(10),
      I1 => first_V_preg(10),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(10)
    );
\int_first_V[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(11),
      I1 => first_V_preg(11),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(11)
    );
\int_first_V[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(12),
      I1 => first_V_preg(12),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(12)
    );
\int_first_V[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(13),
      I1 => first_V_preg(13),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(13)
    );
\int_first_V[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(14),
      I1 => first_V_preg(14),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(14)
    );
\int_first_V[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(15),
      I1 => first_V_preg(15),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(15)
    );
\int_first_V[16]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(16),
      I1 => first_V_preg(16),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(16)
    );
\int_first_V[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(17),
      I1 => first_V_preg(17),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(17)
    );
\int_first_V[18]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(18),
      I1 => first_V_preg(18),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(18)
    );
\int_first_V[19]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(19),
      I1 => first_V_preg(19),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(19)
    );
\int_first_V[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(1),
      I1 => first_V_preg(1),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(1)
    );
\int_first_V[20]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(20),
      I1 => first_V_preg(20),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(20)
    );
\int_first_V[21]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(21),
      I1 => first_V_preg(21),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(21)
    );
\int_first_V[22]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(22),
      I1 => first_V_preg(22),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(22)
    );
\int_first_V[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(23),
      I1 => first_V_preg(23),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(23)
    );
\int_first_V[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(24),
      I1 => first_V_preg(24),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(24)
    );
\int_first_V[25]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(25),
      I1 => first_V_preg(25),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(25)
    );
\int_first_V[26]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(26),
      I1 => first_V_preg(26),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(26)
    );
\int_first_V[27]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(27),
      I1 => first_V_preg(27),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(27)
    );
\int_first_V[28]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(28),
      I1 => first_V_preg(28),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(28)
    );
\int_first_V[29]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(29),
      I1 => first_V_preg(29),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(29)
    );
\int_first_V[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(2),
      I1 => first_V_preg(2),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(2)
    );
\int_first_V[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(30),
      I1 => first_V_preg(30),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(30)
    );
\int_first_V[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(31),
      I1 => first_V_preg(31),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(31)
    );
\int_first_V[31]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"80"
    )
        port map (
      I0 => tready_V(0),
      I1 => tvalid_V(0),
      I2 => tlast_V(0),
      O => p_2_in
    );
\int_first_V[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(3),
      I1 => first_V_preg(3),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(3)
    );
\int_first_V[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(4),
      I1 => first_V_preg(4),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(4)
    );
\int_first_V[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(5),
      I1 => first_V_preg(5),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(5)
    );
\int_first_V[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(6),
      I1 => first_V_preg(6),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(6)
    );
\int_first_V[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(7),
      I1 => first_V_preg(7),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(7)
    );
\int_first_V[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(8),
      I1 => first_V_preg(8),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(8)
    );
\int_first_V[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CACCCCCCCCCCCCCC"
    )
        port map (
      I0 => rtc_V(9),
      I1 => first_V_preg(9),
      I2 => CO(0),
      I3 => Q(1),
      I4 => p_2_in,
      I5 => p_s_fu_60,
      O => first_V(9)
    );
\int_first_V_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(0),
      Q => int_first_V(0),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(10),
      Q => int_first_V(10),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(11),
      Q => int_first_V(11),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(12),
      Q => int_first_V(12),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(13),
      Q => int_first_V(13),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(14),
      Q => int_first_V(14),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(15),
      Q => int_first_V(15),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(16),
      Q => int_first_V(16),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(17),
      Q => int_first_V(17),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(18),
      Q => int_first_V(18),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(19),
      Q => int_first_V(19),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(1),
      Q => int_first_V(1),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(20),
      Q => int_first_V(20),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(21),
      Q => int_first_V(21),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(22),
      Q => int_first_V(22),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(23),
      Q => int_first_V(23),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(24),
      Q => int_first_V(24),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(25),
      Q => int_first_V(25),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(26),
      Q => int_first_V(26),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(27),
      Q => int_first_V(27),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(28),
      Q => int_first_V(28),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(29),
      Q => int_first_V(29),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(2),
      Q => int_first_V(2),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(30),
      Q => int_first_V(30),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(31),
      Q => int_first_V(31),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(3),
      Q => int_first_V(3),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(4),
      Q => int_first_V(4),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(5),
      Q => int_first_V(5),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(6),
      Q => int_first_V(6),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(7),
      Q => int_first_V(7),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(8),
      Q => int_first_V(8),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_first_V_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => first_V(9),
      Q => int_first_V(9),
      R => ap_rst_n_cntrl_aclk_inv
    );
int_gie_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FBFFFFFF08000000"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(0),
      I1 => ap_start_mask_i_3_n_0,
      I2 => \waddr_reg_n_0_[3]\,
      I3 => \waddr_reg_n_0_[2]\,
      I4 => s_axi_CNTRL_WSTRB(0),
      I5 => int_gie,
      O => int_gie_i_1_n_0
    );
int_gie_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_gie_i_1_n_0,
      Q => int_gie,
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_ier[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"4000"
    )
        port map (
      I0 => \waddr_reg_n_0_[2]\,
      I1 => \waddr_reg_n_0_[3]\,
      I2 => ap_start_mask_i_3_n_0,
      I3 => s_axi_CNTRL_WSTRB(0),
      O => int_ier0
    );
\int_ier_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => int_ier0,
      D => s_axi_CNTRL_WDATA(0),
      Q => \int_ier_reg_n_0_[0]\,
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_ier_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => int_ier0,
      D => s_axi_CNTRL_WDATA(1),
      Q => p_0_in,
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_isr[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F777F888"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(0),
      I1 => int_isr_reg02_out,
      I2 => Q(2),
      I3 => \int_ier_reg_n_0_[0]\,
      I4 => \int_isr_reg_n_0_[0]\,
      O => \int_isr[0]_i_1_n_0\
    );
\int_isr[0]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00008000"
    )
        port map (
      I0 => s_axi_CNTRL_WSTRB(0),
      I1 => \waddr_reg_n_0_[2]\,
      I2 => ap_start_mask_i_3_n_0,
      I3 => \waddr_reg_n_0_[3]\,
      I4 => isr_mask,
      O => int_isr_reg02_out
    );
\int_isr[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F777F888"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(1),
      I1 => int_isr_reg02_out,
      I2 => Q(2),
      I3 => p_0_in,
      I4 => p_1_in,
      O => \int_isr[1]_i_1_n_0\
    );
\int_isr_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_isr[0]_i_1_n_0\,
      Q => \int_isr_reg_n_0_[0]\,
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_isr_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_isr[1]_i_1_n_0\,
      Q => p_1_in,
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(0),
      Q => int_last_V(0),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(10),
      Q => int_last_V(10),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(11),
      Q => int_last_V(11),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(12),
      Q => int_last_V(12),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(13),
      Q => int_last_V(13),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(14),
      Q => int_last_V(14),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(15),
      Q => int_last_V(15),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(16),
      Q => int_last_V(16),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(17),
      Q => int_last_V(17),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(18),
      Q => int_last_V(18),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(19),
      Q => int_last_V(19),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(1),
      Q => int_last_V(1),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(20),
      Q => int_last_V(20),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(21),
      Q => int_last_V(21),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(22),
      Q => int_last_V(22),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(23),
      Q => int_last_V(23),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(24),
      Q => int_last_V(24),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(25),
      Q => int_last_V(25),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(26),
      Q => int_last_V(26),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(27),
      Q => int_last_V(27),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(28),
      Q => int_last_V(28),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(29),
      Q => int_last_V(29),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(2),
      Q => int_last_V(2),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(30),
      Q => int_last_V(30),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(31),
      Q => int_last_V(31),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(3),
      Q => int_last_V(3),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(4),
      Q => int_last_V(4),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(5),
      Q => int_last_V(5),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(6),
      Q => int_last_V(6),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(7),
      Q => int_last_V(7),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(8),
      Q => int_last_V(8),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_last_V_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_last_V_reg[31]_0\(9),
      Q => int_last_V(9),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(0),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(0),
      O => \int_num_blocks_V[0]_i_1_n_0\
    );
\int_num_blocks_V[10]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(10),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(10),
      O => \int_num_blocks_V[10]_i_1_n_0\
    );
\int_num_blocks_V[11]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(11),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(11),
      O => \int_num_blocks_V[11]_i_1_n_0\
    );
\int_num_blocks_V[12]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(12),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(12),
      O => \int_num_blocks_V[12]_i_1_n_0\
    );
\int_num_blocks_V[13]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(13),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(13),
      O => \int_num_blocks_V[13]_i_1_n_0\
    );
\int_num_blocks_V[14]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(14),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(14),
      O => \int_num_blocks_V[14]_i_1_n_0\
    );
\int_num_blocks_V[15]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(15),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(15),
      O => \int_num_blocks_V[15]_i_1_n_0\
    );
\int_num_blocks_V[16]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(16),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(16),
      O => \int_num_blocks_V[16]_i_1_n_0\
    );
\int_num_blocks_V[17]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(17),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(17),
      O => \int_num_blocks_V[17]_i_1_n_0\
    );
\int_num_blocks_V[18]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(18),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(18),
      O => \int_num_blocks_V[18]_i_1_n_0\
    );
\int_num_blocks_V[19]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(19),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(19),
      O => \int_num_blocks_V[19]_i_1_n_0\
    );
\int_num_blocks_V[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(1),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(1),
      O => \int_num_blocks_V[1]_i_1_n_0\
    );
\int_num_blocks_V[20]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(20),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(20),
      O => \int_num_blocks_V[20]_i_1_n_0\
    );
\int_num_blocks_V[21]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(21),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(21),
      O => \int_num_blocks_V[21]_i_1_n_0\
    );
\int_num_blocks_V[22]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(22),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(22),
      O => \int_num_blocks_V[22]_i_1_n_0\
    );
\int_num_blocks_V[23]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(23),
      I1 => s_axi_CNTRL_WSTRB(2),
      I2 => \^int_num_blocks_v_reg[31]_0\(23),
      O => \int_num_blocks_V[23]_i_1_n_0\
    );
\int_num_blocks_V[24]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(24),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(24),
      O => \int_num_blocks_V[24]_i_1_n_0\
    );
\int_num_blocks_V[25]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(25),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(25),
      O => \int_num_blocks_V[25]_i_1_n_0\
    );
\int_num_blocks_V[26]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(26),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(26),
      O => \int_num_blocks_V[26]_i_1_n_0\
    );
\int_num_blocks_V[27]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(27),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(27),
      O => \int_num_blocks_V[27]_i_1_n_0\
    );
\int_num_blocks_V[28]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(28),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(28),
      O => \int_num_blocks_V[28]_i_1_n_0\
    );
\int_num_blocks_V[29]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(29),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(29),
      O => \int_num_blocks_V[29]_i_1_n_0\
    );
\int_num_blocks_V[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(2),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(2),
      O => \int_num_blocks_V[2]_i_1_n_0\
    );
\int_num_blocks_V[30]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(30),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(30),
      O => \int_num_blocks_V[30]_i_1_n_0\
    );
\int_num_blocks_V[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0010"
    )
        port map (
      I0 => \waddr_reg_n_0_[3]\,
      I1 => \waddr_reg_n_0_[2]\,
      I2 => \waddr_reg_n_0_[4]\,
      I3 => \int_num_blocks_V[31]_i_3_n_0\,
      O => \int_num_blocks_V[31]_i_1_n_0\
    );
\int_num_blocks_V[31]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(31),
      I1 => s_axi_CNTRL_WSTRB(3),
      I2 => \^int_num_blocks_v_reg[31]_0\(31),
      O => \int_num_blocks_V[31]_i_2_n_0\
    );
\int_num_blocks_V[31]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFEFFF"
    )
        port map (
      I0 => \waddr_reg_n_0_[0]\,
      I1 => \waddr_reg_n_0_[5]\,
      I2 => s_axi_CNTRL_WVALID,
      I3 => \^fsm_onehot_wstate_reg[2]_0\,
      I4 => \waddr_reg_n_0_[1]\,
      O => \int_num_blocks_V[31]_i_3_n_0\
    );
\int_num_blocks_V[3]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(3),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(3),
      O => \int_num_blocks_V[3]_i_1_n_0\
    );
\int_num_blocks_V[4]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(4),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(4),
      O => \int_num_blocks_V[4]_i_1_n_0\
    );
\int_num_blocks_V[5]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(5),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(5),
      O => \int_num_blocks_V[5]_i_1_n_0\
    );
\int_num_blocks_V[6]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(6),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(6),
      O => \int_num_blocks_V[6]_i_1_n_0\
    );
\int_num_blocks_V[7]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(7),
      I1 => s_axi_CNTRL_WSTRB(0),
      I2 => \^int_num_blocks_v_reg[31]_0\(7),
      O => \int_num_blocks_V[7]_i_1_n_0\
    );
\int_num_blocks_V[8]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(8),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(8),
      O => \int_num_blocks_V[8]_i_1_n_0\
    );
\int_num_blocks_V[9]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_CNTRL_WDATA(9),
      I1 => s_axi_CNTRL_WSTRB(1),
      I2 => \^int_num_blocks_v_reg[31]_0\(9),
      O => \int_num_blocks_V[9]_i_1_n_0\
    );
\int_num_blocks_V_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[0]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(0),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[10]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(10),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[11]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(11),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[12]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(12),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[13]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(13),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[14]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(14),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[15]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(15),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[16]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(16),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[17]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(17),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[18]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(18),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[19]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(19),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[1]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(1),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[20]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(20),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[21]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(21),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[22]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(22),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[23]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(23),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[24]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(24),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[25]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(25),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[26]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(26),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[27]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(27),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[28]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(28),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[29]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(29),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[2]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(2),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[30]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(30),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[31]_i_2_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(31),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[3]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(3),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[4]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(4),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[5]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(5),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[6]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(6),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[7]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(7),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[8]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(8),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_num_blocks_V_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => \int_num_blocks_V[31]_i_1_n_0\,
      D => \int_num_blocks_V[9]_i_1_n_0\,
      Q => \^int_num_blocks_v_reg[31]_0\(9),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(0),
      Q => int_stalled_V(0),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(10),
      Q => int_stalled_V(10),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(11),
      Q => int_stalled_V(11),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(12),
      Q => int_stalled_V(12),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(13),
      Q => int_stalled_V(13),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(14),
      Q => int_stalled_V(14),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(15),
      Q => int_stalled_V(15),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(16),
      Q => int_stalled_V(16),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(17),
      Q => int_stalled_V(17),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(18),
      Q => int_stalled_V(18),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(19),
      Q => int_stalled_V(19),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(1),
      Q => int_stalled_V(1),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(20),
      Q => int_stalled_V(20),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(21),
      Q => int_stalled_V(21),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(22),
      Q => int_stalled_V(22),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(23),
      Q => int_stalled_V(23),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(24),
      Q => int_stalled_V(24),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(25),
      Q => int_stalled_V(25),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(26),
      Q => int_stalled_V(26),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(27),
      Q => int_stalled_V(27),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(28),
      Q => int_stalled_V(28),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(29),
      Q => int_stalled_V(29),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(2),
      Q => int_stalled_V(2),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(30),
      Q => int_stalled_V(30),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(31),
      Q => int_stalled_V(31),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(3),
      Q => int_stalled_V(3),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(4),
      Q => int_stalled_V(4),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(5),
      Q => int_stalled_V(5),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(6),
      Q => int_stalled_V(6),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(7),
      Q => int_stalled_V(7),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(8),
      Q => int_stalled_V(8),
      R => ap_rst_n_cntrl_aclk_inv
    );
\int_stalled_V_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_stalled_V_reg[31]_0\(9),
      Q => int_stalled_V(9),
      R => ap_rst_n_cntrl_aclk_inv
    );
interrupt_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => int_gie,
      I1 => p_1_in,
      I2 => \int_isr_reg_n_0_[0]\,
      O => interrupt
    );
isr_mask_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => \waddr_reg_n_0_[3]\,
      I1 => ap_start_mask_i_3_n_0,
      I2 => \waddr_reg_n_0_[2]\,
      I3 => s_axi_CNTRL_WSTRB(0),
      O => isr_toggle
    );
isr_mask_reg: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => '1',
      D => isr_toggle,
      Q => isr_mask,
      R => ap_rst_n_cntrl_aclk_inv
    );
\num_blocks_V_read_reg_237[31]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => ap_start,
      I1 => Q(0),
      O => \^e\(0)
    );
\p_s_fu_60[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F8F8F8F808F8F8F8"
    )
        port map (
      I0 => ap_start,
      I1 => Q(0),
      I2 => p_s_fu_60,
      I3 => p_2_in,
      I4 => Q(1),
      I5 => CO(0),
      O => int_ap_start_reg_0
    );
\rdata[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"000000E2"
    )
        port map (
      I0 => \rdata_reg[0]_i_2_n_0\,
      I1 => s_axi_CNTRL_ARADDR(2),
      I2 => \rdata[0]_i_3_n_0\,
      I3 => s_axi_CNTRL_ARADDR(0),
      I4 => s_axi_CNTRL_ARADDR(1),
      O => \rdata[0]_i_1_n_0\
    );
\rdata[0]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"11100010"
    )
        port map (
      I0 => s_axi_CNTRL_ARADDR(5),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_gie,
      I3 => s_axi_CNTRL_ARADDR(3),
      I4 => \int_isr_reg_n_0_[0]\,
      O => \rdata[0]_i_3_n_0\
    );
\rdata[0]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"30BB3088"
    )
        port map (
      I0 => \^int_num_blocks_v_reg[31]_0\(0),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_last_V(0),
      I3 => s_axi_CNTRL_ARADDR(5),
      I4 => ap_start,
      O => \rdata[0]_i_4_n_0\
    );
\rdata[0]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"30BB3088"
    )
        port map (
      I0 => int_first_V(0),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_stalled_V(0),
      I3 => s_axi_CNTRL_ARADDR(5),
      I4 => \int_ier_reg_n_0_[0]\,
      O => \rdata[0]_i_5_n_0\
    );
\rdata[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(10),
      I1 => int_stalled_V(10),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(10),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(10),
      O => \rdata[10]_i_1_n_0\
    );
\rdata[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(11),
      I1 => int_stalled_V(11),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(11),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(11),
      O => \rdata[11]_i_1_n_0\
    );
\rdata[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(12),
      I1 => int_stalled_V(12),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(12),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(12),
      O => \rdata[12]_i_1_n_0\
    );
\rdata[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(13),
      I1 => int_stalled_V(13),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(13),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(13),
      O => \rdata[13]_i_1_n_0\
    );
\rdata[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(14),
      I1 => int_stalled_V(14),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(14),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(14),
      O => \rdata[14]_i_1_n_0\
    );
\rdata[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(15),
      I1 => int_stalled_V(15),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(15),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(15),
      O => \rdata[15]_i_1_n_0\
    );
\rdata[16]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(16),
      I1 => int_stalled_V(16),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(16),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(16),
      O => \rdata[16]_i_1_n_0\
    );
\rdata[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(17),
      I1 => int_stalled_V(17),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(17),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(17),
      O => \rdata[17]_i_1_n_0\
    );
\rdata[18]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(18),
      I1 => int_stalled_V(18),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(18),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(18),
      O => \rdata[18]_i_1_n_0\
    );
\rdata[19]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(19),
      I1 => int_stalled_V(19),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(19),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(19),
      O => \rdata[19]_i_1_n_0\
    );
\rdata[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000002222E222"
    )
        port map (
      I0 => \rdata_reg[1]_i_2_n_0\,
      I1 => s_axi_CNTRL_ARADDR(2),
      I2 => p_1_in,
      I3 => s_axi_CNTRL_ARADDR(3),
      I4 => \rdata[1]_i_3_n_0\,
      I5 => \rdata[1]_i_4_n_0\,
      O => \rdata[1]_i_1_n_0\
    );
\rdata[1]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => s_axi_CNTRL_ARADDR(5),
      I1 => s_axi_CNTRL_ARADDR(4),
      O => \rdata[1]_i_3_n_0\
    );
\rdata[1]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => s_axi_CNTRL_ARADDR(1),
      I1 => s_axi_CNTRL_ARADDR(0),
      O => \rdata[1]_i_4_n_0\
    );
\rdata[1]_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"30BB3088"
    )
        port map (
      I0 => \^int_num_blocks_v_reg[31]_0\(1),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_last_V(1),
      I3 => s_axi_CNTRL_ARADDR(5),
      I4 => int_ap_done,
      O => \rdata[1]_i_5_n_0\
    );
\rdata[1]_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"30BB3088"
    )
        port map (
      I0 => int_first_V(1),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_stalled_V(1),
      I3 => s_axi_CNTRL_ARADDR(5),
      I4 => p_0_in,
      O => \rdata[1]_i_6_n_0\
    );
\rdata[20]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(20),
      I1 => int_stalled_V(20),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(20),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(20),
      O => \rdata[20]_i_1_n_0\
    );
\rdata[21]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(21),
      I1 => int_stalled_V(21),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(21),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(21),
      O => \rdata[21]_i_1_n_0\
    );
\rdata[22]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(22),
      I1 => int_stalled_V(22),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(22),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(22),
      O => \rdata[22]_i_1_n_0\
    );
\rdata[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(23),
      I1 => int_stalled_V(23),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(23),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(23),
      O => \rdata[23]_i_1_n_0\
    );
\rdata[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(24),
      I1 => int_stalled_V(24),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(24),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(24),
      O => \rdata[24]_i_1_n_0\
    );
\rdata[25]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(25),
      I1 => int_stalled_V(25),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(25),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(25),
      O => \rdata[25]_i_1_n_0\
    );
\rdata[26]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(26),
      I1 => int_stalled_V(26),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(26),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(26),
      O => \rdata[26]_i_1_n_0\
    );
\rdata[27]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(27),
      I1 => int_stalled_V(27),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(27),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(27),
      O => \rdata[27]_i_1_n_0\
    );
\rdata[28]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(28),
      I1 => int_stalled_V(28),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(28),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(28),
      O => \rdata[28]_i_1_n_0\
    );
\rdata[29]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(29),
      I1 => int_stalled_V(29),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(29),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(29),
      O => \rdata[29]_i_1_n_0\
    );
\rdata[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101010000000100"
    )
        port map (
      I0 => s_axi_CNTRL_ARADDR(1),
      I1 => s_axi_CNTRL_ARADDR(0),
      I2 => s_axi_CNTRL_ARADDR(2),
      I3 => \rdata[2]_i_2_n_0\,
      I4 => s_axi_CNTRL_ARADDR(3),
      I5 => \rdata[2]_i_3_n_0\,
      O => rdata(2)
    );
\rdata[2]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"30BB3088"
    )
        port map (
      I0 => \^int_num_blocks_v_reg[31]_0\(2),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_last_V(2),
      I3 => s_axi_CNTRL_ARADDR(5),
      I4 => int_ap_idle,
      O => \rdata[2]_i_2_n_0\
    );
\rdata[2]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"3808"
    )
        port map (
      I0 => int_first_V(2),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => s_axi_CNTRL_ARADDR(5),
      I3 => int_stalled_V(2),
      O => \rdata[2]_i_3_n_0\
    );
\rdata[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(30),
      I1 => int_stalled_V(30),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(30),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(30),
      O => \rdata[30]_i_1_n_0\
    );
\rdata[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAAAAAAAAAA88A"
    )
        port map (
      I0 => ar_hs,
      I1 => s_axi_CNTRL_ARADDR(1),
      I2 => s_axi_CNTRL_ARADDR(5),
      I3 => s_axi_CNTRL_ARADDR(4),
      I4 => s_axi_CNTRL_ARADDR(0),
      I5 => s_axi_CNTRL_ARADDR(2),
      O => \rdata[31]_i_1_n_0\
    );
\rdata[31]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => s_axi_CNTRL_ARVALID,
      I1 => \^fsm_onehot_rstate_reg[1]_0\,
      O => ar_hs
    );
\rdata[31]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(31),
      I1 => int_stalled_V(31),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(31),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(31),
      O => \rdata[31]_i_3_n_0\
    );
\rdata[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101010000000100"
    )
        port map (
      I0 => s_axi_CNTRL_ARADDR(1),
      I1 => s_axi_CNTRL_ARADDR(0),
      I2 => s_axi_CNTRL_ARADDR(2),
      I3 => \rdata[3]_i_2_n_0\,
      I4 => s_axi_CNTRL_ARADDR(3),
      I5 => \rdata[3]_i_3_n_0\,
      O => rdata(3)
    );
\rdata[3]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"30BB3088"
    )
        port map (
      I0 => \^int_num_blocks_v_reg[31]_0\(3),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_last_V(3),
      I3 => s_axi_CNTRL_ARADDR(5),
      I4 => int_ap_ready,
      O => \rdata[3]_i_2_n_0\
    );
\rdata[3]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"3808"
    )
        port map (
      I0 => int_first_V(3),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => s_axi_CNTRL_ARADDR(5),
      I3 => int_stalled_V(3),
      O => \rdata[3]_i_3_n_0\
    );
\rdata[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(4),
      I1 => int_stalled_V(4),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(4),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(4),
      O => \rdata[4]_i_1_n_0\
    );
\rdata[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(5),
      I1 => int_stalled_V(5),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(5),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(5),
      O => \rdata[5]_i_1_n_0\
    );
\rdata[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(6),
      I1 => int_stalled_V(6),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(6),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(6),
      O => \rdata[6]_i_1_n_0\
    );
\rdata[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0101010000000100"
    )
        port map (
      I0 => s_axi_CNTRL_ARADDR(1),
      I1 => s_axi_CNTRL_ARADDR(0),
      I2 => s_axi_CNTRL_ARADDR(2),
      I3 => \rdata[7]_i_2_n_0\,
      I4 => s_axi_CNTRL_ARADDR(3),
      I5 => \rdata[7]_i_3_n_0\,
      O => rdata(7)
    );
\rdata[7]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"30BB3088"
    )
        port map (
      I0 => \^int_num_blocks_v_reg[31]_0\(7),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => int_last_V(7),
      I3 => s_axi_CNTRL_ARADDR(5),
      I4 => int_auto_restart,
      O => \rdata[7]_i_2_n_0\
    );
\rdata[7]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"3808"
    )
        port map (
      I0 => int_first_V(7),
      I1 => s_axi_CNTRL_ARADDR(4),
      I2 => s_axi_CNTRL_ARADDR(5),
      I3 => int_stalled_V(7),
      O => \rdata[7]_i_3_n_0\
    );
\rdata[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(8),
      I1 => int_stalled_V(8),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(8),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(8),
      O => \rdata[8]_i_1_n_0\
    );
\rdata[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => int_first_V(9),
      I1 => int_stalled_V(9),
      I2 => s_axi_CNTRL_ARADDR(3),
      I3 => \^int_num_blocks_v_reg[31]_0\(9),
      I4 => s_axi_CNTRL_ARADDR(4),
      I5 => int_last_V(9),
      O => \rdata[9]_i_1_n_0\
    );
\rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[0]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(0),
      R => '0'
    );
\rdata_reg[0]_i_2\: unisim.vcomponents.MUXF7
     port map (
      I0 => \rdata[0]_i_4_n_0\,
      I1 => \rdata[0]_i_5_n_0\,
      O => \rdata_reg[0]_i_2_n_0\,
      S => s_axi_CNTRL_ARADDR(3)
    );
\rdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[10]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(10),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[11]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(11),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[12]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(12),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[13]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(13),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[14]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(14),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[15]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(15),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[16]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(16),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[17]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(17),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[18]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(18),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[19]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(19),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[1]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(1),
      R => '0'
    );
\rdata_reg[1]_i_2\: unisim.vcomponents.MUXF7
     port map (
      I0 => \rdata[1]_i_5_n_0\,
      I1 => \rdata[1]_i_6_n_0\,
      O => \rdata_reg[1]_i_2_n_0\,
      S => s_axi_CNTRL_ARADDR(3)
    );
\rdata_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[20]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(20),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[21]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(21),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[22]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(22),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[23]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(23),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[24]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(24),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[25]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(25),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[26]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(26),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[27]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(27),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[28]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(28),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[29]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(29),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => rdata(2),
      Q => s_axi_CNTRL_RDATA(2),
      R => '0'
    );
\rdata_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[30]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(30),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[31]_i_3_n_0\,
      Q => s_axi_CNTRL_RDATA(31),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => rdata(3),
      Q => s_axi_CNTRL_RDATA(3),
      R => '0'
    );
\rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[4]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(4),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[5]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(5),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[6]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(6),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => rdata(7),
      Q => s_axi_CNTRL_RDATA(7),
      R => '0'
    );
\rdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[8]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(8),
      R => \rdata[31]_i_1_n_0\
    );
\rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => ar_hs,
      D => \rdata[9]_i_1_n_0\,
      Q => s_axi_CNTRL_RDATA(9),
      R => \rdata[31]_i_1_n_0\
    );
\t_V_1_fu_68[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAAAAAA2AAAAAAA"
    )
        port map (
      I0 => \^e\(0),
      I1 => tready_V(0),
      I2 => tvalid_V(0),
      I3 => tlast_V(0),
      I4 => Q(1),
      I5 => CO(0),
      O => t_V_1_fu_68
    );
\t_V_reg_124[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8088"
    )
        port map (
      I0 => Q(0),
      I1 => ap_start,
      I2 => CO(0),
      I3 => Q(1),
      O => \ap_CS_fsm_reg[0]\
    );
\waddr[5]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => s_axi_CNTRL_AWVALID,
      I1 => \^fsm_onehot_wstate_reg[1]_0\,
      O => waddr
    );
\waddr_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => waddr,
      D => s_axi_CNTRL_AWADDR(0),
      Q => \waddr_reg_n_0_[0]\,
      R => '0'
    );
\waddr_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => waddr,
      D => s_axi_CNTRL_AWADDR(1),
      Q => \waddr_reg_n_0_[1]\,
      R => '0'
    );
\waddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => waddr,
      D => s_axi_CNTRL_AWADDR(2),
      Q => \waddr_reg_n_0_[2]\,
      R => '0'
    );
\waddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => waddr,
      D => s_axi_CNTRL_AWADDR(3),
      Q => \waddr_reg_n_0_[3]\,
      R => '0'
    );
\waddr_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => waddr,
      D => s_axi_CNTRL_AWADDR(4),
      Q => \waddr_reg_n_0_[4]\,
      R => '0'
    );
\waddr_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => cntrl_aclk,
      CE => waddr,
      D => s_axi_CNTRL_AWADDR(5),
      Q => \waddr_reg_n_0_[5]\,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity project_1_enc_ip_mon_0_monitor is
  port (
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    rtc_V : in STD_LOGIC_VECTOR ( 31 downto 0 );
    tvalid_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    tready_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    tlast_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_CNTRL_AWVALID : in STD_LOGIC;
    s_axi_CNTRL_AWREADY : out STD_LOGIC;
    s_axi_CNTRL_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_CNTRL_WVALID : in STD_LOGIC;
    s_axi_CNTRL_WREADY : out STD_LOGIC;
    s_axi_CNTRL_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CNTRL_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_CNTRL_ARVALID : in STD_LOGIC;
    s_axi_CNTRL_ARREADY : out STD_LOGIC;
    s_axi_CNTRL_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_CNTRL_RVALID : out STD_LOGIC;
    s_axi_CNTRL_RREADY : in STD_LOGIC;
    s_axi_CNTRL_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CNTRL_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_CNTRL_BVALID : out STD_LOGIC;
    s_axi_CNTRL_BREADY : in STD_LOGIC;
    s_axi_CNTRL_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    interrupt : out STD_LOGIC;
    cntrl_aclk : in STD_LOGIC;
    ap_rst_n_cntrl_aclk : in STD_LOGIC
  );
  attribute C_S_AXI_CNTRL_ADDR_WIDTH : integer;
  attribute C_S_AXI_CNTRL_ADDR_WIDTH of project_1_enc_ip_mon_0_monitor : entity is 6;
  attribute C_S_AXI_CNTRL_DATA_WIDTH : integer;
  attribute C_S_AXI_CNTRL_DATA_WIDTH of project_1_enc_ip_mon_0_monitor : entity is 32;
  attribute C_S_AXI_CNTRL_WSTRB_WIDTH : integer;
  attribute C_S_AXI_CNTRL_WSTRB_WIDTH of project_1_enc_ip_mon_0_monitor : entity is 4;
  attribute C_S_AXI_DATA_WIDTH : integer;
  attribute C_S_AXI_DATA_WIDTH of project_1_enc_ip_mon_0_monitor : entity is 32;
  attribute C_S_AXI_WSTRB_WIDTH : integer;
  attribute C_S_AXI_WSTRB_WIDTH of project_1_enc_ip_mon_0_monitor : entity is 4;
  attribute ap_ST_fsm_state1 : string;
  attribute ap_ST_fsm_state1 of project_1_enc_ip_mon_0_monitor : entity is "3'b001";
  attribute ap_ST_fsm_state2 : string;
  attribute ap_ST_fsm_state2 of project_1_enc_ip_mon_0_monitor : entity is "3'b010";
  attribute ap_ST_fsm_state3 : string;
  attribute ap_ST_fsm_state3 of project_1_enc_ip_mon_0_monitor : entity is "3'b100";
  attribute hls_module : string;
  attribute hls_module of project_1_enc_ip_mon_0_monitor : entity is "yes";
end project_1_enc_ip_mon_0_monitor;

architecture STRUCTURE of project_1_enc_ip_mon_0_monitor is
  signal \<const0>\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_10_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_11_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_12_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_13_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_14_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_4_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_5_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_6_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_7_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_8_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm[2]_i_9_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_2_n_5\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_2_n_6\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_2_n_7\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_0\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_1\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_2\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_3\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_4\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_5\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_6\ : STD_LOGIC;
  signal \ap_CS_fsm_reg[2]_i_3_n_7\ : STD_LOGIC;
  signal \ap_CS_fsm_reg_n_0_[0]\ : STD_LOGIC;
  signal ap_CS_fsm_state2 : STD_LOGIC;
  signal ap_CS_fsm_state3 : STD_LOGIC;
  signal ap_NS_fsm : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal ap_NS_fsm11_out : STD_LOGIC;
  signal ap_rst_n_inv : STD_LOGIC;
  signal first_V_preg : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal first_V_preg1 : STD_LOGIC;
  signal monitor_CNTRL_s_axi_U_n_11 : STD_LOGIC;
  signal monitor_CNTRL_s_axi_U_n_6 : STD_LOGIC;
  signal num_blocks_V : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal num_blocks_V_read_reg_237 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal p_s_fu_60 : STD_LOGIC;
  signal t_V_1_fu_68 : STD_LOGIC;
  signal t_V_1_fu_680 : STD_LOGIC;
  signal \t_V_1_fu_68[0]_i_3_n_0\ : STD_LOGIC;
  signal t_V_1_fu_68_reg : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \t_V_1_fu_68_reg[0]_i_2_n_0\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_1\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_10\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_11\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_12\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_13\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_14\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_15\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_2\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_3\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_4\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_5\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_6\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_7\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_8\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[0]_i_2_n_9\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_0\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_1\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_10\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_11\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_12\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_13\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_14\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_15\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_2\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_3\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_4\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_5\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_6\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_7\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_8\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[16]_i_1_n_9\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_1\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_10\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_11\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_12\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_13\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_14\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_15\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_2\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_3\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_4\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_5\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_6\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_7\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_8\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[24]_i_1_n_9\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_0\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_1\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_10\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_11\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_12\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_13\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_14\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_15\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_2\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_3\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_4\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_5\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_6\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_7\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_8\ : STD_LOGIC;
  signal \t_V_1_fu_68_reg[8]_i_1_n_9\ : STD_LOGIC;
  signal t_V_reg_124 : STD_LOGIC;
  signal \t_V_reg_124[0]_i_4_n_0\ : STD_LOGIC;
  signal t_V_reg_124_reg : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \t_V_reg_124_reg[0]_i_3_n_0\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_1\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_10\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_11\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_12\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_13\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_14\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_15\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_2\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_3\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_4\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_5\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_6\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_7\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_8\ : STD_LOGIC;
  signal \t_V_reg_124_reg[0]_i_3_n_9\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_0\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_1\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_10\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_11\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_12\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_13\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_14\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_15\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_2\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_3\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_4\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_5\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_6\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_7\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_8\ : STD_LOGIC;
  signal \t_V_reg_124_reg[16]_i_1_n_9\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_1\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_10\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_11\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_12\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_13\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_14\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_15\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_2\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_3\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_4\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_5\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_6\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_7\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_8\ : STD_LOGIC;
  signal \t_V_reg_124_reg[24]_i_1_n_9\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_0\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_1\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_10\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_11\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_12\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_13\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_14\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_15\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_2\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_3\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_4\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_5\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_6\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_7\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_8\ : STD_LOGIC;
  signal \t_V_reg_124_reg[8]_i_1_n_9\ : STD_LOGIC;
  signal time_stamp_V_1_fu_64 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \NLW_ap_CS_fsm_reg[2]_i_2_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 3 );
  signal \NLW_ap_CS_fsm_reg[2]_i_2_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_ap_CS_fsm_reg[2]_i_3_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_t_V_1_fu_68_reg[24]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal \NLW_t_V_reg_124_reg[24]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  attribute FSM_ENCODING : string;
  attribute FSM_ENCODING of \ap_CS_fsm_reg[0]\ : label is "none";
  attribute FSM_ENCODING of \ap_CS_fsm_reg[1]\ : label is "none";
  attribute FSM_ENCODING of \ap_CS_fsm_reg[2]\ : label is "none";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \t_V_1_fu_68_reg[0]_i_2\ : label is 16;
  attribute ADDER_THRESHOLD of \t_V_1_fu_68_reg[16]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \t_V_1_fu_68_reg[24]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \t_V_1_fu_68_reg[8]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \t_V_reg_124_reg[0]_i_3\ : label is 16;
  attribute ADDER_THRESHOLD of \t_V_reg_124_reg[16]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \t_V_reg_124_reg[24]_i_1\ : label is 16;
  attribute ADDER_THRESHOLD of \t_V_reg_124_reg[8]_i_1\ : label is 16;
begin
  s_axi_CNTRL_BRESP(1) <= \<const0>\;
  s_axi_CNTRL_BRESP(0) <= \<const0>\;
  s_axi_CNTRL_RRESP(1) <= \<const0>\;
  s_axi_CNTRL_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
\ap_CS_fsm[2]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \ap_CS_fsm_reg[2]_i_2_n_5\,
      I1 => ap_CS_fsm_state2,
      O => ap_NS_fsm(2)
    );
\ap_CS_fsm[2]_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(12),
      I1 => num_blocks_V_read_reg_237(12),
      I2 => num_blocks_V_read_reg_237(14),
      I3 => t_V_1_fu_68_reg(14),
      I4 => num_blocks_V_read_reg_237(13),
      I5 => t_V_1_fu_68_reg(13),
      O => \ap_CS_fsm[2]_i_10_n_0\
    );
\ap_CS_fsm[2]_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(9),
      I1 => num_blocks_V_read_reg_237(9),
      I2 => num_blocks_V_read_reg_237(11),
      I3 => t_V_1_fu_68_reg(11),
      I4 => num_blocks_V_read_reg_237(10),
      I5 => t_V_1_fu_68_reg(10),
      O => \ap_CS_fsm[2]_i_11_n_0\
    );
\ap_CS_fsm[2]_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(6),
      I1 => num_blocks_V_read_reg_237(6),
      I2 => num_blocks_V_read_reg_237(8),
      I3 => t_V_1_fu_68_reg(8),
      I4 => num_blocks_V_read_reg_237(7),
      I5 => t_V_1_fu_68_reg(7),
      O => \ap_CS_fsm[2]_i_12_n_0\
    );
\ap_CS_fsm[2]_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(3),
      I1 => num_blocks_V_read_reg_237(3),
      I2 => num_blocks_V_read_reg_237(5),
      I3 => t_V_1_fu_68_reg(5),
      I4 => num_blocks_V_read_reg_237(4),
      I5 => t_V_1_fu_68_reg(4),
      O => \ap_CS_fsm[2]_i_13_n_0\
    );
\ap_CS_fsm[2]_i_14\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(0),
      I1 => num_blocks_V_read_reg_237(0),
      I2 => num_blocks_V_read_reg_237(2),
      I3 => t_V_1_fu_68_reg(2),
      I4 => num_blocks_V_read_reg_237(1),
      I5 => t_V_1_fu_68_reg(1),
      O => \ap_CS_fsm[2]_i_14_n_0\
    );
\ap_CS_fsm[2]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(30),
      I1 => num_blocks_V_read_reg_237(30),
      I2 => t_V_1_fu_68_reg(31),
      I3 => num_blocks_V_read_reg_237(31),
      O => \ap_CS_fsm[2]_i_4_n_0\
    );
\ap_CS_fsm[2]_i_5\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(27),
      I1 => num_blocks_V_read_reg_237(27),
      I2 => num_blocks_V_read_reg_237(29),
      I3 => t_V_1_fu_68_reg(29),
      I4 => num_blocks_V_read_reg_237(28),
      I5 => t_V_1_fu_68_reg(28),
      O => \ap_CS_fsm[2]_i_5_n_0\
    );
\ap_CS_fsm[2]_i_6\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(24),
      I1 => num_blocks_V_read_reg_237(24),
      I2 => num_blocks_V_read_reg_237(26),
      I3 => t_V_1_fu_68_reg(26),
      I4 => num_blocks_V_read_reg_237(25),
      I5 => t_V_1_fu_68_reg(25),
      O => \ap_CS_fsm[2]_i_6_n_0\
    );
\ap_CS_fsm[2]_i_7\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(21),
      I1 => num_blocks_V_read_reg_237(21),
      I2 => num_blocks_V_read_reg_237(23),
      I3 => t_V_1_fu_68_reg(23),
      I4 => num_blocks_V_read_reg_237(22),
      I5 => t_V_1_fu_68_reg(22),
      O => \ap_CS_fsm[2]_i_7_n_0\
    );
\ap_CS_fsm[2]_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(18),
      I1 => num_blocks_V_read_reg_237(18),
      I2 => num_blocks_V_read_reg_237(20),
      I3 => t_V_1_fu_68_reg(20),
      I4 => num_blocks_V_read_reg_237(19),
      I5 => t_V_1_fu_68_reg(19),
      O => \ap_CS_fsm[2]_i_8_n_0\
    );
\ap_CS_fsm[2]_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9009000000009009"
    )
        port map (
      I0 => t_V_1_fu_68_reg(15),
      I1 => num_blocks_V_read_reg_237(15),
      I2 => num_blocks_V_read_reg_237(17),
      I3 => t_V_1_fu_68_reg(17),
      I4 => num_blocks_V_read_reg_237(16),
      I5 => t_V_1_fu_68_reg(16),
      O => \ap_CS_fsm[2]_i_9_n_0\
    );
\ap_CS_fsm_reg[0]\: unisim.vcomponents.FDSE
    generic map(
      INIT => '1'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => ap_NS_fsm(0),
      Q => \ap_CS_fsm_reg_n_0_[0]\,
      S => ap_rst_n_inv
    );
\ap_CS_fsm_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => ap_NS_fsm(1),
      Q => ap_CS_fsm_state2,
      R => ap_rst_n_inv
    );
\ap_CS_fsm_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => ap_NS_fsm(2),
      Q => ap_CS_fsm_state3,
      R => ap_rst_n_inv
    );
\ap_CS_fsm_reg[2]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => \ap_CS_fsm_reg[2]_i_3_n_0\,
      CI_TOP => '0',
      CO(7 downto 3) => \NLW_ap_CS_fsm_reg[2]_i_2_CO_UNCONNECTED\(7 downto 3),
      CO(2) => \ap_CS_fsm_reg[2]_i_2_n_5\,
      CO(1) => \ap_CS_fsm_reg[2]_i_2_n_6\,
      CO(0) => \ap_CS_fsm_reg[2]_i_2_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => \NLW_ap_CS_fsm_reg[2]_i_2_O_UNCONNECTED\(7 downto 0),
      S(7 downto 3) => B"00000",
      S(2) => \ap_CS_fsm[2]_i_4_n_0\,
      S(1) => \ap_CS_fsm[2]_i_5_n_0\,
      S(0) => \ap_CS_fsm[2]_i_6_n_0\
    );
\ap_CS_fsm_reg[2]_i_3\: unisim.vcomponents.CARRY8
     port map (
      CI => '1',
      CI_TOP => '0',
      CO(7) => \ap_CS_fsm_reg[2]_i_3_n_0\,
      CO(6) => \ap_CS_fsm_reg[2]_i_3_n_1\,
      CO(5) => \ap_CS_fsm_reg[2]_i_3_n_2\,
      CO(4) => \ap_CS_fsm_reg[2]_i_3_n_3\,
      CO(3) => \ap_CS_fsm_reg[2]_i_3_n_4\,
      CO(2) => \ap_CS_fsm_reg[2]_i_3_n_5\,
      CO(1) => \ap_CS_fsm_reg[2]_i_3_n_6\,
      CO(0) => \ap_CS_fsm_reg[2]_i_3_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7 downto 0) => \NLW_ap_CS_fsm_reg[2]_i_3_O_UNCONNECTED\(7 downto 0),
      S(7) => \ap_CS_fsm[2]_i_7_n_0\,
      S(6) => \ap_CS_fsm[2]_i_8_n_0\,
      S(5) => \ap_CS_fsm[2]_i_9_n_0\,
      S(4) => \ap_CS_fsm[2]_i_10_n_0\,
      S(3) => \ap_CS_fsm[2]_i_11_n_0\,
      S(2) => \ap_CS_fsm[2]_i_12_n_0\,
      S(1) => \ap_CS_fsm[2]_i_13_n_0\,
      S(0) => \ap_CS_fsm[2]_i_14_n_0\
    );
\first_V_preg[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4000000000000000"
    )
        port map (
      I0 => \ap_CS_fsm_reg[2]_i_2_n_5\,
      I1 => ap_CS_fsm_state2,
      I2 => tready_V(0),
      I3 => tvalid_V(0),
      I4 => tlast_V(0),
      I5 => p_s_fu_60,
      O => first_V_preg1
    );
\first_V_preg_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(0),
      Q => first_V_preg(0),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(10),
      Q => first_V_preg(10),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(11),
      Q => first_V_preg(11),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(12),
      Q => first_V_preg(12),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(13),
      Q => first_V_preg(13),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(14),
      Q => first_V_preg(14),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(15),
      Q => first_V_preg(15),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(16),
      Q => first_V_preg(16),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(17),
      Q => first_V_preg(17),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(18),
      Q => first_V_preg(18),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(19),
      Q => first_V_preg(19),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(1),
      Q => first_V_preg(1),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(20),
      Q => first_V_preg(20),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(21),
      Q => first_V_preg(21),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(22),
      Q => first_V_preg(22),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(23),
      Q => first_V_preg(23),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(24),
      Q => first_V_preg(24),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(25),
      Q => first_V_preg(25),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(26),
      Q => first_V_preg(26),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(27),
      Q => first_V_preg(27),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(28),
      Q => first_V_preg(28),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(29),
      Q => first_V_preg(29),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(2),
      Q => first_V_preg(2),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(30),
      Q => first_V_preg(30),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(31),
      Q => first_V_preg(31),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(3),
      Q => first_V_preg(3),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(4),
      Q => first_V_preg(4),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(5),
      Q => first_V_preg(5),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(6),
      Q => first_V_preg(6),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(7),
      Q => first_V_preg(7),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(8),
      Q => first_V_preg(8),
      R => ap_rst_n_inv
    );
\first_V_preg_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => first_V_preg1,
      D => rtc_V(9),
      Q => first_V_preg(9),
      R => ap_rst_n_inv
    );
monitor_CNTRL_s_axi_U: entity work.project_1_enc_ip_mon_0_monitor_CNTRL_s_axi
     port map (
      CO(0) => \ap_CS_fsm_reg[2]_i_2_n_5\,
      D(1 downto 0) => ap_NS_fsm(1 downto 0),
      E(0) => ap_NS_fsm11_out,
      \FSM_onehot_rstate_reg[1]_0\ => s_axi_CNTRL_ARREADY,
      \FSM_onehot_wstate_reg[1]_0\ => s_axi_CNTRL_AWREADY,
      \FSM_onehot_wstate_reg[2]_0\ => s_axi_CNTRL_WREADY,
      Q(2) => ap_CS_fsm_state3,
      Q(1) => ap_CS_fsm_state2,
      Q(0) => \ap_CS_fsm_reg_n_0_[0]\,
      \ap_CS_fsm_reg[0]\ => monitor_CNTRL_s_axi_U_n_6,
      ap_clk => ap_clk,
      ap_rst_n => ap_rst_n,
      ap_rst_n_cntrl_aclk => ap_rst_n_cntrl_aclk,
      ap_rst_n_inv => ap_rst_n_inv,
      cntrl_aclk => cntrl_aclk,
      first_V_preg(31 downto 0) => first_V_preg(31 downto 0),
      int_ap_start_reg_0 => monitor_CNTRL_s_axi_U_n_11,
      \int_last_V_reg[31]_0\(31 downto 0) => time_stamp_V_1_fu_64(31 downto 0),
      \int_num_blocks_V_reg[31]_0\(31 downto 0) => num_blocks_V(31 downto 0),
      \int_stalled_V_reg[31]_0\(31 downto 0) => t_V_reg_124_reg(31 downto 0),
      interrupt => interrupt,
      p_s_fu_60 => p_s_fu_60,
      rtc_V(31 downto 0) => rtc_V(31 downto 0),
      s_axi_CNTRL_ARADDR(5 downto 0) => s_axi_CNTRL_ARADDR(5 downto 0),
      s_axi_CNTRL_ARVALID => s_axi_CNTRL_ARVALID,
      s_axi_CNTRL_AWADDR(5 downto 0) => s_axi_CNTRL_AWADDR(5 downto 0),
      s_axi_CNTRL_AWVALID => s_axi_CNTRL_AWVALID,
      s_axi_CNTRL_BREADY => s_axi_CNTRL_BREADY,
      s_axi_CNTRL_BVALID => s_axi_CNTRL_BVALID,
      s_axi_CNTRL_RDATA(31 downto 0) => s_axi_CNTRL_RDATA(31 downto 0),
      s_axi_CNTRL_RREADY => s_axi_CNTRL_RREADY,
      s_axi_CNTRL_RVALID => s_axi_CNTRL_RVALID,
      s_axi_CNTRL_WDATA(31 downto 0) => s_axi_CNTRL_WDATA(31 downto 0),
      s_axi_CNTRL_WSTRB(3 downto 0) => s_axi_CNTRL_WSTRB(3 downto 0),
      s_axi_CNTRL_WVALID => s_axi_CNTRL_WVALID,
      t_V_1_fu_68 => t_V_1_fu_68,
      tlast_V(0) => tlast_V(0),
      tready_V(0) => tready_V(0),
      tvalid_V(0) => tvalid_V(0)
    );
\num_blocks_V_read_reg_237_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(0),
      Q => num_blocks_V_read_reg_237(0),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(10),
      Q => num_blocks_V_read_reg_237(10),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(11),
      Q => num_blocks_V_read_reg_237(11),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(12),
      Q => num_blocks_V_read_reg_237(12),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(13),
      Q => num_blocks_V_read_reg_237(13),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(14),
      Q => num_blocks_V_read_reg_237(14),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(15),
      Q => num_blocks_V_read_reg_237(15),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(16),
      Q => num_blocks_V_read_reg_237(16),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(17),
      Q => num_blocks_V_read_reg_237(17),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(18),
      Q => num_blocks_V_read_reg_237(18),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(19),
      Q => num_blocks_V_read_reg_237(19),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(1),
      Q => num_blocks_V_read_reg_237(1),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(20),
      Q => num_blocks_V_read_reg_237(20),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(21),
      Q => num_blocks_V_read_reg_237(21),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(22),
      Q => num_blocks_V_read_reg_237(22),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(23),
      Q => num_blocks_V_read_reg_237(23),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(24),
      Q => num_blocks_V_read_reg_237(24),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(25),
      Q => num_blocks_V_read_reg_237(25),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(26),
      Q => num_blocks_V_read_reg_237(26),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(27),
      Q => num_blocks_V_read_reg_237(27),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(28),
      Q => num_blocks_V_read_reg_237(28),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(29),
      Q => num_blocks_V_read_reg_237(29),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(2),
      Q => num_blocks_V_read_reg_237(2),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(30),
      Q => num_blocks_V_read_reg_237(30),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(31),
      Q => num_blocks_V_read_reg_237(31),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(3),
      Q => num_blocks_V_read_reg_237(3),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(4),
      Q => num_blocks_V_read_reg_237(4),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(5),
      Q => num_blocks_V_read_reg_237(5),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(6),
      Q => num_blocks_V_read_reg_237(6),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(7),
      Q => num_blocks_V_read_reg_237(7),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(8),
      Q => num_blocks_V_read_reg_237(8),
      R => '0'
    );
\num_blocks_V_read_reg_237_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_NS_fsm11_out,
      D => num_blocks_V(9),
      Q => num_blocks_V_read_reg_237(9),
      R => '0'
    );
\p_s_fu_60_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => '1',
      D => monitor_CNTRL_s_axi_U_n_11,
      Q => p_s_fu_60,
      R => '0'
    );
\t_V_1_fu_68[0]_i_3\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => t_V_1_fu_68_reg(0),
      O => \t_V_1_fu_68[0]_i_3_n_0\
    );
\t_V_1_fu_68_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_15\,
      Q => t_V_1_fu_68_reg(0),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[0]_i_2\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \t_V_1_fu_68_reg[0]_i_2_n_0\,
      CO(6) => \t_V_1_fu_68_reg[0]_i_2_n_1\,
      CO(5) => \t_V_1_fu_68_reg[0]_i_2_n_2\,
      CO(4) => \t_V_1_fu_68_reg[0]_i_2_n_3\,
      CO(3) => \t_V_1_fu_68_reg[0]_i_2_n_4\,
      CO(2) => \t_V_1_fu_68_reg[0]_i_2_n_5\,
      CO(1) => \t_V_1_fu_68_reg[0]_i_2_n_6\,
      CO(0) => \t_V_1_fu_68_reg[0]_i_2_n_7\,
      DI(7 downto 0) => B"00000001",
      O(7) => \t_V_1_fu_68_reg[0]_i_2_n_8\,
      O(6) => \t_V_1_fu_68_reg[0]_i_2_n_9\,
      O(5) => \t_V_1_fu_68_reg[0]_i_2_n_10\,
      O(4) => \t_V_1_fu_68_reg[0]_i_2_n_11\,
      O(3) => \t_V_1_fu_68_reg[0]_i_2_n_12\,
      O(2) => \t_V_1_fu_68_reg[0]_i_2_n_13\,
      O(1) => \t_V_1_fu_68_reg[0]_i_2_n_14\,
      O(0) => \t_V_1_fu_68_reg[0]_i_2_n_15\,
      S(7 downto 1) => t_V_1_fu_68_reg(7 downto 1),
      S(0) => \t_V_1_fu_68[0]_i_3_n_0\
    );
\t_V_1_fu_68_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_13\,
      Q => t_V_1_fu_68_reg(10),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_12\,
      Q => t_V_1_fu_68_reg(11),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_11\,
      Q => t_V_1_fu_68_reg(12),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_10\,
      Q => t_V_1_fu_68_reg(13),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_9\,
      Q => t_V_1_fu_68_reg(14),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_8\,
      Q => t_V_1_fu_68_reg(15),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_15\,
      Q => t_V_1_fu_68_reg(16),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[16]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \t_V_1_fu_68_reg[8]_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \t_V_1_fu_68_reg[16]_i_1_n_0\,
      CO(6) => \t_V_1_fu_68_reg[16]_i_1_n_1\,
      CO(5) => \t_V_1_fu_68_reg[16]_i_1_n_2\,
      CO(4) => \t_V_1_fu_68_reg[16]_i_1_n_3\,
      CO(3) => \t_V_1_fu_68_reg[16]_i_1_n_4\,
      CO(2) => \t_V_1_fu_68_reg[16]_i_1_n_5\,
      CO(1) => \t_V_1_fu_68_reg[16]_i_1_n_6\,
      CO(0) => \t_V_1_fu_68_reg[16]_i_1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \t_V_1_fu_68_reg[16]_i_1_n_8\,
      O(6) => \t_V_1_fu_68_reg[16]_i_1_n_9\,
      O(5) => \t_V_1_fu_68_reg[16]_i_1_n_10\,
      O(4) => \t_V_1_fu_68_reg[16]_i_1_n_11\,
      O(3) => \t_V_1_fu_68_reg[16]_i_1_n_12\,
      O(2) => \t_V_1_fu_68_reg[16]_i_1_n_13\,
      O(1) => \t_V_1_fu_68_reg[16]_i_1_n_14\,
      O(0) => \t_V_1_fu_68_reg[16]_i_1_n_15\,
      S(7 downto 0) => t_V_1_fu_68_reg(23 downto 16)
    );
\t_V_1_fu_68_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_14\,
      Q => t_V_1_fu_68_reg(17),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_13\,
      Q => t_V_1_fu_68_reg(18),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_12\,
      Q => t_V_1_fu_68_reg(19),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_14\,
      Q => t_V_1_fu_68_reg(1),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_11\,
      Q => t_V_1_fu_68_reg(20),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_10\,
      Q => t_V_1_fu_68_reg(21),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_9\,
      Q => t_V_1_fu_68_reg(22),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[16]_i_1_n_8\,
      Q => t_V_1_fu_68_reg(23),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_15\,
      Q => t_V_1_fu_68_reg(24),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[24]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \t_V_1_fu_68_reg[16]_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \NLW_t_V_1_fu_68_reg[24]_i_1_CO_UNCONNECTED\(7),
      CO(6) => \t_V_1_fu_68_reg[24]_i_1_n_1\,
      CO(5) => \t_V_1_fu_68_reg[24]_i_1_n_2\,
      CO(4) => \t_V_1_fu_68_reg[24]_i_1_n_3\,
      CO(3) => \t_V_1_fu_68_reg[24]_i_1_n_4\,
      CO(2) => \t_V_1_fu_68_reg[24]_i_1_n_5\,
      CO(1) => \t_V_1_fu_68_reg[24]_i_1_n_6\,
      CO(0) => \t_V_1_fu_68_reg[24]_i_1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \t_V_1_fu_68_reg[24]_i_1_n_8\,
      O(6) => \t_V_1_fu_68_reg[24]_i_1_n_9\,
      O(5) => \t_V_1_fu_68_reg[24]_i_1_n_10\,
      O(4) => \t_V_1_fu_68_reg[24]_i_1_n_11\,
      O(3) => \t_V_1_fu_68_reg[24]_i_1_n_12\,
      O(2) => \t_V_1_fu_68_reg[24]_i_1_n_13\,
      O(1) => \t_V_1_fu_68_reg[24]_i_1_n_14\,
      O(0) => \t_V_1_fu_68_reg[24]_i_1_n_15\,
      S(7 downto 0) => t_V_1_fu_68_reg(31 downto 24)
    );
\t_V_1_fu_68_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_14\,
      Q => t_V_1_fu_68_reg(25),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_13\,
      Q => t_V_1_fu_68_reg(26),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_12\,
      Q => t_V_1_fu_68_reg(27),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_11\,
      Q => t_V_1_fu_68_reg(28),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_10\,
      Q => t_V_1_fu_68_reg(29),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_13\,
      Q => t_V_1_fu_68_reg(2),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_9\,
      Q => t_V_1_fu_68_reg(30),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[24]_i_1_n_8\,
      Q => t_V_1_fu_68_reg(31),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_12\,
      Q => t_V_1_fu_68_reg(3),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_11\,
      Q => t_V_1_fu_68_reg(4),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_10\,
      Q => t_V_1_fu_68_reg(5),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_9\,
      Q => t_V_1_fu_68_reg(6),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[0]_i_2_n_8\,
      Q => t_V_1_fu_68_reg(7),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_15\,
      Q => t_V_1_fu_68_reg(8),
      R => t_V_1_fu_68
    );
\t_V_1_fu_68_reg[8]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \t_V_1_fu_68_reg[0]_i_2_n_0\,
      CI_TOP => '0',
      CO(7) => \t_V_1_fu_68_reg[8]_i_1_n_0\,
      CO(6) => \t_V_1_fu_68_reg[8]_i_1_n_1\,
      CO(5) => \t_V_1_fu_68_reg[8]_i_1_n_2\,
      CO(4) => \t_V_1_fu_68_reg[8]_i_1_n_3\,
      CO(3) => \t_V_1_fu_68_reg[8]_i_1_n_4\,
      CO(2) => \t_V_1_fu_68_reg[8]_i_1_n_5\,
      CO(1) => \t_V_1_fu_68_reg[8]_i_1_n_6\,
      CO(0) => \t_V_1_fu_68_reg[8]_i_1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \t_V_1_fu_68_reg[8]_i_1_n_8\,
      O(6) => \t_V_1_fu_68_reg[8]_i_1_n_9\,
      O(5) => \t_V_1_fu_68_reg[8]_i_1_n_10\,
      O(4) => \t_V_1_fu_68_reg[8]_i_1_n_11\,
      O(3) => \t_V_1_fu_68_reg[8]_i_1_n_12\,
      O(2) => \t_V_1_fu_68_reg[8]_i_1_n_13\,
      O(1) => \t_V_1_fu_68_reg[8]_i_1_n_14\,
      O(0) => \t_V_1_fu_68_reg[8]_i_1_n_15\,
      S(7 downto 0) => t_V_1_fu_68_reg(15 downto 8)
    );
\t_V_1_fu_68_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => \t_V_1_fu_68_reg[8]_i_1_n_14\,
      Q => t_V_1_fu_68_reg(9),
      R => t_V_1_fu_68
    );
\t_V_reg_124[0]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0400"
    )
        port map (
      I0 => \ap_CS_fsm_reg[2]_i_2_n_5\,
      I1 => ap_CS_fsm_state2,
      I2 => tready_V(0),
      I3 => tvalid_V(0),
      O => t_V_reg_124
    );
\t_V_reg_124[0]_i_4\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => t_V_reg_124_reg(0),
      O => \t_V_reg_124[0]_i_4_n_0\
    );
\t_V_reg_124_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_15\,
      Q => t_V_reg_124_reg(0),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[0]_i_3\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \t_V_reg_124_reg[0]_i_3_n_0\,
      CO(6) => \t_V_reg_124_reg[0]_i_3_n_1\,
      CO(5) => \t_V_reg_124_reg[0]_i_3_n_2\,
      CO(4) => \t_V_reg_124_reg[0]_i_3_n_3\,
      CO(3) => \t_V_reg_124_reg[0]_i_3_n_4\,
      CO(2) => \t_V_reg_124_reg[0]_i_3_n_5\,
      CO(1) => \t_V_reg_124_reg[0]_i_3_n_6\,
      CO(0) => \t_V_reg_124_reg[0]_i_3_n_7\,
      DI(7 downto 0) => B"00000001",
      O(7) => \t_V_reg_124_reg[0]_i_3_n_8\,
      O(6) => \t_V_reg_124_reg[0]_i_3_n_9\,
      O(5) => \t_V_reg_124_reg[0]_i_3_n_10\,
      O(4) => \t_V_reg_124_reg[0]_i_3_n_11\,
      O(3) => \t_V_reg_124_reg[0]_i_3_n_12\,
      O(2) => \t_V_reg_124_reg[0]_i_3_n_13\,
      O(1) => \t_V_reg_124_reg[0]_i_3_n_14\,
      O(0) => \t_V_reg_124_reg[0]_i_3_n_15\,
      S(7 downto 1) => t_V_reg_124_reg(7 downto 1),
      S(0) => \t_V_reg_124[0]_i_4_n_0\
    );
\t_V_reg_124_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_13\,
      Q => t_V_reg_124_reg(10),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_12\,
      Q => t_V_reg_124_reg(11),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_11\,
      Q => t_V_reg_124_reg(12),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_10\,
      Q => t_V_reg_124_reg(13),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_9\,
      Q => t_V_reg_124_reg(14),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_8\,
      Q => t_V_reg_124_reg(15),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_15\,
      Q => t_V_reg_124_reg(16),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[16]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \t_V_reg_124_reg[8]_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \t_V_reg_124_reg[16]_i_1_n_0\,
      CO(6) => \t_V_reg_124_reg[16]_i_1_n_1\,
      CO(5) => \t_V_reg_124_reg[16]_i_1_n_2\,
      CO(4) => \t_V_reg_124_reg[16]_i_1_n_3\,
      CO(3) => \t_V_reg_124_reg[16]_i_1_n_4\,
      CO(2) => \t_V_reg_124_reg[16]_i_1_n_5\,
      CO(1) => \t_V_reg_124_reg[16]_i_1_n_6\,
      CO(0) => \t_V_reg_124_reg[16]_i_1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \t_V_reg_124_reg[16]_i_1_n_8\,
      O(6) => \t_V_reg_124_reg[16]_i_1_n_9\,
      O(5) => \t_V_reg_124_reg[16]_i_1_n_10\,
      O(4) => \t_V_reg_124_reg[16]_i_1_n_11\,
      O(3) => \t_V_reg_124_reg[16]_i_1_n_12\,
      O(2) => \t_V_reg_124_reg[16]_i_1_n_13\,
      O(1) => \t_V_reg_124_reg[16]_i_1_n_14\,
      O(0) => \t_V_reg_124_reg[16]_i_1_n_15\,
      S(7 downto 0) => t_V_reg_124_reg(23 downto 16)
    );
\t_V_reg_124_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_14\,
      Q => t_V_reg_124_reg(17),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_13\,
      Q => t_V_reg_124_reg(18),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_12\,
      Q => t_V_reg_124_reg(19),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_14\,
      Q => t_V_reg_124_reg(1),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_11\,
      Q => t_V_reg_124_reg(20),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_10\,
      Q => t_V_reg_124_reg(21),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_9\,
      Q => t_V_reg_124_reg(22),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[16]_i_1_n_8\,
      Q => t_V_reg_124_reg(23),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_15\,
      Q => t_V_reg_124_reg(24),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[24]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \t_V_reg_124_reg[16]_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \NLW_t_V_reg_124_reg[24]_i_1_CO_UNCONNECTED\(7),
      CO(6) => \t_V_reg_124_reg[24]_i_1_n_1\,
      CO(5) => \t_V_reg_124_reg[24]_i_1_n_2\,
      CO(4) => \t_V_reg_124_reg[24]_i_1_n_3\,
      CO(3) => \t_V_reg_124_reg[24]_i_1_n_4\,
      CO(2) => \t_V_reg_124_reg[24]_i_1_n_5\,
      CO(1) => \t_V_reg_124_reg[24]_i_1_n_6\,
      CO(0) => \t_V_reg_124_reg[24]_i_1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \t_V_reg_124_reg[24]_i_1_n_8\,
      O(6) => \t_V_reg_124_reg[24]_i_1_n_9\,
      O(5) => \t_V_reg_124_reg[24]_i_1_n_10\,
      O(4) => \t_V_reg_124_reg[24]_i_1_n_11\,
      O(3) => \t_V_reg_124_reg[24]_i_1_n_12\,
      O(2) => \t_V_reg_124_reg[24]_i_1_n_13\,
      O(1) => \t_V_reg_124_reg[24]_i_1_n_14\,
      O(0) => \t_V_reg_124_reg[24]_i_1_n_15\,
      S(7 downto 0) => t_V_reg_124_reg(31 downto 24)
    );
\t_V_reg_124_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_14\,
      Q => t_V_reg_124_reg(25),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_13\,
      Q => t_V_reg_124_reg(26),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_12\,
      Q => t_V_reg_124_reg(27),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_11\,
      Q => t_V_reg_124_reg(28),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_10\,
      Q => t_V_reg_124_reg(29),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_13\,
      Q => t_V_reg_124_reg(2),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_9\,
      Q => t_V_reg_124_reg(30),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[24]_i_1_n_8\,
      Q => t_V_reg_124_reg(31),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_12\,
      Q => t_V_reg_124_reg(3),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_11\,
      Q => t_V_reg_124_reg(4),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_10\,
      Q => t_V_reg_124_reg(5),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_9\,
      Q => t_V_reg_124_reg(6),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[0]_i_3_n_8\,
      Q => t_V_reg_124_reg(7),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_15\,
      Q => t_V_reg_124_reg(8),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\t_V_reg_124_reg[8]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \t_V_reg_124_reg[0]_i_3_n_0\,
      CI_TOP => '0',
      CO(7) => \t_V_reg_124_reg[8]_i_1_n_0\,
      CO(6) => \t_V_reg_124_reg[8]_i_1_n_1\,
      CO(5) => \t_V_reg_124_reg[8]_i_1_n_2\,
      CO(4) => \t_V_reg_124_reg[8]_i_1_n_3\,
      CO(3) => \t_V_reg_124_reg[8]_i_1_n_4\,
      CO(2) => \t_V_reg_124_reg[8]_i_1_n_5\,
      CO(1) => \t_V_reg_124_reg[8]_i_1_n_6\,
      CO(0) => \t_V_reg_124_reg[8]_i_1_n_7\,
      DI(7 downto 0) => B"00000000",
      O(7) => \t_V_reg_124_reg[8]_i_1_n_8\,
      O(6) => \t_V_reg_124_reg[8]_i_1_n_9\,
      O(5) => \t_V_reg_124_reg[8]_i_1_n_10\,
      O(4) => \t_V_reg_124_reg[8]_i_1_n_11\,
      O(3) => \t_V_reg_124_reg[8]_i_1_n_12\,
      O(2) => \t_V_reg_124_reg[8]_i_1_n_13\,
      O(1) => \t_V_reg_124_reg[8]_i_1_n_14\,
      O(0) => \t_V_reg_124_reg[8]_i_1_n_15\,
      S(7 downto 0) => t_V_reg_124_reg(15 downto 8)
    );
\t_V_reg_124_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_reg_124,
      D => \t_V_reg_124_reg[8]_i_1_n_14\,
      Q => t_V_reg_124_reg(9),
      R => monitor_CNTRL_s_axi_U_n_6
    );
\time_stamp_V_1_fu_64[31]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000000"
    )
        port map (
      I0 => \ap_CS_fsm_reg[2]_i_2_n_5\,
      I1 => ap_CS_fsm_state2,
      I2 => tlast_V(0),
      I3 => tvalid_V(0),
      I4 => tready_V(0),
      O => t_V_1_fu_680
    );
\time_stamp_V_1_fu_64_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(0),
      Q => time_stamp_V_1_fu_64(0),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(10),
      Q => time_stamp_V_1_fu_64(10),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(11),
      Q => time_stamp_V_1_fu_64(11),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(12),
      Q => time_stamp_V_1_fu_64(12),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(13),
      Q => time_stamp_V_1_fu_64(13),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(14),
      Q => time_stamp_V_1_fu_64(14),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(15),
      Q => time_stamp_V_1_fu_64(15),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(16),
      Q => time_stamp_V_1_fu_64(16),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(17),
      Q => time_stamp_V_1_fu_64(17),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(18),
      Q => time_stamp_V_1_fu_64(18),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(19),
      Q => time_stamp_V_1_fu_64(19),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(1),
      Q => time_stamp_V_1_fu_64(1),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(20),
      Q => time_stamp_V_1_fu_64(20),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(21),
      Q => time_stamp_V_1_fu_64(21),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(22),
      Q => time_stamp_V_1_fu_64(22),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(23),
      Q => time_stamp_V_1_fu_64(23),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(24),
      Q => time_stamp_V_1_fu_64(24),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(25),
      Q => time_stamp_V_1_fu_64(25),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(26),
      Q => time_stamp_V_1_fu_64(26),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(27),
      Q => time_stamp_V_1_fu_64(27),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(28),
      Q => time_stamp_V_1_fu_64(28),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(29),
      Q => time_stamp_V_1_fu_64(29),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(2),
      Q => time_stamp_V_1_fu_64(2),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(30),
      Q => time_stamp_V_1_fu_64(30),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(31),
      Q => time_stamp_V_1_fu_64(31),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(3),
      Q => time_stamp_V_1_fu_64(3),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(4),
      Q => time_stamp_V_1_fu_64(4),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(5),
      Q => time_stamp_V_1_fu_64(5),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(6),
      Q => time_stamp_V_1_fu_64(6),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(7),
      Q => time_stamp_V_1_fu_64(7),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(8),
      Q => time_stamp_V_1_fu_64(8),
      R => '0'
    );
\time_stamp_V_1_fu_64_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => t_V_1_fu_680,
      D => rtc_V(9),
      Q => time_stamp_V_1_fu_64(9),
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity project_1_enc_ip_mon_0 is
  port (
    s_axi_CNTRL_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_CNTRL_AWVALID : in STD_LOGIC;
    s_axi_CNTRL_AWREADY : out STD_LOGIC;
    s_axi_CNTRL_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CNTRL_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_CNTRL_WVALID : in STD_LOGIC;
    s_axi_CNTRL_WREADY : out STD_LOGIC;
    s_axi_CNTRL_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_CNTRL_BVALID : out STD_LOGIC;
    s_axi_CNTRL_BREADY : in STD_LOGIC;
    s_axi_CNTRL_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
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
    rtc_V : in STD_LOGIC_VECTOR ( 31 downto 0 );
    tvalid_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    tready_V : in STD_LOGIC_VECTOR ( 0 to 0 );
    tlast_V : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of project_1_enc_ip_mon_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of project_1_enc_ip_mon_0 : entity is "project_1_dec_ip_mon_0,monitor,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of project_1_enc_ip_mon_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of project_1_enc_ip_mon_0 : entity is "HLS";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of project_1_enc_ip_mon_0 : entity is "monitor,Vivado 2020.1";
  attribute hls_module : string;
  attribute hls_module of project_1_enc_ip_mon_0 : entity is "yes";
end project_1_enc_ip_mon_0;

architecture STRUCTURE of project_1_enc_ip_mon_0 is
  attribute C_S_AXI_CNTRL_ADDR_WIDTH : integer;
  attribute C_S_AXI_CNTRL_ADDR_WIDTH of inst : label is 6;
  attribute C_S_AXI_CNTRL_DATA_WIDTH : integer;
  attribute C_S_AXI_CNTRL_DATA_WIDTH of inst : label is 32;
  attribute C_S_AXI_CNTRL_WSTRB_WIDTH : integer;
  attribute C_S_AXI_CNTRL_WSTRB_WIDTH of inst : label is 4;
  attribute C_S_AXI_DATA_WIDTH : integer;
  attribute C_S_AXI_DATA_WIDTH of inst : label is 32;
  attribute C_S_AXI_WSTRB_WIDTH : integer;
  attribute C_S_AXI_WSTRB_WIDTH of inst : label is 4;
  attribute ap_ST_fsm_state1 : string;
  attribute ap_ST_fsm_state1 of inst : label is "3'b001";
  attribute ap_ST_fsm_state2 : string;
  attribute ap_ST_fsm_state2 of inst : label is "3'b010";
  attribute ap_ST_fsm_state3 : string;
  attribute ap_ST_fsm_state3 of inst : label is "3'b100";
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of ap_clk : signal is "xilinx.com:signal:clock:1.0 ap_clk CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of ap_clk : signal is "XIL_INTERFACENAME ap_clk, ASSOCIATED_RESET ap_rst_n, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 300000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of ap_rst_n : signal is "xilinx.com:signal:reset:1.0 ap_rst_n RST";
  attribute X_INTERFACE_PARAMETER of ap_rst_n : signal is "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of ap_rst_n_cntrl_aclk : signal is "xilinx.com:signal:reset:1.0 ap_rst_n_cntrl_aclk RST";
  attribute X_INTERFACE_PARAMETER of ap_rst_n_cntrl_aclk : signal is "XIL_INTERFACENAME ap_rst_n_cntrl_aclk, POLARITY ACTIVE_LOW, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {RST {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of cntrl_aclk : signal is "xilinx.com:signal:clock:1.0 cntrl_aclk CLK";
  attribute X_INTERFACE_PARAMETER of cntrl_aclk : signal is "XIL_INTERFACENAME cntrl_aclk, ASSOCIATED_BUSIF s_axi_CNTRL, ASSOCIATED_RESET ap_rst_n_cntrl_aclk, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of interrupt : signal is "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT";
  attribute X_INTERFACE_PARAMETER of interrupt : signal is "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {INTERRUPT {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, PortWidth 1";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_ARREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARREADY";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_ARVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARVALID";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_AWREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWREADY";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_AWVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWVALID";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_BREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BREADY";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_BVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BVALID";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_RREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RREADY";
  attribute X_INTERFACE_PARAMETER of s_axi_CNTRL_RREADY : signal is "XIL_INTERFACENAME s_axi_CNTRL, ADDR_WIDTH 6, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {CLK {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}}}, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN project_1_clk_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_RVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RVALID";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_WREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WREADY";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_WVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WVALID";
  attribute X_INTERFACE_INFO of rtc_V : signal is "xilinx.com:signal:data:1.0 rtc_V DATA";
  attribute X_INTERFACE_PARAMETER of rtc_V : signal is "XIL_INTERFACENAME rtc_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_ARADDR : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL ARADDR";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_AWADDR : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL AWADDR";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_BRESP : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL BRESP";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_RDATA : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RDATA";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_RRESP : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL RRESP";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_WDATA : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WDATA";
  attribute X_INTERFACE_INFO of s_axi_CNTRL_WSTRB : signal is "xilinx.com:interface:aximm:1.0 s_axi_CNTRL WSTRB";
  attribute X_INTERFACE_INFO of tlast_V : signal is "xilinx.com:signal:data:1.0 tlast_V DATA";
  attribute X_INTERFACE_PARAMETER of tlast_V : signal is "XIL_INTERFACENAME tlast_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}";
  attribute X_INTERFACE_INFO of tready_V : signal is "xilinx.com:signal:data:1.0 tready_V DATA";
  attribute X_INTERFACE_PARAMETER of tready_V : signal is "XIL_INTERFACENAME tready_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}";
  attribute X_INTERFACE_INFO of tvalid_V : signal is "xilinx.com:signal:data:1.0 tvalid_V DATA";
  attribute X_INTERFACE_PARAMETER of tvalid_V : signal is "XIL_INTERFACENAME tvalid_V, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {DATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} integer {signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value false}}}}}";
begin
inst: entity work.project_1_enc_ip_mon_0_monitor
     port map (
      ap_clk => ap_clk,
      ap_rst_n => ap_rst_n,
      ap_rst_n_cntrl_aclk => ap_rst_n_cntrl_aclk,
      cntrl_aclk => cntrl_aclk,
      interrupt => interrupt,
      rtc_V(31 downto 0) => rtc_V(31 downto 0),
      s_axi_CNTRL_ARADDR(5 downto 0) => s_axi_CNTRL_ARADDR(5 downto 0),
      s_axi_CNTRL_ARREADY => s_axi_CNTRL_ARREADY,
      s_axi_CNTRL_ARVALID => s_axi_CNTRL_ARVALID,
      s_axi_CNTRL_AWADDR(5 downto 0) => s_axi_CNTRL_AWADDR(5 downto 0),
      s_axi_CNTRL_AWREADY => s_axi_CNTRL_AWREADY,
      s_axi_CNTRL_AWVALID => s_axi_CNTRL_AWVALID,
      s_axi_CNTRL_BREADY => s_axi_CNTRL_BREADY,
      s_axi_CNTRL_BRESP(1 downto 0) => s_axi_CNTRL_BRESP(1 downto 0),
      s_axi_CNTRL_BVALID => s_axi_CNTRL_BVALID,
      s_axi_CNTRL_RDATA(31 downto 0) => s_axi_CNTRL_RDATA(31 downto 0),
      s_axi_CNTRL_RREADY => s_axi_CNTRL_RREADY,
      s_axi_CNTRL_RRESP(1 downto 0) => s_axi_CNTRL_RRESP(1 downto 0),
      s_axi_CNTRL_RVALID => s_axi_CNTRL_RVALID,
      s_axi_CNTRL_WDATA(31 downto 0) => s_axi_CNTRL_WDATA(31 downto 0),
      s_axi_CNTRL_WREADY => s_axi_CNTRL_WREADY,
      s_axi_CNTRL_WSTRB(3 downto 0) => s_axi_CNTRL_WSTRB(3 downto 0),
      s_axi_CNTRL_WVALID => s_axi_CNTRL_WVALID,
      tlast_V(0) => tlast_V(0),
      tready_V(0) => tready_V(0),
      tvalid_V(0) => tvalid_V(0)
    );
end STRUCTURE;
