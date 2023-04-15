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
		FlushBatchDraw();//��ʼ������ͼ,չʾ���µ�ͼ
		ShowMap(level, enemy_list, bullet_list, player, base_position, map, play_time);
		Update(level, enemy_list, bullet_list, player, base_position, map, play_time);

		//�ж���Ϸ�Ƿ����
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


		//���esc���룬������ͣ����
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			cout << "escape" << endl;
			BeginBatchDraw();
			ExMessage msg;
			while (1)
			{

				setfillcolor(BLACK);
				fillrectangle(sl, st, sr, sd);//���ͼ��
				setfillcolor(WHITE);

				settextstyle(18, 0, "����");
				outtextxy(400, 550, "���»س���������Ϸ.....");

				settextstyle(50, 0, "����");
				button(sl + 75, st + 25, 250, 100, "������");//����175��125
				button(sl + 75, st + 25 + 100 + 25, 250, 100, "������Ϸ");//����175��250
				button(sl + 75, st + 275, 250, 100, "���ز˵�");//����175��375

				if (peekmessage(&msg, EX_MOUSE))
				{
					if (msg.message == WM_LBUTTONDOWN && msg.x > 175 && msg.x < 325 && msg.y > 125 && msg.y < 125 + 100)
					{
						//������
						Settings();
						break;

					}
					else if (msg.message == WM_LBUTTONDOWN && msg.x > 175 && msg.x < 325 && msg.y > 250 && msg.y < 250 + 100)
					{
						//������Ϸ
						SaveData(level, enemy_list, bullet_list, player, base_position, map, play_time);
						outtextxy(300, 0, "����ɹ�.....");// ��ʾ����ɹ�
					}
					else if (msg.message == WM_LBUTTONDOWN && msg.x > 175 && msg.x < 325 && msg.y > 375 && msg.y < 375 + 100)
					{
						//���ز˵�
						SaveData(level, enemy_list, bullet_list, player, base_position, map, play_time);
						MainMenu();
					}
				}

				FlushBatchDraw();
				//���»س�
				if (GetAsyncKeyState(VK_RETURN) & 0x8000)//�жϻس��Ƿ񱻰���
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