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
`timescale 1 ps / 1 ps
//-----------------------------------------------------------------------------
// Generally instance in your top level testbench and connect as shown
//-----------------------------------------------------------------------------
// hsams_axi_decode hsams_axi_decode_i (
// .s_axi_aclk       (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_aclk     ),
// .s_axi_aresetn    (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_aresetn  ),
// .s_axi_awaddr     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_awaddr   ),
// .s_axi_awvalid    (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_awvalid  ),
// .s_axi_awready    (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_awready  ),
// .s_axi_wdata      (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_wdata    ),
// .s_axi_wvalid     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_wvalid   ),
// .s_axi_wready     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_wready   ),
// .s_axi_bresp      (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_bresp    ),
// .s_axi_bvalid     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_bvalid   ),
// .s_axi_bready     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_bready   ),
// .s_axi_araddr     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_araddr   ),
// .s_axi_arvalid    (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_arvalid  ),
// .s_axi_arready    (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_arready  ),
// .s_axi_rdata      (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_rdata    ),
// .s_axi_rresp      (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_rresp    ),
// .s_axi_rvalid     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_rvalid   ),
// .s_axi_rready     (  hirs_1.hier2.hier3.hierWhereBankIs.s_axi_rready   )
// );

//`define SHOWHEXNOTDEC_OFFSETS
//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
module demo_tb_axi_transaction_decode_hsams #(
 parameter integer  DATA_BYTE_WIDTH_POW            = 2,
 parameter integer  BANK_DECODE_HIGH_BIT           = 19,
 parameter integer  BANK_DECODE_HIGH_LOW           = 13
) (

   input  wire s_axi_aclk    ,
   input  wire s_axi_aresetn ,
   input  enable             ,

   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi AWADDR" *)  input  wire [31:0] s_axi_awaddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi AWVALID" *) input  wire        s_axi_awvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi AWREADY" *) input  wire        s_axi_awready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi WDATA" *)   input  wire [31:0] s_axi_wdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi WVALID" *)  input  wire        s_axi_wvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi WREADY" *)  input  wire        s_axi_wready   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi BRESP" *)   input  wire  [1:0] s_axi_bresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi BVALID" *)  input  wire        s_axi_bvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi BREADY" *)  input  wire        s_axi_bready   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi ARADDR" *)  input  wire [31:0] s_axi_araddr   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi ARVALID" *) input  wire        s_axi_arvalid  , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi ARREADY" *) input  wire        s_axi_arready  , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi RDATA" *)   input  wire [31:0] s_axi_rdata    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi RRESP" *)   input  wire  [1:0] s_axi_rresp    , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi RVALID" *)  input  wire        s_axi_rvalid   , // 
   (* X_INTERFACE_INFO = "xilinx.com:user:axi_monitor_if:1.0 decoder_axi RREADY" *)  input  wire        s_axi_rready     // 

);

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
reg   [31:0]   s_axi_awaddr_locked    = 0; // 
reg   [31:0]   s_axi_wdata_locked     = 0; // 
reg   [31:0]   s_axi_araddr_locked    = 0; // 
reg   [31:0]   s_axi_rdata_locked     = 0; // 

wire           w_addr_phase_done;          // 
wire           w_data_phase_done;          // 
wire           w_resp_phase_done;          // 
wire           r_addr_phase_done;          // 
wire           r_resp_phase_done;          // 

wire  [8*39:0] w_addr_string;              // 
wire  [8*39:0] r_addr_string;              // 

time           w_curr=0;                   // 
time           w_last=0;                   // 
time           r_curr=0;                   // 
time           r_last=0;                   // 

wire [BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW] s_axi_awaddr_decode_high; 
wire [BANK_DECODE_HIGH_BIT:BANK_DECODE_HIGH_LOW] s_axi_araddr_decode_high;
wire [BANK_DECODE_HIGH_LOW-1:0]                  s_axi_awaddr_decode_low; 
wire [BANK_DECODE_HIGH_LOW-1:0]                  s_axi_araddr_decode_low;

//-----------------------------------------------------------------------------
// Phase complete signals, for readability & debug
//-----------------------------------------------------------------------------
assign w_addr_phase_done = s_axi_awvalid & s_axi_awready;
assign w_data_phase_done = s_axi_wvalid  & s_axi_wready;
assign w_resp_phase_done = s_axi_bvalid  & s_axi_bready;
assign r_addr_phase_done = s_axi_arvalid & s_axi_arready;
assign r_resp_phase_done = s_axi_rvalid  & s_axi_rready;

//-----------------------------------------------------------------------------
// Decoded address's for display
//-----------------------------------------------------------------------------
assign s_axi_awaddr_decode_high = s_axi_awaddr_locked[BANK_DECODE_HIGH_BIT  :BANK_DECODE_HIGH_LOW];
assign s_axi_awaddr_decode_low  = s_axi_awaddr_locked[BANK_DECODE_HIGH_LOW-1:DATA_BYTE_WIDTH_POW];
assign s_axi_araddr_decode_high = s_axi_araddr_locked[BANK_DECODE_HIGH_BIT  :BANK_DECODE_HIGH_LOW];
assign s_axi_araddr_decode_low  = s_axi_araddr_locked[BANK_DECODE_HIGH_LOW-1:DATA_BYTE_WIDTH_POW];

//-----------------------------------------------------------------------------
// Data locks, simple for now
//-----------------------------------------------------------------------------
always @(posedge s_axi_aclk) begin
   if(w_addr_phase_done)
      s_axi_awaddr_locked <= s_axi_awaddr;

   if(w_data_phase_done)
      s_axi_wdata_locked  <= s_axi_wdata;

   if(r_addr_phase_done)
      s_axi_araddr_locked <= s_axi_araddr;

   if(r_resp_phase_done)
      s_axi_rdata_locked  <= s_axi_rdata;
end

//-----------------------------------------------------------------------------
// INFO:  at time   45.177us : DRP WRITE: Address=0725, Data=fe00 :: Slice=7, Register=HSCOM_HSCOM_PWR
//-----------------------------------------------------------------------------
always @(posedge s_axi_aclk) begin
   if(w_resp_phase_done & enable) begin
      w_curr = $time;
      $write ("T=%12d D=%12d (ps): ", w_curr, w_curr - w_last);
      $write ("AXI WRITE: AxiAddr=0x%08x, ", s_axi_awaddr_locked);
      $write ("Decode H=%2d L=%5d, ", s_axi_awaddr_decode_high,s_axi_awaddr_decode_low);
      $display ("Data=0x%08x %-39s", s_axi_wdata_locked, w_addr_string);
      w_last = w_curr;
   end
end

always @(posedge s_axi_aclk) begin
   if(r_resp_phase_done & enable) begin
      r_curr = $time;
      $write ("T=%-12d D=%12d (ps): ", r_curr, r_curr - r_last);
      $write ("AXI READ : Address=0x%08x, ", s_axi_araddr_locked );
`ifdef SHOWHEXNOTDEC_OFFSETS
      $write ("Decode H=0x%04x L=0x%04x, ", s_axi_araddr_decode_high,s_axi_araddr_decode_low);
`else
      $write ("Decode H=%2d L=%5d, ", s_axi_araddr_decode_high,s_axi_araddr_decode_low);
`endif
      $display ("Data=0x%08x %-39s", s_axi_rdata, r_addr_string);
      r_last = r_curr;
   end
end

//-----------------------------------------------------------------------------
// Instantiate address to string conversion
//-----------------------------------------------------------------------------
hsams_axi_decode_address_to_string a2s_r ( .address_in(s_axi_araddr_locked), .addr_string(r_addr_string));
hsams_axi_decode_address_to_string a2s_w ( .address_in(s_axi_awaddr_locked), .addr_string(w_addr_string));

endmodule

//-----------------------------------------------------------------------------
// Address to string conversion
//-----------------------------------------------------------------------------
module hsams_axi_decode_address_to_string (

   input   wire  [31:0]   address_in  ,
   output  reg   [8*39:0] addr_string

);

always @ (*)
case (address_in)
     // Decode definitions for bank hsams_config with prefix cfg_ @ address 0x0
     'h00000000 : addr_string = "CFG_MAJOR_REVISION_ADDR                ";  // 0
     'h00000000 : addr_string = "CFG_MINOR_REVISION_ADDR                ";  // 0
     'h00000000 : addr_string = "CFG_VERSION_REVISION_ADDR              ";  // 0
     'h00000004 : addr_string = "CFG_CTRL_RESET_ADDR                    ";  // 4
     'h00000004 : addr_string = "CFG_CTRL_RESET_STATE_ADDR              ";  // 4
     'h00000008 : addr_string = "CFG_RESTART_STATE_ADDR                 ";  // 8
     'h00000010 : addr_string = "CFG_TIMEOUT_ENABLE_ADDR                ";  // 16
     'h00000014 : addr_string = "CFG_TIMEOUT_STATUS_ADDR                ";  // 20
     'h00000018 : addr_string = "CFG_TIMEOUT_VALUE_ADDR                 ";  // 24
     // Decode definitions for bank t0_dcc with prefix dcc0 @ address 0x4000
     'h00004000 : addr_string = "DCC0_RESET_REGISTER_ADDR               ";  // 16384
     'h00004004 : addr_string = "DCC0_RESTART_REGISTER_ADDR             ";  // 16388
     'h00004008 : addr_string = "DCC0_RESTART_STATE_START_ADDR          ";  // 16392
     'h00004008 : addr_string = "DCC0_RESTART_STATE_END_ADDR            ";  // 16392
     'h0000400c : addr_string = "DCC0_CURRENT_STATE_ADDR                ";  // 16396
     'h00004010 : addr_string = "DCC0_TILE_INFO_ADDR                    ";  // 16400
     'h00004100 : addr_string = "DCC0_SUPPLY_DETECTION_TIMER_ADDR       ";  // 16640
     'h00004104 : addr_string = "DCC0_ADC_CALIBRATION_TIMER_ADDR        ";  // 16644
     'h00004200 : addr_string = "DCC0_INTERRUPT_STATUS_S0_ADDR          ";  // 16896
     'h00004200 : addr_string = "DCC0_INTERRUPT_STATUS_S1_ADDR          ";  // 16896
     'h00004200 : addr_string = "DCC0_INTERRUPT_STATUS_S2_ADDR          ";  // 16896
     'h00004200 : addr_string = "DCC0_INTERRUPT_STATUS_S3_ADDR          ";  // 16896
     'h00004200 : addr_string = "DCC0_INTERRUPT_STATUS_COM_ADDR         ";  // 16896
     'h00004204 : addr_string = "DCC0_INTERRUPT_ENABLE_S0_ADDR          ";  // 16900
     'h00004204 : addr_string = "DCC0_INTERRUPT_ENABLE_S1_ADDR          ";  // 16900
     'h00004204 : addr_string = "DCC0_INTERRUPT_ENABLE_S2_ADDR          ";  // 16900
     'h00004204 : addr_string = "DCC0_INTERRUPT_ENABLE_S3_ADDR          ";  // 16900
     'h00004204 : addr_string = "DCC0_INTERRUPT_ENABLE_COM_ADDR         ";  // 16900
     'h00004208 : addr_string = "DCC0_STATUS_S0_INTS_ADDR               ";  // 16904
     'h0000420c : addr_string = "DCC0_ENABLE_S0_INTS_ADDR               ";  // 16908
     'h00004210 : addr_string = "DCC0_STATUS_S1_INTS_ADDR               ";  // 16912
     'h00004214 : addr_string = "DCC0_ENABLE_S1_INTS_ADDR               ";  // 16916
     'h00004218 : addr_string = "DCC0_STATUS_S2_INTS_ADDR               ";  // 16920
     'h0000421c : addr_string = "DCC0_ENABLE_S2_INTS_ADDR               ";  // 16924
     'h00004220 : addr_string = "DCC0_STATUS_S3_INTS_ADDR               ";  // 16928
     'h00004224 : addr_string = "DCC0_ENABLE_S3_INTS_ADDR               ";  // 16932
     'h00004228 : addr_string = "DCC0_STATUS_COM_INTS_ADDR              ";  // 16936
     'h0000422c : addr_string = "DCC0_ENABLE_COM_INTS_ADDR              ";  // 16940
     // Decode definitions for bank t0_dac with prefix dac0 @ address 0x6000
     'h00006008 : addr_string = "DAC00_FABRIC_RATE_ADDR                 ";  // 24584
     'h00006040 : addr_string = "DAC00_INTERP_CTRL_ADDR                 ";  // 24640
     'h00006044 : addr_string = "DAC00_INTERP_DATA_ADDR                 ";  // 24644
     'h00006080 : addr_string = "DAC00_MIXER_CONFIG0_ADDR               ";  // 24704
     'h00006084 : addr_string = "DAC00_MIXER_CONFIG1_ADDR               ";  // 24708
     'h00006088 : addr_string = "DAC00_MIXER_MODE_ADDR                  ";  // 24712
     'h00006408 : addr_string = "DAC01_FABRIC_RATE_ADDR                 ";  // 25608
     'h00006440 : addr_string = "DAC01_INTERP_CTRL_ADDR                 ";  // 25664
     'h00006444 : addr_string = "DAC01_INTERP_DATA_ADDR                 ";  // 25668
     'h00006480 : addr_string = "DAC01_MIXER_CONFIG0_ADDR               ";  // 25728
     'h00006484 : addr_string = "DAC01_MIXER_CONFIG1_ADDR               ";  // 25732
     'h00006488 : addr_string = "DAC01_MIXER_MODE_ADDR                  ";  // 25736
     'h00006808 : addr_string = "DAC02_FABRIC_RATE_ADDR                 ";  // 26632
     'h00006840 : addr_string = "DAC02_INTERP_CTRL_ADDR                 ";  // 26688
     'h00006844 : addr_string = "DAC02_INTERP_DATA_ADDR                 ";  // 26692
     'h00006880 : addr_string = "DAC02_MIXER_CONFIG0_ADDR               ";  // 26752
     'h00006884 : addr_string = "DAC02_MIXER_CONFIG1_ADDR               ";  // 26756
     'h00006888 : addr_string = "DAC02_MIXER_MODE_ADDR                  ";  // 26760
     'h00006c08 : addr_string = "DAC03_FABRIC_RATE_ADDR                 ";  // 27656
     'h00006c40 : addr_string = "DAC03_INTERP_CTRL_ADDR                 ";  // 27712
     'h00006c44 : addr_string = "DAC03_INTERP_DATA_ADDR                 ";  // 27716
     'h00006c80 : addr_string = "DAC03_MIXER_CONFIG0_ADDR               ";  // 27776
     'h00006c84 : addr_string = "DAC03_MIXER_CONFIG1_ADDR               ";  // 27780
     'h00006c88 : addr_string = "DAC03_MIXER_MODE_ADDR                  ";  // 27784
     // Decode definitions for bank t1_dcc with prefix dcc1 @ address 0x8000
     'h00008000 : addr_string = "DCC1_RESET_REGISTER_ADDR               ";  // 32768
     'h00008004 : addr_string = "DCC1_RESTART_REGISTER_ADDR             ";  // 32772
     'h00008008 : addr_string = "DCC1_RESTART_STATE_START_ADDR          ";  // 32776
     'h00008008 : addr_string = "DCC1_RESTART_STATE_END_ADDR            ";  // 32776
     'h0000800c : addr_string = "DCC1_CURRENT_STATE_ADDR                ";  // 32780
     'h00008010 : addr_string = "DCC1_TILE_INFO_ADDR                    ";  // 32784
     'h00008100 : addr_string = "DCC1_SUPPLY_DETECTION_TIMER_ADDR       ";  // 33024
     'h00008104 : addr_string = "DCC1_ADC_CALIBRATION_TIMER_ADDR        ";  // 33028
     'h00008200 : addr_string = "DCC1_INTERRUPT_STATUS_S0_ADDR          ";  // 33280
     'h00008200 : addr_string = "DCC1_INTERRUPT_STATUS_S1_ADDR          ";  // 33280
     'h00008200 : addr_string = "DCC1_INTERRUPT_STATUS_S2_ADDR          ";  // 33280
     'h00008200 : addr_string = "DCC1_INTERRUPT_STATUS_S3_ADDR          ";  // 33280
     'h00008200 : addr_string = "DCC1_INTERRUPT_STATUS_COM_ADDR         ";  // 33280
     'h00008204 : addr_string = "DCC1_INTERRUPT_ENABLE_S0_ADDR          ";  // 33284
     'h00008204 : addr_string = "DCC1_INTERRUPT_ENABLE_S1_ADDR          ";  // 33284
     'h00008204 : addr_string = "DCC1_INTERRUPT_ENABLE_S2_ADDR          ";  // 33284
     'h00008204 : addr_string = "DCC1_INTERRUPT_ENABLE_S3_ADDR          ";  // 33284
     'h00008204 : addr_string = "DCC1_INTERRUPT_ENABLE_COM_ADDR         ";  // 33284
     'h00008208 : addr_string = "DCC1_STATUS_S0_INTS_ADDR               ";  // 33288
     'h0000820c : addr_string = "DCC1_ENABLE_S0_INTS_ADDR               ";  // 33292
     'h00008210 : addr_string = "DCC1_STATUS_S1_INTS_ADDR               ";  // 33296
     'h00008214 : addr_string = "DCC1_ENABLE_S1_INTS_ADDR               ";  // 33300
     'h00008218 : addr_string = "DCC1_STATUS_S2_INTS_ADDR               ";  // 33304
     'h0000821c : addr_string = "DCC1_ENABLE_S2_INTS_ADDR               ";  // 33308
     'h00008220 : addr_string = "DCC1_STATUS_S3_INTS_ADDR               ";  // 33312
     'h00008224 : addr_string = "DCC1_ENABLE_S3_INTS_ADDR               ";  // 33316
     'h00008228 : addr_string = "DCC1_STATUS_COM_INTS_ADDR              ";  // 33320
     'h0000822c : addr_string = "DCC1_ENABLE_COM_INTS_ADDR              ";  // 33324
     // Decode definitions for bank t1_dac with prefix dac1 @ address 0xa000
     'h0000a008 : addr_string = "DAC10_FABRIC_RATE_ADDR                 ";  // 40968
     'h0000a040 : addr_string = "DAC10_INTERP_CTRL_ADDR                 ";  // 41024
     'h0000a044 : addr_string = "DAC10_INTERP_DATA_ADDR                 ";  // 41028
     'h0000a080 : addr_string = "DAC10_MIXER_CONFIG0_ADDR               ";  // 41088
     'h0000a084 : addr_string = "DAC10_MIXER_CONFIG1_ADDR               ";  // 41092
     'h0000a088 : addr_string = "DAC10_MIXER_MODE_ADDR                  ";  // 41096
     'h0000a408 : addr_string = "DAC11_FABRIC_RATE_ADDR                 ";  // 41992
     'h0000a440 : addr_string = "DAC11_INTERP_CTRL_ADDR                 ";  // 42048
     'h0000a444 : addr_string = "DAC11_INTERP_DATA_ADDR                 ";  // 42052
     'h0000a480 : addr_string = "DAC11_MIXER_CONFIG0_ADDR               ";  // 42112
     'h0000a484 : addr_string = "DAC11_MIXER_CONFIG1_ADDR               ";  // 42116
     'h0000a488 : addr_string = "DAC11_MIXER_MODE_ADDR                  ";  // 42120
     'h0000a808 : addr_string = "DAC12_FABRIC_RATE_ADDR                 ";  // 43016
     'h0000a840 : addr_string = "DAC12_INTERP_CTRL_ADDR                 ";  // 43072
     'h0000a844 : addr_string = "DAC12_INTERP_DATA_ADDR                 ";  // 43076
     'h0000a880 : addr_string = "DAC12_MIXER_CONFIG0_ADDR               ";  // 43136
     'h0000a884 : addr_string = "DAC12_MIXER_CONFIG1_ADDR               ";  // 43140
     'h0000a888 : addr_string = "DAC12_MIXER_MODE_ADDR                  ";  // 43144
     'h0000ac08 : addr_string = "DAC13_FABRIC_RATE_ADDR                 ";  // 44040
     'h0000ac40 : addr_string = "DAC13_INTERP_CTRL_ADDR                 ";  // 44096
     'h0000ac44 : addr_string = "DAC13_INTERP_DATA_ADDR                 ";  // 44100
     'h0000ac80 : addr_string = "DAC13_MIXER_CONFIG0_ADDR               ";  // 44160
     'h0000ac84 : addr_string = "DAC13_MIXER_CONFIG1_ADDR               ";  // 44164
     'h0000ac88 : addr_string = "DAC13_MIXER_MODE_ADDR                  ";  // 44168
     // Decode definitions for bank t2_dcc with prefix dcc2 @ address 0xc000
     'h0000c000 : addr_string = "DCC2_RESET_REGISTER_ADDR               ";  // 49152
     'h0000c004 : addr_string = "DCC2_RESTART_REGISTER_ADDR             ";  // 49156
     'h0000c008 : addr_string = "DCC2_RESTART_STATE_START_ADDR          ";  // 49160
     'h0000c008 : addr_string = "DCC2_RESTART_STATE_END_ADDR            ";  // 49160
     'h0000c00c : addr_string = "DCC2_CURRENT_STATE_ADDR                ";  // 49164
     'h0000c010 : addr_string = "DCC2_TILE_INFO_ADDR                    ";  // 49168
     'h0000c100 : addr_string = "DCC2_SUPPLY_DETECTION_TIMER_ADDR       ";  // 49408
     'h0000c104 : addr_string = "DCC2_ADC_CALIBRATION_TIMER_ADDR        ";  // 49412
     'h0000c200 : addr_string = "DCC2_INTERRUPT_STATUS_S0_ADDR          ";  // 49664
     'h0000c200 : addr_string = "DCC2_INTERRUPT_STATUS_S1_ADDR          ";  // 49664
     'h0000c200 : addr_string = "DCC2_INTERRUPT_STATUS_S2_ADDR          ";  // 49664
     'h0000c200 : addr_string = "DCC2_INTERRUPT_STATUS_S3_ADDR          ";  // 49664
     'h0000c200 : addr_string = "DCC2_INTERRUPT_STATUS_COM_ADDR         ";  // 49664
     'h0000c204 : addr_string = "DCC2_INTERRUPT_ENABLE_S0_ADDR          ";  // 49668
     'h0000c204 : addr_string = "DCC2_INTERRUPT_ENABLE_S1_ADDR          ";  // 49668
     'h0000c204 : addr_string = "DCC2_INTERRUPT_ENABLE_S2_ADDR          ";  // 49668
     'h0000c204 : addr_string = "DCC2_INTERRUPT_ENABLE_S3_ADDR          ";  // 49668
     'h0000c204 : addr_string = "DCC2_INTERRUPT_ENABLE_COM_ADDR         ";  // 49668
     'h0000c208 : addr_string = "DCC2_STATUS_S0_INTS_ADDR               ";  // 49672
     'h0000c20c : addr_string = "DCC2_ENABLE_S0_INTS_ADDR               ";  // 49676
     'h0000c210 : addr_string = "DCC2_STATUS_S1_INTS_ADDR               ";  // 49680
     'h0000c214 : addr_string = "DCC2_ENABLE_S1_INTS_ADDR               ";  // 49684
     'h0000c218 : addr_string = "DCC2_STATUS_S2_INTS_ADDR               ";  // 49688
     'h0000c21c : addr_string = "DCC2_ENABLE_S2_INTS_ADDR               ";  // 49692
     'h0000c220 : addr_string = "DCC2_STATUS_S3_INTS_ADDR               ";  // 49696
     'h0000c224 : addr_string = "DCC2_ENABLE_S3_INTS_ADDR               ";  // 49700
     'h0000c228 : addr_string = "DCC2_STATUS_COM_INTS_ADDR              ";  // 49704
     'h0000c22c : addr_string = "DCC2_ENABLE_COM_INTS_ADDR              ";  // 49708
     // Decode definitions for bank t2_dac with prefix dac2 @ address 0xe000
     'h0000e008 : addr_string = "DAC20_FABRIC_RATE_ADDR                 ";  // 57352
     'h0000e040 : addr_string = "DAC20_INTERP_CTRL_ADDR                 ";  // 57408
     'h0000e044 : addr_string = "DAC20_INTERP_DATA_ADDR                 ";  // 57412
     'h0000e080 : addr_string = "DAC20_MIXER_CONFIG0_ADDR               ";  // 57472
     'h0000e084 : addr_string = "DAC20_MIXER_CONFIG1_ADDR               ";  // 57476
     'h0000e088 : addr_string = "DAC20_MIXER_MODE_ADDR                  ";  // 57480
     'h0000e408 : addr_string = "DAC21_FABRIC_RATE_ADDR                 ";  // 58376
     'h0000e440 : addr_string = "DAC21_INTERP_CTRL_ADDR                 ";  // 58432
     'h0000e444 : addr_string = "DAC21_INTERP_DATA_ADDR                 ";  // 58436
     'h0000e480 : addr_string = "DAC21_MIXER_CONFIG0_ADDR               ";  // 58496
     'h0000e484 : addr_string = "DAC21_MIXER_CONFIG1_ADDR               ";  // 58500
     'h0000e488 : addr_string = "DAC21_MIXER_MODE_ADDR                  ";  // 58504
     'h0000e808 : addr_string = "DAC22_FABRIC_RATE_ADDR                 ";  // 59400
     'h0000e840 : addr_string = "DAC22_INTERP_CTRL_ADDR                 ";  // 59456
     'h0000e844 : addr_string = "DAC22_INTERP_DATA_ADDR                 ";  // 59460
     'h0000e880 : addr_string = "DAC22_MIXER_CONFIG0_ADDR               ";  // 59520
     'h0000e884 : addr_string = "DAC22_MIXER_CONFIG1_ADDR               ";  // 59524
     'h0000e888 : addr_string = "DAC22_MIXER_MODE_ADDR                  ";  // 59528
     'h0000ec08 : addr_string = "DAC23_FABRIC_RATE_ADDR                 ";  // 60424
     'h0000ec40 : addr_string = "DAC23_INTERP_CTRL_ADDR                 ";  // 60480
     'h0000ec44 : addr_string = "DAC23_INTERP_DATA_ADDR                 ";  // 60484
     'h0000ec80 : addr_string = "DAC23_MIXER_CONFIG0_ADDR               ";  // 60544
     'h0000ec84 : addr_string = "DAC23_MIXER_CONFIG1_ADDR               ";  // 60548
     'h0000ec88 : addr_string = "DAC23_MIXER_MODE_ADDR                  ";  // 60552
     // Decode definitions for bank t3_dcc with prefix dcc3 @ address 0x10000
     'h00010000 : addr_string = "DCC3_RESET_REGISTER_ADDR               ";  // 65536
     'h00010004 : addr_string = "DCC3_RESTART_REGISTER_ADDR             ";  // 65540
     'h00010008 : addr_string = "DCC3_RESTART_STATE_START_ADDR          ";  // 65544
     'h00010008 : addr_string = "DCC3_RESTART_STATE_END_ADDR            ";  // 65544
     'h0001000c : addr_string = "DCC3_CURRENT_STATE_ADDR                ";  // 65548
     'h00010010 : addr_string = "DCC3_TILE_INFO_ADDR                    ";  // 65552
     'h00010100 : addr_string = "DCC3_SUPPLY_DETECTION_TIMER_ADDR       ";  // 65792
     'h00010104 : addr_string = "DCC3_ADC_CALIBRATION_TIMER_ADDR        ";  // 65796
     'h00010200 : addr_string = "DCC3_INTERRUPT_STATUS_S0_ADDR          ";  // 66048
     'h00010200 : addr_string = "DCC3_INTERRUPT_STATUS_S1_ADDR          ";  // 66048
     'h00010200 : addr_string = "DCC3_INTERRUPT_STATUS_S2_ADDR          ";  // 66048
     'h00010200 : addr_string = "DCC3_INTERRUPT_STATUS_S3_ADDR          ";  // 66048
     'h00010200 : addr_string = "DCC3_INTERRUPT_STATUS_COM_ADDR         ";  // 66048
     'h00010204 : addr_string = "DCC3_INTERRUPT_ENABLE_S0_ADDR          ";  // 66052
     'h00010204 : addr_string = "DCC3_INTERRUPT_ENABLE_S1_ADDR          ";  // 66052
     'h00010204 : addr_string = "DCC3_INTERRUPT_ENABLE_S2_ADDR          ";  // 66052
     'h00010204 : addr_string = "DCC3_INTERRUPT_ENABLE_S3_ADDR          ";  // 66052
     'h00010204 : addr_string = "DCC3_INTERRUPT_ENABLE_COM_ADDR         ";  // 66052
     'h00010208 : addr_string = "DCC3_STATUS_S0_INTS_ADDR               ";  // 66056
     'h0001020c : addr_string = "DCC3_ENABLE_S0_INTS_ADDR               ";  // 66060
     'h00010210 : addr_string = "DCC3_STATUS_S1_INTS_ADDR               ";  // 66064
     'h00010214 : addr_string = "DCC3_ENABLE_S1_INTS_ADDR               ";  // 66068
     'h00010218 : addr_string = "DCC3_STATUS_S2_INTS_ADDR               ";  // 66072
     'h0001021c : addr_string = "DCC3_ENABLE_S2_INTS_ADDR               ";  // 66076
     'h00010220 : addr_string = "DCC3_STATUS_S3_INTS_ADDR               ";  // 66080
     'h00010224 : addr_string = "DCC3_ENABLE_S3_INTS_ADDR               ";  // 66084
     'h00010228 : addr_string = "DCC3_STATUS_COM_INTS_ADDR              ";  // 66088
     'h0001022c : addr_string = "DCC3_ENABLE_COM_INTS_ADDR              ";  // 66092
     // Decode definitions for bank t3_dac with prefix dac3 @ address 0x12000
     'h00012008 : addr_string = "DAC30_FABRIC_RATE_ADDR                 ";  // 73736
     'h00012040 : addr_string = "DAC30_INTERP_CTRL_ADDR                 ";  // 73792
     'h00012044 : addr_string = "DAC30_INTERP_DATA_ADDR                 ";  // 73796
     'h00012080 : addr_string = "DAC30_MIXER_CONFIG0_ADDR               ";  // 73856
     'h00012084 : addr_string = "DAC30_MIXER_CONFIG1_ADDR               ";  // 73860
     'h00012088 : addr_string = "DAC30_MIXER_MODE_ADDR                  ";  // 73864
     'h00012408 : addr_string = "DAC31_FABRIC_RATE_ADDR                 ";  // 74760
     'h00012440 : addr_string = "DAC31_INTERP_CTRL_ADDR                 ";  // 74816
     'h00012444 : addr_string = "DAC31_INTERP_DATA_ADDR                 ";  // 74820
     'h00012480 : addr_string = "DAC31_MIXER_CONFIG0_ADDR               ";  // 74880
     'h00012484 : addr_string = "DAC31_MIXER_CONFIG1_ADDR               ";  // 74884
     'h00012488 : addr_string = "DAC31_MIXER_MODE_ADDR                  ";  // 74888
     'h00012808 : addr_string = "DAC32_FABRIC_RATE_ADDR                 ";  // 75784
     'h00012840 : addr_string = "DAC32_INTERP_CTRL_ADDR                 ";  // 75840
     'h00012844 : addr_string = "DAC32_INTERP_DATA_ADDR                 ";  // 75844
     'h00012880 : addr_string = "DAC32_MIXER_CONFIG0_ADDR               ";  // 75904
     'h00012884 : addr_string = "DAC32_MIXER_CONFIG1_ADDR               ";  // 75908
     'h00012888 : addr_string = "DAC32_MIXER_MODE_ADDR                  ";  // 75912
     'h00012c08 : addr_string = "DAC33_FABRIC_RATE_ADDR                 ";  // 76808
     'h00012c40 : addr_string = "DAC33_INTERP_CTRL_ADDR                 ";  // 76864
     'h00012c44 : addr_string = "DAC33_INTERP_DATA_ADDR                 ";  // 76868
     'h00012c80 : addr_string = "DAC33_MIXER_CONFIG0_ADDR               ";  // 76928
     'h00012c84 : addr_string = "DAC33_MIXER_CONFIG1_ADDR               ";  // 76932
     'h00012c88 : addr_string = "DAC33_MIXER_MODE_ADDR                  ";  // 76936
     // Decode definitions for bank t0_acc with prefix acc0 @ address 0x14000
     'h00014000 : addr_string = "ACC0_RESET_REGISTER_ADDR               ";  // 81920
     'h00014004 : addr_string = "ACC0_RESTART_REGISTER_ADDR             ";  // 81924
     'h00014008 : addr_string = "ACC0_RESTART_STATE_START_ADDR          ";  // 81928
     'h00014008 : addr_string = "ACC0_RESTART_STATE_END_ADDR            ";  // 81928
     'h0001400c : addr_string = "ACC0_CURRENT_STATE_ADDR                ";  // 81932
     'h00014010 : addr_string = "ACC0_TILE_INFO_ADDR                    ";  // 81936
     'h00014100 : addr_string = "ACC0_SUPPLY_DETECTION_TIMER_ADDR       ";  // 82176
     'h00014104 : addr_string = "ACC0_ADC_CALIBRATION_TIMER_ADDR        ";  // 82180
     'h00014200 : addr_string = "ACC0_INTERRUPT_STATUS_S0_ADDR          ";  // 82432
     'h00014200 : addr_string = "ACC0_INTERRUPT_STATUS_S1_ADDR          ";  // 82432
     'h00014200 : addr_string = "ACC0_INTERRUPT_STATUS_S2_ADDR          ";  // 82432
     'h00014200 : addr_string = "ACC0_INTERRUPT_STATUS_S3_ADDR          ";  // 82432
     'h00014200 : addr_string = "ACC0_INTERRUPT_STATUS_COM_ADDR         ";  // 82432
     'h00014204 : addr_string = "ACC0_INTERRUPT_ENABLE_S0_ADDR          ";  // 82436
     'h00014204 : addr_string = "ACC0_INTERRUPT_ENABLE_S1_ADDR          ";  // 82436
     'h00014204 : addr_string = "ACC0_INTERRUPT_ENABLE_S2_ADDR          ";  // 82436
     'h00014204 : addr_string = "ACC0_INTERRUPT_ENABLE_S3_ADDR          ";  // 82436
     'h00014204 : addr_string = "ACC0_INTERRUPT_ENABLE_COM_ADDR         ";  // 82436
     'h00014208 : addr_string = "ACC0_STATUS_S0_INTS_ADDR               ";  // 82440
     'h0001420c : addr_string = "ACC0_ENABLE_S0_INTS_ADDR               ";  // 82444
     'h00014210 : addr_string = "ACC0_STATUS_S1_INTS_ADDR               ";  // 82448
     'h00014214 : addr_string = "ACC0_ENABLE_S1_INTS_ADDR               ";  // 82452
     'h00014218 : addr_string = "ACC0_STATUS_S2_INTS_ADDR               ";  // 82456
     'h0001421c : addr_string = "ACC0_ENABLE_S2_INTS_ADDR               ";  // 82460
     'h00014220 : addr_string = "ACC0_STATUS_S3_INTS_ADDR               ";  // 82464
     'h00014224 : addr_string = "ACC0_ENABLE_S3_INTS_ADDR               ";  // 82468
     'h00014228 : addr_string = "ACC0_STATUS_COM_INTS_ADDR              ";  // 82472
     'h0001422c : addr_string = "ACC0_ENABLE_COM_INTS_ADDR              ";  // 82476
     // Decode definitions for bank t0_adc with prefix adc0 @ address 0x16000
     'h00016008 : addr_string = "ADC00_FABRIC_RATE_ADDR                 ";  // 90120
     'h00016080 : addr_string = "ADC00_MIXER_CONFIG0_ADDR               ";  // 90240
     'h00016084 : addr_string = "ADC00_MIXER_CONFIG1_ADDR               ";  // 90244
     'h00016088 : addr_string = "ADC00_MIXER_MODE_ADDR                  ";  // 90248
     'h00016408 : addr_string = "ADC01_FABRIC_RATE_ADDR                 ";  // 91144
     'h00016480 : addr_string = "ADC01_MIXER_CONFIG0_ADDR               ";  // 91264
     'h00016484 : addr_string = "ADC01_MIXER_CONFIG1_ADDR               ";  // 91268
     'h00016488 : addr_string = "ADC01_MIXER_MODE_ADDR                  ";  // 91272
     'h00016808 : addr_string = "ADC02_FABRIC_RATE_ADDR                 ";  // 92168
     'h00016880 : addr_string = "ADC02_MIXER_CONFIG0_ADDR               ";  // 92288
     'h00016884 : addr_string = "ADC02_MIXER_CONFIG1_ADDR               ";  // 92292
     'h00016888 : addr_string = "ADC02_MIXER_MODE_ADDR                  ";  // 92296
     'h00016c08 : addr_string = "ADC03_FABRIC_RATE_ADDR                 ";  // 93192
     'h00016c80 : addr_string = "ADC03_MIXER_CONFIG0_ADDR               ";  // 93312
     'h00016c84 : addr_string = "ADC03_MIXER_CONFIG1_ADDR               ";  // 93316
     'h00016c88 : addr_string = "ADC03_MIXER_MODE_ADDR                  ";  // 93320
     // Decode definitions for bank t1_acc with prefix acc1 @ address 0x18000
     'h00018000 : addr_string = "ACC1_RESET_REGISTER_ADDR               ";  // 98304
     'h00018004 : addr_string = "ACC1_RESTART_REGISTER_ADDR             ";  // 98308
     'h00018008 : addr_string = "ACC1_RESTART_STATE_START_ADDR          ";  // 98312
     'h00018008 : addr_string = "ACC1_RESTART_STATE_END_ADDR            ";  // 98312
     'h0001800c : addr_string = "ACC1_CURRENT_STATE_ADDR                ";  // 98316
     'h00018010 : addr_string = "ACC1_TILE_INFO_ADDR                    ";  // 98320
     'h00018100 : addr_string = "ACC1_SUPPLY_DETECTION_TIMER_ADDR       ";  // 98560
     'h00018104 : addr_string = "ACC1_ADC_CALIBRATION_TIMER_ADDR        ";  // 98564
     'h00018200 : addr_string = "ACC1_INTERRUPT_STATUS_S0_ADDR          ";  // 98816
     'h00018200 : addr_string = "ACC1_INTERRUPT_STATUS_S1_ADDR          ";  // 98816
     'h00018200 : addr_string = "ACC1_INTERRUPT_STATUS_S2_ADDR          ";  // 98816
     'h00018200 : addr_string = "ACC1_INTERRUPT_STATUS_S3_ADDR          ";  // 98816
     'h00018200 : addr_string = "ACC1_INTERRUPT_STATUS_COM_ADDR         ";  // 98816
     'h00018204 : addr_string = "ACC1_INTERRUPT_ENABLE_S0_ADDR          ";  // 98820
     'h00018204 : addr_string = "ACC1_INTERRUPT_ENABLE_S1_ADDR          ";  // 98820
     'h00018204 : addr_string = "ACC1_INTERRUPT_ENABLE_S2_ADDR          ";  // 98820
     'h00018204 : addr_string = "ACC1_INTERRUPT_ENABLE_S3_ADDR          ";  // 98820
     'h00018204 : addr_string = "ACC1_INTERRUPT_ENABLE_COM_ADDR         ";  // 98820
     'h00018208 : addr_string = "ACC1_STATUS_S0_INTS_ADDR               ";  // 98824
     'h0001820c : addr_string = "ACC1_ENABLE_S0_INTS_ADDR               ";  // 98828
     'h00018210 : addr_string = "ACC1_STATUS_S1_INTS_ADDR               ";  // 98832
     'h00018214 : addr_string = "ACC1_ENABLE_S1_INTS_ADDR               ";  // 98836
     'h00018218 : addr_string = "ACC1_STATUS_S2_INTS_ADDR               ";  // 98840
     'h0001821c : addr_string = "ACC1_ENABLE_S2_INTS_ADDR               ";  // 98844
     'h00018220 : addr_string = "ACC1_STATUS_S3_INTS_ADDR               ";  // 98848
     'h00018224 : addr_string = "ACC1_ENABLE_S3_INTS_ADDR               ";  // 98852
     'h00018228 : addr_string = "ACC1_STATUS_COM_INTS_ADDR              ";  // 98856
     'h0001822c : addr_string = "ACC1_ENABLE_COM_INTS_ADDR              ";  // 98860
     // Decode definitions for bank t1_adc with prefix adc1 @ address 0x1a000
     'h0001a008 : addr_string = "ADC10_FABRIC_RATE_ADDR                 ";  // 106504
     'h0001a080 : addr_string = "ADC10_MIXER_CONFIG0_ADDR               ";  // 106624
     'h0001a084 : addr_string = "ADC10_MIXER_CONFIG1_ADDR               ";  // 106628
     'h0001a088 : addr_string = "ADC10_MIXER_MODE_ADDR                  ";  // 106632
     'h0001a408 : addr_string = "ADC11_FABRIC_RATE_ADDR                 ";  // 107528
     'h0001a480 : addr_string = "ADC11_MIXER_CONFIG0_ADDR               ";  // 107648
     'h0001a484 : addr_string = "ADC11_MIXER_CONFIG1_ADDR               ";  // 107652
     'h0001a488 : addr_string = "ADC11_MIXER_MODE_ADDR                  ";  // 107656
     'h0001a808 : addr_string = "ADC12_FABRIC_RATE_ADDR                 ";  // 108552
     'h0001a880 : addr_string = "ADC12_MIXER_CONFIG0_ADDR               ";  // 108672
     'h0001a884 : addr_string = "ADC12_MIXER_CONFIG1_ADDR               ";  // 108676
     'h0001a888 : addr_string = "ADC12_MIXER_MODE_ADDR                  ";  // 108680
     'h0001ac08 : addr_string = "ADC13_FABRIC_RATE_ADDR                 ";  // 109576
     'h0001ac80 : addr_string = "ADC13_MIXER_CONFIG0_ADDR               ";  // 109696
     'h0001ac84 : addr_string = "ADC13_MIXER_CONFIG1_ADDR               ";  // 109700
     'h0001ac88 : addr_string = "ADC13_MIXER_MODE_ADDR                  ";  // 109704
     // Decode definitions for bank t2_acc with prefix acc2 @ address 0x1c000
     'h0001c000 : addr_string = "ACC2_RESET_REGISTER_ADDR               ";  // 114688
     'h0001c004 : addr_string = "ACC2_RESTART_REGISTER_ADDR             ";  // 114692
     'h0001c008 : addr_string = "ACC2_RESTART_STATE_START_ADDR          ";  // 114696
     'h0001c008 : addr_string = "ACC2_RESTART_STATE_END_ADDR            ";  // 114696
     'h0001c00c : addr_string = "ACC2_CURRENT_STATE_ADDR                ";  // 114700
     'h0001c010 : addr_string = "ACC2_TILE_INFO_ADDR                    ";  // 114704
     'h0001c100 : addr_string = "ACC2_SUPPLY_DETECTION_TIMER_ADDR       ";  // 114944
     'h0001c104 : addr_string = "ACC2_ADC_CALIBRATION_TIMER_ADDR        ";  // 114948
     'h0001c200 : addr_string = "ACC2_INTERRUPT_STATUS_S0_ADDR          ";  // 115200
     'h0001c200 : addr_string = "ACC2_INTERRUPT_STATUS_S1_ADDR          ";  // 115200
     'h0001c200 : addr_string = "ACC2_INTERRUPT_STATUS_S2_ADDR          ";  // 115200
     'h0001c200 : addr_string = "ACC2_INTERRUPT_STATUS_S3_ADDR          ";  // 115200
     'h0001c200 : addr_string = "ACC2_INTERRUPT_STATUS_COM_ADDR         ";  // 115200
     'h0001c204 : addr_string = "ACC2_INTERRUPT_ENABLE_S0_ADDR          ";  // 115204
     'h0001c204 : addr_string = "ACC2_INTERRUPT_ENABLE_S1_ADDR          ";  // 115204
     'h0001c204 : addr_string = "ACC2_INTERRUPT_ENABLE_S2_ADDR          ";  // 115204
     'h0001c204 : addr_string = "ACC2_INTERRUPT_ENABLE_S3_ADDR          ";  // 115204
     'h0001c204 : addr_string = "ACC2_INTERRUPT_ENABLE_COM_ADDR         ";  // 115204
     'h0001c208 : addr_string = "ACC2_STATUS_S0_INTS_ADDR               ";  // 115208
     'h0001c20c : addr_string = "ACC2_ENABLE_S0_INTS_ADDR               ";  // 115212
     'h0001c210 : addr_string = "ACC2_STATUS_S1_INTS_ADDR               ";  // 115216
     'h0001c214 : addr_string = "ACC2_ENABLE_S1_INTS_ADDR               ";  // 115220
     'h0001c218 : addr_string = "ACC2_STATUS_S2_INTS_ADDR               ";  // 115224
     'h0001c21c : addr_string = "ACC2_ENABLE_S2_INTS_ADDR               ";  // 115228
     'h0001c220 : addr_string = "ACC2_STATUS_S3_INTS_ADDR               ";  // 115232
     'h0001c224 : addr_string = "ACC2_ENABLE_S3_INTS_ADDR               ";  // 115236
     'h0001c228 : addr_string = "ACC2_STATUS_COM_INTS_ADDR              ";  // 115240
     'h0001c22c : addr_string = "ACC2_ENABLE_COM_INTS_ADDR              ";  // 115244
     // Decode definitions for bank t2_adc with prefix adc2 @ address 0x1e000
     'h0001e008 : addr_string = "ADC20_FABRIC_RATE_ADDR                 ";  // 122888
     'h0001e040 : addr_string = "ADC20_INTERP_CTRL_ADDR                 ";  // 122944
     'h0001e044 : addr_string = "ADC20_INTERP_DATA_ADDR                 ";  // 122948
     'h0001e080 : addr_string = "ADC20_MIXER_CONFIG0_ADDR               ";  // 123008
     'h0001e084 : addr_string = "ADC20_MIXER_CONFIG1_ADDR               ";  // 123012
     'h0001e088 : addr_string = "ADC20_MIXER_MODE_ADDR                  ";  // 123016
     'h0001e408 : addr_string = "ADC21_FABRIC_RATE_ADDR                 ";  // 123912
     'h0001e440 : addr_string = "ADC21_INTERP_CTRL_ADDR                 ";  // 123968
     'h0001e444 : addr_string = "ADC21_INTERP_DATA_ADDR                 ";  // 123972
     'h0001e480 : addr_string = "ADC21_MIXER_CONFIG0_ADDR               ";  // 124032
     'h0001e484 : addr_string = "ADC21_MIXER_CONFIG1_ADDR               ";  // 124036
     'h0001e488 : addr_string = "ADC21_MIXER_MODE_ADDR                  ";  // 124040
     'h0001e808 : addr_string = "ADC22_FABRIC_RATE_ADDR                 ";  // 124936
     'h0001e840 : addr_string = "ADC22_INTERP_CTRL_ADDR                 ";  // 124992
     'h0001e844 : addr_string = "ADC22_INTERP_DATA_ADDR                 ";  // 124996
     'h0001e880 : addr_string = "ADC22_MIXER_CONFIG0_ADDR               ";  // 125056
     'h0001e884 : addr_string = "ADC22_MIXER_CONFIG1_ADDR               ";  // 125060
     'h0001e888 : addr_string = "ADC22_MIXER_MODE_ADDR                  ";  // 125064
     'h0001ec08 : addr_string = "ADC23_FABRIC_RATE_ADDR                 ";  // 125960
     'h0001ec40 : addr_string = "ADC23_INTERP_CTRL_ADDR                 ";  // 126016
     'h0001ec44 : addr_string = "ADC23_INTERP_DATA_ADDR                 ";  // 126020
     'h0001ec80 : addr_string = "ADC23_MIXER_CONFIG0_ADDR               ";  // 126080
     'h0001ec84 : addr_string = "ADC23_MIXER_CONFIG1_ADDR               ";  // 126084
     'h0001ec88 : addr_string = "ADC23_MIXER_MODE_ADDR                  ";  // 126088
     // Decode definitions for bank t3_acc with prefix acc3 @ address 0x20000
     'h00020000 : addr_string = "ACC3_RESET_REGISTER_ADDR               ";  // 131072
     'h00020004 : addr_string = "ACC3_RESTART_REGISTER_ADDR             ";  // 131076
     'h00020008 : addr_string = "ACC3_RESTART_STATE_START_ADDR          ";  // 131080
     'h00020008 : addr_string = "ACC3_RESTART_STATE_END_ADDR            ";  // 131080
     'h0002000c : addr_string = "ACC3_CURRENT_STATE_ADDR                ";  // 131084
     'h00020010 : addr_string = "ACC3_TILE_INFO_ADDR                    ";  // 131088
     'h00020100 : addr_string = "ACC3_SUPPLY_DETECTION_TIMER_ADDR       ";  // 131328
     'h00020104 : addr_string = "ACC3_ADC_CALIBRATION_TIMER_ADDR        ";  // 131332
     'h00020200 : addr_string = "ACC3_INTERRUPT_STATUS_S0_ADDR          ";  // 131584
     'h00020200 : addr_string = "ACC3_INTERRUPT_STATUS_S1_ADDR          ";  // 131584
     'h00020200 : addr_string = "ACC3_INTERRUPT_STATUS_S2_ADDR          ";  // 131584
     'h00020200 : addr_string = "ACC3_INTERRUPT_STATUS_S3_ADDR          ";  // 131584
     'h00020200 : addr_string = "ACC3_INTERRUPT_STATUS_COM_ADDR         ";  // 131584
     'h00020204 : addr_string = "ACC3_INTERRUPT_ENABLE_S0_ADDR          ";  // 131588
     'h00020204 : addr_string = "ACC3_INTERRUPT_ENABLE_S1_ADDR          ";  // 131588
     'h00020204 : addr_string = "ACC3_INTERRUPT_ENABLE_S2_ADDR          ";  // 131588
     'h00020204 : addr_string = "ACC3_INTERRUPT_ENABLE_S3_ADDR          ";  // 131588
     'h00020204 : addr_string = "ACC3_INTERRUPT_ENABLE_COM_ADDR         ";  // 131588
     'h00020208 : addr_string = "ACC3_STATUS_S0_INTS_ADDR               ";  // 131592
     'h0002020c : addr_string = "ACC3_ENABLE_S0_INTS_ADDR               ";  // 131596
     'h00020210 : addr_string = "ACC3_STATUS_S1_INTS_ADDR               ";  // 131600
     'h00020214 : addr_string = "ACC3_ENABLE_S1_INTS_ADDR               ";  // 131604
     'h00020218 : addr_string = "ACC3_STATUS_S2_INTS_ADDR               ";  // 131608
     'h0002021c : addr_string = "ACC3_ENABLE_S2_INTS_ADDR               ";  // 131612
     'h00020220 : addr_string = "ACC3_STATUS_S3_INTS_ADDR               ";  // 131616
     'h00020224 : addr_string = "ACC3_ENABLE_S3_INTS_ADDR               ";  // 131620
     'h00020228 : addr_string = "ACC3_STATUS_COM_INTS_ADDR              ";  // 131624
     'h0002022c : addr_string = "ACC3_ENABLE_COM_INTS_ADDR              ";  // 131628
     // Decode definitions for bank t3_adc with prefix adc3 @ address 0x22000
     'h00022008 : addr_string = "ADC30_FABRIC_RATE_ADDR                 ";  // 139272
     'h00022040 : addr_string = "ADC30_INTERP_CTRL_ADDR                 ";  // 139328
     'h00022044 : addr_string = "ADC30_INTERP_DATA_ADDR                 ";  // 139332
     'h00022080 : addr_string = "ADC30_MIXER_CONFIG0_ADDR               ";  // 139392
     'h00022084 : addr_string = "ADC30_MIXER_CONFIG1_ADDR               ";  // 139396
     'h00022088 : addr_string = "ADC30_MIXER_MODE_ADDR                  ";  // 139400
     'h00022408 : addr_string = "ADC31_FABRIC_RATE_ADDR                 ";  // 140296
     'h00022440 : addr_string = "ADC31_INTERP_CTRL_ADDR                 ";  // 140352
     'h00022444 : addr_string = "ADC31_INTERP_DATA_ADDR                 ";  // 140356
     'h00022480 : addr_string = "ADC31_MIXER_CONFIG0_ADDR               ";  // 140416
     'h00022484 : addr_string = "ADC31_MIXER_CONFIG1_ADDR               ";  // 140420
     'h00022488 : addr_string = "ADC31_MIXER_MODE_ADDR                  ";  // 140424
     'h00022808 : addr_string = "ADC32_FABRIC_RATE_ADDR                 ";  // 141320
     'h00022840 : addr_string = "ADC32_INTERP_CTRL_ADDR                 ";  // 141376
     'h00022844 : addr_string = "ADC32_INTERP_DATA_ADDR                 ";  // 141380
     'h00022880 : addr_string = "ADC32_MIXER_CONFIG0_ADDR               ";  // 141440
     'h00022884 : addr_string = "ADC32_MIXER_CONFIG1_ADDR               ";  // 141444
     'h00022888 : addr_string = "ADC32_MIXER_MODE_ADDR                  ";  // 141448
     'h00022c08 : addr_string = "ADC33_FABRIC_RATE_ADDR                 ";  // 142344
     'h00022c40 : addr_string = "ADC33_INTERP_CTRL_ADDR                 ";  // 142400
     'h00022c44 : addr_string = "ADC33_INTERP_DATA_ADDR                 ";  // 142404
     'h00022c80 : addr_string = "ADC33_MIXER_CONFIG0_ADDR               ";  // 142464
     'h00022c84 : addr_string = "ADC33_MIXER_CONFIG1_ADDR               ";  // 142468
     'h00022c88 : addr_string = "ADC33_MIXER_MODE_ADDR                  ";  // 142472
     default    : addr_string = "                                       ";  // default = no print
   endcase

endmodule
