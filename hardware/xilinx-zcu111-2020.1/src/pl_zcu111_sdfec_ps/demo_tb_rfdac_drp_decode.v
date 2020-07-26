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

module rfdac_drp_decode #(
   parameter integer C_S_DRP_ADDR_WIDTH = 12 // Address of the DRP address Bus.
) (
   input                           drp_clk ,
   input [C_S_DRP_ADDR_WIDTH-1:0]  drp_addr,
   input [15:0]                    drp_di  ,
   input                           drp_we  ,
   input                           drp_en  ,
   input [15:0]                    drp_do  ,
   input                           drp_rdy ,
   input                           enable  ,
   input [7:0]                     marker
);

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
reg [C_S_DRP_ADDR_WIDTH-1:0]  drp_addr_locked = 0;  // 
reg                   [15:0]  drp_di_locked = 0;    //
reg                   [15:0]  drp_do_locked = 0;    //
reg                           read_in_progress=0;   // 
reg                           write_in_progress=0;  // 
wire                 [8*37:0] addr_string;          // 
time                          w_curr=0;             // 
time                          w_last=0;             // 
time                          r_curr=0;             // 
time                          r_last=0;             // 
wire                          write_access;         // 
wire                          read_access;          // 

//-----------------------------------------------------------------------------
// Phase complete signals, for readability & debug
//-----------------------------------------------------------------------------
assign write_access = drp_we & drp_en;
assign read_access  = (~drp_we) & drp_en;

//-----------------------------------------------------------------------------
// Data locks, simple for now
//-----------------------------------------------------------------------------
always @(posedge drp_clk) begin
   if(write_access | read_access)
      drp_addr_locked <= drp_addr;

   if(write_access)
      drp_di_locked   <= drp_di;

   if(drp_rdy & read_access)
      drp_do_locked   <= drp_do;

   if (write_access)
      write_in_progress <= 1'd1;
   else 
      if(drp_rdy | write_access | read_access) // Timeout protection
         write_in_progress <= 1'd0;

   if (read_access)
      read_in_progress <= 1'd1;
   else 
      if(drp_rdy | write_access | read_access) // Timeout protection
         read_in_progress <= 1'd0;

end

//-----------------------------------------------------------------------------
// INFO:  at time   45.177us : DRP WRITE: Address=0725, Data=fe00 :: Slice=7, Register=HSCOM_HSCOM_PWR
//-----------------------------------------------------------------------------
always @(posedge drp_clk) begin
   if(drp_rdy & write_in_progress & enable) begin
      w_curr = $time;
      $write ("T=%12d D=%12d (ps): ", w_curr, w_curr - w_last);
      $write ("DRP %3d WRITE: AxiAddr=0x%08x, ", marker, drp_addr_locked);
      $display ("Data=0x%08x %-37s", drp_di_locked, addr_string);
      w_last = w_curr;
   end
end

always @(posedge drp_clk) begin
   if(drp_rdy & read_in_progress & enable) begin
      r_curr = $time;
      $write ("T=%-12d D=%12d (ps): ", r_curr, r_curr - r_last);
      $write ("DRP %3d READ : Address=0x%08x, ", marker, drp_addr_locked );
      $display ("Data=0x%08x %-37s", drp_do, addr_string);
      r_last = r_curr;
   end
end

//-----------------------------------------------------------------------------
// Instantiate address to string conversion
//-----------------------------------------------------------------------------
hsdac_axi_decode_address_to_string d2s ( .address_in(drp_addr_locked), .addr_string(addr_string));

endmodule

//-----------------------------------------------------------------------------
// Address to string conversion
//-----------------------------------------------------------------------------
module hsdac_axi_decode_address_to_string (

   input   wire  [11:0]   address_in  ,
   output  reg   [8*37:0] addr_string

);

always @ (*)
case (address_in)
     // Decode definitions for bank dac with prefix dac @ address 0x0
     'h002 : addr_string = "DAC0_FABRIC_RATE_ADDR                ";  // 2
     'h010 : addr_string = "DAC0_INTERP_CTRL_ADDR                ";  // 16
     'h011 : addr_string = "DAC0_INTERP_DATA_ADDR                ";  // 17
     'h020 : addr_string = "DAC0_MIXER_CONFIG0_ADDR              ";  // 32
     'h021 : addr_string = "DAC0_MIXER_CONFIG1_ADDR              ";  // 33
     'h022 : addr_string = "DAC0_MIXER_MODE_ADDR                 ";  // 34
     'h102 : addr_string = "DAC1_FABRIC_RATE_ADDR                ";  // 258
     'h110 : addr_string = "DAC1_INTERP_CTRL_ADDR                ";  // 272
     'h111 : addr_string = "DAC1_INTERP_DATA_ADDR                ";  // 273
     'h120 : addr_string = "DAC1_MIXER_CONFIG0_ADDR              ";  // 288
     'h121 : addr_string = "DAC1_MIXER_CONFIG1_ADDR              ";  // 289
     'h122 : addr_string = "DAC1_MIXER_MODE_ADDR                 ";  // 290
     'h202 : addr_string = "DAC2_FABRIC_RATE_ADDR                ";  // 514
     'h210 : addr_string = "DAC2_INTERP_CTRL_ADDR                ";  // 528
     'h211 : addr_string = "DAC2_INTERP_DATA_ADDR                ";  // 529
     'h220 : addr_string = "DAC2_MIXER_CONFIG0_ADDR              ";  // 544
     'h221 : addr_string = "DAC2_MIXER_CONFIG1_ADDR              ";  // 545
     'h222 : addr_string = "DAC2_MIXER_MODE_ADDR                 ";  // 546
     'h302 : addr_string = "DAC3_FABRIC_RATE_ADDR                ";  // 770
     'h310 : addr_string = "DAC3_INTERP_CTRL_ADDR                ";  // 784
     'h311 : addr_string = "DAC3_INTERP_DATA_ADDR                ";  // 785
     'h320 : addr_string = "DAC3_MIXER_CONFIG0_ADDR              ";  // 800
     'h321 : addr_string = "DAC3_MIXER_CONFIG1_ADDR              ";  // 801
     'h322 : addr_string = "DAC3_MIXER_MODE_ADDR                 ";  // 802
     default : addr_string = "                                     ";  // default

   endcase

endmodule
