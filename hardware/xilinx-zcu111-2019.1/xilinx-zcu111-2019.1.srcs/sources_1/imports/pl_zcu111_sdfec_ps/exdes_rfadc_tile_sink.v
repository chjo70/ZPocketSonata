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
`timescale 1ns / 1ps

// ----------------------------------------------------------------------------
// IQ data sink tile
// ----------------------------------------------------------------------------
(* X_INTERFACE_PRIORITY_LIST = "xilinx.com:user:hsams_data_sink_ctrl:1.0" *)
(* DowngradeIPIdentifiedWarnings="yes" *)
module ds_slice #(

  parameter  p_cons          = 16,    // axis word width (gui default = 8)
  parameter  p_con_w         = 12,    // bits per axis word (default = 16)
  parameter  p_useable_w     = 12,
  parameter  p_increment_w   = 12,
  parameter  p_data_type_w   = 3, 
  parameter  p_change_w      = 8

) (

  input  wire                         clk            , //
  input  wire            [p_cons-1:0] ds_enable      , //
  input  wire     [p_increment_w-1:0] ds_inc         , //
  input  wire     [p_data_type_w-1:0] ds_type        , //
  input  wire        [p_change_w-1:0] ds_change_count, //
  input  wire  [(p_con_w*p_cons)-1:0] ds_in          , //     
  output reg                          ds_done=0      , //
  output reg                          ds_error=0       //
  
  );

// ----------------------------------------------------------------------------
// Internal done bus, register single bit output
// ----------------------------------------------------------------------------
wire [p_cons-1:0] ds_done_bus;  // 
wire [p_cons-1:0] ds_error_bus; // 

always @(posedge clk) begin
   ds_done  <= &ds_done_bus;
   ds_error <= |ds_error_bus;
end


// ----------------------------------------------------------------------------
// IQ data sinks, generate as IQ pairs
// ----------------------------------------------------------------------------
genvar i;
generate
   for (i=0; i<p_cons; i=i+1) begin : dg_cell
      ds_cell #(
         .p_con_w         ( p_con_w       ),
         .p_useable_w     ( p_useable_w   ),
         .p_increment_w   ( p_increment_w ),
         .p_data_type_w   ( p_data_type_w ),
         .p_change_w      ( p_change_w    )
      ) dg_cell_i_i (
         .clk             (clk                ),
         .ds_enable       (ds_enable[(i)]     ),
         .ds_inc          (ds_inc             ),
         .ds_type         (ds_type            ),
         .ds_change_count (ds_change_count    ),
         .ds_done         (ds_done_bus[(i)]   ),
         .ds_error        (ds_error_bus[(i)]  ),
         .ds_in           (ds_in[(p_con_w*(i+1))-1:(p_con_w*(i))])
      );
end 
endgenerate
endmodule

// ----------------------------------------------------------------------------
// Data sink cell. 
// ----------------------------------------------------------------------------
module ds_cell #(

  parameter  p_con_w         = 12, // Data bus width
  parameter  p_useable_w     = 12, // Usable subset of the data bus width
  parameter  p_increment_w   = 12, 
  parameter  p_data_type_w   = 3,  // Default TYPE for data testing
  parameter  p_change_w      = 8   // Change counter width. 

) (

  input  wire                       clk            , // 
  input  wire                       ds_enable      , // 
  input  wire   [p_increment_w-1:0] ds_inc         , //   
  input  wire   [p_data_type_w-1:0] ds_type        , //
  input  wire      [p_change_w-1:0] ds_change_count, //

  input               [p_con_w-1:0] ds_in          , //
  output reg                        ds_done=0      , //
  output reg                        ds_error=0        
  
  );
  
// ----------------------------------------------------------------------------
// local params
// ----------------------------------------------------------------------------
localparam p_data_default_type = 0; // Default data type, Triangle Wave
localparam p_data_inc_val_init = 1; // Default value for data increment
localparam p_useable_offset    = 0; // Offset for useable width
localparam map_bit_max  = p_useable_w + p_useable_offset; 
localparam CHECK_IDLE   = 4'h0;
localparam CHECK_LOCKED = 4'hf;
localparam p_inc_stuff  = p_con_w - p_increment_w;
localparam half_range   = (2**p_useable_w)>>1;

// ----------------------------------------------------------------------------
// local variables
// ----------------------------------------------------------------------------
reg         [p_con_w-1:0]     din_r            = 0;// Remap the incoming data bus (IPI EOU)
reg         [p_data_type_w-1:0] ds_type_r      = 0; // register
reg         [p_useable_w-1:0] ds_inc_r         = p_data_inc_val_init; // Register for timing
reg signed  [p_useable_w-1:0] din_remapped_curr= 0;// Remap the incoming data bus (IPI EOU)
reg signed  [p_useable_w-1:0] din_remapped_last= 0;// Copy of previous data for diff
reg signed  [p_useable_w:0]   curr_m_last      = {p_useable_w+1{1'd0}}; // Current data minus last
reg         [p_useable_w:0]   difference       = 0;
reg         [p_change_w-1:0] change_counter    = 0; // 
reg                          ds_done_internal  = 0; // Internal done signal
reg                          ds_error_pre      = 0; // register the error detection decision
reg                          ds_error_mask     = 0; // register the error masking decision
reg                          ds_enable_r       = 0; // register the enable
reg                          ds_data_seen      = 0; // sticky register to indicate data has been seen
reg                    [2:0] startupcount      = 0; // allow incoming high bit data count
      
reg                          last_pos_input    = 1'b0;
reg                          last_neg_input    = 1'b0;
// ----------------------------------------------------------------------------
// Wave types
// ----------------------------------------------------------------------------
localparam DGTYPE_TRGL      = 'd0;
localparam DGTYPE_TRGL_S    = 'd1;
localparam DGTYPE_RAMPUP    = 'd2;
localparam DGTYPE_RAMPDOWN  = 'd3;
localparam DGTYPE_SINEM     = 'd4; // Sine in the MS bits
localparam DGTYPE_SINEL     = 'd5; // Sine ine the LS bits

// ----------------------------------------------------------------------------
// Allow for wider data input widths and select sub section for testing
// This is useful in IPI, allowing bus connections to be simply connected
// Register this path to highlight any timing model issues
// Note the offsest will be applicable to msb or lsb on incoming data word.
// register inputs for timing/fanout
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   din_r       <= ds_in;
   ds_type_r   <= ds_type;
   ds_inc_r    <= {{p_inc_stuff{1'b0}},ds_inc};
   ds_enable_r <= ds_enable;
end

// ----------------------------------------------------------------------------
// Calculate the difference from current to previous & store current
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   curr_m_last       <= din_remapped_curr - din_remapped_last;
   din_remapped_last <= din_remapped_curr;
end

// ----------------------------------------------------------------------------
always @(posedge clk) begin
      din_remapped_curr <=  din_r[map_bit_max-1 : p_useable_offset];
end

// ----------------------------------------------------------------------------
// Change counter should only increment when the checker is enabled and 
// data is in a valid state. There is no way for the ADC to signal that the
// data being output should be correct, this judgement is up to the 
// downstream logic (in our case this checker) based on either a delay or the
// type of signal it is being fed.
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   if(~ds_enable_r | ~ds_data_seen) begin
      change_counter   <= {p_change_w{1'd0}};
   end else begin
      if (din_remapped_last != din_remapped_curr)
         change_counter <= change_counter + {{p_change_w-1{1'd0}},1'd1};
      else 
         change_counter <= change_counter;
   end
end

// ----------------------------------------------------------------------------
// If disabled a checker is marked done so check mechanism only has to look
// for an OR of all the done flags at the checker top level.
// As soon as its enabled it will go low only returning high when 
// A rising edge on done indicates that this checker is complete, i.e. seen 
// the number of transition is was asked to monitor.
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   if(~ds_enable_r) begin

      ds_done          <= 1'd1;
      ds_done_internal <= 1'd0;

   end else begin

      // This is sticky, first time seen, keep high, unless disabled
      ds_done <= ds_done_internal;
      if (change_counter == ds_change_count) 
         ds_done_internal <= 1'd1;

   end
end

// ----------------------------------------------------------------------------
// If the differrence result is -ve flip it, we dont bother adding the one
// We only have a power of 2 mask check so should be within bounds, or its an
// error
// ----------------------------------------------------------------------------
always @ (*) begin
   if(curr_m_last[p_useable_w])
      difference = ~curr_m_last;
   else 
      difference = curr_m_last;
end

// ----------------------------------------------------------------------------
// Conditional checking registered logic.
// ----------------------------------------------------------------------------

wire neg_input;
wire pos_input;

assign neg_input = ((din_r[p_con_w-1] == 1'b1) && (din_r[p_con_w-1:p_con_w-8] < 8'hfe)) ;
assign pos_input = ((din_r[p_con_w-1] == 1'b0) && (din_r[p_con_w-1:0] > 8'h80)) ;

always @(posedge clk) begin
   if(ds_enable_r) begin

      // detect transitions around 0, and inc a counter
      if ((pos_input) && (~last_pos_input))
         begin
           startupcount <= startupcount + 3'd1;
           last_pos_input <= 1'b1;
           last_neg_input <= 1'b0;
         end
      else if ((neg_input) && (~last_neg_input))
         begin
           startupcount <= startupcount + 3'd1;
           last_neg_input <= 1'b1;
           last_pos_input <= 1'b0;
         end

      // Flag to hold off error check until we have multiple past values
      // This masks abnormalities at startup, which for this checker are not
      // valid.
      if(ds_data_seen) begin
         // The error is based on a power of two check mask. Low resource 
         // check for large jumps. The input data must be compatable with this
         // check. A triangle wave is recommended, though a SINE wave can work 
         // as well. 
         // Ramps will cause an error, Useful for testing the error mechanism.
         // 
         // ds_error_pre indicate individual error is detected
         ds_error_pre  <= |(difference&(~ds_inc_r));
         ds_error_mask <= (ds_type_r != DGTYPE_TRGL_S);
         // latch ds_error when an data error is seen, otherwise errors can be missed
         if (ds_error_pre & (~ds_error_mask))
           ds_error      <= 1'b1;
      end else begin
         ds_error     <= 1'd0;
      end

      if (~ds_data_seen & startupcount[2])
         ds_data_seen <= 1'd1;

   end else begin
      startupcount   <= 3'd0;
      ds_error_pre   <= 1'd0;
      ds_error_mask  <= 1'b0;
      ds_error       <= 1'd0;
      ds_data_seen   <= 1'b0;
      last_neg_input <= 1'b0;
      last_pos_input <= 1'b0;
   end
end

endmodule
