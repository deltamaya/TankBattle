//#include <graphics.h>
//#include <conio.h>
////�����ˣ�����
////���ܣ�չʾ�����߳�Ա���棬���Է���������
////������void
////����ֵ��void
//void Help() {
//    // �����Ļ
//    cleardevice();
//
//    // ��ʾ�����ı�
//    IMAGE img;
//    loadimage(&img, "./images\\help.png", getwidth(), getheight());
//
//    // ��ʾͼƬ
//    putimage(0, 0, &img);
//
//    // �ȴ��û������Է������˵�
//    while (1) {
//        if (_kbhit())break;
//    }
//}
//
////�����ˣ�����
////���ܣ�չʾ����ҳ�棬�����չʾ�����淨�����Է���������
////������void
////����ֵ��void
//void Developers() {
//    // �����Ļ
//    cleardevice();
//
//    // ���ؿ����߳�ԱͼƬ
//    IMAGE img;
//    loadimage(&img, "./images\\developer.png", getwidth(), getheight());
//
//    // ��ʾͼƬ
//    putimage(0, 0, &img);
//
//    // �ȴ��û������Է������˵�
//    while (1) {
//        if (_kbhit())break;
//    }
//}
//bool ContinueGame() {
//    int result = MessageBox(GetHWnd(), "����δ��ɵ���Ϸ���Ƿ������", "��ʾ", MB_YESNO);
//    if (result == IDYES) {
//        return true;
//    }
//    else {
//        return false;
//    }
//}