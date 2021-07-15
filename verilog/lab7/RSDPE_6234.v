`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/04/11 15:26:01
// Design Name: 
// Module Name: RSDP9
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module RSDPE(
     input clk,
     input rst,
     input [31:0]inst_field,
     input [31:0]Data_in,
     input ALUSrc_A,
     input ALUSrc_B,
     input [2:0]ALUC,
     input [1:0]ImmSel,
     input [1:0]DatatoReg,
     input PCEN,
     input [1:0]PCSource, // PCSource replaces Branch Jump signal
     input RegWrite,
     input Sign,
     output [31:0]PCOUT,
     output [31:0]Data_out,
     output [31:0]ALU_out,
     output overflow,
     output zero,
     output [31:0]rs1_data,
     output [31:0]Wt_data,
     output [31:0]ALUA,
     output [31:0]ALUB,
     input [6:0]Debug_addr,
     output [31:0]Debug_regs
);

     wire [31:0]ALU_res;
     wire [31:0]Imm;
     wire [31:0]regs_data_in;
     wire [31:0]PC_MUX_out;
     
     wire [31:0]PC_reg_out;
     wire [31:0]regs_data_out_1;
     wire [31:0]regs_data_out_2;

     wire [31:0]PC_4;
     wire [31:0]PC_rel;
     assign PC_4 = PC_reg_out + 32'h4;
     assign PC_rel = PC_reg_out + Imm;

     assign ALU_out[31:0] = ALU_res;
     assign Data_out[31:0] = regs_data_out_2;
     assign PCOUT[31:0] = PC_reg_out;
     assign rs1_data = regs_data_out_1;
     assign Wt_data = regs_data_in;

     ALU U1(
          .A(regs_data_out_1),
          .B(ALUB),
          .ALU_operation(ALUC),
          .sign(Sign),
          .res(ALU_res),
          .zero(zero),
          .overflow(overflow)
     );

     MUX4T1_32   ImmGen(
          .s(ImmSel),
          .I0({{20{inst_field[31]}},inst_field[31:20]}),                        // I
          .I1({{20{inst_field[31]}},inst_field[31:25],inst_field[11:7]}),       // S
          .I2({{19{inst_field[31]}},inst_field[31],inst_field[7],               // Branch
               inst_field[30:25],inst_field[11:8],1'b0}),
          .I3({{11{inst_field[31]}},inst_field[31],inst_field[19:12],           // UJ
               inst_field[20],inst_field[30:21],1'b0}),
          .o(Imm)
     );

     MUX4T1_32 PC_MUX(
          .I0(PC_4),
          .I1(PC_rel),
          .I2(PC_rel),
          .I3(PC_rel),
          .o(PC_MUX_out),
          .s({PCSource[1],{PCSource[0] & zero}})
     );
     
     MUX2T1_32 ALUB_MUX(
          .I0(regs_data_out_2),
          .I1(Imm),
          .o(ALUB),
          .s(ALUSrc_B)
     );
          
     MUX4T1_32 DatatoReg_MUX(
          .I0(ALU_res),
          .I1(Data_in),
          .I2(PC_4),
          .I3({inst_field[31:12],12'b0000_0000_0000}), // change for lui, only lui uses datatoreg:11
          .o(regs_data_in),
          .s(DatatoReg)
     );
          
     Reg32 PC(
          .CE(1'b1),
          .D(PC_MUX_out),
          .Q(PC_reg_out),
          .clk(clk),
          .rst(rst)
     );
          
     regs U2(
          .clk(clk),
          .rst(rst),
          .Wt_data(regs_data_in),
          .Rs1_data(regs_data_out_1),
          .Rs2_data(regs_data_out_2),
          .Rs1_addr(inst_field[19:15]),
          .Rs2_addr(inst_field[24:20]),
          .Wt_addr(inst_field[11:7]),
          .RegWrite(RegWrite)
     );
          
endmodule
