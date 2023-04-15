#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>//������ý�����豸�ӿ�ͷ�ļ�
#include <conio.h>
#pragma comment(lib, "winmm.lib")//���ؾ�̬��

//���ɾ��ΰ�ť���ڲ������������
void button(int x, int y, int width, int height, const char* text);
void BGM() {
	//�����֣���������
	mciSendString("open ./haixiu.mp3 alias nb", 0, 0, 0);
	//mciSendString("play nb repeat", 0, 0, 0);

	if (0) {
		mciSendString("close nb", 0, 0, 0);
	}
}

void change() {
	// ��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "BABY");
	int isok = MessageBox(NULL, "��ϲ����ѧ���˵���", "��ʾ", MB_OKCANCEL);
	if (isok == IDOK) {
		MessageBox(NULL, "��ϲ����ѧ���˵���,���ȡ��", "��ʾ", MB_OKCANCEL);
	}
	else if (isok == IDCANCEL) {
		MessageBox(NULL, "��ϲ����ѧ���˵��������ȷ��", "��ʾ", MB_OKCANCEL);
	}
}

int main() {
	//�������ڣ����ô��ڴ�С��showconsole
	//initgraph(640, 480, SHOWCONSOLE | NOMINIMIZE | NOCLOSE);
	initgraph(640, 480, EX_SHOWCONSOLE);

	change();//����
	BGM();//��������

	//���ñ�����ɫ
	setbkcolor(CYAN); //1
	cleardevice(); //2

	//������
	setfillcolor(GREEN);
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 1);
	//��Ժ
	circle(100, 100, 100);
	fillcircle(150, 150, 50);
	solidcircle(100, 100, 75);

	//��������
	settextcolor(RED);
	//����û��outtext����ת���Ĳ�������
	//�ַ�����������Ĵ���
	//1.�ַ���ǰ�� L
	//2.��TEXT()����ת���ַ���,_Tԭ��ͬ��
	//3.����Ҫ����κδ��룬��Ŀ->����->����-> �ַ���->���ֽ��ַ���,�Ƽ�ʹ��
	//outtextxy(100, 100, L"�������niupi");
	//outtextxy(100, 120, TEXT("�������niupi"));
	//����������ʽ
	settextstyle(20, 0,"����");
	//���ñ���ģʽ transprant
	setbkmode(TRANSPARENT);
	settextcolor(RGB(220, 229, 239));
	outtextxy(100, 100, "�������niupi");

	//���־���
	settextcolor(RGB(0, 0, 239));
	fillrectangle(200, 120, 500, 220);
	char arr[] = "���Ǿ�����ʾniubia";
	int width = 200 + (500 - 200) / 2 - textwidth(arr) / 2;
	int height = 120 + (220 - 120) / 2 - textheight(arr) / 2;
	outtextxy(width, height, arr);

	//ͼ�����
	IMAGE img;//���� 
    //����ͼƬ
	//���·����./��ʾ��ǰ�ļ�����, ../��ʾ��ǰ�ļ�����һ�� ./easyx.png
	//����·����D:\Desktop\̹�˴�ս\easyx\easyx\easyx.png,б��Ҫ����
	//png��֧�ֱ���͸��
	loadimage(&img, "D:\\Desktop\\̹�˴�ս\\easyx\\easyx\\easyx.png");
	putimage(0, 0, &img);

	cleardevice();
	settextcolor(RED);
	button(100, 100, 150, 50, "���ǰ�ť");

	ExMessage msg; int x = 0, y = 0, z = 50;
	
	while (1) {
		
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img);
		button(100, 100, 150, 50, "���ǰ�ť");
		setfillcolor(RED);
		fillcircle(x, y, z);

		FlushBatchDraw();
		EndBatchDraw();
		

		if (GetAsyncKeyState(VK_UP)) y = (y - 1) % 480;
		if (GetAsyncKeyState(VK_DOWN)) y = (y + 1) % 480;
		if (GetAsyncKeyState(VK_LEFT)) x = (x - 1) % 640;
		if (GetAsyncKeyState(VK_RIGHT)) x = (x + 1) % 640;
		if (GetAsyncKeyState(VK_SPACE)) z = (z - 1) ;

		//������Ϣ
		/*if (_kbhit()) {
			char key = _getch();//ȱ�㣬getchΪ����������������һֱ�ȴ�
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
		


		//�����Ϣ
		/*if (peekmessage(&msg, EX_MOUSE)) {
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 100 && msg.x < 100 + 150 && msg.y > 100 && msg.y < 100 + 50)
					printf("�����ұ�����\n");
				break;
			}
		}*/

	}

	//������
	
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