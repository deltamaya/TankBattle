#pragma once
#include <easyx.h>
#include <mmsystem.h>
#include <list>
#include <string>
#include <iostream>
#pragma comment(lib, "winmm.lib")
using std::cout;
using std::endl;

class image {
private:
    std::string path_;
    int x_, y_;
    IMAGE img_;
    
public:
    image(std::string path, int x = 0, int y = 0)
        : path_(path), x_(x), y_(y) {
        loadimage(&img_, path_.c_str());
    };
    void draw() { putimage(x_, y_, &img_); }
};

class button {
private:
    int x_, y_, w_, h_;
    std::string text_;
    int line_color_;
    bool solid_;
    int full_color_;

public:
    button(int x, int y, int w, int h, std::string text = "", int color = WHITE, bool solid = 0, int full_color = RED)
        : x_(x), y_(y), w_(w), h_(h), text_(text), line_color_(color), solid_(solid), full_color_(full_color) {}
    void draw() {
        if (solid_) {
            setfillcolor(full_color_);
            setlinecolor(line_color_);
            fillrectangle(x_, y_, x_ + w_, y_ + h_);
        }
        else {
            setlinecolor(line_color_);
            rectangle(x_, y_, x_ + w_, y_ + h_);
        }
        if (!(text_ == "")) {
            setbkmode(TRANSPARENT);
            settextcolor(line_color_);
            settextstyle(20, 0, "黑体");
            outtextxy(x_ + w_ / 2 - textwidth(text_.c_str()) / 2, y_ + h_ / 2 - textheight(text_.c_str()) / 2, text_.c_str());
        }
    }
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_w() const { return w_; }
    int get_h() const { return h_; }
};

class music {
   private:
    std::string path_;
    int volume_;

   public:
    music(std::string path, int volume = 100) : path_(path), volume_(volume) {
        std::string cmd = "open " + path_;
        mciSendString(cmd.c_str(), NULL, 0, NULL);
        set_volume(volume_);
    };
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
    ExMessage msg_;
    std::list<image> images_;
    std::list<button> buttons_;
    
public:
    void InitUI(std::string title, int width, int height) {
        initgraph(width, height);// EX_SHOWCONSOLE
        HWND hwnd = GetHWnd();
        SetWindowText(hwnd, title.c_str());
    };
    void begin() { BeginBatchDraw(); };
    void end() { EndBatchDraw(); };
    void clear() { cleardevice(); };
    image AddImage(std::string path, int x = 0, int y = 0) {
        image img(path, x, y);
        images_.push_back(img);
        return img;
    };
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
    button AddButton(int x, int y, int w, int h, std::string text = "", int line_color = WHITE, bool solid = 0, int full_color = RED) {
        button b(x, y, w, h, text, line_color, solid, full_color);
        buttons_.push_back(b);
        return b;
    };
    void PrintButton() {
        for (auto x : buttons_) {
            x.draw();
        }
    };
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

void Settings();
void ShowGameUI();
