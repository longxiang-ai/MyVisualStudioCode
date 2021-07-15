REG_IF_ID IFID(
        .clk(clk),
        .rst(rst),
        .EN(1'b1),
        .Data_stall(),              // 尚未实现，保留接口
        .flush(),                   // 尚未实现，保留接口
        .PCOUT(PCOUT),
        .IR(inst_field),
        .ID_IR(ID_IR),
        .ID_PCurrent(ID_PCurrent)
    );


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

    //IF/ID Latch          
    REG_IF_ID IFID(
        .clk(clk),
        .rst(rst),
        .EN(1'b1),
        .Data_stall(Data_stall),
        .flush(BJ_stall),
        .PCOUT(PCOUT),
        .IR(inst_field),
        .ID_IR(ID_IR),
        .ID_PCurrent(ID_PCurrent)
    );
    
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
            if (Data_stall) begin               // 优先处理数据冒险竞争，此处仅禁止PC更新
                ID_IR   <= ID_IR ;              // IR waiting for Data Hazards
                ID_PCurrent <= ID_PCurrent;     // 保存对应PC指针
            end
            else if (flush) begin
                ID_IR <= 32'h0000_2003 ;        // 若 branch flush 3 条指令
                ID_PCurrent <= ID_PCurrent;     // 清除指令并暂停取指
            end
            else begin
            ID_IR       <= IR;
            ID_PCurrent <= PCOUT;
            end
        end
        else begin
            ID_IR       <= ID_IR;
            ID_PCurrent <= ID_PCurrent;
        end
    end
endmodule