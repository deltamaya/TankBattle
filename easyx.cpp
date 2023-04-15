#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>//包含多媒体是设备接口头文件
#include <conio.h>
#pragma comment(lib, "winmm.lib")//加载静态库

//生成矩形按钮，内部居中输出文字
void button(int x, int y, int width, int height, const char* text);
void BGM() {
	//打开音乐，播放音乐
	mciSendString("open ./haixiu.mp3 alias nb", 0, 0, 0);
	//mciSendString("play nb repeat", 0, 0, 0);

	if (0) {
		mciSendString("close nb", 0, 0, 0);
	}
}

void change() {
	// 获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "BABY");
	int isok = MessageBox(NULL, "恭喜，你学会了弹窗", "提示", MB_OKCANCEL);
	if (isok == IDOK) {
		MessageBox(NULL, "恭喜，你学会了弹窗,请点取消", "提示", MB_OKCANCEL);
	}
	else if (isok == IDCANCEL) {
		MessageBox(NULL, "恭喜，你学会了弹窗，请点确定", "提示", MB_OKCANCEL);
	}
}

int main() {
	//创建窗口，设置窗口大小，showconsole
	//initgraph(640, 480, SHOWCONSOLE | NOMINIMIZE | NOCLOSE);
	initgraph(640, 480, EX_SHOWCONSOLE);

	change();//弹窗
	BGM();//背景音乐

	//设置背景颜色
	setbkcolor(CYAN); //1
	cleardevice(); //2

	//设置线
	setfillcolor(GREEN);
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 1);
	//画院
	circle(100, 100, 100);
	fillcircle(150, 150, 50);
	solidcircle(100, 100, 75);

	//绘制文字
	settextcolor(RED);
	//错误没有outtext可以转换的参数类型
	//字符串问题引起的错误
	//1.字符串前加 L
	//2.用TEXT()函数转换字符串,_T原理同上
	//3.不需要添加任何代码，项目->属性->常规-> 字符集->多字节字符集,推荐使用
	//outtextxy(100, 100, L"拉是真的niupi");
	//outtextxy(100, 120, TEXT("拉是真的niupi"));
	//设置文字样式
	settextstyle(20, 0,"楷体");
	//设置背景模式 transprant
	setbkmode(TRANSPARENT);
	settextcolor(RGB(220, 229, 239));
	outtextxy(100, 100, "拉是真的niupi");

	//文字居中
	settextcolor(RGB(0, 0, 239));
	fillrectangle(200, 120, 500, 220);
	char arr[] = "我是居中显示niubia";
	int width = 200 + (500 - 200) / 2 - textwidth(arr) / 2;
	int height = 120 + (220 - 120) / 2 - textheight(arr) / 2;
	outtextxy(width, height, arr);

	//图像输出
	IMAGE img;//定义 
    //加载图片
	//相对路径：./表示当前文件夹下, ../表示当前文件夹上一级 ./easyx.png
	//绝对路径：D:\Desktop\坦克大战\easyx\easyx\easyx.png,斜杠要两个
	//png不支持背景透明
	loadimage(&img, "D:\\Desktop\\坦克大战\\easyx\\easyx\\easyx.png");
	putimage(0, 0, &img);

	cleardevice();
	settextcolor(RED);
	button(100, 100, 150, 50, "我是按钮");

	ExMessage msg; int x = 0, y = 0, z = 50;
	
	while (1) {
		
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img);
		button(100, 100, 150, 50, "我是按钮");
		setfillcolor(RED);
		fillcircle(x, y, z);

		FlushBatchDraw();
		EndBatchDraw();
		

		if (GetAsyncKeyState(VK_UP)) y = (y - 1) % 480;
		if (GetAsyncKeyState(VK_DOWN)) y = (y + 1) % 480;
		if (GetAsyncKeyState(VK_LEFT)) x = (x - 1) % 640;
		if (GetAsyncKeyState(VK_RIGHT)) x = (x + 1) % 640;
		if (GetAsyncKeyState(VK_SPACE)) z = (z - 1) ;

		//键盘消息
		/*if (_kbhit()) {
			char key = _getch();//缺点，getch为阻塞函数，不输入一直等待
			printf("%d %c\n", key, key);
			switch (key)
			{
			case 119:
			case 'W':
				y -= 5;
				break;
			case 115:
			case 'S':
				y += 5;
				break;
			case 97:
			case 'A':
				x -= 5;
				break;
			case 100:
			case 'D':
				x += 5;
				break;
			}
		}*/
		


		//鼠标消息
		/*if (peekmessage(&msg, EX_MOUSE)) {
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 100 && msg.x < 100 + 150 && msg.y > 100 && msg.y < 100 + 50)
					printf("啊，我被按了\n");
				break;
			}
		}*/

	}

	//鼠标输出
	
	getchar();
	closegraph();

	return 0;
}

void button(int x, int y, int width, int height, const char* text) {
	setfillcolor(BROWN);
	rectangle(x, y, x + width, y + height);

	int tw = textwidth(text); int th = textheight(text);
	int tx = x + width / 2 - tw / 2;
	int ty = y + height / 2 - th / 2;
	outtextxy(tx, ty, text);
}