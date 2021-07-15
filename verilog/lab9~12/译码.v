//---------------------- ID stage-------------------------------
    wire [4:0] rs1_addr = ID_IR[19:15];
    wire [4:0] rs2_addr = ID_IR[24:20];
    wire [4:0] rd_addr = ID_IR[11:7];
    wire [4:0] WB_rd;
    wire WB_RegWrite;

      regs DU2(
          .clk(clk),
          .rst(rst),
          .Wt_data(Wt_data),
          .rdata_A(rs1_data),
          .rdata_B(rs2_data),
          .R_addr_A(rs1_addr),
          .R_addr_B(rs2_addr),
          .Wt_addr(WB_rd),
          .L_S(WB_RegWrite),
          .Debug_addr(Debug_addr[4:0]),
          .Debug_regs(Debug_regs)
      );

    ImmGen ImmGen_0
         (.s(ImmSel),
          .sign(1),
          .o(Imm32),
          .I(ID_IR));