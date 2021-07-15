from math import *
from matplotlib import pyplot as plt # 用于预览生成的波形


WIDTH = 480
DEPTH = 640

hex_table = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
points = []
out = []

file = open("D:/ISE/COE/" + FILENAME, "w+")
file.write("memory_initialization_radix=16;\n") # 数据以16进制格式存储
file.write("memory_initialization_vector=")
base = 2**(WIDTH - 1) - 1

def BMPtoCOE (filepath):
    file = open (filepath,"w+")
    if file is None :
        print("ERROR,找不到图片")
    
    char bm[2];
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);
    BITMAPINFOHEADER head;
    fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
    int picwidth = head.biWidth, picheight = head.biHeight;
    short ind;
    fseek(fp, 0L, 0);
    fread(bm, 2, 1, fp);
    fseek(fp, 0x1CL, 0);
    fread(&ind, 2, 1, fp);
    if (bm[0] != 'B' || bm[1] != 'M' || ind != 32)
    {
        printf("该图片不是 32 位的位图\n");
        return 1;
    }
    if (picheight < 0)
        picheight = -picheight;
    fseek(fp, 0x36L, 0);
    printf("图片尺寸%d*%d\n", picwidth, picheight);
    int buf = (picwidth * 3 % 4) ? 4 - (picwidth * 3) % 4 : 0;
    char *tmp = (char *)malloc(sizeof(char) * buf);
    int i, j;
    unsigned char r, g, b, t;
    for (i = 0; i < picheight; i++)
        for (j = 0; j < picwidth; j++)
        {
            fread(&b, 1, 1, fp);
            fread(&g, 1, 1, fp);
            fread(&r, 1, 1, fp);
            fprintf(outfp, "%3x%x%x", (int)(b / 256.0 * 16), (int)(g / 256.0 * 16), (int)(r / 256.0 * 16));
            if (i == picheight - 1 && j == picwidth - 1 && isfinished)
                fprintf(outfp, ";");
            else
                fprintf(outfp, ",");
            carry2++;
            if (carry2 == 16)
                fprintf(outfp, "\n"), carry2 = 0;
            // 基于数字系统的飞机大战游戏设计
            // 54 / 55
            fread(&t, 1, 1, fp);
        }
    free(tmp);
    fclose(fp);
    return 0;
for i in range(DEPTH):

    # var = int(base + (-1 if i >= DEPTH // 2 else 1) * base) # 方波
    # var = int(base + sin(i / DEPTH * 2 * pi) * base) # 正弦波
    var = int(i / DEPTH * (2 ** WIDTH - 1)) # 锯齿波
    # var = int((1 - abs((i * 2 / (DEPTH - 1)) - 1)) * (2**WIDTH - 1))  # 三角波

    if var >= 2**WIDTH: # 抹平超出范围的数据
        var = 2**WIDTH - 1
    points.append(var)

    var_hex = ""
    while (var > 0):
        var_hex += hex_table[var & 0xf] # 取低4位并转换为16进制存入var_hex中
        var >>= 4 # 右移去掉已处理的4位
    var_hex += '0' * ((WIDTH - 1) // 4 - len(var_hex) + 1) # 根据WIDTH补零
    out.append(var_hex[::-1]) # 将var_hex中的内容翻转

for i in range(DEPTH):  # 逆序存入文件
    print(out[DEPTH - i - 1], end=" ")
    file.write(out[DEPTH - i - 1] + " ")

file.close()
plt.plot(points) # 用于预览生成的波形
plt.show() # 用于预览生成的波形