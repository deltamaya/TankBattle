#include <graphics.h>
#include <conio.h>
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
