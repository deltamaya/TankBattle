#include "ui.h"
ui TankBattle, menu, level, setting, developer, help, show, stop, win, lose;

int MainMenu() {
    menu.begin();
    menu.clear();
    menu.add_image("./interface\\MainInterface.jpg");
    menu.add_button(340, 240, 120, 40, "GameStart");
    menu.add_button(340, 280, 120, 40, "Setting");
    menu.add_button(340, 320, 120, 40, "Help");
    menu.add_button(340, 360, 120, 40, "Developer");
    menu.add_button(340, 400, 120, 40, "Exit");
    menu.end();
    enum { GameStart, Setting, Help, Developer, Exit };
    switch (menu.check_button()) {
        case GameStart:
            return GameStart;
        case Setting:
            return Setting;
        case Help:
            return Help;
        case Developer:
            return Developer;
        case Exit:
            return Exit;
    }
}

bool ContinueGame() {
    int result = MessageBox(GetHWnd(), "你有未完成的游戏，是否继续？", "提示", MB_YESNO);
    if (result == IDYES) {
        return true;
    } else {
        return false;
    }
}

int LevelSelect() {
    level.begin();
    level.clear();
    level.add_button(40, 150, 150, 300, "Return");
    level.add_button(230, 150, 150, 300, "Ruins");
    level.add_button(420, 150, 150, 300, "Jungle");
    level.add_button(610, 150, 150, 300, "MilitaryBase");
    level.end();
    enum { Return, Ruins, Jungle, MilitaryBase };
    switch (level.check_button()) {
        case Return:
            return Return;
        case Ruins:
            return Ruins;
        case Jungle:
            return Jungle;
        case MilitaryBase:
            return MilitaryBase;
    }
}

void Settings() {  // 函数原型：void Settings(int& music_volume,int& sound_volume);
    while (true) {
        setting.begin();
        setting.clear();
        setting.add_button(40, 150, 150, 300, "Return");
        setting.add_button(230, 150, 150, 300, "AddVolume");
        setting.add_button(420, 150, 150, 300, "ReduceVolume");
        setting.end();
        enum { Return, AddVolume, ReduceVolume };
        switch (setting.check_button()) {
            case Return:
                return;  // 哪里调用就返回哪里
            case AddVolume:
                // 增加音量
                break;
            case ReduceVolume:
                // 减小音量
                break;
        }
    }
}

void Developers() {
    while (true) {
        developer.begin();
        developer.clear();
        developer.add_image("./images\\developer.png");
        developer.add_button(0, 0, 800, 600);
        developer.end();
        if (developer.check_button() == 0)
            return;
    }
}

void Help() {
    while (true) {
        help.begin();
        help.clear();
        help.add_image("./images\\help.png");
        help.add_button(0, 0, 800, 600);
        help.end();
        if (help.check_button() == 0)
            return;
    }
}

void GameStop();
void GameWin();
void GameLose();
void ShowMap() {
    int level = 1, enemy_num = 1, play_time = 100, hp = 999;
    std::string level_str = "Level: " + std::to_string(level);
    std::string enemy_num_str = "Enemy: " + std::to_string(enemy_num);
    std::string play_time_str = "Time: " + std::to_string(play_time);
    std::string hp_str = "HP: " + std::to_string(hp);
    while (true) {
        show.begin();
        show.clear();
        show.add_button(40, 150, 150, 300, "GameStop");
        show.add_button(230, 150, 150, 300, "GameWin");
        show.add_button(420, 150, 150, 300, "GameLose");
        show.add_button(600, 0, 200, 150);
        show.add_button(600, 150, 200, 450);
        settextcolor(WHITE);
        settextstyle(20, 0, "宋体");
        outtextxy(600, 50, level_str.c_str());
        outtextxy(600, 100, enemy_num_str.c_str());
        outtextxy(600, 200, play_time_str.c_str());
        outtextxy(600, 250, hp_str.c_str());
        show.end();
        enum { Stop, Win, Lose };
        switch (show.check_button()) {
            case Stop:
                GameStop();
                break;
            case Win:
                GameWin();
                break;
            case Lose:
                GameLose();
                break;
        }
    }
}

void GameStop() {
    while (true) {
        stop.begin();
        stop.clear();
        stop.add_button(170, 270, 80, 60, "Continue");
        stop.add_button(270, 270, 80, 60, "Save");
        stop.add_button(370, 270, 80, 60, "Setting");
        stop.add_button(470, 270, 80, 60, "Exit");
        enum { Continue, Save, Setting, Exit };
        stop.end();
        switch (stop.check_button()) {
            case Continue:
                return;
            case Save:
                // 保存游戏
                break;
            case Setting:
                Settings();
                break;
            case Exit:
                exit(0);
        }
    }
}

void test_ui();
void GameWin() {  // 函数原型：void GameWin(const time_t& play_time);
    int play_time = 100;
    std::string time = std::to_string(play_time);
    std::string time_str = "You win in " + time + "seconds!";
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(60, 0, "黑体");
    outtextxy(90, 310, time_str.c_str());
    while (true) {
        win.begin();
        win.clear();
        win.add_image("./interface\\GameOver.jpg");
        win.add_button(200, 400, 170, 50, "ToHome");
        win.add_button(430, 400, 170, 50, "Exit");
        win.end();
        switch (win.check_button()) {
            case 0:
                test_ui();
            case 1:
                exit(0);
        }
    }
}

void GameLose() {
    while (true) {
        lose.begin();
        lose.clear();
        lose.add_image("./interface\\GameOver.jpg");
        lose.add_button(200, 400, 170, 50, "ToHome");
        lose.add_button(430, 400, 170, 50, "Exit");
        lose.end();
        switch (lose.check_button()) {
            case 0:
                test_ui();
            case 1:
                exit(0);
        }
    }
}

void test_ui() {  // menu, level, setting, developer, help
    int flag = 0;
    while (true) {
        switch (MainMenu()) {
            case 0:
                if (ContinueGame()) {
                    // 继续游戏
                } else {
                    while (true) {
                        switch (LevelSelect()) {
                            case 0:
                                flag = 1;
                                break;
                            case 1:
                                // Ruins
                                break;
                            case 2:
                                // Jungle
                                break;
                            case 3:
                                // MilitaryBase
                                break;
                        }
                        if (flag == 1) {
                            flag = 0;
                            break;
                        }
                    }
                }
                break;
            case 1:
                Settings();
                break;
            case 2:
                Help();
                break;
            case 3:
                Developers();
                break;
            case 4:
                exit(0);
        }
    }
}

void test_game() {
    ShowMap();
}

int main() {
    TankBattle.InitUI("Tank Battle", 800, 600);
    test_game();
    return 0;
}