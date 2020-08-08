`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/10 11:13:34
// Design Name: 
// Module Name: test_b
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


module test_b;
wire OUT;
reg W,X,Y,Z;

b_1 U0(.out(OUT),.w(W),.x(X),.y(Y),.z(Z));
b_2 U1(.out(OUT),.w(W),.x(X),.y(Y),.z(Z));

initial
begin
    W=0; X=0; Y=0; Z=0;
    #10 W=0; X=0; Y=0; Z=1;
    #10 W=0; X=0; Y=1; Z=0;
    #10 W=0; X=0; Y=1; Z=1;
    #10 W=0; X=1; Y=0; Z=0;
    #10 W=0; X=1; Y=0; Z=1;
    #10 W=0; X=1; Y=1; Z=0;
    #10 W=0; X=1; Y=1; Z=1;
    #10 W=1; X=0; Y=0; Z=0;
    #10 W=1; X=0; Y=0; Z=1;
    #10 W=1; X=0; Y=1; Z=0;
    #10 W=1; X=0; Y=1; Z=1;
    #10 W=1; X=1; Y=0; Z=0;
    #10 W=1; X=1; Y=0; Z=1;
    #10 W=1; X=1; Y=1; Z=0;
    #10 W=1; X=1; Y=1; Z=1;
end

endmodule
