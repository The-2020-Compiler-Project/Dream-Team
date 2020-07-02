#include<string>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<conio.h>
#include<string.h>
#include<stack>
#define MAX 10
using namespace std;
const char* keyword[20] = { "program","var","integer","real","char","begin","end","if","then","else","while","do","ifend","return" };//关键字表
char jiefuchart[20] = { ',',':',';','=','*','/','+','-','.','(',')','>','<','@','[',']','{','}' };//界符表
static int index = 0;
static int tag = 0;
char test[1000];
static int tag1 = 0;
static int ip = 0;
int mm = 0;
string siyuanshi2[20] ;
int j = 0;//表示当前是第几个操作
string acc = "0";//寄存器标志：0表示为空，非0，被占用
struct formula {
	string operationName;//操作码
	char opp1[MAX];//操作数
	char opp2[MAX];
	string ans;
	int temp;
}Operate[40];
struct Token {
	char content[10];
	int code;
}token[200];//TOKEN序列数组，用来存放生成的token
int if1;//用于if四元式回填地址时使用的
int if2;
int while1;//用于while四元式回填地址时使用的
int while2;//用于while四元式回填地址时使用的
int while3;
int while4;
int chongdingyi = 0;//用于语义分析，重定义时使用的
int weidingyi = 1;//用于语义分析，未定义时使用的

//前期准备，栈的定义
class Stack
{
public:
	Stack();
	void Push(string b);
	string Pop();
	void Clear();
	string Peek() const;
	bool isEmpty() const;
private:
	string a[100];
	int Top;
};
Stack::Stack()
{
	Top = -1;
}
void Stack::Push(string b)
{
	if (Top == 99)
		return;
	Top++;
	a[Top] = b;
}
string Stack::Pop()
{
	string element;
	//如果栈空，则返回0；
	if (Top == -1)
		return 0;
	element = a[Top];
	Top--;
	return element;
}
void Stack::Clear()
{
	Top = -1;//直接置栈顶指针，没有清空栈
}
string Stack::Peek()const//取栈顶元素
{
	//如果栈为空，则返回0；
	if (Top == -1)
		return 0;
	return a[Top];
}
bool Stack::isEmpty() const
{
	if (Top == -1)
		return true;
	else
		return false;
}
//前期准备，数字转字符串函数
string int2str(int& i)
{
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

int str2int(string s)
{
	int num;
	stringstream ss(s);
	ss >> num;
	return num;
}







//词法分析阶段开始
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
			return (i + 1);
	}
	return 0;
}
int konggeornot(char ch) {  //判断当前字符是不是字母
	if (ch == ' ')
		return 1;
	else
		return 0;
}

int changshucharuhanshu(string a);
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
	token[tag].code = j;
	token[tag].content[0] = 'p';
	index++;
	tag++;
}

int biaoshifucharuhanshu(string a);
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

string changshubiao[100];//记录常数
string biaoshifubiao[100];//记录标示符
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
{
	while (test[index] != '#')
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
	int j = 0;
	while (token[i].content[0] != '\0')
	{
		cout << "(" << token[i].content[0] << "," << token[i].code << ")" << "  ";
		i++;
		j++;
		if (j == 10)
		{
			cout << endl;
			j = 0;
		}
	}
	cout << endl;
}

void outputchangshubiao()//输出常数表
{
	cout << endl << "常数表如下：" << endl;
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
	cout << endl << "标识符表如下：" << endl;
	int m = 0;
	while (biaoshifubiao[m] != "#")
	{
		cout << biaoshifubiao[m] << " " << m << endl;
		m++;
	}
	return;
}

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
//词法分析结束



//结构体用于临时保存数组相关信息
typedef struct array1 {
	string name;
	int length;
};
//结构体用于临时保存子程序相关信息
typedef struct function {
	string name;
	string type;
	int len;
	int fn = 0;
	int off = 0;
	string params[10];
	string types[10];
	int lens[10];
};
typedef struct params {
	string name;
	string csb[10];
	string types[10];
	int lens[10];
	int fn = 0;
};

//符号表生成
string fhb[50][4];
string szb[10][4];
string hsb[10][4];
Stack s;
Stack s1;
Stack s2;
Stack s3;
Stack s4;
stack<array1> s5;
stack<array1> s6;
stack<params> s7;
stack<params> s8;
string type;
int len;
int m = 1;//处理到fhb第几项
int position = -1;//数组表第几项
int page = -1;//函数表第几项
int offset;

void func10(function fun)//函数声明部分填表
{
	//参数表
	params para;
	para.name = fun.name;
	para.fn = fun.fn;
	int i = 0;
	while (fun.params[i] != "#")
	{

		para.csb[i] = fun.params[i];
		para.types[i] = fun.types[i];
		para.lens[i] = fun.lens[i];
		fun.off += para.lens[i];
		i++;
	}
	s7.push(para);
	//符号表
	fhb[m][0] = fun.name;
	fhb[m][1] = "p";
	fhb[m][2] = "f";
	fhb[m][3] = int2str(offset);
	offset = offset + fun.off;
	m++;
	//函数表
	page++;
	hsb[page][1] = int2str(fun.off);
	hsb[page][2] = int2str(fun.fn);
	hsb[page][3] = fun.name;
}

void goujianfhb()
{
	int i = 0;
	for (i = 0; i < 50; i++)
	{
		fhb[i][0] = "#";
	}
	for (i = 0; i < 10; i++)
	{
		szb[i][0] = "#";
	}
	for (i = 0; i < 10; i++)
	{
		hsb[i][0] = "#";
	}
}
void func0()//填入符号表第一项，函数的名字
{
	fhb[0][0] = biaoshifubiao[token[ip].code];
	fhb[0][1] = "/";
	fhb[0][2] = "f";
}
void func1()//总体性质的执行，执行且只执行一次
{
	int i;
	for (i = 1; i < 50; i++)
	{
		fhb[i][2] = "V";
	}
	offset = 0;
	for (i = 0; i < 10; i++)
	{
		szb[i][0] = "0";
	}
	for (i = 0; i < 10; i++)
	{
		hsb[i][0] = "0";
	}

}
void func2()//在一个声明变量意群模块里，依次把标识符压进栈中
{
	s1.Push(biaoshifubiao[token[ip].code]);
}
void func9(string up, string type, string len)
{
	position++;
	szb[position][1] = up;
	szb[position][2] = type;
	szb[position][3] = len;
}
void func8(string na, int len)
{
	array1 a;
	a.name = na;
	a.length = len;
	s5.push(a);
}

void func7()//S2用于恢复定义变量时的顺序
{
	while (!(s1.isEmpty()))
	{
		s2.Push(s1.Pop());
	}
	while (!(s5.empty()))
	{
		s6.push(s5.top());
		s5.pop();
	}

}

void func3()//设置整型填入标识符的性质
{
	type = "i";
	len = 4;
}
void func4()//设置实型填入标识符的性质
{
	type = "r";
	len = 8;
}
void func5()//设置字符型填入标识符的性质
{
	type = "c";
	len = 1;
}

void func6()//声明部分填表算法，按定义的顺序填表，性质对应，最后的offset更新为下一个要填的变量的地址
{
	string* aname = new string;
	int     alength;
	if (!(s6.empty())) {
		*aname = s6.top().name;
		alength = s6.top().length;
		s6.pop();
	}
	while (!(s2.isEmpty()))
	{
		fhb[m][0] = s2.Pop();
		if (*aname == fhb[m][0])
		{
			fhb[m][1] = "a";
			fhb[m][3] = int2str(offset);
			offset = offset + len * alength;
			int up = alength - 1;
			func9(int2str(up), type, int2str(len));
			if (!(s6.empty()))
			{
				*aname = s6.top().name;
				alength = s6.top().length;
				s6.pop();
			}
		}
		else
		{
			fhb[m][1] = type;
			fhb[m][3] = int2str(offset);
			offset = offset + len;
		}
		m++;
	}
}



void outputfhb()//输出符号表函数
{
	int i = 0;
	fhb[0][3] = int2str(offset);
	cout << "\n符号表如下:" << endl;
	while (fhb[i][0] != "#")
	{
		cout << fhb[i][0] << "_" << fhb[i][1] << "_" << fhb[i][2] << "_" << fhb[i][3] << endl;
		i++;
	}
	if (position != -1) {
		i = 0;
		cout << "\n数组表如下:" << endl;
		while (i <= position)
		{
			cout << szb[i][0] << "_" << szb[i][1] << "_" << szb[i][2] << "_" << szb[i][3] << endl;
			i++;
		}
	}
	if (page != -1) {
		i = 0;
		cout << "\n函数表如下:" << endl;
		while (i <= page)
		{
			cout << hsb[i][0] << "_" << hsb[i][1] << "_" << hsb[i][2] << "_" << hsb[i][3] << endl;
			i++;
		}
	}
	while (!s7.empty())
	{
		int off = 0;
		i = 0;
		params para = s7.top();
		s7.pop();
		cout << para.name << "函数的参数表如下:" << endl;
		while (i < para.fn)
		{
			cout << para.csb[i] << "_" << para.types[i] << "_" << "V" << "_" << off << endl;
			off += para.lens[i];
			i++;
		}
	}
}
//以上为声明语句填符号表部分
//以下为操作语句填写符号表部分

void FUNC1()//根据中间变量如果为整型的话就有如下性质
{
	type = "i";
	len = 4;
}
void FUNC2()//根据中间变量如果为实型的话就有如下性质
{
	type = "r";
	len = 8;
}
void FUNC3()//根据中间变量如果为字符型型的话就有如下性质
{
	type = "c";
	len = 1;
}
/*void FUNC4(string c)//每生成一个四元式将其中的t...压进去，注意插入函数位置
{
	s1.Push(c);
}*/
void FUNC5()//还原一个四元式意群的中间变量的顺序存在S4中
{
	while (!(s3.isEmpty()))
	{
		s4.Push(s3.Pop());
	}
}
void FUNC6()//填表算法，同上
{
	while (!(s4.isEmpty()))
	{
		fhb[m][0] = s4.Pop();
		fhb[m][1] = type;
		fhb[m][3] = int2str(offset);
		offset = offset + len;
		m++;
	}
}

int searchfhb(string a)//搜索符号表并若成功返回变量位置，用以判别中间变量的类型的
{
	int i = 0;
	while (fhb[i][0] != "#")
	{
		if (a == fhb[i][0])
		{
			return i;
		}
		else
		{
			i++;
		}
	}
	return 0;
}
//填符号表第二部分完成

















//语法分析需提前声明部分
void SEARCH1(string a);
void SEARCH2(string a);
void QUATFIRST();
void QUATJIA();
void QUATJIAN();
void QUATCHENGE();
void QUATCHU();
void QUATFUZHI(string len, int type);
void QUATLAST();
void QUATBEGIN();
void QUATBOOL();
void QUATTHEN();
void QUATELSE();
void QUATIFEND();
void QUATWHILE();
void QUATDO();
void QUATWHILEEND();
void QUATHANSHUSHENGMING(string str1, string str2);
void QUATDIAOYONG(string str);
void QUATRETURN();
string tp;//执行赋值语句时作为中间桥梁
int xuhao = 0;//用以记录生成第几个四元式
int jilu = 0;//用以记录第几个中间变量的生成
string siyuanshi[100];//存取四元式字符串数组
string temp1;
string temp2;
string bo;//存取bool的比较符，要插动作





//语法分析开始
int PROGRAM();
int SUB_PROGRAM();
int VARIABLE();
int ID_SEQUENCE();
int ARRAY();
int TYPE();
int COM_SENTENCE();
int SEN_SEQUENCE();
int EVA_SENTENCE();
int EXPRESSION();
int TERM();
int FACTOR();
int CONDITION();
int BOOL();
int CIRCLE();

int ANOUNCE_FUNCTION();
int FUN_SENTENCE();
int RETURN();
int FUNCTION();
//声明语句、赋值语句和算术表达式语法分析的开始
int PROGRAM()
{
	int back = 0;
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 0)))/*不是program*/
	{
		back++;
		return 0;
	}
	else/*是program*/
	{
		QUATFIRST();//生成第一个四元式
		ip++;//program正确，移向下一个
	}//识别program关键字

	if (!(token[ip].content[0] == 'i'))/*不是标识符*/
	{
		back++;
		return 0;
	}
	else/*是标识符*/
	{
		func0();
		ip++;//标示符正确，移向下一个
	}//识别标示符

	if ((SUB_PROGRAM()) == 0)
	{
		back++;
		return 0;
	}//识别SUB_PROGRAM是否正确

	if ((token[ip].content[0] == 'p') && (token[ip].code == 9))//p9为点
	{
		QUATLAST();//生成最后一个四元式
	}
	else
	{
		back++;
		return 0;
	}

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}
int SUB_PROGRAM()
{

	int back = 0;
	if (!(VARIABLE()))/*不正确*/
	{
		back++;
		return 0;
	}//识别VARIABLE是否正确

	while (((token[ip].content[0] == 'k') && (token[ip].code == 1)))//如果当前单词是var
	{

		if (!(ANOUNCE_FUNCTION()))//识别函数定义不正确
		{
			cout << "函数识别错误" << endl;
			back++;
			return 0;
		}
		else {
			//正确
			if (((token[ip].content[0] == 'p') && (token[ip].code == 3)))//p3是分号
				ip++;
			else
			{
				back++;
				return 0;
			}
		}
	}

	if (!COM_SENTENCE())/*不正确*/
	{
		back++;
		return 0;
	}

	if (back > 0)//如果能到达这个区，那么应该返回的就是1
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int VARIABLE()
{
	int back = 0;
	if (!(token[ip].content[0] == 'k') && (token[ip].code == 1))/*不是var*/
	{
		back++;
		return 0;
	}
	else/*是var*/
	{
		func1();
		ip++;//没有缺var关键字
	}//是否写了var

	if ((ID_SEQUENCE()) == 0)
	{
		back++;
		return 0;
	}

	if (!(token[ip].content[0] == 'p') && (token[ip].code == 2))/*不是：*/
	{
		back++;
		return 0;
	}
	else/*是：*/
	{
		func7();
		ip++;//没有缺省:号
	}

	if (TYPE() == 0)/*不是type*/
	{
		back++;
		return 0;
	}
	else/*是type*/
	{
		func6();
	}

	if ((token[ip].content[0] == 'p') && (token[ip].code == 3))/*是;*/
	{
		ip++;
	}//看缺不缺分号
	else/*不是;*/
	{
		back++;
		return 0;
	}

	while (!(((token[ip].content[0] == 'k') && (token[ip].code == 5)) || ((token[ip].content[0] == 'k') && (token[ip].code == 1))))//k5是begin,k1是var
	{
		if (!(ID_SEQUENCE()))
		{
			back++;
			return 0;
		}

		if ((token[ip].content[0] == 'p') && (token[ip].code == 2))//p2是冒号
		{
			func7();
			ip++;
		}
		else
		{
			back++;
			ip++;
			return 0;
		}

		if (!(TYPE()))
		{
			back++;
			return 0;
		}
		else
		{
			func6();
		}

		if ((token[ip].content[0] == 'p') && (token[ip].code == 3))//p3是分号
		{
			ip++;
		}
		else
		{
			back++;
			return 0;
		}
	}

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int ID_SEQUENCE()//在没有关键字的时候这个函数会出现错误
{
	int back = 0;
	if (token[ip].content[0] == 'i')
	{
		SEARCH1(biaoshifubiao[token[ip].code]);
		func2();
		ip++;//正确识别第一个标示符
	}
	else
	{
		back++;
		return 0;
	}
	int returnNum = ARRAY();
	if (returnNum == 0)
	{
		back++;
		return 0;
	}
	if (returnNum == 2) {
		//TODO

		func8(biaoshifubiao[token[ip - 4].code], str2int(changshubiao[token[ip - 2].code]));

	}

	while (((token[ip].content[0] == 'p') && (token[ip].code == 1)))//p1是逗号
	{
		ip++;
		if (token[ip].content[0] == 'i')
		{
			SEARCH1(biaoshifubiao[token[ip].code]);
			func2();
			ip++;
		}
		returnNum = ARRAY();
		if (returnNum == 0)
		{
			back++;
			return 0;
		}
		if (returnNum == 2) {
			//TODO
			func8(biaoshifubiao[token[ip - 4].code], str2int(changshubiao[token[ip - 2].code]));
		}
	}

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int ARRAY()
{
	int back = 0;
	if ((token[ip].content[0] == 'p') && (token[ip].code == 15))
	{
		ip++;
	}
	else
	{
		return 1;
	}
	if ((token[ip].content[0] == 'c'))
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 16))
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 2;
	}
}

int TYPE()
{
	if ((token[ip].content[0] == 'k') && ((token[ip].code == 2) || (token[ip].code == 3) || (token[ip].code == 4)))
	{
		if (token[ip].code == 2)//k2为integer
		{
			func3();
			ip++;
			return 1;
		}
		if (token[ip].code == 3)//k3为real
		{
			func4();
			ip++;
			return 2;

		}
		if (token[ip].code == 4)//k4为char
		{
			func5();
			ip++;
			return 3;
		}

	}
	else
	{
		return 0;
	}
}

int COM_SENTENCE()
{
	int back = 0;
	if ((token[ip].content[0] == 'k') && (token[ip].code == 5))/*是begin*/
	{
		QUATBEGIN();
		ip++;
	}
	else
	{
		back++;
		return 0;
	}

	if (!((SEN_SEQUENCE() == 1) || (CONDITION() == 1) || (CIRCLE() == 1)))
	{
		ip--;
		if (!(FUNCTION() == 1))
		{
			back++;
			return 0;
		}
	}
	while (((token[ip].content[0] == 'p') && (token[ip].code == 3)))
	{
		ip++;
		if (!((SEN_SEQUENCE() == 1) || (CONDITION() == 1) || (CIRCLE() == 1)))
		{
			ip--;
			if (!(FUNCTION() == 1))
			{
				back++;
				return 0;
			}
		}
	}


	if (!((token[ip].content[0] == 'k') && (token[ip].code == 6)))//k6为end
	{
		back++;
		return 0;
	}
	else
	{
		// QUATLAST();
		ip++;
	}


	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int SEN_SEQUENCE()
{
	int back = 0;
	if (EVA_SENTENCE() == 0)
	{

		back++;
		return 0;
	}

	while (((token[ip].content[0] == 'p') && (token[ip].code == 3)))//p3是分号
	{
		ip++;
		if (EVA_SENTENCE() == 0)
		{
			back++;
			return 0;
		}

	}

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int EVA_SENTENCE()
{
	int back = 0;
	int temp;
	string length = "";
	int type = 0;
	if (!(token[ip].content[0] == 'i'))
	{
		back++;
		return 0;
	}
	else
	{
		SEARCH2(biaoshifubiao[token[ip].code]);
		temp = searchfhb(biaoshifubiao[token[ip].code]);
		if (fhb[temp][1] == "i")
		{
			FUNC1();
		}
		if (fhb[temp][1] == "r")
		{
			FUNC2();
		}
		if (fhb[temp][1] == "c")
		{
			FUNC3();
		}
		tp = biaoshifubiao[token[ip].code];
		ip++;
	}
	int returnNum = ARRAY();
	if (returnNum == 0)
	{
		back++;
		return 0;
	}
	if (returnNum == 2) {
		length = changshubiao[token[ip - 2].code];
		type = 1;
	}

	if (!((token[ip].content[0] == 'p') && (token[ip].code == 4)))//p4为等于号
	{
		back++;//p4为等于号
		return 0;
	}
	else
	{
		ip++;
	}

	if (EXPRESSION() == 0)
	{
		back++;
		return 0;
	}

	QUATFUZHI(length, type);

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int EXPRESSION()
{
	int back = 0;
	if (TERM() == 0)
	{
		back++;
		return 0;
	}

	while (((token[ip].content[0] == 'p') && (token[ip].code == 7)) || ((token[ip].content[0] == 'p') && (token[ip].code == 8)))//p7为加号
	{
		ip++;
		if (TERM() == 0)
		{
			back++;
			return 0;
		}
		if (((token[ip].content[0] == 'p') && (token[ip].code == 7)))
			QUATJIA();
		else
			QUATJIAN();
		jilu++;
	}
	FUNC5();
	FUNC6();
	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int TERM()
{
	int back = 0;
	if (FACTOR() == 0)
	{
		back++;
		return 0;
	}//否则FACTOR（）执行一遍，再判断是否递归执行
	while (((token[ip].content[0] == 'p') && (token[ip].code == 5)) || ((token[ip].content[0] == 'p') && (token[ip].code == 6)))//p5为乘号
	{
		ip++;
		if (FACTOR() == 0)
		{
			back++;
			return 0;
		}
		if (((token[ip].content[0] == 'p') && (token[ip].code == 5)))
			QUATCHENGE();
		else
			QUATCHU();
		jilu++;
	}

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int FACTOR()
{
	string str;
	int back = 0;
	if ((token[ip].content[0] == 'i') || (token[ip].content[0] == 'c'))/*是标识符或常量*/
	{
		if (token[ip].content[0] == 'i')
		{
			str = biaoshifubiao[token[ip].code];
			ip++;
			int returnNum = ARRAY();
			if (returnNum == 1 || returnNum == 2)
			{
				if (returnNum == 2) {
					string length = changshubiao[token[ip - 2].code];
					str += "[" + length + "]";
				}
				s.Push(str);
				return 1;
			}
			else
				s.Push(str);
		}

		if (token[ip].content[0] == 'c')
		{
			s.Push(changshubiao[token[ip].code]);
			ip++;
			return 1;
		}



	}

	if ((token[ip].content[0] == 'p') && (token[ip].code == 10))/*是左括号*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}

	if (EXPRESSION() == 0)
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 11))/*是右括号*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//声明语句、赋值语句及算术表达式语法分析结束

//条件语句和循环语句语法分析的开始
int CONDITION()
{
	int back = 0;
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 7)))/*不是if*/
	{
		back++;
		return 0;
	}
	else
	{
		ip++;
	}
	if (BOOL() == 0)
	{
		back++;
		return 0;
	}
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 8)))//k8为then
	{
		back++;
		return 0;
	}
	else
	{
		QUATTHEN();
		jilu++;//很重要，不遗漏
		ip++;
	}
	if (SEN_SEQUENCE() == 0)
	{
		back++;
		return 0;
	}

	if (((token[ip].content[0] == 'k') && (token[ip].code == 9)))/*是else*/
	{
		QUATELSE();
		ip++;
		if (SEN_SEQUENCE() == 0)
		{
			back++;
			return 0;
		}
		if ((token[ip].content[0] == 'k') && (token[ip].code == 12))/*是ifend*/
		{
			QUATIFEND();
			ip++;
		}
	}

	//QUATIFEND();

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int BOOL()
{
	int back = 0;
	if (FACTOR() == 0)
	{
		back++;
		return 0;
	}
	if (!(token[ip].content[0] == 'p'))
	{
		back++;
		return 0;
	}

	if (!((token[ip].code == 12) || (token[ip].code == 13) || (token[ip].code == 14)))
	{
		back++;
		return 0;
	}
	else
	{
		if (token[ip].code == 12)//p12为小于号
		{
			bo = "<";
		}
		if (token[ip].code == 13)//p13为大于号
		{
			bo = ">";
		}
		if (token[ip].code == 14)//p14为判断是否相等
		{
			bo = "@";
		}
		ip++;
	}

	if (FACTOR() == 0)
	{
		back++;
		return 0;
	}
	QUATBOOL();

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int CIRCLE()
{
	int back = 0;
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 10)))/*不是while*/
	{
		back++;
		return 0;
	}
	else
	{
		QUATWHILE();
		ip++;
	}
	if (BOOL() == 0)
	{
		back++;
		return 0;
	}
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 11)))/*不是do*/
	{
		back++;
		return 0;
	}
	else
	{
		QUATDO();
		jilu++;//很重要，不遗漏
		ip++;
	}
	if (COM_SENTENCE() == 0)
	{
		back++;
		return 0;
	}

	QUATWHILEEND();

	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}


}
//条件语句和循环语句语法分析结束

//子程序相关函数
int ANOUNCE_FUNCTION()
{
	string str_id, str_type;
	int returnNum;
	function fun;//用于保存子程序信息
	int back = 0;
	if ((token[ip].content[0] == 'k') && (token[ip].code == 1))/*是var*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (token[ip].content[0] == 'i')/*正确识别一个标示符*/
	{
		str_id = biaoshifubiao[token[ip].code];
		SEARCH1(biaoshifubiao[token[ip].code]);
		fun.name = biaoshifubiao[token[ip].code];
		fun.fn = 0;
		for (int i = 0; i < 10; i++)
		{
			fun.params[i] = "#";
			fun.types[i] = "#";
			fun.lens[i] = 0;
		}
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 10))/*是(*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (token[ip].content[0] == 'i')/*正确识别一个标示符*/
	{
		int k = fun.fn;
		fun.params[k] = biaoshifubiao[token[ip].code];
		fun.fn++;
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 2))/*是：*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}

	returnNum = TYPE();
	int k = fun.fn - 1;
	if (returnNum == 1)/*是type*/
	{
		fun.types[k] = "i";
		fun.lens[k] = 4;

	}
	else if (returnNum == 2)
	{
		fun.types[k] = "r";
		fun.lens[k] = 8;

	}
	else if (returnNum == 3)
	{
		fun.types[k] = "c";
		fun.lens[k] = 1;
	}
	else/*不是type*/
	{
		back++;
		return 0;
	}

	while (((token[ip].content[0] == 'p') && (token[ip].code == 1)))//当是，时
	{
		ip++;
		if (token[ip].content[0] == 'i')/*正确识别一个标示符*/
		{
			int k = fun.fn;
			fun.params[k] = biaoshifubiao[token[ip].code];
			fun.fn++;
			ip++;
		}
		else
		{
			back++;
			return 0;
		}
		if ((token[ip].content[0] == 'p') && (token[ip].code == 2))/*是：*/
		{
			ip++;
		}
		else/*是：*/
		{
			back++;
			return 0;
		}
		returnNum = TYPE();
		int k = fun.fn - 1;
		if (returnNum == 1)/*是type*/
		{
			fun.types[k] = "i";
			fun.lens[k] = 4;

		}
		else if (returnNum == 2)
		{
			fun.types[k] = "r";
			fun.lens[k] = 8;

		}
		else if (returnNum == 3)
		{
			fun.types[k] = "c";
			fun.lens[k] = 1;
		}
		else
		{
			back++;
			return 0;
		}
	}/*while结束*/

	if ((token[ip].content[0] == 'p') && (token[ip].code == 11))/*是)*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 2))/*是：*/
	{
		ip++;
	}
	else/*不是：*/
	{
		back++;
		return 0;
	}

	returnNum = TYPE();
	if (returnNum == 1)/*是type*/
	{
		str_type = "interger";
		fun.type = "i";
		fun.len = 4;

	}
	else if (returnNum == 2)
	{
		str_type = "real";
		fun.type = "r";
		fun.len = 8;

	}
	else if (returnNum == 3)
	{
		str_type = "char";
		fun.type = "c";
		fun.len = 1;
	}
	else
	{
		back++;
		return 0;
	}
	QUATHANSHUSHENGMING(str_id, str_type);
	if ((token[ip].content[0] == 'p') && (token[ip].code == 17))/*是{,code为17*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (FUN_SENTENCE() == 1)/*是*/
	{

	}
	else
	{

		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 18))/*是}，code为18*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	func10(fun);
	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int FUN_SENTENCE()
{
	int back = 0;
	if ((token[ip].content[0] == 'k') && (token[ip].code == 5))/*是begin*/
	{
		QUATBEGIN();
		ip++;
	}
	else
	{
		back++;
		return 0;
	}

	if (!((SEN_SEQUENCE() == 1) || (CONDITION() == 1) || (CIRCLE() == 1)))
	{

		back++;
		return 0;
	}
	while (((token[ip].content[0] == 'p') && (token[ip].code == 3)))
	{
		ip++;
		if (!((SEN_SEQUENCE() == 1) || (CONDITION() == 1) || (CIRCLE() == 1)))
		{

			back++;
			return 0;
		}
	}
	if (RETURN() == 1)
	{
		QUATRETURN();
	}
	else
	{

		back++;
		return 0;
	}
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 6)))//k6为end
	{

		back++;
		return 0;
	}
	else
	{
		QUATLAST();
		ip++;

	}
	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int RETURN()
{
	int back = 0;
	if ((token[ip].content[0] == 'k') && (token[ip].code == 13))/*是return*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (FACTOR() == 1)
	{

	}
	else
	{

		back++;
		return 0;
	}
	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int FUNCTION()
{
	string str_id;
	int back = 0;
	if (token[ip].content[0] == 'i')/*正确识别第一个标示符*/
	{
		str_id = biaoshifubiao[token[ip].code];
		ip++;
		//cout<<"识别函数名"<<endl;
	}
	else
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 10))/*是(*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (token[ip].content[0] == 'i')/*正确识别第一个标示符*/
	{
		cout << "识别第一个参数" << endl;
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	while (((token[ip].content[0] == 'p') && (token[ip].code == 1)))/*p1是逗号*/
	{
		ip++;
		if (token[ip].content[0] == 'i')
		{
			ip++;
		}
		else
		{
			back++;
			return 0;
		}
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 11))/*是)*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	QUATDIAOYONG(str_id);
	if (back > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



//从这里开始加入前端和后端的衔接~~~~~~~~~~~~~~~~~~~~啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦啦~~~
int xuhao1 = 0;
string siyuanshi1[100];

//语法制导生成四元式
void QUATFIRST()//生成第一个四元式
{
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(program," + "I0" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(program," + "I0" + "," + "_" + "," + "_" + ")";
	xuhao1++;
	xuhao++;
}
void QUATJIA()//加号生成四元式
{
	temp1 = s.Pop();
	temp2 = s.Pop();
	string* p = new string;
	*p = "t" + int2str(jilu);
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(+," + temp2 + "," + temp1 + "," + *p + ")";
	siyuanshi1[xuhao1] = "(+," + temp2 + "," + temp1 + "," + *p + ")";
	s3.Push(*p);
	s.Push(*p);
	xuhao1++;
	xuhao++;

}
void QUATJIAN()//减号生成四元式
{
	temp1 = s.Pop();
	temp2 = s.Pop();
	string* p = new string;
	*p = "t" + int2str(jilu);
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(-," + temp2 + "," + temp1 + "," + *p + ")";
	siyuanshi1[xuhao1] = "(-," + temp2 + "," + temp1 + "," + *p + ")";
	s3.Push(*p);
	s.Push(*p);
	xuhao1++;
	xuhao++;
}
void QUATCHENGE()//乘号生成四元式
{
	temp1 = s.Pop();
	temp2 = s.Pop();
	string* p = new string;
	*p = "t" + int2str(jilu);
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(*," + temp2 + "," + temp1 + "," + *p + ")";
	siyuanshi1[xuhao1] = "(*," + temp2 + "," + temp1 + "," + *p + ")";
	s3.Push(*p);
	s.Push(*p);
	xuhao1++;
	xuhao++;
}

//赋值语句生成四元式所需函数
void QUATCHU()
{
	temp1 = s.Pop();
	temp2 = s.Pop();
	string* p = new string;
	*p = "t" + int2str(jilu);
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(/," + temp2 + "," + temp1 + "," + *p + ")";
	siyuanshi1[xuhao1] = "(/," + temp2 + "," + temp1 + "," + *p + ")";
	s3.Push(*p);
	s.Push(*p);
	xuhao1++;
	xuhao++;
}
void QUATFUZHI(string len, int type)
{
	temp1 = s.Pop();
	if (type) {
		siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(=," + temp1 + "," + "_" + "," + tp + "[" + len + "]" + ")";
		siyuanshi1[xuhao1] = "(=," + temp1 + "," + "_" + "," + tp + "[" + len + "]" + ")";

	}
	else
	{
		siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(=," + temp1 + "," + "_" + "," + tp + ")";
		siyuanshi1[xuhao1] = "(=," + temp1 + "," + "_" + "," + tp + ")";
	}
	xuhao1++;
	xuhao++;
}

void QUATLAST()//生成最后一个四元式
{
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(end," + "I0" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(end," + "I0" + "," + "_" + "," + "_" + ")";
	xuhao1++;
	xuhao++;
}
void QUATBEGIN()//生成最后一个四元式
{
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(begin," + "I0" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(begin," + "I0" + "," + "_" + "," + "_" + ")";
	xuhao++;
	xuhao1++;
}
void outputsiyuanshi()//输出所有四元式函数
{
	cout << "四元式序列为：" << endl;
	int i = 0;
	while (siyuanshi[i] != "")
	{
		cout << siyuanshi[i] << endl;
		i++;
	}
	cout << endl;
}
/*
void outputsiyuanshi1()//输出所有四元式函数
{
	cout << "四元式一序列为：" << endl;
	int i = 0;
	while (siyuanshi1[i] != "")
	{
		cout << siyuanshi1[i] << endl;
		i++;
	}
	cout << endl;
}
*/

//以下为条件语句和循环语句生成四元式部分所需函数
void QUATBOOL()
{
	temp1 = s.Pop();
	temp2 = s.Pop();
	string* p = new string;
	*p = "t" + int2str(jilu);
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + bo + "," + temp2 + "," + temp1 + "," + *p + ")";
	siyuanshi1[xuhao1] = "(" + bo + "," + temp2 + "," + temp1 + "," + *p + ")";
	xuhao++;
	xuhao1++;
	s.Push(*p);//将bool表达式的结果存入栈中
}
void QUATTHEN()
{
	temp1 = s.Pop();
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "then" + "," + temp1 + "," + "_" + ",";//此时s.pop就是bool表达式的结果
	siyuanshi1[xuhao1] = temp + "(" + "then" + "," + temp1 + "," + "_" + ",";
	if1 = xuhao;
	if2 = xuhao1;
	xuhao++;
	xuhao1++;
}
void QUATELSE()
{
	string temp = "";
	int i = xuhao + 1;
	int j = xuhao1 + 1;
	siyuanshi[if1] += int2str(i) + ")";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "else" + "," + "_" + "," + "_" + ",";
	siyuanshi1[if2] += int2str(j) + ")";
	siyuanshi1[xuhao1] = temp + "(" + "else" + "," + "_" + "," + "_" + ",";
	if1 = xuhao;
	if2 = xuhao1;
	xuhao++;
	xuhao1++;
}
void QUATIFEND()
{
	string temp = "";
	siyuanshi[if1] += int2str(xuhao) + ")";
	siyuanshi1[if2] += int2str(xuhao1) + ")";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "ifend" + "," + "_" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(" + "ifend" + "," + "_" + "," + "_" + "," + "_" + ")";
	xuhao1++;
	xuhao++;
}
void QUATWHILE()
{
	string temp = "";
	while1 = xuhao;
	while3 = xuhao1;
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "while" + "," + "_" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(" + "while" + "," + "_" + "," + "_" + "," + "_" + ")";
	xuhao1++;
	xuhao++;
}
void QUATDO()
{
	while2 = xuhao;
	while4 = xuhao1;
	string temp = "";
	temp1 = s.Pop();
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "do" + "," + temp1 + "," + "_" + ",";//bool那个区已经将bool表达式的结果存进去了，即s.pop
	siyuanshi1[xuhao1] = temp + "(" + "do" + "," + temp1 + "," + "_" + ",";
	xuhao1++;
	xuhao++;
}
void QUATWHILEEND()
{
	string temp = "";
	int i = xuhao + 1;
	int j = while1 + 1;
	int k = xuhao1 + 1;
	int m = while3 + 1;
	siyuanshi[while2] += int2str(i) + ")";
	siyuanshi1[while4] += int2str(k) + ")";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "whend" + "," + "_" + "," + "_" + "," + int2str(j) + ")";
	siyuanshi1[xuhao1] = temp + "(" + "whend" + "," + "_" + "," + "_" + "," + int2str(m) + ")";
	xuhao1++;
	xuhao++;
}
void QUATHANSHUSHENGMING(string str1, string str2)
{
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + str1 + "," + "_" + "," + "_" + "," + str2 + ")";
	siyuanshi1[xuhao1] = "(" + str1 + "," + "_" + "," + "_" + "," + str2 + ")";
	xuhao1++;

}
void QUATDIAOYONG(string str)
{
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + str + "," + "_" + "," + "_" + "_" + ")";
	xuhao++;

}
void QUATRETURN()
{
	string temp = "";
	temp1 = s.Pop();
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(return," + "_" + "," + "_" + "," + temp1 + ")";
	siyuanshi1[xuhao1] = temp + "(return," + "_" + "," + "_" + "," + temp1 + ")";
	xuhao1++;
	xuhao++;
}
//生成四元式区















//语义分析部分
void SEARCH1(string a)
{
	int i = 0;
	while (fhb[i][0] != "#")
	{
		if (a == fhb[i][0])
		{
			chongdingyi = 1;
			return;
		}
		else
		{
			i++;
		}
	}
}
void SEARCH2(string a)
{
	int i = 0;
	while (fhb[i][0] != "#")
	{
		if (a == fhb[i][0])
		{
			weidingyi = 0;
			return;
			i++;
		}
		else
		{
			weidingyi = 1;
			i++;
		}
	}
}
void yuyifenxi()
{
	int back = 0;
	cout << endl << "语义分析结果如下:" << endl;
	if (chongdingyi == 1)
	{
		cout << "重定义错误!" << endl;
		back++;
	}
	if (weidingyi == 1)
	{
		cout << "未定义错误!" << endl;
		back++;
	}
	if (back > 0)
	{
		return;
	}
	else
	{
		cout << "语义正确！" << endl;
	}
}
//语义分析结束
//基本块划分

int compa(string ch[])
{
	int i;
	int k = 0;
	for (i = 1; ch[i].length() != 0; i++) {
		if ((ch[i] == "(while,_,_,_)") || (ch[i] == "(proc,_,_,_)") || (ch[i] == "(func,_,_,_)") || (ch[i] == "(ifend,_,_,_)") || (ch[i] == "(lable,_,_,_)"))
		{
			if (siyuanshi2[k].length() == 0)
				siyuanshi2[k] = ch[i];
			else
				k++;
			siyuanshi2[k] = ch[i];
		}
		else if ((ch[i].substr(0, 6) == "(goto,") || (ch[i].substr(0, 6) == "(then,") || (ch[i].substr(0, 6) == ("(else,")) || (ch[i].substr(0, 6) == "(whend" || (ch[i].substr(0, 6) == "(do,_,") || (ch[i].substr(0, 6) == "(call,")))
		{//cout<<"**********"<<endl;
			siyuanshi2[k] += ch[i];
			//cout<<base[k]<<endl;
			k++;
		}
		else if (ch[i].substr(0, 3) == "(=,")
		{//cout<<"**********"<<endl;
		//for (j=0;j<=(i-temp);j++,record++)
			siyuanshi2[k] += ch[i];
			k++;
		}
		else if (ch[i].substr(0, 7) == "(return")
			continue;
		else siyuanshi2[k] += ch[i];
	}
	cout << "基本块划分为：" << endl;
	for (i = 0; siyuanshi2[i].length() != 0; i++)
		cout << "(" << (i + 1) << ")" << siyuanshi2[i] << endl;
	// cout<<ch[19]<<endl;
	return 0;
}
int isOperator(string ch) {
	if (ch == "then")
		return 1;
	if (ch == "else")
		return 2;
	if (ch == "+")
		return 3;
	if (ch == "-")
		return 4;
	if (ch == "*")
		return 5;
	if (ch == "/")
		return 6;
	if (ch == "=")
		return 7;
	if (ch == "<")
		return 8;
	if (ch == "ifend")
		return 9;
	if (ch == ">")
		return 10;
	if (ch == "while")
		return 11;
	if (ch == "do")
		return 12;
	if (ch == "whend")
		return 13;
	if (ch == "fun2")
		return 14;
	if (ch == "@")
		return 8;
	else return 0;
}
void Operator_Number() {
	int i;
	char* p = (char*)siyuanshi2[j].data();
	while (*p == '(') {
		p++;
		while (*p != ',') {
			Operate[mm].operationName += *p;
			p++;
		}
		p++;
		for (i = 0; *p != ','; i++) {
			Operate[mm].opp1[i] = *p;
			p++;
		}
		p++;
		for (i = 0; *p != ','; i++) {
			Operate[mm].opp2[i] = *p;
			p++;
		}
		p++;
		while (*p != ')') {
			Operate[mm].ans += *p;
			p++;
		}
		p++;
		Operate[mm].temp = isOperator(Operate[mm].operationName);
		mm++;
	}
}

const char* OperatorToString(int i) {
	switch (i) {
	case 1:
		return "JUMP0";
	case 2:
		return "JMP";
	case 3:
		return "ADD";
	case 4:
		return "SUB";
	case 5:
		return "MUL";
	case 6:
		return "DIV";
	case 7:
		return 0;
	case 8:
		return "COMPARE";
	case 9:
		return " ";
	case 10:
		return "COMPARE";
	case 11:
		return " ";
	case 12:
		return "JUMP0";
	case 13:
		return "JMP";
	case 14:
		return "FUN";
	default:
		return " ";
	}
}
int displayOperations(int k) {
	if (OperatorToString(Operate[k].temp) == " ")
		return 0;
	else {
		cout << "LD" << "\t" << "R" << "," << Operate[k].opp1 << endl;
		cout << OperatorToString(Operate[k].temp) << "\t" << "R" << "," << Operate[k].opp2 << endl;
	}
	return 0;
}

int displayOperations1(int k) {
	if (OperatorToString(Operate[k].temp) == " ")
		return 0;
	else {
		if ((Operate[k].temp == 1) || (Operate[k].temp == 12))
		{
			cout << "ST" << "\t" << "R" << "," << acc << endl;
			cout << "LD" << "\t" << "R" << "," << Operate[k].opp1 << endl;
			cout << OperatorToString(Operate[k].temp) << "\t" << "R" << "," << Operate[k].ans << endl;
		}
		if ((Operate[k].temp == 2) || (Operate[k].temp == 13))
		{
			cout << OperatorToString(Operate[k].temp) << "\t" << Operate[k].ans << endl;
		}
		if ((Operate[k].temp == 4) || (Operate[k].temp == 6))
		{
			cout << "ST" << "\t" << "R" << "," << acc << endl;
			cout << "LD" << "\t" << "R" << "," << Operate[k].opp1 << endl;
			cout << OperatorToString(Operate[k].temp) << "\t" << "R" << "," << Operate[k].opp2 << endl;
		}
		if ((Operate[k].temp == 3) || (Operate[k].temp == 5)) {
			cout << OperatorToString(Operate[k].temp) << "\t" << "R" << "," << Operate[k].opp2 << endl;
		}
		if (Operate[k].temp == 7)
		{
			if (acc != "_")
			{
				cout << "ST" << "\t" << "R" << "," << acc << endl;
			}
			cout << "LD" << "\t" << "R" << "," << Operate[k].opp1 << endl;
			cout << "ST" << "\t" << "R" << "," << Operate[k].ans << endl;
		}
		if (Operate[k].temp == 8)
			cout << OperatorToString(Operate[k].temp) << "\t" << Operate[k].opp2 << "," << Operate[k].opp1 << endl;
		if (Operate[k].temp == 10)
			cout << OperatorToString(Operate[k].temp) << "\t" << Operate[k].opp1 << "," << Operate[k].opp2 << endl;
		if (Operate[k].temp == 14)
			cout << OperatorToString(Operate[k].temp) << ":" << endl;
	}
	return 0;
}

//}
void last() {
	int i = 0;
	while (siyuanshi2[j].length() != 0) {
		Operator_Number();
		j++;
	}
	cout << "最后生成的汇编代码如下：" << endl;
	for (i = 0; Operate[i].operationName.length() != 0; i++) {
		if (acc == "0")
			displayOperations(i);
		else displayOperations1(i);
		acc = Operate[i].ans;
	}
}

//主函数
int main() {
	changshubiaogoujian();
	biaoshifubiaogoujian();
	goujianfhb();
	//处理输入程序为处理格式
	cout << "请输入程序：（以换行加#号结束）" << endl;
	string temp = "";
	char input[1000];
	cin.getline(input, 1000, '\n');
	while (input[0] != '#')
	{
		temp += input;
		temp += ' ';
		cin.getline(input, 1000, '\n');
	}
	temp = temp + '#';
	int y = 0;
	while (temp[y] != '#')
	{
		test[y] = temp[y];
		y++;
	}
	test[y] = '#';
	//处理完毕
	cout << endl << "token序列为:" << endl;
	workout();//生成token
	outputtoken();//按序输出token
	outputchangshubiao();
	outputbiaoshifubiao();
	outkeywords();
	outputjiefuchart();
	cout << endl << "语法分析" << endl;
	if (PROGRAM() == 1)
	{
		cout << "the result of syntax analysis is succeed!" << endl << endl;
	}
	else
	{
		cout << "the result of syntax analysis is error!" << endl;
		//说明：错误以后不再执行后续工作
	}
	outputsiyuanshi();//输出四元式序列
	outputfhb();
	yuyifenxi();
	compa(siyuanshi1);
	last();
	return 1;
}
