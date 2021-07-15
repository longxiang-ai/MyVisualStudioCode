`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/30 18:40:21
// Design Name: 
// Module Name: CSTERISCV
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


module CSTERISCV(
input clk_100mhz,
input RSTN,
input [15:0]SW,
input [3:0]KCOL,
output [4:0]KROW,
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

output [3:0]AN,
output [7:0]SEGMENT,
output [7:0]LED,
output Buzzer,

output [3:0]Red,
output [3:0]Green,
output [3:0]Blue,
output HSYNC,
output VSYNC
);
wire mapup;
wire [31:0] Ai, Bi;
wire CPUClk,nCPUClk, nclk,clka;
wire MIO;
wire C0,C1,C2;
wire [31:0]Counter;
wire [31:0] Addr,Datai,Datao,inst;
wire CONT_W0208,GPIO_W0200,GPIO_W0204;
wire [31:0] Peripheral;
wire [3:0] BTNO;
wire [4:0] KCODE;
wire [6:0] Debug_addr;
wire [7:0] blink;
wire [9:0] PCol,PRow;
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
wire [4:0] state;
wire [15:0] SWO;
wire WR;
assign Buzzer = DIVO[25] & SWO[8];
assign IO_clk = nCPUClk;
//RSCPU9 U1(
//.clk(CPUClk),
//.reset(rst),
//.TNI(8'h0),
//.Ready(Ready),
//.Addr(Addr),
//.Datai(Datai),
//.Datao(Datao),
//.INST(inst),
//.MIO(MIO),
//.PC(PC[31:0]),
//.WR(WR),
//.ALE(clka),
//.Debug_addr(Debug_addr),
//.Debug_data(Debug_data));


wire zero;
wire ALUSrc_A,ALUSrc_B,PCEN,Jump,Branch,RegWrite;

wire [1:0]DatatoReg;
wire [2:0]ALUC;
wire [1:0]ImmSel;

wire [31:0]rs1_data,Wt_data,ALUA,ALUB,Debug_regs;
RSCU9 U1_1
(.clk(CPUClk),.reset(rst),.OPcode(inst[6:2]),
.Fun3(inst[14:12]),.Fun7(inst[30]),.MIO_ready(Ready),.zero(zero),.ALUSrc_A(ALUSrc_A),.ALUSrc_B(ALUSrc_B),.ImmSel(ImmSel),.DatatoReg(DatatoReg),
.PCEN(PCEN),.Jump(Jump),.Branch(Branch),.RegWrite(RegWrite),.WR(WR),.ALUC(ALUC),.CPU_MIO(MIO),.ALE(clka)
);
RSDP9 U1_2
(.clk(CPUClk),.rst(rst),.inst_field(inst),.Data_in(Datai),.ALUSrc_A(ALUSrc_A),.ALUSrc_B(ALUSrc_B),.ALUC(ALUC),.ImmSel(ImmSel),.DatatoReg(DatatoReg),
.PCEN(PCEN),.Jump(Jump),.Branch(Branch),.RegWrite(RegWrite),
.Debug_addr(Debug_addr),.PCOUT(PC),.Data_out(Datao),.ALU_out(Addr),.zero(zero),.rs1_data(rs1_data),.Wt_data(Wt_data),.ALUA(ALUA),.ALUB(ALUB),.Debug_regs(Debug_regs)
);
wire [31:0]Test_signal;
CPUTEST U1_3 
(
.PC(PC),.INST(inst),.RS1DATA(rs1_data),.Datai(Datai),.Datao(Datao),.Addr(Addr),.A(ALUA),.B(ALUB),.WDATA(Wt_data),
.ALUC(ALUC),.DatatoReg(DatatoReg),.ALUSrc_A(ALUSrc_A),.ALUSrc_B(ALUSrc_B),.WR(WR),.RegWrite(RegWrite),.Branch(Branch),.Jump(Jump),.Debug_addr(Debug_addr[4:0]),
.Test_signal(Test_signal)
);

wire [31:0] TestReg;
assign TestReg = Debug_addr[5]?Test_signal:Debug_regs;

ROM_D U2(.a(PC[11:2]),.spo(inst));

RAM_B U3(.addra(ram_addr[11:0]),.clka(clka),.dina(ram_data_in[31:0]),.wea(data_ram_we[0]),.douta(ram_data_out));

wire [31:0] MEM_Addr = SWO[13] ? MIO ? {20'h0000, ram_addr, 2'b00} : 32'hFFFFFFFF:PC;

wire [31:0] MEM_Data = SWO[13] ? MIO ? ram_data_out : 32'hAA5555AA: inst;

MIOBUS U4(.clk(clk_100mhz),.rst(rst),.BTN(BTNO),.SW(SWO),.CPU_wait(Ready),.mem_w(WR),.Addr_bus(Addr),.Data4CPU(Datao),.Data2CPU(Datai[31:0]),
.GPIO_W0200(GPIO_W0200),.GPIO_W0204(GPIO_W0204),.CONT_W0208(CONT_W0208),.Peripheral(Peripheral),.C0(C0),.C1(C1),.C2(C2),.Counter(Counter),.ram_addr(ram_addr),.data_ram_we(data_ram_we),.ram_data_out(ram_data_out),.ram_data_in(ram_data_in)
);

DSEGIO U5(.clk(IO_clk),.rst(rst),.EN(GPIO_W0204),.A0(DIVO[6]),
.map2up(DIVO[20]),.Test(SWO[7:5]),.LES(64'h0),.points({DIVO[31:0],DIVO[31:13],5'b0,8'h0}),
.Data0(Peripheral),
.data1({2'b00,PC[31:2]}),
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

Display U6(.clk(clk_100mhz),
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

Disp2Hex U61(.Scan2(SWO[1]),
.Scan10(DIVO[19:18]),
.flash(DIVO[25]),
.Text(SWO[0]),
.LES(LE),
.points(point),
.Hexs(Disp_num),
.AN(AN),
.SEGMENT(SEGMENT)
);

GPIO U7(.clk(IO_clk),
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

PIO U71 (.clk(IO_clk),
.rst(rst),
.EN(GPIO_W0200),
.Datai(Peripheral),
.LED(LED[7:0]),
.GPIOf0()
);

Counter U10 (.clk(clk_100mhz),
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

Clkdiv  U8 (.clk(clk_100mhz),
.rst(rst),
.STEP(SWO[2]),
.clkdiv(DIVO),
.nclk(nclk),
.CPUClk(CPUClk),
.nCPUClk(nCPUClk)
);

Arraykeys U9 (
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

EnterT32 M4(.clk(clk_100mhz),
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

VGA_TEST U11 (.clk(clk_100mhz),
.clk25(DIVO[1]),
.Debug_addr(Debug_addr),
.Debug_data(Debug_data),
.MEM_Addr(MEM_Addr),
.MEM_Data(MEM_Data),
.SWO14(SWO[14]),
.SWO13(SWO[13]),
.Red(Red),
.Green(Green),
.Blue(Blue),
.VSYNC(VSYNC),
.HSYNC(HSYNC)
);


endmodule

