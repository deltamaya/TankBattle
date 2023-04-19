#include "ui.h"

ui TankBattle, menu, level, setting, developer, help, show, stop, win, lose;

class click {
   public:
    static int flag_music_;
    music click_;
    click() : click_("click.wav", 1000){};
    void play() {
        click_.play();
        click_.close();
        if (flag_music_) {
            click_.play();
        }
    }
};
int click::flag_music_ = 1;
click click_;

int MainMenu() {
    while(true){
        menu.begin();
        menu.clear();
        menu.PrintImage();
        menu.PrintButton();
        menu.end();
        enum { GameStart, Setting, Help, Developer, Exit };
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
        }
    }
}

int LevelSelect() {
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
        click_.play();
        cout << "Return" << endl;
        return 0;
    case Ruins:
        click_.play();
        cout << "Ruins" << endl;
        return 1;
    case Jungle:
        click_.play();
        cout << "Jungle" << endl;
        return 2;
    case MilitaryBase:
        click_.play();
        cout << "MilitaryBase" << endl;
        return 3;
    }
}

void Settings() {
    while (true) {
        setting.begin();
        setting.clear();
        setting.PrintButton();
        setting.end();
        enum { Return, AddVolume, ReduceVolume };
        switch (setting.CheckButton()) {
        case Return:
            click_.play();
            return;
        case AddVolume:
            click_.play();
            click::flag_music_ = 1;
            break;
        case ReduceVolume:
            click::flag_music_ = 0;
            break;
        }
    }
}

void Developers() {
    while (true) {
        developer.begin();
        developer.clear();
        developer.PrintImage();
        developer.PrintButton();
        developer.end();
        if (developer.CheckButton() == 0){
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
        if (help.CheckButton() == 0){
            click_.play();
            return;
        }
    }
}

void GameWin() {
    std::string time_str = "YOU WON!!!!";
    while (true) {
        win.begin();
        win.clear();
        win.PrintImage();
        win.PrintButton();
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        settextstyle(60, 0, "黑体");
        outtextxy(170, 310, time_str.c_str());
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
