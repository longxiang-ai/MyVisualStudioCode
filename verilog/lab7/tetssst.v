initial begin
    OPcode = 0;
    Fun3 = 0; Fun7 = 0;
    MIO_ready = 0;
    #40;
    // 检查输出信号和关键信号输出是否满足真值表
    OPcode = 5'b01100;  //ALU 指令，检查 ALUop=2'b10; RegDst=1; RegWrite=1
    Fun3 = 3'b000; Fun7 = 1'b0;//add, 检查 ALU_Control=3'b010
    #20;
    Fun3 = 3'b000; Fun7 = 1'b1;//sub, 检查 ALU_Control=3'b110
    #20;
    Fun3 = 3'b111; Fun7 = 1'b0;//and, 检查 ALU_Control=3'b000
    #20;
    Fun3 = 3'b110; Fun7 = 1'b0;//or, 检查 ALU_Control=3'b001
    #20;
    Fun3 = 3'b010; Fun7 = 1'b0 ;//slt, 检查 ALU_Control=3'b111
    #20;
    Fun3 = 3'b101; Fun7 = 1'b0//srl, 检查 ALU_Control=3'b101
    #20;
    Fun3 = 3'b100; Fun7 = 1'b0//xor, 检查 ALU_Control=3'b011
    #20;
    Fun3 = 3'b111; Fun7 = 1'b1; // 间隔
    #1;
    OPcode = 5'b00000;//load 指令，检查 ALUop=2'b01,
    #20; // ALUSrc_B=1, MemtoReg=1, RegWrite=1
    OPcode = 5'b01000;
    #20; //store 指令，检查 ALUop=2'b10, MemRW=1, ALUSrc_B=1
    OPcode = 5'b11000;//beq 指令，检查 ALUop=2'b11, Branch=1
    #20;
    OPcode = 5'b11011;//jump 指令，检查 Jump=1
    Jump = 1'b0;
    #20;
    Jump = 1'b1;
    #20;
    // I-type 部分，9指令暂不支持
    // OPcode = 5'b00100; //I 指令，检查 ALUop=2'b01; RegWrite=1
    // ALUop = 2'b01;
    // RegWrite = 1'b1;
    // ImmSel = 2'b00;
    // #20;
    // Fun3 = 3'b000; //addi, 检查 ALU_Control=3'b010
    // #20;
    // Fun3 = 3'b001; //
    // #20;
    // Fun3 = 3'b010; //slti
    // #20;
    // Fun3 = 3'b011; //srli
    // #20;
    // Fun3 = 3'b100; //xori
    // #20;
    // Fun3 = 3'b101; //
    // #20;
    // Fun3 = 3'b110; //ori
    // #20;
    // Fun3 = 3'b111; //
    // #20;
    OPcode = 5'h1f; // 
    Fun3 = 3'b000; Fun7 = 1'b0; // 
end
