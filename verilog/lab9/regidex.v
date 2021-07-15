`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/01 17:16:40
// Design Name: 
// Module Name: REG_ID_EX
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


module REG_ID_EX(
    input clk,
    input rst,
    input EN,
    input flush,
    input [31:0]ID_IR,
    input [31:0]ID_PCurrent,
    input [31:0]rs1_data,
    input [31:0]rs2_data,
    input [31:0]Imm32,
    input [4:0]rd_addr,
    input [1:0]ALUSrc_A,
    input [1:0]ALUSrc_B,
    input [2:0]ALUC,
    input [1:0]DatatoReg,
    input RegWrite,
    input Jump,
    input Branch,
    input WR,
    input MIO,
    input sign,

    output reg [31:0]EX_PCurrent,
    output reg [31:0]EX_IR,
    output reg [31:0]EX_A,
    output reg [31:0]EX_B,
    output reg [4:0]EX_Imm32,
    // 6/9 修改 位数错误
    output reg [4:0]EX_rd,
    output reg EX_ALUSrc_A,
    output reg EX_ALUSrc_B,
    output reg [2:0]EX_ALUC,
    output reg [1:0]EX_DatatoReg,
    output reg EX_RegWrite,
    output reg EX_Jump,
    output reg EX_Branch,
    output reg EX_WR,
    output reg EX_MIO,
    output reg EX_sign
);

    always @(posedge clk) begin
        if(rst) begin
            EX_rd           <= 0;
            EX_RegWrite     <= 0;
            EX_Jump         <= 0; 
            EX_Branch       <= 0; 
            EX_WR           <= 0; 
            EX_MIO          <= 0; 
            EX_IR           <= 32'h0000_0000; 
            EX_PCurrent     <= 32'h0000_0000;
        end
        else if (EN) begin
            EX_PCurrent     <= ID_PCurrent;
            EX_IR           <= ID_IR;
            EX_A            <= rs1_data;
            EX_B            <= rs2_data;
            EX_Imm32        <= Imm32;
            EX_rd           <= rd_addr;
            EX_ALUSrc_A     <= ALUSrc_A;
            EX_ALUSrc_B     <= ALUSrc_B;
            EX_ALUC         <= ALUC;
            EX_DatatoReg    <= DatatoReg;
            EX_Jump         <= Jump;
            EX_Branch       <= Branch;
            EX_RegWrite     <= RegWrite;
            EX_WR           <= WR;
            EX_MIO          <= MIO;
            EX_sign         <= sign;
        end
    end
endmodule
