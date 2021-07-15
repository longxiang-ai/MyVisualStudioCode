module REG32(
    input clk,
    input rst,
    input CE,
    input [31:0]D,
    output reg [31:0]Q
    );
    
always @(posedge clk or posedge rst)begin
        if (rst == 1) 
            Q <= 32'h0000_0000;
        else if (CE == 1) 
            Q <= D;
    end
endmodule