
`timescale 1 ns / 1 ps

  module demod_4x_mul_mul_lbW_DSP48_3(clk, rst, ce, a, b, p);
input clk;
input rst;
input ce;
input [17 - 1 : 0] a; // synthesis attribute keep a "true"
input signed [18 - 1 : 0] b; // synthesis attribute keep b "true"
output signed [35 - 1 : 0] p; // synthesis attribute keep p "true"

reg signed [35 - 1 : 0] p_reg; 


always @ (posedge clk) begin
    if (ce) begin
        p_reg <= $signed ({1'b0, a}) * $signed (b);
    end
end

assign p = p_reg;

endmodule

`timescale 1 ns / 1 ps
module demod_4x_mul_mul_lbW(
    clk,
    reset,
    ce,
    din0,
    din1,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input clk;
input reset;
input ce;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
output[dout_WIDTH - 1:0] dout;



demod_4x_mul_mul_lbW_DSP48_3 demod_4x_mul_mul_lbW_DSP48_3_U(
    .clk( clk ),
    .rst( reset ),
    .ce( ce ),
    .a( din0 ),
    .b( din1 ),
    .p( dout ));

endmodule

