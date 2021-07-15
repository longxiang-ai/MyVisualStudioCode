`timescale 1ns / 1ps

module RV32IPDP_C(
    input clk,
    input rst,
    input ALUSrc_A,
    input ALUSrc_B,
    input [1:0]ImmSel,
    input [2:0]ALUC,
    input Jump,
    input Branch,
    input [1:0]DatatoReg,
    input [31:0]Data_in,
    input wire rs1_used,
    input wire rs2_used,
    
    input [31:0]inst_field,
    input PCEN,
    input RegWrite,
    input wire WR,
    input wire MIO,
    
    output [31:0]ALU_out,
    output [31:0]Data_out,
    //////////////////////////////
    output wire MWR,
    output wire M_MIO,
    output [31:0]PCOUT,
    
    // input jalr,    
    input sign,
    // input blt,
    output zero,
    output overflow,
    //-----------debug signals------------
    output wire [31:0]ID_IR,
    output wire [31:0]EX_IR,
    output wire [31:0]MEM_IR,
    output wire [31:0]WB_IR,
    output wire [31:0]ID_PCurrent,
    output wire [31:0]EX_PCurrent,
    output wire [31:0]MEM_PCurrent,
    output wire [31:0]WB_PCurrent,
    output wire [31:0]MEM_Target,
    output [31:0]ALUA,
    output [31:0]ALUB,
    output BJ_stall,
    output Data_stall,
    output wire[1:0] PCSource,
    output [31:0]rs1_data,
    output [31:0]rs2_data,
    output [31:0]Imm32,
    output reg [31:0]Wt_data,
    input [6:0]Debug_addr,
    output [31:0]Debug_regs
);

// IF stage -------------------------------------
reg [31:0] PCNEXT;
    wire [31:0] PC_4 = PCOUT +4;        // 顺序执行PC地址
    wire [31:0] PC_JUMP = MEM_Target;   // jump指令目标地址
    wire [31:0] PC_Branch = MEM_Target; // Beq指令目标地址
    wire MEM_zero,MEM_Jump,MEM_Branch;
    wire Btake = MEM_zero && MEM_Branch;
    assign PCSource = {MEM_Jump,Btake}; // 下一指令地址选择
    wire PCWR = PCEN;

    always @(*) begin
        case (PCSource)
            2'b00: PCNEXT = PC_4;
            2'b01: PCNEXT = PC_Branch;
            2'b10: PCNEXT = PC_JUMP;
            2'b11: PCNEXT = PC_4;
        endcase
    end

    REG32  IMPC(.clk(clk),
                .rst(rst),
                .CE(PCWR),
                .D(PCNEXT),
                .Q(PCOUT));

// IF/ID Latch          ID级锁存变量： ID_IR, ID_PCurrent
    REG_IF_ID   IFID(
        .clk(clk),
        .rst(rst),
        .EN(1'b1),
        .Data_stall(),
        .flush(),
        .PCOUT(PCOUT),
        .IR(inst_field),
        .ID_IR(ID_IR),
        .ID_PCurrent(ID_PCurrent)
        );
// ID Stage-------------------------------------------------------
    wire [4:0] rs1_addr = ID_IR[19:15];
    wire [4:0] rs2_addr = ID_IR[24:20];
    wire [4:0] rd_addr = ID_IR[11:7];
    // reg[31:0]Wt_data;
    wire[4:0]WB_rd;
    wire WB_RegWrite;
        regs    DU2(
            .clk(clk),
            .rst(rst),
            .L_S(WB_RegWrite),
            .R_addr_A(rs1_addr),
            .R_addr_B(rs2_addr),
            .rdata_A(rs1_data),
            .rdata_B(rs2_data),
            .Wt_addr(WB_rd),
            .Wt_data(Wt_data),
            .Debug_addr(Debug_addr[4:0]),
            .Debug_regs(Debug_regs));
    // wire [31:0] Imm32;
        MUX4T1_32   MUX0(
            .s(ImmSel),
            .I0({{20{ID_IR[31]}},ID_IR[31:20]}),
            .I1({{20{ID_IR[31]}},ID_IR[31:25],ID_IR[11:7]}),
            .I2({{19{ID_IR[31]}},ID_IR[31],ID_IR[7],ID_IR[30:25],ID_IR[11:8],1'b0}),
            .I3({{11{ID_IR[31]}},ID_IR[31],ID_IR[19:12],ID_IR[20],ID_IR[30:21],1'b0}),
            .o(Imm32)
        );
    wire [31:0] EX_A,EX_B,EX_Imm32;
    wire[4:0]EX_rd;
    wire[2:0]EX_ALUC;
    wire[1:0]EX_DatatoReg;
    wire EX_ALUSrc_A,EX_ALUSrc_B,EX_Jump,EX_Branch,EX_RegWrite,EX_WR,EX_Sign;

    // ID/EX Latch    EX级锁存变量： EX_IR,EX_PCurrent,EX_A,EX_B,EX_Imm32,EX_rd,EX_ALUSrc_A,EX_ALUSrc_B,EX_ALUC,EX_DatatoReg,EX_RegWrite,EX_Jump,EX_Branch,EX_WR,EX_Sign
    wire EX_MIO;///////////////
//    wire Sign;//////////////////////////////////
    REG_ID_EX   IDEX(
        .clk(clk),
        .rst(rst),
        .EN(1'b1),
        .flush(1'b0),
        .ID_IR(ID_IR),
        .ID_PCurrent(ID_PCurrent),
        .rs1_data(rs1_data),
        .rs2_data(rs2_data),
        .Imm32(Imm32),
        .rd_addr(rd_addr),
        .ALUSrc_A(ALUSrc_A),
        .ALUSrc_B(ALUSrc_B),
        .ALUC(ALUC),
        .DatatoReg(DatatoReg),
        .RegWrite(RegWrite),
        .Jump(Jump),
        .Branch(Branch),
        .WR(WR),
        .MIO(MIO),
        .Sign(sign),

        .EX_PCurrent(EX_PCurrent),
        .EX_IR(EX_IR),
        .EX_A(EX_A),
        .EX_B(EX_B),
        .EX_Imm32(EX_Imm32),
        .EX_rd(EX_rd),
        .EX_ALUSrc_A(EX_ALUSrc_A),
        .EX_ALUSrc_B(EX_ALUSrc_B),
        .EX_ALUC(EX_ALUC),
        .EX_DatatoReg(EX_DatatoReg),
        .EX_RegWrite(EX_RegWrite),
        .EX_Jump(EX_Jump),
        .EX_Branch(EX_Branch),
        .EX_WR(EX_WR),
        .EX_MIO(EX_MIO),
        .EX_Sign(EX_Sign));
    
    // EXE stage -------------------------------------------------

    wire[31:0]EX_ALUO;
        assign ALUA = EX_A;
        assign ALUB = EX_ALUSrc_B ? EX_Imm32 : EX_B;
        wire [31:0] EX_Target = EX_PCurrent + EX_Imm32;

        alu     DU1(
            .A(ALUA),
            .B(ALUB),
            .ALUC(EX_ALUC),
            .res(EX_ALUO),
            .sign(EX_Sign),
//            .Co(),
//            .overflow(),
            .zero(zero)
            );
    wire [31:0] MEM_ALUO,MEM_Datao;
//    wire [31:0] MEM_PCurrent;
    wire [4:0] MEM_rd;
    wire [1:0] MEM_DatatoReg;
    wire MEM_RegWrite,MEM_WR;
    wire MEM_MIO;
    // EX/MEM Latch MEM级锁存变量： EX_IR,EX_PCurrent,EM_Target,MEM_Datao,MEM_ALUO,MEM_rd,MEM_DatatoReg,MEM_RegWrite,MEM_Jump,MEM_Branch,MEM_WR
    

        REG_EX_MEN  EXMEM(
            .clk(clk),
            .rst(rst),
            .EN(1'b1),
            .flush(),
            .EX_IR(EX_IR),
            .EX_PCurrent(EX_PCurrent),
            // .EX_A(EX_A),
            .EX_B(EX_B),
            .EX_ALUO(EX_ALUO),
            .EX_Target(EX_Target),
            .zero(zero),
            .EX_rd(EX_rd),
            .EX_DatatoReg(EX_DatatoReg),
            .EX_RegWrite(EX_RegWrite),
            .EX_Jump(EX_Jump),
            .EX_Branch(EX_Branch),
            .EX_MIO(EX_MIO),
            .EX_WR(EX_WR),
            
            .MEM_PCurrent(MEM_PCurrent),
            .MEM_IR(MEM_IR),
            .MEM_ALUO(MEM_ALUO),
            .MEM_Datao(MEM_Datao),
            .MEM_Target(MEM_Target),
            .MEM_rd(MEM_rd),
            .MEM_DatatoReg(MEM_DatatoReg),
            .MEM_RegWrite(MEM_RegWrite),
            .MEM_zero(MEM_zero),
            .MEM_Jump(MEM_Jump),
            .MEM_Branch(MEM_Branch),
            .MEM_MIO(MEM_MIO),
            .MEM_WR(MEM_WR)
        );
// MEM stage --------------------------------------------------
    wire [31:0]DATA_out = MEM_Datao ;
    wire [31:0]ALU_OUT = MEM_ALUO;
    assign MWR = MEM_WR;
    assign M_MIO = MEM_MIO;

//    assign Btake = MEM_zero && MEM_Branch;
    wire [31:0] WB_ALUO,WB_MDR;
//    wire [31:0] WB_PCurrent;
    wire [1:0] WB_DatatoReg;

    // MEM、WB Latch WM级锁存变量：
    // WB_IR,WB_PCurrent, MEM_ALUO, WB_MDR,WB_rd,WB_DatatoReg,WB_RegWrite

        REG_MEM_WB MEMWB(
            .clk(clk),
            .rst(rst),
            .EN(1'b1),
            .MEM_IR(MEM_IR),
            .MEM_PCurrent(MEM_PCurrent),
            .MEM_ALUO(MEM_ALUO),
            .Datai(Data_in),
            .MEM_rd(MEM_rd),
            .MEM_DatatoReg(MEM_DatatoReg),
            .MEM_RegWrite(MEM_RegWrite),

            .WB_PCurrent(WB_PCurrent),
            .WB_IR(WB_IR),
            .WB_ALUO(WB_ALUO),
            .WB_MDR(WB_MDR),
            .WB_rd(WB_rd),
            .WB_DatatoReg(WB_DatatoReg),
            .WB_RegWrite(WB_RegWrite)

        );

    // WB stage ----------------------------------------
    always @(*) begin
        case (WB_DatatoReg)
            2'b00 : Wt_data = WB_ALUO;
            2'b01 : Wt_data = WB_MDR;
            2'b10 : Wt_data = WB_PCurrent + 4;
            2'b11 : Wt_data = WB_PCurrent + 4;
        endcase
    end

endmodule