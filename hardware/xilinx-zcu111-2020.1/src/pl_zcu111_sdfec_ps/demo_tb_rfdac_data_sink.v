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

module demo_tb_rfdac_data_sink #(
  parameter  p_connections       = 16,
  parameter  p_connection_width  = 16,
  parameter  p_useable_width     = 14,
  parameter  p_data_inc_val_init = 1,
  parameter  p_data_type_width   = 3
) (

   // AXI-Lite Interface
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi AWADDR"  *) input  wire [17:0] s_axi_awaddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi AWVALID" *) input  wire        s_axi_awvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi AWREADY" *) output wire        s_axi_awready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi WDATA"   *) input  wire [31:0] s_axi_wdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi WVALID"  *) input  wire        s_axi_wvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi WREADY"  *) output wire        s_axi_wready   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi BRESP"   *) output wire  [1:0] s_axi_bresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi BVALID"  *) output wire        s_axi_bvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi BREADY"  *) input  wire        s_axi_bready   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi ARADDR"  *) input  wire [17:0] s_axi_araddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi ARVALID" *) input  wire        s_axi_arvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi ARREADY" *) output wire        s_axi_arready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi RDATA"   *) output wire [31:0] s_axi_rdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi RRESP"   *) output wire  [1:0] s_axi_rresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi RVALID"  *) output wire        s_axi_rvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_dec_axi RREADY"  *) input  wire        s_axi_rready   ,  // 

   input [63:0]       vin_00_p,
   input [63:0]       vin_00_n,

   input              sample_rate0_clk,
   input              fabric_rate0_clk,

   // Error/Complete indication
   output reg         done_flag=0  ,
   output wire        error_flag   ,
   output wire [15:0] clock_enable_reg,

   // AXI-Lite Clock/Reset
   input  wire        s_axi_aclk  ,    
   input  wire        s_axi_aresetn
  
  );

// ----------------------------------------------------------------------------
// Wire declarations
// ----------------------------------------------------------------------------
wire                          global_enable;
wire [15:0] done_axi_reg;
wire [15:0] error_axi_reg;
wire                          m00_enable        ; //
wire    [p_useable_width-1:0] m00_inc           ; //
wire  [p_data_type_width-1:0] m00_type          ; //
wire                   [31:0] m00_scaling_factor; //
wire                   [31:0] m00_offset        ; //
wire                   [15:0] m00_phase_high    ; //
wire                   [15:0] m00_phase_low     ; //
wire                   [15:0] m00_change_count  ; //
wire                    [7:0] m00_ds_ctrl          ;
wire                   [31:0] m00_ds_fft_exec_cnt  ;
wire                   [31:0] m00_ds_fft_max_level ;
wire                    [7:0] m00_ds_status        ;

wire [7:0] error_bus;
wire [1:0] done_bus;
reg  [1:0]                   done_delay = 2'd3;

// ----------------------------------------------------------------------------
// Sticky rising edge detection on done signal. & error/done assignment
// Unused checked set done high when disabled, hence &done_bus
// ----------------------------------------------------------------------------
assign error_flag = |error_bus;
always @(posedge s_axi_aclk) begin
   done_delay <= {done_delay[0],&done_bus};
   if (~global_enable)
      done_flag <= 1'd0; 
      if (~done_delay[1] & done_delay[0])
         done_flag <= 1'd1; 
end

// ----------------------------------------------------------------------------
// Data generator tile 0
// ----------------------------------------------------------------------------
demo_tb_rfdac_tile_sink tile_sink_0_i(

	// Connect data source 0
   .s0_error          (error_bus[0]),







   .s0_enable         (m00_enable & global_enable), //
   .s0_inc            (m00_inc             ), //
   .s0_type           (m00_type            ), //
   .s0_scaling_factor (m00_scaling_factor  ), //
   .s0_offset         (m00_offset          ), //
   .s0_clk_phase_hl   ({m00_phase_high,m00_phase_low}),
   .s0_change_count   (m00_change_count    ),
   // 
   .s0_ds_ctrl             (m00_ds_ctrl           ),
   .s0_ds_fft_exec_cnt     (m00_ds_fft_exec_cnt   ),
   .s0_ds_fft_max_level    (m00_ds_fft_max_level  ),
   .s0_ds_status           (m00_ds_status         ),
   .s0_din_p          (vin_00_p            ), //
   .s0_din_n          (vin_00_n            ), //


	// Connect data source 1
   .s1_error          (error_bus[1]),







   .s1_enable         ({1{1'b0}}                ), //
   .s1_inc            ({p_useable_width{1'b0}}  ), //
   .s1_type           ({p_data_type_width{1'b0}}), //
   .s1_scaling_factor (32'd0                    ), //
   .s1_offset         (32'd0                    ), //
   .s1_clk_phase_hl   (32'd0                    ),
   .s1_change_count   (16'd0                    ),
   // 
   .s1_ds_ctrl             (8'd0),
   .s1_ds_fft_exec_cnt     ( ),
   .s1_ds_fft_max_level    ( ),
   .s1_ds_status           ( ),
   .s1_din_p          (64'd0                    ), //
   .s1_din_n          (64'd0                    ), //

	// Connect data source 2
   .s2_error          (error_bus[2]),







   .s2_enable         ({1{1'b0}}                ), //
   .s2_inc            ({p_useable_width{1'b0}}  ), //
   .s2_type           ({p_data_type_width{1'b0}}), //
   .s2_scaling_factor (32'd0                    ), //
   .s2_offset         (32'd0                    ), //
   .s2_clk_phase_hl   (32'd0                    ),
   .s2_change_count   (16'd0                    ),
   // 
   .s2_ds_ctrl             (8'd0),
   .s2_ds_fft_exec_cnt     ( ),
   .s2_ds_fft_max_level    ( ),
   .s2_ds_status           ( ),
   .s2_din_p          (64'd0                    ), //
   .s2_din_n          (64'd0                    ), //

	// Connect data source 3
   .s3_error          (error_bus[3]),







   .s3_enable         ({1{1'b0}}                ), //
   .s3_inc            ({p_useable_width{1'b0}}  ), //
   .s3_type           ({p_data_type_width{1'b0}}), //
   .s3_scaling_factor (32'd0                    ), //
   .s3_offset         (32'd0                    ), //
   .s3_clk_phase_hl   (32'd0                    ),
   .s3_change_count   (16'd0                    ),
   // 
   .s3_ds_ctrl             (8'd0),
   .s3_ds_fft_exec_cnt     ( ),
   .s3_ds_fft_max_level    ( ),
   .s3_ds_status           ( ),
   .s3_din_p          (64'd0                    ), //
   .s3_din_n          (64'd0                    ), //

  .clk_samp           (sample_rate0_clk ), //
  .clk_fabric         (fabric_rate0_clk ),  //
  .done               (done_bus[0])  //
  
  );
// ----------------------------------------------------------------------------
// Data generator tile 1
// ----------------------------------------------------------------------------
demo_tb_rfdac_tile_sink tile_sink_1_i(

	// Connect data source 0
   .s0_error          (error_bus[4]),







   .s0_enable         ({1{1'b0}}                ), //
   .s0_inc            ({p_useable_width{1'b0}}  ), //
   .s0_type           ({p_data_type_width{1'b0}}), //
   .s0_scaling_factor (32'd0                    ), //
   .s0_offset         (32'd0                    ), //
   .s0_clk_phase_hl   (32'd0                    ),
   .s0_change_count   (16'd0                    ),
   // 
   .s0_ds_ctrl             (8'd0),
   .s0_ds_fft_exec_cnt     ( ),
   .s0_ds_fft_max_level    ( ),
   .s0_ds_status           ( ),
   .s0_din_p          (64'd0                    ), //
   .s0_din_n          (64'd0                    ), //

	// Connect data source 1
   .s1_error          (error_bus[5]),







   .s1_enable         ({1{1'b0}}                ), //
   .s1_inc            ({p_useable_width{1'b0}}  ), //
   .s1_type           ({p_data_type_width{1'b0}}), //
   .s1_scaling_factor (32'd0                    ), //
   .s1_offset         (32'd0                    ), //
   .s1_clk_phase_hl   (32'd0                    ),
   .s1_change_count   (16'd0                    ),
   // 
   .s1_ds_ctrl             (8'd0),
   .s1_ds_fft_exec_cnt     ( ),
   .s1_ds_fft_max_level    ( ),
   .s1_ds_status           ( ),
   .s1_din_p          (64'd0                    ), //
   .s1_din_n          (64'd0                    ), //

	// Connect data source 2
   .s2_error          (error_bus[6]),







   .s2_enable         ({1{1'b0}}                ), //
   .s2_inc            ({p_useable_width{1'b0}}  ), //
   .s2_type           ({p_data_type_width{1'b0}}), //
   .s2_scaling_factor (32'd0                    ), //
   .s2_offset         (32'd0                    ), //
   .s2_clk_phase_hl   (32'd0                    ),
   .s2_change_count   (16'd0                    ),
   // 
   .s2_ds_ctrl             (8'd0),
   .s2_ds_fft_exec_cnt     ( ),
   .s2_ds_fft_max_level    ( ),
   .s2_ds_status           ( ),
   .s2_din_p          (64'd0                    ), //
   .s2_din_n          (64'd0                    ), //

	// Connect data source 3
   .s3_error          (error_bus[7]),







   .s3_enable         ({1{1'b0}}                ), //
   .s3_inc            ({p_useable_width{1'b0}}  ), //
   .s3_type           ({p_data_type_width{1'b0}}), //
   .s3_scaling_factor (32'd0                    ), //
   .s3_offset         (32'd0                    ), //
   .s3_clk_phase_hl   (32'd0                    ),
   .s3_change_count   (16'd0                    ),
   // 
   .s3_ds_ctrl             (8'd0),
   .s3_ds_fft_exec_cnt     ( ),
   .s3_ds_fft_max_level    ( ),
   .s3_ds_status           ( ),
   .s3_din_p          (64'd0                    ), //
   .s3_din_n          (64'd0                    ), //

  .clk_samp           (1'd0 ), //
  .clk_fabric         (1'd0 ),  //
  .done               (done_bus[1])  //
  
  );

//-----------------------------------------------------------------------------
// Create a Tile/Slice ordered bus for the AXI interface
//-----------------------------------------------------------------------------
assign done_axi_reg [ 0] = done_bus [0];
assign error_axi_reg[ 0] = error_bus[0];
assign done_axi_reg [ 1] = done_bus [0];
assign error_axi_reg[ 1] = error_bus[1];
assign done_axi_reg [ 2] = done_bus [0];
assign error_axi_reg[ 2] = error_bus[2];
assign done_axi_reg [ 3] = done_bus [0];
assign error_axi_reg[ 3] = error_bus[3];
assign done_axi_reg [ 4] = 1'd1;
assign error_axi_reg[ 4] = 1'd0;
assign done_axi_reg [ 5] = 1'd1;
assign error_axi_reg[ 5] = 1'd0;
assign done_axi_reg [ 6] = 1'd1;
assign error_axi_reg[ 6] = 1'd0;
assign done_axi_reg [ 7] = 1'd1;
assign error_axi_reg[ 7] = 1'd0;
assign done_axi_reg [ 8] = 1'd1;
assign error_axi_reg[ 8] = 1'd0;
assign done_axi_reg [ 9] = 1'd1;
assign error_axi_reg[ 9] = 1'd0;
assign done_axi_reg [10] = 1'd1;
assign error_axi_reg[10] = 1'd0;
assign done_axi_reg [11] = 1'd1;
assign error_axi_reg[11] = 1'd0;
assign done_axi_reg [12] = 1'd1;
assign error_axi_reg[12] = 1'd0;
assign done_axi_reg [13] = 1'd1;
assign error_axi_reg[13] = 1'd0;
assign done_axi_reg [14] = 1'd1;
assign error_axi_reg[14] = 1'd0;
assign done_axi_reg [15] = 1'd1;
assign error_axi_reg[15] = 1'd0;

//-----------------------------------------------------------------------------
// Other clock domain IO
//-----------------------------------------------------------------------------
demo_tb_hsdac_ctrl hsdac_exdes_ctrl_i (
   .dac00_ds_enable_0         (m00_enable        ), //
   .dac00_ds_inc_0            (m00_inc           ), //
   .dac00_ds_type_0           (m00_type          ), //
   .dac00_ds_scaling_factor_0 (m00_scaling_factor), //
   .dac00_ds_offset_0         (m00_offset        ), //
   .dac00_ds_phase_high_0     (m00_phase_high    ), //
   .dac00_ds_phase_low_0      (m00_phase_low     ), //
   .dac00_ds_out_clk_div_0    (),
   .dac00_ds_error_0          (1'd0), //
   .dac00_ds_change_count_0   (m00_change_count      ), 
   .dac00_ds_ctrl_0           (m00_ds_ctrl           ),
   .dac00_ds_fft_exec_cnt_0   (m00_ds_fft_exec_cnt   ),
   .dac00_ds_fft_max_level_0  (m00_ds_fft_max_level  ),
   .dac00_ds_status_0         (m00_ds_status         ),

   .dac01_ds_enable_0         (), //
   .dac01_ds_inc_0            (), //
   .dac01_ds_type_0           (), //
   .dac01_ds_scaling_factor_0 (), //
   .dac01_ds_offset_0         (), //
   .dac01_ds_phase_high_0     (), //
   .dac01_ds_phase_low_0      (), //
   .dac01_ds_out_clk_div_0    (), // 
   .dac01_ds_error_0          (1'd0), //
   .dac01_ds_change_count_0   (), //
   .dac01_ds_ctrl_0           (),
   .dac01_ds_fft_exec_cnt_0   (32'd0),
   .dac01_ds_fft_max_level_0  (32'd0),
   .dac01_ds_status_0         (8'd0),

   .dac02_ds_enable_0         (), //
   .dac02_ds_inc_0            (), //
   .dac02_ds_type_0           (), //
   .dac02_ds_scaling_factor_0 (), //
   .dac02_ds_offset_0         (), //
   .dac02_ds_phase_high_0     (), //
   .dac02_ds_phase_low_0      (), //
   .dac02_ds_out_clk_div_0    (), // 
   .dac02_ds_error_0          (1'd0), //
   .dac02_ds_change_count_0   (), //
   .dac02_ds_ctrl_0           (),
   .dac02_ds_fft_exec_cnt_0   (32'd0),
   .dac02_ds_fft_max_level_0  (32'd0),
   .dac02_ds_status_0         (8'd0),

   .dac03_ds_enable_0         (), //
   .dac03_ds_inc_0            (), //
   .dac03_ds_type_0           (), //
   .dac03_ds_scaling_factor_0 (), //
   .dac03_ds_offset_0         (), //
   .dac03_ds_phase_high_0     (), //
   .dac03_ds_phase_low_0      (), //
   .dac03_ds_out_clk_div_0    (), // 
   .dac03_ds_error_0          (1'd0), //
   .dac03_ds_change_count_0   (), //
   .dac03_ds_ctrl_0           (),
   .dac03_ds_fft_exec_cnt_0   (32'd0),
   .dac03_ds_fft_max_level_0  (32'd0),
   .dac03_ds_status_0         (8'd0),

   .dac10_ds_enable_0         (), //
   .dac10_ds_inc_0            (), //
   .dac10_ds_type_0           (), //
   .dac10_ds_scaling_factor_0 (), //
   .dac10_ds_offset_0         (), //
   .dac10_ds_phase_high_0     (), //
   .dac10_ds_phase_low_0      (), //
   .dac10_ds_out_clk_div_0    (), // 
   .dac10_ds_error_0          (1'd0), //
   .dac10_ds_change_count_0   (), //
   .dac10_ds_ctrl_0           (),
   .dac10_ds_fft_exec_cnt_0   (32'd0),
   .dac10_ds_fft_max_level_0  (32'd0),
   .dac10_ds_status_0         (8'd0),

   .dac11_ds_enable_0         (), //
   .dac11_ds_inc_0            (), //
   .dac11_ds_type_0           (), //
   .dac11_ds_scaling_factor_0 (), //
   .dac11_ds_offset_0         (), //
   .dac11_ds_phase_high_0     (), //
   .dac11_ds_phase_low_0      (), //
   .dac11_ds_out_clk_div_0    (), // 
   .dac11_ds_error_0          (1'd0), //
   .dac11_ds_change_count_0   (), //
   .dac11_ds_ctrl_0           (),
   .dac11_ds_fft_exec_cnt_0   (32'd0),
   .dac11_ds_fft_max_level_0  (32'd0),
   .dac11_ds_status_0         (8'd0),

   .dac12_ds_enable_0         (), //
   .dac12_ds_inc_0            (), //
   .dac12_ds_type_0           (), //
   .dac12_ds_scaling_factor_0 (), //
   .dac12_ds_offset_0         (), //
   .dac12_ds_phase_high_0     (), //
   .dac12_ds_phase_low_0      (), //
   .dac12_ds_out_clk_div_0    (), // 
   .dac12_ds_error_0          (1'd0), //
   .dac12_ds_change_count_0   (), //
   .dac12_ds_ctrl_0           (),
   .dac12_ds_fft_exec_cnt_0   (32'd0),
   .dac12_ds_fft_max_level_0  (32'd0),
   .dac12_ds_status_0         (8'd0),

   .dac13_ds_enable_0         (), //
   .dac13_ds_inc_0            (), //
   .dac13_ds_type_0           (), //
   .dac13_ds_scaling_factor_0 (), //
   .dac13_ds_offset_0         (), //
   .dac13_ds_phase_high_0     (), //
   .dac13_ds_phase_low_0      (), //
   .dac13_ds_out_clk_div_0    (), // 
   .dac13_ds_error_0          (1'd0), //
   .dac13_ds_change_count_0   (), //
   .dac13_ds_ctrl_0           (),
   .dac13_ds_fft_exec_cnt_0   (32'd0),
   .dac13_ds_fft_max_level_0  (32'd0),
   .dac13_ds_status_0         (8'd0),

   .dac20_ds_enable_0         (), //
   .dac20_ds_inc_0            (), //
   .dac20_ds_type_0           (), //
   .dac20_ds_scaling_factor_0 (), //
   .dac20_ds_offset_0         (), //
   .dac20_ds_phase_high_0     (), //
   .dac20_ds_phase_low_0      (), //
   .dac20_ds_out_clk_div_0    (), // 
   .dac20_ds_error_0          (1'd0), //
   .dac20_ds_change_count_0   (), 
   .dac20_ds_ctrl_0           (),
   .dac20_ds_fft_exec_cnt_0   (32'd0),
   .dac20_ds_fft_max_level_0  (32'd0),
   .dac20_ds_status_0         (8'd0),

   .dac21_ds_enable_0         (), //
   .dac21_ds_inc_0            (), //
   .dac21_ds_type_0           (), //
   .dac21_ds_scaling_factor_0 (), //
   .dac21_ds_offset_0         (), //
   .dac21_ds_phase_high_0     (), //
   .dac21_ds_phase_low_0      (), //
   .dac21_ds_out_clk_div_0    (), // 
   .dac21_ds_error_0          (1'd0), //
   .dac21_ds_change_count_0   (), 
   .dac21_ds_ctrl_0           (),
   .dac21_ds_fft_exec_cnt_0   (32'd0),
   .dac21_ds_fft_max_level_0  (32'd0),
   .dac21_ds_status_0         (8'd0),

   .dac22_ds_enable_0         (), //
   .dac22_ds_inc_0            (), //
   .dac22_ds_type_0           (), //
   .dac22_ds_scaling_factor_0 (), //
   .dac22_ds_offset_0         (), //
   .dac22_ds_phase_high_0     (), //
   .dac22_ds_phase_low_0      (), //
   .dac22_ds_out_clk_div_0    (), // 
   .dac22_ds_error_0          (1'd0), //
   .dac22_ds_change_count_0   (), 
   .dac22_ds_ctrl_0           (),
   .dac22_ds_fft_exec_cnt_0   (32'd0),
   .dac22_ds_fft_max_level_0  (32'd0),
   .dac22_ds_status_0         (8'd0),

   .dac23_ds_enable_0         (), //
   .dac23_ds_inc_0            (), //
   .dac23_ds_type_0           (), //
   .dac23_ds_scaling_factor_0 (), //
   .dac23_ds_offset_0         (), //
   .dac23_ds_phase_high_0     (), //
   .dac23_ds_phase_low_0      (), //
   .dac23_ds_out_clk_div_0    (), // 
   .dac23_ds_error_0          (1'd0), //
   .dac23_ds_change_count_0   (), 
   .dac23_ds_ctrl_0           (),
   .dac23_ds_fft_exec_cnt_0   (32'd0),
   .dac23_ds_fft_max_level_0  (32'd0),
   .dac23_ds_status_0         (8'd0),

   .dac30_ds_enable_0         (), //
   .dac30_ds_inc_0            (), //
   .dac30_ds_type_0           (), //
   .dac30_ds_scaling_factor_0 (), //
   .dac30_ds_offset_0         (), //
   .dac30_ds_phase_high_0     (), //
   .dac30_ds_phase_low_0      (), //
   .dac30_ds_out_clk_div_0    (), // 
   .dac30_ds_error_0          (1'd0), //
   .dac30_ds_change_count_0   (), 
   .dac30_ds_ctrl_0           (),
   .dac30_ds_fft_exec_cnt_0   (32'd0),
   .dac30_ds_fft_max_level_0  (32'd0),
   .dac30_ds_status_0         (8'd0),

   .dac31_ds_enable_0         (), //
   .dac31_ds_inc_0            (), //
   .dac31_ds_type_0           (), //
   .dac31_ds_scaling_factor_0 (), //
   .dac31_ds_offset_0         (), //
   .dac31_ds_phase_high_0     (), //
   .dac31_ds_phase_low_0      (), //
   .dac31_ds_out_clk_div_0    (), // 
   .dac31_ds_error_0          (1'd0), //
   .dac31_ds_change_count_0   (), 
   .dac31_ds_ctrl_0           (),
   .dac31_ds_fft_exec_cnt_0   (32'd0),
   .dac31_ds_fft_max_level_0  (32'd0),
   .dac31_ds_status_0         (8'd0),

   .dac32_ds_enable_0         (), //
   .dac32_ds_inc_0            (), //
   .dac32_ds_type_0           (), //
   .dac32_ds_scaling_factor_0 (), //
   .dac32_ds_offset_0         (), //
   .dac32_ds_phase_high_0     (), //
   .dac32_ds_phase_low_0      (), //
   .dac32_ds_out_clk_div_0    (), // 
   .dac32_ds_error_0          (1'd0), //
   .dac32_ds_change_count_0   (), 
   .dac32_ds_ctrl_0           (),
   .dac32_ds_fft_exec_cnt_0   (32'd0),
   .dac32_ds_fft_max_level_0  (32'd0),
   .dac32_ds_status_0         (8'd0),

   .dac33_ds_enable_0         (), //
   .dac33_ds_inc_0            (), //
   .dac33_ds_type_0           (), //
   .dac33_ds_scaling_factor_0 (), //
   .dac33_ds_offset_0         (), //
   .dac33_ds_phase_high_0     (), //
   .dac33_ds_phase_low_0      (), //
   .dac33_ds_out_clk_div_0    (), // 
   .dac33_ds_error_0          (1'd0), //
   .dac33_ds_change_count_0   (), 
   .dac33_ds_ctrl_0           (),
   .dac33_ds_fft_exec_cnt_0   (32'd0),
   .dac33_ds_fft_max_level_0  (32'd0),
   .dac33_ds_status_0         (8'd0),

   .dac_fab_reset0         (s_axi_aresetn   ),// This is a negedge reset despite the name
   .dac_fab_reset1         (s_axi_aresetn   ),
   .dac_fab_reset2         (s_axi_aresetn   ),
   .dac_fab_reset3         (s_axi_aresetn   ),

   .dac_fab_clk0           (s_axi_aclk      ),
   .dac_fab_clk1           (s_axi_aclk      ),
   .dac_fab_clk2           (s_axi_aclk      ),
   .dac_fab_clk3           (s_axi_aclk      ),

   .enable                 (global_enable   ),

   .done_axi_reg           (done_axi_reg    ), 
   .error_axi_reg          (error_axi_reg   ), 
   .clock_enable_reg       (clock_enable_reg),

   .timeout_enable_in      (1'd0            ),
   .timeout_value_in       (12'd0           ),

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


endmodule
