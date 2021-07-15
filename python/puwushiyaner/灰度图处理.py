import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import math

def calcGrayHist(I):
    # 计算灰度直方图
    h, w = I.shape[:2]
    grayHist = np.zeros([256], np.uint64)
    for i in range(h):
        for j in range(w):
            grayHist[I[i][j]] += 1
    return grayHist

def equalHist(img):
    # 灰度图像矩阵的高、宽
    h, w = img.shape
    # 第一步：计算灰度直方图
    grayHist = calcGrayHist(img)
    # 第二步：计算累加灰度直方图
    zeroCumuMoment = np.zeros([256], np.uint32)
    for p in range(256):
        if p == 0:
            zeroCumuMoment[p] = grayHist[0]
        else:
            zeroCumuMoment[p] = zeroCumuMoment[p - 1] + grayHist[p]
    # 第三步：根据累加灰度直方图得到输入灰度级和输出灰度级之间的映射关系
    outPut_q = np.zeros([256], np.uint8)
    cofficient = 256.0 / (h * w)
    for p in range(256):
        q = cofficient * float(zeroCumuMoment[p]) - 1
        if q >= 0:
            outPut_q[p] = math.floor(q)
        else:
            outPut_q[p] = 0
    # 第四步：得到直方图均衡化后的图像
    equalHistImage = np.zeros(img.shape, np.uint8)
    for i in range(h):
        for j in range(w):
            equalHistImage[i][j] = outPut_q[img[i][j]]
    return equalHistImage

for i in range (1,10):

    # file = f"image{i}"
    file = f"{i}"
    # img = Image.open('D:\\课程文件\\vs-code\\python\\puwushiyaner\\{}.jpg'.format(file))
    img = Image.open('D:\\qq\\1425507157\\FileRecv\\普物实验_视频处理1\视频2\\{}.png'.format(file))
    img = img.convert('L')
    img = np.array(img)

    print(img.shape)

    equa = equalHist(img)

    img3 = cv.resize(img, None, fx=0.5, fy=0.5)
    # 创建CLAHE对象
    clahe = cv.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
    # 限制对比度的自适应阈值均衡化
    dst = clahe.apply(img)
    # 使用全局直方图均衡化
    equa2 = cv.equalizeHist(img)
    # 分别显示原图，CLAHE，HE
    cv.imshow("img", img)
    cv.imshow("dst", dst)
    cv.imshow("equa", equa2)
    cv.waitKey()

    # path = "D:\\课程文件\\vs-code\\python\\puwushiyaner\\image2.jpg"
    # path =cv.imdecode(np.fromfile(path,dtype=np.uint8),-1)
    path  =  "D:\\huidutuchuli\\shx1.{}.jpg".format(file)
    cv.imwrite(path, dst)
