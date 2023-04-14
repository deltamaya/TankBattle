#include "architechture.h"
#include <fstream>
#include <graphics.h>
#include <conio.h>

void SaveData(const int level, const list<Enemy>& enemy_list, const list<Bullet>& bullet_list, const Player& player, const Position& base_position, const vector<vector<int>>& map, const time_t& play_time)
{
	ofstream outFile("Data.txt");
	//����ؿ�������
	outFile << level << endl;
	//����з�̹�����������
	//̹�˵ĵ����ݰ�����ĳ�Ա���ν��б��棬ÿ��̹�˱���Ϊһ��
	for (auto iter = enemy_list.begin(); iter != enemy_list.end(); ++iter) {
		outFile << iter->cur_position_.x_ << " " << iter->cur_position_.y_ << " " << static_cast<int>(iter->direction_) << " " << iter->hp_ << " " << iter->fire_delay_ << " " << iter->target_ << endl;
	}//static_cast<int>(iter->direction_ ):��ö��ֵת��Ϊ��Ӧ������ֵ���浽�ļ���
	outFile << 1000 << endl;//100���ڱ�ʾ�з�̹������������Ѿ��������

	//�����ӵ����������
	for (auto iter = bullet_list.begin(); iter != bullet_list.end(); ++iter) {
		outFile << iter->cur_position_.x_ << " " << iter->cur_position_.y_ << " " << static_cast<int>(iter->direction_) << " " << iter->friendly_ << endl;
	}
	outFile << 1000 << endl;//100���ڱ�ʾ�ӵ�����������Ѿ��������

	//�������̹�˵�����
	outFile << player.cur_position_.x_ << " " << player.cur_position_.y_ << " " << static_cast<int>(player.direction_) << " " << player.hp_ << " " << player.fire_delay_ << endl;
	//�������λ�õ�����
	outFile << base_position.x_ << " " << base_position.y_ << endl;
	//�����ͼ����
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			outFile << map[i][j] << " ";
		}
		outFile << endl;
	}
	//������Ϸʱ������
	outFile << play_time << endl;
	outFile << endl;

	outFile.close();//�ر��ļ�

}

bool ReadData(int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player, Position& base_position, vector<vector<int>>& map, time_t& play_time)
{
	ifstream inFile("Data.txt");
	if (!inFile.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return false;
	}
	int judge;//��Ϊ�ж���־���ж������������Ƿ��Ѿ�����
	//��ȡ�ؿ�����
	inFile >> level;
	if (level == 0)//�ؿ�ֵΪ0����ʾ��Ϸ�ѽ������ѷ���������
		return false;
	//��ȡ�з�̹�����������
	while (1)
	{
		Position cur_position;
		inFile >> cur_position.x_;
		//�жϵз�̹�˵������Ƿ��Ѿ�����������ǣ�������ѭ����������һ�����ݵĶ�ȡ
		if (cur_position.x_ == 1000)
			continue;
		inFile >> cur_position.y_;
		int dir;//����ö��ֵ�������ļ���ת��������Ӧ������ֵ����dir_��ȡ��Ӧ������
		int hp;
		int fire_delay;
		bool target;
		inFile >> dir >> hp >> fire_delay >> target;
		DIR direction = static_cast<DIR>(dir);//static_cast<DIR>��dir_ǿ��ת���ɶ�Ӧ��ö��ֵ
		Enemy enemy(enemy_list, cur_position, direction);//��ʼ���з�̹��

		//�޸�̹�����ݣ�ʹ����浵����һ�¡�hp_��fire_delay_��target_�������������޸�
		auto temp = enemy_list.back();
		temp.hp_ = hp;
		temp.fire_delay_ = fire_delay;
		temp.target_ = target;
		enemy_list.pop_back();//ɾ����ʼ����̹��
		enemy_list.push_back(temp);//����޸ĺ��̹��

	}
	//��ȡ�ӵ����������
	while (1)
	{
		Position cur_position;
		inFile >> cur_position.x_;
		//�ж��ӵ��������Ƿ��Ѿ�����������ǣ�������ѭ����������һ�����ݵĶ�ȡ
		if (cur_position.x_ == 1000)
			continue;
		int dir;
		bool friendly;
		inFile >> cur_position.y_ >> dir >> friendly;
		DIR direction = static_cast<DIR>(dir);
		Bullet bullet(bullet_list, cur_position, direction, friendly);//��ʼ���ӵ�
	}
	//��ȡ�������
	int dir;
	inFile >> player.cur_position_.x_ >> player.cur_position_.y_ >> dir >> player.hp_ >> player.fire_delay_;
	player.direction_ = static_cast<DIR>(dir);
	//��ȡ����λ��
	inFile >> base_position.x_ >> base_position.y_;
	//��ȡ��ͼ
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			inFile >> map[i][j];
		}
	}
	//��ȡ��Ϸʱ��
	inFile >> play_time;

	inFile.close();//�ر��ļ�

	return true;
}

int LevelSelect()
{
	setbkcolor(BLACK);
	cleardevice();
	setfillcolor(WHITE);
	BeginBatchDraw();//��ʼ������ͼ
	fillrectangle(40, 150, 190, 450);
	fillrectangle(230, 150, 380, 450);
	fillrectangle(420, 150, 570, 450);
	fillrectangle(610, 150, 760, 450);
	settextcolor(BLACK);
	settextstyle(20, 0, "����");
	setbkmode(TRANSPARENT);

	//���־��б�ʾ
	char arr1[] = "���ز˵�����";
	int width1 = 150 / 2 - textwidth(arr1) / 2;
	int height1 = 300 / 2 - textheight(arr1) / 2;
	outtextxy(40 + width1, 150 + height1, arr1);
	char arr2[] = "����¥";
	int width2 = 150 / 2 - textwidth(arr2) / 2;
	int height2 = 300 / 2 - textheight(arr2) / 2;
	outtextxy(230 + width2, 150 + height2, arr2);
	char arr3[] = "����";
	int width3 = 150 / 2 - textwidth(arr3) / 2;
	int height3 = 300 / 2 - textheight(arr3) / 2;
	outtextxy(420 + width3, 150 + height3, arr3);
	char arr4[] = "���»���";
	int width4 = 150 / 2 - textwidth(arr4) / 2;
	int height4 = 300 / 2 - textheight(arr4) / 2;
	outtextxy(610 + width4, 150 + height4, arr4);
	FlushBatchDraw();//����������ͼ

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