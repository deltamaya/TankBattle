#pragma once//确实挺不错的
#include <vector>
#include <list>
#include <queue>
#include <iostream>
using namespace std;
class Bullet;
class Enemy;
class Player;
list<Enemy>enemy_list;
list<Bullet>bullet_list;
enum DIR {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};
const int ROW = 20;
const int COL = 20;
enum Grid {
	SPACE,
	WALL,
};
class Position {
public:
	int x_;
	int y_;
	Position(int a, int b) :
		x_(a), y_(b) {};
	Position() :
		x_(0), y_(0) {};
	Position operator+(const Position& another)const{
		Position ret(x_, y_);
		ret.x_ += another.x_;
		ret.y_ += another.y_;
		return ret;
	}
	bool operator==(const Position& another)const {
		return x_ == another.x_ && y_ == another.y_;
	}
	[[nodiscard]]bool Walkable(const vector<vector<int>>& matrix)const {
		return x_ >= 0 && x_ < matrix.size() && y_>=0 && y_ < matrix[0].size() && !matrix[x_][y_];
	}
};
const vector<Position>DIRECTION = {{-1,0},{1,0},{0,-1},{0,1} };
vector<vector<int>>map = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};




class Bullet {
public:
	Position cur_position_;
	Position direction_;
	bool friendly_;
	Bullet(Position cur_position,Position direction,bool friendly) :
		cur_position_(cur_position), direction_(direction), friendly_(friendly) {
		bullet_list.push_back(*this);
	};
};

class Player {
	static const int MAX_FIRE_DELAY = 500;
public:
	Position cur_position_;
	Position direction_;
	int hp_;
	int fire_delay_;
	Player(Position cur_position, Position direction) :
		cur_position_(cur_position), direction_(direction), hp_(2), fire_delay_(0) {};
	void Fire() {
		Bullet player_bullet(cur_position_,direction_,true);
		fire_delay_ = MAX_FIRE_DELAY;
	}
	void Hit() {
		--hp_;
	}
	void Move() {
		auto next = cur_position_ + direction_;
		if (next.Walkable(map)) {
			cur_position_ = next;
		}
	}
	void Reload() {
		if (fire_delay_ > 0)--fire_delay_;
	}
};

Player player({ 0,0 }, { 0,0 });

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
int Manhattan(const Position& cur_position, const Position& destination) {
	return abs(cur_position.x_ - destination.x_) + abs(cur_position.y_ - destination.y_);
}
DIR AStarAlgorithm(const vector<vector<int>>& matrix, const Position& begin_position, const Position& destination) {
	vector<vector<bool>>known(matrix.size(), vector<bool>(matrix[0].size(), false));
	priority_queue<Node*,vector<Node*>,cmp>frontier;
	queue<Node*>possible_node;
	auto begin_node = new Node(begin_position, nullptr, 0, Manhattan(begin_position, destination));
	known[begin_position.x_][begin_position.y_] = true;
	frontier.push(begin_node);
	while (!frontier.empty()) {
		auto cur_node = frontier.top();
		if (cur_node->position_ == destination)break;
		frontier.pop();
		possible_node.push(cur_node);
		for (auto& dir : DIRECTION) {
			auto next = new Node(cur_node->position_ + dir, cur_node, cur_node->cur_cost_ + 1, Manhattan(cur_node->position_ + dir, destination));
			if (next->position_.Walkable(matrix) && !known[next->position_.x_][next->position_.y_]) {
				known[next->position_.x_][next->position_.y_] = true;
				frontier.push(next);
			}
			else {
				delete next;
			}
		}
	}
	auto node = frontier.top();
	while (node->pre_node_&&!(node->pre_node_->position_ == begin_position)) {
		node = node->pre_node_;
	}
	DIR ret=UP;
	if (node->position_.x_ == begin_position.x_ - 1)ret = UP;
	else if (node->position_.x_ == begin_position.x_ + 1)ret = DOWN;
	else if (node->position_.y_ == begin_position.y_ - 1)ret = LEFT;
	else if (node->position_.y_ == begin_position.y_ + 1)ret = RIGHT;
	else {
		cout <<"In line :" << __LINE__ << "  two position are same!\n";
	}
	while (!possible_node.empty()) {
		delete possible_node.front();
		possible_node.pop();
	}
	while (!frontier.empty()) {
		delete frontier.top();
		frontier.pop();
	}
	return ret;
}
class Enemy {
	static const int MAX_FIRE_DELAY = 500;
public:
	Position cur_position_;
	Position direction_;
	int hp_;
	int fire_delay_;
	Enemy(Position cur_position, Position direction) :
		cur_position_(cur_position), direction_(direction), hp_(2), fire_delay_(0) {};
	void Hit() {
		--hp_;
	}
	void Fire() {
		Bullet enemy_bullet(cur_position_,direction_,false);
		fire_delay_ = MAX_FIRE_DELAY;
	}
	void FireCheck() { 
		auto ori_dir = direction_;
		if (cur_position_.x_ == player.cur_position_.x_) {
			int wall_cnt = 0;
			int low_y = cur_position_.y_, high_y = player.cur_position_.y_;
			direction_ = DIRECTION[RIGHT];
			if (low_y > high_y) { 
				swap(low_y, high_y); 
				direction_ = DIRECTION[LEFT];
			}
			for (int i = low_y; i <= high_y; ++i) {
				if (map[cur_position_.x_][i] == 1)++wall_cnt;
			}
			if (wall_cnt <= 1&&fire_delay_==0)Fire();
		}
		if (cur_position_.y_ == player.cur_position_.y_) {
			int wall_cnt = 0;
			int low_x = cur_position_.x_, high_x = player.cur_position_.x_;
			direction_ = DIRECTION[UP];
			if (low_x > high_x) { 
				swap(low_x, high_x); 
				direction_ = DIRECTION[DOWN];
			}
			for (int i = low_x; i <= high_x; ++i) {
				if (map[i][cur_position_.y_] == 1)++wall_cnt;
			}
			if (wall_cnt <= 1&&fire_delay_==0)Fire();
		}
		direction_ = ori_dir;
	}
	void Move() {
		cur_position_ = cur_position_ + direction_;
		auto dir = AStarAlgorithm(map, cur_position_, player.cur_position_);
		direction_ = DIRECTION[dir];
	}
	void Reload() {
		if (fire_delay_ > 0)--fire_delay_;
	}
};


void JudgeBullets() {
	for (auto iter = bullet_list.begin(); iter != bullet_list.end(); ++iter) {
		if (map[(*iter).cur_position_.x_][(*iter).cur_position_.y_] == 1) {
			map[(*iter).cur_position_.x_][(*iter).cur_position_.y_] = 0;
			bullet_list.erase(iter);
			continue;
		}
		if ((*iter).cur_position_ == player.cur_position_ && !(*iter).friendly_) {
			player.Hit();
			bullet_list.erase(iter);
			continue;
		}
		for (auto e_iter = enemy_list.begin(); e_iter != enemy_list.end(); ++e_iter) {
			if ((*iter).cur_position_ == (*e_iter).cur_position_&&(*iter).friendly_) {
				(*e_iter).Hit();
				if (((*e_iter).hp_) == 0) {
					enemy_list.erase(e_iter, ++e_iter);
				}
				bullet_list.erase(iter);
				continue;
			}
		}
		iter->cur_position_ = iter->cur_position_ + iter->direction_;
	}
}
