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

`define EXDES_ADC_RAM_SINK

(* DowngradeIPIdentifiedWarnings="yes" *)
module exdes_rfadc_data_sink #(
  parameter  p_connections       = 8,
  parameter  p_connection_width  = 16
) (

   // AXI-Lite Interface
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWADDR"  *) input  wire [17:0]  s_axi_awaddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWVALID" *) input  wire         s_axi_awvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi AWREADY" *) output wire         s_axi_awready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WDATA"   *) input  wire [31:0]  s_axi_wdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WVALID"  *) input  wire         s_axi_wvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WREADY"  *) output wire         s_axi_wready   , //
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi WSTRB"   *) input  wire  [3:0]  s_axi_wstrb    , //
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BRESP"   *) output wire  [1:0]  s_axi_bresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BVALID"  *) output wire         s_axi_bvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi BREADY"  *) input  wire         s_axi_bready   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARADDR"  *) input  wire [17:0]  s_axi_araddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARVALID" *) input  wire         s_axi_arvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi ARREADY" *) output wire         s_axi_arready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RDATA"   *) output wire [31:0]  s_axi_rdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RRESP"   *) output wire  [1:0]  s_axi_rresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RVALID"  *) output wire         s_axi_rvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi RREADY"  *) input  wire         s_axi_rready   ,  // 

   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 s00 TDATA" *)       input  wire [127:0] s00_tdata , //
   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 s00 TVALID" *)      input  wire         s00_tvalid, //
   (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 s00 TREADY" *)      output wire         s00_tready, //

   (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 s0_axis_clock CLK" *)
   (* X_INTERFACE_PARAMETER = "ASSOCIATED_BUSIF s00" *)
                                                                               input  wire         s0_axis_clock, //

   // Checker status for ADC path
   output reg            error_flag=0,
   output reg            done_flag=0,

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
localparam  p_useable_width     = 16;
localparam  p_useable_offset    = 0;
localparam  p_data_inc_val_init = 1;
localparam  p_change_width      = 12;
localparam  p_data_type_width   = 4;
localparam  p_increment_w       = 12;

// ----------------------------------------------------------------------------
// Variable declarations
// ----------------------------------------------------------------------------
wire        enable;
wire        timeout_enable;
wire [11:0] timeout_value;
reg  [1:0]  done_delay = 2'd3;
wire [15:0] done_axi_reg;
wire [15:0] error_axi_reg;

wire [0:0] error_bus;
wire [0:0] error_bus_rt;
wire [0:0] done_bus;
wire [0:0] done_bus_rt;
wire [3:0] axis_resetn_rt;
wire                                    [7:0] s00_ds_enable       ; //
wire                      [p_increment_w-1:0] s00_ds_inc          ; //
wire                  [p_data_type_width-1:0] s00_ds_type         ; //
wire                     [p_change_width-1:0] s00_ds_change_count ; //
wire                                    [1:0] s00_ds_control      ; //
wire                                          s00_ds_pulse_control; //
wire                                          s00_ds_status       ; //


// ----------------------------------------------------------------------------
// Data generator tile 0
// ----------------------------------------------------------------------------
`ifdef EXDES_ADC_RAM_SINK

xpm_mem_ds_dataCap  #( 

   .wordWidth(p_connection_width * 8)

) ds_slice_00 (

  .clk             (s0_axis_clock),
  .enable          (s00_ds_pulse_control), // This should be a pulse 
  .addrb           (s00_ds_inc  ),
  .doutb           (  ), 
  .working         (s00_ds_status  ), 
  .data_to_capture (s00_tdata)          

);

`else

ds_slice #(

   .p_cons          ( 8    ),
   .p_con_w            (p_connection_width ),
   .p_useable_w        (p_useable_width    ),
   .p_increment_w      (p_increment_w      ),
   .p_data_type_w      (p_data_type_width  ),
   .p_change_w         (p_change_width     )

) ds_slice_00 (
   .clk             (s0_axis_clock),
   //.ds_enable       (s00_ds_enable[7:0] & {8{s00_tvalid}}),
   .ds_enable       (s00_ds_enable[7:0]),
   .ds_inc          (s00_ds_inc          ),
   .ds_type         (s00_ds_type         ),
   .ds_in           (s00_tdata           ),
   .ds_change_count (s00_ds_change_count ),
   .ds_done         (done_bus[0]),
   .ds_error        (error_bus[0])
);

`endif

assign s00_tready = s00_ds_enable;

//-----------------------------------------------------------------------------
// Retime the error flags onto the AXI clock
//-----------------------------------------------------------------------------
xpm_cdc_single #(.SRC_INPUT_REG(0), .DEST_SYNC_FF(5)) cdc_error_0i (.src_clk(1'd0),.dest_clk (s_axi_aclk), .src_in (error_bus[0]), .dest_out (error_bus_rt[0]) );

always @(posedge s_axi_aclk)
   error_flag <= |error_bus_rt;

//-----------------------------------------------------------------------------
// Retime the done flags onto the AXI clock. Make output posedge sticky
//-----------------------------------------------------------------------------
xpm_cdc_single #(.SRC_INPUT_REG(0), .DEST_SYNC_FF(5)) cdc_done_0i (.src_clk(1'd0), .dest_clk (s_axi_aclk), .src_in (done_bus[0]), .dest_out (done_bus_rt[0]) );

always @(posedge s_axi_aclk) begin
   done_delay <= {done_delay[0],&done_bus_rt};
   if (~enable)
      done_flag <= 1'd0; 
   else 
      if (~done_delay[1] & done_delay[0])
         done_flag <= 1'd1; 
end

//-----------------------------------------------------------------------------
// Retime the AXIS resets for each tile
//-----------------------------------------------------------------------------
xpm_cdc_sync_rst #(.INIT(0), .INIT_SYNC_FF(1), .DEST_SYNC_FF(5)) cdc_arstn_0i ( .dest_clk (s0_axis_clock), .src_rst (s_axi_aresetn), .dest_rst (axis_resetn_rt[0]) );
assign axis_resetn_rt[1] = s_axi_aresetn;
assign axis_resetn_rt[2] = s_axi_aresetn;
assign axis_resetn_rt[3] = s_axi_aresetn;

//-----------------------------------------------------------------------------
// Create a Tile/Slice ordered bus for the AXI interface
//-----------------------------------------------------------------------------
assign done_axi_reg [ 0] = done_bus_rt [0];
assign error_axi_reg[ 0] = error_bus_rt[0];
assign done_axi_reg [ 1] = 1'd1;
assign error_axi_reg[ 1] = 1'd0;
assign done_axi_reg [ 2] = 1'd1;
assign error_axi_reg[ 2] = 1'd0;
assign done_axi_reg [ 3] = 1'd1;
assign error_axi_reg[ 3] = 1'd0;
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
// Control register map. Reusing the same bank as generated for the DAC
// data path control, hence the naming on the block below
//-----------------------------------------------------------------------------
rfadc_exdes_ctrl rfadc_exdes_ctrl_i (
   .adc00_ds_enable_0         (s00_ds_enable      ), //
   .adc00_ds_inc_0            (s00_ds_inc         ), //
   .adc00_ds_type_0           (s00_ds_type        ), //
   .adc00_ds_control_0        (s00_ds_control     ), //
   .adc00_ds_change_count_0   (s00_ds_change_count), //

   .adc00_ds_pulse_control_0  (s00_ds_pulse_control),
`ifdef EXDES_ADC_RAM_SINK
   .adc00_ds_status_0         (s00_ds_status ),
   .adc00_ds_data_0           (s00_tdata),
`else
   .adc00_ds_status_0         (1'b0  ),
   .adc00_ds_data_0           (128'd0),
`endif

   .adc01_ds_enable_0         (), //
   .adc01_ds_inc_0            (), //
   .adc01_ds_type_0           (), //
   .adc01_ds_control_0        (), //
   .adc01_ds_change_count_0   (), //

   .adc01_ds_pulse_control_0  (),
   .adc01_ds_status_0         (1'd0 ),
   .adc01_ds_data_0           (128'd0),

   .adc02_ds_enable_0         (), //
   .adc02_ds_inc_0            (), //
   .adc02_ds_type_0           (), //
   .adc02_ds_control_0        (), //
   .adc02_ds_change_count_0   (), //

   .adc02_ds_pulse_control_0  (),
   .adc02_ds_status_0         (1'd0 ),
   .adc02_ds_data_0           (128'd0),

   .adc03_ds_enable_0         (), //
   .adc03_ds_inc_0            (), //
   .adc03_ds_type_0           (), //
   .adc03_ds_control_0        (), //
   .adc03_ds_change_count_0   (), //

   .adc03_ds_pulse_control_0  (),
   .adc03_ds_status_0         (1'd0 ),
   .adc03_ds_data_0           (128'd0),

   .adc10_ds_enable_0         (), //
   .adc10_ds_inc_0            (), //
   .adc10_ds_type_0           (), //
   .adc10_ds_control_0        (), //
   .adc10_ds_change_count_0   (), //

   .adc10_ds_pulse_control_0  (),
   .adc10_ds_status_0         (1'd0 ),
   .adc10_ds_data_0           (128'd0),

   .adc11_ds_enable_0         (), //
   .adc11_ds_inc_0            (), //
   .adc11_ds_type_0           (), //
   .adc11_ds_control_0        (), //
   .adc11_ds_change_count_0   (), //

   .adc11_ds_pulse_control_0  (),
   .adc11_ds_status_0         (1'd0 ),
   .adc11_ds_data_0           (128'd0),

   .adc12_ds_enable_0         (), //
   .adc12_ds_inc_0            (), //
   .adc12_ds_type_0           (), //
   .adc12_ds_control_0        (), //
   .adc12_ds_change_count_0   (), //

   .adc12_ds_pulse_control_0  (),
   .adc12_ds_status_0         (1'd0 ),
   .adc12_ds_data_0           (128'd0),

   .adc13_ds_enable_0         (), //
   .adc13_ds_inc_0            (), //
   .adc13_ds_type_0           (), //
   .adc13_ds_control_0        (), //
   .adc13_ds_change_count_0   (), //

   .adc13_ds_pulse_control_0  (),
   .adc13_ds_status_0         (1'd0 ),
   .adc13_ds_data_0           (128'd0),

   .adc20_ds_enable_0         (), //
   .adc20_ds_inc_0            (), //
   .adc20_ds_type_0           (), //
   .adc20_ds_control_0        (), //
   .adc20_ds_change_count_0   (), //

   .adc20_ds_pulse_control_0  (),
   .adc20_ds_status_0         (1'd0 ),
   .adc20_ds_data_0           (128'd0),

   .adc21_ds_enable_0         (), //
   .adc21_ds_inc_0            (), //
   .adc21_ds_type_0           (), //
   .adc21_ds_control_0        (), //
   .adc21_ds_change_count_0   (), //

   .adc21_ds_pulse_control_0  (),
   .adc21_ds_status_0         (1'd0 ),
   .adc21_ds_data_0           (128'd0),

   .adc22_ds_enable_0         (), //
   .adc22_ds_inc_0            (), //
   .adc22_ds_type_0           (), //
   .adc22_ds_control_0        (), //
   .adc22_ds_change_count_0   (), //

   .adc22_ds_pulse_control_0  (),
   .adc22_ds_status_0         (1'd0 ),
   .adc22_ds_data_0           (128'd0),

   .adc23_ds_enable_0         (), //
   .adc23_ds_inc_0            (), //
   .adc23_ds_type_0           (), //
   .adc23_ds_control_0        (), //
   .adc23_ds_change_count_0   (), //

   .adc23_ds_pulse_control_0  (),
   .adc23_ds_status_0         (1'd0 ),
   .adc23_ds_data_0           (128'd0),

   .adc30_ds_enable_0         (), //
   .adc30_ds_inc_0            (), //
   .adc30_ds_type_0           (), //
   .adc30_ds_control_0        (), //
   .adc30_ds_change_count_0   (), //

   .adc30_ds_pulse_control_0  (),
   .adc30_ds_status_0         (1'd0 ),
   .adc30_ds_data_0           (128'd0),

   .adc31_ds_enable_0         (), //
   .adc31_ds_inc_0            (), //
   .adc31_ds_type_0           (), //
   .adc31_ds_control_0        (), //
   .adc31_ds_change_count_0   (), //

   .adc31_ds_pulse_control_0  (),
   .adc31_ds_status_0         (1'd0 ),
   .adc31_ds_data_0           (128'd0),

   .adc32_ds_enable_0         (), //
   .adc32_ds_inc_0            (), //
   .adc32_ds_type_0           (), //
   .adc32_ds_control_0        (), //
   .adc32_ds_change_count_0   (), //

   .adc32_ds_pulse_control_0  (),
   .adc32_ds_status_0         (1'd0 ),
   .adc32_ds_data_0           (128'd0),

   .adc33_ds_enable_0         (), //
   .adc33_ds_inc_0            (), //
   .adc33_ds_type_0           (), //
   .adc33_ds_control_0        (), //
   .adc33_ds_change_count_0   (), //

   .adc33_ds_pulse_control_0  (),
   .adc33_ds_status_0         (1'd0 ),
   .adc33_ds_data_0           (128'd0),


   .adc_fab_clk0           (s0_axis_clock),
   .adc_fab_resetn0        (axis_resetn_rt[0] ), // Negedge reset
   .adc_fab_clk1           (s_axi_aclk     ),
   .adc_fab_resetn1        (axis_resetn_rt[1] ), // Negedge reset
   .adc_fab_clk2           (s_axi_aclk     ),
   .adc_fab_resetn2        (axis_resetn_rt[2] ), // Negedge reset
   .adc_fab_clk3           (s_axi_aclk     ),
   .adc_fab_resetn3        (axis_resetn_rt[3] ), // Negedge reset

   .enable                 (enable          ),
   .timeout_enable         (timeout_enable  ),
   .timeout_value          (timeout_value   ),
   .error                  (error_flag      ),

   .timeout_enable_in      (timeout_enable  ),
   .timeout_value_in       (timeout_value   ), 

   .done_axi_reg           (done_axi_reg    ), 
   .error_axi_reg          (error_axi_reg   ), 

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

`ifdef EXDES_ADC_RAM_SINK
//------------------------------------------------------------------------------
// RAM Data capture module.
//------------------------------------------------------------------------------
module xpm_mem_ds_dataCap #(
   parameter wordWidth     = 32,
   parameter addrWidth     = 8
) (

  input  wire                    clk            ,
  input  wire                    enable         , // This should be a pulse 
  input  wire [addrWidth-1:0]    addrb          ,
  output wire [wordWidth-1:0]    doutb          , 
  output reg                     working=0      , 
  input  wire [wordWidth-1:0]    data_to_capture          

);

// 
localparam wordsInMemory = 2 ** addrWidth;

// Internal variables
reg                    wea   =0; // 
reg [addrWidth-1:0]    addra =0; // 
reg [wordWidth-1:0]    dina  =0; // 

// Always keep our mem 2^^n so this can just rollover
always @(posedge clk) begin
   if (~working) begin
      addra   <=  'd0;
      dina    <=  'd0;
      wea     <=  enable;
      working <=  enable; // Set on an enable pulse. Enable is ignored until complete
   end else begin
      addra <= addra + 'd1;
      dina  <= data_to_capture;
      if (addra == (wordsInMemory - 1)) begin
         // Once we reach the top of memory we stop.
         wea     <= 1'd0;
         working <= 1'b0;      
      end else begin
         wea     <= 1'd1;
         working <= 1'b1;           
      end
   end
end

//-----------------------------------------------------------------------------
// Instance the wrapped xpm wrapper
//-----------------------------------------------------------------------------
xpm_mem_ds_wrap2 #(

   .wordWidth     (wordWidth),
   .wordsInMemory (wordsInMemory),
   .addrWidth     (addrWidth)
   
) xpm_mem_ds_wrap2_i (
.clk            (clk      ) ,
.wea            (wea      ) ,
.addra          (addra    ) ,
.dina           (dina     ) ,
.addrb          (addrb    ) ,
.doutb          (doutb    ) 

);

endmodule

//-----------------------------------------------------------------------------
// Wrap the XPM wrapper with fixed enables
//-----------------------------------------------------------------------------
module xpm_mem_ds_wrap2 #(
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

xpm_mem_ds_sdpram_wrap #(

   .wordWidth     (wordWidth    ),
   .wordsInMemory (wordsInMemory),
   .addrWidth     (addrWidth    )
   
) xpm_mem_ds_sdpram_wrap_i (
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
module xpm_mem_ds_sdpram_wrap #(
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
