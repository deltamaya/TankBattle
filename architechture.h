#ifndef ARCHITECHTURE
#define ARCHITECHTURE
#include <vector>
#include <list>
#include <queue>
#include <iostream>
class Bullet;
class Enemy;
class Player;
class Position;
using namespace std;
//---view---


//�����ˣ���֮ŵ
//���ܣ�չʾ�����棬�ṩ�û�������ť������ѡ��ʼ��Ϸ����ѡ��ؿ�����
//		���Խ������ý��桢�����߳�Ա�����Լ��˳���Ϸ��ť
//������void
//����ֵ����ҵ�ѡ��
int MainMenu();

//�����ˣ�����
//���ܣ�չʾ���ý��棬�û����Ե���bgm����Ч�Ĵ�С
//������������С����Ч��С
//����ֵ��void
void Settings(int& music_volume,int& sound_volume);

//�����ˣ�����
//���ܣ�չʾ�����߳�Ա���棬���Է���������
//������void
//����ֵ��void
void Developers();

//�����ˣ�����
//���ܣ�չʾ����ҳ�棬�����չʾ�����淨�����Է���������
//������void
//����ֵ��void
void Help();

//�����ˣ�kong
//���ܣ���ʾ�����δ��ɵ���Ϸ���Ƿ����
//������void
//����ֵ��������ѡ�������Ϸ����true�������������Ϸ����false
bool ContinueGame();

//�����ˣ�����
//���ܣ������չʾѡ��ؿ����棬���Է���������
//������void
//����ֵ�����ѡ��Ĺؿ�������0�����������棬1~3����ѡ��Ĺؿ�
int LevelSelect();

//***��Ҫ***
//�����ˣ�ŵŵ
//���ܣ������չʾ��Ϸ����
//�������ؿ�id,���������ӵ�������ң�����λ�ã���ͼ������ʱ��
//����ֵ��void
void ShowMap(const int& level, const list<Enemy>& enemy_list, const list<Bullet>& bullet_list, const Player& player, const Position& base_position, const vector<vector<int>>& map, const time_t& play_time);

//---view---


//---service---


//+main.cpp�е�������ͼ
//�����ˣ�asd
//���ܣ���ʼ����ͼ��ʹ��level_x��ʼ��map,��ʼ������λ�ã����ˣ���ң�����ʱ��
//�������ؿ�id,���������ӵ�������ң�����λ�ã���ͼ������ʱ��
//����ֵ��void
void InitMap(const int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player, Position& base_position, vector<vector<int>>& map, time_t& play_time);



//***��Ҫ***
//�����ˣ�������
//���ܣ�������Ϸ������showmapչʾ���棬����update������Ϸ״̬������bulletjudge�����ж�
// ��������ͣ����ʾ��ͣҳ�档
// �������˳�������SaveData�󷵻������档
// ��Ϸ���������������չʾ������棬����savedata��Ȼ�󷵻�������
//�������ؿ�id,���������ӵ�������ң�����λ�ã���ͼ������ʱ��
//����ֵ��void
void NewGame(const int level, list<Enemy>& enemy_list, list<Bullet> &bullet_list, Player& player, const Position& base_position, vector<vector<int>>& map, time_t& play_time);

//***��Ҫ***
//�����ˣ�asd
//���ܣ���ȡ������룬������Ϸ״̬��reload ,move�ȣ�
//�������ؿ�id,���������ӵ�������ң�����λ�ã���ͼ������ʱ��
//����ֵ��void
void Update(const int level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player, const Position& base_position, vector<vector<int>>& map, time_t& play_time);

//�����ˣ�ŵŵ
//���ܣ������չʾ��ʤ����
//����������ʱ��
//����ֵ��void
void GameWin(const time_t &play_time);

//�����ˣ�ŵŵ
//���ܣ������չʾʧ�ܽ���
//������void
//����ֵ��void
void GameLose();

//�����ˣ�����
//���ܣ�����Ϸ����д��浵����
//���������ˣ��ӵ�����ң���ͼ������ʱ��
//����ֵ��void
void SaveData(const int level,const list<Enemy>& enemy_list,const list<Bullet>&bullet_list,const Player& player,const Position& base_position,const vector<vector<int>>& map,const time_t& play_time);

//�����ˣ�����
//���ܣ�����Ϸ��Ϣ��ȡ�ŵ������У�ע�⣺�������浵�Ѿ��������������false
//���������ˣ��ӵ�����ң���ͼ������ʱ��
//����ֵ�������ȡ�ɹ�����true�����ʧ�ܷ���false
bool ReadData(int &level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player,Position& base_position, vector<vector<int>>& map, time_t& play_time);

//---service---

//�����ö�٣����DIRECTIONʹ��
enum DIR {
	NONE=0,
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};
//����λ��ö�٣����mapʹ��
enum Grid {
	SPACE = 0,
	WALL = 1,
	BASE = 2,
};
//λ����
class Position {
public:
	int x_;//������
	int y_;//������
	Position(int a, int b) ://��������ֵ����ʼ��һ������
		x_(a), y_(b) {};
	Position() ://������ֵ��ʼ��һ������
		x_(0), y_(0) {};
	Position operator+(const Position& another)const {//�ӷ������������DIRECTIONʹ��
		Position ret(x_, y_);
		ret.x_ += another.x_;
		ret.y_ += another.y_;
		return ret;
	}//���ڲ��������������λ�õĺ������궼��ȣ�����true�����򷵻�false
	bool operator==(const Position& another)const {
		return x_ == another.x_ && y_ == another.y_;
	}
	//λ�õķ���������map���жϵ�ͼ�����λ���Ƿ������
	[[nodiscard]] bool Walkable(const vector<vector<int>>& matrix)const {
		return x_ >= 0 && x_ < matrix.size() && y_ >= 0 && y_ < matrix[0].size() && !matrix[x_][y_];
	}
};

const vector<Position>DIRECTION = { {0,0}, {-1,0},{1,0},{0,-1},{0,1} };
//�ӵ���
class Bullet {
public:
	Position cur_position_;//��ǰλ��
	DIR direction_;//����
	bool friendly_;//�Ƿ�����
	//��ʼ����ʱ���뿪��λ��λ�úͷ����Լ�������ӵ�friendlyΪtrue�����˷����Ϊfalse
	Bullet(list<Bullet>bullet_list,Position cur_position, DIR direction, bool friendly) :
		cur_position_(cur_position), direction_(direction), friendly_(friendly) {
		bullet_list.push_back(*this);
	};
};

//�����
class Player {
	static const int MAX_FIRE_DELAY = 500;//�����ʱ����λΪ����
public:
	Position cur_position_;//��ǰλ��
	DIR direction_;//��ǰ����
	int hp_;//Ѫ��
	int fire_delay_;//��ǰ�����ʱ
	Player(Position cur_position, DIR direction) :
		cur_position_(cur_position), direction_(direction), hp_(2), fire_delay_(0) {};
	void Fire(list<Bullet>bullet_list) {//����������ʼ��һ���ӵ������������ʱ����Ϊ�����ʱ
		Bullet player_bullet(bullet_list, cur_position_, direction_, true);
		fire_delay_ = MAX_FIRE_DELAY;
	}
	void Hit() {//�����к������ή�����hp��hpΪ���lose�����Լ���һЩ����
		--hp_;
	}
	void Move(const vector<vector<int>>&map) {//�ƶ�����������һ�����ӿ����ߣ��͸���λ��
		auto next = cur_position_ + DIRECTION[ direction_];
		if (next.Walkable(map)) {
			cur_position_ = next;
		}
	}//װ��������͵�ǰ�����ʱֱ��0��ÿ�������һ��
	void Reload() {
		if (fire_delay_ > 0)--fire_delay_;
	}
};


//��node��manhattan����A*�㷨�ĸ�����û��Ҫ�
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
//---����

//A*Ѱ·�㷨������map�����λ�ã��յ�λ�ã����ش���㵽�յ����·���ĵ�һ������һ��DIRö�٣�
DIR AStarAlgorithm(const vector<vector<int>>& matrix, const Position& begin_position, const Position& destination);

//�����࣬�ܶ������඼һ����ֻע�Ͳ�һ����
class Enemy {
	static const int MAX_FIRE_DELAY = 500;
public:
	Position cur_position_;
	DIR direction_;
	int hp_;
	int fire_delay_;
	bool target_;//Ŀ�꣬trueΪ��ң�falseΪ����
	Enemy(list<Enemy>enemy_list,Position cur_position, DIR direction) :
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
	//�����飬����Ŀ��λ��һ��ֱ���� ��֮���ǽ��С�ڵ���1 �ҿ�����ʱΪ0������Ŀ�꿪��
	void FireCheck(const vector<vector<int>>& map, list<Bullet>bullet_list, Player& player, Position& base_position);
	//�����ƶ��������ʼ�����ƶ�һ�Σ�Ȼ��ͨ��Ѱ·�㷨���·���
	void Move(const vector<vector<int>>& map,Player& player,Position& base_position) {
		cur_position_ = cur_position_ + DIRECTION[direction_];
		DIR dir;
		if (target_) dir = AStarAlgorithm(map, cur_position_, player.cur_position_);
		else dir = AStarAlgorithm(map, cur_position_, base_position);
		direction_ = dir;
	}
	void Reload() {
		if (fire_delay_ > 0)--fire_delay_;
	}
};

//�ӵ��ж��㷨���з��ӵ�ɱ����һ���л��ؾ�ʧ��
//����ǽ�ʹݻ�ǽ���ѷ��ӵ����е��˾ͽ�����hp
//����0��ʾ��Ϸ����������1��ʾ��Ϸʧ�ܣ�����2��ʾʤ��
int JudgeBullets(vector<vector<int>>& map, Player& player, Position& base_position,list<Bullet>bullet_list, list<Enemy>enemy_list);


#endif // ARCHITECHTURE



