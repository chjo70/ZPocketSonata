-- (c) Copyright 1995-2019 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: xilinx.com:user:axis_probe:1.0
-- IP Revision: 1

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY design_1_enc_ip_probe_0 IS
  PORT (
    clk : IN STD_LOGIC;
    mon_tvalid : IN STD_LOGIC;
    mon_tready : IN STD_LOGIC;
    mon_tlast : IN STD_LOGIC;
    valid_op : OUT STD_LOGIC;
    ready_op : OUT STD_LOGIC;
    last_op : OUT STD_LOGIC
  );
END design_1_enc_ip_probe_0;

ARCHITECTURE design_1_enc_ip_probe_0_arch OF design_1_enc_ip_probe_0 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF design_1_enc_ip_probe_0_arch: ARCHITECTURE IS "yes";
  COMPONENT axis_probe IS
    PORT (
      clk : IN STD_LOGIC;
      mon_tvalid : IN STD_LOGIC;
      mon_tready : IN STD_LOGIC;
      mon_tlast : IN STD_LOGIC;
      valid_op : OUT STD_LOGIC;
      ready_op : OUT STD_LOGIC;
      last_op : OUT STD_LOGIC
    );
  END COMPONENT axis_probe;
  ATTRIBUTE IP_DEFINITION_SOURCE : STRING;
  ATTRIBUTE IP_DEFINITION_SOURCE OF design_1_enc_ip_probe_0_arch: ARCHITECTURE IS "package_project";
  ATTRIBUTE X_INTERFACE_INFO : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER : STRING;
  ATTRIBUTE X_INTERFACE_INFO OF mon_tlast: SIGNAL IS "xilinx.com:interface:axis:1.0 mon TLAST";
  ATTRIBUTE X_INTERFACE_INFO OF mon_tready: SIGNAL IS "xilinx.com:interface:axis:1.0 mon TREADY";
  ATTRIBUTE X_INTERFACE_PARAMETER OF mon_tvalid: SIGNAL IS "XIL_INTERFACENAME mon, TDATA_NUM_BYTES 0, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 0, HAS_TLAST 1, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN design_1_clk_wiz_0_clk_out1, LAYERED_METADATA undef, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF mon_tvalid: SIGNAL IS "xilinx.com:interface:axis:1.0 mon TVALID";
  ATTRIBUTE X_INTERFACE_PARAMETER OF clk: SIGNAL IS "XIL_INTERFACENAME clk, ASSOCIATED_BUSIF mon, FREQ_HZ 300000000, PHASE 0.0, CLK_DOMAIN design_1_clk_wiz_0_clk_out1, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF clk: SIGNAL IS "xilinx.com:signal:clock:1.0 clk CLK";
BEGIN
  U0 : axis_probe
    PORT MAP (
      clk => clk,
      mon_tvalid => mon_tvalid,
      mon_tready => mon_tready,
      mon_tlast => mon_tlast,
      valid_op => valid_op,
      ready_op => ready_op,
      last_op => last_op
    );
END design_1_enc_ip_probe_0_arch;
