//----------------------------------------------------------------------------
// Title : Demo Testbench
// Project : Ultrascale+ RF Data Converter Subsystem
//----------------------------------------------------------------------------
// File : demo_tb.v
//----------------------------------------------------------------------------
//
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
//
//----------------------------------------------------------------------------

`timescale 1ps / 1ps

// List of instance paths used in the AXI transaction messaging blocks
`define DUT_AXI_PATH     dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst

// Allow hierarchial probing of the design. Use in functional simulation only
`define ENABLE_VERILOG_HIER_PROBES
// `define ENABLE_VERILOG_SM_PROBES

module demo_tb ;

//-----------------------------------------------------------------------------
// declare TB signals
//-----------------------------------------------------------------------------
wire           s_axi_aclk    ; //   
wire           s_axi_aresetn ; //  
wire           s_axi_tb_aresetn ; // 
wire [31:0]    s_axi_awaddr  ; // 
wire           s_axi_awvalid ; //  
wire           s_axi_awready ; // 
wire [31:0]    s_axi_wdata   ; //  
wire           s_axi_wvalid  ; //  
wire           s_axi_wready  ; //  
wire [ 1:0]    s_axi_bresp   ; //  
wire           s_axi_bvalid  ; //  
wire           s_axi_bready  ; //   
wire [31:0]    s_axi_araddr  ; //   
wire           s_axi_arvalid ; //  
wire           s_axi_arready ; // 
wire [31:0]    s_axi_rdata   ; //  
wire [ 1:0]    s_axi_rresp   ; //  
wire           s_axi_rvalid  ; // 
wire           s_axi_rready  ; // 
wire           seq_done      ; // Sequencer done flag 
wire           dac_sink_error_flag; //
wire           dac_sink_done_flag ; //
wire           adc_sink_error_flag; //
wire           adc_sink_done_flag ; //
wire [3:0]     external_signal_bus; //
wire [7:0]     tile_clock_enable;   //


//-----------------------------------------------------------------------------
// Sequencer to generate AXI control to exdes and textbench
// Refer to demo_tb_axi4l_nano_seq.v to modify the AXI test sequence.
//-----------------------------------------------------------------------------
demo_tb_axi4l_nano_seq sequencer_i (

   .axi_awaddr             (s_axi_awaddr       ) , // 
   .axi_awvalid            (s_axi_awvalid      ) , // 
   .axi_awready            (s_axi_awready      ) , // 
   .axi_wdata              (s_axi_wdata        ) , // 
   .axi_wvalid             (s_axi_wvalid       ) , // 
   .axi_wready             (s_axi_wready       ) , // 
   .axi_bresp              (s_axi_bresp        ) , // 
   .axi_bvalid             (s_axi_bvalid       ) , // 
   .axi_bready             (s_axi_bready       ) , // 
   .axi_araddr             (s_axi_araddr       ) , // 
   .axi_arvalid            (s_axi_arvalid      ) , // 
   .axi_arready            (s_axi_arready      ) , // 
   .axi_rdata              (s_axi_rdata        ) , // 
   .axi_rresp              (s_axi_rresp        ) , // 
   .axi_rvalid             (s_axi_rvalid       ) , // 
   .axi_rready             (s_axi_rready       ) , // 

   .clk                    (s_axi_aclk         ) , //
   .reset                  (1'd0               ) , //
   .axi_message_enable     (axi_message_enable ),
   .external_signal_bus    (external_signal_bus) , //
   .tile_clock_enable      (tile_clock_enable  ) , //
   .rising_stop_trigger    (seq_done           ) , //
   .axi_aresetn            (                   ) , // 
   .int_axi_aresetn        (s_axi_aresetn      ) , //  
   .int_tb_aresetn         (s_axi_tb_aresetn   ) , //  
   .seq_done               (seq_done           )   // 
);

assign external_signal_bus[0] = dac_sink_error_flag;
assign external_signal_bus[1] = adc_sink_error_flag;
assign external_signal_bus[2] = dac_sink_done_flag;
assign external_signal_bus[3] = adc_sink_done_flag;

//-----------------------------------------------------------------------------
// This block contains the DUT and the real number sink/sources for the AMS IP.
//-----------------------------------------------------------------------------
demo_tb_dut_checker dut_and_data_i (

   .s_axi_awaddr           (s_axi_awaddr[21:0]) , // 
   .s_axi_awvalid          (s_axi_awvalid     ) , // 
   .s_axi_awready          (s_axi_awready     ) , // 
   .s_axi_wdata            (s_axi_wdata       ) , //
   .s_axi_wstrb            (4'hf              ) , // 
   .s_axi_wvalid           (s_axi_wvalid      ) , // 
   .s_axi_wready           (s_axi_wready      ) , // 
   .s_axi_bresp            (s_axi_bresp       ) , // 
   .s_axi_bvalid           (s_axi_bvalid      ) , // 
   .s_axi_bready           (s_axi_bready      ) , // 
   .s_axi_araddr           (s_axi_araddr[21:0]) , // 
   .s_axi_arvalid          (s_axi_arvalid     ) , // 
   .s_axi_arready          (s_axi_arready     ) , // 
   .s_axi_rdata            (s_axi_rdata       ) , // 
   .s_axi_rresp            (s_axi_rresp       ) , // 
   .s_axi_rvalid           (s_axi_rvalid      ) , // 
   .s_axi_rready           (s_axi_rready      ) , //

   .tile_clock_enable      (tile_clock_enable ) , // 
   .clock_enable_reg       (),

   .dac_sink_error_flag    (dac_sink_error_flag),
   .dac_sink_done_flag     (dac_sink_done_flag ),
   .adc_sink_error_flag    (adc_sink_error_flag),
   .adc_sink_done_flag     (adc_sink_done_flag ),
   
   .s_axi_aclk             (s_axi_aclk        ) , //
   .s_axi_aresetn          (s_axi_aresetn     ) , //  
   .s_axi_tb_aresetn       (s_axi_tb_aresetn  )   //  
);

//-----------------------------------------------------------------------------
// Decodes AXI transaction to the IP and "pretty" prints message to the screen
//-----------------------------------------------------------------------------
`ifdef ENABLE_VERILOG_HIER_PROBES
demo_tb_axi_transaction_decode_hsams transaction_decode_i (
   .s_axi_aclk             ( `DUT_AXI_PATH.s_axi_aclk           ),
   .s_axi_aresetn          ( `DUT_AXI_PATH.s_axi_aresetn        ),
   .enable                 (  axi_message_enable                ),
   .s_axi_awaddr           ( {14'd0,`DUT_AXI_PATH.s_axi_awaddr} ),
   .s_axi_awvalid          ( `DUT_AXI_PATH.s_axi_awvalid        ),
   .s_axi_awready          ( `DUT_AXI_PATH.s_axi_awready        ),
   .s_axi_wdata            ( `DUT_AXI_PATH.s_axi_wdata          ),
   .s_axi_wvalid           ( `DUT_AXI_PATH.s_axi_wvalid         ),
   .s_axi_wready           ( `DUT_AXI_PATH.s_axi_wready         ),
   .s_axi_bresp            ( `DUT_AXI_PATH.s_axi_bresp          ),
   .s_axi_bvalid           ( `DUT_AXI_PATH.s_axi_bvalid         ),
   .s_axi_bready           ( `DUT_AXI_PATH.s_axi_bready         ),
   .s_axi_araddr           ( {14'd0,`DUT_AXI_PATH.s_axi_araddr} ),
   .s_axi_arvalid          ( `DUT_AXI_PATH.s_axi_arvalid        ),
   .s_axi_arready          ( `DUT_AXI_PATH.s_axi_arready        ),
   .s_axi_rdata            ( `DUT_AXI_PATH.s_axi_rdata          ),
   .s_axi_rresp            ( `DUT_AXI_PATH.s_axi_rresp          ),
   .s_axi_rvalid           ( `DUT_AXI_PATH.s_axi_rvalid         ),
   .s_axi_rready           ( `DUT_AXI_PATH.s_axi_rready         )
);
`endif

//-----------------------------------------------------------------------------
// Interface signal range measurement
//-----------------------------------------------------------------------------
demo_tb_signal_ranges sig_range_stats (

   .seq_done_adc           (adc_sink_done_flag),
   .seq_done_dac           (dac_sink_done_flag)

);

//-----------------------------------------------------------------------------
// RFAMS Analog Real pins for easy reference
//-----------------------------------------------------------------------------
`ifndef DO_NOT_USE_RFAMS_REAL_SIGNAL_FORCE
// ADC
real adc0_01_p;
real adc0_01_n;

always @ (*) begin
   // Map the ADC signals to top level. Probed at UNSIM level for driver confidence
   //adc0_01_p = $bitstoreal(dut_and_data_i.adc_source.vout_001_p);
   //adc0_01_n = $bitstoreal(dut_and_data_i.adc_source.vout_001_n);
   adc0_01_p = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST._vin_i01_p;
   adc0_01_n = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST._vin_i01_n;
   sig_range_stats.adc0_01_a.sig_p = adc0_01_p;
   sig_range_stats.adc0_01_a.sig_n = adc0_01_n;
end

// DAC
real dac00_p;
real dac00_n;

always @ (*) begin
   // Map the DAC signals to the top level
   dac00_p = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST._vout0_p;
   dac00_n = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST._vout0_n;
   sig_range_stats.dac00_a.sig_p = dac00_p;
   sig_range_stats.dac00_a.sig_n = dac00_n;
end
`endif

//-----------------------------------------------------------------------------
// Probe data interfaces for EOU
//-----------------------------------------------------------------------------
`ifdef ENABLE_VERILOG_HIER_PROBES
// ADC - 00
reg [127:0] adc00_axis_tdata ; //
reg         adc00_axis_tvalid; //
reg         adc00_axis_tready; //

// DAC - 00
reg [255:0] dac00_axis_tdata ; //
reg         dac00_axis_tvalid; //
reg         dac00_axis_tready; //

always @ (*) begin
   adc00_axis_tdata  = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.m00_axis_tdata;
   adc00_axis_tvalid = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.m00_axis_tvalid;
   adc00_axis_tready = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.m00_axis_tready;
   sig_range_stats.adc00_x.sig_axis_tdata = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.m00_axis_tdata;
   sig_range_stats.adc00_x.sig_axis_valid = adc00_axis_tvalid & adc00_axis_tready;
   dac00_axis_tdata  = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.s00_axis_tdata;
   dac00_axis_tvalid = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.s00_axis_tvalid;
   dac00_axis_tready = dut_and_data_i.DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.s00_axis_tready;
   sig_range_stats.dac00_x.sig_axis_tdata = dac00_axis_tdata;
   sig_range_stats.dac00_x.sig_axis_valid = dac00_axis_tvalid & dac00_axis_tready;
end
`endif

endmodule

//-----------------------------------------------------------------------------
// Module to report signal ranges
//-----------------------------------------------------------------------------
module demo_tb_signal_ranges #(
   parameter p_data_width = 16
) ( 
   input wire seq_done_adc, 
   input wire seq_done_dac
);

//-----------------------------------------------------------------------------
// Probe analog interfaces for EOU
//-----------------------------------------------------------------------------
dtb_sig_range_analog #(.p_id("<<-----        ADC0_01"),.p_code_w(12)) adc0_01_a (.seq_done(seq_done_adc), .enable_toggle_time(1'd0));
// DAC - 00
dtb_sig_range_analog #(.p_id("       ----->> DAC00"),.p_code_w(14)) dac00_a (.seq_done(seq_done_dac), .enable_toggle_time(1'd1));
   
//-----------------------------------------------------------------------------
// Probe data interfaces for EOU
//-----------------------------------------------------------------------------
dtb_sig_range_axis   #(.p_id("<<-----        ADC00"))  adc00_x (.seq_done(seq_done_adc), .enable_toggle_time(1'd1));
dtb_sig_range_axis   #(.p_id("       ----->> DAC00"))  dac00_x (.seq_done(seq_done_dac), .enable_toggle_time(1'd0));
   
endmodule

//-----------------------------------------------------------------------------
// Module to report AXI Stream code range
//-----------------------------------------------------------------------------
module dtb_sig_range_axis #(
   parameter p_data_width = 16,
   parameter p_id = ""
) ( 
   input wire seq_done,
   input wire enable_toggle_time
);

reg     [255:0] sig_axis_tdata ; //
reg             sig_axis_valid; //

integer         transitions = 0; //
integer         sig_axis_tdata_maxval = 0; //
integer         sig_axis_tdata_minval = (2**31)-1; //
integer         sig_axis_tdata_sign_extended; //
integer         sig_axis_tdata_made_positive; //

localparam p_transition_limit = 20;

always @ (sig_axis_tdata) begin
   if (sig_axis_valid & enable_toggle_time)
      transitions = transitions + 'd1;
end

`ifdef QUESTA_REPORT_UTC_TIME
always @ (posedge (transitions == p_transition_limit)) begin
   $write("%s AXI-Stream started @", p_id);
   $system("date -u +%Y%m%d_%H%M%S");
end
`endif

always @ (*) begin
   
   // Perform a "cast" from the 16 bit net to an integer to get +-values for GT/LT comparrisons.
   sig_axis_tdata_sign_extended = {{32 - p_data_width{sig_axis_tdata[p_data_width-1]}},(sig_axis_tdata[p_data_width-1:0])};

end

always @ (*) begin
   
   // Then make +ve by adding the half the bit range
   sig_axis_tdata_made_positive = sig_axis_tdata_sign_extended + (2**(p_data_width - 1));

end

always @ (*) begin

   if (sig_axis_valid) begin
      if ((sig_axis_tdata_made_positive > sig_axis_tdata_maxval) ) begin
         #1 sig_axis_tdata_maxval = sig_axis_tdata_made_positive;
      end
   end

end

always @ (*) begin
   
   if (sig_axis_valid) begin
      if ((sig_axis_tdata_made_positive < sig_axis_tdata_minval) ) begin
         #1 sig_axis_tdata_minval = sig_axis_tdata_made_positive;
      end
   end

end

always @(posedge seq_done)
   $display("%s AXI-Stream range = %d", p_id, sig_axis_tdata_maxval - sig_axis_tdata_minval);
   
endmodule

//-----------------------------------------------------------------------------
// Module to calculate analog signal code range
//-----------------------------------------------------------------------------
module dtb_sig_range_analog #(
   parameter p_code_w     = 16,
   parameter p_max_r      = 1.12/2,
   parameter p_id         = "",
   parameter p_tcount_max = 20
) ( 
   input wire seq_done,
   input wire enable_toggle_time
);

localparam plsb_value = p_max_r/(2**p_code_w);

//-----------------------------------------------------------------------------
// Mechanism for displaying ranges on the DAC
//-----------------------------------------------------------------------------
// DAC
real sig_p;
real sig_n;
real sig_p_maxval=0;
real sig_p_minval=1;
real range;
real codes;

integer transition_count = 0;

always @ (*) begin
   
   if (transition_count > p_tcount_max) begin
      if ((sig_p > sig_p_maxval) ) begin
         #1 sig_p_maxval = sig_p;
      end

       if(sig_p == 0)
         sig_p_minval = 1;
       else
         if ((sig_p < sig_p_minval) ) begin
            #1 sig_p_minval = sig_p;
         end // else do nothing
   end
   
   transition_count = transition_count + 1;
   
end

`ifdef QUESTA_REPORT_UTC_TIME
always @ (posedge ((transition_count == p_tcount_max) & enable_toggle_time)) begin
   $write("%s Analog REAL started @", p_id);
   $system("date -u +%Y%m%d_%H%M%S");
end
`endif

always @(posedge seq_done) begin
   range = sig_p_maxval - sig_p_minval;
   codes = range/plsb_value;
   $display("%s Analog range = %.3f @%dbit = %.1f codes (%.1f%%)", p_id, range, p_code_w, codes, 100*codes/(2**p_code_w));
   end
   
endmodule

//-----------------------------------------------------------------------------
// Wrapper for the clock block. Allows direct USE in IPI with correct 
// frequencies. Note Clocks are generated from multiples of the sample rate in
// ps for correct operation in the simulator. The IPI clock frequencies are 
// generated his the High and Low phases in PS.
//-----------------------------------------------------------------------------
module demo_tb_clk_gen_wrap #( parameter axi_reset_cycles   = 100 )(

  input  wire [7:0]     tile_clock_enable,

  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 dac0_axis_aclk CLK" *)
  (* X_INTERFACE_PARAMETER = "FREQ_HZ 400000000" *)
  output wire           dac0_axis_aclk      ,
  output wire           dac0_clk_p          ,
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 adc0_axis_aclk CLK" *)
  (* X_INTERFACE_PARAMETER = "FREQ_HZ 250000000" *)
  output wire           adc0_axis_aclk      ,
  output wire           adc0_clk_p          ,

  // AXI-Lite Control/Status
   (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 axi_resetn RST" *)
   (* X_INTERFACE_PARAMETER = "POLARITY ACTIVE_LOW" *)
  output wire           axi_resetn , 
   (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 axi_reset  RST" *)
   (* X_INTERFACE_PARAMETER = "POLARITY ACTIVE_HIGH" *)
  output wire           axi_reset  , 
  output wire           s_axi_aclk   

) ;

//-----------------------------------------------------------------------------
// Clock generator block
// This is wrapped with the port settings fixed so this block can be used
// directly in IPI
//-----------------------------------------------------------------------------
demo_tb_clk_gen # ( .axi_reset_cycles (axi_reset_cycles) ) clocks_i(
   
   .axi_clk_phase         ({16'd5000, 16'd5000} ), // AXI CLK 100.0MHz
   .clkdac_0_fab_phase    ({16'd1248 ,16'd1248 }), // 400.000MHz // FAB_CCHECK:1248.0:1250:DIFF=-2.0:SAMP=156
   .clkdac_0_ref_phase    ({16'd78   ,16'd78   }), // 6410.000MHz // REF_CCHECK:78.0:78:DIFF=0.0:SAMP=156
   .clkdac_0_enable       (tile_clock_enable[0] ), //

   .clkadc_0_fab_phase    ({16'd2000 ,16'd2000 }), // 250.000MHz // FAB_CCHECK:2000.0:2000:DIFF=0.0:SAMP=500
   .clkadc_0_ref_phase    ({16'd250  ,16'd250  }), // 2000.000MHz // REF_CCHECK:250.0:250:DIFF=0.0:SAMP=500
   .clkadc_0_enable       (tile_clock_enable[4] ), //


   .clkdac_0_fab          (dac0_axis_aclk       ),
   .clkdac_0_ref          (dac0_clk_p           ),
   .clkadc_0_fab          (adc0_axis_aclk       ),
   .clkadc_0_ref          (adc0_clk_p           ),
   .axi_resetn             (axi_resetn ), // 
   .axi_reset              (axi_reset  ), // 
   .clk_axi                (s_axi_aclk )  // 

);

endmodule

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// This testbench layer wraps the real data generation/checking with the DUT
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
module demo_tb_dut_checker(

  // AXI-Lite clock/reset
  output wire           s_axi_aclk   ,
  input  wire           s_axi_aresetn,
  input  wire           s_axi_tb_aresetn,

  output wire           dac_sink_error_flag,
  output wire           dac_sink_done_flag ,
  output wire           adc_sink_error_flag,
  output wire           adc_sink_done_flag ,

  input  wire [7:0]     tile_clock_enable,
  output wire [15:0]    clock_enable_reg,

  // AXI-Lite Control/Status
  input  wire [21:0]    s_axi_awaddr ,
  input  wire           s_axi_awvalid,
  output wire           s_axi_awready,
  input  wire [31:0]    s_axi_wdata  ,
  input  wire  [3:0]    s_axi_wstrb  ,
  input  wire           s_axi_wvalid ,
  output wire           s_axi_wready ,
  output wire  [1:0]    s_axi_bresp  ,
  output wire           s_axi_bvalid ,
  input  wire           s_axi_bready ,
  input  wire [21:0]    s_axi_araddr ,
  input  wire           s_axi_arvalid,
  output wire           s_axi_arready,
  output wire [31:0]    s_axi_rdata  ,
  output wire  [1:0]    s_axi_rresp  ,
  output wire           s_axi_rvalid ,
  input  wire           s_axi_rready 

) ;

//-----------------------------------------------------------------------------
// Wires for ADC sample generation High[31:16]/Low[15:0] phase
//-----------------------------------------------------------------------------
wire [31:0]  clk_phase_hl_00;

//-----------------------------------------------------------------------------
// Clock declarations
//-----------------------------------------------------------------------------
wire         adc0_clk_p    ; 
wire         adc0_axis_aclk; //
wire         dac0_clk_p    ; //
wire         dac0_axis_aclk; //

//-----------------------------------------------------------------------------
// Declare AXI decoder wires
//-----------------------------------------------------------------------------
// AXI M 0
wire [19:0]  m_exdes_axi_awaddr  ; // 
wire         m_exdes_axi_awvalid ; // 
wire         m_exdes_axi_awready ; // 
wire [31:0]  m_exdes_axi_wdata   ; // 
wire  [3:0]  m_exdes_axi_wstrb   ; // 
wire         m_exdes_axi_wvalid  ; // 
wire         m_exdes_axi_wready  ; // 
wire  [1:0]  m_exdes_axi_bresp   ; // 
wire         m_exdes_axi_bvalid  ; // 
wire         m_exdes_axi_bready  ; // 
wire [19:0]  m_exdes_axi_araddr  ; // 
wire         m_exdes_axi_arvalid ; // 
wire         m_exdes_axi_arready ; // 
wire [31:0]  m_exdes_axi_rdata   ; // 
wire  [1:0]  m_exdes_axi_rresp   ; // 
wire         m_exdes_axi_rvalid  ; // 
wire         m_exdes_axi_rready  ; // 

// AXI M 1
wire [19:0]  m_tbsrc_axi_awaddr  ; // 
wire         m_tbsrc_axi_awvalid ; // 
wire         m_tbsrc_axi_awready ; // 
wire [31:0]  m_tbsrc_axi_wdata   ; // 
wire  [3:0]  m_tbsrc_axi_wstrb   ; // 
wire         m_tbsrc_axi_wvalid  ; // 
wire         m_tbsrc_axi_wready  ; // 
wire  [1:0]  m_tbsrc_axi_bresp   ; // 
wire         m_tbsrc_axi_bvalid  ; // 
wire         m_tbsrc_axi_bready  ; // 
wire [19:0]  m_tbsrc_axi_araddr  ; // 
wire         m_tbsrc_axi_arvalid ; // 
wire         m_tbsrc_axi_arready ; // 
wire [31:0]  m_tbsrc_axi_rdata   ; // 
wire  [1:0]  m_tbsrc_axi_rresp   ; // 
wire         m_tbsrc_axi_rvalid  ; // 
wire         m_tbsrc_axi_rready  ; // 

// AXI M 2
wire [19:0]  m_tbsnk_axi_awaddr  ; // 
wire         m_tbsnk_axi_awvalid ; // 
wire         m_tbsnk_axi_awready ; // 
wire [31:0]  m_tbsnk_axi_wdata   ; // 
wire  [3:0]  m_tbsnk_axi_wstrb   ; // 
wire         m_tbsnk_axi_wvalid  ; // 
wire         m_tbsnk_axi_wready  ; // 
wire  [1:0]  m_tbsnk_axi_bresp   ; // 
wire         m_tbsnk_axi_bvalid  ; // 
wire         m_tbsnk_axi_bready  ; // 
wire [19:0]  m_tbsnk_axi_araddr  ; // 
wire         m_tbsnk_axi_arvalid ; // 
wire         m_tbsnk_axi_arready ; // 
wire [31:0]  m_tbsnk_axi_rdata   ; // 
wire  [1:0]  m_tbsnk_axi_rresp   ; // 
wire         m_tbsnk_axi_rvalid  ; // 
wire         m_tbsnk_axi_rready  ; // 

`ifdef SIM_ONLY_FULL_WRITE_BUS
wire [31:0]  s_axi_rdata_i;
 `else
wire [15:0]  s_axi_rdata_i;
`endif

//-----------------------------------------------------------------------------
// Clock generator wrapper block, improved IPI EOU
//-----------------------------------------------------------------------------
demo_tb_clk_gen_wrap clocks_w_i(

   .dac0_axis_aclk         (dac0_axis_aclk      ), // clkdac_0_fab
   .dac0_clk_p             (dac0_clk_p          ), // clkdac_0_ref
   .adc0_axis_aclk         (adc0_axis_aclk      ), // clkadc_0_fab
   .adc0_clk_p             (adc0_clk_p          ), // clkadc_0_ref

   .tile_clock_enable      (tile_clock_enable   ), 
   .axi_resetn             (),
   .axi_reset              (),
   .s_axi_aclk             (s_axi_aclk          )  // 

);

//-----------------------------------------------------------------------------
// RFAMS Example Design
//-----------------------------------------------------------------------------
usp_rf_data_converter_0_example_design DUT(
  // External SYSREF input
   .sysref_in_p            (),
   .sysref_in_n            (),

   .adc0_clk_p             (adc0_clk_p       ), // ADC Reference Clock for Tile 0
   .adc0_clk_n             (~adc0_clk_p      ), //
   .adc0_axis_aclk         (adc0_axis_aclk   ), // ADC AXI Streaming Clock and Reset for ADC0
   .adc0_axis_aresetn      (1'b1),
  
   .dac0_clk_p             (dac0_clk_p       ), // DAC Reference Clock for Tile 0
   .dac0_clk_n             (~dac0_clk_p      ), 
   .dac0_axis_aclk         (dac0_axis_aclk   ), // DAC AXI Streaming Clock and Reset for DAC0
   .dac0_axis_aresetn      (1'b1), 

   .vin0_01_p              ( ),
   .vin0_01_n              ( ),

   .vout00_p               ( ),
   .vout00_n               ( ),

   .adc_sink_error_flag    (adc_sink_error_flag     ), //
   .adc_sink_done_flag     (adc_sink_done_flag      ), //

   .s_axi_aclk             (s_axi_aclk              ), // 
   .s_axi_aresetn          (s_axi_aresetn           ), //

   .s_axi_awaddr           (m_exdes_axi_awaddr[19:0]), // 
   .s_axi_awvalid          (m_exdes_axi_awvalid     ), // 
   .s_axi_awready          (m_exdes_axi_awready     ), // 
`ifdef SIM_ONLY_FULL_WRITE_BUS
   .s_axi_wdata            (m_exdes_axi_wdata[31:0] ), // 
`else
   .s_axi_wdata            (m_exdes_axi_wdata[15:0] ), // 
`endif
   .s_axi_wvalid           (m_exdes_axi_wvalid      ), // 
   .s_axi_wready           (m_exdes_axi_wready      ), // 
   .s_axi_bresp            (m_exdes_axi_bresp       ), // 
   .s_axi_bvalid           (m_exdes_axi_bvalid      ), // 
   .s_axi_bready           (m_exdes_axi_bready      ), // 
   .s_axi_araddr           (m_exdes_axi_araddr[19:0]), // 
   .s_axi_arvalid          (m_exdes_axi_arvalid     ), // 
   .s_axi_arready          (m_exdes_axi_arready     ), // 
   .s_axi_rdata            (s_axi_rdata_i           ), // 
   .s_axi_rresp            (m_exdes_axi_rresp       ), // 
   .s_axi_rvalid           (m_exdes_axi_rvalid      ), // 
   .s_axi_rready           (m_exdes_axi_rready      ), //
  
   
   .irq                    ()
);

`ifdef SIM_ONLY_FULL_WRITE_BUS
  assign m_exdes_axi_rdata = s_axi_rdata_i[31:0];       // Full width data bus
 `else
  assign m_exdes_axi_rdata = {16'h0000, s_axi_rdata_i}; // Truncated data bus
`endif

//-----------------------------------------------------------------------------
// Decoder for the AXI4 bus. The REAL source/sink blocks also have processor
// interfaces for configuration
//-----------------------------------------------------------------------------
demo_tb_axi4l_decode axi4l_decoder_tb_i (

   // AXI M 0
   .m0_axi_awaddr          (m_exdes_axi_awaddr  ), // 
   .m0_axi_awvalid         (m_exdes_axi_awvalid ), // 
   .m0_axi_awready         (m_exdes_axi_awready ), // 
   .m0_axi_wdata           (m_exdes_axi_wdata   ), // 
   .m0_axi_wstrb           (m_exdes_axi_wstrb   ), // 
   .m0_axi_wvalid          (m_exdes_axi_wvalid  ), // 
   .m0_axi_wready          (m_exdes_axi_wready  ), // 
   .m0_axi_bresp           (m_exdes_axi_bresp   ), // 
   .m0_axi_bvalid          (m_exdes_axi_bvalid  ), // 
   .m0_axi_bready          (m_exdes_axi_bready  ), // 
   .m0_axi_araddr          (m_exdes_axi_araddr  ), // 
   .m0_axi_arvalid         (m_exdes_axi_arvalid ), // 
   .m0_axi_arready         (m_exdes_axi_arready ), // 
   .m0_axi_rdata           (m_exdes_axi_rdata   ), // 
   .m0_axi_rresp           (m_exdes_axi_rresp   ), // 
   .m0_axi_rvalid          (m_exdes_axi_rvalid  ), // 
   .m0_axi_rready          (m_exdes_axi_rready  ), // 
      
   // AXI M 1
   .m1_axi_awaddr          (m_tbsrc_axi_awaddr  ), // 
   .m1_axi_awvalid         (m_tbsrc_axi_awvalid ), // 
   .m1_axi_awready         (m_tbsrc_axi_awready ), // 
   .m1_axi_wdata           (m_tbsrc_axi_wdata   ), // 
   .m1_axi_wstrb           (m_tbsrc_axi_wstrb   ), // 
   .m1_axi_wvalid          (m_tbsrc_axi_wvalid  ), // 
   .m1_axi_wready          (m_tbsrc_axi_wready  ), // 
   .m1_axi_bresp           (m_tbsrc_axi_bresp   ), // 
   .m1_axi_bvalid          (m_tbsrc_axi_bvalid  ), // 
   .m1_axi_bready          (m_tbsrc_axi_bready  ), // 
   .m1_axi_araddr          (m_tbsrc_axi_araddr  ), // 
   .m1_axi_arvalid         (m_tbsrc_axi_arvalid ), // 
   .m1_axi_arready         (m_tbsrc_axi_arready ), // 
   .m1_axi_rdata           (m_tbsrc_axi_rdata   ), // 
   .m1_axi_rresp           (m_tbsrc_axi_rresp   ), // 
   .m1_axi_rvalid          (m_tbsrc_axi_rvalid  ), // 
   .m1_axi_rready          (m_tbsrc_axi_rready  ), // 
      
   // AXI M 2
   .m2_axi_awaddr          (m_tbsnk_axi_awaddr  ), // 
   .m2_axi_awvalid         (m_tbsnk_axi_awvalid ), // 
   .m2_axi_awready         (m_tbsnk_axi_awready ), // 
   .m2_axi_wdata           (m_tbsnk_axi_wdata   ), // 
   .m2_axi_wstrb           (m_tbsnk_axi_wstrb   ), // 
   .m2_axi_wvalid          (m_tbsnk_axi_wvalid  ), // 
   .m2_axi_wready          (m_tbsnk_axi_wready  ), // 
   .m2_axi_bresp           (m_tbsnk_axi_bresp   ), // 
   .m2_axi_bvalid          (m_tbsnk_axi_bvalid  ), // 
   .m2_axi_bready          (m_tbsnk_axi_bready  ), // 
   .m2_axi_araddr          (m_tbsnk_axi_araddr  ), // 
   .m2_axi_arvalid         (m_tbsnk_axi_arvalid ), // 
   .m2_axi_arready         (m_tbsnk_axi_arready ), // 
   .m2_axi_rdata           (m_tbsnk_axi_rdata   ), // 
   .m2_axi_rresp           (m_tbsnk_axi_rresp   ), // 
   .m2_axi_rvalid          (m_tbsnk_axi_rvalid  ), // 
   .m2_axi_rready          (m_tbsnk_axi_rready  ), // 
      
   
   // AXI-Lite Interface
   .s_axi_awaddr           (s_axi_awaddr  ), // 
   .s_axi_awvalid          (s_axi_awvalid ), // 
   .s_axi_awready          (s_axi_awready ), // 
   .s_axi_wdata            (s_axi_wdata   ), // 
   .s_axi_wstrb            (4'hF          ), // 
   .s_axi_wvalid           (s_axi_wvalid  ), // 
   .s_axi_wready           (s_axi_wready  ), // 
   .s_axi_bresp            (s_axi_bresp   ), // 
   .s_axi_bvalid           (s_axi_bvalid  ), // 
   .s_axi_bready           (s_axi_bready  ), // 
   .s_axi_araddr           (s_axi_araddr  ), // 
   .s_axi_arvalid          (s_axi_arvalid ), // 
   .s_axi_arready          (s_axi_arready ), // 
   .s_axi_rdata            (s_axi_rdata   ), // 
   .s_axi_rresp            (s_axi_rresp   ), // 
   .s_axi_rvalid           (s_axi_rvalid  ), // 
   .s_axi_rready           (s_axi_rready  ),  // 
 
   .clk                    (s_axi_aclk    ) ,
   .s_axi_aresetn          (s_axi_tb_aresetn )

);

//-----------------------------------------------------------------------------
// Demo testbench real data source, with processor configuration interface.
// Forces are used to apply real data from the DAC onto these pins
//-----------------------------------------------------------------------------
demo_tb_rfdac_data_sink dac_sink(

   .s_axi_awaddr           (m_tbsnk_axi_awaddr[17:0]), // 
   .s_axi_awvalid          (m_tbsnk_axi_awvalid), // 
   .s_axi_awready          (m_tbsnk_axi_awready), // 
   .s_axi_wdata            (m_tbsnk_axi_wdata  ), // 
   .s_axi_wvalid           (m_tbsnk_axi_wvalid ), // 
   .s_axi_wready           (m_tbsnk_axi_wready ), // 
   .s_axi_bresp            (m_tbsnk_axi_bresp  ), // 
   .s_axi_bvalid           (m_tbsnk_axi_bvalid ), // 
   .s_axi_bready           (m_tbsnk_axi_bready ), // 
   .s_axi_araddr           (m_tbsnk_axi_araddr[17:0]), // 
   .s_axi_arvalid          (m_tbsnk_axi_arvalid), // 
   .s_axi_arready          (m_tbsnk_axi_arready), // 
   .s_axi_rdata            (m_tbsnk_axi_rdata  ), // 
   .s_axi_rresp            (m_tbsnk_axi_rresp  ), // 
   .s_axi_rvalid           (m_tbsnk_axi_rvalid ), // 
   .s_axi_rready           (m_tbsnk_axi_rready ),  // 

   .vin_00_p               ( ),
   .vin_00_n               ( ),
   .sample_rate0_clk       (dac0_clk_p  ),
   .fabric_rate0_clk       (dac0_axis_aclk), 

   .done_flag              (dac_sink_done_flag ),
   .error_flag             (dac_sink_error_flag),
   .clock_enable_reg       (clock_enable_reg   ),

   // AXI-Lite Clock/Reset
   .s_axi_aclk             (s_axi_aclk         ) ,
   .s_axi_aresetn          (s_axi_tb_aresetn   )

  );

//-----------------------------------------------------------------------------
// Demo testbench real data generation, with processor configuration interface.
// Forces are used to apply real data to the ADC.
//-----------------------------------------------------------------------------
assign clk_phase_hl_00 = {16'd2000 ,16'd2000 }; // Int=1=x1 4G part

demo_tb_rfadc_data_source adc_source(

   .s_axi_awaddr           (m_tbsrc_axi_awaddr[17:0]), // 
   .s_axi_awvalid          (m_tbsrc_axi_awvalid), // 
   .s_axi_awready          (m_tbsrc_axi_awready), // 
   .s_axi_wdata            (m_tbsrc_axi_wdata  ), // 
   .s_axi_wvalid           (m_tbsrc_axi_wvalid ), // 
   .s_axi_wready           (m_tbsrc_axi_wready ), // 
   .s_axi_bresp            (m_tbsrc_axi_bresp  ), // 
   .s_axi_bvalid           (m_tbsrc_axi_bvalid ), // 
   .s_axi_bready           (m_tbsrc_axi_bready ), // 
   .s_axi_araddr           (m_tbsrc_axi_araddr[17:0]), // 
   .s_axi_arvalid          (m_tbsrc_axi_arvalid), // 
   .s_axi_arready          (m_tbsrc_axi_arready), // 
   .s_axi_rdata            (m_tbsrc_axi_rdata  ), // 
   .s_axi_rresp            (m_tbsrc_axi_rresp  ), // 
   .s_axi_rvalid           (m_tbsrc_axi_rvalid ), // 
   .s_axi_rready           (m_tbsrc_axi_rready ),  // 
 
   .clk_phase_hl_00        (clk_phase_hl_00),
   .vout_00_p              ( ),
   .vout_00_n              ( ),

   // AXI-Lite Clock/Reset
   .s_axi_aclk             (s_axi_aclk         ) ,
   .s_axi_aresetn          (s_axi_tb_aresetn   )

  );

//-----------------------------------------------------------------------------
// Force the analog signals.
//-----------------------------------------------------------------------------
`ifndef DO_NOT_USE_RFAMS_REAL_SIGNAL_FORCE
// Map the walking one to a 32 bit window to allow a covergroup binding
reg  [31:0]     adc_wo_driver_remap=0; 
reg  [31:0]     adc_wo_endpoint_remap=0;

// ADC
reg  [1:0] adc_wo_driver = 1; 
reg  [1:0] adc_wo_endpoint;

real adc0_01_p;
real adc0_01_n;

always @(*) begin
   force DUT.vin0_01_n               = adc_wo_driver[0];
   force DUT.vin0_01_p               = adc_wo_driver[1];

   adc_wo_endpoint[0] =  DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.VIN_I01_N; // 
   adc_wo_endpoint[1] =  DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.VIN_I01_P; //
end

always @(*) begin
   adc_wo_driver_remap   = 32'd0;
   adc_wo_driver_remap  [1:0] = adc_wo_driver[1:0];
end

always @(*) begin
   adc_wo_endpoint_remap = 32'd0;
   adc_wo_endpoint_remap[1:0] = adc_wo_endpoint    [1:0];
end

always @(posedge s_axi_aclk) begin
   adc_wo_driver <= {adc_wo_driver[0:0],adc_wo_driver[1]};
end

always @ (*) begin
   // Map the ADC signals to top level
   adc0_01_p = $bitstoreal(adc_source.vout_00_p);
   adc0_01_n = $bitstoreal(adc_source.vout_00_n);
 
   // Force the ADC analog input
   force DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST._vin_i01_p = adc0_01_p; // 
   force DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST._vin_i01_n = adc0_01_n; //
end

// Map the walking one to a 32 bit window to allow a covergroup binding
reg  [31:0]     dac_wo_driver_remap=0; 
reg  [31:0]     dac_wo_endpoint_remap=0;
// DAC
real dac00_p;
real dac00_n;

// Walking one shift registers for DUT attachment
reg  [1:0] dac_wo_driver = 1; 
reg  [1:0] dac_wo_endpoint;

always @(*) begin
   dac_wo_endpoint[0] = DUT.vout00_n               ;
   dac_wo_endpoint[1] = DUT.vout00_p               ;

   force DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.VOUT0_N = dac_wo_driver[0]; //VOUT0_N
   force DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.VOUT0_P = dac_wo_driver[1]; //VOUT0_P
end

always @(*) begin
   dac_wo_driver_remap   = 32'd0;
   dac_wo_driver_remap  [1:0] = dac_wo_driver[1:0];
end

always @(*) begin
   dac_wo_endpoint_remap = 32'd0;
   dac_wo_endpoint_remap[1:0] = dac_wo_endpoint    [1:0];
end

// Generate the walking one bit on AXI clock. This is vrirtual and not timed to a domain.
always @(posedge s_axi_aclk) begin
   dac_wo_driver <= {dac_wo_driver[0:0],dac_wo_driver[1]};
end

always @ (*) begin
   // Map the DAC signals to the top level
   dac00_p = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST._vout0_p;
   dac00_n = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST._vout0_n;
  
   // force the DAC output onto he DAC sink
   force dac_sink.vin_00_p = $realtobits(dac00_p);
   force dac_sink.vin_00_n = $realtobits(dac00_n);
 
end
`endif


//-----------------------------------------------------------------------------
// POR SM state probes
//-----------------------------------------------------------------------------
`ifdef ENABLE_VERILOG_SM_PROBES
wire [12:0] dgb_por_sm_dac0;

wire [12:0] dgb_por_sm_adc0;

assign dgb_por_sm_dac0 = {
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_dac0.done,
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_dac0.status,
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_dac0.start_stage,
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_dac0.end_stage
                         };

assign dgb_por_sm_adc0 = {
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_adc0.done,
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_adc0.status,
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_adc0.start_stage,
                           DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.por_state_machine_i.por_fsm_adc0.end_stage
                         };
`endif

//-----------------------------------------------------------------------------
// Probe data interfaces for EOU
//-----------------------------------------------------------------------------
`ifdef ENABLE_VERILOG_HIER_PROBES
// ADC - 00
reg [127:0] adc00_axis_tdata ; //
reg         adc00_axis_tvalid; //
reg         adc00_axis_tready; //

// DAC - 00
reg [255:0] dac00_axis_tdata ; //
reg         dac00_axis_tvalid; //
reg         dac00_axis_tready; //

always @ (*) begin
   adc00_axis_tdata  = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.m00_axis_tdata;
   adc00_axis_tvalid = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.m00_axis_tvalid;
   adc00_axis_tready = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.m00_axis_tready;
   dac00_axis_tdata  = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.s00_axis_tdata;
   dac00_axis_tvalid = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.s00_axis_tvalid;
   dac00_axis_tready = DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.s00_axis_tready;
end

//-----------------------------------------------------------------------------
// Monitors for the AMS DRP bus. Force these in the simulator to display.
// Example command for Questa
// force -freeze sim:/demo_tb/dut_and_data_i/hsadc_drp_decode_i/enable 1'h1 0
//-----------------------------------------------------------------------------
rfdac_drp_decode z_dac_drp_decode_0_i (
 
   .marker      (8'd0),
   .enable      (1'd0),
   .drp_clk     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST.DCLK  ),
   .drp_addr    (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST.DADDR ),
   .drp_we      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST.DWE   ),
   .drp_di      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST.DI    ),
   .drp_en      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST.DEN   ),
   .drp_rdy     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST.DRDY  ),
   .drp_do      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx0_u_dac.SIP_HSDAC_INST.DOUT  )
);

rfdac_drp_decode z_dac_drp_decode_1_i (
 
   .marker      (8'd1),
   .enable      (1'd0),
   .drp_clk     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx1_u_dac.SIP_HSDAC_INST.DCLK  ),
   .drp_addr    (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx1_u_dac.SIP_HSDAC_INST.DADDR ),
   .drp_we      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx1_u_dac.SIP_HSDAC_INST.DWE   ),
   .drp_di      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx1_u_dac.SIP_HSDAC_INST.DI    ),
   .drp_en      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx1_u_dac.SIP_HSDAC_INST.DEN   ),
   .drp_rdy     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx1_u_dac.SIP_HSDAC_INST.DRDY  ),
   .drp_do      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.tx1_u_dac.SIP_HSDAC_INST.DOUT  )
);

rfadc_drp_decode z_adc_drp_decode_0_i (
 
   .marker      (8'd0),
   .enable      (1'd0),
   .drp_clk     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST.DCLK  ),
   .drp_addr    (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST.DADDR ),
   .drp_we      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST.DWE   ),
   .drp_di      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST.DI    ),
   .drp_en      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST.DEN   ),
   .drp_rdy     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST.DRDY  ),
   .drp_do      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx0_u_adc.SIP_HSADC_INST.DOUT  )
);

rfadc_drp_decode z_adc_drp_decode_1_i (
 
   .marker      (8'd1),
   .enable      (1'd0),
   .drp_clk     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx1_u_adc.SIP_HSADC_INST.DCLK  ),
   .drp_addr    (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx1_u_adc.SIP_HSADC_INST.DADDR ),
   .drp_we      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx1_u_adc.SIP_HSADC_INST.DWE   ),
   .drp_di      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx1_u_adc.SIP_HSADC_INST.DI    ),
   .drp_en      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx1_u_adc.SIP_HSADC_INST.DEN   ),
   .drp_rdy     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx1_u_adc.SIP_HSADC_INST.DRDY  ),
   .drp_do      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx1_u_adc.SIP_HSADC_INST.DOUT  )
);

rfadc_drp_decode z_adc_drp_decode_2_i (
 
   .marker      (8'd2),
   .enable      (1'd0),
   .drp_clk     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx2_u_adc.SIP_HSADC_INST.DCLK  ),
   .drp_addr    (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx2_u_adc.SIP_HSADC_INST.DADDR ),
   .drp_we      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx2_u_adc.SIP_HSADC_INST.DWE   ),
   .drp_di      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx2_u_adc.SIP_HSADC_INST.DI    ),
   .drp_en      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx2_u_adc.SIP_HSADC_INST.DEN   ),
   .drp_rdy     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx2_u_adc.SIP_HSADC_INST.DRDY  ),
   .drp_do      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx2_u_adc.SIP_HSADC_INST.DOUT  )
);

rfadc_drp_decode z_adc_drp_decode_3_i (
 
   .marker      (8'd3),
   .enable      (1'd0),
   .drp_clk     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx3_u_adc.SIP_HSADC_INST.DCLK  ),
   .drp_addr    (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx3_u_adc.SIP_HSADC_INST.DADDR ),
   .drp_we      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx3_u_adc.SIP_HSADC_INST.DWE   ),
   .drp_di      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx3_u_adc.SIP_HSADC_INST.DI    ),
   .drp_en      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx3_u_adc.SIP_HSADC_INST.DEN   ),
   .drp_rdy     (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx3_u_adc.SIP_HSADC_INST.DRDY  ),
   .drp_do      (DUT.usp_rf_data_converter_0_ex_i.usp_rf_data_converter_0_i.inst.usp_rf_data_converter_0_ex_usp_rf_data_converter_0_i_0_rf_wrapper_i.rx3_u_adc.SIP_HSADC_INST.DOUT  )
);

`endif

endmodule
