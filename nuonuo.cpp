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
        settextstyle(60, 0, "����");
        setbkmode(TRANSPARENT);
        outtextxy(90, 310, str);
        settextcolor(BLACK);
        settextstyle(30, 0, "����");
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
        if (GetAsyncKeyState(LEFT)) {  // ����ѡ��
            flag = LEFT;
        } else if (GetAsyncKeyState(RIGHT)) {
            flag = RIGHT;
        } else if (GetAsyncKeyState(SPACE)) {
            switch (flag) {
                case LEFT:
                    LevelSelect();  // ����ѡ��ؿ�����
                    break;
                case RIGHT:
                    MainMenu();  // ����������
                    break;
            }
        } else if (GetAsyncKeyState(ESC)) {
            exit(0);
        }
    }
}

void GameLose() {
    // ׼����ͼ
    IMAGE GameOver;                                               // ����һ��ͼƬ����
    loadimage(&GameOver, "./interface\\GameOver.jpg");            // ����ͼƬ
    initgraph(800, 600);                                          // ��ʼ����ͼ����
    enum Button { LEFT = 65, RIGHT = 68, SPACE = 32, ESC = 27 };  // ���尴��ö������
    int flag = LEFT;                                              // ��¼ѡ��İ�ť
    while (true) {
        // ���ñ���
        BeginBatchDraw();           // ��ʼ������ͼ
        setbkcolor(WHITE);          // ���ñ���ɫΪ��ɫ
        cleardevice();              // ��ջ�ͼ����
        putimage(0, 0, &GameOver);  // ��ͼƬ���Ƶ���ͼ����
        // ��ӡʧ����Ϣ
        settextcolor(RED);
        settextstyle(60, 0, "����");
        setbkmode(TRANSPARENT);
        outtextxy(280, 310, "YOU LOSE!");
        // ������ѡ�صİ�ť
        setfillcolor(RED);                    // ���������ɫΪ��ɫ
        setlinecolor(RED);                    // ���ñ߿���ɫΪ��ɫ
        fillrectangle(200, 400, 370, 450);    // ��һ�����ľ���
        settextcolor(WHITE);                  // ����������ɫΪ��ɫ
        settextstyle(30, 0, "����");          // ���������СΪ30������Ϊ����
        outtextxy(205, 410, "SELECT_LEVEL");  // ��ָ��λ���������
        // ���˳���Ϸ�İ�ť
        setfillcolor(RED);  // ͬ��
        setlinecolor(RED);
        fillrectangle(430, 400, 600, 450);
        settextcolor(WHITE);
        settextstyle(30, 0, "����");
        outtextxy(460, 410, "TO_HOME");
        // ѡ��ť��ʾ��ɫ�߿�Ч��
        if (GetAsyncKeyState(LEFT)) {       // A��
            setlinecolor(WHITE);            // ���ñ߿���ɫΪ��ɫ
            rectangle(200, 400, 370, 450);  // ��һ��Ĭ�ϵ��ޱ߿����
            flag = LEFT;
        } else if (GetAsyncKeyState(RIGHT)) {  // D��
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
        if (GetAsyncKeyState(SPACE)) {  // ���¿ո��������������
            switch (flag) {
                case LEFT:
                    LevelSelect();  // ����ѡ��ؿ�����
                    break;
                case RIGHT:
                    MainMenu();  // ����������
                    break;
            }
        }
        EndBatchDraw();  // ����������ͼ
    }
}