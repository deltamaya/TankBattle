#include "ui.h"
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include "ui.h"
#include "architechture.h"
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
void InitMap(const int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player,
	Position& base_position, vector<vector<int>>& map, time_t& play_time)
{

	bullet_list.clear();
	enemy_list.clear();
	switch (level)
	{
	case 1: {
		map = level_1;
		player = { {1,1},UP};
		player.hp_ = 10;
		Enemy e1 = { enemy_list,{18,18},NONE };
		enemy_list.push_back(e1);
		Enemy e2 = { enemy_list,{16,18},NONE };
		enemy_list.push_back(e2);
		//Enemy e3 = { enemy_list,{10,4},RIGHT };
		//enemy_list.push_back(e3);
		base_position = { 18,14 };
		cout << enemy_list.size() << endl;
		break; 
	}
	case 2:
	{
		map = level_2;
	player = { {9,5},NONE };
	player.hp_ = 5;
	Enemy e1 = { enemy_list,{18,5},NONE };
	enemy_list.push_back(e1);
	Enemy e2 = { enemy_list,{14,12},NONE };
	enemy_list.push_back(e2);
	Enemy e3 = { enemy_list,{5,14},NONE };
	enemy_list.push_back(e3);
	base_position = { 18,14 };
	cout << enemy_list.size() << endl;
	break;

	}
	case 3:
	{
		map = level_3;
		player = { {6,9},NONE };
		player.hp_ = 5;
		Enemy e1 = { enemy_list,{1,1},NONE };
		enemy_list.push_back(e1);
		Enemy e2 = { enemy_list,{1,18},NONE };
		enemy_list.push_back(e2);
		Enemy e3 = { enemy_list,{18,1},NONE };
		enemy_list.push_back(e3);
		Enemy e4 = { enemy_list,{18,18},NONE };
		enemy_list.push_back(e4);
		cout << enemy_list.size() << endl;
		break;
	}
	default:
		break;
	}
}
void Update(const int level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player,
	const Position& base_position, vector<vector<int>>& map, time_t& play_time)
{
	static int ucount = 0;
	player.Move(map);
	cout << player.direction_ << endl;
	for (auto e_iter = enemy_list.begin(); e_iter != enemy_list.end(); ++e_iter) {
		if (ucount % 2 == 0) {
			e_iter->Move(map, player, base_position);
			e_iter->FireCheck(map, bullet_list, player, base_position);
		}
		else {
			

		}
		
		
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
			auto b=player.Fire(bullet_list);
			bullet_list.push_back(b);
			break;
		}

	}
	cout << enemy_list.size() << ' ' << bullet_list.size() << endl;

}



vector<vector<int>>map = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
extern ui TankBattle, menu, level, setting, developer, help, show, stop, win, lose;
//音乐音量，音效音量
int music_volume = 100, sound_volume = 100;
int main() {
	menu.AddImage("./interface\\MainInterface.jpg");
	menu.AddButton(340, 240, 120, 40, "GameStart");
	menu.AddButton(340, 280, 120, 40, "Setting");
	menu.AddButton(340, 320, 120, 40, "Help");
	menu.AddButton(340, 360, 120, 40, "Developer");
	menu.AddButton(340, 400, 120, 40, "Exit");
	level.AddButton(40, 150, 150, 300, "Return");
	level.AddButton(230, 150, 150, 300, "Level_1");
	level.AddButton(420, 150, 150, 300, "Level_2");
	level.AddButton(610, 150, 150, 300, "Level_3");
	setting.AddButton(40, 150, 150, 300, "Return");
	setting.AddButton(230, 150, 150, 300, "OnSound");
	setting.AddButton(420, 150, 150, 300, "OffSound");
	developer.AddImage("./images\\developer.png");
	developer.AddButton(0, 0, 800, 600);
	help.AddImage("./images\\help.png");
	help.AddButton(0, 0, 800, 600);
	show.AddButton(600, 0, 200, 150);
	show.AddButton(600, 150, 200, 450);
	stop.AddButton(170, 270, 80, 60, "Continue");
	stop.AddButton(370, 270, 80, 60, "Setting");
	stop.AddButton(470, 270, 80, 60, "Exit");
	win.AddImage("./interface\\GameOver.jpg");
	win.AddButton(200, 400, 170, 50, "ToHome");
	win.AddButton(430, 400, 170, 50, "Exit");
	lose.AddImage("./interface\\GameOver.jpg");
	lose.AddButton(200, 400, 170, 50, "ToHome");
	lose.AddButton(430, 400, 170, 50, "Exit");
	initgraph(800, 600);
	//包含游戏中所有敌对单位的链表
	list<Enemy>enemy_list;
	//包含游戏中所有子弹的链表
	list<Bullet>bullet_list;
	//玩家
	Player player({ 0,0 }, UP);
	//基地位置
	Position base_position;
	//游玩时间
	time_t play_time;
	//主界面的玩家选择
	int choice;
	//关卡
	int level;
	while (1) {
		//是否存在有效存档
		setbkcolor(BLACK);
		cleardevice();
		//bool has_data = false;//ReadData(level, enemy_list, bullet_list, player, base_position, map, play_time);
		choice = MainMenu();
		
		switch (choice)
		{
		case 0:
			level = LevelSelect();
			if (!level)break;
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
