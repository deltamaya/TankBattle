#include <conio.h>
#include "architechture.h"
#include "ui.h"
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
IMAGE Bullet_img;

extern ui TankBattle, menu, level, setting, developer, help, show, stop, win, lose;
void InitUI() {
    menu.AddImage("./interface\\MainInterface.jpg");
    menu.AddButton(302, 180, 180, 40, "开始游戏");
    menu.AddButton(330, 245, 120, 40, "设置");
    menu.AddButton(350, 310, 80, 40, "游戏说明");
    menu.AddButton(300, 370, 180, 40, "开发者界面");
    menu.AddButton(350, 434, 80, 40, "退出");
    // menu.AddButton(0, 120, 800, 120);
    level.AddImage("./interface\\SelectLevel.jpg");
    level.AddButton(40, 150, 150, 300, "Return");
    level.AddButton(230, 150, 150, 300);
    level.AddButton(420, 150, 150, 300);
    level.AddButton(610, 150, 150, 300);
    setting.AddImage("./interface\\SettingOn.jpg");
    setting.AddImage("./interface\\SettingOff.jpg");
    setting.AddButton(40, 150, 150, 300, "Return");
    setting.AddButton(230, 150, 150, 300, "OnSound");
    setting.AddButton(420, 150, 150, 300, "OffSound");
    developer.AddImage("./images\\nuonuo.png");
    developer.AddImage("./images\\maya.png");
    developer.AddImage("./images\\KONG.png");
    developer.AddImage("./images\\suixin.png");
    developer.AddImage("./images\\xingxuan.png");
    developer.AddImage("./images\\wangda.png");
    developer.AddImage("./images\\shengzhinuo.png");
    developer.AddImage("./images\\asd.png");
    developer.AddImage("./images\\chumengxian.png");
    developer.AddButton(128, 230, 100, 100);
    developer.AddButton(272, 230, 100, 100);
    developer.AddButton(422, 234, 100, 100);
    developer.AddButton(570, 235, 100, 100);
    developer.AddButton(129, 370, 100, 100);
    developer.AddButton(272, 374, 100, 100);
    developer.AddButton(423, 370, 100, 100);
    developer.AddButton(570, 370, 100, 100);
    developer.AddButton(0, 0, 128, 600);
    developer.AddButton(672, 0, 128, 600);
    developer.AddButton(0, 0, 800, 88);
    developer.AddButton(0, 510, 800, 90);
    help.AddImage("./images\\help.png");
    help.AddButton(0, 0, 800, 600);
    show.AddButton(600, 0, 199, 149);
    show.AddButton(600, 150, 199, 448);
    stop.AddButton(270, 270, 80, 60, "Continue");
    stop.AddButton(370, 270, 80, 60, "Setting");
    stop.AddButton(470, 270, 80, 60, "Exit");
    win.AddImage("./interface\\GameOver.jpg");
    win.AddButton(200, 400, 170, 50, "ToHome");
    win.AddButton(430, 400, 170, 50, "Exit");
    lose.AddImage("./interface\\GameOver.jpg");
    lose.AddButton(200, 400, 170, 50, "ToHome");
    lose.AddButton(430, 400, 170, 50, "Exit");
}

const vector<vector<int>> level_1 = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2},
    {2, 0, 0, 4, 1, 0, 0, 1, 4, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 0, 4, 1, 2, 2, 1, 4, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 0, 4, 1, 2, 2, 1, 4, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 2},
    {2, 0, 0, 4, 1, 0, 0, 1, 4, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 2}, 
    {2, 0, 0, 4, 1, 0, 0, 1, 4, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 4, 4, 4, 4, 4, 0, 0, 2},
    {2, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 4, 2, 2, 2, 4, 0, 0, 2}, 
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 4, 2, 2, 2, 4, 0, 0, 2}, 
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 4, 2, 2, 2, 4, 0, 0, 2},
    {2, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 2}, 
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 2}, 
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};

const vector<vector<int>> level_2 = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 2}, 
    {2, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 2},
    {2, 0, 1, 4, 1, 4, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2}, 
    {2, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2}, 
    {2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};

const vector<vector<int>> level_3 = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 1, 0, 0, 1, 0, 4, 2, 2, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 0, 4, 2, 2, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 0, 1, 4, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 2},
    {2, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 1, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2}, 
    {2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2},
    {2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, 
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};

void InitMap(const int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player, Position& base_position, vector<vector<int>>& map, time_t& play_time) {
    bullet_list.clear();
    enemy_list.clear();
    switch (level) {
        case 1: {
            map = level_1;
            player = {{1, 1}, UP};
            player.hp_ = 5;
            Enemy e1 = {enemy_list, {18, 18}, NONE};
            enemy_list.push_back(e1);
            Enemy e2 = {enemy_list, {16, 18}, NONE};
            enemy_list.push_back(e2);
            // Enemy e3 = { enemy_list,{10,4},RIGHT };
            // enemy_list.push_back(e3);
            base_position = {18, 14};
            cout << enemy_list.size() << endl;
            break;
        }
        case 2: {
            map = level_2;
            player = {{9, 5}, NONE};
            player.hp_ = 5;
            Enemy e1 = {enemy_list, {18, 5}, NONE};
            enemy_list.push_back(e1);
            Enemy e2 = {enemy_list, {14, 12}, NONE};
            enemy_list.push_back(e2);
            Enemy e3 = {enemy_list, {5, 14}, NONE};
            enemy_list.push_back(e3);
            base_position = {18, 14};
            cout << enemy_list.size() << endl;
            break;
        }
        case 3: {
            map = level_3;
            player = {{6, 9}, NONE};
            player.hp_ = 5;
            Enemy e1 = {enemy_list, {1, 1}, NONE};
            enemy_list.push_back(e1);
            Enemy e2 = {enemy_list, {1, 18}, NONE};
            enemy_list.push_back(e2);
            Enemy e3 = {enemy_list, {18, 1}, NONE};
            enemy_list.push_back(e3);
            Enemy e4 = {enemy_list, {18, 18}, NONE};
            enemy_list.push_back(e4);
            cout << enemy_list.size() << endl;
            break;
        }
        default:
            break;
    }
}
void Update(const int level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player, const Position& base_position, vector<vector<int>>& map, time_t& play_time) {
    static int ucount = 0;
    player.Move(map);
    cout << player.direction_ << endl;
    for (auto e_iter = enemy_list.begin(); e_iter != enemy_list.end(); ++e_iter) {
        if (ucount % 2 == 0) {
            e_iter->Move(map, player, base_position);
            e_iter->FireCheck(map, bullet_list, player, base_position);
        } else {
        }
    }
    ++ucount;

    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                player.direction_ = LEFT;
                break;
            case 's':
                player.direction_ = DOWN;
                break;
            case 'd':
                player.direction_ = RIGHT;
                break;
            case 'w':
                player.direction_ = UP;
                break;
            case ' ':
                auto b = player.Fire(bullet_list);
                bullet_list.push_back(b);
                break;
        }
    }
    cout << enemy_list.size() << ' ' << bullet_list.size() << endl;
}

vector<vector<int>> map = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int music_volume = 100, sound_volume = 100;
int main() {
    InitUI();
    initgraph(800, 600);
    list<Enemy> enemy_list;
    list<Bullet> bullet_list;
    Player player({0, 0}, UP);
    Position base_position;
    time_t play_time;
    int choice;
    int level;
    while (1) {
        setbkcolor(BLACK);
        cleardevice();
        // bool has_data = false;//ReadData(level, enemy_list, bullet_list, player, base_position, map, play_time);
        choice = MainMenu();

        switch (choice) {
            case 0:
                level = LevelSelect();
                if (!level)
                    break;
                InitMap(level, enemy_list, bullet_list, player, base_position, map, play_time);
                NewGame(level, enemy_list, bullet_list, player, base_position, map, play_time);
                break;
            case 1:
                Settings();
                break;
            case 2:
                Help();
                break;
            case 3:
                Developers();
                break;
            case 4:
                exit(0);
            default:
                break;
        }
    }
}