module VGA_TEST(
	input clk,
	input clk25,
//	input [9:0] PCol,                                      //改了变量名（建议与VGA文本模式统一，增加VGA外设。但修改问题太多，暂时恢复）
//	input [9:0] PRow,                                      //改了变量名
	input SWO14,                                           //存储数据翻页。2021 Modify :增加显示两帧ROM数据
	input SWO13,                                           //ROM、RAM切换
	input [31:0] Debug_data,
	input [31:0] MEM_Addr,                                 //2021 新增 ROM测试地址线
	input [31:0] MEM_Data,                                 //2021 新增 ROM 测试数据线
	
	output[3:0] Red,
    output[3:0] Green,
    output[3:0] Blue,
    output VSYNC,
    output HSYNC,

//	output reg [11:0]dout,
	output [6:0] Debug_addr);
	
reg [8*89-1:0] Headline="Zhejiang University Computer Organization Experimental SOC Test Environment (With RISC-V)";	
reg [31:0] data_buf [0:3];
reg [31:0] MEMBUF[0:255];            //存储器测试数据缓存：128单元，后继需要增加，并修改显示定位和格式
reg [7:0] ascii_code;
reg [8*7:0] strdata;
reg [11:0]dout;
wire pixel;
wire [9:0] PRow, PCol;

wire  [9:0] row_addr =  PRow - 10'd35;     // pixel ram row addr 
wire  [9:0] col_addr =  PCol- 10'd143;    // pixel ram col addr 

wire should_latch_debug_data = (PCol < 10'd143) && (PCol[2:0] == 3'b000) && (row_addr[3:0] == 4'b0000);

wire [4:0] char_index_row = row_addr[8:4] - 3;
wire [6:0] char_index_col = (PCol < 10'd143) ? 0 : (col_addr / 8 + 1);
wire [1:0] char_page = char_index_col / 20;
wire [4:0] char_index_in_page = char_index_col % 20;
//wire [2:0] char_index_in_reg_buf = 7 - (char_index_in_page - 9);               //没有使用   2021 Modify 注释掉
    
//    assign dout = pixel ? {4'b1111, {4{~Debug_addr[5]}}, {4{~Debug_addr[6]}}} : 12'b1100_0000_0000;         //Debug_addr[5]     12'b111111111111
reg flag;
    always @* begin                                                            // 2021 Modify 区域分色方便观察
       if(pixel)
        case(Debug_addr[6:5])
            2'b00:   dout = 12'b1111_1111_1111; 
            2'b01:   dout = 12'b0000_0000_1111; 
            2'b10:   dout = 12'b0000_1111_1111; 
            default: dout = 12'b0000_1111_1111; 
        endcase
      else if(row_addr[9:4] == 17 && col_addr[9:3] > 1 && col_addr[9:3] < 18)
                dout = 12'b1100_1100_1100;
           else dout = 12'b1000_0000_0000;
    end

assign Debug_addr = {char_index_row , PCol[4:3]};
wire[7:0] current_display_reg_addr = {1'b0, char_index_row, char_page};
reg[31:0] OPCODE;

    always @(negedge clk) begin                                     //2021 Modify ：ROM工作数据写入
        MEMBUF[{SWO13,MEM_Addr[8:2]}] <= MEM_Data;                  //SWO13=1缓存RAM,否则ROM
        if(Debug_addr==7'b0100001)OPCODE <= Debug_data;
        else OPCODE <= OPCODE;
    end
    
reg[19*8-1:0]INST_OP;
    wire[3*8-1:0] INST_rd ={"x", num2str({3'b000,OPCODE[11]}), num2str(OPCODE[10:7])};            
    wire[3*8-1:0] INST_rs1 ={"x", num2str({3'b000,OPCODE[19]}), num2str(OPCODE[18:15])};            
    wire[3*8-1:0] INST_rs2 ={"x", num2str({3'b000,OPCODE[24]}), num2str(OPCODE[23:20])};  
    wire[3*8-1:0] imm_12 ={num2str(OPCODE[31:28]), num2str(OPCODE[27:24]), num2str(OPCODE[23:20])};
    wire[3*8-1:0] Simm_12 ={num2str(OPCODE[31:28]), num2str({OPCODE[27:25],OPCODE[11]}), num2str(OPCODE[10:7])};
    
    wire[4*8-1:0] SBim_12 ={num2str(OPCODE[31]),num2str({ OPCODE[7],OPCODE[30:28]}), num2str({OPCODE[27:25],OPCODE[11]}), num2str({OPCODE[10:8],1'b0})};
    wire[6*8-1:0] UJim_20 ={num2str(OPCODE[31]),num2str(OPCODE[19:16]),num2str(OPCODE[15:12]),num2str({OPCODE[20],OPCODE[30:28]}), num2str(OPCODE[27:24]), num2str({OPCODE[23:21],1'b0})};
    wire[5*8-1:0] Uimm_20 ={num2str(OPCODE[31:28]),num2str(OPCODE[27:24]),num2str(OPCODE[23:20]), num2str(OPCODE[19:16]), num2str(OPCODE[15:12])};
    
    wire[13*8-1:0] R_Type = {" ", INST_rd,",", INST_rs1,",",INST_rs2, " "};          //3*3+2=11     1
    wire[13*8-1:0] I_Type = {" ", INST_rd,",", INST_rs1,",", imm_12, "H"};           //3*3+2=11      1
    wire[13*8-1:0] S_Type = {" ", INST_rs1,",", INST_rs2,",", Simm_12, "H"};         //3*3+2=11     1
    wire[13*8-1:0] SB_Type = {" ",INST_rs1,",", INST_rs2,",", SBim_12};             //2*3+4+2=12    0
    wire[13*8-1:0] UJ_Type = {" ",INST_rd,",", UJim_20, "H "};                       //3+6+1=10    1  
    wire[13*8-1:0] U_Type = {" ", INST_rd,",", Uimm_20, "H  "};                      //3+5+1=9    3
    
    always @* begin 
        case(OPCODE[6:2])                                    //OP
        5'b01100:begin
            case({OPCODE[14:12],OPCODE[30]})                     //fun3fun7[6]
                4'b0000: INST_OP = {" add",R_Type, "  "};
                4'b0001: INST_OP = {" sub",R_Type, "  "};
                4'b1110: INST_OP = {" and",R_Type, "  "};
                4'b1100: INST_OP = {" or",R_Type, "   "};
                4'b0100: INST_OP = {" slt",R_Type, "  "};
                4'b1010: INST_OP = {" srl",R_Type, "  "};
                4'b1000: INST_OP = {" xor",R_Type, "  "};
                default: INST_OP = "illegal instruction";                   //illegal instruction     
             endcase
        end
        5'b00000: INST_OP = {" lw",I_Type, "   "};
        5'b01000: INST_OP = {" sw",S_Type, "   "};
        5'b11000: INST_OP = {"beq",SB_Type, "   "};
        5'b11011: INST_OP = {"jal", UJ_Type, "  "};
        5'b01101: INST_OP = {"lui",U_Type, "  "}; // TODO:
        5'b11001: INST_OP = {"jalr",I_Type,"  "};
        5'b00100: begin 
        case(OPCODE[14:12])                                 //ALU(I): fun3
           3'b000: INST_OP = {"addi", I_Type, "  "};
           3'b111: INST_OP = {"andi", I_Type, "  "};
           3'b110: INST_OP = {"ori", I_Type, "  "};
           3'b010: INST_OP = {"slti", I_Type, "  "};
           3'b101: INST_OP = {"srli", I_Type, "  "};
           3'b100: INST_OP = {"xori", I_Type, "  "};
           default: INST_OP = "illegal instruction";                   //illegal instruction     
       endcase
            end 
        default:  INST_OP = "illegal instruction";                          //illegal instruction     
        endcase  
    end
    
    wire [31:0] MEMDATA = MEMBUF[{SWO13,1'b0,SWO14 + Debug_addr[5],Debug_addr[4:0]}];  //2021 Modify 显示ROM/RAM数据，没有读过的为0000_00000H。SWO14控制两帧，每帧32个字
   
always @(posedge clk) begin                                         //2021 Modify 
	if (should_latch_debug_data) begin
		if(Debug_addr[6]) data_buf[Debug_addr[1:0]] <= MEMDATA;   //屏幕下方显示ROM数据
		else data_buf[Debug_addr[1:0]] <= Debug_data; 
	end
end
always @(posedge clk) begin 
flag <=0;                                                    //2021 Modify：动态显示定位
	if ((row_addr < 1 * 16) || (row_addr >= 480 - 1 * 16)) 
         ascii_code <= " ";
    else if(row_addr[9:4] <= 2)
        ascii_code <= row_addr[9:4] == 1 ? (col_addr[9:3] > 13 && col_addr[9:3] < 68 ) ? Headline[(89 - col_addr[9:3] +13)*8 +:8] : " "
                                         : (col_addr[9:3] > 23 && col_addr[9:3] < 58 ) ? Headline[(34 - col_addr[9:3] +23)*8 +:8] : " "; 
        else begin
        if(row_addr[9:4] == 17 && col_addr[9:3] > 1 && col_addr[9:3] < 20)begin
           ascii_code <= INST_OP[(18 - col_addr[9:3] +2)*8 +:8] ;
           flag <= 1;
        end       
        else begin
            if (col_addr[2:0] == 3'b111) begin
                if ((char_index_in_page >= 2) && (char_index_in_page <= 8)) begin
                     ascii_code <= strdata[(6 - (char_index_in_page - 2)) * 8 +:8];
                end
               else if ((char_index_in_page >= 10) && (char_index_in_page <= 10 + 7)) begin
                     ascii_code <=  num2str(data_buf[char_page][(7 - (char_index_in_page - 10)) * 4  +: 4]);
                end else ascii_code <= " ";
            end
            else ascii_code <= ascii_code;         
        end
	end
end

    wire [8*5:0] MEMADDRSTR = SWO13 ? "RAM:0" : "CODE-";                                   //切换RAM/ROM地址显示标志
always @(posedge clk) begin                                                                 //2021 Modify ,后期还需要调整
		case (current_display_reg_addr[7:5])
			3'b000: //strdata <= {"REG-x", num2str(current_display_reg_addr[5:4]), num2str(current_display_reg_addr[3:0])};
			//begin strdata[23:0] <= {"x",num2str(current_display_reg_addr[5:4]), num2str(current_display_reg_addr[3:0])};
			       case (current_display_reg_addr[4:0])
			       0: strdata <= "x0:zero";
			       1: strdata <= "x01: ra";
			       2: strdata <= "x02: sp";
			       3: strdata <= "x03: gp";
			       4: strdata <= "x04: tp";
                   5: strdata <= "x05: t0";
                   6: strdata <= "x06: t1";
                   7: strdata <= "x07: t2";
 
 			       8: strdata <= "x8:fps0";
                   9: strdata <= "x09: s1";
                  10: strdata <= "x10: a0";
                  11: strdata <= "x11: a1";
                  12: strdata <= "x12: a2";
                  13: strdata <= "x13: a3";
                  14: strdata <= "x14: a4";
                  15: strdata <= "x15: a5";
                  16: strdata <= "x16: a6";
                  17: strdata <= "x17: a7";
                  
                  18: strdata <= "x18: s2";
                  19: strdata <= "x19: s3";
                  20: strdata <= "x20: s4";
                  21: strdata <= "x21: s5";
                  22: strdata <= "x22: s6";
                  23: strdata <= "x23: s7";
                  24: strdata <= "x24: s8";
                  25: strdata <= "x25: s9";
                  26: strdata <= "x26:s10";
                  27: strdata <= "x27:s11";
                  28: strdata <= "x28: t3";
                  29: strdata <= "x29: t4";
                  30: strdata <= "x30: t5";
                  31: strdata <= "x31: t6";
			       default: strdata <= "-------";
               endcase
//            end
			        
			3'b001: case (current_display_reg_addr[4:0])
				// datapath debug signals, MUST be compatible with 'debug_data_signal' in 'datapath.v'
				0: strdata <= "I-Point";
				1: strdata <= "I--CODE";
				2: strdata <= "Imm--12";
				3: strdata <= "UJim-20";
				
				4: strdata <= "rs1Addr";     
				5: strdata <= "rs1Data";    
				6: strdata <= "SImm-12";
				7: strdata <= "LUim-20";
				
				8: strdata <= "rs2Addr";
				9: strdata <= "rs2Data";
				10: strdata <= "SBim-12";
				11: strdata <= "W-R-AUC";      // control signal: WE、RegWrite、ALUC
				
				12: strdata <= "rd-Addr";   
				13: strdata <= "rd/W-Da";    
				14: strdata <= "MIO-CPU";   
				15: strdata <= "B/J-D2R";     // control signal: Branch、JUMP、DatatoReg   
				
				16: strdata <= "ALU-Ain";
				17: strdata <= "ALU-out";
				18: strdata <= "CPU-DAi";
				19: strdata <= "WB-Addr";
				
				20: strdata <= "ALU-Bin";
				21: strdata <= "CPUAddr";
				22: strdata <= "CPU-DAo";
				23: strdata <= "WB-DATA";
				
				24: strdata <= "-------";
				25: strdata <= "-------";
				26: strdata <= "-------";
				27: strdata <= "-------";

				default: strdata <= "RESERVE";
			endcase
			3'b010: strdata <= {MEMADDRSTR, num2str({SWO14 + current_display_reg_addr[5],current_display_reg_addr[4]}), num2str(current_display_reg_addr[3:0])};
			3'b011: strdata <= {MEMADDRSTR, num2str({SWO14 ,current_display_reg_addr[5]}+1'b1), num2str(current_display_reg_addr[3:0])};
//			3'b010: strdata <= {MEMADDRSTR, num2str({SWO14 + current_display_reg_addr[5],current_display_reg_addr[4]}), num2str(current_display_reg_addr[3:0])};

			default: strdata <= "RESERVE";
		endcase
end


FONT8_16 FONT_8X16 (                                //后续修改为标准字库
	.clk(clk),
	.ascii_code(ascii_code[6:0]),
	.row(row_addr[3:0]),
	.col(col_addr[2:0]),
	.row_of_pixels(pixel)
);

	function [7:0] num2str;
		input [3:0] number;
		begin
			if (number < 10)
				num2str = "0" + number;
			else
				num2str = "A" - 10 + number;
		end
	endfunction

        vga     U12(.clk(clk25),
                    .rst(1'b0),
                    .Din(dout),
                    .PCol(PCol),
                    .PRow(PRow),
                    .R(Red),
                    .G(Green),
                    .B(Blue),
                    .VS(VSYNC),
                    .HS(HSYNC)
                     );


endmodule
