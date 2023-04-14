#include "architechture.h"
#include <fstream>

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
