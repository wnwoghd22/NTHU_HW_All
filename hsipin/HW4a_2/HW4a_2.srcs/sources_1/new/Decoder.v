`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/30 16:25:18
// Design Name: 
// Module Name: Decoder
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


module Decoder(in,en,out);
    input [2:0]in;
    input en;
    output [7:0]out;
    
    assign out[0] = en&~in[0]&~in[1]&~in[2];
    assign out[1] = en&in[0]&~in[1]&~in[2];
    assign out[2] = en&~in[0]&in[1]&~in[2];
    assign out[3] = en&in[0]&in[1]&~in[2];
    assign out[4] = en&~in[0]&~in[1]&in[2];
    assign out[5] = en&in[0]&~in[1]&in[2];
    assign out[6] = en&~in[0]&in[1]&in[2];
    assign out[7] = en&in[0]&in[1]&in[2];
    
endmodule
