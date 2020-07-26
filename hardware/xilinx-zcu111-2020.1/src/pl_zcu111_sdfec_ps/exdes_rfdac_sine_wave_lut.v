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
module exdes_rfdac_sine_wave_lut #(

   parameter bitwidth       = 16,
   parameter addresswidth   = 7

   ) (

   output wire [bitwidth-1:0]     sine_value,
   input  wire [addresswidth-1:0] address

);

// array
wire [15:0] sine_lut128_16bit[0:127];

// -----------------------------------------------------------------------------
// Sine wave LUT
// -----------------------------------------------------------------------------
// Freq=50.0MHz,  LUT Entries=128, Bitwidth=16, TwosComplement=1
assign sine_lut128_16bit[0   ] = 16'h647     ; // offset dec =   1607 signed = 1607.035095
assign sine_lut128_16bit[1   ] = 16'hc8a     ; // offset dec =   3210 signed = 3210.202626
assign sine_lut128_16bit[2   ] = 16'h12c5    ; // offset dec =   4805 signed = 4805.644335
assign sine_lut128_16bit[3   ] = 16'h18f5    ; // offset dec =   6389 signed = 6389.520559
assign sine_lut128_16bit[4   ] = 16'h1f16    ; // offset dec =   7958 signed = 7958.019469
assign sine_lut128_16bit[5   ] = 16'h2523    ; // offset dec =   9507 signed = 9507.366242
assign sine_lut128_16bit[6   ] = 16'h2b19    ; // offset dec =  11033 signed = 11033.832149
assign sine_lut128_16bit[7   ] = 16'h30f5    ; // offset dec =  12533 signed = 12533.743527
assign sine_lut128_16bit[8   ] = 16'h36b3    ; // offset dec =  14003 signed = 14003.490620
assign sine_lut128_16bit[9   ] = 16'h3c4f    ; // offset dec =  15439 signed = 15439.536267
assign sine_lut128_16bit[10  ] = 16'h41c6    ; // offset dec =  16838 signed = 16838.424415
assign sine_lut128_16bit[11  ] = 16'h4714    ; // offset dec =  18196 signed = 18196.788435
assign sine_lut128_16bit[12  ] = 16'h4c37    ; // offset dec =  19511 signed = 19511.359224
assign sine_lut128_16bit[13  ] = 16'h512a    ; // offset dec =  20778 signed = 20778.973078
assign sine_lut128_16bit[14  ] = 16'h55ec    ; // offset dec =  21996 signed = 21996.579297
assign sine_lut128_16bit[15  ] = 16'h5a79    ; // offset dec =  23161 signed = 23161.247534
assign sine_lut128_16bit[16  ] = 16'h5ece    ; // offset dec =  24270 signed = 24270.174846
assign sine_lut128_16bit[17  ] = 16'h62e8    ; // offset dec =  25320 signed = 25320.692437
assign sine_lut128_16bit[18  ] = 16'h66c6    ; // offset dec =  26310 signed = 26310.272082
assign sine_lut128_16bit[19  ] = 16'h6a64    ; // offset dec =  27236 signed = 27236.532213
assign sine_lut128_16bit[20  ] = 16'h6dc1    ; // offset dec =  28097 signed = 28097.243651
assign sine_lut128_16bit[21  ] = 16'h70da    ; // offset dec =  28890 signed = 28890.334967
assign sine_lut128_16bit[22  ] = 16'h73ad    ; // offset dec =  29613 signed = 29613.897472
assign sine_lut128_16bit[23  ] = 16'h763a    ; // offset dec =  30266 signed = 30266.189806
assign sine_lut128_16bit[24  ] = 16'h787d    ; // offset dec =  30845 signed = 30845.642133
assign sine_lut128_16bit[25  ] = 16'h7a76    ; // offset dec =  31350 signed = 31350.859915
assign sine_lut128_16bit[26  ] = 16'h7c24    ; // offset dec =  31780 signed = 31780.627274
assign sine_lut128_16bit[27  ] = 16'h7d85    ; // offset dec =  32133 signed = 32133.909910
assign sine_lut128_16bit[28  ] = 16'h7e99    ; // offset dec =  32409 signed = 32409.857597
assign sine_lut128_16bit[29  ] = 16'h7f5f    ; // offset dec =  32607 signed = 32607.806227
assign sine_lut128_16bit[30  ] = 16'h7fd7    ; // offset dec =  32727 signed = 32727.279408
assign sine_lut128_16bit[31  ] = 16'h7fff    ; // offset dec =  32767 signed = 32767.989610
assign sine_lut128_16bit[32  ] = 16'h7fd9    ; // offset dec =  32729 signed = 32729.838858
assign sine_lut128_16bit[33  ] = 16'h7f64    ; // offset dec =  32612 signed = 32612.918968
assign sine_lut128_16bit[34  ] = 16'h7ea1    ; // offset dec =  32417 signed = 32417.511323
assign sine_lut128_16bit[35  ] = 16'h7d90    ; // offset dec =  32144 signed = 32144.086201
assign sine_lut128_16bit[36  ] = 16'h7c31    ; // offset dec =  31793 signed = 31793.301641
assign sine_lut128_16bit[37  ] = 16'h7a86    ; // offset dec =  31366 signed = 31366.001855
assign sine_lut128_16bit[38  ] = 16'h788f    ; // offset dec =  30863 signed = 30863.215203
assign sine_lut128_16bit[39  ] = 16'h764e    ; // offset dec =  30286 signed = 30286.151715
assign sine_lut128_16bit[40  ] = 16'h73c4    ; // offset dec =  29636 signed = 29636.200179
assign sine_lut128_16bit[41  ] = 16'h70f2    ; // offset dec =  28914 signed = 28914.924797
assign sine_lut128_16bit[42  ] = 16'h6ddc    ; // offset dec =  28124 signed = 28124.061425
assign sine_lut128_16bit[43  ] = 16'h6a81    ; // offset dec =  27265 signed = 27265.513390
assign sine_lut128_16bit[44  ] = 16'h66e5    ; // offset dec =  26341 signed = 26341.346915
assign sine_lut128_16bit[45  ] = 16'h6309    ; // offset dec =  25353 signed = 25353.786139
assign sine_lut128_16bit[46  ] = 16'h5ef1    ; // offset dec =  24305 signed = 24305.207774
assign sine_lut128_16bit[47  ] = 16'h5a9e    ; // offset dec =  23198 signed = 23198.135375
assign sine_lut128_16bit[48  ] = 16'h5613    ; // offset dec =  22035 signed = 22035.233274
assign sine_lut128_16bit[49  ] = 16'h5153    ; // offset dec =  20819 signed = 20819.300165
assign sine_lut128_16bit[50  ] = 16'h4c61    ; // offset dec =  19553 signed = 19553.262369
assign sine_lut128_16bit[51  ] = 16'h4740    ; // offset dec =  18240 signed = 18240.166791
assign sine_lut128_16bit[52  ] = 16'h41f3    ; // offset dec =  16883 signed = 16883.173586
assign sine_lut128_16bit[53  ] = 16'h3c7d    ; // offset dec =  15485 signed = 15485.548558
assign sine_lut128_16bit[54  ] = 16'h36e2    ; // offset dec =  14050 signed = 14050.655295
assign sine_lut128_16bit[55  ] = 16'h3125    ; // offset dec =  12581 signed = 12581.947077
assign sine_lut128_16bit[56  ] = 16'h2b4a    ; // offset dec =  11082 signed = 11082.958566
assign sine_lut128_16bit[57  ] = 16'h2555    ; // offset dec =   9557 signed = 9557.297296
assign sine_lut128_16bit[58  ] = 16'h1f48    ; // offset dec =   8008 signed = 8008.634993
assign sine_lut128_16bit[59  ] = 16'h1928    ; // offset dec =   6440 signed = 6440.698741
assign sine_lut128_16bit[60  ] = 16'h12f9    ; // offset dec =   4857 signed = 4857.262006
assign sine_lut128_16bit[61  ] = 16'hcbe     ; // offset dec =   3262 signed = 3262.135560
assign sine_lut128_16bit[62  ] = 16'h67b     ; // offset dec =   1659 signed = 1659.158309
assign sine_lut128_16bit[63  ] = 16'h34      ; // offset dec =     52 signed = 52.188051
assign sine_lut128_16bit[64  ] = 16'hf9ed    ; // offset dec =  63981 signed = -1554.907806
assign sine_lut128_16bit[65  ] = 16'hf3a9    ; // offset dec =  62377 signed = -3158.261549
assign sine_lut128_16bit[66  ] = 16'hed6d    ; // offset dec =  60781 signed = -4754.014475
assign sine_lut128_16bit[67  ] = 16'he73d    ; // offset dec =  59197 signed = -6338.326170
assign sine_lut128_16bit[68  ] = 16'he11c    ; // offset dec =  57628 signed = -7907.383758
assign sine_lut128_16bit[69  ] = 16'hdb0e    ; // offset dec =  56078 signed = -9457.411071
assign sine_lut128_16bit[70  ] = 16'hd517    ; // offset dec =  54551 signed = -10984.677743
assign sine_lut128_16bit[71  ] = 16'hcf3a    ; // offset dec =  53050 signed = -12485.508184
assign sine_lut128_16bit[72  ] = 16'hc97b    ; // offset dec =  51579 signed = -13956.290424
assign sine_lut128_16bit[73  ] = 16'hc3de    ; // offset dec =  50142 signed = -15393.484813
assign sine_lut128_16bit[74  ] = 16'hbe66    ; // offset dec =  48742 signed = -16793.632532
assign sine_lut128_16bit[75  ] = 16'hb916    ; // offset dec =  47382 signed = -18153.363921
assign sine_lut128_16bit[76  ] = 16'hb3f2    ; // offset dec =  46066 signed = -19469.406588
assign sine_lut128_16bit[77  ] = 16'haefd    ; // offset dec =  44797 signed = -20738.593284
assign sine_lut128_16bit[78  ] = 16'haa3a    ; // offset dec =  43578 signed = -21957.869525
assign sine_lut128_16bit[79  ] = 16'ha5ab    ; // offset dec =  42411 signed = -23124.300945
assign sine_lut128_16bit[80  ] = 16'ha154    ; // offset dec =  41300 signed = -24235.080357
assign sine_lut128_16bit[81  ] = 16'h9d38    ; // offset dec =  40248 signed = -25287.534507
assign sine_lut128_16bit[82  ] = 16'h9958    ; // offset dec =  39256 signed = -26279.130511
assign sine_lut128_16bit[83  ] = 16'h95b8    ; // offset dec =  38328 signed = -27207.481949
assign sine_lut128_16bit[84  ] = 16'h9259    ; // offset dec =  37465 signed = -28070.354607
assign sine_lut128_16bit[85  ] = 16'h8f3e    ; // offset dec =  36670 signed = -28865.671855
assign sine_lut128_16bit[86  ] = 16'h8c68    ; // offset dec =  35944 signed = -29591.519648
assign sine_lut128_16bit[87  ] = 16'h89d9    ; // offset dec =  35289 signed = -30246.151125
assign sine_lut128_16bit[88  ] = 16'h8794    ; // offset dec =  34708 signed = -30827.990821
assign sine_lut128_16bit[89  ] = 16'h8598    ; // offset dec =  34200 signed = -31335.638453
assign sine_lut128_16bit[90  ] = 16'h83e8    ; // offset dec =  33768 signed = -31767.872294
assign sine_lut128_16bit[91  ] = 16'h8284    ; // offset dec =  33412 signed = -32123.652109
assign sine_lut128_16bit[92  ] = 16'h816d    ; // offset dec =  33133 signed = -32402.121662
assign sine_lut128_16bit[93  ] = 16'h80a5    ; // offset dec =  32933 signed = -32602.610776
assign sine_lut128_16bit[94  ] = 16'h802b    ; // offset dec =  32811 signed = -32724.636944
assign sine_lut128_16bit[95  ] = 16'h8000    ; // offset dec =  32768 signed = -32767.906493
assign sine_lut128_16bit[96  ] = 16'h8023    ; // offset dec =  32803 signed = -32732.315287
assign sine_lut128_16bit[97  ] = 16'h8096    ; // offset dec =  32918 signed = -32617.948984
assign sine_lut128_16bit[98  ] = 16'h8156    ; // offset dec =  33110 signed = -32425.082820
assign sine_lut128_16bit[99  ] = 16'h8265    ; // offset dec =  33381 signed = -32154.180958
assign sine_lut128_16bit[100 ] = 16'h83c2    ; // offset dec =  33730 signed = -31805.895362
assign sine_lut128_16bit[101 ] = 16'h856a    ; // offset dec =  34154 signed = -31381.064233
assign sine_lut128_16bit[102 ] = 16'h875f    ; // offset dec =  34655 signed = -30880.709988
assign sine_lut128_16bit[103 ] = 16'h899d    ; // offset dec =  35229 signed = -30306.036803
assign sine_lut128_16bit[104 ] = 16'h8c25    ; // offset dec =  35877 signed = -29658.427713
assign sine_lut128_16bit[105 ] = 16'h8ef4    ; // offset dec =  36596 signed = -28939.441284
assign sine_lut128_16bit[106 ] = 16'h9209    ; // offset dec =  37385 signed = -28150.807862
assign sine_lut128_16bit[107 ] = 16'h9561    ; // offset dec =  38241 signed = -27294.425408
assign sine_lut128_16bit[108 ] = 16'h98fb    ; // offset dec =  39163 signed = -26372.354932
assign sine_lut128_16bit[109 ] = 16'h9cd5    ; // offset dec =  40149 signed = -25386.815531
assign sine_lut128_16bit[110 ] = 16'ha0eb    ; // offset dec =  41195 signed = -24340.179050
assign sine_lut128_16bit[111 ] = 16'ha53d    ; // offset dec =  42301 signed = -23234.964372
assign sine_lut128_16bit[112 ] = 16'ha9c6    ; // offset dec =  43462 signed = -22073.831358
assign sine_lut128_16bit[113 ] = 16'hae84    ; // offset dec =  44676 signed = -20859.574444
assign sine_lut128_16bit[114 ] = 16'hb374    ; // offset dec =  45940 signed = -19595.115916
assign sine_lut128_16bit[115 ] = 16'hb894    ; // offset dec =  47252 signed = -18283.498880
assign sine_lut128_16bit[116 ] = 16'hbde0    ; // offset dec =  48608 signed = -16927.879933
assign sine_lut128_16bit[117 ] = 16'hc354    ; // offset dec =  50004 signed = -15531.521569
assign sine_lut128_16bit[118 ] = 16'hc8ee    ; // offset dec =  51438 signed = -14097.784330
assign sine_lut128_16bit[119 ] = 16'hcea9    ; // offset dec =  52905 signed = -12630.118714
assign sine_lut128_16bit[120 ] = 16'hd483    ; // offset dec =  54403 signed = -11132.056871
assign sine_lut128_16bit[121 ] = 16'hda78    ; // offset dec =  55928 signed = -9607.204108
assign sine_lut128_16bit[122 ] = 16'he084    ; // offset dec =  57476 signed = -8059.230204
assign sine_lut128_16bit[123 ] = 16'he6a4    ; // offset dec =  59044 signed = -6491.860585
assign sine_lut128_16bit[124 ] = 16'hecd3    ; // offset dec =  60627 signed = -4908.867356
assign sine_lut128_16bit[125 ] = 16'hf30d    ; // offset dec =  62221 signed = -3314.060220
assign sine_lut128_16bit[126 ] = 16'hf950    ; // offset dec =  63824 signed = -1711.277314
assign sine_lut128_16bit[127 ] = 16'hff97    ; // offset dec =  65431 signed = -104.375969


// -----------------------------------------------------------------------------
// Assign the output
// -----------------------------------------------------------------------------
assign sine_value = sine_lut128_16bit[address];

endmodule

