from matplotlib import pyplot as plt  # 展示图片
import numpy as np  # 数值处理
import cv2  # opencv库
from sklearn.linear_model import LinearRegression, Ridge, Lasso  # 回归分析

def noise_mask_image(img, noise_ratio=[0.8,0.4,0.6]):
    """
    根据题目要求生成受损图片
    :param img: cv2 读取图片,而且通道数顺序为 RGB
    :param noise_ratio: 噪声比率，类型是 List,，内容:[r 上的噪声比率,g 上的噪声比率,b 上的噪声比率]
                        默认值分别是 [0.8,0.4,0.6]
    :return: noise_img 受损图片, 图像矩阵值 0-1 之间，数据类型为 np.array,
             数据类型对象 (dtype): np.double, 图像形状:(height,width,channel),通道(channel) 顺序为RGB
    """
    # 受损图片初始化
    noise_img = None
    # -------------实现受损图像答题区域-----------------
    noise_img = np.copy(img)

    Red = np.random.random((noise_img.shape[0],noise_img.shape[1]))
    Green = np.random.random((noise_img.shape[0],noise_img.shape[1]))
    Blue = np.random.random((noise_img.shape[0],noise_img.shape[1]))

    for i in range(noise_img.shape[0]):
        for j in range (noise_img.shape[1]):
            if Red[i][j]< noise_ratio[0]:
                Red[i][j]=0
            else:
                Red[i][j]=1
            if Green[i][j]< noise_ratio[1]:
                Green[i][j]=0
            else:
                Green[i][j]=1
            if Blue[i][j]< noise_ratio[2]:
                Blue[i][j]=0
            else:
                Blue[i][j]=1

    noise_img[:,:,0] = noise_img[:,:,0] * Red
    noise_img[:,:,1] = noise_img[:,:,1] * Green
    noise_img[:,:,2] = noise_img[:,:,2] * Blue

    # -----------------------------------------------

    return noise_img


def get_noise_mask(noise_img):
    """
    获取噪声图像，一般为 np.array
    :param noise_img: 带有噪声的图片
    :return: 噪声图像矩阵
    """
    # 将图片数据矩阵只包含 0和1,如果不能等于 0 则就是 1。
    return np.array(noise_img != 0, dtype='double')

def restore_image(noise_img, size=4):
    """
    使用 你最擅长的算法模型 进行图像恢复。
    :param noise_img: 一个受损的图像
    :param size: 输入区域半径，长宽是以 size*size 方形区域获取区域, 默认是 4
    :return: res_img 恢复后的图片，图像矩阵值 0-1 之间，数据类型为 np.array,
            数据类型对象 (dtype): np.double, 图像形状:(height,width,channel), 通道(channel) 顺序为RGB
    """
    # 恢复图片初始化，首先 copy 受损图片，然后预测噪声点的坐标后作为返回值。
    res_img = np.copy(noise_img)

    # 获取噪声图像
    noise_mask = get_noise_mask(noise_img)

    # -------------实现图像恢复代码答题区域----------------------------
    
    # 在边缘补0
    r = size //2
    red_img = np.pad(res_img[:, :, 0], (r, r),
                     'constant', constant_values=(0, 0))
    green_img = np.pad(res_img[:, :, 1], (r, r),
                       'constant', constant_values=(0, 0))
    blue_img = np.pad(res_img[:, :, 2], (r, r),
                      'constant', constant_values=(0, 0))

    def Re(i, j, size, img):
        matrix = img[i-r:i+r+1,j-r:j+r+1]
        # print(matrix)
        points = []
        for i_temp in range (matrix.shape[0]):
            for j_temp in range (matrix.shape[1]):
                if matrix[i_temp,j_temp]!=0:
                    points.append([i_temp,j_temp,matrix[i_temp,j_temp]])
        # print(points)
        points = np.array(points)
        # print(points)
        if len(points) > 0:
            X = points[:,:-1]
            # print(X)
            # x1 = x[:,0]
            # x2 = x[:,-1]
            Y = points[:,-1]
            regr = LinearRegression()
            regr.fit(X,Y)
            x_test = np.array([[r+1,r+1]])
            y_test = regr.predict(x_test)
            if y_test <0 :
                y_test = 0
            elif y_test >1 :
                y_test = 1
            img [i,j] = y_test
            # print(img[i,j])
        

    for i in range(r, res_img.shape[0]+r):
        for j in range(r, res_img.shape[1]+r):
            Re(i, j, size, red_img)
            Re(i, j, size, green_img)
            Re(i, j, size, blue_img)
    
    
    for i in range(res_img.shape[0]):
        for j in range(res_img.shape[1]):
            res_img[i, j, 0] = red_img[i+r, j+r]
            res_img[i, j, 1] = green_img[i+r, j+r]
            res_img[i, j, 2] = blue_img[i+r, j+r]
    
    # ---------------------------------------------------------------

    return res_img




    # 原始图片
# 加载图片的路径和名称
# img_path = 'samples/forest.png'
img_path = 'samples/mona_lisa.png'
# img_path = 'samples/potala_palace.png'
# img_path = 'samples/xihu.png'
# img_path = 'samples/the_school_of_athens.png'
# img_path = 'A.png'
# 读取原始图片
img = read_image(img_path)

# 展示原始图片
plot_image(image=img, image_title="original image")

# 生成受损图片
# 图像数据归一化
nor_img = normalization(img)

# 每个通道数不同的噪声比率
noise_ratio = [0.4, 0.6, 0.8]

# 生成受损图片
noise_img = noise_mask_image(nor_img, noise_ratio)

if noise_img is not None:
    # 展示受损图片
    plot_image(image=noise_img, image_title="the noise_ratio = %s of original image"%noise_ratio)

    # 恢复图片
    res_img = restore_image(noise_img)
    
    # 计算恢复图片与原始图片的误差
    print("恢复图片与原始图片的评估误差: ", compute_error(res_img, nor_img))
    print("恢复图片与原始图片的 SSIM 相似度: ", calc_ssim(res_img, nor_img))
    print("恢复图片与原始图片的 Cosine 相似度: ", calc_csim(res_img, nor_img))

    # 展示恢复图片
    plot_image(image=res_img, image_title="restore image")

    # 保存恢复图片
    save_image('res_' + img_path, res_img)
else:
    # 未生成受损图片
    print("返回值是 None, 请生成受损图片并返回!")