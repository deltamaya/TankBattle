#pragma once
#include <easyx.h>
#include <list>
#include <string>

class image {
   private:
    int x_, y_;
    IMAGE img_;
    std::string path_;

   public:
    image(std::string path, int x = 0, int y = 0)  // 文字颜色样式
        : path_(path), x_(x), y_(y) {
        loadimage(&img_, path_.c_str());
        putimage(x_, y_, &img_);
    };
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
        : x_(x), y_(y), w_(w), h_(h), text_(text), line_color_(color), solid_(solid), full_color_(full_color) {
        if (solid_) {
            setfillcolor(full_color_);                // 填充颜色
            setlinecolor(line_color_);                // 线条颜色
            fillrectangle(x_, y_, x_ + w_, y_ + h_);  // 填充矩形
        } else {
            setlinecolor(line_color_);            // 线条颜色
            rectangle(x_, y_, x_ + w_, y_ + h_);  // 画矩形
        }
        if (!(text_ == "")) {
            setbkmode(TRANSPARENT);
            settextcolor(line_color_);    // 文字颜色
            settextstyle(20, 0, "黑体");  // 文字样式
            outtextxy(x_ + w_ / 2 - textwidth(text_.c_str()) / 2, y_ + h_ / 2 - textheight(text_.c_str()) / 2, text_.c_str());
        }
    }
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_w() const { return w_; }
    int get_h() const { return h_; }
};

class ui {
   private:
    ExMessage msg_;              // 消息
    std::list<button> buttons_;  // 按钮列表
   public:
    // 创建一个界面
    void InitUI(std::string title, int width, int height) {
        initgraph(width, height);  // EX_SHOWCONSOLE
        HWND hwnd = GetHWnd();
        SetWindowText(hwnd, title.c_str());
    };
    // 开始绘图
    void begin() { BeginBatchDraw(); };
    // 结束绘图
    void end() { EndBatchDraw(); };
    // 用背景色清空界面
    void clear() { cleardevice(); };
    // 创建一个按钮
    button add_button(int x, int y, int w, int h, std::string text = "", int line_color = WHITE, bool solid = 0, int full_color = RED) {
        button b(x, y, w, h, text, line_color, solid, full_color);
        buttons_.push_back(b);
        return b;
    };
    // 检测按钮列表中是否有按钮被点击，返回被点击的按钮的下标
    int check_button() {
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
    // 创建一个图片
    image add_image(std::string path, int x = 0, int y = 0) { return image(path, x, y); };
};