import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import math
for i in range (16):

    file = f"image{i}"
    img = Image.open('D:\\课程文件\\vs-code\\python\\puwushiyaner\\{}.jpg'.format(file))
    cv.imshow("img", img)