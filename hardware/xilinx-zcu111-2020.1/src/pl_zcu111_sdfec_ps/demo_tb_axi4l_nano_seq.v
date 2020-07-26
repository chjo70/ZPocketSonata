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

//--------------------------------------------------------------------------------
// Helper Address defines for IP.
// The DAC and ADC Tiles are split into 0x4000 addressable segments with 
// 0x0000 -> 0x1FFF : existing in the IP wrapper, register names to thia segment
//                    are reported in simulation prefixed with 
//                    DCC for DAC and ACC for ADC  
// 0x2000 -> 0x3FFF : existing in the silincon primitive. There are accessed via
//                    the AXI 2 DRP bridge. Register names to thia segment
//                    are reported in simulation prefixed with DAC and ADC  
//--------------------------------------------------------------------------------
// Base address
`define HSAMS_CONFIG_BASE_ADDR                            'h0          // 0
`define T0_DCC_BASE_ADDR                                  'h4000       // 16384
`define T0_DAC_BASE_ADDR                                  'h6000       // 24576
`define T1_DCC_BASE_ADDR                                  'h8000       // 32768
`define T1_DAC_BASE_ADDR                                  'ha000       // 40960
`define T2_DCC_BASE_ADDR                                  'hc000       // 49152
`define T2_DAC_BASE_ADDR                                  'he000       // 57344
`define T3_DCC_BASE_ADDR                                  'h10000      // 65536
`define T3_DAC_BASE_ADDR                                  'h12000      // 73728
`define T0_ACC_BASE_ADDR                                  'h14000      // 81920
`define T0_ADC_BASE_ADDR                                  'h16000      // 90112
`define T1_ACC_BASE_ADDR                                  'h18000      // 98304
`define T1_ADC_BASE_ADDR                                  'h1a000      // 106496
`define T2_ACC_BASE_ADDR                                  'h1c000      // 114688
`define T2_ADC_BASE_ADDR                                  'h1e000      // 122880
`define T3_ACC_BASE_ADDR                                  'h20000      // 131072
`define T3_ADC_BASE_ADDR                                  'h22000      // 139264
// IP control register examples
`define DCC0_RESET_REGISTER_ADDR                          'h4000       // 16384
`define DCC0_RESTART_REGISTER_ADDR                        'h4004       // 16388
`define DCC0_RESTART_STATE_START_ADDR                     'h4008       // 16392
`define DCC0_RESTART_STATE_END_ADDR                       'h4008       // 16392
`define DCC0_CURRENT_STATE_ADDR                           'h400c       // 16396
`define DCC0_SIM_LEVEL_ADDR                               'h4100       // 16640
`define DCC1_SIM_LEVEL_ADDR                               'h8100       // 33024
`define DCC2_SIM_LEVEL_ADDR                               'hc100       // 49408
`define DCC3_SIM_LEVEL_ADDR                               'h10100      // 65792
`define ACC0_RESET_REGISTER_ADDR                          'h14000      // 81920
`define ACC0_RESTART_REGISTER_ADDR                        'h14004      // 81924
`define ACC0_RESTART_STATE_START_ADDR                     'h14008      // 81928
`define ACC0_RESTART_STATE_END_ADDR                       'h14008      // 81928
`define ACC0_CURRENT_STATE_ADDR                           'h1400c      // 81932
`define ACC0_SIM_LEVEL_ADDR                               'h14100      // 82176
`define ACC1_SIM_LEVEL_ADDR                               'h18100      // 98560
`define ACC2_SIM_LEVEL_ADDR                               'h1c100      // 114944
`define ACC3_SIM_LEVEL_ADDR                               'h20100      // 131328


///////////////////////////////////////////////////////////////////////////////
// CONFIGURATION_DEFINES_START
///////////////////////////////////////////////////////////////////////////////
//`define ENABLE_IPI_HELPER_BLOCKS
// Nano sequencer
//`define ENABLE_RW_MESSAGE_PRINT
`define ENABLE_NANO_STOP_IN_MODULE
//`define ENABLE_AXI4_LITE_MON_PORT
// Sim Stopper
//`define ENABLE_SIM_STOPPER_COUNT_PORTS
//`define ENABLE_SIM_STOPPER_STOP_IN_MODULE
`define SIM_TIMEOUT_IN_AXI_CYCLES 150000
///////////////////////////////////////////////////////////////////////////////
// CONFIGURATION_DEFINES_END
///////////////////////////////////////////////////////////////////////////////

`define DGTYPE_TRGL     0
`define DGTYPE_TRGL_S   1

///////////////////////////////////////////////////////////////////////////////
// 
// Module Name: axi4l_nano_seq
//
// Description: This module is designed to enable a user to quickly inject
// AXI4-Lite stimulation into a design.
//
// This block is encapsulated in a module to allow it to be instantiated in IPI
// enabling the user to apply stimulus to and AXI4-Lite interface.
//
// This should be regarded as a template as other IO/tasks can be added as
// required. Im its raw form however it should be suffictent to configure
// AXI4-Lite interfaced systems in either IPI or general HDL.
// 
// This module is non-synthesisable however does contain two synthesiseable 
// components that can be reused in IPI or general HDL
//   axi4l_ns_rw_2_axi    : Conversion from RW data interface to AXI4-Lite
//   axi4l_ns_sim_stopper : Condition counter to indicate end on simulation
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
///////////////////////////////////////////////////////////////////////////////

// All submodules prefixed with the abbreviated with axi4l_ns
module demo_tb_axi4l_nano_seq #(
   parameter EXTERN_RETIMED_SIGNAL_BUS_W = 4 
) (

`ifdef ENABLE_AXI4_LITE_MON_PORT
   // If this module is used in IPI and the user wants to add a monitor on the 
   // AXI bus, this port set can be enabled. IPI does not currently allow 
   // multiple bus connections, so this offers a clean way to monitor the design
   // in simulation
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon AWADDR"  *) output  wire [31:0] mon_axi_awaddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon AWVALID" *) output  wire        mon_axi_awvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon AWREADY" *) output  wire        mon_axi_awready  , // 
   
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon WDATA"   *) output  wire [31:0] mon_axi_wdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon WVALID"  *) output  wire        mon_axi_wvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon WREADY"  *) output  wire        mon_axi_wready   , // 
   
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon BRESP"   *) output  wire  [1:0] mon_axi_bresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon BVALID"  *) output  wire        mon_axi_bvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon BREADY"  *) output  wire        mon_axi_bready   , // 
   
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon ARADDR"  *) output  wire [31:0] mon_axi_araddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon ARVALID" *) output  wire        mon_axi_arvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon ARREADY" *) output  wire        mon_axi_arready  , // 
   
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon RDATA"   *) output  wire [31:0] mon_axi_rdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon RRESP"   *) output  wire  [1:0] mon_axi_rresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon RVALID"  *) output  wire        mon_axi_rvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 nano_mon RREADY"  *) output  wire        mon_axi_rready   , // 
`endif

   // AXI-Lite Interface
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi AWADDR"  *)     output  wire [31:0] axi_awaddr       , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi AWVALID" *)     output  wire        axi_awvalid      , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi AWREADY" *)     input   wire        axi_awready      , // 
        
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi WDATA"   *)     output  wire [31:0] axi_wdata        , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi WVALID"  *)     output  wire        axi_wvalid       , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi WREADY"  *)     input   wire        axi_wready       , // 
        
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi BRESP"   *)     input   wire  [1:0] axi_bresp        , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi BVALID"  *)     input   wire        axi_bvalid       , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi BREADY"  *)     output  wire        axi_bready       , // 
        
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi ARADDR"  *)     output  wire [31:0] axi_araddr       , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi ARVALID" *)     output  wire        axi_arvalid      , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi ARREADY" *)     input   wire        axi_arready      , // 
        
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi RDATA"   *)     input   wire [31:0] axi_rdata        , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi RRESP"   *)     input   wire  [1:0] axi_rresp        , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi RVALID"  *)     input   wire        axi_rvalid       , // 
   (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 nano_axi RREADY"  *)     output  wire        axi_rready       , // 
   
   // clock and reset
   (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 clk CLK" *)
   (* X_INTERFACE_PARAMETER = "ASSOCIATED_BUSIF nano_axi, ASSOCIATED_RESET reset" *)
   input  wire clk                ,
   (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 reset RST" *)
   (* X_INTERFACE_PARAMETER = "POLARITY ACTIVE_HIGH" *)
   input  wire reset              ,
   input  wire rising_stop_trigger,

   // External flags indicating error and complete status
   input  wire [EXTERN_RETIMED_SIGNAL_BUS_W-1: 0] external_signal_bus,

   // general purpose
   output reg  [7:0]   tile_clock_enable = 8'hff, // Clock enables to allow simulation acceleration
   output reg          axi_message_enable = 1'b1, // Optional AXI message disable
   output reg          int_axi_aresetn =0,        // 
   output reg          int_tb_aresetn =0,         // 
   output wire         axi_aresetn ,              // Inverted reset for AXI4 land 
   output reg          seq_done = 0               // 
);

//----------------------------------------------------------------------------
// Internal signals
//----------------------------------------------------------------------------
// Simple strobes to drive AXI control
reg           wr_req                = 0; // Set to request a write access
reg           rd_req                = 0; // Set to request a read access
reg    [31:0] address               = 0; // Address to use for request
reg    [31:0] wr_data               = 0; // Data to write on a write

wire          req_busy;                 // AXI4-Lite access is in progress
wire   [31:0] rd_data;                  // The data returned from the AXI4-Lite read
reg    [31:0] working_value         =0; // Used as working variable in AXI tasks
reg           enable_axi_ams_status =0;
wire          dac_sink_error_flag;
wire          adc_sink_error_flag;
wire          dac_sink_done_flag ;
wire          adc_sink_done_flag ;

integer       dac_error_counter     =0;
integer       adc_error_counter     =0;
reg           data_error            =0;

reg    [31:0] dac_done              ='hffff_ffff;
reg    [31:0] dac_done_last         ='hffff_ffff;
reg    [31:0] adc_done              ='hffff_ffff;
reg    [31:0] adc_done_last         ='hffff_ffff;
wire          adc_axi_based_done;
wire          dac_axi_based_done;
reg     [7:0] sm_done_map           ='h0C;
reg     [7:0] sm_stage1_map         ='h0C;

//-----------------------------------------------------------------------------
// Strobes that indicate the AXI read done function has completed
//-----------------------------------------------------------------------------
assign dac_axi_based_done = (!(&dac_done_last)) & (&dac_done) ;
assign adc_axi_based_done = (!(&adc_done_last)) & (&adc_done) ;

//-----------------------------------------------------------------------------
// Status flag demux
//-----------------------------------------------------------------------------
assign dac_sink_error_flag = external_signal_bus[0];
assign adc_sink_error_flag = external_signal_bus[1];
assign dac_sink_done_flag  = external_signal_bus[2];
assign adc_sink_done_flag  = external_signal_bus[3];

//-----------------------------------------------------------------------------
// Assign AXI4-Lite monitor port outputs
//-----------------------------------------------------------------------------
`ifdef ENABLE_AXI4_LITE_MON_PORT
 assign mon_axi_awaddr  =  axi_awaddr  ; // 
 assign mon_axi_awvalid =  axi_awvalid ; // 
 assign mon_axi_awready =  axi_awready ; // 
 assign mon_axi_wdata   =  axi_wdata   ; // 
 assign mon_axi_wvalid  =  axi_wvalid  ; // 
 assign mon_axi_wready  =  axi_wready  ; // 
 assign mon_axi_bresp   =  axi_bresp   ; // 
 assign mon_axi_bvalid  =  axi_bvalid  ; // 
 assign mon_axi_bready  =  axi_bready  ; // 
 assign mon_axi_araddr  =  axi_araddr  ; // 
 assign mon_axi_arvalid =  axi_arvalid ; // 
 assign mon_axi_arready =  axi_arready ; // 
 assign mon_axi_rdata   =  axi_rdata   ; // 
 assign mon_axi_rresp   =  axi_rresp   ; // 
 assign mon_axi_rvalid  =  axi_rvalid  ; // 
 assign mon_axi_rready  =  axi_rready  ; // 
`endif

localparam p_max_slice_count     = 4;
localparam p_max_allowable_error = 30;

//-----------------------------------------------------------------------------
// Error counters
//-----------------------------------------------------------------------------
always @(posedge clk) begin
//always @(*) begin
   if(dac_sink_error_flag)
      dac_error_counter <= dac_error_counter + 1;
   if(adc_sink_error_flag)
      adc_error_counter <= adc_error_counter + 1;
end

always @(posedge clk) begin
   if(((adc_error_counter > p_max_allowable_error) & (~adc_sink_done_flag)) | 
   	  ((dac_error_counter >p_max_allowable_error) & (~dac_sink_done_flag))
   	 )
      data_error <= 1'd1;
end

//-----------------------------------------------------------------------------
// Optional stop on rising edge of stop_trigger. Note this intentionally 
// located here so that when the simulator stops you are located near the task
// code in your Text browser. Move it and scroll!
//-----------------------------------------------------------------------------
`ifdef ENABLE_NANO_STOP_IN_MODULE
always @(posedge ((!reset) & rising_stop_trigger)) begin
   $stop;
end
`endif

//-----------------------------------------------------------------------------
// (RECOMENDED_USER_MODIFY_SEQUENCE_SECTION_START)
//-----------------------------------------------------------------------------
// Memory MAP for exdes and testbench
//-----------------------------------------------------------------------------
`define BASE_ADDR_RFAMS  'h0008_0000  // DUT ( to 0x000C_FFFF)           
`define BASE_ADDR_EXSRC  'h0004_0000  // EXDES data Source   DAC
`define BASE_ADDR_EXSNK  'h0000_0000  // EXDES data Sink     ADC
`define BASE_ADDR_TBSRC  'h0010_0000  // TB    data Source   ADC
`define BASE_ADDR_TBSNK  'h0020_0000  // TB    data Sink         DAC
//-----------------------------------------------------------------------------
//
//   DAC Source              AMS IP      .       DAC Sink                         
//  -----------           -----------    .      -----------                     
// | 0x04_0000 |         |           |   .     | 0x20_0000 |                        
// |  exsrc_w  | ---->>> |           | ---->>> |  tbsnk_w  |                        
// |  exsrc_r  |         |           |   .     |  tbsnk_r  |                        
//  -----------          |           |   .      -----------                         
//                       | 0x00_0000 |   .                             
//   ADC Sink            |  rfams_w  |   .       ADC Source                            
//  -----------          |  rfams_r  |   .      -----------                          
// | 0x08_0000 |         |           |   .     | 0x10_0000 |                         
// |  exsnk_w  | <<<---- |           | <<<---- |  tbsrc_w  |                         
// |  exsnk_r  |         |           |   .     |  tbsrc_r  |                         
//  -----------           -----------    .      ----------- 
//                                "REAL Number Interface"
//                                       .                   
// Example design AXI address space      . Testbench AXI address space   
//-----------------------------------------------------------------------------
// RFAMS AXI register map
//`include "demo_tb_rfams.v"
//-----------------------------------------------------------------------------
initial begin
   // -------------------------------------------------------------------------
   // Task based demo testbench. 
   // Example basic tasks exist for interaction with the IP. 
   // Additional sequences may be added by the user. Be sure to save these to 
   // another file before IP regeneration 
   // -------------------------------------------------------------------------
   $display("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
   $display("T=%12d: Xilinx RF AMS Demo Testbench.", $time);
   $display("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
`ifdef ENABLE_IP_CONFIG_MESSAGE
   enable_axi_ams_status=1;
`endif
   int_axi_reset_after_for_cycles(10,20);
   delay_ps_32  (1000);
   axi_cwait    (40);   // Startup delay

   $display("T=%12d: Accelerate SIM startup", $time);
   set_timers_to_fast_sim(1);
   
   $display("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
   $display("T=%12d: Disable the ADC cal to reduce simulation time.", $time);
   $display("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
   call_adc_setup_ip_end_state(0);

   $display("T=%12d: Wait for the serial tile configuration to complete before configuring core.", $time);
   $display("T=%12d: This is true once all POR tiles have left stage 0.", $time);
   while ((&sm_stage1_map) == 0)
      wait_on_config_exit();

   $display("T=%12d: ADC configuration", $time);
   //-------------------------------------------------------------
   // Analog  = 0_01
   // Digital = 00
   //-------------------------------------------------------------
   call_adc_setup_bench(0, 0, 8, 0, 2, 1); // AMS_CFG_ADC T=0 s=0 DW=8 DT=0=R MT=2=BP Dec=1=x1 Samp=2.0 FabClk=250.000MHz
   call_adc_disable_mix(0, 1, 8, 0, 2, 1); // AMS_CFG_ADC T=0 s=0 DW=8 DT=0=R MT=2=BP Dec=1=x1 Samp=2.0 FabClk=250.000MHz
   call_adc_setup_ip   (0, 0, 8, 0, 2, 1); // AMS_CFG_ADC T=0 s=0 DW=8 DT=0=R MT=2=BP Dec=1=x1 Samp=2.0 FabClk=250.000MHz
   call_adc_enable_sinks(0, 0, 8, 0, 2, 1); // AMS_CFG_ADC T=0 s=0 DW=8 DT=0=R MT=2=BP Dec=1=x1 Samp=2.0 FabClk=250.000MHz

   $display("T=%12d: DAC configuration", $time);
   //-------------------------------------------------------------
   // Analog  = 00
   // Digital = 00
   //-------------------------------------------------------------
   call_dac_setup_ip   (0, 0, 16, 0, 1); // AMS_CFG_DAC T=0 s=0 DW=16 DT=0=R MT=2=BP Int=1=x1 Samp=6.4 FabClk=400.000MHz
   call_dac_setup_bench(0, 0, 16, 0, 1); // AMS_CFG_DAC T=0 s=0 DW=16 DT=0=R MT=2=BP Int=1=x1 Samp=6.4 FabClk=400.000MHz

   //-------------------------------------------------------------
   // TB enables
   //-------------------------------------------------------------
   config_adc_exdes_sink_slice(0, 0, 0, 'd1); // Master ADC data sink enable
   config_adc_tb_source_slice (0, 0, 0, 'd1); // Global Source Enable 
   config_dac_tb_sink_slice   (0, 0, 0, 'd1); // Global DAC CFG

   if (enable_axi_ams_status) begin
      eyeball_config_registers;
   end
   $display("T=%12d: Wait for data........", $time);

   // Example task to manually start ADC 0 
   //adc0_manual_start;

//   @(posedge (dac_sink_done_flag & adc_sink_done_flag) );
   while ( !dac_axi_based_done | !adc_axi_based_done ) begin
      wait_axi_adc_done();
      wait_axi_dac_done();
      report_endstates();
   end

   axi_cwait    (20); // breathing room for waveform
   `ifdef QUESTA_REPORT_UTC_TIME
   $write("Test finished @");
   $system("date -u +%Y%m%d_%H%M%S");
   `endif

`ifndef ENABLE_IP_CONFIG_MESSAGE
   $display("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
   $display("Run with ENABLE_IP_CONFIG_MESSAGE defined to review AMS block configuration");
`endif

   $display("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
   if(data_error) begin
      $display("** Test Failed");
      $display("** Test incomplete");
   end else begin
      $display("** Test Passed");
      $display("** Test completed successfully");    
   end
   $display("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
   set_seq_done; // Sim AXI sequence complete
   $stop;
    
end

//-----------------------------------------------------------------------------
// TIMEOUT.
//-----------------------------------------------------------------------------
initial begin
   // Hardcoded PS value
   #2147000000
   `ifdef QUESTA_REPORT_UTC_TIME
   $write("ERROR RFAMS demo_tb timeout @");
   $system("date -u +%Y%m%d_%H%M%S");
   `else
   $display("ERROR RFAMS demo_tb timeout");
   `endif
   $stop;
end

//-----------------------------------------------------------------------------
// (RECOMENDED_USER_MODIFY_SEQUENCE_SECTION_END)
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER tasks
// The USER should add additional tasks here
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Report the end state occurances. Use as an example of monitoring progress
//-----------------------------------------------------------------------------
task report_endstates; 
   integer i, count;
   reg [31:0] end_start;
   begin
       
   axi_message_enable = 1'd0;
   for (i = 0; i<8; i=i+1) begin

      rfams_r(`T0_DCC_BASE_ADDR  + ('h4000 * i) + 'h8 ); // START_END_STATE_ADDR  
      end_start = rd_data;
      rfams_r(`T0_DCC_BASE_ADDR  + ('h4000 * i) + 'hc ); // CURRENT_STATE_ADDR
      
      if ((rd_data & 'hf) == (end_start & 'hf)) begin
         if (!sm_done_map[i]) begin
            $display("T=%12d: Tile %02d has reached its end state of %h", $time, i, end_start);
            sm_done_map[i] = 1'b1;
            end
         end 
      end
      axi_message_enable = 1'd1;
   end
endtask

//-----------------------------------------------------------------------------
// Wait until all the POR's are in state1, indicating that the POR has loaded
// This is serial not parallel, so the length depends on the number of tiles
// & slices enabled in the design
//-----------------------------------------------------------------------------
task wait_on_config_exit; 
   integer i, count;
   reg [31:0] end_start;
   begin
       
   axi_message_enable = 1'd0;
   for (i = 0; i<8; i=i+1) begin

      rfams_r(`T0_DCC_BASE_ADDR  + ('h4000 * i) + 'h8 ); // START_END_STATE_ADDR  
      end_start = rd_data;
      rfams_r(`T0_DCC_BASE_ADDR  + ('h4000 * i) + 'hc ); // CURRENT_STATE_ADDR
      
      if ((rd_data & 'hf) != 'h0) begin
         if (!sm_stage1_map[i]) begin
            $display("T=%12d: Tile %02d has reached its end state of %h", $time, i, end_start);
            sm_stage1_map[i] = 1'b1;
            end
         end 
      end
      axi_message_enable = 1'd1;
   end
endtask

//-----------------------------------------------------------------------------
// EYEball register dump
//-----------------------------------------------------------------------------
task eyeball_config_registers; 
   begin
   $display("T=%12d: Eyeball IP configuration", $time);
   rfams_r(`T0_DCC_BASE_ADDR  + ('h4000 * 0) + 'hc ); // CURRENT_STATE_ADDR  

   rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h40); // INTERP_CTRL_ADDR  
   rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h44); // INTERP_DATA_ADDR  
   rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h80); // MIXER_CONFIG0_ADDR
   rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h84); // MIXER_CONFIG1_ADDR
   rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h88); // MIXER_MODE_ADDR   

   rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h08);  // FABRIC_RATE
   rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h40);  // DECIMATION_CONFIG
   rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * 0) + ('h400 * 0) + 'h44);  // DECIMATION_MODE
   end
endtask

//---------------------------------------------------------------------------
// set timers for simulation speedup
//---------------------------------------------------------------------------

task set_timers_to_fast_sim;
   input sim_level;
   begin
   // DAC
   rfams_w(`DCC0_SIM_LEVEL_ADDR, sim_level );
   rfams_w(`DCC1_SIM_LEVEL_ADDR, sim_level );
   rfams_w(`DCC2_SIM_LEVEL_ADDR, sim_level );
   rfams_w(`DCC3_SIM_LEVEL_ADDR, sim_level );
   // ADC
   rfams_w(`ACC0_SIM_LEVEL_ADDR, sim_level );
   rfams_w(`ACC1_SIM_LEVEL_ADDR, sim_level );
   rfams_w(`ACC2_SIM_LEVEL_ADDR, sim_level );
   rfams_w(`ACC3_SIM_LEVEL_ADDR, sim_level );
   end
endtask

//---------------------------------------------------------------------------
// Done readbacks
// These do a lot of AXI messaging, so disable for these calls only. Force
// in simulator if required for debug.
//---------------------------------------------------------------------------
task wait_axi_adc_done;
   integer t, s, count;
   begin
   if(!adc_axi_based_done)  begin
      axi_message_enable = 1'd0;
      adc_done_last = adc_done;
      read_adc_done(adc_done);
      adc_done = adc_done | 'hffff_0000;
      @(posedge clk);
      @(posedge clk);

      for(t=0;t<p_max_slice_count;t=t+1) begin
         count = 0;
         for(s=0;s<p_max_slice_count;s=s+1) begin
            if ((adc_done_last[(t*4)+s]!= adc_done[(t*4)+s]) & adc_done[(t*4)+s]) begin
               count = count + 'd1;
            end
         end

         if (count == 4) begin
            $display("SIM-SPEEDUP ADC TILE = %d can be disabled (Use force on tile_clock_enable bit %1d to override)", t, (t+4));
            tile_clock_enable[4+t] = 1'd0;
         end
      end

      axi_message_enable = 1'd1;
   end
   end
endtask

task wait_axi_dac_done;
   integer t, s, count;
   begin
   if(!dac_axi_based_done)  begin
      axi_message_enable = 1'd0;
      dac_done_last = dac_done;
      read_dac_done(dac_done);
      dac_done = dac_done | 'hffff_0000;
      @(posedge clk);

      for(t=0;t<p_max_slice_count;t=t+1) begin
         count = 0;
         for(s=0;s<p_max_slice_count;s=s+1) begin
            if ((dac_done_last[(t*4)+s]!= dac_done[(t*4)+s]) & dac_done[(t*4)+s]) begin
               count = count + 'd1;
            end
         end

         if (count == 4) begin
            $display("SIM-SPEEDUP DAC TILE = %d can be disabled (Use force on tile_clock_enable bit %1d to override)", t, t);
            tile_clock_enable[t] = 1'd0;
         end
      end

      axi_message_enable = 1'd1;
   end
   end
endtask

//---------------------------------------------------------------------------
// DAC slice setup IP 
//---------------------------------------------------------------------------
task call_dac_setup_ip;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] width;
   input  [7:0] type;
   input  [7:0] interp;

   reg   [31:0] inc_val;
   reg   [15:0] mixer_cfg0;
   reg   [15:0] mixer_cfg1;
   reg   [15:0] dac_mix_mode;
   begin

      rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h80);  //  
      mixer_cfg0 = rd_data & 'hffff;
      rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h84);  //  
      mixer_cfg1 = rd_data & 'hffff;
   
      if ((|mixer_cfg0) | (|mixer_cfg1)) begin
         $display("Coarse mixer cfg0 set to = %x, clearing for simulation", mixer_cfg0);
         rfams_w(`T0_DAC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h80, 'd0);  //  
         $display("Coarse mixer cfg1 set to = %x, clearing for simulation", mixer_cfg1);
         rfams_w(`T0_DAC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h84, 'd0);  //
      
         rfams_w(`T0_DAC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h20, 'd6);  // Update Mixer settings
      end
      
      rfams_r(`T0_DAC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C4);  //
      dac_mix_mode = rd_data & 'h0002;   
      if (|dac_mix_mode) begin
         $display("DAC mix mode set to = %x, clearing for simulation", dac_mix_mode);
         rfams_w(`T0_DAC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C4, {rd_data[15:2], 1'b0, rd_data[0]});
      end

      // Allow for the common setup address space.
      tile = tile + 1;
      inc_val = interp;
      inc_val = inc_val * 'd8;
      // Source
      config_dac_exdes_src_slice (tile, slice, 'h0004, inc_val);        // increment
      config_dac_exdes_src_slice (tile, slice, 'h0008, `DGTYPE_TRGL_S); // type

      // Sink
      config_dac_tb_sink_slice(tile,slice,'h08, 127);   // Error boundary, Lower when model fixed
      config_dac_tb_sink_slice(tile,slice,'h20, 15000); // scaling from 0.75->1.2V up to bits
      config_dac_tb_sink_slice(tile,slice,'h20, 10000); // offset to remove
      config_dac_tb_sink_slice(tile,slice,'h34, 8000);  // Look for N changes in data
   end
endtask

//---------------------------------------------------------------------------
// DAC slice setup bench signal generation
//---------------------------------------------------------------------------
task call_dac_setup_bench;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] width;
   input  [7:0] type;
   input  [7:0] interp;

   reg   [31:0] inc_val;
   reg   [15:0] mixer_cfg0;
   reg   [15:0] mixer_cfg1;
   begin
      // Allow for the common setup address space.
      tile = tile + 1;
      // Source
          
      // dg_enable  : {access: rw,    bitOffset: 0,  bitWidth: 16, addrOffset: 0x00, default: 0, doc: 'Enable' }
      // dg_inc     : {access: rwpdef,bitOffset: 0,  bitWidth:  7, addrOffset: 0x04, default: 1, doc: 'Increment value' }
      // dg_type    : {access: rwpdef,bitOffset: 0,  bitWidth:  4, addrOffset: 0x08, default: 0, doc: 'Type of data to generate' }
      // dg_control : {access: rwpdef,bitOffset: 0,  bitWidth:  8, addrOffset: 0x0C, default: 0, doc: 'Allow additional control flags' }

      // config_dac_exdes_src_slice (tile, slice, 'h0008, 'h5); // Set the Data type to SINE wave

      config_dac_exdes_src_slice (tile, slice, 'h0000, 'hffff);
      // Sink
      config_dac_tb_sink_slice(tile,slice,'h00, 1  ); // Enable the sink lane 
   end
endtask

//---------------------------------------------------------------------------
// ADC slice setup IP only
//---------------------------------------------------------------------------
task call_adc_setup_ip;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] width;
   input  [7:0] type;
   input  [7:0] mixer;
   input  [7:0] decim;

   reg   [47:0] nco_freq;
   reg   [47:0] temp;
   reg   [15:0] mixer_cfg0;
   reg   [15:0] mixer_cfg1;
   reg   [15:0] rx_mc_config0;
   reg   [15:0] ti_dcb_ctrl0;
   begin
   
      // Disable dither so that we don't have to run through calibration.
      // This is for simulation only.
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C4);  //
      rx_mc_config0 = rd_data & 'hffdf;
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C4, rx_mc_config0);  // Turn off dither
      
      // Disable chopping.
      // This is for simulation only.
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h144);  //
      ti_dcb_ctrl0 = rd_data & 'h87ff;
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h144, ti_dcb_ctrl0);  // Turn off chopping
      
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h80);  //  
      mixer_cfg0 = rd_data & 'hffff;
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h84);  //  
      mixer_cfg1 = rd_data & 'hffff;
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h88);  //  
      $display("Coarse mixer settings = %x", (rd_data & 'hffff));
      
      if ((|mixer_cfg0) | (|mixer_cfg1)) begin
         $display("Coarse mixer cfg0 set to = %x, clearing for simulation", mixer_cfg0);
         rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h80, 'd0);  //  
         $display("Coarse mixer cfg1 set to = %x, clearing for simulation", mixer_cfg1);
         rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h84, 'd0);  //

         rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C, 'd6);  // Update Mixer settings

      end

      // 
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h94);  // Freq 47:32
      temp = rd_data & 'hffff;
      nco_freq = nco_freq | (temp << 32);
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h98);  // Freq 31:16 
      temp = rd_data & 'hffff;
      nco_freq = nco_freq | (temp << 16);
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h9C);  // Freq 15:0 
      temp = rd_data & 'hffff;
      nco_freq = nco_freq | (temp << 0);
      $display("NCO_Freq is %h %f", nco_freq, (nco_freq / (2**48)));

      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'ha0);  // Freq 17:16 
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'ha4);  // Freq 15:0 

      // Clean the NCO frequency
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h94, 'd0);  // Freq 47:32
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h98, 'd0);  // Freq 31:16 
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h9C, 'd0);  // Freq 15:0 
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1c, 'd2);  // Update NCO freq

   end
endtask

//---------------------------------------------------------------------------
// ADC slice setup bench only
//---------------------------------------------------------------------------
task call_adc_setup_bench;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] width;
   input  [7:0] type;
   input  [7:0] mixer;
   input  [7:0] decim;

   reg   [47:0] nco_freq;
   reg   [47:0] temp;
   reg   [15:0] mixer_cfg0;
   reg   [15:0] mixer_cfg1;
   begin

      // ADC source type inside testbench. This is unsynthesiseable code.
      config_adc_tb_source_slice (tile + 1,slice, 'h10, 'd0     ); // Data type 0=triangle, 3=sine
 
      //-----------------------------------------------------------------------
      // OVERRIDE MIXER FREQ,
      // We set this to zero in the demo_tb
      //-----------------------------------------------------------------------
      config_adc_tb_source_slice (tile + 1,slice, 'h08, 'd1     ); // Set the increment
      config_adc_tb_source_slice (tile + 1,slice, 'h24, 'd0     ); // Set the offset 
      config_adc_tb_source_slice (tile + 1,slice, 'h28, 'd1000  ); // Set the phase high 
      config_adc_tb_source_slice (tile + 1,slice, 'h2C, 'd1000  ); // Set the phase low 
      config_adc_tb_source_slice (tile + 1,slice, 'h00, 'd1     ); // Enable the generator

      // ADC sink, inside example design logic, synthesiseable
      config_adc_exdes_sink_slice(tile + 1, slice, 'h04, 'hff    ); // Error boundary - remember only 12 bit for 3:0 = f. 4 Bit error mask in effect = 0->15
      config_adc_exdes_sink_slice(tile + 1, slice, 'h08, 'h01    ); // 
      config_adc_exdes_sink_slice(tile + 1, slice, 'h10, 'd4000  ); // Wait data cycles
      // if ((type == 0)) begin
      //    case(mixer)
      //    0: begin
      //       $display("REAL data with IQ in = %d", mixer);
      //       config_adc_exdes_sink_slice(tile + 1,    slice, 'h00, 8'hFF   ); // Enable             
      //       end
      //    2: begin
      //       $display("REAL data with Real out = %d", mixer);
      //       config_adc_exdes_sink_slice(tile + 1,    slice, 'h00, 8'h0F   ); // Enable             
      //       end
      //    endcase
      // end else begin
      //    // As we set the Mixer freq to be 0, the Q output bobbles around 0 with few
      //    // transitions. Disable this channel
      //    $display("IQ data with Mixer = %d", mixer);
      //    config_adc_exdes_sink_slice(tile + 1,    slice, 'h00, 8'h55   ); // Enable 
      //end

   end
endtask

//---------------------------------------------------------------------------
// ADC sink slice enable
//---------------------------------------------------------------------------
task call_adc_enable_sinks;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] width;
   input  [7:0] type;
   input  [7:0] mixer;
   input  [7:0] decim;

   begin

      if ((type == 0)) begin
         case(mixer)
         0: begin
            $display("REAL data with IQ in = %d", mixer);
            config_adc_exdes_sink_slice(tile + 1,    slice, 'h00, 8'hFF   ); // Enable             
            end
         2: begin
            $display("REAL data with Real out = %d", mixer);
            config_adc_exdes_sink_slice(tile + 1,    slice, 'h00, 8'h0F   ); // Enable             
            end
         endcase
      end else begin
         // As we set the Mixer freq to be 0, the Q output bobbles around 0 with few
         // transitions. Disable this channel
         $display("IQ data with Mixer = %d", mixer);
         config_adc_exdes_sink_slice(tile + 1,    slice, 'h00, 8'h55   ); // Enable 
      end

   end
endtask

//---------------------------------------------------------------------------
// ADC slice setup IP only
//---------------------------------------------------------------------------
task call_adc_disable_mix;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] width;
   input  [7:0] type;
   input  [7:0] mixer;
   input  [7:0] decim;

   reg   [47:0] nco_freq;
   reg   [47:0] temp;
   reg   [15:0] mixer_cfg0;
   reg   [15:0] mixer_cfg1;
   reg   [15:0] rx_mc_config0;
   reg   [15:0] ti_dcb_ctrl0;
   begin
      
      // Disable dither so that we don't have to run through calibration.
      // This is for simulation only.
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C4);  //
      rx_mc_config0 = rd_data & 'hffdf;
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C4, rx_mc_config0);  // Turn off dither
      
      // Disable chopping.
      // This is for simulation only.
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h144);  //
      ti_dcb_ctrl0 = rd_data & 'h87ff;
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h144, ti_dcb_ctrl0);  // Turn off chopping
      
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h80);  //  
      mixer_cfg0 = rd_data & 'hffff;
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h84);  //  
      mixer_cfg1 = rd_data & 'hffff;
      rfams_r(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h88);  //  
      $display("Coarse mixer settings = %x", (rd_data & 'hffff));
      
      if ((|mixer_cfg0) | (|mixer_cfg1)) begin
         $display("Coarse mixer cfg0 set to = %x, clearing for simulation", mixer_cfg0);
         rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h80, 'd0);  //  
         $display("Coarse mixer cfg1 set to = %x, clearing for simulation", mixer_cfg1);
         rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h84, 'd0);  // 

         rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1C, 'd6);  // Update Mixer settings

      end

      // Clean the NCO frequency
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h94, 'd0);  // Freq 47:32
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h98, 'd0);  // Freq 31:16 
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h9C, 'd0);  // Freq 15:0 
      rfams_w(`T0_ADC_BASE_ADDR  + ('h4000 * tile) + ('h400 * slice) + 'h1c, 'd2);  // Update NCO freq

   end
endtask

//---------------------------------------------------------------------------
// ADC slice setup bench only
//---------------------------------------------------------------------------
task call_adc_setup_ip_end_state;
   input  [7:0] tile;
   begin

   // Stop the CAL running
   rfams_w(`ACC0_RESTART_STATE_END_ADDR + ('h4000 * tile), 32'hb); //
   rfams_w(`ACC0_RESTART_REGISTER_ADDR  + ('h4000 * tile), 32'd1); // Restart the POR
       
   end
endtask

//---------------------------------------------------------------------------
// Demo TB Dac Sink Slice configure task.
//
// 0_00  .. Slice 0
// 3_00     Slice 3
// 0_000 .. Tile  0
// 3_000    Tile  3
//  enable         : rw,    off: 0, width:  1,  addr: 0x00
//  dg_inc         : rw,    off: 0, width: 14,  addr: 0x08
//  dg_type        : rw,    off: 0, width:  3,  addr: 0x10
//  scaling_factor : rw,    off: 0, width: 32,  addr: 0x20
//  offset         : rw,    off: 0, width: 32,  addr: 0x24
//  phase_high     : rw,    off: 0, width: 16,  addr: 0x28
//  phase_low      : rw,    off: 0, width: 16,  addr: 0x2C
//  out_clk_div    : rw,    off: 0, width: 16,  addr: 0x30
//  change_count   : rw,    off: 0, width: 16,  addr: 0x34
//  error          : roSig, off: 0, width:  1,  addr: 0x38
//
//---------------------------------------------------------------------------

task config_dac_tb_sink_slice;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] address;
   input [31:0] value;
   reg   [31:0] working;
   begin
   working = (tile << 12) + (slice << 8) + address;
   tbsnk_w(working, value);
   end
endtask

task config_dac_exdes_src_slice;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] address;
   input [31:0] value;
   reg   [31:0] working;
   begin
   working = (tile << 12) + (slice << 8) + address;
   exsrc_w(working, value);
   end
endtask

task config_adc_tb_source_slice;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] address;
   input [31:0] value;
   reg   [31:0] working;
   begin
   working = (tile << 12) + (slice << 8) + address;
   tbsrc_w(working, value);
   end
endtask

task config_adc_exdes_sink_slice;
   input  [7:0] tile;
   input  [7:0] slice;
   input  [7:0] address;
   input [31:0] value;
   reg   [31:0] working;
   begin
   working = (tile << 12) + (slice << 8) + address;
   exsnk_w(working, value);
   end
endtask

task read_dac_done;
   output [31:0] value;
   begin
   tbsnk_r('h40);
   value = rd_data;
   end
endtask

task read_adc_done;
   output [31:0] value;
   begin
   exsnk_r('h40);
   value = rd_data;
   end
endtask

//---------------------------------------------------------------------------
// AXI RW tasks for each base address. Written as single lines, they are
// a wrapper around axi tasks with the appropiate address offset added to the
// address passed into the task.
//---------------------------------------------------------------------------
task rfams_w; input [31:0] addr;input [31:0] data; begin axi_write (`BASE_ADDR_RFAMS + addr, data);end endtask
task exsrc_w; input [31:0] addr;input [31:0] data; begin axi_write (`BASE_ADDR_EXSRC + addr, data);end endtask
task exsnk_w; input [31:0] addr;input [31:0] data; begin axi_write (`BASE_ADDR_EXSNK + addr, data);end endtask
task tbsrc_w; input [31:0] addr;input [31:0] data; begin axi_write (`BASE_ADDR_TBSRC + addr, data);end endtask
task tbsnk_w; input [31:0] addr;input [31:0] data; begin axi_write (`BASE_ADDR_TBSNK + addr, data);end endtask

task rfams_r; input [31:0] addr; begin axi_read  (`BASE_ADDR_RFAMS + addr);end endtask
task exsrc_r; input [31:0] addr; begin axi_read  (`BASE_ADDR_EXSRC + addr);end endtask
task exsnk_r; input [31:0] addr; begin axi_read  (`BASE_ADDR_EXSNK + addr);end endtask
task tbsrc_r; input [31:0] addr; begin axi_read  (`BASE_ADDR_TBSRC + addr);end endtask
task tbsnk_r; input [31:0] addr; begin axi_read  (`BASE_ADDR_TBSNK + addr);end endtask

// Wrap the reads with a test
task rfams_ck; input [31:0] addr;input [31:0] data; begin axi_check  (`BASE_ADDR_RFAMS + addr, data);end endtask
task exsrc_ck; input [31:0] addr;input [31:0] data; begin axi_check  (`BASE_ADDR_EXSRC + addr, data);end endtask
task exsnk_ck; input [31:0] addr;input [31:0] data; begin axi_check  (`BASE_ADDR_EXSNK + addr, data);end endtask
task tbsrc_ck; input [31:0] addr;input [31:0] data; begin axi_check  (`BASE_ADDR_TBSRC + addr, data);end endtask
task tbsnk_ck; input [31:0] addr;input [31:0] data; begin axi_check  (`BASE_ADDR_TBSNK + addr, data);end endtask

// read modify write
task rfams_rmw; input [31:0] addr;input [31:0] mask; input [31:0] value; begin axi_rmw  (`BASE_ADDR_RFAMS + addr, mask, value); end endtask
task exsrc_rmw; input [31:0] addr;input [31:0] mask; input [31:0] value; begin axi_rmw  (`BASE_ADDR_EXSRC + addr, mask, value); end endtask
task exsnk_rmw; input [31:0] addr;input [31:0] mask; input [31:0] value; begin axi_rmw  (`BASE_ADDR_EXSNK + addr, mask, value); end endtask
task tbsrc_rmw; input [31:0] addr;input [31:0] mask; input [31:0] value; begin axi_rmw  (`BASE_ADDR_TBSRC + addr, mask, value); end endtask
task tbsnk_rmw; input [31:0] addr;input [31:0] mask; input [31:0] value; begin axi_rmw  (`BASE_ADDR_TBSNK + addr, mask, value); end endtask

//---------------------------------------------------------------------------
// AXI write task.
//---------------------------------------------------------------------------
task axi_write;
  input [31:0] addr;
  input [31:0] data;
  begin
    while (req_busy)       // Wait on other tasks completing
      @(posedge clk);
    
    @(posedge clk);        // Drive Address, data and the request flag
    wr_req  <= 1'b1;
    wr_data <= data;
    address <= addr;

    while (req_busy == 0)  // Wait until the AXI convertor is busy
      @(posedge clk);

    wr_req  <= 1'b0;       // Clear the request

    while (req_busy)       // Wait for the AXI4-Lite transaction to complete
      @(posedge clk);

`ifdef ENABLE_RW_MESSAGE_PRINT
    $display ("MWR: @ 0x%8x = 0x%x", address, data);
`endif

  end
endtask // axi_write

//---------------------------------------------------------------------------
// AXI read task.
//---------------------------------------------------------------------------
task axi_read;
  input [31:0] addr;
  begin
    while (req_busy)       // Wait on other tasks completing
      @(posedge clk);
    
    @(posedge clk);        // Drive Address and the request flag
    rd_req  <= 1'b1;
    address <= addr;

    while (req_busy == 0)  // Wait until the AXI convertor is busy
      @(posedge clk);

    rd_req  <= 1'b0;       // Clear the request

    while (req_busy)       // Wait for the AXI4-Lite transaction to complete
      @(posedge clk);

`ifdef ENABLE_RW_MESSAGE_PRINT
    $display ("MRD: @ 0x%8x = 0x%x", address, rd_data);
`endif
  end
endtask // axi_read

// AXI read task with a data check
task axi_check;
  input [31:0] addr;
  input [31:0] value;
  begin
    axi_read(addr);
    if (rd_data != value)
       $display ("T=%12d: MISMATCH IN AXI READ: @ 0x%8x = 0x%8x, expected 0x%8x", $time, address, rd_data, value);
  end
endtask // axi_check

// AXI poll task
task axi_poll;
  input [31:0] addr;
  input [31:0] mask;
  input [31:0] value;
  input [31:0] attempts;
  begin
    while (attempts>0) begin
      axi_read(addr);
      if ((rd_data & mask) == value)
        attempts = 0;
      else
        attempts = attempts - 1;
    end
  end
endtask // axi_poll

// AXI read modify write task
task axi_rmw;
  input [31:0] addr;
  input [31:0] mask;
  input [31:0] value;
  begin
    axi_read(addr);
    working_value = rd_data;
    working_value = working_value & (~mask);
    working_value = working_value | value;
    axi_write(addr, working_value);
  end
endtask // axi_rmw

//---------------------------------------------------------------------------
// Wait a number of AXI clock cycles.
//---------------------------------------------------------------------------
task int_axi_reset_after_for_cycles;
  input [31:0] cycles_after;
  input [31:0] cycles_for;
  begin
    while (cycles_after > 0) begin
      @(posedge clk);
      cycles_after <= cycles_after - 'd1;
    end
    int_axi_aresetn = 0;
    while (cycles_for > 0) begin
      @(posedge clk);
      cycles_for <= cycles_for - 'd1;
    end
    int_axi_aresetn = 1;
    int_tb_aresetn  = 1;
  end
endtask // int_axi_reset_after_for_cycles

task axi_cwait;
  input [31:0] cycles;
  begin
    @(posedge clk);
    @(posedge clk);
    $display("T=%d: Delay of %d cycles requested.", $time, cycles);
    while (cycles > 0) begin
      @(posedge clk);
      cycles <= cycles - 'd1;
    end
    @(posedge clk);
  end
endtask // axi_cwait

task axi_cwait_to;
  input [31:0] cycles;
  begin
    while (cycles > 0) begin
      @(posedge clk);
      cycles <= cycles - 'd1;
    end
    $display("ERROR RFAMS demo_tb timeout");
    // Set sequence done instead of stopping so the simulator stops hear the
    // stimulus in the file
    set_seq_done;
    //$stop;
  end
endtask // axi_cwait

task delay_ps_32;
  input [31:0] delay_time;
  begin
    #(delay_time);
  end
endtask // delay_ps_32
  
task set_seq_done;
  begin
  seq_done=1;
  end
endtask // set_seq_done

// Tasks to remove
//-----------------------------------------------------------------------------
// DAC exdes data generator
//-----------------------------------------------------------------------------

task enable_exdes_dac_generator;
   begin
   // DAC
   exdes_dac_en_tile('h0_000, 'hf); 
   exdes_dac_en_tile('h1_000, 'hf); 
   exdes_dac_en_tile('h2_000, 'hf); 
   exdes_dac_en_tile('h3_000, 'hf); 
   end
endtask

task exdes_dac_en_tile;
   input [31:0] base;
   input  [3:0] slice_en;
   begin
   exdes_dac_en_slice (base + 'h000, slice_en[0]);
   exdes_dac_en_slice (base + 'h100, slice_en[1]);
   exdes_dac_en_slice (base + 'h200, slice_en[2]);
   exdes_dac_en_slice (base + 'h300, slice_en[3]);
   end
endtask

task exdes_dac_en_slice;
   input [31:0] base;
   input        slice_en;
   begin
      if (slice_en) begin
         exsrc_w (base + 'h0008, 'h10);
         exsrc_w (base + 'h000C, 'h10);
         exsrc_w (base + 'h0000, 'hffff);
      end
   end
endtask

//-----------------------------------------------------------------------------
// ADC demo_tb data generator
//-----------------------------------------------------------------------------

task enable_demotb_adc_generator;
   begin
   // DAC
   demotb_adc_en_tile('h1_000, 'hf); 
   demotb_adc_en_tile('h2_000, 'hf); 
   demotb_adc_en_tile('h3_000, 'hf); 
   demotb_adc_en_tile('h4_000, 'hf); 
   end
endtask

task demotb_adc_en_tile;
   input [31:0] base;
   input  [3:0] slice_en;
   begin
   demotb_adc_en_slice (base + 'h000, slice_en[0]);
   demotb_adc_en_slice (base + 'h100, slice_en[1]);
   demotb_adc_en_slice (base + 'h200, slice_en[2]);
   demotb_adc_en_slice (base + 'h300, slice_en[3]);
   end
endtask

task demotb_adc_en_slice;
   input [31:0] base;
   input        slice_en;
   begin
      if (slice_en) begin
         tbsrc_w (base + 'h08, 'd64);  // Set the increment
         tbsrc_w (base + 'h20, 'd1);   // Set the scaling factor 
         tbsrc_w (base + 'h24, 'd0);   // Set the offset 
         tbsrc_w (base + 'h28, 'd100); // Set the phase high 
         tbsrc_w (base + 'h2C, 'd20);  // Set the phase low 
         tbsrc_w (base + 'h00, 'd1);   // Enable the generator
      end
   end
endtask

//---------------------------------------------------------------------------
// ADC Manua; startup sequence
//---------------------------------------------------------------------------

task adc0_manual_start;
   begin

   rfams_r(`T0_ADC_BASE_ADDR); //          
   rfams_w(`T0_ADC_BASE_ADDR, 'd1); //          
   rfams_r(`T0_ADC_BASE_ADDR); //          
   rfams_w(`T0_ADC_BASE_ADDR, 'd0); //          
   rfams_r(`T0_ADC_BASE_ADDR); //          

   
   rfams_r(`T1_ADC_BASE_ADDR); //          
   rfams_r(`T2_ADC_BASE_ADDR); //          
   rfams_r(`T3_ADC_BASE_ADDR); //          

   rfams_r(`T0_DAC_BASE_ADDR); //          
   rfams_r(`T1_DAC_BASE_ADDR); //          
   rfams_r(`T2_DAC_BASE_ADDR); //          
   rfams_r(`T3_DAC_BASE_ADDR); //          
   

   rfams_w(`T0_ADC_BASE_ADDR, 0); //          
   rfams_w(`T1_ADC_BASE_ADDR, 0); //          
   rfams_w(`T2_ADC_BASE_ADDR, 0); //          
   rfams_w(`T3_ADC_BASE_ADDR, 0); //          

   rfams_w(`T0_DAC_BASE_ADDR, 0); //          
   rfams_w(`T1_DAC_BASE_ADDR, 0); //          
   rfams_w(`T2_DAC_BASE_ADDR, 0); //          
   rfams_w(`T3_DAC_BASE_ADDR, 0); //  

   // Stop the ADC at stage 3  
   rfams_w(`ACC0_RESET_REGISTER_ADDR,     1);
   rfams_w(`ACC0_RESTART_STATE_END_ADDR,  2);
   rfams_w(`ACC0_RESET_REGISTER_ADDR,    0);
   rfams_w(`ACC0_RESTART_REGISTER_ADDR,  1);
   rfams_w(`ACC0_RESTART_REGISTER_ADDR,  0);

   axi_cwait    (1000); // 
  
   rfams_w(`T0_ADC_BASE_ADDR + ('h0725<<2), 16'h8000); // ADC_T0_HSCOM_HSCOM_PWR_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0725<<2), 16'hc000); // ADC_T0_HSCOM_HSCOM_PWR_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h072b<<2), 16'h0100); // ADC_T0_HSCOM_VBG_CTRL_ADDR          
   rfams_w(`T0_ADC_BASE_ADDR + ('h0070<<2), 16'h0020); // ADC_T0_S0_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0170<<2), 16'h0020); // ADC_T0_S1_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0270<<2), 16'h0020); // ADC_T0_S2_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0370<<2), 16'h0020); // ADC_T0_S3_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0725<<2), 16'hfc00); // ADC_T0_HSCOM_HSCOM_PWR_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0725<<2), 16'hfe00); // ADC_T0_HSCOM_HSCOM_PWR_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0725<<2), 16'hfe40); // ADC_T0_HSCOM_HSCOM_PWR_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0070<<2), 16'h003f); // ADC_T0_S0_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0170<<2), 16'h003f); // ADC_T0_S1_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0270<<2), 16'h003f); // ADC_T0_S2_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0370<<2), 16'h003f); // ADC_T0_S3_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0724<<2), 16'h1000); // ADC_T0_HSCOM_CLK_NETWORK_CTRL1_ADDR 
   rfams_w(`T0_ADC_BASE_ADDR + ('h0070<<2), 16'h007f); // ADC_T0_S0_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0170<<2), 16'h007f); // ADC_T0_S1_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0270<<2), 16'h007f); // ADC_T0_S2_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0370<<2), 16'h007f); // ADC_T0_S3_RX_MC_PWRDWN_ADDR         
   rfams_w(`T0_ADC_BASE_ADDR + ('h0724<<2), 16'h0000); // ADC_T0_HSCOM_CLK_NETWORK_CTRL1_ADDR 
   rfams_w(`T0_ADC_BASE_ADDR + ('h072c<<2), 16'h0002); // ADC_T0_HSCOM_CLK_DIV_ADDR           
   rfams_w(`T0_ADC_BASE_ADDR + ('h0300<<2), 16'h001f); // ADC_T0_S3_CLK_ENABLE_ADDR           
   rfams_w(`T0_ADC_BASE_ADDR + ('h0200<<2), 16'h001f); // ADC_T0_S2_CLK_ENABLE_ADDR           
   rfams_w(`T0_ADC_BASE_ADDR + ('h0100<<2), 16'h001f); // ADC_T0_S1_CLK_ENABLE_ADDR           
   rfams_w(`T0_ADC_BASE_ADDR + ('h0000<<2), 16'h001f); // ADC_T0_S0_CLK_ENABLE_ADDR           
   rfams_w(`T0_ADC_BASE_ADDR + ('h0302<<2), 16'h0808); // ADC_T0_S3_FABRIC_RATE_ADDR          
   rfams_w(`T0_ADC_BASE_ADDR + ('h0202<<2), 16'h0808); // ADC_T0_S2_FABRIC_RATE_ADDR          
   rfams_w(`T0_ADC_BASE_ADDR + ('h0102<<2), 16'h0808); // ADC_T0_S1_FABRIC_RATE_ADDR          
   rfams_w(`T0_ADC_BASE_ADDR + ('h0002<<2), 16'h0808); // ADC_T0_S0_FABRIC_RATE_ADDR          
   rfams_w(`T0_ADC_BASE_ADDR + ('h0011<<2), 16'h0001); // ADC_T0_S0_DECIMATION_MODE_ADDR      
   rfams_w(`T0_ADC_BASE_ADDR + ('h0111<<2), 16'h0001); // ADC_T0_S1_DECIMATION_MODE_ADDR      
   rfams_w(`T0_ADC_BASE_ADDR + ('h0211<<2), 16'h0001); // ADC_T0_S2_DECIMATION_MODE_ADDR      
   rfams_w(`T0_ADC_BASE_ADDR + ('h0311<<2), 16'h0001); // ADC_T0_S3_DECIMATION_MODE_ADDR      
   rfams_w(`T0_ADC_BASE_ADDR + ('h0074<<2), 16'h0080); // ADC_T0_S0_RX_PAIR_MC_CONFIG0_ADDR   
   rfams_w(`T0_ADC_BASE_ADDR + ('h0174<<2), 16'h0080); // ADC_T0_S1_RX_PAIR_MC_CONFIG0_ADDR   
   rfams_w(`T0_ADC_BASE_ADDR + ('h013a<<2), 16'h0004); // ADC_T0_S1_SWITCH_MATRIX_CONFIG_ADDR 
   rfams_w(`T0_ADC_BASE_ADDR + ('h0274<<2), 16'h0080); // ADC_T0_S2_RX_PAIR_MC_CONFIG0_ADDR   
   rfams_w(`T0_ADC_BASE_ADDR + ('h023a<<2), 16'h0008); // ADC_T0_S2_SWITCH_MATRIX_CONFIG_ADDR 
   rfams_w(`T0_ADC_BASE_ADDR + ('h0374<<2), 16'h0080); // ADC_T0_S3_RX_PAIR_MC_CONFIG0_ADDR   
   rfams_w(`T0_ADC_BASE_ADDR + ('h033a<<2), 16'h000c); // ADC_T0_S3_SWITCH_MATRIX_CONFIG_ADDR 
   rfams_w(`T0_ADC_BASE_ADDR + ('h0010<<2), 16'h8000); // CFG_T0_CONTROL_ADC_COMMON_ADDR      
   end
endtask

//---------------------------------------------------------------------------
// Task to manually start the DAC and ADC
//---------------------------------------------------------------------------

task run_manual_dac_adc_startup;
   begin
   rfams_w(`T0_DCC_BASE_ADDR + 'h00, 'hFFFF_FFFF); // Reset SM

   rfams_w('h0_2000, 'hFFFF_FFFF); // Reset SM
   rfams_w('h0_2008, 'hFFFF_FFFF); // Start and end SM at ff, i.e, does nothing
   rfams_r('h0_2000);
   rfams_r('h0_4000);

   rfams_w(`T0_DAC_BASE_ADDR + 'h1c94, 'h00008000); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h1c94, 'h0000c000); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h1cac, 'h00000100); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h1cac, 'h00000100); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h1cac, 'h00000180); // AXI WRITE:
   rfams_r(`T0_DAC_BASE_ADDR + 'h1d28);             // AXI READ :
   rfams_w(`T0_DAC_BASE_ADDR + 'h01c0, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h05c0, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h09c0, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0dc0, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h1c94, 'h0000fc00); // AXI WRITE:
   rfams_r(`T0_DAC_BASE_ADDR + 'h1d24);             // AXI READ :
   rfams_w(`T0_DAC_BASE_ADDR + 'h1c94, 'h0000fe00); // AXI WRITE:
   rfams_r(`T0_DAC_BASE_ADDR + 'h1c90);             // AXI READ :
   rfams_w(`T0_DAC_BASE_ADDR + 'h1c94, 'h0000fe40); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h01c4, 'h00000014); // AXI WRITE:
   rfams_r(`T0_DAC_BASE_ADDR + 'h01cc);             // AXI READ :
   rfams_w(`T0_DAC_BASE_ADDR + 'h01cc, 'h00000000); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h05c4, 'h00000014); // AXI WRITE:
   rfams_r(`T0_DAC_BASE_ADDR + 'h05cc);             // AXI READ :
   rfams_w(`T0_DAC_BASE_ADDR + 'h05cc, 'h00000000); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h09c4, 'h00000014); // AXI WRITE:
   rfams_r(`T0_DAC_BASE_ADDR + 'h09cc);             // AXI READ :
   rfams_w(`T0_DAC_BASE_ADDR + 'h09cc, 'h00000000); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0dc4, 'h00000014); // AXI WRITE:
   rfams_r(`T0_DAC_BASE_ADDR + 'h0dcc);             // AXI READ :
   rfams_w(`T0_DAC_BASE_ADDR + 'h0dcc, 'h00000000); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h1c90, 'h00001000); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h1cb0, 'h00000002); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0000, 'h0000000f); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0008, 'h00000808); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0400, 'h0000000f); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0408, 'h00000808); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0800, 'h0000000f); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0808, 'h00000808); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0c00, 'h0000000f); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0c08, 'h00000808); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0cc4, 'h00000040); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h08c4, 'h00000040); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h04c4, 'h00000040); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h00c4, 'h00000040); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0c40, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0840, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0440, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0040, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0d84, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0984, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0584, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0184, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0d80, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0980, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0580, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0180, 'h00000001); // AXI WRITE:
   rfams_w(`T0_DAC_BASE_ADDR + 'h0054, 'h00008000); // AXI WRITE:

   end
endtask // run_manual_dac_adc_startup

//----------------------------------------------------------------------------
// Loop through the DRP addresses writing to each one. Ensures that 
// all accesses are correct. To be used only for testing
//----------------------------------------------------------------------------
// task write_drp_test;
  // input [17:0] drp_baseaddr;
  // input [17:0] chip_sel;
  // reg   [17:0] sel;
   // begin : read_seq
       // integer i, count;
       
       // $display ("Start writing DRP Addr from: @ 0x%4x", drp_baseaddr); 
       // count = 0;
       // for (i = 0; i<100; i=i+1)
       // begin
         // rfams_w(drp_baseaddr + 4*i, 'hF);
         
         // sel  = dut_and_data_i.DUT.i_usp_rf_data_converter_0_block.inst.i_register_decode.chip_select;
         // if (sel != chip_sel) begin
           // $display ("ERROR: Invalid chip select values: 0x%5x != 0x%5x", sel, chip_sel); 
           // $stop;    
         // end  
         
         // while (req_busy)       // Wait for the AXI4-Lite transaction to complete
           // @(posedge clk);
           
         // count = count + 1;
       // end
       // $display ("Completed a total of %d DRP Writes", count);
   // end
// endtask

//----------------------------------------------------------------------------
// Loop through the DRP addresses reading each one. Ensures that all accesses
// are correct. To be used only for testing
//----------------------------------------------------------------------------
// task read_drp_test;
  // input [17:0] drp_baseaddr;
  // input [17:0] chip_sel;
  // reg  [17:0] sel;
   // begin : read_seq
       // integer i, count;
       // count = 0;
       // for (i = 0; i<1400; i=i+1)
       // begin
         // rfams_r(drp_baseaddr + 4*i);
        
         // sel  = dut_and_data_i.DUT.i_usp_rf_data_converter_0_block.inst.i_register_decode.chip_select;
         // if (sel != chip_sel) begin
           // $display ("ERROR: Invalid chip select values: 0x%5x != 0x%5x", sel, chip_sel);
           // $stop;
         // end  
                  
         // while (req_busy)       // Wait for the AXI4-Lite transaction to complete
           // @(posedge clk);
           
         // count = count + 1;         
       // end
       // $display ("Completed a total of %d DRP Reads", count);
   // end
// endtask

//----------------------------------------------------------------------------
// convert simple RW strobing to AXI4 Lite.
//----------------------------------------------------------------------------
axi4l_ns_rw_2_axi rw_2_axi_i (
     .clk              ( clk                ),
     .rst              ( reset              ),
     
     .wr_req           ( wr_req             ),
     .rd_req           ( rd_req             ),
     .address          ( address            ),
     .wr_data          ( wr_data            ),
     .rd_data          ( rd_data            ),
     
     .axi_aresetn      ( axi_aresetn        ),
     .axi_awaddr       ( axi_awaddr         ),
     .axi_awvalid      ( axi_awvalid        ),
     .axi_awready      ( axi_awready        ),
     
     .axi_wdata        ( axi_wdata          ),
     .axi_wvalid       ( axi_wvalid         ),
     .axi_wready       ( axi_wready         ),
     
     .axi_bresp        ( axi_bresp          ),
     .axi_bvalid       ( axi_bvalid         ),
     .axi_bready       ( axi_bready         ),
     
     .axi_araddr       ( axi_araddr         ),
     .axi_arvalid      ( axi_arvalid        ),
     .axi_arready      ( axi_arready        ),
     
     .axi_rdata        ( axi_rdata          ),
     .axi_rresp        ( axi_rresp          ),
     .axi_rvalid       ( axi_rvalid         ),
     .axi_rready       ( axi_rready         ),
     
     .access_busy      ( req_busy           ) 
);

endmodule

//////////////////////////////////////////////////////////////////////////////////
// Description: module to convert a simple strobe RW Data interface to AXI4-Lite
// This has been included as it both simplified the RW tasks above and can also
// be used as a standalone module in HW, with the input control strobes driven 
// by VIO or some other mechanism.
// Once requrested by at least a single pulse the SM will carry out a read or 
// write access, simultanious is not supported, with the access_busy going high
// when the request is accepted and remaining high for the duration of the AXI4
// transaction
// Additional Comments: Conversion of the VHDL AXI IF state machine.
//////////////////////////////////////////////////////////////////////////////////

module axi4l_ns_rw_2_axi (

  input             clk                   , // 
  input             rst                   , // 

  // VIO Interface
  input             wr_req                , // 
  input             rd_req                , // 
  input      [31:0] address               , // 
  input      [31:0] wr_data               , // 
  output reg [31:0] rd_data       = 0     , // 

  // AXI-Lite Interface
  output reg        axi_aresetn   = 0     , // 
  output reg [31:0] axi_awaddr    = 0     , // 
  output reg        axi_awvalid   = 0     , // 
  input             axi_awready           , // 
  
  output reg [31:0] axi_wdata     = 0     , // 
  output reg        axi_wvalid    = 0     , // 
  input             axi_wready            , // 
  
  input       [1:0] axi_bresp             , // 
  input             axi_bvalid            , // 
  output reg        axi_bready    = 0     , // 
  
  output reg [31:0] axi_araddr    = 0     , // 
  output reg        axi_arvalid   = 0     , // 
  input             axi_arready           , // 
  
  input      [31:0] axi_rdata             , // 
  input       [1:0] axi_rresp             , // 
  input             axi_rvalid            , // 
  output reg        axi_rready    = 0     , // 

  // Status
  output reg        access_busy   = 0       // 

  );

  parameter A_IDLE = 'd0;
  parameter WR0    = 'd1;
  parameter WR1    = 'd2;
  parameter RD0    = 'd3;
  parameter RD1    = 'd4;
  
  reg [3:0] accessor=0;

  //-- AXI interface
  //-- State machine for controlling individual writes and reads to and from the
  //-- AXI management registers
  always @(posedge clk)
    begin
    if (rst)
      begin
      accessor        <= A_IDLE;
      axi_awaddr      <= 'd0;
      axi_awvalid     <= 'd0;
      axi_wdata       <= 'd0;
      axi_wvalid      <= 'd0;
      axi_bready      <= 'd0;
      axi_araddr      <= 'd0;
      axi_arvalid     <= 'd0;
      axi_rready      <= 'd0;
      axi_aresetn     <= 'd0;
      access_busy     <= 'd0;
      end

    else
      begin

      axi_aresetn <= 'd1;
      accessor    <= accessor;

      case(accessor)
        A_IDLE : 
          begin
          axi_awvalid <= 'd0;
          axi_wvalid  <= 'd0;
          axi_bready  <= 'd0;
          axi_arvalid <= 'd0;
          axi_rready  <= 'd0;
          if (wr_req)
            begin
            accessor <= WR0;
            access_busy <= 1;
            end
          else 
            if (rd_req)
              begin
              accessor <= RD0;
              access_busy <= 1;
              end
            else
              begin
              accessor <= accessor;
              access_busy <= 0;
              end
          end

        WR0 :
          begin
          // Write address/data phase
          axi_awaddr  <= address;
          axi_awvalid <= 'd1;
          axi_wdata   <= wr_data;
          axi_wvalid  <= 'd1;
          axi_bready  <= 'd1;
          accessor    <= WR1;
          end
          
        WR1 :
          begin
          if (axi_awready)
            axi_awvalid <= 0;

          if (axi_wready)
            begin
            axi_wvalid <= 0;
            axi_bready <= 1;
            end

          //-- response phase
          if (axi_bvalid)
            begin
            accessor   <= A_IDLE;
            axi_bready <= 0;
            end
          end

        RD0 :
          begin
          // -- Read address phase
          axi_araddr  <= address;

          if ( axi_arready & axi_arvalid)
            begin
            accessor <= RD1;
            axi_arvalid <= 0;
            axi_rready  <= 1; 
            end
          else
            begin
            axi_arvalid <= 1;
            axi_rready  <= 0;
          end
          
          end

        RD1 :
          begin
          // -- Read response phase
          axi_arvalid <= 0;

          if (axi_rvalid)
            begin
            accessor     <= A_IDLE;
            axi_rready   <= 0;
            rd_data      <= axi_rdata;
            end
          end

      endcase
      end
    end 

endmodule

//////////////////////////////////////////////////////////////////////////////////
// Description: Simple module to facilitate simulation halt in IPI or general HDL
// Note this module is synthesiseable and can
// be used in hardware, either to drive LED, ILA or registers.
//////////////////////////////////////////////////////////////////////////////////
`ifdef ENABLE_IPI_HELPER_BLOCKS
module axi4l_ns_sim_stopper #(
   parameter edge_count_width     = 8,
   parameter cycles_count_width   = 16,
   parameter default_edge_count   = 1,
   parameter default_cycles_count = 1000,
   parameter tieoff_widths        = 1
) (
`ifdef ENABLE_SIM_STOPPER_COUNT_PORTS
   input  wire [edge_count_width   - 1:0] edges_to_count         , // Stop only after this number of edges
   input  wire [cycles_count_width - 1:0] cycles_after_last_edge , // After the last edge, wait this many cycles before raising complete flag
`endif
   input  wire                            rising_edge_signal     , // Signal to count edges on. Rising edge count
   input  wire                            clk                    , //
   input  wire                            restart                , //
       
   output wire [tieoff_widths-1:0]        high_tieoff            , // Quick user tieoff
   output wire [tieoff_widths-1:0]        low_tieoff             , // Quick user tieoff
   output reg                             complete_flag=0          // Complete flag

   );

reg                            rising_edge_signal_r = 0; // 
reg [edge_count_width - 1:0]   edge_count           = 0; // 
reg [cycles_count_width - 1:0] cycles_count         = 0; // 

assign low_tieoff  = {tieoff_widths,{1'b0}};
assign high_tieoff = {tieoff_widths,{1'b1}};

`ifndef ENABLE_SIM_STOPPER_COUNT_PORTS
   wire [edge_count_width - 1:0]   edges_to_count         ; // Stop only after this number of edges
   wire [cycles_count_width - 1:0] cycles_after_last_edge ; // After the last edge, wait this many cycles before raising complete flag
   assign edges_to_count = default_edge_count;
   assign cycles_after_last_edge = default_cycles_count;
`endif

// rising edge detect
always @(posedge clk) begin
   rising_edge_signal_r <= rising_edge_signal;
end

// count the edges, note this is a posedge count
always @(posedge clk) begin

   if (restart) begin
         edge_count <= 0;
   end else begin
      if((!rising_edge_signal_r) & rising_edge_signal) begin
         edge_count <= edge_count + 'd1;
      end else begin
         edge_count <= edge_count;
      end
   end

end

// Once all the edges requested have been counted we count cycles.
// The though being the user counts so many events, then a buffer out the
// back to see any post edge events. This should be sufficient for most
// use cases as edges can be aggregated externally.
always @(posedge clk) begin

   if (restart) begin
         cycles_count <= 0;
   end else begin
      if((cycles_count == 0) & (!complete_flag) & (edge_count == edges_to_count)) begin
         cycles_count <= cycles_after_last_edge;
      end else begin
         if(cycles_count != 0) begin
            cycles_count <= cycles_count - 'd1;
         end
      end
   end

end

// Generate the complete strobe. Note this module is synthesiseable and can
// be used in hardware, either to drive LED, ILA or registers.
always @(posedge clk) begin

   if (restart) begin
         complete_flag <= 0;
   end else begin
      if(cycles_count == 1) begin
         complete_flag <= 1'd1;
`ifdef ENABLE_SIM_STOPPER_STOP_IN_MODULE
         $stop;
`endif
      end else begin
         complete_flag <= complete_flag;
      end
   end

end

endmodule
`endif
