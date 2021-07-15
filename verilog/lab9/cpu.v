`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/01 11:00:29
// Design Name: 
// Module Name: RV32PCPU
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

module RV32PCPU( 
    input clk, 
    input reset,                     //rst
    input Ready,                     //MIO_ready
    input [31:0]Datai, 
    output [31:0]Datao, 
    output [31:0]Addr, 
    output [31:0]PC, 
    input [31:0]INST,                //inst_field
    input [7:0]TNI, 
    output ALE, 
    output M_MIO, 
    output MWR,
    input [6:0]Debug_addr,
    output [31:0]Debug_data
);

    wire [31:0]A, B, RS1DATA, WDATA;                    //ALUA,ALUB,rs1_data,wt_data
    wire [31:0] RS2DATA;
    wire [31:0] Imm32;
    wire [4:0] Wt_addr;                                 //wt_addr
    wire WR,ALUSrc_B, ALUSrc_A;                            //ALUmux
    wire [2:0] ALUC;                                    //ALU_Control
    wire RegWrite;                                      //register write
    wire [1:0] DatatoReg;                               //MemtoReg

    wire Jump,Branch;
    wire PCEN, zero;
    wire rs1_used,rs2_used;
    // wire blt;
    // wire jalr;
    // wire sign;
    wire [1:0] ImmSel;
    
    wire ID_MIO;
    
    RV32IPCU_C  	U1_1(
        .clk(clk), 
        .reset(reset), 
        .OPcode(ID_IR[6:2]), 
        .Fun3(ID_IR[14:12]), 
        .Fun7(ID_IR[30]),
        .MIO_ready(Ready), 
        
        .zero(zero), 
        .ALE(ALE), 
        .ALUSrc_A(ALUSrc_A),
        .ALUSrc_B(ALUSrc_B),
        .ALUC(ALUC),                               //ALU_Control
        // .sign(sign),
        // .blt(blt),
        // .jalr(jalr),

        .Branch(Branch),
        .Jump(Jump),
        .ImmSel(ImmSel),
        .CPU_MIO(ID_MIO), 
        .DatatoReg(DatatoReg),                     //MemtoReg
        .PCEN(PCEN), 
        .RegWrite(RegWrite), 
        .WR(WR),
        .rs1_used(rs1_used),
        .rs2_used(rs2_used)
    );                                  //MemRW

    wire BJ_stall,Data_stall;
    wire [31:0] ID_IR, EX_IR , MEM_IR , WB_IR , ID_PCurrent, EX_PCurrent , MEM_PCurrent, WB_PCurrent, MEM_Target;
    wire [1:0] PCSource;

    wire[31:0]Debug_regs;					  
    RV32IPDP_C	 U1_2(
        .clk(clk),
        .rst(reset), 
        .ALUSrc_A(ALUSrc_A), 
        .ALUSrc_B(ALUSrc_B),
        .ImmSel(ImmSel),
        .ALUC(ALUC),                          //ALU_Control
        // .sign(sign),                          //Sign
        // .jalr(jalr),
        // .PCSource(PCSource),
        .Jump(Jump),
        .Branch(Branch),
        // .blt(blt),                            // blt
        .DatatoReg(DatatoReg),                //MemtoReg
        .Data_in(Datai), 
        .rs1_used(rs1_used),
        .rs2_used(rs2_used),

        .inst_field(INST), 
        .PCEN(PCEN), 
        .RegWrite(RegWrite),
        .WR(WR),
        .MIO(ID_MIO),

        .ALU_out(Addr),                       //res
        .Data_out(Datao), 
        /////////////////////////////////////////////
        .MWR(MWR),
        .M_MIO(M_MIO),
        
        .PCOUT(PC), 
        .overflow(), 
        .zero(zero),

        .ID_IR(ID_IR),
        .EX_IR(EX_IR),
        .MEM_IR(MEM_IR),
        .WB_IR(WB_IR),
        .ID_PCurrent(ID_PCurrent),
        .EX_PCurrent(EX_PCurrent),
        .MEM_PCurrent(MEM_PCurrent),
        .WB_PCurrent(WB_PCurrent),
        .MEM_Target(MEM_Target),
        
        .ALUA(A),
        .ALUB(B),
        .BJ_stall(BJ_stall),
        .Data_stall(Data_stall),
        .PCSource(PCSource),

        .rs1_data(RS1DATA),
        .rs2_data(RS2DATA),
        .Imm32(Imm32),
        .Wt_data(WDATA),
        // debug
        .Debug_addr(Debug_addr),
        .Debug_regs(Debug_regs)
    );


    //DEBUG TEST:
    wire [31:0] Test_signal;
    assign Debug_data = Debug_addr[5] ? Test_signal : Debug_regs;

    CPUTEST    U1_3(
        .PC_IF(PC),
        .PC_ID(ID_PCurrent),
        .PC_EXE(EX_PCurrent),
        .PC_MEM(MEM_PCurrent),
        .PC_WB(WB_PCurrent),
        .PC_next_IF(MEM_Target),
        .PCJump(MEM_Target),
        .inst_IF(INST),
        .inst_ID(ID_IR),
        .inst_EXE(EX_IR),
        .inst_MEM(MEM_IR),
        .inst_WB(WB_IR),
        .PCEN(PCEN),
        .Branch(Branch),
        // .Jump(Jump),        // ?
        .PCSource(PCSource),
        .RS1DATA(RS1DATA),
        .RS2DATA(RS2DATA),
        .Imm32(Imm32),
        .ImmSel(ImmSel),
        .ALUC(ALUC),
        .ALUSrc_A(ALUSrc_A),
        .ALUSrc_B(ALUSrc_B),
        .A(A),
        .B(B),
        
        .Datai(Datai),
        .Datao(Datao),
        .Addr(Addr),
        .WR(MWR),
        .MIO(M_MIO),
        .WDATA(WDATA),
        .DatatoReg(DatatoReg),
        .RegWrite(RegWrite), 
        .data_hazard(Data_stall),
        .control_hazard(BJ_stall),
    
        .Debug_addr(Debug_addr[4:0]),
        .Test_signal(Test_signal)    
    );
endmodule

