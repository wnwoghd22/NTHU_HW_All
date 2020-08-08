`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/12/19 21:51:06
// Design Name: 
// Module Name: ccc
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


module BinaryCounter_a(
    input rst,
    input clk,
    output [2:0]out
    );
wire [2:0]Q;

D_FF d0(1, rst, clk,Q[0]);
D_FF d1(Q[2]*~Q[1], rst, clk, Q[1]);
D_FF d2(~Q[1], rst, clk, Q[2]);

assign out = Q;

endmodule

module BinaryCounter_b(rst, clk, out);
input rst, clk;
output [2:0]out;

wire [2:0]Q;

D_FF d0(0, rst, clk,Q[0]);
D_FF d1(~Q[1], rst, clk, Q[1]);
D_FF d2(Q[2]*~Q[1]|~Q[2]*Q[1], rst, clk, Q[2]);

assign out = Q;

endmodule
