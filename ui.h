#pragma once
#include <easyx.h>
#include <mmsystem.h>
#include <list>
#include <string>
#pragma comment(lib, "winmm.lib")

void Settings();
void GameStop();
extern int flag_music_;

class image {
   private:
    std::string path_;  // 图片路径
    int x_, y_;         // 图片坐标
    IMAGE img_;         // 图片

   public:
    // 生成图片
    image(std::string path, int x = 0, int y = 0) : path_(path), x_(x), y_(y) { loadimage(&img_, path_.c_str()); };
    // 打印图片
    void draw() { putimage(x_, y_, &img_); }
};

class button {
   private:
    int x_, y_, w_, h_;  // 按钮坐标，宽度，高度
    std::string text_;   // 按钮文字
    int line_color_;     // 按钮及边框颜色
    bool solid_;         // 是否填充
    int full_color_;     // 填充颜色

   public:
    // 生成按钮
    button(int x, int y, int w, int h, std::string text = "", int color = WHITE, bool solid = 0, int full_color = RED)
        : x_(x), y_(y), w_(w), h_(h), text_(text), line_color_(color), solid_(solid), full_color_(full_color) {}
    // 打印按钮
    void draw() {
        if (solid_) {
            setfillcolor(full_color_);
            setlinecolor(line_color_);
            fillrectangle(x_, y_, x_ + w_, y_ + h_);
        } else {
            setlinecolor(line_color_);
            rectangle(x_, y_, x_ + w_, y_ + h_);
        }
        if (!(text_ == "")) {
            setbkmode(TRANSPARENT);
            settextcolor(line_color_);
            settextstyle(25, 0, "榛戜綋");
            outtextxy(x_ + w_ / 2 - textwidth(text_.c_str()) / 2, y_ + h_ / 2 - textheight(text_.c_str()) / 2, text_.c_str());
        }
    }
    // 获取按钮坐标，宽度，高度
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_w() const { return w_; }
    int get_h() const { return h_; }
};

class music {
   private:
    std::string path_;  // 音乐路径
    int volume_;        // 音量

   public:
    music(std::string path, int volume = 100) : path_(path), volume_(volume) {
        std::string cmd = "open " + path_;
        mciSendString(cmd.c_str(), NULL, 0, NULL);
        set_volume(volume_);
    };
    // 参数loop表示是否循环播放
    void play(bool loop = false) {
        std::string cmd = "play " + path_;
        if (loop)
            cmd += " repeat";
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
    void stop() {
        std::string cmd = "stop " + path_;
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
    // 这个函数是错的，不要用
    void set_volume(int volume) {
        volume_ = volume;
        std::string cmd = "setaudio " + path_ + " volume to " + std::to_string(volume_);
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
    void close() {
        std::string cmd = "close " + path_;
        mciSendString(cmd.c_str(), NULL, 0, NULL);
    };
};

class ui {
   private:
    ExMessage msg_;              // 用于获取鼠标消息
    std::list<image> images_;    // 用于存储图片
    std::list<button> buttons_;  // 用于存储按钮

   public:
    // 初始化窗口
    void InitUI(std::string title, int width, int height) {
        initgraph(width, height);
        HWND hwnd = GetHWnd();
        SetWindowText(hwnd, title.c_str());
    };
    // EasyX的一些函数
    void begin() { BeginBatchDraw(); };
    void end() { EndBatchDraw(); };
    void clear() { cleardevice(); };
    // 添加图片
    image AddImage(std::string path, int x = 0, int y = 0) {
        image img(path, x, y);
        images_.push_back(img);
        return img;
    };
    // 打印图片
    void PrintImage(int index = 0) {
        int i = 0;
        for (auto x : images_) {
            if (i == index) {
                x.draw();
                break;
            }
            i++;
        }
    };
    // 添加按钮
    button AddButton(int x, int y, int w, int h, std::string text = "", int line_color = WHITE, bool solid = 0, int full_color = RED) {
        button b(x, y, w, h, text, line_color, solid, full_color);
        buttons_.push_back(b);
        return b;
    };
    // 打印按钮
    void PrintButton() {
        for (auto x : buttons_) {
            x.draw();
        }
    };
    // 检查按钮是否被按下,返回按钮下标
    int CheckButton() {
        if (peekmessage(&msg_, PM_REMOVE)) {
            if (msg_.message == WM_LBUTTONDOWN) {
                int i = 0;
                for (auto x : buttons_) {
                    if (msg_.x >= x.get_x() && msg_.x <= x.get_x() + x.get_w() && msg_.y >= x.get_y() && msg_.y <= x.get_y() + x.get_h()) {
                        return i;
                    }
                    i++;
                }
            }
        }
        return -1;
    };
};

class click {  // 点击音效
   public:
    music click_;
    click() : click_("./music\\click.wav", 1000){};
    void play() {
        click_.play();
        click_.close();
        if (flag_music_) {
            click_.play();
        }
    }
};

class GameBegin {  // 游戏开始音效
   public:
    music begin_;
    GameBegin() : begin_("./music\\GameBegin.mp3", 1000){};
    void play() {
        begin_.play();
        begin_.close();
        if (flag_music_) {
            begin_.play();
        }
    }
};

class GameEnd {  // 游戏结束音效
   public:
    music end_;
    GameEnd() : end_("./music\\GameOver.mp3", 1000){};
    void play() {
        end_.play();
        end_.close();
        if (flag_music_) {
            end_.play();
        }
    }
};

class OpenFire {  // 开火音效
   public:
    music fire_;
    OpenFire() : fire_("./music\\OpenFire.mp3", 1000){};
    void play() {
        fire_.play();
        fire_.close();
        if (flag_music_) {
            fire_.play();
        }
    }
};