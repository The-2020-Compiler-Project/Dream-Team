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
const char* keyword[20] = { "program","var","integer","real","char","begin","end","if","then","else","while","do","ifend","return" }; //关键字表
char jiefuchart[20] = { ',',':',';','=','*','/','+','-','.','(',')','>','<','@','[',']','{','}' }; //界符表
string changshubiao[100];    //记录常数
string biaoshifubiao[100];   //记录标示符
static int index = 0;
static int tag = 0;
static int tag1 = 0;
	int y = 0;
char test[1000];
struct Token {
	char content[10];
	int code;
}token[100];              //token序列结构体数组，用来存放生成的token
char token_content[10];
int token_code;
int changshucharuhanshu(string a);
int biaoshifucharuhanshu(string a);
int charornot(char ch) { //判断当前字符是不是字母
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return 1;
	else
		return 0;
}
int numberornot(char ch) { //判断当前字符是不是数字
	if (ch >= '0' && ch <= '9')
		return 1;
	else
		return 0;
}
int jiefuornot(char ch) {  //判断当前字符是不是界符
	int i;
	for (i = 0; i < 18; i++) {
		if (ch == jiefuchart[i])
			return (i+1) ;
	}
	return 0;
}
int konggeornot(char ch) {  //判断当前字符是不是空格
	if (ch == ' ')
		return 1;
	else
		return 0;
}

void shuzichuli(char* p) //数字处理函数
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
void jiefuchuli(char* p) { //界符处理函数
	int j = jiefuornot(*p);
	token[tag].code = j-1;
	token[tag].content[0] = 'p';
	index++;
	tag++;
}


int guanjianzichuli(char* p) { //关键字处理函数
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
}//初始化时将所有的string赋值成“#”

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
}//插入完成以后可以返回插入的位置

void biaoshifubiaogoujian()
{
	for (int j = 0; j < 100; j++)
	{
		biaoshifubiao[j] = "#";
	}
}////初始化时将所有的string赋值成“#”

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
}//能够返回标示符的位置

void workout()//生成token序列函数，其实就是使用自动机的原理
{    cout<<"*********token序列为:" << endl;
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

void outputtoken()//输出token序列
{
	int i = 0;
	while (token[i].content[0] != '\0')

	{
		cout << "(" << token[i].content[0] << "," << token[i].code << ")" <<endl<<endl;
		i++;
	}

	cout << endl;
}

void outputchangshubiao()//输出常数表
{
	cout<< "*********常数表如下：" << endl;
	int m = 0;
	while (changshubiao[m] != "#")
	{
		cout << changshubiao[m] << " " << m << endl;
		m++;
	}
	return;
}

void outputbiaoshifubiao()//输出标识符表
{
	cout<<endl<< "*********标识符表如下：" << endl;
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
void outkeywords()//输出关键字表
{
	int i;
	int j = 0;
	cout << endl << "关键字表是:" << endl;
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
void outputjiefuchart()//输出界符表
{
	int i;
	cout << endl << "界符表是：" << endl;
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
        cout<<"*********文件打开错误！！！*********"<<endl;
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
	workout();  //生成token
	outputtoken();  //按序输出token
	outputchangshubiao();
	outputbiaoshifubiao();
    return 0;
}
