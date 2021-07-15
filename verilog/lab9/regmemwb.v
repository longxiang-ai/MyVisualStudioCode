`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/01 18:52:18
// Design Name: 
// Module Name: REG_MEM_WB
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



module REG_MEM_WB(
    input clk,
    input rst,
    input EN,
    input [31:0] MEM_IR,
    input [31:0] MEM_PCurrent,
    input [31:0] MEM_ALUO,
    input [31:0] Datai,
    input [4:0] MEM_rd,
    input [1:0] MEM_DatatoReg,
    input MEM_RegWrite,

    output reg [31:0] WB_PCurrent,
    output reg [31:0] WB_IR,
    output reg [31:0] WB_ALUO,
    output reg [31:0] WB_MDR,
    output reg [4:0]  WB_rd,
    output reg [1:0]  WB_DatatoReg,
    output reg        WB_RegWrite
);

    always @(posedge clk) begin
        if(rst) begin
            WB_rd           <= 0;
            WB_RegWrite     <= 0;
            WB_IR           <= 0;
            WB_PCurrent     <= 0;
        end
        else if (EN) begin
            WB_IR           <= MEM_IR;
            WB_PCurrent     <= MEM_PCurrent;
            WB_ALUO         <= MEM_ALUO;
            WB_MDR          <= Datai;
            WB_rd           <= MEM_rd;
            WB_RegWrite     <= MEM_RegWrite;
            WB_DatatoReg    <= MEM_DatatoReg;
        end
    end
endmodule