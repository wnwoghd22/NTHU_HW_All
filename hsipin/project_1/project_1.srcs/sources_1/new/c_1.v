`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/10 11:26:32
// Design Name: 
// Module Name: c_1
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


module c_1(
    input x,
    input y,
    input z,
    output out
    );
    
assign out = ~(x|y)|(~z)&(~(~x|z));

endmodule
