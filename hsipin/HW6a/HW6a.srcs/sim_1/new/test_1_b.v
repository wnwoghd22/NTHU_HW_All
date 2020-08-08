`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/12/19 20:44:39
// Design Name: 
// Module Name: test_1_b
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


module test_1_b;
reg clk;
reg rst;
wire [3:0]out;

FourBitUpCounter BC(.clk(clk),.rst(rst),.out(out));

always
 #5 clk =~clk;

initial
begin
clk=0;rst=0;
#10 rst = 1;
end
    
endmodule
