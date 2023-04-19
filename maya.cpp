#include "architechture.h"
#include <easyx.h>
#include <conio.h>

void Enemy::FireCheck(const vector<vector<int>>& map, list<Bullet>&bullet_list, Player& player,const Position& base_position) {
	Position target_position;
	target_position = player.cur_position_;
	auto ori_dir = direction_;
	if (cur_position_.x_ == target_position.x_) {
		int wall_cnt = 0;
		int low_y = cur_position_.y_, high_y = target_position.y_;
		direction_ = RIGHT;
		if (low_y > high_y) {
			swap(low_y, high_y);
			direction_ = LEFT;
		}
		for (int i = low_y; i <= high_y; ++i) {
			if (map[cur_position_.x_][i] == WALL)++wall_cnt;
		}
		if (wall_cnt <= 1 && fire_delay_ == 0)Fire(bullet_list);
	}
	else if (cur_position_.y_ == target_position.y_) {
		int wall_cnt = 0;
		int low_x = cur_position_.x_, high_x = target_position.x_;
		direction_ = DOWN;
		if (low_x > high_x) {
			swap(low_x, high_x);
			direction_ =UP;
		}
		for (int i = low_x; i <= high_x; ++i) {
			if (map[i][cur_position_.y_] == WALL)++wall_cnt;
		}
		if (wall_cnt <= 1 && fire_delay_ == 0)Fire(bullet_list);
	}
	direction_ = ori_dir;
}
DIR AStarAlgorithm(const vector<vector<int>>& matrix, const Position& begin_position, const Position& destination) {
	vector<vector<bool>>known(matrix.size(), vector<bool>(matrix[0].size(), false));
	priority_queue<Node*, vector<Node*>, cmp>frontier;
	queue<Node*>possible_node;
	auto begin_node = new Node(begin_position, nullptr, 0, Manhattan(begin_position, destination));
	known[begin_position.x_][begin_position.y_] = true;
	frontier.push(begin_node);
	while (!frontier.empty()) {
		auto cur_node = frontier.top();
		if (cur_node->position_ == destination)break;
		frontier.pop();
		possible_node.push(cur_node);
		for (int d = UP; d <= RIGHT;++d) {
			auto dir = DIRECTION[d];
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
	while (node->pre_node_ && !(node->pre_node_->position_ == begin_position)) {
		node = node->pre_node_;
	}
	DIR ret;
	if (node->position_.x_ == begin_position.x_ - 1)ret = UP;
	else if (node->position_.x_ == begin_position.x_ + 1)ret = DOWN;
	else if (node->position_.y_ == begin_position.y_ - 1)ret = LEFT;
	else if (node->position_.y_ == begin_position.y_ + 1)ret = RIGHT;
	else ret = NONE;
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
int JudgeBullets(vector<vector<int>>& map,Player& player,const Position& base_position, list<Bullet>&bullet_list, list<Enemy>&enemy_list) {
	for (auto iter = bullet_list.begin(); iter != bullet_list.end(); ) {
		if (map[(*iter).cur_position_.x_][(*iter).cur_position_.y_] == BASE) {
			iter = bullet_list.erase(iter);
			continue;
		}
		else if (map[(*iter).cur_position_.x_][(*iter).cur_position_.y_] == WALL) {
			map[(*iter).cur_position_.x_][(*iter).cur_position_.y_] = SPACE;
			iter=bullet_list.erase(iter);
			continue;
		}
		else if ((*iter).cur_position_ == player.cur_position_ && !(*iter).friendly_) {
			player.Hit();
			if (player.hp_ == 0)return 1;
			iter=bullet_list.erase(iter);
			continue;
		}
		else if ((*iter).cur_position_ == base_position && !(*iter).friendly_) {
			return 1;
		}
		for (auto e_iter = enemy_list.begin(); e_iter != enemy_list.end(); ) {
			if ((*iter).cur_position_ == (*e_iter).cur_position_ && (*iter).friendly_) {
				(*e_iter).Hit();
				if (((*e_iter).hp_) == 0) {
					e_iter=enemy_list.erase(e_iter);
				}
				iter=bullet_list.erase(iter);
				break;
			}
			++e_iter;
		}
		if(iter!=bullet_list.end())++iter;
	}
	if (enemy_list.empty()) {
		return 2;
	}
	return 0;
}