`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/25 19:06:14
// Design Name: 
// Module Name: ALU
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


module ALU(
    input [31:0]A,
    input [31:0]B,
    input [2:0]ALU_operation,
    
    input sign,         // �������޷��������㣬sign = 0,�����޷�����, sign = 1 �����з�����
    output reg [31:0]res,
    output zero,        // res Ϊȫ0ʱ zero = 1
    output overflow     // �ж��������overflow
    );
    
    wire [31:0] slt;
    wire signa, signb;
    assign signa = A[31];
    assign signb = B[31];
    assign slt = (sign == 0 || signa & signb == 0) ? ((A < B) ? 32'h1 : 32'h0) : (signa == 1 && signb == 0) ? 32'h1 : (signa == 0 && signb == 1) ? 32'h0 : (A < B) ? 32'h0 : 32'h1;

    always @(*)
    begin
        case (ALU_operation)
            3'b000: res = A & B;
            3'b001: res = A | B;
            3'b010: res = A + B;
            3'b011: res = A ^ B;
            3'b100: res = ~(A | B);
            3'b101: res = A >> B;
            3'b110: res = A - B;
            3'b111: res = slt;          // �з��������޷������Ľ����ͬ
            default: res = 32'hxxxx_xxxx;
        endcase
    end
    
    assign zero = (res==0) ? 1:0;
endmodule