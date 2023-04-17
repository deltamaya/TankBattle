#pragma once
#include <easyx.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib, "winmm.lib")

namespace ui {

class music {
   private:
    char* path_;  // 音乐路径
    int volume_;  // 音乐大小

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

class image {     // 请把文字ps成图片，然后用这个类加载图片
    int x_, y_;   // 坐标
    IMAGE img;    // 图片
    char* path_;  // 图片路径

   public:
   // 接收图片路径，坐标，打印图片
    image(char* path, int x = 0, int y = 0)  // 文字颜色样式
        : path_(path), x_(x), y_(y) {
        loadimage(&img, path_);
        putimage(x_, y_, &img);
    };
};

class button {
   private:
    int x_, y_, w_, h_;    // 坐标和宽高
    char* text_;           // 文字
    int color_;            // 线条和字体颜色
    bool solid_;           // 是否为实心
    int full_color_;       // 实心颜色
    ExMessage msg;  // 消息

   public:
   // 接收坐标，宽高，文字，颜色，是否实心，实心颜色，打印按钮，空心按钮边框与文字颜色一致
    button(int x, int y, int w, int h, char* text = NULL, int color = WHITE, bool solid = 0,int full_color = RED)  // 文字颜色样式
        : x_(x), y_(y), w_(w), h_(h), text_(text), color_(color), solid_(solid) ,full_color_(full_color) {
        if (solid_) {
            setfillcolor(full_color_);                     // 填充颜色
            fillrectangle(x_, y_, x_ + w_, y_ + h_);  // 填充矩形
        } else {
            setlinecolor(color_);                 // 线条颜色
            rectangle(x_, y_, x_ + w_, y_ + h_);  // 画矩形
        }
        if (text_) {
            settextcolor(color_);                                  // 文字颜色
            settextstyle(20, 0, "黑体");                           // 文字样式
            outtextxy(x_ + w_ / 2 - 10, y_ + h_ / 2 - 10, text_);  // 输出文字
        }
    }
    // 检测鼠标是否点击了按钮
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