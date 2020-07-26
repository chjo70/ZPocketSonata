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

// Uncomment the line below to allow signal type selection via the AXI interface
// This also enables full control over the initial start values for the generation counters
`define DACEXDES_ENABLETYPE_SELECTION
//`define EXDES_DAC_RAM_SOURCE
`ifdef EXDES_DAC_RAM_SOURCE
   // Undef this when using the DAC RAM source.
   `undef DACEXDES_ENABLETYPE_SELECTION
`endif

(* DowngradeIPIdentifiedWarnings="yes" *)
module exdes_rfdac_data_source #(
  
  parameter  enable_override          = 1'd1, // 

  parameter  default_signal_type      = 4'h4, //
  parameter  initial_interword_offset = 1     // 

) (

   // AXI-Lite Interface
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWADDR"  *) input  wire [17:0] s_axi_awaddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWVALID" *) input  wire        s_axi_awvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWREADY" *) output wire        s_axi_awready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WDATA"   *) input  wire [31:0] s_axi_wdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WVALID"  *) input  wire        s_axi_wvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WREADY"  *) output wire        s_axi_wready   , //
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WSTRB"   *) input  wire  [3:0] s_axi_wstrb    , //
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BRESP"   *) output wire  [1:0] s_axi_bresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BVALID"  *) output wire        s_axi_bvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BREADY"  *) input  wire        s_axi_bready   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARADDR"  *) input  wire [17:0] s_axi_araddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARVALID" *) input  wire        s_axi_arvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARREADY" *) output wire        s_axi_arready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RDATA"   *) output wire [31:0] s_axi_rdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RRESP"   *) output wire  [1:0] s_axi_rresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RVALID"  *) output wire        s_axi_rvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RREADY"  *) input  wire        s_axi_rready   , // 

   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m00 TDATA" *)       output wire [255:0] m00_tdata ,     //
   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m00 TVALID" *)      output wire         m00_tvalid,     //
   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m00 TREADY" *)      input  wire         m00_tready,     //

   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m01 TDATA" *)       output wire [255:0] m01_tdata ,     //
   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m01 TVALID" *)      output wire         m01_tvalid,     //
   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 m01 TREADY" *)      input  wire         m01_tready,     //


   (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 m0_axis_clock CLK" *)
   (* X_INTERFACE_PARAMETER = "ASSOCIATED_BUSIF m00:m01" *)
   input  wire           m0_axis_clock, //
   // AXI-Lite Clock/Reset. Be explicit with the IPI interface declarations
   (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s_axi_aclk CLK" *)
   (* X_INTERFACE_PARAMETER = "ASSOCIATED_BUSIF s_axi" *)
   input  wire           s_axi_aclk   ,
   (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 s_axi_aresetn RST" *)
   (* X_INTERFACE_PARAMETER = "POLARITY ACTIVE_LOW" *)
   input  wire           s_axi_aresetn
  
  );

// ----------------------------------------------------------------------------
// Local params
// ----------------------------------------------------------------------------
localparam  p_useable_w         = 16; // 
localparam  p_increment_w       = 7;  // 
localparam  p_data_inc_val_init = 1;  // 
localparam  p_data_type_width   = 4;  // 
localparam  p_init_incval       = 8;  // 
localparam  p_con_w             = 16; // 

// ----------------------------------------------------------------------------
// Wire declarations
// ----------------------------------------------------------------------------
wire                            enable;
wire                            timeout_enable;
wire                     [11:0] timeout_value;
wire                     [3:0] axis_resetn_rt;
wire                     [15:0] m00_dg_enable; //
wire                      [7:0] m00_dg_control;//
wire        [p_increment_w-1:0] m00_dg_inc   ; //
wire                    [255:0] m00_dg_init  ; //
wire                    [255:0] m00_dg_init_i; //
wire    [p_data_type_width-1:0] m00_dg_type  ; //

wire                            m00_dg_pulse_control_0;//
wire                     [15:0] m00_dg_i_value_0      ;//
wire                     [15:0] m00_dg_q_value_0      ;//
wire                      [2:0] m00_dg_mult_control_0 ;//

wire                     [15:0] m01_dg_enable; //
wire                      [7:0] m01_dg_control;//
wire        [p_increment_w-1:0] m01_dg_inc   ; //
wire                    [255:0] m01_dg_init  ; //
wire                    [255:0] m01_dg_init_i; //
wire    [p_data_type_width-1:0] m01_dg_type  ; //

wire                            m01_dg_pulse_control_0;//
wire                     [15:0] m01_dg_i_value_0      ;//
wire                     [15:0] m01_dg_q_value_0      ;//
wire                      [2:0] m01_dg_mult_control_0 ;//


`ifndef DACEXDES_ENABLETYPE_SELECTION
assign m00_dg_init[(16* 1) - 1 : (16* 0)]  =  0 * initial_interword_offset;
assign m00_dg_init[(16* 2) - 1 : (16* 1)]  =  1 * initial_interword_offset;
assign m00_dg_init[(16* 3) - 1 : (16* 2)]  =  2 * initial_interword_offset;
assign m00_dg_init[(16* 4) - 1 : (16* 3)]  =  3 * initial_interword_offset;
assign m00_dg_init[(16* 5) - 1 : (16* 4)]  =  4 * initial_interword_offset;
assign m00_dg_init[(16* 6) - 1 : (16* 5)]  =  5 * initial_interword_offset;
assign m00_dg_init[(16* 7) - 1 : (16* 6)]  =  6 * initial_interword_offset;
assign m00_dg_init[(16* 8) - 1 : (16* 7)]  =  7 * initial_interword_offset;
assign m00_dg_init[(16* 9) - 1 : (16* 8)]  =  8 * initial_interword_offset;
assign m00_dg_init[(16*10) - 1 : (16* 9)]  =  9 * initial_interword_offset;
assign m00_dg_init[(16*11) - 1 : (16*10)]  = 10 * initial_interword_offset;
assign m00_dg_init[(16*12) - 1 : (16*11)]  = 11 * initial_interword_offset;
assign m00_dg_init[(16*13) - 1 : (16*12)]  = 12 * initial_interword_offset;
assign m00_dg_init[(16*14) - 1 : (16*13)]  = 13 * initial_interword_offset;
assign m00_dg_init[(16*15) - 1 : (16*14)]  = 14 * initial_interword_offset;
assign m00_dg_init[(16*16) - 1 : (16*15)]  = 15 * initial_interword_offset;
//assign m00_dg_init = { 16'd0, 16'd4, 16'd8, 16'd12, 16'd16, 16'd20, 16'd24, 16'd28, 16'd32, 16'd36, 16'd40, 16'd44, 16'd48, 16'd52, 16'd56, 16'd60 };
assign m01_dg_init[(16* 1) - 1 : (16* 0)]  =  0 * initial_interword_offset;
assign m01_dg_init[(16* 2) - 1 : (16* 1)]  =  1 * initial_interword_offset;
assign m01_dg_init[(16* 3) - 1 : (16* 2)]  =  2 * initial_interword_offset;
assign m01_dg_init[(16* 4) - 1 : (16* 3)]  =  3 * initial_interword_offset;
assign m01_dg_init[(16* 5) - 1 : (16* 4)]  =  4 * initial_interword_offset;
assign m01_dg_init[(16* 6) - 1 : (16* 5)]  =  5 * initial_interword_offset;
assign m01_dg_init[(16* 7) - 1 : (16* 6)]  =  6 * initial_interword_offset;
assign m01_dg_init[(16* 8) - 1 : (16* 7)]  =  7 * initial_interword_offset;
assign m01_dg_init[(16* 9) - 1 : (16* 8)]  =  8 * initial_interword_offset;
assign m01_dg_init[(16*10) - 1 : (16* 9)]  =  9 * initial_interword_offset;
assign m01_dg_init[(16*11) - 1 : (16*10)]  = 10 * initial_interword_offset;
assign m01_dg_init[(16*12) - 1 : (16*11)]  = 11 * initial_interword_offset;
assign m01_dg_init[(16*13) - 1 : (16*12)]  = 12 * initial_interword_offset;
assign m01_dg_init[(16*14) - 1 : (16*13)]  = 13 * initial_interword_offset;
assign m01_dg_init[(16*15) - 1 : (16*14)]  = 14 * initial_interword_offset;
assign m01_dg_init[(16*16) - 1 : (16*15)]  = 15 * initial_interword_offset;
//assign m01_dg_init = { 16'd0, 16'd4, 16'd8, 16'd12, 16'd16, 16'd20, 16'd24, 16'd28, 16'd32, 16'd36, 16'd40, 16'd44, 16'd48, 16'd52, 16'd56, 16'd60 };
`endif

`ifdef EXDES_DAC_RAM_SOURCE
xpm_mem_dg #(
   
  .wordWidth     (256),
  .addrWidth     (7)

) dg_slice_00 (

   .clk       ( m0_axis_clock    ),
   .enable    ( m00_dg_enable[15:0] | {16{enable_override}}),

   .addra     ( m00_dg_inc             ),
   .wea       ( m00_dg_pulse_control_0 ),
   .dina      ( m00_dg_init            ),

   .endaddrb  ( 128                    ),

   .axis_data  ( m00_tdata              ),
   .axis_valid ( m00_tvalid             ),
   .axis_ready ( m00_tready             )

);

`else
dg_slice #(
   
  .p_cons        (16),
  .p_con_w       (p_con_w),
  .p_useable_w   (p_useable_w),
  .p_increment_w (p_increment_w),
  .p_data_type_w (p_data_type_width)

) dg_slice_00 (

   .clk       ( m0_axis_clock ),
   .dg_enable ( m00_dg_enable[15:0] | {16{enable_override}}),
   .dg_inc    ( m00_dg_inc       ),
`ifdef DACEXDES_ENABLETYPE_SELECTION
   .dg_type   ( m00_dg_type      ),
`else
   .dg_type   ( default_signal_type   ),
`endif
   .dg_init   ( m00_dg_init      ),
   .dg_control( m00_dg_control   ), //

   .dg_tdata  ( m00_tdata        ),
   .dg_tvalid ( m00_tvalid       ),
   .dg_tready ( m00_tready       )

);
`endif
`ifdef EXDES_DAC_RAM_SOURCE
xpm_mem_dg #(
   
  .wordWidth     (256),
  .addrWidth     (7)

) dg_slice_01 (

   .clk       ( m0_axis_clock    ),
   .enable    ( m01_dg_enable[15:0] | {16{enable_override}}),

   .addra     ( m01_dg_inc             ),
   .wea       ( m01_dg_pulse_control_0 ),
   .dina      ( m01_dg_init            ),

   .endaddrb  ( 128                    ),

   .axis_data  ( m01_tdata              ),
   .axis_valid ( m01_tvalid             ),
   .axis_ready ( m01_tready             )

);

`else
dg_slice #(
   
  .p_cons        (16),
  .p_con_w       (p_con_w),
  .p_useable_w   (p_useable_w),
  .p_increment_w (p_increment_w),
  .p_data_type_w (p_data_type_width)

) dg_slice_01 (

   .clk       ( m0_axis_clock ),
   .dg_enable ( m01_dg_enable[15:0] | {16{enable_override}}),
   .dg_inc    ( m01_dg_inc       ),
`ifdef DACEXDES_ENABLETYPE_SELECTION
   .dg_type   ( m01_dg_type      ),
`else
   .dg_type   ( default_signal_type   ),
`endif
   .dg_init   ( m01_dg_init      ),
   .dg_control( m01_dg_control   ), //

   .dg_tdata  ( m01_tdata        ),
   .dg_tvalid ( m01_tvalid       ),
   .dg_tready ( m01_tready       )

);
`endif

//-----------------------------------------------------------------------------
// Retime the AXIS resets for each tile
//-----------------------------------------------------------------------------
xpm_cdc_single #(.SRC_INPUT_REG(0), .DEST_SYNC_FF(5)) cdc_arstn_0i (.src_clk(1'd0), .dest_clk (m0_axis_clock), .src_in (s_axi_aresetn), .dest_out (axis_resetn_rt[0]) );
assign axis_resetn_rt[1] = s_axi_aresetn;
assign axis_resetn_rt[2] = s_axi_aresetn;
assign axis_resetn_rt[3] = s_axi_aresetn;

//-----------------------------------------------------------------------------
// Other clock domain IO
//-----------------------------------------------------------------------------
rfdac_exdes_ctrl rfdac_exdes_ctrl_i (
   .dac00_dg_enable_0            (m00_dg_enable ), //
   .dac00_dg_inc_0               (m00_dg_inc    ), //
   .dac00_dg_inc_0_pdef          (7'd16), //
   .dac00_dg_type_0              (m00_dg_type   ), //
   .dac00_dg_type_0_pdef         ( default_signal_type ), //
`ifdef DACEXDES_ENABLETYPE_SELECTION
   .dac00_dg_init_0              (m00_dg_init_i   ), //
`else
   .dac00_dg_init_0              (), //
`endif
   .dac00_dg_control_0           (m00_dg_control), //
   .dac00_dg_control_0_pdef      (8'd0), //
   .dac00_dg_pulse_control_0     (m00_dg_pulse_control_0), //
   .dac00_dg_i_value_0           (m00_dg_i_value_0      ), //
   .dac00_dg_q_value_0           (m00_dg_q_value_0      ), //
   .dac00_dg_mult_control_0      (m00_dg_mult_control_0 ), //
   .dac00_dg_i_value_0_pdef      (16'd0), //
   .dac00_dg_q_value_0_pdef      (16'd0), //
   .dac00_dg_mult_control_0_pdef (3'd0),  //

   .dac01_dg_enable_0            (m01_dg_enable ), //
   .dac01_dg_inc_0               (m01_dg_inc    ), //
   .dac01_dg_inc_0_pdef          (7'd16), //
   .dac01_dg_type_0              (m01_dg_type   ), //
   .dac01_dg_type_0_pdef         ( default_signal_type ), //
`ifdef DACEXDES_ENABLETYPE_SELECTION
   .dac01_dg_init_0              (m01_dg_init_i   ), //
`else
   .dac01_dg_init_0              (), //
`endif
   .dac01_dg_control_0           (m01_dg_control), //
   .dac01_dg_control_0_pdef      (8'd0), //
   .dac01_dg_pulse_control_0     (m01_dg_pulse_control_0), //
   .dac01_dg_i_value_0           (m01_dg_i_value_0      ), //
   .dac01_dg_q_value_0           (m01_dg_q_value_0      ), //
   .dac01_dg_mult_control_0      (m01_dg_mult_control_0 ), //
   .dac01_dg_i_value_0_pdef      (16'd0), //
   .dac01_dg_q_value_0_pdef      (16'd0), //
   .dac01_dg_mult_control_0_pdef (3'd0),  //

   .dac02_dg_type_0_pdef         (4'd0), //
   .dac02_dg_control_0_pdef      (8'd0), //
   .dac02_dg_inc_0_pdef          (7'd0),//
   .dac02_dg_enable_0            (), //
   .dac02_dg_inc_0               (), //
   .dac02_dg_type_0              (), //
   .dac02_dg_init_0              (), //
   .dac02_dg_control_0           (), //
   .dac02_dg_pulse_control_0     (), //
   .dac02_dg_i_value_0           (), //
   .dac02_dg_q_value_0           (), //
   .dac02_dg_mult_control_0      (), //
   .dac02_dg_i_value_0_pdef      (16'd0), //
   .dac02_dg_q_value_0_pdef      (16'd0), //
   .dac02_dg_mult_control_0_pdef (3'd0),  //

   .dac03_dg_type_0_pdef         (4'd0), //
   .dac03_dg_control_0_pdef      (8'd0), //
   .dac03_dg_inc_0_pdef          (7'd0),//
   .dac03_dg_enable_0            (), //
   .dac03_dg_inc_0               (), //
   .dac03_dg_type_0              (), //
   .dac03_dg_init_0              (), //
   .dac03_dg_control_0           (), //
   .dac03_dg_pulse_control_0     (), //
   .dac03_dg_i_value_0           (), //
   .dac03_dg_q_value_0           (), //
   .dac03_dg_mult_control_0      (), //
   .dac03_dg_i_value_0_pdef      (16'd0), //
   .dac03_dg_q_value_0_pdef      (16'd0), //
   .dac03_dg_mult_control_0_pdef (3'd0),  //

   .dac10_dg_type_0_pdef         (4'd0), //
   .dac10_dg_control_0_pdef      (8'd0), //
   .dac10_dg_inc_0_pdef          (7'd0),//
   .dac10_dg_enable_0            (), //
   .dac10_dg_inc_0               (), //
   .dac10_dg_type_0              (), //
   .dac10_dg_init_0              (), //
   .dac10_dg_control_0           (), //
   .dac10_dg_pulse_control_0     (), //
   .dac10_dg_i_value_0           (), //
   .dac10_dg_q_value_0           (), //
   .dac10_dg_mult_control_0      (), //
   .dac10_dg_i_value_0_pdef      (16'd0), //
   .dac10_dg_q_value_0_pdef      (16'd0), //
   .dac10_dg_mult_control_0_pdef (3'd0),  //

   .dac11_dg_type_0_pdef         (4'd0), //
   .dac11_dg_control_0_pdef      (8'd0), //
   .dac11_dg_inc_0_pdef          (7'd0),//
   .dac11_dg_enable_0            (), //
   .dac11_dg_inc_0               (), //
   .dac11_dg_type_0              (), //
   .dac11_dg_init_0              (), //
   .dac11_dg_control_0           (), //
   .dac11_dg_pulse_control_0     (), //
   .dac11_dg_i_value_0           (), //
   .dac11_dg_q_value_0           (), //
   .dac11_dg_mult_control_0      (), //
   .dac11_dg_i_value_0_pdef      (16'd0), //
   .dac11_dg_q_value_0_pdef      (16'd0), //
   .dac11_dg_mult_control_0_pdef (3'd0),  //

   .dac12_dg_type_0_pdef         (4'd0), //
   .dac12_dg_control_0_pdef      (8'd0), //
   .dac12_dg_inc_0_pdef          (7'd0),//
   .dac12_dg_enable_0            (), //
   .dac12_dg_inc_0               (), //
   .dac12_dg_type_0              (), //
   .dac12_dg_init_0              (), //
   .dac12_dg_control_0           (), //
   .dac12_dg_pulse_control_0     (), //
   .dac12_dg_i_value_0           (), //
   .dac12_dg_q_value_0           (), //
   .dac12_dg_mult_control_0      (), //
   .dac12_dg_i_value_0_pdef      (16'd0), //
   .dac12_dg_q_value_0_pdef      (16'd0), //
   .dac12_dg_mult_control_0_pdef (3'd0),  //

   .dac13_dg_type_0_pdef         (4'd0), //
   .dac13_dg_control_0_pdef      (8'd0), //
   .dac13_dg_inc_0_pdef          (7'd0),//
   .dac13_dg_enable_0            (), //
   .dac13_dg_inc_0               (), //
   .dac13_dg_type_0              (), //
   .dac13_dg_init_0              (), //
   .dac13_dg_control_0           (), //
   .dac13_dg_pulse_control_0     (), //
   .dac13_dg_i_value_0           (), //
   .dac13_dg_q_value_0           (), //
   .dac13_dg_mult_control_0      (), //
   .dac13_dg_i_value_0_pdef      (16'd0), //
   .dac13_dg_q_value_0_pdef      (16'd0), //
   .dac13_dg_mult_control_0_pdef (3'd0),  //

   .dac20_dg_type_0_pdef         (4'd0), //
   .dac20_dg_control_0_pdef      (8'd0), //
   .dac20_dg_inc_0_pdef          (7'd0),//
   .dac20_dg_enable_0            (), //
   .dac20_dg_inc_0               (), //
   .dac20_dg_type_0              (), //
   .dac20_dg_init_0              (), //
   .dac20_dg_control_0           (), //
   .dac20_dg_pulse_control_0     (), //
   .dac20_dg_i_value_0           (), //
   .dac20_dg_q_value_0           (), //
   .dac20_dg_mult_control_0      (), //
   .dac20_dg_i_value_0_pdef      (16'd0), //
   .dac20_dg_q_value_0_pdef      (16'd0), //
   .dac20_dg_mult_control_0_pdef (3'd0),  //

   .dac21_dg_type_0_pdef         (4'd0), //
   .dac21_dg_control_0_pdef      (8'd0), //
   .dac21_dg_inc_0_pdef          (7'd0),//
   .dac21_dg_enable_0            (), //
   .dac21_dg_inc_0               (), //
   .dac21_dg_type_0              (), //
   .dac21_dg_init_0              (), //
   .dac21_dg_control_0           (), //
   .dac21_dg_pulse_control_0     (), //
   .dac21_dg_i_value_0           (), //
   .dac21_dg_q_value_0           (), //
   .dac21_dg_mult_control_0      (), //
   .dac21_dg_i_value_0_pdef      (16'd0), //
   .dac21_dg_q_value_0_pdef      (16'd0), //
   .dac21_dg_mult_control_0_pdef (3'd0),  //

   .dac22_dg_type_0_pdef         (4'd0), //
   .dac22_dg_control_0_pdef      (8'd0), //
   .dac22_dg_inc_0_pdef          (7'd0),//
   .dac22_dg_enable_0            (), //
   .dac22_dg_inc_0               (), //
   .dac22_dg_type_0              (), //
   .dac22_dg_init_0              (), //
   .dac22_dg_control_0           (), //
   .dac22_dg_pulse_control_0     (), //
   .dac22_dg_i_value_0           (), //
   .dac22_dg_q_value_0           (), //
   .dac22_dg_mult_control_0      (), //
   .dac22_dg_i_value_0_pdef      (16'd0), //
   .dac22_dg_q_value_0_pdef      (16'd0), //
   .dac22_dg_mult_control_0_pdef (3'd0),  //

   .dac23_dg_type_0_pdef         (4'd0), //
   .dac23_dg_control_0_pdef      (8'd0), //
   .dac23_dg_inc_0_pdef          (7'd0),//
   .dac23_dg_enable_0            (), //
   .dac23_dg_inc_0               (), //
   .dac23_dg_type_0              (), //
   .dac23_dg_init_0              (), //
   .dac23_dg_control_0           (), //
   .dac23_dg_pulse_control_0     (), //
   .dac23_dg_i_value_0           (), //
   .dac23_dg_q_value_0           (), //
   .dac23_dg_mult_control_0      (), //
   .dac23_dg_i_value_0_pdef      (16'd0), //
   .dac23_dg_q_value_0_pdef      (16'd0), //
   .dac23_dg_mult_control_0_pdef (3'd0),  //

   .dac30_dg_type_0_pdef         (4'd0), //
   .dac30_dg_control_0_pdef      (8'd0), //
   .dac30_dg_inc_0_pdef          (7'd0),//
   .dac30_dg_enable_0            (), //
   .dac30_dg_inc_0               (), //
   .dac30_dg_type_0              (), //
   .dac30_dg_init_0              (), //
   .dac30_dg_control_0           (), //
   .dac30_dg_pulse_control_0     (), //
   .dac30_dg_i_value_0           (), //
   .dac30_dg_q_value_0           (), //
   .dac30_dg_mult_control_0      (), //
   .dac30_dg_i_value_0_pdef      (16'd0), //
   .dac30_dg_q_value_0_pdef      (16'd0), //
   .dac30_dg_mult_control_0_pdef (3'd0),  //

   .dac31_dg_type_0_pdef         (4'd0), //
   .dac31_dg_control_0_pdef      (8'd0), //
   .dac31_dg_inc_0_pdef          (7'd0),//
   .dac31_dg_enable_0            (), //
   .dac31_dg_inc_0               (), //
   .dac31_dg_type_0              (), //
   .dac31_dg_init_0              (), //
   .dac31_dg_control_0           (), //
   .dac31_dg_pulse_control_0     (), //
   .dac31_dg_i_value_0           (), //
   .dac31_dg_q_value_0           (), //
   .dac31_dg_mult_control_0      (), //
   .dac31_dg_i_value_0_pdef      (16'd0), //
   .dac31_dg_q_value_0_pdef      (16'd0), //
   .dac31_dg_mult_control_0_pdef (3'd0),  //

   .dac32_dg_type_0_pdef         (4'd0), //
   .dac32_dg_control_0_pdef      (8'd0), //
   .dac32_dg_inc_0_pdef          (7'd0),//
   .dac32_dg_enable_0            (), //
   .dac32_dg_inc_0               (), //
   .dac32_dg_type_0              (), //
   .dac32_dg_init_0              (), //
   .dac32_dg_control_0           (), //
   .dac32_dg_pulse_control_0     (), //
   .dac32_dg_i_value_0           (), //
   .dac32_dg_q_value_0           (), //
   .dac32_dg_mult_control_0      (), //
   .dac32_dg_i_value_0_pdef      (16'd0), //
   .dac32_dg_q_value_0_pdef      (16'd0), //
   .dac32_dg_mult_control_0_pdef (3'd0),  //

   .dac33_dg_type_0_pdef         (4'd0), //
   .dac33_dg_control_0_pdef      (8'd0), //
   .dac33_dg_inc_0_pdef          (7'd0),//
   .dac33_dg_enable_0            (), //
   .dac33_dg_inc_0               (), //
   .dac33_dg_type_0              (), //
   .dac33_dg_init_0              (), //
   .dac33_dg_control_0           (), //
   .dac33_dg_pulse_control_0     (), //
   .dac33_dg_i_value_0           (), //
   .dac33_dg_q_value_0           (), //
   .dac33_dg_mult_control_0      (), //
   .dac33_dg_i_value_0_pdef      (16'd0), //
   .dac33_dg_q_value_0_pdef      (16'd0), //
   .dac33_dg_mult_control_0_pdef (3'd0),  //

   .dac_fab_clk0           (m0_axis_clock),
   .dac_fab_resetn0        (axis_resetn_rt[0]), // Negedge reset despite the name
   .dac_fab_clk1           (s_axi_aclk     ),
   .dac_fab_resetn1        (axis_resetn_rt[1]), // Negedge reset despite the name
   .dac_fab_clk2           (s_axi_aclk     ),
   .dac_fab_resetn2        (axis_resetn_rt[2]), // Negedge reset despite the name
   .dac_fab_clk3           (s_axi_aclk     ),
   .dac_fab_resetn3        (axis_resetn_rt[3]), // Negedge reset despite the name

   .enable                 (enable          ),
   .timeout_enable         (timeout_enable  ),
   .timeout_value          (timeout_value   ),

   .timeout_enable_in      (timeout_enable  ),
   .timeout_value_in       (timeout_value   ), 

   .s_axi_aclk             (s_axi_aclk      ),
   .s_axi_aresetn          (s_axi_aresetn   ),

   .s_axi_awaddr           (s_axi_awaddr    ),
   .s_axi_awvalid          (s_axi_awvalid   ),
   .s_axi_awready          (s_axi_awready   ),
   .s_axi_wdata            (s_axi_wdata     ),
   .s_axi_wvalid           (s_axi_wvalid    ),
   .s_axi_wready           (s_axi_wready    ),
   .s_axi_bresp            (s_axi_bresp     ),
   .s_axi_bvalid           (s_axi_bvalid    ),
   .s_axi_bready           (s_axi_bready    ),
   .s_axi_araddr           (s_axi_araddr    ),
   .s_axi_arvalid          (s_axi_arvalid   ),
   .s_axi_arready          (s_axi_arready   ),
   .s_axi_rdata            (s_axi_rdata     ),
   .s_axi_rresp            (s_axi_rresp     ),
   .s_axi_rvalid           (s_axi_rvalid    ),
   .s_axi_rready           (s_axi_rready    )

);

`ifdef DACEXDES_ENABLETYPE_SELECTION
  assign m00_dg_init = m00_dg_init_i[255:0];
  assign m01_dg_init = m01_dg_init_i[255:0];
`endif

endmodule

`ifdef EXDES_DAC_RAM_SOURCE
//------------------------------------------------------------------------------
// RAM based data generator module
//------------------------------------------------------------------------------
module xpm_mem_dg #(
   parameter wordWidth     = 32,
   parameter addrWidth     = 8
) (

  input  wire                    clk            ,
  input  wire                    enable         ,
  
  input  wire                    wea            ,
  input  wire [addrWidth-1:0]    addra          ,
  input  wire [wordWidth-1:0]    dina           ,

  input  wire [addrWidth-1:0]    endaddrb       ,

  input  wire                    axis_ready     ,    
  output reg                     axis_valid=0   ,
  output wire [wordWidth-1:0]    axis_data          

);

localparam wordsInMemory = 2 ** addrWidth;

// Internal variables
reg [addrWidth-1:0]    addrb=0;

// Always keep our mem 2^^n so this can just rollover
always @(posedge clk) begin
   if (~enable) begin
      addrb      <= 'd0;
      axis_valid <= 1'd0;
   end else 
      if (~axis_ready) begin
         addrb      <= addrb;
         axis_valid <= 1'd0;
      end else begin
         // Reset on max address value. Allows more control over frequency
         // of wave being generated
         if (addrb == endaddrb)
            addrb      <= 'd0;
         else
            addrb      <= addrb + 'd1;
         // Signal is always valid when enabled
         axis_valid <= 1'd1;
      end
end

xpm_mem_dg_wrap2 #(

   .wordWidth     (wordWidth),
   .wordsInMemory (wordsInMemory),
   .addrWidth     (addrWidth)
   
) xpm_mem_dg_wrap2_i (
.clk            (clk      ) ,
.wea            (wea      ) ,
.addra          (addra    ) ,
.dina           (dina     ) ,
.addrb          (addrb    ) ,
.doutb          (axis_data) 

);

endmodule

//-----------------------------------------------------------------------------
// Wrap the XPM wrapper with fixed enables, abstraction allows for IPI dev use.
//-----------------------------------------------------------------------------
module xpm_mem_dg_wrap2 #(
   parameter wordWidth     = 32,
   parameter wordsInMemory = 128,
   parameter addrWidth     = 8
) (

  input  wire                    clk            ,

  input  wire                    wea            ,
  input  wire [addrWidth-1:0]    addra          ,
  input  wire [wordWidth-1:0]    dina           ,

  input  wire [addrWidth-1:0]    addrb          ,
  output wire [wordWidth-1:0]    doutb          

);

xpm_mem_dg_sdpram_wrap #(

   .wordWidth     (wordWidth    ),
   .wordsInMemory (wordsInMemory),
   .addrWidth     (addrWidth    )
   
) xpm_mem_dg_sdpram_wrap_i (
.clka           (clk    ) ,
.ena            (1'd1   ) , // Tie of the enables
.wea            (wea    ) ,
.addra          (addra  ) ,
.dina           (dina   ) ,
.clkb           (clk    ) ,
.rstb           (1'd0   ) ,
.enb            (1'd1   ) ,
.regceb         (1'd1   ) ,
.addrb          (addrb  ) ,
.doutb          (doutb  ) 

);

endmodule

//-----------------------------------------------------------------------------
// XPM wrapper. Lowest level block in RAM CAP/GEN
//-----------------------------------------------------------------------------
module xpm_mem_dg_sdpram_wrap #(
   parameter wordWidth     = 256,
   parameter wordsInMemory = 128,
   parameter addrWidth     = 8
) (

  input  wire                    clka           ,
  input  wire                    ena            ,
  input  wire                    wea            ,
  input  wire [addrWidth-1:0]    addra          ,
  input  wire [wordWidth-1:0]    dina           ,

  // Port B module ports
  input  wire                    clkb           ,
  input  wire                    rstb           ,
  input  wire                    enb            ,
  input  wire                    regceb         ,
  input  wire [addrWidth-1:0]    addrb          ,
  output wire [wordWidth-1:0]    doutb          

);

// xpm_memory_sdpram: Simple Dual Port RAM
// Xilinx Parameterized Macro, Version 2016.3
xpm_memory_sdpram # (

  // Common module parameters
  .MEMORY_SIZE        (wordWidth*wordsInMemory), //positive integer
  .MEMORY_PRIMITIVE   ("auto"),                  // string; "auto", "distributed", "block" or "ultra";
  .CLOCKING_MODE      ("common_clock"),          // string; "common_clock", "independent_clock" 
  .MEMORY_INIT_FILE   ("none"),                  // string; "none" or "<filename>.mem" 
  .MEMORY_INIT_PARAM  (""    ),                  // string;
  .USE_MEM_INIT       (1),                       // integer; 0,1
  .WAKEUP_TIME        ("disable_sleep"),         // string; "disable_sleep" or "use_sleep_pin" 
  .MESSAGE_CONTROL    (0),                       // integer; 0,1
  .ECC_MODE           ("no_ecc"),                // string; "no_ecc", "encode_only", "decode_only" or "both_encode_and_decode" 
  .AUTO_SLEEP_TIME    (0),                       // Do not Change

  // Port A module parameters
  .WRITE_DATA_WIDTH_A (wordWidth),               // positive integer
  .BYTE_WRITE_WIDTH_A (wordWidth),               // integer; 8, 9, or WRITE_DATA_WIDTH_A value
  .ADDR_WIDTH_A       (addrWidth),               // positive integer

  // Port B module parameters
  .READ_DATA_WIDTH_B  (wordWidth),               // positive integer
  .ADDR_WIDTH_B       (addrWidth),               // positive integer
  .READ_RESET_VALUE_B ("0"),                     // string
  .READ_LATENCY_B     (2),                       // non-negative integer
  .WRITE_MODE_B       ("no_change")              // string; "write_first", "read_first", "no_change" 

) xpm_memory_sdpram_inst (

  // Common module ports
  .sleep          (1'b0),

  // Port A module ports
  .clka           (clka),
  .ena            (ena),
  .wea            (wea),
  .addra          (addra),
  .dina           (dina),
  .injectsbiterra (1'b0),
  .injectdbiterra (1'b0),

  // Port B module ports
  .clkb           (clkb),
  .rstb           (rstb),
  .enb            (enb),
  .regceb         (regceb),
  .addrb          (addrb),
  .doutb          (doutb),
  .sbiterrb       (),
  .dbiterrb       ()

);

endmodule

`endif
