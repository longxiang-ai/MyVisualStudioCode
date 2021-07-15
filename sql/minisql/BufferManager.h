#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <string>
using namespace std;

// Buffer与文件进行传输的最小单位, 单页大小4KB
#define PAGESIZE 4096
// Buffer最大容量100
#define MAXBUFFERSIZE 100

// 缓冲块最小单位类, 记录块的必要信息
class Frame
{
    // BufferManager声明为友元类, 便于访问和修改Frame中的成员变量
    friend class BufferManager;
    public:
        // 构造函数, 仅调用Clear()清空
        Frame();
    private:
        // 与Buffer进行传输的文件名(路径)
        string file_name_;
        // 文件中对应的页编号
        int page_id_;
        // 存放数据的数组
        char frame_content_[PAGESIZE];
        // Frame内容被钉住(禁止替换)的标记
        int pin_count_;
        // Frame内容被改变的标记
        bool dirty_;
        // 时钟算法标志位
        bool referenced_;
        // Frame是否可用的标记
        bool valid_;
        // 清空当前Frame
        void Clear();
};

// 缓冲管理模块类, 实现缓冲区与文件的传输管理
class BufferManager
{
    public:
        // 默认构造函数, 设置Buffer Pool大小为最大值
        BufferManager();
        // 指定大小的构造函数
        BufferManager(int buffer_size);
        // 析构函数, 主要将Buffer Pool所有内容写回文件
        ~BufferManager();
        // 获取文件内容在Buffer Pool中对应的Frame编号, 不存在返回-1
        int GetPageId(string file_name , int page_id);
        // 读取文件中指定页的内容, 并返回指向内容的指针
        char* ReadPage(string file_name, int page_id);
        // 将指定Frame中的内容写回文件中对应的位置
        void FlushPage(string file_name, int page_id, int frame_id);
        // 锁定一个Frame
        void PinPage(int frame_id);
        // 解锁一个Frame
        void UnpinPage(int frame_id);
        // 标记Frame改变
        void ModifyPage(int frame_id);
    private:
        // Buffer Pool的存储空间
        Frame* buffer_pool_;
        // Buffer Pool大小
        int buffer_size_;
        // 时钟臂, 用于时钟算法遍历Buffer Pool
        int clock_hand_;
        // 使用时钟算法分配可用存储空间, 返回分配的可用Frame编号
        int AllocateFrame();
};

#endif