//#include <graphics.h>
//#include <conio.h>
////负责人：王大
////功能：展示开发者成员界面，可以返回主界面
////参数：void
////返回值：void
//void Help() {
//    // 清除屏幕
//    cleardevice();
//
//    // 显示帮助文本
//    IMAGE img;
//    loadimage(&img, "./images\\help.png", getwidth(), getheight());
//
//    // 显示图片
//    putimage(0, 0, &img);
//
//    // 等待用户输入以返回主菜单
//    while (1) {
//        if (_kbhit())break;
//    }
//}
//
////负责人：王大
////功能：展示帮助页面，向玩家展示操作玩法，可以返回主界面
////参数：void
////返回值：void
//void Developers() {
//    // 清除屏幕
//    cleardevice();
//
//    // 加载开发者成员图片
//    IMAGE img;
//    loadimage(&img, "./images\\developer.png", getwidth(), getheight());
//
//    // 显示图片
//    putimage(0, 0, &img);
//
//    // 等待用户输入以返回主菜单
//    while (1) {
//        if (_kbhit())break;
//    }
//}
//bool ContinueGame() {
//    int result = MessageBox(GetHWnd(), "你有未完成的游戏，是否继续？", "提示", MB_YESNO);
//    if (result == IDYES) {
//        return true;
//    }
//    else {
//        return false;
//    }
//}