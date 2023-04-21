#include "ui.h"

ui TankBattle, menu, level, setting, developer, help, show, stop, win, lose;
int flag_music_ = 1;
click click_;
GameBegin begin_;
GameEnd end_;
OpenFire fire;

int MainMenu() {
    while (true) {
        menu.begin();
        menu.clear();
        menu.PrintButton();
        menu.PrintImage();
        menu.end();
        enum { GameStart, Setting, Help, Developer, Exit, Tank };
        switch (menu.CheckButton()) {
            case GameStart:
                click_.play();
                return 0;
            case Setting:
                click_.play();
                return 1;
            case Help:
                click_.play();
                return 2;
            case Developer:
                click_.play();
                return 3;
            case Exit:
                click_.play();
                return 4;
            case Tank:
                fire.play();
                break;
        }
    }
}

int LevelSelect() {
    level.begin();
    level.clear();
    level.PrintImage();
    level.PrintButton();
    level.end();
    enum { Return, Ruins, Jungle, MilitaryBase };
    int ret = -1;
    while (1) {
        ret = level.CheckButton();
        if (ret != -1)
            break;
    }
    switch (ret) {
        case Return:
            click_.play();
            return 0;
        case Ruins:
            click_.play();
            begin_.play();
            return 1;
        case Jungle:
            click_.play();
            begin_.play();
            return 2;
        case MilitaryBase:
            click_.play();
            begin_.play();
            return 3;
    }
}

void Settings() {
    while (true) {
        setting.begin();
        setting.clear();
        if (flag_music_ == 1) {
            setting.PrintImage(0);
        } else {
            setting.PrintImage(1);
        }
        setting.PrintButton();
        setting.end();
        enum { Return, AddVolume, ReduceVolume };
        switch (setting.CheckButton()) {
            case Return:
                click_.play();
                return;
            case AddVolume:
                click_.click_.play();
                flag_music_ = 1;
                break;
            case ReduceVolume:
                flag_music_ = 0;
                break;
        }
    }
}

void Developers() {
    int flag = 0;
    while (true) {
        developer.begin();
        developer.clear();
        developer.PrintButton();
        switch (flag) {
            case 0:
                developer.PrintImage(0);
                break;
            case 1:
                developer.PrintImage(1);
                break;
            case 2:
                developer.PrintImage(2);
                break;
            case 3:
                developer.PrintImage(3);
                break;
            case 4:
                developer.PrintImage(4);
                break;
            case 5:
                developer.PrintImage(5);
                break;
            case 6:
                developer.PrintImage(6);
                break;
            case 7:
                developer.PrintImage(7);
                break;
            case 8:
                developer.PrintImage(8);
                break;
        }
        developer.end();
        switch (developer.CheckButton()) {
            case 0:
                click_.play();
                if (flag == 1) {
                    flag = 0;
                    break;
                }
                flag = 1;
                break;
            case 1:
                click_.play();
                if (flag == 2) {
                    flag = 0;
                    break;
                }
                flag = 2;
                break;
            case 2:
                click_.play();
                if (flag == 3) {
                    flag = 0;
                    break;
                }
                flag = 3;
                break;
            case 3:
                click_.play();
                if (flag == 4) {
                    flag = 0;
                    break;
                }
                flag = 4;
                break;
            case 4:
                click_.play();
                if (flag == 5) {
                    flag = 0;
                    break;
                }
                flag = 5;
                break;
            case 5:
                click_.play();
                if (flag == 6) {
                    flag = 0;
                    break;
                }
                flag = 6;
                break;
            case 6:
                click_.play();
                if (flag == 7) {
                    flag = 0;
                    break;
                }
                flag = 7;
                break;
            case 7:
                click_.play();
                if (flag == 8) {
                    flag = 0;
                    break;
                }
                flag = 8;
                break;
            case 8:
                click_.play();
                return;
            case 9:
                click_.play();
                return;
            case 10:
                click_.play();
                return;
            case 11:
                click_.play();
                return;
        }
    }
}

void Help() {
    while (true) {
        help.begin();
        help.clear();
        help.PrintImage();
        help.PrintButton();
        help.end();
        if (help.CheckButton() == 0) {
            click_.play();
            return;
        }
    }
}

void GameWin() {
    std::string time_str = "YOU WON!!!";
    end_.play();
    while (true) {
        win.begin();
        win.clear();
        win.PrintImage();
        win.PrintButton();
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        settextstyle(60, 0, "黑体");
        outtextxy(270, 310, time_str.c_str());
        win.end();
        switch (win.CheckButton()) {
            case 0:
                click_.play();
                return;
            case 1:
                click_.play();
                exit(0);
        }
    }
}

void GameLose() {
    std::string lose_str = "You lose!";
    end_.play();
    while (true) {
        lose.begin();
        lose.clear();
        lose.PrintImage();
        lose.PrintButton();
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        settextstyle(60, 0, "黑体");
        outtextxy(290, 310, lose_str.c_str());
        lose.end();
        switch (lose.CheckButton()) {
            case 0:
                click_.play();
                return;
            case 1:
                click_.play();
                exit(0);
        }
    }
}

void GameStop() {
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return;
        }
    }
}