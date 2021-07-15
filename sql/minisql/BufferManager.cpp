#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include "BufferManager.h"

Frame::Frame()
{
    Clear();
}

void Frame::Clear()
{
    file_name_ = "";
    page_id_ = -1;
    memset(frame_content_, '\0', sizeof(frame_content_));
    pin_count_ = -1;
    dirty_ = false;
    referenced_ = false;
    valid_ = true;
}

BufferManager::BufferManager()
{
    buffer_pool_ = new Frame[MAXBUFFERSIZE];
    buffer_size_ = MAXBUFFERSIZE;
    clock_hand_ = 0;  // 初始化时钟臂, 使其指向第0个Frame
}

BufferManager::BufferManager(int buffer_size)
{
    buffer_pool_ = new Frame[buffer_size];
    buffer_size_ = buffer_size;
    clock_hand_ = 0;
}

int BufferManager::GetPageId(string file_name , int page_id)
{
    int pos;
    for(pos = 0; pos < buffer_size_; pos++){
        if(buffer_pool_[pos].file_name_ == file_name && buffer_pool_[pos].page_id_ == page_id)
            return pos;
    }
    return -1;
}

char* BufferManager::ReadPage(string file_name, int page_id)
{
    fstream file;
    // 遍历Buffer Pool, 检查文件内容是否已经存在于某个Frame中
    int pos = GetPageId(file_name, page_id);
    // 文件内容不存在于Buffer Pool中, 调用AllocateFrame()函数分配一块可用的Frame
    // 将文件内容写入分配的Frame, 并设定Frame的各成员变量
    // 注意时钟算法使用的的referenced_在每次访问时均要设置为true
    if(pos == -1){
        pos = AllocateFrame();
        buffer_pool_[pos].file_name_ = file_name;
        buffer_pool_[pos].page_id_ = page_id;
        // buffer_pool_[pos].pin_count_ = 1;
        buffer_pool_[pos].pin_count_ = 0;
        buffer_pool_[pos].dirty_ = false;
        buffer_pool_[pos].referenced_ = true;
        buffer_pool_[pos].valid_ = false;
        file.open(file_name, ios::in | ios::binary);
        file.seekg(page_id * PAGESIZE);  // 文件中的page_id从0开始标号
        file.read(buffer_pool_[pos].frame_content_, PAGESIZE);
        file.close();
    }
    // 文件内容已存在于Buffer Pool中, 设置referenced_为true即可
    else{
        // buffer_pool_[pos].pin_count_++;
        buffer_pool_[pos].referenced_ = true;
    }
    return buffer_pool_[pos].frame_content_;
}

void BufferManager::FlushPage(string file_name, int page_id, int frame_id)
{
    fstream file;
    file.open(file_name, ios::in | ios::out | ios::binary);  // 以读写方式打开二进制文件, 避免写入内容覆盖
    file.seekp(page_id * PAGESIZE);
    file.write(buffer_pool_[frame_id].frame_content_, PAGESIZE);
    file.close();
}

BufferManager::~BufferManager()
{
    int i;
    // 遍历Buffer Pool, 将改变过的内容全部写回文件
    for(i = 0; i < buffer_size_; i++){
        if(buffer_pool_[i].dirty_ == true)
            FlushPage(buffer_pool_[i].file_name_, buffer_pool_[i].page_id_, i);
    }
}

int BufferManager::AllocateFrame()
{
    int i;
    // 遍历Buffer Pool, 如果存在空Frame, 直接返回该Frame的编号
    for(i = 0; i < buffer_size_; i++){
        if(buffer_pool_[i].valid_ == true)
            return i;
    }
    // Buffer Pool已满, 则使用时钟算法选取替换的Frame
    while(true){
        // referenced_位为true, 则该Frame不进行替换
        // 将该位设为false, 检查下一个Frame
        if(buffer_pool_[clock_hand_].referenced_ == true)
            buffer_pool_[clock_hand_].referenced_ = false;
        // referenced_位为false, 则进一步检查pin_count_
        // pin_count_为0表明该Frame未被锁定, 可以进行替换
        // 如替换Frame被修改过, 需将内容写回文件
        else if(buffer_pool_[clock_hand_].pin_count_ == 0){
            if(buffer_pool_[clock_hand_].dirty_ == true)
                FlushPage(buffer_pool_[clock_hand_].file_name_, buffer_pool_[clock_hand_].page_id_, clock_hand_);
            buffer_pool_[clock_hand_].Clear();
            return clock_hand_;
        }
        clock_hand_ = (clock_hand_ + 1) % buffer_size_;  // 时钟臂从0到buffer_size_ - 1循环
    }
}

void BufferManager::PinPage(int frame_id)
{
    // Frame非空才可进行锁定, 每次锁定将pin_count_ + 1
    if(buffer_pool_[frame_id].valid_ == false)
        buffer_pool_[frame_id].pin_count_++;
}

void BufferManager::UnpinPage(int frame_id)
{
    // 解锁时每次将pin_count_ - 1, 最多减小到0
    if(buffer_pool_[frame_id].valid_ == false && buffer_pool_[frame_id].pin_count_ > 0)
        buffer_pool_[frame_id].pin_count_--;
}

void BufferManager::ModifyPage(int frame_id)
{
    // Frame非空才可进行改变标记
    if(buffer_pool_[frame_id].valid_ == false)
        buffer_pool_[frame_id].dirty_ = true;
}