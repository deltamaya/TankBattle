#include <easyx.h>
#include <iostream>
#include "architechture.h"

void ShowMap(const int& level,
             const list<Enemy>& enemy_list,
             const list<Bullet>& bullet_list,
             const Player& player,
             const Position& base_position,
             const vector<vector<int>>& map,
             const time_t& play_time) {
    const int LENGTH = 30;  // 地图块边长
    IMAGE base;
    IMAGE wall;
    IMAGE grass;
    IMAGE camp;
    IMAGE MyTankU;
    IMAGE MyTankD;
    IMAGE MyTankL;
    IMAGE MyTankR;
    IMAGE EnemyTankU;
    IMAGE EnemyTankD;
    IMAGE EnemyTankL;
    IMAGE EnemyTankR;
    IMAGE Bullet;
    loadimage(&base, "./terrain\\base.jpg");
    loadimage(&wall, "./terrain\\wall.jpg");
    loadimage(&grass, "./terrain\\grassland.jpg");
    loadimage(&camp, "./terrain\\camp.jpg");
    loadimage(&MyTankU, "./tank\\MyTankU.jpg");
    loadimage(&MyTankD, "./tank\\MyTankD.jpg");
    loadimage(&MyTankL, "./tank\\MyTankL.jpg");
    loadimage(&MyTankR, "./tank\\MyTankR.jpg");
    loadimage(&EnemyTankU, "./tank\\EnemyTankU.jpg");
    loadimage(&EnemyTankD, "./tank\\EnemyTankD.jpg");
    loadimage(&EnemyTankL, "./tank\\EnemyTankL.jpg");
    loadimage(&EnemyTankR, "./tank\\EnemyTankR.jpg");
    loadimage(&Bullet, "./tank\\bullet.jpg");
    initgraph(800, 600);
    BeginBatchDraw();
    setbkcolor(BLACK);
    cleardevice();
    // 画出地图
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == WALL) {
                putimage(i * LENGTH, j * LENGTH, &wall);
            } else if (map[i][j] == BASE) {
                putimage(i * LENGTH, j * LENGTH, &base);
            }
        }
    }
    // 画出玩家的坦克
    switch (player.direction_) {
        case UP:
            putimage(player.cur_position_.x_ * LENGTH, player.cur_position_.y_ * LENGTH, &MyTankU);
            break;
        case DOWN:
            putimage(player.cur_position_.x_ * LENGTH, player.cur_position_.y_ * LENGTH, &MyTankD);
            break;
        case LEFT:
            putimage(player.cur_position_.x_ * LENGTH, player.cur_position_.y_ * LENGTH, &MyTankL);
            break;
        case RIGHT:
            putimage(player.cur_position_.x_ * LENGTH, player.cur_position_.y_ * LENGTH, &MyTankR);
            break;
    }
    // 画出敌人的坦克
    for (auto enemy : enemy_list) {
        switch (enemy.direction_) {
            case UP:
                putimage(enemy.cur_position_.x_ * LENGTH, enemy.cur_position_.y_ * LENGTH, &EnemyTankU);
                break;
            case DOWN:
                putimage(enemy.cur_position_.x_ * LENGTH, enemy.cur_position_.y_ * LENGTH, &EnemyTankD);
                break;
            case LEFT:
                putimage(enemy.cur_position_.x_ * LENGTH, enemy.cur_position_.y_ * LENGTH, &EnemyTankL);
                break;
            case RIGHT:
                putimage(enemy.cur_position_.x_ * LENGTH, enemy.cur_position_.y_ * LENGTH, &EnemyTankR);
                break;
        }
    }
    // 画出子弹
    for (auto bullet : bullet_list) {
        putimage(bullet.cur_position_.x_, bullet.cur_position_.y_, &Bullet);
    }
    // 画出基地
    putimage(base_position.x_ * LENGTH, base_position.y_ * LENGTH, &camp);
    // 右侧敌我信息
    settextcolor(BLACK);
    settextstyle(20, 0, "黑体");
    char str[100];
    sprintf(str, "Level: %d", level);
    outtextxy(600, 50, str);
    sprintf(str, "Enemy: %d", enemy_list.size());
    outtextxy(600, 100, str);
    sprintf(str, "Time: %d", play_time);
    outtextxy(600, 200, str);
    sprintf(str, "Life: %d", player.hp_);
    outtextxy(600, 250, str);
    EndBatchDraw();
    closegraph();
}

void GameWin(const time_t& play_time) {
    // 图片声明并加载
    IMAGE GameWin;
    loadimage(&GameWin, "./interface\\GameOver.jpg");
    // 根据游戏用时生成胜利信息
    char str[100];
    sprintf(str, "You win in %d seconds!", play_time);
    // 按钮范围定义
    typedef struct {
        int x;
        int y;
    } coordinate;
    typedef struct {
        coordinate lu;
        coordinate rd;
    } Button;
    Button select_level = {{200, 400}, {370, 450}};
    Button exit_game = {{430, 400}, {600, 450}};
    // 键盘输入定义
    enum BUTTON { LEFT = 65, RIGHT = 68, SPACE = 32, ENTER = 13, ESC = 27 };
    int flag = LEFT;
    // 鼠标输入定义
    ExMessage msg;
    // 窗口设置
    initgraph(800, 600, EX_DBLCLKS);
    // 反复读取用户输入并作出相应的处理
    while (true) {
        BeginBatchDraw();
        // 设置背景色并用背景色清屏
        setbkcolor(WHITE);
        cleardevice();
        // 放置图片
        putimage(0, 0, &GameWin);
        // 设置所有文字的透明效果
        setbkmode(TRANSPARENT);
        // 设置胜利信息的颜色，大小，字体，位置，内容
        settextcolor(WHITE);
        settextstyle(60, 0, "黑体");
        outtextxy(90, 310, str);
        // 根据用户输入改变按钮的状态
        if (flag == LEFT) {
            setfillcolor(WHITE);  // 左边变白
            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
            setfillcolor(LIGHTGRAY);  // 右边变灰
            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
        } else if (flag == RIGHT) {
            setfillcolor(LIGHTGRAY);  // 左边变灰
            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
            setfillcolor(WHITE);  // 右边变白
            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
        }
        // 设置按钮信息的颜色，大小，字体，位置，内容
        settextcolor(BLACK);
        settextstyle(25, 0, "黑体");  // 大小和位置要根据字体和按钮的大小调整
        outtextxy(205, 412, "SELECT_LEVEL");
        outtextxy(470, 412, "TO_HOME");
        EndBatchDraw();
        // 键盘输入处理
        if (GetAsyncKeyState(LEFT)) {
            flag = LEFT;
        } else if (GetAsyncKeyState(RIGHT)) {
            flag = RIGHT;
        } else if (GetAsyncKeyState(SPACE) || GetAsyncKeyState(ENTER)) {
            switch (flag) {
                case LEFT:
                    LevelSelect();
                    break;
                case RIGHT:
                    MainMenu();
                    break;
            }
            Sleep(300);
        } else if (GetAsyncKeyState(ESC)) {
            exit(0);
        }
        // 鼠标输入处理
        if (peekmessage(&msg, PM_REMOVE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:  // 鼠标左键按下
                    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
                        msg.y <= select_level.rd.y) {
                        flag = LEFT;
                    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
                               msg.y <= exit_game.rd.y) {
                        flag = RIGHT;
                    }
                    break;
                case WM_LBUTTONDBLCLK:  // 双击鼠标左键
                    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
                        msg.y <= select_level.rd.y) {
                        LevelSelect();
                    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
                               msg.y <= exit_game.rd.y) {
                        MainMenu();
                    }
                    break;
            }
        }
    }
}

void GameLose() {
    IMAGE GameLose;
    loadimage(&GameLose, "./interface\\GameOver.jpg");
    typedef struct {
        int x;
        int y;
    } coordinate;
    typedef struct {
        coordinate lu;
        coordinate rd;
    } Button;
    Button select_level = {{200, 400}, {370, 450}};
    Button exit_game = {{430, 400}, {600, 450}};
    enum BUTTON { LEFT = 65, RIGHT = 68, SPACE = 32, ENTER = 13, ESC = 27 };
    int flag = LEFT;
    ExMessage msg;
    initgraph(800, 600, EX_DBLCLKS);
    while (true) {
        BeginBatchDraw();
        setbkcolor(WHITE);
        cleardevice();
        putimage(0, 0, &GameLose);
        setbkmode(TRANSPARENT);
        settextcolor(RED);
        settextstyle(60, 0, "黑体");
        outtextxy(280, 310, "You lose!");
        setfillcolor(RED);
        setlinecolor(WHITE);
        if (flag == LEFT) {
            fillrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
        } else if (flag == RIGHT) {
            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
            fillrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
        }
        settextcolor(WHITE);
        settextstyle(25, 0, "黑体");
        outtextxy(205, 412, "SELECT_LEVEL");
        outtextxy(470, 412, "TO_HOME");
        EndBatchDraw();
        if (GetAsyncKeyState(LEFT)) {
            flag = LEFT;
        } else if (GetAsyncKeyState(RIGHT)) {
            flag = RIGHT;
        } else if (GetAsyncKeyState(SPACE) || GetAsyncKeyState(ENTER)) {
            switch (flag) {
                case LEFT:
                    LevelSelect();
                    break;
                case RIGHT:
                    MainMenu();
                    break;
            }
            Sleep(300);
        } else if (GetAsyncKeyState(ESC)) {
            exit(0);
        }
        if (peekmessage(&msg, PM_REMOVE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
                        msg.y <= select_level.rd.y) {
                        flag = LEFT;
                    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
                               msg.y <= exit_game.rd.y) {
                        flag = RIGHT;
                    }
                    break;
                case WM_LBUTTONDBLCLK:
                    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
                        msg.y <= select_level.rd.y) {
                        LevelSelect();
                    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
                               msg.y <= exit_game.rd.y) {
                        MainMenu();
                    }
                    break;
            }
        }
    }
}