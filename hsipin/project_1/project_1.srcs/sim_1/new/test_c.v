`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/10 11:28:54
// Design Name: 
// Module Name: test_c
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


module test_c;

wire OUT;
reg X,Y,Z;

c_1 U0(.out(OUT),.x(X),.y(Y),.z(Z));
c_2 U1(.out(OUT),.x(X),.y(Y),.z(Z));

initial
begin
    X=0; Y=0; Z=0;
    #10 X=0; Y=0; Z=1;
    #10 X=0; Y=1; Z=0;
    #10 X=0; Y=1; Z=1;
    #10 X=1; Y=0; Z=0;
    #10 X=1; Y=0; Z=1;
    #10 X=1; Y=1; Z=0;
    #10 X=1; Y=1; Z=1;
end

endmodule
