//---------------------Hazards Detection by Data dependence --------------------------

    wire Hazards = (EX_RegWrite && EX_rd != 0 || MEM_RegWrite && MEM_rd !=0); // 前续1(2) 指令写 且不为零
    assign Data_stall = (rs1_used && rs1_addr != 0 && Hazards && (rs1_addr == EX_rd || rs1_addr == MEM_rd))
     || (rs2_used && rs2_addr != 0 && Hazards && (rs2_addr == EX_rd || rs2_addr == MEM_rd));
    assign BJ_stall = Branch || Jump || EX_Branch || EX_Jump || MEM_Branch || MEM_Jump;
    assign J_Stall = Branch || Jump || EX_Branch || EX_Jump ;
    
    //---------------------Hazards Detection by Data dependence --------------------------
    wire Hazards = (EX_RegWrite && EX_rd != 0 || MEM_RegWrite && MEM_rd !=0);
    assign Data_stall = (rs1_used && rs1_addr != 0 && Hazards && (rs1_addr == EX_rd || rs1_addr == MEM_rd))
    || (rs2_used && rs2_addr != 0 && Hazards && (rs2_addr == EX_rd || rs2_addr == MEM_rd));

    assign BJ_stall = Btaken || Jump;


    //---------------------Hazards Detection by load instruction --------------------------
    reg HazardLoad;
    always @* begin
        HazardLoad = 0;
        if(~EX_WR && EX_MIO && EX_rd !=0 && ((rs1_addr !=0 && rs1_addr == EX_rd) || 
        (rs2_addr != 0 && rs2_addr == EX_rd))) begin
            HazardLoad = 1;
        end
    end
    assign Data_stall = (rs1_used && rs1_addr != 0 && HazardLoad && (rs1_addr == EX_rd || rs1_addr == MEM_rd))
     || (rs2_used && rs2_addr != 0 && HazardLoad && (rs2_addr == EX_rd || rs2_addr == MEM_rd));
    assign BJ_stall = Btake || Jump;