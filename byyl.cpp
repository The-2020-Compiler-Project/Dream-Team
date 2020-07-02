#include<string>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<conio.h>
#include<string.h>
#include<stack>
#define MAX 10
using namespace std;
const char* keyword[20] = { "program","var","integer","real","char","begin","end","if","then","else","while","do","ifend","return" };//�ؼ��ֱ�
char jiefuchart[20] = { ',',':',';','=','*','/','+','-','.','(',')','>','<','@','[',']','{','}' };//�����
static int index = 0;
static int tag = 0;
char test[1000];
static int tag1 = 0;
static int ip = 0;
int mm = 0;
string siyuanshi2[20] ;
int j = 0;//��ʾ��ǰ�ǵڼ�������
string acc = "0";//�Ĵ�����־��0��ʾΪ�գ���0����ռ��
struct formula {
	string operationName;//������
	char opp1[MAX];//������
	char opp2[MAX];
	string ans;
	int temp;
}Operate[40];
struct Token {
	char content[10];
	int code;
}token[200];//TOKEN�������飬����������ɵ�token
int if1;//����if��Ԫʽ�����ַʱʹ�õ�
int if2;
int while1;//����while��Ԫʽ�����ַʱʹ�õ�
int while2;//����while��Ԫʽ�����ַʱʹ�õ�
int while3;
int while4;
int chongdingyi = 0;//��������������ض���ʱʹ�õ�
int weidingyi = 1;//�������������δ����ʱʹ�õ�

//ǰ��׼����ջ�Ķ���
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
	//���ջ�գ��򷵻�0��
	if (Top == -1)
		return 0;
	element = a[Top];
	Top--;
	return element;
}
void Stack::Clear()
{
	Top = -1;//ֱ����ջ��ָ�룬û�����ջ
}
string Stack::Peek()const//ȡջ��Ԫ��
{
	//���ջΪ�գ��򷵻�0��
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
//ǰ��׼��������ת�ַ�������
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







//�ʷ������׶ο�ʼ
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
			return (i + 1);
	}
	return 0;
}
int konggeornot(char ch) {  //�жϵ�ǰ�ַ��ǲ�����ĸ
	if (ch == ' ')
		return 1;
	else
		return 0;
}

int changshucharuhanshu(string a);
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
	token[tag].code = j;
	token[tag].content[0] = 'p';
	index++;
	tag++;
}

int biaoshifucharuhanshu(string a);
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

string changshubiao[100];//��¼����
string biaoshifubiao[100];//��¼��ʾ��
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

void outputtoken()//���token����
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

void outputchangshubiao()//���������
{
	cout << endl << "���������£�" << endl;
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
	cout << endl << "��ʶ�������£�" << endl;
	int m = 0;
	while (biaoshifubiao[m] != "#")
	{
		cout << biaoshifubiao[m] << " " << m << endl;
		m++;
	}
	return;
}

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
//�ʷ���������



//�ṹ��������ʱ�������������Ϣ
typedef struct array1 {
	string name;
	int length;
};
//�ṹ��������ʱ�����ӳ��������Ϣ
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

//���ű�����
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
int m = 1;//����fhb�ڼ���
int position = -1;//�����ڼ���
int page = -1;//������ڼ���
int offset;

void func10(function fun)//���������������
{
	//������
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
	//���ű�
	fhb[m][0] = fun.name;
	fhb[m][1] = "p";
	fhb[m][2] = "f";
	fhb[m][3] = int2str(offset);
	offset = offset + fun.off;
	m++;
	//������
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
void func0()//������ű��һ�����������
{
	fhb[0][0] = biaoshifubiao[token[ip].code];
	fhb[0][1] = "/";
	fhb[0][2] = "f";
}
void func1()//�������ʵ�ִ�У�ִ����ִֻ��һ��
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
void func2()//��һ������������Ⱥģ������ΰѱ�ʶ��ѹ��ջ��
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

void func7()//S2���ڻָ��������ʱ��˳��
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

void func3()//�������������ʶ��������
{
	type = "i";
	len = 4;
}
void func4()//����ʵ�������ʶ��������
{
	type = "r";
	len = 8;
}
void func5()//�����ַ��������ʶ��������
{
	type = "c";
	len = 1;
}

void func6()//������������㷨���������˳��������ʶ�Ӧ������offset����Ϊ��һ��Ҫ��ı����ĵ�ַ
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



void outputfhb()//������ű���
{
	int i = 0;
	fhb[0][3] = int2str(offset);
	cout << "\n���ű�����:" << endl;
	while (fhb[i][0] != "#")
	{
		cout << fhb[i][0] << "_" << fhb[i][1] << "_" << fhb[i][2] << "_" << fhb[i][3] << endl;
		i++;
	}
	if (position != -1) {
		i = 0;
		cout << "\n���������:" << endl;
		while (i <= position)
		{
			cout << szb[i][0] << "_" << szb[i][1] << "_" << szb[i][2] << "_" << szb[i][3] << endl;
			i++;
		}
	}
	if (page != -1) {
		i = 0;
		cout << "\n����������:" << endl;
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
		cout << para.name << "�����Ĳ���������:" << endl;
		while (i < para.fn)
		{
			cout << para.csb[i] << "_" << para.types[i] << "_" << "V" << "_" << off << endl;
			off += para.lens[i];
			i++;
		}
	}
}
//����Ϊ�����������ű���
//����Ϊ���������д���ű���

void FUNC1()//�����м�������Ϊ���͵Ļ�������������
{
	type = "i";
	len = 4;
}
void FUNC2()//�����м�������Ϊʵ�͵Ļ�������������
{
	type = "r";
	len = 8;
}
void FUNC3()//�����м�������Ϊ�ַ����͵Ļ�������������
{
	type = "c";
	len = 1;
}
/*void FUNC4(string c)//ÿ����һ����Ԫʽ�����е�t...ѹ��ȥ��ע����뺯��λ��
{
	s1.Push(c);
}*/
void FUNC5()//��ԭһ����Ԫʽ��Ⱥ���м������˳�����S4��
{
	while (!(s3.isEmpty()))
	{
		s4.Push(s3.Pop());
	}
}
void FUNC6()//����㷨��ͬ��
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

int searchfhb(string a)//�������ű����ɹ����ر���λ�ã������б��м���������͵�
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
//����ű�ڶ��������

















//�﷨��������ǰ��������
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
string tp;//ִ�и�ֵ���ʱ��Ϊ�м�����
int xuhao = 0;//���Լ�¼���ɵڼ�����Ԫʽ
int jilu = 0;//���Լ�¼�ڼ����м����������
string siyuanshi[100];//��ȡ��Ԫʽ�ַ�������
string temp1;
string temp2;
string bo;//��ȡbool�ıȽϷ���Ҫ�嶯��





//�﷨������ʼ
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
//������䡢��ֵ�����������ʽ�﷨�����Ŀ�ʼ
int PROGRAM()
{
	int back = 0;
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 0)))/*����program*/
	{
		back++;
		return 0;
	}
	else/*��program*/
	{
		QUATFIRST();//���ɵ�һ����Ԫʽ
		ip++;//program��ȷ��������һ��
	}//ʶ��program�ؼ���

	if (!(token[ip].content[0] == 'i'))/*���Ǳ�ʶ��*/
	{
		back++;
		return 0;
	}
	else/*�Ǳ�ʶ��*/
	{
		func0();
		ip++;//��ʾ����ȷ��������һ��
	}//ʶ���ʾ��

	if ((SUB_PROGRAM()) == 0)
	{
		back++;
		return 0;
	}//ʶ��SUB_PROGRAM�Ƿ���ȷ

	if ((token[ip].content[0] == 'p') && (token[ip].code == 9))//p9Ϊ��
	{
		QUATLAST();//�������һ����Ԫʽ
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
	if (!(VARIABLE()))/*����ȷ*/
	{
		back++;
		return 0;
	}//ʶ��VARIABLE�Ƿ���ȷ

	while (((token[ip].content[0] == 'k') && (token[ip].code == 1)))//�����ǰ������var
	{

		if (!(ANOUNCE_FUNCTION()))//ʶ�������岻��ȷ
		{
			cout << "����ʶ�����" << endl;
			back++;
			return 0;
		}
		else {
			//��ȷ
			if (((token[ip].content[0] == 'p') && (token[ip].code == 3)))//p3�Ƿֺ�
				ip++;
			else
			{
				back++;
				return 0;
			}
		}
	}

	if (!COM_SENTENCE())/*����ȷ*/
	{
		back++;
		return 0;
	}

	if (back > 0)//����ܵ������������ôӦ�÷��صľ���1
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
	if (!(token[ip].content[0] == 'k') && (token[ip].code == 1))/*����var*/
	{
		back++;
		return 0;
	}
	else/*��var*/
	{
		func1();
		ip++;//û��ȱvar�ؼ���
	}//�Ƿ�д��var

	if ((ID_SEQUENCE()) == 0)
	{
		back++;
		return 0;
	}

	if (!(token[ip].content[0] == 'p') && (token[ip].code == 2))/*���ǣ�*/
	{
		back++;
		return 0;
	}
	else/*�ǣ�*/
	{
		func7();
		ip++;//û��ȱʡ:��
	}

	if (TYPE() == 0)/*����type*/
	{
		back++;
		return 0;
	}
	else/*��type*/
	{
		func6();
	}

	if ((token[ip].content[0] == 'p') && (token[ip].code == 3))/*��;*/
	{
		ip++;
	}//��ȱ��ȱ�ֺ�
	else/*����;*/
	{
		back++;
		return 0;
	}

	while (!(((token[ip].content[0] == 'k') && (token[ip].code == 5)) || ((token[ip].content[0] == 'k') && (token[ip].code == 1))))//k5��begin,k1��var
	{
		if (!(ID_SEQUENCE()))
		{
			back++;
			return 0;
		}

		if ((token[ip].content[0] == 'p') && (token[ip].code == 2))//p2��ð��
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

		if ((token[ip].content[0] == 'p') && (token[ip].code == 3))//p3�Ƿֺ�
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

int ID_SEQUENCE()//��û�йؼ��ֵ�ʱ�������������ִ���
{
	int back = 0;
	if (token[ip].content[0] == 'i')
	{
		SEARCH1(biaoshifubiao[token[ip].code]);
		func2();
		ip++;//��ȷʶ���һ����ʾ��
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

	while (((token[ip].content[0] == 'p') && (token[ip].code == 1)))//p1�Ƕ���
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
		if (token[ip].code == 2)//k2Ϊinteger
		{
			func3();
			ip++;
			return 1;
		}
		if (token[ip].code == 3)//k3Ϊreal
		{
			func4();
			ip++;
			return 2;

		}
		if (token[ip].code == 4)//k4Ϊchar
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
	if ((token[ip].content[0] == 'k') && (token[ip].code == 5))/*��begin*/
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


	if (!((token[ip].content[0] == 'k') && (token[ip].code == 6)))//k6Ϊend
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

	while (((token[ip].content[0] == 'p') && (token[ip].code == 3)))//p3�Ƿֺ�
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

	if (!((token[ip].content[0] == 'p') && (token[ip].code == 4)))//p4Ϊ���ں�
	{
		back++;//p4Ϊ���ں�
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

	while (((token[ip].content[0] == 'p') && (token[ip].code == 7)) || ((token[ip].content[0] == 'p') && (token[ip].code == 8)))//p7Ϊ�Ӻ�
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
	}//����FACTOR����ִ��һ�飬���ж��Ƿ�ݹ�ִ��
	while (((token[ip].content[0] == 'p') && (token[ip].code == 5)) || ((token[ip].content[0] == 'p') && (token[ip].code == 6)))//p5Ϊ�˺�
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
	if ((token[ip].content[0] == 'i') || (token[ip].content[0] == 'c'))/*�Ǳ�ʶ������*/
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

	if ((token[ip].content[0] == 'p') && (token[ip].code == 10))/*��������*/
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
	if ((token[ip].content[0] == 'p') && (token[ip].code == 11))/*��������*/
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
//������䡢��ֵ��估�������ʽ�﷨��������

//��������ѭ������﷨�����Ŀ�ʼ
int CONDITION()
{
	int back = 0;
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 7)))/*����if*/
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
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 8)))//k8Ϊthen
	{
		back++;
		return 0;
	}
	else
	{
		QUATTHEN();
		jilu++;//����Ҫ������©
		ip++;
	}
	if (SEN_SEQUENCE() == 0)
	{
		back++;
		return 0;
	}

	if (((token[ip].content[0] == 'k') && (token[ip].code == 9)))/*��else*/
	{
		QUATELSE();
		ip++;
		if (SEN_SEQUENCE() == 0)
		{
			back++;
			return 0;
		}
		if ((token[ip].content[0] == 'k') && (token[ip].code == 12))/*��ifend*/
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
		if (token[ip].code == 12)//p12ΪС�ں�
		{
			bo = "<";
		}
		if (token[ip].code == 13)//p13Ϊ���ں�
		{
			bo = ">";
		}
		if (token[ip].code == 14)//p14Ϊ�ж��Ƿ����
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
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 10)))/*����while*/
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
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 11)))/*����do*/
	{
		back++;
		return 0;
	}
	else
	{
		QUATDO();
		jilu++;//����Ҫ������©
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
//��������ѭ������﷨��������

//�ӳ�����غ���
int ANOUNCE_FUNCTION()
{
	string str_id, str_type;
	int returnNum;
	function fun;//���ڱ����ӳ�����Ϣ
	int back = 0;
	if ((token[ip].content[0] == 'k') && (token[ip].code == 1))/*��var*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (token[ip].content[0] == 'i')/*��ȷʶ��һ����ʾ��*/
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
	if ((token[ip].content[0] == 'p') && (token[ip].code == 10))/*��(*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (token[ip].content[0] == 'i')/*��ȷʶ��һ����ʾ��*/
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
	if ((token[ip].content[0] == 'p') && (token[ip].code == 2))/*�ǣ�*/
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
	if (returnNum == 1)/*��type*/
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
	else/*����type*/
	{
		back++;
		return 0;
	}

	while (((token[ip].content[0] == 'p') && (token[ip].code == 1)))//���ǣ�ʱ
	{
		ip++;
		if (token[ip].content[0] == 'i')/*��ȷʶ��һ����ʾ��*/
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
		if ((token[ip].content[0] == 'p') && (token[ip].code == 2))/*�ǣ�*/
		{
			ip++;
		}
		else/*�ǣ�*/
		{
			back++;
			return 0;
		}
		returnNum = TYPE();
		int k = fun.fn - 1;
		if (returnNum == 1)/*��type*/
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
	}/*while����*/

	if ((token[ip].content[0] == 'p') && (token[ip].code == 11))/*��)*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 2))/*�ǣ�*/
	{
		ip++;
	}
	else/*���ǣ�*/
	{
		back++;
		return 0;
	}

	returnNum = TYPE();
	if (returnNum == 1)/*��type*/
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
	if ((token[ip].content[0] == 'p') && (token[ip].code == 17))/*��{,codeΪ17*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (FUN_SENTENCE() == 1)/*��*/
	{

	}
	else
	{

		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 18))/*��}��codeΪ18*/
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
	if ((token[ip].content[0] == 'k') && (token[ip].code == 5))/*��begin*/
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
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 6)))//k6Ϊend
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
	if ((token[ip].content[0] == 'k') && (token[ip].code == 13))/*��return*/
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
	if (token[ip].content[0] == 'i')/*��ȷʶ���һ����ʾ��*/
	{
		str_id = biaoshifubiao[token[ip].code];
		ip++;
		//cout<<"ʶ������"<<endl;
	}
	else
	{
		back++;
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 10))/*��(*/
	{
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	if (token[ip].content[0] == 'i')/*��ȷʶ���һ����ʾ��*/
	{
		cout << "ʶ���һ������" << endl;
		ip++;
	}
	else
	{
		back++;
		return 0;
	}
	while (((token[ip].content[0] == 'p') && (token[ip].code == 1)))/*p1�Ƕ���*/
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
	if ((token[ip].content[0] == 'p') && (token[ip].code == 11))/*��)*/
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



//�����￪ʼ����ǰ�˺ͺ�˵��ν�~~~~~~~~~~~~~~~~~~~~��������������������������������������~~~
int xuhao1 = 0;
string siyuanshi1[100];

//�﷨�Ƶ�������Ԫʽ
void QUATFIRST()//���ɵ�һ����Ԫʽ
{
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(program," + "I0" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(program," + "I0" + "," + "_" + "," + "_" + ")";
	xuhao1++;
	xuhao++;
}
void QUATJIA()//�Ӻ�������Ԫʽ
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
void QUATJIAN()//����������Ԫʽ
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
void QUATCHENGE()//�˺�������Ԫʽ
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

//��ֵ���������Ԫʽ���躯��
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

void QUATLAST()//�������һ����Ԫʽ
{
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(end," + "I0" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(end," + "I0" + "," + "_" + "," + "_" + ")";
	xuhao1++;
	xuhao++;
}
void QUATBEGIN()//�������һ����Ԫʽ
{
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(begin," + "I0" + "," + "_" + "," + "_" + ")";
	siyuanshi1[xuhao1] = temp + "(begin," + "I0" + "," + "_" + "," + "_" + ")";
	xuhao++;
	xuhao1++;
}
void outputsiyuanshi()//���������Ԫʽ����
{
	cout << "��Ԫʽ����Ϊ��" << endl;
	int i = 0;
	while (siyuanshi[i] != "")
	{
		cout << siyuanshi[i] << endl;
		i++;
	}
	cout << endl;
}
/*
void outputsiyuanshi1()//���������Ԫʽ����
{
	cout << "��Ԫʽһ����Ϊ��" << endl;
	int i = 0;
	while (siyuanshi1[i] != "")
	{
		cout << siyuanshi1[i] << endl;
		i++;
	}
	cout << endl;
}
*/

//����Ϊ��������ѭ�����������Ԫʽ�������躯��
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
	s.Push(*p);//��bool���ʽ�Ľ������ջ��
}
void QUATTHEN()
{
	temp1 = s.Pop();
	string temp = "";
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "then" + "," + temp1 + "," + "_" + ",";//��ʱs.pop����bool���ʽ�Ľ��
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
	siyuanshi[xuhao] = "QT[" + int2str(xuhao) + "]:(" + "do" + "," + temp1 + "," + "_" + ",";//bool�Ǹ����Ѿ���bool���ʽ�Ľ�����ȥ�ˣ���s.pop
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
//������Ԫʽ��















//�����������
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
	cout << endl << "��������������:" << endl;
	if (chongdingyi == 1)
	{
		cout << "�ض������!" << endl;
		back++;
	}
	if (weidingyi == 1)
	{
		cout << "δ�������!" << endl;
		back++;
	}
	if (back > 0)
	{
		return;
	}
	else
	{
		cout << "������ȷ��" << endl;
	}
}
//�����������
//�����黮��

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
	cout << "�����黮��Ϊ��" << endl;
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
	cout << "������ɵĻ��������£�" << endl;
	for (i = 0; Operate[i].operationName.length() != 0; i++) {
		if (acc == "0")
			displayOperations(i);
		else displayOperations1(i);
		acc = Operate[i].ans;
	}
}

//������
int main() {
	changshubiaogoujian();
	biaoshifubiaogoujian();
	goujianfhb();
	//�����������Ϊ�����ʽ
	cout << "��������򣺣��Ի��м�#�Ž�����" << endl;
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
	//�������
	cout << endl << "token����Ϊ:" << endl;
	workout();//����token
	outputtoken();//�������token
	outputchangshubiao();
	outputbiaoshifubiao();
	outkeywords();
	outputjiefuchart();
	cout << endl << "�﷨����" << endl;
	if (PROGRAM() == 1)
	{
		cout << "the result of syntax analysis is succeed!" << endl << endl;
	}
	else
	{
		cout << "the result of syntax analysis is error!" << endl;
		//˵���������Ժ���ִ�к�������
	}
	outputsiyuanshi();//�����Ԫʽ����
	outputfhb();
	yuyifenxi();
	compa(siyuanshi1);
	last();
	return 1;
}
