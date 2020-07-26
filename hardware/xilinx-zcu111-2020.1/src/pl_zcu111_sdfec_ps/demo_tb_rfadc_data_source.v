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

module demo_tb_rfadc_data_source #(
  parameter  p_connections       = 8,
  parameter  p_connection_width  = 16,
  parameter  p_useable_width     = 12,
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

   input  wire [31:0]    clk_phase_hl_00,
   output wire [63:0]    vout_00_p,
   output wire [63:0]    vout_00_n,

   // AXI-Lite Clock/Reset
   input  wire           s_axi_aclk   ,
   input  wire           s_axi_aresetn
  
  );
// ----------------------------------------------------------------------------
// Wire declarations for slices 0_01
// ----------------------------------------------------------------------------
wire                          global_enable;
wire      [p_connections-1:0] s00_enable         ; //
wire    [p_useable_width-1:0] s00_inc            ; //
wire  [p_data_type_width-1:0] s00_type           ; //
wire                   [31:0] s00_scaling_factor ; //
wire                   [31:0] s00_offset         ; //
wire                   [15:0] s00_phase_high     ; //
wire                   [15:0] s00_phase_low      ; //

// ----------------------------------------------------------------------------
// Data generator tile 0
// ----------------------------------------------------------------------------
demo_tb_rfadc_tile_source tile_source_0_i(

	// Connect data source 0
   .s0_init           ({p_useable_width{1'b0}}),  //
   .s0_enable         (s00_enable[0] & global_enable), //
   .s0_inc            (s00_inc             ), //
   .s0_type           (s00_type            ), //
   .s0_scaling_factor (s00_scaling_factor  ), //
   .s0_offset         (s00_offset          ), //
   .s0_clk_phase_hl   (clk_phase_hl_00     ),
   .vout_0_p          (vout_00_p           ),
   .vout_0_n          (vout_00_n           ),

	// Connect data source 1
   .s1_init           ({p_useable_width{1'b0}}),  //
   .s1_scaling_factor (32'd0  ), //
   .s1_offset         (32'd0  ), //
   .s1_enable         (1'b0   ),  //
   .s1_inc            ({p_useable_width{1'b0}}),  //
   .s1_type           ({p_data_type_width{1'b0}}),  //
   .s1_clk_phase_hl   (32'd0  ),
   .vout_1_p          (),
   .vout_1_n          (),

	// Connect data source 2
   .s2_init           ({p_useable_width{1'b0}}),  //
   .s2_scaling_factor (32'd0  ), //
   .s2_offset         (32'd0  ), //
   .s2_enable         (1'b0   ),  //
   .s2_inc            ({p_useable_width{1'b0}}),  //
   .s2_type           ({p_data_type_width{1'b0}}),  //
   .s2_clk_phase_hl   (32'd0  ),
   .vout_2_p          (),
   .vout_2_n          (),

	// Connect data source 3
   .s3_init           ({p_useable_width{1'b0}}),  //
   .s3_scaling_factor (32'd0  ), //
   .s3_offset         (32'd0  ), //
   .s3_enable         (1'b0   ),  //
   .s3_inc            ({p_useable_width{1'b0}}),  //
   .s3_type           ({p_data_type_width{1'b0}}),  //
   .s3_clk_phase_hl   (32'd0  ),
   .vout_3_p          (),
   .vout_3_n          (),

  .status             ()

  );

// ----------------------------------------------------------------------------
// Data generator tile 1
// ----------------------------------------------------------------------------
demo_tb_rfadc_tile_source tile_source_1_i(

	// Connect data source 0
   .s0_init           ({p_useable_width{1'b0}}),  //
   .s0_scaling_factor (32'd0  ), //
   .s0_offset         (32'd0  ), //
   .s0_enable         (1'b0   ),  //
   .s0_inc            ({p_useable_width{1'b0}}),  //
   .s0_type           ({p_data_type_width{1'b0}}),  //
   .s0_clk_phase_hl   (32'd0  ),
   .vout_0_p          (),
   .vout_0_n          (),

	// Connect data source 1
   .s1_init           ({p_useable_width{1'b0}}),  //
   .s1_scaling_factor (32'd0  ), //
   .s1_offset         (32'd0  ), //
   .s1_enable         (1'b0   ),  //
   .s1_inc            ({p_useable_width{1'b0}}),  //
   .s1_type           ({p_data_type_width{1'b0}}),  //
   .s1_clk_phase_hl   (32'd0  ),
   .vout_1_p          (),
   .vout_1_n          (),

	// Connect data source 2
   .s2_init           ({p_useable_width{1'b0}}),  //
   .s2_scaling_factor (32'd0  ), //
   .s2_offset         (32'd0  ), //
   .s2_enable         (1'b0   ),  //
   .s2_inc            ({p_useable_width{1'b0}}),  //
   .s2_type           ({p_data_type_width{1'b0}}),  //
   .s2_clk_phase_hl   (32'd0  ),
   .vout_2_p          (),
   .vout_2_n          (),

	// Connect data source 3
   .s3_init           ({p_useable_width{1'b0}}),  //
   .s3_scaling_factor (32'd0  ), //
   .s3_offset         (32'd0  ), //
   .s3_enable         (1'b0   ),  //
   .s3_inc            ({p_useable_width{1'b0}}),  //
   .s3_type           ({p_data_type_width{1'b0}}),  //
   .s3_clk_phase_hl   (32'd0  ),
   .vout_3_p          (),
   .vout_3_n          (),

  .status             ()

  );

// ----------------------------------------------------------------------------
// Data generator tile 2
// ----------------------------------------------------------------------------
demo_tb_rfadc_tile_source tile_source_2_i(

	// Connect data source 0
   .s0_init           ({p_useable_width{1'b0}}),  //
   .s0_scaling_factor (32'd0  ), //
   .s0_offset         (32'd0  ), //
   .s0_enable         (1'b0   ),  //
   .s0_inc            ({p_useable_width{1'b0}}),  //
   .s0_type           ({p_data_type_width{1'b0}}),  //
   .s0_clk_phase_hl   (32'd0  ),
   .vout_0_p          (),
   .vout_0_n          (),

	// Connect data source 1
   .s1_init           ({p_useable_width{1'b0}}),  //
   .s1_scaling_factor (32'd0  ), //
   .s1_offset         (32'd0  ), //
   .s1_enable         (1'b0   ),  //
   .s1_inc            ({p_useable_width{1'b0}}),  //
   .s1_type           ({p_data_type_width{1'b0}}),  //
   .s1_clk_phase_hl   (32'd0  ),
   .vout_1_p          (),
   .vout_1_n          (),

	// Connect data source 2
   .s2_init           ({p_useable_width{1'b0}}),  //
   .s2_scaling_factor (32'd0  ), //
   .s2_offset         (32'd0  ), //
   .s2_enable         (1'b0   ),  //
   .s2_inc            ({p_useable_width{1'b0}}),  //
   .s2_type           ({p_data_type_width{1'b0}}),  //
   .s2_clk_phase_hl   (32'd0  ),
   .vout_2_p          (),
   .vout_2_n          (),

	// Connect data source 3
   .s3_init           ({p_useable_width{1'b0}}),  //
   .s3_scaling_factor (32'd0  ), //
   .s3_offset         (32'd0  ), //
   .s3_enable         (1'b0   ),  //
   .s3_inc            ({p_useable_width{1'b0}}),  //
   .s3_type           ({p_data_type_width{1'b0}}),  //
   .s3_clk_phase_hl   (32'd0  ),
   .vout_3_p          (),
   .vout_3_n          (),

  .status             ()

  );

// ----------------------------------------------------------------------------
// Data generator tile 3
// ----------------------------------------------------------------------------
demo_tb_rfadc_tile_source tile_source_3_i(

	// Connect data source 0
   .s0_init           ({p_useable_width{1'b0}}),  //
   .s0_scaling_factor (32'd0  ), //
   .s0_offset         (32'd0  ), //
   .s0_enable         (1'b0   ),  //
   .s0_inc            ({p_useable_width{1'b0}}),  //
   .s0_type           ({p_data_type_width{1'b0}}),  //
   .s0_clk_phase_hl   (32'd0  ),
   .vout_0_p          (),
   .vout_0_n          (),

	// Connect data source 1
   .s1_init           ({p_useable_width{1'b0}}),  //
   .s1_scaling_factor (32'd0  ), //
   .s1_offset         (32'd0  ), //
   .s1_enable         (1'b0   ),  //
   .s1_inc            ({p_useable_width{1'b0}}),  //
   .s1_type           ({p_data_type_width{1'b0}}),  //
   .s1_clk_phase_hl   (32'd0  ),
   .vout_1_p          (),
   .vout_1_n          (),

	// Connect data source 2
   .s2_init           ({p_useable_width{1'b0}}),  //
   .s2_scaling_factor (32'd0  ), //
   .s2_offset         (32'd0  ), //
   .s2_enable         (1'b0   ),  //
   .s2_inc            ({p_useable_width{1'b0}}),  //
   .s2_type           ({p_data_type_width{1'b0}}),  //
   .s2_clk_phase_hl   (32'd0  ),
   .vout_2_p          (),
   .vout_2_n          (),

	// Connect data source 3
   .s3_init           ({p_useable_width{1'b0}}),  //
   .s3_scaling_factor (32'd0  ), //
   .s3_offset         (32'd0  ), //
   .s3_enable         (1'b0   ),  //
   .s3_inc            ({p_useable_width{1'b0}}),  //
   .s3_type           ({p_data_type_width{1'b0}}),  //
   .s3_clk_phase_hl   (32'd0  ),
   .vout_3_p          (),
   .vout_3_n          (),

  .status             ()

  );


//-----------------------------------------------------------------------------
// Control register map. Reusing the same bank as generated for the DAC
// data path control, hence the naming on the block below
//-----------------------------------------------------------------------------
demo_tb_hsadc_ctrl hsadc_exdes_ctrl_i (
   .adc00_enable_0         (s00_enable        ), //
   .adc00_dg_inc_0         (s00_inc           ), //
   .adc00_dg_type_0        (s00_type          ), //
   .adc00_scaling_factor_0 (s00_scaling_factor), //
   .adc00_offset_0         (s00_offset        ), //
   .adc00_phase_high_0     (s00_phase_high    ), //
   .adc00_phase_low_0      (s00_phase_low     ), //

   .adc01_enable_0         (), //
   .adc01_dg_inc_0         (), //
   .adc01_dg_type_0        (), //
   .adc01_scaling_factor_0 (), //
   .adc01_offset_0         (), //
   .adc01_phase_high_0     (), //
   .adc01_phase_low_0      (), //

   .adc02_enable_0         (), //
   .adc02_dg_inc_0         (), //
   .adc02_dg_type_0        (), //
   .adc02_scaling_factor_0 (), //
   .adc02_offset_0         (), //
   .adc02_phase_high_0     (), //
   .adc02_phase_low_0      (), //

   .adc03_enable_0         (), //
   .adc03_dg_inc_0         (), //
   .adc03_dg_type_0        (), //
   .adc03_scaling_factor_0 (), //
   .adc03_offset_0         (), //
   .adc03_phase_high_0     (), //
   .adc03_phase_low_0      (), //

   .adc10_enable_0         (), //
   .adc10_dg_inc_0         (), //
   .adc10_dg_type_0        (), //
   .adc10_scaling_factor_0 (), //
   .adc10_offset_0         (), //
   .adc10_phase_high_0     (), //
   .adc10_phase_low_0      (), //

   .adc11_enable_0         (), //
   .adc11_dg_inc_0         (), //
   .adc11_dg_type_0        (), //
   .adc11_scaling_factor_0 (), //
   .adc11_offset_0         (), //
   .adc11_phase_high_0     (), //
   .adc11_phase_low_0      (), //

   .adc12_enable_0         (), //
   .adc12_dg_inc_0         (), //
   .adc12_dg_type_0        (), //
   .adc12_scaling_factor_0 (), //
   .adc12_offset_0         (), //
   .adc12_phase_high_0     (), //
   .adc12_phase_low_0      (), //

   .adc13_enable_0         (), //
   .adc13_dg_inc_0         (), //
   .adc13_dg_type_0        (), //
   .adc13_scaling_factor_0 (), //
   .adc13_offset_0         (), //
   .adc13_phase_high_0     (), //
   .adc13_phase_low_0      (), //

   .adc20_enable_0         (), //
   .adc20_dg_inc_0         (), //
   .adc20_dg_type_0        (), //
   .adc20_scaling_factor_0 (), //
   .adc20_offset_0         (), //
   .adc20_phase_high_0     (), //
   .adc20_phase_low_0      (), //

   .adc21_enable_0         (), //
   .adc21_dg_inc_0         (), //
   .adc21_dg_type_0        (), //
   .adc21_scaling_factor_0 (), //
   .adc21_offset_0         (), //
   .adc21_phase_high_0     (), //
   .adc21_phase_low_0      (), //

   .adc22_enable_0         (), //
   .adc22_dg_inc_0         (), //
   .adc22_dg_type_0        (), //
   .adc22_scaling_factor_0 (), //
   .adc22_offset_0         (), //
   .adc22_phase_high_0     (), //
   .adc22_phase_low_0      (), //

   .adc23_enable_0         (), //
   .adc23_dg_inc_0         (), //
   .adc23_dg_type_0        (), //
   .adc23_scaling_factor_0 (), //
   .adc23_offset_0         (), //
   .adc23_phase_high_0     (), //
   .adc23_phase_low_0      (), //

   .adc30_enable_0         (), //
   .adc30_dg_inc_0         (), //
   .adc30_dg_type_0        (), //
   .adc30_scaling_factor_0 (), //
   .adc30_offset_0         (), //
   .adc30_phase_high_0     (), //
   .adc30_phase_low_0      (), //

   .adc31_enable_0         (), //
   .adc31_dg_inc_0         (), //
   .adc31_dg_type_0        (), //
   .adc31_scaling_factor_0 (), //
   .adc31_offset_0         (), //
   .adc31_phase_high_0     (), //
   .adc31_phase_low_0      (), //

   .adc32_enable_0         (), //
   .adc32_dg_inc_0         (), //
   .adc32_dg_type_0        (), //
   .adc32_scaling_factor_0 (), //
   .adc32_offset_0         (), //
   .adc32_phase_high_0     (), //
   .adc32_phase_low_0      (), //

   .adc33_enable_0         (), //
   .adc33_dg_inc_0         (), //
   .adc33_dg_type_0        (), //
   .adc33_scaling_factor_0 (), //
   .adc33_offset_0         (), //
   .adc33_phase_high_0     (), //
   .adc33_phase_low_0      (), //

   .adc_fab_clk0           (s_axi_aclk      ),
   .adc_fab_clk1           (s_axi_aclk      ),
   .adc_fab_clk2           (s_axi_aclk      ),
   .adc_fab_clk3           (s_axi_aclk      ),

   .adc_fab_reset0         (s_axi_aresetn   ),// This is a negedge reset despite the name
   .adc_fab_reset1         (s_axi_aresetn   ),
   .adc_fab_reset2         (s_axi_aresetn   ),
   .adc_fab_reset3         (s_axi_aresetn   ), 

   .enable                 (global_enable   ),

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
