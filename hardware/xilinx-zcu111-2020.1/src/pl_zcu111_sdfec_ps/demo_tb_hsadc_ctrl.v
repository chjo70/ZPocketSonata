//-----------------------------------------------------------------------------
// Title      : adc0_demo_tb_hsadc_ctrl_axi
// Project    : NA
//-----------------------------------------------------------------------------
// File       : adc0_demo_tb_hsadc_ctrl_axi.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module adc0_demo_tb_hsadc_ctrl_axi #(
   parameter integer                   C_S_AXI_ADDR_WIDTH   = 11
   )
(
   input                                  s_axi_aclk,
   input                                  s_axi_aresetn,

   input                                  clk2_clk,
   input                                  clk2_reset,
   
   // IO for bank 0 
   output reg  [7:0]                      adc00_enable_0 = 0,
   output reg  [11:0]                     adc00_dg_inc_0 = 64,
   output reg  [2:0]                      adc00_dg_type_0 = 0,
   output reg  [31:0]                     adc00_scaling_factor_0 = 1,
   output reg  [31:0]                     adc00_offset_0 = 0,
   output reg  [15:0]                     adc00_phase_high_0 = 0,
   output reg  [15:0]                     adc00_phase_low_0 = 0,
   output reg  [7:0]                      adc01_enable_0 = 0,
   output reg  [11:0]                     adc01_dg_inc_0 = 64,
   output reg  [2:0]                      adc01_dg_type_0 = 0,
   output reg  [31:0]                     adc01_scaling_factor_0 = 1,
   output reg  [31:0]                     adc01_offset_0 = 0,
   output reg  [15:0]                     adc01_phase_high_0 = 0,
   output reg  [15:0]                     adc01_phase_low_0 = 0,
   output reg  [7:0]                      adc02_enable_0 = 0,
   output reg  [11:0]                     adc02_dg_inc_0 = 64,
   output reg  [2:0]                      adc02_dg_type_0 = 0,
   output reg  [31:0]                     adc02_scaling_factor_0 = 1,
   output reg  [31:0]                     adc02_offset_0 = 0,
   output reg  [15:0]                     adc02_phase_high_0 = 0,
   output reg  [15:0]                     adc02_phase_low_0 = 0,
   output reg  [7:0]                      adc03_enable_0 = 0,
   output reg  [11:0]                     adc03_dg_inc_0 = 64,
   output reg  [2:0]                      adc03_dg_type_0 = 0,
   output reg  [31:0]                     adc03_scaling_factor_0 = 1,
   output reg  [31:0]                     adc03_offset_0 = 0,
   output reg  [15:0]                     adc03_phase_high_0 = 0,
   output reg  [15:0]                     adc03_phase_low_0 = 0,

 
   // basic register interface
   input                                  slv_rden,
   input                                  slv_wren,
   input       [31:0]                     slv_wdata,
   input       [C_S_AXI_ADDR_WIDTH-1:2]   slv_addr,
   
   output reg                             slv_rd_done,
   output reg                             slv_wr_done,
   output reg  [31:0]                     slv_rdata
 
);

  localparam C_INT_ADDRWIDTH = C_S_AXI_ADDR_WIDTH - 2;

  //----------------------------------------------------------------------------
  // Internal reg/wire declarations
  //----------------------------------------------------------------------------

  reg         slv_rden_r;            // Registered incoming read 
  wire        slv_rden_pls;          // Internally generated pulse
  reg         slv_access_valid_hold; // Flag indicates access in progress in axi domain
  wire        slv_wren_clear;        // Clears the held access valid signal
  reg         slv_access_is_read;    // High is access is a read
  reg  [31:0] slv_wdata_r_internal;  // Register the write data
  wire        slv_wren_clk2;         // Pulse on clk2 when rising edge of valid seen
  wire        slv_wren_done_pulse;   // Pulse on falling edge of clk1_ready
  wire        do_write_clk2;         // Use for debug

  //----------------------------------------------------------------------------
  // Create a held wr or rd signal. This is used to flag an access in progress
  // accross the clock domain.  This is reset when the signal has passed back
  // from the clk2 domain into the axi domain
  //----------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_access_valid_hold <= 'd0;
      slv_wdata_r_internal <= 'd0;
      end
    else begin
      if(slv_wren | slv_rden_pls) begin
        slv_access_valid_hold <= 'd1;
        // register the data locally for cross clock domain crossing
        slv_wdata_r_internal <= slv_wdata;
        end
      else begin
        if(slv_wren_clear) begin
          slv_access_valid_hold <= 'd0;
          end
        // Hold data
        slv_wdata_r_internal <= slv_wdata_r_internal;
        end
      end
    end

  //---------------------------------------------------------------------------
  // register the incoming read strobe, this will stay high, so we create a 
  // pulse to use. to generate the request across the clock domain.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_rden_r <= 'd0; // Zero all data
      end
    else begin
      slv_rden_r <= slv_rden;
      end
    end
    
  assign slv_rden_pls = (!slv_rden_r) & slv_rden;

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  // Clk2 clock domain handshake
  // 
  // This logic pass's the Clk2 access request across the clock domain.
  // On the DRP side, a pulse is generated to initialte the Clk2 access. When
  // The RDY pulse is received, a ready signal is passed back across the clock
  // boundary to the AXI clock domain. This causes the valid request to be
  // removed, and when seen on the DRP domain, the ready is lowered.
  // When the ready falling edge is seen in the AXI domain the AXI transaction
  // is finally completed.
  // Although this logic is slow, it minimises the logic required.
  // It also ensures if the Clk2 rate is very slow compared to the AXI rate
  // transactions will fully complete before another can be requested, though
  // in the case the user should probally set wait_for_drp low and poll for
  // the Clk2 completion
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  demo_tb_hsadc_ctrl_hshk_pls_gen clk2clk_handshake_pulse_gen_i(
   .clk1             (s_axi_aclk              ),
   .clk1_rst         (s_axi_aresetn           ),
   
   .clk1_valid       (slv_access_valid_hold   ), // Access in clk1 requested flag, pass to clk2
   .clk1_ready       (slv_wren_clear          ), // Access is complete in clk2, lower request in clk1
   .clk1_ready_pulse (slv_wren_done_pulse     ), // Pulsed on falling edge of clk1_ready, access complete in clk1 & clk2
   
   .clk2             (clk2_clk                ),
   .clk2_rst         (clk2_reset              ),
 
   .clk2_valid       ( ),
   .clk2_valid_pulse (slv_wren_clk2           ),
   .clk2_ready_pulse (slv_wren_clk2           )
    
  );
  
  // Gate the write strobe with the access type. In this case only the read enable
  // is high while we wait for the result
  assign do_write_clk2 = slv_wren_clk2 & (! slv_rden_r);

  //----------------------------------------------------------------------------
  // Register write logic
  //----------------------------------------------------------------------------
   always @( posedge clk2_clk )
   begin
      if (~clk2_reset) begin
        // set RW register defaults

         adc00_enable_0                           <= 8'd0;
         adc00_dg_inc_0                           <= 12'd64;
         adc00_dg_type_0                          <= 3'd0;
         adc00_scaling_factor_0                   <= 32'd1;
         adc00_offset_0                           <= 32'd0;
         adc00_phase_high_0                       <= 16'd0;
         adc00_phase_low_0                        <= 16'd0;
         adc01_enable_0                           <= 8'd0;
         adc01_dg_inc_0                           <= 12'd64;
         adc01_dg_type_0                          <= 3'd0;
         adc01_scaling_factor_0                   <= 32'd1;
         adc01_offset_0                           <= 32'd0;
         adc01_phase_high_0                       <= 16'd0;
         adc01_phase_low_0                        <= 16'd0;
         adc02_enable_0                           <= 8'd0;
         adc02_dg_inc_0                           <= 12'd64;
         adc02_dg_type_0                          <= 3'd0;
         adc02_scaling_factor_0                   <= 32'd1;
         adc02_offset_0                           <= 32'd0;
         adc02_phase_high_0                       <= 16'd0;
         adc02_phase_low_0                        <= 16'd0;
         adc03_enable_0                           <= 8'd0;
         adc03_dg_inc_0                           <= 12'd64;
         adc03_dg_type_0                          <= 3'd0;
         adc03_scaling_factor_0                   <= 32'd1;
         adc03_offset_0                           <= 32'd0;
         adc03_phase_high_0                       <= 16'd0;
         adc03_phase_low_0                        <= 16'd0;

 
      end 
      else begin    
         // on a write we write to the appropriate register
         // Not that slv_rden_r comes from the AXI clock domain, but will be stable
         // when the pulse arrives to register the data.
         if (slv_wren_clk2 & (~slv_rden_r)) begin
            case (slv_addr)
            // WRITE assignments for signal block 0
            'h0     : begin // @ address = 0
                      adc00_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h2     : begin // @ address = 8
                      adc00_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h4     : begin // @ address = 16
                      adc00_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h8     : begin // @ address = 32
                      adc00_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h9     : begin // @ address = 36
                      adc00_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'ha     : begin // @ address = 40
                      adc00_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hb     : begin // @ address = 44
                      adc00_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h40    : begin // @ address = 256
                      adc01_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h42    : begin // @ address = 264
                      adc01_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h44    : begin // @ address = 272
                      adc01_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h48    : begin // @ address = 288
                      adc01_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h49    : begin // @ address = 292
                      adc01_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h4a    : begin // @ address = 296
                      adc01_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h4b    : begin // @ address = 300
                      adc01_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h80    : begin // @ address = 512
                      adc02_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h82    : begin // @ address = 520
                      adc02_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h84    : begin // @ address = 528
                      adc02_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h88    : begin // @ address = 544
                      adc02_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h89    : begin // @ address = 548
                      adc02_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h8a    : begin // @ address = 552
                      adc02_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h8b    : begin // @ address = 556
                      adc02_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'hc0    : begin // @ address = 768
                      adc03_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'hc2    : begin // @ address = 776
                      adc03_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'hc4    : begin // @ address = 784
                      adc03_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'hc8    : begin // @ address = 800
                      adc03_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'hc9    : begin // @ address = 804
                      adc03_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'hca    : begin // @ address = 808
                      adc03_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hcb    : begin // @ address = 812
                      adc03_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end


            endcase
         end   
      end
   end
   
  //----------------------------------------------------------------------------
  // Register read logic
  // All signal come from clk 2, however by design these should be RW signals,
  // originating in this block. Therefore we know these signals will be steady
  // on a read.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      end
    else begin
      slv_rdata <= 'd0; // Zero all data bits, individual bits may be modified in the case below
      case (slv_addr)
      // READ assignments for signal block 0
     'h0     : begin // @ address = 0
               slv_rdata[7:0]       <= adc00_enable_0;
               end
     'h2     : begin // @ address = 8
               slv_rdata[11:0]      <= adc00_dg_inc_0;
               end
     'h4     : begin // @ address = 16
               slv_rdata[2:0]       <= adc00_dg_type_0;
               end
     'h8     : begin // @ address = 32
               slv_rdata[31:0]      <= adc00_scaling_factor_0;
               end
     'h9     : begin // @ address = 36
               slv_rdata[31:0]      <= adc00_offset_0;
               end
     'ha     : begin // @ address = 40
               slv_rdata[15:0]      <= adc00_phase_high_0;
               end
     'hb     : begin // @ address = 44
               slv_rdata[15:0]      <= adc00_phase_low_0;
               end
     'h40    : begin // @ address = 256
               slv_rdata[7:0]       <= adc01_enable_0;
               end
     'h42    : begin // @ address = 264
               slv_rdata[11:0]      <= adc01_dg_inc_0;
               end
     'h44    : begin // @ address = 272
               slv_rdata[2:0]       <= adc01_dg_type_0;
               end
     'h48    : begin // @ address = 288
               slv_rdata[31:0]      <= adc01_scaling_factor_0;
               end
     'h49    : begin // @ address = 292
               slv_rdata[31:0]      <= adc01_offset_0;
               end
     'h4a    : begin // @ address = 296
               slv_rdata[15:0]      <= adc01_phase_high_0;
               end
     'h4b    : begin // @ address = 300
               slv_rdata[15:0]      <= adc01_phase_low_0;
               end
     'h80    : begin // @ address = 512
               slv_rdata[7:0]       <= adc02_enable_0;
               end
     'h82    : begin // @ address = 520
               slv_rdata[11:0]      <= adc02_dg_inc_0;
               end
     'h84    : begin // @ address = 528
               slv_rdata[2:0]       <= adc02_dg_type_0;
               end
     'h88    : begin // @ address = 544
               slv_rdata[31:0]      <= adc02_scaling_factor_0;
               end
     'h89    : begin // @ address = 548
               slv_rdata[31:0]      <= adc02_offset_0;
               end
     'h8a    : begin // @ address = 552
               slv_rdata[15:0]      <= adc02_phase_high_0;
               end
     'h8b    : begin // @ address = 556
               slv_rdata[15:0]      <= adc02_phase_low_0;
               end
     'hc0    : begin // @ address = 768
               slv_rdata[7:0]       <= adc03_enable_0;
               end
     'hc2    : begin // @ address = 776
               slv_rdata[11:0]      <= adc03_dg_inc_0;
               end
     'hc4    : begin // @ address = 784
               slv_rdata[2:0]       <= adc03_dg_type_0;
               end
     'hc8    : begin // @ address = 800
               slv_rdata[31:0]      <= adc03_scaling_factor_0;
               end
     'hc9    : begin // @ address = 804
               slv_rdata[31:0]      <= adc03_offset_0;
               end
     'hca    : begin // @ address = 808
               slv_rdata[15:0]      <= adc03_phase_high_0;
               end
     'hcb    : begin // @ address = 812
               slv_rdata[15:0]      <= adc03_phase_low_0;
               end

      default: slv_rdata            <= 'd0;
      endcase
      end
    end
   
   //---------------------------------------------------------------------------
   // read/write done logic.
   // Completed with the retruning pulse from the clk2 domain
   //---------------------------------------------------------------------------
   always @(*)
     begin
     slv_rd_done = slv_wren_done_pulse & (  slv_rden_r) ;
     slv_wr_done = slv_wren_done_pulse & (! slv_rden_r);
     end

endmodule
//-----------------------------------------------------------------------------
// Title      : adc1_demo_tb_hsadc_ctrl_axi
// Project    : NA
//-----------------------------------------------------------------------------
// File       : adc1_demo_tb_hsadc_ctrl_axi.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module adc1_demo_tb_hsadc_ctrl_axi #(
   parameter integer                   C_S_AXI_ADDR_WIDTH   = 11
   )
(
   input                                  s_axi_aclk,
   input                                  s_axi_aresetn,

   input                                  clk2_clk,
   input                                  clk2_reset,
   
   // IO for bank 0 
   output reg  [7:0]                      adc10_enable_0 = 0,
   output reg  [11:0]                     adc10_dg_inc_0 = 64,
   output reg  [2:0]                      adc10_dg_type_0 = 0,
   output reg  [31:0]                     adc10_scaling_factor_0 = 1,
   output reg  [31:0]                     adc10_offset_0 = 0,
   output reg  [15:0]                     adc10_phase_high_0 = 0,
   output reg  [15:0]                     adc10_phase_low_0 = 0,
   output reg  [7:0]                      adc11_enable_0 = 0,
   output reg  [11:0]                     adc11_dg_inc_0 = 64,
   output reg  [2:0]                      adc11_dg_type_0 = 0,
   output reg  [31:0]                     adc11_scaling_factor_0 = 1,
   output reg  [31:0]                     adc11_offset_0 = 0,
   output reg  [15:0]                     adc11_phase_high_0 = 0,
   output reg  [15:0]                     adc11_phase_low_0 = 0,
   output reg  [7:0]                      adc12_enable_0 = 0,
   output reg  [11:0]                     adc12_dg_inc_0 = 64,
   output reg  [2:0]                      adc12_dg_type_0 = 0,
   output reg  [31:0]                     adc12_scaling_factor_0 = 1,
   output reg  [31:0]                     adc12_offset_0 = 0,
   output reg  [15:0]                     adc12_phase_high_0 = 0,
   output reg  [15:0]                     adc12_phase_low_0 = 0,
   output reg  [7:0]                      adc13_enable_0 = 0,
   output reg  [11:0]                     adc13_dg_inc_0 = 64,
   output reg  [2:0]                      adc13_dg_type_0 = 0,
   output reg  [31:0]                     adc13_scaling_factor_0 = 1,
   output reg  [31:0]                     adc13_offset_0 = 0,
   output reg  [15:0]                     adc13_phase_high_0 = 0,
   output reg  [15:0]                     adc13_phase_low_0 = 0,

 
   // basic register interface
   input                                  slv_rden,
   input                                  slv_wren,
   input       [31:0]                     slv_wdata,
   input       [C_S_AXI_ADDR_WIDTH-1:2]   slv_addr,
   
   output reg                             slv_rd_done,
   output reg                             slv_wr_done,
   output reg  [31:0]                     slv_rdata
 
);

  localparam C_INT_ADDRWIDTH = C_S_AXI_ADDR_WIDTH - 2;

  //----------------------------------------------------------------------------
  // Internal reg/wire declarations
  //----------------------------------------------------------------------------

  reg         slv_rden_r;            // Registered incoming read 
  wire        slv_rden_pls;          // Internally generated pulse
  reg         slv_access_valid_hold; // Flag indicates access in progress in axi domain
  wire        slv_wren_clear;        // Clears the held access valid signal
  reg         slv_access_is_read;    // High is access is a read
  reg  [31:0] slv_wdata_r_internal;  // Register the write data
  wire        slv_wren_clk2;         // Pulse on clk2 when rising edge of valid seen
  wire        slv_wren_done_pulse;   // Pulse on falling edge of clk1_ready
  wire        do_write_clk2;         // Use for debug

  //----------------------------------------------------------------------------
  // Create a held wr or rd signal. This is used to flag an access in progress
  // accross the clock domain.  This is reset when the signal has passed back
  // from the clk2 domain into the axi domain
  //----------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_access_valid_hold <= 'd0;
      slv_wdata_r_internal <= 'd0;
      end
    else begin
      if(slv_wren | slv_rden_pls) begin
        slv_access_valid_hold <= 'd1;
        // register the data locally for cross clock domain crossing
        slv_wdata_r_internal <= slv_wdata;
        end
      else begin
        if(slv_wren_clear) begin
          slv_access_valid_hold <= 'd0;
          end
        // Hold data
        slv_wdata_r_internal <= slv_wdata_r_internal;
        end
      end
    end

  //---------------------------------------------------------------------------
  // register the incoming read strobe, this will stay high, so we create a 
  // pulse to use. to generate the request across the clock domain.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_rden_r <= 'd0; // Zero all data
      end
    else begin
      slv_rden_r <= slv_rden;
      end
    end
    
  assign slv_rden_pls = (!slv_rden_r) & slv_rden;

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  // Clk2 clock domain handshake
  // 
  // This logic pass's the Clk2 access request across the clock domain.
  // On the DRP side, a pulse is generated to initialte the Clk2 access. When
  // The RDY pulse is received, a ready signal is passed back across the clock
  // boundary to the AXI clock domain. This causes the valid request to be
  // removed, and when seen on the DRP domain, the ready is lowered.
  // When the ready falling edge is seen in the AXI domain the AXI transaction
  // is finally completed.
  // Although this logic is slow, it minimises the logic required.
  // It also ensures if the Clk2 rate is very slow compared to the AXI rate
  // transactions will fully complete before another can be requested, though
  // in the case the user should probally set wait_for_drp low and poll for
  // the Clk2 completion
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  demo_tb_hsadc_ctrl_hshk_pls_gen clk2clk_handshake_pulse_gen_i(
   .clk1             (s_axi_aclk              ),
   .clk1_rst         (s_axi_aresetn           ),
   
   .clk1_valid       (slv_access_valid_hold   ), // Access in clk1 requested flag, pass to clk2
   .clk1_ready       (slv_wren_clear          ), // Access is complete in clk2, lower request in clk1
   .clk1_ready_pulse (slv_wren_done_pulse     ), // Pulsed on falling edge of clk1_ready, access complete in clk1 & clk2
   
   .clk2             (clk2_clk                ),
   .clk2_rst         (clk2_reset              ),
 
   .clk2_valid       ( ),
   .clk2_valid_pulse (slv_wren_clk2           ),
   .clk2_ready_pulse (slv_wren_clk2           )
    
  );
  
  // Gate the write strobe with the access type. In this case only the read enable
  // is high while we wait for the result
  assign do_write_clk2 = slv_wren_clk2 & (! slv_rden_r);

  //----------------------------------------------------------------------------
  // Register write logic
  //----------------------------------------------------------------------------
   always @( posedge clk2_clk )
   begin
      if (~clk2_reset) begin
        // set RW register defaults

         adc10_enable_0                           <= 8'd0;
         adc10_dg_inc_0                           <= 12'd64;
         adc10_dg_type_0                          <= 3'd0;
         adc10_scaling_factor_0                   <= 32'd1;
         adc10_offset_0                           <= 32'd0;
         adc10_phase_high_0                       <= 16'd0;
         adc10_phase_low_0                        <= 16'd0;
         adc11_enable_0                           <= 8'd0;
         adc11_dg_inc_0                           <= 12'd64;
         adc11_dg_type_0                          <= 3'd0;
         adc11_scaling_factor_0                   <= 32'd1;
         adc11_offset_0                           <= 32'd0;
         adc11_phase_high_0                       <= 16'd0;
         adc11_phase_low_0                        <= 16'd0;
         adc12_enable_0                           <= 8'd0;
         adc12_dg_inc_0                           <= 12'd64;
         adc12_dg_type_0                          <= 3'd0;
         adc12_scaling_factor_0                   <= 32'd1;
         adc12_offset_0                           <= 32'd0;
         adc12_phase_high_0                       <= 16'd0;
         adc12_phase_low_0                        <= 16'd0;
         adc13_enable_0                           <= 8'd0;
         adc13_dg_inc_0                           <= 12'd64;
         adc13_dg_type_0                          <= 3'd0;
         adc13_scaling_factor_0                   <= 32'd1;
         adc13_offset_0                           <= 32'd0;
         adc13_phase_high_0                       <= 16'd0;
         adc13_phase_low_0                        <= 16'd0;

 
      end 
      else begin    
         // on a write we write to the appropriate register
         // Not that slv_rden_r comes from the AXI clock domain, but will be stable
         // when the pulse arrives to register the data.
         if (slv_wren_clk2 & (~slv_rden_r)) begin
            case (slv_addr)
            // WRITE assignments for signal block 0
            'h0     : begin // @ address = 0
                      adc10_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h2     : begin // @ address = 8
                      adc10_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h4     : begin // @ address = 16
                      adc10_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h8     : begin // @ address = 32
                      adc10_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h9     : begin // @ address = 36
                      adc10_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'ha     : begin // @ address = 40
                      adc10_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hb     : begin // @ address = 44
                      adc10_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h40    : begin // @ address = 256
                      adc11_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h42    : begin // @ address = 264
                      adc11_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h44    : begin // @ address = 272
                      adc11_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h48    : begin // @ address = 288
                      adc11_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h49    : begin // @ address = 292
                      adc11_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h4a    : begin // @ address = 296
                      adc11_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h4b    : begin // @ address = 300
                      adc11_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h80    : begin // @ address = 512
                      adc12_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h82    : begin // @ address = 520
                      adc12_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h84    : begin // @ address = 528
                      adc12_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h88    : begin // @ address = 544
                      adc12_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h89    : begin // @ address = 548
                      adc12_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h8a    : begin // @ address = 552
                      adc12_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h8b    : begin // @ address = 556
                      adc12_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'hc0    : begin // @ address = 768
                      adc13_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'hc2    : begin // @ address = 776
                      adc13_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'hc4    : begin // @ address = 784
                      adc13_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'hc8    : begin // @ address = 800
                      adc13_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'hc9    : begin // @ address = 804
                      adc13_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'hca    : begin // @ address = 808
                      adc13_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hcb    : begin // @ address = 812
                      adc13_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end


            endcase
         end   
      end
   end
   
  //----------------------------------------------------------------------------
  // Register read logic
  // All signal come from clk 2, however by design these should be RW signals,
  // originating in this block. Therefore we know these signals will be steady
  // on a read.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      end
    else begin
      slv_rdata <= 'd0; // Zero all data bits, individual bits may be modified in the case below
      case (slv_addr)
      // READ assignments for signal block 0
     'h0     : begin // @ address = 0
               slv_rdata[7:0]       <= adc10_enable_0;
               end
     'h2     : begin // @ address = 8
               slv_rdata[11:0]      <= adc10_dg_inc_0;
               end
     'h4     : begin // @ address = 16
               slv_rdata[2:0]       <= adc10_dg_type_0;
               end
     'h8     : begin // @ address = 32
               slv_rdata[31:0]      <= adc10_scaling_factor_0;
               end
     'h9     : begin // @ address = 36
               slv_rdata[31:0]      <= adc10_offset_0;
               end
     'ha     : begin // @ address = 40
               slv_rdata[15:0]      <= adc10_phase_high_0;
               end
     'hb     : begin // @ address = 44
               slv_rdata[15:0]      <= adc10_phase_low_0;
               end
     'h40    : begin // @ address = 256
               slv_rdata[7:0]       <= adc11_enable_0;
               end
     'h42    : begin // @ address = 264
               slv_rdata[11:0]      <= adc11_dg_inc_0;
               end
     'h44    : begin // @ address = 272
               slv_rdata[2:0]       <= adc11_dg_type_0;
               end
     'h48    : begin // @ address = 288
               slv_rdata[31:0]      <= adc11_scaling_factor_0;
               end
     'h49    : begin // @ address = 292
               slv_rdata[31:0]      <= adc11_offset_0;
               end
     'h4a    : begin // @ address = 296
               slv_rdata[15:0]      <= adc11_phase_high_0;
               end
     'h4b    : begin // @ address = 300
               slv_rdata[15:0]      <= adc11_phase_low_0;
               end
     'h80    : begin // @ address = 512
               slv_rdata[7:0]       <= adc12_enable_0;
               end
     'h82    : begin // @ address = 520
               slv_rdata[11:0]      <= adc12_dg_inc_0;
               end
     'h84    : begin // @ address = 528
               slv_rdata[2:0]       <= adc12_dg_type_0;
               end
     'h88    : begin // @ address = 544
               slv_rdata[31:0]      <= adc12_scaling_factor_0;
               end
     'h89    : begin // @ address = 548
               slv_rdata[31:0]      <= adc12_offset_0;
               end
     'h8a    : begin // @ address = 552
               slv_rdata[15:0]      <= adc12_phase_high_0;
               end
     'h8b    : begin // @ address = 556
               slv_rdata[15:0]      <= adc12_phase_low_0;
               end
     'hc0    : begin // @ address = 768
               slv_rdata[7:0]       <= adc13_enable_0;
               end
     'hc2    : begin // @ address = 776
               slv_rdata[11:0]      <= adc13_dg_inc_0;
               end
     'hc4    : begin // @ address = 784
               slv_rdata[2:0]       <= adc13_dg_type_0;
               end
     'hc8    : begin // @ address = 800
               slv_rdata[31:0]      <= adc13_scaling_factor_0;
               end
     'hc9    : begin // @ address = 804
               slv_rdata[31:0]      <= adc13_offset_0;
               end
     'hca    : begin // @ address = 808
               slv_rdata[15:0]      <= adc13_phase_high_0;
               end
     'hcb    : begin // @ address = 812
               slv_rdata[15:0]      <= adc13_phase_low_0;
               end

      default: slv_rdata            <= 'd0;
      endcase
      end
    end
   
   //---------------------------------------------------------------------------
   // read/write done logic.
   // Completed with the retruning pulse from the clk2 domain
   //---------------------------------------------------------------------------
   always @(*)
     begin
     slv_rd_done = slv_wren_done_pulse & (  slv_rden_r) ;
     slv_wr_done = slv_wren_done_pulse & (! slv_rden_r);
     end

endmodule
//-----------------------------------------------------------------------------
// Title      : adc2_demo_tb_hsadc_ctrl_axi
// Project    : NA
//-----------------------------------------------------------------------------
// File       : adc2_demo_tb_hsadc_ctrl_axi.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module adc2_demo_tb_hsadc_ctrl_axi #(
   parameter integer                   C_S_AXI_ADDR_WIDTH   = 11
   )
(
   input                                  s_axi_aclk,
   input                                  s_axi_aresetn,

   input                                  clk2_clk,
   input                                  clk2_reset,
   
   // IO for bank 0 
   output reg  [7:0]                      adc20_enable_0 = 0,
   output reg  [11:0]                     adc20_dg_inc_0 = 64,
   output reg  [2:0]                      adc20_dg_type_0 = 0,
   output reg  [31:0]                     adc20_scaling_factor_0 = 1,
   output reg  [31:0]                     adc20_offset_0 = 0,
   output reg  [15:0]                     adc20_phase_high_0 = 0,
   output reg  [15:0]                     adc20_phase_low_0 = 0,
   output reg  [7:0]                      adc21_enable_0 = 0,
   output reg  [11:0]                     adc21_dg_inc_0 = 64,
   output reg  [2:0]                      adc21_dg_type_0 = 0,
   output reg  [31:0]                     adc21_scaling_factor_0 = 1,
   output reg  [31:0]                     adc21_offset_0 = 0,
   output reg  [15:0]                     adc21_phase_high_0 = 0,
   output reg  [15:0]                     adc21_phase_low_0 = 0,
   output reg  [7:0]                      adc22_enable_0 = 0,
   output reg  [11:0]                     adc22_dg_inc_0 = 64,
   output reg  [2:0]                      adc22_dg_type_0 = 0,
   output reg  [31:0]                     adc22_scaling_factor_0 = 1,
   output reg  [31:0]                     adc22_offset_0 = 0,
   output reg  [15:0]                     adc22_phase_high_0 = 0,
   output reg  [15:0]                     adc22_phase_low_0 = 0,
   output reg  [7:0]                      adc23_enable_0 = 0,
   output reg  [11:0]                     adc23_dg_inc_0 = 64,
   output reg  [2:0]                      adc23_dg_type_0 = 0,
   output reg  [31:0]                     adc23_scaling_factor_0 = 1,
   output reg  [31:0]                     adc23_offset_0 = 0,
   output reg  [15:0]                     adc23_phase_high_0 = 0,
   output reg  [15:0]                     adc23_phase_low_0 = 0,

 
   // basic register interface
   input                                  slv_rden,
   input                                  slv_wren,
   input       [31:0]                     slv_wdata,
   input       [C_S_AXI_ADDR_WIDTH-1:2]   slv_addr,
   
   output reg                             slv_rd_done,
   output reg                             slv_wr_done,
   output reg  [31:0]                     slv_rdata
 
);

  localparam C_INT_ADDRWIDTH = C_S_AXI_ADDR_WIDTH - 2;

  //----------------------------------------------------------------------------
  // Internal reg/wire declarations
  //----------------------------------------------------------------------------

  reg         slv_rden_r;            // Registered incoming read 
  wire        slv_rden_pls;          // Internally generated pulse
  reg         slv_access_valid_hold; // Flag indicates access in progress in axi domain
  wire        slv_wren_clear;        // Clears the held access valid signal
  reg         slv_access_is_read;    // High is access is a read
  reg  [31:0] slv_wdata_r_internal;  // Register the write data
  wire        slv_wren_clk2;         // Pulse on clk2 when rising edge of valid seen
  wire        slv_wren_done_pulse;   // Pulse on falling edge of clk1_ready
  wire        do_write_clk2;         // Use for debug

  //----------------------------------------------------------------------------
  // Create a held wr or rd signal. This is used to flag an access in progress
  // accross the clock domain.  This is reset when the signal has passed back
  // from the clk2 domain into the axi domain
  //----------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_access_valid_hold <= 'd0;
      slv_wdata_r_internal <= 'd0;
      end
    else begin
      if(slv_wren | slv_rden_pls) begin
        slv_access_valid_hold <= 'd1;
        // register the data locally for cross clock domain crossing
        slv_wdata_r_internal <= slv_wdata;
        end
      else begin
        if(slv_wren_clear) begin
          slv_access_valid_hold <= 'd0;
          end
        // Hold data
        slv_wdata_r_internal <= slv_wdata_r_internal;
        end
      end
    end

  //---------------------------------------------------------------------------
  // register the incoming read strobe, this will stay high, so we create a 
  // pulse to use. to generate the request across the clock domain.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_rden_r <= 'd0; // Zero all data
      end
    else begin
      slv_rden_r <= slv_rden;
      end
    end
    
  assign slv_rden_pls = (!slv_rden_r) & slv_rden;

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  // Clk2 clock domain handshake
  // 
  // This logic pass's the Clk2 access request across the clock domain.
  // On the DRP side, a pulse is generated to initialte the Clk2 access. When
  // The RDY pulse is received, a ready signal is passed back across the clock
  // boundary to the AXI clock domain. This causes the valid request to be
  // removed, and when seen on the DRP domain, the ready is lowered.
  // When the ready falling edge is seen in the AXI domain the AXI transaction
  // is finally completed.
  // Although this logic is slow, it minimises the logic required.
  // It also ensures if the Clk2 rate is very slow compared to the AXI rate
  // transactions will fully complete before another can be requested, though
  // in the case the user should probally set wait_for_drp low and poll for
  // the Clk2 completion
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  demo_tb_hsadc_ctrl_hshk_pls_gen clk2clk_handshake_pulse_gen_i(
   .clk1             (s_axi_aclk              ),
   .clk1_rst         (s_axi_aresetn           ),
   
   .clk1_valid       (slv_access_valid_hold   ), // Access in clk1 requested flag, pass to clk2
   .clk1_ready       (slv_wren_clear          ), // Access is complete in clk2, lower request in clk1
   .clk1_ready_pulse (slv_wren_done_pulse     ), // Pulsed on falling edge of clk1_ready, access complete in clk1 & clk2
   
   .clk2             (clk2_clk                ),
   .clk2_rst         (clk2_reset              ),
 
   .clk2_valid       ( ),
   .clk2_valid_pulse (slv_wren_clk2           ),
   .clk2_ready_pulse (slv_wren_clk2           )
    
  );
  
  // Gate the write strobe with the access type. In this case only the read enable
  // is high while we wait for the result
  assign do_write_clk2 = slv_wren_clk2 & (! slv_rden_r);

  //----------------------------------------------------------------------------
  // Register write logic
  //----------------------------------------------------------------------------
   always @( posedge clk2_clk )
   begin
      if (~clk2_reset) begin
        // set RW register defaults

         adc20_enable_0                           <= 8'd0;
         adc20_dg_inc_0                           <= 12'd64;
         adc20_dg_type_0                          <= 3'd0;
         adc20_scaling_factor_0                   <= 32'd1;
         adc20_offset_0                           <= 32'd0;
         adc20_phase_high_0                       <= 16'd0;
         adc20_phase_low_0                        <= 16'd0;
         adc21_enable_0                           <= 8'd0;
         adc21_dg_inc_0                           <= 12'd64;
         adc21_dg_type_0                          <= 3'd0;
         adc21_scaling_factor_0                   <= 32'd1;
         adc21_offset_0                           <= 32'd0;
         adc21_phase_high_0                       <= 16'd0;
         adc21_phase_low_0                        <= 16'd0;
         adc22_enable_0                           <= 8'd0;
         adc22_dg_inc_0                           <= 12'd64;
         adc22_dg_type_0                          <= 3'd0;
         adc22_scaling_factor_0                   <= 32'd1;
         adc22_offset_0                           <= 32'd0;
         adc22_phase_high_0                       <= 16'd0;
         adc22_phase_low_0                        <= 16'd0;
         adc23_enable_0                           <= 8'd0;
         adc23_dg_inc_0                           <= 12'd64;
         adc23_dg_type_0                          <= 3'd0;
         adc23_scaling_factor_0                   <= 32'd1;
         adc23_offset_0                           <= 32'd0;
         adc23_phase_high_0                       <= 16'd0;
         adc23_phase_low_0                        <= 16'd0;

 
      end 
      else begin    
         // on a write we write to the appropriate register
         // Not that slv_rden_r comes from the AXI clock domain, but will be stable
         // when the pulse arrives to register the data.
         if (slv_wren_clk2 & (~slv_rden_r)) begin
            case (slv_addr)
            // WRITE assignments for signal block 0
            'h0     : begin // @ address = 0
                      adc20_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h2     : begin // @ address = 8
                      adc20_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h4     : begin // @ address = 16
                      adc20_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h8     : begin // @ address = 32
                      adc20_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h9     : begin // @ address = 36
                      adc20_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'ha     : begin // @ address = 40
                      adc20_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hb     : begin // @ address = 44
                      adc20_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h40    : begin // @ address = 256
                      adc21_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h42    : begin // @ address = 264
                      adc21_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h44    : begin // @ address = 272
                      adc21_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h48    : begin // @ address = 288
                      adc21_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h49    : begin // @ address = 292
                      adc21_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h4a    : begin // @ address = 296
                      adc21_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h4b    : begin // @ address = 300
                      adc21_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h80    : begin // @ address = 512
                      adc22_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h82    : begin // @ address = 520
                      adc22_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h84    : begin // @ address = 528
                      adc22_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h88    : begin // @ address = 544
                      adc22_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h89    : begin // @ address = 548
                      adc22_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h8a    : begin // @ address = 552
                      adc22_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h8b    : begin // @ address = 556
                      adc22_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'hc0    : begin // @ address = 768
                      adc23_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'hc2    : begin // @ address = 776
                      adc23_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'hc4    : begin // @ address = 784
                      adc23_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'hc8    : begin // @ address = 800
                      adc23_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'hc9    : begin // @ address = 804
                      adc23_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'hca    : begin // @ address = 808
                      adc23_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hcb    : begin // @ address = 812
                      adc23_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end


            endcase
         end   
      end
   end
   
  //----------------------------------------------------------------------------
  // Register read logic
  // All signal come from clk 2, however by design these should be RW signals,
  // originating in this block. Therefore we know these signals will be steady
  // on a read.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      end
    else begin
      slv_rdata <= 'd0; // Zero all data bits, individual bits may be modified in the case below
      case (slv_addr)
      // READ assignments for signal block 0
     'h0     : begin // @ address = 0
               slv_rdata[7:0]       <= adc20_enable_0;
               end
     'h2     : begin // @ address = 8
               slv_rdata[11:0]      <= adc20_dg_inc_0;
               end
     'h4     : begin // @ address = 16
               slv_rdata[2:0]       <= adc20_dg_type_0;
               end
     'h8     : begin // @ address = 32
               slv_rdata[31:0]      <= adc20_scaling_factor_0;
               end
     'h9     : begin // @ address = 36
               slv_rdata[31:0]      <= adc20_offset_0;
               end
     'ha     : begin // @ address = 40
               slv_rdata[15:0]      <= adc20_phase_high_0;
               end
     'hb     : begin // @ address = 44
               slv_rdata[15:0]      <= adc20_phase_low_0;
               end
     'h40    : begin // @ address = 256
               slv_rdata[7:0]       <= adc21_enable_0;
               end
     'h42    : begin // @ address = 264
               slv_rdata[11:0]      <= adc21_dg_inc_0;
               end
     'h44    : begin // @ address = 272
               slv_rdata[2:0]       <= adc21_dg_type_0;
               end
     'h48    : begin // @ address = 288
               slv_rdata[31:0]      <= adc21_scaling_factor_0;
               end
     'h49    : begin // @ address = 292
               slv_rdata[31:0]      <= adc21_offset_0;
               end
     'h4a    : begin // @ address = 296
               slv_rdata[15:0]      <= adc21_phase_high_0;
               end
     'h4b    : begin // @ address = 300
               slv_rdata[15:0]      <= adc21_phase_low_0;
               end
     'h80    : begin // @ address = 512
               slv_rdata[7:0]       <= adc22_enable_0;
               end
     'h82    : begin // @ address = 520
               slv_rdata[11:0]      <= adc22_dg_inc_0;
               end
     'h84    : begin // @ address = 528
               slv_rdata[2:0]       <= adc22_dg_type_0;
               end
     'h88    : begin // @ address = 544
               slv_rdata[31:0]      <= adc22_scaling_factor_0;
               end
     'h89    : begin // @ address = 548
               slv_rdata[31:0]      <= adc22_offset_0;
               end
     'h8a    : begin // @ address = 552
               slv_rdata[15:0]      <= adc22_phase_high_0;
               end
     'h8b    : begin // @ address = 556
               slv_rdata[15:0]      <= adc22_phase_low_0;
               end
     'hc0    : begin // @ address = 768
               slv_rdata[7:0]       <= adc23_enable_0;
               end
     'hc2    : begin // @ address = 776
               slv_rdata[11:0]      <= adc23_dg_inc_0;
               end
     'hc4    : begin // @ address = 784
               slv_rdata[2:0]       <= adc23_dg_type_0;
               end
     'hc8    : begin // @ address = 800
               slv_rdata[31:0]      <= adc23_scaling_factor_0;
               end
     'hc9    : begin // @ address = 804
               slv_rdata[31:0]      <= adc23_offset_0;
               end
     'hca    : begin // @ address = 808
               slv_rdata[15:0]      <= adc23_phase_high_0;
               end
     'hcb    : begin // @ address = 812
               slv_rdata[15:0]      <= adc23_phase_low_0;
               end

      default: slv_rdata            <= 'd0;
      endcase
      end
    end
   
   //---------------------------------------------------------------------------
   // read/write done logic.
   // Completed with the retruning pulse from the clk2 domain
   //---------------------------------------------------------------------------
   always @(*)
     begin
     slv_rd_done = slv_wren_done_pulse & (  slv_rden_r) ;
     slv_wr_done = slv_wren_done_pulse & (! slv_rden_r);
     end

endmodule
//-----------------------------------------------------------------------------
// Title      : adc3_demo_tb_hsadc_ctrl_axi
// Project    : NA
//-----------------------------------------------------------------------------
// File       : adc3_demo_tb_hsadc_ctrl_axi.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module adc3_demo_tb_hsadc_ctrl_axi #(
   parameter integer                   C_S_AXI_ADDR_WIDTH   = 11
   )
(
   input                                  s_axi_aclk,
   input                                  s_axi_aresetn,

   input                                  clk2_clk,
   input                                  clk2_reset,
   
   // IO for bank 0 
   output reg  [7:0]                      adc30_enable_0 = 0,
   output reg  [11:0]                     adc30_dg_inc_0 = 64,
   output reg  [2:0]                      adc30_dg_type_0 = 0,
   output reg  [31:0]                     adc30_scaling_factor_0 = 1,
   output reg  [31:0]                     adc30_offset_0 = 0,
   output reg  [15:0]                     adc30_phase_high_0 = 0,
   output reg  [15:0]                     adc30_phase_low_0 = 0,
   output reg  [7:0]                      adc31_enable_0 = 0,
   output reg  [11:0]                     adc31_dg_inc_0 = 64,
   output reg  [2:0]                      adc31_dg_type_0 = 0,
   output reg  [31:0]                     adc31_scaling_factor_0 = 1,
   output reg  [31:0]                     adc31_offset_0 = 0,
   output reg  [15:0]                     adc31_phase_high_0 = 0,
   output reg  [15:0]                     adc31_phase_low_0 = 0,
   output reg  [7:0]                      adc32_enable_0 = 0,
   output reg  [11:0]                     adc32_dg_inc_0 = 64,
   output reg  [2:0]                      adc32_dg_type_0 = 0,
   output reg  [31:0]                     adc32_scaling_factor_0 = 1,
   output reg  [31:0]                     adc32_offset_0 = 0,
   output reg  [15:0]                     adc32_phase_high_0 = 0,
   output reg  [15:0]                     adc32_phase_low_0 = 0,
   output reg  [7:0]                      adc33_enable_0 = 0,
   output reg  [11:0]                     adc33_dg_inc_0 = 64,
   output reg  [2:0]                      adc33_dg_type_0 = 0,
   output reg  [31:0]                     adc33_scaling_factor_0 = 1,
   output reg  [31:0]                     adc33_offset_0 = 0,
   output reg  [15:0]                     adc33_phase_high_0 = 0,
   output reg  [15:0]                     adc33_phase_low_0 = 0,

 
   // basic register interface
   input                                  slv_rden,
   input                                  slv_wren,
   input       [31:0]                     slv_wdata,
   input       [C_S_AXI_ADDR_WIDTH-1:2]   slv_addr,
   
   output reg                             slv_rd_done,
   output reg                             slv_wr_done,
   output reg  [31:0]                     slv_rdata
 
);

  localparam C_INT_ADDRWIDTH = C_S_AXI_ADDR_WIDTH - 2;

  //----------------------------------------------------------------------------
  // Internal reg/wire declarations
  //----------------------------------------------------------------------------

  reg         slv_rden_r;            // Registered incoming read 
  wire        slv_rden_pls;          // Internally generated pulse
  reg         slv_access_valid_hold; // Flag indicates access in progress in axi domain
  wire        slv_wren_clear;        // Clears the held access valid signal
  reg         slv_access_is_read;    // High is access is a read
  reg  [31:0] slv_wdata_r_internal;  // Register the write data
  wire        slv_wren_clk2;         // Pulse on clk2 when rising edge of valid seen
  wire        slv_wren_done_pulse;   // Pulse on falling edge of clk1_ready
  wire        do_write_clk2;         // Use for debug

  //----------------------------------------------------------------------------
  // Create a held wr or rd signal. This is used to flag an access in progress
  // accross the clock domain.  This is reset when the signal has passed back
  // from the clk2 domain into the axi domain
  //----------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_access_valid_hold <= 'd0;
      slv_wdata_r_internal <= 'd0;
      end
    else begin
      if(slv_wren | slv_rden_pls) begin
        slv_access_valid_hold <= 'd1;
        // register the data locally for cross clock domain crossing
        slv_wdata_r_internal <= slv_wdata;
        end
      else begin
        if(slv_wren_clear) begin
          slv_access_valid_hold <= 'd0;
          end
        // Hold data
        slv_wdata_r_internal <= slv_wdata_r_internal;
        end
      end
    end

  //---------------------------------------------------------------------------
  // register the incoming read strobe, this will stay high, so we create a 
  // pulse to use. to generate the request across the clock domain.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      slv_rden_r <= 'd0; // Zero all data
      end
    else begin
      slv_rden_r <= slv_rden;
      end
    end
    
  assign slv_rden_pls = (!slv_rden_r) & slv_rden;

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  // Clk2 clock domain handshake
  // 
  // This logic pass's the Clk2 access request across the clock domain.
  // On the DRP side, a pulse is generated to initialte the Clk2 access. When
  // The RDY pulse is received, a ready signal is passed back across the clock
  // boundary to the AXI clock domain. This causes the valid request to be
  // removed, and when seen on the DRP domain, the ready is lowered.
  // When the ready falling edge is seen in the AXI domain the AXI transaction
  // is finally completed.
  // Although this logic is slow, it minimises the logic required.
  // It also ensures if the Clk2 rate is very slow compared to the AXI rate
  // transactions will fully complete before another can be requested, though
  // in the case the user should probally set wait_for_drp low and poll for
  // the Clk2 completion
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  demo_tb_hsadc_ctrl_hshk_pls_gen clk2clk_handshake_pulse_gen_i(
   .clk1             (s_axi_aclk              ),
   .clk1_rst         (s_axi_aresetn           ),
   
   .clk1_valid       (slv_access_valid_hold   ), // Access in clk1 requested flag, pass to clk2
   .clk1_ready       (slv_wren_clear          ), // Access is complete in clk2, lower request in clk1
   .clk1_ready_pulse (slv_wren_done_pulse     ), // Pulsed on falling edge of clk1_ready, access complete in clk1 & clk2
   
   .clk2             (clk2_clk                ),
   .clk2_rst         (clk2_reset              ),
 
   .clk2_valid       ( ),
   .clk2_valid_pulse (slv_wren_clk2           ),
   .clk2_ready_pulse (slv_wren_clk2           )
    
  );
  
  // Gate the write strobe with the access type. In this case only the read enable
  // is high while we wait for the result
  assign do_write_clk2 = slv_wren_clk2 & (! slv_rden_r);

  //----------------------------------------------------------------------------
  // Register write logic
  //----------------------------------------------------------------------------
   always @( posedge clk2_clk )
   begin
      if (~clk2_reset) begin
        // set RW register defaults

         adc30_enable_0                           <= 8'd0;
         adc30_dg_inc_0                           <= 12'd64;
         adc30_dg_type_0                          <= 3'd0;
         adc30_scaling_factor_0                   <= 32'd1;
         adc30_offset_0                           <= 32'd0;
         adc30_phase_high_0                       <= 16'd0;
         adc30_phase_low_0                        <= 16'd0;
         adc31_enable_0                           <= 8'd0;
         adc31_dg_inc_0                           <= 12'd64;
         adc31_dg_type_0                          <= 3'd0;
         adc31_scaling_factor_0                   <= 32'd1;
         adc31_offset_0                           <= 32'd0;
         adc31_phase_high_0                       <= 16'd0;
         adc31_phase_low_0                        <= 16'd0;
         adc32_enable_0                           <= 8'd0;
         adc32_dg_inc_0                           <= 12'd64;
         adc32_dg_type_0                          <= 3'd0;
         adc32_scaling_factor_0                   <= 32'd1;
         adc32_offset_0                           <= 32'd0;
         adc32_phase_high_0                       <= 16'd0;
         adc32_phase_low_0                        <= 16'd0;
         adc33_enable_0                           <= 8'd0;
         adc33_dg_inc_0                           <= 12'd64;
         adc33_dg_type_0                          <= 3'd0;
         adc33_scaling_factor_0                   <= 32'd1;
         adc33_offset_0                           <= 32'd0;
         adc33_phase_high_0                       <= 16'd0;
         adc33_phase_low_0                        <= 16'd0;

 
      end 
      else begin    
         // on a write we write to the appropriate register
         // Not that slv_rden_r comes from the AXI clock domain, but will be stable
         // when the pulse arrives to register the data.
         if (slv_wren_clk2 & (~slv_rden_r)) begin
            case (slv_addr)
            // WRITE assignments for signal block 0
            'h0     : begin // @ address = 0
                      adc30_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h2     : begin // @ address = 8
                      adc30_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h4     : begin // @ address = 16
                      adc30_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h8     : begin // @ address = 32
                      adc30_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h9     : begin // @ address = 36
                      adc30_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'ha     : begin // @ address = 40
                      adc30_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hb     : begin // @ address = 44
                      adc30_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h40    : begin // @ address = 256
                      adc31_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h42    : begin // @ address = 264
                      adc31_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h44    : begin // @ address = 272
                      adc31_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h48    : begin // @ address = 288
                      adc31_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h49    : begin // @ address = 292
                      adc31_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h4a    : begin // @ address = 296
                      adc31_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h4b    : begin // @ address = 300
                      adc31_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'h80    : begin // @ address = 512
                      adc32_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'h82    : begin // @ address = 520
                      adc32_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'h84    : begin // @ address = 528
                      adc32_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'h88    : begin // @ address = 544
                      adc32_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'h89    : begin // @ address = 548
                      adc32_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'h8a    : begin // @ address = 552
                      adc32_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'h8b    : begin // @ address = 556
                      adc32_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end
            'hc0    : begin // @ address = 768
                      adc33_enable_0                           <= slv_wdata_r_internal[7:0];
                      end
            'hc2    : begin // @ address = 776
                      adc33_dg_inc_0                           <= slv_wdata_r_internal[11:0];
                      end
            'hc4    : begin // @ address = 784
                      adc33_dg_type_0                          <= slv_wdata_r_internal[2:0];
                      end
            'hc8    : begin // @ address = 800
                      adc33_scaling_factor_0                   <= slv_wdata_r_internal[31:0];
                      end
            'hc9    : begin // @ address = 804
                      adc33_offset_0                           <= slv_wdata_r_internal[31:0];
                      end
            'hca    : begin // @ address = 808
                      adc33_phase_high_0                       <= slv_wdata_r_internal[15:0];
                      end
            'hcb    : begin // @ address = 812
                      adc33_phase_low_0                        <= slv_wdata_r_internal[15:0];
                      end


            endcase
         end   
      end
   end
   
  //----------------------------------------------------------------------------
  // Register read logic
  // All signal come from clk 2, however by design these should be RW signals,
  // originating in this block. Therefore we know these signals will be steady
  // on a read.
  //---------------------------------------------------------------------------
  always @( posedge s_axi_aclk ) begin
    if ( ~s_axi_aresetn ) begin
      end
    else begin
      slv_rdata <= 'd0; // Zero all data bits, individual bits may be modified in the case below
      case (slv_addr)
      // READ assignments for signal block 0
     'h0     : begin // @ address = 0
               slv_rdata[7:0]       <= adc30_enable_0;
               end
     'h2     : begin // @ address = 8
               slv_rdata[11:0]      <= adc30_dg_inc_0;
               end
     'h4     : begin // @ address = 16
               slv_rdata[2:0]       <= adc30_dg_type_0;
               end
     'h8     : begin // @ address = 32
               slv_rdata[31:0]      <= adc30_scaling_factor_0;
               end
     'h9     : begin // @ address = 36
               slv_rdata[31:0]      <= adc30_offset_0;
               end
     'ha     : begin // @ address = 40
               slv_rdata[15:0]      <= adc30_phase_high_0;
               end
     'hb     : begin // @ address = 44
               slv_rdata[15:0]      <= adc30_phase_low_0;
               end
     'h40    : begin // @ address = 256
               slv_rdata[7:0]       <= adc31_enable_0;
               end
     'h42    : begin // @ address = 264
               slv_rdata[11:0]      <= adc31_dg_inc_0;
               end
     'h44    : begin // @ address = 272
               slv_rdata[2:0]       <= adc31_dg_type_0;
               end
     'h48    : begin // @ address = 288
               slv_rdata[31:0]      <= adc31_scaling_factor_0;
               end
     'h49    : begin // @ address = 292
               slv_rdata[31:0]      <= adc31_offset_0;
               end
     'h4a    : begin // @ address = 296
               slv_rdata[15:0]      <= adc31_phase_high_0;
               end
     'h4b    : begin // @ address = 300
               slv_rdata[15:0]      <= adc31_phase_low_0;
               end
     'h80    : begin // @ address = 512
               slv_rdata[7:0]       <= adc32_enable_0;
               end
     'h82    : begin // @ address = 520
               slv_rdata[11:0]      <= adc32_dg_inc_0;
               end
     'h84    : begin // @ address = 528
               slv_rdata[2:0]       <= adc32_dg_type_0;
               end
     'h88    : begin // @ address = 544
               slv_rdata[31:0]      <= adc32_scaling_factor_0;
               end
     'h89    : begin // @ address = 548
               slv_rdata[31:0]      <= adc32_offset_0;
               end
     'h8a    : begin // @ address = 552
               slv_rdata[15:0]      <= adc32_phase_high_0;
               end
     'h8b    : begin // @ address = 556
               slv_rdata[15:0]      <= adc32_phase_low_0;
               end
     'hc0    : begin // @ address = 768
               slv_rdata[7:0]       <= adc33_enable_0;
               end
     'hc2    : begin // @ address = 776
               slv_rdata[11:0]      <= adc33_dg_inc_0;
               end
     'hc4    : begin // @ address = 784
               slv_rdata[2:0]       <= adc33_dg_type_0;
               end
     'hc8    : begin // @ address = 800
               slv_rdata[31:0]      <= adc33_scaling_factor_0;
               end
     'hc9    : begin // @ address = 804
               slv_rdata[31:0]      <= adc33_offset_0;
               end
     'hca    : begin // @ address = 808
               slv_rdata[15:0]      <= adc33_phase_high_0;
               end
     'hcb    : begin // @ address = 812
               slv_rdata[15:0]      <= adc33_phase_low_0;
               end

      default: slv_rdata            <= 'd0;
      endcase
      end
    end
   
   //---------------------------------------------------------------------------
   // read/write done logic.
   // Completed with the retruning pulse from the clk2 domain
   //---------------------------------------------------------------------------
   always @(*)
     begin
     slv_rd_done = slv_wren_done_pulse & (  slv_rden_r) ;
     slv_wr_done = slv_wren_done_pulse & (! slv_rden_r);
     end

endmodule
//-----------------------------------------------------------------------------
// Title      : adc_demo_tb_cfg
// Project    : NA
//-----------------------------------------------------------------------------
// File       : adc_demo_tb_cfg.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module adc_demo_tb_cfg #(
   parameter integer                   C_S_AXI_ADDR_WIDTH   = 11
   )
(
   input                                  s_axi_aclk,
   input                                  s_axi_aresetn,
   
   // 
   output reg                             enable = 0,

 
   // basic register interface
   input                                  slv_rden,
   input                                  slv_wren,
   input       [31:0]                     slv_wdata,
   input       [C_S_AXI_ADDR_WIDTH-1:2]   slv_addr,
   
   output reg                             slv_rd_done,
   output reg                             slv_wr_done,
   output reg  [31:0]                     slv_rdata
 
);

  localparam C_INT_ADDRWIDTH = C_S_AXI_ADDR_WIDTH - 2;

  //----------------------------------------------------------------------------
  // Internal reg/wire declarations
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // constant wire asisgnments, ease readability instead of coding into the
  // register read statement
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // Register write logic
  //----------------------------------------------------------------------------
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
        // set RW register defaults
         enable                                   <= 1'd0;

      end
      else begin

         // on a write we write to the appropiate register 
         if (slv_wren) begin
            case (slv_addr)
            'h0     : begin // @ address = 0x0000
                      enable                                   <= slv_wdata[0];
                      end

            endcase
         end
      end
   end
   
   //---------------------------------------------------------------------------
   // Register read logic, non registered, 
   //---------------------------------------------------------------------------
   always @(*)
     begin
     slv_rdata = 'd0; // Zero all data
     case (slv_addr)
     'h0     : begin // @ address = 0x0000
               slv_rdata[0]         = enable;
               end

     default   : slv_rdata = 'd0;
     endcase
     end
   
   //---------------------------------------------------------------------------
   // read/write done logic.
   // For the basic register bank these are fed directly back in as the reg
   // delay is known and fixed.
   //---------------------------------------------------------------------------
   always @(*)
     begin
     slv_rd_done = slv_rden;
     slv_wr_done = slv_wren;
     end

endmodule
//-----------------------------------------------------------------------------
// Title      : demo_tb_hsadc_ctrl_ax4l
// Project    : NA
//-----------------------------------------------------------------------------
// File       : demo_tb_hsadc_ctrl_ax4l.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

//-----------------------------------------------------------------------------
// AMBA AXI and ACE Protocol Specification
// ARM IHI 0022D (ID102711)
// Note section's:
//                A3.3 Relationships between channels
//                B1   AMBA AXI4-Lite
//-----------------------------------------------------------------------------
module demo_tb_hsadc_ctrl_axi #(
 
   parameter integer                   C_S_AXI_ADDR_WIDTH   = 18,
   parameter integer                   BANK_DECODE_HIGH_BIT = 17,
   parameter integer                   BANK_DECODE_HIGH_LOW = 12,
   parameter integer                   C_S_TIMEOUT_WIDTH = 12
     )
(
   input                                  s_axi_aclk,
   input                                  s_axi_aresetn,
   input       [C_S_AXI_ADDR_WIDTH-1:0]   s_axi_awaddr,
   input                                  s_axi_awvalid,
   output                                 s_axi_awready,
   input       [31:0]                     s_axi_wdata,
   input                                  s_axi_wvalid,
   output                                 s_axi_wready,
   output      [1:0]                      s_axi_bresp,
   output                                 s_axi_bvalid,
   input                                  s_axi_bready,
   input       [C_S_AXI_ADDR_WIDTH-1:0]   s_axi_araddr,
   input                                  s_axi_arvalid,
   output                                 s_axi_arready,
   output      [31:0]                     s_axi_rdata,
   output      [1:0]                      s_axi_rresp,
   output                                 s_axi_rvalid,
   input                                  s_axi_rready,
   
   // Strobes & data bank connections
   output                                 adc0slv_wren,
   output  reg                            adc0slv_rden,
   input                                  adc0slv_wr_done,
   input                                  adc0slv_rd_done,
   input        [31:0]                    adc0slv_rdata,

   output                                 adc1slv_wren,
   output  reg                            adc1slv_rden,
   input                                  adc1slv_wr_done,
   input                                  adc1slv_rd_done,
   input        [31:0]                    adc1slv_rdata,

   output                                 adc2slv_wren,
   output  reg                            adc2slv_rden,
   input                                  adc2slv_wr_done,
   input                                  adc2slv_rd_done,
   input        [31:0]                    adc2slv_rdata,

   output                                 adc3slv_wren,
   output  reg                            adc3slv_rden,
   input                                  adc3slv_wr_done,
   input                                  adc3slv_rd_done,
   input        [31:0]                    adc3slv_rdata,

   output                                 cfg_slv_wren,
   output  reg                            cfg_slv_rden,
   input                                  cfg_slv_wr_done,
   input                                  cfg_slv_rd_done,
   input        [31:0]                    cfg_slv_rdata,

   input                                  timeout_enable_in,
   input       [C_S_TIMEOUT_WIDTH-1:0]    timeout_value_in,

   output      [31:0]                     slv_wdata,
   output reg  [BANK_DECODE_HIGH_LOW-1:2] slv_addr,
   output reg                             slv_reg_rden

);

   localparam                             ADC0BANK_SEL         = 'd1;
   localparam                             ADC1BANK_SEL         = 'd2;
   localparam                             ADC2BANK_SEL         = 'd3;
   localparam                             ADC3BANK_SEL         = 'd4;
   localparam                             CFG_BANK_SEL         = 'd0;
   localparam                             BANK_DECODE          = BANK_DECODE_HIGH_BIT - BANK_DECODE_HIGH_LOW;

   // AXI4LITE signals
   reg                                    axi_awready = 0;
   reg                                    axi_wready  = 0;
   reg         [1:0]                      axi_bresp   = 0;
   reg                                    axi_bvalid  = 0;
   reg                                    axi_arready = 0;
   reg         [31:0]                     axi_rdata   = 0;
   reg         [1:0]                      axi_rresp   = 0;
   reg                                    axi_rvalid  = 0;

   reg                                    valid_waddr = 0;

   reg                                    adc0axi_map_wready;
   wire                                   adc0axi_map_selected;
   reg                                    adc1axi_map_wready;
   wire                                   adc1axi_map_selected;
   reg                                    adc2axi_map_wready;
   wire                                   adc2axi_map_selected;
   reg                                    adc3axi_map_wready;
   wire                                   adc3axi_map_selected;
   reg                                    cfg_axi_map_wready;
   wire                                   cfg_axi_map_selected;
    
   wire                                   or_all_mapped_wready;
   
   reg         [BANK_DECODE:0]            slv_rd_addr = 0;
   reg                                    slv_reg_done; // correct read done indicator, muxed using read address
   
   // Timeout signals
   wire                                   load_timeout_timer;
   wire                                   clear_timeout_timer;
   wire                                   timeout;
   reg         [C_S_TIMEOUT_WIDTH:0]      timeout_timer_count;
      
   // Flags to stretch access response
   reg                                    read_in_progress;
   reg                                    write_in_progress;
         
   // I/O Connections assignments

   assign s_axi_awready                = axi_awready;                              
   assign s_axi_wready                 = axi_wready;                               
   assign s_axi_bresp                  = axi_bresp;                                
   assign s_axi_bvalid                 = axi_bvalid;                               
   assign s_axi_arready                = axi_arready;                              
   assign s_axi_rdata                  = axi_rdata;                                
   assign s_axi_rresp                  = axi_rresp;                                
   assign s_axi_rvalid                 = axi_rvalid;
   
   assign slv_wdata                    = s_axi_wdata;
   
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------         
// WRITE LOGIC
//---------------------------------------------------------------------------         
//---------------------------------------------------------------------------         
   // Due the potential transaction stretching capabilites of the banks, 
   // we need to keep a track of an ongoing write transaction to prevent
   // reads starting
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         write_in_progress                   <= 1'b0;
      end 
      else begin    
         if ( (s_axi_bready && s_axi_bvalid) | 
               timeout
             ) begin
           // End of a valid write phase, i.e. the complete axi transaction
           // Note this may have been triggered by a timeout
           write_in_progress                <= 1'b0;
         end
         else begin
           if ((axi_awready && s_axi_awvalid)|(axi_wready && s_axi_wvalid)) begin
             // indicates that the slave has acceped the valid read address
             write_in_progress              <= 1'b1;
           end
         end
      end 
   end       
   
   // The axi spec states there is no relationship between the different interfaces.
   // this means the data can complete before the address or vice versa.  In either case we have to think
   // of the overall transaction as being complete if a full address and data set has completed and at this point
   // the resp should be output..  If a write address transaction occurs and it is not for this dut then 
   // it is not only ignored but cancels any pending write_data transaction..

   // Implement axi_awready generation
   // do not allow a new address to be accepted if a current transaction is ongoing
   // if a write and read are active at the same time then prioritise the read (as per axi-ipif)
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         axi_awready                   <= 1'b0;
      end 
      else begin
         // 
         if ((~s_axi_arvalid) & (~read_in_progress)) begin
            if (~axi_awready && s_axi_awvalid && ~valid_waddr) begin
               axi_awready             <= 1'b1;
            end
            else begin
               axi_awready             <= 1'b0;
            end
         end
      end 
   end          

   // the address phase is valid until both the address and data are valid but 
   // they can become valid at any point
   // Note that on a timeout, read_in_progress should be low on a write, but arvalid
   // may now be high. Therefore we need to clear this flag on the timeout condition
   // which will cause axi_bvalid to be set
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         valid_waddr                   <= 1'b0;
      end 
      else begin
         if ((~s_axi_arvalid) & (~read_in_progress) | timeout) begin
            if ((s_axi_bready && axi_bvalid) | timeout) begin
               valid_waddr             <= 1'b0;
            end
            else 
        if (~axi_awready && s_axi_awvalid) begin
                valid_waddr          <= 1'b1;
                end
         end
      end 
   end          

   // Implement slv_addr latching
   // This process is used to latch the address early i.e when awvalid is asserted
   // should then hold until it is used (i.e valid_waddr is low)
   // do we need to consider the case where the read and write addresses are valid together?
   // probably should as there is nothing to stop this happening - in  that case hold off the write
   // to allow the read to continue
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         slv_addr                    <= {(BANK_DECODE_HIGH_LOW-2){1'b0}};
         slv_rd_addr                 <= 'd0;
      end 
      else begin    
         // only allow a write to take the address bus if no read is ongoing
         if (~valid_waddr) begin
            if (s_axi_arvalid & (~read_in_progress)) begin
               // Read address latching
               slv_addr                <= s_axi_araddr[BANK_DECODE_HIGH_LOW-1:2];
               slv_rd_addr             <= s_axi_araddr[BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW];
            end
            else if (~axi_awready && s_axi_awvalid) begin
               // write address latching 
               slv_addr                <= s_axi_awaddr[BANK_DECODE_HIGH_LOW-1:2];
               slv_rd_addr             <= s_axi_awaddr[BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW];
            end
         end
      end 
   end       

   // Implement axi_wready generation
   // axi_wready is asserted for one s_axi_aclk clock cycle when both
   // s_axi_awvalid and s_axi_wvalid are asserted. axi_wready is 
   // de-asserted when reset is low.  
   // may be acceptable to hold the data transaction until we see the address - avoids the need to 
   // flop the data
   
   assign adc0axi_map_selected = slv_rd_addr == ADC0BANK_SEL;

   always @( posedge s_axi_aclk )
     begin
        if (~s_axi_aresetn) begin
           adc0axi_map_wready                <= 1'b0;
        end 
        else begin    
           if (~s_axi_arvalid) begin
              if ((~adc0axi_map_wready) && s_axi_wvalid && valid_waddr  && adc0axi_map_selected) begin
                 adc0axi_map_wready          <= 1'b1;
              end
              else begin
                 adc0axi_map_wready          <= 1'b0;
              end
           end
        end 
     end

  
   assign adc1axi_map_selected = slv_rd_addr == ADC1BANK_SEL;

   always @( posedge s_axi_aclk )
     begin
        if (~s_axi_aresetn) begin
           adc1axi_map_wready                <= 1'b0;
        end 
        else begin    
           if (~s_axi_arvalid) begin
              if ((~adc1axi_map_wready) && s_axi_wvalid && valid_waddr  && adc1axi_map_selected) begin
                 adc1axi_map_wready          <= 1'b1;
              end
              else begin
                 adc1axi_map_wready          <= 1'b0;
              end
           end
        end 
     end

  
   assign adc2axi_map_selected = slv_rd_addr == ADC2BANK_SEL;

   always @( posedge s_axi_aclk )
     begin
        if (~s_axi_aresetn) begin
           adc2axi_map_wready                <= 1'b0;
        end 
        else begin    
           if (~s_axi_arvalid) begin
              if ((~adc2axi_map_wready) && s_axi_wvalid && valid_waddr  && adc2axi_map_selected) begin
                 adc2axi_map_wready          <= 1'b1;
              end
              else begin
                 adc2axi_map_wready          <= 1'b0;
              end
           end
        end 
     end

  
   assign adc3axi_map_selected = slv_rd_addr == ADC3BANK_SEL;

   always @( posedge s_axi_aclk )
     begin
        if (~s_axi_aresetn) begin
           adc3axi_map_wready                <= 1'b0;
        end 
        else begin    
           if (~s_axi_arvalid) begin
              if ((~adc3axi_map_wready) && s_axi_wvalid && valid_waddr  && adc3axi_map_selected) begin
                 adc3axi_map_wready          <= 1'b1;
              end
              else begin
                 adc3axi_map_wready          <= 1'b0;
              end
           end
        end 
     end

  
   assign cfg_axi_map_selected = slv_rd_addr == CFG_BANK_SEL;

   always @( posedge s_axi_aclk )
     begin
        if (~s_axi_aresetn) begin
           cfg_axi_map_wready                <= 1'b0;
        end 
        else begin    
           if (~s_axi_arvalid) begin
              if ((~cfg_axi_map_wready) && s_axi_wvalid && valid_waddr  && cfg_axi_map_selected) begin
                 cfg_axi_map_wready          <= 1'b1;
              end
              else begin
                 cfg_axi_map_wready          <= 1'b0;
              end
           end
        end 
     end

  
   // We have this signal to sweep up out of band memory writes
   reg axi_wr_access;
   always @( posedge s_axi_aclk )
     begin
        if (~s_axi_aresetn) begin
           axi_wr_access                <= 1'b0;
        end 
        else begin    
           if (~s_axi_arvalid) begin
              if ((~axi_wr_access) && s_axi_wvalid && valid_waddr) begin
                 axi_wr_access          <= 1'b1;
              end
              else begin
                 axi_wr_access          <= 1'b0;
              end
           end
        end 
     end
   
   // create an OR of all the mapped ready's so we can see if there was a write request 
   // to a bank that did not exist.
   assign or_all_mapped_wready = adc0axi_map_wready || adc1axi_map_wready || adc2axi_map_wready || adc3axi_map_wready || cfg_axi_map_wready;

   always @(*)
   begin
      if (axi_wr_access) begin
         axi_wready                    = 1'b1;
      end
      else begin
         axi_wready                    = 1'b0;
      end
   end

   // Implement memory mapped register select and write logic generation
   // The write data is accepted and written to memory mapped registers when
   // axi_awready, s_axi_wvalid, axi_wready and s_axi_wvalid are asserted. Write strobes are used to
   // select byte enables of slave registers while writing.
   // These registers are cleared when reset (active low) is applied.
   // Slave register write enable is asserted when valid address and data are available
   // and the slave is ready to accept the write address and write data.
   assign adc0slv_wren                   = adc0axi_map_wready             && s_axi_wvalid;
   assign adc1slv_wren                   = adc1axi_map_wready             && s_axi_wvalid;
   assign adc2slv_wren                   = adc2axi_map_wready             && s_axi_wvalid;
   assign adc3slv_wren                   = adc3axi_map_wready             && s_axi_wvalid;
   assign cfg_slv_wren                   = cfg_axi_map_wready             && s_axi_wvalid;
   
   // Implement write response logic generation
   // The write response and response valid signals are asserted by the slave 
   // when axi_wready, s_axi_wvalid, axi_wready and s_axi_wvalid are asserted.  
   // This marks the acceptance of address and indicates the status of 
   // write transaction. 
   wire bank_write_done;
   
   // If or_all_mapped_wready it indicates an invalid address was written to. We complete as it does
   // no harm, however, possible report a bad address
   assign bank_write_done = adc0slv_wr_done | adc1slv_wr_done | adc2slv_wr_done | adc3slv_wr_done | cfg_slv_wr_done;

   always @( posedge s_axi_aclk ) begin
      if (~s_axi_aresetn) begin
         axi_bvalid                    <= 1'b0;
         axi_bresp                     <= 2'b0;
         end 
      else begin    
         // The timeout is gated with s_axi_bready to ensure its only set when there is a valid write
         // The timeout is shared by the read and write logic and 
         if ((timeout & write_in_progress) | (~axi_bvalid && bank_write_done) | (axi_wr_access & ((or_all_mapped_wready == 'd0))) ) begin
            axi_bvalid                 <= 1'b1;
            if (~timeout) begin
              axi_bresp                  <= 2'b00; // 'OKAY' response
              end
            else begin
              axi_bresp                  <= 2'b10; // 'SLVERR' response
              end
           end // work error responses in future
         else begin
            //check if bready is asserted while bvalid is high) 
            //(there is a possibility that bready is always asserted high)   
            if (s_axi_bready && axi_bvalid) begin
               axi_bresp               <= 2'b00;
               axi_bvalid              <= 1'b0; 
               end  
            end
         end
      end   

//---------------------------------------------------------------------------         
//---------------------------------------------------------------------------         
// READ LOGIC
//---------------------------------------------------------------------------         
//---------------------------------------------------------------------------         
   // Due the potential transaction stretching capabilites of the banks, 
   // we need to keep a track of an ongoing read transaction to prevent
   // writes starting and detecting a valid end condition. The master can
   // wait for rvalid before it asserts rready so we can not rely on an
   // external indicator
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         read_in_progress                   <= 1'b0;
      end 
      else begin    
         if ( (s_axi_rready && s_axi_rvalid) | 
               timeout
             ) begin
           // End of a valid read phase, i.e. the complete axi transaction
           // Note this may have been triggered by a timeout
           read_in_progress                <= 1'b0;
         end
         else begin
           if (axi_arready && s_axi_arvalid) begin
             // indicates that the slave has acceped the valid read address
             read_in_progress              <= 1'b1;
           end
         end
      end 
   end       

   // Implement axi_arready generation
   // axi_arready is asserted for one s_axi_aclk clock cycle when
   // s_axi_arvalid is asserted. axi_arready is 
   // de-asserted when reset (active low) is asserted. 
   // The read address is also latched when s_axi_arvalid is 
   // asserted. slv_addr is reset to zero on reset assertion.
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         axi_arready                   <= 1'b0;
      end 
      else begin    
         // if a read and write happen at the same time then prioritise the read
         // s_axi_arvalid must be low for write_in_progress to be set, so it cannot
         // go high this cycle as s_axi_arvalid is high
         if ((~axi_arready && s_axi_arvalid) & (~read_in_progress) & (~write_in_progress)) begin
            // indicates that the slave has acceped the valid read address
            axi_arready                <= 1'b1;
         end
         else begin
            axi_arready                <= 1'b0;
         end
      end 
   end       

   // Implement axi_arvalid generation
   // axi_rvalid is asserted for one s_axi_aclk clock cycle when both 
   // s_axi_arvalid and axi_arready are asserted. The slave registers 
   // data are available on the axi_rdata bus at this instance. The 
   // assertion of axi_rvalid marks the validity of read data on the 
   // bus and axi_rresp indicates the status of read transaction.axi_rvalid 
   // is deasserted on reset (active low). axi_rresp and axi_rdata are 
   // cleared to zero on reset (active low).  
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         axi_rvalid                    <= 1'b0;
         axi_rresp                     <= 2'b0;
      end 
      else begin
         // timeout should not be gated with (s_axi_rready) this is illegal in the spec!
         // It is gated with read_in_progress so as not to pulse rvalid on a write timeout.
         // read_in_progress is also reset by the timeout
         //
         // slv_reg_done is a muxed version of read done from the bank. This can simply
         // reflect the input read read request <...>_slv_rden (a register below) or be
         // a pulse that should happen at some point in the future to indicate the 
         // transaction is complete. The returning read_done signals are muxed into slv_reg_done
         //
         // Best case this this a registered signal set when (axi_arready && s_axi_arvalid && ~axi_rvalid)
         // A AXI slave is not allowed to raise rvalid until both arready & arvalid are set (A3.3.1)
         //
         // Worst case this is a DRP access that does not complete and the timout is used to complete
         // the AXI tranaction
         //
         if ((timeout & read_in_progress & (~axi_rvalid) ) | 
             (slv_reg_done & (~axi_rvalid) & read_in_progress)
       ) begin
            // Valid read data is available at the read data bus
            axi_rvalid                 <= 1'b1;
            if (~timeout) begin
              axi_rresp                  <= 2'b00; // 'OKAY' response
              end
            else begin
              axi_rresp                  <= 2'b10; // 'SLVERR' response
              end
         end   
         else if (axi_rvalid && s_axi_rready) begin
            // Read data is accepted by the master, we are done
            axi_rvalid <= 1'b0;
         end                
      end
   end    

   // Implement memory mapped register select and read logic generation
   // Slave register read enable is asserted when valid address is available
   // and the slave is ready to accept the read address.
   // bits [UPPER:LOWER] of the address bus are sampled to ensure that if a 
   // write access starts during the read that the correct data is returned
   always @( posedge s_axi_aclk ) begin
     if (~s_axi_aresetn) begin
       slv_reg_rden  <= 'b0;
       adc0slv_rden                   <= 'd0;
       adc1slv_rden                   <= 'd0;
       adc2slv_rden                   <= 'd0;
       adc3slv_rden                   <= 'd0;
       cfg_slv_rden                   <= 'd0;
       end
     else begin
       if (axi_arready && s_axi_arvalid && ~axi_rvalid) begin
          slv_reg_rden  <= 1'b1;
          adc0slv_rden                   <= s_axi_araddr[BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW] == 'd1;
          adc1slv_rden                   <= s_axi_araddr[BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW] == 'd2;
          adc2slv_rden                   <= s_axi_araddr[BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW] == 'd3;
          adc3slv_rden                   <= s_axi_araddr[BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW] == 'd4;
          cfg_slv_rden                   <= s_axi_araddr[BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW] == 'd0;
          end
       else begin
         if (slv_reg_done) begin
           slv_reg_rden   <= 1'b0;
           adc0slv_rden                   <= 'd0;
           adc1slv_rden                   <= 'd0;
           adc2slv_rden                   <= 'd0;
           adc3slv_rden                   <= 'd0;
           cfg_slv_rden                   <= 'd0;
           end
         else begin
           slv_reg_rden   <= slv_reg_rden;
           adc0slv_rden                   <= adc0slv_rden;
           adc1slv_rden                   <= adc1slv_rden;
           adc2slv_rden                   <= adc2slv_rden;
           adc3slv_rden                   <= adc3slv_rden;
           cfg_slv_rden                   <= cfg_slv_rden;
           end
       end
     end
   end
      
   // Output register or memory read data
   always @( posedge s_axi_aclk )
   begin
      if (~s_axi_aresetn) begin
         axi_rdata                     <= 32'd0;
      end 
      else begin    
         // When there is a valid read address (s_axi_arvalid) with 
         // acceptance of read address by the slave (axi_arready), output the read data 
         if (slv_reg_rden) begin
            case (slv_rd_addr)
            ADC0BANK_SEL         : axi_rdata <= adc0slv_rdata;
            ADC1BANK_SEL         : axi_rdata <= adc1slv_rdata;
            ADC2BANK_SEL         : axi_rdata <= adc2slv_rdata;
            ADC3BANK_SEL         : axi_rdata <= adc3slv_rdata;
            CFG_BANK_SEL         : axi_rdata <= cfg_slv_rdata;
            default              : axi_rdata <= 'd0;
            endcase
         end   
      end
   end
   
   // Mux the correct read done flag onto the set, all values in should be from registers
   always @(*)
     begin
     case (slv_rd_addr)
     ADC0BANK_SEL         : slv_reg_done = adc0slv_rd_done;
     ADC1BANK_SEL         : slv_reg_done = adc1slv_rd_done;
     ADC2BANK_SEL         : slv_reg_done = adc2slv_rd_done;
     ADC3BANK_SEL         : slv_reg_done = adc3slv_rd_done;
     CFG_BANK_SEL         : slv_reg_done = cfg_slv_rd_done;
     default              : slv_reg_done = 'd1; // Must be 1 so all reads to invalid addres's complete
     endcase 
     end
     
//---------------------------------------------------------------------------         
//---------------------------------------------------------------------------         
// TIMEOUT LOGIC
//---------------------------------------------------------------------------         
//---------------------------------------------------------------------------         

  assign load_timeout_timer   = (s_axi_awvalid & s_axi_awready)   |
                                (s_axi_wvalid  & s_axi_wready)    |
                                (s_axi_arvalid & s_axi_arready);
                      
  assign clear_timeout_timer  = (s_axi_bvalid & s_axi_bready)     |
                                (s_axi_rvalid & s_axi_rready);
                                
  assign timeout              = timeout_timer_count[C_S_TIMEOUT_WIDTH];
  
  always @( posedge s_axi_aclk ) begin
    if (~s_axi_aresetn) begin
      timeout_timer_count <= 'd0;
      end
    else begin
      // clear the timeout at the end of AXI transactions or a timeout event 
      if (clear_timeout_timer | timeout) begin
        timeout_timer_count <= 'd0;
      end
      else begin
      // load the timer at the start of a RW access and only if the timeout is enabled
      if(load_timeout_timer & timeout_enable_in) begin
        timeout_timer_count <= {1'b0,(~timeout_value_in)};
        end
      else begin
        // if the timeout counter is greater than 0 and enabled we count
        if ((timeout_timer_count != 'd0 ) & timeout_enable_in) begin
          timeout_timer_count <= timeout_timer_count + 'd1;
          end
        end
      end
    end 
  end
     
endmodule
//-----------------------------------------------------------------------------
// Title      : demo_tb_hsadc_ctrl_handshake
// Project    : NA
//-----------------------------------------------------------------------------
// File       : demo_tb_hsadc_ctrl_handshake.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

//-----------------------------------------------------------------------------
// Pulse handshake
//-----------------------------------------------------------------------------
module demo_tb_hsadc_ctrl_hshk_pls_gen (
  input       clk1,
  input       clk1_rst,
  
  input       clk1_valid,
  output      clk1_ready,
  output reg  clk1_ready_pulse,
 
  input       clk2,
  input       clk2_rst,
  
  output      clk2_valid,
  output reg  clk2_valid_pulse,
  input       clk2_ready_pulse
   
 );
 
//-----------------------------------------------------------------------------
// internal registers
//-----------------------------------------------------------------------------
reg clk2_valid_sync_r;
reg clk1_ready_sync_r;
reg clk2_ready;
       
//-----------------------------------------------------------------------------
// sync the valid signal. This should be held high by the clk1 domain until
// ready is seen back in the clk1 domain, when the transaction is complete
//-----------------------------------------------------------------------------
demo_tb_hsadc_ctrl_sync axi_2_drp_valid_i (
  .clk      (clk2),
  .data_in  (clk1_valid),
  .data_out (clk2_valid) 
);
  
//-----------------------------------------------------------------------------
// Generate a vali pulse in clk2 domain when a rising edge is seen on valid
// When the returning ready pulse is seen the ready flag is raised and then
// passed to the clk1 domain. This signal is cleared when the valid signal
// goes low. It is the responsability of the clk 1 domain to clear this signal
//-----------------------------------------------------------------------------
always @(posedge clk2) begin
  if (~clk2_rst) begin
    clk2_valid_sync_r <= 1'd0;
    clk2_ready        <= 1'd0;
    clk2_valid_pulse  <= 1'd0;
    end
  else begin
    // register the sync output to create an pulse
    clk2_valid_sync_r <= clk2_valid;
    
    // create a pulse on a rising edge across the clock domain
    clk2_valid_pulse <= (~clk2_valid_sync_r) & clk2_valid;
    
    // Generate the ready signal, based on the incoming pulse
    if (clk2_ready_pulse) begin
      clk2_ready <= 1'd1;
      end
    else begin
      if(~clk2_valid) begin
        clk2_ready <= 1'd0;
        end
      end
    end
  end
 
//-----------------------------------------------------------------------------
// pass the ready signal between the two clock domains
//-----------------------------------------------------------------------------
demo_tb_hsadc_ctrl_sync drp_2_axi_in_progress_i (
  .clk      (clk1),
  .data_in  (clk2_ready),
  .data_out (clk1_ready) 
);
 
//-----------------------------------------------------------------------------
// Generate a pulse on the falling edge of ready. 
//-----------------------------------------------------------------------------
always @(posedge clk1) begin
  if (~clk1_rst) begin
    clk1_ready_pulse  <= 1'd0;
    clk1_ready_sync_r <= 1'd0;
    end
  else begin
    // register the sync output to create an pulse
    clk1_ready_sync_r <= clk1_ready;
    
    // create a pulse on a FALLING edge across the clock domain
    // This is going to be really slow, but for a slow clk2, we need to ensure
    // we dont start another access before its done!
    clk1_ready_pulse <= (~clk1_ready) & (clk1_ready_sync_r);
    end
  end
 
endmodule

//-----------------------------------------------------------------------------
// Title      : demo_tb_hsadc_ctrl_sync
// Project    : NA
//-----------------------------------------------------------------------------
// File       : demo_tb_hsadc_ctrl_sync.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

//-----------------------------------------------------------------------------
// 5 flop Syncroniser
//-----------------------------------------------------------------------------
//(* dont_touch = "yes" *)
module demo_tb_hsadc_ctrl_sync #(
  parameter INITIALISE = 1'b0
)
(
  input        clk,              // clock to be sync'ed to
  input        data_in,          // Data to be 'synced'
  output       data_out          // synced data
);

`ifdef USE_XPM_CDC
  // Use the new Xilinx CDC libraries. 
  xpm_cdc_single #(
  .DEST_SYNC_FF  (5), // Number of registers in the destination clock domain to account for MTBF
  .SRC_INPUT_REG (0)  // Determines whether there is an input register in src_clk domain.  
                      // SRC_INPUT_REG = 0, input register is not present
  ) cdc_i  (
  .src_clk  (1'b0     ),  
  .dest_clk (clk      ),  
  .src_in   (data_in  ),
  .dest_out (data_out )
  );

`else
  // Internal Signals
  wire   data_sync0;
  wire   data_sync1;
  wire   data_sync2;
  wire   data_sync3;
  wire   data_sync4;


  (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *)
  FD #(
    .INIT (INITIALISE[0])
  ) data_sync_reg0 (
    .C  (clk),
    .D  (data_in),
    .Q  (data_sync0)
  );

  (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *)
  FD #(
   .INIT (INITIALISE[0])
  ) data_sync_reg1 (
  .C  (clk),
  .D  (data_sync0),
  .Q  (data_sync1)
  );

  (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *)
  FD #(
   .INIT (INITIALISE[0])
  ) data_sync_reg2 (
  .C  (clk),
  .D  (data_sync1),
  .Q  (data_sync2)
  );

  (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *)
  FD #(
   .INIT (INITIALISE[0])
  ) data_sync_reg3 (
  .C  (clk),
  .D  (data_sync2),
  .Q  (data_sync3)
  );

  (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *)
  FD #(
   .INIT (INITIALISE[0])
  ) data_sync_reg4 (
  .C  (clk),
  .D  (data_sync3),
  .Q  (data_sync4)
  );
  
  assign data_out = data_sync4;
`endif

endmodule

//-----------------------------------------------------------------------------
// Title      : demo_tb_hsadc_ctrl
// Project    : NA
//-----------------------------------------------------------------------------
// File       : demo_tb_hsadc_ctrl.v
// Author     : Xilinx Inc.
//-----------------------------------------------------------------------------
// (c) Copyright 2016 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE 'AS IS' AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, 'Critical
// Applications'). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//-----------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module demo_tb_hsadc_ctrl #(
 parameter integer  C_S_AXI_ADDR_WIDTH             = 18,
 parameter integer  BANK_DECODE_HIGH_BIT           = 17,
 parameter integer  BANK_DECODE_HIGH_LOW           = 12,
 parameter integer  C_S_TIMEOUT_WIDTH              = 12
) (
 
//-----------------------------------------------------------------------------
// Signal declarations for BANK adc_demo_tb_cfg
//-----------------------------------------------------------------------------
   output                                 enable,

 
//-----------------------------------------------------------------------------
// Signal declarations for BANK adc0_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc00_if_0 enable" *)
   output      [7:0]                      adc00_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc00_if_0 dg_inc_i" *)
   output      [11:0]                     adc00_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc00_if_0 dg_type" *)
   output      [2:0]                      adc00_dg_type_0,
   output      [31:0]                     adc00_scaling_factor_0,
   output      [31:0]                     adc00_offset_0,
   output      [15:0]                     adc00_phase_high_0,
   output      [15:0]                     adc00_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc01_if_0 enable" *)
   output      [7:0]                      adc01_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc01_if_0 dg_inc_i" *)
   output      [11:0]                     adc01_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc01_if_0 dg_type" *)
   output      [2:0]                      adc01_dg_type_0,
   output      [31:0]                     adc01_scaling_factor_0,
   output      [31:0]                     adc01_offset_0,
   output      [15:0]                     adc01_phase_high_0,
   output      [15:0]                     adc01_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc02_if_0 enable" *)
   output      [7:0]                      adc02_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc02_if_0 dg_inc_i" *)
   output      [11:0]                     adc02_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc02_if_0 dg_type" *)
   output      [2:0]                      adc02_dg_type_0,
   output      [31:0]                     adc02_scaling_factor_0,
   output      [31:0]                     adc02_offset_0,
   output      [15:0]                     adc02_phase_high_0,
   output      [15:0]                     adc02_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc03_if_0 enable" *)
   output      [7:0]                      adc03_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc03_if_0 dg_inc_i" *)
   output      [11:0]                     adc03_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc03_if_0 dg_type" *)
   output      [2:0]                      adc03_dg_type_0,
   output      [31:0]                     adc03_scaling_factor_0,
   output      [31:0]                     adc03_offset_0,
   output      [15:0]                     adc03_phase_high_0,
   output      [15:0]                     adc03_phase_low_0,

//-----------------------------------------------------------------------------
// Signal declarations for BANK adc1_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc10_if_0 enable" *)
   output      [7:0]                      adc10_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc10_if_0 dg_inc_i" *)
   output      [11:0]                     adc10_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc10_if_0 dg_type" *)
   output      [2:0]                      adc10_dg_type_0,
   output      [31:0]                     adc10_scaling_factor_0,
   output      [31:0]                     adc10_offset_0,
   output      [15:0]                     adc10_phase_high_0,
   output      [15:0]                     adc10_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc11_if_0 enable" *)
   output      [7:0]                      adc11_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc11_if_0 dg_inc_i" *)
   output      [11:0]                     adc11_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc11_if_0 dg_type" *)
   output      [2:0]                      adc11_dg_type_0,
   output      [31:0]                     adc11_scaling_factor_0,
   output      [31:0]                     adc11_offset_0,
   output      [15:0]                     adc11_phase_high_0,
   output      [15:0]                     adc11_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc12_if_0 enable" *)
   output      [7:0]                      adc12_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc12_if_0 dg_inc_i" *)
   output      [11:0]                     adc12_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc12_if_0 dg_type" *)
   output      [2:0]                      adc12_dg_type_0,
   output      [31:0]                     adc12_scaling_factor_0,
   output      [31:0]                     adc12_offset_0,
   output      [15:0]                     adc12_phase_high_0,
   output      [15:0]                     adc12_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc13_if_0 enable" *)
   output      [7:0]                      adc13_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc13_if_0 dg_inc_i" *)
   output      [11:0]                     adc13_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc13_if_0 dg_type" *)
   output      [2:0]                      adc13_dg_type_0,
   output      [31:0]                     adc13_scaling_factor_0,
   output      [31:0]                     adc13_offset_0,
   output      [15:0]                     adc13_phase_high_0,
   output      [15:0]                     adc13_phase_low_0,

//-----------------------------------------------------------------------------
// Signal declarations for BANK adc2_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc20_if_0 enable" *)
   output      [7:0]                      adc20_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc20_if_0 dg_inc_i" *)
   output      [11:0]                     adc20_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc20_if_0 dg_type" *)
   output      [2:0]                      adc20_dg_type_0,
   output      [31:0]                     adc20_scaling_factor_0,
   output      [31:0]                     adc20_offset_0,
   output      [15:0]                     adc20_phase_high_0,
   output      [15:0]                     adc20_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc21_if_0 enable" *)
   output      [7:0]                      adc21_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc21_if_0 dg_inc_i" *)
   output      [11:0]                     adc21_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc21_if_0 dg_type" *)
   output      [2:0]                      adc21_dg_type_0,
   output      [31:0]                     adc21_scaling_factor_0,
   output      [31:0]                     adc21_offset_0,
   output      [15:0]                     adc21_phase_high_0,
   output      [15:0]                     adc21_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc22_if_0 enable" *)
   output      [7:0]                      adc22_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc22_if_0 dg_inc_i" *)
   output      [11:0]                     adc22_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc22_if_0 dg_type" *)
   output      [2:0]                      adc22_dg_type_0,
   output      [31:0]                     adc22_scaling_factor_0,
   output      [31:0]                     adc22_offset_0,
   output      [15:0]                     adc22_phase_high_0,
   output      [15:0]                     adc22_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc23_if_0 enable" *)
   output      [7:0]                      adc23_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc23_if_0 dg_inc_i" *)
   output      [11:0]                     adc23_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc23_if_0 dg_type" *)
   output      [2:0]                      adc23_dg_type_0,
   output      [31:0]                     adc23_scaling_factor_0,
   output      [31:0]                     adc23_offset_0,
   output      [15:0]                     adc23_phase_high_0,
   output      [15:0]                     adc23_phase_low_0,

//-----------------------------------------------------------------------------
// Signal declarations for BANK adc3_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc30_if_0 enable" *)
   output      [7:0]                      adc30_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc30_if_0 dg_inc_i" *)
   output      [11:0]                     adc30_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc30_if_0 dg_type" *)
   output      [2:0]                      adc30_dg_type_0,
   output      [31:0]                     adc30_scaling_factor_0,
   output      [31:0]                     adc30_offset_0,
   output      [15:0]                     adc30_phase_high_0,
   output      [15:0]                     adc30_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc31_if_0 enable" *)
   output      [7:0]                      adc31_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc31_if_0 dg_inc_i" *)
   output      [11:0]                     adc31_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc31_if_0 dg_type" *)
   output      [2:0]                      adc31_dg_type_0,
   output      [31:0]                     adc31_scaling_factor_0,
   output      [31:0]                     adc31_offset_0,
   output      [15:0]                     adc31_phase_high_0,
   output      [15:0]                     adc31_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc32_if_0 enable" *)
   output      [7:0]                      adc32_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc32_if_0 dg_inc_i" *)
   output      [11:0]                     adc32_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc32_if_0 dg_type" *)
   output      [2:0]                      adc32_dg_type_0,
   output      [31:0]                     adc32_scaling_factor_0,
   output      [31:0]                     adc32_offset_0,
   output      [15:0]                     adc32_phase_high_0,
   output      [15:0]                     adc32_phase_low_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc33_if_0 enable" *)
   output      [7:0]                      adc33_enable_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc33_if_0 dg_inc_i" *)
   output      [11:0]                     adc33_dg_inc_0,
(* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 adc33_if_0 dg_type" *)
   output      [2:0]                      adc33_dg_type_0,
   output      [31:0]                     adc33_scaling_factor_0,
   output      [31:0]                     adc33_offset_0,
   output      [15:0]                     adc33_phase_high_0,
   output      [15:0]                     adc33_phase_low_0,


//-----------------------------------------------------------------------------
// Other clock domain IO
//-----------------------------------------------------------------------------
// Secondary clock domain adc_fab_clk0
   input                                  adc_fab_clk0,
   input                                  adc_fab_reset0,

// Secondary clock domain adc_fab_clk1
   input                                  adc_fab_clk1,
   input                                  adc_fab_reset1,

// Secondary clock domain adc_fab_clk2
   input                                  adc_fab_clk2,
   input                                  adc_fab_reset2,

// Secondary clock domain adc_fab_clk3
   input                                  adc_fab_clk3,
   input                                  adc_fab_reset3,

//-----------------------------------------------------------------------------
// Time out connections in
//-----------------------------------------------------------------------------
   input                                  timeout_enable_in,
   input       [C_S_TIMEOUT_WIDTH-1:0]    timeout_value_in,

//-----------------------------------------------------------------------------
// AXI Lite IO
//-----------------------------------------------------------------------------
   input                                  s_axi_aclk,
   input                                  s_axi_aresetn,
   input       [C_S_AXI_ADDR_WIDTH-1:0]   s_axi_awaddr,
   input                                  s_axi_awvalid,
   output                                 s_axi_awready,
   input       [31:0]                     s_axi_wdata,
   input                                  s_axi_wvalid,
   output                                 s_axi_wready,
   output      [1:0]                      s_axi_bresp,
   output                                 s_axi_bvalid,
   input                                  s_axi_bready,
   input       [C_S_AXI_ADDR_WIDTH-1:0]   s_axi_araddr,
   input                                  s_axi_arvalid,
   output                                 s_axi_arready,
   output      [31:0]                     s_axi_rdata,
   output      [1:0]                      s_axi_rresp,
   output                                 s_axi_rvalid,
   input                                  s_axi_rready

);

//-----------------------------------------------------------------------------
// internal register strobe declarations
//-----------------------------------------------------------------------------
   wire        [BANK_DECODE_HIGH_LOW-1:2] slv_addr;
   wire        [31:0]                     slv_wdata;   
   wire                                   slv_reg_rden;

   wire        [31:0]                     adc0slv_rdata;
   wire                                   adc0slv_wren;
   wire                                   adc0slv_rden;
   wire                                   adc0slv_wr_done;
   wire                                   adc0slv_rd_done;
  
   wire        [31:0]                     adc1slv_rdata;
   wire                                   adc1slv_wren;
   wire                                   adc1slv_rden;
   wire                                   adc1slv_wr_done;
   wire                                   adc1slv_rd_done;
  
   wire        [31:0]                     adc2slv_rdata;
   wire                                   adc2slv_wren;
   wire                                   adc2slv_rden;
   wire                                   adc2slv_wr_done;
   wire                                   adc2slv_rd_done;
  
   wire        [31:0]                     adc3slv_rdata;
   wire                                   adc3slv_wren;
   wire                                   adc3slv_rden;
   wire                                   adc3slv_wr_done;
   wire                                   adc3slv_rd_done;
  
   wire        [31:0]                     cfg_slv_rdata;
   wire                                   cfg_slv_wren;
   wire                                   cfg_slv_rden;
   wire                                   cfg_slv_wr_done;
   wire                                   cfg_slv_rd_done;
  

//-----------------------------------------------------------------------------
// Signal bus wire declarations for BANK adc0_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Signal bus wire declarations for BANK adc1_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Signal bus wire declarations for BANK adc2_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Signal bus wire declarations for BANK adc3_demo_tb_hsadc_ctrl_axi
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Main AXI interface
//-----------------------------------------------------------------------------
demo_tb_hsadc_ctrl_axi #(
.C_S_AXI_ADDR_WIDTH           (C_S_AXI_ADDR_WIDTH),
.BANK_DECODE_HIGH_BIT         (BANK_DECODE_HIGH_BIT),
.BANK_DECODE_HIGH_LOW         (BANK_DECODE_HIGH_LOW),
.C_S_TIMEOUT_WIDTH            (C_S_TIMEOUT_WIDTH)
) axi_register_if_i (

  .slv_reg_rden                             (slv_reg_rden                            ),
  .slv_addr                                 (slv_addr                                ),
  .slv_wdata                                (slv_wdata                               ),

  .adc0slv_rdata                            (adc0slv_rdata                           ),
  .adc0slv_wren                             (adc0slv_wren                            ),
  .adc0slv_rden                             (adc0slv_rden                            ),
  .adc0slv_rd_done                          (adc0slv_rd_done                         ),
  .adc0slv_wr_done                          (adc0slv_wr_done                         ),

  .adc1slv_rdata                            (adc1slv_rdata                           ),
  .adc1slv_wren                             (adc1slv_wren                            ),
  .adc1slv_rden                             (adc1slv_rden                            ),
  .adc1slv_rd_done                          (adc1slv_rd_done                         ),
  .adc1slv_wr_done                          (adc1slv_wr_done                         ),

  .adc2slv_rdata                            (adc2slv_rdata                           ),
  .adc2slv_wren                             (adc2slv_wren                            ),
  .adc2slv_rden                             (adc2slv_rden                            ),
  .adc2slv_rd_done                          (adc2slv_rd_done                         ),
  .adc2slv_wr_done                          (adc2slv_wr_done                         ),

  .adc3slv_rdata                            (adc3slv_rdata                           ),
  .adc3slv_wren                             (adc3slv_wren                            ),
  .adc3slv_rden                             (adc3slv_rden                            ),
  .adc3slv_rd_done                          (adc3slv_rd_done                         ),
  .adc3slv_wr_done                          (adc3slv_wr_done                         ),

  .cfg_slv_rdata                            (cfg_slv_rdata                           ),
  .cfg_slv_wren                             (cfg_slv_wren                            ),
  .cfg_slv_rden                             (cfg_slv_rden                            ),
  .cfg_slv_rd_done                          (cfg_slv_rd_done                         ),
  .cfg_slv_wr_done                          (cfg_slv_wr_done                         ),

  .timeout_enable_in                        (timeout_enable_in                       ),
  .timeout_value_in                         (timeout_value_in                        ),
 
  .s_axi_aclk                               (s_axi_aclk                              ),
  .s_axi_aresetn                            (s_axi_aresetn                           ),

  .s_axi_awaddr                             (s_axi_awaddr                            ),
  .s_axi_awvalid                            (s_axi_awvalid                           ),
  .s_axi_awready                            (s_axi_awready                           ),

  .s_axi_wdata                              (s_axi_wdata                             ),
  .s_axi_wvalid                             (s_axi_wvalid                            ),
  .s_axi_wready                             (s_axi_wready                            ),

  .s_axi_bresp                              (s_axi_bresp                             ),
  .s_axi_bvalid                             (s_axi_bvalid                            ),
  .s_axi_bready                             (s_axi_bready                            ),

  .s_axi_araddr                             (s_axi_araddr                            ),
  .s_axi_arvalid                            (s_axi_arvalid                           ),
  .s_axi_arready                            (s_axi_arready                           ),

  .s_axi_rdata                              (s_axi_rdata                             ),
  .s_axi_rresp                              (s_axi_rresp                             ),
  .s_axi_rvalid                             (s_axi_rvalid                            ),
  .s_axi_rready                             (s_axi_rready                            )

);

//-----------------------------------------------------------------------------
// adc0_demo_tb_hsadc_ctrl_axi register bank, with replicated IO and internal select
//-----------------------------------------------------------------------------
adc0_demo_tb_hsadc_ctrl_axi #(
   .C_S_AXI_ADDR_WIDTH           (BANK_DECODE_HIGH_LOW)
) adc0_demo_tb_hsadc_ctrl_axi_i (


  .adc00_enable_0                           (adc00_enable_0                          ),
  .adc00_dg_inc_0                           (adc00_dg_inc_0                          ),
  .adc00_dg_type_0                          (adc00_dg_type_0                         ),
  .adc00_scaling_factor_0                   (adc00_scaling_factor_0                  ),
  .adc00_offset_0                           (adc00_offset_0                          ),
  .adc00_phase_high_0                       (adc00_phase_high_0                      ),
  .adc00_phase_low_0                        (adc00_phase_low_0                       ),
  .adc01_enable_0                           (adc01_enable_0                          ),
  .adc01_dg_inc_0                           (adc01_dg_inc_0                          ),
  .adc01_dg_type_0                          (adc01_dg_type_0                         ),
  .adc01_scaling_factor_0                   (adc01_scaling_factor_0                  ),
  .adc01_offset_0                           (adc01_offset_0                          ),
  .adc01_phase_high_0                       (adc01_phase_high_0                      ),
  .adc01_phase_low_0                        (adc01_phase_low_0                       ),
  .adc02_enable_0                           (adc02_enable_0                          ),
  .adc02_dg_inc_0                           (adc02_dg_inc_0                          ),
  .adc02_dg_type_0                          (adc02_dg_type_0                         ),
  .adc02_scaling_factor_0                   (adc02_scaling_factor_0                  ),
  .adc02_offset_0                           (adc02_offset_0                          ),
  .adc02_phase_high_0                       (adc02_phase_high_0                      ),
  .adc02_phase_low_0                        (adc02_phase_low_0                       ),
  .adc03_enable_0                           (adc03_enable_0                          ),
  .adc03_dg_inc_0                           (adc03_dg_inc_0                          ),
  .adc03_dg_type_0                          (adc03_dg_type_0                         ),
  .adc03_scaling_factor_0                   (adc03_scaling_factor_0                  ),
  .adc03_offset_0                           (adc03_offset_0                          ),
  .adc03_phase_high_0                       (adc03_phase_high_0                      ),
  .adc03_phase_low_0                        (adc03_phase_low_0                       ),

  .slv_addr                                 (slv_addr                                ),
  .slv_wdata                                (slv_wdata                               ),
  .slv_rden                                 (adc0slv_rden                            ),
  .slv_wren                                 (adc0slv_wren                            ),

  .slv_wr_done                              (adc0slv_wr_done                         ),
  .slv_rd_done                              (adc0slv_rd_done                         ),
  .slv_rdata                                (adc0slv_rdata                           ),

  .clk2_clk                                 (adc_fab_clk0                            ),
  .clk2_reset                               (adc_fab_reset0                          ),

  .s_axi_aclk                               (s_axi_aclk                              ),
  .s_axi_aresetn                            (s_axi_aresetn                           )

);
//-----------------------------------------------------------------------------
// adc1_demo_tb_hsadc_ctrl_axi register bank, with replicated IO and internal select
//-----------------------------------------------------------------------------
adc1_demo_tb_hsadc_ctrl_axi #(
   .C_S_AXI_ADDR_WIDTH           (BANK_DECODE_HIGH_LOW)
) adc1_demo_tb_hsadc_ctrl_axi_i (


  .adc10_enable_0                           (adc10_enable_0                          ),
  .adc10_dg_inc_0                           (adc10_dg_inc_0                          ),
  .adc10_dg_type_0                          (adc10_dg_type_0                         ),
  .adc10_scaling_factor_0                   (adc10_scaling_factor_0                  ),
  .adc10_offset_0                           (adc10_offset_0                          ),
  .adc10_phase_high_0                       (adc10_phase_high_0                      ),
  .adc10_phase_low_0                        (adc10_phase_low_0                       ),
  .adc11_enable_0                           (adc11_enable_0                          ),
  .adc11_dg_inc_0                           (adc11_dg_inc_0                          ),
  .adc11_dg_type_0                          (adc11_dg_type_0                         ),
  .adc11_scaling_factor_0                   (adc11_scaling_factor_0                  ),
  .adc11_offset_0                           (adc11_offset_0                          ),
  .adc11_phase_high_0                       (adc11_phase_high_0                      ),
  .adc11_phase_low_0                        (adc11_phase_low_0                       ),
  .adc12_enable_0                           (adc12_enable_0                          ),
  .adc12_dg_inc_0                           (adc12_dg_inc_0                          ),
  .adc12_dg_type_0                          (adc12_dg_type_0                         ),
  .adc12_scaling_factor_0                   (adc12_scaling_factor_0                  ),
  .adc12_offset_0                           (adc12_offset_0                          ),
  .adc12_phase_high_0                       (adc12_phase_high_0                      ),
  .adc12_phase_low_0                        (adc12_phase_low_0                       ),
  .adc13_enable_0                           (adc13_enable_0                          ),
  .adc13_dg_inc_0                           (adc13_dg_inc_0                          ),
  .adc13_dg_type_0                          (adc13_dg_type_0                         ),
  .adc13_scaling_factor_0                   (adc13_scaling_factor_0                  ),
  .adc13_offset_0                           (adc13_offset_0                          ),
  .adc13_phase_high_0                       (adc13_phase_high_0                      ),
  .adc13_phase_low_0                        (adc13_phase_low_0                       ),

  .slv_addr                                 (slv_addr                                ),
  .slv_wdata                                (slv_wdata                               ),
  .slv_rden                                 (adc1slv_rden                            ),
  .slv_wren                                 (adc1slv_wren                            ),

  .slv_wr_done                              (adc1slv_wr_done                         ),
  .slv_rd_done                              (adc1slv_rd_done                         ),
  .slv_rdata                                (adc1slv_rdata                           ),

  .clk2_clk                                 (adc_fab_clk1                            ),
  .clk2_reset                               (adc_fab_reset1                          ),

  .s_axi_aclk                               (s_axi_aclk                              ),
  .s_axi_aresetn                            (s_axi_aresetn                           )

);
//-----------------------------------------------------------------------------
// adc2_demo_tb_hsadc_ctrl_axi register bank, with replicated IO and internal select
//-----------------------------------------------------------------------------
adc2_demo_tb_hsadc_ctrl_axi #(
   .C_S_AXI_ADDR_WIDTH           (BANK_DECODE_HIGH_LOW)
) adc2_demo_tb_hsadc_ctrl_axi_i (


  .adc20_enable_0                           (adc20_enable_0                          ),
  .adc20_dg_inc_0                           (adc20_dg_inc_0                          ),
  .adc20_dg_type_0                          (adc20_dg_type_0                         ),
  .adc20_scaling_factor_0                   (adc20_scaling_factor_0                  ),
  .adc20_offset_0                           (adc20_offset_0                          ),
  .adc20_phase_high_0                       (adc20_phase_high_0                      ),
  .adc20_phase_low_0                        (adc20_phase_low_0                       ),
  .adc21_enable_0                           (adc21_enable_0                          ),
  .adc21_dg_inc_0                           (adc21_dg_inc_0                          ),
  .adc21_dg_type_0                          (adc21_dg_type_0                         ),
  .adc21_scaling_factor_0                   (adc21_scaling_factor_0                  ),
  .adc21_offset_0                           (adc21_offset_0                          ),
  .adc21_phase_high_0                       (adc21_phase_high_0                      ),
  .adc21_phase_low_0                        (adc21_phase_low_0                       ),
  .adc22_enable_0                           (adc22_enable_0                          ),
  .adc22_dg_inc_0                           (adc22_dg_inc_0                          ),
  .adc22_dg_type_0                          (adc22_dg_type_0                         ),
  .adc22_scaling_factor_0                   (adc22_scaling_factor_0                  ),
  .adc22_offset_0                           (adc22_offset_0                          ),
  .adc22_phase_high_0                       (adc22_phase_high_0                      ),
  .adc22_phase_low_0                        (adc22_phase_low_0                       ),
  .adc23_enable_0                           (adc23_enable_0                          ),
  .adc23_dg_inc_0                           (adc23_dg_inc_0                          ),
  .adc23_dg_type_0                          (adc23_dg_type_0                         ),
  .adc23_scaling_factor_0                   (adc23_scaling_factor_0                  ),
  .adc23_offset_0                           (adc23_offset_0                          ),
  .adc23_phase_high_0                       (adc23_phase_high_0                      ),
  .adc23_phase_low_0                        (adc23_phase_low_0                       ),

  .slv_addr                                 (slv_addr                                ),
  .slv_wdata                                (slv_wdata                               ),
  .slv_rden                                 (adc2slv_rden                            ),
  .slv_wren                                 (adc2slv_wren                            ),

  .slv_wr_done                              (adc2slv_wr_done                         ),
  .slv_rd_done                              (adc2slv_rd_done                         ),
  .slv_rdata                                (adc2slv_rdata                           ),

  .clk2_clk                                 (adc_fab_clk2                            ),
  .clk2_reset                               (adc_fab_reset2                          ),

  .s_axi_aclk                               (s_axi_aclk                              ),
  .s_axi_aresetn                            (s_axi_aresetn                           )

);
//-----------------------------------------------------------------------------
// adc3_demo_tb_hsadc_ctrl_axi register bank, with replicated IO and internal select
//-----------------------------------------------------------------------------
adc3_demo_tb_hsadc_ctrl_axi #(
   .C_S_AXI_ADDR_WIDTH           (BANK_DECODE_HIGH_LOW)
) adc3_demo_tb_hsadc_ctrl_axi_i (


  .adc30_enable_0                           (adc30_enable_0                          ),
  .adc30_dg_inc_0                           (adc30_dg_inc_0                          ),
  .adc30_dg_type_0                          (adc30_dg_type_0                         ),
  .adc30_scaling_factor_0                   (adc30_scaling_factor_0                  ),
  .adc30_offset_0                           (adc30_offset_0                          ),
  .adc30_phase_high_0                       (adc30_phase_high_0                      ),
  .adc30_phase_low_0                        (adc30_phase_low_0                       ),
  .adc31_enable_0                           (adc31_enable_0                          ),
  .adc31_dg_inc_0                           (adc31_dg_inc_0                          ),
  .adc31_dg_type_0                          (adc31_dg_type_0                         ),
  .adc31_scaling_factor_0                   (adc31_scaling_factor_0                  ),
  .adc31_offset_0                           (adc31_offset_0                          ),
  .adc31_phase_high_0                       (adc31_phase_high_0                      ),
  .adc31_phase_low_0                        (adc31_phase_low_0                       ),
  .adc32_enable_0                           (adc32_enable_0                          ),
  .adc32_dg_inc_0                           (adc32_dg_inc_0                          ),
  .adc32_dg_type_0                          (adc32_dg_type_0                         ),
  .adc32_scaling_factor_0                   (adc32_scaling_factor_0                  ),
  .adc32_offset_0                           (adc32_offset_0                          ),
  .adc32_phase_high_0                       (adc32_phase_high_0                      ),
  .adc32_phase_low_0                        (adc32_phase_low_0                       ),
  .adc33_enable_0                           (adc33_enable_0                          ),
  .adc33_dg_inc_0                           (adc33_dg_inc_0                          ),
  .adc33_dg_type_0                          (adc33_dg_type_0                         ),
  .adc33_scaling_factor_0                   (adc33_scaling_factor_0                  ),
  .adc33_offset_0                           (adc33_offset_0                          ),
  .adc33_phase_high_0                       (adc33_phase_high_0                      ),
  .adc33_phase_low_0                        (adc33_phase_low_0                       ),

  .slv_addr                                 (slv_addr                                ),
  .slv_wdata                                (slv_wdata                               ),
  .slv_rden                                 (adc3slv_rden                            ),
  .slv_wren                                 (adc3slv_wren                            ),

  .slv_wr_done                              (adc3slv_wr_done                         ),
  .slv_rd_done                              (adc3slv_rd_done                         ),
  .slv_rdata                                (adc3slv_rdata                           ),

  .clk2_clk                                 (adc_fab_clk3                            ),
  .clk2_reset                               (adc_fab_reset3                          ),

  .s_axi_aclk                               (s_axi_aclk                              ),
  .s_axi_aresetn                            (s_axi_aresetn                           )

);
//-----------------------------------------------------------------------------
// adc_demo_tb_cfg register bank
//-----------------------------------------------------------------------------
adc_demo_tb_cfg #(
   .C_S_AXI_ADDR_WIDTH           (BANK_DECODE_HIGH_LOW)
) adc_demo_tb_cfg_i (

  .enable                                   (enable                                  ),


  .slv_addr                                 (slv_addr                                ),
  .slv_wdata                                (slv_wdata                               ),
  .slv_rden                                 (cfg_slv_rden                            ),
  .slv_wren                                 (cfg_slv_wren                            ),

  .slv_wr_done                              (cfg_slv_wr_done                         ),
  .slv_rd_done                              (cfg_slv_rd_done                         ),
  .slv_rdata                                (cfg_slv_rdata                           ),

  .s_axi_aclk                               (s_axi_aclk                              ),
  .s_axi_aresetn                            (s_axi_aresetn                           )

);



endmodule

