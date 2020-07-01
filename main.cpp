#include <iostream>
#include<string>
#include <cassert>
#include<stdlib.h>
#include<sstream>
#include<conio.h>
#include<string.h>
#include<stack>
#include <fstream>

using namespace std;
const char* keyword[20] = { "program","var","integer","real","char","begin","end","if","then","else","while","do","ifend","return" }; //�ؼ��ֱ�
char jiefuchart[20] = { ',',':',';','=','*','/','+','-','.','(',')','>','<','@','[',']','{','}' }; //�����
string changshubiao[100];    //��¼����
string biaoshifubiao[100];   //��¼��ʾ��
static int index = 0;
static int tag = 0;
static int tag1 = 0;
	int y = 0;
char test[1000];
struct Token {
	char content[10];
	int code;
}token[100];              //token���нṹ�����飬����������ɵ�token
char token_content[10];
int token_code;
int changshucharuhanshu(string a);
int biaoshifucharuhanshu(string a);
int charornot(char ch) { //�жϵ�ǰ�ַ��ǲ�����ĸ
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return 1;
	else
		return 0;
}
int numberornot(char ch) { //�жϵ�ǰ�ַ��ǲ�������
	if (ch >= '0' && ch <= '9')
		return 1;
	else
		return 0;
}
int jiefuornot(char ch) {  //�жϵ�ǰ�ַ��ǲ��ǽ��
	int i;
	for (i = 0; i < 18; i++) {
		if (ch == jiefuchart[i])
			return (i+1) ;
	}
	return 0;
}
int konggeornot(char ch) {  //�жϵ�ǰ�ַ��ǲ��ǿո�
	if (ch == ' ')
		return 1;
	else
		return 0;
}

void shuzichuli(char* p) //���ִ�����
{
	int i = 0;
	int j = 0;
	while ((*p >= '0' && *p <= '9') || (*p == '.'))
	{

		token[tag].content[j++] = *p;
		p++;
		index++;
	}
	int temp;
	temp = changshucharuhanshu(token[tag].content);
	token[tag].content[0] = 'c';
	token[tag].code = temp;
	tag++;
}
void jiefuchuli(char* p) { //���������
	int j = jiefuornot(*p);
	token[tag].code = j-1;
	token[tag].content[0] = 'p';
	index++;
	tag++;
}


int guanjianzichuli(char* p) { //�ؼ��ִ�����
	int i = 0;
	while (!jiefuornot(*p) && !konggeornot(*p) && (test[index] != '#'))
	{
		token[tag].content[i] = *p;
		i++;
		p++;
		index++;
	}
	int j;
	for (j = 0; j < 14; j++)
	{
		if (strcmp(keyword[j], token[tag].content) == 0)
		{
			token[tag].code = j;
			token[tag].content[0] = 'k';
			tag++;
			return 1;
		}
	}
	token[tag].code = biaoshifucharuhanshu(token[tag].content);
	token[tag].content[0] = 'i';
	tag++;
	return 0;
}

void changshubiaogoujian()
{
	for (int j = 0; j < 100; j++)
	{
		changshubiao[j] = "#";
	}
}//��ʼ��ʱ�����е�string��ֵ�ɡ�#��

int changshucharuhanshu(string a)
{
	int i = 0;
	if (changshubiao[0] == "#")
	{
		changshubiao[0] = a;
		return i;
	}
	while (changshubiao[i] != "#")
	{
		if ((changshubiao[i] != a))
		{
			i++;
		}
		else
		{
			return i;
		}
	}
	changshubiao[i] = a;
	return i;
}//��������Ժ���Է��ز����λ��

void biaoshifubiaogoujian()
{
	for (int j = 0; j < 100; j++)
	{
		biaoshifubiao[j] = "#";
	}
}////��ʼ��ʱ�����е�string��ֵ�ɡ�#��

int biaoshifucharuhanshu(string a)
{
	int i = 0;
	if (biaoshifubiao[0] == "#")
	{
		biaoshifubiao[0] = a;
		return i;
	}
	while (biaoshifubiao[i] != "#")
	{
		if ((biaoshifubiao[i] != a))
		{
			i++;
		}
		else
		{
			return i;
		}
	}
	biaoshifubiao[i] = a;
	return i;
}//�ܹ����ر�ʾ����λ��

void workout()//����token���к�������ʵ����ʹ���Զ�����ԭ��
{    cout<<"*********token����Ϊ:" << endl;
    while(test[index] != '#')
	{
		if (numberornot(test[index]))
		{
			shuzichuli(&test[index]);
			tag1++;
		}
		else if (konggeornot(test[index]))
		{
			index++;
		}
		else if (jiefuornot(test[index]))
		{
			jiefuchuli(&test[index]);
			tag1++;
		}
		else if (charornot(test[index]))
		{
			guanjianzichuli(&test[index]);
			tag1++;
		}
	}
	if (test[index] == '#')
		return;
}

void outputtoken()//���token����
{
	int i = 0;
	while (token[i].content[0] != '\0')

	{
		cout << "(" << token[i].content[0] << "," << token[i].code << ")" <<endl<<endl;
		i++;
	}

	cout << endl;
}

void outputchangshubiao()//���������
{
	cout<< "*********���������£�" << endl;
	int m = 0;
	while (changshubiao[m] != "#")
	{
		cout << changshubiao[m] << " " << m << endl;
		m++;
	}
	return;
}

void outputbiaoshifubiao()//�����ʶ����
{
	cout<<endl<< "*********��ʶ�������£�" << endl;
	int m = 0;
	while (biaoshifubiao[m] != "#")
	{
		cout << biaoshifubiao[m] << " " << m << endl;
		m++;
	}
	return;
}
 //void zhushichuli()




/*
void outkeywords()//����ؼ��ֱ�
{
	int i;
	int j = 0;
	cout << endl << "�ؼ��ֱ���:" << endl;
	for (i = 0; i < 14; i++)
	{
		while (*(keyword[i] + j) != '\0')
		{
			cout << *(keyword[i] + j);
			j++;
		}
		cout << " " << i << endl;
		j = 0;
	}
}
void outputjiefuchart()//��������
{
	int i;
	cout << endl << "������ǣ�" << endl;
	for (i = 0; i < 18; i++)
	{
		cout << jiefuchart[i] << " " << (i + 1) << endl;
	}
}
*/
void wenjianchuli()
{  ifstream file;
      file.open("data.txt",ios::in);
      if(!file.is_open())
        cout<<"*********�ļ��򿪴��󣡣���*********"<<endl;
      string strline;
      	string temp = "";
    while(getline(file,strline))
    {
        if(strline.empty())
            continue;
            temp += strline;
	     	temp += ' ';

    }
	temp = temp + '#';
	//int y = 0;
	while (temp[y] != '#')
	{
		test[y] = temp[y];
		y++;
	}
	test[y] = '#';

}

int main()
{
    changshubiaogoujian();
	biaoshifubiaogoujian();
	wenjianchuli();
	workout();  //����token
	outputtoken();  //�������token
	outputchangshubiao();
	outputbiaoshifubiao();
    return 0;
}
