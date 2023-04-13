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
    IMAGE base;
    IMAGE wall;
    IMAGE grass;
    IMAGE water;
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
    loadimage(&water, _T("./terrain\\water.jpg"));
    loadimage(&camp, _T("./terrain\\camp.jpg"));
    loadimage(&MyTankU, _T("./tank\\MyTankU.jpg"));
    loadimage(&MyTankD, _T("./tank\\MyTankD.jpg"));
    loadimage(&MyTankL, _T("./tank\\MyTankL.jpg"));
    loadimage(&MyTankR, _T("./tank\\MyTankR.jpg"));
    loadimage(&EnemyTankU, _T("./tank\\EnemyTankU.jpg"));
    loadimage(&EnemyTankD, _T("./tank\\EnemyTankD.jpg"));
    loadimage(&EnemyTankL, _T("./tank\\EnemyTankL.jpg"));
    loadimage(&EnemyTankR, _T("./tank\\EnemyTankR.jpg"));

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == WALL) {
                putimage(i * 30, j * 30, &wall);
            } else if (map[i][j] == BASE) {
                putimage(i * 30, j * 30, &base);
            }
        }
    }
    system("pause");
}