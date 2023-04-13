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
    initgraph(800, 600);
    setbkcolor(WHITE);
    cleardevice();
    const int WIDTH = 30;
    const int HEIGHT = 30;
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
    loadimage(&base, _T("./terrain\\base.jpg"));
    loadimage(&wall, _T("./terrain\\wall.jpg"));
    loadimage(&grass, _T("./terrain\\grassland.jpg"));
    loadimage(&camp, _T("./terrain\\camp.jpg"));
    loadimage(&MyTankU, _T("./tank\\MyTankU.jpg"));
    loadimage(&MyTankD, _T("./tank\\MyTankD.jpg"));
    loadimage(&MyTankL, _T("./tank\\MyTankL.jpg"));
    loadimage(&MyTankR, _T("./tank\\MyTankR.jpg"));
    loadimage(&EnemyTankU, _T("./tank\\EnemyTankU.jpg"));
    loadimage(&EnemyTankD, _T("./tank\\EnemyTankD.jpg"));
    loadimage(&EnemyTankL, _T("./tank\\EnemyTankL.jpg"));
    loadimage(&EnemyTankR, _T("./tank\\EnemyTankR.jpg"));
    while (1) {
        BeginBatchDraw();
        setbkcolor(BLACK);
        cleardevice();
        // ������ͼ
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] == WALL) {
                    putimage(i * 30, j * 30, &wall);
                } else if (map[i][j] == BASE) {
                    putimage(i * 30, j * 30, &base);
                }
            }
        }
        setlinecolor(BLACK);
        rectangle(0, 0, WIDTH, HEIGHT);
        // ������ҵ�̹��
        switch (player.direction_) {
            case UP:
                putimage(player.cur_position_.x_ * 30, player.cur_position_.y_ * 30, &MyTankU);
                break;
            case DOWN:
                putimage(player.cur_position_.x_ * 30, player.cur_position_.y_ * 30, &MyTankD);
                break;
            case LEFT:
                putimage(player.cur_position_.x_ * 30, player.cur_position_.y_ * 30, &MyTankL);
                break;
            case RIGHT:
                putimage(player.cur_position_.x_ * 30, player.cur_position_.y_ * 30, &MyTankR);
                break;
        }
        // �������˵�̹��
        for (auto enemy : enemy_list) {
            switch (enemy.direction_) {
                case UP:
                    putimage(enemy.cur_position_.x_ * 30, enemy.cur_position_.y_ * 30, &EnemyTankU);
                    break;
                case DOWN:
                    putimage(enemy.cur_position_.x_ * 30, enemy.cur_position_.y_ * 30, &EnemyTankD);
                    break;
                case LEFT:
                    putimage(enemy.cur_position_.x_ * 30, enemy.cur_position_.y_ * 30, &EnemyTankL);
                    break;
                case RIGHT:
                    putimage(enemy.cur_position_.x_ * 30, enemy.cur_position_.y_ * 30, &EnemyTankR);
                    break;
            }
        }
        // �����ӵ�
        for (auto bullet : bullet_list) {
            setfillcolor(BLACK);
            solidcircle(bullet.cur_position_.x_ * 30 + 15, bullet.cur_position_.y_ * 30 + 15, 3);
        }
        // ��������
        putimage(base_position.x_ * 30, base_position.y_ * 30, &camp);
        /**/
        // �Ҳ������Ϣ
        settextcolor(BLACK);
        settextstyle(20, 0, _T("����"));
        char str[100];
        sprintf(str, "Level: %d", level);
        outtextxy(600, 50, str);  // ��ʾ��ǰ�ؿ�
        sprintf(str, "Enemy: %d", enemy_list.size());
        outtextxy(600, 100, str);  // ��ʾ��ǰ��������
        sprintf(str, "Time: %d", play_time);
        outtextxy(600, 200, str);  // ��ʾ��ǰ��Ϸʱ��
        sprintf(str, "Life: %d", player.hp_);
        outtextxy(600, 250, str);  // ��ʾ��ǰѪ��
        * /
            // �����ҷ�̹���ƶ�
            if (GetAsyncKeyState(VK_UP)) {
            player.direction_ = UP;
        }
        else if (GetAsyncKeyState(VK_DOWN)) {
            player.direction_ = DOWN;
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            player.direction_ = LEFT;
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            player.direction_ = RIGHT;
        }

        EndBatchDraw();
    }
    system("pause");
    closegraph();
}