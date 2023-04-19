#include "ui.h"

ui TankBattle, menu, level, setting, developer, help, show, stop, win, lose;

int MainMenu() {  // ������
    menu.begin();
    menu.clear();
    menu.PrintImage();
    menu.PrintButton();
    menu.end();
    enum { GameStart, Setting, Help, Developer, Exit };
    switch (menu.CheckButton()) {
    case GameStart:
        return 0;
    case Setting:
        return 1;
    case Help:
        return 2;
    case Developer:
        return 3;
    case Exit:
        return 4;
    }
}

int LevelSelect() {  // ѡ��ؿ�
    level.begin();
    level.clear();
    level.PrintButton();
    level.end();
    enum { Return, Ruins, Jungle, MilitaryBase };
    int ret = -1;
    while (1) {
        ret=level.CheckButton();
        if (ret != -1)break;
    }
    switch (ret) {
    case Return:
        cout << "Return" << endl;
        return 0;
    case Ruins:
        cout << "Ruins" << endl;
        return 1;
    case Jungle:
        cout << "Jungle" << endl;
        return 2;
    case MilitaryBase:
        cout << "MilitaryBase" << endl;
        return 3;
    }
}

void Settings() {  // ����ԭ�ͣ�void Settings(int& music_volume,int& sound_volume);���ĸ�������ֻ����ʾ������
    while (true) {
        setting.begin();
        setting.clear();
        setting.PrintButton();
        setting.end();
        enum { Return, AddVolume, ReduceVolume };
        switch (setting.CheckButton()) {
        case Return:
            return;  // ������þͷ�������
        case AddVolume:
            // ��������
            break;
        case ReduceVolume:
            // ��С����
            break;
        }
    }
}

void Developers() {  // ������
    while (true) {
        developer.begin();
        developer.clear();
        developer.PrintImage();
        developer.PrintButton();
        developer.end();
        if (developer.CheckButton() == 0)
            return;
    }
}

void Help() {  // ����
    while (true) {
        help.begin();
        help.clear();
        help.PrintImage();
        help.PrintButton();
        help.end();
        if (help.CheckButton() == 0)
            return;
    }
}

//void ShowGameUI() {                                           // ��ʾ��Ϸ����
//    int level = 1, enemy_num = 1, play_time = 100, hp = 999;  // ������Ҫ�������Ĳ���������ֻ�ǲ���
//    std::string level_str = "Level: " + std::to_string(level);
//    std::string enemy_num_str = "Enemy: " + std::to_string(enemy_num);
//    std::string play_time_str = "Time: " + std::to_string(play_time);
//    std::string hp_str = "HP: " + std::to_string(hp);
//    while (true) {
//        show.begin();
//        show.clear();
//        // ������Ϸ����
//
//        // ������Ϸ�����
//        show.PrintButton();
//        settextcolor(WHITE);
//        settextstyle(20, 0, "����");
//        outtextxy(600, 50, level_str.c_str());
//        outtextxy(600, 100, enemy_num_str.c_str());
//        outtextxy(600, 200, play_time_str.c_str());
//        outtextxy(600, 250, hp_str.c_str());
//        show.end();
//    }
//}
//
//void test_ui() {  // menu, level, setting, developer, help
//    int flag = 0;
//    while (true) {
//        switch (MainMenu()) {
//        case 0:
//            while (true) {
//                switch (LevelSelect()) {
//                case 0:
//                    flag = 1;
//                    break;
//                case 1:  // ��һ��
//                    // Ruins
//                    break;
//                case 2:  // �ڶ���
//                    // Jungle
//                    break;
//                case 3:  // ������
//                    // MilitaryBase
//                    break;
//                }
//                if (flag == 1) {
//                    flag = 0;
//                    break;
//                }
//            }
//            break;
//        case 1:
//            Settings();
//            break;
//        case 2:
//            Help();
//            break;
//        case 3:
//            Developers();
//            break;
//        case 4:
//            exit(0);
//        }
//    }
//}

//int main() {
//    TankBattle.InitUI("Tank Battle", 800, 600);  // ��ʼ������
    //menu.add_button(340, 240, 120, 40, "GameStart");
    //menu.add_button(340, 280, 120, 40, "Setting");
    //menu.add_button(340, 320, 120, 40, "Help");
    //menu.add_button(340, 360, 120, 40, "Developer");
    //menu.add_button(340, 400, 120, 40, "Exit");
    //level.add_button(40, 150, 150, 300, "Return");
    //level.add_button(230, 150, 150, 300, "Ruins");
    //level.add_button(420, 150, 150, 300, "Jungle");
    //level.add_button(610, 150, 150, 300, "MilitaryBase");
    //setting.add_button(40, 150, 150, 300, "Return");
    //setting.add_button(230, 150, 150, 300, "AddVolume");
    //setting.add_button(420, 150, 150, 300, "ReduceVolume");
    //developer.add_button(0, 0, 800, 600);
    //help.add_button(0, 0, 800, 600);
    //show.add_button(600, 0, 200, 150);
    //show.add_button(600, 150, 200, 450);
//    test_ui();
//    return 0;
//}

void GameWin() {  // ����ԭ�ͣ�void GameWin(const time_t& play_time);
    int play_time = 100;
    std::string time = std::to_string(play_time);
    std::string time_str = "YOU WON!!!!";
    while (true) {
        win.begin();
        win.clear();
        win.PrintImage();
        win.PrintButton();
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        settextstyle(60, 0, "����");
        outtextxy(170, 310, time_str.c_str());
        win.end();
        switch (win.CheckButton()) {
        case 0:
            return;
        case 1:
            exit(0);
        }
    }
}

void GameLose() {
    std::string lose_str = "You lose!";
    while (true) {
        lose.begin();
        lose.clear();
        lose.PrintImage();
        lose.PrintButton();
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        settextstyle(60, 0, "����");
        outtextxy(290, 310, lose_str.c_str());
        lose.end();
        switch (lose.CheckButton()) {
        case 0:
            return;
        case 1:
            exit(0);
        }
    }
}

void GameStop() {
    while (true) {
        stop.begin();
        stop.clear();
        stop.AddButton(170, 270, 80, 60, "Continue");
        stop.AddButton(370, 270, 80, 60, "Setting");
        stop.AddButton(470, 270, 80, 60, "Exit");
        enum { Continue, Setting, Exit };
        stop.end();
        switch (stop.CheckButton()) {
        case Continue:
            return;
        case Setting:
            Settings();
            break;
        case Exit:
            exit(0);
        }
    }
}