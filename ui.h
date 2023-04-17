#pragma once
#include <easyx.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib, "winmm.lib")

namespace ui {

class music {
   private:
    char* path_;  // ����·��
    int volume_;  // ���ִ�С

   public:
    music(char* path) : path_(path), volume_(1000) {
        std::string cmd = "open " + std::string(path_) + " alias " + std::string(path_);
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
    void play(bool loop = false) {
        std::string cmd = "play " + std::string(path_);
        if (loop)
            cmd += " repeat";
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
    void stop() {
        std::string cmd = "stop " + std::string(path_);
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
    void set_volume(int volume) {
        volume_ = volume;
        std::string cmd = "setaudio " + std::string(path_) + " volume to " + std::to_string(volume_);
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
    void close() {
        std::string cmd = "close " + std::string(path_);
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
};

class image {     // �������ps��ͼƬ��Ȼ������������ͼƬ
    int x_, y_;   // ����
    IMAGE img;    // ͼƬ
    char* path_;  // ͼƬ·��

   public:
   // ����ͼƬ·�������꣬��ӡͼƬ
    image(char* path, int x = 0, int y = 0)  // ������ɫ��ʽ
        : path_(path), x_(x), y_(y) {
        loadimage(&img, path_);
        putimage(x_, y_, &img);
    };
};

class button {
   private:
    int x_, y_, w_, h_;    // ����Ϳ��
    char* text_;           // ����
    int color_;            // ������������ɫ
    bool solid_;           // �Ƿ�Ϊʵ��
    int full_color_;       // ʵ����ɫ
    ExMessage msg;  // ��Ϣ

   public:
   // �������꣬��ߣ����֣���ɫ���Ƿ�ʵ�ģ�ʵ����ɫ����ӡ��ť�����İ�ť�߿���������ɫһ��
    button(int x, int y, int w, int h, char* text = NULL, int color = WHITE, bool solid = 0,int full_color = RED)  // ������ɫ��ʽ
        : x_(x), y_(y), w_(w), h_(h), text_(text), color_(color), solid_(solid) ,full_color_(full_color) {
        if (solid_) {
            setfillcolor(full_color_);                     // �����ɫ
            fillrectangle(x_, y_, x_ + w_, y_ + h_);  // ������
        } else {
            setlinecolor(color_);                 // ������ɫ
            rectangle(x_, y_, x_ + w_, y_ + h_);  // ������
        }
        if (text_) {
            settextcolor(color_);                                  // ������ɫ
            settextstyle(20, 0, "����");                           // ������ʽ
            outtextxy(x_ + w_ / 2 - 10, y_ + h_ / 2 - 10, text_);  // �������
        }
    }
    // �������Ƿ����˰�ť
    bool click() {
        if (peekmessage(&msg, PM_REMOVE)) {
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= x_ && msg.x <= x_ + w_ && msg.y >= y_ && msg.y <= y_ + h_) {
                    return true;
                }
            }
        }
        return false;
    }
};

}