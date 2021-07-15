    //MEM stage
    assign Data_out = MEM_Datao;
    assign ALU_out = MEM_ALUO;
    assign MWR = MEM_WR;
    assign M_MIO = MEM_MIO;
    wire [31:0] WB_ALUO, WB_MDR;
    wire [1:0] WB_DatatoReg;