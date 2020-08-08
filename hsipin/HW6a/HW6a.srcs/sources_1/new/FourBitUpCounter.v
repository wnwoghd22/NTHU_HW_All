`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/12/19 17:25:39
// Design Name: 
// Module Name: FourBitUpCounter
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


module ForBitUpCounter(rst, clk, out);
input rst, clk;
output [3:0]out;

wire [3:0]Q;

D_FF d0(~Q[0], rst, clk,Q[0]);
D_FF d1(Q[0]*~Q[1]|~Q[0]*Q[1], rst, clk, Q[1]);
D_FF d2(Q[2]*~Q[1]|Q[2]*~Q[0]|~Q[2]*Q[1]*Q[0], rst, clk, Q[2]);
D_FF d3(Q[3]*~Q[2]|Q[3]*~Q[1]|Q[3]*~Q[0]|~Q[3]*Q[2]*Q[1]*Q[0],rst,clk,Q[3]);

assign out = Q;

endmodule
