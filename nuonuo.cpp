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
    const int LENGTH = 30;  // ��ͼ��߳�
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
    // ������ͼ
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == WALL) {
                putimage(i * LENGTH, j * LENGTH, &wall);
            } else if (map[i][j] == BASE) {
                putimage(i * LENGTH, j * LENGTH, &base);
            }
        }
    }
    // ������ҵ�̹��
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
    // �������˵�̹��
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
    // �����ӵ�
    for (auto bullet : bullet_list) {
        putimage(bullet.cur_position_.x_, bullet.cur_position_.y_, &Bullet);
    }
    // ��������
    putimage(base_position.x_ * LENGTH, base_position.y_ * LENGTH, &camp);
    // �Ҳ������Ϣ
    settextcolor(BLACK);
    settextstyle(20, 0, "����");
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
    // ͼƬ����������
    IMAGE GameWin;
    loadimage(&GameWin, "./interface\\GameOver.jpg");
    // ������Ϸ��ʱ����ʤ����Ϣ
    char str[100];
    sprintf(str, "You win in %d seconds!", play_time);
    // ��ť��Χ����
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
    // �������붨��
    enum BUTTON { LEFT = 65, RIGHT = 68, SPACE = 32, ENTER = 13, ESC = 27 };
    int flag = LEFT;
    // ������붨��
    ExMessage msg;
    // ��������
    initgraph(800, 600, EX_DBLCLKS);
    // ������ȡ�û����벢������Ӧ�Ĵ���
    while (true) {
        BeginBatchDraw();
        // ���ñ���ɫ���ñ���ɫ����
        setbkcolor(WHITE);
        cleardevice();
        // ����ͼƬ
        putimage(0, 0, &GameWin);
        // �����������ֵ�͸��Ч��
        setbkmode(TRANSPARENT);
        // ����ʤ����Ϣ����ɫ����С�����壬λ�ã�����
        settextcolor(WHITE);
        settextstyle(60, 0, "����");
        outtextxy(90, 310, str);
        // �����û�����ı䰴ť��״̬
        if (flag == LEFT) {
            setfillcolor(WHITE);  // ��߱��
            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
            setfillcolor(LIGHTGRAY);  // �ұ߱��
            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
        } else if (flag == RIGHT) {
            setfillcolor(LIGHTGRAY);  // ��߱��
            solidrectangle(select_level.lu.x, select_level.lu.y, select_level.rd.x, select_level.rd.y);
            setfillcolor(WHITE);  // �ұ߱��
            solidrectangle(exit_game.lu.x, exit_game.lu.y, exit_game.rd.x, exit_game.rd.y);
        }
        // ���ð�ť��Ϣ����ɫ����С�����壬λ�ã�����
        settextcolor(BLACK);
        settextstyle(25, 0, "����");  // ��С��λ��Ҫ��������Ͱ�ť�Ĵ�С����
        outtextxy(205, 412, "SELECT_LEVEL");
        outtextxy(470, 412, "TO_HOME");
        EndBatchDraw();
        // �������봦��
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
        // ������봦��
        if (peekmessage(&msg, PM_REMOVE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:  // ����������
                    if (msg.x >= select_level.lu.x && msg.x <= select_level.rd.x && msg.y >= select_level.lu.y &&
                        msg.y <= select_level.rd.y) {
                        flag = LEFT;
                    } else if (msg.x >= exit_game.lu.x && msg.x <= exit_game.rd.x && msg.y >= exit_game.lu.y &&
                               msg.y <= exit_game.rd.y) {
                        flag = RIGHT;
                    }
                    break;
                case WM_LBUTTONDBLCLK:  // ˫��������
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
        settextstyle(60, 0, "����");
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
        settextstyle(25, 0, "����");
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