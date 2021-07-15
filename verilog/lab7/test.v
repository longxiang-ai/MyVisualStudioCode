module ImmGen(
    input [1:0]s,
    input [31:0]I,
    input sign,
    output reg [31:0] o
    );
    always @(*)
    begin
        case(s)
        2'b00: o <= (sign == 1) ? {{20{I[31]}}, I[31:20]} : {{20'b0}, I[31:20]};
        2'b01: o <= (sign == 1) ? {{20{I[31]}}, I[31:25], I[11:7]} : {{20'b0}, I[31:25], I[11:7]};
        2'b10: o <= (sign == 1) ? {{19{I[31]}}, I[31], I[7], I[30:25], I[11:8], 1'b0} : {{19'b0}, I[31], I[7], I[30:25], I[11:8], 1'b0};
        2'b11: o <= (sign == 1) ? {{11{I[31]}}, I[31], I[19:12], I[20], I[30:21], 1'b0} : {{11'b0}, I[31], I[19:12], I[20], I[30:21], 1'b0};
        default:o <= o;
        endcase
    end
endmodule