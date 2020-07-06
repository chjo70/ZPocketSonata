//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
//Date        : Sat May 25 00:48:29 2019
//Host        : xcosswbld07 running 64-bit Red Hat Enterprise Linux Workstation release 7.2 (Maipo)
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=87,numReposBlks=69,numNonXlnxBlks=0,numHierBlks=18,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=10,numHdlrefBlks=2,numPkgbdBlks=0,bdsource=USER,da_zynq_ultra_ps_e_cnt=1,synth_mode=Global}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
   (adc0_clk_clk_n,
    adc0_clk_clk_p,
    clk_adc0,
    clk_dac0,
    dac0_clk_clk_n,
    dac0_clk_clk_p,
    done_flag,
    emio_uart1_rxd_0,
    emio_uart1_txd_0,
    error_flag,
    irq,
    led_bits_tri_o,
    reset,
    sys_diff_clock_clk_n,
    sys_diff_clock_clk_p,
    sysref_in_diff_n,
    sysref_in_diff_p,
    vin0_01_v_n,
    vin0_01_v_p,
    vout00_v_n,
    vout00_v_p);
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 adc0_clk CLK_N" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME adc0_clk, CAN_DEBUG false, FREQ_HZ 2000000000.0" *) input adc0_clk_clk_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 adc0_clk CLK_P" *) input adc0_clk_clk_p;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_ADC0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_ADC0, CLK_DOMAIN design_1_usp_rf_data_converter_0_i_0_clk_adc0, FREQ_HZ 125000000.0, INSERT_VIP 0, PHASE 0.000" *) output clk_adc0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_DAC0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_DAC0, CLK_DOMAIN design_1_usp_rf_data_converter_0_i_0_clk_dac0, FREQ_HZ 400000000.0, INSERT_VIP 0, PHASE 0.000" *) output clk_dac0;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 dac0_clk CLK_N" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME dac0_clk, CAN_DEBUG false, FREQ_HZ 6400000000.0" *) input dac0_clk_clk_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 dac0_clk CLK_P" *) input dac0_clk_clk_p;
  output done_flag;
  input emio_uart1_rxd_0;
  output emio_uart1_txd_0;
  output error_flag;
  output irq;
  (* X_INTERFACE_INFO = "xilinx.com:interface:gpio:1.0 led_bits TRI_O" *) output [4:0]led_bits_tri_o;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET, INSERT_VIP 0, POLARITY ACTIVE_HIGH" *) input reset;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 sys_diff_clock CLK_N" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME sys_diff_clock, CAN_DEBUG false, FREQ_HZ 100000000" *) input sys_diff_clock_clk_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_clock:1.0 sys_diff_clock CLK_P" *) input sys_diff_clock_clk_p;
  (* X_INTERFACE_INFO = "xilinx.com:display_usp_rf_data_converter:diff_pins:1.0 sysref_in diff_n" *) input sysref_in_diff_n;
  (* X_INTERFACE_INFO = "xilinx.com:display_usp_rf_data_converter:diff_pins:1.0 sysref_in diff_p" *) input sysref_in_diff_p;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_analog_io:1.0 vin0_01 V_N" *) input vin0_01_v_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_analog_io:1.0 vin0_01 V_P" *) input vin0_01_v_p;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_analog_io:1.0 vout00 V_N" *) output vout00_v_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:diff_analog_io:1.0 vout00 V_P" *) output vout00_v_p;

  wire [0:0]ARESETN_1;
  wire adc0_clk_1_CLK_N;
  wire adc0_clk_1_CLK_P;
  wire adc_sink_i_done_flag;
  wire adc_sink_i_error_flag;
  wire [4:0]axi_gpio_GPIO_TRI_O;
  wire axi_intc_irq;
  wire [39:0]axi_interconnect_0_M00_AXI_ARADDR;
  wire axi_interconnect_0_M00_AXI_ARREADY;
  wire axi_interconnect_0_M00_AXI_ARVALID;
  wire [39:0]axi_interconnect_0_M00_AXI_AWADDR;
  wire axi_interconnect_0_M00_AXI_AWREADY;
  wire axi_interconnect_0_M00_AXI_AWVALID;
  wire axi_interconnect_0_M00_AXI_BREADY;
  wire [1:0]axi_interconnect_0_M00_AXI_BRESP;
  wire axi_interconnect_0_M00_AXI_BVALID;
  wire [31:0]axi_interconnect_0_M00_AXI_RDATA;
  wire axi_interconnect_0_M00_AXI_RREADY;
  wire [1:0]axi_interconnect_0_M00_AXI_RRESP;
  wire axi_interconnect_0_M00_AXI_RVALID;
  wire [31:0]axi_interconnect_0_M00_AXI_WDATA;
  wire axi_interconnect_0_M00_AXI_WREADY;
  wire [3:0]axi_interconnect_0_M00_AXI_WSTRB;
  wire axi_interconnect_0_M00_AXI_WVALID;
  wire [39:0]axi_interconnect_0_M01_AXI_ARADDR;
  wire axi_interconnect_0_M01_AXI_ARREADY;
  wire axi_interconnect_0_M01_AXI_ARVALID;
  wire [39:0]axi_interconnect_0_M01_AXI_AWADDR;
  wire axi_interconnect_0_M01_AXI_AWREADY;
  wire axi_interconnect_0_M01_AXI_AWVALID;
  wire axi_interconnect_0_M01_AXI_BREADY;
  wire [1:0]axi_interconnect_0_M01_AXI_BRESP;
  wire axi_interconnect_0_M01_AXI_BVALID;
  wire [31:0]axi_interconnect_0_M01_AXI_RDATA;
  wire axi_interconnect_0_M01_AXI_RREADY;
  wire [1:0]axi_interconnect_0_M01_AXI_RRESP;
  wire axi_interconnect_0_M01_AXI_RVALID;
  wire [31:0]axi_interconnect_0_M01_AXI_WDATA;
  wire axi_interconnect_0_M01_AXI_WREADY;
  wire [3:0]axi_interconnect_0_M01_AXI_WSTRB;
  wire axi_interconnect_0_M01_AXI_WVALID;
  wire [39:0]axi_interconnect_0_M02_AXI_ARADDR;
  wire axi_interconnect_0_M02_AXI_ARREADY;
  wire [0:0]axi_interconnect_0_M02_AXI_ARVALID;
  wire [39:0]axi_interconnect_0_M02_AXI_AWADDR;
  wire axi_interconnect_0_M02_AXI_AWREADY;
  wire [0:0]axi_interconnect_0_M02_AXI_AWVALID;
  wire [0:0]axi_interconnect_0_M02_AXI_BREADY;
  wire [1:0]axi_interconnect_0_M02_AXI_BRESP;
  wire axi_interconnect_0_M02_AXI_BVALID;
  wire [31:0]axi_interconnect_0_M02_AXI_RDATA;
  wire [0:0]axi_interconnect_0_M02_AXI_RREADY;
  wire [1:0]axi_interconnect_0_M02_AXI_RRESP;
  wire axi_interconnect_0_M02_AXI_RVALID;
  wire [31:0]axi_interconnect_0_M02_AXI_WDATA;
  wire axi_interconnect_0_M02_AXI_WREADY;
  wire [3:0]axi_interconnect_0_M02_AXI_WSTRB;
  wire [0:0]axi_interconnect_0_M02_AXI_WVALID;
  wire [63:0]chan_ctrl_fifo_M_AXIS_TDATA;
  wire chan_ctrl_fifo_M_AXIS_TREADY;
  wire chan_ctrl_fifo_M_AXIS_TVALID;
  wire [63:0]chan_ctrl_reg_M_AXIS_TDATA;
  wire chan_ctrl_reg_M_AXIS_TREADY;
  wire chan_ctrl_reg_M_AXIS_TVALID;
  wire clk_wiz_clk_out1;
  wire clk_wiz_clk_out2;
  wire clk_wiz_clk_out3;
  wire clk_wiz_locked;
  wire [1:0]concat_int_dout;
  wire [0:0]const_1_dout;
  wire dac0_clk_1_CLK_N;
  wire dac0_clk_1_CLK_P;
  wire [255:0]dac_source_i_m00_TDATA;
  wire dac_source_i_m00_TREADY;
  wire dac_source_i_m00_TVALID;
  wire [63:0]data_source_chan_ctrl_out_V_TDATA;
  wire data_source_chan_ctrl_out_V_TREADY;
  wire data_source_chan_ctrl_out_V_TVALID;
  wire [39:0]data_source_dec_ctrl_out_TDATA;
  wire [0:0]data_source_dec_ctrl_out_TLAST;
  wire data_source_dec_ctrl_out_TREADY;
  wire data_source_dec_ctrl_out_TVALID;
  wire [63:0]data_source_dec_keep_ctrl_V_V_TDATA;
  wire data_source_dec_keep_ctrl_V_V_TREADY;
  wire data_source_dec_keep_ctrl_V_V_TVALID;
  wire [39:0]data_source_enc_ctrl_out_TDATA;
  wire [0:0]data_source_enc_ctrl_out_TLAST;
  wire data_source_enc_ctrl_out_TREADY;
  wire data_source_enc_ctrl_out_TVALID;
  wire [63:0]data_source_enc_keep_ctrl_V_V_TDATA;
  wire data_source_enc_keep_ctrl_V_V_TREADY;
  wire data_source_enc_keep_ctrl_V_V_TVALID;
  wire [127:0]data_source_hard_data_out_TDATA;
  wire [15:0]data_source_hard_data_out_TKEEP;
  wire [0:0]data_source_hard_data_out_TLAST;
  wire data_source_hard_data_out_TREADY;
  wire data_source_hard_data_out_TVALID;
  wire [127:0]dec_add_keep_dout_TDATA;
  wire [15:0]dec_add_keep_dout_TKEEP;
  wire [0:0]dec_add_keep_dout_TLAST;
  wire dec_add_keep_dout_TREADY;
  wire dec_add_keep_dout_TVALID;
  wire [15:0]dec_add_keep_trim_M_AXIS_TDATA;
  wire dec_add_keep_trim_M_AXIS_TREADY;
  wire dec_add_keep_trim_M_AXIS_TVALID;
  wire [31:0]dec_ctrl_fifo_M_AXIS_TDATA;
  wire dec_ctrl_fifo_M_AXIS_TREADY;
  wire dec_ctrl_fifo_M_AXIS_TVALID;
  wire [31:0]dec_ctrl_reg_M_AXIS_TDATA;
  wire dec_ctrl_reg_M_AXIS_TLAST;
  wire dec_ctrl_reg_M_AXIS_TREADY;
  wire dec_ctrl_reg_M_AXIS_TVALID;
  wire [31:0]dec_ctrl_reinterpret_M_AXIS_TDATA;
  wire dec_ctrl_reinterpret_M_AXIS_TLAST;
  wire dec_ctrl_reinterpret_M_AXIS_TREADY;
  wire dec_ctrl_reinterpret_M_AXIS_TVALID;
  wire [127:0]dec_data_reinterpret_M_AXIS_TDATA;
  wire dec_data_reinterpret_M_AXIS_TLAST;
  wire dec_data_reinterpret_M_AXIS_TREADY;
  wire dec_data_reinterpret_M_AXIS_TVALID;
  wire dec_ip_probe_last_op;
  wire dec_ip_probe_ready_op;
  wire dec_ip_probe_valid_op;
  wire [15:0]dec_keep_ctrl_fifo_M_AXIS_TDATA;
  wire dec_keep_ctrl_fifo_M_AXIS_TREADY;
  wire dec_keep_ctrl_fifo_M_AXIS_TVALID;
  wire dec_op_probe_last_op;
  wire dec_op_probe_ready_op;
  wire dec_op_probe_valid_op;
  wire [39:0]dec_stat_reinterpret_M_AXIS_TDATA;
  wire dec_stat_reinterpret_M_AXIS_TREADY;
  wire dec_stat_reinterpret_M_AXIS_TVALID;
  wire [127:0]demod_hard_data_TDATA;
  wire [0:0]demod_hard_data_TLAST;
  wire demod_hard_data_TREADY;
  wire demod_hard_data_TVALID;
  wire [191:0]demod_soft_data_TDATA;
  wire [23:0]demod_soft_data_TKEEP;
  wire [0:0]demod_soft_data_TLAST;
  wire demod_soft_data_TREADY;
  wire demod_soft_data_TVALID;
  wire diff_clock_rtl_0_1_CLK_N;
  wire diff_clock_rtl_0_1_CLK_P;
  wire emio_uart1_rxd_0_1;
  wire [127:0]enc_add_keep_dout_TDATA;
  wire [15:0]enc_add_keep_dout_TKEEP;
  wire [0:0]enc_add_keep_dout_TLAST;
  wire enc_add_keep_dout_TREADY;
  wire enc_add_keep_dout_TVALID;
  wire [15:0]enc_add_keep_trim_M_AXIS_TDATA;
  wire enc_add_keep_trim_M_AXIS_TREADY;
  wire enc_add_keep_trim_M_AXIS_TVALID;
  wire [31:0]enc_ctrl_reinterpret_M_AXIS_TDATA;
  wire enc_ctrl_reinterpret_M_AXIS_TREADY;
  wire enc_ctrl_reinterpret_M_AXIS_TVALID;
  wire [95:0]enc_data_fifo_M_AXIS_TDATA;
  wire enc_data_fifo_M_AXIS_TREADY;
  wire enc_data_fifo_M_AXIS_TVALID;
  wire [95:0]enc_data_reinterpret_M_AXIS_TDATA;
  wire [11:0]enc_data_reinterpret_M_AXIS_TKEEP;
  wire enc_data_reinterpret_M_AXIS_TLAST;
  wire enc_data_reinterpret_M_AXIS_TREADY;
  wire enc_data_reinterpret_M_AXIS_TVALID;
  wire enc_ip_probe_last_op;
  wire enc_ip_probe_ready_op;
  wire enc_ip_probe_valid_op;
  wire [15:0]enc_keep_ctrl_fifo_M_AXIS_TDATA;
  wire enc_keep_ctrl_fifo_M_AXIS_TREADY;
  wire enc_keep_ctrl_fifo_M_AXIS_TVALID;
  wire enc_op_probe_last_op;
  wire enc_op_probe_ready_op;
  wire enc_op_probe_valid_op;
  wire [7:0]gpio_reset_gpio_io_o;
  wire [127:0]hard_chan_data_fifo_M_AXIS_TDATA;
  wire hard_chan_data_fifo_M_AXIS_TLAST;
  wire hard_chan_data_fifo_M_AXIS_TREADY;
  wire hard_chan_data_fifo_M_AXIS_TVALID;
  wire [127:0]hard_data_reg_M_AXIS_TDATA;
  wire [15:0]hard_data_reg_M_AXIS_TKEEP;
  wire hard_data_reg_M_AXIS_TLAST;
  wire hard_data_reg_M_AXIS_TREADY;
  wire hard_data_reg_M_AXIS_TVALID;
  wire [255:0]llr_reinterpret_M_AXIS_TDATA;
  wire llr_reinterpret_M_AXIS_TLAST;
  wire llr_reinterpret_M_AXIS_TREADY;
  wire llr_reinterpret_M_AXIS_TVALID;
  wire [255:0]llr_reshape_M_AXIS_TDATA;
  wire [31:0]llr_reshape_M_AXIS_TKEEP;
  wire llr_reshape_M_AXIS_TLAST;
  wire llr_reshape_M_AXIS_TREADY;
  wire llr_reshape_M_AXIS_TVALID;
  wire [39:0]mod_and_chan_chan_data_1_V_TDATA;
  wire mod_and_chan_chan_data_1_V_TREADY;
  wire mod_and_chan_chan_data_1_V_TVALID;
  wire [39:0]mod_and_chan_chan_data_2_V_TDATA;
  wire mod_and_chan_chan_data_2_V_TREADY;
  wire mod_and_chan_chan_data_2_V_TVALID;
  wire [39:0]mod_and_chan_chan_data_3_V_TDATA;
  wire mod_and_chan_chan_data_3_V_TREADY;
  wire mod_and_chan_chan_data_3_V_TVALID;
  wire [39:0]mod_and_chan_chan_data_4_V_TDATA;
  wire mod_and_chan_chan_data_4_V_TREADY;
  wire mod_and_chan_chan_data_4_V_TVALID;
  wire [63:0]mod_and_chan_ctrl_out_V_TDATA;
  wire mod_and_chan_ctrl_out_V_TREADY;
  wire mod_and_chan_ctrl_out_V_TVALID;
  wire reset_rtl_0_1;
  wire [0:0]reset_slice_Dout;
  wire [0:0]rst_clk_wiz_100M_interconnect_aresetn;
  wire [0:0]rst_clk_wiz_100M_peripheral_aresetn;
  wire [0:0]rst_clk_wiz_300M_interconnect_aresetn;
  wire [0:0]rst_clk_wiz_300M_peripheral_aresetn;
  wire [0:0]rst_clk_wiz_300M_peripheral_reset;
  wire [0:0]rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn;
  wire [31:0]rtc_Q;
  wire [127:0]sd_fec_dec_M_AXIS_DOUT_TDATA;
  wire sd_fec_dec_M_AXIS_DOUT_TLAST;
  wire sd_fec_dec_M_AXIS_DOUT_TREADY;
  wire sd_fec_dec_M_AXIS_DOUT_TVALID;
  wire [31:0]sd_fec_dec_M_AXIS_STATUS_TDATA;
  wire sd_fec_dec_M_AXIS_STATUS_TREADY;
  wire sd_fec_dec_M_AXIS_STATUS_TVALID;
  wire sd_fec_dec_interrupt;
  wire [127:0]sd_fec_enc_M_AXIS_DOUT_TDATA;
  wire sd_fec_enc_M_AXIS_DOUT_TLAST;
  wire sd_fec_enc_M_AXIS_DOUT_TREADY;
  wire sd_fec_enc_M_AXIS_DOUT_TVALID;
  wire sd_fec_enc_interrupt;
  wire [127:0]src_data_broadcast_M00_AXIS_TDATA;
  wire [0:0]src_data_broadcast_M00_AXIS_TLAST;
  wire src_data_broadcast_M00_AXIS_TREADY;
  wire [0:0]src_data_broadcast_M00_AXIS_TVALID;
  wire [255:128]src_data_broadcast_M01_AXIS_TDATA;
  wire [31:16]src_data_broadcast_M01_AXIS_TKEEP;
  wire [1:1]src_data_broadcast_M01_AXIS_TLAST;
  wire src_data_broadcast_M01_AXIS_TREADY;
  wire [1:1]src_data_broadcast_M01_AXIS_TVALID;
  wire [127:0]src_data_fifo_M_AXIS_TDATA;
  wire src_data_fifo_M_AXIS_TREADY;
  wire src_data_fifo_M_AXIS_TVALID;
  wire sysref_in_1_diff_n;
  wire sysref_in_1_diff_p;
  wire usp_rf_data_converter_0_i_clk_adc0;
  wire usp_rf_data_converter_0_i_clk_dac0;
  wire usp_rf_data_converter_0_i_irq;
  wire [127:0]usp_rf_data_converter_0_i_m00_axis_TDATA;
  wire usp_rf_data_converter_0_i_m00_axis_TREADY;
  wire usp_rf_data_converter_0_i_m00_axis_TVALID;
  wire usp_rf_data_converter_0_i_vout00_V_N;
  wire usp_rf_data_converter_0_i_vout00_V_P;
  wire vin0_01_0_1_V_N;
  wire vin0_01_0_1_V_P;
  wire [39:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARADDR;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARBURST;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARCACHE;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARID;
  wire [7:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARLEN;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARLOCK;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARPROT;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARQOS;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARREADY;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARSIZE;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARUSER;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARVALID;
  wire [39:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWADDR;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWBURST;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWCACHE;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWID;
  wire [7:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWLEN;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWLOCK;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWPROT;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWQOS;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWREADY;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWSIZE;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWUSER;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWVALID;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BID;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BRESP;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BVALID;
  wire [127:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RDATA;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RID;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RLAST;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RRESP;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RVALID;
  wire [127:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WDATA;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WLAST;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WREADY;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WSTRB;
  wire zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WVALID;
  wire [39:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARADDR;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARBURST;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARCACHE;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARID;
  wire [7:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARLEN;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARLOCK;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARPROT;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARQOS;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARREADY;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARSIZE;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARVALID;
  wire [39:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWADDR;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWBURST;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWCACHE;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWID;
  wire [7:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWLEN;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWLOCK;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWPROT;
  wire [3:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWQOS;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWREADY;
  wire [2:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWSIZE;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWVALID;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BID;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BRESP;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BVALID;
  wire [127:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RDATA;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RID;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RLAST;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RRESP;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RVALID;
  wire [127:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WDATA;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WLAST;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WREADY;
  wire [15:0]zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WSTRB;
  wire zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WVALID;
  wire [7:0]zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARVALID;
  wire [7:0]zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M00_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M00_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M00_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M00_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M00_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M00_AXI_WVALID;
  wire [17:0]zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARVALID;
  wire [17:0]zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_BREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M01_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_RREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M01_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_WREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M01_AXI_WVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M02_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M02_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M02_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M02_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M02_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M02_AXI_WVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M03_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M03_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M03_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M03_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M03_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M03_AXI_WVALID;
  wire [17:0]zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARVALID;
  wire [17:0]zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_BREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M04_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_RREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M04_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_WREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M04_AXI_WVALID;
  wire [6:0]zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARVALID;
  wire [6:0]zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M05_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M05_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M05_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M05_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M05_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M05_AXI_WVALID;
  wire [8:0]zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARVALID;
  wire [8:0]zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M06_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M06_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M06_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M06_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M06_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M06_AXI_WVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M07_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M07_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M07_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M07_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M07_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M07_AXI_WVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARVALID;
  wire [5:0]zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M08_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M08_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M08_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M08_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M08_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M08_AXI_WVALID;
  wire [8:0]zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARVALID;
  wire [8:0]zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M09_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M09_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M09_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M09_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M09_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M09_AXI_WVALID;
  wire [8:0]zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARVALID;
  wire [8:0]zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWADDR;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWREADY;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWVALID;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M10_AXI_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_BVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M10_AXI_RDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_M10_AXI_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_RVALID;
  wire [31:0]zynq_ultra_ps_e_0_axi_periph_M10_AXI_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_WREADY;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_M10_AXI_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_M10_AXI_WVALID;
  wire zynq_ultra_ps_e_0_emio_uart1_txd;
  wire zynq_ultra_ps_e_0_pl_clk0;
  wire zynq_ultra_ps_e_0_pl_resetn0;
  wire [31:0]NLW_src_data_broadcast_m_axis_tkeep_UNCONNECTED;

  assign adc0_clk_1_CLK_N = adc0_clk_clk_n;
  assign adc0_clk_1_CLK_P = adc0_clk_clk_p;
  assign clk_adc0 = usp_rf_data_converter_0_i_clk_adc0;
  assign clk_dac0 = usp_rf_data_converter_0_i_clk_dac0;
  assign dac0_clk_1_CLK_N = dac0_clk_clk_n;
  assign dac0_clk_1_CLK_P = dac0_clk_clk_p;
  assign diff_clock_rtl_0_1_CLK_N = sys_diff_clock_clk_n;
  assign diff_clock_rtl_0_1_CLK_P = sys_diff_clock_clk_p;
  assign done_flag = adc_sink_i_done_flag;
  assign emio_uart1_rxd_0_1 = emio_uart1_rxd_0;
  assign emio_uart1_txd_0 = zynq_ultra_ps_e_0_emio_uart1_txd;
  assign error_flag = adc_sink_i_error_flag;
  assign irq = usp_rf_data_converter_0_i_irq;
  assign led_bits_tri_o[4:0] = axi_gpio_GPIO_TRI_O;
  assign reset_rtl_0_1 = reset;
  assign sysref_in_1_diff_n = sysref_in_diff_n;
  assign sysref_in_1_diff_p = sysref_in_diff_p;
  assign vin0_01_0_1_V_N = vin0_01_v_n;
  assign vin0_01_0_1_V_P = vin0_01_v_p;
  assign vout00_v_n = usp_rf_data_converter_0_i_vout00_V_N;
  assign vout00_v_p = usp_rf_data_converter_0_i_vout00_V_P;
  design_1_adc_sink_i_0 adc_sink_i
       (.done_flag(adc_sink_i_done_flag),
        .error_flag(adc_sink_i_error_flag),
        .s00_tdata(usp_rf_data_converter_0_i_m00_axis_TDATA),
        .s00_tready(usp_rf_data_converter_0_i_m00_axis_TREADY),
        .s00_tvalid(usp_rf_data_converter_0_i_m00_axis_TVALID),
        .s0_axis_clock(clk_wiz_clk_out3),
        .s_axi_aclk(zynq_ultra_ps_e_0_pl_clk0),
        .s_axi_araddr(axi_interconnect_0_M02_AXI_ARADDR[17:0]),
        .s_axi_aresetn(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .s_axi_arready(axi_interconnect_0_M02_AXI_ARREADY),
        .s_axi_arvalid(axi_interconnect_0_M02_AXI_ARVALID),
        .s_axi_awaddr(axi_interconnect_0_M02_AXI_AWADDR[17:0]),
        .s_axi_awready(axi_interconnect_0_M02_AXI_AWREADY),
        .s_axi_awvalid(axi_interconnect_0_M02_AXI_AWVALID),
        .s_axi_bready(axi_interconnect_0_M02_AXI_BREADY),
        .s_axi_bresp(axi_interconnect_0_M02_AXI_BRESP),
        .s_axi_bvalid(axi_interconnect_0_M02_AXI_BVALID),
        .s_axi_rdata(axi_interconnect_0_M02_AXI_RDATA),
        .s_axi_rready(axi_interconnect_0_M02_AXI_RREADY),
        .s_axi_rresp(axi_interconnect_0_M02_AXI_RRESP),
        .s_axi_rvalid(axi_interconnect_0_M02_AXI_RVALID),
        .s_axi_wdata(axi_interconnect_0_M02_AXI_WDATA),
        .s_axi_wready(axi_interconnect_0_M02_AXI_WREADY),
        .s_axi_wstrb(axi_interconnect_0_M02_AXI_WSTRB),
        .s_axi_wvalid(axi_interconnect_0_M02_AXI_WVALID));
  design_1_axi_gpio_0 axi_gpio
       (.gpio_io_o(axi_gpio_GPIO_TRI_O),
        .s_axi_aclk(clk_wiz_clk_out3),
        .s_axi_araddr(zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARADDR),
        .s_axi_aresetn(rst_clk_wiz_100M_peripheral_aresetn),
        .s_axi_arready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARREADY),
        .s_axi_arvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARVALID),
        .s_axi_awaddr(zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWADDR),
        .s_axi_awready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWREADY),
        .s_axi_awvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWVALID),
        .s_axi_bready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_BREADY),
        .s_axi_bresp(zynq_ultra_ps_e_0_axi_periph_M06_AXI_BRESP),
        .s_axi_bvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_BVALID),
        .s_axi_rdata(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RDATA),
        .s_axi_rready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RREADY),
        .s_axi_rresp(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RRESP),
        .s_axi_rvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RVALID),
        .s_axi_wdata(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WDATA),
        .s_axi_wready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WREADY),
        .s_axi_wstrb(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WSTRB),
        .s_axi_wvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WVALID));
  design_1_axi_intc_0 axi_intc
       (.intr(concat_int_dout),
        .irq(axi_intc_irq),
        .s_axi_aclk(clk_wiz_clk_out3),
        .s_axi_araddr(zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARADDR),
        .s_axi_aresetn(rst_clk_wiz_100M_peripheral_aresetn),
        .s_axi_arready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARREADY),
        .s_axi_arvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARVALID),
        .s_axi_awaddr(zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWADDR),
        .s_axi_awready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWREADY),
        .s_axi_awvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWVALID),
        .s_axi_bready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_BREADY),
        .s_axi_bresp(zynq_ultra_ps_e_0_axi_periph_M10_AXI_BRESP),
        .s_axi_bvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_BVALID),
        .s_axi_rdata(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RDATA),
        .s_axi_rready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RREADY),
        .s_axi_rresp(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RRESP),
        .s_axi_rvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RVALID),
        .s_axi_wdata(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WDATA),
        .s_axi_wready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WREADY),
        .s_axi_wstrb(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WSTRB),
        .s_axi_wvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WVALID));
  design_1_axi_interconnect_0_0 axi_interconnect_0
       (.ACLK(zynq_ultra_ps_e_0_pl_clk0),
        .ARESETN(ARESETN_1),
        .M00_ACLK(zynq_ultra_ps_e_0_pl_clk0),
        .M00_ARESETN(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .M00_AXI_araddr(axi_interconnect_0_M00_AXI_ARADDR),
        .M00_AXI_arready(axi_interconnect_0_M00_AXI_ARREADY),
        .M00_AXI_arvalid(axi_interconnect_0_M00_AXI_ARVALID),
        .M00_AXI_awaddr(axi_interconnect_0_M00_AXI_AWADDR),
        .M00_AXI_awready(axi_interconnect_0_M00_AXI_AWREADY),
        .M00_AXI_awvalid(axi_interconnect_0_M00_AXI_AWVALID),
        .M00_AXI_bready(axi_interconnect_0_M00_AXI_BREADY),
        .M00_AXI_bresp(axi_interconnect_0_M00_AXI_BRESP),
        .M00_AXI_bvalid(axi_interconnect_0_M00_AXI_BVALID),
        .M00_AXI_rdata(axi_interconnect_0_M00_AXI_RDATA),
        .M00_AXI_rready(axi_interconnect_0_M00_AXI_RREADY),
        .M00_AXI_rresp(axi_interconnect_0_M00_AXI_RRESP),
        .M00_AXI_rvalid(axi_interconnect_0_M00_AXI_RVALID),
        .M00_AXI_wdata(axi_interconnect_0_M00_AXI_WDATA),
        .M00_AXI_wready(axi_interconnect_0_M00_AXI_WREADY),
        .M00_AXI_wstrb(axi_interconnect_0_M00_AXI_WSTRB),
        .M00_AXI_wvalid(axi_interconnect_0_M00_AXI_WVALID),
        .M01_ACLK(zynq_ultra_ps_e_0_pl_clk0),
        .M01_ARESETN(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .M01_AXI_araddr(axi_interconnect_0_M01_AXI_ARADDR),
        .M01_AXI_arready(axi_interconnect_0_M01_AXI_ARREADY),
        .M01_AXI_arvalid(axi_interconnect_0_M01_AXI_ARVALID),
        .M01_AXI_awaddr(axi_interconnect_0_M01_AXI_AWADDR),
        .M01_AXI_awready(axi_interconnect_0_M01_AXI_AWREADY),
        .M01_AXI_awvalid(axi_interconnect_0_M01_AXI_AWVALID),
        .M01_AXI_bready(axi_interconnect_0_M01_AXI_BREADY),
        .M01_AXI_bresp(axi_interconnect_0_M01_AXI_BRESP),
        .M01_AXI_bvalid(axi_interconnect_0_M01_AXI_BVALID),
        .M01_AXI_rdata(axi_interconnect_0_M01_AXI_RDATA),
        .M01_AXI_rready(axi_interconnect_0_M01_AXI_RREADY),
        .M01_AXI_rresp(axi_interconnect_0_M01_AXI_RRESP),
        .M01_AXI_rvalid(axi_interconnect_0_M01_AXI_RVALID),
        .M01_AXI_wdata(axi_interconnect_0_M01_AXI_WDATA),
        .M01_AXI_wready(axi_interconnect_0_M01_AXI_WREADY),
        .M01_AXI_wstrb(axi_interconnect_0_M01_AXI_WSTRB),
        .M01_AXI_wvalid(axi_interconnect_0_M01_AXI_WVALID),
        .M02_ACLK(zynq_ultra_ps_e_0_pl_clk0),
        .M02_ARESETN(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .M02_AXI_araddr(axi_interconnect_0_M02_AXI_ARADDR),
        .M02_AXI_arready(axi_interconnect_0_M02_AXI_ARREADY),
        .M02_AXI_arvalid(axi_interconnect_0_M02_AXI_ARVALID),
        .M02_AXI_awaddr(axi_interconnect_0_M02_AXI_AWADDR),
        .M02_AXI_awready(axi_interconnect_0_M02_AXI_AWREADY),
        .M02_AXI_awvalid(axi_interconnect_0_M02_AXI_AWVALID),
        .M02_AXI_bready(axi_interconnect_0_M02_AXI_BREADY),
        .M02_AXI_bresp(axi_interconnect_0_M02_AXI_BRESP),
        .M02_AXI_bvalid(axi_interconnect_0_M02_AXI_BVALID),
        .M02_AXI_rdata(axi_interconnect_0_M02_AXI_RDATA),
        .M02_AXI_rready(axi_interconnect_0_M02_AXI_RREADY),
        .M02_AXI_rresp(axi_interconnect_0_M02_AXI_RRESP),
        .M02_AXI_rvalid(axi_interconnect_0_M02_AXI_RVALID),
        .M02_AXI_wdata(axi_interconnect_0_M02_AXI_WDATA),
        .M02_AXI_wready(axi_interconnect_0_M02_AXI_WREADY),
        .M02_AXI_wstrb(axi_interconnect_0_M02_AXI_WSTRB),
        .M02_AXI_wvalid(axi_interconnect_0_M02_AXI_WVALID),
        .S00_ACLK(zynq_ultra_ps_e_0_pl_clk0),
        .S00_ARESETN(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .S00_AXI_araddr(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARADDR),
        .S00_AXI_arburst(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARBURST),
        .S00_AXI_arcache(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARCACHE),
        .S00_AXI_arid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARID),
        .S00_AXI_arlen(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARLEN),
        .S00_AXI_arlock(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARLOCK),
        .S00_AXI_arprot(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARPROT),
        .S00_AXI_arqos(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARQOS),
        .S00_AXI_arready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARREADY),
        .S00_AXI_arsize(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARSIZE),
        .S00_AXI_arvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARVALID),
        .S00_AXI_awaddr(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWADDR),
        .S00_AXI_awburst(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWBURST),
        .S00_AXI_awcache(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWCACHE),
        .S00_AXI_awid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWID),
        .S00_AXI_awlen(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWLEN),
        .S00_AXI_awlock(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWLOCK),
        .S00_AXI_awprot(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWPROT),
        .S00_AXI_awqos(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWQOS),
        .S00_AXI_awready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWREADY),
        .S00_AXI_awsize(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWSIZE),
        .S00_AXI_awvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWVALID),
        .S00_AXI_bid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BID),
        .S00_AXI_bready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BREADY),
        .S00_AXI_bresp(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BRESP),
        .S00_AXI_bvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BVALID),
        .S00_AXI_rdata(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RDATA),
        .S00_AXI_rid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RID),
        .S00_AXI_rlast(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RLAST),
        .S00_AXI_rready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RREADY),
        .S00_AXI_rresp(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RRESP),
        .S00_AXI_rvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RVALID),
        .S00_AXI_wdata(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WDATA),
        .S00_AXI_wlast(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WLAST),
        .S00_AXI_wready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WREADY),
        .S00_AXI_wstrb(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WSTRB),
        .S00_AXI_wvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WVALID));
  design_1_chan_ctrl_fifo_0 chan_ctrl_fifo
       (.m_axis_tdata(chan_ctrl_fifo_M_AXIS_TDATA),
        .m_axis_tready(chan_ctrl_fifo_M_AXIS_TREADY),
        .m_axis_tvalid(chan_ctrl_fifo_M_AXIS_TVALID),
        .s_axis_aclk(clk_wiz_clk_out2),
        .s_axis_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .s_axis_tdata(chan_ctrl_reg_M_AXIS_TDATA),
        .s_axis_tready(chan_ctrl_reg_M_AXIS_TREADY),
        .s_axis_tvalid(chan_ctrl_reg_M_AXIS_TVALID));
  design_1_chan_ctrl_reg_0 chan_ctrl_reg
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(chan_ctrl_reg_M_AXIS_TDATA),
        .m_axis_tready(chan_ctrl_reg_M_AXIS_TREADY),
        .m_axis_tvalid(chan_ctrl_reg_M_AXIS_TVALID),
        .s_axis_tdata(data_source_chan_ctrl_out_V_TDATA),
        .s_axis_tready(data_source_chan_ctrl_out_V_TREADY),
        .s_axis_tvalid(data_source_chan_ctrl_out_V_TVALID));
  design_1_clk_wiz_0 clk_wiz
       (.clk_in1_n(diff_clock_rtl_0_1_CLK_N),
        .clk_in1_p(diff_clock_rtl_0_1_CLK_P),
        .clk_out1(clk_wiz_clk_out1),
        .clk_out2(clk_wiz_clk_out2),
        .clk_out3(clk_wiz_clk_out3),
        .locked(clk_wiz_locked),
        .reset(reset_rtl_0_1));
  design_1_concat_int_0 concat_int
       (.In0(sd_fec_enc_interrupt),
        .In1(sd_fec_dec_interrupt),
        .dout(concat_int_dout));
  design_1_const_1_0 const_1
       (.dout(const_1_dout));
  design_1_dac_source_i_0 dac_source_i
       (.m00_tdata(dac_source_i_m00_TDATA),
        .m00_tready(dac_source_i_m00_TREADY),
        .m00_tvalid(dac_source_i_m00_TVALID),
        .m0_axis_clock(clk_wiz_clk_out3),
        .s_axi_aclk(zynq_ultra_ps_e_0_pl_clk0),
        .s_axi_araddr(axi_interconnect_0_M01_AXI_ARADDR[17:0]),
        .s_axi_aresetn(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .s_axi_arready(axi_interconnect_0_M01_AXI_ARREADY),
        .s_axi_arvalid(axi_interconnect_0_M01_AXI_ARVALID),
        .s_axi_awaddr(axi_interconnect_0_M01_AXI_AWADDR[17:0]),
        .s_axi_awready(axi_interconnect_0_M01_AXI_AWREADY),
        .s_axi_awvalid(axi_interconnect_0_M01_AXI_AWVALID),
        .s_axi_bready(axi_interconnect_0_M01_AXI_BREADY),
        .s_axi_bresp(axi_interconnect_0_M01_AXI_BRESP),
        .s_axi_bvalid(axi_interconnect_0_M01_AXI_BVALID),
        .s_axi_rdata(axi_interconnect_0_M01_AXI_RDATA),
        .s_axi_rready(axi_interconnect_0_M01_AXI_RREADY),
        .s_axi_rresp(axi_interconnect_0_M01_AXI_RRESP),
        .s_axi_rvalid(axi_interconnect_0_M01_AXI_RVALID),
        .s_axi_wdata(axi_interconnect_0_M01_AXI_WDATA),
        .s_axi_wready(axi_interconnect_0_M01_AXI_WREADY),
        .s_axi_wstrb(axi_interconnect_0_M01_AXI_WSTRB),
        .s_axi_wvalid(axi_interconnect_0_M01_AXI_WVALID));
  design_1_data_source_0 data_source
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ap_rst_n_cntrl_aclk(rst_clk_wiz_100M_peripheral_aresetn),
        .chan_ctrl_out_V_TDATA(data_source_chan_ctrl_out_V_TDATA),
        .chan_ctrl_out_V_TREADY(data_source_chan_ctrl_out_V_TREADY),
        .chan_ctrl_out_V_TVALID(data_source_chan_ctrl_out_V_TVALID),
        .cntrl_aclk(clk_wiz_clk_out3),
        .dec_ctrl_out_TDATA(data_source_dec_ctrl_out_TDATA),
        .dec_ctrl_out_TLAST(data_source_dec_ctrl_out_TLAST),
        .dec_ctrl_out_TREADY(data_source_dec_ctrl_out_TREADY),
        .dec_ctrl_out_TVALID(data_source_dec_ctrl_out_TVALID),
        .dec_keep_ctrl_V_V_TDATA(data_source_dec_keep_ctrl_V_V_TDATA),
        .dec_keep_ctrl_V_V_TREADY(data_source_dec_keep_ctrl_V_V_TREADY),
        .dec_keep_ctrl_V_V_TVALID(data_source_dec_keep_ctrl_V_V_TVALID),
        .enc_ctrl_out_TDATA(data_source_enc_ctrl_out_TDATA),
        .enc_ctrl_out_TLAST(data_source_enc_ctrl_out_TLAST),
        .enc_ctrl_out_TREADY(data_source_enc_ctrl_out_TREADY),
        .enc_ctrl_out_TVALID(data_source_enc_ctrl_out_TVALID),
        .enc_keep_ctrl_V_V_TDATA(data_source_enc_keep_ctrl_V_V_TDATA),
        .enc_keep_ctrl_V_V_TREADY(data_source_enc_keep_ctrl_V_V_TREADY),
        .enc_keep_ctrl_V_V_TVALID(data_source_enc_keep_ctrl_V_V_TVALID),
        .hard_data_out_TDATA(data_source_hard_data_out_TDATA),
        .hard_data_out_TKEEP(data_source_hard_data_out_TKEEP),
        .hard_data_out_TLAST(data_source_hard_data_out_TLAST),
        .hard_data_out_TREADY(data_source_hard_data_out_TREADY),
        .hard_data_out_TVALID(data_source_hard_data_out_TVALID),
        .s_axi_CNTRL_ARADDR(zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARADDR),
        .s_axi_CNTRL_ARREADY(zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARREADY),
        .s_axi_CNTRL_ARVALID(zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARVALID),
        .s_axi_CNTRL_AWADDR(zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWADDR),
        .s_axi_CNTRL_AWREADY(zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWREADY),
        .s_axi_CNTRL_AWVALID(zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWVALID),
        .s_axi_CNTRL_BREADY(zynq_ultra_ps_e_0_axi_periph_M00_AXI_BREADY),
        .s_axi_CNTRL_BRESP(zynq_ultra_ps_e_0_axi_periph_M00_AXI_BRESP),
        .s_axi_CNTRL_BVALID(zynq_ultra_ps_e_0_axi_periph_M00_AXI_BVALID),
        .s_axi_CNTRL_RDATA(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RDATA),
        .s_axi_CNTRL_RREADY(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RREADY),
        .s_axi_CNTRL_RRESP(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RRESP),
        .s_axi_CNTRL_RVALID(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RVALID),
        .s_axi_CNTRL_WDATA(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WDATA),
        .s_axi_CNTRL_WREADY(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WREADY),
        .s_axi_CNTRL_WSTRB(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WSTRB),
        .s_axi_CNTRL_WVALID(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WVALID));
  design_1_dec_add_keep_0 dec_add_keep
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ctrl_V_V_TDATA(dec_keep_ctrl_fifo_M_AXIS_TDATA),
        .ctrl_V_V_TREADY(dec_keep_ctrl_fifo_M_AXIS_TREADY),
        .ctrl_V_V_TVALID(dec_keep_ctrl_fifo_M_AXIS_TVALID),
        .din_TDATA(sd_fec_dec_M_AXIS_DOUT_TDATA),
        .din_TLAST(sd_fec_dec_M_AXIS_DOUT_TLAST),
        .din_TREADY(sd_fec_dec_M_AXIS_DOUT_TREADY),
        .din_TVALID(sd_fec_dec_M_AXIS_DOUT_TVALID),
        .dout_TDATA(dec_add_keep_dout_TDATA),
        .dout_TKEEP(dec_add_keep_dout_TKEEP),
        .dout_TLAST(dec_add_keep_dout_TLAST),
        .dout_TREADY(dec_add_keep_dout_TREADY),
        .dout_TVALID(dec_add_keep_dout_TVALID));
  design_1_dec_add_keep_trim_0 dec_add_keep_trim
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(dec_add_keep_trim_M_AXIS_TDATA),
        .m_axis_tready(dec_add_keep_trim_M_AXIS_TREADY),
        .m_axis_tvalid(dec_add_keep_trim_M_AXIS_TVALID),
        .s_axis_tdata(data_source_dec_keep_ctrl_V_V_TDATA),
        .s_axis_tready(data_source_dec_keep_ctrl_V_V_TREADY),
        .s_axis_tvalid(data_source_dec_keep_ctrl_V_V_TVALID));
  design_1_dec_ctrl_fifo_0 dec_ctrl_fifo
       (.m_axis_tdata(dec_ctrl_fifo_M_AXIS_TDATA),
        .m_axis_tready(dec_ctrl_fifo_M_AXIS_TREADY),
        .m_axis_tvalid(dec_ctrl_fifo_M_AXIS_TVALID),
        .s_axis_aclk(clk_wiz_clk_out2),
        .s_axis_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .s_axis_tdata(dec_ctrl_reg_M_AXIS_TDATA),
        .s_axis_tlast(dec_ctrl_reg_M_AXIS_TLAST),
        .s_axis_tready(dec_ctrl_reg_M_AXIS_TREADY),
        .s_axis_tvalid(dec_ctrl_reg_M_AXIS_TVALID));
  design_1_dec_ctrl_reg_0 dec_ctrl_reg
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(dec_ctrl_reg_M_AXIS_TDATA),
        .m_axis_tlast(dec_ctrl_reg_M_AXIS_TLAST),
        .m_axis_tready(dec_ctrl_reg_M_AXIS_TREADY),
        .m_axis_tvalid(dec_ctrl_reg_M_AXIS_TVALID),
        .s_axis_tdata(dec_ctrl_reinterpret_M_AXIS_TDATA),
        .s_axis_tlast(dec_ctrl_reinterpret_M_AXIS_TLAST),
        .s_axis_tready(dec_ctrl_reinterpret_M_AXIS_TREADY),
        .s_axis_tvalid(dec_ctrl_reinterpret_M_AXIS_TVALID));
  design_1_dec_ctrl_reinterpret_0 dec_ctrl_reinterpret
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(dec_ctrl_reinterpret_M_AXIS_TDATA),
        .m_axis_tlast(dec_ctrl_reinterpret_M_AXIS_TLAST),
        .m_axis_tready(dec_ctrl_reinterpret_M_AXIS_TREADY),
        .m_axis_tvalid(dec_ctrl_reinterpret_M_AXIS_TVALID),
        .s_axis_tdata(data_source_dec_ctrl_out_TDATA),
        .s_axis_tlast(data_source_dec_ctrl_out_TLAST),
        .s_axis_tready(data_source_dec_ctrl_out_TREADY),
        .s_axis_tvalid(data_source_dec_ctrl_out_TVALID));
  design_1_dec_data_reinterpret_0 dec_data_reinterpret
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(dec_data_reinterpret_M_AXIS_TDATA),
        .m_axis_tlast(dec_data_reinterpret_M_AXIS_TLAST),
        .m_axis_tready(dec_data_reinterpret_M_AXIS_TREADY),
        .m_axis_tvalid(dec_data_reinterpret_M_AXIS_TVALID),
        .s_axis_tdata(dec_add_keep_dout_TDATA),
        .s_axis_tkeep(dec_add_keep_dout_TKEEP),
        .s_axis_tlast(dec_add_keep_dout_TLAST),
        .s_axis_tready(dec_add_keep_dout_TREADY),
        .s_axis_tvalid(dec_add_keep_dout_TVALID));
  design_1_dec_ip_mon_0 dec_ip_mon
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ap_rst_n_cntrl_aclk(rst_clk_wiz_100M_peripheral_aresetn),
        .cntrl_aclk(clk_wiz_clk_out3),
        .rtc_V(rtc_Q),
        .s_axi_CNTRL_ARADDR(zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARADDR),
        .s_axi_CNTRL_ARREADY(zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARREADY),
        .s_axi_CNTRL_ARVALID(zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARVALID),
        .s_axi_CNTRL_AWADDR(zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWADDR),
        .s_axi_CNTRL_AWREADY(zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWREADY),
        .s_axi_CNTRL_AWVALID(zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWVALID),
        .s_axi_CNTRL_BREADY(zynq_ultra_ps_e_0_axi_periph_M07_AXI_BREADY),
        .s_axi_CNTRL_BRESP(zynq_ultra_ps_e_0_axi_periph_M07_AXI_BRESP),
        .s_axi_CNTRL_BVALID(zynq_ultra_ps_e_0_axi_periph_M07_AXI_BVALID),
        .s_axi_CNTRL_RDATA(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RDATA),
        .s_axi_CNTRL_RREADY(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RREADY),
        .s_axi_CNTRL_RRESP(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RRESP),
        .s_axi_CNTRL_RVALID(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RVALID),
        .s_axi_CNTRL_WDATA(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WDATA),
        .s_axi_CNTRL_WREADY(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WREADY),
        .s_axi_CNTRL_WSTRB(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WSTRB),
        .s_axi_CNTRL_WVALID(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WVALID),
        .tlast_V(dec_ip_probe_last_op),
        .tready_V(dec_ip_probe_ready_op),
        .tvalid_V(dec_ip_probe_valid_op));
  design_1_dec_ip_probe_0 dec_ip_probe
       (.clk(clk_wiz_clk_out2),
        .last_op(dec_ip_probe_last_op),
        .mon_tlast(llr_reinterpret_M_AXIS_TLAST),
        .mon_tready(llr_reinterpret_M_AXIS_TREADY),
        .mon_tvalid(llr_reinterpret_M_AXIS_TVALID),
        .ready_op(dec_ip_probe_ready_op),
        .valid_op(dec_ip_probe_valid_op));
  design_1_dec_keep_ctrl_fifo_0 dec_keep_ctrl_fifo
       (.m_axis_tdata(dec_keep_ctrl_fifo_M_AXIS_TDATA),
        .m_axis_tready(dec_keep_ctrl_fifo_M_AXIS_TREADY),
        .m_axis_tvalid(dec_keep_ctrl_fifo_M_AXIS_TVALID),
        .s_axis_aclk(clk_wiz_clk_out2),
        .s_axis_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .s_axis_tdata(dec_add_keep_trim_M_AXIS_TDATA),
        .s_axis_tready(dec_add_keep_trim_M_AXIS_TREADY),
        .s_axis_tvalid(dec_add_keep_trim_M_AXIS_TVALID));
  design_1_dec_op_mon_0 dec_op_mon
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ap_rst_n_cntrl_aclk(rst_clk_wiz_100M_peripheral_aresetn),
        .cntrl_aclk(clk_wiz_clk_out3),
        .rtc_V(rtc_Q),
        .s_axi_CNTRL_ARADDR(zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARADDR),
        .s_axi_CNTRL_ARREADY(zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARREADY),
        .s_axi_CNTRL_ARVALID(zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARVALID),
        .s_axi_CNTRL_AWADDR(zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWADDR),
        .s_axi_CNTRL_AWREADY(zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWREADY),
        .s_axi_CNTRL_AWVALID(zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWVALID),
        .s_axi_CNTRL_BREADY(zynq_ultra_ps_e_0_axi_periph_M08_AXI_BREADY),
        .s_axi_CNTRL_BRESP(zynq_ultra_ps_e_0_axi_periph_M08_AXI_BRESP),
        .s_axi_CNTRL_BVALID(zynq_ultra_ps_e_0_axi_periph_M08_AXI_BVALID),
        .s_axi_CNTRL_RDATA(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RDATA),
        .s_axi_CNTRL_RREADY(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RREADY),
        .s_axi_CNTRL_RRESP(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RRESP),
        .s_axi_CNTRL_RVALID(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RVALID),
        .s_axi_CNTRL_WDATA(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WDATA),
        .s_axi_CNTRL_WREADY(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WREADY),
        .s_axi_CNTRL_WSTRB(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WSTRB),
        .s_axi_CNTRL_WVALID(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WVALID),
        .tlast_V(dec_op_probe_last_op),
        .tready_V(dec_op_probe_ready_op),
        .tvalid_V(dec_op_probe_valid_op));
  design_1_dec_op_probe_0 dec_op_probe
       (.clk(clk_wiz_clk_out2),
        .last_op(dec_op_probe_last_op),
        .mon_tlast(sd_fec_dec_M_AXIS_DOUT_TLAST),
        .mon_tready(sd_fec_dec_M_AXIS_DOUT_TREADY),
        .mon_tvalid(sd_fec_dec_M_AXIS_DOUT_TVALID),
        .ready_op(dec_op_probe_ready_op),
        .valid_op(dec_op_probe_valid_op));
  design_1_dec_stat_reinterpret_0 dec_stat_reinterpret
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(dec_stat_reinterpret_M_AXIS_TDATA),
        .m_axis_tready(dec_stat_reinterpret_M_AXIS_TREADY),
        .m_axis_tvalid(dec_stat_reinterpret_M_AXIS_TVALID),
        .s_axis_tdata(sd_fec_dec_M_AXIS_STATUS_TDATA),
        .s_axis_tready(sd_fec_dec_M_AXIS_STATUS_TREADY),
        .s_axis_tvalid(sd_fec_dec_M_AXIS_STATUS_TVALID));
  design_1_demod_0 demod
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .chan_data_1_V_TDATA(mod_and_chan_chan_data_1_V_TDATA),
        .chan_data_1_V_TREADY(mod_and_chan_chan_data_1_V_TREADY),
        .chan_data_1_V_TVALID(mod_and_chan_chan_data_1_V_TVALID),
        .chan_data_2_V_TDATA(mod_and_chan_chan_data_2_V_TDATA),
        .chan_data_2_V_TREADY(mod_and_chan_chan_data_2_V_TREADY),
        .chan_data_2_V_TVALID(mod_and_chan_chan_data_2_V_TVALID),
        .chan_data_3_V_TDATA(mod_and_chan_chan_data_3_V_TDATA),
        .chan_data_3_V_TREADY(mod_and_chan_chan_data_3_V_TREADY),
        .chan_data_3_V_TVALID(mod_and_chan_chan_data_3_V_TVALID),
        .chan_data_4_V_TDATA(mod_and_chan_chan_data_4_V_TDATA),
        .chan_data_4_V_TREADY(mod_and_chan_chan_data_4_V_TREADY),
        .chan_data_4_V_TVALID(mod_and_chan_chan_data_4_V_TVALID),
        .ctrl_in_V_TDATA(mod_and_chan_ctrl_out_V_TDATA),
        .ctrl_in_V_TREADY(mod_and_chan_ctrl_out_V_TREADY),
        .ctrl_in_V_TVALID(mod_and_chan_ctrl_out_V_TVALID),
        .hard_data_TDATA(demod_hard_data_TDATA),
        .hard_data_TLAST(demod_hard_data_TLAST),
        .hard_data_TREADY(demod_hard_data_TREADY),
        .hard_data_TVALID(demod_hard_data_TVALID),
        .soft_data_TDATA(demod_soft_data_TDATA),
        .soft_data_TKEEP(demod_soft_data_TKEEP),
        .soft_data_TLAST(demod_soft_data_TLAST),
        .soft_data_TREADY(demod_soft_data_TREADY),
        .soft_data_TVALID(demod_soft_data_TVALID));
  design_1_enc_add_keep_0 enc_add_keep
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ctrl_V_V_TDATA(enc_keep_ctrl_fifo_M_AXIS_TDATA),
        .ctrl_V_V_TREADY(enc_keep_ctrl_fifo_M_AXIS_TREADY),
        .ctrl_V_V_TVALID(enc_keep_ctrl_fifo_M_AXIS_TVALID),
        .din_TDATA(sd_fec_enc_M_AXIS_DOUT_TDATA),
        .din_TLAST(sd_fec_enc_M_AXIS_DOUT_TLAST),
        .din_TREADY(sd_fec_enc_M_AXIS_DOUT_TREADY),
        .din_TVALID(sd_fec_enc_M_AXIS_DOUT_TVALID),
        .dout_TDATA(enc_add_keep_dout_TDATA),
        .dout_TKEEP(enc_add_keep_dout_TKEEP),
        .dout_TLAST(enc_add_keep_dout_TLAST),
        .dout_TREADY(enc_add_keep_dout_TREADY),
        .dout_TVALID(enc_add_keep_dout_TVALID));
  design_1_enc_add_keep_trim_0 enc_add_keep_trim
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(enc_add_keep_trim_M_AXIS_TDATA),
        .m_axis_tready(enc_add_keep_trim_M_AXIS_TREADY),
        .m_axis_tvalid(enc_add_keep_trim_M_AXIS_TVALID),
        .s_axis_tdata(data_source_enc_keep_ctrl_V_V_TDATA),
        .s_axis_tready(data_source_enc_keep_ctrl_V_V_TREADY),
        .s_axis_tvalid(data_source_enc_keep_ctrl_V_V_TVALID));
  design_1_enc_ctrl_reinterpret_0 enc_ctrl_reinterpret
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(enc_ctrl_reinterpret_M_AXIS_TDATA),
        .m_axis_tready(enc_ctrl_reinterpret_M_AXIS_TREADY),
        .m_axis_tvalid(enc_ctrl_reinterpret_M_AXIS_TVALID),
        .s_axis_tdata(data_source_enc_ctrl_out_TDATA),
        .s_axis_tlast(data_source_enc_ctrl_out_TLAST),
        .s_axis_tready(data_source_enc_ctrl_out_TREADY),
        .s_axis_tvalid(data_source_enc_ctrl_out_TVALID));
  design_1_enc_data_fifo_0 enc_data_fifo
       (.m_axis_tdata(enc_data_fifo_M_AXIS_TDATA),
        .m_axis_tready(enc_data_fifo_M_AXIS_TREADY),
        .m_axis_tvalid(enc_data_fifo_M_AXIS_TVALID),
        .s_axis_aclk(clk_wiz_clk_out2),
        .s_axis_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .s_axis_tdata(enc_data_reinterpret_M_AXIS_TDATA),
        .s_axis_tkeep(enc_data_reinterpret_M_AXIS_TKEEP),
        .s_axis_tlast(enc_data_reinterpret_M_AXIS_TLAST),
        .s_axis_tready(enc_data_reinterpret_M_AXIS_TREADY),
        .s_axis_tvalid(enc_data_reinterpret_M_AXIS_TVALID));
  design_1_enc_data_reinterpret_0 enc_data_reinterpret
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(enc_data_reinterpret_M_AXIS_TDATA),
        .m_axis_tkeep(enc_data_reinterpret_M_AXIS_TKEEP),
        .m_axis_tlast(enc_data_reinterpret_M_AXIS_TLAST),
        .m_axis_tready(enc_data_reinterpret_M_AXIS_TREADY),
        .m_axis_tvalid(enc_data_reinterpret_M_AXIS_TVALID),
        .s_axis_tdata(enc_add_keep_dout_TDATA),
        .s_axis_tkeep(enc_add_keep_dout_TKEEP),
        .s_axis_tlast(enc_add_keep_dout_TLAST),
        .s_axis_tready(enc_add_keep_dout_TREADY),
        .s_axis_tvalid(enc_add_keep_dout_TVALID));
  design_1_enc_ip_mon_0 enc_ip_mon
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ap_rst_n_cntrl_aclk(rst_clk_wiz_100M_peripheral_aresetn),
        .cntrl_aclk(clk_wiz_clk_out3),
        .rtc_V(rtc_Q),
        .s_axi_CNTRL_ARADDR(zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARADDR),
        .s_axi_CNTRL_ARREADY(zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARREADY),
        .s_axi_CNTRL_ARVALID(zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARVALID),
        .s_axi_CNTRL_AWADDR(zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWADDR),
        .s_axi_CNTRL_AWREADY(zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWREADY),
        .s_axi_CNTRL_AWVALID(zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWVALID),
        .s_axi_CNTRL_BREADY(zynq_ultra_ps_e_0_axi_periph_M02_AXI_BREADY),
        .s_axi_CNTRL_BRESP(zynq_ultra_ps_e_0_axi_periph_M02_AXI_BRESP),
        .s_axi_CNTRL_BVALID(zynq_ultra_ps_e_0_axi_periph_M02_AXI_BVALID),
        .s_axi_CNTRL_RDATA(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RDATA),
        .s_axi_CNTRL_RREADY(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RREADY),
        .s_axi_CNTRL_RRESP(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RRESP),
        .s_axi_CNTRL_RVALID(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RVALID),
        .s_axi_CNTRL_WDATA(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WDATA),
        .s_axi_CNTRL_WREADY(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WREADY),
        .s_axi_CNTRL_WSTRB(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WSTRB),
        .s_axi_CNTRL_WVALID(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WVALID),
        .tlast_V(enc_ip_probe_last_op),
        .tready_V(enc_ip_probe_ready_op),
        .tvalid_V(enc_ip_probe_valid_op));
  design_1_enc_ip_probe_0 enc_ip_probe
       (.clk(clk_wiz_clk_out2),
        .last_op(enc_ip_probe_last_op),
        .mon_tlast(src_data_broadcast_M00_AXIS_TLAST),
        .mon_tready(src_data_broadcast_M00_AXIS_TREADY),
        .mon_tvalid(src_data_broadcast_M00_AXIS_TVALID),
        .ready_op(enc_ip_probe_ready_op),
        .valid_op(enc_ip_probe_valid_op));
  design_1_enc_keep_ctrl_fifo_0 enc_keep_ctrl_fifo
       (.m_axis_tdata(enc_keep_ctrl_fifo_M_AXIS_TDATA),
        .m_axis_tready(enc_keep_ctrl_fifo_M_AXIS_TREADY),
        .m_axis_tvalid(enc_keep_ctrl_fifo_M_AXIS_TVALID),
        .s_axis_aclk(clk_wiz_clk_out2),
        .s_axis_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .s_axis_tdata(enc_add_keep_trim_M_AXIS_TDATA),
        .s_axis_tready(enc_add_keep_trim_M_AXIS_TREADY),
        .s_axis_tvalid(enc_add_keep_trim_M_AXIS_TVALID));
  design_1_enc_op_mon_0 enc_op_mon
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ap_rst_n_cntrl_aclk(rst_clk_wiz_100M_peripheral_aresetn),
        .cntrl_aclk(clk_wiz_clk_out3),
        .rtc_V(rtc_Q),
        .s_axi_CNTRL_ARADDR(zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARADDR),
        .s_axi_CNTRL_ARREADY(zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARREADY),
        .s_axi_CNTRL_ARVALID(zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARVALID),
        .s_axi_CNTRL_AWADDR(zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWADDR),
        .s_axi_CNTRL_AWREADY(zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWREADY),
        .s_axi_CNTRL_AWVALID(zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWVALID),
        .s_axi_CNTRL_BREADY(zynq_ultra_ps_e_0_axi_periph_M03_AXI_BREADY),
        .s_axi_CNTRL_BRESP(zynq_ultra_ps_e_0_axi_periph_M03_AXI_BRESP),
        .s_axi_CNTRL_BVALID(zynq_ultra_ps_e_0_axi_periph_M03_AXI_BVALID),
        .s_axi_CNTRL_RDATA(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RDATA),
        .s_axi_CNTRL_RREADY(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RREADY),
        .s_axi_CNTRL_RRESP(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RRESP),
        .s_axi_CNTRL_RVALID(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RVALID),
        .s_axi_CNTRL_WDATA(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WDATA),
        .s_axi_CNTRL_WREADY(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WREADY),
        .s_axi_CNTRL_WSTRB(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WSTRB),
        .s_axi_CNTRL_WVALID(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WVALID),
        .tlast_V(enc_op_probe_last_op),
        .tready_V(enc_op_probe_ready_op),
        .tvalid_V(enc_op_probe_valid_op));
  design_1_enc_op_probe_0 enc_op_probe
       (.clk(clk_wiz_clk_out2),
        .last_op(enc_op_probe_last_op),
        .mon_tlast(sd_fec_enc_M_AXIS_DOUT_TLAST),
        .mon_tready(sd_fec_enc_M_AXIS_DOUT_TREADY),
        .mon_tvalid(sd_fec_enc_M_AXIS_DOUT_TVALID),
        .ready_op(enc_op_probe_ready_op),
        .valid_op(enc_op_probe_valid_op));
  design_1_gpio_reset_0 gpio_reset
       (.gpio_io_o(gpio_reset_gpio_io_o),
        .s_axi_aclk(clk_wiz_clk_out3),
        .s_axi_araddr(zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARADDR),
        .s_axi_aresetn(rst_clk_wiz_100M_peripheral_aresetn),
        .s_axi_arready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARREADY),
        .s_axi_arvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARVALID),
        .s_axi_awaddr(zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWADDR),
        .s_axi_awready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWREADY),
        .s_axi_awvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWVALID),
        .s_axi_bready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_BREADY),
        .s_axi_bresp(zynq_ultra_ps_e_0_axi_periph_M09_AXI_BRESP),
        .s_axi_bvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_BVALID),
        .s_axi_rdata(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RDATA),
        .s_axi_rready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RREADY),
        .s_axi_rresp(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RRESP),
        .s_axi_rvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RVALID),
        .s_axi_wdata(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WDATA),
        .s_axi_wready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WREADY),
        .s_axi_wstrb(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WSTRB),
        .s_axi_wvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WVALID));
  design_1_hard_chan_data_fifo_0 hard_chan_data_fifo
       (.m_axis_tdata(hard_chan_data_fifo_M_AXIS_TDATA),
        .m_axis_tlast(hard_chan_data_fifo_M_AXIS_TLAST),
        .m_axis_tready(hard_chan_data_fifo_M_AXIS_TREADY),
        .m_axis_tvalid(hard_chan_data_fifo_M_AXIS_TVALID),
        .s_axis_aclk(clk_wiz_clk_out2),
        .s_axis_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .s_axis_tdata(demod_hard_data_TDATA),
        .s_axis_tlast(demod_hard_data_TLAST),
        .s_axis_tready(demod_hard_data_TREADY),
        .s_axis_tvalid(demod_hard_data_TVALID));
  design_1_hard_data_reg_0 hard_data_reg
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(hard_data_reg_M_AXIS_TDATA),
        .m_axis_tkeep(hard_data_reg_M_AXIS_TKEEP),
        .m_axis_tlast(hard_data_reg_M_AXIS_TLAST),
        .m_axis_tready(hard_data_reg_M_AXIS_TREADY),
        .m_axis_tvalid(hard_data_reg_M_AXIS_TVALID),
        .s_axis_tdata(data_source_hard_data_out_TDATA),
        .s_axis_tkeep(data_source_hard_data_out_TKEEP),
        .s_axis_tlast(data_source_hard_data_out_TLAST),
        .s_axis_tready(data_source_hard_data_out_TREADY),
        .s_axis_tvalid(data_source_hard_data_out_TVALID));
  design_1_llr_reinterpret_0 llr_reinterpret
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(llr_reinterpret_M_AXIS_TDATA),
        .m_axis_tlast(llr_reinterpret_M_AXIS_TLAST),
        .m_axis_tready(llr_reinterpret_M_AXIS_TREADY),
        .m_axis_tvalid(llr_reinterpret_M_AXIS_TVALID),
        .s_axis_tdata(llr_reshape_M_AXIS_TDATA),
        .s_axis_tkeep(llr_reshape_M_AXIS_TKEEP),
        .s_axis_tlast(llr_reshape_M_AXIS_TLAST),
        .s_axis_tready(llr_reshape_M_AXIS_TREADY),
        .s_axis_tvalid(llr_reshape_M_AXIS_TVALID));
  design_1_llr_reshape_0 llr_reshape
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata(llr_reshape_M_AXIS_TDATA),
        .m_axis_tkeep(llr_reshape_M_AXIS_TKEEP),
        .m_axis_tlast(llr_reshape_M_AXIS_TLAST),
        .m_axis_tready(llr_reshape_M_AXIS_TREADY),
        .m_axis_tvalid(llr_reshape_M_AXIS_TVALID),
        .s_axis_tdata(demod_soft_data_TDATA),
        .s_axis_tkeep(demod_soft_data_TKEEP),
        .s_axis_tlast(demod_soft_data_TLAST),
        .s_axis_tready(demod_soft_data_TREADY),
        .s_axis_tvalid(demod_soft_data_TVALID));
  design_1_mod_and_chan_0 mod_and_chan
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .chan_data_1_V_TDATA(mod_and_chan_chan_data_1_V_TDATA),
        .chan_data_1_V_TREADY(mod_and_chan_chan_data_1_V_TREADY),
        .chan_data_1_V_TVALID(mod_and_chan_chan_data_1_V_TVALID),
        .chan_data_2_V_TDATA(mod_and_chan_chan_data_2_V_TDATA),
        .chan_data_2_V_TREADY(mod_and_chan_chan_data_2_V_TREADY),
        .chan_data_2_V_TVALID(mod_and_chan_chan_data_2_V_TVALID),
        .chan_data_3_V_TDATA(mod_and_chan_chan_data_3_V_TDATA),
        .chan_data_3_V_TREADY(mod_and_chan_chan_data_3_V_TREADY),
        .chan_data_3_V_TVALID(mod_and_chan_chan_data_3_V_TVALID),
        .chan_data_4_V_TDATA(mod_and_chan_chan_data_4_V_TDATA),
        .chan_data_4_V_TREADY(mod_and_chan_chan_data_4_V_TREADY),
        .chan_data_4_V_TVALID(mod_and_chan_chan_data_4_V_TVALID),
        .ctrl_in_V_TDATA(chan_ctrl_fifo_M_AXIS_TDATA),
        .ctrl_in_V_TREADY(chan_ctrl_fifo_M_AXIS_TREADY),
        .ctrl_in_V_TVALID(chan_ctrl_fifo_M_AXIS_TVALID),
        .ctrl_out_V_TDATA(mod_and_chan_ctrl_out_V_TDATA),
        .ctrl_out_V_TREADY(mod_and_chan_ctrl_out_V_TREADY),
        .ctrl_out_V_TVALID(mod_and_chan_ctrl_out_V_TVALID),
        .hard_data_V_V_TDATA(enc_data_fifo_M_AXIS_TDATA),
        .hard_data_V_V_TREADY(enc_data_fifo_M_AXIS_TREADY),
        .hard_data_V_V_TVALID(enc_data_fifo_M_AXIS_TVALID));
  design_1_reset_slice_0 reset_slice
       (.Din(gpio_reset_gpio_io_o),
        .Dout(reset_slice_Dout));
  design_1_rst_clk_wiz_100M_0 rst_clk_wiz_100M
       (.aux_reset_in(1'b1),
        .dcm_locked(clk_wiz_locked),
        .ext_reset_in(reset_rtl_0_1),
        .interconnect_aresetn(rst_clk_wiz_100M_interconnect_aresetn),
        .mb_debug_sys_rst(1'b0),
        .peripheral_aresetn(rst_clk_wiz_100M_peripheral_aresetn),
        .slowest_sync_clk(clk_wiz_clk_out3));
  design_1_rst_clk_wiz_300M_0 rst_clk_wiz_300M
       (.aux_reset_in(reset_slice_Dout),
        .dcm_locked(clk_wiz_locked),
        .ext_reset_in(reset_rtl_0_1),
        .interconnect_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .mb_debug_sys_rst(1'b0),
        .peripheral_aresetn(rst_clk_wiz_300M_peripheral_aresetn),
        .peripheral_reset(rst_clk_wiz_300M_peripheral_reset),
        .slowest_sync_clk(clk_wiz_clk_out2));
  design_1_rst_zynq_ultra_ps_e_0_99M_0 rst_zynq_ultra_ps_e_0_99M
       (.aux_reset_in(1'b1),
        .dcm_locked(1'b1),
        .ext_reset_in(zynq_ultra_ps_e_0_pl_resetn0),
        .interconnect_aresetn(ARESETN_1),
        .mb_debug_sys_rst(1'b0),
        .peripheral_aresetn(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .slowest_sync_clk(zynq_ultra_ps_e_0_pl_clk0));
  design_1_rtc_0 rtc
       (.CLK(clk_wiz_clk_out2),
        .Q(rtc_Q),
        .SCLR(rst_clk_wiz_300M_peripheral_reset));
  design_1_sd_fec_dec_0 sd_fec_dec
       (.core_clk(clk_wiz_clk_out1),
        .interrupt(sd_fec_dec_interrupt),
        .m_axis_dout_aclk(clk_wiz_clk_out2),
        .m_axis_dout_tdata(sd_fec_dec_M_AXIS_DOUT_TDATA),
        .m_axis_dout_tlast(sd_fec_dec_M_AXIS_DOUT_TLAST),
        .m_axis_dout_tready(sd_fec_dec_M_AXIS_DOUT_TREADY),
        .m_axis_dout_tvalid(sd_fec_dec_M_AXIS_DOUT_TVALID),
        .m_axis_status_aclk(clk_wiz_clk_out2),
        .m_axis_status_tdata(sd_fec_dec_M_AXIS_STATUS_TDATA),
        .m_axis_status_tready(sd_fec_dec_M_AXIS_STATUS_TREADY),
        .m_axis_status_tvalid(sd_fec_dec_M_AXIS_STATUS_TVALID),
        .reset_n(rst_clk_wiz_300M_peripheral_aresetn),
        .s_axi_aclk(clk_wiz_clk_out3),
        .s_axi_araddr(zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARADDR),
        .s_axi_arready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARREADY),
        .s_axi_arvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARVALID),
        .s_axi_awaddr(zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWADDR),
        .s_axi_awready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWREADY),
        .s_axi_awvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWVALID),
        .s_axi_bready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_BREADY),
        .s_axi_bvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_BVALID),
        .s_axi_rdata(zynq_ultra_ps_e_0_axi_periph_M04_AXI_RDATA),
        .s_axi_rready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_RREADY),
        .s_axi_rvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_RVALID),
        .s_axi_wdata(zynq_ultra_ps_e_0_axi_periph_M04_AXI_WDATA),
        .s_axi_wready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_WREADY),
        .s_axi_wvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_WVALID),
        .s_axis_ctrl_aclk(clk_wiz_clk_out2),
        .s_axis_ctrl_tdata(dec_ctrl_fifo_M_AXIS_TDATA),
        .s_axis_ctrl_tready(dec_ctrl_fifo_M_AXIS_TREADY),
        .s_axis_ctrl_tvalid(dec_ctrl_fifo_M_AXIS_TVALID),
        .s_axis_din_aclk(clk_wiz_clk_out2),
        .s_axis_din_tdata(llr_reinterpret_M_AXIS_TDATA),
        .s_axis_din_tlast(llr_reinterpret_M_AXIS_TLAST),
        .s_axis_din_tready(llr_reinterpret_M_AXIS_TREADY),
        .s_axis_din_tvalid(llr_reinterpret_M_AXIS_TVALID));
  design_1_sd_fec_enc_0 sd_fec_enc
       (.core_clk(clk_wiz_clk_out1),
        .interrupt(sd_fec_enc_interrupt),
        .m_axis_dout_aclk(clk_wiz_clk_out2),
        .m_axis_dout_tdata(sd_fec_enc_M_AXIS_DOUT_TDATA),
        .m_axis_dout_tlast(sd_fec_enc_M_AXIS_DOUT_TLAST),
        .m_axis_dout_tready(sd_fec_enc_M_AXIS_DOUT_TREADY),
        .m_axis_dout_tvalid(sd_fec_enc_M_AXIS_DOUT_TVALID),
        .m_axis_status_aclk(clk_wiz_clk_out2),
        .m_axis_status_tready(const_1_dout),
        .reset_n(rst_clk_wiz_300M_peripheral_aresetn),
        .s_axi_aclk(clk_wiz_clk_out3),
        .s_axi_araddr(zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARADDR),
        .s_axi_arready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARREADY),
        .s_axi_arvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARVALID),
        .s_axi_awaddr(zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWADDR),
        .s_axi_awready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWREADY),
        .s_axi_awvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWVALID),
        .s_axi_bready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_BREADY),
        .s_axi_bvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_BVALID),
        .s_axi_rdata(zynq_ultra_ps_e_0_axi_periph_M01_AXI_RDATA),
        .s_axi_rready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_RREADY),
        .s_axi_rvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_RVALID),
        .s_axi_wdata(zynq_ultra_ps_e_0_axi_periph_M01_AXI_WDATA),
        .s_axi_wready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_WREADY),
        .s_axi_wvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_WVALID),
        .s_axis_ctrl_aclk(clk_wiz_clk_out2),
        .s_axis_ctrl_tdata(enc_ctrl_reinterpret_M_AXIS_TDATA),
        .s_axis_ctrl_tready(enc_ctrl_reinterpret_M_AXIS_TREADY),
        .s_axis_ctrl_tvalid(enc_ctrl_reinterpret_M_AXIS_TVALID),
        .s_axis_din_aclk(clk_wiz_clk_out2),
        .s_axis_din_tdata(src_data_broadcast_M00_AXIS_TDATA),
        .s_axis_din_tlast(src_data_broadcast_M00_AXIS_TLAST),
        .s_axis_din_tready(src_data_broadcast_M00_AXIS_TREADY),
        .s_axis_din_tvalid(src_data_broadcast_M00_AXIS_TVALID));
  design_1_src_data_broadcast_0 src_data_broadcast
       (.aclk(clk_wiz_clk_out2),
        .aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .m_axis_tdata({src_data_broadcast_M01_AXIS_TDATA,src_data_broadcast_M00_AXIS_TDATA}),
        .m_axis_tkeep({src_data_broadcast_M01_AXIS_TKEEP,NLW_src_data_broadcast_m_axis_tkeep_UNCONNECTED[15:0]}),
        .m_axis_tlast({src_data_broadcast_M01_AXIS_TLAST,src_data_broadcast_M00_AXIS_TLAST}),
        .m_axis_tready({src_data_broadcast_M01_AXIS_TREADY,src_data_broadcast_M00_AXIS_TREADY}),
        .m_axis_tvalid({src_data_broadcast_M01_AXIS_TVALID,src_data_broadcast_M00_AXIS_TVALID}),
        .s_axis_tdata(hard_data_reg_M_AXIS_TDATA),
        .s_axis_tkeep(hard_data_reg_M_AXIS_TKEEP),
        .s_axis_tlast(hard_data_reg_M_AXIS_TLAST),
        .s_axis_tready(hard_data_reg_M_AXIS_TREADY),
        .s_axis_tvalid(hard_data_reg_M_AXIS_TVALID));
  design_1_src_data_fifo_0 src_data_fifo
       (.m_axis_tdata(src_data_fifo_M_AXIS_TDATA),
        .m_axis_tready(src_data_fifo_M_AXIS_TREADY),
        .m_axis_tvalid(src_data_fifo_M_AXIS_TVALID),
        .s_axis_aclk(clk_wiz_clk_out2),
        .s_axis_aresetn(rst_clk_wiz_300M_interconnect_aresetn),
        .s_axis_tdata(src_data_broadcast_M01_AXIS_TDATA),
        .s_axis_tkeep(src_data_broadcast_M01_AXIS_TKEEP),
        .s_axis_tlast(src_data_broadcast_M01_AXIS_TLAST),
        .s_axis_tready(src_data_broadcast_M01_AXIS_TREADY),
        .s_axis_tvalid(src_data_broadcast_M01_AXIS_TVALID));
  design_1_stats_0 stats
       (.ap_clk(clk_wiz_clk_out2),
        .ap_rst_n(rst_clk_wiz_300M_peripheral_aresetn),
        .ap_rst_n_cntrl_aclk(rst_clk_wiz_100M_peripheral_aresetn),
        .cntrl_aclk(clk_wiz_clk_out3),
        .error_data_TDATA(hard_chan_data_fifo_M_AXIS_TDATA),
        .error_data_TLAST(hard_chan_data_fifo_M_AXIS_TLAST),
        .error_data_TREADY(hard_chan_data_fifo_M_AXIS_TREADY),
        .error_data_TVALID(hard_chan_data_fifo_M_AXIS_TVALID),
        .fe_status_V_V_TDATA(dec_stat_reinterpret_M_AXIS_TDATA),
        .fe_status_V_V_TREADY(dec_stat_reinterpret_M_AXIS_TREADY),
        .fe_status_V_V_TVALID(dec_stat_reinterpret_M_AXIS_TVALID),
        .hard_data_TDATA(dec_data_reinterpret_M_AXIS_TDATA),
        .hard_data_TLAST(dec_data_reinterpret_M_AXIS_TLAST),
        .hard_data_TREADY(dec_data_reinterpret_M_AXIS_TREADY),
        .hard_data_TVALID(dec_data_reinterpret_M_AXIS_TVALID),
        .s_axi_CNTRL_ARADDR(zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARADDR),
        .s_axi_CNTRL_ARREADY(zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARREADY),
        .s_axi_CNTRL_ARVALID(zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARVALID),
        .s_axi_CNTRL_AWADDR(zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWADDR),
        .s_axi_CNTRL_AWREADY(zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWREADY),
        .s_axi_CNTRL_AWVALID(zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWVALID),
        .s_axi_CNTRL_BREADY(zynq_ultra_ps_e_0_axi_periph_M05_AXI_BREADY),
        .s_axi_CNTRL_BRESP(zynq_ultra_ps_e_0_axi_periph_M05_AXI_BRESP),
        .s_axi_CNTRL_BVALID(zynq_ultra_ps_e_0_axi_periph_M05_AXI_BVALID),
        .s_axi_CNTRL_RDATA(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RDATA),
        .s_axi_CNTRL_RREADY(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RREADY),
        .s_axi_CNTRL_RRESP(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RRESP),
        .s_axi_CNTRL_RVALID(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RVALID),
        .s_axi_CNTRL_WDATA(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WDATA),
        .s_axi_CNTRL_WREADY(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WREADY),
        .s_axi_CNTRL_WSTRB(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WSTRB),
        .s_axi_CNTRL_WVALID(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WVALID),
        .src_data_V_V_TDATA(src_data_fifo_M_AXIS_TDATA),
        .src_data_V_V_TREADY(src_data_fifo_M_AXIS_TREADY),
        .src_data_V_V_TVALID(src_data_fifo_M_AXIS_TVALID));
  design_1_usp_rf_data_converter_0_i_0 usp_rf_data_converter_0_i
       (.adc0_clk_n(adc0_clk_1_CLK_N),
        .adc0_clk_p(adc0_clk_1_CLK_P),
        .clk_adc0(usp_rf_data_converter_0_i_clk_adc0),
        .clk_dac0(usp_rf_data_converter_0_i_clk_dac0),
        .dac0_clk_n(dac0_clk_1_CLK_N),
        .dac0_clk_p(dac0_clk_1_CLK_P),
        .irq(usp_rf_data_converter_0_i_irq),
        .m00_axis_tdata(usp_rf_data_converter_0_i_m00_axis_TDATA),
        .m00_axis_tready(usp_rf_data_converter_0_i_m00_axis_TREADY),
        .m00_axis_tvalid(usp_rf_data_converter_0_i_m00_axis_TVALID),
        .m0_axis_aclk(clk_wiz_clk_out3),
        .m0_axis_aresetn(rst_clk_wiz_100M_peripheral_aresetn),
        .s00_axis_tdata(dac_source_i_m00_TDATA),
        .s00_axis_tready(dac_source_i_m00_TREADY),
        .s00_axis_tvalid(dac_source_i_m00_TVALID),
        .s0_axis_aclk(clk_wiz_clk_out3),
        .s0_axis_aresetn(rst_clk_wiz_100M_peripheral_aresetn),
        .s_axi_aclk(zynq_ultra_ps_e_0_pl_clk0),
        .s_axi_araddr(axi_interconnect_0_M00_AXI_ARADDR[17:0]),
        .s_axi_aresetn(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .s_axi_arready(axi_interconnect_0_M00_AXI_ARREADY),
        .s_axi_arvalid(axi_interconnect_0_M00_AXI_ARVALID),
        .s_axi_awaddr(axi_interconnect_0_M00_AXI_AWADDR[17:0]),
        .s_axi_awready(axi_interconnect_0_M00_AXI_AWREADY),
        .s_axi_awvalid(axi_interconnect_0_M00_AXI_AWVALID),
        .s_axi_bready(axi_interconnect_0_M00_AXI_BREADY),
        .s_axi_bresp(axi_interconnect_0_M00_AXI_BRESP),
        .s_axi_bvalid(axi_interconnect_0_M00_AXI_BVALID),
        .s_axi_rdata(axi_interconnect_0_M00_AXI_RDATA),
        .s_axi_rready(axi_interconnect_0_M00_AXI_RREADY),
        .s_axi_rresp(axi_interconnect_0_M00_AXI_RRESP),
        .s_axi_rvalid(axi_interconnect_0_M00_AXI_RVALID),
        .s_axi_wdata(axi_interconnect_0_M00_AXI_WDATA),
        .s_axi_wready(axi_interconnect_0_M00_AXI_WREADY),
        .s_axi_wstrb(axi_interconnect_0_M00_AXI_WSTRB),
        .s_axi_wvalid(axi_interconnect_0_M00_AXI_WVALID),
        .sysref_in_n(sysref_in_1_diff_n),
        .sysref_in_p(sysref_in_1_diff_p),
        .vin0_01_n(vin0_01_0_1_V_N),
        .vin0_01_p(vin0_01_0_1_V_P),
        .vout00_n(usp_rf_data_converter_0_i_vout00_V_N),
        .vout00_p(usp_rf_data_converter_0_i_vout00_V_P));
  design_1_zynq_ultra_ps_e_0_0 zynq_ultra_ps_e_0
       (.emio_uart1_rxd(emio_uart1_rxd_0_1),
        .emio_uart1_txd(zynq_ultra_ps_e_0_emio_uart1_txd),
        .maxigp0_araddr(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARADDR),
        .maxigp0_arburst(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARBURST),
        .maxigp0_arcache(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARCACHE),
        .maxigp0_arid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARID),
        .maxigp0_arlen(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARLEN),
        .maxigp0_arlock(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARLOCK),
        .maxigp0_arprot(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARPROT),
        .maxigp0_arqos(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARQOS),
        .maxigp0_arready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARREADY),
        .maxigp0_arsize(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARSIZE),
        .maxigp0_aruser(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARUSER),
        .maxigp0_arvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARVALID),
        .maxigp0_awaddr(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWADDR),
        .maxigp0_awburst(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWBURST),
        .maxigp0_awcache(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWCACHE),
        .maxigp0_awid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWID),
        .maxigp0_awlen(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWLEN),
        .maxigp0_awlock(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWLOCK),
        .maxigp0_awprot(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWPROT),
        .maxigp0_awqos(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWQOS),
        .maxigp0_awready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWREADY),
        .maxigp0_awsize(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWSIZE),
        .maxigp0_awuser(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWUSER),
        .maxigp0_awvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWVALID),
        .maxigp0_bid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BID),
        .maxigp0_bready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BREADY),
        .maxigp0_bresp(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BRESP),
        .maxigp0_bvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BVALID),
        .maxigp0_rdata(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RDATA),
        .maxigp0_rid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RID),
        .maxigp0_rlast(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RLAST),
        .maxigp0_rready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RREADY),
        .maxigp0_rresp(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RRESP),
        .maxigp0_rvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RVALID),
        .maxigp0_wdata(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WDATA),
        .maxigp0_wlast(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WLAST),
        .maxigp0_wready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WREADY),
        .maxigp0_wstrb(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WSTRB),
        .maxigp0_wvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WVALID),
        .maxigp1_araddr(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARADDR),
        .maxigp1_arburst(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARBURST),
        .maxigp1_arcache(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARCACHE),
        .maxigp1_arid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARID),
        .maxigp1_arlen(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARLEN),
        .maxigp1_arlock(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARLOCK),
        .maxigp1_arprot(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARPROT),
        .maxigp1_arqos(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARQOS),
        .maxigp1_arready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARREADY),
        .maxigp1_arsize(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARSIZE),
        .maxigp1_arvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_ARVALID),
        .maxigp1_awaddr(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWADDR),
        .maxigp1_awburst(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWBURST),
        .maxigp1_awcache(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWCACHE),
        .maxigp1_awid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWID),
        .maxigp1_awlen(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWLEN),
        .maxigp1_awlock(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWLOCK),
        .maxigp1_awprot(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWPROT),
        .maxigp1_awqos(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWQOS),
        .maxigp1_awready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWREADY),
        .maxigp1_awsize(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWSIZE),
        .maxigp1_awvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_AWVALID),
        .maxigp1_bid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BID),
        .maxigp1_bready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BREADY),
        .maxigp1_bresp(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BRESP),
        .maxigp1_bvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_BVALID),
        .maxigp1_rdata(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RDATA),
        .maxigp1_rid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RID),
        .maxigp1_rlast(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RLAST),
        .maxigp1_rready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RREADY),
        .maxigp1_rresp(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RRESP),
        .maxigp1_rvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_RVALID),
        .maxigp1_wdata(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WDATA),
        .maxigp1_wlast(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WLAST),
        .maxigp1_wready(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WREADY),
        .maxigp1_wstrb(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WSTRB),
        .maxigp1_wvalid(zynq_ultra_ps_e_0_M_AXI_HPM1_FPD_WVALID),
        .maxihpm0_fpd_aclk(zynq_ultra_ps_e_0_pl_clk0),
        .maxihpm1_fpd_aclk(zynq_ultra_ps_e_0_pl_clk0),
        .pl_clk0(zynq_ultra_ps_e_0_pl_clk0),
        .pl_ps_irq0(axi_intc_irq),
        .pl_resetn0(zynq_ultra_ps_e_0_pl_resetn0));
  design_1_zynq_ultra_ps_e_0_axi_periph_0 zynq_ultra_ps_e_0_axi_periph
       (.ACLK(clk_wiz_clk_out3),
        .ARESETN(rst_clk_wiz_100M_interconnect_aresetn),
        .M00_ACLK(clk_wiz_clk_out3),
        .M00_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M00_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARADDR),
        .M00_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARREADY),
        .M00_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M00_AXI_ARVALID),
        .M00_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWADDR),
        .M00_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWREADY),
        .M00_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M00_AXI_AWVALID),
        .M00_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M00_AXI_BREADY),
        .M00_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M00_AXI_BRESP),
        .M00_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M00_AXI_BVALID),
        .M00_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RDATA),
        .M00_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RREADY),
        .M00_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RRESP),
        .M00_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M00_AXI_RVALID),
        .M00_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WDATA),
        .M00_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WREADY),
        .M00_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WSTRB),
        .M00_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M00_AXI_WVALID),
        .M01_ACLK(clk_wiz_clk_out3),
        .M01_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M01_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARADDR),
        .M01_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARREADY),
        .M01_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_ARVALID),
        .M01_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWADDR),
        .M01_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWREADY),
        .M01_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_AWVALID),
        .M01_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_BREADY),
        .M01_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_BVALID),
        .M01_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M01_AXI_RDATA),
        .M01_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_RREADY),
        .M01_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_RVALID),
        .M01_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M01_AXI_WDATA),
        .M01_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M01_AXI_WREADY),
        .M01_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M01_AXI_WVALID),
        .M02_ACLK(clk_wiz_clk_out3),
        .M02_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M02_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARADDR),
        .M02_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARREADY),
        .M02_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M02_AXI_ARVALID),
        .M02_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWADDR),
        .M02_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWREADY),
        .M02_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M02_AXI_AWVALID),
        .M02_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M02_AXI_BREADY),
        .M02_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M02_AXI_BRESP),
        .M02_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M02_AXI_BVALID),
        .M02_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RDATA),
        .M02_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RREADY),
        .M02_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RRESP),
        .M02_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M02_AXI_RVALID),
        .M02_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WDATA),
        .M02_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WREADY),
        .M02_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WSTRB),
        .M02_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M02_AXI_WVALID),
        .M03_ACLK(clk_wiz_clk_out3),
        .M03_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M03_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARADDR),
        .M03_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARREADY),
        .M03_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M03_AXI_ARVALID),
        .M03_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWADDR),
        .M03_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWREADY),
        .M03_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M03_AXI_AWVALID),
        .M03_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M03_AXI_BREADY),
        .M03_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M03_AXI_BRESP),
        .M03_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M03_AXI_BVALID),
        .M03_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RDATA),
        .M03_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RREADY),
        .M03_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RRESP),
        .M03_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M03_AXI_RVALID),
        .M03_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WDATA),
        .M03_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WREADY),
        .M03_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WSTRB),
        .M03_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M03_AXI_WVALID),
        .M04_ACLK(clk_wiz_clk_out3),
        .M04_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M04_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARADDR),
        .M04_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARREADY),
        .M04_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_ARVALID),
        .M04_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWADDR),
        .M04_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWREADY),
        .M04_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_AWVALID),
        .M04_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_BREADY),
        .M04_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_BVALID),
        .M04_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M04_AXI_RDATA),
        .M04_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_RREADY),
        .M04_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_RVALID),
        .M04_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M04_AXI_WDATA),
        .M04_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M04_AXI_WREADY),
        .M04_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M04_AXI_WVALID),
        .M05_ACLK(clk_wiz_clk_out3),
        .M05_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M05_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARADDR),
        .M05_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARREADY),
        .M05_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M05_AXI_ARVALID),
        .M05_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWADDR),
        .M05_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWREADY),
        .M05_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M05_AXI_AWVALID),
        .M05_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M05_AXI_BREADY),
        .M05_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M05_AXI_BRESP),
        .M05_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M05_AXI_BVALID),
        .M05_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RDATA),
        .M05_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RREADY),
        .M05_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RRESP),
        .M05_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M05_AXI_RVALID),
        .M05_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WDATA),
        .M05_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WREADY),
        .M05_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WSTRB),
        .M05_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M05_AXI_WVALID),
        .M06_ACLK(clk_wiz_clk_out3),
        .M06_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M06_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARADDR),
        .M06_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARREADY),
        .M06_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_ARVALID),
        .M06_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWADDR),
        .M06_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWREADY),
        .M06_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_AWVALID),
        .M06_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_BREADY),
        .M06_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M06_AXI_BRESP),
        .M06_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_BVALID),
        .M06_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RDATA),
        .M06_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RREADY),
        .M06_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RRESP),
        .M06_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_RVALID),
        .M06_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WDATA),
        .M06_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WREADY),
        .M06_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WSTRB),
        .M06_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M06_AXI_WVALID),
        .M07_ACLK(clk_wiz_clk_out3),
        .M07_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M07_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARADDR),
        .M07_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARREADY),
        .M07_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M07_AXI_ARVALID),
        .M07_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWADDR),
        .M07_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWREADY),
        .M07_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M07_AXI_AWVALID),
        .M07_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M07_AXI_BREADY),
        .M07_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M07_AXI_BRESP),
        .M07_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M07_AXI_BVALID),
        .M07_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RDATA),
        .M07_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RREADY),
        .M07_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RRESP),
        .M07_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M07_AXI_RVALID),
        .M07_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WDATA),
        .M07_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WREADY),
        .M07_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WSTRB),
        .M07_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M07_AXI_WVALID),
        .M08_ACLK(clk_wiz_clk_out3),
        .M08_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M08_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARADDR),
        .M08_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARREADY),
        .M08_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M08_AXI_ARVALID),
        .M08_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWADDR),
        .M08_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWREADY),
        .M08_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M08_AXI_AWVALID),
        .M08_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M08_AXI_BREADY),
        .M08_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M08_AXI_BRESP),
        .M08_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M08_AXI_BVALID),
        .M08_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RDATA),
        .M08_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RREADY),
        .M08_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RRESP),
        .M08_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M08_AXI_RVALID),
        .M08_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WDATA),
        .M08_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WREADY),
        .M08_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WSTRB),
        .M08_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M08_AXI_WVALID),
        .M09_ACLK(clk_wiz_clk_out3),
        .M09_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M09_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARADDR),
        .M09_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARREADY),
        .M09_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_ARVALID),
        .M09_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWADDR),
        .M09_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWREADY),
        .M09_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_AWVALID),
        .M09_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_BREADY),
        .M09_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M09_AXI_BRESP),
        .M09_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_BVALID),
        .M09_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RDATA),
        .M09_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RREADY),
        .M09_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RRESP),
        .M09_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_RVALID),
        .M09_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WDATA),
        .M09_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WREADY),
        .M09_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WSTRB),
        .M09_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M09_AXI_WVALID),
        .M10_ACLK(clk_wiz_clk_out3),
        .M10_ARESETN(rst_clk_wiz_100M_peripheral_aresetn),
        .M10_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARADDR),
        .M10_AXI_arready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARREADY),
        .M10_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_ARVALID),
        .M10_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWADDR),
        .M10_AXI_awready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWREADY),
        .M10_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_AWVALID),
        .M10_AXI_bready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_BREADY),
        .M10_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_M10_AXI_BRESP),
        .M10_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_BVALID),
        .M10_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RDATA),
        .M10_AXI_rready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RREADY),
        .M10_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RRESP),
        .M10_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_RVALID),
        .M10_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WDATA),
        .M10_AXI_wready(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WREADY),
        .M10_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WSTRB),
        .M10_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_M10_AXI_WVALID),
        .S00_ACLK(zynq_ultra_ps_e_0_pl_clk0),
        .S00_ARESETN(rst_zynq_ultra_ps_e_0_99M_peripheral_aresetn),
        .S00_AXI_araddr(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARADDR),
        .S00_AXI_arburst(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARBURST),
        .S00_AXI_arcache(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARCACHE),
        .S00_AXI_arid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARID),
        .S00_AXI_arlen(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARLEN),
        .S00_AXI_arlock(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARLOCK),
        .S00_AXI_arprot(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARPROT),
        .S00_AXI_arqos(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARQOS),
        .S00_AXI_arready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARREADY),
        .S00_AXI_arsize(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARSIZE),
        .S00_AXI_aruser(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARUSER),
        .S00_AXI_arvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_ARVALID),
        .S00_AXI_awaddr(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWADDR),
        .S00_AXI_awburst(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWBURST),
        .S00_AXI_awcache(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWCACHE),
        .S00_AXI_awid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWID),
        .S00_AXI_awlen(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWLEN),
        .S00_AXI_awlock(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWLOCK),
        .S00_AXI_awprot(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWPROT),
        .S00_AXI_awqos(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWQOS),
        .S00_AXI_awready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWREADY),
        .S00_AXI_awsize(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWSIZE),
        .S00_AXI_awuser(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWUSER),
        .S00_AXI_awvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_AWVALID),
        .S00_AXI_bid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BID),
        .S00_AXI_bready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BREADY),
        .S00_AXI_bresp(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BRESP),
        .S00_AXI_bvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_BVALID),
        .S00_AXI_rdata(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RDATA),
        .S00_AXI_rid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RID),
        .S00_AXI_rlast(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RLAST),
        .S00_AXI_rready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RREADY),
        .S00_AXI_rresp(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RRESP),
        .S00_AXI_rvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_RVALID),
        .S00_AXI_wdata(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WDATA),
        .S00_AXI_wlast(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WLAST),
        .S00_AXI_wready(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WREADY),
        .S00_AXI_wstrb(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WSTRB),
        .S00_AXI_wvalid(zynq_ultra_ps_e_0_M_AXI_HPM0_FPD_WVALID));
endmodule

module design_1_axi_interconnect_0_0
   (ACLK,
    ARESETN,
    M00_ACLK,
    M00_ARESETN,
    M00_AXI_araddr,
    M00_AXI_arready,
    M00_AXI_arvalid,
    M00_AXI_awaddr,
    M00_AXI_awready,
    M00_AXI_awvalid,
    M00_AXI_bready,
    M00_AXI_bresp,
    M00_AXI_bvalid,
    M00_AXI_rdata,
    M00_AXI_rready,
    M00_AXI_rresp,
    M00_AXI_rvalid,
    M00_AXI_wdata,
    M00_AXI_wready,
    M00_AXI_wstrb,
    M00_AXI_wvalid,
    M01_ACLK,
    M01_ARESETN,
    M01_AXI_araddr,
    M01_AXI_arready,
    M01_AXI_arvalid,
    M01_AXI_awaddr,
    M01_AXI_awready,
    M01_AXI_awvalid,
    M01_AXI_bready,
    M01_AXI_bresp,
    M01_AXI_bvalid,
    M01_AXI_rdata,
    M01_AXI_rready,
    M01_AXI_rresp,
    M01_AXI_rvalid,
    M01_AXI_wdata,
    M01_AXI_wready,
    M01_AXI_wstrb,
    M01_AXI_wvalid,
    M02_ACLK,
    M02_ARESETN,
    M02_AXI_araddr,
    M02_AXI_arready,
    M02_AXI_arvalid,
    M02_AXI_awaddr,
    M02_AXI_awready,
    M02_AXI_awvalid,
    M02_AXI_bready,
    M02_AXI_bresp,
    M02_AXI_bvalid,
    M02_AXI_rdata,
    M02_AXI_rready,
    M02_AXI_rresp,
    M02_AXI_rvalid,
    M02_AXI_wdata,
    M02_AXI_wready,
    M02_AXI_wstrb,
    M02_AXI_wvalid,
    S00_ACLK,
    S00_ARESETN,
    S00_AXI_araddr,
    S00_AXI_arburst,
    S00_AXI_arcache,
    S00_AXI_arid,
    S00_AXI_arlen,
    S00_AXI_arlock,
    S00_AXI_arprot,
    S00_AXI_arqos,
    S00_AXI_arready,
    S00_AXI_arsize,
    S00_AXI_arvalid,
    S00_AXI_awaddr,
    S00_AXI_awburst,
    S00_AXI_awcache,
    S00_AXI_awid,
    S00_AXI_awlen,
    S00_AXI_awlock,
    S00_AXI_awprot,
    S00_AXI_awqos,
    S00_AXI_awready,
    S00_AXI_awsize,
    S00_AXI_awvalid,
    S00_AXI_bid,
    S00_AXI_bready,
    S00_AXI_bresp,
    S00_AXI_bvalid,
    S00_AXI_rdata,
    S00_AXI_rid,
    S00_AXI_rlast,
    S00_AXI_rready,
    S00_AXI_rresp,
    S00_AXI_rvalid,
    S00_AXI_wdata,
    S00_AXI_wlast,
    S00_AXI_wready,
    S00_AXI_wstrb,
    S00_AXI_wvalid);
  input ACLK;
  input ARESETN;
  input M00_ACLK;
  input M00_ARESETN;
  output [39:0]M00_AXI_araddr;
  input M00_AXI_arready;
  output M00_AXI_arvalid;
  output [39:0]M00_AXI_awaddr;
  input M00_AXI_awready;
  output M00_AXI_awvalid;
  output M00_AXI_bready;
  input [1:0]M00_AXI_bresp;
  input M00_AXI_bvalid;
  input [31:0]M00_AXI_rdata;
  output M00_AXI_rready;
  input [1:0]M00_AXI_rresp;
  input M00_AXI_rvalid;
  output [31:0]M00_AXI_wdata;
  input M00_AXI_wready;
  output [3:0]M00_AXI_wstrb;
  output M00_AXI_wvalid;
  input M01_ACLK;
  input M01_ARESETN;
  output [39:0]M01_AXI_araddr;
  input M01_AXI_arready;
  output M01_AXI_arvalid;
  output [39:0]M01_AXI_awaddr;
  input M01_AXI_awready;
  output M01_AXI_awvalid;
  output M01_AXI_bready;
  input [1:0]M01_AXI_bresp;
  input M01_AXI_bvalid;
  input [31:0]M01_AXI_rdata;
  output M01_AXI_rready;
  input [1:0]M01_AXI_rresp;
  input M01_AXI_rvalid;
  output [31:0]M01_AXI_wdata;
  input M01_AXI_wready;
  output [3:0]M01_AXI_wstrb;
  output M01_AXI_wvalid;
  input M02_ACLK;
  input M02_ARESETN;
  output [39:0]M02_AXI_araddr;
  input [0:0]M02_AXI_arready;
  output [0:0]M02_AXI_arvalid;
  output [39:0]M02_AXI_awaddr;
  input [0:0]M02_AXI_awready;
  output [0:0]M02_AXI_awvalid;
  output [0:0]M02_AXI_bready;
  input [1:0]M02_AXI_bresp;
  input [0:0]M02_AXI_bvalid;
  input [31:0]M02_AXI_rdata;
  output [0:0]M02_AXI_rready;
  input [1:0]M02_AXI_rresp;
  input [0:0]M02_AXI_rvalid;
  output [31:0]M02_AXI_wdata;
  input [0:0]M02_AXI_wready;
  output [3:0]M02_AXI_wstrb;
  output [0:0]M02_AXI_wvalid;
  input S00_ACLK;
  input S00_ARESETN;
  input [39:0]S00_AXI_araddr;
  input [1:0]S00_AXI_arburst;
  input [3:0]S00_AXI_arcache;
  input [15:0]S00_AXI_arid;
  input [7:0]S00_AXI_arlen;
  input [0:0]S00_AXI_arlock;
  input [2:0]S00_AXI_arprot;
  input [3:0]S00_AXI_arqos;
  output S00_AXI_arready;
  input [2:0]S00_AXI_arsize;
  input S00_AXI_arvalid;
  input [39:0]S00_AXI_awaddr;
  input [1:0]S00_AXI_awburst;
  input [3:0]S00_AXI_awcache;
  input [15:0]S00_AXI_awid;
  input [7:0]S00_AXI_awlen;
  input [0:0]S00_AXI_awlock;
  input [2:0]S00_AXI_awprot;
  input [3:0]S00_AXI_awqos;
  output S00_AXI_awready;
  input [2:0]S00_AXI_awsize;
  input S00_AXI_awvalid;
  output [15:0]S00_AXI_bid;
  input S00_AXI_bready;
  output [1:0]S00_AXI_bresp;
  output S00_AXI_bvalid;
  output [127:0]S00_AXI_rdata;
  output [15:0]S00_AXI_rid;
  output S00_AXI_rlast;
  input S00_AXI_rready;
  output [1:0]S00_AXI_rresp;
  output S00_AXI_rvalid;
  input [127:0]S00_AXI_wdata;
  input S00_AXI_wlast;
  output S00_AXI_wready;
  input [15:0]S00_AXI_wstrb;
  input S00_AXI_wvalid;

  wire M00_ACLK_1;
  wire M00_ARESETN_1;
  wire M01_ACLK_1;
  wire M01_ARESETN_1;
  wire M02_ACLK_1;
  wire M02_ARESETN_1;
  wire S00_ACLK_1;
  wire S00_ARESETN_1;
  wire axi_interconnect_0_ACLK_net;
  wire axi_interconnect_0_ARESETN_net;
  wire [39:0]axi_interconnect_0_to_s00_couplers_ARADDR;
  wire [1:0]axi_interconnect_0_to_s00_couplers_ARBURST;
  wire [3:0]axi_interconnect_0_to_s00_couplers_ARCACHE;
  wire [15:0]axi_interconnect_0_to_s00_couplers_ARID;
  wire [7:0]axi_interconnect_0_to_s00_couplers_ARLEN;
  wire [0:0]axi_interconnect_0_to_s00_couplers_ARLOCK;
  wire [2:0]axi_interconnect_0_to_s00_couplers_ARPROT;
  wire [3:0]axi_interconnect_0_to_s00_couplers_ARQOS;
  wire axi_interconnect_0_to_s00_couplers_ARREADY;
  wire [2:0]axi_interconnect_0_to_s00_couplers_ARSIZE;
  wire axi_interconnect_0_to_s00_couplers_ARVALID;
  wire [39:0]axi_interconnect_0_to_s00_couplers_AWADDR;
  wire [1:0]axi_interconnect_0_to_s00_couplers_AWBURST;
  wire [3:0]axi_interconnect_0_to_s00_couplers_AWCACHE;
  wire [15:0]axi_interconnect_0_to_s00_couplers_AWID;
  wire [7:0]axi_interconnect_0_to_s00_couplers_AWLEN;
  wire [0:0]axi_interconnect_0_to_s00_couplers_AWLOCK;
  wire [2:0]axi_interconnect_0_to_s00_couplers_AWPROT;
  wire [3:0]axi_interconnect_0_to_s00_couplers_AWQOS;
  wire axi_interconnect_0_to_s00_couplers_AWREADY;
  wire [2:0]axi_interconnect_0_to_s00_couplers_AWSIZE;
  wire axi_interconnect_0_to_s00_couplers_AWVALID;
  wire [15:0]axi_interconnect_0_to_s00_couplers_BID;
  wire axi_interconnect_0_to_s00_couplers_BREADY;
  wire [1:0]axi_interconnect_0_to_s00_couplers_BRESP;
  wire axi_interconnect_0_to_s00_couplers_BVALID;
  wire [127:0]axi_interconnect_0_to_s00_couplers_RDATA;
  wire [15:0]axi_interconnect_0_to_s00_couplers_RID;
  wire axi_interconnect_0_to_s00_couplers_RLAST;
  wire axi_interconnect_0_to_s00_couplers_RREADY;
  wire [1:0]axi_interconnect_0_to_s00_couplers_RRESP;
  wire axi_interconnect_0_to_s00_couplers_RVALID;
  wire [127:0]axi_interconnect_0_to_s00_couplers_WDATA;
  wire axi_interconnect_0_to_s00_couplers_WLAST;
  wire axi_interconnect_0_to_s00_couplers_WREADY;
  wire [15:0]axi_interconnect_0_to_s00_couplers_WSTRB;
  wire axi_interconnect_0_to_s00_couplers_WVALID;
  wire [39:0]m00_couplers_to_axi_interconnect_0_ARADDR;
  wire m00_couplers_to_axi_interconnect_0_ARREADY;
  wire m00_couplers_to_axi_interconnect_0_ARVALID;
  wire [39:0]m00_couplers_to_axi_interconnect_0_AWADDR;
  wire m00_couplers_to_axi_interconnect_0_AWREADY;
  wire m00_couplers_to_axi_interconnect_0_AWVALID;
  wire m00_couplers_to_axi_interconnect_0_BREADY;
  wire [1:0]m00_couplers_to_axi_interconnect_0_BRESP;
  wire m00_couplers_to_axi_interconnect_0_BVALID;
  wire [31:0]m00_couplers_to_axi_interconnect_0_RDATA;
  wire m00_couplers_to_axi_interconnect_0_RREADY;
  wire [1:0]m00_couplers_to_axi_interconnect_0_RRESP;
  wire m00_couplers_to_axi_interconnect_0_RVALID;
  wire [31:0]m00_couplers_to_axi_interconnect_0_WDATA;
  wire m00_couplers_to_axi_interconnect_0_WREADY;
  wire [3:0]m00_couplers_to_axi_interconnect_0_WSTRB;
  wire m00_couplers_to_axi_interconnect_0_WVALID;
  wire [39:0]m01_couplers_to_axi_interconnect_0_ARADDR;
  wire m01_couplers_to_axi_interconnect_0_ARREADY;
  wire m01_couplers_to_axi_interconnect_0_ARVALID;
  wire [39:0]m01_couplers_to_axi_interconnect_0_AWADDR;
  wire m01_couplers_to_axi_interconnect_0_AWREADY;
  wire m01_couplers_to_axi_interconnect_0_AWVALID;
  wire m01_couplers_to_axi_interconnect_0_BREADY;
  wire [1:0]m01_couplers_to_axi_interconnect_0_BRESP;
  wire m01_couplers_to_axi_interconnect_0_BVALID;
  wire [31:0]m01_couplers_to_axi_interconnect_0_RDATA;
  wire m01_couplers_to_axi_interconnect_0_RREADY;
  wire [1:0]m01_couplers_to_axi_interconnect_0_RRESP;
  wire m01_couplers_to_axi_interconnect_0_RVALID;
  wire [31:0]m01_couplers_to_axi_interconnect_0_WDATA;
  wire m01_couplers_to_axi_interconnect_0_WREADY;
  wire [3:0]m01_couplers_to_axi_interconnect_0_WSTRB;
  wire m01_couplers_to_axi_interconnect_0_WVALID;
  wire [39:0]m02_couplers_to_axi_interconnect_0_ARADDR;
  wire [0:0]m02_couplers_to_axi_interconnect_0_ARREADY;
  wire [0:0]m02_couplers_to_axi_interconnect_0_ARVALID;
  wire [39:0]m02_couplers_to_axi_interconnect_0_AWADDR;
  wire [0:0]m02_couplers_to_axi_interconnect_0_AWREADY;
  wire [0:0]m02_couplers_to_axi_interconnect_0_AWVALID;
  wire [0:0]m02_couplers_to_axi_interconnect_0_BREADY;
  wire [1:0]m02_couplers_to_axi_interconnect_0_BRESP;
  wire [0:0]m02_couplers_to_axi_interconnect_0_BVALID;
  wire [31:0]m02_couplers_to_axi_interconnect_0_RDATA;
  wire [0:0]m02_couplers_to_axi_interconnect_0_RREADY;
  wire [1:0]m02_couplers_to_axi_interconnect_0_RRESP;
  wire [0:0]m02_couplers_to_axi_interconnect_0_RVALID;
  wire [31:0]m02_couplers_to_axi_interconnect_0_WDATA;
  wire [0:0]m02_couplers_to_axi_interconnect_0_WREADY;
  wire [3:0]m02_couplers_to_axi_interconnect_0_WSTRB;
  wire [0:0]m02_couplers_to_axi_interconnect_0_WVALID;
  wire [39:0]s00_couplers_to_xbar_ARADDR;
  wire [2:0]s00_couplers_to_xbar_ARPROT;
  wire [0:0]s00_couplers_to_xbar_ARREADY;
  wire s00_couplers_to_xbar_ARVALID;
  wire [39:0]s00_couplers_to_xbar_AWADDR;
  wire [2:0]s00_couplers_to_xbar_AWPROT;
  wire [0:0]s00_couplers_to_xbar_AWREADY;
  wire s00_couplers_to_xbar_AWVALID;
  wire s00_couplers_to_xbar_BREADY;
  wire [1:0]s00_couplers_to_xbar_BRESP;
  wire [0:0]s00_couplers_to_xbar_BVALID;
  wire [31:0]s00_couplers_to_xbar_RDATA;
  wire s00_couplers_to_xbar_RREADY;
  wire [1:0]s00_couplers_to_xbar_RRESP;
  wire [0:0]s00_couplers_to_xbar_RVALID;
  wire [31:0]s00_couplers_to_xbar_WDATA;
  wire [0:0]s00_couplers_to_xbar_WREADY;
  wire [3:0]s00_couplers_to_xbar_WSTRB;
  wire s00_couplers_to_xbar_WVALID;
  wire [39:0]xbar_to_m00_couplers_ARADDR;
  wire xbar_to_m00_couplers_ARREADY;
  wire [0:0]xbar_to_m00_couplers_ARVALID;
  wire [39:0]xbar_to_m00_couplers_AWADDR;
  wire xbar_to_m00_couplers_AWREADY;
  wire [0:0]xbar_to_m00_couplers_AWVALID;
  wire [0:0]xbar_to_m00_couplers_BREADY;
  wire [1:0]xbar_to_m00_couplers_BRESP;
  wire xbar_to_m00_couplers_BVALID;
  wire [31:0]xbar_to_m00_couplers_RDATA;
  wire [0:0]xbar_to_m00_couplers_RREADY;
  wire [1:0]xbar_to_m00_couplers_RRESP;
  wire xbar_to_m00_couplers_RVALID;
  wire [31:0]xbar_to_m00_couplers_WDATA;
  wire xbar_to_m00_couplers_WREADY;
  wire [3:0]xbar_to_m00_couplers_WSTRB;
  wire [0:0]xbar_to_m00_couplers_WVALID;
  wire [79:40]xbar_to_m01_couplers_ARADDR;
  wire xbar_to_m01_couplers_ARREADY;
  wire [1:1]xbar_to_m01_couplers_ARVALID;
  wire [79:40]xbar_to_m01_couplers_AWADDR;
  wire xbar_to_m01_couplers_AWREADY;
  wire [1:1]xbar_to_m01_couplers_AWVALID;
  wire [1:1]xbar_to_m01_couplers_BREADY;
  wire [1:0]xbar_to_m01_couplers_BRESP;
  wire xbar_to_m01_couplers_BVALID;
  wire [31:0]xbar_to_m01_couplers_RDATA;
  wire [1:1]xbar_to_m01_couplers_RREADY;
  wire [1:0]xbar_to_m01_couplers_RRESP;
  wire xbar_to_m01_couplers_RVALID;
  wire [63:32]xbar_to_m01_couplers_WDATA;
  wire xbar_to_m01_couplers_WREADY;
  wire [7:4]xbar_to_m01_couplers_WSTRB;
  wire [1:1]xbar_to_m01_couplers_WVALID;
  wire [119:80]xbar_to_m02_couplers_ARADDR;
  wire [0:0]xbar_to_m02_couplers_ARREADY;
  wire [2:2]xbar_to_m02_couplers_ARVALID;
  wire [119:80]xbar_to_m02_couplers_AWADDR;
  wire [0:0]xbar_to_m02_couplers_AWREADY;
  wire [2:2]xbar_to_m02_couplers_AWVALID;
  wire [2:2]xbar_to_m02_couplers_BREADY;
  wire [1:0]xbar_to_m02_couplers_BRESP;
  wire [0:0]xbar_to_m02_couplers_BVALID;
  wire [31:0]xbar_to_m02_couplers_RDATA;
  wire [2:2]xbar_to_m02_couplers_RREADY;
  wire [1:0]xbar_to_m02_couplers_RRESP;
  wire [0:0]xbar_to_m02_couplers_RVALID;
  wire [95:64]xbar_to_m02_couplers_WDATA;
  wire [0:0]xbar_to_m02_couplers_WREADY;
  wire [11:8]xbar_to_m02_couplers_WSTRB;
  wire [2:2]xbar_to_m02_couplers_WVALID;

  assign M00_ACLK_1 = M00_ACLK;
  assign M00_ARESETN_1 = M00_ARESETN;
  assign M00_AXI_araddr[39:0] = m00_couplers_to_axi_interconnect_0_ARADDR;
  assign M00_AXI_arvalid = m00_couplers_to_axi_interconnect_0_ARVALID;
  assign M00_AXI_awaddr[39:0] = m00_couplers_to_axi_interconnect_0_AWADDR;
  assign M00_AXI_awvalid = m00_couplers_to_axi_interconnect_0_AWVALID;
  assign M00_AXI_bready = m00_couplers_to_axi_interconnect_0_BREADY;
  assign M00_AXI_rready = m00_couplers_to_axi_interconnect_0_RREADY;
  assign M00_AXI_wdata[31:0] = m00_couplers_to_axi_interconnect_0_WDATA;
  assign M00_AXI_wstrb[3:0] = m00_couplers_to_axi_interconnect_0_WSTRB;
  assign M00_AXI_wvalid = m00_couplers_to_axi_interconnect_0_WVALID;
  assign M01_ACLK_1 = M01_ACLK;
  assign M01_ARESETN_1 = M01_ARESETN;
  assign M01_AXI_araddr[39:0] = m01_couplers_to_axi_interconnect_0_ARADDR;
  assign M01_AXI_arvalid = m01_couplers_to_axi_interconnect_0_ARVALID;
  assign M01_AXI_awaddr[39:0] = m01_couplers_to_axi_interconnect_0_AWADDR;
  assign M01_AXI_awvalid = m01_couplers_to_axi_interconnect_0_AWVALID;
  assign M01_AXI_bready = m01_couplers_to_axi_interconnect_0_BREADY;
  assign M01_AXI_rready = m01_couplers_to_axi_interconnect_0_RREADY;
  assign M01_AXI_wdata[31:0] = m01_couplers_to_axi_interconnect_0_WDATA;
  assign M01_AXI_wstrb[3:0] = m01_couplers_to_axi_interconnect_0_WSTRB;
  assign M01_AXI_wvalid = m01_couplers_to_axi_interconnect_0_WVALID;
  assign M02_ACLK_1 = M02_ACLK;
  assign M02_ARESETN_1 = M02_ARESETN;
  assign M02_AXI_araddr[39:0] = m02_couplers_to_axi_interconnect_0_ARADDR;
  assign M02_AXI_arvalid[0] = m02_couplers_to_axi_interconnect_0_ARVALID;
  assign M02_AXI_awaddr[39:0] = m02_couplers_to_axi_interconnect_0_AWADDR;
  assign M02_AXI_awvalid[0] = m02_couplers_to_axi_interconnect_0_AWVALID;
  assign M02_AXI_bready[0] = m02_couplers_to_axi_interconnect_0_BREADY;
  assign M02_AXI_rready[0] = m02_couplers_to_axi_interconnect_0_RREADY;
  assign M02_AXI_wdata[31:0] = m02_couplers_to_axi_interconnect_0_WDATA;
  assign M02_AXI_wstrb[3:0] = m02_couplers_to_axi_interconnect_0_WSTRB;
  assign M02_AXI_wvalid[0] = m02_couplers_to_axi_interconnect_0_WVALID;
  assign S00_ACLK_1 = S00_ACLK;
  assign S00_ARESETN_1 = S00_ARESETN;
  assign S00_AXI_arready = axi_interconnect_0_to_s00_couplers_ARREADY;
  assign S00_AXI_awready = axi_interconnect_0_to_s00_couplers_AWREADY;
  assign S00_AXI_bid[15:0] = axi_interconnect_0_to_s00_couplers_BID;
  assign S00_AXI_bresp[1:0] = axi_interconnect_0_to_s00_couplers_BRESP;
  assign S00_AXI_bvalid = axi_interconnect_0_to_s00_couplers_BVALID;
  assign S00_AXI_rdata[127:0] = axi_interconnect_0_to_s00_couplers_RDATA;
  assign S00_AXI_rid[15:0] = axi_interconnect_0_to_s00_couplers_RID;
  assign S00_AXI_rlast = axi_interconnect_0_to_s00_couplers_RLAST;
  assign S00_AXI_rresp[1:0] = axi_interconnect_0_to_s00_couplers_RRESP;
  assign S00_AXI_rvalid = axi_interconnect_0_to_s00_couplers_RVALID;
  assign S00_AXI_wready = axi_interconnect_0_to_s00_couplers_WREADY;
  assign axi_interconnect_0_ACLK_net = ACLK;
  assign axi_interconnect_0_ARESETN_net = ARESETN;
  assign axi_interconnect_0_to_s00_couplers_ARADDR = S00_AXI_araddr[39:0];
  assign axi_interconnect_0_to_s00_couplers_ARBURST = S00_AXI_arburst[1:0];
  assign axi_interconnect_0_to_s00_couplers_ARCACHE = S00_AXI_arcache[3:0];
  assign axi_interconnect_0_to_s00_couplers_ARID = S00_AXI_arid[15:0];
  assign axi_interconnect_0_to_s00_couplers_ARLEN = S00_AXI_arlen[7:0];
  assign axi_interconnect_0_to_s00_couplers_ARLOCK = S00_AXI_arlock[0];
  assign axi_interconnect_0_to_s00_couplers_ARPROT = S00_AXI_arprot[2:0];
  assign axi_interconnect_0_to_s00_couplers_ARQOS = S00_AXI_arqos[3:0];
  assign axi_interconnect_0_to_s00_couplers_ARSIZE = S00_AXI_arsize[2:0];
  assign axi_interconnect_0_to_s00_couplers_ARVALID = S00_AXI_arvalid;
  assign axi_interconnect_0_to_s00_couplers_AWADDR = S00_AXI_awaddr[39:0];
  assign axi_interconnect_0_to_s00_couplers_AWBURST = S00_AXI_awburst[1:0];
  assign axi_interconnect_0_to_s00_couplers_AWCACHE = S00_AXI_awcache[3:0];
  assign axi_interconnect_0_to_s00_couplers_AWID = S00_AXI_awid[15:0];
  assign axi_interconnect_0_to_s00_couplers_AWLEN = S00_AXI_awlen[7:0];
  assign axi_interconnect_0_to_s00_couplers_AWLOCK = S00_AXI_awlock[0];
  assign axi_interconnect_0_to_s00_couplers_AWPROT = S00_AXI_awprot[2:0];
  assign axi_interconnect_0_to_s00_couplers_AWQOS = S00_AXI_awqos[3:0];
  assign axi_interconnect_0_to_s00_couplers_AWSIZE = S00_AXI_awsize[2:0];
  assign axi_interconnect_0_to_s00_couplers_AWVALID = S00_AXI_awvalid;
  assign axi_interconnect_0_to_s00_couplers_BREADY = S00_AXI_bready;
  assign axi_interconnect_0_to_s00_couplers_RREADY = S00_AXI_rready;
  assign axi_interconnect_0_to_s00_couplers_WDATA = S00_AXI_wdata[127:0];
  assign axi_interconnect_0_to_s00_couplers_WLAST = S00_AXI_wlast;
  assign axi_interconnect_0_to_s00_couplers_WSTRB = S00_AXI_wstrb[15:0];
  assign axi_interconnect_0_to_s00_couplers_WVALID = S00_AXI_wvalid;
  assign m00_couplers_to_axi_interconnect_0_ARREADY = M00_AXI_arready;
  assign m00_couplers_to_axi_interconnect_0_AWREADY = M00_AXI_awready;
  assign m00_couplers_to_axi_interconnect_0_BRESP = M00_AXI_bresp[1:0];
  assign m00_couplers_to_axi_interconnect_0_BVALID = M00_AXI_bvalid;
  assign m00_couplers_to_axi_interconnect_0_RDATA = M00_AXI_rdata[31:0];
  assign m00_couplers_to_axi_interconnect_0_RRESP = M00_AXI_rresp[1:0];
  assign m00_couplers_to_axi_interconnect_0_RVALID = M00_AXI_rvalid;
  assign m00_couplers_to_axi_interconnect_0_WREADY = M00_AXI_wready;
  assign m01_couplers_to_axi_interconnect_0_ARREADY = M01_AXI_arready;
  assign m01_couplers_to_axi_interconnect_0_AWREADY = M01_AXI_awready;
  assign m01_couplers_to_axi_interconnect_0_BRESP = M01_AXI_bresp[1:0];
  assign m01_couplers_to_axi_interconnect_0_BVALID = M01_AXI_bvalid;
  assign m01_couplers_to_axi_interconnect_0_RDATA = M01_AXI_rdata[31:0];
  assign m01_couplers_to_axi_interconnect_0_RRESP = M01_AXI_rresp[1:0];
  assign m01_couplers_to_axi_interconnect_0_RVALID = M01_AXI_rvalid;
  assign m01_couplers_to_axi_interconnect_0_WREADY = M01_AXI_wready;
  assign m02_couplers_to_axi_interconnect_0_ARREADY = M02_AXI_arready[0];
  assign m02_couplers_to_axi_interconnect_0_AWREADY = M02_AXI_awready[0];
  assign m02_couplers_to_axi_interconnect_0_BRESP = M02_AXI_bresp[1:0];
  assign m02_couplers_to_axi_interconnect_0_BVALID = M02_AXI_bvalid[0];
  assign m02_couplers_to_axi_interconnect_0_RDATA = M02_AXI_rdata[31:0];
  assign m02_couplers_to_axi_interconnect_0_RRESP = M02_AXI_rresp[1:0];
  assign m02_couplers_to_axi_interconnect_0_RVALID = M02_AXI_rvalid[0];
  assign m02_couplers_to_axi_interconnect_0_WREADY = M02_AXI_wready[0];
  m00_couplers_imp_1CA5Z32 m00_couplers
       (.M_ACLK(M00_ACLK_1),
        .M_ARESETN(M00_ARESETN_1),
        .M_AXI_araddr(m00_couplers_to_axi_interconnect_0_ARADDR),
        .M_AXI_arready(m00_couplers_to_axi_interconnect_0_ARREADY),
        .M_AXI_arvalid(m00_couplers_to_axi_interconnect_0_ARVALID),
        .M_AXI_awaddr(m00_couplers_to_axi_interconnect_0_AWADDR),
        .M_AXI_awready(m00_couplers_to_axi_interconnect_0_AWREADY),
        .M_AXI_awvalid(m00_couplers_to_axi_interconnect_0_AWVALID),
        .M_AXI_bready(m00_couplers_to_axi_interconnect_0_BREADY),
        .M_AXI_bresp(m00_couplers_to_axi_interconnect_0_BRESP),
        .M_AXI_bvalid(m00_couplers_to_axi_interconnect_0_BVALID),
        .M_AXI_rdata(m00_couplers_to_axi_interconnect_0_RDATA),
        .M_AXI_rready(m00_couplers_to_axi_interconnect_0_RREADY),
        .M_AXI_rresp(m00_couplers_to_axi_interconnect_0_RRESP),
        .M_AXI_rvalid(m00_couplers_to_axi_interconnect_0_RVALID),
        .M_AXI_wdata(m00_couplers_to_axi_interconnect_0_WDATA),
        .M_AXI_wready(m00_couplers_to_axi_interconnect_0_WREADY),
        .M_AXI_wstrb(m00_couplers_to_axi_interconnect_0_WSTRB),
        .M_AXI_wvalid(m00_couplers_to_axi_interconnect_0_WVALID),
        .S_ACLK(axi_interconnect_0_ACLK_net),
        .S_ARESETN(axi_interconnect_0_ARESETN_net),
        .S_AXI_araddr(xbar_to_m00_couplers_ARADDR),
        .S_AXI_arready(xbar_to_m00_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m00_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m00_couplers_AWADDR),
        .S_AXI_awready(xbar_to_m00_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m00_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m00_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m00_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m00_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m00_couplers_RDATA),
        .S_AXI_rready(xbar_to_m00_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m00_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m00_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m00_couplers_WDATA),
        .S_AXI_wready(xbar_to_m00_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m00_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m00_couplers_WVALID));
  m01_couplers_imp_I4GRPB m01_couplers
       (.M_ACLK(M01_ACLK_1),
        .M_ARESETN(M01_ARESETN_1),
        .M_AXI_araddr(m01_couplers_to_axi_interconnect_0_ARADDR),
        .M_AXI_arready(m01_couplers_to_axi_interconnect_0_ARREADY),
        .M_AXI_arvalid(m01_couplers_to_axi_interconnect_0_ARVALID),
        .M_AXI_awaddr(m01_couplers_to_axi_interconnect_0_AWADDR),
        .M_AXI_awready(m01_couplers_to_axi_interconnect_0_AWREADY),
        .M_AXI_awvalid(m01_couplers_to_axi_interconnect_0_AWVALID),
        .M_AXI_bready(m01_couplers_to_axi_interconnect_0_BREADY),
        .M_AXI_bresp(m01_couplers_to_axi_interconnect_0_BRESP),
        .M_AXI_bvalid(m01_couplers_to_axi_interconnect_0_BVALID),
        .M_AXI_rdata(m01_couplers_to_axi_interconnect_0_RDATA),
        .M_AXI_rready(m01_couplers_to_axi_interconnect_0_RREADY),
        .M_AXI_rresp(m01_couplers_to_axi_interconnect_0_RRESP),
        .M_AXI_rvalid(m01_couplers_to_axi_interconnect_0_RVALID),
        .M_AXI_wdata(m01_couplers_to_axi_interconnect_0_WDATA),
        .M_AXI_wready(m01_couplers_to_axi_interconnect_0_WREADY),
        .M_AXI_wstrb(m01_couplers_to_axi_interconnect_0_WSTRB),
        .M_AXI_wvalid(m01_couplers_to_axi_interconnect_0_WVALID),
        .S_ACLK(axi_interconnect_0_ACLK_net),
        .S_ARESETN(axi_interconnect_0_ARESETN_net),
        .S_AXI_araddr(xbar_to_m01_couplers_ARADDR),
        .S_AXI_arready(xbar_to_m01_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m01_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m01_couplers_AWADDR),
        .S_AXI_awready(xbar_to_m01_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m01_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m01_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m01_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m01_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m01_couplers_RDATA),
        .S_AXI_rready(xbar_to_m01_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m01_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m01_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m01_couplers_WDATA),
        .S_AXI_wready(xbar_to_m01_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m01_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m01_couplers_WVALID));
  m02_couplers_imp_1BOGR4T m02_couplers
       (.M_ACLK(M02_ACLK_1),
        .M_ARESETN(M02_ARESETN_1),
        .M_AXI_araddr(m02_couplers_to_axi_interconnect_0_ARADDR),
        .M_AXI_arready(m02_couplers_to_axi_interconnect_0_ARREADY),
        .M_AXI_arvalid(m02_couplers_to_axi_interconnect_0_ARVALID),
        .M_AXI_awaddr(m02_couplers_to_axi_interconnect_0_AWADDR),
        .M_AXI_awready(m02_couplers_to_axi_interconnect_0_AWREADY),
        .M_AXI_awvalid(m02_couplers_to_axi_interconnect_0_AWVALID),
        .M_AXI_bready(m02_couplers_to_axi_interconnect_0_BREADY),
        .M_AXI_bresp(m02_couplers_to_axi_interconnect_0_BRESP),
        .M_AXI_bvalid(m02_couplers_to_axi_interconnect_0_BVALID),
        .M_AXI_rdata(m02_couplers_to_axi_interconnect_0_RDATA),
        .M_AXI_rready(m02_couplers_to_axi_interconnect_0_RREADY),
        .M_AXI_rresp(m02_couplers_to_axi_interconnect_0_RRESP),
        .M_AXI_rvalid(m02_couplers_to_axi_interconnect_0_RVALID),
        .M_AXI_wdata(m02_couplers_to_axi_interconnect_0_WDATA),
        .M_AXI_wready(m02_couplers_to_axi_interconnect_0_WREADY),
        .M_AXI_wstrb(m02_couplers_to_axi_interconnect_0_WSTRB),
        .M_AXI_wvalid(m02_couplers_to_axi_interconnect_0_WVALID),
        .S_ACLK(axi_interconnect_0_ACLK_net),
        .S_ARESETN(axi_interconnect_0_ARESETN_net),
        .S_AXI_araddr(xbar_to_m02_couplers_ARADDR),
        .S_AXI_arready(xbar_to_m02_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m02_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m02_couplers_AWADDR),
        .S_AXI_awready(xbar_to_m02_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m02_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m02_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m02_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m02_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m02_couplers_RDATA),
        .S_AXI_rready(xbar_to_m02_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m02_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m02_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m02_couplers_WDATA),
        .S_AXI_wready(xbar_to_m02_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m02_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m02_couplers_WVALID));
  s00_couplers_imp_O7FAN0 s00_couplers
       (.M_ACLK(axi_interconnect_0_ACLK_net),
        .M_ARESETN(axi_interconnect_0_ARESETN_net),
        .M_AXI_araddr(s00_couplers_to_xbar_ARADDR),
        .M_AXI_arprot(s00_couplers_to_xbar_ARPROT),
        .M_AXI_arready(s00_couplers_to_xbar_ARREADY),
        .M_AXI_arvalid(s00_couplers_to_xbar_ARVALID),
        .M_AXI_awaddr(s00_couplers_to_xbar_AWADDR),
        .M_AXI_awprot(s00_couplers_to_xbar_AWPROT),
        .M_AXI_awready(s00_couplers_to_xbar_AWREADY),
        .M_AXI_awvalid(s00_couplers_to_xbar_AWVALID),
        .M_AXI_bready(s00_couplers_to_xbar_BREADY),
        .M_AXI_bresp(s00_couplers_to_xbar_BRESP),
        .M_AXI_bvalid(s00_couplers_to_xbar_BVALID),
        .M_AXI_rdata(s00_couplers_to_xbar_RDATA),
        .M_AXI_rready(s00_couplers_to_xbar_RREADY),
        .M_AXI_rresp(s00_couplers_to_xbar_RRESP),
        .M_AXI_rvalid(s00_couplers_to_xbar_RVALID),
        .M_AXI_wdata(s00_couplers_to_xbar_WDATA),
        .M_AXI_wready(s00_couplers_to_xbar_WREADY),
        .M_AXI_wstrb(s00_couplers_to_xbar_WSTRB),
        .M_AXI_wvalid(s00_couplers_to_xbar_WVALID),
        .S_ACLK(S00_ACLK_1),
        .S_ARESETN(S00_ARESETN_1),
        .S_AXI_araddr(axi_interconnect_0_to_s00_couplers_ARADDR),
        .S_AXI_arburst(axi_interconnect_0_to_s00_couplers_ARBURST),
        .S_AXI_arcache(axi_interconnect_0_to_s00_couplers_ARCACHE),
        .S_AXI_arid(axi_interconnect_0_to_s00_couplers_ARID),
        .S_AXI_arlen(axi_interconnect_0_to_s00_couplers_ARLEN),
        .S_AXI_arlock(axi_interconnect_0_to_s00_couplers_ARLOCK),
        .S_AXI_arprot(axi_interconnect_0_to_s00_couplers_ARPROT),
        .S_AXI_arqos(axi_interconnect_0_to_s00_couplers_ARQOS),
        .S_AXI_arready(axi_interconnect_0_to_s00_couplers_ARREADY),
        .S_AXI_arsize(axi_interconnect_0_to_s00_couplers_ARSIZE),
        .S_AXI_arvalid(axi_interconnect_0_to_s00_couplers_ARVALID),
        .S_AXI_awaddr(axi_interconnect_0_to_s00_couplers_AWADDR),
        .S_AXI_awburst(axi_interconnect_0_to_s00_couplers_AWBURST),
        .S_AXI_awcache(axi_interconnect_0_to_s00_couplers_AWCACHE),
        .S_AXI_awid(axi_interconnect_0_to_s00_couplers_AWID),
        .S_AXI_awlen(axi_interconnect_0_to_s00_couplers_AWLEN),
        .S_AXI_awlock(axi_interconnect_0_to_s00_couplers_AWLOCK),
        .S_AXI_awprot(axi_interconnect_0_to_s00_couplers_AWPROT),
        .S_AXI_awqos(axi_interconnect_0_to_s00_couplers_AWQOS),
        .S_AXI_awready(axi_interconnect_0_to_s00_couplers_AWREADY),
        .S_AXI_awsize(axi_interconnect_0_to_s00_couplers_AWSIZE),
        .S_AXI_awvalid(axi_interconnect_0_to_s00_couplers_AWVALID),
        .S_AXI_bid(axi_interconnect_0_to_s00_couplers_BID),
        .S_AXI_bready(axi_interconnect_0_to_s00_couplers_BREADY),
        .S_AXI_bresp(axi_interconnect_0_to_s00_couplers_BRESP),
        .S_AXI_bvalid(axi_interconnect_0_to_s00_couplers_BVALID),
        .S_AXI_rdata(axi_interconnect_0_to_s00_couplers_RDATA),
        .S_AXI_rid(axi_interconnect_0_to_s00_couplers_RID),
        .S_AXI_rlast(axi_interconnect_0_to_s00_couplers_RLAST),
        .S_AXI_rready(axi_interconnect_0_to_s00_couplers_RREADY),
        .S_AXI_rresp(axi_interconnect_0_to_s00_couplers_RRESP),
        .S_AXI_rvalid(axi_interconnect_0_to_s00_couplers_RVALID),
        .S_AXI_wdata(axi_interconnect_0_to_s00_couplers_WDATA),
        .S_AXI_wlast(axi_interconnect_0_to_s00_couplers_WLAST),
        .S_AXI_wready(axi_interconnect_0_to_s00_couplers_WREADY),
        .S_AXI_wstrb(axi_interconnect_0_to_s00_couplers_WSTRB),
        .S_AXI_wvalid(axi_interconnect_0_to_s00_couplers_WVALID));
  design_1_xbar_0 xbar
       (.aclk(axi_interconnect_0_ACLK_net),
        .aresetn(axi_interconnect_0_ARESETN_net),
        .m_axi_araddr({xbar_to_m02_couplers_ARADDR,xbar_to_m01_couplers_ARADDR,xbar_to_m00_couplers_ARADDR}),
        .m_axi_arready({xbar_to_m02_couplers_ARREADY,xbar_to_m01_couplers_ARREADY,xbar_to_m00_couplers_ARREADY}),
        .m_axi_arvalid({xbar_to_m02_couplers_ARVALID,xbar_to_m01_couplers_ARVALID,xbar_to_m00_couplers_ARVALID}),
        .m_axi_awaddr({xbar_to_m02_couplers_AWADDR,xbar_to_m01_couplers_AWADDR,xbar_to_m00_couplers_AWADDR}),
        .m_axi_awready({xbar_to_m02_couplers_AWREADY,xbar_to_m01_couplers_AWREADY,xbar_to_m00_couplers_AWREADY}),
        .m_axi_awvalid({xbar_to_m02_couplers_AWVALID,xbar_to_m01_couplers_AWVALID,xbar_to_m00_couplers_AWVALID}),
        .m_axi_bready({xbar_to_m02_couplers_BREADY,xbar_to_m01_couplers_BREADY,xbar_to_m00_couplers_BREADY}),
        .m_axi_bresp({xbar_to_m02_couplers_BRESP,xbar_to_m01_couplers_BRESP,xbar_to_m00_couplers_BRESP}),
        .m_axi_bvalid({xbar_to_m02_couplers_BVALID,xbar_to_m01_couplers_BVALID,xbar_to_m00_couplers_BVALID}),
        .m_axi_rdata({xbar_to_m02_couplers_RDATA,xbar_to_m01_couplers_RDATA,xbar_to_m00_couplers_RDATA}),
        .m_axi_rready({xbar_to_m02_couplers_RREADY,xbar_to_m01_couplers_RREADY,xbar_to_m00_couplers_RREADY}),
        .m_axi_rresp({xbar_to_m02_couplers_RRESP,xbar_to_m01_couplers_RRESP,xbar_to_m00_couplers_RRESP}),
        .m_axi_rvalid({xbar_to_m02_couplers_RVALID,xbar_to_m01_couplers_RVALID,xbar_to_m00_couplers_RVALID}),
        .m_axi_wdata({xbar_to_m02_couplers_WDATA,xbar_to_m01_couplers_WDATA,xbar_to_m00_couplers_WDATA}),
        .m_axi_wready({xbar_to_m02_couplers_WREADY,xbar_to_m01_couplers_WREADY,xbar_to_m00_couplers_WREADY}),
        .m_axi_wstrb({xbar_to_m02_couplers_WSTRB,xbar_to_m01_couplers_WSTRB,xbar_to_m00_couplers_WSTRB}),
        .m_axi_wvalid({xbar_to_m02_couplers_WVALID,xbar_to_m01_couplers_WVALID,xbar_to_m00_couplers_WVALID}),
        .s_axi_araddr(s00_couplers_to_xbar_ARADDR),
        .s_axi_arprot(s00_couplers_to_xbar_ARPROT),
        .s_axi_arready(s00_couplers_to_xbar_ARREADY),
        .s_axi_arvalid(s00_couplers_to_xbar_ARVALID),
        .s_axi_awaddr(s00_couplers_to_xbar_AWADDR),
        .s_axi_awprot(s00_couplers_to_xbar_AWPROT),
        .s_axi_awready(s00_couplers_to_xbar_AWREADY),
        .s_axi_awvalid(s00_couplers_to_xbar_AWVALID),
        .s_axi_bready(s00_couplers_to_xbar_BREADY),
        .s_axi_bresp(s00_couplers_to_xbar_BRESP),
        .s_axi_bvalid(s00_couplers_to_xbar_BVALID),
        .s_axi_rdata(s00_couplers_to_xbar_RDATA),
        .s_axi_rready(s00_couplers_to_xbar_RREADY),
        .s_axi_rresp(s00_couplers_to_xbar_RRESP),
        .s_axi_rvalid(s00_couplers_to_xbar_RVALID),
        .s_axi_wdata(s00_couplers_to_xbar_WDATA),
        .s_axi_wready(s00_couplers_to_xbar_WREADY),
        .s_axi_wstrb(s00_couplers_to_xbar_WSTRB),
        .s_axi_wvalid(s00_couplers_to_xbar_WVALID));
endmodule

module design_1_zynq_ultra_ps_e_0_axi_periph_0
   (ACLK,
    ARESETN,
    M00_ACLK,
    M00_ARESETN,
    M00_AXI_araddr,
    M00_AXI_arready,
    M00_AXI_arvalid,
    M00_AXI_awaddr,
    M00_AXI_awready,
    M00_AXI_awvalid,
    M00_AXI_bready,
    M00_AXI_bresp,
    M00_AXI_bvalid,
    M00_AXI_rdata,
    M00_AXI_rready,
    M00_AXI_rresp,
    M00_AXI_rvalid,
    M00_AXI_wdata,
    M00_AXI_wready,
    M00_AXI_wstrb,
    M00_AXI_wvalid,
    M01_ACLK,
    M01_ARESETN,
    M01_AXI_araddr,
    M01_AXI_arready,
    M01_AXI_arvalid,
    M01_AXI_awaddr,
    M01_AXI_awready,
    M01_AXI_awvalid,
    M01_AXI_bready,
    M01_AXI_bvalid,
    M01_AXI_rdata,
    M01_AXI_rready,
    M01_AXI_rvalid,
    M01_AXI_wdata,
    M01_AXI_wready,
    M01_AXI_wvalid,
    M02_ACLK,
    M02_ARESETN,
    M02_AXI_araddr,
    M02_AXI_arready,
    M02_AXI_arvalid,
    M02_AXI_awaddr,
    M02_AXI_awready,
    M02_AXI_awvalid,
    M02_AXI_bready,
    M02_AXI_bresp,
    M02_AXI_bvalid,
    M02_AXI_rdata,
    M02_AXI_rready,
    M02_AXI_rresp,
    M02_AXI_rvalid,
    M02_AXI_wdata,
    M02_AXI_wready,
    M02_AXI_wstrb,
    M02_AXI_wvalid,
    M03_ACLK,
    M03_ARESETN,
    M03_AXI_araddr,
    M03_AXI_arready,
    M03_AXI_arvalid,
    M03_AXI_awaddr,
    M03_AXI_awready,
    M03_AXI_awvalid,
    M03_AXI_bready,
    M03_AXI_bresp,
    M03_AXI_bvalid,
    M03_AXI_rdata,
    M03_AXI_rready,
    M03_AXI_rresp,
    M03_AXI_rvalid,
    M03_AXI_wdata,
    M03_AXI_wready,
    M03_AXI_wstrb,
    M03_AXI_wvalid,
    M04_ACLK,
    M04_ARESETN,
    M04_AXI_araddr,
    M04_AXI_arready,
    M04_AXI_arvalid,
    M04_AXI_awaddr,
    M04_AXI_awready,
    M04_AXI_awvalid,
    M04_AXI_bready,
    M04_AXI_bvalid,
    M04_AXI_rdata,
    M04_AXI_rready,
    M04_AXI_rvalid,
    M04_AXI_wdata,
    M04_AXI_wready,
    M04_AXI_wvalid,
    M05_ACLK,
    M05_ARESETN,
    M05_AXI_araddr,
    M05_AXI_arready,
    M05_AXI_arvalid,
    M05_AXI_awaddr,
    M05_AXI_awready,
    M05_AXI_awvalid,
    M05_AXI_bready,
    M05_AXI_bresp,
    M05_AXI_bvalid,
    M05_AXI_rdata,
    M05_AXI_rready,
    M05_AXI_rresp,
    M05_AXI_rvalid,
    M05_AXI_wdata,
    M05_AXI_wready,
    M05_AXI_wstrb,
    M05_AXI_wvalid,
    M06_ACLK,
    M06_ARESETN,
    M06_AXI_araddr,
    M06_AXI_arready,
    M06_AXI_arvalid,
    M06_AXI_awaddr,
    M06_AXI_awready,
    M06_AXI_awvalid,
    M06_AXI_bready,
    M06_AXI_bresp,
    M06_AXI_bvalid,
    M06_AXI_rdata,
    M06_AXI_rready,
    M06_AXI_rresp,
    M06_AXI_rvalid,
    M06_AXI_wdata,
    M06_AXI_wready,
    M06_AXI_wstrb,
    M06_AXI_wvalid,
    M07_ACLK,
    M07_ARESETN,
    M07_AXI_araddr,
    M07_AXI_arready,
    M07_AXI_arvalid,
    M07_AXI_awaddr,
    M07_AXI_awready,
    M07_AXI_awvalid,
    M07_AXI_bready,
    M07_AXI_bresp,
    M07_AXI_bvalid,
    M07_AXI_rdata,
    M07_AXI_rready,
    M07_AXI_rresp,
    M07_AXI_rvalid,
    M07_AXI_wdata,
    M07_AXI_wready,
    M07_AXI_wstrb,
    M07_AXI_wvalid,
    M08_ACLK,
    M08_ARESETN,
    M08_AXI_araddr,
    M08_AXI_arready,
    M08_AXI_arvalid,
    M08_AXI_awaddr,
    M08_AXI_awready,
    M08_AXI_awvalid,
    M08_AXI_bready,
    M08_AXI_bresp,
    M08_AXI_bvalid,
    M08_AXI_rdata,
    M08_AXI_rready,
    M08_AXI_rresp,
    M08_AXI_rvalid,
    M08_AXI_wdata,
    M08_AXI_wready,
    M08_AXI_wstrb,
    M08_AXI_wvalid,
    M09_ACLK,
    M09_ARESETN,
    M09_AXI_araddr,
    M09_AXI_arready,
    M09_AXI_arvalid,
    M09_AXI_awaddr,
    M09_AXI_awready,
    M09_AXI_awvalid,
    M09_AXI_bready,
    M09_AXI_bresp,
    M09_AXI_bvalid,
    M09_AXI_rdata,
    M09_AXI_rready,
    M09_AXI_rresp,
    M09_AXI_rvalid,
    M09_AXI_wdata,
    M09_AXI_wready,
    M09_AXI_wstrb,
    M09_AXI_wvalid,
    M10_ACLK,
    M10_ARESETN,
    M10_AXI_araddr,
    M10_AXI_arready,
    M10_AXI_arvalid,
    M10_AXI_awaddr,
    M10_AXI_awready,
    M10_AXI_awvalid,
    M10_AXI_bready,
    M10_AXI_bresp,
    M10_AXI_bvalid,
    M10_AXI_rdata,
    M10_AXI_rready,
    M10_AXI_rresp,
    M10_AXI_rvalid,
    M10_AXI_wdata,
    M10_AXI_wready,
    M10_AXI_wstrb,
    M10_AXI_wvalid,
    S00_ACLK,
    S00_ARESETN,
    S00_AXI_araddr,
    S00_AXI_arburst,
    S00_AXI_arcache,
    S00_AXI_arid,
    S00_AXI_arlen,
    S00_AXI_arlock,
    S00_AXI_arprot,
    S00_AXI_arqos,
    S00_AXI_arready,
    S00_AXI_arsize,
    S00_AXI_aruser,
    S00_AXI_arvalid,
    S00_AXI_awaddr,
    S00_AXI_awburst,
    S00_AXI_awcache,
    S00_AXI_awid,
    S00_AXI_awlen,
    S00_AXI_awlock,
    S00_AXI_awprot,
    S00_AXI_awqos,
    S00_AXI_awready,
    S00_AXI_awsize,
    S00_AXI_awuser,
    S00_AXI_awvalid,
    S00_AXI_bid,
    S00_AXI_bready,
    S00_AXI_bresp,
    S00_AXI_bvalid,
    S00_AXI_rdata,
    S00_AXI_rid,
    S00_AXI_rlast,
    S00_AXI_rready,
    S00_AXI_rresp,
    S00_AXI_rvalid,
    S00_AXI_wdata,
    S00_AXI_wlast,
    S00_AXI_wready,
    S00_AXI_wstrb,
    S00_AXI_wvalid);
  input ACLK;
  input ARESETN;
  input M00_ACLK;
  input M00_ARESETN;
  output [7:0]M00_AXI_araddr;
  input M00_AXI_arready;
  output M00_AXI_arvalid;
  output [7:0]M00_AXI_awaddr;
  input M00_AXI_awready;
  output M00_AXI_awvalid;
  output M00_AXI_bready;
  input [1:0]M00_AXI_bresp;
  input M00_AXI_bvalid;
  input [31:0]M00_AXI_rdata;
  output M00_AXI_rready;
  input [1:0]M00_AXI_rresp;
  input M00_AXI_rvalid;
  output [31:0]M00_AXI_wdata;
  input M00_AXI_wready;
  output [3:0]M00_AXI_wstrb;
  output M00_AXI_wvalid;
  input M01_ACLK;
  input M01_ARESETN;
  output [17:0]M01_AXI_araddr;
  input M01_AXI_arready;
  output M01_AXI_arvalid;
  output [17:0]M01_AXI_awaddr;
  input M01_AXI_awready;
  output M01_AXI_awvalid;
  output M01_AXI_bready;
  input M01_AXI_bvalid;
  input [31:0]M01_AXI_rdata;
  output M01_AXI_rready;
  input M01_AXI_rvalid;
  output [31:0]M01_AXI_wdata;
  input M01_AXI_wready;
  output M01_AXI_wvalid;
  input M02_ACLK;
  input M02_ARESETN;
  output [5:0]M02_AXI_araddr;
  input M02_AXI_arready;
  output M02_AXI_arvalid;
  output [5:0]M02_AXI_awaddr;
  input M02_AXI_awready;
  output M02_AXI_awvalid;
  output M02_AXI_bready;
  input [1:0]M02_AXI_bresp;
  input M02_AXI_bvalid;
  input [31:0]M02_AXI_rdata;
  output M02_AXI_rready;
  input [1:0]M02_AXI_rresp;
  input M02_AXI_rvalid;
  output [31:0]M02_AXI_wdata;
  input M02_AXI_wready;
  output [3:0]M02_AXI_wstrb;
  output M02_AXI_wvalid;
  input M03_ACLK;
  input M03_ARESETN;
  output [5:0]M03_AXI_araddr;
  input M03_AXI_arready;
  output M03_AXI_arvalid;
  output [5:0]M03_AXI_awaddr;
  input M03_AXI_awready;
  output M03_AXI_awvalid;
  output M03_AXI_bready;
  input [1:0]M03_AXI_bresp;
  input M03_AXI_bvalid;
  input [31:0]M03_AXI_rdata;
  output M03_AXI_rready;
  input [1:0]M03_AXI_rresp;
  input M03_AXI_rvalid;
  output [31:0]M03_AXI_wdata;
  input M03_AXI_wready;
  output [3:0]M03_AXI_wstrb;
  output M03_AXI_wvalid;
  input M04_ACLK;
  input M04_ARESETN;
  output [17:0]M04_AXI_araddr;
  input M04_AXI_arready;
  output M04_AXI_arvalid;
  output [17:0]M04_AXI_awaddr;
  input M04_AXI_awready;
  output M04_AXI_awvalid;
  output M04_AXI_bready;
  input M04_AXI_bvalid;
  input [31:0]M04_AXI_rdata;
  output M04_AXI_rready;
  input M04_AXI_rvalid;
  output [31:0]M04_AXI_wdata;
  input M04_AXI_wready;
  output M04_AXI_wvalid;
  input M05_ACLK;
  input M05_ARESETN;
  output [6:0]M05_AXI_araddr;
  input M05_AXI_arready;
  output M05_AXI_arvalid;
  output [6:0]M05_AXI_awaddr;
  input M05_AXI_awready;
  output M05_AXI_awvalid;
  output M05_AXI_bready;
  input [1:0]M05_AXI_bresp;
  input M05_AXI_bvalid;
  input [31:0]M05_AXI_rdata;
  output M05_AXI_rready;
  input [1:0]M05_AXI_rresp;
  input M05_AXI_rvalid;
  output [31:0]M05_AXI_wdata;
  input M05_AXI_wready;
  output [3:0]M05_AXI_wstrb;
  output M05_AXI_wvalid;
  input M06_ACLK;
  input M06_ARESETN;
  output [8:0]M06_AXI_araddr;
  input M06_AXI_arready;
  output M06_AXI_arvalid;
  output [8:0]M06_AXI_awaddr;
  input M06_AXI_awready;
  output M06_AXI_awvalid;
  output M06_AXI_bready;
  input [1:0]M06_AXI_bresp;
  input M06_AXI_bvalid;
  input [31:0]M06_AXI_rdata;
  output M06_AXI_rready;
  input [1:0]M06_AXI_rresp;
  input M06_AXI_rvalid;
  output [31:0]M06_AXI_wdata;
  input M06_AXI_wready;
  output [3:0]M06_AXI_wstrb;
  output M06_AXI_wvalid;
  input M07_ACLK;
  input M07_ARESETN;
  output [5:0]M07_AXI_araddr;
  input M07_AXI_arready;
  output M07_AXI_arvalid;
  output [5:0]M07_AXI_awaddr;
  input M07_AXI_awready;
  output M07_AXI_awvalid;
  output M07_AXI_bready;
  input [1:0]M07_AXI_bresp;
  input M07_AXI_bvalid;
  input [31:0]M07_AXI_rdata;
  output M07_AXI_rready;
  input [1:0]M07_AXI_rresp;
  input M07_AXI_rvalid;
  output [31:0]M07_AXI_wdata;
  input M07_AXI_wready;
  output [3:0]M07_AXI_wstrb;
  output M07_AXI_wvalid;
  input M08_ACLK;
  input M08_ARESETN;
  output [5:0]M08_AXI_araddr;
  input M08_AXI_arready;
  output M08_AXI_arvalid;
  output [5:0]M08_AXI_awaddr;
  input M08_AXI_awready;
  output M08_AXI_awvalid;
  output M08_AXI_bready;
  input [1:0]M08_AXI_bresp;
  input M08_AXI_bvalid;
  input [31:0]M08_AXI_rdata;
  output M08_AXI_rready;
  input [1:0]M08_AXI_rresp;
  input M08_AXI_rvalid;
  output [31:0]M08_AXI_wdata;
  input M08_AXI_wready;
  output [3:0]M08_AXI_wstrb;
  output M08_AXI_wvalid;
  input M09_ACLK;
  input M09_ARESETN;
  output [8:0]M09_AXI_araddr;
  input M09_AXI_arready;
  output M09_AXI_arvalid;
  output [8:0]M09_AXI_awaddr;
  input M09_AXI_awready;
  output M09_AXI_awvalid;
  output M09_AXI_bready;
  input [1:0]M09_AXI_bresp;
  input M09_AXI_bvalid;
  input [31:0]M09_AXI_rdata;
  output M09_AXI_rready;
  input [1:0]M09_AXI_rresp;
  input M09_AXI_rvalid;
  output [31:0]M09_AXI_wdata;
  input M09_AXI_wready;
  output [3:0]M09_AXI_wstrb;
  output M09_AXI_wvalid;
  input M10_ACLK;
  input M10_ARESETN;
  output [8:0]M10_AXI_araddr;
  input M10_AXI_arready;
  output M10_AXI_arvalid;
  output [8:0]M10_AXI_awaddr;
  input M10_AXI_awready;
  output M10_AXI_awvalid;
  output M10_AXI_bready;
  input [1:0]M10_AXI_bresp;
  input M10_AXI_bvalid;
  input [31:0]M10_AXI_rdata;
  output M10_AXI_rready;
  input [1:0]M10_AXI_rresp;
  input M10_AXI_rvalid;
  output [31:0]M10_AXI_wdata;
  input M10_AXI_wready;
  output [3:0]M10_AXI_wstrb;
  output M10_AXI_wvalid;
  input S00_ACLK;
  input S00_ARESETN;
  input [39:0]S00_AXI_araddr;
  input [1:0]S00_AXI_arburst;
  input [3:0]S00_AXI_arcache;
  input [15:0]S00_AXI_arid;
  input [7:0]S00_AXI_arlen;
  input [0:0]S00_AXI_arlock;
  input [2:0]S00_AXI_arprot;
  input [3:0]S00_AXI_arqos;
  output S00_AXI_arready;
  input [2:0]S00_AXI_arsize;
  input [15:0]S00_AXI_aruser;
  input S00_AXI_arvalid;
  input [39:0]S00_AXI_awaddr;
  input [1:0]S00_AXI_awburst;
  input [3:0]S00_AXI_awcache;
  input [15:0]S00_AXI_awid;
  input [7:0]S00_AXI_awlen;
  input [0:0]S00_AXI_awlock;
  input [2:0]S00_AXI_awprot;
  input [3:0]S00_AXI_awqos;
  output S00_AXI_awready;
  input [2:0]S00_AXI_awsize;
  input [15:0]S00_AXI_awuser;
  input S00_AXI_awvalid;
  output [15:0]S00_AXI_bid;
  input S00_AXI_bready;
  output [1:0]S00_AXI_bresp;
  output S00_AXI_bvalid;
  output [127:0]S00_AXI_rdata;
  output [15:0]S00_AXI_rid;
  output S00_AXI_rlast;
  input S00_AXI_rready;
  output [1:0]S00_AXI_rresp;
  output S00_AXI_rvalid;
  input [127:0]S00_AXI_wdata;
  input S00_AXI_wlast;
  output S00_AXI_wready;
  input [15:0]S00_AXI_wstrb;
  input S00_AXI_wvalid;

  wire M00_ACLK_1;
  wire M00_ARESETN_1;
  wire M01_ACLK_1;
  wire M01_ARESETN_1;
  wire M02_ACLK_1;
  wire M02_ARESETN_1;
  wire M03_ACLK_1;
  wire M03_ARESETN_1;
  wire M04_ACLK_1;
  wire M04_ARESETN_1;
  wire M05_ACLK_1;
  wire M05_ARESETN_1;
  wire M06_ACLK_1;
  wire M06_ARESETN_1;
  wire M07_ACLK_1;
  wire M07_ARESETN_1;
  wire M08_ACLK_1;
  wire M08_ARESETN_1;
  wire M09_ACLK_1;
  wire M09_ARESETN_1;
  wire M10_ACLK_1;
  wire M10_ARESETN_1;
  wire S00_ACLK_1;
  wire S00_ARESETN_1;
  wire [7:0]m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [7:0]m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [17:0]m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [17:0]m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [5:0]m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [5:0]m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [5:0]m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [5:0]m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [17:0]m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [17:0]m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [6:0]m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [6:0]m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [8:0]m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [8:0]m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [5:0]m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [5:0]m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [5:0]m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [5:0]m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [8:0]m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [8:0]m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [8:0]m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  wire [8:0]m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  wire [1:0]m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID;
  wire [31:0]m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  wire [1:0]m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID;
  wire [31:0]m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY;
  wire [3:0]m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  wire m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  wire [39:0]s00_couplers_to_xbar_ARADDR;
  wire [2:0]s00_couplers_to_xbar_ARPROT;
  wire [0:0]s00_couplers_to_xbar_ARREADY;
  wire s00_couplers_to_xbar_ARVALID;
  wire [39:0]s00_couplers_to_xbar_AWADDR;
  wire [2:0]s00_couplers_to_xbar_AWPROT;
  wire [0:0]s00_couplers_to_xbar_AWREADY;
  wire s00_couplers_to_xbar_AWVALID;
  wire s00_couplers_to_xbar_BREADY;
  wire [1:0]s00_couplers_to_xbar_BRESP;
  wire [0:0]s00_couplers_to_xbar_BVALID;
  wire [31:0]s00_couplers_to_xbar_RDATA;
  wire s00_couplers_to_xbar_RREADY;
  wire [1:0]s00_couplers_to_xbar_RRESP;
  wire [0:0]s00_couplers_to_xbar_RVALID;
  wire [31:0]s00_couplers_to_xbar_WDATA;
  wire [0:0]s00_couplers_to_xbar_WREADY;
  wire [3:0]s00_couplers_to_xbar_WSTRB;
  wire s00_couplers_to_xbar_WVALID;
  wire [39:0]xbar_to_m00_couplers_ARADDR;
  wire [2:0]xbar_to_m00_couplers_ARPROT;
  wire xbar_to_m00_couplers_ARREADY;
  wire [0:0]xbar_to_m00_couplers_ARVALID;
  wire [39:0]xbar_to_m00_couplers_AWADDR;
  wire [2:0]xbar_to_m00_couplers_AWPROT;
  wire xbar_to_m00_couplers_AWREADY;
  wire [0:0]xbar_to_m00_couplers_AWVALID;
  wire [0:0]xbar_to_m00_couplers_BREADY;
  wire [1:0]xbar_to_m00_couplers_BRESP;
  wire xbar_to_m00_couplers_BVALID;
  wire [31:0]xbar_to_m00_couplers_RDATA;
  wire [0:0]xbar_to_m00_couplers_RREADY;
  wire [1:0]xbar_to_m00_couplers_RRESP;
  wire xbar_to_m00_couplers_RVALID;
  wire [31:0]xbar_to_m00_couplers_WDATA;
  wire xbar_to_m00_couplers_WREADY;
  wire [3:0]xbar_to_m00_couplers_WSTRB;
  wire [0:0]xbar_to_m00_couplers_WVALID;
  wire [79:40]xbar_to_m01_couplers_ARADDR;
  wire [5:3]xbar_to_m01_couplers_ARPROT;
  wire xbar_to_m01_couplers_ARREADY;
  wire [1:1]xbar_to_m01_couplers_ARVALID;
  wire [79:40]xbar_to_m01_couplers_AWADDR;
  wire [5:3]xbar_to_m01_couplers_AWPROT;
  wire xbar_to_m01_couplers_AWREADY;
  wire [1:1]xbar_to_m01_couplers_AWVALID;
  wire [1:1]xbar_to_m01_couplers_BREADY;
  wire [1:0]xbar_to_m01_couplers_BRESP;
  wire xbar_to_m01_couplers_BVALID;
  wire [31:0]xbar_to_m01_couplers_RDATA;
  wire [1:1]xbar_to_m01_couplers_RREADY;
  wire [1:0]xbar_to_m01_couplers_RRESP;
  wire xbar_to_m01_couplers_RVALID;
  wire [63:32]xbar_to_m01_couplers_WDATA;
  wire xbar_to_m01_couplers_WREADY;
  wire [7:4]xbar_to_m01_couplers_WSTRB;
  wire [1:1]xbar_to_m01_couplers_WVALID;
  wire [119:80]xbar_to_m02_couplers_ARADDR;
  wire [8:6]xbar_to_m02_couplers_ARPROT;
  wire xbar_to_m02_couplers_ARREADY;
  wire [2:2]xbar_to_m02_couplers_ARVALID;
  wire [119:80]xbar_to_m02_couplers_AWADDR;
  wire [8:6]xbar_to_m02_couplers_AWPROT;
  wire xbar_to_m02_couplers_AWREADY;
  wire [2:2]xbar_to_m02_couplers_AWVALID;
  wire [2:2]xbar_to_m02_couplers_BREADY;
  wire [1:0]xbar_to_m02_couplers_BRESP;
  wire xbar_to_m02_couplers_BVALID;
  wire [31:0]xbar_to_m02_couplers_RDATA;
  wire [2:2]xbar_to_m02_couplers_RREADY;
  wire [1:0]xbar_to_m02_couplers_RRESP;
  wire xbar_to_m02_couplers_RVALID;
  wire [95:64]xbar_to_m02_couplers_WDATA;
  wire xbar_to_m02_couplers_WREADY;
  wire [11:8]xbar_to_m02_couplers_WSTRB;
  wire [2:2]xbar_to_m02_couplers_WVALID;
  wire [159:120]xbar_to_m03_couplers_ARADDR;
  wire [11:9]xbar_to_m03_couplers_ARPROT;
  wire xbar_to_m03_couplers_ARREADY;
  wire [3:3]xbar_to_m03_couplers_ARVALID;
  wire [159:120]xbar_to_m03_couplers_AWADDR;
  wire [11:9]xbar_to_m03_couplers_AWPROT;
  wire xbar_to_m03_couplers_AWREADY;
  wire [3:3]xbar_to_m03_couplers_AWVALID;
  wire [3:3]xbar_to_m03_couplers_BREADY;
  wire [1:0]xbar_to_m03_couplers_BRESP;
  wire xbar_to_m03_couplers_BVALID;
  wire [31:0]xbar_to_m03_couplers_RDATA;
  wire [3:3]xbar_to_m03_couplers_RREADY;
  wire [1:0]xbar_to_m03_couplers_RRESP;
  wire xbar_to_m03_couplers_RVALID;
  wire [127:96]xbar_to_m03_couplers_WDATA;
  wire xbar_to_m03_couplers_WREADY;
  wire [15:12]xbar_to_m03_couplers_WSTRB;
  wire [3:3]xbar_to_m03_couplers_WVALID;
  wire [199:160]xbar_to_m04_couplers_ARADDR;
  wire [14:12]xbar_to_m04_couplers_ARPROT;
  wire xbar_to_m04_couplers_ARREADY;
  wire [4:4]xbar_to_m04_couplers_ARVALID;
  wire [199:160]xbar_to_m04_couplers_AWADDR;
  wire [14:12]xbar_to_m04_couplers_AWPROT;
  wire xbar_to_m04_couplers_AWREADY;
  wire [4:4]xbar_to_m04_couplers_AWVALID;
  wire [4:4]xbar_to_m04_couplers_BREADY;
  wire [1:0]xbar_to_m04_couplers_BRESP;
  wire xbar_to_m04_couplers_BVALID;
  wire [31:0]xbar_to_m04_couplers_RDATA;
  wire [4:4]xbar_to_m04_couplers_RREADY;
  wire [1:0]xbar_to_m04_couplers_RRESP;
  wire xbar_to_m04_couplers_RVALID;
  wire [159:128]xbar_to_m04_couplers_WDATA;
  wire xbar_to_m04_couplers_WREADY;
  wire [19:16]xbar_to_m04_couplers_WSTRB;
  wire [4:4]xbar_to_m04_couplers_WVALID;
  wire [239:200]xbar_to_m05_couplers_ARADDR;
  wire [17:15]xbar_to_m05_couplers_ARPROT;
  wire xbar_to_m05_couplers_ARREADY;
  wire [5:5]xbar_to_m05_couplers_ARVALID;
  wire [239:200]xbar_to_m05_couplers_AWADDR;
  wire [17:15]xbar_to_m05_couplers_AWPROT;
  wire xbar_to_m05_couplers_AWREADY;
  wire [5:5]xbar_to_m05_couplers_AWVALID;
  wire [5:5]xbar_to_m05_couplers_BREADY;
  wire [1:0]xbar_to_m05_couplers_BRESP;
  wire xbar_to_m05_couplers_BVALID;
  wire [31:0]xbar_to_m05_couplers_RDATA;
  wire [5:5]xbar_to_m05_couplers_RREADY;
  wire [1:0]xbar_to_m05_couplers_RRESP;
  wire xbar_to_m05_couplers_RVALID;
  wire [191:160]xbar_to_m05_couplers_WDATA;
  wire xbar_to_m05_couplers_WREADY;
  wire [23:20]xbar_to_m05_couplers_WSTRB;
  wire [5:5]xbar_to_m05_couplers_WVALID;
  wire [279:240]xbar_to_m06_couplers_ARADDR;
  wire [20:18]xbar_to_m06_couplers_ARPROT;
  wire xbar_to_m06_couplers_ARREADY;
  wire [6:6]xbar_to_m06_couplers_ARVALID;
  wire [279:240]xbar_to_m06_couplers_AWADDR;
  wire [20:18]xbar_to_m06_couplers_AWPROT;
  wire xbar_to_m06_couplers_AWREADY;
  wire [6:6]xbar_to_m06_couplers_AWVALID;
  wire [6:6]xbar_to_m06_couplers_BREADY;
  wire [1:0]xbar_to_m06_couplers_BRESP;
  wire xbar_to_m06_couplers_BVALID;
  wire [31:0]xbar_to_m06_couplers_RDATA;
  wire [6:6]xbar_to_m06_couplers_RREADY;
  wire [1:0]xbar_to_m06_couplers_RRESP;
  wire xbar_to_m06_couplers_RVALID;
  wire [223:192]xbar_to_m06_couplers_WDATA;
  wire xbar_to_m06_couplers_WREADY;
  wire [27:24]xbar_to_m06_couplers_WSTRB;
  wire [6:6]xbar_to_m06_couplers_WVALID;
  wire [319:280]xbar_to_m07_couplers_ARADDR;
  wire [23:21]xbar_to_m07_couplers_ARPROT;
  wire xbar_to_m07_couplers_ARREADY;
  wire [7:7]xbar_to_m07_couplers_ARVALID;
  wire [319:280]xbar_to_m07_couplers_AWADDR;
  wire [23:21]xbar_to_m07_couplers_AWPROT;
  wire xbar_to_m07_couplers_AWREADY;
  wire [7:7]xbar_to_m07_couplers_AWVALID;
  wire [7:7]xbar_to_m07_couplers_BREADY;
  wire [1:0]xbar_to_m07_couplers_BRESP;
  wire xbar_to_m07_couplers_BVALID;
  wire [31:0]xbar_to_m07_couplers_RDATA;
  wire [7:7]xbar_to_m07_couplers_RREADY;
  wire [1:0]xbar_to_m07_couplers_RRESP;
  wire xbar_to_m07_couplers_RVALID;
  wire [255:224]xbar_to_m07_couplers_WDATA;
  wire xbar_to_m07_couplers_WREADY;
  wire [31:28]xbar_to_m07_couplers_WSTRB;
  wire [7:7]xbar_to_m07_couplers_WVALID;
  wire [359:320]xbar_to_m08_couplers_ARADDR;
  wire [26:24]xbar_to_m08_couplers_ARPROT;
  wire xbar_to_m08_couplers_ARREADY;
  wire [8:8]xbar_to_m08_couplers_ARVALID;
  wire [359:320]xbar_to_m08_couplers_AWADDR;
  wire [26:24]xbar_to_m08_couplers_AWPROT;
  wire xbar_to_m08_couplers_AWREADY;
  wire [8:8]xbar_to_m08_couplers_AWVALID;
  wire [8:8]xbar_to_m08_couplers_BREADY;
  wire [1:0]xbar_to_m08_couplers_BRESP;
  wire xbar_to_m08_couplers_BVALID;
  wire [31:0]xbar_to_m08_couplers_RDATA;
  wire [8:8]xbar_to_m08_couplers_RREADY;
  wire [1:0]xbar_to_m08_couplers_RRESP;
  wire xbar_to_m08_couplers_RVALID;
  wire [287:256]xbar_to_m08_couplers_WDATA;
  wire xbar_to_m08_couplers_WREADY;
  wire [35:32]xbar_to_m08_couplers_WSTRB;
  wire [8:8]xbar_to_m08_couplers_WVALID;
  wire [399:360]xbar_to_m09_couplers_ARADDR;
  wire [29:27]xbar_to_m09_couplers_ARPROT;
  wire xbar_to_m09_couplers_ARREADY;
  wire [9:9]xbar_to_m09_couplers_ARVALID;
  wire [399:360]xbar_to_m09_couplers_AWADDR;
  wire [29:27]xbar_to_m09_couplers_AWPROT;
  wire xbar_to_m09_couplers_AWREADY;
  wire [9:9]xbar_to_m09_couplers_AWVALID;
  wire [9:9]xbar_to_m09_couplers_BREADY;
  wire [1:0]xbar_to_m09_couplers_BRESP;
  wire xbar_to_m09_couplers_BVALID;
  wire [31:0]xbar_to_m09_couplers_RDATA;
  wire [9:9]xbar_to_m09_couplers_RREADY;
  wire [1:0]xbar_to_m09_couplers_RRESP;
  wire xbar_to_m09_couplers_RVALID;
  wire [319:288]xbar_to_m09_couplers_WDATA;
  wire xbar_to_m09_couplers_WREADY;
  wire [39:36]xbar_to_m09_couplers_WSTRB;
  wire [9:9]xbar_to_m09_couplers_WVALID;
  wire [439:400]xbar_to_m10_couplers_ARADDR;
  wire [32:30]xbar_to_m10_couplers_ARPROT;
  wire xbar_to_m10_couplers_ARREADY;
  wire [10:10]xbar_to_m10_couplers_ARVALID;
  wire [439:400]xbar_to_m10_couplers_AWADDR;
  wire [32:30]xbar_to_m10_couplers_AWPROT;
  wire xbar_to_m10_couplers_AWREADY;
  wire [10:10]xbar_to_m10_couplers_AWVALID;
  wire [10:10]xbar_to_m10_couplers_BREADY;
  wire [1:0]xbar_to_m10_couplers_BRESP;
  wire xbar_to_m10_couplers_BVALID;
  wire [31:0]xbar_to_m10_couplers_RDATA;
  wire [10:10]xbar_to_m10_couplers_RREADY;
  wire [1:0]xbar_to_m10_couplers_RRESP;
  wire xbar_to_m10_couplers_RVALID;
  wire [351:320]xbar_to_m10_couplers_WDATA;
  wire xbar_to_m10_couplers_WREADY;
  wire [43:40]xbar_to_m10_couplers_WSTRB;
  wire [10:10]xbar_to_m10_couplers_WVALID;
  wire zynq_ultra_ps_e_0_axi_periph_ACLK_net;
  wire zynq_ultra_ps_e_0_axi_periph_ARESETN_net;
  wire [39:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARADDR;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARBURST;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARCACHE;
  wire [15:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARID;
  wire [7:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARLEN;
  wire [0:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARLOCK;
  wire [2:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARPROT;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARQOS;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARREADY;
  wire [2:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARSIZE;
  wire [15:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARUSER;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARVALID;
  wire [39:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWADDR;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWBURST;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWCACHE;
  wire [15:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWID;
  wire [7:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWLEN;
  wire [0:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWLOCK;
  wire [2:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWPROT;
  wire [3:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWQOS;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWREADY;
  wire [2:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWSIZE;
  wire [15:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWUSER;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWVALID;
  wire [15:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BID;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BRESP;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BVALID;
  wire [127:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RDATA;
  wire [15:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RID;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RLAST;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RREADY;
  wire [1:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RRESP;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RVALID;
  wire [127:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WDATA;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WLAST;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WREADY;
  wire [15:0]zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WSTRB;
  wire zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WVALID;

  assign M00_ACLK_1 = M00_ACLK;
  assign M00_ARESETN_1 = M00_ARESETN;
  assign M00_AXI_araddr[7:0] = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M00_AXI_arvalid = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M00_AXI_awaddr[7:0] = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M00_AXI_awvalid = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M00_AXI_bready = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M00_AXI_rready = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M00_AXI_wdata[31:0] = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M00_AXI_wstrb[3:0] = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M00_AXI_wvalid = m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M01_ACLK_1 = M01_ACLK;
  assign M01_ARESETN_1 = M01_ARESETN;
  assign M01_AXI_araddr[17:0] = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M01_AXI_arvalid = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M01_AXI_awaddr[17:0] = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M01_AXI_awvalid = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M01_AXI_bready = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M01_AXI_rready = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M01_AXI_wdata[31:0] = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M01_AXI_wvalid = m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M02_ACLK_1 = M02_ACLK;
  assign M02_ARESETN_1 = M02_ARESETN;
  assign M02_AXI_araddr[5:0] = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M02_AXI_arvalid = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M02_AXI_awaddr[5:0] = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M02_AXI_awvalid = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M02_AXI_bready = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M02_AXI_rready = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M02_AXI_wdata[31:0] = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M02_AXI_wstrb[3:0] = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M02_AXI_wvalid = m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M03_ACLK_1 = M03_ACLK;
  assign M03_ARESETN_1 = M03_ARESETN;
  assign M03_AXI_araddr[5:0] = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M03_AXI_arvalid = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M03_AXI_awaddr[5:0] = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M03_AXI_awvalid = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M03_AXI_bready = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M03_AXI_rready = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M03_AXI_wdata[31:0] = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M03_AXI_wstrb[3:0] = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M03_AXI_wvalid = m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M04_ACLK_1 = M04_ACLK;
  assign M04_ARESETN_1 = M04_ARESETN;
  assign M04_AXI_araddr[17:0] = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M04_AXI_arvalid = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M04_AXI_awaddr[17:0] = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M04_AXI_awvalid = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M04_AXI_bready = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M04_AXI_rready = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M04_AXI_wdata[31:0] = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M04_AXI_wvalid = m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M05_ACLK_1 = M05_ACLK;
  assign M05_ARESETN_1 = M05_ARESETN;
  assign M05_AXI_araddr[6:0] = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M05_AXI_arvalid = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M05_AXI_awaddr[6:0] = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M05_AXI_awvalid = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M05_AXI_bready = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M05_AXI_rready = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M05_AXI_wdata[31:0] = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M05_AXI_wstrb[3:0] = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M05_AXI_wvalid = m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M06_ACLK_1 = M06_ACLK;
  assign M06_ARESETN_1 = M06_ARESETN;
  assign M06_AXI_araddr[8:0] = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M06_AXI_arvalid = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M06_AXI_awaddr[8:0] = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M06_AXI_awvalid = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M06_AXI_bready = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M06_AXI_rready = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M06_AXI_wdata[31:0] = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M06_AXI_wstrb[3:0] = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M06_AXI_wvalid = m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M07_ACLK_1 = M07_ACLK;
  assign M07_ARESETN_1 = M07_ARESETN;
  assign M07_AXI_araddr[5:0] = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M07_AXI_arvalid = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M07_AXI_awaddr[5:0] = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M07_AXI_awvalid = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M07_AXI_bready = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M07_AXI_rready = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M07_AXI_wdata[31:0] = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M07_AXI_wstrb[3:0] = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M07_AXI_wvalid = m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M08_ACLK_1 = M08_ACLK;
  assign M08_ARESETN_1 = M08_ARESETN;
  assign M08_AXI_araddr[5:0] = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M08_AXI_arvalid = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M08_AXI_awaddr[5:0] = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M08_AXI_awvalid = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M08_AXI_bready = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M08_AXI_rready = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M08_AXI_wdata[31:0] = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M08_AXI_wstrb[3:0] = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M08_AXI_wvalid = m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M09_ACLK_1 = M09_ACLK;
  assign M09_ARESETN_1 = M09_ARESETN;
  assign M09_AXI_araddr[8:0] = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M09_AXI_arvalid = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M09_AXI_awaddr[8:0] = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M09_AXI_awvalid = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M09_AXI_bready = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M09_AXI_rready = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M09_AXI_wdata[31:0] = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M09_AXI_wstrb[3:0] = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M09_AXI_wvalid = m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign M10_ACLK_1 = M10_ACLK;
  assign M10_ARESETN_1 = M10_ARESETN;
  assign M10_AXI_araddr[8:0] = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR;
  assign M10_AXI_arvalid = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID;
  assign M10_AXI_awaddr[8:0] = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR;
  assign M10_AXI_awvalid = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID;
  assign M10_AXI_bready = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY;
  assign M10_AXI_rready = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY;
  assign M10_AXI_wdata[31:0] = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA;
  assign M10_AXI_wstrb[3:0] = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB;
  assign M10_AXI_wvalid = m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID;
  assign S00_ACLK_1 = S00_ACLK;
  assign S00_ARESETN_1 = S00_ARESETN;
  assign S00_AXI_arready = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARREADY;
  assign S00_AXI_awready = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWREADY;
  assign S00_AXI_bid[15:0] = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BID;
  assign S00_AXI_bresp[1:0] = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BRESP;
  assign S00_AXI_bvalid = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BVALID;
  assign S00_AXI_rdata[127:0] = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RDATA;
  assign S00_AXI_rid[15:0] = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RID;
  assign S00_AXI_rlast = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RLAST;
  assign S00_AXI_rresp[1:0] = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RRESP;
  assign S00_AXI_rvalid = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RVALID;
  assign S00_AXI_wready = zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WREADY;
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M00_AXI_arready;
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M00_AXI_awready;
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M00_AXI_bresp[1:0];
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M00_AXI_bvalid;
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M00_AXI_rdata[31:0];
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M00_AXI_rresp[1:0];
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M00_AXI_rvalid;
  assign m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M00_AXI_wready;
  assign m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M01_AXI_arready;
  assign m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M01_AXI_awready;
  assign m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M01_AXI_bvalid;
  assign m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M01_AXI_rdata[31:0];
  assign m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M01_AXI_rvalid;
  assign m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M01_AXI_wready;
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M02_AXI_arready;
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M02_AXI_awready;
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M02_AXI_bresp[1:0];
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M02_AXI_bvalid;
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M02_AXI_rdata[31:0];
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M02_AXI_rresp[1:0];
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M02_AXI_rvalid;
  assign m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M02_AXI_wready;
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M03_AXI_arready;
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M03_AXI_awready;
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M03_AXI_bresp[1:0];
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M03_AXI_bvalid;
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M03_AXI_rdata[31:0];
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M03_AXI_rresp[1:0];
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M03_AXI_rvalid;
  assign m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M03_AXI_wready;
  assign m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M04_AXI_arready;
  assign m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M04_AXI_awready;
  assign m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M04_AXI_bvalid;
  assign m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M04_AXI_rdata[31:0];
  assign m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M04_AXI_rvalid;
  assign m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M04_AXI_wready;
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M05_AXI_arready;
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M05_AXI_awready;
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M05_AXI_bresp[1:0];
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M05_AXI_bvalid;
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M05_AXI_rdata[31:0];
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M05_AXI_rresp[1:0];
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M05_AXI_rvalid;
  assign m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M05_AXI_wready;
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M06_AXI_arready;
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M06_AXI_awready;
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M06_AXI_bresp[1:0];
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M06_AXI_bvalid;
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M06_AXI_rdata[31:0];
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M06_AXI_rresp[1:0];
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M06_AXI_rvalid;
  assign m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M06_AXI_wready;
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M07_AXI_arready;
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M07_AXI_awready;
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M07_AXI_bresp[1:0];
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M07_AXI_bvalid;
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M07_AXI_rdata[31:0];
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M07_AXI_rresp[1:0];
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M07_AXI_rvalid;
  assign m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M07_AXI_wready;
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M08_AXI_arready;
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M08_AXI_awready;
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M08_AXI_bresp[1:0];
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M08_AXI_bvalid;
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M08_AXI_rdata[31:0];
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M08_AXI_rresp[1:0];
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M08_AXI_rvalid;
  assign m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M08_AXI_wready;
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M09_AXI_arready;
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M09_AXI_awready;
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M09_AXI_bresp[1:0];
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M09_AXI_bvalid;
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M09_AXI_rdata[31:0];
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M09_AXI_rresp[1:0];
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M09_AXI_rvalid;
  assign m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M09_AXI_wready;
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY = M10_AXI_arready;
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY = M10_AXI_awready;
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP = M10_AXI_bresp[1:0];
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID = M10_AXI_bvalid;
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA = M10_AXI_rdata[31:0];
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP = M10_AXI_rresp[1:0];
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID = M10_AXI_rvalid;
  assign m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY = M10_AXI_wready;
  assign zynq_ultra_ps_e_0_axi_periph_ACLK_net = ACLK;
  assign zynq_ultra_ps_e_0_axi_periph_ARESETN_net = ARESETN;
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARADDR = S00_AXI_araddr[39:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARBURST = S00_AXI_arburst[1:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARCACHE = S00_AXI_arcache[3:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARID = S00_AXI_arid[15:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARLEN = S00_AXI_arlen[7:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARLOCK = S00_AXI_arlock[0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARPROT = S00_AXI_arprot[2:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARQOS = S00_AXI_arqos[3:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARSIZE = S00_AXI_arsize[2:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARUSER = S00_AXI_aruser[15:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARVALID = S00_AXI_arvalid;
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWADDR = S00_AXI_awaddr[39:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWBURST = S00_AXI_awburst[1:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWCACHE = S00_AXI_awcache[3:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWID = S00_AXI_awid[15:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWLEN = S00_AXI_awlen[7:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWLOCK = S00_AXI_awlock[0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWPROT = S00_AXI_awprot[2:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWQOS = S00_AXI_awqos[3:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWSIZE = S00_AXI_awsize[2:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWUSER = S00_AXI_awuser[15:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWVALID = S00_AXI_awvalid;
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BREADY = S00_AXI_bready;
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RREADY = S00_AXI_rready;
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WDATA = S00_AXI_wdata[127:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WLAST = S00_AXI_wlast;
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WSTRB = S00_AXI_wstrb[15:0];
  assign zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WVALID = S00_AXI_wvalid;
  m00_couplers_imp_6WA1NC m00_couplers
       (.M_ACLK(M00_ACLK_1),
        .M_ARESETN(M00_ARESETN_1),
        .M_AXI_araddr(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m00_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m00_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m00_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m00_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m00_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m00_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m00_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m00_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m00_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m00_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m00_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m00_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m00_couplers_RDATA),
        .S_AXI_rready(xbar_to_m00_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m00_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m00_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m00_couplers_WDATA),
        .S_AXI_wready(xbar_to_m00_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m00_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m00_couplers_WVALID));
  m01_couplers_imp_1WOL2K9 m01_couplers
       (.M_ACLK(M01_ACLK_1),
        .M_ARESETN(M01_ARESETN_1),
        .M_AXI_araddr(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bvalid(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rvalid(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wvalid(m01_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m01_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m01_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m01_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m01_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m01_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m01_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m01_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m01_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m01_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m01_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m01_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m01_couplers_RDATA),
        .S_AXI_rready(xbar_to_m01_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m01_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m01_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m01_couplers_WDATA),
        .S_AXI_wready(xbar_to_m01_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m01_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m01_couplers_WVALID));
  m02_couplers_imp_829XSR m02_couplers
       (.M_ACLK(M02_ACLK_1),
        .M_ARESETN(M02_ARESETN_1),
        .M_AXI_araddr(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m02_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m02_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m02_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m02_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m02_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m02_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m02_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m02_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m02_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m02_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m02_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m02_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m02_couplers_RDATA),
        .S_AXI_rready(xbar_to_m02_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m02_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m02_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m02_couplers_WDATA),
        .S_AXI_wready(xbar_to_m02_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m02_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m02_couplers_WVALID));
  m03_couplers_imp_1V8XG3E m03_couplers
       (.M_ACLK(M03_ACLK_1),
        .M_ARESETN(M03_ARESETN_1),
        .M_AXI_araddr(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m03_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m03_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m03_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m03_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m03_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m03_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m03_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m03_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m03_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m03_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m03_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m03_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m03_couplers_RDATA),
        .S_AXI_rready(xbar_to_m03_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m03_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m03_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m03_couplers_WDATA),
        .S_AXI_wready(xbar_to_m03_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m03_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m03_couplers_WVALID));
  m04_couplers_imp_5EAXGE m04_couplers
       (.M_ACLK(M04_ACLK_1),
        .M_ARESETN(M04_ARESETN_1),
        .M_AXI_araddr(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bvalid(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rvalid(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wvalid(m04_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m04_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m04_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m04_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m04_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m04_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m04_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m04_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m04_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m04_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m04_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m04_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m04_couplers_RDATA),
        .S_AXI_rready(xbar_to_m04_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m04_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m04_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m04_couplers_WDATA),
        .S_AXI_wready(xbar_to_m04_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m04_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m04_couplers_WVALID));
  m05_couplers_imp_1XYGQBJ m05_couplers
       (.M_ACLK(M05_ACLK_1),
        .M_ARESETN(M05_ARESETN_1),
        .M_AXI_araddr(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m05_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m05_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m05_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m05_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m05_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m05_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m05_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m05_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m05_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m05_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m05_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m05_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m05_couplers_RDATA),
        .S_AXI_rready(xbar_to_m05_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m05_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m05_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m05_couplers_WDATA),
        .S_AXI_wready(xbar_to_m05_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m05_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m05_couplers_WVALID));
  m06_couplers_imp_6AAJBX m06_couplers
       (.M_ACLK(M06_ACLK_1),
        .M_ARESETN(M06_ARESETN_1),
        .M_AXI_araddr(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m06_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m06_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m06_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m06_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m06_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m06_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m06_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m06_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m06_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m06_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m06_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m06_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m06_couplers_RDATA),
        .S_AXI_rready(xbar_to_m06_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m06_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m06_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m06_couplers_WDATA),
        .S_AXI_wready(xbar_to_m06_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m06_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m06_couplers_WVALID));
  m07_couplers_imp_1XCR5J0 m07_couplers
       (.M_ACLK(M07_ACLK_1),
        .M_ARESETN(M07_ARESETN_1),
        .M_AXI_araddr(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m07_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m07_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m07_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m07_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m07_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m07_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m07_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m07_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m07_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m07_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m07_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m07_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m07_couplers_RDATA),
        .S_AXI_rready(xbar_to_m07_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m07_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m07_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m07_couplers_WDATA),
        .S_AXI_wready(xbar_to_m07_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m07_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m07_couplers_WVALID));
  m08_couplers_imp_4B8Q1G m08_couplers
       (.M_ACLK(M08_ACLK_1),
        .M_ARESETN(M08_ARESETN_1),
        .M_AXI_araddr(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m08_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m08_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m08_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m08_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m08_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m08_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m08_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m08_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m08_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m08_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m08_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m08_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m08_couplers_RDATA),
        .S_AXI_rready(xbar_to_m08_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m08_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m08_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m08_couplers_WDATA),
        .S_AXI_wready(xbar_to_m08_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m08_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m08_couplers_WVALID));
  m09_couplers_imp_1QDWHMD m09_couplers
       (.M_ACLK(M09_ACLK_1),
        .M_ARESETN(M09_ARESETN_1),
        .M_AXI_araddr(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m09_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m09_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m09_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m09_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m09_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m09_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m09_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m09_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m09_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m09_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m09_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m09_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m09_couplers_RDATA),
        .S_AXI_rready(xbar_to_m09_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m09_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m09_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m09_couplers_WDATA),
        .S_AXI_wready(xbar_to_m09_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m09_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m09_couplers_WVALID));
  m10_couplers_imp_1LHWVWG m10_couplers
       (.M_ACLK(M10_ACLK_1),
        .M_ARESETN(M10_ARESETN_1),
        .M_AXI_araddr(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARADDR),
        .M_AXI_arready(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARREADY),
        .M_AXI_arvalid(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_ARVALID),
        .M_AXI_awaddr(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWADDR),
        .M_AXI_awready(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWREADY),
        .M_AXI_awvalid(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_AWVALID),
        .M_AXI_bready(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BREADY),
        .M_AXI_bresp(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BRESP),
        .M_AXI_bvalid(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_BVALID),
        .M_AXI_rdata(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RDATA),
        .M_AXI_rready(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RREADY),
        .M_AXI_rresp(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RRESP),
        .M_AXI_rvalid(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_RVALID),
        .M_AXI_wdata(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WDATA),
        .M_AXI_wready(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WREADY),
        .M_AXI_wstrb(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WSTRB),
        .M_AXI_wvalid(m10_couplers_to_zynq_ultra_ps_e_0_axi_periph_WVALID),
        .S_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .S_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .S_AXI_araddr(xbar_to_m10_couplers_ARADDR),
        .S_AXI_arprot(xbar_to_m10_couplers_ARPROT),
        .S_AXI_arready(xbar_to_m10_couplers_ARREADY),
        .S_AXI_arvalid(xbar_to_m10_couplers_ARVALID),
        .S_AXI_awaddr(xbar_to_m10_couplers_AWADDR),
        .S_AXI_awprot(xbar_to_m10_couplers_AWPROT),
        .S_AXI_awready(xbar_to_m10_couplers_AWREADY),
        .S_AXI_awvalid(xbar_to_m10_couplers_AWVALID),
        .S_AXI_bready(xbar_to_m10_couplers_BREADY),
        .S_AXI_bresp(xbar_to_m10_couplers_BRESP),
        .S_AXI_bvalid(xbar_to_m10_couplers_BVALID),
        .S_AXI_rdata(xbar_to_m10_couplers_RDATA),
        .S_AXI_rready(xbar_to_m10_couplers_RREADY),
        .S_AXI_rresp(xbar_to_m10_couplers_RRESP),
        .S_AXI_rvalid(xbar_to_m10_couplers_RVALID),
        .S_AXI_wdata(xbar_to_m10_couplers_WDATA),
        .S_AXI_wready(xbar_to_m10_couplers_WREADY),
        .S_AXI_wstrb(xbar_to_m10_couplers_WSTRB),
        .S_AXI_wvalid(xbar_to_m10_couplers_WVALID));
  s00_couplers_imp_1QOFPGA s00_couplers
       (.M_ACLK(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .M_ARESETN(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .M_AXI_araddr(s00_couplers_to_xbar_ARADDR),
        .M_AXI_arprot(s00_couplers_to_xbar_ARPROT),
        .M_AXI_arready(s00_couplers_to_xbar_ARREADY),
        .M_AXI_arvalid(s00_couplers_to_xbar_ARVALID),
        .M_AXI_awaddr(s00_couplers_to_xbar_AWADDR),
        .M_AXI_awprot(s00_couplers_to_xbar_AWPROT),
        .M_AXI_awready(s00_couplers_to_xbar_AWREADY),
        .M_AXI_awvalid(s00_couplers_to_xbar_AWVALID),
        .M_AXI_bready(s00_couplers_to_xbar_BREADY),
        .M_AXI_bresp(s00_couplers_to_xbar_BRESP),
        .M_AXI_bvalid(s00_couplers_to_xbar_BVALID),
        .M_AXI_rdata(s00_couplers_to_xbar_RDATA),
        .M_AXI_rready(s00_couplers_to_xbar_RREADY),
        .M_AXI_rresp(s00_couplers_to_xbar_RRESP),
        .M_AXI_rvalid(s00_couplers_to_xbar_RVALID),
        .M_AXI_wdata(s00_couplers_to_xbar_WDATA),
        .M_AXI_wready(s00_couplers_to_xbar_WREADY),
        .M_AXI_wstrb(s00_couplers_to_xbar_WSTRB),
        .M_AXI_wvalid(s00_couplers_to_xbar_WVALID),
        .S_ACLK(S00_ACLK_1),
        .S_ARESETN(S00_ARESETN_1),
        .S_AXI_araddr(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARADDR),
        .S_AXI_arburst(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARBURST),
        .S_AXI_arcache(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARCACHE),
        .S_AXI_arid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARID),
        .S_AXI_arlen(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARLEN),
        .S_AXI_arlock(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARLOCK),
        .S_AXI_arprot(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARPROT),
        .S_AXI_arqos(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARQOS),
        .S_AXI_arready(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARREADY),
        .S_AXI_arsize(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARSIZE),
        .S_AXI_aruser(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARUSER),
        .S_AXI_arvalid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_ARVALID),
        .S_AXI_awaddr(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWADDR),
        .S_AXI_awburst(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWBURST),
        .S_AXI_awcache(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWCACHE),
        .S_AXI_awid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWID),
        .S_AXI_awlen(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWLEN),
        .S_AXI_awlock(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWLOCK),
        .S_AXI_awprot(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWPROT),
        .S_AXI_awqos(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWQOS),
        .S_AXI_awready(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWREADY),
        .S_AXI_awsize(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWSIZE),
        .S_AXI_awuser(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWUSER),
        .S_AXI_awvalid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_AWVALID),
        .S_AXI_bid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BID),
        .S_AXI_bready(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BREADY),
        .S_AXI_bresp(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BRESP),
        .S_AXI_bvalid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_BVALID),
        .S_AXI_rdata(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RDATA),
        .S_AXI_rid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RID),
        .S_AXI_rlast(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RLAST),
        .S_AXI_rready(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RREADY),
        .S_AXI_rresp(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RRESP),
        .S_AXI_rvalid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_RVALID),
        .S_AXI_wdata(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WDATA),
        .S_AXI_wlast(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WLAST),
        .S_AXI_wready(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WREADY),
        .S_AXI_wstrb(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WSTRB),
        .S_AXI_wvalid(zynq_ultra_ps_e_0_axi_periph_to_s00_couplers_WVALID));
  design_1_xbar_1 xbar
       (.aclk(zynq_ultra_ps_e_0_axi_periph_ACLK_net),
        .aresetn(zynq_ultra_ps_e_0_axi_periph_ARESETN_net),
        .m_axi_araddr({xbar_to_m10_couplers_ARADDR,xbar_to_m09_couplers_ARADDR,xbar_to_m08_couplers_ARADDR,xbar_to_m07_couplers_ARADDR,xbar_to_m06_couplers_ARADDR,xbar_to_m05_couplers_ARADDR,xbar_to_m04_couplers_ARADDR,xbar_to_m03_couplers_ARADDR,xbar_to_m02_couplers_ARADDR,xbar_to_m01_couplers_ARADDR,xbar_to_m00_couplers_ARADDR}),
        .m_axi_arprot({xbar_to_m10_couplers_ARPROT,xbar_to_m09_couplers_ARPROT,xbar_to_m08_couplers_ARPROT,xbar_to_m07_couplers_ARPROT,xbar_to_m06_couplers_ARPROT,xbar_to_m05_couplers_ARPROT,xbar_to_m04_couplers_ARPROT,xbar_to_m03_couplers_ARPROT,xbar_to_m02_couplers_ARPROT,xbar_to_m01_couplers_ARPROT,xbar_to_m00_couplers_ARPROT}),
        .m_axi_arready({xbar_to_m10_couplers_ARREADY,xbar_to_m09_couplers_ARREADY,xbar_to_m08_couplers_ARREADY,xbar_to_m07_couplers_ARREADY,xbar_to_m06_couplers_ARREADY,xbar_to_m05_couplers_ARREADY,xbar_to_m04_couplers_ARREADY,xbar_to_m03_couplers_ARREADY,xbar_to_m02_couplers_ARREADY,xbar_to_m01_couplers_ARREADY,xbar_to_m00_couplers_ARREADY}),
        .m_axi_arvalid({xbar_to_m10_couplers_ARVALID,xbar_to_m09_couplers_ARVALID,xbar_to_m08_couplers_ARVALID,xbar_to_m07_couplers_ARVALID,xbar_to_m06_couplers_ARVALID,xbar_to_m05_couplers_ARVALID,xbar_to_m04_couplers_ARVALID,xbar_to_m03_couplers_ARVALID,xbar_to_m02_couplers_ARVALID,xbar_to_m01_couplers_ARVALID,xbar_to_m00_couplers_ARVALID}),
        .m_axi_awaddr({xbar_to_m10_couplers_AWADDR,xbar_to_m09_couplers_AWADDR,xbar_to_m08_couplers_AWADDR,xbar_to_m07_couplers_AWADDR,xbar_to_m06_couplers_AWADDR,xbar_to_m05_couplers_AWADDR,xbar_to_m04_couplers_AWADDR,xbar_to_m03_couplers_AWADDR,xbar_to_m02_couplers_AWADDR,xbar_to_m01_couplers_AWADDR,xbar_to_m00_couplers_AWADDR}),
        .m_axi_awprot({xbar_to_m10_couplers_AWPROT,xbar_to_m09_couplers_AWPROT,xbar_to_m08_couplers_AWPROT,xbar_to_m07_couplers_AWPROT,xbar_to_m06_couplers_AWPROT,xbar_to_m05_couplers_AWPROT,xbar_to_m04_couplers_AWPROT,xbar_to_m03_couplers_AWPROT,xbar_to_m02_couplers_AWPROT,xbar_to_m01_couplers_AWPROT,xbar_to_m00_couplers_AWPROT}),
        .m_axi_awready({xbar_to_m10_couplers_AWREADY,xbar_to_m09_couplers_AWREADY,xbar_to_m08_couplers_AWREADY,xbar_to_m07_couplers_AWREADY,xbar_to_m06_couplers_AWREADY,xbar_to_m05_couplers_AWREADY,xbar_to_m04_couplers_AWREADY,xbar_to_m03_couplers_AWREADY,xbar_to_m02_couplers_AWREADY,xbar_to_m01_couplers_AWREADY,xbar_to_m00_couplers_AWREADY}),
        .m_axi_awvalid({xbar_to_m10_couplers_AWVALID,xbar_to_m09_couplers_AWVALID,xbar_to_m08_couplers_AWVALID,xbar_to_m07_couplers_AWVALID,xbar_to_m06_couplers_AWVALID,xbar_to_m05_couplers_AWVALID,xbar_to_m04_couplers_AWVALID,xbar_to_m03_couplers_AWVALID,xbar_to_m02_couplers_AWVALID,xbar_to_m01_couplers_AWVALID,xbar_to_m00_couplers_AWVALID}),
        .m_axi_bready({xbar_to_m10_couplers_BREADY,xbar_to_m09_couplers_BREADY,xbar_to_m08_couplers_BREADY,xbar_to_m07_couplers_BREADY,xbar_to_m06_couplers_BREADY,xbar_to_m05_couplers_BREADY,xbar_to_m04_couplers_BREADY,xbar_to_m03_couplers_BREADY,xbar_to_m02_couplers_BREADY,xbar_to_m01_couplers_BREADY,xbar_to_m00_couplers_BREADY}),
        .m_axi_bresp({xbar_to_m10_couplers_BRESP,xbar_to_m09_couplers_BRESP,xbar_to_m08_couplers_BRESP,xbar_to_m07_couplers_BRESP,xbar_to_m06_couplers_BRESP,xbar_to_m05_couplers_BRESP,xbar_to_m04_couplers_BRESP,xbar_to_m03_couplers_BRESP,xbar_to_m02_couplers_BRESP,xbar_to_m01_couplers_BRESP,xbar_to_m00_couplers_BRESP}),
        .m_axi_bvalid({xbar_to_m10_couplers_BVALID,xbar_to_m09_couplers_BVALID,xbar_to_m08_couplers_BVALID,xbar_to_m07_couplers_BVALID,xbar_to_m06_couplers_BVALID,xbar_to_m05_couplers_BVALID,xbar_to_m04_couplers_BVALID,xbar_to_m03_couplers_BVALID,xbar_to_m02_couplers_BVALID,xbar_to_m01_couplers_BVALID,xbar_to_m00_couplers_BVALID}),
        .m_axi_rdata({xbar_to_m10_couplers_RDATA,xbar_to_m09_couplers_RDATA,xbar_to_m08_couplers_RDATA,xbar_to_m07_couplers_RDATA,xbar_to_m06_couplers_RDATA,xbar_to_m05_couplers_RDATA,xbar_to_m04_couplers_RDATA,xbar_to_m03_couplers_RDATA,xbar_to_m02_couplers_RDATA,xbar_to_m01_couplers_RDATA,xbar_to_m00_couplers_RDATA}),
        .m_axi_rready({xbar_to_m10_couplers_RREADY,xbar_to_m09_couplers_RREADY,xbar_to_m08_couplers_RREADY,xbar_to_m07_couplers_RREADY,xbar_to_m06_couplers_RREADY,xbar_to_m05_couplers_RREADY,xbar_to_m04_couplers_RREADY,xbar_to_m03_couplers_RREADY,xbar_to_m02_couplers_RREADY,xbar_to_m01_couplers_RREADY,xbar_to_m00_couplers_RREADY}),
        .m_axi_rresp({xbar_to_m10_couplers_RRESP,xbar_to_m09_couplers_RRESP,xbar_to_m08_couplers_RRESP,xbar_to_m07_couplers_RRESP,xbar_to_m06_couplers_RRESP,xbar_to_m05_couplers_RRESP,xbar_to_m04_couplers_RRESP,xbar_to_m03_couplers_RRESP,xbar_to_m02_couplers_RRESP,xbar_to_m01_couplers_RRESP,xbar_to_m00_couplers_RRESP}),
        .m_axi_rvalid({xbar_to_m10_couplers_RVALID,xbar_to_m09_couplers_RVALID,xbar_to_m08_couplers_RVALID,xbar_to_m07_couplers_RVALID,xbar_to_m06_couplers_RVALID,xbar_to_m05_couplers_RVALID,xbar_to_m04_couplers_RVALID,xbar_to_m03_couplers_RVALID,xbar_to_m02_couplers_RVALID,xbar_to_m01_couplers_RVALID,xbar_to_m00_couplers_RVALID}),
        .m_axi_wdata({xbar_to_m10_couplers_WDATA,xbar_to_m09_couplers_WDATA,xbar_to_m08_couplers_WDATA,xbar_to_m07_couplers_WDATA,xbar_to_m06_couplers_WDATA,xbar_to_m05_couplers_WDATA,xbar_to_m04_couplers_WDATA,xbar_to_m03_couplers_WDATA,xbar_to_m02_couplers_WDATA,xbar_to_m01_couplers_WDATA,xbar_to_m00_couplers_WDATA}),
        .m_axi_wready({xbar_to_m10_couplers_WREADY,xbar_to_m09_couplers_WREADY,xbar_to_m08_couplers_WREADY,xbar_to_m07_couplers_WREADY,xbar_to_m06_couplers_WREADY,xbar_to_m05_couplers_WREADY,xbar_to_m04_couplers_WREADY,xbar_to_m03_couplers_WREADY,xbar_to_m02_couplers_WREADY,xbar_to_m01_couplers_WREADY,xbar_to_m00_couplers_WREADY}),
        .m_axi_wstrb({xbar_to_m10_couplers_WSTRB,xbar_to_m09_couplers_WSTRB,xbar_to_m08_couplers_WSTRB,xbar_to_m07_couplers_WSTRB,xbar_to_m06_couplers_WSTRB,xbar_to_m05_couplers_WSTRB,xbar_to_m04_couplers_WSTRB,xbar_to_m03_couplers_WSTRB,xbar_to_m02_couplers_WSTRB,xbar_to_m01_couplers_WSTRB,xbar_to_m00_couplers_WSTRB}),
        .m_axi_wvalid({xbar_to_m10_couplers_WVALID,xbar_to_m09_couplers_WVALID,xbar_to_m08_couplers_WVALID,xbar_to_m07_couplers_WVALID,xbar_to_m06_couplers_WVALID,xbar_to_m05_couplers_WVALID,xbar_to_m04_couplers_WVALID,xbar_to_m03_couplers_WVALID,xbar_to_m02_couplers_WVALID,xbar_to_m01_couplers_WVALID,xbar_to_m00_couplers_WVALID}),
        .s_axi_araddr(s00_couplers_to_xbar_ARADDR),
        .s_axi_arprot(s00_couplers_to_xbar_ARPROT),
        .s_axi_arready(s00_couplers_to_xbar_ARREADY),
        .s_axi_arvalid(s00_couplers_to_xbar_ARVALID),
        .s_axi_awaddr(s00_couplers_to_xbar_AWADDR),
        .s_axi_awprot(s00_couplers_to_xbar_AWPROT),
        .s_axi_awready(s00_couplers_to_xbar_AWREADY),
        .s_axi_awvalid(s00_couplers_to_xbar_AWVALID),
        .s_axi_bready(s00_couplers_to_xbar_BREADY),
        .s_axi_bresp(s00_couplers_to_xbar_BRESP),
        .s_axi_bvalid(s00_couplers_to_xbar_BVALID),
        .s_axi_rdata(s00_couplers_to_xbar_RDATA),
        .s_axi_rready(s00_couplers_to_xbar_RREADY),
        .s_axi_rresp(s00_couplers_to_xbar_RRESP),
        .s_axi_rvalid(s00_couplers_to_xbar_RVALID),
        .s_axi_wdata(s00_couplers_to_xbar_WDATA),
        .s_axi_wready(s00_couplers_to_xbar_WREADY),
        .s_axi_wstrb(s00_couplers_to_xbar_WSTRB),
        .s_axi_wvalid(s00_couplers_to_xbar_WVALID));
endmodule

module m00_couplers_imp_1CA5Z32
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [39:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [39:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire [39:0]m00_couplers_to_m00_couplers_ARADDR;
  wire m00_couplers_to_m00_couplers_ARREADY;
  wire m00_couplers_to_m00_couplers_ARVALID;
  wire [39:0]m00_couplers_to_m00_couplers_AWADDR;
  wire m00_couplers_to_m00_couplers_AWREADY;
  wire m00_couplers_to_m00_couplers_AWVALID;
  wire m00_couplers_to_m00_couplers_BREADY;
  wire [1:0]m00_couplers_to_m00_couplers_BRESP;
  wire m00_couplers_to_m00_couplers_BVALID;
  wire [31:0]m00_couplers_to_m00_couplers_RDATA;
  wire m00_couplers_to_m00_couplers_RREADY;
  wire [1:0]m00_couplers_to_m00_couplers_RRESP;
  wire m00_couplers_to_m00_couplers_RVALID;
  wire [31:0]m00_couplers_to_m00_couplers_WDATA;
  wire m00_couplers_to_m00_couplers_WREADY;
  wire [3:0]m00_couplers_to_m00_couplers_WSTRB;
  wire m00_couplers_to_m00_couplers_WVALID;

  assign M_AXI_araddr[39:0] = m00_couplers_to_m00_couplers_ARADDR;
  assign M_AXI_arvalid = m00_couplers_to_m00_couplers_ARVALID;
  assign M_AXI_awaddr[39:0] = m00_couplers_to_m00_couplers_AWADDR;
  assign M_AXI_awvalid = m00_couplers_to_m00_couplers_AWVALID;
  assign M_AXI_bready = m00_couplers_to_m00_couplers_BREADY;
  assign M_AXI_rready = m00_couplers_to_m00_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m00_couplers_to_m00_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m00_couplers_to_m00_couplers_WSTRB;
  assign M_AXI_wvalid = m00_couplers_to_m00_couplers_WVALID;
  assign S_AXI_arready = m00_couplers_to_m00_couplers_ARREADY;
  assign S_AXI_awready = m00_couplers_to_m00_couplers_AWREADY;
  assign S_AXI_bresp[1:0] = m00_couplers_to_m00_couplers_BRESP;
  assign S_AXI_bvalid = m00_couplers_to_m00_couplers_BVALID;
  assign S_AXI_rdata[31:0] = m00_couplers_to_m00_couplers_RDATA;
  assign S_AXI_rresp[1:0] = m00_couplers_to_m00_couplers_RRESP;
  assign S_AXI_rvalid = m00_couplers_to_m00_couplers_RVALID;
  assign S_AXI_wready = m00_couplers_to_m00_couplers_WREADY;
  assign m00_couplers_to_m00_couplers_ARADDR = S_AXI_araddr[39:0];
  assign m00_couplers_to_m00_couplers_ARREADY = M_AXI_arready;
  assign m00_couplers_to_m00_couplers_ARVALID = S_AXI_arvalid;
  assign m00_couplers_to_m00_couplers_AWADDR = S_AXI_awaddr[39:0];
  assign m00_couplers_to_m00_couplers_AWREADY = M_AXI_awready;
  assign m00_couplers_to_m00_couplers_AWVALID = S_AXI_awvalid;
  assign m00_couplers_to_m00_couplers_BREADY = S_AXI_bready;
  assign m00_couplers_to_m00_couplers_BRESP = M_AXI_bresp[1:0];
  assign m00_couplers_to_m00_couplers_BVALID = M_AXI_bvalid;
  assign m00_couplers_to_m00_couplers_RDATA = M_AXI_rdata[31:0];
  assign m00_couplers_to_m00_couplers_RREADY = S_AXI_rready;
  assign m00_couplers_to_m00_couplers_RRESP = M_AXI_rresp[1:0];
  assign m00_couplers_to_m00_couplers_RVALID = M_AXI_rvalid;
  assign m00_couplers_to_m00_couplers_WDATA = S_AXI_wdata[31:0];
  assign m00_couplers_to_m00_couplers_WREADY = M_AXI_wready;
  assign m00_couplers_to_m00_couplers_WSTRB = S_AXI_wstrb[3:0];
  assign m00_couplers_to_m00_couplers_WVALID = S_AXI_wvalid;
endmodule

module m00_couplers_imp_6WA1NC
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [7:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [7:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m00_couplers_to_m00_regslice_ARADDR;
  wire [2:0]m00_couplers_to_m00_regslice_ARPROT;
  wire m00_couplers_to_m00_regslice_ARREADY;
  wire m00_couplers_to_m00_regslice_ARVALID;
  wire [39:0]m00_couplers_to_m00_regslice_AWADDR;
  wire [2:0]m00_couplers_to_m00_regslice_AWPROT;
  wire m00_couplers_to_m00_regslice_AWREADY;
  wire m00_couplers_to_m00_regslice_AWVALID;
  wire m00_couplers_to_m00_regslice_BREADY;
  wire [1:0]m00_couplers_to_m00_regslice_BRESP;
  wire m00_couplers_to_m00_regslice_BVALID;
  wire [31:0]m00_couplers_to_m00_regslice_RDATA;
  wire m00_couplers_to_m00_regslice_RREADY;
  wire [1:0]m00_couplers_to_m00_regslice_RRESP;
  wire m00_couplers_to_m00_regslice_RVALID;
  wire [31:0]m00_couplers_to_m00_regslice_WDATA;
  wire m00_couplers_to_m00_regslice_WREADY;
  wire [3:0]m00_couplers_to_m00_regslice_WSTRB;
  wire m00_couplers_to_m00_regslice_WVALID;
  wire [7:0]m00_regslice_to_m00_couplers_ARADDR;
  wire m00_regslice_to_m00_couplers_ARREADY;
  wire m00_regslice_to_m00_couplers_ARVALID;
  wire [7:0]m00_regslice_to_m00_couplers_AWADDR;
  wire m00_regslice_to_m00_couplers_AWREADY;
  wire m00_regslice_to_m00_couplers_AWVALID;
  wire m00_regslice_to_m00_couplers_BREADY;
  wire [1:0]m00_regslice_to_m00_couplers_BRESP;
  wire m00_regslice_to_m00_couplers_BVALID;
  wire [31:0]m00_regslice_to_m00_couplers_RDATA;
  wire m00_regslice_to_m00_couplers_RREADY;
  wire [1:0]m00_regslice_to_m00_couplers_RRESP;
  wire m00_regslice_to_m00_couplers_RVALID;
  wire [31:0]m00_regslice_to_m00_couplers_WDATA;
  wire m00_regslice_to_m00_couplers_WREADY;
  wire [3:0]m00_regslice_to_m00_couplers_WSTRB;
  wire m00_regslice_to_m00_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[7:0] = m00_regslice_to_m00_couplers_ARADDR;
  assign M_AXI_arvalid = m00_regslice_to_m00_couplers_ARVALID;
  assign M_AXI_awaddr[7:0] = m00_regslice_to_m00_couplers_AWADDR;
  assign M_AXI_awvalid = m00_regslice_to_m00_couplers_AWVALID;
  assign M_AXI_bready = m00_regslice_to_m00_couplers_BREADY;
  assign M_AXI_rready = m00_regslice_to_m00_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m00_regslice_to_m00_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m00_regslice_to_m00_couplers_WSTRB;
  assign M_AXI_wvalid = m00_regslice_to_m00_couplers_WVALID;
  assign S_AXI_arready = m00_couplers_to_m00_regslice_ARREADY;
  assign S_AXI_awready = m00_couplers_to_m00_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m00_couplers_to_m00_regslice_BRESP;
  assign S_AXI_bvalid = m00_couplers_to_m00_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m00_couplers_to_m00_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m00_couplers_to_m00_regslice_RRESP;
  assign S_AXI_rvalid = m00_couplers_to_m00_regslice_RVALID;
  assign S_AXI_wready = m00_couplers_to_m00_regslice_WREADY;
  assign m00_couplers_to_m00_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m00_couplers_to_m00_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m00_couplers_to_m00_regslice_ARVALID = S_AXI_arvalid;
  assign m00_couplers_to_m00_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m00_couplers_to_m00_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m00_couplers_to_m00_regslice_AWVALID = S_AXI_awvalid;
  assign m00_couplers_to_m00_regslice_BREADY = S_AXI_bready;
  assign m00_couplers_to_m00_regslice_RREADY = S_AXI_rready;
  assign m00_couplers_to_m00_regslice_WDATA = S_AXI_wdata[31:0];
  assign m00_couplers_to_m00_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m00_couplers_to_m00_regslice_WVALID = S_AXI_wvalid;
  assign m00_regslice_to_m00_couplers_ARREADY = M_AXI_arready;
  assign m00_regslice_to_m00_couplers_AWREADY = M_AXI_awready;
  assign m00_regslice_to_m00_couplers_BRESP = M_AXI_bresp[1:0];
  assign m00_regslice_to_m00_couplers_BVALID = M_AXI_bvalid;
  assign m00_regslice_to_m00_couplers_RDATA = M_AXI_rdata[31:0];
  assign m00_regslice_to_m00_couplers_RRESP = M_AXI_rresp[1:0];
  assign m00_regslice_to_m00_couplers_RVALID = M_AXI_rvalid;
  assign m00_regslice_to_m00_couplers_WREADY = M_AXI_wready;
  design_1_m00_regslice_0 m00_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m00_regslice_to_m00_couplers_ARADDR),
        .m_axi_arready(m00_regslice_to_m00_couplers_ARREADY),
        .m_axi_arvalid(m00_regslice_to_m00_couplers_ARVALID),
        .m_axi_awaddr(m00_regslice_to_m00_couplers_AWADDR),
        .m_axi_awready(m00_regslice_to_m00_couplers_AWREADY),
        .m_axi_awvalid(m00_regslice_to_m00_couplers_AWVALID),
        .m_axi_bready(m00_regslice_to_m00_couplers_BREADY),
        .m_axi_bresp(m00_regslice_to_m00_couplers_BRESP),
        .m_axi_bvalid(m00_regslice_to_m00_couplers_BVALID),
        .m_axi_rdata(m00_regslice_to_m00_couplers_RDATA),
        .m_axi_rready(m00_regslice_to_m00_couplers_RREADY),
        .m_axi_rresp(m00_regslice_to_m00_couplers_RRESP),
        .m_axi_rvalid(m00_regslice_to_m00_couplers_RVALID),
        .m_axi_wdata(m00_regslice_to_m00_couplers_WDATA),
        .m_axi_wready(m00_regslice_to_m00_couplers_WREADY),
        .m_axi_wstrb(m00_regslice_to_m00_couplers_WSTRB),
        .m_axi_wvalid(m00_regslice_to_m00_couplers_WVALID),
        .s_axi_araddr(m00_couplers_to_m00_regslice_ARADDR[7:0]),
        .s_axi_arprot(m00_couplers_to_m00_regslice_ARPROT),
        .s_axi_arready(m00_couplers_to_m00_regslice_ARREADY),
        .s_axi_arvalid(m00_couplers_to_m00_regslice_ARVALID),
        .s_axi_awaddr(m00_couplers_to_m00_regslice_AWADDR[7:0]),
        .s_axi_awprot(m00_couplers_to_m00_regslice_AWPROT),
        .s_axi_awready(m00_couplers_to_m00_regslice_AWREADY),
        .s_axi_awvalid(m00_couplers_to_m00_regslice_AWVALID),
        .s_axi_bready(m00_couplers_to_m00_regslice_BREADY),
        .s_axi_bresp(m00_couplers_to_m00_regslice_BRESP),
        .s_axi_bvalid(m00_couplers_to_m00_regslice_BVALID),
        .s_axi_rdata(m00_couplers_to_m00_regslice_RDATA),
        .s_axi_rready(m00_couplers_to_m00_regslice_RREADY),
        .s_axi_rresp(m00_couplers_to_m00_regslice_RRESP),
        .s_axi_rvalid(m00_couplers_to_m00_regslice_RVALID),
        .s_axi_wdata(m00_couplers_to_m00_regslice_WDATA),
        .s_axi_wready(m00_couplers_to_m00_regslice_WREADY),
        .s_axi_wstrb(m00_couplers_to_m00_regslice_WSTRB),
        .s_axi_wvalid(m00_couplers_to_m00_regslice_WVALID));
endmodule

module m01_couplers_imp_1WOL2K9
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [17:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [17:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m01_couplers_to_m01_regslice_ARADDR;
  wire [2:0]m01_couplers_to_m01_regslice_ARPROT;
  wire m01_couplers_to_m01_regslice_ARREADY;
  wire m01_couplers_to_m01_regslice_ARVALID;
  wire [39:0]m01_couplers_to_m01_regslice_AWADDR;
  wire [2:0]m01_couplers_to_m01_regslice_AWPROT;
  wire m01_couplers_to_m01_regslice_AWREADY;
  wire m01_couplers_to_m01_regslice_AWVALID;
  wire m01_couplers_to_m01_regslice_BREADY;
  wire [1:0]m01_couplers_to_m01_regslice_BRESP;
  wire m01_couplers_to_m01_regslice_BVALID;
  wire [31:0]m01_couplers_to_m01_regslice_RDATA;
  wire m01_couplers_to_m01_regslice_RREADY;
  wire [1:0]m01_couplers_to_m01_regslice_RRESP;
  wire m01_couplers_to_m01_regslice_RVALID;
  wire [31:0]m01_couplers_to_m01_regslice_WDATA;
  wire m01_couplers_to_m01_regslice_WREADY;
  wire [3:0]m01_couplers_to_m01_regslice_WSTRB;
  wire m01_couplers_to_m01_regslice_WVALID;
  wire [17:0]m01_regslice_to_m01_couplers_ARADDR;
  wire m01_regslice_to_m01_couplers_ARREADY;
  wire m01_regslice_to_m01_couplers_ARVALID;
  wire [17:0]m01_regslice_to_m01_couplers_AWADDR;
  wire m01_regslice_to_m01_couplers_AWREADY;
  wire m01_regslice_to_m01_couplers_AWVALID;
  wire m01_regslice_to_m01_couplers_BREADY;
  wire m01_regslice_to_m01_couplers_BVALID;
  wire [31:0]m01_regslice_to_m01_couplers_RDATA;
  wire m01_regslice_to_m01_couplers_RREADY;
  wire m01_regslice_to_m01_couplers_RVALID;
  wire [31:0]m01_regslice_to_m01_couplers_WDATA;
  wire m01_regslice_to_m01_couplers_WREADY;
  wire m01_regslice_to_m01_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[17:0] = m01_regslice_to_m01_couplers_ARADDR;
  assign M_AXI_arvalid = m01_regslice_to_m01_couplers_ARVALID;
  assign M_AXI_awaddr[17:0] = m01_regslice_to_m01_couplers_AWADDR;
  assign M_AXI_awvalid = m01_regslice_to_m01_couplers_AWVALID;
  assign M_AXI_bready = m01_regslice_to_m01_couplers_BREADY;
  assign M_AXI_rready = m01_regslice_to_m01_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m01_regslice_to_m01_couplers_WDATA;
  assign M_AXI_wvalid = m01_regslice_to_m01_couplers_WVALID;
  assign S_AXI_arready = m01_couplers_to_m01_regslice_ARREADY;
  assign S_AXI_awready = m01_couplers_to_m01_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m01_couplers_to_m01_regslice_BRESP;
  assign S_AXI_bvalid = m01_couplers_to_m01_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m01_couplers_to_m01_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m01_couplers_to_m01_regslice_RRESP;
  assign S_AXI_rvalid = m01_couplers_to_m01_regslice_RVALID;
  assign S_AXI_wready = m01_couplers_to_m01_regslice_WREADY;
  assign m01_couplers_to_m01_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m01_couplers_to_m01_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m01_couplers_to_m01_regslice_ARVALID = S_AXI_arvalid;
  assign m01_couplers_to_m01_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m01_couplers_to_m01_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m01_couplers_to_m01_regslice_AWVALID = S_AXI_awvalid;
  assign m01_couplers_to_m01_regslice_BREADY = S_AXI_bready;
  assign m01_couplers_to_m01_regslice_RREADY = S_AXI_rready;
  assign m01_couplers_to_m01_regslice_WDATA = S_AXI_wdata[31:0];
  assign m01_couplers_to_m01_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m01_couplers_to_m01_regslice_WVALID = S_AXI_wvalid;
  assign m01_regslice_to_m01_couplers_ARREADY = M_AXI_arready;
  assign m01_regslice_to_m01_couplers_AWREADY = M_AXI_awready;
  assign m01_regslice_to_m01_couplers_BVALID = M_AXI_bvalid;
  assign m01_regslice_to_m01_couplers_RDATA = M_AXI_rdata[31:0];
  assign m01_regslice_to_m01_couplers_RVALID = M_AXI_rvalid;
  assign m01_regslice_to_m01_couplers_WREADY = M_AXI_wready;
  design_1_m01_regslice_0 m01_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m01_regslice_to_m01_couplers_ARADDR),
        .m_axi_arready(m01_regslice_to_m01_couplers_ARREADY),
        .m_axi_arvalid(m01_regslice_to_m01_couplers_ARVALID),
        .m_axi_awaddr(m01_regslice_to_m01_couplers_AWADDR),
        .m_axi_awready(m01_regslice_to_m01_couplers_AWREADY),
        .m_axi_awvalid(m01_regslice_to_m01_couplers_AWVALID),
        .m_axi_bready(m01_regslice_to_m01_couplers_BREADY),
        .m_axi_bresp({1'b0,1'b0}),
        .m_axi_bvalid(m01_regslice_to_m01_couplers_BVALID),
        .m_axi_rdata(m01_regslice_to_m01_couplers_RDATA),
        .m_axi_rready(m01_regslice_to_m01_couplers_RREADY),
        .m_axi_rresp({1'b0,1'b0}),
        .m_axi_rvalid(m01_regslice_to_m01_couplers_RVALID),
        .m_axi_wdata(m01_regslice_to_m01_couplers_WDATA),
        .m_axi_wready(m01_regslice_to_m01_couplers_WREADY),
        .m_axi_wvalid(m01_regslice_to_m01_couplers_WVALID),
        .s_axi_araddr(m01_couplers_to_m01_regslice_ARADDR[17:0]),
        .s_axi_arprot(m01_couplers_to_m01_regslice_ARPROT),
        .s_axi_arready(m01_couplers_to_m01_regslice_ARREADY),
        .s_axi_arvalid(m01_couplers_to_m01_regslice_ARVALID),
        .s_axi_awaddr(m01_couplers_to_m01_regslice_AWADDR[17:0]),
        .s_axi_awprot(m01_couplers_to_m01_regslice_AWPROT),
        .s_axi_awready(m01_couplers_to_m01_regslice_AWREADY),
        .s_axi_awvalid(m01_couplers_to_m01_regslice_AWVALID),
        .s_axi_bready(m01_couplers_to_m01_regslice_BREADY),
        .s_axi_bresp(m01_couplers_to_m01_regslice_BRESP),
        .s_axi_bvalid(m01_couplers_to_m01_regslice_BVALID),
        .s_axi_rdata(m01_couplers_to_m01_regslice_RDATA),
        .s_axi_rready(m01_couplers_to_m01_regslice_RREADY),
        .s_axi_rresp(m01_couplers_to_m01_regslice_RRESP),
        .s_axi_rvalid(m01_couplers_to_m01_regslice_RVALID),
        .s_axi_wdata(m01_couplers_to_m01_regslice_WDATA),
        .s_axi_wready(m01_couplers_to_m01_regslice_WREADY),
        .s_axi_wstrb(m01_couplers_to_m01_regslice_WSTRB),
        .s_axi_wvalid(m01_couplers_to_m01_regslice_WVALID));
endmodule

module m01_couplers_imp_I4GRPB
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [39:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [39:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire [39:0]m01_couplers_to_m01_couplers_ARADDR;
  wire m01_couplers_to_m01_couplers_ARREADY;
  wire m01_couplers_to_m01_couplers_ARVALID;
  wire [39:0]m01_couplers_to_m01_couplers_AWADDR;
  wire m01_couplers_to_m01_couplers_AWREADY;
  wire m01_couplers_to_m01_couplers_AWVALID;
  wire m01_couplers_to_m01_couplers_BREADY;
  wire [1:0]m01_couplers_to_m01_couplers_BRESP;
  wire m01_couplers_to_m01_couplers_BVALID;
  wire [31:0]m01_couplers_to_m01_couplers_RDATA;
  wire m01_couplers_to_m01_couplers_RREADY;
  wire [1:0]m01_couplers_to_m01_couplers_RRESP;
  wire m01_couplers_to_m01_couplers_RVALID;
  wire [31:0]m01_couplers_to_m01_couplers_WDATA;
  wire m01_couplers_to_m01_couplers_WREADY;
  wire [3:0]m01_couplers_to_m01_couplers_WSTRB;
  wire m01_couplers_to_m01_couplers_WVALID;

  assign M_AXI_araddr[39:0] = m01_couplers_to_m01_couplers_ARADDR;
  assign M_AXI_arvalid = m01_couplers_to_m01_couplers_ARVALID;
  assign M_AXI_awaddr[39:0] = m01_couplers_to_m01_couplers_AWADDR;
  assign M_AXI_awvalid = m01_couplers_to_m01_couplers_AWVALID;
  assign M_AXI_bready = m01_couplers_to_m01_couplers_BREADY;
  assign M_AXI_rready = m01_couplers_to_m01_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m01_couplers_to_m01_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m01_couplers_to_m01_couplers_WSTRB;
  assign M_AXI_wvalid = m01_couplers_to_m01_couplers_WVALID;
  assign S_AXI_arready = m01_couplers_to_m01_couplers_ARREADY;
  assign S_AXI_awready = m01_couplers_to_m01_couplers_AWREADY;
  assign S_AXI_bresp[1:0] = m01_couplers_to_m01_couplers_BRESP;
  assign S_AXI_bvalid = m01_couplers_to_m01_couplers_BVALID;
  assign S_AXI_rdata[31:0] = m01_couplers_to_m01_couplers_RDATA;
  assign S_AXI_rresp[1:0] = m01_couplers_to_m01_couplers_RRESP;
  assign S_AXI_rvalid = m01_couplers_to_m01_couplers_RVALID;
  assign S_AXI_wready = m01_couplers_to_m01_couplers_WREADY;
  assign m01_couplers_to_m01_couplers_ARADDR = S_AXI_araddr[39:0];
  assign m01_couplers_to_m01_couplers_ARREADY = M_AXI_arready;
  assign m01_couplers_to_m01_couplers_ARVALID = S_AXI_arvalid;
  assign m01_couplers_to_m01_couplers_AWADDR = S_AXI_awaddr[39:0];
  assign m01_couplers_to_m01_couplers_AWREADY = M_AXI_awready;
  assign m01_couplers_to_m01_couplers_AWVALID = S_AXI_awvalid;
  assign m01_couplers_to_m01_couplers_BREADY = S_AXI_bready;
  assign m01_couplers_to_m01_couplers_BRESP = M_AXI_bresp[1:0];
  assign m01_couplers_to_m01_couplers_BVALID = M_AXI_bvalid;
  assign m01_couplers_to_m01_couplers_RDATA = M_AXI_rdata[31:0];
  assign m01_couplers_to_m01_couplers_RREADY = S_AXI_rready;
  assign m01_couplers_to_m01_couplers_RRESP = M_AXI_rresp[1:0];
  assign m01_couplers_to_m01_couplers_RVALID = M_AXI_rvalid;
  assign m01_couplers_to_m01_couplers_WDATA = S_AXI_wdata[31:0];
  assign m01_couplers_to_m01_couplers_WREADY = M_AXI_wready;
  assign m01_couplers_to_m01_couplers_WSTRB = S_AXI_wstrb[3:0];
  assign m01_couplers_to_m01_couplers_WVALID = S_AXI_wvalid;
endmodule

module m02_couplers_imp_1BOGR4T
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [39:0]M_AXI_araddr;
  input [0:0]M_AXI_arready;
  output [0:0]M_AXI_arvalid;
  output [39:0]M_AXI_awaddr;
  input [0:0]M_AXI_awready;
  output [0:0]M_AXI_awvalid;
  output [0:0]M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input [0:0]M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output [0:0]M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input [0:0]M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input [0:0]M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output [0:0]M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  output [0:0]S_AXI_arready;
  input [0:0]S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  output [0:0]S_AXI_awready;
  input [0:0]S_AXI_awvalid;
  input [0:0]S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output [0:0]S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input [0:0]S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output [0:0]S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output [0:0]S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input [0:0]S_AXI_wvalid;

  wire [39:0]m02_couplers_to_m02_couplers_ARADDR;
  wire [0:0]m02_couplers_to_m02_couplers_ARREADY;
  wire [0:0]m02_couplers_to_m02_couplers_ARVALID;
  wire [39:0]m02_couplers_to_m02_couplers_AWADDR;
  wire [0:0]m02_couplers_to_m02_couplers_AWREADY;
  wire [0:0]m02_couplers_to_m02_couplers_AWVALID;
  wire [0:0]m02_couplers_to_m02_couplers_BREADY;
  wire [1:0]m02_couplers_to_m02_couplers_BRESP;
  wire [0:0]m02_couplers_to_m02_couplers_BVALID;
  wire [31:0]m02_couplers_to_m02_couplers_RDATA;
  wire [0:0]m02_couplers_to_m02_couplers_RREADY;
  wire [1:0]m02_couplers_to_m02_couplers_RRESP;
  wire [0:0]m02_couplers_to_m02_couplers_RVALID;
  wire [31:0]m02_couplers_to_m02_couplers_WDATA;
  wire [0:0]m02_couplers_to_m02_couplers_WREADY;
  wire [3:0]m02_couplers_to_m02_couplers_WSTRB;
  wire [0:0]m02_couplers_to_m02_couplers_WVALID;

  assign M_AXI_araddr[39:0] = m02_couplers_to_m02_couplers_ARADDR;
  assign M_AXI_arvalid[0] = m02_couplers_to_m02_couplers_ARVALID;
  assign M_AXI_awaddr[39:0] = m02_couplers_to_m02_couplers_AWADDR;
  assign M_AXI_awvalid[0] = m02_couplers_to_m02_couplers_AWVALID;
  assign M_AXI_bready[0] = m02_couplers_to_m02_couplers_BREADY;
  assign M_AXI_rready[0] = m02_couplers_to_m02_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m02_couplers_to_m02_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m02_couplers_to_m02_couplers_WSTRB;
  assign M_AXI_wvalid[0] = m02_couplers_to_m02_couplers_WVALID;
  assign S_AXI_arready[0] = m02_couplers_to_m02_couplers_ARREADY;
  assign S_AXI_awready[0] = m02_couplers_to_m02_couplers_AWREADY;
  assign S_AXI_bresp[1:0] = m02_couplers_to_m02_couplers_BRESP;
  assign S_AXI_bvalid[0] = m02_couplers_to_m02_couplers_BVALID;
  assign S_AXI_rdata[31:0] = m02_couplers_to_m02_couplers_RDATA;
  assign S_AXI_rresp[1:0] = m02_couplers_to_m02_couplers_RRESP;
  assign S_AXI_rvalid[0] = m02_couplers_to_m02_couplers_RVALID;
  assign S_AXI_wready[0] = m02_couplers_to_m02_couplers_WREADY;
  assign m02_couplers_to_m02_couplers_ARADDR = S_AXI_araddr[39:0];
  assign m02_couplers_to_m02_couplers_ARREADY = M_AXI_arready[0];
  assign m02_couplers_to_m02_couplers_ARVALID = S_AXI_arvalid[0];
  assign m02_couplers_to_m02_couplers_AWADDR = S_AXI_awaddr[39:0];
  assign m02_couplers_to_m02_couplers_AWREADY = M_AXI_awready[0];
  assign m02_couplers_to_m02_couplers_AWVALID = S_AXI_awvalid[0];
  assign m02_couplers_to_m02_couplers_BREADY = S_AXI_bready[0];
  assign m02_couplers_to_m02_couplers_BRESP = M_AXI_bresp[1:0];
  assign m02_couplers_to_m02_couplers_BVALID = M_AXI_bvalid[0];
  assign m02_couplers_to_m02_couplers_RDATA = M_AXI_rdata[31:0];
  assign m02_couplers_to_m02_couplers_RREADY = S_AXI_rready[0];
  assign m02_couplers_to_m02_couplers_RRESP = M_AXI_rresp[1:0];
  assign m02_couplers_to_m02_couplers_RVALID = M_AXI_rvalid[0];
  assign m02_couplers_to_m02_couplers_WDATA = S_AXI_wdata[31:0];
  assign m02_couplers_to_m02_couplers_WREADY = M_AXI_wready[0];
  assign m02_couplers_to_m02_couplers_WSTRB = S_AXI_wstrb[3:0];
  assign m02_couplers_to_m02_couplers_WVALID = S_AXI_wvalid[0];
endmodule

module m02_couplers_imp_829XSR
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [5:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [5:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m02_couplers_to_m02_regslice_ARADDR;
  wire [2:0]m02_couplers_to_m02_regslice_ARPROT;
  wire m02_couplers_to_m02_regslice_ARREADY;
  wire m02_couplers_to_m02_regslice_ARVALID;
  wire [39:0]m02_couplers_to_m02_regslice_AWADDR;
  wire [2:0]m02_couplers_to_m02_regslice_AWPROT;
  wire m02_couplers_to_m02_regslice_AWREADY;
  wire m02_couplers_to_m02_regslice_AWVALID;
  wire m02_couplers_to_m02_regslice_BREADY;
  wire [1:0]m02_couplers_to_m02_regslice_BRESP;
  wire m02_couplers_to_m02_regslice_BVALID;
  wire [31:0]m02_couplers_to_m02_regslice_RDATA;
  wire m02_couplers_to_m02_regslice_RREADY;
  wire [1:0]m02_couplers_to_m02_regslice_RRESP;
  wire m02_couplers_to_m02_regslice_RVALID;
  wire [31:0]m02_couplers_to_m02_regslice_WDATA;
  wire m02_couplers_to_m02_regslice_WREADY;
  wire [3:0]m02_couplers_to_m02_regslice_WSTRB;
  wire m02_couplers_to_m02_regslice_WVALID;
  wire [5:0]m02_regslice_to_m02_couplers_ARADDR;
  wire m02_regslice_to_m02_couplers_ARREADY;
  wire m02_regslice_to_m02_couplers_ARVALID;
  wire [5:0]m02_regslice_to_m02_couplers_AWADDR;
  wire m02_regslice_to_m02_couplers_AWREADY;
  wire m02_regslice_to_m02_couplers_AWVALID;
  wire m02_regslice_to_m02_couplers_BREADY;
  wire [1:0]m02_regslice_to_m02_couplers_BRESP;
  wire m02_regslice_to_m02_couplers_BVALID;
  wire [31:0]m02_regslice_to_m02_couplers_RDATA;
  wire m02_regslice_to_m02_couplers_RREADY;
  wire [1:0]m02_regslice_to_m02_couplers_RRESP;
  wire m02_regslice_to_m02_couplers_RVALID;
  wire [31:0]m02_regslice_to_m02_couplers_WDATA;
  wire m02_regslice_to_m02_couplers_WREADY;
  wire [3:0]m02_regslice_to_m02_couplers_WSTRB;
  wire m02_regslice_to_m02_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[5:0] = m02_regslice_to_m02_couplers_ARADDR;
  assign M_AXI_arvalid = m02_regslice_to_m02_couplers_ARVALID;
  assign M_AXI_awaddr[5:0] = m02_regslice_to_m02_couplers_AWADDR;
  assign M_AXI_awvalid = m02_regslice_to_m02_couplers_AWVALID;
  assign M_AXI_bready = m02_regslice_to_m02_couplers_BREADY;
  assign M_AXI_rready = m02_regslice_to_m02_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m02_regslice_to_m02_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m02_regslice_to_m02_couplers_WSTRB;
  assign M_AXI_wvalid = m02_regslice_to_m02_couplers_WVALID;
  assign S_AXI_arready = m02_couplers_to_m02_regslice_ARREADY;
  assign S_AXI_awready = m02_couplers_to_m02_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m02_couplers_to_m02_regslice_BRESP;
  assign S_AXI_bvalid = m02_couplers_to_m02_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m02_couplers_to_m02_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m02_couplers_to_m02_regslice_RRESP;
  assign S_AXI_rvalid = m02_couplers_to_m02_regslice_RVALID;
  assign S_AXI_wready = m02_couplers_to_m02_regslice_WREADY;
  assign m02_couplers_to_m02_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m02_couplers_to_m02_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m02_couplers_to_m02_regslice_ARVALID = S_AXI_arvalid;
  assign m02_couplers_to_m02_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m02_couplers_to_m02_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m02_couplers_to_m02_regslice_AWVALID = S_AXI_awvalid;
  assign m02_couplers_to_m02_regslice_BREADY = S_AXI_bready;
  assign m02_couplers_to_m02_regslice_RREADY = S_AXI_rready;
  assign m02_couplers_to_m02_regslice_WDATA = S_AXI_wdata[31:0];
  assign m02_couplers_to_m02_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m02_couplers_to_m02_regslice_WVALID = S_AXI_wvalid;
  assign m02_regslice_to_m02_couplers_ARREADY = M_AXI_arready;
  assign m02_regslice_to_m02_couplers_AWREADY = M_AXI_awready;
  assign m02_regslice_to_m02_couplers_BRESP = M_AXI_bresp[1:0];
  assign m02_regslice_to_m02_couplers_BVALID = M_AXI_bvalid;
  assign m02_regslice_to_m02_couplers_RDATA = M_AXI_rdata[31:0];
  assign m02_regslice_to_m02_couplers_RRESP = M_AXI_rresp[1:0];
  assign m02_regslice_to_m02_couplers_RVALID = M_AXI_rvalid;
  assign m02_regslice_to_m02_couplers_WREADY = M_AXI_wready;
  design_1_m02_regslice_0 m02_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m02_regslice_to_m02_couplers_ARADDR),
        .m_axi_arready(m02_regslice_to_m02_couplers_ARREADY),
        .m_axi_arvalid(m02_regslice_to_m02_couplers_ARVALID),
        .m_axi_awaddr(m02_regslice_to_m02_couplers_AWADDR),
        .m_axi_awready(m02_regslice_to_m02_couplers_AWREADY),
        .m_axi_awvalid(m02_regslice_to_m02_couplers_AWVALID),
        .m_axi_bready(m02_regslice_to_m02_couplers_BREADY),
        .m_axi_bresp(m02_regslice_to_m02_couplers_BRESP),
        .m_axi_bvalid(m02_regslice_to_m02_couplers_BVALID),
        .m_axi_rdata(m02_regslice_to_m02_couplers_RDATA),
        .m_axi_rready(m02_regslice_to_m02_couplers_RREADY),
        .m_axi_rresp(m02_regslice_to_m02_couplers_RRESP),
        .m_axi_rvalid(m02_regslice_to_m02_couplers_RVALID),
        .m_axi_wdata(m02_regslice_to_m02_couplers_WDATA),
        .m_axi_wready(m02_regslice_to_m02_couplers_WREADY),
        .m_axi_wstrb(m02_regslice_to_m02_couplers_WSTRB),
        .m_axi_wvalid(m02_regslice_to_m02_couplers_WVALID),
        .s_axi_araddr(m02_couplers_to_m02_regslice_ARADDR[5:0]),
        .s_axi_arprot(m02_couplers_to_m02_regslice_ARPROT),
        .s_axi_arready(m02_couplers_to_m02_regslice_ARREADY),
        .s_axi_arvalid(m02_couplers_to_m02_regslice_ARVALID),
        .s_axi_awaddr(m02_couplers_to_m02_regslice_AWADDR[5:0]),
        .s_axi_awprot(m02_couplers_to_m02_regslice_AWPROT),
        .s_axi_awready(m02_couplers_to_m02_regslice_AWREADY),
        .s_axi_awvalid(m02_couplers_to_m02_regslice_AWVALID),
        .s_axi_bready(m02_couplers_to_m02_regslice_BREADY),
        .s_axi_bresp(m02_couplers_to_m02_regslice_BRESP),
        .s_axi_bvalid(m02_couplers_to_m02_regslice_BVALID),
        .s_axi_rdata(m02_couplers_to_m02_regslice_RDATA),
        .s_axi_rready(m02_couplers_to_m02_regslice_RREADY),
        .s_axi_rresp(m02_couplers_to_m02_regslice_RRESP),
        .s_axi_rvalid(m02_couplers_to_m02_regslice_RVALID),
        .s_axi_wdata(m02_couplers_to_m02_regslice_WDATA),
        .s_axi_wready(m02_couplers_to_m02_regslice_WREADY),
        .s_axi_wstrb(m02_couplers_to_m02_regslice_WSTRB),
        .s_axi_wvalid(m02_couplers_to_m02_regslice_WVALID));
endmodule

module m03_couplers_imp_1V8XG3E
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [5:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [5:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m03_couplers_to_m03_regslice_ARADDR;
  wire [2:0]m03_couplers_to_m03_regslice_ARPROT;
  wire m03_couplers_to_m03_regslice_ARREADY;
  wire m03_couplers_to_m03_regslice_ARVALID;
  wire [39:0]m03_couplers_to_m03_regslice_AWADDR;
  wire [2:0]m03_couplers_to_m03_regslice_AWPROT;
  wire m03_couplers_to_m03_regslice_AWREADY;
  wire m03_couplers_to_m03_regslice_AWVALID;
  wire m03_couplers_to_m03_regslice_BREADY;
  wire [1:0]m03_couplers_to_m03_regslice_BRESP;
  wire m03_couplers_to_m03_regslice_BVALID;
  wire [31:0]m03_couplers_to_m03_regslice_RDATA;
  wire m03_couplers_to_m03_regslice_RREADY;
  wire [1:0]m03_couplers_to_m03_regslice_RRESP;
  wire m03_couplers_to_m03_regslice_RVALID;
  wire [31:0]m03_couplers_to_m03_regslice_WDATA;
  wire m03_couplers_to_m03_regslice_WREADY;
  wire [3:0]m03_couplers_to_m03_regslice_WSTRB;
  wire m03_couplers_to_m03_regslice_WVALID;
  wire [5:0]m03_regslice_to_m03_couplers_ARADDR;
  wire m03_regslice_to_m03_couplers_ARREADY;
  wire m03_regslice_to_m03_couplers_ARVALID;
  wire [5:0]m03_regslice_to_m03_couplers_AWADDR;
  wire m03_regslice_to_m03_couplers_AWREADY;
  wire m03_regslice_to_m03_couplers_AWVALID;
  wire m03_regslice_to_m03_couplers_BREADY;
  wire [1:0]m03_regslice_to_m03_couplers_BRESP;
  wire m03_regslice_to_m03_couplers_BVALID;
  wire [31:0]m03_regslice_to_m03_couplers_RDATA;
  wire m03_regslice_to_m03_couplers_RREADY;
  wire [1:0]m03_regslice_to_m03_couplers_RRESP;
  wire m03_regslice_to_m03_couplers_RVALID;
  wire [31:0]m03_regslice_to_m03_couplers_WDATA;
  wire m03_regslice_to_m03_couplers_WREADY;
  wire [3:0]m03_regslice_to_m03_couplers_WSTRB;
  wire m03_regslice_to_m03_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[5:0] = m03_regslice_to_m03_couplers_ARADDR;
  assign M_AXI_arvalid = m03_regslice_to_m03_couplers_ARVALID;
  assign M_AXI_awaddr[5:0] = m03_regslice_to_m03_couplers_AWADDR;
  assign M_AXI_awvalid = m03_regslice_to_m03_couplers_AWVALID;
  assign M_AXI_bready = m03_regslice_to_m03_couplers_BREADY;
  assign M_AXI_rready = m03_regslice_to_m03_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m03_regslice_to_m03_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m03_regslice_to_m03_couplers_WSTRB;
  assign M_AXI_wvalid = m03_regslice_to_m03_couplers_WVALID;
  assign S_AXI_arready = m03_couplers_to_m03_regslice_ARREADY;
  assign S_AXI_awready = m03_couplers_to_m03_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m03_couplers_to_m03_regslice_BRESP;
  assign S_AXI_bvalid = m03_couplers_to_m03_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m03_couplers_to_m03_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m03_couplers_to_m03_regslice_RRESP;
  assign S_AXI_rvalid = m03_couplers_to_m03_regslice_RVALID;
  assign S_AXI_wready = m03_couplers_to_m03_regslice_WREADY;
  assign m03_couplers_to_m03_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m03_couplers_to_m03_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m03_couplers_to_m03_regslice_ARVALID = S_AXI_arvalid;
  assign m03_couplers_to_m03_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m03_couplers_to_m03_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m03_couplers_to_m03_regslice_AWVALID = S_AXI_awvalid;
  assign m03_couplers_to_m03_regslice_BREADY = S_AXI_bready;
  assign m03_couplers_to_m03_regslice_RREADY = S_AXI_rready;
  assign m03_couplers_to_m03_regslice_WDATA = S_AXI_wdata[31:0];
  assign m03_couplers_to_m03_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m03_couplers_to_m03_regslice_WVALID = S_AXI_wvalid;
  assign m03_regslice_to_m03_couplers_ARREADY = M_AXI_arready;
  assign m03_regslice_to_m03_couplers_AWREADY = M_AXI_awready;
  assign m03_regslice_to_m03_couplers_BRESP = M_AXI_bresp[1:0];
  assign m03_regslice_to_m03_couplers_BVALID = M_AXI_bvalid;
  assign m03_regslice_to_m03_couplers_RDATA = M_AXI_rdata[31:0];
  assign m03_regslice_to_m03_couplers_RRESP = M_AXI_rresp[1:0];
  assign m03_regslice_to_m03_couplers_RVALID = M_AXI_rvalid;
  assign m03_regslice_to_m03_couplers_WREADY = M_AXI_wready;
  design_1_m03_regslice_0 m03_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m03_regslice_to_m03_couplers_ARADDR),
        .m_axi_arready(m03_regslice_to_m03_couplers_ARREADY),
        .m_axi_arvalid(m03_regslice_to_m03_couplers_ARVALID),
        .m_axi_awaddr(m03_regslice_to_m03_couplers_AWADDR),
        .m_axi_awready(m03_regslice_to_m03_couplers_AWREADY),
        .m_axi_awvalid(m03_regslice_to_m03_couplers_AWVALID),
        .m_axi_bready(m03_regslice_to_m03_couplers_BREADY),
        .m_axi_bresp(m03_regslice_to_m03_couplers_BRESP),
        .m_axi_bvalid(m03_regslice_to_m03_couplers_BVALID),
        .m_axi_rdata(m03_regslice_to_m03_couplers_RDATA),
        .m_axi_rready(m03_regslice_to_m03_couplers_RREADY),
        .m_axi_rresp(m03_regslice_to_m03_couplers_RRESP),
        .m_axi_rvalid(m03_regslice_to_m03_couplers_RVALID),
        .m_axi_wdata(m03_regslice_to_m03_couplers_WDATA),
        .m_axi_wready(m03_regslice_to_m03_couplers_WREADY),
        .m_axi_wstrb(m03_regslice_to_m03_couplers_WSTRB),
        .m_axi_wvalid(m03_regslice_to_m03_couplers_WVALID),
        .s_axi_araddr(m03_couplers_to_m03_regslice_ARADDR[5:0]),
        .s_axi_arprot(m03_couplers_to_m03_regslice_ARPROT),
        .s_axi_arready(m03_couplers_to_m03_regslice_ARREADY),
        .s_axi_arvalid(m03_couplers_to_m03_regslice_ARVALID),
        .s_axi_awaddr(m03_couplers_to_m03_regslice_AWADDR[5:0]),
        .s_axi_awprot(m03_couplers_to_m03_regslice_AWPROT),
        .s_axi_awready(m03_couplers_to_m03_regslice_AWREADY),
        .s_axi_awvalid(m03_couplers_to_m03_regslice_AWVALID),
        .s_axi_bready(m03_couplers_to_m03_regslice_BREADY),
        .s_axi_bresp(m03_couplers_to_m03_regslice_BRESP),
        .s_axi_bvalid(m03_couplers_to_m03_regslice_BVALID),
        .s_axi_rdata(m03_couplers_to_m03_regslice_RDATA),
        .s_axi_rready(m03_couplers_to_m03_regslice_RREADY),
        .s_axi_rresp(m03_couplers_to_m03_regslice_RRESP),
        .s_axi_rvalid(m03_couplers_to_m03_regslice_RVALID),
        .s_axi_wdata(m03_couplers_to_m03_regslice_WDATA),
        .s_axi_wready(m03_couplers_to_m03_regslice_WREADY),
        .s_axi_wstrb(m03_couplers_to_m03_regslice_WSTRB),
        .s_axi_wvalid(m03_couplers_to_m03_regslice_WVALID));
endmodule

module m04_couplers_imp_5EAXGE
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [17:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [17:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m04_couplers_to_m04_regslice_ARADDR;
  wire [2:0]m04_couplers_to_m04_regslice_ARPROT;
  wire m04_couplers_to_m04_regslice_ARREADY;
  wire m04_couplers_to_m04_regslice_ARVALID;
  wire [39:0]m04_couplers_to_m04_regslice_AWADDR;
  wire [2:0]m04_couplers_to_m04_regslice_AWPROT;
  wire m04_couplers_to_m04_regslice_AWREADY;
  wire m04_couplers_to_m04_regslice_AWVALID;
  wire m04_couplers_to_m04_regslice_BREADY;
  wire [1:0]m04_couplers_to_m04_regslice_BRESP;
  wire m04_couplers_to_m04_regslice_BVALID;
  wire [31:0]m04_couplers_to_m04_regslice_RDATA;
  wire m04_couplers_to_m04_regslice_RREADY;
  wire [1:0]m04_couplers_to_m04_regslice_RRESP;
  wire m04_couplers_to_m04_regslice_RVALID;
  wire [31:0]m04_couplers_to_m04_regslice_WDATA;
  wire m04_couplers_to_m04_regslice_WREADY;
  wire [3:0]m04_couplers_to_m04_regslice_WSTRB;
  wire m04_couplers_to_m04_regslice_WVALID;
  wire [17:0]m04_regslice_to_m04_couplers_ARADDR;
  wire m04_regslice_to_m04_couplers_ARREADY;
  wire m04_regslice_to_m04_couplers_ARVALID;
  wire [17:0]m04_regslice_to_m04_couplers_AWADDR;
  wire m04_regslice_to_m04_couplers_AWREADY;
  wire m04_regslice_to_m04_couplers_AWVALID;
  wire m04_regslice_to_m04_couplers_BREADY;
  wire m04_regslice_to_m04_couplers_BVALID;
  wire [31:0]m04_regslice_to_m04_couplers_RDATA;
  wire m04_regslice_to_m04_couplers_RREADY;
  wire m04_regslice_to_m04_couplers_RVALID;
  wire [31:0]m04_regslice_to_m04_couplers_WDATA;
  wire m04_regslice_to_m04_couplers_WREADY;
  wire m04_regslice_to_m04_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[17:0] = m04_regslice_to_m04_couplers_ARADDR;
  assign M_AXI_arvalid = m04_regslice_to_m04_couplers_ARVALID;
  assign M_AXI_awaddr[17:0] = m04_regslice_to_m04_couplers_AWADDR;
  assign M_AXI_awvalid = m04_regslice_to_m04_couplers_AWVALID;
  assign M_AXI_bready = m04_regslice_to_m04_couplers_BREADY;
  assign M_AXI_rready = m04_regslice_to_m04_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m04_regslice_to_m04_couplers_WDATA;
  assign M_AXI_wvalid = m04_regslice_to_m04_couplers_WVALID;
  assign S_AXI_arready = m04_couplers_to_m04_regslice_ARREADY;
  assign S_AXI_awready = m04_couplers_to_m04_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m04_couplers_to_m04_regslice_BRESP;
  assign S_AXI_bvalid = m04_couplers_to_m04_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m04_couplers_to_m04_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m04_couplers_to_m04_regslice_RRESP;
  assign S_AXI_rvalid = m04_couplers_to_m04_regslice_RVALID;
  assign S_AXI_wready = m04_couplers_to_m04_regslice_WREADY;
  assign m04_couplers_to_m04_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m04_couplers_to_m04_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m04_couplers_to_m04_regslice_ARVALID = S_AXI_arvalid;
  assign m04_couplers_to_m04_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m04_couplers_to_m04_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m04_couplers_to_m04_regslice_AWVALID = S_AXI_awvalid;
  assign m04_couplers_to_m04_regslice_BREADY = S_AXI_bready;
  assign m04_couplers_to_m04_regslice_RREADY = S_AXI_rready;
  assign m04_couplers_to_m04_regslice_WDATA = S_AXI_wdata[31:0];
  assign m04_couplers_to_m04_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m04_couplers_to_m04_regslice_WVALID = S_AXI_wvalid;
  assign m04_regslice_to_m04_couplers_ARREADY = M_AXI_arready;
  assign m04_regslice_to_m04_couplers_AWREADY = M_AXI_awready;
  assign m04_regslice_to_m04_couplers_BVALID = M_AXI_bvalid;
  assign m04_regslice_to_m04_couplers_RDATA = M_AXI_rdata[31:0];
  assign m04_regslice_to_m04_couplers_RVALID = M_AXI_rvalid;
  assign m04_regslice_to_m04_couplers_WREADY = M_AXI_wready;
  design_1_m04_regslice_0 m04_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m04_regslice_to_m04_couplers_ARADDR),
        .m_axi_arready(m04_regslice_to_m04_couplers_ARREADY),
        .m_axi_arvalid(m04_regslice_to_m04_couplers_ARVALID),
        .m_axi_awaddr(m04_regslice_to_m04_couplers_AWADDR),
        .m_axi_awready(m04_regslice_to_m04_couplers_AWREADY),
        .m_axi_awvalid(m04_regslice_to_m04_couplers_AWVALID),
        .m_axi_bready(m04_regslice_to_m04_couplers_BREADY),
        .m_axi_bresp({1'b0,1'b0}),
        .m_axi_bvalid(m04_regslice_to_m04_couplers_BVALID),
        .m_axi_rdata(m04_regslice_to_m04_couplers_RDATA),
        .m_axi_rready(m04_regslice_to_m04_couplers_RREADY),
        .m_axi_rresp({1'b0,1'b0}),
        .m_axi_rvalid(m04_regslice_to_m04_couplers_RVALID),
        .m_axi_wdata(m04_regslice_to_m04_couplers_WDATA),
        .m_axi_wready(m04_regslice_to_m04_couplers_WREADY),
        .m_axi_wvalid(m04_regslice_to_m04_couplers_WVALID),
        .s_axi_araddr(m04_couplers_to_m04_regslice_ARADDR[17:0]),
        .s_axi_arprot(m04_couplers_to_m04_regslice_ARPROT),
        .s_axi_arready(m04_couplers_to_m04_regslice_ARREADY),
        .s_axi_arvalid(m04_couplers_to_m04_regslice_ARVALID),
        .s_axi_awaddr(m04_couplers_to_m04_regslice_AWADDR[17:0]),
        .s_axi_awprot(m04_couplers_to_m04_regslice_AWPROT),
        .s_axi_awready(m04_couplers_to_m04_regslice_AWREADY),
        .s_axi_awvalid(m04_couplers_to_m04_regslice_AWVALID),
        .s_axi_bready(m04_couplers_to_m04_regslice_BREADY),
        .s_axi_bresp(m04_couplers_to_m04_regslice_BRESP),
        .s_axi_bvalid(m04_couplers_to_m04_regslice_BVALID),
        .s_axi_rdata(m04_couplers_to_m04_regslice_RDATA),
        .s_axi_rready(m04_couplers_to_m04_regslice_RREADY),
        .s_axi_rresp(m04_couplers_to_m04_regslice_RRESP),
        .s_axi_rvalid(m04_couplers_to_m04_regslice_RVALID),
        .s_axi_wdata(m04_couplers_to_m04_regslice_WDATA),
        .s_axi_wready(m04_couplers_to_m04_regslice_WREADY),
        .s_axi_wstrb(m04_couplers_to_m04_regslice_WSTRB),
        .s_axi_wvalid(m04_couplers_to_m04_regslice_WVALID));
endmodule

module m05_couplers_imp_1XYGQBJ
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [6:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [6:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m05_couplers_to_m05_regslice_ARADDR;
  wire [2:0]m05_couplers_to_m05_regslice_ARPROT;
  wire m05_couplers_to_m05_regslice_ARREADY;
  wire m05_couplers_to_m05_regslice_ARVALID;
  wire [39:0]m05_couplers_to_m05_regslice_AWADDR;
  wire [2:0]m05_couplers_to_m05_regslice_AWPROT;
  wire m05_couplers_to_m05_regslice_AWREADY;
  wire m05_couplers_to_m05_regslice_AWVALID;
  wire m05_couplers_to_m05_regslice_BREADY;
  wire [1:0]m05_couplers_to_m05_regslice_BRESP;
  wire m05_couplers_to_m05_regslice_BVALID;
  wire [31:0]m05_couplers_to_m05_regslice_RDATA;
  wire m05_couplers_to_m05_regslice_RREADY;
  wire [1:0]m05_couplers_to_m05_regslice_RRESP;
  wire m05_couplers_to_m05_regslice_RVALID;
  wire [31:0]m05_couplers_to_m05_regslice_WDATA;
  wire m05_couplers_to_m05_regslice_WREADY;
  wire [3:0]m05_couplers_to_m05_regslice_WSTRB;
  wire m05_couplers_to_m05_regslice_WVALID;
  wire [6:0]m05_regslice_to_m05_couplers_ARADDR;
  wire m05_regslice_to_m05_couplers_ARREADY;
  wire m05_regslice_to_m05_couplers_ARVALID;
  wire [6:0]m05_regslice_to_m05_couplers_AWADDR;
  wire m05_regslice_to_m05_couplers_AWREADY;
  wire m05_regslice_to_m05_couplers_AWVALID;
  wire m05_regslice_to_m05_couplers_BREADY;
  wire [1:0]m05_regslice_to_m05_couplers_BRESP;
  wire m05_regslice_to_m05_couplers_BVALID;
  wire [31:0]m05_regslice_to_m05_couplers_RDATA;
  wire m05_regslice_to_m05_couplers_RREADY;
  wire [1:0]m05_regslice_to_m05_couplers_RRESP;
  wire m05_regslice_to_m05_couplers_RVALID;
  wire [31:0]m05_regslice_to_m05_couplers_WDATA;
  wire m05_regslice_to_m05_couplers_WREADY;
  wire [3:0]m05_regslice_to_m05_couplers_WSTRB;
  wire m05_regslice_to_m05_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[6:0] = m05_regslice_to_m05_couplers_ARADDR;
  assign M_AXI_arvalid = m05_regslice_to_m05_couplers_ARVALID;
  assign M_AXI_awaddr[6:0] = m05_regslice_to_m05_couplers_AWADDR;
  assign M_AXI_awvalid = m05_regslice_to_m05_couplers_AWVALID;
  assign M_AXI_bready = m05_regslice_to_m05_couplers_BREADY;
  assign M_AXI_rready = m05_regslice_to_m05_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m05_regslice_to_m05_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m05_regslice_to_m05_couplers_WSTRB;
  assign M_AXI_wvalid = m05_regslice_to_m05_couplers_WVALID;
  assign S_AXI_arready = m05_couplers_to_m05_regslice_ARREADY;
  assign S_AXI_awready = m05_couplers_to_m05_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m05_couplers_to_m05_regslice_BRESP;
  assign S_AXI_bvalid = m05_couplers_to_m05_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m05_couplers_to_m05_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m05_couplers_to_m05_regslice_RRESP;
  assign S_AXI_rvalid = m05_couplers_to_m05_regslice_RVALID;
  assign S_AXI_wready = m05_couplers_to_m05_regslice_WREADY;
  assign m05_couplers_to_m05_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m05_couplers_to_m05_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m05_couplers_to_m05_regslice_ARVALID = S_AXI_arvalid;
  assign m05_couplers_to_m05_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m05_couplers_to_m05_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m05_couplers_to_m05_regslice_AWVALID = S_AXI_awvalid;
  assign m05_couplers_to_m05_regslice_BREADY = S_AXI_bready;
  assign m05_couplers_to_m05_regslice_RREADY = S_AXI_rready;
  assign m05_couplers_to_m05_regslice_WDATA = S_AXI_wdata[31:0];
  assign m05_couplers_to_m05_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m05_couplers_to_m05_regslice_WVALID = S_AXI_wvalid;
  assign m05_regslice_to_m05_couplers_ARREADY = M_AXI_arready;
  assign m05_regslice_to_m05_couplers_AWREADY = M_AXI_awready;
  assign m05_regslice_to_m05_couplers_BRESP = M_AXI_bresp[1:0];
  assign m05_regslice_to_m05_couplers_BVALID = M_AXI_bvalid;
  assign m05_regslice_to_m05_couplers_RDATA = M_AXI_rdata[31:0];
  assign m05_regslice_to_m05_couplers_RRESP = M_AXI_rresp[1:0];
  assign m05_regslice_to_m05_couplers_RVALID = M_AXI_rvalid;
  assign m05_regslice_to_m05_couplers_WREADY = M_AXI_wready;
  design_1_m05_regslice_0 m05_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m05_regslice_to_m05_couplers_ARADDR),
        .m_axi_arready(m05_regslice_to_m05_couplers_ARREADY),
        .m_axi_arvalid(m05_regslice_to_m05_couplers_ARVALID),
        .m_axi_awaddr(m05_regslice_to_m05_couplers_AWADDR),
        .m_axi_awready(m05_regslice_to_m05_couplers_AWREADY),
        .m_axi_awvalid(m05_regslice_to_m05_couplers_AWVALID),
        .m_axi_bready(m05_regslice_to_m05_couplers_BREADY),
        .m_axi_bresp(m05_regslice_to_m05_couplers_BRESP),
        .m_axi_bvalid(m05_regslice_to_m05_couplers_BVALID),
        .m_axi_rdata(m05_regslice_to_m05_couplers_RDATA),
        .m_axi_rready(m05_regslice_to_m05_couplers_RREADY),
        .m_axi_rresp(m05_regslice_to_m05_couplers_RRESP),
        .m_axi_rvalid(m05_regslice_to_m05_couplers_RVALID),
        .m_axi_wdata(m05_regslice_to_m05_couplers_WDATA),
        .m_axi_wready(m05_regslice_to_m05_couplers_WREADY),
        .m_axi_wstrb(m05_regslice_to_m05_couplers_WSTRB),
        .m_axi_wvalid(m05_regslice_to_m05_couplers_WVALID),
        .s_axi_araddr(m05_couplers_to_m05_regslice_ARADDR[6:0]),
        .s_axi_arprot(m05_couplers_to_m05_regslice_ARPROT),
        .s_axi_arready(m05_couplers_to_m05_regslice_ARREADY),
        .s_axi_arvalid(m05_couplers_to_m05_regslice_ARVALID),
        .s_axi_awaddr(m05_couplers_to_m05_regslice_AWADDR[6:0]),
        .s_axi_awprot(m05_couplers_to_m05_regslice_AWPROT),
        .s_axi_awready(m05_couplers_to_m05_regslice_AWREADY),
        .s_axi_awvalid(m05_couplers_to_m05_regslice_AWVALID),
        .s_axi_bready(m05_couplers_to_m05_regslice_BREADY),
        .s_axi_bresp(m05_couplers_to_m05_regslice_BRESP),
        .s_axi_bvalid(m05_couplers_to_m05_regslice_BVALID),
        .s_axi_rdata(m05_couplers_to_m05_regslice_RDATA),
        .s_axi_rready(m05_couplers_to_m05_regslice_RREADY),
        .s_axi_rresp(m05_couplers_to_m05_regslice_RRESP),
        .s_axi_rvalid(m05_couplers_to_m05_regslice_RVALID),
        .s_axi_wdata(m05_couplers_to_m05_regslice_WDATA),
        .s_axi_wready(m05_couplers_to_m05_regslice_WREADY),
        .s_axi_wstrb(m05_couplers_to_m05_regslice_WSTRB),
        .s_axi_wvalid(m05_couplers_to_m05_regslice_WVALID));
endmodule

module m06_couplers_imp_6AAJBX
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [8:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [8:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m06_couplers_to_m06_regslice_ARADDR;
  wire [2:0]m06_couplers_to_m06_regslice_ARPROT;
  wire m06_couplers_to_m06_regslice_ARREADY;
  wire m06_couplers_to_m06_regslice_ARVALID;
  wire [39:0]m06_couplers_to_m06_regslice_AWADDR;
  wire [2:0]m06_couplers_to_m06_regslice_AWPROT;
  wire m06_couplers_to_m06_regslice_AWREADY;
  wire m06_couplers_to_m06_regslice_AWVALID;
  wire m06_couplers_to_m06_regslice_BREADY;
  wire [1:0]m06_couplers_to_m06_regslice_BRESP;
  wire m06_couplers_to_m06_regslice_BVALID;
  wire [31:0]m06_couplers_to_m06_regslice_RDATA;
  wire m06_couplers_to_m06_regslice_RREADY;
  wire [1:0]m06_couplers_to_m06_regslice_RRESP;
  wire m06_couplers_to_m06_regslice_RVALID;
  wire [31:0]m06_couplers_to_m06_regslice_WDATA;
  wire m06_couplers_to_m06_regslice_WREADY;
  wire [3:0]m06_couplers_to_m06_regslice_WSTRB;
  wire m06_couplers_to_m06_regslice_WVALID;
  wire [8:0]m06_regslice_to_m06_couplers_ARADDR;
  wire m06_regslice_to_m06_couplers_ARREADY;
  wire m06_regslice_to_m06_couplers_ARVALID;
  wire [8:0]m06_regslice_to_m06_couplers_AWADDR;
  wire m06_regslice_to_m06_couplers_AWREADY;
  wire m06_regslice_to_m06_couplers_AWVALID;
  wire m06_regslice_to_m06_couplers_BREADY;
  wire [1:0]m06_regslice_to_m06_couplers_BRESP;
  wire m06_regslice_to_m06_couplers_BVALID;
  wire [31:0]m06_regslice_to_m06_couplers_RDATA;
  wire m06_regslice_to_m06_couplers_RREADY;
  wire [1:0]m06_regslice_to_m06_couplers_RRESP;
  wire m06_regslice_to_m06_couplers_RVALID;
  wire [31:0]m06_regslice_to_m06_couplers_WDATA;
  wire m06_regslice_to_m06_couplers_WREADY;
  wire [3:0]m06_regslice_to_m06_couplers_WSTRB;
  wire m06_regslice_to_m06_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[8:0] = m06_regslice_to_m06_couplers_ARADDR;
  assign M_AXI_arvalid = m06_regslice_to_m06_couplers_ARVALID;
  assign M_AXI_awaddr[8:0] = m06_regslice_to_m06_couplers_AWADDR;
  assign M_AXI_awvalid = m06_regslice_to_m06_couplers_AWVALID;
  assign M_AXI_bready = m06_regslice_to_m06_couplers_BREADY;
  assign M_AXI_rready = m06_regslice_to_m06_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m06_regslice_to_m06_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m06_regslice_to_m06_couplers_WSTRB;
  assign M_AXI_wvalid = m06_regslice_to_m06_couplers_WVALID;
  assign S_AXI_arready = m06_couplers_to_m06_regslice_ARREADY;
  assign S_AXI_awready = m06_couplers_to_m06_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m06_couplers_to_m06_regslice_BRESP;
  assign S_AXI_bvalid = m06_couplers_to_m06_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m06_couplers_to_m06_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m06_couplers_to_m06_regslice_RRESP;
  assign S_AXI_rvalid = m06_couplers_to_m06_regslice_RVALID;
  assign S_AXI_wready = m06_couplers_to_m06_regslice_WREADY;
  assign m06_couplers_to_m06_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m06_couplers_to_m06_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m06_couplers_to_m06_regslice_ARVALID = S_AXI_arvalid;
  assign m06_couplers_to_m06_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m06_couplers_to_m06_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m06_couplers_to_m06_regslice_AWVALID = S_AXI_awvalid;
  assign m06_couplers_to_m06_regslice_BREADY = S_AXI_bready;
  assign m06_couplers_to_m06_regslice_RREADY = S_AXI_rready;
  assign m06_couplers_to_m06_regslice_WDATA = S_AXI_wdata[31:0];
  assign m06_couplers_to_m06_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m06_couplers_to_m06_regslice_WVALID = S_AXI_wvalid;
  assign m06_regslice_to_m06_couplers_ARREADY = M_AXI_arready;
  assign m06_regslice_to_m06_couplers_AWREADY = M_AXI_awready;
  assign m06_regslice_to_m06_couplers_BRESP = M_AXI_bresp[1:0];
  assign m06_regslice_to_m06_couplers_BVALID = M_AXI_bvalid;
  assign m06_regslice_to_m06_couplers_RDATA = M_AXI_rdata[31:0];
  assign m06_regslice_to_m06_couplers_RRESP = M_AXI_rresp[1:0];
  assign m06_regslice_to_m06_couplers_RVALID = M_AXI_rvalid;
  assign m06_regslice_to_m06_couplers_WREADY = M_AXI_wready;
  design_1_m06_regslice_0 m06_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m06_regslice_to_m06_couplers_ARADDR),
        .m_axi_arready(m06_regslice_to_m06_couplers_ARREADY),
        .m_axi_arvalid(m06_regslice_to_m06_couplers_ARVALID),
        .m_axi_awaddr(m06_regslice_to_m06_couplers_AWADDR),
        .m_axi_awready(m06_regslice_to_m06_couplers_AWREADY),
        .m_axi_awvalid(m06_regslice_to_m06_couplers_AWVALID),
        .m_axi_bready(m06_regslice_to_m06_couplers_BREADY),
        .m_axi_bresp(m06_regslice_to_m06_couplers_BRESP),
        .m_axi_bvalid(m06_regslice_to_m06_couplers_BVALID),
        .m_axi_rdata(m06_regslice_to_m06_couplers_RDATA),
        .m_axi_rready(m06_regslice_to_m06_couplers_RREADY),
        .m_axi_rresp(m06_regslice_to_m06_couplers_RRESP),
        .m_axi_rvalid(m06_regslice_to_m06_couplers_RVALID),
        .m_axi_wdata(m06_regslice_to_m06_couplers_WDATA),
        .m_axi_wready(m06_regslice_to_m06_couplers_WREADY),
        .m_axi_wstrb(m06_regslice_to_m06_couplers_WSTRB),
        .m_axi_wvalid(m06_regslice_to_m06_couplers_WVALID),
        .s_axi_araddr(m06_couplers_to_m06_regslice_ARADDR[8:0]),
        .s_axi_arprot(m06_couplers_to_m06_regslice_ARPROT),
        .s_axi_arready(m06_couplers_to_m06_regslice_ARREADY),
        .s_axi_arvalid(m06_couplers_to_m06_regslice_ARVALID),
        .s_axi_awaddr(m06_couplers_to_m06_regslice_AWADDR[8:0]),
        .s_axi_awprot(m06_couplers_to_m06_regslice_AWPROT),
        .s_axi_awready(m06_couplers_to_m06_regslice_AWREADY),
        .s_axi_awvalid(m06_couplers_to_m06_regslice_AWVALID),
        .s_axi_bready(m06_couplers_to_m06_regslice_BREADY),
        .s_axi_bresp(m06_couplers_to_m06_regslice_BRESP),
        .s_axi_bvalid(m06_couplers_to_m06_regslice_BVALID),
        .s_axi_rdata(m06_couplers_to_m06_regslice_RDATA),
        .s_axi_rready(m06_couplers_to_m06_regslice_RREADY),
        .s_axi_rresp(m06_couplers_to_m06_regslice_RRESP),
        .s_axi_rvalid(m06_couplers_to_m06_regslice_RVALID),
        .s_axi_wdata(m06_couplers_to_m06_regslice_WDATA),
        .s_axi_wready(m06_couplers_to_m06_regslice_WREADY),
        .s_axi_wstrb(m06_couplers_to_m06_regslice_WSTRB),
        .s_axi_wvalid(m06_couplers_to_m06_regslice_WVALID));
endmodule

module m07_couplers_imp_1XCR5J0
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [5:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [5:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m07_couplers_to_m07_regslice_ARADDR;
  wire [2:0]m07_couplers_to_m07_regslice_ARPROT;
  wire m07_couplers_to_m07_regslice_ARREADY;
  wire m07_couplers_to_m07_regslice_ARVALID;
  wire [39:0]m07_couplers_to_m07_regslice_AWADDR;
  wire [2:0]m07_couplers_to_m07_regslice_AWPROT;
  wire m07_couplers_to_m07_regslice_AWREADY;
  wire m07_couplers_to_m07_regslice_AWVALID;
  wire m07_couplers_to_m07_regslice_BREADY;
  wire [1:0]m07_couplers_to_m07_regslice_BRESP;
  wire m07_couplers_to_m07_regslice_BVALID;
  wire [31:0]m07_couplers_to_m07_regslice_RDATA;
  wire m07_couplers_to_m07_regslice_RREADY;
  wire [1:0]m07_couplers_to_m07_regslice_RRESP;
  wire m07_couplers_to_m07_regslice_RVALID;
  wire [31:0]m07_couplers_to_m07_regslice_WDATA;
  wire m07_couplers_to_m07_regslice_WREADY;
  wire [3:0]m07_couplers_to_m07_regslice_WSTRB;
  wire m07_couplers_to_m07_regslice_WVALID;
  wire [5:0]m07_regslice_to_m07_couplers_ARADDR;
  wire m07_regslice_to_m07_couplers_ARREADY;
  wire m07_regslice_to_m07_couplers_ARVALID;
  wire [5:0]m07_regslice_to_m07_couplers_AWADDR;
  wire m07_regslice_to_m07_couplers_AWREADY;
  wire m07_regslice_to_m07_couplers_AWVALID;
  wire m07_regslice_to_m07_couplers_BREADY;
  wire [1:0]m07_regslice_to_m07_couplers_BRESP;
  wire m07_regslice_to_m07_couplers_BVALID;
  wire [31:0]m07_regslice_to_m07_couplers_RDATA;
  wire m07_regslice_to_m07_couplers_RREADY;
  wire [1:0]m07_regslice_to_m07_couplers_RRESP;
  wire m07_regslice_to_m07_couplers_RVALID;
  wire [31:0]m07_regslice_to_m07_couplers_WDATA;
  wire m07_regslice_to_m07_couplers_WREADY;
  wire [3:0]m07_regslice_to_m07_couplers_WSTRB;
  wire m07_regslice_to_m07_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[5:0] = m07_regslice_to_m07_couplers_ARADDR;
  assign M_AXI_arvalid = m07_regslice_to_m07_couplers_ARVALID;
  assign M_AXI_awaddr[5:0] = m07_regslice_to_m07_couplers_AWADDR;
  assign M_AXI_awvalid = m07_regslice_to_m07_couplers_AWVALID;
  assign M_AXI_bready = m07_regslice_to_m07_couplers_BREADY;
  assign M_AXI_rready = m07_regslice_to_m07_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m07_regslice_to_m07_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m07_regslice_to_m07_couplers_WSTRB;
  assign M_AXI_wvalid = m07_regslice_to_m07_couplers_WVALID;
  assign S_AXI_arready = m07_couplers_to_m07_regslice_ARREADY;
  assign S_AXI_awready = m07_couplers_to_m07_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m07_couplers_to_m07_regslice_BRESP;
  assign S_AXI_bvalid = m07_couplers_to_m07_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m07_couplers_to_m07_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m07_couplers_to_m07_regslice_RRESP;
  assign S_AXI_rvalid = m07_couplers_to_m07_regslice_RVALID;
  assign S_AXI_wready = m07_couplers_to_m07_regslice_WREADY;
  assign m07_couplers_to_m07_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m07_couplers_to_m07_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m07_couplers_to_m07_regslice_ARVALID = S_AXI_arvalid;
  assign m07_couplers_to_m07_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m07_couplers_to_m07_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m07_couplers_to_m07_regslice_AWVALID = S_AXI_awvalid;
  assign m07_couplers_to_m07_regslice_BREADY = S_AXI_bready;
  assign m07_couplers_to_m07_regslice_RREADY = S_AXI_rready;
  assign m07_couplers_to_m07_regslice_WDATA = S_AXI_wdata[31:0];
  assign m07_couplers_to_m07_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m07_couplers_to_m07_regslice_WVALID = S_AXI_wvalid;
  assign m07_regslice_to_m07_couplers_ARREADY = M_AXI_arready;
  assign m07_regslice_to_m07_couplers_AWREADY = M_AXI_awready;
  assign m07_regslice_to_m07_couplers_BRESP = M_AXI_bresp[1:0];
  assign m07_regslice_to_m07_couplers_BVALID = M_AXI_bvalid;
  assign m07_regslice_to_m07_couplers_RDATA = M_AXI_rdata[31:0];
  assign m07_regslice_to_m07_couplers_RRESP = M_AXI_rresp[1:0];
  assign m07_regslice_to_m07_couplers_RVALID = M_AXI_rvalid;
  assign m07_regslice_to_m07_couplers_WREADY = M_AXI_wready;
  design_1_m07_regslice_0 m07_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m07_regslice_to_m07_couplers_ARADDR),
        .m_axi_arready(m07_regslice_to_m07_couplers_ARREADY),
        .m_axi_arvalid(m07_regslice_to_m07_couplers_ARVALID),
        .m_axi_awaddr(m07_regslice_to_m07_couplers_AWADDR),
        .m_axi_awready(m07_regslice_to_m07_couplers_AWREADY),
        .m_axi_awvalid(m07_regslice_to_m07_couplers_AWVALID),
        .m_axi_bready(m07_regslice_to_m07_couplers_BREADY),
        .m_axi_bresp(m07_regslice_to_m07_couplers_BRESP),
        .m_axi_bvalid(m07_regslice_to_m07_couplers_BVALID),
        .m_axi_rdata(m07_regslice_to_m07_couplers_RDATA),
        .m_axi_rready(m07_regslice_to_m07_couplers_RREADY),
        .m_axi_rresp(m07_regslice_to_m07_couplers_RRESP),
        .m_axi_rvalid(m07_regslice_to_m07_couplers_RVALID),
        .m_axi_wdata(m07_regslice_to_m07_couplers_WDATA),
        .m_axi_wready(m07_regslice_to_m07_couplers_WREADY),
        .m_axi_wstrb(m07_regslice_to_m07_couplers_WSTRB),
        .m_axi_wvalid(m07_regslice_to_m07_couplers_WVALID),
        .s_axi_araddr(m07_couplers_to_m07_regslice_ARADDR[5:0]),
        .s_axi_arprot(m07_couplers_to_m07_regslice_ARPROT),
        .s_axi_arready(m07_couplers_to_m07_regslice_ARREADY),
        .s_axi_arvalid(m07_couplers_to_m07_regslice_ARVALID),
        .s_axi_awaddr(m07_couplers_to_m07_regslice_AWADDR[5:0]),
        .s_axi_awprot(m07_couplers_to_m07_regslice_AWPROT),
        .s_axi_awready(m07_couplers_to_m07_regslice_AWREADY),
        .s_axi_awvalid(m07_couplers_to_m07_regslice_AWVALID),
        .s_axi_bready(m07_couplers_to_m07_regslice_BREADY),
        .s_axi_bresp(m07_couplers_to_m07_regslice_BRESP),
        .s_axi_bvalid(m07_couplers_to_m07_regslice_BVALID),
        .s_axi_rdata(m07_couplers_to_m07_regslice_RDATA),
        .s_axi_rready(m07_couplers_to_m07_regslice_RREADY),
        .s_axi_rresp(m07_couplers_to_m07_regslice_RRESP),
        .s_axi_rvalid(m07_couplers_to_m07_regslice_RVALID),
        .s_axi_wdata(m07_couplers_to_m07_regslice_WDATA),
        .s_axi_wready(m07_couplers_to_m07_regslice_WREADY),
        .s_axi_wstrb(m07_couplers_to_m07_regslice_WSTRB),
        .s_axi_wvalid(m07_couplers_to_m07_regslice_WVALID));
endmodule

module m08_couplers_imp_4B8Q1G
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [5:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [5:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m08_couplers_to_m08_regslice_ARADDR;
  wire [2:0]m08_couplers_to_m08_regslice_ARPROT;
  wire m08_couplers_to_m08_regslice_ARREADY;
  wire m08_couplers_to_m08_regslice_ARVALID;
  wire [39:0]m08_couplers_to_m08_regslice_AWADDR;
  wire [2:0]m08_couplers_to_m08_regslice_AWPROT;
  wire m08_couplers_to_m08_regslice_AWREADY;
  wire m08_couplers_to_m08_regslice_AWVALID;
  wire m08_couplers_to_m08_regslice_BREADY;
  wire [1:0]m08_couplers_to_m08_regslice_BRESP;
  wire m08_couplers_to_m08_regslice_BVALID;
  wire [31:0]m08_couplers_to_m08_regslice_RDATA;
  wire m08_couplers_to_m08_regslice_RREADY;
  wire [1:0]m08_couplers_to_m08_regslice_RRESP;
  wire m08_couplers_to_m08_regslice_RVALID;
  wire [31:0]m08_couplers_to_m08_regslice_WDATA;
  wire m08_couplers_to_m08_regslice_WREADY;
  wire [3:0]m08_couplers_to_m08_regslice_WSTRB;
  wire m08_couplers_to_m08_regslice_WVALID;
  wire [5:0]m08_regslice_to_m08_couplers_ARADDR;
  wire m08_regslice_to_m08_couplers_ARREADY;
  wire m08_regslice_to_m08_couplers_ARVALID;
  wire [5:0]m08_regslice_to_m08_couplers_AWADDR;
  wire m08_regslice_to_m08_couplers_AWREADY;
  wire m08_regslice_to_m08_couplers_AWVALID;
  wire m08_regslice_to_m08_couplers_BREADY;
  wire [1:0]m08_regslice_to_m08_couplers_BRESP;
  wire m08_regslice_to_m08_couplers_BVALID;
  wire [31:0]m08_regslice_to_m08_couplers_RDATA;
  wire m08_regslice_to_m08_couplers_RREADY;
  wire [1:0]m08_regslice_to_m08_couplers_RRESP;
  wire m08_regslice_to_m08_couplers_RVALID;
  wire [31:0]m08_regslice_to_m08_couplers_WDATA;
  wire m08_regslice_to_m08_couplers_WREADY;
  wire [3:0]m08_regslice_to_m08_couplers_WSTRB;
  wire m08_regslice_to_m08_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[5:0] = m08_regslice_to_m08_couplers_ARADDR;
  assign M_AXI_arvalid = m08_regslice_to_m08_couplers_ARVALID;
  assign M_AXI_awaddr[5:0] = m08_regslice_to_m08_couplers_AWADDR;
  assign M_AXI_awvalid = m08_regslice_to_m08_couplers_AWVALID;
  assign M_AXI_bready = m08_regslice_to_m08_couplers_BREADY;
  assign M_AXI_rready = m08_regslice_to_m08_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m08_regslice_to_m08_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m08_regslice_to_m08_couplers_WSTRB;
  assign M_AXI_wvalid = m08_regslice_to_m08_couplers_WVALID;
  assign S_AXI_arready = m08_couplers_to_m08_regslice_ARREADY;
  assign S_AXI_awready = m08_couplers_to_m08_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m08_couplers_to_m08_regslice_BRESP;
  assign S_AXI_bvalid = m08_couplers_to_m08_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m08_couplers_to_m08_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m08_couplers_to_m08_regslice_RRESP;
  assign S_AXI_rvalid = m08_couplers_to_m08_regslice_RVALID;
  assign S_AXI_wready = m08_couplers_to_m08_regslice_WREADY;
  assign m08_couplers_to_m08_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m08_couplers_to_m08_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m08_couplers_to_m08_regslice_ARVALID = S_AXI_arvalid;
  assign m08_couplers_to_m08_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m08_couplers_to_m08_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m08_couplers_to_m08_regslice_AWVALID = S_AXI_awvalid;
  assign m08_couplers_to_m08_regslice_BREADY = S_AXI_bready;
  assign m08_couplers_to_m08_regslice_RREADY = S_AXI_rready;
  assign m08_couplers_to_m08_regslice_WDATA = S_AXI_wdata[31:0];
  assign m08_couplers_to_m08_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m08_couplers_to_m08_regslice_WVALID = S_AXI_wvalid;
  assign m08_regslice_to_m08_couplers_ARREADY = M_AXI_arready;
  assign m08_regslice_to_m08_couplers_AWREADY = M_AXI_awready;
  assign m08_regslice_to_m08_couplers_BRESP = M_AXI_bresp[1:0];
  assign m08_regslice_to_m08_couplers_BVALID = M_AXI_bvalid;
  assign m08_regslice_to_m08_couplers_RDATA = M_AXI_rdata[31:0];
  assign m08_regslice_to_m08_couplers_RRESP = M_AXI_rresp[1:0];
  assign m08_regslice_to_m08_couplers_RVALID = M_AXI_rvalid;
  assign m08_regslice_to_m08_couplers_WREADY = M_AXI_wready;
  design_1_m08_regslice_0 m08_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m08_regslice_to_m08_couplers_ARADDR),
        .m_axi_arready(m08_regslice_to_m08_couplers_ARREADY),
        .m_axi_arvalid(m08_regslice_to_m08_couplers_ARVALID),
        .m_axi_awaddr(m08_regslice_to_m08_couplers_AWADDR),
        .m_axi_awready(m08_regslice_to_m08_couplers_AWREADY),
        .m_axi_awvalid(m08_regslice_to_m08_couplers_AWVALID),
        .m_axi_bready(m08_regslice_to_m08_couplers_BREADY),
        .m_axi_bresp(m08_regslice_to_m08_couplers_BRESP),
        .m_axi_bvalid(m08_regslice_to_m08_couplers_BVALID),
        .m_axi_rdata(m08_regslice_to_m08_couplers_RDATA),
        .m_axi_rready(m08_regslice_to_m08_couplers_RREADY),
        .m_axi_rresp(m08_regslice_to_m08_couplers_RRESP),
        .m_axi_rvalid(m08_regslice_to_m08_couplers_RVALID),
        .m_axi_wdata(m08_regslice_to_m08_couplers_WDATA),
        .m_axi_wready(m08_regslice_to_m08_couplers_WREADY),
        .m_axi_wstrb(m08_regslice_to_m08_couplers_WSTRB),
        .m_axi_wvalid(m08_regslice_to_m08_couplers_WVALID),
        .s_axi_araddr(m08_couplers_to_m08_regslice_ARADDR[5:0]),
        .s_axi_arprot(m08_couplers_to_m08_regslice_ARPROT),
        .s_axi_arready(m08_couplers_to_m08_regslice_ARREADY),
        .s_axi_arvalid(m08_couplers_to_m08_regslice_ARVALID),
        .s_axi_awaddr(m08_couplers_to_m08_regslice_AWADDR[5:0]),
        .s_axi_awprot(m08_couplers_to_m08_regslice_AWPROT),
        .s_axi_awready(m08_couplers_to_m08_regslice_AWREADY),
        .s_axi_awvalid(m08_couplers_to_m08_regslice_AWVALID),
        .s_axi_bready(m08_couplers_to_m08_regslice_BREADY),
        .s_axi_bresp(m08_couplers_to_m08_regslice_BRESP),
        .s_axi_bvalid(m08_couplers_to_m08_regslice_BVALID),
        .s_axi_rdata(m08_couplers_to_m08_regslice_RDATA),
        .s_axi_rready(m08_couplers_to_m08_regslice_RREADY),
        .s_axi_rresp(m08_couplers_to_m08_regslice_RRESP),
        .s_axi_rvalid(m08_couplers_to_m08_regslice_RVALID),
        .s_axi_wdata(m08_couplers_to_m08_regslice_WDATA),
        .s_axi_wready(m08_couplers_to_m08_regslice_WREADY),
        .s_axi_wstrb(m08_couplers_to_m08_regslice_WSTRB),
        .s_axi_wvalid(m08_couplers_to_m08_regslice_WVALID));
endmodule

module m09_couplers_imp_1QDWHMD
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [8:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [8:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m09_couplers_to_m09_regslice_ARADDR;
  wire [2:0]m09_couplers_to_m09_regslice_ARPROT;
  wire m09_couplers_to_m09_regslice_ARREADY;
  wire m09_couplers_to_m09_regslice_ARVALID;
  wire [39:0]m09_couplers_to_m09_regslice_AWADDR;
  wire [2:0]m09_couplers_to_m09_regslice_AWPROT;
  wire m09_couplers_to_m09_regslice_AWREADY;
  wire m09_couplers_to_m09_regslice_AWVALID;
  wire m09_couplers_to_m09_regslice_BREADY;
  wire [1:0]m09_couplers_to_m09_regslice_BRESP;
  wire m09_couplers_to_m09_regslice_BVALID;
  wire [31:0]m09_couplers_to_m09_regslice_RDATA;
  wire m09_couplers_to_m09_regslice_RREADY;
  wire [1:0]m09_couplers_to_m09_regslice_RRESP;
  wire m09_couplers_to_m09_regslice_RVALID;
  wire [31:0]m09_couplers_to_m09_regslice_WDATA;
  wire m09_couplers_to_m09_regslice_WREADY;
  wire [3:0]m09_couplers_to_m09_regslice_WSTRB;
  wire m09_couplers_to_m09_regslice_WVALID;
  wire [8:0]m09_regslice_to_m09_couplers_ARADDR;
  wire m09_regslice_to_m09_couplers_ARREADY;
  wire m09_regslice_to_m09_couplers_ARVALID;
  wire [8:0]m09_regslice_to_m09_couplers_AWADDR;
  wire m09_regslice_to_m09_couplers_AWREADY;
  wire m09_regslice_to_m09_couplers_AWVALID;
  wire m09_regslice_to_m09_couplers_BREADY;
  wire [1:0]m09_regslice_to_m09_couplers_BRESP;
  wire m09_regslice_to_m09_couplers_BVALID;
  wire [31:0]m09_regslice_to_m09_couplers_RDATA;
  wire m09_regslice_to_m09_couplers_RREADY;
  wire [1:0]m09_regslice_to_m09_couplers_RRESP;
  wire m09_regslice_to_m09_couplers_RVALID;
  wire [31:0]m09_regslice_to_m09_couplers_WDATA;
  wire m09_regslice_to_m09_couplers_WREADY;
  wire [3:0]m09_regslice_to_m09_couplers_WSTRB;
  wire m09_regslice_to_m09_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[8:0] = m09_regslice_to_m09_couplers_ARADDR;
  assign M_AXI_arvalid = m09_regslice_to_m09_couplers_ARVALID;
  assign M_AXI_awaddr[8:0] = m09_regslice_to_m09_couplers_AWADDR;
  assign M_AXI_awvalid = m09_regslice_to_m09_couplers_AWVALID;
  assign M_AXI_bready = m09_regslice_to_m09_couplers_BREADY;
  assign M_AXI_rready = m09_regslice_to_m09_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m09_regslice_to_m09_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m09_regslice_to_m09_couplers_WSTRB;
  assign M_AXI_wvalid = m09_regslice_to_m09_couplers_WVALID;
  assign S_AXI_arready = m09_couplers_to_m09_regslice_ARREADY;
  assign S_AXI_awready = m09_couplers_to_m09_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m09_couplers_to_m09_regslice_BRESP;
  assign S_AXI_bvalid = m09_couplers_to_m09_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m09_couplers_to_m09_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m09_couplers_to_m09_regslice_RRESP;
  assign S_AXI_rvalid = m09_couplers_to_m09_regslice_RVALID;
  assign S_AXI_wready = m09_couplers_to_m09_regslice_WREADY;
  assign m09_couplers_to_m09_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m09_couplers_to_m09_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m09_couplers_to_m09_regslice_ARVALID = S_AXI_arvalid;
  assign m09_couplers_to_m09_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m09_couplers_to_m09_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m09_couplers_to_m09_regslice_AWVALID = S_AXI_awvalid;
  assign m09_couplers_to_m09_regslice_BREADY = S_AXI_bready;
  assign m09_couplers_to_m09_regslice_RREADY = S_AXI_rready;
  assign m09_couplers_to_m09_regslice_WDATA = S_AXI_wdata[31:0];
  assign m09_couplers_to_m09_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m09_couplers_to_m09_regslice_WVALID = S_AXI_wvalid;
  assign m09_regslice_to_m09_couplers_ARREADY = M_AXI_arready;
  assign m09_regslice_to_m09_couplers_AWREADY = M_AXI_awready;
  assign m09_regslice_to_m09_couplers_BRESP = M_AXI_bresp[1:0];
  assign m09_regslice_to_m09_couplers_BVALID = M_AXI_bvalid;
  assign m09_regslice_to_m09_couplers_RDATA = M_AXI_rdata[31:0];
  assign m09_regslice_to_m09_couplers_RRESP = M_AXI_rresp[1:0];
  assign m09_regslice_to_m09_couplers_RVALID = M_AXI_rvalid;
  assign m09_regslice_to_m09_couplers_WREADY = M_AXI_wready;
  design_1_m09_regslice_0 m09_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m09_regslice_to_m09_couplers_ARADDR),
        .m_axi_arready(m09_regslice_to_m09_couplers_ARREADY),
        .m_axi_arvalid(m09_regslice_to_m09_couplers_ARVALID),
        .m_axi_awaddr(m09_regslice_to_m09_couplers_AWADDR),
        .m_axi_awready(m09_regslice_to_m09_couplers_AWREADY),
        .m_axi_awvalid(m09_regslice_to_m09_couplers_AWVALID),
        .m_axi_bready(m09_regslice_to_m09_couplers_BREADY),
        .m_axi_bresp(m09_regslice_to_m09_couplers_BRESP),
        .m_axi_bvalid(m09_regslice_to_m09_couplers_BVALID),
        .m_axi_rdata(m09_regslice_to_m09_couplers_RDATA),
        .m_axi_rready(m09_regslice_to_m09_couplers_RREADY),
        .m_axi_rresp(m09_regslice_to_m09_couplers_RRESP),
        .m_axi_rvalid(m09_regslice_to_m09_couplers_RVALID),
        .m_axi_wdata(m09_regslice_to_m09_couplers_WDATA),
        .m_axi_wready(m09_regslice_to_m09_couplers_WREADY),
        .m_axi_wstrb(m09_regslice_to_m09_couplers_WSTRB),
        .m_axi_wvalid(m09_regslice_to_m09_couplers_WVALID),
        .s_axi_araddr(m09_couplers_to_m09_regslice_ARADDR[8:0]),
        .s_axi_arprot(m09_couplers_to_m09_regslice_ARPROT),
        .s_axi_arready(m09_couplers_to_m09_regslice_ARREADY),
        .s_axi_arvalid(m09_couplers_to_m09_regslice_ARVALID),
        .s_axi_awaddr(m09_couplers_to_m09_regslice_AWADDR[8:0]),
        .s_axi_awprot(m09_couplers_to_m09_regslice_AWPROT),
        .s_axi_awready(m09_couplers_to_m09_regslice_AWREADY),
        .s_axi_awvalid(m09_couplers_to_m09_regslice_AWVALID),
        .s_axi_bready(m09_couplers_to_m09_regslice_BREADY),
        .s_axi_bresp(m09_couplers_to_m09_regslice_BRESP),
        .s_axi_bvalid(m09_couplers_to_m09_regslice_BVALID),
        .s_axi_rdata(m09_couplers_to_m09_regslice_RDATA),
        .s_axi_rready(m09_couplers_to_m09_regslice_RREADY),
        .s_axi_rresp(m09_couplers_to_m09_regslice_RRESP),
        .s_axi_rvalid(m09_couplers_to_m09_regslice_RVALID),
        .s_axi_wdata(m09_couplers_to_m09_regslice_WDATA),
        .s_axi_wready(m09_couplers_to_m09_regslice_WREADY),
        .s_axi_wstrb(m09_couplers_to_m09_regslice_WSTRB),
        .s_axi_wvalid(m09_couplers_to_m09_regslice_WVALID));
endmodule

module m10_couplers_imp_1LHWVWG
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arprot,
    S_AXI_arready,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awprot,
    S_AXI_awready,
    S_AXI_awvalid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [8:0]M_AXI_araddr;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [8:0]M_AXI_awaddr;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [2:0]S_AXI_arprot;
  output S_AXI_arready;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [2:0]S_AXI_awprot;
  output S_AXI_awready;
  input S_AXI_awvalid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [31:0]S_AXI_rdata;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [31:0]S_AXI_wdata;
  output S_AXI_wready;
  input [3:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire [39:0]m10_couplers_to_m10_regslice_ARADDR;
  wire [2:0]m10_couplers_to_m10_regslice_ARPROT;
  wire m10_couplers_to_m10_regslice_ARREADY;
  wire m10_couplers_to_m10_regslice_ARVALID;
  wire [39:0]m10_couplers_to_m10_regslice_AWADDR;
  wire [2:0]m10_couplers_to_m10_regslice_AWPROT;
  wire m10_couplers_to_m10_regslice_AWREADY;
  wire m10_couplers_to_m10_regslice_AWVALID;
  wire m10_couplers_to_m10_regslice_BREADY;
  wire [1:0]m10_couplers_to_m10_regslice_BRESP;
  wire m10_couplers_to_m10_regslice_BVALID;
  wire [31:0]m10_couplers_to_m10_regslice_RDATA;
  wire m10_couplers_to_m10_regslice_RREADY;
  wire [1:0]m10_couplers_to_m10_regslice_RRESP;
  wire m10_couplers_to_m10_regslice_RVALID;
  wire [31:0]m10_couplers_to_m10_regslice_WDATA;
  wire m10_couplers_to_m10_regslice_WREADY;
  wire [3:0]m10_couplers_to_m10_regslice_WSTRB;
  wire m10_couplers_to_m10_regslice_WVALID;
  wire [8:0]m10_regslice_to_m10_couplers_ARADDR;
  wire m10_regslice_to_m10_couplers_ARREADY;
  wire m10_regslice_to_m10_couplers_ARVALID;
  wire [8:0]m10_regslice_to_m10_couplers_AWADDR;
  wire m10_regslice_to_m10_couplers_AWREADY;
  wire m10_regslice_to_m10_couplers_AWVALID;
  wire m10_regslice_to_m10_couplers_BREADY;
  wire [1:0]m10_regslice_to_m10_couplers_BRESP;
  wire m10_regslice_to_m10_couplers_BVALID;
  wire [31:0]m10_regslice_to_m10_couplers_RDATA;
  wire m10_regslice_to_m10_couplers_RREADY;
  wire [1:0]m10_regslice_to_m10_couplers_RRESP;
  wire m10_regslice_to_m10_couplers_RVALID;
  wire [31:0]m10_regslice_to_m10_couplers_WDATA;
  wire m10_regslice_to_m10_couplers_WREADY;
  wire [3:0]m10_regslice_to_m10_couplers_WSTRB;
  wire m10_regslice_to_m10_couplers_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[8:0] = m10_regslice_to_m10_couplers_ARADDR;
  assign M_AXI_arvalid = m10_regslice_to_m10_couplers_ARVALID;
  assign M_AXI_awaddr[8:0] = m10_regslice_to_m10_couplers_AWADDR;
  assign M_AXI_awvalid = m10_regslice_to_m10_couplers_AWVALID;
  assign M_AXI_bready = m10_regslice_to_m10_couplers_BREADY;
  assign M_AXI_rready = m10_regslice_to_m10_couplers_RREADY;
  assign M_AXI_wdata[31:0] = m10_regslice_to_m10_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = m10_regslice_to_m10_couplers_WSTRB;
  assign M_AXI_wvalid = m10_regslice_to_m10_couplers_WVALID;
  assign S_AXI_arready = m10_couplers_to_m10_regslice_ARREADY;
  assign S_AXI_awready = m10_couplers_to_m10_regslice_AWREADY;
  assign S_AXI_bresp[1:0] = m10_couplers_to_m10_regslice_BRESP;
  assign S_AXI_bvalid = m10_couplers_to_m10_regslice_BVALID;
  assign S_AXI_rdata[31:0] = m10_couplers_to_m10_regslice_RDATA;
  assign S_AXI_rresp[1:0] = m10_couplers_to_m10_regslice_RRESP;
  assign S_AXI_rvalid = m10_couplers_to_m10_regslice_RVALID;
  assign S_AXI_wready = m10_couplers_to_m10_regslice_WREADY;
  assign m10_couplers_to_m10_regslice_ARADDR = S_AXI_araddr[39:0];
  assign m10_couplers_to_m10_regslice_ARPROT = S_AXI_arprot[2:0];
  assign m10_couplers_to_m10_regslice_ARVALID = S_AXI_arvalid;
  assign m10_couplers_to_m10_regslice_AWADDR = S_AXI_awaddr[39:0];
  assign m10_couplers_to_m10_regslice_AWPROT = S_AXI_awprot[2:0];
  assign m10_couplers_to_m10_regslice_AWVALID = S_AXI_awvalid;
  assign m10_couplers_to_m10_regslice_BREADY = S_AXI_bready;
  assign m10_couplers_to_m10_regslice_RREADY = S_AXI_rready;
  assign m10_couplers_to_m10_regslice_WDATA = S_AXI_wdata[31:0];
  assign m10_couplers_to_m10_regslice_WSTRB = S_AXI_wstrb[3:0];
  assign m10_couplers_to_m10_regslice_WVALID = S_AXI_wvalid;
  assign m10_regslice_to_m10_couplers_ARREADY = M_AXI_arready;
  assign m10_regslice_to_m10_couplers_AWREADY = M_AXI_awready;
  assign m10_regslice_to_m10_couplers_BRESP = M_AXI_bresp[1:0];
  assign m10_regslice_to_m10_couplers_BVALID = M_AXI_bvalid;
  assign m10_regslice_to_m10_couplers_RDATA = M_AXI_rdata[31:0];
  assign m10_regslice_to_m10_couplers_RRESP = M_AXI_rresp[1:0];
  assign m10_regslice_to_m10_couplers_RVALID = M_AXI_rvalid;
  assign m10_regslice_to_m10_couplers_WREADY = M_AXI_wready;
  design_1_m10_regslice_0 m10_regslice
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(m10_regslice_to_m10_couplers_ARADDR),
        .m_axi_arready(m10_regslice_to_m10_couplers_ARREADY),
        .m_axi_arvalid(m10_regslice_to_m10_couplers_ARVALID),
        .m_axi_awaddr(m10_regslice_to_m10_couplers_AWADDR),
        .m_axi_awready(m10_regslice_to_m10_couplers_AWREADY),
        .m_axi_awvalid(m10_regslice_to_m10_couplers_AWVALID),
        .m_axi_bready(m10_regslice_to_m10_couplers_BREADY),
        .m_axi_bresp(m10_regslice_to_m10_couplers_BRESP),
        .m_axi_bvalid(m10_regslice_to_m10_couplers_BVALID),
        .m_axi_rdata(m10_regslice_to_m10_couplers_RDATA),
        .m_axi_rready(m10_regslice_to_m10_couplers_RREADY),
        .m_axi_rresp(m10_regslice_to_m10_couplers_RRESP),
        .m_axi_rvalid(m10_regslice_to_m10_couplers_RVALID),
        .m_axi_wdata(m10_regslice_to_m10_couplers_WDATA),
        .m_axi_wready(m10_regslice_to_m10_couplers_WREADY),
        .m_axi_wstrb(m10_regslice_to_m10_couplers_WSTRB),
        .m_axi_wvalid(m10_regslice_to_m10_couplers_WVALID),
        .s_axi_araddr(m10_couplers_to_m10_regslice_ARADDR[8:0]),
        .s_axi_arprot(m10_couplers_to_m10_regslice_ARPROT),
        .s_axi_arready(m10_couplers_to_m10_regslice_ARREADY),
        .s_axi_arvalid(m10_couplers_to_m10_regslice_ARVALID),
        .s_axi_awaddr(m10_couplers_to_m10_regslice_AWADDR[8:0]),
        .s_axi_awprot(m10_couplers_to_m10_regslice_AWPROT),
        .s_axi_awready(m10_couplers_to_m10_regslice_AWREADY),
        .s_axi_awvalid(m10_couplers_to_m10_regslice_AWVALID),
        .s_axi_bready(m10_couplers_to_m10_regslice_BREADY),
        .s_axi_bresp(m10_couplers_to_m10_regslice_BRESP),
        .s_axi_bvalid(m10_couplers_to_m10_regslice_BVALID),
        .s_axi_rdata(m10_couplers_to_m10_regslice_RDATA),
        .s_axi_rready(m10_couplers_to_m10_regslice_RREADY),
        .s_axi_rresp(m10_couplers_to_m10_regslice_RRESP),
        .s_axi_rvalid(m10_couplers_to_m10_regslice_RVALID),
        .s_axi_wdata(m10_couplers_to_m10_regslice_WDATA),
        .s_axi_wready(m10_couplers_to_m10_regslice_WREADY),
        .s_axi_wstrb(m10_couplers_to_m10_regslice_WSTRB),
        .s_axi_wvalid(m10_couplers_to_m10_regslice_WVALID));
endmodule

module s00_couplers_imp_1QOFPGA
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arprot,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awprot,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arburst,
    S_AXI_arcache,
    S_AXI_arid,
    S_AXI_arlen,
    S_AXI_arlock,
    S_AXI_arprot,
    S_AXI_arqos,
    S_AXI_arready,
    S_AXI_arsize,
    S_AXI_aruser,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awburst,
    S_AXI_awcache,
    S_AXI_awid,
    S_AXI_awlen,
    S_AXI_awlock,
    S_AXI_awprot,
    S_AXI_awqos,
    S_AXI_awready,
    S_AXI_awsize,
    S_AXI_awuser,
    S_AXI_awvalid,
    S_AXI_bid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rid,
    S_AXI_rlast,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wlast,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [39:0]M_AXI_araddr;
  output [2:0]M_AXI_arprot;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [39:0]M_AXI_awaddr;
  output [2:0]M_AXI_awprot;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [1:0]S_AXI_arburst;
  input [3:0]S_AXI_arcache;
  input [15:0]S_AXI_arid;
  input [7:0]S_AXI_arlen;
  input [0:0]S_AXI_arlock;
  input [2:0]S_AXI_arprot;
  input [3:0]S_AXI_arqos;
  output S_AXI_arready;
  input [2:0]S_AXI_arsize;
  input [15:0]S_AXI_aruser;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [1:0]S_AXI_awburst;
  input [3:0]S_AXI_awcache;
  input [15:0]S_AXI_awid;
  input [7:0]S_AXI_awlen;
  input [0:0]S_AXI_awlock;
  input [2:0]S_AXI_awprot;
  input [3:0]S_AXI_awqos;
  output S_AXI_awready;
  input [2:0]S_AXI_awsize;
  input [15:0]S_AXI_awuser;
  input S_AXI_awvalid;
  output [15:0]S_AXI_bid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [127:0]S_AXI_rdata;
  output [15:0]S_AXI_rid;
  output S_AXI_rlast;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [127:0]S_AXI_wdata;
  input S_AXI_wlast;
  output S_AXI_wready;
  input [15:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire M_ACLK_1;
  wire M_ARESETN_1;
  wire S_ACLK_1;
  wire S_ARESETN_1;
  wire [39:0]auto_cc_to_auto_ds_ARADDR;
  wire [1:0]auto_cc_to_auto_ds_ARBURST;
  wire [3:0]auto_cc_to_auto_ds_ARCACHE;
  wire [15:0]auto_cc_to_auto_ds_ARID;
  wire [7:0]auto_cc_to_auto_ds_ARLEN;
  wire [0:0]auto_cc_to_auto_ds_ARLOCK;
  wire [2:0]auto_cc_to_auto_ds_ARPROT;
  wire [3:0]auto_cc_to_auto_ds_ARQOS;
  wire auto_cc_to_auto_ds_ARREADY;
  wire [3:0]auto_cc_to_auto_ds_ARREGION;
  wire [2:0]auto_cc_to_auto_ds_ARSIZE;
  wire auto_cc_to_auto_ds_ARVALID;
  wire [39:0]auto_cc_to_auto_ds_AWADDR;
  wire [1:0]auto_cc_to_auto_ds_AWBURST;
  wire [3:0]auto_cc_to_auto_ds_AWCACHE;
  wire [15:0]auto_cc_to_auto_ds_AWID;
  wire [7:0]auto_cc_to_auto_ds_AWLEN;
  wire [0:0]auto_cc_to_auto_ds_AWLOCK;
  wire [2:0]auto_cc_to_auto_ds_AWPROT;
  wire [3:0]auto_cc_to_auto_ds_AWQOS;
  wire auto_cc_to_auto_ds_AWREADY;
  wire [3:0]auto_cc_to_auto_ds_AWREGION;
  wire [2:0]auto_cc_to_auto_ds_AWSIZE;
  wire auto_cc_to_auto_ds_AWVALID;
  wire [15:0]auto_cc_to_auto_ds_BID;
  wire auto_cc_to_auto_ds_BREADY;
  wire [1:0]auto_cc_to_auto_ds_BRESP;
  wire auto_cc_to_auto_ds_BVALID;
  wire [127:0]auto_cc_to_auto_ds_RDATA;
  wire [15:0]auto_cc_to_auto_ds_RID;
  wire auto_cc_to_auto_ds_RLAST;
  wire auto_cc_to_auto_ds_RREADY;
  wire [1:0]auto_cc_to_auto_ds_RRESP;
  wire auto_cc_to_auto_ds_RVALID;
  wire [127:0]auto_cc_to_auto_ds_WDATA;
  wire auto_cc_to_auto_ds_WLAST;
  wire auto_cc_to_auto_ds_WREADY;
  wire [15:0]auto_cc_to_auto_ds_WSTRB;
  wire auto_cc_to_auto_ds_WVALID;
  wire [39:0]auto_ds_to_auto_pc_ARADDR;
  wire [1:0]auto_ds_to_auto_pc_ARBURST;
  wire [3:0]auto_ds_to_auto_pc_ARCACHE;
  wire [7:0]auto_ds_to_auto_pc_ARLEN;
  wire [0:0]auto_ds_to_auto_pc_ARLOCK;
  wire [2:0]auto_ds_to_auto_pc_ARPROT;
  wire [3:0]auto_ds_to_auto_pc_ARQOS;
  wire auto_ds_to_auto_pc_ARREADY;
  wire [3:0]auto_ds_to_auto_pc_ARREGION;
  wire [2:0]auto_ds_to_auto_pc_ARSIZE;
  wire auto_ds_to_auto_pc_ARVALID;
  wire [39:0]auto_ds_to_auto_pc_AWADDR;
  wire [1:0]auto_ds_to_auto_pc_AWBURST;
  wire [3:0]auto_ds_to_auto_pc_AWCACHE;
  wire [7:0]auto_ds_to_auto_pc_AWLEN;
  wire [0:0]auto_ds_to_auto_pc_AWLOCK;
  wire [2:0]auto_ds_to_auto_pc_AWPROT;
  wire [3:0]auto_ds_to_auto_pc_AWQOS;
  wire auto_ds_to_auto_pc_AWREADY;
  wire [3:0]auto_ds_to_auto_pc_AWREGION;
  wire [2:0]auto_ds_to_auto_pc_AWSIZE;
  wire auto_ds_to_auto_pc_AWVALID;
  wire auto_ds_to_auto_pc_BREADY;
  wire [1:0]auto_ds_to_auto_pc_BRESP;
  wire auto_ds_to_auto_pc_BVALID;
  wire [31:0]auto_ds_to_auto_pc_RDATA;
  wire auto_ds_to_auto_pc_RLAST;
  wire auto_ds_to_auto_pc_RREADY;
  wire [1:0]auto_ds_to_auto_pc_RRESP;
  wire auto_ds_to_auto_pc_RVALID;
  wire [31:0]auto_ds_to_auto_pc_WDATA;
  wire auto_ds_to_auto_pc_WLAST;
  wire auto_ds_to_auto_pc_WREADY;
  wire [3:0]auto_ds_to_auto_pc_WSTRB;
  wire auto_ds_to_auto_pc_WVALID;
  wire [39:0]auto_pc_to_s00_couplers_ARADDR;
  wire [2:0]auto_pc_to_s00_couplers_ARPROT;
  wire auto_pc_to_s00_couplers_ARREADY;
  wire auto_pc_to_s00_couplers_ARVALID;
  wire [39:0]auto_pc_to_s00_couplers_AWADDR;
  wire [2:0]auto_pc_to_s00_couplers_AWPROT;
  wire auto_pc_to_s00_couplers_AWREADY;
  wire auto_pc_to_s00_couplers_AWVALID;
  wire auto_pc_to_s00_couplers_BREADY;
  wire [1:0]auto_pc_to_s00_couplers_BRESP;
  wire auto_pc_to_s00_couplers_BVALID;
  wire [31:0]auto_pc_to_s00_couplers_RDATA;
  wire auto_pc_to_s00_couplers_RREADY;
  wire [1:0]auto_pc_to_s00_couplers_RRESP;
  wire auto_pc_to_s00_couplers_RVALID;
  wire [31:0]auto_pc_to_s00_couplers_WDATA;
  wire auto_pc_to_s00_couplers_WREADY;
  wire [3:0]auto_pc_to_s00_couplers_WSTRB;
  wire auto_pc_to_s00_couplers_WVALID;
  wire [39:0]s00_couplers_to_auto_cc_ARADDR;
  wire [1:0]s00_couplers_to_auto_cc_ARBURST;
  wire [3:0]s00_couplers_to_auto_cc_ARCACHE;
  wire [15:0]s00_couplers_to_auto_cc_ARID;
  wire [7:0]s00_couplers_to_auto_cc_ARLEN;
  wire [0:0]s00_couplers_to_auto_cc_ARLOCK;
  wire [2:0]s00_couplers_to_auto_cc_ARPROT;
  wire [3:0]s00_couplers_to_auto_cc_ARQOS;
  wire s00_couplers_to_auto_cc_ARREADY;
  wire [2:0]s00_couplers_to_auto_cc_ARSIZE;
  wire [15:0]s00_couplers_to_auto_cc_ARUSER;
  wire s00_couplers_to_auto_cc_ARVALID;
  wire [39:0]s00_couplers_to_auto_cc_AWADDR;
  wire [1:0]s00_couplers_to_auto_cc_AWBURST;
  wire [3:0]s00_couplers_to_auto_cc_AWCACHE;
  wire [15:0]s00_couplers_to_auto_cc_AWID;
  wire [7:0]s00_couplers_to_auto_cc_AWLEN;
  wire [0:0]s00_couplers_to_auto_cc_AWLOCK;
  wire [2:0]s00_couplers_to_auto_cc_AWPROT;
  wire [3:0]s00_couplers_to_auto_cc_AWQOS;
  wire s00_couplers_to_auto_cc_AWREADY;
  wire [2:0]s00_couplers_to_auto_cc_AWSIZE;
  wire [15:0]s00_couplers_to_auto_cc_AWUSER;
  wire s00_couplers_to_auto_cc_AWVALID;
  wire [15:0]s00_couplers_to_auto_cc_BID;
  wire s00_couplers_to_auto_cc_BREADY;
  wire [1:0]s00_couplers_to_auto_cc_BRESP;
  wire s00_couplers_to_auto_cc_BVALID;
  wire [127:0]s00_couplers_to_auto_cc_RDATA;
  wire [15:0]s00_couplers_to_auto_cc_RID;
  wire s00_couplers_to_auto_cc_RLAST;
  wire s00_couplers_to_auto_cc_RREADY;
  wire [1:0]s00_couplers_to_auto_cc_RRESP;
  wire s00_couplers_to_auto_cc_RVALID;
  wire [127:0]s00_couplers_to_auto_cc_WDATA;
  wire s00_couplers_to_auto_cc_WLAST;
  wire s00_couplers_to_auto_cc_WREADY;
  wire [15:0]s00_couplers_to_auto_cc_WSTRB;
  wire s00_couplers_to_auto_cc_WVALID;

  assign M_ACLK_1 = M_ACLK;
  assign M_ARESETN_1 = M_ARESETN;
  assign M_AXI_araddr[39:0] = auto_pc_to_s00_couplers_ARADDR;
  assign M_AXI_arprot[2:0] = auto_pc_to_s00_couplers_ARPROT;
  assign M_AXI_arvalid = auto_pc_to_s00_couplers_ARVALID;
  assign M_AXI_awaddr[39:0] = auto_pc_to_s00_couplers_AWADDR;
  assign M_AXI_awprot[2:0] = auto_pc_to_s00_couplers_AWPROT;
  assign M_AXI_awvalid = auto_pc_to_s00_couplers_AWVALID;
  assign M_AXI_bready = auto_pc_to_s00_couplers_BREADY;
  assign M_AXI_rready = auto_pc_to_s00_couplers_RREADY;
  assign M_AXI_wdata[31:0] = auto_pc_to_s00_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = auto_pc_to_s00_couplers_WSTRB;
  assign M_AXI_wvalid = auto_pc_to_s00_couplers_WVALID;
  assign S_ACLK_1 = S_ACLK;
  assign S_ARESETN_1 = S_ARESETN;
  assign S_AXI_arready = s00_couplers_to_auto_cc_ARREADY;
  assign S_AXI_awready = s00_couplers_to_auto_cc_AWREADY;
  assign S_AXI_bid[15:0] = s00_couplers_to_auto_cc_BID;
  assign S_AXI_bresp[1:0] = s00_couplers_to_auto_cc_BRESP;
  assign S_AXI_bvalid = s00_couplers_to_auto_cc_BVALID;
  assign S_AXI_rdata[127:0] = s00_couplers_to_auto_cc_RDATA;
  assign S_AXI_rid[15:0] = s00_couplers_to_auto_cc_RID;
  assign S_AXI_rlast = s00_couplers_to_auto_cc_RLAST;
  assign S_AXI_rresp[1:0] = s00_couplers_to_auto_cc_RRESP;
  assign S_AXI_rvalid = s00_couplers_to_auto_cc_RVALID;
  assign S_AXI_wready = s00_couplers_to_auto_cc_WREADY;
  assign auto_pc_to_s00_couplers_ARREADY = M_AXI_arready;
  assign auto_pc_to_s00_couplers_AWREADY = M_AXI_awready;
  assign auto_pc_to_s00_couplers_BRESP = M_AXI_bresp[1:0];
  assign auto_pc_to_s00_couplers_BVALID = M_AXI_bvalid;
  assign auto_pc_to_s00_couplers_RDATA = M_AXI_rdata[31:0];
  assign auto_pc_to_s00_couplers_RRESP = M_AXI_rresp[1:0];
  assign auto_pc_to_s00_couplers_RVALID = M_AXI_rvalid;
  assign auto_pc_to_s00_couplers_WREADY = M_AXI_wready;
  assign s00_couplers_to_auto_cc_ARADDR = S_AXI_araddr[39:0];
  assign s00_couplers_to_auto_cc_ARBURST = S_AXI_arburst[1:0];
  assign s00_couplers_to_auto_cc_ARCACHE = S_AXI_arcache[3:0];
  assign s00_couplers_to_auto_cc_ARID = S_AXI_arid[15:0];
  assign s00_couplers_to_auto_cc_ARLEN = S_AXI_arlen[7:0];
  assign s00_couplers_to_auto_cc_ARLOCK = S_AXI_arlock[0];
  assign s00_couplers_to_auto_cc_ARPROT = S_AXI_arprot[2:0];
  assign s00_couplers_to_auto_cc_ARQOS = S_AXI_arqos[3:0];
  assign s00_couplers_to_auto_cc_ARSIZE = S_AXI_arsize[2:0];
  assign s00_couplers_to_auto_cc_ARUSER = S_AXI_aruser[15:0];
  assign s00_couplers_to_auto_cc_ARVALID = S_AXI_arvalid;
  assign s00_couplers_to_auto_cc_AWADDR = S_AXI_awaddr[39:0];
  assign s00_couplers_to_auto_cc_AWBURST = S_AXI_awburst[1:0];
  assign s00_couplers_to_auto_cc_AWCACHE = S_AXI_awcache[3:0];
  assign s00_couplers_to_auto_cc_AWID = S_AXI_awid[15:0];
  assign s00_couplers_to_auto_cc_AWLEN = S_AXI_awlen[7:0];
  assign s00_couplers_to_auto_cc_AWLOCK = S_AXI_awlock[0];
  assign s00_couplers_to_auto_cc_AWPROT = S_AXI_awprot[2:0];
  assign s00_couplers_to_auto_cc_AWQOS = S_AXI_awqos[3:0];
  assign s00_couplers_to_auto_cc_AWSIZE = S_AXI_awsize[2:0];
  assign s00_couplers_to_auto_cc_AWUSER = S_AXI_awuser[15:0];
  assign s00_couplers_to_auto_cc_AWVALID = S_AXI_awvalid;
  assign s00_couplers_to_auto_cc_BREADY = S_AXI_bready;
  assign s00_couplers_to_auto_cc_RREADY = S_AXI_rready;
  assign s00_couplers_to_auto_cc_WDATA = S_AXI_wdata[127:0];
  assign s00_couplers_to_auto_cc_WLAST = S_AXI_wlast;
  assign s00_couplers_to_auto_cc_WSTRB = S_AXI_wstrb[15:0];
  assign s00_couplers_to_auto_cc_WVALID = S_AXI_wvalid;
  design_1_auto_cc_0 auto_cc
       (.m_axi_aclk(M_ACLK_1),
        .m_axi_araddr(auto_cc_to_auto_ds_ARADDR),
        .m_axi_arburst(auto_cc_to_auto_ds_ARBURST),
        .m_axi_arcache(auto_cc_to_auto_ds_ARCACHE),
        .m_axi_aresetn(M_ARESETN_1),
        .m_axi_arid(auto_cc_to_auto_ds_ARID),
        .m_axi_arlen(auto_cc_to_auto_ds_ARLEN),
        .m_axi_arlock(auto_cc_to_auto_ds_ARLOCK),
        .m_axi_arprot(auto_cc_to_auto_ds_ARPROT),
        .m_axi_arqos(auto_cc_to_auto_ds_ARQOS),
        .m_axi_arready(auto_cc_to_auto_ds_ARREADY),
        .m_axi_arregion(auto_cc_to_auto_ds_ARREGION),
        .m_axi_arsize(auto_cc_to_auto_ds_ARSIZE),
        .m_axi_arvalid(auto_cc_to_auto_ds_ARVALID),
        .m_axi_awaddr(auto_cc_to_auto_ds_AWADDR),
        .m_axi_awburst(auto_cc_to_auto_ds_AWBURST),
        .m_axi_awcache(auto_cc_to_auto_ds_AWCACHE),
        .m_axi_awid(auto_cc_to_auto_ds_AWID),
        .m_axi_awlen(auto_cc_to_auto_ds_AWLEN),
        .m_axi_awlock(auto_cc_to_auto_ds_AWLOCK),
        .m_axi_awprot(auto_cc_to_auto_ds_AWPROT),
        .m_axi_awqos(auto_cc_to_auto_ds_AWQOS),
        .m_axi_awready(auto_cc_to_auto_ds_AWREADY),
        .m_axi_awregion(auto_cc_to_auto_ds_AWREGION),
        .m_axi_awsize(auto_cc_to_auto_ds_AWSIZE),
        .m_axi_awvalid(auto_cc_to_auto_ds_AWVALID),
        .m_axi_bid(auto_cc_to_auto_ds_BID),
        .m_axi_bready(auto_cc_to_auto_ds_BREADY),
        .m_axi_bresp(auto_cc_to_auto_ds_BRESP),
        .m_axi_bvalid(auto_cc_to_auto_ds_BVALID),
        .m_axi_rdata(auto_cc_to_auto_ds_RDATA),
        .m_axi_rid(auto_cc_to_auto_ds_RID),
        .m_axi_rlast(auto_cc_to_auto_ds_RLAST),
        .m_axi_rready(auto_cc_to_auto_ds_RREADY),
        .m_axi_rresp(auto_cc_to_auto_ds_RRESP),
        .m_axi_rvalid(auto_cc_to_auto_ds_RVALID),
        .m_axi_wdata(auto_cc_to_auto_ds_WDATA),
        .m_axi_wlast(auto_cc_to_auto_ds_WLAST),
        .m_axi_wready(auto_cc_to_auto_ds_WREADY),
        .m_axi_wstrb(auto_cc_to_auto_ds_WSTRB),
        .m_axi_wvalid(auto_cc_to_auto_ds_WVALID),
        .s_axi_aclk(S_ACLK_1),
        .s_axi_araddr(s00_couplers_to_auto_cc_ARADDR),
        .s_axi_arburst(s00_couplers_to_auto_cc_ARBURST),
        .s_axi_arcache(s00_couplers_to_auto_cc_ARCACHE),
        .s_axi_aresetn(S_ARESETN_1),
        .s_axi_arid(s00_couplers_to_auto_cc_ARID),
        .s_axi_arlen(s00_couplers_to_auto_cc_ARLEN),
        .s_axi_arlock(s00_couplers_to_auto_cc_ARLOCK),
        .s_axi_arprot(s00_couplers_to_auto_cc_ARPROT),
        .s_axi_arqos(s00_couplers_to_auto_cc_ARQOS),
        .s_axi_arready(s00_couplers_to_auto_cc_ARREADY),
        .s_axi_arregion({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arsize(s00_couplers_to_auto_cc_ARSIZE),
        .s_axi_aruser(s00_couplers_to_auto_cc_ARUSER),
        .s_axi_arvalid(s00_couplers_to_auto_cc_ARVALID),
        .s_axi_awaddr(s00_couplers_to_auto_cc_AWADDR),
        .s_axi_awburst(s00_couplers_to_auto_cc_AWBURST),
        .s_axi_awcache(s00_couplers_to_auto_cc_AWCACHE),
        .s_axi_awid(s00_couplers_to_auto_cc_AWID),
        .s_axi_awlen(s00_couplers_to_auto_cc_AWLEN),
        .s_axi_awlock(s00_couplers_to_auto_cc_AWLOCK),
        .s_axi_awprot(s00_couplers_to_auto_cc_AWPROT),
        .s_axi_awqos(s00_couplers_to_auto_cc_AWQOS),
        .s_axi_awready(s00_couplers_to_auto_cc_AWREADY),
        .s_axi_awregion({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awsize(s00_couplers_to_auto_cc_AWSIZE),
        .s_axi_awuser(s00_couplers_to_auto_cc_AWUSER),
        .s_axi_awvalid(s00_couplers_to_auto_cc_AWVALID),
        .s_axi_bid(s00_couplers_to_auto_cc_BID),
        .s_axi_bready(s00_couplers_to_auto_cc_BREADY),
        .s_axi_bresp(s00_couplers_to_auto_cc_BRESP),
        .s_axi_bvalid(s00_couplers_to_auto_cc_BVALID),
        .s_axi_rdata(s00_couplers_to_auto_cc_RDATA),
        .s_axi_rid(s00_couplers_to_auto_cc_RID),
        .s_axi_rlast(s00_couplers_to_auto_cc_RLAST),
        .s_axi_rready(s00_couplers_to_auto_cc_RREADY),
        .s_axi_rresp(s00_couplers_to_auto_cc_RRESP),
        .s_axi_rvalid(s00_couplers_to_auto_cc_RVALID),
        .s_axi_wdata(s00_couplers_to_auto_cc_WDATA),
        .s_axi_wlast(s00_couplers_to_auto_cc_WLAST),
        .s_axi_wready(s00_couplers_to_auto_cc_WREADY),
        .s_axi_wstrb(s00_couplers_to_auto_cc_WSTRB),
        .s_axi_wvalid(s00_couplers_to_auto_cc_WVALID));
  design_1_auto_ds_1 auto_ds
       (.m_axi_araddr(auto_ds_to_auto_pc_ARADDR),
        .m_axi_arburst(auto_ds_to_auto_pc_ARBURST),
        .m_axi_arcache(auto_ds_to_auto_pc_ARCACHE),
        .m_axi_arlen(auto_ds_to_auto_pc_ARLEN),
        .m_axi_arlock(auto_ds_to_auto_pc_ARLOCK),
        .m_axi_arprot(auto_ds_to_auto_pc_ARPROT),
        .m_axi_arqos(auto_ds_to_auto_pc_ARQOS),
        .m_axi_arready(auto_ds_to_auto_pc_ARREADY),
        .m_axi_arregion(auto_ds_to_auto_pc_ARREGION),
        .m_axi_arsize(auto_ds_to_auto_pc_ARSIZE),
        .m_axi_arvalid(auto_ds_to_auto_pc_ARVALID),
        .m_axi_awaddr(auto_ds_to_auto_pc_AWADDR),
        .m_axi_awburst(auto_ds_to_auto_pc_AWBURST),
        .m_axi_awcache(auto_ds_to_auto_pc_AWCACHE),
        .m_axi_awlen(auto_ds_to_auto_pc_AWLEN),
        .m_axi_awlock(auto_ds_to_auto_pc_AWLOCK),
        .m_axi_awprot(auto_ds_to_auto_pc_AWPROT),
        .m_axi_awqos(auto_ds_to_auto_pc_AWQOS),
        .m_axi_awready(auto_ds_to_auto_pc_AWREADY),
        .m_axi_awregion(auto_ds_to_auto_pc_AWREGION),
        .m_axi_awsize(auto_ds_to_auto_pc_AWSIZE),
        .m_axi_awvalid(auto_ds_to_auto_pc_AWVALID),
        .m_axi_bready(auto_ds_to_auto_pc_BREADY),
        .m_axi_bresp(auto_ds_to_auto_pc_BRESP),
        .m_axi_bvalid(auto_ds_to_auto_pc_BVALID),
        .m_axi_rdata(auto_ds_to_auto_pc_RDATA),
        .m_axi_rlast(auto_ds_to_auto_pc_RLAST),
        .m_axi_rready(auto_ds_to_auto_pc_RREADY),
        .m_axi_rresp(auto_ds_to_auto_pc_RRESP),
        .m_axi_rvalid(auto_ds_to_auto_pc_RVALID),
        .m_axi_wdata(auto_ds_to_auto_pc_WDATA),
        .m_axi_wlast(auto_ds_to_auto_pc_WLAST),
        .m_axi_wready(auto_ds_to_auto_pc_WREADY),
        .m_axi_wstrb(auto_ds_to_auto_pc_WSTRB),
        .m_axi_wvalid(auto_ds_to_auto_pc_WVALID),
        .s_axi_aclk(M_ACLK_1),
        .s_axi_araddr(auto_cc_to_auto_ds_ARADDR),
        .s_axi_arburst(auto_cc_to_auto_ds_ARBURST),
        .s_axi_arcache(auto_cc_to_auto_ds_ARCACHE),
        .s_axi_aresetn(M_ARESETN_1),
        .s_axi_arid(auto_cc_to_auto_ds_ARID),
        .s_axi_arlen(auto_cc_to_auto_ds_ARLEN),
        .s_axi_arlock(auto_cc_to_auto_ds_ARLOCK),
        .s_axi_arprot(auto_cc_to_auto_ds_ARPROT),
        .s_axi_arqos(auto_cc_to_auto_ds_ARQOS),
        .s_axi_arready(auto_cc_to_auto_ds_ARREADY),
        .s_axi_arregion(auto_cc_to_auto_ds_ARREGION),
        .s_axi_arsize(auto_cc_to_auto_ds_ARSIZE),
        .s_axi_arvalid(auto_cc_to_auto_ds_ARVALID),
        .s_axi_awaddr(auto_cc_to_auto_ds_AWADDR),
        .s_axi_awburst(auto_cc_to_auto_ds_AWBURST),
        .s_axi_awcache(auto_cc_to_auto_ds_AWCACHE),
        .s_axi_awid(auto_cc_to_auto_ds_AWID),
        .s_axi_awlen(auto_cc_to_auto_ds_AWLEN),
        .s_axi_awlock(auto_cc_to_auto_ds_AWLOCK),
        .s_axi_awprot(auto_cc_to_auto_ds_AWPROT),
        .s_axi_awqos(auto_cc_to_auto_ds_AWQOS),
        .s_axi_awready(auto_cc_to_auto_ds_AWREADY),
        .s_axi_awregion(auto_cc_to_auto_ds_AWREGION),
        .s_axi_awsize(auto_cc_to_auto_ds_AWSIZE),
        .s_axi_awvalid(auto_cc_to_auto_ds_AWVALID),
        .s_axi_bid(auto_cc_to_auto_ds_BID),
        .s_axi_bready(auto_cc_to_auto_ds_BREADY),
        .s_axi_bresp(auto_cc_to_auto_ds_BRESP),
        .s_axi_bvalid(auto_cc_to_auto_ds_BVALID),
        .s_axi_rdata(auto_cc_to_auto_ds_RDATA),
        .s_axi_rid(auto_cc_to_auto_ds_RID),
        .s_axi_rlast(auto_cc_to_auto_ds_RLAST),
        .s_axi_rready(auto_cc_to_auto_ds_RREADY),
        .s_axi_rresp(auto_cc_to_auto_ds_RRESP),
        .s_axi_rvalid(auto_cc_to_auto_ds_RVALID),
        .s_axi_wdata(auto_cc_to_auto_ds_WDATA),
        .s_axi_wlast(auto_cc_to_auto_ds_WLAST),
        .s_axi_wready(auto_cc_to_auto_ds_WREADY),
        .s_axi_wstrb(auto_cc_to_auto_ds_WSTRB),
        .s_axi_wvalid(auto_cc_to_auto_ds_WVALID));
  design_1_auto_pc_1 auto_pc
       (.aclk(M_ACLK_1),
        .aresetn(M_ARESETN_1),
        .m_axi_araddr(auto_pc_to_s00_couplers_ARADDR),
        .m_axi_arprot(auto_pc_to_s00_couplers_ARPROT),
        .m_axi_arready(auto_pc_to_s00_couplers_ARREADY),
        .m_axi_arvalid(auto_pc_to_s00_couplers_ARVALID),
        .m_axi_awaddr(auto_pc_to_s00_couplers_AWADDR),
        .m_axi_awprot(auto_pc_to_s00_couplers_AWPROT),
        .m_axi_awready(auto_pc_to_s00_couplers_AWREADY),
        .m_axi_awvalid(auto_pc_to_s00_couplers_AWVALID),
        .m_axi_bready(auto_pc_to_s00_couplers_BREADY),
        .m_axi_bresp(auto_pc_to_s00_couplers_BRESP),
        .m_axi_bvalid(auto_pc_to_s00_couplers_BVALID),
        .m_axi_rdata(auto_pc_to_s00_couplers_RDATA),
        .m_axi_rready(auto_pc_to_s00_couplers_RREADY),
        .m_axi_rresp(auto_pc_to_s00_couplers_RRESP),
        .m_axi_rvalid(auto_pc_to_s00_couplers_RVALID),
        .m_axi_wdata(auto_pc_to_s00_couplers_WDATA),
        .m_axi_wready(auto_pc_to_s00_couplers_WREADY),
        .m_axi_wstrb(auto_pc_to_s00_couplers_WSTRB),
        .m_axi_wvalid(auto_pc_to_s00_couplers_WVALID),
        .s_axi_araddr(auto_ds_to_auto_pc_ARADDR),
        .s_axi_arburst(auto_ds_to_auto_pc_ARBURST),
        .s_axi_arcache(auto_ds_to_auto_pc_ARCACHE),
        .s_axi_arlen(auto_ds_to_auto_pc_ARLEN),
        .s_axi_arlock(auto_ds_to_auto_pc_ARLOCK),
        .s_axi_arprot(auto_ds_to_auto_pc_ARPROT),
        .s_axi_arqos(auto_ds_to_auto_pc_ARQOS),
        .s_axi_arready(auto_ds_to_auto_pc_ARREADY),
        .s_axi_arregion(auto_ds_to_auto_pc_ARREGION),
        .s_axi_arsize(auto_ds_to_auto_pc_ARSIZE),
        .s_axi_arvalid(auto_ds_to_auto_pc_ARVALID),
        .s_axi_awaddr(auto_ds_to_auto_pc_AWADDR),
        .s_axi_awburst(auto_ds_to_auto_pc_AWBURST),
        .s_axi_awcache(auto_ds_to_auto_pc_AWCACHE),
        .s_axi_awlen(auto_ds_to_auto_pc_AWLEN),
        .s_axi_awlock(auto_ds_to_auto_pc_AWLOCK),
        .s_axi_awprot(auto_ds_to_auto_pc_AWPROT),
        .s_axi_awqos(auto_ds_to_auto_pc_AWQOS),
        .s_axi_awready(auto_ds_to_auto_pc_AWREADY),
        .s_axi_awregion(auto_ds_to_auto_pc_AWREGION),
        .s_axi_awsize(auto_ds_to_auto_pc_AWSIZE),
        .s_axi_awvalid(auto_ds_to_auto_pc_AWVALID),
        .s_axi_bready(auto_ds_to_auto_pc_BREADY),
        .s_axi_bresp(auto_ds_to_auto_pc_BRESP),
        .s_axi_bvalid(auto_ds_to_auto_pc_BVALID),
        .s_axi_rdata(auto_ds_to_auto_pc_RDATA),
        .s_axi_rlast(auto_ds_to_auto_pc_RLAST),
        .s_axi_rready(auto_ds_to_auto_pc_RREADY),
        .s_axi_rresp(auto_ds_to_auto_pc_RRESP),
        .s_axi_rvalid(auto_ds_to_auto_pc_RVALID),
        .s_axi_wdata(auto_ds_to_auto_pc_WDATA),
        .s_axi_wlast(auto_ds_to_auto_pc_WLAST),
        .s_axi_wready(auto_ds_to_auto_pc_WREADY),
        .s_axi_wstrb(auto_ds_to_auto_pc_WSTRB),
        .s_axi_wvalid(auto_ds_to_auto_pc_WVALID));
endmodule

module s00_couplers_imp_O7FAN0
   (M_ACLK,
    M_ARESETN,
    M_AXI_araddr,
    M_AXI_arprot,
    M_AXI_arready,
    M_AXI_arvalid,
    M_AXI_awaddr,
    M_AXI_awprot,
    M_AXI_awready,
    M_AXI_awvalid,
    M_AXI_bready,
    M_AXI_bresp,
    M_AXI_bvalid,
    M_AXI_rdata,
    M_AXI_rready,
    M_AXI_rresp,
    M_AXI_rvalid,
    M_AXI_wdata,
    M_AXI_wready,
    M_AXI_wstrb,
    M_AXI_wvalid,
    S_ACLK,
    S_ARESETN,
    S_AXI_araddr,
    S_AXI_arburst,
    S_AXI_arcache,
    S_AXI_arid,
    S_AXI_arlen,
    S_AXI_arlock,
    S_AXI_arprot,
    S_AXI_arqos,
    S_AXI_arready,
    S_AXI_arsize,
    S_AXI_arvalid,
    S_AXI_awaddr,
    S_AXI_awburst,
    S_AXI_awcache,
    S_AXI_awid,
    S_AXI_awlen,
    S_AXI_awlock,
    S_AXI_awprot,
    S_AXI_awqos,
    S_AXI_awready,
    S_AXI_awsize,
    S_AXI_awvalid,
    S_AXI_bid,
    S_AXI_bready,
    S_AXI_bresp,
    S_AXI_bvalid,
    S_AXI_rdata,
    S_AXI_rid,
    S_AXI_rlast,
    S_AXI_rready,
    S_AXI_rresp,
    S_AXI_rvalid,
    S_AXI_wdata,
    S_AXI_wlast,
    S_AXI_wready,
    S_AXI_wstrb,
    S_AXI_wvalid);
  input M_ACLK;
  input M_ARESETN;
  output [39:0]M_AXI_araddr;
  output [2:0]M_AXI_arprot;
  input M_AXI_arready;
  output M_AXI_arvalid;
  output [39:0]M_AXI_awaddr;
  output [2:0]M_AXI_awprot;
  input M_AXI_awready;
  output M_AXI_awvalid;
  output M_AXI_bready;
  input [1:0]M_AXI_bresp;
  input M_AXI_bvalid;
  input [31:0]M_AXI_rdata;
  output M_AXI_rready;
  input [1:0]M_AXI_rresp;
  input M_AXI_rvalid;
  output [31:0]M_AXI_wdata;
  input M_AXI_wready;
  output [3:0]M_AXI_wstrb;
  output M_AXI_wvalid;
  input S_ACLK;
  input S_ARESETN;
  input [39:0]S_AXI_araddr;
  input [1:0]S_AXI_arburst;
  input [3:0]S_AXI_arcache;
  input [15:0]S_AXI_arid;
  input [7:0]S_AXI_arlen;
  input [0:0]S_AXI_arlock;
  input [2:0]S_AXI_arprot;
  input [3:0]S_AXI_arqos;
  output S_AXI_arready;
  input [2:0]S_AXI_arsize;
  input S_AXI_arvalid;
  input [39:0]S_AXI_awaddr;
  input [1:0]S_AXI_awburst;
  input [3:0]S_AXI_awcache;
  input [15:0]S_AXI_awid;
  input [7:0]S_AXI_awlen;
  input [0:0]S_AXI_awlock;
  input [2:0]S_AXI_awprot;
  input [3:0]S_AXI_awqos;
  output S_AXI_awready;
  input [2:0]S_AXI_awsize;
  input S_AXI_awvalid;
  output [15:0]S_AXI_bid;
  input S_AXI_bready;
  output [1:0]S_AXI_bresp;
  output S_AXI_bvalid;
  output [127:0]S_AXI_rdata;
  output [15:0]S_AXI_rid;
  output S_AXI_rlast;
  input S_AXI_rready;
  output [1:0]S_AXI_rresp;
  output S_AXI_rvalid;
  input [127:0]S_AXI_wdata;
  input S_AXI_wlast;
  output S_AXI_wready;
  input [15:0]S_AXI_wstrb;
  input S_AXI_wvalid;

  wire S_ACLK_1;
  wire S_ARESETN_1;
  wire [39:0]auto_ds_to_auto_pc_ARADDR;
  wire [1:0]auto_ds_to_auto_pc_ARBURST;
  wire [3:0]auto_ds_to_auto_pc_ARCACHE;
  wire [7:0]auto_ds_to_auto_pc_ARLEN;
  wire [0:0]auto_ds_to_auto_pc_ARLOCK;
  wire [2:0]auto_ds_to_auto_pc_ARPROT;
  wire [3:0]auto_ds_to_auto_pc_ARQOS;
  wire auto_ds_to_auto_pc_ARREADY;
  wire [3:0]auto_ds_to_auto_pc_ARREGION;
  wire [2:0]auto_ds_to_auto_pc_ARSIZE;
  wire auto_ds_to_auto_pc_ARVALID;
  wire [39:0]auto_ds_to_auto_pc_AWADDR;
  wire [1:0]auto_ds_to_auto_pc_AWBURST;
  wire [3:0]auto_ds_to_auto_pc_AWCACHE;
  wire [7:0]auto_ds_to_auto_pc_AWLEN;
  wire [0:0]auto_ds_to_auto_pc_AWLOCK;
  wire [2:0]auto_ds_to_auto_pc_AWPROT;
  wire [3:0]auto_ds_to_auto_pc_AWQOS;
  wire auto_ds_to_auto_pc_AWREADY;
  wire [3:0]auto_ds_to_auto_pc_AWREGION;
  wire [2:0]auto_ds_to_auto_pc_AWSIZE;
  wire auto_ds_to_auto_pc_AWVALID;
  wire auto_ds_to_auto_pc_BREADY;
  wire [1:0]auto_ds_to_auto_pc_BRESP;
  wire auto_ds_to_auto_pc_BVALID;
  wire [31:0]auto_ds_to_auto_pc_RDATA;
  wire auto_ds_to_auto_pc_RLAST;
  wire auto_ds_to_auto_pc_RREADY;
  wire [1:0]auto_ds_to_auto_pc_RRESP;
  wire auto_ds_to_auto_pc_RVALID;
  wire [31:0]auto_ds_to_auto_pc_WDATA;
  wire auto_ds_to_auto_pc_WLAST;
  wire auto_ds_to_auto_pc_WREADY;
  wire [3:0]auto_ds_to_auto_pc_WSTRB;
  wire auto_ds_to_auto_pc_WVALID;
  wire [39:0]auto_pc_to_s00_couplers_ARADDR;
  wire [2:0]auto_pc_to_s00_couplers_ARPROT;
  wire auto_pc_to_s00_couplers_ARREADY;
  wire auto_pc_to_s00_couplers_ARVALID;
  wire [39:0]auto_pc_to_s00_couplers_AWADDR;
  wire [2:0]auto_pc_to_s00_couplers_AWPROT;
  wire auto_pc_to_s00_couplers_AWREADY;
  wire auto_pc_to_s00_couplers_AWVALID;
  wire auto_pc_to_s00_couplers_BREADY;
  wire [1:0]auto_pc_to_s00_couplers_BRESP;
  wire auto_pc_to_s00_couplers_BVALID;
  wire [31:0]auto_pc_to_s00_couplers_RDATA;
  wire auto_pc_to_s00_couplers_RREADY;
  wire [1:0]auto_pc_to_s00_couplers_RRESP;
  wire auto_pc_to_s00_couplers_RVALID;
  wire [31:0]auto_pc_to_s00_couplers_WDATA;
  wire auto_pc_to_s00_couplers_WREADY;
  wire [3:0]auto_pc_to_s00_couplers_WSTRB;
  wire auto_pc_to_s00_couplers_WVALID;
  wire [39:0]s00_couplers_to_auto_ds_ARADDR;
  wire [1:0]s00_couplers_to_auto_ds_ARBURST;
  wire [3:0]s00_couplers_to_auto_ds_ARCACHE;
  wire [15:0]s00_couplers_to_auto_ds_ARID;
  wire [7:0]s00_couplers_to_auto_ds_ARLEN;
  wire [0:0]s00_couplers_to_auto_ds_ARLOCK;
  wire [2:0]s00_couplers_to_auto_ds_ARPROT;
  wire [3:0]s00_couplers_to_auto_ds_ARQOS;
  wire s00_couplers_to_auto_ds_ARREADY;
  wire [2:0]s00_couplers_to_auto_ds_ARSIZE;
  wire s00_couplers_to_auto_ds_ARVALID;
  wire [39:0]s00_couplers_to_auto_ds_AWADDR;
  wire [1:0]s00_couplers_to_auto_ds_AWBURST;
  wire [3:0]s00_couplers_to_auto_ds_AWCACHE;
  wire [15:0]s00_couplers_to_auto_ds_AWID;
  wire [7:0]s00_couplers_to_auto_ds_AWLEN;
  wire [0:0]s00_couplers_to_auto_ds_AWLOCK;
  wire [2:0]s00_couplers_to_auto_ds_AWPROT;
  wire [3:0]s00_couplers_to_auto_ds_AWQOS;
  wire s00_couplers_to_auto_ds_AWREADY;
  wire [2:0]s00_couplers_to_auto_ds_AWSIZE;
  wire s00_couplers_to_auto_ds_AWVALID;
  wire [15:0]s00_couplers_to_auto_ds_BID;
  wire s00_couplers_to_auto_ds_BREADY;
  wire [1:0]s00_couplers_to_auto_ds_BRESP;
  wire s00_couplers_to_auto_ds_BVALID;
  wire [127:0]s00_couplers_to_auto_ds_RDATA;
  wire [15:0]s00_couplers_to_auto_ds_RID;
  wire s00_couplers_to_auto_ds_RLAST;
  wire s00_couplers_to_auto_ds_RREADY;
  wire [1:0]s00_couplers_to_auto_ds_RRESP;
  wire s00_couplers_to_auto_ds_RVALID;
  wire [127:0]s00_couplers_to_auto_ds_WDATA;
  wire s00_couplers_to_auto_ds_WLAST;
  wire s00_couplers_to_auto_ds_WREADY;
  wire [15:0]s00_couplers_to_auto_ds_WSTRB;
  wire s00_couplers_to_auto_ds_WVALID;

  assign M_AXI_araddr[39:0] = auto_pc_to_s00_couplers_ARADDR;
  assign M_AXI_arprot[2:0] = auto_pc_to_s00_couplers_ARPROT;
  assign M_AXI_arvalid = auto_pc_to_s00_couplers_ARVALID;
  assign M_AXI_awaddr[39:0] = auto_pc_to_s00_couplers_AWADDR;
  assign M_AXI_awprot[2:0] = auto_pc_to_s00_couplers_AWPROT;
  assign M_AXI_awvalid = auto_pc_to_s00_couplers_AWVALID;
  assign M_AXI_bready = auto_pc_to_s00_couplers_BREADY;
  assign M_AXI_rready = auto_pc_to_s00_couplers_RREADY;
  assign M_AXI_wdata[31:0] = auto_pc_to_s00_couplers_WDATA;
  assign M_AXI_wstrb[3:0] = auto_pc_to_s00_couplers_WSTRB;
  assign M_AXI_wvalid = auto_pc_to_s00_couplers_WVALID;
  assign S_ACLK_1 = S_ACLK;
  assign S_ARESETN_1 = S_ARESETN;
  assign S_AXI_arready = s00_couplers_to_auto_ds_ARREADY;
  assign S_AXI_awready = s00_couplers_to_auto_ds_AWREADY;
  assign S_AXI_bid[15:0] = s00_couplers_to_auto_ds_BID;
  assign S_AXI_bresp[1:0] = s00_couplers_to_auto_ds_BRESP;
  assign S_AXI_bvalid = s00_couplers_to_auto_ds_BVALID;
  assign S_AXI_rdata[127:0] = s00_couplers_to_auto_ds_RDATA;
  assign S_AXI_rid[15:0] = s00_couplers_to_auto_ds_RID;
  assign S_AXI_rlast = s00_couplers_to_auto_ds_RLAST;
  assign S_AXI_rresp[1:0] = s00_couplers_to_auto_ds_RRESP;
  assign S_AXI_rvalid = s00_couplers_to_auto_ds_RVALID;
  assign S_AXI_wready = s00_couplers_to_auto_ds_WREADY;
  assign auto_pc_to_s00_couplers_ARREADY = M_AXI_arready;
  assign auto_pc_to_s00_couplers_AWREADY = M_AXI_awready;
  assign auto_pc_to_s00_couplers_BRESP = M_AXI_bresp[1:0];
  assign auto_pc_to_s00_couplers_BVALID = M_AXI_bvalid;
  assign auto_pc_to_s00_couplers_RDATA = M_AXI_rdata[31:0];
  assign auto_pc_to_s00_couplers_RRESP = M_AXI_rresp[1:0];
  assign auto_pc_to_s00_couplers_RVALID = M_AXI_rvalid;
  assign auto_pc_to_s00_couplers_WREADY = M_AXI_wready;
  assign s00_couplers_to_auto_ds_ARADDR = S_AXI_araddr[39:0];
  assign s00_couplers_to_auto_ds_ARBURST = S_AXI_arburst[1:0];
  assign s00_couplers_to_auto_ds_ARCACHE = S_AXI_arcache[3:0];
  assign s00_couplers_to_auto_ds_ARID = S_AXI_arid[15:0];
  assign s00_couplers_to_auto_ds_ARLEN = S_AXI_arlen[7:0];
  assign s00_couplers_to_auto_ds_ARLOCK = S_AXI_arlock[0];
  assign s00_couplers_to_auto_ds_ARPROT = S_AXI_arprot[2:0];
  assign s00_couplers_to_auto_ds_ARQOS = S_AXI_arqos[3:0];
  assign s00_couplers_to_auto_ds_ARSIZE = S_AXI_arsize[2:0];
  assign s00_couplers_to_auto_ds_ARVALID = S_AXI_arvalid;
  assign s00_couplers_to_auto_ds_AWADDR = S_AXI_awaddr[39:0];
  assign s00_couplers_to_auto_ds_AWBURST = S_AXI_awburst[1:0];
  assign s00_couplers_to_auto_ds_AWCACHE = S_AXI_awcache[3:0];
  assign s00_couplers_to_auto_ds_AWID = S_AXI_awid[15:0];
  assign s00_couplers_to_auto_ds_AWLEN = S_AXI_awlen[7:0];
  assign s00_couplers_to_auto_ds_AWLOCK = S_AXI_awlock[0];
  assign s00_couplers_to_auto_ds_AWPROT = S_AXI_awprot[2:0];
  assign s00_couplers_to_auto_ds_AWQOS = S_AXI_awqos[3:0];
  assign s00_couplers_to_auto_ds_AWSIZE = S_AXI_awsize[2:0];
  assign s00_couplers_to_auto_ds_AWVALID = S_AXI_awvalid;
  assign s00_couplers_to_auto_ds_BREADY = S_AXI_bready;
  assign s00_couplers_to_auto_ds_RREADY = S_AXI_rready;
  assign s00_couplers_to_auto_ds_WDATA = S_AXI_wdata[127:0];
  assign s00_couplers_to_auto_ds_WLAST = S_AXI_wlast;
  assign s00_couplers_to_auto_ds_WSTRB = S_AXI_wstrb[15:0];
  assign s00_couplers_to_auto_ds_WVALID = S_AXI_wvalid;
  design_1_auto_ds_0 auto_ds
       (.m_axi_araddr(auto_ds_to_auto_pc_ARADDR),
        .m_axi_arburst(auto_ds_to_auto_pc_ARBURST),
        .m_axi_arcache(auto_ds_to_auto_pc_ARCACHE),
        .m_axi_arlen(auto_ds_to_auto_pc_ARLEN),
        .m_axi_arlock(auto_ds_to_auto_pc_ARLOCK),
        .m_axi_arprot(auto_ds_to_auto_pc_ARPROT),
        .m_axi_arqos(auto_ds_to_auto_pc_ARQOS),
        .m_axi_arready(auto_ds_to_auto_pc_ARREADY),
        .m_axi_arregion(auto_ds_to_auto_pc_ARREGION),
        .m_axi_arsize(auto_ds_to_auto_pc_ARSIZE),
        .m_axi_arvalid(auto_ds_to_auto_pc_ARVALID),
        .m_axi_awaddr(auto_ds_to_auto_pc_AWADDR),
        .m_axi_awburst(auto_ds_to_auto_pc_AWBURST),
        .m_axi_awcache(auto_ds_to_auto_pc_AWCACHE),
        .m_axi_awlen(auto_ds_to_auto_pc_AWLEN),
        .m_axi_awlock(auto_ds_to_auto_pc_AWLOCK),
        .m_axi_awprot(auto_ds_to_auto_pc_AWPROT),
        .m_axi_awqos(auto_ds_to_auto_pc_AWQOS),
        .m_axi_awready(auto_ds_to_auto_pc_AWREADY),
        .m_axi_awregion(auto_ds_to_auto_pc_AWREGION),
        .m_axi_awsize(auto_ds_to_auto_pc_AWSIZE),
        .m_axi_awvalid(auto_ds_to_auto_pc_AWVALID),
        .m_axi_bready(auto_ds_to_auto_pc_BREADY),
        .m_axi_bresp(auto_ds_to_auto_pc_BRESP),
        .m_axi_bvalid(auto_ds_to_auto_pc_BVALID),
        .m_axi_rdata(auto_ds_to_auto_pc_RDATA),
        .m_axi_rlast(auto_ds_to_auto_pc_RLAST),
        .m_axi_rready(auto_ds_to_auto_pc_RREADY),
        .m_axi_rresp(auto_ds_to_auto_pc_RRESP),
        .m_axi_rvalid(auto_ds_to_auto_pc_RVALID),
        .m_axi_wdata(auto_ds_to_auto_pc_WDATA),
        .m_axi_wlast(auto_ds_to_auto_pc_WLAST),
        .m_axi_wready(auto_ds_to_auto_pc_WREADY),
        .m_axi_wstrb(auto_ds_to_auto_pc_WSTRB),
        .m_axi_wvalid(auto_ds_to_auto_pc_WVALID),
        .s_axi_aclk(S_ACLK_1),
        .s_axi_araddr(s00_couplers_to_auto_ds_ARADDR),
        .s_axi_arburst(s00_couplers_to_auto_ds_ARBURST),
        .s_axi_arcache(s00_couplers_to_auto_ds_ARCACHE),
        .s_axi_aresetn(S_ARESETN_1),
        .s_axi_arid(s00_couplers_to_auto_ds_ARID),
        .s_axi_arlen(s00_couplers_to_auto_ds_ARLEN),
        .s_axi_arlock(s00_couplers_to_auto_ds_ARLOCK),
        .s_axi_arprot(s00_couplers_to_auto_ds_ARPROT),
        .s_axi_arqos(s00_couplers_to_auto_ds_ARQOS),
        .s_axi_arready(s00_couplers_to_auto_ds_ARREADY),
        .s_axi_arregion({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arsize(s00_couplers_to_auto_ds_ARSIZE),
        .s_axi_arvalid(s00_couplers_to_auto_ds_ARVALID),
        .s_axi_awaddr(s00_couplers_to_auto_ds_AWADDR),
        .s_axi_awburst(s00_couplers_to_auto_ds_AWBURST),
        .s_axi_awcache(s00_couplers_to_auto_ds_AWCACHE),
        .s_axi_awid(s00_couplers_to_auto_ds_AWID),
        .s_axi_awlen(s00_couplers_to_auto_ds_AWLEN),
        .s_axi_awlock(s00_couplers_to_auto_ds_AWLOCK),
        .s_axi_awprot(s00_couplers_to_auto_ds_AWPROT),
        .s_axi_awqos(s00_couplers_to_auto_ds_AWQOS),
        .s_axi_awready(s00_couplers_to_auto_ds_AWREADY),
        .s_axi_awregion({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awsize(s00_couplers_to_auto_ds_AWSIZE),
        .s_axi_awvalid(s00_couplers_to_auto_ds_AWVALID),
        .s_axi_bid(s00_couplers_to_auto_ds_BID),
        .s_axi_bready(s00_couplers_to_auto_ds_BREADY),
        .s_axi_bresp(s00_couplers_to_auto_ds_BRESP),
        .s_axi_bvalid(s00_couplers_to_auto_ds_BVALID),
        .s_axi_rdata(s00_couplers_to_auto_ds_RDATA),
        .s_axi_rid(s00_couplers_to_auto_ds_RID),
        .s_axi_rlast(s00_couplers_to_auto_ds_RLAST),
        .s_axi_rready(s00_couplers_to_auto_ds_RREADY),
        .s_axi_rresp(s00_couplers_to_auto_ds_RRESP),
        .s_axi_rvalid(s00_couplers_to_auto_ds_RVALID),
        .s_axi_wdata(s00_couplers_to_auto_ds_WDATA),
        .s_axi_wlast(s00_couplers_to_auto_ds_WLAST),
        .s_axi_wready(s00_couplers_to_auto_ds_WREADY),
        .s_axi_wstrb(s00_couplers_to_auto_ds_WSTRB),
        .s_axi_wvalid(s00_couplers_to_auto_ds_WVALID));
  design_1_auto_pc_0 auto_pc
       (.aclk(S_ACLK_1),
        .aresetn(S_ARESETN_1),
        .m_axi_araddr(auto_pc_to_s00_couplers_ARADDR),
        .m_axi_arprot(auto_pc_to_s00_couplers_ARPROT),
        .m_axi_arready(auto_pc_to_s00_couplers_ARREADY),
        .m_axi_arvalid(auto_pc_to_s00_couplers_ARVALID),
        .m_axi_awaddr(auto_pc_to_s00_couplers_AWADDR),
        .m_axi_awprot(auto_pc_to_s00_couplers_AWPROT),
        .m_axi_awready(auto_pc_to_s00_couplers_AWREADY),
        .m_axi_awvalid(auto_pc_to_s00_couplers_AWVALID),
        .m_axi_bready(auto_pc_to_s00_couplers_BREADY),
        .m_axi_bresp(auto_pc_to_s00_couplers_BRESP),
        .m_axi_bvalid(auto_pc_to_s00_couplers_BVALID),
        .m_axi_rdata(auto_pc_to_s00_couplers_RDATA),
        .m_axi_rready(auto_pc_to_s00_couplers_RREADY),
        .m_axi_rresp(auto_pc_to_s00_couplers_RRESP),
        .m_axi_rvalid(auto_pc_to_s00_couplers_RVALID),
        .m_axi_wdata(auto_pc_to_s00_couplers_WDATA),
        .m_axi_wready(auto_pc_to_s00_couplers_WREADY),
        .m_axi_wstrb(auto_pc_to_s00_couplers_WSTRB),
        .m_axi_wvalid(auto_pc_to_s00_couplers_WVALID),
        .s_axi_araddr(auto_ds_to_auto_pc_ARADDR),
        .s_axi_arburst(auto_ds_to_auto_pc_ARBURST),
        .s_axi_arcache(auto_ds_to_auto_pc_ARCACHE),
        .s_axi_arlen(auto_ds_to_auto_pc_ARLEN),
        .s_axi_arlock(auto_ds_to_auto_pc_ARLOCK),
        .s_axi_arprot(auto_ds_to_auto_pc_ARPROT),
        .s_axi_arqos(auto_ds_to_auto_pc_ARQOS),
        .s_axi_arready(auto_ds_to_auto_pc_ARREADY),
        .s_axi_arregion(auto_ds_to_auto_pc_ARREGION),
        .s_axi_arsize(auto_ds_to_auto_pc_ARSIZE),
        .s_axi_arvalid(auto_ds_to_auto_pc_ARVALID),
        .s_axi_awaddr(auto_ds_to_auto_pc_AWADDR),
        .s_axi_awburst(auto_ds_to_auto_pc_AWBURST),
        .s_axi_awcache(auto_ds_to_auto_pc_AWCACHE),
        .s_axi_awlen(auto_ds_to_auto_pc_AWLEN),
        .s_axi_awlock(auto_ds_to_auto_pc_AWLOCK),
        .s_axi_awprot(auto_ds_to_auto_pc_AWPROT),
        .s_axi_awqos(auto_ds_to_auto_pc_AWQOS),
        .s_axi_awready(auto_ds_to_auto_pc_AWREADY),
        .s_axi_awregion(auto_ds_to_auto_pc_AWREGION),
        .s_axi_awsize(auto_ds_to_auto_pc_AWSIZE),
        .s_axi_awvalid(auto_ds_to_auto_pc_AWVALID),
        .s_axi_bready(auto_ds_to_auto_pc_BREADY),
        .s_axi_bresp(auto_ds_to_auto_pc_BRESP),
        .s_axi_bvalid(auto_ds_to_auto_pc_BVALID),
        .s_axi_rdata(auto_ds_to_auto_pc_RDATA),
        .s_axi_rlast(auto_ds_to_auto_pc_RLAST),
        .s_axi_rready(auto_ds_to_auto_pc_RREADY),
        .s_axi_rresp(auto_ds_to_auto_pc_RRESP),
        .s_axi_rvalid(auto_ds_to_auto_pc_RVALID),
        .s_axi_wdata(auto_ds_to_auto_pc_WDATA),
        .s_axi_wlast(auto_ds_to_auto_pc_WLAST),
        .s_axi_wready(auto_ds_to_auto_pc_WREADY),
        .s_axi_wstrb(auto_ds_to_auto_pc_WSTRB),
        .s_axi_wvalid(auto_ds_to_auto_pc_WVALID));
endmodule
