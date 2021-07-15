module ImmGen(
    input [1:0]s,
    input [31:0]I,
    output reg [31:0] o
   );
   
    always @(*)begin
        case(s)
            // I-type
            2'b00: o <= {{20{I[31]}}, I[31:20]};
            // S-type
            2'b01: o <= {{20{I[31]}}, I[31:25], I[11:7]};
            // UJ-type
            2'b10: o <= {{19{I[31]}}, I[31], I[7], I[30:25], I[11:8], 1'b0};
            // U-type
            2'b11: o <= {{11{I[31]}}, I[31], I[19:12], I[20], I[30:21], 1'b0};
            default:o <= o;
        endcase
    end
endmodule