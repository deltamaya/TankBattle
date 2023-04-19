
#pragma once
#include <easyx.h>
#include <list>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
class image {
private:
    std::string path_;
    int x_, y_;
    IMAGE img_;

public:
    image(std::string path, int x = 0, int y = 0)  // ������ɫ��ʽ
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
            setfillcolor(full_color_);                // �����ɫ
            setlinecolor(line_color_);                // ������ɫ
            fillrectangle(x_, y_, x_ + w_, y_ + h_);  // ������
        }
        else {
            setlinecolor(line_color_);            // ������ɫ
            rectangle(x_, y_, x_ + w_, y_ + h_);  // ������
        }
        if (!(text_ == "")) {
            setbkmode(TRANSPARENT);
            settextcolor(line_color_);    // ������ɫ
            settextstyle(20, 0, "����");  // ������ʽ
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
    ExMessage msg_;              // ��Ϣ
    std::list<button> buttons_;  // ��ť�б�
    std::list<image> images_;    // ͼƬ�б�
public:
    // ����һ������
    void InitUI(std::string title, int width, int height) {
        initgraph(width, height, EX_SHOWCONSOLE);  // EX_SHOWCONSOLE
        HWND hwnd = GetHWnd();
        SetWindowText(hwnd, title.c_str());
    };
    // ��ʼ��ͼ
    void begin() { BeginBatchDraw(); };
    // ������ͼ
    void end() { EndBatchDraw(); };
    // �ñ���ɫ��ս���
    void clear() { cleardevice(); };
    // ����һ��ͼƬ
    image AddImage(std::string path, int x = 0, int y = 0) {
        image img(path, x, y);
        images_.push_back(img);
        return img;
    };
    // ��ӡ�ض���ͼƬ
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
    // ����һ����ť
    button AddButton(int x, int y, int w, int h, std::string text = "", int line_color = WHITE, bool solid = 0, int full_color = RED) {
        button b(x, y, w, h, text, line_color, solid, full_color);
        buttons_.push_back(b);
        return b;
    };
    // ��ӡ��ť
    void PrintButton() {
        for (auto x : buttons_) {
            x.draw();
        }
    };
    // ��ⰴť�б����Ƿ��а�ť����������ر�����İ�ť���±�
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