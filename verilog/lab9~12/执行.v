//------------------------ EXE stage -----------------
    wire [31:0] EX_ALUO;
    assign ALUA = EX_A;
    assign ALUB = EX_ALUSrc_B ? EX_Imm32 : EX_B;
    wire [31:0] EX_Target = EX_PCurrent + EX_Imm32;
                
    alu ALU
         (.A(ALUA), 
          .B(ALUB),
          .sign(EX_sign),
          .ALU_operation(EX_ALUC),
          .res(EX_ALUO),
          .zero(zero)
          );