`timescale 1ps / 1ps
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

module demo_tb_clk_gen #(
  
  parameter clkdac_0_fab_delay   = 100  , // Clock startup delay
  parameter clkdac_0_ref_delay   = 100  , // Clock startup delay
  parameter clkadc_0_fab_delay   = 100  , // Clock startup delay
  parameter clkadc_0_ref_delay   = 100  , // Clock startup delay
  parameter axi_reset_cycles     = 100 , // 
  parameter axi_clk_delay        = 100  // Clock startup delay

) (

    input  wire [31:0] axi_clk_phase, // Clock phase

    input  wire [31:0] clkdac_0_fab_phase , // 
    input  wire [31:0] clkdac_0_ref_phase , // 
    input  wire        clkdac_0_enable    , // 
    input  wire [31:0] clkadc_0_fab_phase , // 
    input  wire [31:0] clkadc_0_ref_phase , // 
    input  wire        clkadc_0_enable    , // 

    output reg         clkdac_0_fab       , // 
    output reg         clkdac_0_ref       , // 
    output reg         clkadc_0_fab       , // 
    output reg         clkadc_0_ref       , // 
    output reg         axi_resetn=0       , // 
    output reg         axi_reset=1        , // 
    output reg         clk_axi              // 

);

integer reset_counter = axi_reset_cycles;

//////////////////////////////////////////////////////////////////////////////////
// AXI Clock generator. 
// Generate a POS and Negedge reset for use if required
//////////////////////////////////////////////////////////////////////////////////
initial
  begin
     clk_axi <= 1'b0;
     #(axi_clk_delay);
     forever
     begin
        clk_axi <= 1'b0;
        #(axi_clk_phase[31:16]);
        clk_axi <= 1'b1;
        #(axi_clk_phase[15:0]);
     end
  end

always @(posedge clk_axi) begin
   if (reset_counter != 0)
      reset_counter <= reset_counter - 1;
end

always @(posedge clk_axi) begin
   if (reset_counter == 0) begin
      axi_resetn <= 1;
      axi_reset  <= 0;
   end
end

//////////////////////////////////////////////////////////////////////////////////
// Slice dac_0
//////////////////////////////////////////////////////////////////////////////////
initial
  begin
     clkdac_0_fab <= 1'b0;
     #(clkdac_0_fab_delay);
     forever
     begin
     clkdac_0_fab <= 1'b0;
     #(clkdac_0_fab_phase[31:16]);
     clkdac_0_fab <= clkdac_0_enable;
     #(clkdac_0_fab_phase[15:0]);
     end
  end
initial
  begin
     clkdac_0_ref <= 1'b0;
     #(clkdac_0_ref_delay);
     forever
     begin
     clkdac_0_ref <= 1'b0;
     #(clkdac_0_ref_phase[31:16]);
     clkdac_0_ref <= clkdac_0_enable;
     #(clkdac_0_ref_phase[15:0]);
     end
  end

//////////////////////////////////////////////////////////////////////////////////
// Slice adc_0
//////////////////////////////////////////////////////////////////////////////////
initial
  begin
     clkadc_0_fab <= 1'b0;
     #(clkadc_0_fab_delay);
     forever
     begin
     clkadc_0_fab <= 1'b0;
     #(clkadc_0_fab_phase[31:16]);
     clkadc_0_fab <= clkadc_0_enable;
     #(clkadc_0_fab_phase[15:0]);
     end
  end
initial
  begin
     clkadc_0_ref <= 1'b0;
     #(clkadc_0_ref_delay);
     forever
     begin
     clkadc_0_ref <= 1'b0;
     #(clkadc_0_ref_phase[31:16]);
     clkadc_0_ref <= clkadc_0_enable;
     #(clkadc_0_ref_phase[15:0]);
     end
  end


endmodule
