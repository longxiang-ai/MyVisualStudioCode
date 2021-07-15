// Forwarding unit
    // Forward A 
    always @* begin
        if(MEM_RegWrite && MEM_rd !=0 && EX_rs1 !=0 && EX_rs1 == MEM_rd)
            ForwardA = 2'b10;
        else if (WB_RegWrite && WB_rd !=0 && EX_rs1 !=0 && (EX_rs1 == WB_rd))
            ForwardA = 2'b01;
        else
            ForwardA = 2'b00;
    end
    // ALUA Forwarding with Data Hazard:
    always @* begin 
        case(ForwardA)
            2'b00: ALUA = EX_A; // 无竞争
            2'b01: ALUA = Wt_data;// 竞争2：选择直接通路WB级Wt_data
            2'b10: ALUA = MEM_ALUO; // 竞争1： 选择直接通路MEM级MEM_ALUO
            2'b11: ALUA = EX_A; // no use
        endcase
    end


    // Forward B
    always @* begin
        if(MEM_RegWrite && MEM_rd !=0 && EX_rs2 !=0 && EX_rs2 == MEM_rd)
            ForwardB = 2'b10;
        else if (WB_RegWrite && WB_rd !=0 && EX_rs2 !=0 && (EX_rs2 == WB_rd))
            ForwardB = 2'b01;
        else
            ForwardB = 2'b00;
    end
    // ALUB Forwarding with Data Hazard:
     always @* begin 
         case(ForwardB)
             2'b00: FEX_B = EX_B; // 无竞争
             2'b01: FEX_B = Wt_data;// 竞争2：选择直接通路WB级Wt_data
             2'b10: FEX_B = MEM_ALUO; // 竞争1： 选择直接通路MEM级MEM_ALUO
             2'b11: FEX_B = EX_B; // no use
         endcase
     end
     assign ALUB = EX_ALUSrc_B ? EX_Imm32 : FEX_B;


reg [1:0]Forwardrs1,Forwardrs2;
always @* begin
    if(Branch && EX_RegWrite && EX_rd != 0 && rs1_addr !=0 && rs1_addr == EX_rd)
        Forwardrs1 = 10;
    else if(Branch && MEM_RegWrite && MEM_rd !=0 && rs1_addr != 0 && (rs1_addr == MEM_rd))
        Forwardrs1 = 01;
    else Forwardrs1 = 2'b00;

    if(Branch && EX_RegWrite && EX_rd != 0 && rs2_addr !=0 && rs2_addr == EX_rd)
        Forwardrs2 = 10;
    else if(Branch && MEM_RegWrite && MEM_rd !=0 && rs2_addr != 0 && (rs2_addr == MEM_rd))
        Forwardrs2 = 01;
    else Forwardrs2 = 2'b00;
end
    //---------------------------- IF stage ----------------------------
    // 6.29.2
    reg Btake;
    reg [31:0] PCNEXT;
    wire [31:0] PC_4 = PCOUT + 4;
    wire [31:0] PC_Jump = ID_PCurrent + Imm32 ;           // Jump伪指令目标地址
    wire [31:0] PC_Branch = Btake ? PC_Jump : PCOUT;
    assign PCSource = {Jump, Btake};
// -------------------------- Btake ------------------------------
     always @* begin
             case ({Forwardrs1,Forwardrs2})
                 4'b0000: Btake = Branch && rs1_data == rs2_data;
                 4'b0010: Btake = Branch && rs1_data == EX_ALUO;
                 4'b0001: Btake = Branch && rs1_data == MEM_ALUO;
                 
                 4'b1000: Btake = Branch && EX_ALUO == rs2_data;
                 4'b1010: Btake = Branch && EX_ALUO == EX_ALUO;
                 4'b1001: Btake = Branch && EX_ALUO == MEM_ALUO;
                 
                 4'b0100: Btake = Branch && MEM_ALUO == rs2_data;
                 4'b0110: Btake = Branch && MEM_ALUO == EX_ALUO;
                 4'b0101: Btake = Branch && MEM_ALUO == MEM_ALUO;
                 
                 default : Btake = Branch && rs1_data == rs2_data;
             endcase
         end
         
         