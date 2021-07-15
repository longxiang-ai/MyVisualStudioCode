//------------------ MEM/WB Latch ------------------------
    REG_MEM_WB MEMWB(
        .clk(clk), .rst(rst), .EN(1'b1), .MEM_IR(MEM_IR), .MEM_PCurrent(MEM_PCurrent),
        .MEM_ALUO(MEM_ALUO), .Datai(Data_in), .MEM_rd(MEM_rd),
        .MEM_DatatoReg(MEM_DatatoReg), .MEM_RegWrite(MEM_RegWrite),
        
        .WB_PCurrent(WB_PCurrent), .WB_IR(WB_IR), .WB_ALUO(WB_ALUO), .WB_MDR(WB_MDR),
        .WB_rd(WB_rd), .WB_DatatoReg(WB_DatatoReg), .WB_RegWrite(WB_RegWrite) 
    );

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
    output reg [31:0] WB_MDR,  //锁存MIO送入CPU输入数据
    output reg [4:0] WB_rd,
    output reg [1:0] WB_DatatoReg,
    output reg WB_RegWrite
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
