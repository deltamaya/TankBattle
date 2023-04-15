#include <conio.h>
#include <easyx.h>
#include "architechture.h"

void button(int x, int y, int width, int height, const char* text);

void NewGame(const int level,
	list<Enemy>& enemy_list,
	list<Bullet>& bullet_list,
	Player& player,
	const Position& base_position,
	vector<vector<int>>& map, time_t& play_time)
{
	BeginBatchDraw();
	int sl = 100, sr = 500, st = 100, sd = 500;
	while (1)
	{
		FlushBatchDraw();//开始批量绘图,展示更新地图
		ShowMap(level, enemy_list, bullet_list, player, base_position, map, play_time);
		Update(level, enemy_list, bullet_list, player, base_position, map, play_time);

		//判断游戏是否结束
		int jd = JudgeBullets(map, player, base_position, bullet_list, enemy_list);
		if (jd == 2)
		{
			SaveData(level, enemy_list, bullet_list, player, base_position, map, play_time);
			GameWin(play_time);
		}
		else if (jd == 1)
		{
			GameLose();
		}


		//检测esc输入，进入暂停界面
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			cout << "escape" << endl;
			BeginBatchDraw();
			ExMessage msg;
			while (1)
			{

				setfillcolor(BLACK);
				fillrectangle(sl, st, sr, sd);//输出图像
				setfillcolor(WHITE);

				settextstyle(18, 0, "黑体");
				outtextxy(400, 550, "按下回车键继续游戏.....");

				settextstyle(50, 0, "黑体");
				button(sl + 75, st + 25, 250, 100, "打开设置");//坐标175，125
				button(sl + 75, st + 25 + 100 + 25, 250, 100, "保存游戏");//坐标175，250
				button(sl + 75, st + 275, 250, 100, "返回菜单");//坐标175，375

				if (peekmessage(&msg, EX_MOUSE))
				{
					if (msg.message == WM_LBUTTONDOWN && msg.x > 175 && msg.x < 325 && msg.y > 125 && msg.y < 125 + 100)
					{
						//打开设置
						Settings();
						break;

					}
					else if (msg.message == WM_LBUTTONDOWN && msg.x > 175 && msg.x < 325 && msg.y > 250 && msg.y < 250 + 100)
					{
						//保存游戏
						SaveData(level, enemy_list, bullet_list, player, base_position, map, play_time);
						outtextxy(300, 0, "保存成功.....");// 显示保存成功
					}
					else if (msg.message == WM_LBUTTONDOWN && msg.x > 175 && msg.x < 325 && msg.y > 375 && msg.y < 375 + 100)
					{
						//返回菜单
						SaveData(level, enemy_list, bullet_list, player, base_position, map, play_time);
						MainMenu();
					}
				}

				FlushBatchDraw();
				//按下回车
				if (GetAsyncKeyState(VK_RETURN) & 0x8000)//判断回车是否被按下
				{
					break;
				}
			}

			EndBatchDraw();
		}

		EndBatchDraw();
	}
}

void button(int x, int y, int width, int height, const char* text) {
	rectangle(x, y, x + width, y + height);
	int tw = textwidth(text); int th = textheight(text);
	int tx = x + width / 2 - tw / 2;
	int ty = y + height / 2 - th / 2;
	outtextxy(tx, ty, text);
}