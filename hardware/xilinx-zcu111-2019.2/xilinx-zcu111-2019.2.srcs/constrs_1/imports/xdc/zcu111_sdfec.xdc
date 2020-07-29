#----------------------------------------------------------------------
# Title      : Example top level constraints for UltraScale+ RF Data Converter
#----------------------------------------------------------------------
# File       : usp_rf_data_converter_0_example_design.xdc
#----------------------------------------------------------------------
# Description: Xilinx Constraint file for the example design for
#              UltraScale+ RF Data Converter core
#---------------------------------------------------------------------
#
# DISCLAIMER
# This disclaimer is not a license and does not grant any
# rights to the materials distributed herewith. Except as
# otherwise provided in a valid license issued to you by
# Xilinx, and to the maximum extent permitted by applicable
# law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
# WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
# AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
# BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
# INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
# (2) Xilinx shall not be liable (whether in contract or tort,
# including negligence, or under any other theory of
# liability) for any loss or damage of any kind or nature
# related to, arising under or in connection with these
# materials, including for any direct, or any indirect,
# special, incidental, or consequential loss or damage
# (including loss of data, profits, goodwill, or any type of
# loss or damage suffered as a result of any action brought
# by a third party) even if such damage or loss was
# reasonably foreseeable or Xilinx had been advised of the
# possibility of the same.
# 
# CRITICAL APPLICATIONS
# Xilinx products are not designed or intended to be fail-
# safe, or for use in any application requiring fail-safe
# performance, such as life-support or safety devices or
# systems, Class III medical devices, nuclear facilities,
# applications related to the deployment of airbags, or any
# other applications that could lead to death, personal
# injury, or severe property or environmental damage
# (individually and collectively, "Critical
# Applications"). Customer assumes the sole risk and
# liability of any use of Xilinx products in Critical
# Applications, subject only to applicable laws and
# regulations governing limitations on product liability.
# 
# THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
# PART OF THIS FILE AT ALL TIMES. 
#
#---------------------------------------------------------------------


set_property LOC FE_X0Y6 [get_cells */sd_fec_dec/inst/STD_OTHER_G.STD_OTHER_I/FE_I]
set_property LOC FE_X0Y5 [get_cells */sd_fec_enc/inst/STD_OTHER_G.STD_OTHER_I/FE_I]


#------------------------------------------
# TIMING CONSTRAINTS
#------------------------------------------
# Set AXI-Lite Clock to 100.0MHz
create_clock -period 10.000 -name usp_rf_data_converter_0_axi_aclk [get_ports s_axi_aclk]
# ADC Reference Clock for Tile 0 running at 2000.000 MHz
create_clock -period 0.500 -name usp_rf_data_converter_0_adc0_clk [get_ports adc0_clk_p]

# DAC Reference Clock for Tile 0 running at 6400.000 MHz
create_clock -period 0.156 -name usp_rf_data_converter_0_dac0_clk [get_ports dac0_clk_p]


#AXI Streaming Clock for ADC0
create_clock -period 4.000 -name usp_rf_data_converter_0_m0_axis_aclk [get_ports adc0_axis_aclk]

#AXI Streaming Clock for DAC0
create_clock -period 2.500 -name usp_rf_data_converter_0_s0_axis_aclk [get_ports dac0_axis_aclk]

set_multicycle_path -to [get_pins -filter {REF_PIN_NAME== D} -of [get_cells -hier -filter {name =~ *usp_rf_data_converter_0_ex_i/usp_rf_data_converter_0_i/inst/IP2Bus_Data_reg*}]] -setup 2
set_multicycle_path -to [get_pins -filter {REF_PIN_NAME== D} -of [get_cells -hier -filter {name =~ *usp_rf_data_converter_0_ex_i/usp_rf_data_converter_0_i/inst/IP2Bus_Data_reg*}]] -hold 1
###############################################################################
# False paths
# For debug in synth use
# report_timing_summary -setup -slack_lesser_than 0
###############################################################################

## EXDES
## Paths from the AXI bus write logic to the register in the secondary domain.
## This path is protected by a pulse handshake, therefore the path to the control
## register is an FP
set from_list   [get_cells -hier -regexp .*rf(?:da|ad)c_exdes_ctrl_i\/.+(?:slv_rden_r_reg|slv_wdata_r_internal_reg|slv_addr_reg).*]
set signal_list [get_cells -hier -regexp {.*rf(?:da|ad)c_exdes_ctrl_i.*\/(?:ad|da)c[0-9]{2}_.+_reg.*}]
set_false_path -from $from_list   -to $signal_list
#report_timing -from $from_list -to $signal_list -path_type summary -max_paths 10000

## Mop up all the paths into the read register(AXI) from the control pins in clock domain2.
## Again protected by a pulse handshake.
set to_list     [get_pins -hier -regexp .*rf(?:da|ad)c_exdes_ctrl_i.*\/slv_rdata_reg.+/D]
set_false_path -from $signal_list -to $to_list
#report_timing -from $signal_list -to $to_list -path_type summary -max_paths 10000

create_pblock pblock_ds_adc0
add_cells_to_pblock [get_pblocks pblock_ds_adc0] [get_cells -hier -filter "name =~ *adc_sink_i*ds_slice_0*"]
resize_pblock [get_pblocks pblock_ds_adc0] -add {CLOCKREGION_X4Y0:CLOCKREGION_X5Y0}
create_pblock pblock_dg_dac0
add_cells_to_pblock [get_pblocks pblock_dg_dac0] [get_cells -hier -filter "name =~ *dac_source_i*dg_slice_0*"]
resize_pblock [get_pblocks pblock_dg_dac0] -add {CLOCKREGION_X4Y4:CLOCKREGION_X5Y4}

set_property IOSTANDARD LVCMOS18 [get_ports emio_uart1_rxd_0]
set_property IOSTANDARD LVCMOS18 [get_ports emio_uart1_txd_0]

set_property PACKAGE_PIN AU15 [get_ports emio_uart1_rxd_0]
set_property PACKAGE_PIN AT15 [get_ports emio_uart1_txd_0]

set_property IOSTANDARD LVCMOS18 [get_ports vin0_01_v_n]
set_property IOSTANDARD LVCMOS18 [get_ports vin0_01_v_p]
set_property IOSTANDARD LVCMOS18 [get_ports vout00_v_n]
set_property IOSTANDARD LVCMOS18 [get_ports vout00_v_p]


# Clocks
# o 100MHz board clock
set_property IOSTANDARD LVDS  [get_ports sys_diff_clock_clk_n]
set_property IOSTANDARD LVDS  [get_ports sys_diff_clock_clk_p]
set_property PACKAGE_PIN AN15 [get_ports sys_diff_clock_clk_n]
set_property PACKAGE_PIN AM15 [get_ports sys_diff_clock_clk_p]

# Inputs
set_property IOSTANDARD LVCMOS18 [get_ports reset]
set_property PACKAGE_PIN AW3     [get_ports reset]

# Status
set_property IOSTANDARD LVCMOS18  [get_ports led_bits_tri_o[0]]
set_property PACKAGE_PIN AR13     [get_ports led_bits_tri_o[0]]
set_property IOSTANDARD LVCMOS18  [get_ports led_bits_tri_o[1]]
set_property PACKAGE_PIN AP13     [get_ports led_bits_tri_o[1]]
set_property IOSTANDARD LVCMOS18  [get_ports led_bits_tri_o[2]]
set_property PACKAGE_PIN AR16     [get_ports led_bits_tri_o[2]]
set_property IOSTANDARD LVCMOS18  [get_ports led_bits_tri_o[3]]
set_property PACKAGE_PIN AP16     [get_ports led_bits_tri_o[3]]
set_property IOSTANDARD LVCMOS18  [get_ports led_bits_tri_o[4]]
set_property PACKAGE_PIN AP15     [get_ports led_bits_tri_o[4]]

#Suppress DRC
set_property IS_ENABLED FALSE [get_drc_checks FECPL-1]
set_property IS_ENABLED FALSE [get_drc_checks FECPL-2]
set_property IS_ENABLED FALSE [get_drc_checks FECPL-3]
set_property SEVERITY {Warning} [get_drc_checks NSTD-1]
set_property SEVERITY {Warning} [get_drc_checks UCIO-1]
