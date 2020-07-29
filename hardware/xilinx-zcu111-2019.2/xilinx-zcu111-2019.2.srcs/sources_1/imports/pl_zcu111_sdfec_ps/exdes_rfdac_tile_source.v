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
`timescale 1ps / 1ps

//`define EXCLUDE_SINE_WAVE_LUTS

// ----------------------------------------------------------------------------
// Data generator slice
// This block is a demonstration block and heavily pipelined to prevent any
// timing issue with the main AMS IP.
// ----------------------------------------------------------------------------
(* X_INTERFACE_PRIORITY_LIST = "xilinx.com:user:hsams_data_source_ctrl:1.0" *)
(* DowngradeIPIdentifiedWarnings="yes" *)
module dg_slice #(
  // User modifable
  parameter  p_cons          = 16,
  parameter  p_con_w         = 12,
  parameter  p_useable_w     = 12,
  parameter  p_increment_w   = 12,
  parameter  p_data_type_w   = 3, 
  parameter  p_lut_addr_w    = 7
) (

  input  wire                         clk      ,  //
  input  wire            [p_cons-1:0] dg_enable,  //
  input  wire     [p_increment_w-1:0] dg_inc   ,  //
  input  wire  [(p_cons*p_con_w)-1:0] dg_init  ,  //
  input  wire     [p_data_type_w-1:0] dg_type  ,  // 
  input  wire                   [7:0] dg_control, // 

  input wire                          dg_tready,  //
  output reg                          dg_tvalid=0,//
  output wire  [(p_cons*p_con_w)-1:0] dg_tdata    //

);

//--------------------------------------------------------------------------
// Declarations
//--------------------------------------------------------------------------
reg  [p_cons-1:0] dg_enable_int=0; //

//--------------------------------------------------------------------------
// Generate tready and internal enables to slices
//--------------------------------------------------------------------------
always @(posedge clk)
   begin
   dg_tvalid     <= |dg_enable;
   dg_enable_int <= dg_enable & {p_con_w{dg_tready}};
   end


// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
genvar i;
generate
   for (i=0; i<p_cons; i=i+1) begin : dg_cell
      dg_cell #(
         .p_con_w        ( p_con_w ),
         .p_useable_w    ( p_useable_w    ),
         .p_increment_w  ( p_increment_w  ),
         .p_data_type_w  ( p_data_type_w  ),
         .p_lut_addr_w   ( p_lut_addr_w   )
      ) dg_cell_i (
         .clk       (clk                ),
         .dg_enable (dg_enable_int[i]   ),
         .dg_inc    (dg_inc             ),
         .dg_type   (dg_type            ),
         .dg_control(dg_control         ),
         .dg_init   (dg_init [(p_con_w*(i+1))-1:(p_con_w*i)]),
         .dg_out    (dg_tdata[(p_con_w*(i+1))-1:(p_con_w*i)])
      );
end 
endgenerate

endmodule

// ----------------------------------------------------------------------------
// Generic data generator. Capable of ramps, sine and other waves.
// Programmable increment
// ----------------------------------------------------------------------------
module dg_cell #(

  parameter  p_con_w       = 12,
  parameter  p_useable_w   = 12,
  parameter  p_increment_w = 12,
  parameter  p_data_type_w = 3, 
  parameter  p_lut_addr_w  = 7

) (

  input  wire                     clk      , // 
  input  wire                     dg_enable, // 
  input  wire [p_increment_w-1:0] dg_inc   , // 
  input  wire       [p_con_w-1:0] dg_init  , // 
  input  wire [p_data_type_w-1:0] dg_type  , // 
  input  wire               [7:0] dg_control,// 
  output wire       [p_con_w-1:0] dg_out     //     
  
  );
  
// ----------------------------------------------------------------------------
// local params
// ----------------------------------------------------------------------------
localparam p_value_one         = 1;
localparam p_msb_stuff         = p_con_w - p_useable_w;
localparam p_inc_stuff         = p_con_w - p_increment_w;
localparam p_inc_default_type  = 1;  
localparam p_data_default_type = 0;
localparam p_cnt_msb           = p_useable_w-1;
localparam p_halfValue         = 2 ** (p_con_w - 1);
localparam p_pause_w           = 3;

// Wave types
localparam DGTYPE_TRGL         = 'd0;
localparam DGTYPE_TRGL_S       = 'd1;
localparam DGTYPE_RAMPUP       = 'd2;
localparam DGTYPE_RAMPDOWN     = 'd3;
localparam DGTYPE_SINEM        = 'd4;
localparam DGTYPE_SINEL        = 'd5;
localparam DGTYPE_SQR          = 'd6;
  
// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------
reg [p_data_type_w-1:0] dg_type_r = p_data_default_type; //
reg [p_increment_w-1:0] dg_inc_r  = p_inc_default_type;  //
reg               [7:0] dg_control_r= 0;  // Output modifier controls
reg         [p_con_w:0] dg_modify_r = 0;  // modify output
reg         [p_con_w:0] dg_out_r  = 0;    // selected output register
reg       [p_cnt_msb:0] counter   = 0;    // main counter register
reg                     updown    = 1'd1; // flag for count direction
wire                    overflow;         // flag for max next count
wire    [p_useable_w:0] value_one;        // 1 as counter width
wire    [p_useable_w:0] inc_by;           // zero stuff inc val to counter width
wire    [p_useable_w:0] inc_by_2sC;       // 2s complement on inc_by
reg     [p_useable_w:0] inc_by_2sC_r=0;   // register this inc
wire    [p_useable_w:0] inc_by_sel;       // selected inc value based on upDown
reg     [p_useable_w:0] inc_by_sel_r=0;   // register inc_by_sel
wire      [p_cnt_msb:0] increment_by;     // inc value for counter
wire      [p_cnt_msb:0] sine_value;       // wire from LUT with sine wave
reg     [p_pause_w-1:0] pause=0;          // pause at rollover
reg                     overflow_r=0;     // register overflow
wire                    overflow_i;

// ----------------------------------------------------------------------------
// register control locally
// ----------------------------------------------------------------------------
always @(posedge clk) begin
   dg_inc_r     <= dg_inc;
   dg_type_r    <= dg_type;
   dg_control_r <= dg_control;
end

// ----------------------------------------------------------------------------
// Assignments to generate increment_by value and overflow control signal
// updown = 1 = count up
// updown = 0 = count down
// ----------------------------------------------------------------------------
assign value_one  = p_value_one;
assign inc_by     =   {{p_inc_stuff{1'd0}},dg_inc_r};
assign inc_by_2sC = (~{{p_inc_stuff{1'd0}},dg_inc_r}) + value_one;
assign inc_by_sel = updown ? inc_by : inc_by_2sC_r;

assign {overflow, increment_by} = {1'd0,{counter}} + inc_by_sel;

assign overflow_i = (dg_type_r == DGTYPE_TRGL || dg_type_r == DGTYPE_TRGL_S) ? overflow_r : 1'b0;

// ----------------------------------------------------------------------------
// counter control
// ----------------------------------------------------------------------------
always @(posedge clk) begin

   inc_by_sel_r <= inc_by_sel;
   pause        <= {pause[p_pause_w-2:0], 1'b0}; // Always clear pause
   inc_by_2sC_r <= inc_by_2sC;
   updown       <= updown;

   // Overflow logic only needs to be used for triangle waves. In all other 
   // modes output can be free running. For triangle generation, the pause 
   // allows for the loading of inverse count value. 
   overflow_r   <= overflow;

   if(dg_enable) begin
      counter <= increment_by;
   end else begin
      counter <= dg_init;
   end

   if((~(|pause))) begin
      // When pause shift reg is clear and we detect an overflow load the 
      // register. Overflow is only used for triangle waves to change the
      // count direction
      pause[0] <= overflow_i;
   end
 
   // Up/down direction count flags.
   case (dg_type_r)
      DGTYPE_TRGL     : case({(overflow_i & (~(|pause))),updown})
                           2'b10   : updown <= 1'd1;
                           2'b11   : updown <= 1'd0;
                           default : updown <= updown;
                        endcase
      DGTYPE_TRGL_S   : case({(overflow_i & (~(|pause))),updown})
                           2'b10   : updown <= 1'd1;
                           2'b11   : updown <= 1'd0;
                           default : updown <= updown;
                        endcase
      DGTYPE_RAMPDOWN : updown <= 1'd0;
      default         : updown <= 1'd1;
   endcase

end

// ----------------------------------------------------------------------------
// Register value to be output based on the wave selection
// ----------------------------------------------------------------------------
always @(posedge clk) begin

   if(~(|pause|overflow_i)) begin
      // OUTPUT selection control. SINE waves come from the LUT's with the
      // counter used to address the LUT. Counter used for ramp generation
      casex (dg_type_r)
      DGTYPE_SINEM : dg_out_r <= {{p_msb_stuff{1'd0}}, sine_value};
      DGTYPE_SINEL : dg_out_r <= {sine_value, {p_msb_stuff{1'd0}}};
      DGTYPE_TRGL_S: dg_out_r <= {{p_msb_stuff{1'd0}}, counter} - p_halfValue;
      DGTYPE_SQR   : if (!counter[15])
                        dg_out_r <= {{p_msb_stuff{1'd0}}, 16'h7fff};  // max +ve
                     else
                        dg_out_r <= {{p_msb_stuff{1'd0}}, 16'h8000};  // max -ve
      default      : dg_out_r <= {{p_msb_stuff{1'd0}}, counter};
      endcase 
      
   end else begin
      // Default 
      dg_out_r <= dg_out_r;
   end
end

// ----------------------------------------------------------------------------
// modify output
// The lower 4 bits of control are used as dividers, 2,4,8,16 using a sign
// extended right shift. Recall register is 1 bit breater that output so 
// 8 7 6 5 4 3 2 1 0  // Unshifted normal output
// 7 7 7 6 5 4 3 2 1  // >> 1 = divide by 2
// 7 7 7 7 6 5 4 3 2  // >> 2 = divide by 4
// ----------------------------------------------------------------------------
always @(posedge clk) begin

   casex (dg_control_r[3:0])
   4'bxxx1 : dg_modify_r <= {{2{dg_out_r[p_con_w-1]}}, dg_out_r[p_con_w-1:1]};
   4'bxx1x : dg_modify_r <= {{3{dg_out_r[p_con_w-1]}}, dg_out_r[p_con_w-1:2]};
   4'bx1xx : dg_modify_r <= {{4{dg_out_r[p_con_w-1]}}, dg_out_r[p_con_w-1:3]};
   4'b1xxx : dg_modify_r <= {{5{dg_out_r[p_con_w-1]}}, dg_out_r[p_con_w-1:4]};
   default : dg_modify_r <= dg_out_r;
   endcase

end

// Block output, slice the register
assign dg_out = dg_modify_r[p_con_w-1:0];

// ----------------------------------------------------------------------------
// Instance the SINE wave LUT
// ----------------------------------------------------------------------------
`ifdef EXCLUDE_SINE_WAVE_LUTS
assign sine_value = {p_useable_w{1'd0}};
`else
exdes_rfdac_sine_wave_lut sine0_lut (
   .sine_value ( sine_value                ), 
   .address    ( counter[p_lut_addr_w-1:0] )
);
`endif

endmodule
