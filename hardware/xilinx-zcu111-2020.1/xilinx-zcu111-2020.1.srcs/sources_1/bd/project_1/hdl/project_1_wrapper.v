//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
//Date        : Thu May 28 07:43:12 2020
//Host        : xcosswbld06 running 64-bit Red Hat Enterprise Linux Workstation release 7.4 (Maipo)
//Command     : generate_target project_1_wrapper.bd
//Design      : project_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module project_1_wrapper
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
  input adc0_clk_clk_n;
  input adc0_clk_clk_p;
  output clk_adc0;
  output clk_dac0;
  input dac0_clk_clk_n;
  input dac0_clk_clk_p;
  output done_flag;
  input emio_uart1_rxd_0;
  output emio_uart1_txd_0;
  output error_flag;
  output irq;
  output [4:0]led_bits_tri_o;
  input reset;
  input sys_diff_clock_clk_n;
  input sys_diff_clock_clk_p;
  input sysref_in_diff_n;
  input sysref_in_diff_p;
  input vin0_01_v_n;
  input vin0_01_v_p;
  output vout00_v_n;
  output vout00_v_p;

  wire adc0_clk_clk_n;
  wire adc0_clk_clk_p;
  wire clk_adc0;
  wire clk_dac0;
  wire dac0_clk_clk_n;
  wire dac0_clk_clk_p;
  wire done_flag;
  wire emio_uart1_rxd_0;
  wire emio_uart1_txd_0;
  wire error_flag;
  wire irq;
  wire [4:0]led_bits_tri_o;
  wire reset;
  wire sys_diff_clock_clk_n;
  wire sys_diff_clock_clk_p;
  wire sysref_in_diff_n;
  wire sysref_in_diff_p;
  wire vin0_01_v_n;
  wire vin0_01_v_p;
  wire vout00_v_n;
  wire vout00_v_p;

  project_1 project_1_i
       (.adc0_clk_clk_n(adc0_clk_clk_n),
        .adc0_clk_clk_p(adc0_clk_clk_p),
        .clk_adc0(clk_adc0),
        .clk_dac0(clk_dac0),
        .dac0_clk_clk_n(dac0_clk_clk_n),
        .dac0_clk_clk_p(dac0_clk_clk_p),
        .done_flag(done_flag),
        .emio_uart1_rxd_0(emio_uart1_rxd_0),
        .emio_uart1_txd_0(emio_uart1_txd_0),
        .error_flag(error_flag),
        .irq(irq),
        .led_bits_tri_o(led_bits_tri_o),
        .reset(reset),
        .sys_diff_clock_clk_n(sys_diff_clock_clk_n),
        .sys_diff_clock_clk_p(sys_diff_clock_clk_p),
        .sysref_in_diff_n(sysref_in_diff_n),
        .sysref_in_diff_p(sysref_in_diff_p),
        .vin0_01_v_n(vin0_01_v_n),
        .vin0_01_v_p(vin0_01_v_p),
        .vout00_v_n(vout00_v_n),
        .vout00_v_p(vout00_v_p));
endmodule
