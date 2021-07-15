`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/20 18:01:15
// Design Name: 
// Module Name: RSCU9
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

module RSCUE(
    input clk,
    input reset,
    input [4:0]OPcode,
    input [2:0]Fun3,
    input Fun7,
    input MIO_ready,
    input zero,
    input blt,
    
    output reg ALUSrc_A,
    output reg ALUSrc_B,                // ALUB 选择
    output reg [1:0]ImmSel,             // 立即数生成选择 00:load,ALU(I) 01:store 10:beq 11:jal
    output reg [1:0]DatatoReg,          // 寄存器写选择   00:ALU 01:load 10:jal 11:???
    output PCEN,
    output [1:0]PCSource,               // Jump,Branch
    output reg blt,
    output reg Sign,                    // 有无符号位计算
    output reg RegWrite,                // 寄存器写使能
    output WR,
    output reg [2:0]ALUC,               // ALUControl
    output reg CPU_MIO,                 // 存储器操作信号
    output ALE
    );
    
    reg [1:0]ALUop;
    // 00: load/store 
    // 01: beq(sub)  
    // 10: R-type
    // 11: I-type
    wire [3:0]Fun;
    reg MemRead, MemWrite;
    reg Jump,Branch;
    assign PCSource = {Jump,Branch};
    assign WR = MemWrite && (~MemRead);
    assign ALE = ~clk;
    // reg [11:0]CPU_ctrl_signals;
    `define CPU_ctrl_signals {ImmSel, ALUSrc_B, DatatoReg, RegWrite, MemRead, MemWrite, Branch, Jump, ALUop,jalr}

    // 选择信号模块
    always @* begin
        case(OPcode)
            // add x5,x6,x7: 不需要使用memory,不需要使用立即数
            5'b01100:begin 
                `CPU_ctrl_signals = {12'b10_0_00_1_00_00_10,1'b0};// ALU(R)
            end                           
            // lw x1,1000(x2) 需要读存储器，不需要写存储器，但需要写寄存器
            5'b00000:begin 
                `CPU_ctrl_signals = {12'b00_1_01_1_10_00_00,1'b0};// load
            end      
            // sw x1,1000(x2) 需要写存储器，不需要读存储器
            5'b01000:begin 
                `CPU_ctrl_signals = {12'b01_1_00_0_01_00_00,1'b0};// store
            end     
            // beq x5,x6,Label 
            5'b11000:begin 
                `CPU_ctrl_signals = {12'b10_0_00_0_00_10_01,1'b0};// beq
            end                    
            // jal x1,Label
            5'b11011:begin 
                `CPU_ctrl_signals = {12'b11_1_10_1_00_01_00,1'b0};// UJ-type jal
            end                 
            // addi x5,x6,-1
            5'b00100:begin 
                `CPU_ctrl_signals = {12'b00_1_00_1_00_00_11,1'b0};// ALU(I)
            end                
            // lui x5,196 大立即数
            5'b01101:begin 
                `CPU_ctrl_signals = {12'b00_1_11_1_00_00_00,1'b0};// lui U-type
                       end
            // jalr x1,100(x5)
            5'b11001:begin
                `CPU_ctrl_signals = {12'b00_1_10_1_00_01_00,1'b1};// jalr
            end
            default: begin
                
            end       
        endcase
    end
    

    // ALU 控制信号模块
    assign  Fun = {Fun3,Fun7};
    always @* begin
        case(ALUop)
            // load/store: add 
            2'b00: ALUC = 3'b010;Sign = 1;             
            // branch指令
            2'b01: 
                Sign = 1;
                case(Fun3)
                    3'b000: ALUC = 3'b110; blt = 1;// beq:sub
                    3'b001: ALUC = 3'b110; blt = 0;// bne:sub
                    3'b100: ALUC = 3'b111; blt = 0;// blt:slt
                endcase
            // ALU R type 
            2'b10:
                Sign = 1;
                case(Fun)
                    4'b0000: ALUC = 3'b010; //add
                    4'b0001: ALUC = 3'b110; //sub
                    4'b1110: ALUC = 3'b000; //and
                    4'b1100: ALUC = 3'b001; //or
                    4'b0100: ALUC = 3'b111; //slt
                    4'b0110: ALUC = 3'b111; Sign = 0; // sltu
                    4'b1010: ALUC = 3'b101; //srl
                    4'b1000: ALUC = 3'b011; //xor
                    default: ALUC = 3'bx; Sign = x;
                endcase
            // ALU I type
            2'b11:
                Sign = 1;
                case(Fun3)
                    3'b000: ALUC = 3'b010;  //addi
                    3'b111: ALUC = 3'b000;  //andi
                    3'b110: ALUC = 3'b001;  //ori
                    3'b010: ALUC = 3'b111;  //slti
                    3'b011: ALUC = 3'b111;  Sign = 0; // sltiu
                    3'b101: ALUC = 3'b101;  //srli
                    3'b100: ALUC = 3'b011;  //xori
                    default: ALUC = 3'bx; Sign = x;
                endcase
            default:    ALUC = 3'bx; Sign = x;
        endcase
    end
endmodule
