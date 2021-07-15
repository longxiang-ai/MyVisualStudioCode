
module RV32PCPU(
    input clk,
    input reset,                     //rst
    input Ready,                     //MIO_ready
    input [31:0]Datai, 
    output [31:0]Datao, 
    output [31:0]Addr, 
    output [31:0]PC, 
    input [31:0]INST,                //inst_in
    input [7:0]TNI, 
    output ALE, 
    output M_MIO, 
    output MWR,
    input [6:0] Debug_addr,
    output [31:0] Debug_data
    );
    // 单周期部分中间变量
    wire [31:0] A, B, RS1DATA, RS2DATA, Imm32, WDATA; 
    wire [4:0] Wt_addr;  
    wire ALUSrc_B, ALUSrc_A;
    wire [2:0] ALUC;                                    
    wire RegWrite;
    wire [1:0] DatatoReg;                               
    wire Jump, Branch;
    wire PCEN, zero, WR, rs1_used, rs2_used;
    wire [1:0] ImmSel;
    // 多周期新增
    wire BJ_stall, Data_stall;
    wire [31:0] Debug_regs, ID_IR, EX_IR, MEM_IR, WB_IR, ID_PCurrent, EX_PCurrent, MEM_PCurrent, WB_PCurrent, MEM_Target;
    wire [1:0] PCSource;
    wire MIO;

    RV32IPCU_C  	U1_1(
        .clk(clk), 
        .OPcode(ID_IR[6:2]), 
        .Fun3(ID_IR[14:12]), 
        .Fun7(ID_IR[30]),
        .MIO_ready(Ready), 
        .reset(reset), 
        .zero(zero),
        .ALE(ALE), 
        .ALUSrc_A(ALUSrc_A),
        .ALUSrc_B(ALUSrc_B),
        .ALUC(ALUC),                               //ALU_Control
        .Jump(Jump),
        .Branch(Branch),                           //Jump/Branch
        .ImmSel(ImmSel),
        .CPU_MIO(MIO), 
        .DatatoReg(DatatoReg),                     //MemtoReg
        .PCEN(PCEN), 
        .RegWrite(RegWrite), 
        .WR(WR),
        .rs1_used(rs1_used),
        .rs2_used(rs2_used)
        );                                  //MemRW
                
    RV32IPDP_C	 U1_2(
        .clk(clk),
        .rst(reset), 
        .ALUSrc_A(ALUSrc_A), 
        .ALUSrc_B(ALUSrc_B),
        .ImmSel(ImmSel),
        .ALUC(ALUC),                          //ALU_Control
        .Jump(Jump),
        .Branch(Branch),                      //Branch-Jump
        .DatatoReg(DatatoReg),                //MemtoReg
        .Data_in(Datai), 
        .rs1_used(rs1_used),
        .rs2_used(rs2_used),
        
        .inst_field(INST), 
        .PCEN(PCEN),
        .WR(WR),
        .MIO(MIO), 
        .RegWrite(RegWrite),
        .ALU_out(Addr),                       
        .MWR(MWR),
        .M_MIO(M_MIO),
        .Data_out(Datao), 
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
        .PCSource(PCSource),
        .Imm32(Imm32),
        .ImmSel(ImmSel),
        .RS1DATA(RS1DATA),
        .RS2DATA(RS2DATA),
        .ALUC(ALUC),
        .Datai(Datai),
        .Datao(Datao),
        .ALU_out(Addr),
        .Addr(Addr),
        .A(A),
        .B(B),
        .WDATA(WDATA),
        .DatatoReg(DatatoReg),
        .ALUSrc_A(ALUSrc_A),
        .ALUSrc_B(ALUSrc_B),
        .WR(MWR),
        .MIO(M_MIO),
        .RegWrite(RegWrite),
        .data_hazard(Data_stall),
        .control_hazard(BJ_stall),
        
        .Debug_addr(Debug_addr[4:0]),
        .Test_signal(Test_signal)    
    );
endmodule
