#include <graphics.h>
#include <conio.h>
#include <windows.h>
//�����ˣ�����
//���ܣ�չʾ�����߳�Ա���棬���Է���������
//������void
//����ֵ��void
void Help() {
    // �����Ļ
    cleardevice();

    // ��ʾ�����ı�
    IMAGE img;
    loadimage(&img, "./TankBattle/images/����.png", getwidth(), getheight());

    // ��ʾͼƬ
    putimage(0, 0, &img);

    // �ȴ��û������Է������˵�
    _getch();
}

//�����ˣ�����
//���ܣ�չʾ����ҳ�棬�����չʾ�����淨�����Է���������
//������void
//����ֵ��void
void Developers() {
    // �����Ļ
    cleardevice();

    // ���ؿ����߳�ԱͼƬ
    IMAGE img;
    loadimage(&img, "./TankBattle/images/������.png", getwidth(), getheight());

    // ��ʾͼƬ
    putimage(0, 0, &img);

    // �ȴ��û������Է������˵�
    _getch();
}



 bool ContinueGame() {
     int result = MessageBox(GetHWnd(), "����δ��ɵ���Ϸ���Ƿ������", "��ʾ", MB_YESNO);
     if (result == IDYES) {
         return true;
     }
     else {
         return false;
     }
 }

#if
int main() {
    initgraph(640, 480);
        if (ContinueGame()) {
            outtextxy(100, 200, "������Ϸ");
        }
        else {
            outtextxy(100, 200, "�˳���Ϸ");
        }
    _getch();
    closegraph();
    return 0;
}
#endif // 0