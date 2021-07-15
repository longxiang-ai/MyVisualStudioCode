    // --------------IF stage-----------------
    reg [31:0] PCNEXT;
    wire [31:0] PC_4 = PCOUT + 4;
    wire [31:0] PC_Jump = MEM_Target;

    wire Btaken = MEM_zero && MEM_Branch;
    wire [31:0] PC_Branch = Btaken ? MEM_Target : PCOUT;
    assign PCSource = {MEM_Jump,MEM_Branch};
    wire PCWR = ~J_Stall && ~Data_stall && PCEN; // 禁止取指
   
   always @* begin
    case (PCSource)
        2'b00: PCNEXT = PC_4;
        2'b01: PCNEXT = PC_Branch;  // MEM_branch out
        2'b10: PCNEXT = PC_Jump;
        2'b11: PCNEXT = PC_4;       // no use
    endcase
   end