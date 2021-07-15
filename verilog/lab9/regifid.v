
module REG_IF_ID(
    input clk,
    input rst,
    input EN,
    input Data_stall,
    input flush,
    input [31:0] PCOUT,
    input [31:0] IR,

    output reg [31:0] ID_IR,
    output reg [31:0] ID_PCurrent
);

    always @(posedge clk) begin
        if (rst) begin
            ID_IR       <= 32'h0000_0000;
            ID_PCurrent <= 32'h0000_0000;

        end
        else if (EN) begin
            ID_IR       <= IR;
            ID_PCurrent <= PCOUT;
        end
        else begin
            ID_IR       <= ID_IR;
            ID_PCurrent <= ID_PCurrent;
        end
    end
endmodule