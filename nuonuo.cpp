#include <easyx.h>
#include <iostream>
#include <conio.h>
#include "architechture.h"

bool ShowMap(const int& level,
              list<Enemy>& enemy_list,
              list<Bullet>& bullet_list,
              Player& player,
             const Position& base_position,
              vector<vector<int>>& map,
             const time_t& play_time) {
    //const int LENGTH = 30;  // 地图块边长
    ////BeginBatchDraw();
    //setbkcolor(BLACK);

    //// 画出地图
    //static int pcount = 0;
    //IMAGE* my=NULL;
    //IMAGE* en=NULL;
    //switch (player.direction_) {
    //case UP:
    //    my = &MyTankU;
    //    break;
    //case DOWN:
    //    my = &MyTankD;
    //    break;
    //case LEFT:
    //    my = &MyTankL;
    //    break;
    //case RIGHT:
    //    my = &MyTankR;
    //    break;
    //}
    //bool ok=(player.cur_position_ + DIRECTION[player.direction_]).Walkable(map);
    //int dx, dy;

    //for (int i = 1; i <= 30; ++i) {
    //    settextcolor(BLACK);
    //    settextstyle(20, 0, "黑体");
    //    char str[100];
    //    sprintf_s(str, "Level: %d", level);
    //    outtextxy(600, 50, str);
    //    sprintf_s(str, "Enemy: %d", enemy_list.size());
    //    outtextxy(600, 100, str);
    //    sprintf_s(str, "Time: %d", play_time);
    //    outtextxy(600, 200, str);
    //    sprintf_s(str, "Life: %d", player.hp_);
    //    outtextxy(600, 250, str);
    //    //FlushBatchDraw();

    //    cleardevice();
    //    for (int i = 0; i < map.size(); i++) {
    //        for (int j = 0; j < map[i].size(); j++) {
    //            if (map[j][i] == WALL) {
    //                putimage(i * LENGTH, j * LENGTH, &wall);
    //            }
    //            else if (map[j][i] == BASE) {
    //                putimage(i * LENGTH, j * LENGTH, &base);
    //            }
    //            else if (map[j][i] == GRASS) {
    //                putimage(i * LENGTH, j * LENGTH, &grass);
    //            }
    //        }
    //    }
    //    dx = DIRECTION[player.direction_].x_;
    //    dy = DIRECTION[player.direction_].y_;
    //    if(ok)
    //        putimage(player.cur_position_.y_ * LENGTH+(dy*i), player.cur_position_.x_ * LENGTH+(dx*i), my);
    //    else
    //        putimage(player.cur_position_.y_ * LENGTH , player.cur_position_.x_ * LENGTH, my);
    //    for (auto& e : enemy_list) {
    //        switch (e.direction_) {
    //        case UP:
    //            en = &EnemyTankU;
    //            break;
    //        case DOWN:
    //            en = &EnemyTankD;
    //            break;
    //        case LEFT:
    //            en = &EnemyTankL;
    //            break;
    //        case RIGHT:
    //            en = &EnemyTankR;
    //            break;
    //        default:
    //            en= &EnemyTankU;
    //            break;
    //        }
    //        dx = DIRECTION[e.direction_].x_;
    //        dy = DIRECTION[e.direction_].y_;
    //        if(pcount%2==0)putimage(e.cur_position_.y_ * LENGTH + (dy * i/2), e.cur_position_.x_ * LENGTH + (dx * i/2), en);
    //        else putimage(e.cur_position_.y_ * LENGTH + dy * ((i / 2)+15), e.cur_position_.x_ * LENGTH + dx * ((i / 2) + 15), en);
    //       
    //    }
    //    for (auto& b : bullet_list) {
    //        b.cur_position_ = b.cur_position_ + DIRECTION[b.direction_];
    //    }
    //    for (int t = 0; t <= 1; ++t) {
    //        for (auto& b : bullet_list) {

    //            dx = DIRECTION[b.direction_].x_;
    //            dy = DIRECTION[b.direction_].y_;
    //            if(!t)putimage(b.cur_position_.y_ * LENGTH + (dy * i), b.cur_position_.x_ * LENGTH + (dx * i), &Bullet_img);
    //            else putimage(b.cur_position_.y_ * LENGTH + (dy * (i+30)), b.cur_position_.x_ * LENGTH + (dx * (i + 30)), &Bullet_img);
    //        }
    //        int jd = JudgeBullets(map, player, base_position, bullet_list, enemy_list);//参数存在问题
    //        if (jd == 2)
    //        {
    //            ++pcount;
    //            SaveData(level, enemy_list, bullet_list, player, base_position, map, play_time);
    //            GameWin();
    //        
    //            return true;
    //        }
    //        else if (jd == 1)
    //        {
    //            ++pcount;
    //            GameLose();
    //            return true;
    //        }
    //        
    //    }
    //    

    //    FlushBatchDraw();
    //    //FlushBatchDraw();
    //    Sleep(10);
    //}
    //++pcount;
    //return false;
return true;
}

//void GameWin(const time_t& play_time) {
//    // 图片声明并加载
//    IMAGE GameWin;
//    loadimage(&GameWin, "./interface\\GameOver.jpg");
//    // 根据游戏用时生成胜利信息
//    char str[100];
//    sprintf_s(str, "You win", play_time);
//    // 按钮范围定义
//    typedef struct {
//        int x;
//        int y;
//    } coordinate;
//    typedef struct {
//        coordinate lu;
//        coordinate rd;
//    } Button;
//    Button select_level = {{200, 400}, {370, 450}};
//    Button exit_game = {{430, 400}, {600, 450}};
//    // 键盘输入定义
//    enum BUTTON { LEFT = 65, RIGHT = 68, SPACE = 32, ENTER = 13, ESC = 27 };
//    int flag = LEFT;
//    // 鼠标输入定义
//    ExMessage msg;
//    // 窗口设置
//    // 反复读取用户输入并作出相应的处理
//        BeginBatchDraw();
//        // 设置背景色并用背景色清屏
//        setbkcolor(WHITE);
//        cleardevice();
//        // 放置图片
//        putimage(0, 0, &GameWin);
//        // 设置所有文字的透明效果
//        setbkmode(TRANSPARENT);
//        // 设置胜利信息的颜色，大小，字体，位置，内容
//        settextcolor(WHITE);
//        settextstyle(60, 0, "黑体");
//        outtextxy(90, 310, str);
//        // 根据用户输入改变按钮的状态
//        if (flag == LEFT) {
//            setfillcolor(WHITE);  // 左边变白
//            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
//            setfillcolor(LIGHTGRAY);  // 右边变灰
//            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
//        } else if (flag == RIGHT) {
//            setfillcolor(LIGHTGRAY);  // 左边变灰
//            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
//            setfillcolor(WHITE);  // 右边变白
//            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
//        }
//        // 设置按钮信息的颜色，大小，字体，位置，内容
//        settextcolor(BLACK);
//        settextstyle(25, 0, "黑体");  // 大小和位置要根据字体和按钮的大小调整
//        outtextxy(205, 412, "SELECT_LEVEL");
//        outtextxy(470, 412, "TO_HOME");
//        EndBatchDraw();
//        while (1) {
//            if (_kbhit())return;
//        }
//        // 键盘输入处理
//        if (GetAsyncKeyState(LEFT)) {
//            flag = LEFT;
//        } else if (GetAsyncKeyState(RIGHT)) {
//            flag = RIGHT;
//        } else if (GetAsyncKeyState(SPACE) || GetAsyncKeyState(ENTER)) {
//            switch (flag) {
//                case LEFT:
//                    LevelSelect();
//                    break;
//                case RIGHT:
//                    MainMenu();
//                    break;
//            }
//            Sleep(300);
//        } else if (GetAsyncKeyState(ESC)) {
//            exit(0);
//        }
//        // 鼠标输入处理
//        //if (peekmessage(&msg, PM_REMOVE)) {
//        //    switch (msg.message) {
//        //        //case WM_LBUTTONDOWN:  // 鼠标左键按下
//        //        //    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
//        //        //        msg.y <= select_level.rd.y) {
//        //        //        flag = LEFT;
//        //        //    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
//        //        //               msg.y <= exit_game.rd.y) {
//        //        //        flag = RIGHT;
//        //        //    }
//        //        //    break;
//        //        case WM_LBUTTONDOWN:  // 双击鼠标左键
//        //            if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
//        //                msg.y <= select_level.rd.y) {
//        //              //  LevelSelect();
//        //            } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
//        //                       msg.y <= exit_game.rd.y) {
//        //             //   MainMenu();
//        //            }
//        //            break;
//        //    }
//        //}
//    
//}

//void GameLose() {
//    IMAGE GameLose;
//    loadimage(&GameLose, "./interface\\GameOver.jpg");
//    typedef struct {
//        int x;
//        int y;
//    } coordinate;
//    typedef struct {
//        coordinate lu;
//        coordinate rd;
//    } Button;
//    Button select_level = {{200, 400}, {370, 450}};
//    Button exit_game = {{430, 400}, {600, 450}};
//    enum BUTTON { LEFT = 65, RIGHT = 68, SPACE = 32, ENTER = 13, ESC = 27 };
//    int flag = LEFT;
//    ExMessage msg;
//    while (true) {
//        BeginBatchDraw();
//        setbkcolor(WHITE);
//        cleardevice();
//        putimage(0, 0, &GameLose);
//        setbkmode(TRANSPARENT);
//        settextcolor(RED);
//        settextstyle(60, 0, "黑体");
//        outtextxy(280, 310, "You lose!");
//        setfillcolor(RED);
//        setlinecolor(WHITE);
//        if (flag == LEFT) {
//            fillrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
//            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
//        } else if (flag == RIGHT) {
//            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
//            fillrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
//        }
//        settextcolor(WHITE);
//        settextstyle(25, 0, "黑体");
//        outtextxy(205, 412, "SELECT_LEVEL");
//        outtextxy(470, 412, "TO_HOME");
//        EndBatchDraw();
//        if (GetAsyncKeyState(LEFT)) {
//            flag = LEFT;
//        } else if (GetAsyncKeyState(RIGHT)) {
//            flag = RIGHT;
//        } else if (GetAsyncKeyState(SPACE) || GetAsyncKeyState(ENTER)) {
//            switch (flag) {
//                case LEFT:
//                    LevelSelect();
//                    break;
//                case RIGHT:
//                    MainMenu();
//                    break;
//            }
//            Sleep(300);
//        } else if (GetAsyncKeyState(ESC)) {
//            exit(0);
//        }
//        if (peekmessage(&msg, PM_REMOVE)) {
//            switch (msg.message) {
//                case WM_LBUTTONDOWN:
//                    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
//                        msg.y <= select_level.rd.y) {
//                        flag = LEFT;
//                    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
//                               msg.y <= exit_game.rd.y) {
//                        flag = RIGHT;
//                    }
//                    break;
//                case WM_LBUTTONDBLCLK:
//                    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
//                        msg.y <= select_level.rd.y) {
//                        LevelSelect();
//                    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
//                               msg.y <= exit_game.rd.y) {
//                        MainMenu();
//                    }
//                    break;
//            }
//        }
//    }
//}
