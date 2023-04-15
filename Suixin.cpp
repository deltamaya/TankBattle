#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include "architechture.h"
void Settings(int& music_volume, int& sound_volume)
{
	initgraph(800, 600);
	setbkcolor(BLACK);
	cleardevice();
	setfillcolor(WHITE);
	BeginBatchDraw();//开始批量绘图
	fillrectangle(45, 45, 160, 120);
	fillrectangle(190, 45, 305, 120);
	fillrectangle(335, 45, 450, 120);
	fillrectangle(480, 45, 595, 120);
	fillrectangle(625, 45, 740, 120);
	fillrectangle(45, 177, 160, 252);//第二行
	fillrectangle(190, 177, 305, 252);
	fillrectangle(335, 177, 450, 252);
	fillrectangle(480, 177, 595, 252);
	fillrectangle(625, 177, 740, 252);
	fillrectangle(85, 313, 335, 475);//第三行1
	fillrectangle(405, 313, 655, 475);//第三行2


	//文字
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);
	char arr1[] = "游戏音乐";
	int width1 = 115 / 2 - textwidth(arr1) / 2;
	int height1 = 75 / 2 - textheight(arr1) / 2;
	outtextxy(45 + width1, 45 + height1, arr1);
	char arr2[] = "静音";
	int width2 = 115 / 2 - textwidth(arr2) / 2;
	int height2 = 75 / 2 - textheight(arr2) / 2;
	outtextxy(190 + width2, 45 + height2, arr2);
	char arr3[] = "小";
	int width3 = 115 / 2 - textwidth(arr3) / 2;
	int height3 = 75 / 2 - textheight(arr3) / 2;
	outtextxy(335 + width3, 45 + height3, arr3);
	char arr4[] = "中";
	int width4 = 115 / 2 - textwidth(arr4) / 2;
	int height4 = 75 / 2 - textheight(arr4) / 2;
	outtextxy(480 + width4, 45 + height4, arr4);
	char arr5[] = "大";
	int width5 = 115 / 2 - textwidth(arr5) / 2;
	int height5 = 75 / 2 - textheight(arr5) / 2;
	outtextxy(625 + width5, 45 + height5, arr5);

	char arr6[] = "游戏音效";
	int width6 = 115 / 2 - textwidth(arr6) / 2;
	int height6 = 75 / 2 - textheight(arr6) / 2;
	outtextxy(45 + width6, 177 + height6, arr6);
	char arr7[] = "静音";
	int width7 = 115 / 2 - textwidth(arr7) / 2;
	int height7 = 75 / 2 - textheight(arr7) / 2;
	outtextxy(190 + width7, 177 + height7, arr7);
	char arr8[] = "小";
	int width8 = 115 / 2 - textwidth(arr8) / 2;
	int height8 = 75 / 2 - textheight(arr8) / 2;
	outtextxy(335 + width8, 177 + height8, arr8);
	char arr9[] = "中";
	int width9 = 115 / 2 - textwidth(arr9) / 2;
	int height9 = 75 / 2 - textheight(arr9) / 2;
	outtextxy(480 + width9, 177 + height9, arr9);
	char arr10[] = "大";
	int width10 = 115 / 2 - textwidth(arr10) / 2;
	int height10 = 75 / 2 - textheight(arr10) / 2;
	outtextxy(625 + width10, 177 + height10, arr10);

	char arr11[] = "回到游戏界面";
	int width11 = 250 / 2 - textwidth(arr11) / 2;
	int height11 = 162 / 2 - textheight(arr11) / 2;
	outtextxy(85 + width11, 313 + height11, arr11);
	char arr12[] = "回到首页";
	int width12 = 250 / 2 - textwidth(arr12) / 2;
	int height12 = 162 / 2 - textheight(arr12) / 2;
	outtextxy(405 + width12, 313 + height12, arr12);
	FlushBatchDraw();

	ExMessage m;
	while (1)
	{
		m = getmessage(EX_MOUSE);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			if (m.x > 190 && m.x < 305 && m.y > 45 && m.y < 120)    //静音
			{
				music_volume = 0;
			}
			else if (m.x > 335 && m.x < 450 && m.y > 45 && m.y < 120)  //小
			{
				music_volume = 20;
			}
			else if (m.x > 480 && m.x < 595 && m.y > 45 && m.y < 120)   //中
			{
				music_volume = 50;
			}
			else if (m.x > 625 && m.x < 740 && m.y > 45 && m.y < 120)   //大
			{
				music_volume = 80;
			}
			else if (m.x > 190 && m.x < 305 && m.y > 177 && m.y < 252)   //音效静音
			{
				sound_volume = 0;
			}
			else if (m.x > 335 && m.x < 450 && m.y > 177 && m.y < 252)  //小
			{
				sound_volume = 20;
			}
			else if (m.x > 480 && m.x < 595 && m.y > 177 && m.y < 252)  //中
			{
				sound_volume = 50;
			}
			else if (m.x > 625 && m.x < 740 && m.y > 177 && m.y < 252)   //大
			{
				sound_volume = 80;
			}
			else if (m.x > 85 && m.x < 335 && m.y > 313 && m.y < 475)   //回到游戏界面
			{
				break;
			}
			else if (m.x > 405 && m.x < 655 && m.y > 313 && m.y < 475)   //回到首页
			{
				break;
			}
		}
	}

	_getch();
	closegraph();
}
