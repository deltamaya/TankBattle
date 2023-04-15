#include"architechture.h"
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include<iostream>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
class Bullet;
class Enemy;
class Player;
class Position;
//using namespace std;

//+main.cpp�е�������ͼ
//�����ˣ�asd
//���ܣ���ʼ����ͼ��ʹ��level_x��ʼ��map,��ʼ������λ�ã����ˣ���ң�����ʱ��
//�������ؿ�id,���������ӵ�������ң�����λ�ã���ͼ������ʱ��
//����ֵ��void
void InitMap(const int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list,
	Player& player, Position& base_position, vector<vector<int>>& map, time_t& play_time)
{

}


vector<vector<int>> map = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2},
    {2, 0, 0, 4, 1, 0, 0, 1, 4, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 0, 4, 1, 2, 2, 1, 4, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 0, 4, 1, 2, 2, 1, 4, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 2},
    {2, 0, 0, 4, 1, 0, 0, 1, 4, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 2},
    {2, 0, 0, 4, 1, 0, 0, 1, 4, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 3, 0, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 3, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 4, 4, 4, 4, 4, 0, 0, 2},
    {2, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 4, 2, 2, 2, 4, 0, 0, 2},
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 4, 2, 2, 2, 4, 0, 0, 2},
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 4, 2, 2, 2, 4, 0, 0, 2},
    {2, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 2},
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};

vector<vector<int>> map2 = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2},
    {2, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 1, 4, 1, 4, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2},
    {2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};

vector<vector<int>> map1 = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 4, 2, 2, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 4, 2, 2, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2},
    {2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};


void InitMap()
{

    initgraph(600, 600, SHOWCONSOLE);

    /*
    */
    IMAGE img_wall, img_grass, img_home, img_wall_white;
    IMAGE img_tank_w, img_tank_a, img_tank_s, img_tank_d;
    int map_height = map.size();
    int map_width = map[0].size();
    loadimage(&img_home, "./Images/SparkleTank.ico", 30, 30);
    loadimage(&img_wall, "./Images/walls.gif", 30, 30);
    loadimage(&img_wall_white, "./Images/steel.gif", 30, 30);
    loadimage(&img_grass, "./Images/grass.jpg", 30, 30);
    loadimage(&img_tank_w, "./Images/tank/tank_green_w.gif", 30, 30);
    loadimage(&img_tank_a, "./Images/tank/tank_green_a.gif", 30, 30);
    loadimage(&img_tank_s, "./Images/tank/tank_green_s.gif", 30, 30);
    loadimage(&img_tank_d, "./Images/tank/tank_green_d.gif", 30, 30);

    /*
        ����map�����ͼ

    */
    // ̹�˵�λ�úͷ���
    int tank_x = 18;
    int tank_y = 3;
    char val = 'w';
    IMAGE tank = img_tank_w;
    while (true)
    {   
        BeginBatchDraw();
        cleardevice();
        for (int i = 0; i < map_height; i++)  // y ��
        {
            for (int j = 0; j < map_width; j++) // x ��
            {
                // ���زݵ�
                if (map1[i][j] == 4) 
                {
                    putimage(30 * j, 30 * i, &img_grass);
                }
                // ����ǽ��
                if (map1[i][j] == 2)
                {
                    putimage(30 * j, 30 * i, &img_wall_white);
                }
                // ����ǽ��
                else if (map1[i][j] == 1)
                {
                    putimage(30 * j, 30 * i, &img_wall);
                }
                // ���ػ���
                else if (map1[i][j] == 3)
                {
                    putimage(30 * j, 30 * i, &img_home);
                }
            }
        }
        putimage(30 * tank_x, 30 * tank_y, &tank);
        if (_kbhit())
        {
            val = _getch(); // ��ȡ�ַ�����
            if (val == 'w')
            {
                if (map[tank_y - 1][tank_x] == 0)
                {
                    int temp = map[tank_y][tank_x];
                    map[tank_y][tank_x] = 0;
                    tank_y -= 1;
                    map[tank_y][tank_x] = temp;
                }
                tank = img_tank_w;
                cout << val << endl;
            }
            else if (val == 'a')
            {
                if (map[tank_y][tank_x - 1] == 0)
                {
                    int temp = map[tank_y][tank_x];
                    map[tank_y][tank_x] = 0;
                    tank_x -= 1;
                    map[tank_y][tank_x] = temp;
                }
                tank = img_tank_a;
                cout << val << endl;
            }
            else if (val == 's')
            {
                if (map[tank_y + 1][tank_x] == 0)
                {
                    int temp = map[tank_y][tank_x];
                    map[tank_y][tank_x] = 0;
                    tank_y += 1;
                    map[tank_y][tank_x] = temp;
                }
                tank = img_tank_s;
                cout << val << endl;
            }
            else if (val == 'd')
            {
                if (map[tank_y][tank_x + 1] == 0)
                {
                    int temp = map[tank_y][tank_x];
                    map[tank_y][tank_x] = 0;
                    tank_x += 1;
                    map[tank_y][tank_x] = temp;
                }
                tank = img_tank_d;
                cout << val << endl;
            }
        }
        FlushBatchDraw();
    }
}

int main()
{
    InitMap();

    return 0;
}

