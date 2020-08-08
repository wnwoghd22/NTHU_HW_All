`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/12/19 22:00:10
// Design Name: 
// Module Name: test_2
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


module test_2;
reg clk;
reg rst;
wire [2:0]out_a;
wire [2:0]out_b;

BinaryCounter_a BCa(.clk(clk),.rst(rst),.out(out_a));
BinaryCounter_b BCb(.clk(clk),.rst(rst),.out(out_b));

always
 #5 clk =~clk;

initial
begin
clk=0;rst=0;
#10 rst = 1;
end
    
endmodule
