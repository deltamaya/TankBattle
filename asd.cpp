#include"architechture.h"

//+main.cpp中的三个地图
//负责人：asd
//功能：初始化地图，使用level_x初始化map,初始化基地位置，敌人，玩家，游玩时间
//参数：关卡id,敌人链表，子弹链表，玩家，基地位置，地图，游玩时间
//返回值：void
void InitMap(const int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player,
	Position& base_position, vector<vector<int>>& map, time_t& play_time)
{
	// 根据level_x更新地图
	// 暂未实现

	// 获取的地图的宽和高
	int map_height = map.size();
	int map_width = map[0].size();
	// 遍历地图，初试化玩家，敌人，基地的位置
	// 暂定 
	// 0 ：SPACE	随map已经初始化
	// 1 ：WALL		随map已经初始化
	// 2 ：BASE 	随map已经初始化
	// 3 ：CAMP		随map已经初始化
	// 4 ：GRASS     
	// 5 ：敌方坦克		  需要初始化
	// 6 ：玩家坦克       需要初始化
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			if (map[i][j] == 6) {
				// 玩家坦克
				// 更新玩家坦克位置
				player.cur_position_.x_ = i;
				player.cur_position_.y_ = j;
			}
			else if (map[i][j] == 5) {
				// 敌方坦克
				// 更新敌方坦克位置
				enemy_list.push_back(new Enemy(enemy_list, Position(i, j), UP));
			}
		}
	}


}

//***重要***
//负责人：asd
//功能：获取玩家输入，更新游戏状态（reload ,move等）
//参数：关卡id,敌人链表，子弹链表，玩家，基地位置，地图，游玩时间
//返回值：void
void Update(const int level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player,
	const Position& base_position, vector<vector<int>>& map, time_t& play_time)
{
	// 玩家移动
	player.Move(map);

	// 敌方坦克迭代器，用于更新敌人的位置
	list<Enemy>::iterator enemy_iterator = enemy_list.begin();
	while (enemy_iterator != enemy_list.end()) {
		// 当前这架坦克已经被消灭
		if (enemy_iterator->hp_ == 0) {
			// 坦克位置跟新为空地
			map[enemy_iterator->cur_position_.x_][enemy_iterator->cur_position_.y_] = 0;
			// 删除该坦克
			enemy_list.erase(enemy_iterator++);
			continue;
		}
		// 敌方坦克移动
		enemy_iterator->Move(map, player, base_position);
		// 开火检查
		enemy_iterator->FireCheck(map, bullet_list, player, base_position);
		enemy_iterator->Fire(bullet_list);
	}

	// 子弹的迭代器，用于更新子弹的位置
	list<Bullet>::iterator bullet_iterator = bullet_list.begin();
	// 遍历子弹链表，更新子弹方位，判断对应的状态
	while (bullet_iterator != bullet_list.end()) {
		// 获取子弹的下一个位置
		auto next = bullet_iterator->cur_position_ + DIRECTION[bullet_iterator->direction_];
		// 根据子弹的下一个位置进行对应的操作
		switch (map[next.x_][next.y_])
		{
		case SPACE:  // 空地 
			// 子弹去下一个位置，当前位置设置为空地
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// 更新子弹位置
			bullet_iterator->cur_position_ = next;
			// 子弹到达下一个位置，当前位置设置为子弹
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 7;
			// 下一个子弹
			bullet_iterator++;
			break;
		case WALL:  // 可以摧毁的墙
			// 子弹去下一个位置，当前位置设置为空地
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// 更新子弹位置
			bullet_iterator->cur_position_ = next;
			// 下一个子弹
			bullet_list.erase(bullet_iterator++);
			break;
		case BASE:  // 不可摧毁的墙
			// 当前位置设置为空地
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			//  子弹消失
			bullet_list.erase(bullet_iterator++);
			break;
		case CAMP:  // 子弹到达大本营位置
			if (bullet_iterator->friendly_) {
				// 子弹去下一个位置，当前位置设置为空地
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// 更新子弹位置
				bullet_iterator->cur_position_ = next;
				// 下一个子弹
				bullet_iterator++;
			}
			else {
				// 子弹去下一个位置，当前位置设置为空地
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// 当前位置基地已经被摧毁，当前位置设置为空地
				map[next.x_][next.y_] = 0;
				// 子弹也消失
				bullet_list.erase(bullet_iterator++);
			}
		case GRASS:  // 草地, 效果为隐藏
			// 当前子弹将进入草地/已经进入草地则不会执行
			if (map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] != 0)
				// 子弹位置设置为空地，子弹将前往下一个位置
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			bullet_iterator->cur_position_ = next;
			// 玩家隐藏到草地，被敌人子弹击中
			if (next == player.cur_position_) {
				player.Hit();
				bullet_list.erase(bullet_iterator++);
			}
			else bullet_iterator++;
			break;
		case 5:  // 子弹到达敌方坦克位置
			// 子弹是友善的，坦克不消失
			if (bullet_iterator->friendly_) {
				// 子弹去下一个位置，当前位置设置为空地
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// 更新子弹位置
				bullet_iterator->cur_position_ = next;
				bullet_iterator++;
			}
			else { // 消灭敌方坦克
				// 子弹去下一个位置，当前位置设置为空地
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// 找到被击中的坦克
				list<Enemy>::iterator enemy_it = enemy_list.begin();
				while (enemy_it != enemy_list.end())
				{
					// 找到坦克退出循环
					if (enemy_it->cur_position_ == next)
						break;
					// 下一个坦克
					enemy_it++;
				}
				// 坦克的Hp降低
				enemy_it->Hit();
				// 子弹消失
				bullet_list.erase(bullet_iterator++);
			}
			break;
		case 6:   // 子弹到达玩家坦克位置
			// 子弹去下一个位置，当前位置设置为空地
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// 玩家受到伤害
			player.Hit();
			// 子弹击中后消失
			bullet_list.erase(bullet_iterator++);
			break;

			break;
		case 7: // 子弹相撞（当空地处理）
			// 子弹去下一个位置，当前位置设置为空地
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// 更新子弹位置
			bullet_iterator->cur_position_ = next;
			// 子弹到达下一个位置，当前位置设置为子弹
			map[next.x_][next.y_] = 7;
			// 下一个子弹
			bullet_iterator++;
			break;
		default:
			break;
		}
	}
}


