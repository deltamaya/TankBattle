#include <graphics.h>
#include <conio.h>
//负责人：王大
//功能：展示开发者成员界面，可以返回主界面
//参数：void
//返回值：void
void Help() {
    // 清除屏幕
    cleardevice();

    // 显示帮助文本
    IMAGE img;
    loadimage(&img, "./TankBattle/images/帮助.png", getwidth(), getheight());

    // 显示图片
    putimage(0, 0, &img);

    // 等待用户输入以返回主菜单
    _getch();
}

//负责人：王大
//功能：展示帮助页面，向玩家展示操作玩法，可以返回主界面
//参数：void
//返回值：void
void Developers() {
    // 清除屏幕
    cleardevice();

    // 加载开发者成员图片
    IMAGE img;
    loadimage(&img, "./TankBattle/images/开发者.png", getwidth(), getheight());

    // 显示图片
    putimage(0, 0, &img);

    // 等待用户输入以返回主菜单
    _getch();
}
