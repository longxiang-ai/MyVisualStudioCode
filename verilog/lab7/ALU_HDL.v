`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/21 11:40:58
// Design Name: 
// Module Name: ALU_HDL
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


module ALU_HDL(
input [31:0]A,
input [31:0]B,
input [2:0]ALU_operation,
output reg [31:0]res,
output zero,
output overflow             // 仅保留接口
);    
always @(*)
begin
    case (ALU_operation)
        3'b000: res = A & B;                                    // and
        3'b001: res = A | B;                                    // or
        3'b010: res = A + B;                                    // add
        3'b011: res = A ^ B;                                    // xor
        3'b100: res = ~(A | B);                                 // nor
        3'b101: res = B >> 1;                                   // srl
        3'b110: res = A - B;                                    // sub
        3'b111: res = (A < B) ? 32'b0000_0001 : 32'b0000_0000;  // slt
        default: res = 32'hxxxx_xxxx;
    endcase
end
assign zero = (res==0) ? 1:0;
endmodule