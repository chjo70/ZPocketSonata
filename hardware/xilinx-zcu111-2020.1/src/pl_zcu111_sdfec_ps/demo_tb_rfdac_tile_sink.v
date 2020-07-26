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
//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
`timescale 1ps / 1ps

//`define EXCLUDE_SINE_WAVE_LUTS

`define DGTYPE_TRGL     0
`define DGTYPE_RAMPUP   1
`define DGTYPE_RAMPDOWN 2
`define DGTYPE_SINE0    3

// ----------------------------------------------------------------------------
// Data generator tile
// ----------------------------------------------------------------------------
module demo_tb_rfdac_tile_sink #(
  parameter  p_connection_width  = 16,
  parameter  p_change_width      = 16,
  parameter  p_useable_width     = 14,
  parameter  p_data_inc_val_init = 1,
  parameter  p_data_type_width   = 3
) (

                                                                                    input  wire    [p_change_width-1:0] s0_change_count   , // 
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_0 enable"    *) input  wire                         s0_enable         , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_0 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s0_inc            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_0 dg_type"   *) input  wire [p_data_type_width-1:0] s0_type           , //
                                                                                    input  wire                  [31:0] s0_scaling_factor , //
                                                                                    input  wire                  [31:0] s0_offset         , //
                                                                                    input  wire                  [31:0] s0_clk_phase_hl   , //
                                                                                    input  wire                  [63:0] s0_din_p          , //
                                                                                    input  wire                  [63:0] s0_din_n          , //
                                                                                    //
                                                                                    input  wire                   [7:0] s0_ds_ctrl          ,
                                                                                    output wire                  [31:0] s0_ds_fft_exec_cnt  ,
                                                                                    output wire                  [31:0] s0_ds_fft_max_level ,
                                                                                    output wire                   [7:0] s0_ds_status        ,
                                                                                    output wire                         s0_error          , //
 
                                                                                    input  wire    [p_change_width-1:0] s1_change_count   , // 
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_1 enable"    *) input  wire                         s1_enable         , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_1 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s1_inc            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_1 dg_type"   *) input  wire [p_data_type_width-1:0] s1_type           , //
                                                                                    input  wire                  [31:0] s1_scaling_factor , //
                                                                                    input  wire                  [31:0] s1_offset         , //
                                                                                    input  wire                  [31:0] s1_clk_phase_hl   , //
                                                                                    input  wire                  [63:0] s1_din_p          , //
                                                                                    input  wire                  [63:0] s1_din_n          , //
                                                                                    // 
                                                                                    input  wire                   [7:0] s1_ds_ctrl          ,
                                                                                    output wire                  [31:0] s1_ds_fft_exec_cnt  ,
                                                                                    output wire                  [31:0] s1_ds_fft_max_level ,
                                                                                    output wire                   [7:0] s1_ds_status        ,
                                                                                    output wire                         s1_error          , //

                                                                                    input  wire    [p_change_width-1:0] s2_change_count   , // 
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_2 enable"    *) input  wire                         s2_enable         , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_2 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s2_inc            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_2 dg_type"   *) input  wire [p_data_type_width-1:0] s2_type           , //
                                                                                    input  wire                  [31:0] s2_scaling_factor , //
                                                                                    input  wire                  [31:0] s2_offset         , //
                                                                                    input  wire                  [31:0] s2_clk_phase_hl   , //
                                                                                    input  wire                  [63:0] s2_din_p          , //
                                                                                    input  wire                  [63:0] s2_din_n          , //
                                                                                    //
                                                                                    input  wire                   [7:0] s2_ds_ctrl          ,
                                                                                    output wire                  [31:0] s2_ds_fft_exec_cnt  ,
                                                                                    output wire                  [31:0] s2_ds_fft_max_level ,
                                                                                    output wire                   [7:0] s2_ds_status        ,
                                                                                    output wire                         s2_error          , //
 
                                                                                    input  wire    [p_change_width-1:0] s3_change_count   , // 
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_3 enable"    *) input  wire                         s3_enable         , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_3 dg_inc_i"  *) input  wire   [p_useable_width-1:0] s3_inc            , //
  (* X_INTERFACE_INFO = "xilinx.com:user:hsams_data_gen:1.0 dg_tile_3 dg_type"   *) input  wire [p_data_type_width-1:0] s3_type           , //
                                                                                    input  wire                  [31:0] s3_scaling_factor , //
                                                                                    input  wire                  [31:0] s3_offset         , //
                                                                                    input  wire                  [31:0] s3_clk_phase_hl   , //
                                                                                    input  wire                  [63:0] s3_din_p          , //
                                                                                    input  wire                  [63:0] s3_din_n          , //
                                                                                    // 
                                                                                    input  wire                   [7:0] s3_ds_ctrl          ,
                                                                                    output wire                  [31:0] s3_ds_fft_exec_cnt  ,
                                                                                    output wire                  [31:0] s3_ds_fft_max_level ,
                                                                                    output wire                   [7:0] s3_ds_status        ,
                                                                                    output wire                         s3_error          , //

  output reg  done=1, //
  input  wire clk_samp, //
  input  wire clk_fabric //
  
  );
 
//--------------------------------------------------------------------------
// Signal declarations
//--------------------------------------------------------------------------
wire [3:0] done_bus;

//--------------------------------------------------------------------------
// Create done signal
//--------------------------------------------------------------------------
always @(posedge clk_fabric)
   done <= &done_bus;

//--------------------------------------------------------------------------
// SLICE 0
//--------------------------------------------------------------------------
hsdac_ts_slice #(
   .p_connection_width (p_connection_width ),
   .p_data_inc_val_init(p_data_inc_val_init),
   .p_change_width     (p_change_width     ),
   .p_data_type_width  (p_data_type_width  ),
   .p_useable_width    (p_useable_width    )
) ds_slice_0_1 (
   .clk_samp        (clk_samp         ),
   .clk_fabric      (clk_fabric       ),
   .d_enable        (s0_enable        ),
   .d_inc           (s0_inc           ),
   .d_type          (s0_type          ),
   .d_change_count  (s0_change_count  ),
   .d_scaling_factor(s0_scaling_factor),
   .d_offset        (s0_offset        ),
   .d_clk_phase_hl  (s0_clk_phase_hl  ),
   .d_in_p          (s0_din_p         ),
   .d_in_n          (s0_din_n         ),
   // 
   .ds_ctrl          (s0_ds_ctrl         ) ,
   .ds_fft_exec_cnt  (s0_ds_fft_exec_cnt ) ,
   .ds_fft_max_level (s0_ds_fft_max_level) ,
   .ds_status        (s0_ds_status       ) ,
   .d_done          (done_bus[0]      ),
   .d_error         (s0_error         )
);

//--------------------------------------------------------------------------
// SLICE 1
//--------------------------------------------------------------------------
hsdac_ts_slice #(
   .p_connection_width (p_connection_width ),
   .p_data_inc_val_init(p_data_inc_val_init),
   .p_change_width     (p_change_width     ),
   .p_data_type_width  (p_data_type_width  ),
   .p_useable_width    (p_useable_width    )
) ds_slice_1_1 (
   .clk_samp        (clk_samp         ),
   .clk_fabric      (clk_fabric       ),
   .d_enable        (s1_enable        ),
   .d_inc           (s1_inc           ),
   .d_type          (s1_type          ),
   .d_change_count  (s1_change_count  ),
   .d_scaling_factor(s1_scaling_factor),
   .d_offset        (s1_offset        ),
   .d_clk_phase_hl  (s1_clk_phase_hl  ),
   .d_in_p          (s1_din_p         ),
   .d_in_n          (s1_din_n         ),
   //
   .ds_ctrl          (s1_ds_ctrl         ) ,
   .ds_fft_exec_cnt  (s1_ds_fft_exec_cnt ) ,
   .ds_fft_max_level (s1_ds_fft_max_level) ,
   .ds_status        (s1_ds_status       ) ,
   .d_done          (done_bus[1]      ),
   .d_error         (s1_error         )
);

//--------------------------------------------------------------------------
// SLICE 2
//--------------------------------------------------------------------------
hsdac_ts_slice #(
   .p_connection_width (p_connection_width ),
   .p_data_inc_val_init(p_data_inc_val_init),
   .p_change_width     (p_change_width     ),
   .p_data_type_width  (p_data_type_width  ),
   .p_useable_width    (p_useable_width    )
) ds_slice_2_1 (
   .clk_samp        (clk_samp         ),
   .clk_fabric      (clk_fabric       ),
   .d_enable        (s2_enable        ),
   .d_inc           (s2_inc           ),
   .d_type          (s2_type          ),
   .d_change_count  (s2_change_count  ),
   .d_scaling_factor(s2_scaling_factor),
   .d_offset        (s2_offset        ),
   .d_clk_phase_hl  (s2_clk_phase_hl  ),
   .d_in_p          (s2_din_p         ),
   .d_in_n          (s2_din_n         ),
   //
   .ds_ctrl          (s2_ds_ctrl         ) ,
   .ds_fft_exec_cnt  (s2_ds_fft_exec_cnt ) ,
   .ds_fft_max_level (s2_ds_fft_max_level) ,
   .ds_status        (s2_ds_status       ) ,
   .d_done          (done_bus[2]      ),
   .d_error         (s2_error         )
);

//--------------------------------------------------------------------------
// SLICE 3
//--------------------------------------------------------------------------
hsdac_ts_slice #(
   .p_connection_width (p_connection_width ),
   .p_data_inc_val_init(p_data_inc_val_init),
   .p_change_width     (p_change_width     ),
   .p_data_type_width  (p_data_type_width  ),
   .p_useable_width    (p_useable_width    )
) ds_slice_3_1 (
   .clk_samp        (clk_samp         ),
   .clk_fabric      (clk_fabric       ),
   .d_enable        (s3_enable        ),
   .d_inc           (s3_inc           ),
   .d_type          (s3_type          ),
   .d_change_count  (s3_change_count  ),
   .d_scaling_factor(s3_scaling_factor),
   .d_offset        (s3_offset        ),
   .d_clk_phase_hl  (s3_clk_phase_hl  ),
   .d_in_p          (s3_din_p         ),
   .d_in_n          (s3_din_n         ),
   //
   .ds_ctrl          (s3_ds_ctrl         ) ,
   .ds_fft_exec_cnt  (s3_ds_fft_exec_cnt ) ,
   .ds_fft_max_level (s3_ds_fft_max_level) ,
   .ds_status        (s3_ds_status       ) ,
   .d_done          (done_bus[3]      ),
   .d_error         (s3_error         )
);

endmodule

// ----------------------------------------------------------------------------
// Data sink slice
// ----------------------------------------------------------------------------
module hsdac_ts_slice #(
  parameter  p_connection_width  = 16,
  parameter  p_useable_width     = 14,
  parameter  p_change_width      = 16,
  parameter  p_data_inc_val_init = 1,
  parameter  p_data_type_width   = 1
) (

  input  wire                            d_enable         , //
  input  wire                            clk_samp         , //
  input  wire                            clk_fabric       , //
  input  wire      [p_useable_width-1:0] d_inc            , //
  input  wire    [p_data_type_width-1:0] d_type           , //
  input  wire       [p_change_width-1:0] d_change_count   , // 
  input  wire                     [31:0] d_scaling_factor , //
  input  wire                     [31:0] d_offset         , //
  input  wire                     [31:0] d_clk_phase_hl   , //

  input  wire                     [63:0] d_in_p           , //
  input  wire                     [63:0] d_in_n           , //
  //
  input  wire                    [7:0]   ds_ctrl          ,
  output wire                   [31:0]   ds_fft_exec_cnt  ,
  output wire                   [31:0]   ds_fft_max_level ,
  output wire                    [7:0]   ds_status        ,


  output wire                            d_done           , // 
  output wire                            d_error            //

  );

// ----------------------------------------------------------------------------
// Signal declarations
// ----------------------------------------------------------------------------
wire        change_clk;
wire [15:0] sample;
wire [15:0] sample_fs;

 hsdac_data_sink hsdac_data_sink_i(
 .scaling_factor  (d_scaling_factor), // real to int scaling factor
 .d_offset        (d_offset        ), // VCM offset
 .VIN_N           (d_in_n          ), // 
 .VIN_P           (d_in_p          ), // 
 .change_clk      (change_clk      ), // 
 .samp_fs         (sample_fs       ), // 
 .samp            (sample          )  // 
);


  // tie off unused axi register read ports
  assign ds_fft_exec_cnt  = 31'd0;
  assign ds_fft_max_level = 31'd0;
  assign ds_status        = 7'd0;

tb_dac_cell  #(
   .p_connection_width (p_connection_width ),
   .p_data_inc_val_init(p_data_inc_val_init),
   .p_data_type_width  (p_data_type_width  ),
   .p_useable_width    (p_useable_width    )
) tb_sink_cell(

  .enable         (d_enable        ), // 
  .clk            (change_clk      ), // 
  .ds_inc         (d_inc           ), // 
  .ds_change_count(d_change_count  ), //

  .ds_in          (sample          ), //
  .ds_done        (d_done          ),
  .error          (d_error         )  // 
);  


endmodule
// ----------------------------------------------------------------------------
// Convert the REAL signals to a n-bit code value 
// ----------------------------------------------------------------------------
module hsdac_data_sink #(
  parameter  p_connection_width  = 16,  // Data bus width
  parameter  p_useable_width     = 14,  // Usable subset of the data bus width
  parameter  p_useable_offset    = 0,   // Offset for useable width, use if 14-bit to 12 for example
  parameter  p_data_inc_val_init = 1,   // Default value for data increment
  parameter  p_data_type_width   = 1,   // Default TYPE for data testing
  parameter  p_data_default_type = 0    // Default data type, Triangle Wave
) (

 input  wire [31:0] scaling_factor , // real to int scaling factor
 input  wire [63:0] VIN_N          , // 
 input  wire [63:0] VIN_P          , // 
 input  wire [31:0] d_offset       , //

 output wire [15:0] samp           , // 
 output wire [15:0] samp_fs        , // 
 output reg         change_clk=0     // 

);

// Convert out reals, keep this verbose for debug
real    f64_VIN_N;        // 
real    f64_VIN_P;        //
real    f64_VIN_N_scaled; // 
real    f64_VIN_P_scaled; // 
integer s32_VIN_N;        // 
integer s32_VIN_N_dly;    // 
integer s32_VIN_P;        // 
integer s32_diff;         // 

real    dac_fs;            // recover full scale voltage
real    dac_fs_scaled;     // scale to codes, 2**16
integer dac_fs_scaled_int; // use for 16 bit truncation (possibly add over/under flow warnings)

always @(*) begin
   // Convert back to a real number
   f64_VIN_P        = $bitstoreal(VIN_P); 
   f64_VIN_N        = $bitstoreal(VIN_N); 
   // Scale the value to an integer acceptable code range
   f64_VIN_P_scaled = f64_VIN_P * scaling_factor;
   f64_VIN_N_scaled = f64_VIN_N * scaling_factor;
   // Convert to integer
   s32_VIN_P        = $rtoi(f64_VIN_P_scaled); 
   s32_VIN_N        = $rtoi(f64_VIN_N_scaled); 
   // Form output sample
   s32_diff         = s32_VIN_P - d_offset;
end
// Assign output
assign samp = s32_diff[15:0];

//------------------------------------------------------------------------------
// Create a 2's complement codes version of the real signal. 
// This assumes a fullscale on the DAC of 1V. Need to check this.
// Samp generation logic can be removed at some point
//------------------------------------------------------------------------------
always @(*) begin
   dac_fs            = (f64_VIN_P - f64_VIN_N) * 2; // To get full scale
   dac_fs_scaled     = dac_fs * 'h7fff;             // code conversion
   dac_fs_scaled_int = $rtoi(dac_fs_scaled);        // as INT
end

assign samp_fs = dac_fs_scaled_int[15:0];

//------------------------------------------------------------------------------
// Generate a sample clock based on signal change
//------------------------------------------------------------------------------
always @(VIN_P) begin
   change_clk = 0;
   #20 change_clk = 1;
end

endmodule

// ----------------------------------------------------------------------------
// Self checking module
// ----------------------------------------------------------------------------
module tb_dac_cell #(
  parameter  p_connection_width  = 16,  // Data bus width
  parameter  p_change_width      = 16,  // Width of change counter
  parameter  p_useable_width     = 14,  // Usable subset of the data bus width
  parameter  p_useable_offset    = 0,   // Offset for useable width, use if 14-bit to 12 for example
  parameter  p_data_inc_val_init = 1,   // Default value for data increment
  parameter  p_data_type_width   = 1,   // Default TYPE for data testing
  parameter  p_data_default_type = 0    // Default data type, Triangle Wave
) (

  input  wire                           enable          , // 
  input  wire                           clk             , // 
  input  wire     [p_useable_width-1:0] ds_inc          , // 
  input  wire      [p_change_width-1:0] ds_change_count , // 

  input        [p_connection_width-1:0] ds_in           , //
  output reg                            ds_done=1       , // Done flag
  output reg                            error=0           // Error flag
  
  );
  
// ----------------------------------------------------------------------------
// local params
// ----------------------------------------------------------------------------
localparam map_bit_max  = p_useable_width + p_useable_offset; 
localparam CHECK_IDLE   = 7'd0;
localparam CHECK_LOCKED = 7'h7F;
  
// ----------------------------------------------------------------------------
// local variables
// ----------------------------------------------------------------------------

wire [p_useable_width-1:0] din_remapped_curr;  // Remap the incoming data bus (IPI EOU)
reg  [p_useable_width-1:0] din_remapped_last;  // Copy of previous data for diff
reg  [p_useable_width:0]   difference   = {p_useable_width+1{1'd0}}; // Holds the difference
reg  [p_useable_width:0]   last_m_curr  = {p_useable_width+1{1'd0}}; // last data minus current
reg  [p_useable_width:0]   curr_m_last  = {p_useable_width+1{1'd0}}; // Current data minus last
reg                  [6:0] check_status = CHECK_IDLE; // Hold of check at startup 
reg  [p_useable_width-1:0] ds_inc_int   = p_data_inc_val_init; // Reg for timing
reg   [p_change_width-1:0] change_counter =0; // 
reg                        ds_int =0;         // Internal done signal
wire lmc_is_neg ; // Last minus current is negative flag
wire lmc_is_zero; // Last minus current is Zero flag
wire cml_is_neg ; // Current minus last is negative flag
wire cml_is_zero; // Current minus last is Zero flag

// ----------------------------------------------------------------------------
// Allow for wider data input widths and select sub section for testing
// This is useful in IPI, allowing bus connections to be simply conected
// ----------------------------------------------------------------------------
assign din_remapped_curr = ds_in[map_bit_max-1 : p_useable_offset];

// ----------------------------------------------------------------------------
// Pos/Neg/Zero indicator flags
// ----------------------------------------------------------------------------
assign lmc_is_neg  = last_m_curr[p_useable_width];
assign lmc_is_zero = last_m_curr=={p_useable_width+1{1'd0}};
assign cml_is_neg  = curr_m_last[p_useable_width];
assign cml_is_zero = curr_m_last=={p_useable_width+1{1'd0}};

// ----------------------------------------------------------------------------
// register inputs for timing/fanout
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   ds_inc_int <= ds_inc;

   // create our difference values, one will be -ve and one +ve
   // This can freerun
   curr_m_last <= din_remapped_curr - din_remapped_last;
   last_m_curr <= din_remapped_last - din_remapped_curr;

   // Always update the last data
   din_remapped_last <= din_remapped_curr;

end

// ----------------------------------------------------------------------------
// Change counter, used to stop test
// Done is reset high as if the channel is deselected no clock will appear as
// we generate a pseudo recovered clock from signal change events
// We also need to look as posedge of enable as this can occur before we see
// a recovered clock.
// ----------------------------------------------------------------------------
always @(posedge clk or posedge enable) begin
   if(~enable) begin
      change_counter <= {p_change_width{1'd0}};
      ds_done        <= 1'd1;
      ds_int         <= 1'd0;
   end else begin
      if (din_remapped_last != din_remapped_curr)
         change_counter <= change_counter + {{p_change_width-1{1'd0}},1'd1};
      else 
         change_counter <= change_counter;

      // This is sticky, first time seem, keep high, unless disabled
      ds_done <= ds_int;
      if (change_counter == ds_change_count) 
         ds_int <= 1'd1;
   end
end

// ----------------------------------------------------------------------------
// Conditional checking registered logic.
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   if(enable) begin
      // update the difference dependent on the flags, i.e. which is not -ve
      // Zero difference is also not updated as some waveforms intentionally
      // pause at max/min value
      case ({cml_is_neg,lmc_is_zero,cml_is_zero})
      3'b000 : difference <= curr_m_last;
      3'b001 : difference <= curr_m_last;
      3'b010 : difference <= difference;
      3'b011 : difference <= difference;
      3'b100 : difference <= last_m_curr;
      3'b101 : difference <= difference;
      3'b110 : difference <= last_m_curr;
      3'b111 : difference <= difference;
      endcase
      
      // Flag to hold off error check until we have multiple past values
      // This masks abnormalities at startup, which for this checker are not
      // valid.
      if(check_status == CHECK_LOCKED) begin
         // The error is based on a power of two check mask. Low resource 
         // check for large jumps. The input data must be compatable with this
         // check. A triangle wave is recomnded, though a SINE wave can work 
         // as well. 
         // Ramps will cause an error, Useful for testing the error mechanism.
         error        <= |(difference&(~ds_inc_int));
         check_status <= check_status;
      end else begin
         error        <= 1'd0;
         check_status <= check_status + 7'd1;
      end
      
   end else begin
      error        <= 1'd0;
      check_status <= CHECK_IDLE;
   end
end

endmodule


