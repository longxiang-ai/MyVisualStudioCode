// --------------------------- WB stage --------------------------- 
    always @* begin
        case (WB_DatatoReg)
            2'b00: Wt_data = WB_ALUO;
            2'b01: Wt_data = WB_MDR;
            2'b10: Wt_data = WB_PCurrent + 4;
            2'b11: Wt_data = WB_PCurrent + 4;
        endcase
    end    