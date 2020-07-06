
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2019.1
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl


# The design that will be created by this Tcl script contains the following 
# module references:
# exdes_rfadc_data_sink, exdes_rfdac_src

# Please add the sources of those modules before sourcing this Tcl script.

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xczu28dr-ffvg1517-2-e
   set_property BOARD_PART xilinx.com:zcu111:part0:1.2 [current_project]
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name design_1

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_msg_id "BD_TCL-001" "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_msg_id "BD_TCL-002" "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_msg_id "BD_TCL-003" "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_msg_id "BD_TCL-004" "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_msg_id "BD_TCL-005" "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_msg_id "BD_TCL-114" "ERROR" $errMsg}
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set adc0_clk [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 adc0_clk ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {2000000000.0} \
   ] $adc0_clk

  set dac0_clk [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 dac0_clk ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {6400000000.0} \
   ] $dac0_clk

  set led_bits [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 led_bits ]

  set sys_diff_clock [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 sys_diff_clock ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {100000000} \
   ] $sys_diff_clock

  set sysref_in [ create_bd_intf_port -mode Slave -vlnv xilinx.com:display_usp_rf_data_converter:diff_pins_rtl:1.0 sysref_in ]

  set vin0_01 [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_analog_io_rtl:1.0 vin0_01 ]

  set vout00 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:diff_analog_io_rtl:1.0 vout00 ]


  # Create ports
  set clk_adc0 [ create_bd_port -dir O -type clk clk_adc0 ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {125000000.0} \
 ] $clk_adc0
  set clk_dac0 [ create_bd_port -dir O -type clk clk_dac0 ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {400000000.0} \
 ] $clk_dac0
  set done_flag [ create_bd_port -dir O done_flag ]
  set emio_uart1_rxd_0 [ create_bd_port -dir I emio_uart1_rxd_0 ]
  set emio_uart1_txd_0 [ create_bd_port -dir O emio_uart1_txd_0 ]
  set error_flag [ create_bd_port -dir O error_flag ]
  set irq [ create_bd_port -dir O irq ]
  set reset [ create_bd_port -dir I -type rst reset ]
  set_property -dict [ list \
   CONFIG.POLARITY {ACTIVE_HIGH} \
 ] $reset

  # Create instance: adc_sink_i, and set properties
  set block_name exdes_rfadc_data_sink
  set block_cell_name adc_sink_i
  if { [catch {set adc_sink_i [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_msg_id "BD_TCL-105" "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $adc_sink_i eq "" } {
     catch {common::send_msg_id "BD_TCL-106" "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: axi_gpio, and set properties
  set axi_gpio [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio ]
  set_property -dict [ list \
   CONFIG.C_ALL_OUTPUTS {1} \
   CONFIG.C_GPIO_WIDTH {5} \
 ] $axi_gpio

  # Create instance: axi_intc, and set properties
  set axi_intc [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_intc:4.1 axi_intc ]
  set_property -dict [ list \
   CONFIG.C_IRQ_CONNECTION {1} \
 ] $axi_intc

  # Create instance: axi_interconnect_0, and set properties
  set axi_interconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_interconnect_0 ]
  set_property -dict [ list \
   CONFIG.NUM_MI {3} \
 ] $axi_interconnect_0

  # Create instance: chan_ctrl_fifo, and set properties
  set chan_ctrl_fifo [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:2.0 chan_ctrl_fifo ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {512} \
 ] $chan_ctrl_fifo

  # Create instance: chan_ctrl_reg, and set properties
  set chan_ctrl_reg [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 chan_ctrl_reg ]

  # Create instance: clk_wiz, and set properties
  set clk_wiz [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wiz ]
  set_property -dict [ list \
   CONFIG.CLKOUT1_JITTER {69.097} \
   CONFIG.CLKOUT1_PHASE_ERROR {76.967} \
   CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {667} \
   CONFIG.CLKOUT2_JITTER {79.341} \
   CONFIG.CLKOUT2_PHASE_ERROR {76.967} \
   CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {300} \
   CONFIG.CLKOUT2_USED {true} \
   CONFIG.CLKOUT3_JITTER {96.283} \
   CONFIG.CLKOUT3_PHASE_ERROR {76.967} \
   CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {100} \
   CONFIG.CLKOUT3_USED {true} \
   CONFIG.MMCM_CLKFBOUT_MULT_F {15.000} \
   CONFIG.MMCM_CLKOUT0_DIVIDE_F {2.250} \
   CONFIG.MMCM_CLKOUT1_DIVIDE {5} \
   CONFIG.MMCM_CLKOUT2_DIVIDE {15} \
   CONFIG.NUM_OUT_CLKS {3} \
   CONFIG.PRIM_SOURCE {Differential_clock_capable_pin} \
 ] $clk_wiz

  # Create instance: concat_int, and set properties
  set concat_int [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 concat_int ]
  set_property -dict [ list \
   CONFIG.NUM_PORTS {2} \
 ] $concat_int

  # Create instance: const_1, and set properties
  set const_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 const_1 ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {1} \
 ] $const_1

  # Create instance: dac_source_i, and set properties
  set block_name exdes_rfdac_src
  set block_cell_name dac_source_i
  if { [catch {set dac_source_i [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_msg_id "BD_TCL-105" "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $dac_source_i eq "" } {
     catch {common::send_msg_id "BD_TCL-106" "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: data_source, and set properties
  set data_source [ create_bd_cell -type ip -vlnv xilinx.com:hls:data_source_top:1.0 data_source ]

  # Create instance: dec_add_keep, and set properties
  set dec_add_keep [ create_bd_cell -type ip -vlnv xilinx.com:hls:add_keep_128:1.0 dec_add_keep ]

  # Create instance: dec_add_keep_trim, and set properties
  set dec_add_keep_trim [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 dec_add_keep_trim ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {2} \
 ] $dec_add_keep_trim

  # Create instance: dec_ctrl_fifo, and set properties
  set dec_ctrl_fifo [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:2.0 dec_ctrl_fifo ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {512} \
 ] $dec_ctrl_fifo

  # Create instance: dec_ctrl_reg, and set properties
  set dec_ctrl_reg [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 dec_ctrl_reg ]

  # Create instance: dec_ctrl_reinterpret, and set properties
  set dec_ctrl_reinterpret [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 dec_ctrl_reinterpret ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {4} \
 ] $dec_ctrl_reinterpret

  # Create instance: dec_data_reinterpret, and set properties
  set dec_data_reinterpret [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 dec_data_reinterpret ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {16} \
   CONFIG.S_TDATA_NUM_BYTES {16} \
   CONFIG.TDATA_REMAP {tdata[127:0]} \
 ] $dec_data_reinterpret

  # Create instance: dec_ip_mon, and set properties
  set dec_ip_mon [ create_bd_cell -type ip -vlnv xilinx.com:hls:monitor:1.0 dec_ip_mon ]

  # Create instance: dec_ip_probe, and set properties
  set dec_ip_probe [ create_bd_cell -type ip -vlnv xilinx.com:user:axis_probe:1.0 dec_ip_probe ]

  # Create instance: dec_keep_ctrl_fifo, and set properties
  set dec_keep_ctrl_fifo [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:2.0 dec_keep_ctrl_fifo ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {512} \
 ] $dec_keep_ctrl_fifo

  # Create instance: dec_op_mon, and set properties
  set dec_op_mon [ create_bd_cell -type ip -vlnv xilinx.com:hls:monitor:1.0 dec_op_mon ]

  # Create instance: dec_op_probe, and set properties
  set dec_op_probe [ create_bd_cell -type ip -vlnv xilinx.com:user:axis_probe:1.0 dec_op_probe ]

  # Create instance: dec_stat_reinterpret, and set properties
  set dec_stat_reinterpret [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 dec_stat_reinterpret ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {5} \
 ] $dec_stat_reinterpret

  # Create instance: demod, and set properties
  set demod [ create_bd_cell -type ip -vlnv xilinx.com:hls:demod_4x:1.0 demod ]

  # Create instance: enc_add_keep, and set properties
  set enc_add_keep [ create_bd_cell -type ip -vlnv xilinx.com:hls:add_keep_128:1.0 enc_add_keep ]

  # Create instance: enc_add_keep_trim, and set properties
  set enc_add_keep_trim [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 enc_add_keep_trim ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {2} \
 ] $enc_add_keep_trim

  # Create instance: enc_ctrl_reinterpret, and set properties
  set enc_ctrl_reinterpret [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 enc_ctrl_reinterpret ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {4} \
 ] $enc_ctrl_reinterpret

  # Create instance: enc_data_fifo, and set properties
  set enc_data_fifo [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:2.0 enc_data_fifo ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {32768} \
 ] $enc_data_fifo

  # Create instance: enc_data_reinterpret, and set properties
  set enc_data_reinterpret [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 enc_data_reinterpret ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {12} \
   CONFIG.S_TDATA_NUM_BYTES {16} \
   CONFIG.TDATA_REMAP {tdata[95:0]} \
 ] $enc_data_reinterpret

  # Create instance: enc_ip_mon, and set properties
  set enc_ip_mon [ create_bd_cell -type ip -vlnv xilinx.com:hls:monitor:1.0 enc_ip_mon ]

  # Create instance: enc_ip_probe, and set properties
  set enc_ip_probe [ create_bd_cell -type ip -vlnv xilinx.com:user:axis_probe:1.0 enc_ip_probe ]

  # Create instance: enc_keep_ctrl_fifo, and set properties
  set enc_keep_ctrl_fifo [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:2.0 enc_keep_ctrl_fifo ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {512} \
 ] $enc_keep_ctrl_fifo

  # Create instance: enc_op_mon, and set properties
  set enc_op_mon [ create_bd_cell -type ip -vlnv xilinx.com:hls:monitor:1.0 enc_op_mon ]

  # Create instance: enc_op_probe, and set properties
  set enc_op_probe [ create_bd_cell -type ip -vlnv xilinx.com:user:axis_probe:1.0 enc_op_probe ]

  # Create instance: gpio_reset, and set properties
  set gpio_reset [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 gpio_reset ]
  set_property -dict [ list \
   CONFIG.C_ALL_OUTPUTS {1} \
   CONFIG.C_GPIO_WIDTH {8} \
 ] $gpio_reset

  # Create instance: hard_chan_data_fifo, and set properties
  set hard_chan_data_fifo [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:2.0 hard_chan_data_fifo ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {16384} \
 ] $hard_chan_data_fifo

  # Create instance: hard_data_reg, and set properties
  set hard_data_reg [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 hard_data_reg ]

  # Create instance: llr_reinterpret, and set properties
  set llr_reinterpret [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.1 llr_reinterpret ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {32} \
   CONFIG.S_TDATA_NUM_BYTES {32} \
   CONFIG.TDATA_REMAP {tdata[255:128],tdata[127:0]} \
 ] $llr_reinterpret

  # Create instance: llr_reshape, and set properties
  set llr_reshape [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_dwidth_converter:1.1 llr_reshape ]
  set_property -dict [ list \
   CONFIG.M_TDATA_NUM_BYTES {32} \
 ] $llr_reshape

  # Create instance: mod_and_chan, and set properties
  set mod_and_chan [ create_bd_cell -type ip -vlnv xilinx.com:hls:mod_and_chan_4x:1.0 mod_and_chan ]

  # Create instance: reset_slice, and set properties
  set reset_slice [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 reset_slice ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {0} \
   CONFIG.DIN_TO {0} \
   CONFIG.DIN_WIDTH {8} \
 ] $reset_slice

  # Create instance: rst_clk_wiz_100M, and set properties
  set rst_clk_wiz_100M [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 rst_clk_wiz_100M ]

  # Create instance: rst_clk_wiz_300M, and set properties
  set rst_clk_wiz_300M [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 rst_clk_wiz_300M ]
  set_property -dict [ list \
   CONFIG.C_AUX_RESET_HIGH {1} \
 ] $rst_clk_wiz_300M

  # Create instance: rst_zynq_ultra_ps_e_0_99M, and set properties
  set rst_zynq_ultra_ps_e_0_99M [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 rst_zynq_ultra_ps_e_0_99M ]

  # Create instance: rtc, and set properties
  set rtc [ create_bd_cell -type ip -vlnv xilinx.com:ip:c_counter_binary:12.0 rtc ]
  set_property -dict [ list \
   CONFIG.Output_Width {32} \
   CONFIG.SCLR {true} \
 ] $rtc

  # Create instance: sd_fec_dec, and set properties
  set sd_fec_dec [ create_bd_cell -type ip -vlnv xilinx.com:ip:sd_fec:1.1 sd_fec_dec ]
  set_property -dict [ list \
   CONFIG.AXI_WR_Protect {false} \
   CONFIG.Activity {100} \
   CONFIG.Build_SDK_Project {true} \
   CONFIG.Bypass {false} \
   CONFIG.Code_WR_Protect {false} \
   CONFIG.DIN_Interface {Pre-Configured} \
   CONFIG.DIN_Lanes {2} \
   CONFIG.DIN_Words {16} \
   CONFIG.DIN_Words_Configuration {Fixed} \
   CONFIG.DOUT_Interface {Pre-Configured} \
   CONFIG.DOUT_Lanes {1} \
   CONFIG.DOUT_Words {16} \
   CONFIG.DOUT_Words_Configuration {Fixed} \
   CONFIG.ECC_Interrupts {None} \
   CONFIG.Enable_IFs {false} \
   CONFIG.Enable_Wgt1 {false} \
   CONFIG.Example_Design_PS_Type {ZYNQ_UltraScale+_RFSoC} \
   CONFIG.Include_Encoder {true} \
   CONFIG.Include_PS_Example_Design {true} \
   CONFIG.Interrupts {false} \
   CONFIG.LDPC_Decode {true} \
   CONFIG.LDPC_Decode_Code_Definition {../../../../../../project_1.srcs/sources_1/imports/pl_zcu111_sdfec_ps/all_code_def.txt} \
   CONFIG.LDPC_Decode_Max_Schedule {0} \
   CONFIG.LDPC_Decode_No_OPC {false} \
   CONFIG.LDPC_Decode_Overrides {false} \
   CONFIG.LDPC_Decode_Scale {12} \
   CONFIG.LDPC_Encode {false} \
   CONFIG.LD_PERCENT_LOAD {100} \
   CONFIG.LE_PERCENT_LOAD {0} \
   CONFIG.Out_of_Order {false} \
   CONFIG.Parameter_Interface {Runtime-Configured} \
   CONFIG.Percentage_Loading {Automatic} \
   CONFIG.Standard {Custom} \
   CONFIG.TD_PERCENT_LOAD {0} \
   CONFIG.Turbo_Decode {false} \
   CONFIG.Turbo_Decode_Algorithm {MaxScale} \
   CONFIG.Turbo_Decode_Scale {12} \
 ] $sd_fec_dec

  # Create instance: sd_fec_enc, and set properties
  set sd_fec_enc [ create_bd_cell -type ip -vlnv xilinx.com:ip:sd_fec:1.1 sd_fec_enc ]
  set_property -dict [ list \
   CONFIG.AXI_WR_Protect {false} \
   CONFIG.Activity {100} \
   CONFIG.Build_SDK_Project {true} \
   CONFIG.Bypass {false} \
   CONFIG.Code_WR_Protect {false} \
   CONFIG.DIN_Interface {Pre-Configured} \
   CONFIG.DIN_Lanes {1} \
   CONFIG.DIN_Words {16} \
   CONFIG.DIN_Words_Configuration {Fixed} \
   CONFIG.DOUT_Interface {Pre-Configured} \
   CONFIG.DOUT_Lanes {1} \
   CONFIG.DOUT_Words {12} \
   CONFIG.DOUT_Words_Configuration {Fixed} \
   CONFIG.ECC_Interrupts {None} \
   CONFIG.Enable_IFs {false} \
   CONFIG.Enable_Wgt1 {false} \
   CONFIG.Example_Design_PS_Type {ZYNQ_UltraScale+_RFSoC} \
   CONFIG.Include_Encoder {true} \
   CONFIG.Include_PS_Example_Design {true} \
   CONFIG.Interrupts {false} \
   CONFIG.LDPC_Decode {false} \
   CONFIG.LDPC_Decode_Max_Schedule {0} \
   CONFIG.LDPC_Decode_No_OPC {false} \
   CONFIG.LDPC_Decode_Overrides {false} \
   CONFIG.LDPC_Decode_Scale {12} \
   CONFIG.LDPC_Encode {true} \
   CONFIG.LDPC_Encode_Code_Definition {../../../../../../project_1.srcs/sources_1/imports/pl_zcu111_sdfec_ps/all_code_def.txt} \
   CONFIG.LD_PERCENT_LOAD {0} \
   CONFIG.LE_PERCENT_LOAD {100} \
   CONFIG.Out_of_Order {false} \
   CONFIG.Parameter_Interface {Runtime-Configured} \
   CONFIG.Percentage_Loading {Automatic} \
   CONFIG.Standard {Custom} \
   CONFIG.TD_PERCENT_LOAD {0} \
   CONFIG.Turbo_Decode {false} \
   CONFIG.Turbo_Decode_Algorithm {MaxScale} \
   CONFIG.Turbo_Decode_Scale {12} \
 ] $sd_fec_enc

  # Create instance: src_data_broadcast, and set properties
  set src_data_broadcast [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_broadcaster:1.1 src_data_broadcast ]

  # Create instance: src_data_fifo, and set properties
  set src_data_fifo [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:2.0 src_data_fifo ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {16384} \
 ] $src_data_fifo

  # Create instance: stats, and set properties
  set stats [ create_bd_cell -type ip -vlnv xilinx.com:hls:stats_top:1.0 stats ]

  # Create instance: usp_rf_data_converter_0_i, and set properties
  set usp_rf_data_converter_0_i [ create_bd_cell -type ip -vlnv xilinx.com:ip:usp_rf_data_converter:2.1 usp_rf_data_converter_0_i ]
  set_property -dict [ list \
   CONFIG.ADC0_Enable {1} \
   CONFIG.ADC0_Fabric_Freq {250.000} \
   CONFIG.ADC0_Link_Coupling {0} \
   CONFIG.ADC0_Multi_Tile_Sync {false} \
   CONFIG.ADC0_Outclk_Freq {125.000} \
   CONFIG.ADC0_Outdiv {2} \
   CONFIG.ADC0_PLL_Enable {false} \
   CONFIG.ADC0_Refclk_Freq {2000.000} \
   CONFIG.ADC0_Sampling_Rate {2.0} \
   CONFIG.ADC1_Enable {0} \
   CONFIG.ADC1_Fabric_Freq {0.0} \
   CONFIG.ADC1_Link_Coupling {0} \
   CONFIG.ADC1_Multi_Tile_Sync {false} \
   CONFIG.ADC1_Outclk_Freq {15.625} \
   CONFIG.ADC1_Outdiv {2} \
   CONFIG.ADC1_PLL_Enable {false} \
   CONFIG.ADC1_Refclk_Freq {2000.000} \
   CONFIG.ADC1_Sampling_Rate {2.0} \
   CONFIG.ADC224_En {false} \
   CONFIG.ADC225_En {false} \
   CONFIG.ADC226_En {false} \
   CONFIG.ADC227_En {false} \
   CONFIG.ADC2_Enable {0} \
   CONFIG.ADC2_Fabric_Freq {0.0} \
   CONFIG.ADC2_Link_Coupling {0} \
   CONFIG.ADC2_Multi_Tile_Sync {false} \
   CONFIG.ADC2_Outclk_Freq {15.625} \
   CONFIG.ADC2_Outdiv {2} \
   CONFIG.ADC2_PLL_Enable {false} \
   CONFIG.ADC2_Refclk_Freq {2000.000} \
   CONFIG.ADC2_Sampling_Rate {2.0} \
   CONFIG.ADC3_Enable {0} \
   CONFIG.ADC3_Fabric_Freq {0.0} \
   CONFIG.ADC3_Link_Coupling {0} \
   CONFIG.ADC3_Multi_Tile_Sync {false} \
   CONFIG.ADC3_Outclk_Freq {15.625} \
   CONFIG.ADC3_Outdiv {2} \
   CONFIG.ADC3_PLL_Enable {false} \
   CONFIG.ADC3_Refclk_Freq {2000.000} \
   CONFIG.ADC3_Sampling_Rate {2.0} \
   CONFIG.ADC_CalOpt_Mode00 {1} \
   CONFIG.ADC_CalOpt_Mode01 {1} \
   CONFIG.ADC_CalOpt_Mode02 {1} \
   CONFIG.ADC_CalOpt_Mode03 {1} \
   CONFIG.ADC_CalOpt_Mode10 {1} \
   CONFIG.ADC_CalOpt_Mode11 {1} \
   CONFIG.ADC_CalOpt_Mode12 {1} \
   CONFIG.ADC_CalOpt_Mode13 {1} \
   CONFIG.ADC_CalOpt_Mode20 {1} \
   CONFIG.ADC_CalOpt_Mode21 {1} \
   CONFIG.ADC_CalOpt_Mode22 {1} \
   CONFIG.ADC_CalOpt_Mode23 {1} \
   CONFIG.ADC_CalOpt_Mode30 {1} \
   CONFIG.ADC_CalOpt_Mode31 {1} \
   CONFIG.ADC_CalOpt_Mode32 {1} \
   CONFIG.ADC_CalOpt_Mode33 {1} \
   CONFIG.ADC_Coarse_Mixer_Freq00 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq01 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq02 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq03 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq10 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq11 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq12 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq13 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq20 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq21 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq22 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq23 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq30 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq31 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq32 {0} \
   CONFIG.ADC_Coarse_Mixer_Freq33 {0} \
   CONFIG.ADC_Data_Type00 {0} \
   CONFIG.ADC_Data_Type01 {0} \
   CONFIG.ADC_Data_Type02 {0} \
   CONFIG.ADC_Data_Type03 {0} \
   CONFIG.ADC_Data_Type10 {0} \
   CONFIG.ADC_Data_Type11 {0} \
   CONFIG.ADC_Data_Type12 {0} \
   CONFIG.ADC_Data_Type13 {0} \
   CONFIG.ADC_Data_Type20 {0} \
   CONFIG.ADC_Data_Type21 {0} \
   CONFIG.ADC_Data_Type22 {0} \
   CONFIG.ADC_Data_Type23 {0} \
   CONFIG.ADC_Data_Type30 {0} \
   CONFIG.ADC_Data_Type31 {0} \
   CONFIG.ADC_Data_Type32 {0} \
   CONFIG.ADC_Data_Type33 {0} \
   CONFIG.ADC_Data_Width00 {8} \
   CONFIG.ADC_Data_Width01 {8} \
   CONFIG.ADC_Data_Width02 {8} \
   CONFIG.ADC_Data_Width03 {8} \
   CONFIG.ADC_Data_Width10 {8} \
   CONFIG.ADC_Data_Width11 {8} \
   CONFIG.ADC_Data_Width12 {8} \
   CONFIG.ADC_Data_Width13 {8} \
   CONFIG.ADC_Data_Width20 {8} \
   CONFIG.ADC_Data_Width21 {8} \
   CONFIG.ADC_Data_Width22 {8} \
   CONFIG.ADC_Data_Width23 {8} \
   CONFIG.ADC_Data_Width30 {8} \
   CONFIG.ADC_Data_Width31 {8} \
   CONFIG.ADC_Data_Width32 {8} \
   CONFIG.ADC_Data_Width33 {8} \
   CONFIG.ADC_Debug {false} \
   CONFIG.ADC_Decimation_Mode00 {1} \
   CONFIG.ADC_Decimation_Mode01 {1} \
   CONFIG.ADC_Decimation_Mode02 {0} \
   CONFIG.ADC_Decimation_Mode03 {0} \
   CONFIG.ADC_Decimation_Mode10 {0} \
   CONFIG.ADC_Decimation_Mode11 {0} \
   CONFIG.ADC_Decimation_Mode12 {0} \
   CONFIG.ADC_Decimation_Mode13 {0} \
   CONFIG.ADC_Decimation_Mode20 {0} \
   CONFIG.ADC_Decimation_Mode21 {0} \
   CONFIG.ADC_Decimation_Mode22 {0} \
   CONFIG.ADC_Decimation_Mode23 {0} \
   CONFIG.ADC_Decimation_Mode30 {0} \
   CONFIG.ADC_Decimation_Mode31 {0} \
   CONFIG.ADC_Decimation_Mode32 {0} \
   CONFIG.ADC_Decimation_Mode33 {0} \
   CONFIG.ADC_Dither00 {true} \
   CONFIG.ADC_Dither01 {true} \
   CONFIG.ADC_Dither02 {true} \
   CONFIG.ADC_Dither03 {true} \
   CONFIG.ADC_Dither10 {true} \
   CONFIG.ADC_Dither11 {true} \
   CONFIG.ADC_Dither12 {true} \
   CONFIG.ADC_Dither13 {true} \
   CONFIG.ADC_Dither20 {true} \
   CONFIG.ADC_Dither21 {true} \
   CONFIG.ADC_Dither22 {true} \
   CONFIG.ADC_Dither23 {true} \
   CONFIG.ADC_Dither30 {true} \
   CONFIG.ADC_Dither31 {true} \
   CONFIG.ADC_Dither32 {true} \
   CONFIG.ADC_Dither33 {true} \
   CONFIG.ADC_Mixer_Mode00 {2} \
   CONFIG.ADC_Mixer_Mode01 {2} \
   CONFIG.ADC_Mixer_Mode02 {2} \
   CONFIG.ADC_Mixer_Mode03 {2} \
   CONFIG.ADC_Mixer_Mode10 {2} \
   CONFIG.ADC_Mixer_Mode11 {2} \
   CONFIG.ADC_Mixer_Mode12 {2} \
   CONFIG.ADC_Mixer_Mode13 {2} \
   CONFIG.ADC_Mixer_Mode20 {2} \
   CONFIG.ADC_Mixer_Mode21 {2} \
   CONFIG.ADC_Mixer_Mode22 {2} \
   CONFIG.ADC_Mixer_Mode23 {2} \
   CONFIG.ADC_Mixer_Mode30 {2} \
   CONFIG.ADC_Mixer_Mode31 {2} \
   CONFIG.ADC_Mixer_Mode32 {2} \
   CONFIG.ADC_Mixer_Mode33 {2} \
   CONFIG.ADC_Mixer_Type00 {0} \
   CONFIG.ADC_Mixer_Type01 {0} \
   CONFIG.ADC_Mixer_Type02 {3} \
   CONFIG.ADC_Mixer_Type03 {3} \
   CONFIG.ADC_Mixer_Type10 {3} \
   CONFIG.ADC_Mixer_Type11 {3} \
   CONFIG.ADC_Mixer_Type12 {3} \
   CONFIG.ADC_Mixer_Type13 {3} \
   CONFIG.ADC_Mixer_Type20 {3} \
   CONFIG.ADC_Mixer_Type21 {3} \
   CONFIG.ADC_Mixer_Type22 {3} \
   CONFIG.ADC_Mixer_Type23 {3} \
   CONFIG.ADC_Mixer_Type30 {3} \
   CONFIG.ADC_Mixer_Type31 {3} \
   CONFIG.ADC_Mixer_Type32 {3} \
   CONFIG.ADC_Mixer_Type33 {3} \
   CONFIG.ADC_NCO_Freq00 {0.0} \
   CONFIG.ADC_NCO_Freq01 {0.0} \
   CONFIG.ADC_NCO_Freq02 {0.0} \
   CONFIG.ADC_NCO_Freq03 {0.0} \
   CONFIG.ADC_NCO_Freq10 {0.0} \
   CONFIG.ADC_NCO_Freq11 {0.0} \
   CONFIG.ADC_NCO_Freq12 {0.0} \
   CONFIG.ADC_NCO_Freq13 {0.0} \
   CONFIG.ADC_NCO_Freq20 {0.0} \
   CONFIG.ADC_NCO_Freq21 {0.0} \
   CONFIG.ADC_NCO_Freq22 {0.0} \
   CONFIG.ADC_NCO_Freq23 {0.0} \
   CONFIG.ADC_NCO_Freq30 {0.0} \
   CONFIG.ADC_NCO_Freq31 {0.0} \
   CONFIG.ADC_NCO_Freq32 {0.0} \
   CONFIG.ADC_NCO_Freq33 {0.0} \
   CONFIG.ADC_NCO_Phase00 {0} \
   CONFIG.ADC_NCO_Phase01 {0} \
   CONFIG.ADC_NCO_Phase02 {0} \
   CONFIG.ADC_NCO_Phase03 {0} \
   CONFIG.ADC_NCO_Phase10 {0} \
   CONFIG.ADC_NCO_Phase11 {0} \
   CONFIG.ADC_NCO_Phase12 {0} \
   CONFIG.ADC_NCO_Phase13 {0} \
   CONFIG.ADC_NCO_Phase20 {0} \
   CONFIG.ADC_NCO_Phase21 {0} \
   CONFIG.ADC_NCO_Phase22 {0} \
   CONFIG.ADC_NCO_Phase23 {0} \
   CONFIG.ADC_NCO_Phase30 {0} \
   CONFIG.ADC_NCO_Phase31 {0} \
   CONFIG.ADC_NCO_Phase32 {0} \
   CONFIG.ADC_NCO_Phase33 {0} \
   CONFIG.ADC_Neg_Quadrature00 {false} \
   CONFIG.ADC_Neg_Quadrature01 {false} \
   CONFIG.ADC_Neg_Quadrature02 {false} \
   CONFIG.ADC_Neg_Quadrature03 {false} \
   CONFIG.ADC_Neg_Quadrature10 {false} \
   CONFIG.ADC_Neg_Quadrature11 {false} \
   CONFIG.ADC_Neg_Quadrature12 {false} \
   CONFIG.ADC_Neg_Quadrature13 {false} \
   CONFIG.ADC_Neg_Quadrature20 {false} \
   CONFIG.ADC_Neg_Quadrature21 {false} \
   CONFIG.ADC_Neg_Quadrature22 {false} \
   CONFIG.ADC_Neg_Quadrature23 {false} \
   CONFIG.ADC_Neg_Quadrature30 {false} \
   CONFIG.ADC_Neg_Quadrature31 {false} \
   CONFIG.ADC_Neg_Quadrature32 {false} \
   CONFIG.ADC_Neg_Quadrature33 {false} \
   CONFIG.ADC_Nyquist00 {0} \
   CONFIG.ADC_Nyquist01 {0} \
   CONFIG.ADC_Nyquist02 {0} \
   CONFIG.ADC_Nyquist03 {0} \
   CONFIG.ADC_Nyquist10 {0} \
   CONFIG.ADC_Nyquist11 {0} \
   CONFIG.ADC_Nyquist12 {0} \
   CONFIG.ADC_Nyquist13 {0} \
   CONFIG.ADC_Nyquist20 {0} \
   CONFIG.ADC_Nyquist21 {0} \
   CONFIG.ADC_Nyquist22 {0} \
   CONFIG.ADC_Nyquist23 {0} \
   CONFIG.ADC_Nyquist30 {0} \
   CONFIG.ADC_Nyquist31 {0} \
   CONFIG.ADC_Nyquist32 {0} \
   CONFIG.ADC_Nyquist33 {0} \
   CONFIG.ADC_RTS {false} \
   CONFIG.ADC_Slice00_Enable {true} \
   CONFIG.ADC_Slice01_Enable {true} \
   CONFIG.ADC_Slice02_Enable {false} \
   CONFIG.ADC_Slice03_Enable {false} \
   CONFIG.ADC_Slice10_Enable {false} \
   CONFIG.ADC_Slice11_Enable {false} \
   CONFIG.ADC_Slice12_Enable {false} \
   CONFIG.ADC_Slice13_Enable {false} \
   CONFIG.ADC_Slice20_Enable {false} \
   CONFIG.ADC_Slice21_Enable {false} \
   CONFIG.ADC_Slice22_Enable {false} \
   CONFIG.ADC_Slice23_Enable {false} \
   CONFIG.ADC_Slice30_Enable {false} \
   CONFIG.ADC_Slice31_Enable {false} \
   CONFIG.ADC_Slice32_Enable {false} \
   CONFIG.ADC_Slice33_Enable {false} \
   CONFIG.AMS_Factory_Var {0} \
   CONFIG.Analog_Detection {1} \
   CONFIG.Auto_Calibration_Freeze {false} \
   CONFIG.Axiclk_Freq {100.0} \
   CONFIG.Calibration_Freeze {false} \
   CONFIG.Calibration_Time {10} \
   CONFIG.Clock_Forwarding {false} \
   CONFIG.Converter_Setup {1} \
   CONFIG.DAC0_Enable {1} \
   CONFIG.DAC0_Fabric_Freq {400.000} \
   CONFIG.DAC0_Multi_Tile_Sync {false} \
   CONFIG.DAC0_Outclk_Freq {400.000} \
   CONFIG.DAC0_Outdiv {2} \
   CONFIG.DAC0_PLL_Enable {false} \
   CONFIG.DAC0_Refclk_Freq {6400.000} \
   CONFIG.DAC0_Sampling_Rate {6.4} \
   CONFIG.DAC1_Enable {0} \
   CONFIG.DAC1_Fabric_Freq {0.0} \
   CONFIG.DAC1_Multi_Tile_Sync {false} \
   CONFIG.DAC1_Outclk_Freq {50.000} \
   CONFIG.DAC1_Outdiv {2} \
   CONFIG.DAC1_PLL_Enable {false} \
   CONFIG.DAC1_Refclk_Freq {6400.000} \
   CONFIG.DAC1_Sampling_Rate {6.4} \
   CONFIG.DAC228_En {false} \
   CONFIG.DAC229_En {false} \
   CONFIG.DAC230_En {false} \
   CONFIG.DAC231_En {false} \
   CONFIG.DAC2_Enable {0} \
   CONFIG.DAC2_Fabric_Freq {0.0} \
   CONFIG.DAC2_Multi_Tile_Sync {false} \
   CONFIG.DAC2_Outclk_Freq {50.000} \
   CONFIG.DAC2_Outdiv {2} \
   CONFIG.DAC2_PLL_Enable {false} \
   CONFIG.DAC2_Refclk_Freq {6400.000} \
   CONFIG.DAC2_Sampling_Rate {6.4} \
   CONFIG.DAC3_Enable {0} \
   CONFIG.DAC3_Fabric_Freq {0.0} \
   CONFIG.DAC3_Multi_Tile_Sync {false} \
   CONFIG.DAC3_Outclk_Freq {50.000} \
   CONFIG.DAC3_Outdiv {2} \
   CONFIG.DAC3_PLL_Enable {false} \
   CONFIG.DAC3_Refclk_Freq {6400.000} \
   CONFIG.DAC3_Sampling_Rate {6.4} \
   CONFIG.DAC_Coarse_Mixer_Freq00 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq01 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq02 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq03 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq10 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq11 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq12 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq13 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq20 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq21 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq22 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq23 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq30 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq31 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq32 {0} \
   CONFIG.DAC_Coarse_Mixer_Freq33 {0} \
   CONFIG.DAC_Data_Type00 {0} \
   CONFIG.DAC_Data_Type01 {0} \
   CONFIG.DAC_Data_Type02 {0} \
   CONFIG.DAC_Data_Type03 {0} \
   CONFIG.DAC_Data_Type10 {0} \
   CONFIG.DAC_Data_Type11 {0} \
   CONFIG.DAC_Data_Type12 {0} \
   CONFIG.DAC_Data_Type13 {0} \
   CONFIG.DAC_Data_Type20 {0} \
   CONFIG.DAC_Data_Type21 {0} \
   CONFIG.DAC_Data_Type22 {0} \
   CONFIG.DAC_Data_Type23 {0} \
   CONFIG.DAC_Data_Type30 {0} \
   CONFIG.DAC_Data_Type31 {0} \
   CONFIG.DAC_Data_Type32 {0} \
   CONFIG.DAC_Data_Type33 {0} \
   CONFIG.DAC_Data_Width00 {16} \
   CONFIG.DAC_Data_Width01 {16} \
   CONFIG.DAC_Data_Width02 {16} \
   CONFIG.DAC_Data_Width03 {16} \
   CONFIG.DAC_Data_Width10 {16} \
   CONFIG.DAC_Data_Width11 {16} \
   CONFIG.DAC_Data_Width12 {16} \
   CONFIG.DAC_Data_Width13 {16} \
   CONFIG.DAC_Data_Width20 {16} \
   CONFIG.DAC_Data_Width21 {16} \
   CONFIG.DAC_Data_Width22 {16} \
   CONFIG.DAC_Data_Width23 {16} \
   CONFIG.DAC_Data_Width30 {16} \
   CONFIG.DAC_Data_Width31 {16} \
   CONFIG.DAC_Data_Width32 {16} \
   CONFIG.DAC_Data_Width33 {16} \
   CONFIG.DAC_Debug {false} \
   CONFIG.DAC_Decoder_Mode00 {0} \
   CONFIG.DAC_Decoder_Mode01 {0} \
   CONFIG.DAC_Decoder_Mode02 {0} \
   CONFIG.DAC_Decoder_Mode03 {0} \
   CONFIG.DAC_Decoder_Mode10 {0} \
   CONFIG.DAC_Decoder_Mode11 {0} \
   CONFIG.DAC_Decoder_Mode12 {0} \
   CONFIG.DAC_Decoder_Mode13 {0} \
   CONFIG.DAC_Decoder_Mode20 {0} \
   CONFIG.DAC_Decoder_Mode21 {0} \
   CONFIG.DAC_Decoder_Mode22 {0} \
   CONFIG.DAC_Decoder_Mode23 {0} \
   CONFIG.DAC_Decoder_Mode30 {0} \
   CONFIG.DAC_Decoder_Mode31 {0} \
   CONFIG.DAC_Decoder_Mode32 {0} \
   CONFIG.DAC_Decoder_Mode33 {0} \
   CONFIG.DAC_Interpolation_Mode00 {1} \
   CONFIG.DAC_Interpolation_Mode01 {0} \
   CONFIG.DAC_Interpolation_Mode02 {0} \
   CONFIG.DAC_Interpolation_Mode03 {0} \
   CONFIG.DAC_Interpolation_Mode10 {0} \
   CONFIG.DAC_Interpolation_Mode11 {0} \
   CONFIG.DAC_Interpolation_Mode12 {0} \
   CONFIG.DAC_Interpolation_Mode13 {0} \
   CONFIG.DAC_Interpolation_Mode20 {0} \
   CONFIG.DAC_Interpolation_Mode21 {0} \
   CONFIG.DAC_Interpolation_Mode22 {0} \
   CONFIG.DAC_Interpolation_Mode23 {0} \
   CONFIG.DAC_Interpolation_Mode30 {0} \
   CONFIG.DAC_Interpolation_Mode31 {0} \
   CONFIG.DAC_Interpolation_Mode32 {0} \
   CONFIG.DAC_Interpolation_Mode33 {0} \
   CONFIG.DAC_Invsinc_Ctrl00 {false} \
   CONFIG.DAC_Invsinc_Ctrl01 {false} \
   CONFIG.DAC_Invsinc_Ctrl02 {false} \
   CONFIG.DAC_Invsinc_Ctrl03 {false} \
   CONFIG.DAC_Invsinc_Ctrl10 {false} \
   CONFIG.DAC_Invsinc_Ctrl11 {false} \
   CONFIG.DAC_Invsinc_Ctrl12 {false} \
   CONFIG.DAC_Invsinc_Ctrl13 {false} \
   CONFIG.DAC_Invsinc_Ctrl20 {false} \
   CONFIG.DAC_Invsinc_Ctrl21 {false} \
   CONFIG.DAC_Invsinc_Ctrl22 {false} \
   CONFIG.DAC_Invsinc_Ctrl23 {false} \
   CONFIG.DAC_Invsinc_Ctrl30 {false} \
   CONFIG.DAC_Invsinc_Ctrl31 {false} \
   CONFIG.DAC_Invsinc_Ctrl32 {false} \
   CONFIG.DAC_Invsinc_Ctrl33 {false} \
   CONFIG.DAC_Mixer_Mode00 {2} \
   CONFIG.DAC_Mixer_Mode01 {2} \
   CONFIG.DAC_Mixer_Mode02 {2} \
   CONFIG.DAC_Mixer_Mode03 {2} \
   CONFIG.DAC_Mixer_Mode10 {2} \
   CONFIG.DAC_Mixer_Mode11 {2} \
   CONFIG.DAC_Mixer_Mode12 {2} \
   CONFIG.DAC_Mixer_Mode13 {2} \
   CONFIG.DAC_Mixer_Mode20 {2} \
   CONFIG.DAC_Mixer_Mode21 {2} \
   CONFIG.DAC_Mixer_Mode22 {2} \
   CONFIG.DAC_Mixer_Mode23 {2} \
   CONFIG.DAC_Mixer_Mode30 {2} \
   CONFIG.DAC_Mixer_Mode31 {2} \
   CONFIG.DAC_Mixer_Mode32 {2} \
   CONFIG.DAC_Mixer_Mode33 {2} \
   CONFIG.DAC_Mixer_Type00 {0} \
   CONFIG.DAC_Mixer_Type01 {3} \
   CONFIG.DAC_Mixer_Type02 {3} \
   CONFIG.DAC_Mixer_Type03 {3} \
   CONFIG.DAC_Mixer_Type10 {3} \
   CONFIG.DAC_Mixer_Type11 {3} \
   CONFIG.DAC_Mixer_Type12 {3} \
   CONFIG.DAC_Mixer_Type13 {3} \
   CONFIG.DAC_Mixer_Type20 {3} \
   CONFIG.DAC_Mixer_Type21 {3} \
   CONFIG.DAC_Mixer_Type22 {3} \
   CONFIG.DAC_Mixer_Type23 {3} \
   CONFIG.DAC_Mixer_Type30 {3} \
   CONFIG.DAC_Mixer_Type31 {3} \
   CONFIG.DAC_Mixer_Type32 {3} \
   CONFIG.DAC_Mixer_Type33 {3} \
   CONFIG.DAC_NCO_Freq00 {0.0} \
   CONFIG.DAC_NCO_Freq01 {0.0} \
   CONFIG.DAC_NCO_Freq02 {0.0} \
   CONFIG.DAC_NCO_Freq03 {0.0} \
   CONFIG.DAC_NCO_Freq10 {0.0} \
   CONFIG.DAC_NCO_Freq11 {0.0} \
   CONFIG.DAC_NCO_Freq12 {0.0} \
   CONFIG.DAC_NCO_Freq13 {0.0} \
   CONFIG.DAC_NCO_Freq20 {0.0} \
   CONFIG.DAC_NCO_Freq21 {0.0} \
   CONFIG.DAC_NCO_Freq22 {0.0} \
   CONFIG.DAC_NCO_Freq23 {0.0} \
   CONFIG.DAC_NCO_Freq30 {0.0} \
   CONFIG.DAC_NCO_Freq31 {0.0} \
   CONFIG.DAC_NCO_Freq32 {0.0} \
   CONFIG.DAC_NCO_Freq33 {0.0} \
   CONFIG.DAC_NCO_Phase00 {0} \
   CONFIG.DAC_NCO_Phase01 {0} \
   CONFIG.DAC_NCO_Phase02 {0} \
   CONFIG.DAC_NCO_Phase03 {0} \
   CONFIG.DAC_NCO_Phase10 {0} \
   CONFIG.DAC_NCO_Phase11 {0} \
   CONFIG.DAC_NCO_Phase12 {0} \
   CONFIG.DAC_NCO_Phase13 {0} \
   CONFIG.DAC_NCO_Phase20 {0} \
   CONFIG.DAC_NCO_Phase21 {0} \
   CONFIG.DAC_NCO_Phase22 {0} \
   CONFIG.DAC_NCO_Phase23 {0} \
   CONFIG.DAC_NCO_Phase30 {0} \
   CONFIG.DAC_NCO_Phase31 {0} \
   CONFIG.DAC_NCO_Phase32 {0} \
   CONFIG.DAC_NCO_Phase33 {0} \
   CONFIG.DAC_Neg_Quadrature00 {false} \
   CONFIG.DAC_Neg_Quadrature01 {false} \
   CONFIG.DAC_Neg_Quadrature02 {false} \
   CONFIG.DAC_Neg_Quadrature03 {false} \
   CONFIG.DAC_Neg_Quadrature10 {false} \
   CONFIG.DAC_Neg_Quadrature11 {false} \
   CONFIG.DAC_Neg_Quadrature12 {false} \
   CONFIG.DAC_Neg_Quadrature13 {false} \
   CONFIG.DAC_Neg_Quadrature20 {false} \
   CONFIG.DAC_Neg_Quadrature21 {false} \
   CONFIG.DAC_Neg_Quadrature22 {false} \
   CONFIG.DAC_Neg_Quadrature23 {false} \
   CONFIG.DAC_Neg_Quadrature30 {false} \
   CONFIG.DAC_Neg_Quadrature31 {false} \
   CONFIG.DAC_Neg_Quadrature32 {false} \
   CONFIG.DAC_Neg_Quadrature33 {false} \
   CONFIG.DAC_Nyquist00 {0} \
   CONFIG.DAC_Nyquist01 {0} \
   CONFIG.DAC_Nyquist02 {0} \
   CONFIG.DAC_Nyquist03 {0} \
   CONFIG.DAC_Nyquist10 {0} \
   CONFIG.DAC_Nyquist11 {0} \
   CONFIG.DAC_Nyquist12 {0} \
   CONFIG.DAC_Nyquist13 {0} \
   CONFIG.DAC_Nyquist20 {0} \
   CONFIG.DAC_Nyquist21 {0} \
   CONFIG.DAC_Nyquist22 {0} \
   CONFIG.DAC_Nyquist23 {0} \
   CONFIG.DAC_Nyquist30 {0} \
   CONFIG.DAC_Nyquist31 {0} \
   CONFIG.DAC_Nyquist32 {0} \
   CONFIG.DAC_Nyquist33 {0} \
   CONFIG.DAC_Output_Current {0} \
   CONFIG.DAC_RTS {false} \
   CONFIG.DAC_Slice00_Enable {true} \
   CONFIG.DAC_Slice01_Enable {false} \
   CONFIG.DAC_Slice02_Enable {false} \
   CONFIG.DAC_Slice03_Enable {false} \
   CONFIG.DAC_Slice10_Enable {false} \
   CONFIG.DAC_Slice11_Enable {false} \
   CONFIG.DAC_Slice12_Enable {false} \
   CONFIG.DAC_Slice13_Enable {false} \
   CONFIG.DAC_Slice20_Enable {false} \
   CONFIG.DAC_Slice21_Enable {false} \
   CONFIG.DAC_Slice22_Enable {false} \
   CONFIG.DAC_Slice23_Enable {false} \
   CONFIG.DAC_Slice30_Enable {false} \
   CONFIG.DAC_Slice31_Enable {false} \
   CONFIG.DAC_Slice32_Enable {false} \
   CONFIG.DAC_Slice33_Enable {false} \
   CONFIG.PRESET {None} \
   CONFIG.Sysref_Source {1} \
   CONFIG.VNC_Testing {false} \
   CONFIG.disable_bg_cal_en {0} \
   CONFIG.mADC_CalOpt_Mode00 {1} \
   CONFIG.mADC_CalOpt_Mode01 {1} \
   CONFIG.mADC_CalOpt_Mode02 {1} \
   CONFIG.mADC_CalOpt_Mode03 {1} \
   CONFIG.mADC_Coarse_Mixer_Freq00 {0} \
   CONFIG.mADC_Coarse_Mixer_Freq01 {0} \
   CONFIG.mADC_Coarse_Mixer_Freq02 {0} \
   CONFIG.mADC_Coarse_Mixer_Freq03 {0} \
   CONFIG.mADC_Data_Type00 {0} \
   CONFIG.mADC_Data_Type01 {0} \
   CONFIG.mADC_Data_Type02 {0} \
   CONFIG.mADC_Data_Type03 {0} \
   CONFIG.mADC_Data_Width00 {8} \
   CONFIG.mADC_Data_Width01 {8} \
   CONFIG.mADC_Data_Width02 {8} \
   CONFIG.mADC_Data_Width03 {8} \
   CONFIG.mADC_Decimation_Mode00 {0} \
   CONFIG.mADC_Decimation_Mode01 {0} \
   CONFIG.mADC_Decimation_Mode02 {0} \
   CONFIG.mADC_Decimation_Mode03 {0} \
   CONFIG.mADC_Dither00 {true} \
   CONFIG.mADC_Dither01 {true} \
   CONFIG.mADC_Dither02 {true} \
   CONFIG.mADC_Dither03 {true} \
   CONFIG.mADC_Enable {0} \
   CONFIG.mADC_Fabric_Freq {0.0} \
   CONFIG.mADC_Link_Coupling {0} \
   CONFIG.mADC_Mixer_Mode00 {2} \
   CONFIG.mADC_Mixer_Mode01 {2} \
   CONFIG.mADC_Mixer_Mode02 {2} \
   CONFIG.mADC_Mixer_Mode03 {2} \
   CONFIG.mADC_Mixer_Type00 {3} \
   CONFIG.mADC_Mixer_Type01 {3} \
   CONFIG.mADC_Mixer_Type02 {3} \
   CONFIG.mADC_Mixer_Type03 {3} \
   CONFIG.mADC_Multi_Tile_Sync {false} \
   CONFIG.mADC_NCO_Freq00 {0.0} \
   CONFIG.mADC_NCO_Freq01 {0.0} \
   CONFIG.mADC_NCO_Freq02 {0.0} \
   CONFIG.mADC_NCO_Freq03 {0.0} \
   CONFIG.mADC_NCO_Phase00 {0} \
   CONFIG.mADC_NCO_Phase01 {0} \
   CONFIG.mADC_NCO_Phase02 {0} \
   CONFIG.mADC_NCO_Phase03 {0} \
   CONFIG.mADC_Neg_Quadrature00 {false} \
   CONFIG.mADC_Neg_Quadrature01 {false} \
   CONFIG.mADC_Neg_Quadrature02 {false} \
   CONFIG.mADC_Neg_Quadrature03 {false} \
   CONFIG.mADC_Nyquist00 {0} \
   CONFIG.mADC_Nyquist01 {0} \
   CONFIG.mADC_Nyquist02 {0} \
   CONFIG.mADC_Nyquist03 {0} \
   CONFIG.mADC_Outclk_Freq {15.625} \
   CONFIG.mADC_PLL_Enable {false} \
   CONFIG.mADC_Refclk_Freq {2000.000} \
   CONFIG.mADC_Sampling_Rate {2.0} \
   CONFIG.mADC_Slice00_Enable {false} \
   CONFIG.mADC_Slice01_Enable {false} \
   CONFIG.mADC_Slice02_Enable {false} \
   CONFIG.mADC_Slice03_Enable {false} \
   CONFIG.mDAC_Coarse_Mixer_Freq00 {0} \
   CONFIG.mDAC_Coarse_Mixer_Freq01 {0} \
   CONFIG.mDAC_Coarse_Mixer_Freq02 {0} \
   CONFIG.mDAC_Coarse_Mixer_Freq03 {0} \
   CONFIG.mDAC_Data_Type00 {0} \
   CONFIG.mDAC_Data_Type01 {0} \
   CONFIG.mDAC_Data_Type02 {0} \
   CONFIG.mDAC_Data_Type03 {0} \
   CONFIG.mDAC_Data_Width00 {16} \
   CONFIG.mDAC_Data_Width01 {16} \
   CONFIG.mDAC_Data_Width02 {16} \
   CONFIG.mDAC_Data_Width03 {16} \
   CONFIG.mDAC_Decoder_Mode00 {0} \
   CONFIG.mDAC_Decoder_Mode01 {0} \
   CONFIG.mDAC_Decoder_Mode02 {0} \
   CONFIG.mDAC_Decoder_Mode03 {0} \
   CONFIG.mDAC_Enable {0} \
   CONFIG.mDAC_Fabric_Freq {0.0} \
   CONFIG.mDAC_Interpolation_Mode00 {0} \
   CONFIG.mDAC_Interpolation_Mode01 {0} \
   CONFIG.mDAC_Interpolation_Mode02 {0} \
   CONFIG.mDAC_Interpolation_Mode03 {0} \
   CONFIG.mDAC_Invsinc_Ctrl00 {false} \
   CONFIG.mDAC_Invsinc_Ctrl01 {false} \
   CONFIG.mDAC_Invsinc_Ctrl02 {false} \
   CONFIG.mDAC_Invsinc_Ctrl03 {false} \
   CONFIG.mDAC_Mixer_Mode00 {2} \
   CONFIG.mDAC_Mixer_Mode01 {2} \
   CONFIG.mDAC_Mixer_Mode02 {2} \
   CONFIG.mDAC_Mixer_Mode03 {2} \
   CONFIG.mDAC_Mixer_Type00 {3} \
   CONFIG.mDAC_Mixer_Type01 {3} \
   CONFIG.mDAC_Mixer_Type02 {3} \
   CONFIG.mDAC_Mixer_Type03 {3} \
   CONFIG.mDAC_Multi_Tile_Sync {false} \
   CONFIG.mDAC_NCO_Freq00 {0.0} \
   CONFIG.mDAC_NCO_Freq01 {0.0} \
   CONFIG.mDAC_NCO_Freq02 {0.0} \
   CONFIG.mDAC_NCO_Freq03 {0.0} \
   CONFIG.mDAC_NCO_Phase00 {0} \
   CONFIG.mDAC_NCO_Phase01 {0} \
   CONFIG.mDAC_NCO_Phase02 {0} \
   CONFIG.mDAC_NCO_Phase03 {0} \
   CONFIG.mDAC_Neg_Quadrature00 {false} \
   CONFIG.mDAC_Neg_Quadrature01 {false} \
   CONFIG.mDAC_Neg_Quadrature02 {false} \
   CONFIG.mDAC_Neg_Quadrature03 {false} \
   CONFIG.mDAC_Nyquist00 {0} \
   CONFIG.mDAC_Nyquist01 {0} \
   CONFIG.mDAC_Nyquist02 {0} \
   CONFIG.mDAC_Nyquist03 {0} \
   CONFIG.mDAC_Outclk_Freq {50.000} \
   CONFIG.mDAC_PLL_Enable {false} \
   CONFIG.mDAC_Refclk_Freq {6400.000} \
   CONFIG.mDAC_Sampling_Rate {6.4} \
   CONFIG.mDAC_Slice00_Enable {false} \
   CONFIG.mDAC_Slice01_Enable {false} \
   CONFIG.mDAC_Slice02_Enable {false} \
   CONFIG.mDAC_Slice03_Enable {false} \
   CONFIG.production_simulation {0} \
 ] $usp_rf_data_converter_0_i

  # Create instance: zynq_ultra_ps_e_0, and set properties
  set zynq_ultra_ps_e_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.3 zynq_ultra_ps_e_0 ]
  set_property -dict [ list \
   CONFIG.PSU_BANK_0_IO_STANDARD {LVCMOS18} \
   CONFIG.PSU_BANK_1_IO_STANDARD {LVCMOS18} \
   CONFIG.PSU_BANK_2_IO_STANDARD {LVCMOS18} \
   CONFIG.PSU_DDR_RAM_HIGHADDR {0xFFFFFFFF} \
   CONFIG.PSU_DDR_RAM_HIGHADDR_OFFSET {0x800000000} \
   CONFIG.PSU_DDR_RAM_LOWADDR_OFFSET {0x80000000} \
   CONFIG.PSU_DYNAMIC_DDR_CONFIG_EN {0} \
   CONFIG.PSU_MIO_0_DIRECTION {out} \
   CONFIG.PSU_MIO_0_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_0_POLARITY {Default} \
   CONFIG.PSU_MIO_10_DIRECTION {inout} \
   CONFIG.PSU_MIO_10_POLARITY {Default} \
   CONFIG.PSU_MIO_11_DIRECTION {inout} \
   CONFIG.PSU_MIO_11_POLARITY {Default} \
   CONFIG.PSU_MIO_12_DIRECTION {out} \
   CONFIG.PSU_MIO_12_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_12_POLARITY {Default} \
   CONFIG.PSU_MIO_13_DIRECTION {inout} \
   CONFIG.PSU_MIO_13_POLARITY {Default} \
   CONFIG.PSU_MIO_14_DIRECTION {inout} \
   CONFIG.PSU_MIO_14_POLARITY {Default} \
   CONFIG.PSU_MIO_15_DIRECTION {inout} \
   CONFIG.PSU_MIO_15_POLARITY {Default} \
   CONFIG.PSU_MIO_16_DIRECTION {inout} \
   CONFIG.PSU_MIO_16_POLARITY {Default} \
   CONFIG.PSU_MIO_17_DIRECTION {inout} \
   CONFIG.PSU_MIO_17_POLARITY {Default} \
   CONFIG.PSU_MIO_18_DIRECTION {in} \
   CONFIG.PSU_MIO_18_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_18_POLARITY {Default} \
   CONFIG.PSU_MIO_18_SLEW {fast} \
   CONFIG.PSU_MIO_19_DIRECTION {out} \
   CONFIG.PSU_MIO_19_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_19_POLARITY {Default} \
   CONFIG.PSU_MIO_1_DIRECTION {inout} \
   CONFIG.PSU_MIO_1_POLARITY {Default} \
   CONFIG.PSU_MIO_20_DIRECTION {inout} \
   CONFIG.PSU_MIO_20_POLARITY {Default} \
   CONFIG.PSU_MIO_21_DIRECTION {inout} \
   CONFIG.PSU_MIO_21_POLARITY {Default} \
   CONFIG.PSU_MIO_22_DIRECTION {inout} \
   CONFIG.PSU_MIO_22_POLARITY {Default} \
   CONFIG.PSU_MIO_23_DIRECTION {inout} \
   CONFIG.PSU_MIO_23_POLARITY {Default} \
   CONFIG.PSU_MIO_24_DIRECTION {inout} \
   CONFIG.PSU_MIO_24_POLARITY {Default} \
   CONFIG.PSU_MIO_25_DIRECTION {inout} \
   CONFIG.PSU_MIO_25_POLARITY {Default} \
   CONFIG.PSU_MIO_26_DIRECTION {inout} \
   CONFIG.PSU_MIO_26_POLARITY {Default} \
   CONFIG.PSU_MIO_27_DIRECTION {out} \
   CONFIG.PSU_MIO_27_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_27_POLARITY {Default} \
   CONFIG.PSU_MIO_28_DIRECTION {in} \
   CONFIG.PSU_MIO_28_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_28_POLARITY {Default} \
   CONFIG.PSU_MIO_28_SLEW {fast} \
   CONFIG.PSU_MIO_29_DIRECTION {out} \
   CONFIG.PSU_MIO_29_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_29_POLARITY {Default} \
   CONFIG.PSU_MIO_2_DIRECTION {inout} \
   CONFIG.PSU_MIO_2_POLARITY {Default} \
   CONFIG.PSU_MIO_30_DIRECTION {in} \
   CONFIG.PSU_MIO_30_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_30_POLARITY {Default} \
   CONFIG.PSU_MIO_30_SLEW {fast} \
   CONFIG.PSU_MIO_31_DIRECTION {inout} \
   CONFIG.PSU_MIO_31_POLARITY {Default} \
   CONFIG.PSU_MIO_32_DIRECTION {out} \
   CONFIG.PSU_MIO_32_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_32_POLARITY {Default} \
   CONFIG.PSU_MIO_33_DIRECTION {out} \
   CONFIG.PSU_MIO_33_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_33_POLARITY {Default} \
   CONFIG.PSU_MIO_34_DIRECTION {out} \
   CONFIG.PSU_MIO_34_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_34_POLARITY {Default} \
   CONFIG.PSU_MIO_35_DIRECTION {out} \
   CONFIG.PSU_MIO_35_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_35_POLARITY {Default} \
   CONFIG.PSU_MIO_36_DIRECTION {out} \
   CONFIG.PSU_MIO_36_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_36_POLARITY {Default} \
   CONFIG.PSU_MIO_37_DIRECTION {out} \
   CONFIG.PSU_MIO_37_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_37_POLARITY {Default} \
   CONFIG.PSU_MIO_38_DIRECTION {inout} \
   CONFIG.PSU_MIO_38_POLARITY {Default} \
   CONFIG.PSU_MIO_39_DIRECTION {inout} \
   CONFIG.PSU_MIO_39_POLARITY {Default} \
   CONFIG.PSU_MIO_3_DIRECTION {inout} \
   CONFIG.PSU_MIO_3_POLARITY {Default} \
   CONFIG.PSU_MIO_40_DIRECTION {inout} \
   CONFIG.PSU_MIO_40_POLARITY {Default} \
   CONFIG.PSU_MIO_41_DIRECTION {inout} \
   CONFIG.PSU_MIO_41_POLARITY {Default} \
   CONFIG.PSU_MIO_42_DIRECTION {inout} \
   CONFIG.PSU_MIO_42_POLARITY {Default} \
   CONFIG.PSU_MIO_43_DIRECTION {inout} \
   CONFIG.PSU_MIO_43_POLARITY {Default} \
   CONFIG.PSU_MIO_44_DIRECTION {inout} \
   CONFIG.PSU_MIO_44_POLARITY {Default} \
   CONFIG.PSU_MIO_45_DIRECTION {in} \
   CONFIG.PSU_MIO_45_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_45_POLARITY {Default} \
   CONFIG.PSU_MIO_45_SLEW {fast} \
   CONFIG.PSU_MIO_46_DIRECTION {inout} \
   CONFIG.PSU_MIO_46_POLARITY {Default} \
   CONFIG.PSU_MIO_47_DIRECTION {inout} \
   CONFIG.PSU_MIO_47_POLARITY {Default} \
   CONFIG.PSU_MIO_48_DIRECTION {inout} \
   CONFIG.PSU_MIO_48_POLARITY {Default} \
   CONFIG.PSU_MIO_49_DIRECTION {inout} \
   CONFIG.PSU_MIO_49_POLARITY {Default} \
   CONFIG.PSU_MIO_4_DIRECTION {inout} \
   CONFIG.PSU_MIO_4_POLARITY {Default} \
   CONFIG.PSU_MIO_50_DIRECTION {inout} \
   CONFIG.PSU_MIO_50_POLARITY {Default} \
   CONFIG.PSU_MIO_51_DIRECTION {out} \
   CONFIG.PSU_MIO_51_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_51_POLARITY {Default} \
   CONFIG.PSU_MIO_52_DIRECTION {in} \
   CONFIG.PSU_MIO_52_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_52_POLARITY {Default} \
   CONFIG.PSU_MIO_52_SLEW {fast} \
   CONFIG.PSU_MIO_53_DIRECTION {in} \
   CONFIG.PSU_MIO_53_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_53_POLARITY {Default} \
   CONFIG.PSU_MIO_53_SLEW {fast} \
   CONFIG.PSU_MIO_54_DIRECTION {inout} \
   CONFIG.PSU_MIO_54_POLARITY {Default} \
   CONFIG.PSU_MIO_55_DIRECTION {in} \
   CONFIG.PSU_MIO_55_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_55_POLARITY {Default} \
   CONFIG.PSU_MIO_55_SLEW {fast} \
   CONFIG.PSU_MIO_56_DIRECTION {inout} \
   CONFIG.PSU_MIO_56_POLARITY {Default} \
   CONFIG.PSU_MIO_57_DIRECTION {inout} \
   CONFIG.PSU_MIO_57_POLARITY {Default} \
   CONFIG.PSU_MIO_58_DIRECTION {out} \
   CONFIG.PSU_MIO_58_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_58_POLARITY {Default} \
   CONFIG.PSU_MIO_59_DIRECTION {inout} \
   CONFIG.PSU_MIO_59_POLARITY {Default} \
   CONFIG.PSU_MIO_5_DIRECTION {out} \
   CONFIG.PSU_MIO_5_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_5_POLARITY {Default} \
   CONFIG.PSU_MIO_60_DIRECTION {inout} \
   CONFIG.PSU_MIO_60_POLARITY {Default} \
   CONFIG.PSU_MIO_61_DIRECTION {inout} \
   CONFIG.PSU_MIO_61_POLARITY {Default} \
   CONFIG.PSU_MIO_62_DIRECTION {inout} \
   CONFIG.PSU_MIO_62_POLARITY {Default} \
   CONFIG.PSU_MIO_63_DIRECTION {inout} \
   CONFIG.PSU_MIO_63_POLARITY {Default} \
   CONFIG.PSU_MIO_64_DIRECTION {out} \
   CONFIG.PSU_MIO_64_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_64_POLARITY {Default} \
   CONFIG.PSU_MIO_65_DIRECTION {out} \
   CONFIG.PSU_MIO_65_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_65_POLARITY {Default} \
   CONFIG.PSU_MIO_66_DIRECTION {out} \
   CONFIG.PSU_MIO_66_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_66_POLARITY {Default} \
   CONFIG.PSU_MIO_67_DIRECTION {out} \
   CONFIG.PSU_MIO_67_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_67_POLARITY {Default} \
   CONFIG.PSU_MIO_68_DIRECTION {out} \
   CONFIG.PSU_MIO_68_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_68_POLARITY {Default} \
   CONFIG.PSU_MIO_69_DIRECTION {out} \
   CONFIG.PSU_MIO_69_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_69_POLARITY {Default} \
   CONFIG.PSU_MIO_6_DIRECTION {out} \
   CONFIG.PSU_MIO_6_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_6_POLARITY {Default} \
   CONFIG.PSU_MIO_70_DIRECTION {in} \
   CONFIG.PSU_MIO_70_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_70_POLARITY {Default} \
   CONFIG.PSU_MIO_70_SLEW {fast} \
   CONFIG.PSU_MIO_71_DIRECTION {in} \
   CONFIG.PSU_MIO_71_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_71_POLARITY {Default} \
   CONFIG.PSU_MIO_71_SLEW {fast} \
   CONFIG.PSU_MIO_72_DIRECTION {in} \
   CONFIG.PSU_MIO_72_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_72_POLARITY {Default} \
   CONFIG.PSU_MIO_72_SLEW {fast} \
   CONFIG.PSU_MIO_73_DIRECTION {in} \
   CONFIG.PSU_MIO_73_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_73_POLARITY {Default} \
   CONFIG.PSU_MIO_73_SLEW {fast} \
   CONFIG.PSU_MIO_74_DIRECTION {in} \
   CONFIG.PSU_MIO_74_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_74_POLARITY {Default} \
   CONFIG.PSU_MIO_74_SLEW {fast} \
   CONFIG.PSU_MIO_75_DIRECTION {in} \
   CONFIG.PSU_MIO_75_DRIVE_STRENGTH {12} \
   CONFIG.PSU_MIO_75_POLARITY {Default} \
   CONFIG.PSU_MIO_75_SLEW {fast} \
   CONFIG.PSU_MIO_76_DIRECTION {out} \
   CONFIG.PSU_MIO_76_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_76_POLARITY {Default} \
   CONFIG.PSU_MIO_77_DIRECTION {inout} \
   CONFIG.PSU_MIO_77_POLARITY {Default} \
   CONFIG.PSU_MIO_7_DIRECTION {out} \
   CONFIG.PSU_MIO_7_INPUT_TYPE {cmos} \
   CONFIG.PSU_MIO_7_POLARITY {Default} \
   CONFIG.PSU_MIO_8_DIRECTION {inout} \
   CONFIG.PSU_MIO_8_POLARITY {Default} \
   CONFIG.PSU_MIO_9_DIRECTION {inout} \
   CONFIG.PSU_MIO_9_POLARITY {Default} \
   CONFIG.PSU_MIO_TREE_PERIPHERALS {Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Feedback Clk#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#Quad SPI Flash#GPIO0 MIO#I2C 0#I2C 0#I2C 1#I2C 1#UART 0#UART 0#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO0 MIO#GPIO1 MIO#DPAUX#DPAUX#DPAUX#DPAUX#GPIO1 MIO#PMU GPO 0#PMU GPO 1#PMU GPO 2#PMU GPO 3#PMU GPO 4#PMU GPO 5#GPIO1 MIO#SD 1#SD 1#SD 1#SD 1#GPIO1 MIO#GPIO1 MIO#SD 1#SD 1#SD 1#SD 1#SD 1#SD 1#SD 1#USB 0#USB 0#USB 0#USB 0#USB 0#USB 0#USB 0#USB 0#USB 0#USB 0#USB 0#USB 0#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#Gem 3#MDIO 3#MDIO 3} \
   CONFIG.PSU_MIO_TREE_SIGNALS {sclk_out#miso_mo1#mo2#mo3#mosi_mi0#n_ss_out#clk_for_lpbk#n_ss_out_upper#mo_upper[0]#mo_upper[1]#mo_upper[2]#mo_upper[3]#sclk_out_upper#gpio0[13]#scl_out#sda_out#scl_out#sda_out#rxd#txd#gpio0[20]#gpio0[21]#gpio0[22]#gpio0[23]#gpio0[24]#gpio0[25]#gpio1[26]#dp_aux_data_out#dp_hot_plug_detect#dp_aux_data_oe#dp_aux_data_in#gpio1[31]#gpo[0]#gpo[1]#gpo[2]#gpo[3]#gpo[4]#gpo[5]#gpio1[38]#sdio1_data_out[4]#sdio1_data_out[5]#sdio1_data_out[6]#sdio1_data_out[7]#gpio1[43]#gpio1[44]#sdio1_cd_n#sdio1_data_out[0]#sdio1_data_out[1]#sdio1_data_out[2]#sdio1_data_out[3]#sdio1_cmd_out#sdio1_clk_out#ulpi_clk_in#ulpi_dir#ulpi_tx_data[2]#ulpi_nxt#ulpi_tx_data[0]#ulpi_tx_data[1]#ulpi_stp#ulpi_tx_data[3]#ulpi_tx_data[4]#ulpi_tx_data[5]#ulpi_tx_data[6]#ulpi_tx_data[7]#rgmii_tx_clk#rgmii_txd[0]#rgmii_txd[1]#rgmii_txd[2]#rgmii_txd[3]#rgmii_tx_ctl#rgmii_rx_clk#rgmii_rxd[0]#rgmii_rxd[1]#rgmii_rxd[2]#rgmii_rxd[3]#rgmii_rx_ctl#gem3_mdc#gem3_mdio_out} \
   CONFIG.PSU_SD1_INTERNAL_BUS_WIDTH {8} \
   CONFIG.PSU_USB3__DUAL_CLOCK_ENABLE {1} \
   CONFIG.PSU__ACT_DDR_FREQ_MHZ {1066.656006} \
   CONFIG.PSU__CAN1__GRP_CLK__ENABLE {0} \
   CONFIG.PSU__CAN1__PERIPHERAL__ENABLE {0} \
   CONFIG.PSU__CRF_APB__ACPU_CTRL__ACT_FREQMHZ {1199.988037} \
   CONFIG.PSU__CRF_APB__ACPU_CTRL__DIVISOR0 {1} \
   CONFIG.PSU__CRF_APB__ACPU_CTRL__FREQMHZ {1200} \
   CONFIG.PSU__CRF_APB__ACPU_CTRL__SRCSEL {APLL} \
   CONFIG.PSU__CRF_APB__APLL_CTRL__DIV2 {1} \
   CONFIG.PSU__CRF_APB__APLL_CTRL__FBDIV {72} \
   CONFIG.PSU__CRF_APB__APLL_CTRL__FRACDATA {0.000000} \
   CONFIG.PSU__CRF_APB__APLL_CTRL__SRCSEL {PSS_REF_CLK} \
   CONFIG.PSU__CRF_APB__APLL_FRAC_CFG__ENABLED {0} \
   CONFIG.PSU__CRF_APB__APLL_TO_LPD_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRF_APB__DBG_FPD_CTRL__ACT_FREQMHZ {249.997498} \
   CONFIG.PSU__CRF_APB__DBG_FPD_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__DBG_FPD_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRF_APB__DBG_FPD_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRF_APB__DBG_TRACE_CTRL__DIVISOR0 {5} \
   CONFIG.PSU__CRF_APB__DBG_TRACE_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRF_APB__DBG_TRACE_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRF_APB__DBG_TSTMP_CTRL__ACT_FREQMHZ {249.997498} \
   CONFIG.PSU__CRF_APB__DBG_TSTMP_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__DBG_TSTMP_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRF_APB__DBG_TSTMP_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRF_APB__DDR_CTRL__ACT_FREQMHZ {533.328003} \
   CONFIG.PSU__CRF_APB__DDR_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__DDR_CTRL__FREQMHZ {1067} \
   CONFIG.PSU__CRF_APB__DDR_CTRL__SRCSEL {DPLL} \
   CONFIG.PSU__CRF_APB__DPDMA_REF_CTRL__ACT_FREQMHZ {599.994019} \
   CONFIG.PSU__CRF_APB__DPDMA_REF_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__DPDMA_REF_CTRL__FREQMHZ {600} \
   CONFIG.PSU__CRF_APB__DPDMA_REF_CTRL__SRCSEL {APLL} \
   CONFIG.PSU__CRF_APB__DPLL_CTRL__DIV2 {1} \
   CONFIG.PSU__CRF_APB__DPLL_CTRL__FBDIV {64} \
   CONFIG.PSU__CRF_APB__DPLL_CTRL__FRACDATA {0.000000} \
   CONFIG.PSU__CRF_APB__DPLL_CTRL__SRCSEL {PSS_REF_CLK} \
   CONFIG.PSU__CRF_APB__DPLL_FRAC_CFG__ENABLED {0} \
   CONFIG.PSU__CRF_APB__DPLL_TO_LPD_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__DP_AUDIO_REF_CTRL__ACT_FREQMHZ {24.999750} \
   CONFIG.PSU__CRF_APB__DP_AUDIO_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRF_APB__DP_AUDIO_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRF_APB__DP_AUDIO_REF_CTRL__SRCSEL {RPLL} \
   CONFIG.PSU__CRF_APB__DP_AUDIO__FRAC_ENABLED {0} \
   CONFIG.PSU__CRF_APB__DP_STC_REF_CTRL__ACT_FREQMHZ {26.785446} \
   CONFIG.PSU__CRF_APB__DP_STC_REF_CTRL__DIVISOR0 {14} \
   CONFIG.PSU__CRF_APB__DP_STC_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRF_APB__DP_STC_REF_CTRL__SRCSEL {RPLL} \
   CONFIG.PSU__CRF_APB__DP_VIDEO_REF_CTRL__ACT_FREQMHZ {299.997009} \
   CONFIG.PSU__CRF_APB__DP_VIDEO_REF_CTRL__DIVISOR0 {5} \
   CONFIG.PSU__CRF_APB__DP_VIDEO_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRF_APB__DP_VIDEO_REF_CTRL__SRCSEL {VPLL} \
   CONFIG.PSU__CRF_APB__DP_VIDEO__FRAC_ENABLED {0} \
   CONFIG.PSU__CRF_APB__GDMA_REF_CTRL__ACT_FREQMHZ {599.994019} \
   CONFIG.PSU__CRF_APB__GDMA_REF_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__GDMA_REF_CTRL__FREQMHZ {600} \
   CONFIG.PSU__CRF_APB__GDMA_REF_CTRL__SRCSEL {APLL} \
   CONFIG.PSU__CRF_APB__GPU_REF_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRF_APB__GPU_REF_CTRL__FREQMHZ {500} \
   CONFIG.PSU__CRF_APB__GPU_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRF_APB__PCIE_REF_CTRL__DIVISOR0 {6} \
   CONFIG.PSU__CRF_APB__PCIE_REF_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRF_APB__PCIE_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRF_APB__SATA_REF_CTRL__ACT_FREQMHZ {249.997498} \
   CONFIG.PSU__CRF_APB__SATA_REF_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__SATA_REF_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRF_APB__SATA_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRF_APB__TOPSW_LSBUS_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRF_APB__TOPSW_LSBUS_CTRL__DIVISOR0 {5} \
   CONFIG.PSU__CRF_APB__TOPSW_LSBUS_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRF_APB__TOPSW_LSBUS_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRF_APB__TOPSW_MAIN_CTRL__ACT_FREQMHZ {533.328003} \
   CONFIG.PSU__CRF_APB__TOPSW_MAIN_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRF_APB__TOPSW_MAIN_CTRL__FREQMHZ {533.33} \
   CONFIG.PSU__CRF_APB__TOPSW_MAIN_CTRL__SRCSEL {DPLL} \
   CONFIG.PSU__CRF_APB__VPLL_CTRL__DIV2 {1} \
   CONFIG.PSU__CRF_APB__VPLL_CTRL__FBDIV {90} \
   CONFIG.PSU__CRF_APB__VPLL_CTRL__FRACDATA {0.000000} \
   CONFIG.PSU__CRF_APB__VPLL_CTRL__SRCSEL {PSS_REF_CLK} \
   CONFIG.PSU__CRF_APB__VPLL_FRAC_CFG__ENABLED {0} \
   CONFIG.PSU__CRF_APB__VPLL_TO_LPD_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRL_APB__ADMA_REF_CTRL__ACT_FREQMHZ {499.994995} \
   CONFIG.PSU__CRL_APB__ADMA_REF_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRL_APB__ADMA_REF_CTRL__FREQMHZ {500} \
   CONFIG.PSU__CRL_APB__ADMA_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__AFI6_REF_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRL_APB__AMS_REF_CTRL__ACT_FREQMHZ {49.999500} \
   CONFIG.PSU__CRL_APB__AMS_REF_CTRL__DIVISOR0 {30} \
   CONFIG.PSU__CRL_APB__AMS_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__CAN0_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__CAN0_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__CAN1_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__CAN1_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__CAN1_REF_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__CAN1_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__CPU_R5_CTRL__ACT_FREQMHZ {499.994995} \
   CONFIG.PSU__CRL_APB__CPU_R5_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRL_APB__CPU_R5_CTRL__FREQMHZ {500} \
   CONFIG.PSU__CRL_APB__CPU_R5_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__DBG_LPD_CTRL__ACT_FREQMHZ {249.997498} \
   CONFIG.PSU__CRL_APB__DBG_LPD_CTRL__DIVISOR0 {6} \
   CONFIG.PSU__CRL_APB__DBG_LPD_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRL_APB__DBG_LPD_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__DLL_REF_CTRL__ACT_FREQMHZ {1499.984985} \
   CONFIG.PSU__CRL_APB__GEM0_REF_CTRL__DIVISOR0 {12} \
   CONFIG.PSU__CRL_APB__GEM0_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__GEM1_REF_CTRL__DIVISOR0 {12} \
   CONFIG.PSU__CRL_APB__GEM1_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__GEM2_REF_CTRL__DIVISOR0 {12} \
   CONFIG.PSU__CRL_APB__GEM2_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__GEM3_REF_CTRL__ACT_FREQMHZ {124.998749} \
   CONFIG.PSU__CRL_APB__GEM3_REF_CTRL__DIVISOR0 {12} \
   CONFIG.PSU__CRL_APB__GEM3_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__GEM3_REF_CTRL__FREQMHZ {125} \
   CONFIG.PSU__CRL_APB__GEM3_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__GEM_TSU_REF_CTRL__ACT_FREQMHZ {249.997498} \
   CONFIG.PSU__CRL_APB__GEM_TSU_REF_CTRL__DIVISOR0 {6} \
   CONFIG.PSU__CRL_APB__GEM_TSU_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__GEM_TSU_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__I2C0_REF_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRL_APB__I2C0_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__I2C0_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__I2C0_REF_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__I2C0_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__I2C1_REF_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRL_APB__I2C1_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__I2C1_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__I2C1_REF_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__I2C1_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__IOPLL_CTRL__DIV2 {1} \
   CONFIG.PSU__CRL_APB__IOPLL_CTRL__FBDIV {90} \
   CONFIG.PSU__CRL_APB__IOPLL_CTRL__FRACDATA {0.000000} \
   CONFIG.PSU__CRL_APB__IOPLL_CTRL__SRCSEL {PSS_REF_CLK} \
   CONFIG.PSU__CRL_APB__IOPLL_FRAC_CFG__ENABLED {0} \
   CONFIG.PSU__CRL_APB__IOPLL_TO_FPD_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRL_APB__IOU_SWITCH_CTRL__ACT_FREQMHZ {249.997498} \
   CONFIG.PSU__CRL_APB__IOU_SWITCH_CTRL__DIVISOR0 {6} \
   CONFIG.PSU__CRL_APB__IOU_SWITCH_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRL_APB__IOU_SWITCH_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__LPD_LSBUS_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRL_APB__LPD_LSBUS_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__LPD_LSBUS_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__LPD_LSBUS_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__LPD_SWITCH_CTRL__ACT_FREQMHZ {499.994995} \
   CONFIG.PSU__CRL_APB__LPD_SWITCH_CTRL__DIVISOR0 {3} \
   CONFIG.PSU__CRL_APB__LPD_SWITCH_CTRL__FREQMHZ {500} \
   CONFIG.PSU__CRL_APB__LPD_SWITCH_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__NAND_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__NAND_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__PCAP_CTRL__ACT_FREQMHZ {187.498123} \
   CONFIG.PSU__CRL_APB__PCAP_CTRL__DIVISOR0 {8} \
   CONFIG.PSU__CRL_APB__PCAP_CTRL__FREQMHZ {200} \
   CONFIG.PSU__CRL_APB__PCAP_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__PL0_REF_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRL_APB__PL0_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__PL0_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__PL0_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__PL1_REF_CTRL__DIVISOR0 {4} \
   CONFIG.PSU__CRL_APB__PL1_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__PL2_REF_CTRL__DIVISOR0 {4} \
   CONFIG.PSU__CRL_APB__PL2_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__PL3_REF_CTRL__DIVISOR0 {4} \
   CONFIG.PSU__CRL_APB__PL3_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__ACT_FREQMHZ {124.998749} \
   CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__DIVISOR0 {12} \
   CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__FREQMHZ {125} \
   CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__RPLL_CTRL__DIV2 {1} \
   CONFIG.PSU__CRL_APB__RPLL_CTRL__FBDIV {45} \
   CONFIG.PSU__CRL_APB__RPLL_CTRL__FRACDATA {0.000000} \
   CONFIG.PSU__CRL_APB__RPLL_CTRL__SRCSEL {PSS_REF_CLK} \
   CONFIG.PSU__CRL_APB__RPLL_FRAC_CFG__ENABLED {0} \
   CONFIG.PSU__CRL_APB__RPLL_TO_FPD_CTRL__DIVISOR0 {2} \
   CONFIG.PSU__CRL_APB__SDIO0_REF_CTRL__DIVISOR0 {7} \
   CONFIG.PSU__CRL_APB__SDIO0_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__SDIO1_REF_CTRL__ACT_FREQMHZ {187.498123} \
   CONFIG.PSU__CRL_APB__SDIO1_REF_CTRL__DIVISOR0 {8} \
   CONFIG.PSU__CRL_APB__SDIO1_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__SDIO1_REF_CTRL__FREQMHZ {200} \
   CONFIG.PSU__CRL_APB__SDIO1_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__SPI0_REF_CTRL__DIVISOR0 {7} \
   CONFIG.PSU__CRL_APB__SPI0_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__SPI1_REF_CTRL__DIVISOR0 {7} \
   CONFIG.PSU__CRL_APB__SPI1_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__TIMESTAMP_REF_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRL_APB__TIMESTAMP_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__TIMESTAMP_REF_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__TIMESTAMP_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__UART0_REF_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRL_APB__UART0_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__UART0_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__UART0_REF_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__UART0_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__UART1_REF_CTRL__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__CRL_APB__UART1_REF_CTRL__DIVISOR0 {15} \
   CONFIG.PSU__CRL_APB__UART1_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__UART1_REF_CTRL__FREQMHZ {100} \
   CONFIG.PSU__CRL_APB__UART1_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__USB0_BUS_REF_CTRL__ACT_FREQMHZ {249.997498} \
   CONFIG.PSU__CRL_APB__USB0_BUS_REF_CTRL__DIVISOR0 {6} \
   CONFIG.PSU__CRL_APB__USB0_BUS_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__USB0_BUS_REF_CTRL__FREQMHZ {250} \
   CONFIG.PSU__CRL_APB__USB0_BUS_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__USB1_BUS_REF_CTRL__DIVISOR0 {6} \
   CONFIG.PSU__CRL_APB__USB1_BUS_REF_CTRL__DIVISOR1 {1} \
   CONFIG.PSU__CRL_APB__USB3_DUAL_REF_CTRL__ACT_FREQMHZ {19.999800} \
   CONFIG.PSU__CRL_APB__USB3_DUAL_REF_CTRL__DIVISOR0 {25} \
   CONFIG.PSU__CRL_APB__USB3_DUAL_REF_CTRL__DIVISOR1 {3} \
   CONFIG.PSU__CRL_APB__USB3_DUAL_REF_CTRL__FREQMHZ {20} \
   CONFIG.PSU__CRL_APB__USB3_DUAL_REF_CTRL__SRCSEL {IOPLL} \
   CONFIG.PSU__CRL_APB__USB3__ENABLE {1} \
   CONFIG.PSU__CSUPMU__PERIPHERAL__VALID {1} \
   CONFIG.PSU__DDRC__ADDR_MIRROR {0} \
   CONFIG.PSU__DDRC__BANK_ADDR_COUNT {2} \
   CONFIG.PSU__DDRC__BG_ADDR_COUNT {1} \
   CONFIG.PSU__DDRC__BRC_MAPPING {ROW_BANK_COL} \
   CONFIG.PSU__DDRC__BUS_WIDTH {64 Bit} \
   CONFIG.PSU__DDRC__CL {15} \
   CONFIG.PSU__DDRC__CLOCK_STOP_EN {0} \
   CONFIG.PSU__DDRC__COL_ADDR_COUNT {10} \
   CONFIG.PSU__DDRC__COMPONENTS {UDIMM} \
   CONFIG.PSU__DDRC__CWL {14} \
   CONFIG.PSU__DDRC__DDR3L_T_REF_RANGE {NA} \
   CONFIG.PSU__DDRC__DDR3_T_REF_RANGE {NA} \
   CONFIG.PSU__DDRC__DDR4_ADDR_MAPPING {0} \
   CONFIG.PSU__DDRC__DDR4_CAL_MODE_ENABLE {0} \
   CONFIG.PSU__DDRC__DDR4_CRC_CONTROL {0} \
   CONFIG.PSU__DDRC__DDR4_T_REF_MODE {0} \
   CONFIG.PSU__DDRC__DDR4_T_REF_RANGE {Normal (0-85)} \
   CONFIG.PSU__DDRC__DEEP_PWR_DOWN_EN {0} \
   CONFIG.PSU__DDRC__DEVICE_CAPACITY {8192 MBits} \
   CONFIG.PSU__DDRC__DIMM_ADDR_MIRROR {0} \
   CONFIG.PSU__DDRC__DM_DBI {DM_NO_DBI} \
   CONFIG.PSU__DDRC__DQMAP_0_3 {0} \
   CONFIG.PSU__DDRC__DQMAP_12_15 {0} \
   CONFIG.PSU__DDRC__DQMAP_16_19 {0} \
   CONFIG.PSU__DDRC__DQMAP_20_23 {0} \
   CONFIG.PSU__DDRC__DQMAP_24_27 {0} \
   CONFIG.PSU__DDRC__DQMAP_28_31 {0} \
   CONFIG.PSU__DDRC__DQMAP_32_35 {0} \
   CONFIG.PSU__DDRC__DQMAP_36_39 {0} \
   CONFIG.PSU__DDRC__DQMAP_40_43 {0} \
   CONFIG.PSU__DDRC__DQMAP_44_47 {0} \
   CONFIG.PSU__DDRC__DQMAP_48_51 {0} \
   CONFIG.PSU__DDRC__DQMAP_4_7 {0} \
   CONFIG.PSU__DDRC__DQMAP_52_55 {0} \
   CONFIG.PSU__DDRC__DQMAP_56_59 {0} \
   CONFIG.PSU__DDRC__DQMAP_60_63 {0} \
   CONFIG.PSU__DDRC__DQMAP_64_67 {0} \
   CONFIG.PSU__DDRC__DQMAP_68_71 {0} \
   CONFIG.PSU__DDRC__DQMAP_8_11 {0} \
   CONFIG.PSU__DDRC__DRAM_WIDTH {16 Bits} \
   CONFIG.PSU__DDRC__ECC {Disabled} \
   CONFIG.PSU__DDRC__ENABLE_LP4_HAS_ECC_COMP {0} \
   CONFIG.PSU__DDRC__ENABLE_LP4_SLOWBOOT {0} \
   CONFIG.PSU__DDRC__FGRM {1X} \
   CONFIG.PSU__DDRC__LPDDR3_T_REF_RANGE {NA} \
   CONFIG.PSU__DDRC__LPDDR4_T_REF_RANGE {NA} \
   CONFIG.PSU__DDRC__LP_ASR {manual normal} \
   CONFIG.PSU__DDRC__MEMORY_TYPE {DDR 4} \
   CONFIG.PSU__DDRC__PARITY_ENABLE {0} \
   CONFIG.PSU__DDRC__PER_BANK_REFRESH {0} \
   CONFIG.PSU__DDRC__PHY_DBI_MODE {0} \
   CONFIG.PSU__DDRC__RANK_ADDR_COUNT {0} \
   CONFIG.PSU__DDRC__ROW_ADDR_COUNT {16} \
   CONFIG.PSU__DDRC__SB_TARGET {15-15-15} \
   CONFIG.PSU__DDRC__SELF_REF_ABORT {0} \
   CONFIG.PSU__DDRC__SPEED_BIN {DDR4_2133P} \
   CONFIG.PSU__DDRC__STATIC_RD_MODE {0} \
   CONFIG.PSU__DDRC__TRAIN_DATA_EYE {1} \
   CONFIG.PSU__DDRC__TRAIN_READ_GATE {1} \
   CONFIG.PSU__DDRC__TRAIN_WRITE_LEVEL {1} \
   CONFIG.PSU__DDRC__T_FAW {30.0} \
   CONFIG.PSU__DDRC__T_RAS_MIN {33} \
   CONFIG.PSU__DDRC__T_RC {47.06} \
   CONFIG.PSU__DDRC__T_RCD {15} \
   CONFIG.PSU__DDRC__T_RP {15} \
   CONFIG.PSU__DDRC__VENDOR_PART {OTHERS} \
   CONFIG.PSU__DDRC__VREF {1} \
   CONFIG.PSU__DDR_HIGH_ADDRESS_GUI_ENABLE {1} \
   CONFIG.PSU__DDR__INTERFACE__FREQMHZ {533.500} \
   CONFIG.PSU__DISPLAYPORT__LANE0__ENABLE {1} \
   CONFIG.PSU__DISPLAYPORT__LANE0__IO {GT Lane1} \
   CONFIG.PSU__DISPLAYPORT__LANE1__ENABLE {1} \
   CONFIG.PSU__DISPLAYPORT__LANE1__IO {GT Lane0} \
   CONFIG.PSU__DISPLAYPORT__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__DLL__ISUSED {1} \
   CONFIG.PSU__DPAUX__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__DPAUX__PERIPHERAL__IO {MIO 27 .. 30} \
   CONFIG.PSU__DP__LANE_SEL {Dual Lower} \
   CONFIG.PSU__DP__REF_CLK_FREQ {27} \
   CONFIG.PSU__DP__REF_CLK_SEL {Ref Clk1} \
   CONFIG.PSU__ENET3__FIFO__ENABLE {0} \
   CONFIG.PSU__ENET3__GRP_MDIO__ENABLE {1} \
   CONFIG.PSU__ENET3__GRP_MDIO__IO {MIO 76 .. 77} \
   CONFIG.PSU__ENET3__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__ENET3__PERIPHERAL__IO {MIO 64 .. 75} \
   CONFIG.PSU__ENET3__PTP__ENABLE {0} \
   CONFIG.PSU__ENET3__TSU__ENABLE {0} \
   CONFIG.PSU__FPDMASTERS_COHERENCY {0} \
   CONFIG.PSU__FPD_SLCR__WDT1__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__FPD_SLCR__WDT1__FREQMHZ {99.999001} \
   CONFIG.PSU__FPD_SLCR__WDT_CLK_SEL__SELECT {APB} \
   CONFIG.PSU__FPGA_PL0_ENABLE {1} \
   CONFIG.PSU__GEM3_COHERENCY {0} \
   CONFIG.PSU__GEM3_ROUTE_THROUGH_FPD {0} \
   CONFIG.PSU__GEM__TSU__ENABLE {0} \
   CONFIG.PSU__GPIO0_MIO__IO {MIO 0 .. 25} \
   CONFIG.PSU__GPIO0_MIO__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__GPIO1_MIO__IO {MIO 26 .. 51} \
   CONFIG.PSU__GPIO1_MIO__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__GPIO_EMIO__WIDTH {[94:0]} \
   CONFIG.PSU__GT__LINK_SPEED {HBR} \
   CONFIG.PSU__GT__PRE_EMPH_LVL_4 {0} \
   CONFIG.PSU__GT__VLT_SWNG_LVL_4 {0} \
   CONFIG.PSU__HIGH_ADDRESS__ENABLE {1} \
   CONFIG.PSU__I2C0__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__I2C0__PERIPHERAL__IO {MIO 14 .. 15} \
   CONFIG.PSU__I2C1__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__I2C1__PERIPHERAL__IO {MIO 16 .. 17} \
   CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC0_SEL {APB} \
   CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC1_SEL {APB} \
   CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC2_SEL {APB} \
   CONFIG.PSU__IOU_SLCR__IOU_TTC_APB_CLK__TTC3_SEL {APB} \
   CONFIG.PSU__IOU_SLCR__TTC0__ACT_FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__TTC0__FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__TTC1__ACT_FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__TTC1__FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__TTC2__ACT_FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__TTC2__FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__TTC3__ACT_FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__TTC3__FREQMHZ {100.000000} \
   CONFIG.PSU__IOU_SLCR__WDT0__ACT_FREQMHZ {99.999001} \
   CONFIG.PSU__IOU_SLCR__WDT0__FREQMHZ {99.999001} \
   CONFIG.PSU__IOU_SLCR__WDT_CLK_SEL__SELECT {APB} \
   CONFIG.PSU__LPD_SLCR__CSUPMU__ACT_FREQMHZ {100.000000} \
   CONFIG.PSU__LPD_SLCR__CSUPMU__FREQMHZ {100.000000} \
   CONFIG.PSU__MAXIGP0__DATA_WIDTH {128} \
   CONFIG.PSU__MAXIGP1__DATA_WIDTH {128} \
   CONFIG.PSU__MAXIGP2__DATA_WIDTH {32} \
   CONFIG.PSU__NUM_FABRIC_RESETS {1} \
   CONFIG.PSU__OVERRIDE__BASIC_CLOCK {0} \
   CONFIG.PSU__PL_CLK0_BUF {TRUE} \
   CONFIG.PSU__PMU_COHERENCY {0} \
   CONFIG.PSU__PMU__AIBACK__ENABLE {0} \
   CONFIG.PSU__PMU__EMIO_GPI__ENABLE {0} \
   CONFIG.PSU__PMU__EMIO_GPO__ENABLE {0} \
   CONFIG.PSU__PMU__GPI0__ENABLE {0} \
   CONFIG.PSU__PMU__GPI1__ENABLE {0} \
   CONFIG.PSU__PMU__GPI2__ENABLE {0} \
   CONFIG.PSU__PMU__GPI3__ENABLE {0} \
   CONFIG.PSU__PMU__GPI4__ENABLE {0} \
   CONFIG.PSU__PMU__GPI5__ENABLE {0} \
   CONFIG.PSU__PMU__GPO0__ENABLE {1} \
   CONFIG.PSU__PMU__GPO0__IO {MIO 32} \
   CONFIG.PSU__PMU__GPO1__ENABLE {1} \
   CONFIG.PSU__PMU__GPO1__IO {MIO 33} \
   CONFIG.PSU__PMU__GPO2__ENABLE {1} \
   CONFIG.PSU__PMU__GPO2__IO {MIO 34} \
   CONFIG.PSU__PMU__GPO2__POLARITY {low} \
   CONFIG.PSU__PMU__GPO3__ENABLE {1} \
   CONFIG.PSU__PMU__GPO3__IO {MIO 35} \
   CONFIG.PSU__PMU__GPO3__POLARITY {low} \
   CONFIG.PSU__PMU__GPO4__ENABLE {1} \
   CONFIG.PSU__PMU__GPO4__IO {MIO 36} \
   CONFIG.PSU__PMU__GPO4__POLARITY {low} \
   CONFIG.PSU__PMU__GPO5__ENABLE {1} \
   CONFIG.PSU__PMU__GPO5__IO {MIO 37} \
   CONFIG.PSU__PMU__GPO5__POLARITY {low} \
   CONFIG.PSU__PMU__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__PMU__PLERROR__ENABLE {0} \
   CONFIG.PSU__PRESET_APPLIED {1} \
   CONFIG.PSU__PROTECTION__MASTERS {USB1:NonSecure;0|USB0:NonSecure;1|S_AXI_LPD:NA;0|S_AXI_HPC1_FPD:NA;0|S_AXI_HPC0_FPD:NA;0|S_AXI_HP3_FPD:NA;0|S_AXI_HP2_FPD:NA;0|S_AXI_HP1_FPD:NA;0|S_AXI_HP0_FPD:NA;0|S_AXI_ACP:NA;0|S_AXI_ACE:NA;0|SD1:NonSecure;1|SD0:NonSecure;0|SATA1:NonSecure;1|SATA0:NonSecure;1|RPU1:Secure;1|RPU0:Secure;1|QSPI:NonSecure;1|PMU:NA;1|PCIe:NonSecure;0|NAND:NonSecure;0|LDMA:NonSecure;1|GPU:NonSecure;1|GEM3:NonSecure;1|GEM2:NonSecure;0|GEM1:NonSecure;0|GEM0:NonSecure;0|FDMA:NonSecure;1|DP:NonSecure;1|DAP:NA;1|Coresight:NA;1|CSU:NA;1|APU:NA;1} \
   CONFIG.PSU__PROTECTION__SLAVES {LPD;USB3_1_XHCI;FE300000;FE3FFFFF;0|LPD;USB3_1;FF9E0000;FF9EFFFF;0|LPD;USB3_0_XHCI;FE200000;FE2FFFFF;1|LPD;USB3_0;FF9D0000;FF9DFFFF;1|LPD;UART1;FF010000;FF01FFFF;1|LPD;UART0;FF000000;FF00FFFF;1|LPD;TTC3;FF140000;FF14FFFF;1|LPD;TTC2;FF130000;FF13FFFF;1|LPD;TTC1;FF120000;FF12FFFF;1|LPD;TTC0;FF110000;FF11FFFF;1|FPD;SWDT1;FD4D0000;FD4DFFFF;1|LPD;SWDT0;FF150000;FF15FFFF;1|LPD;SPI1;FF050000;FF05FFFF;0|LPD;SPI0;FF040000;FF04FFFF;0|FPD;SMMU_REG;FD5F0000;FD5FFFFF;1|FPD;SMMU;FD800000;FDFFFFFF;1|FPD;SIOU;FD3D0000;FD3DFFFF;1|FPD;SERDES;FD400000;FD47FFFF;1|LPD;SD1;FF170000;FF17FFFF;1|LPD;SD0;FF160000;FF16FFFF;0|FPD;SATA;FD0C0000;FD0CFFFF;1|LPD;RTC;FFA60000;FFA6FFFF;1|LPD;RSA_CORE;FFCE0000;FFCEFFFF;1|LPD;RPU;FF9A0000;FF9AFFFF;1|LPD;R5_TCM_RAM_GLOBAL;FFE00000;FFE3FFFF;1|LPD;R5_1_Instruction_Cache;FFEC0000;FFECFFFF;1|LPD;R5_1_Data_Cache;FFED0000;FFEDFFFF;1|LPD;R5_1_BTCM_GLOBAL;FFEB0000;FFEBFFFF;1|LPD;R5_1_ATCM_GLOBAL;FFE90000;FFE9FFFF;1|LPD;R5_0_Instruction_Cache;FFE40000;FFE4FFFF;1|LPD;R5_0_Data_Cache;FFE50000;FFE5FFFF;1|LPD;R5_0_BTCM_GLOBAL;FFE20000;FFE2FFFF;1|LPD;R5_0_ATCM_GLOBAL;FFE00000;FFE0FFFF;1|LPD;QSPI_Linear_Address;C0000000;DFFFFFFF;1|LPD;QSPI;FF0F0000;FF0FFFFF;1|LPD;PMU_RAM;FFDC0000;FFDDFFFF;1|LPD;PMU_GLOBAL;FFD80000;FFDBFFFF;1|FPD;PCIE_MAIN;FD0E0000;FD0EFFFF;0|FPD;PCIE_LOW;E0000000;EFFFFFFF;0|FPD;PCIE_HIGH2;8000000000;BFFFFFFFFF;0|FPD;PCIE_HIGH1;600000000;7FFFFFFFF;0|FPD;PCIE_DMA;FD0F0000;FD0FFFFF;0|FPD;PCIE_ATTRIB;FD480000;FD48FFFF;0|LPD;OCM_XMPU_CFG;FFA70000;FFA7FFFF;1|LPD;OCM_SLCR;FF960000;FF96FFFF;1|OCM;OCM;FFFC0000;FFFFFFFF;1|LPD;NAND;FF100000;FF10FFFF;0|LPD;MBISTJTAG;FFCF0000;FFCFFFFF;1|LPD;LPD_XPPU_SINK;FF9C0000;FF9CFFFF;1|LPD;LPD_XPPU;FF980000;FF98FFFF;1|LPD;LPD_SLCR_SECURE;FF4B0000;FF4DFFFF;1|LPD;LPD_SLCR;FF410000;FF4AFFFF;1|LPD;LPD_GPV;FE100000;FE1FFFFF;1|LPD;LPD_DMA_7;FFAF0000;FFAFFFFF;1|LPD;LPD_DMA_6;FFAE0000;FFAEFFFF;1|LPD;LPD_DMA_5;FFAD0000;FFADFFFF;1|LPD;LPD_DMA_4;FFAC0000;FFACFFFF;1|LPD;LPD_DMA_3;FFAB0000;FFABFFFF;1|LPD;LPD_DMA_2;FFAA0000;FFAAFFFF;1|LPD;LPD_DMA_1;FFA90000;FFA9FFFF;1|LPD;LPD_DMA_0;FFA80000;FFA8FFFF;1|LPD;IPI_CTRL;FF380000;FF3FFFFF;1|LPD;IOU_SLCR;FF180000;FF23FFFF;1|LPD;IOU_SECURE_SLCR;FF240000;FF24FFFF;1|LPD;IOU_SCNTRS;FF260000;FF26FFFF;1|LPD;IOU_SCNTR;FF250000;FF25FFFF;1|LPD;IOU_GPV;FE000000;FE0FFFFF;1|LPD;I2C1;FF030000;FF03FFFF;1|LPD;I2C0;FF020000;FF02FFFF;1|FPD;GPU;FD4B0000;FD4BFFFF;0|LPD;GPIO;FF0A0000;FF0AFFFF;1|LPD;GEM3;FF0E0000;FF0EFFFF;1|LPD;GEM2;FF0D0000;FF0DFFFF;0|LPD;GEM1;FF0C0000;FF0CFFFF;0|LPD;GEM0;FF0B0000;FF0BFFFF;0|FPD;FPD_XMPU_SINK;FD4F0000;FD4FFFFF;1|FPD;FPD_XMPU_CFG;FD5D0000;FD5DFFFF;1|FPD;FPD_SLCR_SECURE;FD690000;FD6CFFFF;1|FPD;FPD_SLCR;FD610000;FD68FFFF;1|FPD;FPD_GPV;FD700000;FD7FFFFF;1|FPD;FPD_DMA_CH7;FD570000;FD57FFFF;1|FPD;FPD_DMA_CH6;FD560000;FD56FFFF;1|FPD;FPD_DMA_CH5;FD550000;FD55FFFF;1|FPD;FPD_DMA_CH4;FD540000;FD54FFFF;1|FPD;FPD_DMA_CH3;FD530000;FD53FFFF;1|FPD;FPD_DMA_CH2;FD520000;FD52FFFF;1|FPD;FPD_DMA_CH1;FD510000;FD51FFFF;1|FPD;FPD_DMA_CH0;FD500000;FD50FFFF;1|LPD;EFUSE;FFCC0000;FFCCFFFF;1|FPD;Display Port;FD4A0000;FD4AFFFF;1|FPD;DPDMA;FD4C0000;FD4CFFFF;1|FPD;DDR_XMPU5_CFG;FD050000;FD05FFFF;1|FPD;DDR_XMPU4_CFG;FD040000;FD04FFFF;1|FPD;DDR_XMPU3_CFG;FD030000;FD03FFFF;1|FPD;DDR_XMPU2_CFG;FD020000;FD02FFFF;1|FPD;DDR_XMPU1_CFG;FD010000;FD01FFFF;1|FPD;DDR_XMPU0_CFG;FD000000;FD00FFFF;1|FPD;DDR_QOS_CTRL;FD090000;FD09FFFF;1|FPD;DDR_PHY;FD080000;FD08FFFF;1|DDR;DDR_LOW;0;7FFFFFFF;1|DDR;DDR_HIGH;800000000;87FFFFFFF;1|FPD;DDDR_CTRL;FD070000;FD070FFF;1|LPD;Coresight;FE800000;FEFFFFFF;1|LPD;CSU_DMA;FFC80000;FFC9FFFF;1|LPD;CSU;FFCA0000;FFCAFFFF;0|LPD;CRL_APB;FF5E0000;FF85FFFF;1|FPD;CRF_APB;FD1A0000;FD2DFFFF;1|FPD;CCI_REG;FD5E0000;FD5EFFFF;1|FPD;CCI_GPV;FD6E0000;FD6EFFFF;1|LPD;CAN1;FF070000;FF07FFFF;0|LPD;CAN0;FF060000;FF06FFFF;0|FPD;APU;FD5C0000;FD5CFFFF;1|LPD;APM_INTC_IOU;FFA20000;FFA2FFFF;1|LPD;APM_FPD_LPD;FFA30000;FFA3FFFF;1|FPD;APM_5;FD490000;FD49FFFF;1|FPD;APM_0;FD0B0000;FD0BFFFF;1|LPD;APM2;FFA10000;FFA1FFFF;1|LPD;APM1;FFA00000;FFA0FFFF;1|LPD;AMS;FFA50000;FFA5FFFF;1|FPD;AFI_5;FD3B0000;FD3BFFFF;1|FPD;AFI_4;FD3A0000;FD3AFFFF;1|FPD;AFI_3;FD390000;FD39FFFF;1|FPD;AFI_2;FD380000;FD38FFFF;1|FPD;AFI_1;FD370000;FD37FFFF;1|FPD;AFI_0;FD360000;FD36FFFF;1|LPD;AFIFM6;FF9B0000;FF9BFFFF;1|FPD;ACPU_GIC;F9010000;F907FFFF;1} \
   CONFIG.PSU__PSS_REF_CLK__FREQMHZ {33.333} \
   CONFIG.PSU__QSPI_COHERENCY {0} \
   CONFIG.PSU__QSPI_ROUTE_THROUGH_FPD {0} \
   CONFIG.PSU__QSPI__GRP_FBCLK__ENABLE {1} \
   CONFIG.PSU__QSPI__GRP_FBCLK__IO {MIO 6} \
   CONFIG.PSU__QSPI__PERIPHERAL__DATA_MODE {x4} \
   CONFIG.PSU__QSPI__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__QSPI__PERIPHERAL__IO {MIO 0 .. 12} \
   CONFIG.PSU__QSPI__PERIPHERAL__MODE {Dual Parallel} \
   CONFIG.PSU__SATA__LANE0__ENABLE {0} \
   CONFIG.PSU__SATA__LANE1__ENABLE {1} \
   CONFIG.PSU__SATA__LANE1__IO {GT Lane3} \
   CONFIG.PSU__SATA__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__SATA__REF_CLK_FREQ {125} \
   CONFIG.PSU__SATA__REF_CLK_SEL {Ref Clk3} \
   CONFIG.PSU__SD1_COHERENCY {0} \
   CONFIG.PSU__SD1_ROUTE_THROUGH_FPD {0} \
   CONFIG.PSU__SD1__DATA_TRANSFER_MODE {8Bit} \
   CONFIG.PSU__SD1__GRP_CD__ENABLE {1} \
   CONFIG.PSU__SD1__GRP_CD__IO {MIO 45} \
   CONFIG.PSU__SD1__GRP_POW__ENABLE {0} \
   CONFIG.PSU__SD1__GRP_WP__ENABLE {0} \
   CONFIG.PSU__SD1__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__SD1__PERIPHERAL__IO {MIO 39 .. 51} \
   CONFIG.PSU__SD1__RESET__ENABLE {0} \
   CONFIG.PSU__SD1__SLOT_TYPE {SD 3.0} \
   CONFIG.PSU__SWDT0__CLOCK__ENABLE {0} \
   CONFIG.PSU__SWDT0__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__SWDT0__RESET__ENABLE {0} \
   CONFIG.PSU__SWDT1__CLOCK__ENABLE {0} \
   CONFIG.PSU__SWDT1__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__SWDT1__RESET__ENABLE {0} \
   CONFIG.PSU__TSU__BUFG_PORT_PAIR {0} \
   CONFIG.PSU__TTC0__CLOCK__ENABLE {0} \
   CONFIG.PSU__TTC0__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__TTC0__WAVEOUT__ENABLE {0} \
   CONFIG.PSU__TTC1__CLOCK__ENABLE {0} \
   CONFIG.PSU__TTC1__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__TTC1__WAVEOUT__ENABLE {0} \
   CONFIG.PSU__TTC2__CLOCK__ENABLE {0} \
   CONFIG.PSU__TTC2__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__TTC2__WAVEOUT__ENABLE {0} \
   CONFIG.PSU__TTC3__CLOCK__ENABLE {0} \
   CONFIG.PSU__TTC3__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__TTC3__WAVEOUT__ENABLE {0} \
   CONFIG.PSU__UART0__BAUD_RATE {115200} \
   CONFIG.PSU__UART0__MODEM__ENABLE {0} \
   CONFIG.PSU__UART0__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__UART0__PERIPHERAL__IO {MIO 18 .. 19} \
   CONFIG.PSU__UART1__BAUD_RATE {115200} \
   CONFIG.PSU__UART1__MODEM__ENABLE {0} \
   CONFIG.PSU__UART1__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__UART1__PERIPHERAL__IO {EMIO} \
   CONFIG.PSU__USB0_COHERENCY {0} \
   CONFIG.PSU__USB0__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__USB0__PERIPHERAL__IO {MIO 52 .. 63} \
   CONFIG.PSU__USB0__REF_CLK_FREQ {26} \
   CONFIG.PSU__USB0__REF_CLK_SEL {Ref Clk2} \
   CONFIG.PSU__USB0__RESET__ENABLE {0} \
   CONFIG.PSU__USB1__RESET__ENABLE {0} \
   CONFIG.PSU__USB2_0__EMIO__ENABLE {0} \
   CONFIG.PSU__USB3_0__EMIO__ENABLE {0} \
   CONFIG.PSU__USB3_0__PERIPHERAL__ENABLE {1} \
   CONFIG.PSU__USB3_0__PERIPHERAL__IO {GT Lane2} \
   CONFIG.PSU__USB__RESET__MODE {Boot Pin} \
   CONFIG.PSU__USB__RESET__POLARITY {Active Low} \
   CONFIG.PSU__USE__FABRIC__RST {1} \
   CONFIG.PSU__USE__IRQ0 {1} \
   CONFIG.PSU__USE__IRQ1 {0} \
   CONFIG.PSU__USE__M_AXI_GP0 {1} \
   CONFIG.PSU__USE__M_AXI_GP1 {1} \
   CONFIG.PSU__USE__M_AXI_GP2 {0} \
   CONFIG.PSU__USE__VIDEO {0} \
   CONFIG.SUBPRESET1 {Custom} \
 ] $zynq_ultra_ps_e_0

  # Create instance: zynq_ultra_ps_e_0_axi_periph, and set properties
  set zynq_ultra_ps_e_0_axi_periph [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 zynq_ultra_ps_e_0_axi_periph ]
  set_property -dict [ list \
   CONFIG.M00_HAS_REGSLICE {4} \
   CONFIG.M01_HAS_REGSLICE {4} \
   CONFIG.M02_HAS_REGSLICE {4} \
   CONFIG.M03_HAS_REGSLICE {4} \
   CONFIG.M04_HAS_REGSLICE {4} \
   CONFIG.M05_HAS_REGSLICE {4} \
   CONFIG.M06_HAS_REGSLICE {4} \
   CONFIG.M07_HAS_REGSLICE {4} \
   CONFIG.M08_HAS_REGSLICE {4} \
   CONFIG.M09_HAS_REGSLICE {4} \
   CONFIG.M10_HAS_REGSLICE {4} \
   CONFIG.NUM_MI {11} \
 ] $zynq_ultra_ps_e_0_axi_periph

  # Create interface connections
  connect_bd_intf_net -intf_net adc0_clk_1 [get_bd_intf_ports adc0_clk] [get_bd_intf_pins usp_rf_data_converter_0_i/adc0_clk]
  connect_bd_intf_net -intf_net axi_gpio_GPIO [get_bd_intf_ports led_bits] [get_bd_intf_pins axi_gpio/GPIO]
  connect_bd_intf_net -intf_net axi_interconnect_0_M00_AXI [get_bd_intf_pins axi_interconnect_0/M00_AXI] [get_bd_intf_pins usp_rf_data_converter_0_i/s_axi]
  connect_bd_intf_net -intf_net axi_interconnect_0_M01_AXI [get_bd_intf_pins axi_interconnect_0/M01_AXI] [get_bd_intf_pins dac_source_i/s_axi]
  connect_bd_intf_net -intf_net axi_interconnect_0_M02_AXI [get_bd_intf_pins adc_sink_i/s_axi] [get_bd_intf_pins axi_interconnect_0/M02_AXI]
  connect_bd_intf_net -intf_net chan_ctrl_fifo_M_AXIS [get_bd_intf_pins chan_ctrl_fifo/M_AXIS] [get_bd_intf_pins mod_and_chan/ctrl_in_V]
  connect_bd_intf_net -intf_net chan_ctrl_reg_M_AXIS [get_bd_intf_pins chan_ctrl_fifo/S_AXIS] [get_bd_intf_pins chan_ctrl_reg/M_AXIS]
  connect_bd_intf_net -intf_net dac0_clk_1 [get_bd_intf_ports dac0_clk] [get_bd_intf_pins usp_rf_data_converter_0_i/dac0_clk]
  connect_bd_intf_net -intf_net dac_source_i_m00 [get_bd_intf_pins dac_source_i/m00] [get_bd_intf_pins usp_rf_data_converter_0_i/s00_axis]
  connect_bd_intf_net -intf_net data_source_chan_ctrl_out_V [get_bd_intf_pins chan_ctrl_reg/S_AXIS] [get_bd_intf_pins data_source/chan_ctrl_out_V]
  connect_bd_intf_net -intf_net data_source_dec_ctrl_out [get_bd_intf_pins data_source/dec_ctrl_out] [get_bd_intf_pins dec_ctrl_reinterpret/S_AXIS]
  connect_bd_intf_net -intf_net data_source_dec_keep_ctrl_V_V [get_bd_intf_pins data_source/dec_keep_ctrl_V_V] [get_bd_intf_pins dec_add_keep_trim/S_AXIS]
  connect_bd_intf_net -intf_net data_source_enc_ctrl_out [get_bd_intf_pins data_source/enc_ctrl_out] [get_bd_intf_pins enc_ctrl_reinterpret/S_AXIS]
  connect_bd_intf_net -intf_net data_source_enc_keep_ctrl_V_V [get_bd_intf_pins data_source/enc_keep_ctrl_V_V] [get_bd_intf_pins enc_add_keep_trim/S_AXIS]
  connect_bd_intf_net -intf_net data_source_hard_data_out [get_bd_intf_pins data_source/hard_data_out] [get_bd_intf_pins hard_data_reg/S_AXIS]
  connect_bd_intf_net -intf_net dec_add_keep_dout [get_bd_intf_pins dec_add_keep/dout] [get_bd_intf_pins dec_data_reinterpret/S_AXIS]
  connect_bd_intf_net -intf_net dec_add_keep_trim_M_AXIS [get_bd_intf_pins dec_add_keep_trim/M_AXIS] [get_bd_intf_pins dec_keep_ctrl_fifo/S_AXIS]
  connect_bd_intf_net -intf_net dec_ctrl_fifo_M_AXIS [get_bd_intf_pins dec_ctrl_fifo/M_AXIS] [get_bd_intf_pins sd_fec_dec/S_AXIS_CTRL]
  connect_bd_intf_net -intf_net dec_ctrl_reg_M_AXIS [get_bd_intf_pins dec_ctrl_fifo/S_AXIS] [get_bd_intf_pins dec_ctrl_reg/M_AXIS]
  connect_bd_intf_net -intf_net dec_ctrl_reinterpret_M_AXIS [get_bd_intf_pins dec_ctrl_reg/S_AXIS] [get_bd_intf_pins dec_ctrl_reinterpret/M_AXIS]
  connect_bd_intf_net -intf_net dec_data_reinterpret_M_AXIS [get_bd_intf_pins dec_data_reinterpret/M_AXIS] [get_bd_intf_pins stats/hard_data]
  connect_bd_intf_net -intf_net dec_keep_ctrl_fifo_M_AXIS [get_bd_intf_pins dec_add_keep/ctrl_V_V] [get_bd_intf_pins dec_keep_ctrl_fifo/M_AXIS]
  connect_bd_intf_net -intf_net dec_stat_reinterpret_M_AXIS [get_bd_intf_pins dec_stat_reinterpret/M_AXIS] [get_bd_intf_pins stats/fe_status_V_V]
  connect_bd_intf_net -intf_net demod_hard_data [get_bd_intf_pins demod/hard_data] [get_bd_intf_pins hard_chan_data_fifo/S_AXIS]
  connect_bd_intf_net -intf_net demod_soft_data [get_bd_intf_pins demod/soft_data] [get_bd_intf_pins llr_reshape/S_AXIS]
  connect_bd_intf_net -intf_net diff_clock_rtl_0_1 [get_bd_intf_ports sys_diff_clock] [get_bd_intf_pins clk_wiz/CLK_IN1_D]
  connect_bd_intf_net -intf_net enc_add_keep_dout [get_bd_intf_pins enc_add_keep/dout] [get_bd_intf_pins enc_data_reinterpret/S_AXIS]
  connect_bd_intf_net -intf_net enc_add_keep_trim_M_AXIS [get_bd_intf_pins enc_add_keep_trim/M_AXIS] [get_bd_intf_pins enc_keep_ctrl_fifo/S_AXIS]
  connect_bd_intf_net -intf_net enc_ctrl_reinterpret_M_AXIS [get_bd_intf_pins enc_ctrl_reinterpret/M_AXIS] [get_bd_intf_pins sd_fec_enc/S_AXIS_CTRL]
  connect_bd_intf_net -intf_net enc_data_fifo_M_AXIS [get_bd_intf_pins enc_data_fifo/M_AXIS] [get_bd_intf_pins mod_and_chan/hard_data_V_V]
  connect_bd_intf_net -intf_net enc_data_reinterpret_M_AXIS [get_bd_intf_pins enc_data_fifo/S_AXIS] [get_bd_intf_pins enc_data_reinterpret/M_AXIS]
  connect_bd_intf_net -intf_net enc_keep_ctrl_fifo_M_AXIS [get_bd_intf_pins enc_add_keep/ctrl_V_V] [get_bd_intf_pins enc_keep_ctrl_fifo/M_AXIS]
  connect_bd_intf_net -intf_net hard_chan_data_fifo_M_AXIS [get_bd_intf_pins hard_chan_data_fifo/M_AXIS] [get_bd_intf_pins stats/error_data]
  connect_bd_intf_net -intf_net hard_data_reg_M_AXIS [get_bd_intf_pins hard_data_reg/M_AXIS] [get_bd_intf_pins src_data_broadcast/S_AXIS]
  connect_bd_intf_net -intf_net llr_reinterpret_M_AXIS [get_bd_intf_pins llr_reinterpret/M_AXIS] [get_bd_intf_pins sd_fec_dec/S_AXIS_DIN]
connect_bd_intf_net -intf_net [get_bd_intf_nets llr_reinterpret_M_AXIS] [get_bd_intf_pins dec_ip_probe/mon] [get_bd_intf_pins llr_reinterpret/M_AXIS]
  connect_bd_intf_net -intf_net llr_reshape_M_AXIS [get_bd_intf_pins llr_reinterpret/S_AXIS] [get_bd_intf_pins llr_reshape/M_AXIS]
  connect_bd_intf_net -intf_net mod_and_chan_chan_data_1_V [get_bd_intf_pins demod/chan_data_1_V] [get_bd_intf_pins mod_and_chan/chan_data_1_V]
  connect_bd_intf_net -intf_net mod_and_chan_chan_data_2_V [get_bd_intf_pins demod/chan_data_2_V] [get_bd_intf_pins mod_and_chan/chan_data_2_V]
  connect_bd_intf_net -intf_net mod_and_chan_chan_data_3_V [get_bd_intf_pins demod/chan_data_3_V] [get_bd_intf_pins mod_and_chan/chan_data_3_V]
  connect_bd_intf_net -intf_net mod_and_chan_chan_data_4_V [get_bd_intf_pins demod/chan_data_4_V] [get_bd_intf_pins mod_and_chan/chan_data_4_V]
  connect_bd_intf_net -intf_net mod_and_chan_ctrl_out_V [get_bd_intf_pins demod/ctrl_in_V] [get_bd_intf_pins mod_and_chan/ctrl_out_V]
  connect_bd_intf_net -intf_net sd_fec_dec_M_AXIS_DOUT [get_bd_intf_pins dec_add_keep/din] [get_bd_intf_pins sd_fec_dec/M_AXIS_DOUT]
connect_bd_intf_net -intf_net [get_bd_intf_nets sd_fec_dec_M_AXIS_DOUT] [get_bd_intf_pins dec_op_probe/mon] [get_bd_intf_pins sd_fec_dec/M_AXIS_DOUT]
  connect_bd_intf_net -intf_net sd_fec_dec_M_AXIS_STATUS [get_bd_intf_pins dec_stat_reinterpret/S_AXIS] [get_bd_intf_pins sd_fec_dec/M_AXIS_STATUS]
  connect_bd_intf_net -intf_net sd_fec_enc_M_AXIS_DOUT [get_bd_intf_pins enc_add_keep/din] [get_bd_intf_pins sd_fec_enc/M_AXIS_DOUT]
connect_bd_intf_net -intf_net [get_bd_intf_nets sd_fec_enc_M_AXIS_DOUT] [get_bd_intf_pins enc_op_probe/mon] [get_bd_intf_pins sd_fec_enc/M_AXIS_DOUT]
  connect_bd_intf_net -intf_net src_data_broadcast_M00_AXIS [get_bd_intf_pins sd_fec_enc/S_AXIS_DIN] [get_bd_intf_pins src_data_broadcast/M00_AXIS]
connect_bd_intf_net -intf_net [get_bd_intf_nets src_data_broadcast_M00_AXIS] [get_bd_intf_pins enc_ip_probe/mon] [get_bd_intf_pins src_data_broadcast/M00_AXIS]
  connect_bd_intf_net -intf_net src_data_broadcast_M01_AXIS [get_bd_intf_pins src_data_broadcast/M01_AXIS] [get_bd_intf_pins src_data_fifo/S_AXIS]
  connect_bd_intf_net -intf_net src_data_fifo_M_AXIS [get_bd_intf_pins src_data_fifo/M_AXIS] [get_bd_intf_pins stats/src_data_V_V]
  connect_bd_intf_net -intf_net sysref_in_1 [get_bd_intf_ports sysref_in] [get_bd_intf_pins usp_rf_data_converter_0_i/sysref_in]
  connect_bd_intf_net -intf_net usp_rf_data_converter_0_i_m00_axis [get_bd_intf_pins adc_sink_i/s00] [get_bd_intf_pins usp_rf_data_converter_0_i/m00_axis]
  connect_bd_intf_net -intf_net usp_rf_data_converter_0_i_vout00 [get_bd_intf_ports vout00] [get_bd_intf_pins usp_rf_data_converter_0_i/vout00]
  connect_bd_intf_net -intf_net vin0_01_0_1 [get_bd_intf_ports vin0_01] [get_bd_intf_pins usp_rf_data_converter_0_i/vin0_01]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_M_AXI_HPM0_FPD [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM0_FPD] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/S00_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_M_AXI_HPM1_FPD [get_bd_intf_pins axi_interconnect_0/S00_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M00_AXI [get_bd_intf_pins data_source/s_axi_CNTRL] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M00_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M01_AXI [get_bd_intf_pins sd_fec_enc/S_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M01_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M02_AXI [get_bd_intf_pins enc_ip_mon/s_axi_CNTRL] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M02_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M03_AXI [get_bd_intf_pins enc_op_mon/s_axi_CNTRL] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M03_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M04_AXI [get_bd_intf_pins sd_fec_dec/S_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M04_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M05_AXI [get_bd_intf_pins stats/s_axi_CNTRL] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M05_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M06_AXI [get_bd_intf_pins axi_gpio/S_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M06_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M07_AXI [get_bd_intf_pins dec_ip_mon/s_axi_CNTRL] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M07_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M08_AXI [get_bd_intf_pins dec_op_mon/s_axi_CNTRL] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M08_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M09_AXI [get_bd_intf_pins gpio_reset/S_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M09_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_0_axi_periph_M10_AXI [get_bd_intf_pins axi_intc/s_axi] [get_bd_intf_pins zynq_ultra_ps_e_0_axi_periph/M10_AXI]

  # Create port connections
  connect_bd_net -net ARESETN_1 [get_bd_pins axi_interconnect_0/ARESETN] [get_bd_pins rst_zynq_ultra_ps_e_0_99M/interconnect_aresetn]
  connect_bd_net -net adc_sink_i_done_flag [get_bd_ports done_flag] [get_bd_pins adc_sink_i/done_flag]
  connect_bd_net -net adc_sink_i_error_flag [get_bd_ports error_flag] [get_bd_pins adc_sink_i/error_flag]
  connect_bd_net -net axi_intc_irq [get_bd_pins axi_intc/irq] [get_bd_pins zynq_ultra_ps_e_0/pl_ps_irq0]
  connect_bd_net -net clk_wiz_clk_out1 [get_bd_pins clk_wiz/clk_out1] [get_bd_pins sd_fec_dec/core_clk] [get_bd_pins sd_fec_enc/core_clk]
  connect_bd_net -net clk_wiz_clk_out2 [get_bd_pins chan_ctrl_fifo/s_axis_aclk] [get_bd_pins chan_ctrl_reg/aclk] [get_bd_pins clk_wiz/clk_out2] [get_bd_pins data_source/ap_clk] [get_bd_pins dec_add_keep/ap_clk] [get_bd_pins dec_add_keep_trim/aclk] [get_bd_pins dec_ctrl_fifo/s_axis_aclk] [get_bd_pins dec_ctrl_reg/aclk] [get_bd_pins dec_ctrl_reinterpret/aclk] [get_bd_pins dec_data_reinterpret/aclk] [get_bd_pins dec_ip_mon/ap_clk] [get_bd_pins dec_ip_probe/clk] [get_bd_pins dec_keep_ctrl_fifo/s_axis_aclk] [get_bd_pins dec_op_mon/ap_clk] [get_bd_pins dec_op_probe/clk] [get_bd_pins dec_stat_reinterpret/aclk] [get_bd_pins demod/ap_clk] [get_bd_pins enc_add_keep/ap_clk] [get_bd_pins enc_add_keep_trim/aclk] [get_bd_pins enc_ctrl_reinterpret/aclk] [get_bd_pins enc_data_fifo/s_axis_aclk] [get_bd_pins enc_data_reinterpret/aclk] [get_bd_pins enc_ip_mon/ap_clk] [get_bd_pins enc_ip_probe/clk] [get_bd_pins enc_keep_ctrl_fifo/s_axis_aclk] [get_bd_pins enc_op_mon/ap_clk] [get_bd_pins enc_op_probe/clk] [get_bd_pins hard_chan_data_fifo/s_axis_aclk] [get_bd_pins hard_data_reg/aclk] [get_bd_pins llr_reinterpret/aclk] [get_bd_pins llr_reshape/aclk] [get_bd_pins mod_and_chan/ap_clk] [get_bd_pins rst_clk_wiz_300M/slowest_sync_clk] [get_bd_pins rtc/CLK] [get_bd_pins sd_fec_dec/m_axis_dout_aclk] [get_bd_pins sd_fec_dec/m_axis_status_aclk] [get_bd_pins sd_fec_dec/s_axis_ctrl_aclk] [get_bd_pins sd_fec_dec/s_axis_din_aclk] [get_bd_pins sd_fec_enc/m_axis_dout_aclk] [get_bd_pins sd_fec_enc/m_axis_status_aclk] [get_bd_pins sd_fec_enc/s_axis_ctrl_aclk] [get_bd_pins sd_fec_enc/s_axis_din_aclk] [get_bd_pins src_data_broadcast/aclk] [get_bd_pins src_data_fifo/s_axis_aclk] [get_bd_pins stats/ap_clk]
  connect_bd_net -net clk_wiz_clk_out3 [get_bd_pins adc_sink_i/s0_axis_clock] [get_bd_pins axi_gpio/s_axi_aclk] [get_bd_pins axi_intc/s_axi_aclk] [get_bd_pins clk_wiz/clk_out3] [get_bd_pins dac_source_i/m0_axis_clock] [get_bd_pins data_source/cntrl_aclk] [get_bd_pins dec_ip_mon/cntrl_aclk] [get_bd_pins dec_op_mon/cntrl_aclk] [get_bd_pins enc_ip_mon/cntrl_aclk] [get_bd_pins enc_op_mon/cntrl_aclk] [get_bd_pins gpio_reset/s_axi_aclk] [get_bd_pins rst_clk_wiz_100M/slowest_sync_clk] [get_bd_pins sd_fec_dec/s_axi_aclk] [get_bd_pins sd_fec_enc/s_axi_aclk] [get_bd_pins stats/cntrl_aclk] [get_bd_pins usp_rf_data_converter_0_i/m0_axis_aclk] [get_bd_pins usp_rf_data_converter_0_i/s0_axis_aclk] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M00_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M01_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M02_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M03_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M04_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M05_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M06_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M07_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M08_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M09_ACLK] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M10_ACLK]
  connect_bd_net -net clk_wiz_locked [get_bd_pins clk_wiz/locked] [get_bd_pins rst_clk_wiz_100M/dcm_locked] [get_bd_pins rst_clk_wiz_300M/dcm_locked]
  connect_bd_net -net concat_int_dout [get_bd_pins axi_intc/intr] [get_bd_pins concat_int/dout]
  connect_bd_net -net const_1_dout [get_bd_pins const_1/dout] [get_bd_pins sd_fec_enc/m_axis_status_tready]
  connect_bd_net -net dec_ip_probe_last_op [get_bd_pins dec_ip_mon/tlast_V] [get_bd_pins dec_ip_probe/last_op]
  connect_bd_net -net dec_ip_probe_ready_op [get_bd_pins dec_ip_mon/tready_V] [get_bd_pins dec_ip_probe/ready_op]
  connect_bd_net -net dec_ip_probe_valid_op [get_bd_pins dec_ip_mon/tvalid_V] [get_bd_pins dec_ip_probe/valid_op]
  connect_bd_net -net dec_op_probe_last_op [get_bd_pins dec_op_mon/tlast_V] [get_bd_pins dec_op_probe/last_op]
  connect_bd_net -net dec_op_probe_ready_op [get_bd_pins dec_op_mon/tready_V] [get_bd_pins dec_op_probe/ready_op]
  connect_bd_net -net dec_op_probe_valid_op [get_bd_pins dec_op_mon/tvalid_V] [get_bd_pins dec_op_probe/valid_op]
  connect_bd_net -net emio_uart1_rxd_0_1 [get_bd_ports emio_uart1_rxd_0] [get_bd_pins zynq_ultra_ps_e_0/emio_uart1_rxd]
  connect_bd_net -net enc_ip_probe_last_op [get_bd_pins enc_ip_mon/tlast_V] [get_bd_pins enc_ip_probe/last_op]
  connect_bd_net -net enc_ip_probe_ready_op [get_bd_pins enc_ip_mon/tready_V] [get_bd_pins enc_ip_probe/ready_op]
  connect_bd_net -net enc_ip_probe_valid_op [get_bd_pins enc_ip_mon/tvalid_V] [get_bd_pins enc_ip_probe/valid_op]
  connect_bd_net -net enc_op_probe_last_op [get_bd_pins enc_op_mon/tlast_V] [get_bd_pins enc_op_probe/last_op]
  connect_bd_net -net enc_op_probe_ready_op [get_bd_pins enc_op_mon/tready_V] [get_bd_pins enc_op_probe/ready_op]
  connect_bd_net -net enc_op_probe_valid_op [get_bd_pins enc_op_mon/tvalid_V] [get_bd_pins enc_op_probe/valid_op]
  connect_bd_net -net gpio_reset_gpio_io_o [get_bd_pins gpio_reset/gpio_io_o] [get_bd_pins reset_slice/Din]
  connect_bd_net -net reset_rtl_0_1 [get_bd_ports reset] [get_bd_pins clk_wiz/reset] [get_bd_pins rst_clk_wiz_100M/ext_reset_in] [get_bd_pins rst_clk_wiz_300M/ext_reset_in]
  connect_bd_net -net reset_slice_Dout [get_bd_pins reset_slice/Dout] [get_bd_pins rst_clk_wiz_300M/aux_reset_in]
  connect_bd_net -net rst_clk_wiz_100M_interconnect_aresetn [get_bd_pins rst_clk_wiz_100M/interconnect_aresetn] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/ARESETN]
  connect_bd_net -net rst_clk_wiz_100M_peripheral_aresetn [get_bd_pins axi_gpio/s_axi_aresetn] [get_bd_pins axi_intc/s_axi_aresetn] [get_bd_pins data_source/ap_rst_n_cntrl_aclk] [get_bd_pins dec_ip_mon/ap_rst_n_cntrl_aclk] [get_bd_pins dec_op_mon/ap_rst_n_cntrl_aclk] [get_bd_pins enc_ip_mon/ap_rst_n_cntrl_aclk] [get_bd_pins enc_op_mon/ap_rst_n_cntrl_aclk] [get_bd_pins gpio_reset/s_axi_aresetn] [get_bd_pins rst_clk_wiz_100M/peripheral_aresetn] [get_bd_pins stats/ap_rst_n_cntrl_aclk] [get_bd_pins usp_rf_data_converter_0_i/m0_axis_aresetn] [get_bd_pins usp_rf_data_converter_0_i/s0_axis_aresetn] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M00_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M01_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M02_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M03_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M04_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M05_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M06_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M07_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M08_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M09_ARESETN] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/M10_ARESETN]
  connect_bd_net -net rst_clk_wiz_300M_interconnect_aresetn [get_bd_pins chan_ctrl_fifo/s_axis_aresetn] [get_bd_pins chan_ctrl_reg/aresetn] [get_bd_pins dec_add_keep_trim/aresetn] [get_bd_pins dec_ctrl_fifo/s_axis_aresetn] [get_bd_pins dec_ctrl_reg/aresetn] [get_bd_pins dec_ctrl_reinterpret/aresetn] [get_bd_pins dec_data_reinterpret/aresetn] [get_bd_pins dec_keep_ctrl_fifo/s_axis_aresetn] [get_bd_pins dec_stat_reinterpret/aresetn] [get_bd_pins enc_add_keep_trim/aresetn] [get_bd_pins enc_ctrl_reinterpret/aresetn] [get_bd_pins enc_data_fifo/s_axis_aresetn] [get_bd_pins enc_data_reinterpret/aresetn] [get_bd_pins enc_keep_ctrl_fifo/s_axis_aresetn] [get_bd_pins hard_chan_data_fifo/s_axis_aresetn] [get_bd_pins hard_data_reg/aresetn] [get_bd_pins llr_reinterpret/aresetn] [get_bd_pins llr_reshape/aresetn] [get_bd_pins rst_clk_wiz_300M/interconnect_aresetn] [get_bd_pins src_data_broadcast/aresetn] [get_bd_pins src_data_fifo/s_axis_aresetn]
  connect_bd_net -net rst_clk_wiz_300M_peripheral_aresetn [get_bd_pins data_source/ap_rst_n] [get_bd_pins dec_add_keep/ap_rst_n] [get_bd_pins dec_ip_mon/ap_rst_n] [get_bd_pins dec_op_mon/ap_rst_n] [get_bd_pins demod/ap_rst_n] [get_bd_pins enc_add_keep/ap_rst_n] [get_bd_pins enc_ip_mon/ap_rst_n] [get_bd_pins enc_op_mon/ap_rst_n] [get_bd_pins mod_and_chan/ap_rst_n] [get_bd_pins rst_clk_wiz_300M/peripheral_aresetn] [get_bd_pins sd_fec_dec/reset_n] [get_bd_pins sd_fec_enc/reset_n] [get_bd_pins stats/ap_rst_n]
  connect_bd_net -net rst_clk_wiz_300M_peripheral_reset [get_bd_pins rst_clk_wiz_300M/peripheral_reset] [get_bd_pins rtc/SCLR]
  connect_bd_net -net rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn [get_bd_pins adc_sink_i/s_axi_aresetn] [get_bd_pins axi_interconnect_0/M00_ARESETN] [get_bd_pins axi_interconnect_0/M01_ARESETN] [get_bd_pins axi_interconnect_0/M02_ARESETN] [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins dac_source_i/s_axi_aresetn] [get_bd_pins rst_zynq_ultra_ps_e_0_99M/peripheral_aresetn] [get_bd_pins usp_rf_data_converter_0_i/s_axi_aresetn] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/S00_ARESETN]
  connect_bd_net -net rtc_Q [get_bd_pins dec_ip_mon/rtc_V] [get_bd_pins dec_op_mon/rtc_V] [get_bd_pins enc_ip_mon/rtc_V] [get_bd_pins enc_op_mon/rtc_V] [get_bd_pins rtc/Q]
  connect_bd_net -net sd_fec_dec_interrupt [get_bd_pins concat_int/In1] [get_bd_pins sd_fec_dec/interrupt]
  connect_bd_net -net sd_fec_enc_interrupt [get_bd_pins concat_int/In0] [get_bd_pins sd_fec_enc/interrupt]
  connect_bd_net -net usp_rf_data_converter_0_i_clk_adc0 [get_bd_ports clk_adc0] [get_bd_pins usp_rf_data_converter_0_i/clk_adc0]
  connect_bd_net -net usp_rf_data_converter_0_i_clk_dac0 [get_bd_ports clk_dac0] [get_bd_pins usp_rf_data_converter_0_i/clk_dac0]
  connect_bd_net -net usp_rf_data_converter_0_i_irq [get_bd_ports irq] [get_bd_pins usp_rf_data_converter_0_i/irq]
  connect_bd_net -net zynq_ultra_ps_e_0_emio_uart1_txd [get_bd_ports emio_uart1_txd_0] [get_bd_pins zynq_ultra_ps_e_0/emio_uart1_txd]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk0 [get_bd_pins adc_sink_i/s_axi_aclk] [get_bd_pins axi_interconnect_0/ACLK] [get_bd_pins axi_interconnect_0/M00_ACLK] [get_bd_pins axi_interconnect_0/M01_ACLK] [get_bd_pins axi_interconnect_0/M02_ACLK] [get_bd_pins axi_interconnect_0/S00_ACLK] [get_bd_pins dac_source_i/s_axi_aclk] [get_bd_pins rst_zynq_ultra_ps_e_0_99M/slowest_sync_clk] [get_bd_pins usp_rf_data_converter_0_i/s_axi_aclk] [get_bd_pins zynq_ultra_ps_e_0/maxihpm0_fpd_aclk] [get_bd_pins zynq_ultra_ps_e_0/maxihpm1_fpd_aclk] [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins zynq_ultra_ps_e_0_axi_periph/S00_ACLK]
  connect_bd_net -net zynq_ultra_ps_e_0_pl_resetn0 [get_bd_pins rst_zynq_ultra_ps_e_0_99M/ext_reset_in] [get_bd_pins zynq_ultra_ps_e_0/pl_resetn0]

  # Create address segments
  create_bd_addr_seg -range 0x00040000 -offset 0xB0000000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs adc_sink_i/s_axi/reg0] SEG_adc_sink_i_reg0
  create_bd_addr_seg -range 0x00001000 -offset 0xA00C0000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs axi_gpio/S_AXI/Reg] SEG_axi_gpio_Reg
  create_bd_addr_seg -range 0x00001000 -offset 0xA00C2000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs axi_intc/S_AXI/Reg] SEG_axi_intc_Reg
  create_bd_addr_seg -range 0x00040000 -offset 0xB0040000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs dac_source_i/s_axi/reg0] SEG_dac_source_i_reg0
  create_bd_addr_seg -range 0x00010000 -offset 0xA0000000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs data_source/s_axi_CNTRL/Reg] SEG_data_source_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0xA00D0000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs dec_ip_mon/s_axi_CNTRL/Reg] SEG_dec_ip_mon_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0xA00E0000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs dec_op_mon/s_axi_CNTRL/Reg] SEG_dec_op_mon_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0xA0010000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs enc_ip_mon/s_axi_CNTRL/Reg] SEG_enc_ip_mon_Reg
  create_bd_addr_seg -range 0x00010000 -offset 0xA0020000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs enc_op_mon/s_axi_CNTRL/Reg] SEG_enc_op_mon_Reg
  create_bd_addr_seg -range 0x00001000 -offset 0xA00C1000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs gpio_reset/S_AXI/Reg] SEG_gpio_reset_Reg
  create_bd_addr_seg -range 0x00040000 -offset 0xA0080000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs sd_fec_dec/S_AXI/PARAMS] SEG_sd_fec_dec_PARAMS
  create_bd_addr_seg -range 0x00040000 -offset 0xA0040000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs sd_fec_enc/S_AXI/PARAMS] SEG_sd_fec_enc_PARAMS
  create_bd_addr_seg -range 0x00010000 -offset 0xA0030000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs stats/s_axi_CNTRL/Reg] SEG_stats_Reg
  create_bd_addr_seg -range 0x00040000 -offset 0xB0080000 [get_bd_addr_spaces zynq_ultra_ps_e_0/Data] [get_bd_addr_segs usp_rf_data_converter_0_i/s_axi/Reg] SEG_usp_rf_data_converter_0_i_Reg


  # Restore current instance
  current_bd_instance $oldCurInst

  validate_bd_design
  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


