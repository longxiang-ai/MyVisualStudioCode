//------------------ ID/EX Latch ---------------------
    wire [31:0] EX_A, EX_B, EX_Imm32;
    wire [4:0] EX_rd;
    wire [2:0] EX_ALUC;
    wire [1:0] EX_DatatoReg;
    wire EX_ALUSrc_A, EX_ALUSrc_B, EX_Jump, EX_Branch, EX_RegWrite, EX_WR, EX_MIO, EX_sign;
          
    REG_ID_EX IDEX(
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
        .sign(sign),
        
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
        .EX_sign(EX_sign)
    );        


module REG_ID_EX(
    input clk,                    //ID/EX Latch
    input rst,
    input EN,
    input flush,
    input [31:0] ID_IR,
    input [31:0] ID_PCurrent,
    input [31:0] rs1_data,
    input [31:0] rs2_data,
    input [31:0] Imm32,
    input [4:0] rd_addr,
    input [1:0] ALUSrc_A,
    input [1:0] ALUSrc_B,
    input [2:0] ALUC,
    input [1:0] DatatoReg,
    input RegWrite,
    input Jump,
    input Branch,
    input WR,
    input MIO,
    input sign,
    
    output reg [31:0] EX_PCurrent,
    output reg [31:0] EX_IR,
    output reg [31:0] EX_A,
    output reg [31:0] EX_B,
    output reg [31:0] EX_Imm32,
    output reg [4:0] EX_rd,
    output reg EX_ALUSrc_A,
    output reg EX_ALUSrc_B,
    output reg [2:0] EX_ALUC,
    output reg [1:0] EX_DatatoReg,
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

REG_ID_EX IDEX(
        .clk(clk),
        .rst(rst),
        .EN(1'b1),
        .flush(Data_stall),
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
        .sign(sign),
        
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
        .EX_sign(EX_sign)
    );   
    
module REG_ID_EX(
    input clk,                    //ID/EX Latch
    input rst,
    input EN,
    input flush,                    // 6.28 若指令数据竞争则插入两个 bubble, IF 已禁止PC更新
    input [31:0] ID_IR,
    input [31:0] ID_PCurrent,
    input [31:0] rs1_data,
    input [31:0] rs2_data,
    input [31:0] Imm32,
    input [4:0] rd_addr,
    input [1:0] ALUSrc_A,
    input [1:0] ALUSrc_B,
    input [2:0] ALUC,
    input [1:0] DatatoReg,
    input RegWrite,
    input Jump,
    input Branch,
    input WR,
    input MIO,
    input sign,
    
    output reg [31:0] EX_PCurrent,
    output reg [31:0] EX_IR,
    output reg [31:0] EX_A,
    output reg [31:0] EX_B,
    output reg [31:0] EX_Imm32,
    output reg [4:0] EX_rd,
    output reg EX_ALUSrc_A,
    output reg EX_ALUSrc_B,
    output reg [2:0] EX_ALUC,
    output reg [1:0] EX_DatatoReg,
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
            //EX_MIO          <= 0; 
            EX_IR           <= 32'h0000_0000; 
            EX_PCurrent     <= 32'h0000_0000;
        end
        else if (EN) begin
            if (flush) begin        // 数据冲突时，冲刷流水线禁止改变PC状态
                EX_IR <= 32'h0000_0000;
                EX_rd <= 0;
                EX_RegWrite <= 0;
                EX_Jump <= 0;
                EX_Branch <= 0;
                EX_WR <= 0;
                EX_MIO <= MIO;
                EX_PCurrent <= ID_PCurrent;
            end
            else begin 
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
    end
endmodule

