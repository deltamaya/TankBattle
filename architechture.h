#ifndef ARCHITECHTURE
#define ARCHITECHTURE
#include <vector>
#include <list>
#include <queue>
#include <iostream>
using namespace std;
//---view---


//负责人：
//功能：展示主界面，提供用户几个按钮，可以选择开始游戏进入选择关卡界面
//		可以进入设置界面、开发者成员界面以及退出游戏按钮
//参数：void
//返回值：void
void MainMenu();

//负责人：
//功能：展示设置界面，用户可以调整bgm、音效的大小
//参数：void
//返回值：void
void Settings();

//负责人：
//功能：展示开发者成员界面，可以返回主界面
//参数：
//返回值：
void Developers();

//负责人：
//功能：展示帮助页面，向玩家展示操作玩法，可以返回主界面
//参数：
//返回值：
void Help();

void ContinueGame();

//负责人：
//功能：向玩家展示选择关卡界面，可以返回主界面
//		在玩家选择关卡之后：
//			1.使用上面的地图初始化map（在maya.h中）
//			2.根据地图初始化base_position
//			3.进入NewGame函数
//参数：
//返回值：
void LevelSelect();

//负责人：
//功能：初始化地图，使用上面的vector
//参数：
//返回值：
void InitMap();

//***关键***
//负责人：
//功能：
//参数：
//返回值：
void ShowMap();

//---view---


//---service---


//负责人：
//功能：
//参数：
//返回值：
void NewGame();

//负责人：
//功能：
//参数：
//返回值：
void GameWin();

//负责人：
//功能：
//参数：
//返回值：
void GameLose();

//负责人：
//功能：
//参数：
//返回值：
void SaveData();

//负责人：
//功能：
//参数：
//返回值：
void ReadData();

//---service---

class Bullet;
class Enemy;
class Player;

//方向的枚举，配合下面的DIRECTION使用
enum DIR {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};
//网格单位的枚举，配合map使用
enum Grid {
	SPACE = 0,
	WALL = 1,
	BASE = 2,
};
//位置类
class Position {
public:
	int x_;//横坐标
	int y_;//纵坐标
	Position(int a, int b) ://传入两个值，初始化一个对象
		x_(a), y_(b) {};
	Position() ://不传入值初始化一个对象
		x_(0), y_(0) {};
	Position operator+(const Position& another)const {//加法操作符，配合DIRECTION使用
		Position ret(x_, y_);
		ret.x_ += another.x_;
		ret.y_ += another.y_;
		return ret;
	}//等于操作符，如果两个位置的横纵坐标都相等，返回true，否则返回false
	bool operator==(const Position& another)const {
		return x_ == another.x_ && y_ == another.y_;
	}
	//位置的方法，传入map，判断地图的这个位置是否可以走
	[[nodiscard]] bool Walkable(const vector<vector<int>>& matrix)const {
		return x_ >= 0 && x_ < matrix.size() && y_ >= 0 && y_ < matrix[0].size() && !matrix[x_][y_];
	}
};

const vector<Position>DIRECTION = { {-1,0},{1,0},{0,-1},{0,1} };
//子弹类
class Bullet {
public:
	Position cur_position_;//当前位置
	Position direction_;//方向
	bool friendly_;//是否友善
	//初始化的时候传入开火单位的位置和方向，自己发射的子弹friendly为true，敌人发射的为false
	Bullet(list<Bullet>bullet_list,Position cur_position, Position direction, bool friendly) :
		cur_position_(cur_position), direction_(direction), friendly_(friendly) {
		bullet_list.push_back(*this);
	};
};

//玩家类
class Player {
	static const int MAX_FIRE_DELAY = 500;//最大延时，单位为毫秒
public:
	Position cur_position_;//当前位置
	Position direction_;//当前方向
	int hp_;//血量
	int fire_delay_;//当前射击延时
	Player(Position cur_position, Position direction) :
		cur_position_(cur_position), direction_(direction), hp_(2), fire_delay_(0) {};
	void Fire(list<Bullet>bullet_list) {//开火函数，初始化一个子弹，并将射击延时设置为最大延时
		Bullet player_bullet(bullet_list, cur_position_, direction_, true);
		fire_delay_ = MAX_FIRE_DELAY;
	}
	void Hit() {//被击中函数，会降低玩家hp，hp为零就lose，可以加入一些动画
		--hp_;
	}
	void Move(const vector<vector<int>>&map) {//移动函数，当下一个格子可以走，就更改位置
		auto next = cur_position_ + direction_;
		if (next.Walkable(map)) {
			cur_position_ = next;
		}
	}//装填函数，降低当前射击延时直至0，每毫秒调用一次
	void Reload() {
		if (fire_delay_ > 0)--fire_delay_;
	}
};


//从node到manhattan都是A*算法的附属，没必要深究
class Node {
public:
	Position position_;
	Node* pre_node_;
	int cur_cost_;
	int predict_cost_;
	Node(const Position& cur_position, Node* pre_node, int cur_cost, int predict_cost) :
		position_(cur_position),
		pre_node_(pre_node),
		cur_cost_(cur_cost),
		predict_cost_(predict_cost) {};
};
struct cmp
{
	bool operator()(Node*& a, Node*& b) const
	{
		return a->cur_cost_ + a->predict_cost_ > b->cur_cost_ + b->predict_cost_;
	}
};
inline int Manhattan(const Position& cur_position, const Position& destination) {
	return abs(cur_position.x_ - destination.x_) + abs(cur_position.y_ - destination.y_);
}
//---以上

//A*寻路算法，传入map，起点位置，终点位置，返回从起点到终点最短路径的第一个方向（一个DIR枚举）
DIR AStarAlgorithm(const vector<vector<int>>& matrix, const Position& begin_position, const Position& destination);

//敌人类，很多跟玩家类都一样，只注释不一样的
class Enemy {
	static const int MAX_FIRE_DELAY = 500;
public:
	Position cur_position_;
	Position direction_;
	int hp_;
	int fire_delay_;
	bool target_;//目标，true为玩家，false为基地
	Enemy(list<Enemy>enemy_list,Position cur_position, Position direction) :
		cur_position_(cur_position), direction_(direction), hp_(2), fire_delay_(0), target_(1) {
		enemy_list.push_back(*this);
	};
	void Hit() {
		--hp_;
	}
	void Fire(list<Bullet>bullet_list) {
		Bullet enemy_bullet(bullet_list, cur_position_, direction_, false);
		fire_delay_ = MAX_FIRE_DELAY;
	}
	//开火检查，当与目标位于一条直线上 且之间的墙数小于等于1 且开火延时为0，就向目标开火
	void FireCheck(const vector<vector<int>>& map, list<Bullet>bullet_list, Player& player, Position& base_position);
	//敌人移动，先向初始方向移动一次，然后通过寻路算法更新方向
	void Move(const vector<vector<int>>& map,Player& player,Position& base_position) {
		cur_position_ = cur_position_ + direction_;
		DIR dir;
		if (target_) dir = AStarAlgorithm(map, cur_position_, player.cur_position_);
		else dir = AStarAlgorithm(map, cur_position_, base_position);
		direction_ = DIRECTION[dir];
	}
	void Reload() {
		if (fire_delay_ > 0)--fire_delay_;
	}
};

//子弹判定算法，敌方子弹杀死玩家或击中基地就失败，自动调用GameLose函数
//击中墙就摧毁墙，友方子弹击中敌人就降低其hp
void JudgeBullets(vector<vector<int>>& map, Player& player, Position& base_position,list<Bullet>bullet_list, list<Enemy>enemy_list);


#endif // ARCHITECHTURE



