`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/25 18:05:16
// Design Name: 
// Module Name: RSCUE
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


module RSCUE(
    input clk,
    input reset,
    input [4:0]OPcode,
    input [2:0]Fun3,
    input Fun7,
    input MIO_ready,
    input zero,
    
    output reg ALUSrc_A,
    output reg ALUSrc_B,
    output reg [1:0]ImmSel,
    output reg [1:0]DatatoReg,
    output PCEN,
    // output reg Jump,
    // output reg Branch,
    output reg [1:0]PCSource,
    output reg RegWrite,
    output WR,
    output reg [2:0]ALUC,
    output reg CPU_MIO,
    output ALE
);
    
reg [1:0]ALUop;
reg [5:0]Error;
wire [3:0]Fun;
reg MemRead, MemWrite;

assign WR = MemWrite && (~MemRead);
assign ALE = ~clk;

initial begin
    ALUSrc_A  = 0;
    ALUSrc_B  = 0;
    DatatoReg = 0;
    RegWrite  = 0;
    PCSource = 2'b00;
    CPU_MIO   = 0;
    ALUop     = 2'b10;
    Error     = 6'b000000;
end

always @* begin
    case(OPcode)
        5'b01100:begin ALUop=2'b10;RegWrite=1;          ALUSrc_B=0;PCSource = 2'b00;DatatoReg=2'b00;MemRead=1; MemWrite=0; end //ALU(R)
        5'b00000:begin ALUop=2'b00;RegWrite=1;ImmSel=00;ALUSrc_B=1;PCSource = 2'b00;DatatoReg=2'b01;MemRead=1; MemWrite=0;  CPU_MIO=1; end //load
        5'b01000:begin ALUop=2'b00;RegWrite=0;ImmSel=01;ALUSrc_B=1;PCSource = 2'b00; CPU_MIO=1;MemRead=0; MemWrite=1; end //store
        5'b11000:begin ALUop=2'b01;RegWrite=0;ImmSel=10;ALUSrc_B=0;PCSource = 2'b01; MemRead=1; MemWrite=0;                end //beq
        5'b11011:begin ALUop=2'b            RegWrite=1;ImmSel=11;           PCSource = 2'b10;DatatoReg=2'b10;MemRead=1; MemWrite=0; end //jal
        5'b00100:begin ALUop=2'b11;RegWrite=1;ImmSel=00;ALUSrc_B=1;PCSource = 2'b00;DatatoReg=2'b00; MemRead=1; MemWrite=0;end //ALU(I)
        5'b11001:begin // 
        5'b01101:begin ALUop=//lui
            
        end
            
        end
        default:        Error   =6'b101010;
    endcase
end

assign  Fun = {Fun3,Fun7};
always @* begin
    case(ALUop)
        2'b00: ALUC=3'b010;             //load/store
        2'b01: ALUC=3'b110;             //sub:beq
        2'b10:
            case(Fun)
                4'b0000: ALUC = 3'b010; //add
                4'b0001: ALUC = 3'b110; //sub
                4'b1110: ALUC = 3'b000; //and
                4'b1100: ALUC = 3'b001; //or
                4'b0100: ALUC = 3'b111; //slt
                4'b1010: ALUC = 3'b101; //srl
                4'b1000: ALUC = 3'b011; //xor
                default: ALUC = 3'bxxx;
            endcase
        2'b11:
            case(Fun3)
                3'b000: ALUC = 3'b010;  //addi
                3'b111: ALUC = 3'b000;  //andi
                3'b110: ALUC = 3'b001;  //ori
                3'b010: ALUC = 3'b111;  //slti
                3'b101: ALUC = 3'b101;  //srl
                3'b100: ALUC = 3'b011;  //xori
                default: ALUC = 3'bxxx;
            endcase
        default:    ALUC = 3'bxxx;
    endcase
end
endmodule



`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/25 18:06:35
// Design Name: 
// Module Name: RSDPE
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
    input clk,rst,
    input [31:0]Data_in,inst_field,
    input [2:0]ALU_operation,
    input [1:0]MemtoReg,ImmSel,
    input Jump,Branch,ALUSrc_A,ALUSrc_B,RegWrite,
   
    input [6:0]Debug_addr,
    // lab7 新增
    input sign,
    input PCEN,
    
    output [31:0]ALU_out,Data_out,PC_out,
    output [31:0]Debug_regs,rs1_data,Wt_data,
    output [31:0]ALUB,
    output zero,
    output overflow
    );
    
// regs
wire [4:0] Rs1_addr, Rs2_addr, Wt_addr;
// Imm
wire [31:0]Imm_out;
// PC
wire [31:0]PC_4,PC_offset;
assign PC_4 = PC_out + 32'h4;
assign PC_offset = PC_out + Imm_out;
// mux中间变量
wire [31:0]mux_branch_out,mux_jump_out;

MUX4T1_32 mux_memtoreg(
    .s(MemtoReg),
    .I0(ALU_out),
    .I1(Data_in),
    .I2(PC_4),
    .I3(PC_4),
    .o(Wt_data)
    );
MUX2T1_32 mux_branch(
    .s(zero & Branch),
    .I0(PC_4),
    .I1(PC_offset),
    .o(mux_branch_out)
    );
MUX2T1_32 mux_ALUB(
    .s(ALUSrc_B),
    .I0(Data_out),
    .I1(PC_offset),
    .o(ALUB));
MUX2T1_32 mux_jump(
    .s(Jump),
    .I0(mux_branch_out),
    .I1(PC_offset),
    .o(mux_jump_out));
ImmGen U3(
    .s(ImmSel),
    .I(inst_field),
    .o(Imm_out));
regs Regs(
    .clk(clk),
    .rst(rst),
    .Rs1_addr(inst_field[19:15]),
    .Rs2_addr(inst_field[24:20]),
    .Wt_addr(inst_field[11:7]),
    .Wt_data(Wt_data),
    .RegWrite(RegWrite),
    .Rs1_data(rs1_data),
    .Rs2_data(Data_out));

REG32 PC(
    .clk(clk),
    .rst(rst),
    .CE(1'b1),
    .D(mux_jump_out),
    .Q(PC_out));
//ALU_HDL ALU(
ALU(
    .A(rs1_data),
    .B(ALUB),
    .ALU_operation(ALU_operation),
    .res(ALU_out),
    .zero(zero),
    .overflow(overflow),
    // 控制有无符号数
    .sign(sign)
    );
endmodule





`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/25 18:05:16
// Design Name: 
// Module Name: RSCUE
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


module RSCUE(
    input clk,
    input reset,
    input [4:0]OPcode,
    input [2:0]Fun3,
    input Fun7,
    input MIO_ready,
    input zero,
    
    output reg ALUSrc_A,
    output reg ALUSrc_B,
    output reg [1:0]ImmSel,
    output reg [1:0]DatatoReg,
    output PCEN,
    output reg Jump,
    output reg Branch,
    output reg RegWrite,
    output WR,
    output reg [2:0]ALUC,
    output reg CPU_MIO,
    output ALE
);
    
reg [1:0]ALUop;
reg [5:0]Error;
wire [3:0]Fun;
reg MemRead, MemWrite;

assign WR = MemWrite && (~MemRead);
assign ALE = ~clk;

initial begin
    ALUSrc_A  = 0;
    ALUSrc_B  = 0;
    DatatoReg = 0;
    RegWrite  = 0;
    Branch    = 0;
    Jump      = 0;
    CPU_MIO   = 0;
    ALUop     = 2'b10;
    Error     = 6'b000000;
end

always @* begin
    case(OPcode)
        5'b01100:begin ALUop=2'b10;RegWrite=1;           ALUSrc_B=0;Branch=0;Jump=0;DatatoReg=2'b00;MemRead=1; MemWrite=0; end //ALU(R)
        5'b00000:begin ALUop=2'b00;RegWrite=1;ImmSel=00;ALUSrc_B=1;Branch=0;Jump=0;DatatoReg=2'b01;
                                                                                  MemRead=1; MemWrite=0;  CPU_MIO=1; end //load
        5'b01000:begin ALUop=2'b00;RegWrite=0;ImmSel=01;ALUSrc_B=1;Branch=0;Jump=0; CPU_MIO=1;MemRead=0; MemWrite=1; end //store
        5'b11000:begin ALUop=2'b01;RegWrite=0;ImmSel=10;ALUSrc_B=0;Branch=1;Jump=0; MemRead=1; MemWrite=0;                end //beq
        5'b11011:begin             RegWrite=1;ImmSel=11;                    Jump=1;DatatoReg=2'b10;MemRead=1; MemWrite=0; end //????
        5'b00100:begin ALUop=2'b11;RegWrite=1;ImmSel=00;ALUSrc_B=1;Branch=0;Jump=0;DatatoReg=2'b00; MemRead=1; MemWrite=0;end //ALU(I)
        default:        Error   =6'b101010;
    endcase
end

assign  Fun = {Fun3,Fun7};
always @* begin
    case(ALUop)
        2'b00: ALUC=3'b010;             //load/store
        2'b01: ALUC=3'b110;             //sub:beq
        2'b10:
            case(Fun)
                4'b0000: ALUC = 3'b010; //add
                4'b0001: ALUC = 3'b110; //sub
                4'b1110: ALUC = 3'b000; //and
                4'b1100: ALUC = 3'b001; //or
                4'b0100: ALUC = 3'b111; //slt
                4'b1010: ALUC = 3'b101; //srl
                4'b1000: ALUC = 3'b011; //xor
                default: ALUC = 3'bxxx;
            endcase
        2'b11:
            case(Fun3)
                3'b000: ALUC = 3'b010;  //addi
                3'b111: ALUC = 3'b000;  //andi
                3'b110: ALUC = 3'b001;  //ori
                3'b010: ALUC = 3'b111;  //slti
                3'b101: ALUC = 3'b101;  //srl
                3'b100: ALUC = 3'b011;  //xori
                default: ALUC = 3'bxxx;
            endcase
        default:    ALUC = 3'bxxx;
    endcase
end
endmodule






`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/25 18:08:50
// Design Name: 
// Module Name: CSTE_SRV32
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


module CSTE_SRV32(
    input clk_100mhz,
    input RSTN,
    input [15:0] SW,
    input [3:0] KCOL,
    output [4:0] KROW,
    output CR,
    output RDY,
    output readn,
    
    output LEDCK,
    output LEDCR,
    output LEDEN,
    output LEDDT,
    
    output SEGCK,
    output SEGCR,
    output SEGEN,
    output SEGDT,
    
    output [3:0] AN,
    output [7:0] SEGMENT,
    output [7:0] LED,
    output Buzzer,
    
    output [3:0] Red,
    output [3:0] Green,
    output [3:0] Blue,
    output HSYNC,
    output VSYNC
    );
    
    wire mapup;
    wire [31:0] Ai, Bi;
    wire CPUClk, nCPUClk, nclk, clka;
    wire MIO;
    wire C0, C1, C2;
    wire [31:0] Counter;
    wire [31:0] Addr, Datai, Datao, inst;
    wire CONT_W0208, GPIO_W0200, GPIO_W0204;
    wire [31:0] Peripheral;
    wire [3:0] BTNO;
    wire [4:0] KCODE;
    wire [6:0] Debug_addr;
    wire [7:0] blink;
    wire [9:0] PCol, PRow;
    wire [11:0] dout;
    wire [15:0] GPIOf0;
    
    wire [31:0] Debug_data;
    wire [31:0] DIVO;
    wire [31:0] Disp_num;
    wire [0:0] data_ram_we;
    wire GPIOE00;
    wire GPIOF0;
    wire IO_clk;
    wire [7:0] LE;
    wire [31:0] PC;
    wire [7:0] point;
    wire [3:0] Pulse;
    wire [11:0] ram_addr;
    wire [31:0] ram_data_in;
    wire [31:0] ram_data_out;
    wire Ready;
    wire rst;
    wire [4:0] State;
    wire [15:0] SWO;
    wire WR;
    
    assign Buzzer = DIVO[25] & SWO[8];
    assign IO_clk = nCPUClk;
    
    RSCPUE U1(
    .clk(CPUClk),
    .reset(rst),
    .TNI(8'h0),
    .Ready(Ready),
    .Addr(Addr),
    .Datai(Datai),
    .Datao(Datao),
    .inst(inst),
    .MIO(MIO),
    .PC(PC[31:0]),
    .WR(WR),
    .ALE(clka),
    .Debug_addr(Debug_addr),
    .Debug_data(Debug_data)
    );
    
    ROM U2(
    .a(PC[11:2]),
    .spo(inst)
    );
    
    RAM U3(
    .addra(ram_addr[11:0]),
    .clka(clka),
    .dina(ram_data_in[31:0]),
    .wea(data_ram_we[0]),
    .douta(ram_data_out)
    );
    
    wire [31:0] MEM_Addr = SWO[13] ? MIO ? {20'h0000, ram_addr, 2'b00} : 32'hFFFF_FFFF
                                    : PC;
    wire [31:0] MEM_Data = SWO[13] ? MIO ? ram_data_out : 32'hAA55_AA55
                                    : inst;
    MIOBUS U4(
    .clk(clk_100mhz),
    .rst(rst),
    .BTN(BTNO),
    .SW(SWO),
    .CPU_wait(Ready),
    .mem_w(WR),
    .Addr_bus(Addr),
    .Data4CPU(Datao),
    .Data2CPU(Datai[31:0]),
    
    .GPIO_W0200(GPIO_W0200),
    .GPIO_W0204(GPIO_W0204),
    .CONT_W0208(CONT_W0208),
    .Peripheral(Peripheral),
    .C0(C0),
    .C1(C1),
    .C2(C2),
    .Counter(Counter),
    .ram_addr(ram_addr),
    .data_ram_we(data_ram_we),
    .ram_data_out(ram_data_out),
    .ram_data_in(ram_data_in)
    );
    
    DSEGIO U5(
    .clk(IO_clk),
    .rst(rst),
    .EN(GPIO_W0204),
    .A0(DIVO[6]),
    .map2up(DIVO[20]),
    .Test(SWO[7:5]),
    .LES(64'h0000_0000_0000_0000),
    .points({DIVO[31:0], DIVO[31:13], 5'b0_0000, 8'h00}),
    .Data0(Peripheral),
    .data1({2'b00, PC[31:2]}),
    .data2(inst),
    .data3(Counter),
    .data4(Addr),
    .data5(Datao),
    .data6(ram_data_out[31:0]),
    .data7(Ai),
    
    .Disp(Disp_num[31:0]),
    .LE(LE),
    .point(point),
    .mapup(mapup)
    );
    
    Display U6(
    .clk(clk_100mhz),
    .rst(rst),
    .Start(DIVO[20]),
    .Text(SWO[0]),
    .flash(DIVO[25]),
    .Hexs(Disp_num),
    .LES(LE),
    .points(point),
    .mapup(DIVO[20]),
    
    .segclk(SEGCK),
    .segclrn(SEGCR),
    .SEGEN(SEGEN),
    .segsout(SEGDT)
    );
    
    Disp2Hex U61(
    .Scan2(SWO[1]),
    .Scan10(DIVO[19:18]),
    .flash(DIVO[25]),
    .Text(SWO[0]),
    .LES(LE),
    .points(point),
    .Hexs(Disp_num),
    
    .AN(AN),
    .SEGMENT(SEGMENT)
    );
    
    GPIO U7 (
    .clk(IO_clk),
    .rst(rst),
    .EN(GPIO_W0200),
    .Datai(Peripheral),
    .Start(DIVO[20]),
    .GPIOf0(GPIOf0),
    .LEDo(),
    .ledclk(LEDCK),
    .ledclrn(LEDCR),
    .LEDEN(LEDEN),
    .ledsout(LEDDT)
    );
    
    PIO U71(
    .clk(IO_clk),
    .rst(rst),
    .EN(GPIO_W0200),
    .Datai(Peripheral),
    .LED(LED[7:0]),
    .GPIOf0()
    );
    
    Counter U10(
    .clk(clk_100mhz),
    .clk0(DIVO[8]),
    .clk1(DIVO[9]),
    .clk2(DIVO[11]),
    .counter_ch(GPIOf0[1:0]),
    .counter_val(Peripheral),
    .counter_we(CONT_W0208),
    .rst(rst),
    .Counter(Counter),
    .counter0_OUT(C0),
    .counter1_OUT(C1),
    .counter2_OUT(C2)
    );
    
    Clkdiv U8(
    .clk(clk_100mhz),
    .rst(rst),
    .STEP(SWO[2]),
    .clkdiv(DIVO),
    .nclk(nclk),
    .CPUClk(CPUClk),
    .nCPUClk(nCPUClk)
    );  
    
    Arraykeys U9(
    .clk(clk_100mhz),
    .rst(rst),
    .RSTN(RSTN),
    .KCOL(KCOL),
    .KROW(KROW),
    .SW(SW),
    .BTNO(BTNO),
    .pulse(Pulse),
    .CR(CR),
    .readn(readn),
    .KCODE(KCODE),
    .KRDY(RDY),
    .SWO(SWO)
    );
    
    EnterT32 M4(
    .clk(clk_100mhz),
    .BTN(BTNO[3:0]),
    .ArrayKey(SWO[15]),
    .TEST(SWO[7:5]),
    .Text(SWO[0]),
    .UP16(SWO[1]),
    .Din(KCODE),
    .DRDY(RDY),
    .Ai(Ai),
    .Bi(Bi),
    .blink(blink),
    .readn(readn)
    );
    
    VGA_TEST U11(
    .clk25(DIVO[1]),
    .clk(clk_100mhz),
    //.PCol(PCol),
    //.PRow(PRow),
    .Debug_addr(Debug_addr),
    .Debug_data(Debug_data),
    .MEM_Addr(MEM_Addr),
    .MEM_Data(MEM_Data),
    .SWO14(SWO[14]),
    .SWO13(SWO[13]),
    //.dout(dout),
    .Red(Red),
    .Green(Green),
    .Blue(Blue),
    .VSYNC(VSYNC),
    .HSYNC(HSYNC)
    );
    
endmodule
