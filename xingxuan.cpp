#include "architechture.h"
#include <fstream>
#include <graphics.h>
#include <conio.h>

void SaveData(const int level, const list<Enemy>& enemy_list, const list<Bullet>& bullet_list, const Player& player, const Position& base_position, const vector<vector<int>>& map, const time_t& play_time)
{
	ofstream outFile("Data.txt");
	//保存关卡的数据
	outFile << level << endl;
	//保存敌方坦克链表的数据
	//坦克的的数据按照类的成员依次进行保存，每个坦克保存为一行
	for (auto iter = enemy_list.begin(); iter != enemy_list.end(); ++iter) {
		outFile << iter->cur_position_.x_ << " " << iter->cur_position_.y_ << " " << static_cast<int>(iter->direction_) << " " << iter->hp_ << " " << iter->fire_delay_ << " " << iter->target_ << endl;
	}//static_cast<int>(iter->direction_ ):把枚举值转化为对应的整数值保存到文件里
	outFile << 1000 << endl;//100用于表示敌方坦克链表的数据已经保存完毕

	//保存子弹链表的数据
	for (auto iter = bullet_list.begin(); iter != bullet_list.end(); ++iter) {
		outFile << iter->cur_position_.x_ << " " << iter->cur_position_.y_ << " " << static_cast<int>(iter->direction_) << " " << iter->friendly_ << endl;
	}
	outFile << 1000 << endl;//100用于表示子弹链表的数据已经保存完毕

	//保存玩家坦克的数据
	outFile << player.cur_position_.x_ << " " << player.cur_position_.y_ << " " << static_cast<int>(player.direction_) << " " << player.hp_ << " " << player.fire_delay_ << endl;
	//保存基地位置的数据
	outFile << base_position.x_ << " " << base_position.y_ << endl;
	//保存地图数据
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			outFile << map[i][j] << " ";
		}
		outFile << endl;
	}
	//保存游戏时间数据
	outFile << play_time << endl;
	outFile << endl;

	outFile.close();//关闭文件

}

bool ReadData(int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player, Position& base_position, vector<vector<int>>& map, time_t& play_time)
{
	ifstream inFile("Data.txt");
	if (!inFile.is_open()) {
		cout << "打开文件失败" << endl;
		return false;
	}
	int judge;//作为判定标志，判断链表类数据是否已经结束
	//读取关卡数据
	inFile >> level;
	if (level == 0)//关卡值为0，表示游戏已结束，已返回主界面
		return false;
	//读取敌方坦克链表的数据
	while (1)
	{
		Position cur_position;
		inFile >> cur_position.x_;
		//判断敌方坦克的数据是否已经结束，如果是，则跳出循环，进行下一类数据的读取
		if (cur_position.x_ == 1000)
			continue;
		inFile >> cur_position.y_;
		int dir;//由于枚举值保存在文件中转换成了相应的整数值，用dir_读取对应的整数
		int hp;
		int fire_delay;
		bool target;
		inFile >> dir >> hp >> fire_delay >> target;
		DIR direction = static_cast<DIR>(dir);//static_cast<DIR>将dir_强制转化成对应的枚举值
		Enemy enemy(enemy_list, cur_position, direction);//初始化敌方坦克

		//修改坦克数据，使其与存档数据一致。hp_、fire_delay_、target_三项数据仍需修改
		auto temp = enemy_list.back();
		temp.hp_ = hp;
		temp.fire_delay_ = fire_delay;
		temp.target_ = target;
		enemy_list.pop_back();//删除初始化的坦克
		enemy_list.push_back(temp);//添加修改后的坦克

	}
	//读取子弹链表的数据
	while (1)
	{
		Position cur_position;
		inFile >> cur_position.x_;
		//判断子弹的数据是否已经结束，如果是，则跳出循环，进行下一类数据的读取
		if (cur_position.x_ == 1000)
			continue;
		int dir;
		bool friendly;
		inFile >> cur_position.y_ >> dir >> friendly;
		DIR direction = static_cast<DIR>(dir);
		Bullet bullet(bullet_list, cur_position, direction, friendly);//初始化子弹
	}
	//读取玩家数据
	int dir;
	inFile >> player.cur_position_.x_ >> player.cur_position_.y_ >> dir >> player.hp_ >> player.fire_delay_;
	player.direction_ = static_cast<DIR>(dir);
	//读取基地位置
	inFile >> base_position.x_ >> base_position.y_;
	//读取地图
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			inFile >> map[i][j];
		}
	}
	//读取游戏时间
	inFile >> play_time;

	inFile.close();//关闭文件

	return true;
}

int LevelSelect()
{
	setbkcolor(BLACK);
	cleardevice();
	setfillcolor(WHITE);
	BeginBatchDraw();//开始批量绘图
	fillrectangle(40, 150, 190, 450);
	fillrectangle(230, 150, 380, 450);
	fillrectangle(420, 150, 570, 450);
	fillrectangle(610, 150, 760, 450);
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);

	//文字居中表示
	char arr1[] = "返回菜单界面";
	int width1 = 150 / 2 - textwidth(arr1) / 2;
	int height1 = 300 / 2 - textheight(arr1) / 2;
	outtextxy(40 + width1, 150 + height1, arr1);
	char arr2[] = "废墟楼";
	int width2 = 150 / 2 - textwidth(arr2) / 2;
	int height2 = 300 / 2 - textheight(arr2) / 2;
	outtextxy(230 + width2, 150 + height2, arr2);
	char arr3[] = "丛林";
	int width3 = 150 / 2 - textwidth(arr3) / 2;
	int height3 = 300 / 2 - textheight(arr3) / 2;
	outtextxy(420 + width3, 150 + height3, arr3);
	char arr4[] = "军事基地";
	int width4 = 150 / 2 - textwidth(arr4) / 2;
	int height4 = 300 / 2 - textheight(arr4) / 2;
	outtextxy(610 + width4, 150 + height4, arr4);
	FlushBatchDraw();//结束批量绘图

	ExMessage m;
	while (1)
	{
		m = getmessage(EX_MOUSE);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			if (m.x > 40 && m.x < 190 && m.y > 150 && m.y < 450)
				return 0;
			else if (m.x > 230 && m.x < 380 && m.y > 150 && m.y < 450)
				return 1;
			else if (m.x > 420 && m.x < 570 && m.y > 150 && m.y < 450)
				return 2;
			else if (m.x > 610 && m.x < 760 && m.y > 150 && m.y < 450)
				return 3;
		}
	}

}