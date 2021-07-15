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

filePath = "D:\\课程文件\\vs-code\\python\\puwushiyaner\\image.jpg"
img=cv.imdecode(np.fromfile(filePath,dtype=np.uint8),-1)
print(img.shape)
img2 = Image.open('D:\\课程文件\\vs-code\\python\\puwushiyaner\\image.jpg')
img2 = img2.convert('L')
img2 = np.array(img2)

print(img2.shape)
# img = cv.imread("../testImages/4/img1.jpg", 0)
# 使用自己写的函数实现
equa = equalHist(img2)
# grayHist(img, equa)
# 使用OpenCV提供的直方图均衡化函数实现
# equa = cv.equalizeHist(img)
cv.imshow("img", img2)
cv.imshow("equa", equa)
cv.waitKey()



grayHist = calcGrayHist(img)
x = np.arange(256)
# 绘制灰度直方图
plt.plot(x, grayHist, 'r', linewidth=2, c='black')
plt.xlabel("gray Label")
plt.ylabel("number of pixels")
plt.show()


img3 = cv.resize(img2, None, fx=0.5, fy=0.5)
# 创建CLAHE对象
clahe = cv.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
# 限制对比度的自适应阈值均衡化
dst = clahe.apply(img2)
# 使用全局直方图均衡化
equa2 = cv.equalizeHist(img2)
# 分别显示原图，CLAHE，HE
cv.imshow("img", img2)
cv.imshow("dst", dst)
cv.imshow("equa", equa2)
cv.waitKey()
