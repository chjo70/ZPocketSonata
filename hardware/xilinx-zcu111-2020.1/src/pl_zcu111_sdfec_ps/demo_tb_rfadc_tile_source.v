// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
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
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES. 
`timescale 1ps / 1ps

//`define EXCLUDE_SINE_WAVE_LUTS

`define DGTYPE_TRGL     0
`define DGTYPE_RAMPUP   1
`define DGTYPE_RAMPDOWN 2
`define DGTYPE_SINE0    3
`define DGTYPE_SQR      6

// ----------------------------------------------------------------------------
// Non synthesiseable real data generator
// ----------------------------------------------------------------------------
module demo_tb_rfadc_tile_source #(
  parameter  p_useable_width     = 12,
  parameter  p_data_inc_val_init = 1,
  parameter  p_data_type_width   = 3
) (

  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_0 enable"    *) input  wire                         s0_enable            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_0 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s0_inc               , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_0 dg_type"   *) input  wire [p_data_type_width-1:0] s0_type              , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_0 dg_init"   *) input  wire   [p_useable_width-1:0] s0_init              , //
                                                                                    input  wire                  [31:0] s0_scaling_factor    , //
                                                                                    input  wire                  [31:0] s0_offset            , //
                                                                                    input  wire                  [31:0] s0_clk_phase_hl      , //
                                                                                    output wire                  [63:0] vout_0_p             , //
                                                                                    output wire                  [63:0] vout_0_n             , //

  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_1 enable"    *) input  wire                         s1_enable            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_1 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s1_inc               , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_1 dg_type"   *) input  wire [p_data_type_width-1:0] s1_type              , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_1 dg_init"   *) input  wire   [p_useable_width-1:0] s1_init              , //
                                                                                    input  wire                  [31:0] s1_scaling_factor    , //
                                                                                    input  wire                  [31:0] s1_offset            , //
                                                                                    input  wire                  [31:0] s1_clk_phase_hl      , //
                                                                                    output wire                  [63:0] vout_1_p             , //
                                                                                    output wire                  [63:0] vout_1_n             , //

  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_2 enable"    *) input  wire                         s2_enable            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_2 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s2_inc               , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_2 dg_type"   *) input  wire [p_data_type_width-1:0] s2_type              , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_2 dg_init"   *) input  wire   [p_useable_width-1:0] s2_init              , //
                                                                                    input  wire                  [31:0] s2_scaling_factor    , //
                                                                                    input  wire                  [31:0] s2_offset            , //
                                                                                    input  wire                  [31:0] s2_clk_phase_hl      , //
                                                                                    output wire                  [63:0] vout_2_p             , //
                                                                                    output wire                  [63:0] vout_2_n             , //

  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_3 enable"    *) input  wire                         s3_enable            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_3 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s3_inc               , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_3 dg_type"   *) input  wire [p_data_type_width-1:0] s3_type              , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 ds_tile_3 dg_init"   *) input  wire   [p_useable_width-1:0] s3_init              , //
                                                                                    input  wire                  [31:0] s3_scaling_factor    , //
                                                                                    input  wire                  [31:0] s3_offset            , //
                                                                                    input  wire                  [31:0] s3_clk_phase_hl      , //
                                                                                    output wire                  [63:0] vout_3_p             , //
                                                                                    output wire                  [63:0] vout_3_n             , //

  output wire           status  // 
  );

// ----------------------------------------------------------------------------
// Internal signals
// ----------------------------------------------------------------------------
wire s0_status;
wire s1_status;
wire s2_status;
wire s3_status;

// ----------------------------------------------------------------------------
// Status flag
// ----------------------------------------------------------------------------
assign status = s0_status|s1_status|s2_status|s3_status;

// ----------------------------------------------------------------------------
// Tile slices
// ----------------------------------------------------------------------------
      adc_src_slice #(
      .p_data_inc_val_init(p_data_inc_val_init),
      .p_data_type_width  (p_data_type_width  ),
      .p_useable_width    (p_useable_width    )
      ) ds_slice_0_1 (
         .vout_p         (vout_0_p              ),
         .vout_n         (vout_0_n              ),
         .clk_high       (s0_clk_phase_hl[31:16]),
         .clk_low        (s0_clk_phase_hl[15:0] ),
         .enable         (s0_enable             ),
         .inc            (s0_inc                ),
         .type           (s0_type               ),
         .init           (s0_init               ),
         .scaling_factor (s0_scaling_factor     ),
         .offset         (s0_offset             ),
         .status         (s0_status             )
      );
      adc_src_slice #(
      .p_data_inc_val_init(p_data_inc_val_init),
      .p_data_type_width  (p_data_type_width  ),
      .p_useable_width    (p_useable_width    )
      ) ds_slice_1_1 (
         .vout_p         (vout_1_p              ),
         .vout_n         (vout_1_n              ),
         .clk_high       (s1_clk_phase_hl[31:16]),
         .clk_low        (s1_clk_phase_hl[15:0] ),
         .enable         (s1_enable             ),
         .inc            (s1_inc                ),
         .type           (s1_type               ),
         .init           (s1_init               ),
         .scaling_factor (s1_scaling_factor     ),
         .offset         (s1_offset             ),
         .status         (s1_status             )
      );
      adc_src_slice #(
      .p_data_inc_val_init(p_data_inc_val_init),
      .p_data_type_width  (p_data_type_width  ),
      .p_useable_width    (p_useable_width    )
      ) ds_slice_2_1 (
         .vout_p         (vout_2_p              ),
         .vout_n         (vout_2_n              ),
         .clk_high       (s2_clk_phase_hl[31:16]),
         .clk_low        (s2_clk_phase_hl[15:0] ),
         .enable         (s2_enable             ),
         .inc            (s2_inc                ),
         .type           (s2_type               ),
         .init           (s2_init               ),
         .scaling_factor (s2_scaling_factor     ),
         .offset         (s2_offset             ),
         .status         (s2_status             )
      );
      adc_src_slice #(
      .p_data_inc_val_init(p_data_inc_val_init),
      .p_data_type_width  (p_data_type_width  ),
      .p_useable_width    (p_useable_width    )
      ) ds_slice_3_1 (
         .vout_p         (vout_3_p              ),
         .vout_n         (vout_3_n              ),
         .clk_high       (s3_clk_phase_hl[31:16]),
         .clk_low        (s3_clk_phase_hl[15:0] ),
         .enable         (s3_enable             ),
         .inc            (s3_inc                ),
         .type           (s3_type               ),
         .init           (s3_init               ),
         .scaling_factor (s3_scaling_factor     ),
         .offset         (s3_offset             ),
         .status         (s3_status             )
      );

endmodule

// ----------------------------------------------------------------------------
// Data sink slice block
// ----------------------------------------------------------------------------
module adc_src_slice #(
  parameter  p_useable_width     = 12,
  parameter  p_data_inc_val_init = 1,
  parameter  p_data_type_width   = 3
) (

  input  wire                   [15:0] clk_high       , //
  input  wire                   [15:0] clk_low        , //
  output wire                   [63:0] vout_p         , //
  output wire                   [63:0] vout_n         , //

  input  wire                          enable         , //
  input  wire    [p_useable_width-1:0] inc            , //
  input  wire  [p_data_type_width-1:0] type           , //
  input  wire    [p_useable_width-1:0] init           , //     
  input  wire                   [31:0] scaling_factor , // 
  input  wire                   [31:0] offset         , // 
  output wire                          status           //
  
  );

// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------
reg sample_clock=0;

// ----------------------------------------------------------------------------
// clock generation
// ----------------------------------------------------------------------------
always @(*)
   while((clk_high != 16'd0) & (clk_low != 16'd0)) begin
      sample_clock = 1;
      #(clk_high);
      sample_clock = 0;
      #(clk_low);
   end

  hsadc_data_source #(

   .p_data_inc_val_init(p_data_inc_val_init),
   .p_data_type_width  (p_data_type_width  ),
   .p_useable_width    (p_useable_width    )

  ) hsadc_data_source_i(

  .data_gen_type   ( type           ), // input   wire [3:0]  
  .data_gen_inc    ( inc            ), // input   wire [31:0] 
  .update_clk      ( sample_clock   ), // input   wire        
  .enable          ( enable         ), // input   wire        
  .scaling_factor  ( scaling_factor ), // input   wire [31:0] real to int scaling factor
  .offset          ( offset         ), // input   wire [31:0] real to int scaling factor
  .vout_p          ( vout_p         ), // output  wire [63:0] 
  .vout_n          ( vout_n         ), // output  wire [63:0] 

  .samp            (                )  // output  wire [15:0] 

  );

endmodule

// ----------------------------------------------------------------------------
// Generic data generator. Capable of ramps, sine and other waves.
// Programmable increment
// ----------------------------------------------------------------------------
//`define MAKE_RAMPS_POS_ONLY_IN_DEMO_TB
module hsadc_data_source #(
  parameter  p_useable_width     = 12,  //
  parameter  p_data_inc_val_init = 1,   //
  parameter  p_data_type_width   = 1    //
) (
 input   wire [p_data_type_width-1:0]   data_gen_type   , // 
 input   wire [p_useable_width-1:0]     data_gen_inc    , // 
 input   wire                           update_clk      , // 
 input   wire                           enable          , // 
 input   wire [31:0]                    scaling_factor  , // real to int scaling factor
 input   wire [31:0]                    offset          , // real to int scaling factor
 output  wire [63:0]                    vout_p          , // 
 output  wire [63:0]                    vout_n          , //

 output  wire [p_useable_width-1:0]     samp              // 

);

// -----------------------------------------------------------------------------
// Parameters for V full scale & common mode voltage
// -----------------------------------------------------------------------------
parameter VCM = 1.27;           // adjust to match fe/ch switch common mode attenuation
parameter FS = 1.12;            // p to p
parameter LSB = 0.0000732421;   // lsb size

parameter diff_range   = FS;                   // 
parameter bits         = 12;                   // Modelled Bits in use                
parameter in_scale_lsb = diff_range/(2**bits); // LSB                
parameter bit_width_d2 = (2**bits)/2;          // half bits range

// -----------------------------------------------------------------------------
// Variables
// -----------------------------------------------------------------------------
real           f64_VIN_N_scaled;          // 
real           f64_VIN_P_scaled;          // 
integer        sequence_counter;          // 
real           sequence_counter_asreal;   // 

// Convert out reals, keep this verbose for debug
always @(*) begin
   // Scale the value to an integer acceptable code range
   sequence_counter = samp;
`ifdef MAKE_RAMPS_POS_ONLY_IN_DEMO_TB
   sequence_counter_asreal = ((sequence_counter - 0)            * (in_scale_lsb/2));
`else
   // Scale to 90% of range as dither can cause ringing with a full range triangle wave
   // used in the demo_tb to verify basic function.
   sequence_counter_asreal = ((sequence_counter - bit_width_d2) * in_scale_lsb) * 0.9;
`endif
   f64_VIN_P_scaled = VCM + (sequence_counter_asreal/2);
   f64_VIN_N_scaled = VCM - (sequence_counter_asreal/2);
end

// Assign output
assign vout_p = $realtobits(f64_VIN_P_scaled);
assign vout_n = $realtobits(f64_VIN_N_scaled);

adc_gen_cell #(

   .p_data_inc_val_init(p_data_inc_val_init),
   .p_data_type_width  (p_data_type_width  ),
   .p_useable_width    (p_useable_width    )

  ) adc_gen_cell_i (

  .enable      (enable                 ), // 
  .clk         (update_clk             ), // 
  .dg_inc      (data_gen_inc           ), // 
  .dg_init     ({p_useable_width{1'd0}}), // 
  .dg_type     (data_gen_type          ), // 
  .dg_fast_i   (),
  .dg_fast_q   (),
  .dg_out      (samp                   )  // 
);

endmodule


// ----------------------------------------------------------------------------
// Generic data generator. Capable of ramps, sine and other waves.
// Programmable increment
// ----------------------------------------------------------------------------
module adc_gen_cell #(
  parameter  p_useable_width     = 12,             //
  parameter  p_data_inc_val_init = 1,              //
  parameter  p_data_type_width   = 1               //
) (

  input  wire                           enable   , // 
  input  wire                           clk      , // 
  input  wire     [p_useable_width-1:0] dg_inc   , // 
  input  wire     [p_useable_width-1:0] dg_init  , // 
  input  wire   [p_data_type_width-1:0] dg_type  , // 

  output reg      [p_useable_width-1:0] dg_out   , //
  output wire     [p_useable_width-1:0] dg_fast_i,  
  output wire     [p_useable_width-1:0] dg_fast_q
  
  );
  
// ----------------------------------------------------------------------------
// local params
// ----------------------------------------------------------------------------
localparam zero_stuff = 0; // 0 for the real number generators
  
// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------
reg  [p_useable_width-1:0] counter      = 0;    // 
reg  [p_useable_width-1:0] counter_fast = 0;    // 
reg                        updown       = 1'd1; // 
reg  [p_useable_width-1:0] dg_inc_int   = p_data_inc_val_init; // Reg for timing
wire [p_useable_width-1:0] next_count; // 
wire                       overflow;   // 
wire [p_useable_width-1:0] sine_value; // 
wire [p_useable_width:0]   inc_by;     // 
wire [p_useable_width:0]   inc_by_inv; // 

// ----------------------------------------------------------------------------
// Counter 
// ----------------------------------------------------------------------------
assign inc_by     =  {1'd0,{dg_inc_int[p_useable_width-1:0]}};
assign inc_by_inv = ~{1'd0,{dg_inc_int[p_useable_width-1:0]}} + {{p_useable_width{1'b0}}, 1'b1};
assign {overflow, next_count} = {1'd0,{counter}} + (updown?inc_by:inc_by_inv);

// ----------------------------------------------------------------------------
// RAMP generation
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   dg_inc_int <= dg_inc; // Data increment
   if(enable) begin
      updown <= updown;  // Default maintain value when enabled.

      // Counter load control. Assign sequence counter. May or may not change
      // the state of updown. 
      case (dg_type)
      `DGTYPE_TRGL     : case({updown,overflow})
                         2'b00 : begin counter <= next_count;              end
                         2'b01 : begin counter <= counter; updown <= 1'd1; end
                         2'b10 : begin counter <= next_count;              end
                         2'b11 : begin counter <= counter; updown <= 1'd0; end
                         endcase
      `DGTYPE_RAMPUP   : begin counter <= next_count; updown <= 1'd1;   end
      `DGTYPE_RAMPDOWN : begin counter <= next_count; updown <= 1'd0;   end
      `DGTYPE_SINE0    : begin counter <= next_count; updown <= 1'd1;   end
      `DGTYPE_SQR      : begin counter <= next_count; updown <= 1'd1;   end
      default          : counter <= 0;
      endcase 

      // Always increment, though only used to generate sine IQ LO
      counter_fast <= counter_fast + 'd16;

      // OUTPUT aselection control. SINE waves come from the LUT's with the
      // counter used to address the LUT
      // Zero stuff has been removed as there is no concept in an analog source
      case (dg_type)
      `DGTYPE_SINE0    : dg_out <= sine_value;
      `DGTYPE_SQR      : if (counter[p_useable_width-1] == 0) begin
                           dg_out <= {1'b0, {(p_useable_width-1){1'b0}}};  // max -ve ( = 0 )
                         end
                         else begin
                           dg_out <= {1'b1, {(p_useable_width-1){1'b1}}};  // max +ve ( = all 1's )
                         end
      default          : dg_out <= counter;
      endcase 
      
   end else begin
      // Default 
      counter_fast <= dg_init[p_useable_width-1:0];
      counter      <= dg_init[p_useable_width-1:0];
      dg_out       <= dg_init[p_useable_width-1:0];
      updown       <= 1'd1;
   end
end

// ----------------------------------------------------------------------------
// Instance the SINE wave LUT
// ----------------------------------------------------------------------------
`ifdef EXCLUDE_SINE_WAVE_LUTS
assign sine_value = 'd0;
`else
demo_tb_rfadc_sine_wave_lut sine0_lut (
   .sine_value     (sine_value       ), 
   .address        (counter[8:0]     ),
   .sine_value_i   (dg_fast_i        ),
   .sine_value_q   (dg_fast_q        ),
   .address_fast   (counter_fast[8:0])
);
`endif

endmodule

module demo_tb_rfadc_sine_wave_lut #(

   parameter bitwidth       = 12,
   parameter addresswidth   = 9

   ) (

   output wire [bitwidth-1:0]     sine_value   ,
   input  wire [addresswidth-1:0] address      ,
   output wire [bitwidth-1:0]     sine_value_i ,
   output wire [bitwidth-1:0]     sine_value_q ,
   input  wire [addresswidth-1:0] address_fast

);

// array
wire [11:0] sine_lut512_12bit[0:511];

// -----------------------------------------------------------------------------
// Sine wave LUT
// -----------------------------------------------------------------------------
// Freq=50.0MHz,  LUT Entries=512, Bitwidth=12, TwosComplement=0
assign sine_lut512_12bit[0] = 12'h819     ; // offset dec =   2073 signed = 25.119370
assign sine_lut512_12bit[1] = 12'h832     ; // offset dec =   2098 signed = 50.234961
assign sine_lut512_12bit[2] = 12'h84b     ; // offset dec =   2123 signed = 75.342995
assign sine_lut512_12bit[3] = 12'h864     ; // offset dec =   2148 signed = 100.439693
assign sine_lut512_12bit[4] = 12'h87d     ; // offset dec =   2173 signed = 125.521282
assign sine_lut512_12bit[5] = 12'h896     ; // offset dec =   2198 signed = 150.583986
assign sine_lut512_12bit[6] = 12'h8af     ; // offset dec =   2223 signed = 175.624036
assign sine_lut512_12bit[7] = 12'h8c8     ; // offset dec =   2248 signed = 200.637664
assign sine_lut512_12bit[8] = 12'h8e1     ; // offset dec =   2273 signed = 225.621108
assign sine_lut512_12bit[9] = 12'h8fa     ; // offset dec =   2298 signed = 250.570608
assign sine_lut512_12bit[10] = 12'h913     ; // offset dec =   2323 signed = 275.482412
assign sine_lut512_12bit[11] = 12'h92c     ; // offset dec =   2348 signed = 300.352771
assign sine_lut512_12bit[12] = 12'h945     ; // offset dec =   2373 signed = 325.177944
assign sine_lut512_12bit[13] = 12'h95d     ; // offset dec =   2397 signed = 349.954196
assign sine_lut512_12bit[14] = 12'h976     ; // offset dec =   2422 signed = 374.677799
assign sine_lut512_12bit[15] = 12'h98f     ; // offset dec =   2447 signed = 399.345035
assign sine_lut512_12bit[16] = 12'h9a7     ; // offset dec =   2471 signed = 423.952192
assign sine_lut512_12bit[17] = 12'h9c0     ; // offset dec =   2496 signed = 448.495567
assign sine_lut512_12bit[18] = 12'h9d8     ; // offset dec =   2520 signed = 472.971470
assign sine_lut512_12bit[19] = 12'h9f1     ; // offset dec =   2545 signed = 497.376217
assign sine_lut512_12bit[20] = 12'ha09     ; // offset dec =   2569 signed = 521.706137
assign sine_lut512_12bit[21] = 12'ha21     ; // offset dec =   2593 signed = 545.957569
assign sine_lut512_12bit[22] = 12'ha3a     ; // offset dec =   2618 signed = 570.126866
assign sine_lut512_12bit[23] = 12'ha52     ; // offset dec =   2642 signed = 594.210390
assign sine_lut512_12bit[24] = 12'ha6a     ; // offset dec =   2666 signed = 618.204519
assign sine_lut512_12bit[25] = 12'ha82     ; // offset dec =   2690 signed = 642.105644
assign sine_lut512_12bit[26] = 12'ha99     ; // offset dec =   2713 signed = 665.910168
assign sine_lut512_12bit[27] = 12'hab1     ; // offset dec =   2737 signed = 689.614509
assign sine_lut512_12bit[28] = 12'hac9     ; // offset dec =   2761 signed = 713.215103
assign sine_lut512_12bit[29] = 12'hae0     ; // offset dec =   2784 signed = 736.708398
assign sine_lut512_12bit[30] = 12'haf8     ; // offset dec =   2808 signed = 760.090860
assign sine_lut512_12bit[31] = 12'hb0f     ; // offset dec =   2831 signed = 783.358970
assign sine_lut512_12bit[32] = 12'hb26     ; // offset dec =   2854 signed = 806.509230
assign sine_lut512_12bit[33] = 12'hb3d     ; // offset dec =   2877 signed = 829.538155
assign sine_lut512_12bit[34] = 12'hb54     ; // offset dec =   2900 signed = 852.442282
assign sine_lut512_12bit[35] = 12'hb6b     ; // offset dec =   2923 signed = 875.218164
assign sine_lut512_12bit[36] = 12'hb81     ; // offset dec =   2945 signed = 897.862375
assign sine_lut512_12bit[37] = 12'hb98     ; // offset dec =   2968 signed = 920.371508
assign sine_lut512_12bit[38] = 12'hbae     ; // offset dec =   2990 signed = 942.742177
assign sine_lut512_12bit[39] = 12'hbc4     ; // offset dec =   3012 signed = 964.971017
assign sine_lut512_12bit[40] = 12'hbdb     ; // offset dec =   3035 signed = 987.054683
assign sine_lut512_12bit[41] = 12'hbf0     ; // offset dec =   3056 signed = 1008.989852
assign sine_lut512_12bit[42] = 12'hc06     ; // offset dec =   3078 signed = 1030.773226
assign sine_lut512_12bit[43] = 12'hc1c     ; // offset dec =   3100 signed = 1052.401526
assign sine_lut512_12bit[44] = 12'hc31     ; // offset dec =   3121 signed = 1073.871499
assign sine_lut512_12bit[45] = 12'hc47     ; // offset dec =   3143 signed = 1095.179915
assign sine_lut512_12bit[46] = 12'hc5c     ; // offset dec =   3164 signed = 1116.323568
assign sine_lut512_12bit[47] = 12'hc71     ; // offset dec =   3185 signed = 1137.299277
assign sine_lut512_12bit[48] = 12'hc86     ; // offset dec =   3206 signed = 1158.103887
assign sine_lut512_12bit[49] = 12'hc9a     ; // offset dec =   3226 signed = 1178.734267
assign sine_lut512_12bit[50] = 12'hcaf     ; // offset dec =   3247 signed = 1199.187314
assign sine_lut512_12bit[51] = 12'hcc3     ; // offset dec =   3267 signed = 1219.459952
assign sine_lut512_12bit[52] = 12'hcd7     ; // offset dec =   3287 signed = 1239.549129
assign sine_lut512_12bit[53] = 12'hceb     ; // offset dec =   3307 signed = 1259.451823
assign sine_lut512_12bit[54] = 12'hcff     ; // offset dec =   3327 signed = 1279.165041
assign sine_lut512_12bit[55] = 12'hd12     ; // offset dec =   3346 signed = 1298.685817
assign sine_lut512_12bit[56] = 12'hd26     ; // offset dec =   3366 signed = 1318.011214
assign sine_lut512_12bit[57] = 12'hd39     ; // offset dec =   3385 signed = 1337.138325
assign sine_lut512_12bit[58] = 12'hd4c     ; // offset dec =   3404 signed = 1356.064271
assign sine_lut512_12bit[59] = 12'hd5e     ; // offset dec =   3422 signed = 1374.786206
assign sine_lut512_12bit[60] = 12'hd71     ; // offset dec =   3441 signed = 1393.301313
assign sine_lut512_12bit[61] = 12'hd83     ; // offset dec =   3459 signed = 1411.606807
assign sine_lut512_12bit[62] = 12'hd95     ; // offset dec =   3477 signed = 1429.699934
assign sine_lut512_12bit[63] = 12'hda7     ; // offset dec =   3495 signed = 1447.577971
assign sine_lut512_12bit[64] = 12'hdb9     ; // offset dec =   3513 signed = 1465.238229
assign sine_lut512_12bit[65] = 12'hdca     ; // offset dec =   3530 signed = 1482.678052
assign sine_lut512_12bit[66] = 12'hddb     ; // offset dec =   3547 signed = 1499.894815
assign sine_lut512_12bit[67] = 12'hdec     ; // offset dec =   3564 signed = 1516.885928
assign sine_lut512_12bit[68] = 12'hdfd     ; // offset dec =   3581 signed = 1533.648835
assign sine_lut512_12bit[69] = 12'he0e     ; // offset dec =   3598 signed = 1550.181015
assign sine_lut512_12bit[70] = 12'he1e     ; // offset dec =   3614 signed = 1566.479980
assign sine_lut512_12bit[71] = 12'he2e     ; // offset dec =   3630 signed = 1582.543277
assign sine_lut512_12bit[72] = 12'he3e     ; // offset dec =   3646 signed = 1598.368491
assign sine_lut512_12bit[73] = 12'he4d     ; // offset dec =   3661 signed = 1613.953241
assign sine_lut512_12bit[74] = 12'he5d     ; // offset dec =   3677 signed = 1629.295182
assign sine_lut512_12bit[75] = 12'he6c     ; // offset dec =   3692 signed = 1644.392005
assign sine_lut512_12bit[76] = 12'he7b     ; // offset dec =   3707 signed = 1659.241440
assign sine_lut512_12bit[77] = 12'he89     ; // offset dec =   3721 signed = 1673.841253
assign sine_lut512_12bit[78] = 12'he98     ; // offset dec =   3736 signed = 1688.189247
assign sine_lut512_12bit[79] = 12'hea6     ; // offset dec =   3750 signed = 1702.283263
assign sine_lut512_12bit[80] = 12'heb4     ; // offset dec =   3764 signed = 1716.121182
assign sine_lut512_12bit[81] = 12'hec1     ; // offset dec =   3777 signed = 1729.700921
assign sine_lut512_12bit[82] = 12'hecf     ; // offset dec =   3791 signed = 1743.020438
assign sine_lut512_12bit[83] = 12'hedc     ; // offset dec =   3804 signed = 1756.077728
assign sine_lut512_12bit[84] = 12'hee8     ; // offset dec =   3816 signed = 1768.870828
assign sine_lut512_12bit[85] = 12'hef5     ; // offset dec =   3829 signed = 1781.397812
assign sine_lut512_12bit[86] = 12'hf01     ; // offset dec =   3841 signed = 1793.656796
assign sine_lut512_12bit[87] = 12'hf0d     ; // offset dec =   3853 signed = 1805.645935
assign sine_lut512_12bit[88] = 12'hf19     ; // offset dec =   3865 signed = 1817.363427
assign sine_lut512_12bit[89] = 12'hf24     ; // offset dec =   3876 signed = 1828.807508
assign sine_lut512_12bit[90] = 12'hf2f     ; // offset dec =   3887 signed = 1839.976456
assign sine_lut512_12bit[91] = 12'hf3a     ; // offset dec =   3898 signed = 1850.868592
assign sine_lut512_12bit[92] = 12'hf45     ; // offset dec =   3909 signed = 1861.482276
assign sine_lut512_12bit[93] = 12'hf4f     ; // offset dec =   3919 signed = 1871.815912
assign sine_lut512_12bit[94] = 12'hf59     ; // offset dec =   3929 signed = 1881.867945
assign sine_lut512_12bit[95] = 12'hf63     ; // offset dec =   3939 signed = 1891.636863
assign sine_lut512_12bit[96] = 12'hf6d     ; // offset dec =   3949 signed = 1901.121196
assign sine_lut512_12bit[97] = 12'hf76     ; // offset dec =   3958 signed = 1910.319517
assign sine_lut512_12bit[98] = 12'hf7f     ; // offset dec =   3967 signed = 1919.230443
assign sine_lut512_12bit[99] = 12'hf87     ; // offset dec =   3975 signed = 1927.852633
assign sine_lut512_12bit[100] = 12'hf90     ; // offset dec =   3984 signed = 1936.184790
assign sine_lut512_12bit[101] = 12'hf98     ; // offset dec =   3992 signed = 1944.225660
assign sine_lut512_12bit[102] = 12'hf9f     ; // offset dec =   3999 signed = 1951.974033
assign sine_lut512_12bit[103] = 12'hfa7     ; // offset dec =   4007 signed = 1959.428745
assign sine_lut512_12bit[104] = 12'hfae     ; // offset dec =   4014 signed = 1966.588672
assign sine_lut512_12bit[105] = 12'hfb5     ; // offset dec =   4021 signed = 1973.452739
assign sine_lut512_12bit[106] = 12'hfbc     ; // offset dec =   4028 signed = 1980.019913
assign sine_lut512_12bit[107] = 12'hfc2     ; // offset dec =   4034 signed = 1986.289205
assign sine_lut512_12bit[108] = 12'hfc8     ; // offset dec =   4040 signed = 1992.259672
assign sine_lut512_12bit[109] = 12'hfcd     ; // offset dec =   4045 signed = 1997.930416
assign sine_lut512_12bit[110] = 12'hfd3     ; // offset dec =   4051 signed = 2003.300585
assign sine_lut512_12bit[111] = 12'hfd8     ; // offset dec =   4056 signed = 2008.369369
assign sine_lut512_12bit[112] = 12'hfdd     ; // offset dec =   4061 signed = 2013.136007
assign sine_lut512_12bit[113] = 12'hfe1     ; // offset dec =   4065 signed = 2017.599782
assign sine_lut512_12bit[114] = 12'hfe5     ; // offset dec =   4069 signed = 2021.760021
assign sine_lut512_12bit[115] = 12'hfe9     ; // offset dec =   4073 signed = 2025.616100
assign sine_lut512_12bit[116] = 12'hfed     ; // offset dec =   4077 signed = 2029.167437
assign sine_lut512_12bit[117] = 12'hff0     ; // offset dec =   4080 signed = 2032.413499
assign sine_lut512_12bit[118] = 12'hff3     ; // offset dec =   4083 signed = 2035.353797
assign sine_lut512_12bit[119] = 12'hff5     ; // offset dec =   4085 signed = 2037.987889
assign sine_lut512_12bit[120] = 12'hff8     ; // offset dec =   4088 signed = 2040.315379
assign sine_lut512_12bit[121] = 12'hffa     ; // offset dec =   4090 signed = 2042.335916
assign sine_lut512_12bit[122] = 12'hffc     ; // offset dec =   4092 signed = 2044.049197
assign sine_lut512_12bit[123] = 12'hffd     ; // offset dec =   4093 signed = 2045.454963
assign sine_lut512_12bit[124] = 12'hffe     ; // offset dec =   4094 signed = 2046.553004
assign sine_lut512_12bit[125] = 12'hfff     ; // offset dec =   4095 signed = 2047.343153
assign sine_lut512_12bit[126] = 12'hfff     ; // offset dec =   4095 signed = 2047.825293
assign sine_lut512_12bit[127] = 12'hfff     ; // offset dec =   4095 signed = 2047.999351
assign sine_lut512_12bit[128] = 12'hfff     ; // offset dec =   4095 signed = 2047.865300
assign sine_lut512_12bit[129] = 12'hfff     ; // offset dec =   4095 signed = 2047.423160
assign sine_lut512_12bit[130] = 12'hffe     ; // offset dec =   4094 signed = 2046.672999
assign sine_lut512_12bit[131] = 12'hffd     ; // offset dec =   4093 signed = 2045.614929
assign sine_lut512_12bit[132] = 12'hffc     ; // offset dec =   4092 signed = 2044.249109
assign sine_lut512_12bit[133] = 12'hffa     ; // offset dec =   4090 signed = 2042.575744
assign sine_lut512_12bit[134] = 12'hff8     ; // offset dec =   4088 signed = 2040.595087
assign sine_lut512_12bit[135] = 12'hff6     ; // offset dec =   4086 signed = 2038.307435
assign sine_lut512_12bit[136] = 12'hff3     ; // offset dec =   4083 signed = 2035.713133
assign sine_lut512_12bit[137] = 12'hff0     ; // offset dec =   4080 signed = 2032.812571
assign sine_lut512_12bit[138] = 12'hfed     ; // offset dec =   4077 signed = 2029.606185
assign sine_lut512_12bit[139] = 12'hfea     ; // offset dec =   4074 signed = 2026.094458
assign sine_lut512_12bit[140] = 12'hfe6     ; // offset dec =   4070 signed = 2022.277917
assign sine_lut512_12bit[141] = 12'hfe2     ; // offset dec =   4066 signed = 2018.157138
assign sine_lut512_12bit[142] = 12'hfdd     ; // offset dec =   4061 signed = 2013.732739
assign sine_lut512_12bit[143] = 12'hfd9     ; // offset dec =   4057 signed = 2009.005388
assign sine_lut512_12bit[144] = 12'hfd3     ; // offset dec =   4051 signed = 2003.975794
assign sine_lut512_12bit[145] = 12'hfce     ; // offset dec =   4046 signed = 1998.644714
assign sine_lut512_12bit[146] = 12'hfc9     ; // offset dec =   4041 signed = 1993.012952
assign sine_lut512_12bit[147] = 12'hfc3     ; // offset dec =   4035 signed = 1987.081353
assign sine_lut512_12bit[148] = 12'hfbc     ; // offset dec =   4028 signed = 1980.850810
assign sine_lut512_12bit[149] = 12'hfb6     ; // offset dec =   4022 signed = 1974.322260
assign sine_lut512_12bit[150] = 12'hfaf     ; // offset dec =   4015 signed = 1967.496687
assign sine_lut512_12bit[151] = 12'hfa8     ; // offset dec =   4008 signed = 1960.375116
assign sine_lut512_12bit[152] = 12'hfa0     ; // offset dec =   4000 signed = 1952.958619
assign sine_lut512_12bit[153] = 12'hf99     ; // offset dec =   3993 signed = 1945.248312
assign sine_lut512_12bit[154] = 12'hf91     ; // offset dec =   3985 signed = 1937.245354
assign sine_lut512_12bit[155] = 12'hf88     ; // offset dec =   3976 signed = 1928.950950
assign sine_lut512_12bit[156] = 12'hf80     ; // offset dec =   3968 signed = 1920.366348
assign sine_lut512_12bit[157] = 12'hf77     ; // offset dec =   3959 signed = 1911.492839
assign sine_lut512_12bit[158] = 12'hf6e     ; // offset dec =   3950 signed = 1902.331757
assign sine_lut512_12bit[159] = 12'hf64     ; // offset dec =   3940 signed = 1892.884482
assign sine_lut512_12bit[160] = 12'hf5b     ; // offset dec =   3931 signed = 1883.152435
assign sine_lut512_12bit[161] = 12'hf51     ; // offset dec =   3921 signed = 1873.137079
assign sine_lut512_12bit[162] = 12'hf46     ; // offset dec =   3910 signed = 1862.839921
assign sine_lut512_12bit[163] = 12'hf3c     ; // offset dec =   3900 signed = 1852.262511
assign sine_lut512_12bit[164] = 12'hf31     ; // offset dec =   3889 signed = 1841.406440
assign sine_lut512_12bit[165] = 12'hf26     ; // offset dec =   3878 signed = 1830.273341
assign sine_lut512_12bit[166] = 12'hf1a     ; // offset dec =   3866 signed = 1818.864889
assign sine_lut512_12bit[167] = 12'hf0f     ; // offset dec =   3855 signed = 1807.182800
assign sine_lut512_12bit[168] = 12'hf03     ; // offset dec =   3843 signed = 1795.228832
assign sine_lut512_12bit[169] = 12'hef7     ; // offset dec =   3831 signed = 1783.004783
assign sine_lut512_12bit[170] = 12'heea     ; // offset dec =   3818 signed = 1770.512492
assign sine_lut512_12bit[171] = 12'hedd     ; // offset dec =   3805 signed = 1757.753839
assign sine_lut512_12bit[172] = 12'hed0     ; // offset dec =   3792 signed = 1744.730743
assign sine_lut512_12bit[173] = 12'hec3     ; // offset dec =   3779 signed = 1731.445163
assign sine_lut512_12bit[174] = 12'heb5     ; // offset dec =   3765 signed = 1717.899099
assign sine_lut512_12bit[175] = 12'hea8     ; // offset dec =   3752 signed = 1704.094587
assign sine_lut512_12bit[176] = 12'he9a     ; // offset dec =   3738 signed = 1690.033705
assign sine_lut512_12bit[177] = 12'he8b     ; // offset dec =   3723 signed = 1675.718568
assign sine_lut512_12bit[178] = 12'he7d     ; // offset dec =   3709 signed = 1661.151330
assign sine_lut512_12bit[179] = 12'he6e     ; // offset dec =   3694 signed = 1646.334182
assign sine_lut512_12bit[180] = 12'he5f     ; // offset dec =   3679 signed = 1631.269354
assign sine_lut512_12bit[181] = 12'he4f     ; // offset dec =   3663 signed = 1615.959111
assign sine_lut512_12bit[182] = 12'he40     ; // offset dec =   3648 signed = 1600.405758
assign sine_lut512_12bit[183] = 12'he30     ; // offset dec =   3632 signed = 1584.611634
assign sine_lut512_12bit[184] = 12'he20     ; // offset dec =   3616 signed = 1568.579115
assign sine_lut512_12bit[185] = 12'he10     ; // offset dec =   3600 signed = 1552.310613
assign sine_lut512_12bit[186] = 12'hdff     ; // offset dec =   3583 signed = 1535.808576
assign sine_lut512_12bit[187] = 12'hdef     ; // offset dec =   3567 signed = 1519.075486
assign sine_lut512_12bit[188] = 12'hdde     ; // offset dec =   3550 signed = 1502.113861
assign sine_lut512_12bit[189] = 12'hdcc     ; // offset dec =   3532 signed = 1484.926252
assign sine_lut512_12bit[190] = 12'hdbb     ; // offset dec =   3515 signed = 1467.515246
assign sine_lut512_12bit[191] = 12'hda9     ; // offset dec =   3497 signed = 1449.883461
assign sine_lut512_12bit[192] = 12'hd98     ; // offset dec =   3480 signed = 1432.033550
assign sine_lut512_12bit[193] = 12'hd85     ; // offset dec =   3461 signed = 1413.968199
assign sine_lut512_12bit[194] = 12'hd73     ; // offset dec =   3443 signed = 1395.690126
assign sine_lut512_12bit[195] = 12'hd61     ; // offset dec =   3425 signed = 1377.202080
assign sine_lut512_12bit[196] = 12'hd4e     ; // offset dec =   3406 signed = 1358.506842
assign sine_lut512_12bit[197] = 12'hd3b     ; // offset dec =   3387 signed = 1339.607226
assign sine_lut512_12bit[198] = 12'hd28     ; // offset dec =   3368 signed = 1320.506074
assign sine_lut512_12bit[199] = 12'hd15     ; // offset dec =   3349 signed = 1301.206260
assign sine_lut512_12bit[200] = 12'hd01     ; // offset dec =   3329 signed = 1281.710689
assign sine_lut512_12bit[201] = 12'hcee     ; // offset dec =   3310 signed = 1262.022291
assign sine_lut512_12bit[202] = 12'hcda     ; // offset dec =   3290 signed = 1242.144031
assign sine_lut512_12bit[203] = 12'hcc6     ; // offset dec =   3270 signed = 1222.078898
assign sine_lut512_12bit[204] = 12'hcb1     ; // offset dec =   3249 signed = 1201.829911
assign sine_lut512_12bit[205] = 12'hc9d     ; // offset dec =   3229 signed = 1181.400116
assign sine_lut512_12bit[206] = 12'hc88     ; // offset dec =   3208 signed = 1160.792587
assign sine_lut512_12bit[207] = 12'hc74     ; // offset dec =   3188 signed = 1140.010424
assign sine_lut512_12bit[208] = 12'hc5f     ; // offset dec =   3167 signed = 1119.056754
assign sine_lut512_12bit[209] = 12'hc49     ; // offset dec =   3145 signed = 1097.934729
assign sine_lut512_12bit[210] = 12'hc34     ; // offset dec =   3124 signed = 1076.647526
assign sine_lut512_12bit[211] = 12'hc1f     ; // offset dec =   3103 signed = 1055.198349
assign sine_lut512_12bit[212] = 12'hc09     ; // offset dec =   3081 signed = 1033.590424
assign sine_lut512_12bit[213] = 12'hbf3     ; // offset dec =   3059 signed = 1011.827002
assign sine_lut512_12bit[214] = 12'hbdd     ; // offset dec =   3037 signed = 989.911356
assign sine_lut512_12bit[215] = 12'hbc7     ; // offset dec =   3015 signed = 967.846785
assign sine_lut512_12bit[216] = 12'hbb1     ; // offset dec =   2993 signed = 945.636607
assign sine_lut512_12bit[217] = 12'hb9b     ; // offset dec =   2971 signed = 923.284164
assign sine_lut512_12bit[218] = 12'hb84     ; // offset dec =   2948 signed = 900.792820
assign sine_lut512_12bit[219] = 12'hb6e     ; // offset dec =   2926 signed = 878.165956
assign sine_lut512_12bit[220] = 12'hb57     ; // offset dec =   2903 signed = 855.406978
assign sine_lut512_12bit[221] = 12'hb40     ; // offset dec =   2880 signed = 832.519309
assign sine_lut512_12bit[222] = 12'hb29     ; // offset dec =   2857 signed = 809.506393
assign sine_lut512_12bit[223] = 12'hb12     ; // offset dec =   2834 signed = 786.371692
assign sine_lut512_12bit[224] = 12'hafb     ; // offset dec =   2811 signed = 763.118687
assign sine_lut512_12bit[225] = 12'hae3     ; // offset dec =   2787 signed = 739.750875
assign sine_lut512_12bit[226] = 12'hacc     ; // offset dec =   2764 signed = 716.271772
assign sine_lut512_12bit[227] = 12'hab4     ; // offset dec =   2740 signed = 692.684910
assign sine_lut512_12bit[228] = 12'ha9c     ; // offset dec =   2716 signed = 668.993839
assign sine_lut512_12bit[229] = 12'ha85     ; // offset dec =   2693 signed = 645.202122
assign sine_lut512_12bit[230] = 12'ha6d     ; // offset dec =   2669 signed = 621.313338
assign sine_lut512_12bit[231] = 12'ha55     ; // offset dec =   2645 signed = 597.331081
assign sine_lut512_12bit[232] = 12'ha3d     ; // offset dec =   2621 signed = 573.258960
assign sine_lut512_12bit[233] = 12'ha25     ; // offset dec =   2597 signed = 549.100595
assign sine_lut512_12bit[234] = 12'ha0c     ; // offset dec =   2572 signed = 524.859622
assign sine_lut512_12bit[235] = 12'h9f4     ; // offset dec =   2548 signed = 500.539687
assign sine_lut512_12bit[236] = 12'h9dc     ; // offset dec =   2524 signed = 476.144449
assign sine_lut512_12bit[237] = 12'h9c3     ; // offset dec =   2499 signed = 451.677578
assign sine_lut512_12bit[238] = 12'h9ab     ; // offset dec =   2475 signed = 427.142755
assign sine_lut512_12bit[239] = 12'h992     ; // offset dec =   2450 signed = 402.543671
assign sine_lut512_12bit[240] = 12'h979     ; // offset dec =   2425 signed = 377.884027
assign sine_lut512_12bit[241] = 12'h961     ; // offset dec =   2401 signed = 353.167533
assign sine_lut512_12bit[242] = 12'h948     ; // offset dec =   2376 signed = 328.397907
assign sine_lut512_12bit[243] = 12'h92f     ; // offset dec =   2351 signed = 303.578875
assign sine_lut512_12bit[244] = 12'h916     ; // offset dec =   2326 signed = 278.714172
assign sine_lut512_12bit[245] = 12'h8fd     ; // offset dec =   2301 signed = 253.807539
assign sine_lut512_12bit[246] = 12'h8e4     ; // offset dec =   2276 signed = 228.862721
assign sine_lut512_12bit[247] = 12'h8cb     ; // offset dec =   2251 signed = 203.883473
assign sine_lut512_12bit[248] = 12'h8b2     ; // offset dec =   2226 signed = 178.873551
assign sine_lut512_12bit[249] = 12'h899     ; // offset dec =   2201 signed = 153.836719
assign sine_lut512_12bit[250] = 12'h880     ; // offset dec =   2176 signed = 128.776744
assign sine_lut512_12bit[251] = 12'h867     ; // offset dec =   2151 signed = 103.697394
assign sine_lut512_12bit[252] = 12'h84e     ; // offset dec =   2126 signed = 78.602444
assign sine_lut512_12bit[253] = 12'h835     ; // offset dec =   2101 signed = 53.495669
assign sine_lut512_12bit[254] = 12'h81c     ; // offset dec =   2076 signed = 28.380846
assign sine_lut512_12bit[255] = 12'h803     ; // offset dec =   2051 signed = 3.261753
assign sine_lut512_12bit[256] = 12'h7ea     ; // offset dec =   2026 signed = -21.857830
assign sine_lut512_12bit[257] = 12'h7d1     ; // offset dec =   2001 signed = -46.974126
assign sine_lut512_12bit[258] = 12'h7b7     ; // offset dec =   1975 signed = -72.083354
assign sine_lut512_12bit[259] = 12'h79e     ; // offset dec =   1950 signed = -97.181738
assign sine_lut512_12bit[260] = 12'h785     ; // offset dec =   1925 signed = -122.265501
assign sine_lut512_12bit[261] = 12'h76c     ; // offset dec =   1900 signed = -147.330871
assign sine_lut512_12bit[262] = 12'h753     ; // offset dec =   1875 signed = -172.374075
assign sine_lut512_12bit[263] = 12'h73a     ; // offset dec =   1850 signed = -197.391347
assign sine_lut512_12bit[264] = 12'h721     ; // offset dec =   1825 signed = -222.378922
assign sine_lut512_12bit[265] = 12'h708     ; // offset dec =   1800 signed = -247.333042
assign sine_lut512_12bit[266] = 12'h6ef     ; // offset dec =   1775 signed = -272.249953
assign sine_lut512_12bit[267] = 12'h6d6     ; // offset dec =   1750 signed = -297.125905
assign sine_lut512_12bit[268] = 12'h6be     ; // offset dec =   1726 signed = -321.957156
assign sine_lut512_12bit[269] = 12'h6a5     ; // offset dec =   1701 signed = -346.739971
assign sine_lut512_12bit[270] = 12'h68c     ; // offset dec =   1676 signed = -371.470621
assign sine_lut512_12bit[271] = 12'h673     ; // offset dec =   1651 signed = -396.145386
assign sine_lut512_12bit[272] = 12'h65b     ; // offset dec =   1627 signed = -420.760553
assign sine_lut512_12bit[273] = 12'h642     ; // offset dec =   1602 signed = -445.312419
assign sine_lut512_12bit[274] = 12'h62a     ; // offset dec =   1578 signed = -469.797291
assign sine_lut512_12bit[275] = 12'h611     ; // offset dec =   1553 signed = -494.211485
assign sine_lut512_12bit[276] = 12'h5f9     ; // offset dec =   1529 signed = -518.551328
assign sine_lut512_12bit[277] = 12'h5e1     ; // offset dec =   1505 signed = -542.813158
assign sine_lut512_12bit[278] = 12'h5c9     ; // offset dec =   1481 signed = -566.993325
assign sine_lut512_12bit[279] = 12'h5b0     ; // offset dec =   1456 signed = -591.088192
assign sine_lut512_12bit[280] = 12'h598     ; // offset dec =   1432 signed = -615.094133
assign sine_lut512_12bit[281] = 12'h580     ; // offset dec =   1408 signed = -639.007538
assign sine_lut512_12bit[282] = 12'h569     ; // offset dec =   1385 signed = -662.824807
assign sine_lut512_12bit[283] = 12'h551     ; // offset dec =   1361 signed = -686.542359
assign sine_lut512_12bit[284] = 12'h539     ; // offset dec =   1337 signed = -710.156625
assign sine_lut512_12bit[285] = 12'h522     ; // offset dec =   1314 signed = -733.664052
assign sine_lut512_12bit[286] = 12'h50a     ; // offset dec =   1290 signed = -757.061104
assign sine_lut512_12bit[287] = 12'h4f3     ; // offset dec =   1267 signed = -780.344261
assign sine_lut512_12bit[288] = 12'h4dc     ; // offset dec =   1244 signed = -803.510021
assign sine_lut512_12bit[289] = 12'h4c5     ; // offset dec =   1221 signed = -826.554897
assign sine_lut512_12bit[290] = 12'h4ae     ; // offset dec =   1198 signed = -849.475423
assign sine_lut512_12bit[291] = 12'h497     ; // offset dec =   1175 signed = -872.268152
assign sine_lut512_12bit[292] = 12'h481     ; // offset dec =   1153 signed = -894.929652
assign sine_lut512_12bit[293] = 12'h46a     ; // offset dec =   1130 signed = -917.456517
assign sine_lut512_12bit[294] = 12'h454     ; // offset dec =   1108 signed = -939.845356
assign sine_lut512_12bit[295] = 12'h43d     ; // offset dec =   1085 signed = -962.092801
assign sine_lut512_12bit[296] = 12'h427     ; // offset dec =   1063 signed = -984.195505
assign sine_lut512_12bit[297] = 12'h411     ; // offset dec =   1041 signed = -1006.150144
assign sine_lut512_12bit[298] = 12'h3fc     ; // offset dec =   1020 signed = -1027.953413
assign sine_lut512_12bit[299] = 12'h3e6     ; // offset dec =    998 signed = -1049.602033
assign sine_lut512_12bit[300] = 12'h3d0     ; // offset dec =    976 signed = -1071.092748
assign sine_lut512_12bit[301] = 12'h3bb     ; // offset dec =    955 signed = -1092.422323
assign sine_lut512_12bit[302] = 12'h3a6     ; // offset dec =    934 signed = -1113.587550
assign sine_lut512_12bit[303] = 12'h391     ; // offset dec =    913 signed = -1134.585245
assign sine_lut512_12bit[304] = 12'h37c     ; // offset dec =    892 signed = -1155.412249
assign sine_lut512_12bit[305] = 12'h367     ; // offset dec =    871 signed = -1176.065428
assign sine_lut512_12bit[306] = 12'h353     ; // offset dec =    851 signed = -1196.541676
assign sine_lut512_12bit[307] = 12'h33f     ; // offset dec =    831 signed = -1216.837912
assign sine_lut512_12bit[308] = 12'h32b     ; // offset dec =    811 signed = -1236.951082
assign sine_lut512_12bit[309] = 12'h317     ; // offset dec =    791 signed = -1256.878160
assign sine_lut512_12bit[310] = 12'h303     ; // offset dec =    771 signed = -1276.616150
assign sine_lut512_12bit[311] = 12'h2ef     ; // offset dec =    751 signed = -1296.162080
assign sine_lut512_12bit[312] = 12'h2dc     ; // offset dec =    732 signed = -1315.513011
assign sine_lut512_12bit[313] = 12'h2c9     ; // offset dec =    713 signed = -1334.666032
assign sine_lut512_12bit[314] = 12'h2b6     ; // offset dec =    694 signed = -1353.618260
assign sine_lut512_12bit[315] = 12'h2a3     ; // offset dec =    675 signed = -1372.366845
assign sine_lut512_12bit[316] = 12'h291     ; // offset dec =    657 signed = -1390.908966
assign sine_lut512_12bit[317] = 12'h27e     ; // offset dec =    638 signed = -1409.241834
assign sine_lut512_12bit[318] = 12'h26c     ; // offset dec =    620 signed = -1427.362690
assign sine_lut512_12bit[319] = 12'h25a     ; // offset dec =    602 signed = -1445.268809
assign sine_lut512_12bit[320] = 12'h249     ; // offset dec =    585 signed = -1462.957496
assign sine_lut512_12bit[321] = 12'h237     ; // offset dec =    567 signed = -1480.426090
assign sine_lut512_12bit[322] = 12'h226     ; // offset dec =    550 signed = -1497.671964
assign sine_lut512_12bit[323] = 12'h215     ; // offset dec =    533 signed = -1514.692522
assign sine_lut512_12bit[324] = 12'h204     ; // offset dec =    516 signed = -1531.485205
assign sine_lut512_12bit[325] = 12'h1f3     ; // offset dec =    499 signed = -1548.047485
assign sine_lut512_12bit[326] = 12'h1e3     ; // offset dec =    483 signed = -1564.376871
assign sine_lut512_12bit[327] = 12'h1d3     ; // offset dec =    467 signed = -1580.470907
assign sine_lut512_12bit[328] = 12'h1c3     ; // offset dec =    451 signed = -1596.327170
assign sine_lut512_12bit[329] = 12'h1b4     ; // offset dec =    436 signed = -1611.943277
assign sine_lut512_12bit[330] = 12'h1a4     ; // offset dec =    420 signed = -1627.316877
assign sine_lut512_12bit[331] = 12'h195     ; // offset dec =    405 signed = -1642.445657
assign sine_lut512_12bit[332] = 12'h186     ; // offset dec =    390 signed = -1657.327342
assign sine_lut512_12bit[333] = 12'h178     ; // offset dec =    376 signed = -1671.959692
assign sine_lut512_12bit[334] = 12'h169     ; // offset dec =    361 signed = -1686.340507
assign sine_lut512_12bit[335] = 12'h15b     ; // offset dec =    347 signed = -1700.467622
assign sine_lut512_12bit[336] = 12'h14d     ; // offset dec =    333 signed = -1714.338913
assign sine_lut512_12bit[337] = 12'h140     ; // offset dec =    320 signed = -1727.952292
assign sine_lut512_12bit[338] = 12'h132     ; // offset dec =    306 signed = -1741.305712
assign sine_lut512_12bit[339] = 12'h125     ; // offset dec =    293 signed = -1754.397163
assign sine_lut512_12bit[340] = 12'h118     ; // offset dec =    280 signed = -1767.224676
assign sine_lut512_12bit[341] = 12'h10c     ; // offset dec =    268 signed = -1779.786322
assign sine_lut512_12bit[342] = 12'hff      ; // offset dec =    255 signed = -1792.080210
assign sine_lut512_12bit[343] = 12'hf3      ; // offset dec =    243 signed = -1804.104491
assign sine_lut512_12bit[344] = 12'he8      ; // offset dec =    232 signed = -1815.857356
assign sine_lut512_12bit[345] = 12'hdc      ; // offset dec =    220 signed = -1827.337036
assign sine_lut512_12bit[346] = 12'hd1      ; // offset dec =    209 signed = -1838.541806
assign sine_lut512_12bit[347] = 12'hc6      ; // offset dec =    198 signed = -1849.469978
assign sine_lut512_12bit[348] = 12'hbb      ; // offset dec =    187 signed = -1860.119909
assign sine_lut512_12bit[349] = 12'hb1      ; // offset dec =    177 signed = -1870.489997
assign sine_lut512_12bit[350] = 12'ha7      ; // offset dec =    167 signed = -1880.578682
assign sine_lut512_12bit[351] = 12'h9d      ; // offset dec =    157 signed = -1890.384445
assign sine_lut512_12bit[352] = 12'h94      ; // offset dec =    148 signed = -1899.905812
assign sine_lut512_12bit[353] = 12'h8a      ; // offset dec =    138 signed = -1909.141351
assign sine_lut512_12bit[354] = 12'h81      ; // offset dec =    129 signed = -1918.089671
assign sine_lut512_12bit[355] = 12'h79      ; // offset dec =    121 signed = -1926.749426
assign sine_lut512_12bit[356] = 12'h70      ; // offset dec =    112 signed = -1935.119315
assign sine_lut512_12bit[357] = 12'h68      ; // offset dec =    104 signed = -1943.198077
assign sine_lut512_12bit[358] = 12'h61      ; // offset dec =     97 signed = -1950.984497
assign sine_lut512_12bit[359] = 12'h59      ; // offset dec =     89 signed = -1958.477403
assign sine_lut512_12bit[360] = 12'h52      ; // offset dec =     82 signed = -1965.675670
assign sine_lut512_12bit[361] = 12'h4b      ; // offset dec =     75 signed = -1972.578212
assign sine_lut512_12bit[362] = 12'h44      ; // offset dec =     68 signed = -1979.183993
assign sine_lut512_12bit[363] = 12'h3e      ; // offset dec =     62 signed = -1985.492018
assign sine_lut512_12bit[364] = 12'h38      ; // offset dec =     56 signed = -1991.501339
assign sine_lut512_12bit[365] = 12'h32      ; // offset dec =     50 signed = -1997.211050
assign sine_lut512_12bit[366] = 12'h2d      ; // offset dec =     45 signed = -2002.620294
assign sine_lut512_12bit[367] = 12'h28      ; // offset dec =     40 signed = -2007.728257
assign sine_lut512_12bit[368] = 12'h23      ; // offset dec =     35 signed = -2012.534169
assign sine_lut512_12bit[369] = 12'h1e      ; // offset dec =     30 signed = -2017.037309
assign sine_lut512_12bit[370] = 12'h1a      ; // offset dec =     26 signed = -2021.236997
assign sine_lut512_12bit[371] = 12'h16      ; // offset dec =     22 signed = -2025.132604
assign sine_lut512_12bit[372] = 12'h13      ; // offset dec =     19 signed = -2028.723542
assign sine_lut512_12bit[373] = 12'hf       ; // offset dec =     15 signed = -2032.009272
assign sine_lut512_12bit[374] = 12'hd       ; // offset dec =     13 signed = -2034.989298
assign sine_lut512_12bit[375] = 12'ha       ; // offset dec =     10 signed = -2037.663173
assign sine_lut512_12bit[376] = 12'h7       ; // offset dec =      7 signed = -2040.030495
assign sine_lut512_12bit[377] = 12'h5       ; // offset dec =      5 signed = -2042.090907
assign sine_lut512_12bit[378] = 12'h4       ; // offset dec =      4 signed = -2043.844100
assign sine_lut512_12bit[379] = 12'h2       ; // offset dec =      2 signed = -2045.289809
assign sine_lut512_12bit[380] = 12'h1       ; // offset dec =      1 signed = -2046.427817
assign sine_lut512_12bit[381] = 12'h0       ; // offset dec =      0 signed = -2047.257953
assign sine_lut512_12bit[382] = 12'h0       ; // offset dec =      0 signed = -2047.780092
assign sine_lut512_12bit[383] = 12'h0       ; // offset dec =      0 signed = -2047.994156
assign sine_lut512_12bit[384] = 12'h0       ; // offset dec =      0 signed = -2047.900112
assign sine_lut512_12bit[385] = 12'h0       ; // offset dec =      0 signed = -2047.497974
assign sine_lut512_12bit[386] = 12'h1       ; // offset dec =      1 signed = -2046.787803
assign sine_lut512_12bit[387] = 12'h2       ; // offset dec =      2 signed = -2045.769705
assign sine_lut512_12bit[388] = 12'h3       ; // offset dec =      3 signed = -2044.443835
assign sine_lut512_12bit[389] = 12'h5       ; // offset dec =      5 signed = -2042.810391
assign sine_lut512_12bit[390] = 12'h7       ; // offset dec =      7 signed = -2040.869619
assign sine_lut512_12bit[391] = 12'h9       ; // offset dec =      9 signed = -2038.621811
assign sine_lut512_12bit[392] = 12'hb       ; // offset dec =     11 signed = -2036.067306
assign sine_lut512_12bit[393] = 12'he       ; // offset dec =     14 signed = -2033.206487
assign sine_lut512_12bit[394] = 12'h11      ; // offset dec =     17 signed = -2030.039785
assign sine_lut512_12bit[395] = 12'h15      ; // offset dec =     21 signed = -2026.567676
assign sine_lut512_12bit[396] = 12'h19      ; // offset dec =     25 signed = -2022.790683
assign sine_lut512_12bit[397] = 12'h1d      ; // offset dec =     29 signed = -2018.709374
assign sine_lut512_12bit[398] = 12'h21      ; // offset dec =     33 signed = -2014.324363
assign sine_lut512_12bit[399] = 12'h26      ; // offset dec =     38 signed = -2009.636310
assign sine_lut512_12bit[400] = 12'h2b      ; // offset dec =     43 signed = -2004.645919
assign sine_lut512_12bit[401] = 12'h30      ; // offset dec =     48 signed = -1999.353943
assign sine_lut512_12bit[402] = 12'h36      ; // offset dec =     54 signed = -1993.761176
assign sine_lut512_12bit[403] = 12'h3c      ; // offset dec =     60 signed = -1987.868460
assign sine_lut512_12bit[404] = 12'h42      ; // offset dec =     66 signed = -1981.676682
assign sine_lut512_12bit[405] = 12'h48      ; // offset dec =     72 signed = -1975.186774
assign sine_lut512_12bit[406] = 12'h4f      ; // offset dec =     79 signed = -1968.399711
assign sine_lut512_12bit[407] = 12'h56      ; // offset dec =     86 signed = -1961.316515
assign sine_lut512_12bit[408] = 12'h5e      ; // offset dec =     94 signed = -1953.938251
assign sine_lut512_12bit[409] = 12'h65      ; // offset dec =    101 signed = -1946.266029
assign sine_lut512_12bit[410] = 12'h6d      ; // offset dec =    109 signed = -1938.301004
assign sine_lut512_12bit[411] = 12'h75      ; // offset dec =    117 signed = -1930.044374
assign sine_lut512_12bit[412] = 12'h7e      ; // offset dec =    126 signed = -1921.497381
assign sine_lut512_12bit[413] = 12'h87      ; // offset dec =    135 signed = -1912.661311
assign sine_lut512_12bit[414] = 12'h90      ; // offset dec =    144 signed = -1903.537493
assign sine_lut512_12bit[415] = 12'h99      ; // offset dec =    153 signed = -1894.127300
assign sine_lut512_12bit[416] = 12'ha3      ; // offset dec =    163 signed = -1884.432148
assign sine_lut512_12bit[417] = 12'had      ; // offset dec =    173 signed = -1874.453494
assign sine_lut512_12bit[418] = 12'hb7      ; // offset dec =    183 signed = -1864.192841
assign sine_lut512_12bit[419] = 12'hc2      ; // offset dec =    194 signed = -1853.651732
assign sine_lut512_12bit[420] = 12'hcd      ; // offset dec =    205 signed = -1842.831753
assign sine_lut512_12bit[421] = 12'hd8      ; // offset dec =    216 signed = -1831.734531
assign sine_lut512_12bit[422] = 12'he3      ; // offset dec =    227 signed = -1820.361737
assign sine_lut512_12bit[423] = 12'hef      ; // offset dec =    239 signed = -1808.715080
assign sine_lut512_12bit[424] = 12'hfb      ; // offset dec =    251 signed = -1796.796314
assign sine_lut512_12bit[425] = 12'h107     ; // offset dec =    263 signed = -1784.607231
assign sine_lut512_12bit[426] = 12'h113     ; // offset dec =    275 signed = -1772.149666
assign sine_lut512_12bit[427] = 12'h120     ; // offset dec =    288 signed = -1759.425491
assign sine_lut512_12bit[428] = 12'h12d     ; // offset dec =    301 signed = -1746.436623
assign sine_lut512_12bit[429] = 12'h13a     ; // offset dec =    314 signed = -1733.185013
assign sine_lut512_12bit[430] = 12'h148     ; // offset dec =    328 signed = -1719.672658
assign sine_lut512_12bit[431] = 12'h156     ; // offset dec =    342 signed = -1705.901588
assign sine_lut512_12bit[432] = 12'h164     ; // offset dec =    356 signed = -1691.873876
assign sine_lut512_12bit[433] = 12'h172     ; // offset dec =    370 signed = -1677.591633
assign sine_lut512_12bit[434] = 12'h180     ; // offset dec =    384 signed = -1663.057006
assign sine_lut512_12bit[435] = 12'h18f     ; // offset dec =    399 signed = -1648.272183
assign sine_lut512_12bit[436] = 12'h19e     ; // offset dec =    414 signed = -1633.239388
assign sine_lut512_12bit[437] = 12'h1ae     ; // offset dec =    430 signed = -1617.960883
assign sine_lut512_12bit[438] = 12'h1bd     ; // offset dec =    445 signed = -1602.438965
assign sine_lut512_12bit[439] = 12'h1cd     ; // offset dec =    461 signed = -1586.675971
assign sine_lut512_12bit[440] = 12'h1dd     ; // offset dec =    477 signed = -1570.674271
assign sine_lut512_12bit[441] = 12'h1ed     ; // offset dec =    493 signed = -1554.436273
assign sine_lut512_12bit[442] = 12'h1fe     ; // offset dec =    510 signed = -1537.964420
assign sine_lut512_12bit[443] = 12'h20e     ; // offset dec =    526 signed = -1521.261191
assign sine_lut512_12bit[444] = 12'h21f     ; // offset dec =    543 signed = -1504.329097
assign sine_lut512_12bit[445] = 12'h230     ; // offset dec =    560 signed = -1487.170686
assign sine_lut512_12bit[446] = 12'h242     ; // offset dec =    578 signed = -1469.788540
assign sine_lut512_12bit[447] = 12'h253     ; // offset dec =    595 signed = -1452.185273
assign sine_lut512_12bit[448] = 12'h265     ; // offset dec =    613 signed = -1434.363535
assign sine_lut512_12bit[449] = 12'h277     ; // offset dec =    631 signed = -1416.326005
assign sine_lut512_12bit[450] = 12'h289     ; // offset dec =    649 signed = -1398.075398
assign sine_lut512_12bit[451] = 12'h29c     ; // offset dec =    668 signed = -1379.614460
assign sine_lut512_12bit[452] = 12'h2af     ; // offset dec =    687 signed = -1360.945967
assign sine_lut512_12bit[453] = 12'h2c1     ; // offset dec =    705 signed = -1342.072729
assign sine_lut512_12bit[454] = 12'h2d5     ; // offset dec =    725 signed = -1322.997584
assign sine_lut512_12bit[455] = 12'h2e8     ; // offset dec =    744 signed = -1303.723403
assign sine_lut512_12bit[456] = 12'h2fb     ; // offset dec =    763 signed = -1284.253084
assign sine_lut512_12bit[457] = 12'h30f     ; // offset dec =    783 signed = -1264.589558
assign sine_lut512_12bit[458] = 12'h323     ; // offset dec =    803 signed = -1244.735783
assign sine_lut512_12bit[459] = 12'h337     ; // offset dec =    823 signed = -1224.694745
assign sine_lut512_12bit[460] = 12'h34b     ; // offset dec =    843 signed = -1204.469459
assign sine_lut512_12bit[461] = 12'h35f     ; // offset dec =    863 signed = -1184.062969
assign sine_lut512_12bit[462] = 12'h374     ; // offset dec =    884 signed = -1163.478343
assign sine_lut512_12bit[463] = 12'h389     ; // offset dec =    905 signed = -1142.718680
assign sine_lut512_12bit[464] = 12'h39e     ; // offset dec =    926 signed = -1121.787102
assign sine_lut512_12bit[465] = 12'h3b3     ; // offset dec =    947 signed = -1100.686758
assign sine_lut512_12bit[466] = 12'h3c8     ; // offset dec =    968 signed = -1079.420823
assign sine_lut512_12bit[467] = 12'h3de     ; // offset dec =    990 signed = -1057.992496
assign sine_lut512_12bit[468] = 12'h3f3     ; // offset dec =   1011 signed = -1036.405000
assign sine_lut512_12bit[469] = 12'h409     ; // offset dec =   1033 signed = -1014.661584
assign sine_lut512_12bit[470] = 12'h41f     ; // offset dec =   1055 signed = -992.765519
assign sine_lut512_12bit[471] = 12'h435     ; // offset dec =   1077 signed = -970.720098
assign sine_lut512_12bit[472] = 12'h44b     ; // offset dec =   1099 signed = -948.528639
assign sine_lut512_12bit[473] = 12'h461     ; // offset dec =   1121 signed = -926.194479
assign sine_lut512_12bit[474] = 12'h478     ; // offset dec =   1144 signed = -903.720979
assign sine_lut512_12bit[475] = 12'h48e     ; // offset dec =   1166 signed = -881.111521
assign sine_lut512_12bit[476] = 12'h4a5     ; // offset dec =   1189 signed = -858.369504
assign sine_lut512_12bit[477] = 12'h4bc     ; // offset dec =   1212 signed = -835.498352
assign sine_lut512_12bit[478] = 12'h4d3     ; // offset dec =   1235 signed = -812.501503
assign sine_lut512_12bit[479] = 12'h4ea     ; // offset dec =   1258 signed = -789.382420
assign sine_lut512_12bit[480] = 12'h501     ; // offset dec =   1281 signed = -766.144578
assign sine_lut512_12bit[481] = 12'h519     ; // offset dec =   1305 signed = -742.791475
assign sine_lut512_12bit[482] = 12'h530     ; // offset dec =   1328 signed = -719.326624
assign sine_lut512_12bit[483] = 12'h548     ; // offset dec =   1352 signed = -695.753554
assign sine_lut512_12bit[484] = 12'h55f     ; // offset dec =   1375 signed = -672.075813
assign sine_lut512_12bit[485] = 12'h577     ; // offset dec =   1399 signed = -648.296963
assign sine_lut512_12bit[486] = 12'h58f     ; // offset dec =   1423 signed = -624.420580
assign sine_lut512_12bit[487] = 12'h5a7     ; // offset dec =   1447 signed = -600.450257
assign sine_lut512_12bit[488] = 12'h5bf     ; // offset dec =   1471 signed = -576.389600
assign sine_lut512_12bit[489] = 12'h5d7     ; // offset dec =   1495 signed = -552.242229
assign sine_lut512_12bit[490] = 12'h5ef     ; // offset dec =   1519 signed = -528.011776
assign sine_lut512_12bit[491] = 12'h608     ; // offset dec =   1544 signed = -503.701888
assign sine_lut512_12bit[492] = 12'h620     ; // offset dec =   1568 signed = -479.316220
assign sine_lut512_12bit[493] = 12'h639     ; // offset dec =   1593 signed = -454.858443
assign sine_lut512_12bit[494] = 12'h651     ; // offset dec =   1617 signed = -430.332235
assign sine_lut512_12bit[495] = 12'h66a     ; // offset dec =   1642 signed = -405.741287
assign sine_lut512_12bit[496] = 12'h682     ; // offset dec =   1666 signed = -381.089297
assign sine_lut512_12bit[497] = 12'h69b     ; // offset dec =   1691 signed = -356.379974
assign sine_lut512_12bit[498] = 12'h6b4     ; // offset dec =   1716 signed = -331.617037
assign sine_lut512_12bit[499] = 12'h6cd     ; // offset dec =   1741 signed = -306.804210
assign sine_lut512_12bit[500] = 12'h6e6     ; // offset dec =   1766 signed = -281.945226
assign sine_lut512_12bit[501] = 12'h6fe     ; // offset dec =   1790 signed = -257.043825
assign sine_lut512_12bit[502] = 12'h717     ; // offset dec =   1815 signed = -232.103754
assign sine_lut512_12bit[503] = 12'h730     ; // offset dec =   1840 signed = -207.128764
assign sine_lut512_12bit[504] = 12'h749     ; // offset dec =   1865 signed = -182.122613
assign sine_lut512_12bit[505] = 12'h762     ; // offset dec =   1890 signed = -157.089062
assign sine_lut512_12bit[506] = 12'h77b     ; // offset dec =   1915 signed = -132.031879
assign sine_lut512_12bit[507] = 12'h795     ; // offset dec =   1941 signed = -106.954832
assign sine_lut512_12bit[508] = 12'h7ae     ; // offset dec =   1966 signed = -81.861695
assign sine_lut512_12bit[509] = 12'h7c7     ; // offset dec =   1991 signed = -56.756242
assign sine_lut512_12bit[510] = 12'h7e0     ; // offset dec =   2016 signed = -31.642250
assign sine_lut512_12bit[511] = 12'h7f9     ; // offset dec =   2041 signed = -6.523498


// -----------------------------------------------------------------------------
// Assign the output
// -----------------------------------------------------------------------------
assign sine_value   = sine_lut512_12bit[address];
assign sine_value_i = sine_lut512_12bit[address_fast + 9'd128];
assign sine_value_q = sine_lut512_12bit[address_fast];

endmodule
