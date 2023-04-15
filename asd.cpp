#include"architechture.h"

//+main.cpp�е�������ͼ
//�����ˣ�asd
//���ܣ���ʼ����ͼ��ʹ��level_x��ʼ��map,��ʼ������λ�ã����ˣ���ң�����ʱ��
//�������ؿ�id,���������ӵ�������ң�����λ�ã���ͼ������ʱ��
//����ֵ��void
void InitMap(const int& level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player,
	Position& base_position, vector<vector<int>>& map, time_t& play_time)
{
	// ����level_x���µ�ͼ
	// ��δʵ��

	// ��ȡ�ĵ�ͼ�Ŀ�͸�
	int map_height = map.size();
	int map_width = map[0].size();
	// ������ͼ�����Ի���ң����ˣ����ص�λ��
	// �ݶ� 
	// 0 ��SPACE	��map�Ѿ���ʼ��
	// 1 ��WALL		��map�Ѿ���ʼ��
	// 2 ��BASE 	��map�Ѿ���ʼ��
	// 3 ��CAMP		��map�Ѿ���ʼ��
	// 4 ��GRASS     
	// 5 ���з�̹��		  ��Ҫ��ʼ��
	// 6 �����̹��       ��Ҫ��ʼ��
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			if (map[i][j] == 6) {
				// ���̹��
				// �������̹��λ��
				player.cur_position_.x_ = i;
				player.cur_position_.y_ = j;
			}
			else if (map[i][j] == 5) {
				// �з�̹��
				// ���µз�̹��λ��
				enemy_list.push_back(Enemy(enemy_list, Position(i, j), UP));
			}
		}
	}


}

//***��Ҫ***
//�����ˣ�asd
//���ܣ���ȡ������룬������Ϸ״̬��reload ,move�ȣ�
//�������ؿ�id,���������ӵ�������ң�����λ�ã���ͼ������ʱ��
//����ֵ��void
void Update(const int level, list<Enemy>& enemy_list, list<Bullet>& bullet_list, Player& player,
	const Position& base_position, vector<vector<int>>& map, time_t& play_time)
{
	// ����ƶ�
	player.Move(map);

	// �з�̹�˵����������ڸ��µ��˵�λ��
	list<Enemy>::iterator enemy_iterator = enemy_list.begin();
	while (enemy_iterator != enemy_list.end()) {
		// ��ǰ���̹���Ѿ�������
		if (enemy_iterator->hp_ == 0) {
			// ̹��λ�ø���Ϊ�յ�
			map[enemy_iterator->cur_position_.x_][enemy_iterator->cur_position_.y_] = 0;
			// ɾ����̹��
			enemy_list.erase(enemy_iterator++);
			continue;
		}
		// �з�̹���ƶ�
		enemy_iterator->Move(map, player, base_position);
		// ������
		enemy_iterator->FireCheck(map, bullet_list, player, base_position);
		enemy_iterator->Fire(bullet_list);
	}

	// �ӵ��ĵ����������ڸ����ӵ���λ��
	list<Bullet>::iterator bullet_iterator = bullet_list.begin();
	// �����ӵ����������ӵ���λ���ж϶�Ӧ��״̬
	while (bullet_iterator != bullet_list.end()) {
		// ��ȡ�ӵ�����һ��λ��
		auto next = bullet_iterator->cur_position_ + DIRECTION[bullet_iterator->direction_];
		// �����ӵ�����һ��λ�ý��ж�Ӧ�Ĳ���
		switch (map[next.x_][next.y_])
		{
		case SPACE:  // �յ� 
			// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// �����ӵ�λ��
			bullet_iterator->cur_position_ = next;
			// �ӵ�������һ��λ�ã���ǰλ������Ϊ�ӵ�
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 7;
			// ��һ���ӵ�
			bullet_iterator++;
			break;
		case WALL:  // ���Դݻٵ�ǽ
			// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// �����ӵ�λ��
			bullet_iterator->cur_position_ = next;
			// ��һ���ӵ�
			bullet_list.erase(bullet_iterator++);
			break;
		case BASE:  // ���ɴݻٵ�ǽ
			// ��ǰλ������Ϊ�յ�
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			//  �ӵ���ʧ
			bullet_list.erase(bullet_iterator++);
			break;
		case CAMP:  // �ӵ������Ӫλ��
			if (bullet_iterator->friendly_) {
				// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// �����ӵ�λ��
				bullet_iterator->cur_position_ = next;
				// ��һ���ӵ�
				bullet_iterator++;
			}
			else {
				// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// ��ǰλ�û����Ѿ����ݻ٣���ǰλ������Ϊ�յ�
				map[next.x_][next.y_] = 0;
				// �ӵ�Ҳ��ʧ
				bullet_list.erase(bullet_iterator++);
			}
		case GRASS:  // �ݵ�, Ч��Ϊ����
			// ��ǰ�ӵ�������ݵ�/�Ѿ�����ݵ��򲻻�ִ��
			if (map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] != 0)
				// �ӵ�λ������Ϊ�յأ��ӵ���ǰ����һ��λ��
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			bullet_iterator->cur_position_ = next;
			// ������ص��ݵأ��������ӵ�����
			if (next == player.cur_position_) {
				player.Hit();
				bullet_list.erase(bullet_iterator++);
			}
			else bullet_iterator++;
			break;
		case 5:  // �ӵ�����з�̹��λ��
			// �ӵ������Ƶģ�̹�˲���ʧ
			if (bullet_iterator->friendly_) {
				// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// �����ӵ�λ��
				bullet_iterator->cur_position_ = next;
				bullet_iterator++;
			}
			else { // ����з�̹��
				// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
				map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
				// �ҵ������е�̹��
				list<Enemy>::iterator enemy_it = enemy_list.begin();
				while (enemy_it != enemy_list.end())
				{
					// �ҵ�̹���˳�ѭ��
					if (enemy_it->cur_position_ == next)
						break;
					// ��һ��̹��
					enemy_it++;
				}
				// ̹�˵�Hp����
				enemy_it->Hit();
				// �ӵ���ʧ
				bullet_list.erase(bullet_iterator++);
			}
			break;
		case 6:   // �ӵ��������̹��λ��
			// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// ����ܵ��˺�
			player.Hit();
			// �ӵ����к���ʧ
			bullet_list.erase(bullet_iterator++);
			break;

			break;
		case 7: // �ӵ���ײ�����յش���
			// �ӵ�ȥ��һ��λ�ã���ǰλ������Ϊ�յ�
			map[bullet_iterator->cur_position_.x_][bullet_iterator->cur_position_.y_] = 0;
			// �����ӵ�λ��
			bullet_iterator->cur_position_ = next;
			// �ӵ�������һ��λ�ã���ǰλ������Ϊ�ӵ�
			map[next.x_][next.y_] = 7;
			// ��һ���ӵ�
			bullet_iterator++;
			break;
		default:
			break;
		}
	}
}


