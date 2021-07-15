`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/01 11:17:40
// Design Name: 
// Module Name: RV32IPCU_C
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




module RV32IPCU_C(
    input clk,
    input reset,
    input [4:0]OPcode,
    input [2:0]Fun3,
    input Fun7,
    input MIO_ready,
    input zero,
    
    output reg ALUSrc_A,
    output reg ALUSrc_B,                // ALUB 选择
    output reg [1:0]ImmSel,             // 立即数生成选择 00:load,ALU(I) 01:store 10:beq 11:jal
    output reg [1:0]DatatoReg,          // 寄存器写选择   00:ALU 01:load 10:jal 11:lui
    output PCEN,
    output reg Jump,
    output reg Branch,
    // output reg blt,
    // output reg jalr,
    // output reg sign,                    // 有无符号位计算
    output reg RegWrite,                // 寄存器写使能
    output reg WR,
    output reg [2:0]ALUC,               // ALUControl
    // 缺省为ID级变量？
    output reg rs1_used,
    output reg rs2_used,

    output reg CPU_MIO,                 // 存储器操作信号
    output ALE                          // 访问存储器有效
    );
    
    reg [1:0]ALUop;
    // 00: load/store 
    // 01: branch
    // 10: R-type
    // 11: I-type
    wire [3:0]Fun;
    assign ALE = ~clk;
    assign PCEN = 1;

    // 选择信号模块
    always @* begin
        ALUSrc_A  = 0;
        ALUSrc_B  = 0;
        DatatoReg = 0;
        RegWrite  = 0;
        Branch    = 0;
        Jump      = 0;
        WR        = 0;
        CPU_MIO   = 0;
        ALUop     = 2'b00;
        rs1_used  = 0;
        rs2_used  = 0;

        case(OPcode)
            // add x5,x6,x7     ALU(R)
            5'b01100:begin 
                ALUop = 2'b10;RegWrite = 1;         ALUSrc_B = 0;Branch = 0;Jump = 0; DatatoReg = 2'b00;
                rs1_used = 1;rs2_used =1;
            end                           
            // lw x1,1000(x2) // load / I type
            5'b00000:begin 
                ALUop = 2'b00;RegWrite = 1; ImmSel = 2'b00;         ALUSrc_B = 1;Branch = 0;Jump = 0; DatatoReg = 2'b01;
                rs1_used = 1;
                WR = 0;CPU_MIO = 1;
            end      
            // sw x1,1000(x2) 需要写存储器，不需要读存储器 // store
            5'b01000:begin 
                ALUop = 2'b00;RegWrite = 0; ImmSel = 2'b01;         ALUSrc_B = 1;Branch = 0;Jump = 0; DatatoReg = 2'b01;
                rs1_used = 1;rs2_used = 1;
                WR = 1;CPU_MIO = 1;
            end     
            // beq x5,x6,Label // beq
            5'b11000:begin 
                ALUop = 2'b01;RegWrite = 0; ImmSel = 2'b10;         ALUSrc_B = 0;Branch = 1;Jump = 0;
                rs1_used = 1;rs2_used = 1;
            end                    
            // jal x1,Label // UJ-type
            5'b11011:begin
                RegWrite = 1;ImmSel = 2'b11;
            end                 
            
            default: 
                ALUop = 2'b00;
        endcase
    end
    

    // ALU 控制信号模块
    assign  Fun = {Fun3,Fun7};
    always @* begin
        case(ALUop)
            // load/store: add
            2'b00: ALUC = 3'b010;             
            // beq:sub
            2'b01: ALUC = 3'b110;             
            // ALU R type 
            2'b10:
                case(Fun)
                    4'b0000: ALUC = 3'b010; //add
                    4'b0001: ALUC = 3'b110; //sub
                    4'b1110: ALUC = 3'b000; //and
                    4'b1100: ALUC = 3'b001; //or
                    4'b0100: ALUC = 3'b111; //slt
                    4'b1010: ALUC = 3'b101; //srl
                    4'b1000: ALUC = 3'b011; //xor
                    default: ALUC = 3'bx;
                endcase
            // ALU I type
            2'b11:
                case(Fun3)
                    3'b000: ALUC = 3'b010;  //addi
                    3'b010: ALUC = 3'b111;  //slti
                    3'b100: ALUC = 3'b011;  //xori
                    3'b101: ALUC = 3'b101;  //srli
                    3'b110: ALUC = 3'b001;  //ori
                    3'b111: ALUC = 3'b000;  //andi    
                    default: ALUC = 3'bx;
                endcase
            default:    ALUC = 3'bx;
        endcase
    end
endmodule


