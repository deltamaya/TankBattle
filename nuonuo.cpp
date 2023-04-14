#include <conio.h>
#include <easyx.h>
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
    IMAGE GameWin;
    loadimage(&GameWin, "./interface\\GameOver.jpg");
    initgraph(800, 600);
    enum Button { LEFT = 65, RIGHT = 68, SPACE = 32, ESC = 27 };
    int flag = LEFT;
    char str[100];
    sprintf(str, "You win in %d seconds", play_time);
    while (true) {
        BeginBatchDraw();
        setbkcolor(WHITE);
        cleardevice();
        putimage(0, 0, &GameWin);
        settextcolor(WHITE);
        settextstyle(60, 0, "黑体");
        setbkmode(TRANSPARENT);
        outtextxy(90, 310, str);
        settextcolor(BLACK);
        settextstyle(30, 0, "黑体");
        setbkmode(TRANSPARENT);
        if (flag == LEFT) {
            setfillcolor(WHITE);
            fillrectangle(200, 400, 370, 450);
            setfillcolor(LIGHTGRAY);
            solidrectangle(430, 400, 600, 450);
        } else if (flag == RIGHT) {
            setfillcolor(LIGHTGRAY);
            solidrectangle(200, 400, 370, 450);
            setfillcolor(WHITE);
            fillrectangle(430, 400, 600, 450);
        }
        outtextxy(205, 410, "SELECT_LEVEL");
        outtextxy(460, 410, "TO_HOME");
        EndBatchDraw();
        if (GetAsyncKeyState(LEFT)) {  // 更改选项
            flag = LEFT;
        } else if (GetAsyncKeyState(RIGHT)) {
            flag = RIGHT;
        } else if (GetAsyncKeyState(SPACE)) {
            switch (flag) {
                case LEFT:
                    LevelSelect();  // 进入选择关卡界面
                    break;
                case RIGHT:
                    MainMenu();  // 返回主界面
                    break;
            }
        } else if (GetAsyncKeyState(ESC)) {
            exit(0);
        }
    }
}

void GameLose() {
    // 准备绘图
    IMAGE GameOver;                                               // 定义一个图片变量
    loadimage(&GameOver, "./interface\\GameOver.jpg");            // 加载图片
    initgraph(800, 600);                                          // 初始化绘图窗口
    enum Button { LEFT = 65, RIGHT = 68, SPACE = 32, ESC = 27 };  // 定义按键枚举类型
    int flag = LEFT;                                              // 记录选择的按钮
    while (true) {
        // 设置背景
        BeginBatchDraw();           // 开始批量绘图
        setbkcolor(WHITE);          // 设置背景色为白色
        cleardevice();              // 清空绘图窗口
        putimage(0, 0, &GameOver);  // 将图片绘制到绘图窗口
        // 打印失败信息
        settextcolor(RED);
        settextstyle(60, 0, "黑体");
        setbkmode(TRANSPARENT);
        outtextxy(280, 310, "YOU LOSE!");
        // 画重新选关的按钮
        setfillcolor(RED);                    // 设置填充颜色为红色
        setlinecolor(RED);                    // 设置边框颜色为红色
        fillrectangle(200, 400, 370, 450);    // 画一个填充的矩形
        settextcolor(WHITE);                  // 设置字体颜色为白色
        settextstyle(30, 0, "黑体");          // 设置字体大小为30，字体为黑体
        outtextxy(205, 410, "SELECT_LEVEL");  // 在指定位置输出文字
        // 画退出游戏的按钮
        setfillcolor(RED);  // 同上
        setlinecolor(RED);
        fillrectangle(430, 400, 600, 450);
        settextcolor(WHITE);
        settextstyle(30, 0, "黑体");
        outtextxy(460, 410, "TO_HOME");
        // 选择按钮显示白色边框效果
        if (GetAsyncKeyState(LEFT)) {       // A键
            setlinecolor(WHITE);            // 设置边框颜色为白色
            rectangle(200, 400, 370, 450);  // 画一个默认的无边框矩形
            flag = LEFT;
        } else if (GetAsyncKeyState(RIGHT)) {  // D键
            setlinecolor(WHITE);
            rectangle(430, 400, 600, 450);
            flag = RIGHT;
        } else if (GetAsyncKeyState(ESC)) {
            exit(0);
        } else {
            switch (flag) {
                case LEFT:
                    setlinecolor(WHITE);
                    rectangle(200, 400, 370, 450);
                    break;
                case RIGHT:
                    setlinecolor(WHITE);
                    rectangle(430, 400, 600, 450);
                    break;
            }
        }
        if (GetAsyncKeyState(SPACE)) {  // 按下空格键进入其他界面
            switch (flag) {
                case LEFT:
                    LevelSelect();  // 进入选择关卡界面
                    break;
                case RIGHT:
                    MainMenu();  // 返回主界面
                    break;
            }
        }
        EndBatchDraw();  // 结束批量绘图
    }
}