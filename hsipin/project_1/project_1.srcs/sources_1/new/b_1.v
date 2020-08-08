`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/10 11:08:45
// Design Name: 
// Module Name: b_1
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


module b_1(
    input w,
    input x,
    input y,
    input z,
    output out
    );
    
assign out = ~(x&~(y&~z|~y&z)|w&y&(~y|~x&z));

endmodule
