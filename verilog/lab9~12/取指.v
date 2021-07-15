    // ----------------------- IF Stage -------------------------------
    reg [31:0] PCNEXT;                      // 下一步PC指令
    wire [31:0] PC_4 = PCOUT + 4;           // 直接+4
    wire [31:0] PC_Jump = MEM_Target;       // 从MEM读取出跳转指令的位置
    wire [31:0] PC_Branch = MEM_Target;
    wire Btake = MEM_zero && MEM_Branch;    // 采取分支跳转条件
    assign PCSource = {MEM_Jump, Btake};    // PCSource
    wire PCWR = PCEN;                       // PC更改写使能信号
   
   always @* begin
    case (PCSource)
        2'b00: PCNEXT = PC_4;
        2'b01: PCNEXT = PC_Branch;
        2'b10: PCNEXT = PC_Jump;
        2'b11: PCNEXT = PC_4;               // no use
    endcase
   end
    
    REG32 PC
         (.CE(PCWR),
          .D(PCNEXT),
          .Q(PCOUT),
          .clk(clk),
          .rst(rst)
          );

    //--------------------------------------- IF stage ----------------------------------------------- 
    // 6.29
    wire Btaken = Branch && (rs1_data == rs2_data);         // 判断是否采取分支
    reg [31:0] PCNEXT;
    wire [31:0] PC_4 = PCOUT + 4;
    wire [31:0] PC_Jump = ID_PCurrent + Imm32 ;             // Jump伪指令目标地址
    wire [31:0] PC_Branch = Btaken ? PC_Jump : PCOUT;       // PC跳转位置
    assign PCSource = {Jump,Btaken};
    wire PCWR = ~Data_stall && PCEN;