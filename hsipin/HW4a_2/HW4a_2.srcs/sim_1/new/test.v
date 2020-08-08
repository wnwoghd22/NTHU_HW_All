`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/30 16:54:26
// Design Name: 
// Module Name: test
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test;

wire [7:0] out;
reg [2:0] in;
reg en;

Decoder DC(in, en, out);

initial
begin
en = 0; in[2] = 0; in[1] = 0; in[0] = 0;
#5 en = 0; in[2] = 0; in[1] = 0; in[0] = 1;
#5 en = 0; in[2] = 0; in[1] = 1; in[0] = 0;
#5 en = 0; in[2] = 0; in[1] = 1; in[0] = 1;
#5 en = 0; in[2] = 1; in[1] = 0; in[0] = 0;
#5 en = 0; in[2] = 1; in[1] = 0; in[0] = 1;
#5 en = 0; in[2] = 1; in[1] = 1; in[0] = 0;
#5 en = 0; in[2] = 1; in[1] = 1; in[0] = 1;

#5 en = 1; in[2] = 0; in[1] = 0; in[0] = 0;
#5 en = 1; in[2] = 0; in[1] = 0; in[0] = 1;
#5 en = 1; in[2] = 0; in[1] = 1; in[0] = 0;
#5 en = 1; in[2] = 0; in[1] = 1; in[0] = 1;
#5 en = 1; in[2] = 1; in[1] = 0; in[0] = 0;
#5 en = 1; in[2] = 1; in[1] = 0; in[0] = 1;
#5 en = 1; in[2] = 1; in[1] = 1; in[0] = 0;
#5 en = 1; in[2] = 1; in[1] = 1; in[0] = 1;
end

endmodule
