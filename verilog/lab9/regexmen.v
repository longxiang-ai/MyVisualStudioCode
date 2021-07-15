`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/01 18:28:44
// Design Name: 
// Module Name: REG_EX_MEN
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

module REG_EX_MEN(
    input clk,
    input rst,
    input EN,
    input flush,
    input [31:0] EX_IR,
    input [31:0] EX_PCurrent,
    input [31:0] EX_ALUO,
    input zero,
    input [31:0] EX_B,
    input [31:0] EX_Target,

    input [4:0]EX_rd,
    input [1:0]EX_DatatoReg,
    input EX_RegWrite,
    input EX_Jump,
    input EX_Branch,
    input EX_WR,
    input EX_MIO,
    
    output reg [31:0] MEM_PCurrent,
    output reg [31:0] MEM_IR,
    output reg [31:0] MEM_ALUO,
    output reg [31:0] MEM_Datao,
    output reg [31:0] MEM_Target,
    output reg [4:0]MEM_rd,
    output reg [1:0]MEM_DatatoReg,
    output reg  MEM_RegWrite,
    output reg  MEM_zero,
    output reg  MEM_Jump,
    output reg  MEM_Branch,
    output reg  MEM_MIO,
    output reg  MEM_WR
);
always @(posedge clk) begin
    if(rst) begin
        MEM_IR          <= 0 ;
        MEM_PCurrent    <= 0 ;
        MEM_Target      <= 0 ;
        MEM_rd          <= 0 ;
        MEM_RegWrite    <= 0 ;
        MEM_Jump        <= 0 ;
        MEM_Branch      <= 0 ;
        MEM_WR          <= 0 ;
        MEM_MIO         <= 0 ;
    end
    else if (EN) begin
        MEM_IR              <= EX_IR;
        MEM_PCurrent        <= EX_PCurrent;
        MEM_Target          <= EX_Target;
        MEM_ALUO            <= EX_ALUO;
        MEM_zero            <= zero;
        MEM_Datao           <= EX_B;
        MEM_DatatoReg       <= EX_DatatoReg;
        MEM_Jump            <= EX_Jump;
        MEM_Branch          <= EX_Branch;
        MEM_RegWrite        <= EX_RegWrite;
        MEM_WR              <= EX_WR;
        MEM_MIO             <= EX_MIO; 
        MEM_rd              <= EX_rd;
    end
end
endmodule
