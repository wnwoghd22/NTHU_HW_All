`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/30 12:06:21
// Design Name: 
// Module Name: HalfAdder
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

module HalfAdder(
    input a,
    input b,
    output c,
    output s
    );
    
    assign s = a^b;
    assign c = a&b;
    
endmodule
module FullAdder(
    input a,
    input b,
    input cin,
    output cout,
    output s
    );

    wire g,p;
    wire cp;
    
    HalfAdder HA1(.a(a),.b(b),.c(g),.s(p));
    HalfAdder HA2(.a(p),.b(cin),.c(cp),.s(s));
    assign cout = g|cp;

endmodule
module Adder(a,b,cin,cout,s);
    parameter n = 4;
    input [n-1:0]a,b;
    input cin;
    output [n-1:0]s;
    output cout;
    wire [n-1:0]c;
    integer i;
    
    assign cout = c[3];
    
    FullAdder FA0(.a(a[0]),.b(b[0]),.cin(cin),.cout(c[0]),.s(s[0]));
    FullAdder FA1(.a(a[1]),.b(b[1]),.cin(c[0]),.cout(c[1]),.s(s[1]));
    FullAdder FA2(.a(a[2]),.b(b[2]),.cin(c[1]),.cout(c[2]),.s(s[2]));
    FullAdder FA3(.a(a[3]),.b(b[3]),.cin(c[2]),.cout(c[3]),.s(s[3]));
    
endmodule
module BinaryDecimalConverter(cin,sb,cout,s);
    parameter n = 4;
    input [n-1:0]sb;
    input cin;
    output [n-1:0]s;
    output cout;
    
    assign s[0] = sb[0];
    assign s[1] = (~sb[3]&sb[1]&~cin) | (sb[3]&sb[2]&~sb[1]) | (~sb[1]&cin);
    assign s[2] = (~sb[3]&sb[2]) | (sb[2]&sb[1]) | (~sb[1]&cin);
    assign s[3] = (sb[3]&~sb[2]&~sb[1])|(sb[1]&cin);
    assign cout = (sb[3]&sb[2])|(sb[3]&sb[1])|cin;
    
endmodule
module DecimalAdder(a,b,cin,cout,s);
    parameter n = 4;
    input [n-1:0]a,b;
    input cin;
    output cout;
    output [n-1:0]s;
    wire cb;
    wire [n-1:0]sb;
    
    Adder Add(.a(a),.b(b),.cin(cin),.cout(cb),.s(sb));
    BinaryDecimalConverter BCD(.cin(cb),.sb(sb),.cout(cout),.s(s));   
endmodule
