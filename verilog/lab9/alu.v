`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/01 18:53:38
// Design Name: 
// Module Name: alu
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

module alu(
    input [31:0]A,
    input [31:0]B,
    input [2:0]ALUC,
    input sign,
    output reg [31:0]res,
    output zero,       
    output overflow
    );
    wire [31:0] slt;
    wire signa, signb;
    assign signa = A[31];
    assign signb = B[31];
    assign slt = (sign == 0 || signa & signb == 0) ? ((A < B) ? 32'h1 : 32'h0) : (signa == 1 && signb == 0) ? 32'h1 : (signa == 0 && signb == 1) ? 32'h0 : (A < B) ? 32'h0 : 32'h1;
    always @(*)
    begin
        case (ALUC)
            3'b000: res = A & B;
            3'b001: res = A | B;
            3'b010: res = A + B;
            3'b011: res = A ^ B;
            3'b100: res = ~(A | B);
            3'b101: res = A >> B;
            3'b110: res = A - B;
            3'b111: res = slt;
            default: res = 32'hxxxx_xxxx;
        endcase
    end
    
    assign zero = (res==0) ? 1:0;
endmodule

