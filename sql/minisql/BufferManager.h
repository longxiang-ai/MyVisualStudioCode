#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <string>
using namespace std;

// Buffer���ļ����д������С��λ, ��ҳ��С4KB
#define PAGESIZE 4096
// Buffer�������100
#define MAXBUFFERSIZE 100

// �������С��λ��, ��¼��ı�Ҫ��Ϣ
class Frame
{
    // BufferManager����Ϊ��Ԫ��, ���ڷ��ʺ��޸�Frame�еĳ�Ա����
    friend class BufferManager;
    public:
        // ���캯��, ������Clear()���
        Frame();
    private:
        // ��Buffer���д�����ļ���(·��)
        string file_name_;
        // �ļ��ж�Ӧ��ҳ���
        int page_id_;
        // ������ݵ�����
        char frame_content_[PAGESIZE];
        // Frame���ݱ���ס(��ֹ�滻)�ı��
        int pin_count_;
        // Frame���ݱ��ı�ı��
        bool dirty_;
        // ʱ���㷨��־λ
        bool referenced_;
        // Frame�Ƿ���õı��
        bool valid_;
        // ��յ�ǰFrame
        void Clear();
};

// �������ģ����, ʵ�ֻ��������ļ��Ĵ������
class BufferManager
{
    public:
        // Ĭ�Ϲ��캯��, ����Buffer Pool��СΪ���ֵ
        BufferManager();
        // ָ����С�Ĺ��캯��
        BufferManager(int buffer_size);
        // ��������, ��Ҫ��Buffer Pool��������д���ļ�
        ~BufferManager();
        // ��ȡ�ļ�������Buffer Pool�ж�Ӧ��Frame���, �����ڷ���-1
        int GetPageId(string file_name , int page_id);
        // ��ȡ�ļ���ָ��ҳ������, ������ָ�����ݵ�ָ��
        char* ReadPage(string file_name, int page_id);
        // ��ָ��Frame�е�����д���ļ��ж�Ӧ��λ��
        void FlushPage(string file_name, int page_id, int frame_id);
        // ����һ��Frame
        void PinPage(int frame_id);
        // ����һ��Frame
        void UnpinPage(int frame_id);
        // ���Frame�ı�
        void ModifyPage(int frame_id);
    private:
        // Buffer Pool�Ĵ洢�ռ�
        Frame* buffer_pool_;
        // Buffer Pool��С
        int buffer_size_;
        // ʱ�ӱ�, ����ʱ���㷨����Buffer Pool
        int clock_hand_;
        // ʹ��ʱ���㷨������ô洢�ռ�, ���ط���Ŀ���Frame���
        int AllocateFrame();
};

#endif