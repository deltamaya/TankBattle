#include <conio.h>
#include <easyx.h>
#include "ui.h"
#include "architechture.h"

extern ui TankBattle, menu, level, setting, developer, help, show, stop, win, lose;
void button(int x, int y, int width, int height, const char* text);
extern int music_volume, sound_volume;
void NewGame(const int level,
	list<Enemy>& enemy_list,
	list<Bullet>& bullet_list,
	Player& player,
	const Position& base_position,
	vector<vector<int>>& map, time_t& play_time)
{
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
    loadimage(&base, "./terrain\\base.jpg");
    loadimage(&wall, "./terrain\\wall.jpg");
    loadimage(&grass, "./terrain\\grass.jpg");
    loadimage(&camp, "./terrain\\camp.jpg");
    loadimage(&MyTankU, "./tank\\MyTankU.jpg");
    loadimage(&MyTankD, "./tank\\MyTankD.jpg");
    loadimage(&MyTankL, "./tank\\MyTankL.jpg");
    loadimage(&MyTankR, "./tank\\MyTankR.jpg");
    loadimage(&EnemyTankU, "./tank\\EnemyTankU.jpg");
    loadimage(&EnemyTankD, "./tank\\EnemyTankD.jpg");
    loadimage(&EnemyTankL, "./tank\\EnemyTankL.jpg");
    loadimage(&EnemyTankR, "./tank\\EnemyTankR.jpg");
    loadimage(&Bullet_img, "./tank\\bullet.jpg");
	BeginBatchDraw(); 
    string level_str = "Level: " + std::to_string(level);
    string enemy_num_str = "Enemy: " + std::to_string(enemy_list.size());
    string hp_str = "HP: " + std::to_string(player.hp_);
	int sl = 100, sr = 500, st = 100, sd = 500;
	while (1)
	{

       
        static int ucount = 0;
        
        cout << player.direction_ << endl;
        for (auto e_iter = enemy_list.begin(); e_iter != enemy_list.end(); ++e_iter) {
            if (ucount % 2 == 0) {
                e_iter->Move(map, player, base_position);
                e_iter->FireCheck(map, bullet_list, player, base_position);
            }
            else {


            }
            if(e_iter->fire_delay_>0)--e_iter->fire_delay_;

        }++ucount;
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
                
                if(player.fire_delay_==0)player.Fire(bullet_list);
                break;
            }

        }
        
        
        cout << enemy_list.size() << ' ' << bullet_list.size() << endl;
    
        
        
        


        //showmap
        const int LENGTH = 30; 
        setbkcolor(BLACK);

        // 画出地图
        static int pcount = 0;
        IMAGE* my = NULL;
        IMAGE* en = NULL;
        switch (player.direction_) {
        case UP:
            my = &MyTankU;
            break;
        case DOWN:
            my = &MyTankD;
            break;
        case LEFT:
            my = &MyTankL;
            break;
        case RIGHT:
            my = &MyTankR;
            break;
        default:
            my = &MyTankU;
            break;
        }
        bool ok = (player.cur_position_ + DIRECTION[player.direction_]).Walkable(map);
        int dx, dy;

        for (int i = 1; i <= 30; ++i) {
            
            cleardevice();
            level_str = "Level: " + std::to_string(level);
            enemy_num_str = "Enemy: " + std::to_string(enemy_list.size());
            hp_str = "HP: " + std::to_string(player.hp_);

            // ������Ϸ����

            // ������Ϸ�����
            show.PrintButton();
            settextcolor(WHITE);
            settextstyle(20, 0, "黑体");
            outtextxy(610, 50, level_str.c_str());
            outtextxy(610, 100, enemy_num_str.c_str());
            outtextxy(610, 250, hp_str.c_str());
            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (map[j][i] == WALL) {
                        putimage(i * LENGTH, j * LENGTH, &wall);
                    }
                    else if (map[j][i] == BASE) {
                        putimage(i * LENGTH, j * LENGTH, &base);
                    }
                    else if (map[j][i] == GRASS) {
                        putimage(i * LENGTH, j * LENGTH, &grass);
                    }
                }
            }
            if (i <= 10)
                for (auto& b : bullet_list) {

                    dx = DIRECTION[b.direction_].x_;
                    dy = DIRECTION[b.direction_].y_;
                    putimage(b.cur_position_.y_ * LENGTH + (dy * i * 3) + 10, b.cur_position_.x_ * LENGTH + (dx * i * 3) + 10, &Bullet_img);


                }
            else if (i <= 20) {
                for (auto& b : bullet_list) {

                    dx = DIRECTION[b.direction_].x_;
                    dy = DIRECTION[b.direction_].y_;
                    putimage(b.cur_position_.y_ * LENGTH + (dy * (i - 10) * 3) + 10, b.cur_position_.x_ * LENGTH + (dx * (i - 10) * 3) + 10, &Bullet_img);


                }
            }
            else {
                for (auto& b : bullet_list) {

                    dx = DIRECTION[b.direction_].x_;
                    dy = DIRECTION[b.direction_].y_;
                    putimage(b.cur_position_.y_ * LENGTH + (dy * (i - 20) * 3) + 10, b.cur_position_.x_ * LENGTH + (dx * (i - 20) * 3) + 10, &Bullet_img);


                }
            }
            if (i % 10 == 0) {

                for (auto& b : bullet_list)
                    b.cur_position_ = b.cur_position_ + DIRECTION[b.direction_];

                auto jd = JudgeBullets(map, player, base_position, bullet_list, enemy_list);
                if (jd == 2)
                {
                    ucount = 0;
                    pcount = 0;
                    GameWin();
                    goto end;
                }
                else if (jd == 1)
                {
                    ucount = 0;
                    pcount = 0;
                    GameLose();
                    goto end;
                }

            }
            dx = DIRECTION[player.direction_].x_;
            dy = DIRECTION[player.direction_].y_;
            if (ok)
                putimage(player.cur_position_.y_ * LENGTH + (dy * i), player.cur_position_.x_ * LENGTH + (dx * i), my);
            else
                putimage(player.cur_position_.y_ * LENGTH, player.cur_position_.x_ * LENGTH, my);
            for (auto& e : enemy_list) {
                switch (e.direction_) {
                case UP:
                    en = &EnemyTankU;
                    break;
                case DOWN:
                    en = &EnemyTankD;
                    break;
                case LEFT:
                    en = &EnemyTankL;
                    break;
                case RIGHT:
                    en = &EnemyTankR;
                    break;
                default:
                    en = &EnemyTankU;
                    break;
                }
                dx = DIRECTION[e.direction_].x_;
                dy = DIRECTION[e.direction_].y_;
                if (pcount % 2 == 0)putimage(e.cur_position_.y_ * LENGTH + (dy * i / 2), e.cur_position_.x_ * LENGTH + (dx * i / 2), en);
                else putimage(e.cur_position_.y_ * LENGTH + dy * ((i / 2) + 15), e.cur_position_.x_ * LENGTH + dx * ((i / 2) + 15), en);

            }
            

            FlushBatchDraw();
            Sleep(10);
        }
        player.Move(map);
        if (player.fire_delay_ > 0)--player.fire_delay_;
        ++pcount;
		//判断游戏是否结束
		
		//检测esc输入，进入暂停界面
        if (GetAsyncKeyState(VK_ESCAPE)) {
            ucount = 0;
            pcount = 0;
            GameLose();
            goto end;
        }
	}
end:
    EndBatchDraw();
}

void button(int x, int y, int width, int height, const char* text) {
	rectangle(x, y, x + width, y + height);
	int tw = textwidth(text); int th = textheight(text);
	int tx = x + width / 2 - tw / 2;
	int ty = y + height / 2 - th / 2;
	outtextxy(tx, ty, text);
}
