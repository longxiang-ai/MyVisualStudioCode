j initial 		     # 0
add zero, zero, zero # 4
add zero, zero, zero # 8
add zero, zero, zero # C
add zero, zero, zero # 10
add zero, zero, zero # 14
add zero, zero, zero # 18
add zero, zero, zero # 1C
initial:
addi x5,x5,8
addi x6,x6,1
addi x7,x7,1
addi x10,x10,1
sw x0, 0(x5)    # Code-03 = 0
lw x7, 0(x0) 	# x7 = Code-00
lui x3, 0xff000 # r3=FF000000
lui x4, 0xabcde # r4=ABCDE000
lui x9, 0x11111 # r8=11111000
addi x5,x0,1    # x5 = 1
slt x6, x0, x5          #x6 = 1
slti x6,x6, 2   # x6 = 0x 0000 0100
slti x6,x6, -2  # x6 = 1
addi x6,x6,2    # x6 = 3
xori x6, x0, 1			#x6 = 1
andi x7, x0, 0          #x7 = 0
addi x8, x0, 5          #x8 = 5
testbranch:
add x7, x7, x6         #x7++
beq x7, x8, test2
sub x28, x7, x6       #x28 
addi x14, x28, 2      #x14 
addi x14, x28, -2     #x29
sltu x14, x7, x8
slti x14, x7, -2
slt x14, x6, x7
bne x0, x0, testbranch
sltiu x14, x6, 12    
and x28, x28, x14
or x28, x7, x6
srl x28, x7, x6
xor x28, x0, x7
xori x14, x0, 12
srli x14, x14, 2
ori x14, x7, 23
andi x14, x7, 128
lui x14, 0x1234  
blt x0, x14, testbranch

test2:
jal x0, start
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
start:
lw x5, 12(x0)
sltu x6, x0, x5 #test sltu
add x7, x6, x6
add x28, x7, x6
add x14, x7, x7
add x5, x28, x28
add x5, x5, x5
add x29, x5, x28
add x30, x29, x29
add x30, x30, x30
add x8, x30, x28
add x30, x30, x30
add x30, x30, x30
add x31, x30, x29
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x30, x30, x30
add x9, x30, x30
or x12, x9, x30
add x18, x9, x9
add x5, x18, x18
add x5, x5, x5
loop:
sub x13, x0, x6
sw x12, 4(x9)
lw x11, 0(x9)
add x11, x11, x11
add x11, x11, x11
sw x11, 0(x9)
add x21, x21, x6
sw x21 0(x18)
lw x22 20(x0)
loop2:
lw x11, 0(x9)
add x11, x11, x11
add x11, x11, x11
sw x11, 0(x9)
lw x11 0(x9)
and x24, x11, x5
add x22, x22, x6
beq x22, x0, C_init
l_next:
lw x11, 0(x9)
add x23, x14, x14
add x25, x23, x23
add x23, x23, x25
and x24, x11, x23
beq x24, x0, L00
beq x24, x23, L11
add x23, x14, x14
beq x24, x23, L01
sw x21, 0(x18)
jal x0, loop2
L00:
beq x15, x13, L4
jal x0, L3
L4:
add x15, x13, x13
L3:
sw x15, 0(x18)
jal x0, loop2
L11:
lw x21, 96(x19)
sw x21, 0(x18)
jal x0, loop2
L01:
lw x21, 32(x19)
sw x21, 0(x18)
jal x0, loop2
C_init:
lw x22, 20(x0)
add x15, x15, x15
or x15, x15, x6
add x19, x19, x14
and x19, x19, x8
add x21, x21, x6
beq x21, x13, L6
jal x0, L7
L6:
add x21, x0, x14
add x21, x21, x6
L7:
lw x11, 0(x9)
add x24, x11, x11
add x24, x24, x24
sw x24, 0(x9)
sw x12, 4(x9)
jal x0, l_next