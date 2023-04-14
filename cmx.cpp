#include <conio.h>
#include <easyx.h>
#include "architechture.h"

void NewGame(const int level,
	list<Enemy>& enemy_list,
	list<Bullet>& bullet_list,
	Player& player,
	const Position& base_position,
	vector<vector<int>>& map, time_t& play_time)
{
	BeginBatchDraw();
	while (1)
	{
		FlushBatchDraw();//开始批量绘图
		ShowMap(&level, &enemy_list, &bullet_list, &player, &base_position, &map, &play_time);
		Update(&level, &enemy_list, &bullet_list, &player, &base_position, &map, &play_time);
		if (JudgeBullets(&map, &player, &base_position, &bullet_list, &enemy_list) == 1)
		{
			SaveData(&level, &enemy_list, &bullet_list, &player, &base_position, &map, &play_time);
			GameWin(& play_time);
		}
		else if (JudgeBullets(&map, &player, &base_position, &bullet_list, &enemy_list) == 2)
		{
			GameLose();
		}

		if (GetAsyncKeyState(VK_ESCAPE)) 
		{
			//暂停页面;
		}



	}
	EndBatchDraw();
}