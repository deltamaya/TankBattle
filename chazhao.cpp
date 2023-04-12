#include<iostream>
using namespace std;
int main()
{
	char str1[60];
	char str2[30];
	char str3[30];
	int i, len,count=0;
	char c; //主串字符
	char* p;//接收比较字符地址
	cout << "请依次输入查找串和替换串，空格或者回车隔开：";
	cin >> str2;
	cin >> str3;
	i = 0;
	c = getchar();
	while ((c = getchar() != '\n' && c != EOF))
	{
		str1[i] = c;
		i++;
	}
	str1[i] = '\0';
	p = strstr(str1, str2);
	while (p)
	{
		count++;
		strReplace(p, strlen(str2), str3);
		p = p + strlen(str3);
		p = strstr(p,str2);

	}
	cout << "替换后的字符串为：" << str1 << endl;
}