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
	int yy=0;
char test[1000];
struct Token {
	char content[10];
	int code;
}token[100];              //token序列结构体数组，用来存放生成的token
char ttoken;
int number;
char chuli[1000];
char token_content[10];
int token_code;
int changshucharuhanshu(string a);
int biaoshifucharuhanshu(string a);
void caozuo();
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
	for (i = 0; i < 18; i++)
        {
		if (ch == jiefuchart[i])
			return (i+1) ;
	}
	return 0;
}
int konggeornot(char ch) {  //判断当前字符是不是空格
	if (ch ==' ')
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
	ttoken=token[tag].content[0];
			number=token[tag].code;
	tag++;
}

void jiefuchuli(char* p)
{      //界符处理函数
	int j = jiefuornot(*p);
	p++;
	int m=jiefuornot(*p);
	p--;
	if(j==6)
    {
        if(m==6)
    {    p++;
        index++;
        p++;
        index++;
        while(konggeornot(*p)!=1)
        {
            p++;
            index++;
        }
      //  index++;

    }
    if(m!=6)
    {
        token[tag].code = j-1;
	token[tag].content[0] = 'p';
	ttoken=token[tag].content[0];
    number=token[tag].code;
	index++;
	tag++;
    }

    }
    if(j==10)
    {   if(m==5)
        {p++;
        index++;
        index++;
        p++;
        while(jiefuornot(*p)!=5)
        {   p++;
            if(jiefuornot(*p)!=11)
            {
                index++;
            }
        }}
        if(m!=5)
        {
             token[tag].code = j-1;
	         token[tag].content[0] = 'p';
	        ttoken=token[tag].content[0];
            number=token[tag].code;
	        index++;
	       tag++;
        }
    }

        if(j==17)
    {
        p++;
        index++;
        while(jiefuornot(*p)!=18)
        {
            p++;
            index++;
        }
        index++;
    }
    if((j!=17)&&(j!=10)&&(j!=6))
    {
        token[tag].code = j-1;
	token[tag].content[0] = 'p';
	ttoken=token[tag].content[0];
    number=token[tag].code;
	index++;
	tag++;}





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
			ttoken=token[tag].content[0];
			number=token[tag].code;
			tag++;
			return 1;
		}
	}
	token[tag].code = biaoshifucharuhanshu(token[tag].content);
	token[tag].content[0] = 'i';
	ttoken=token[tag].content[0];
			number=token[tag].code;
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


void workout()
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
			tag1++;}


		}

	if (test[index] == '#')
		return ;
}



void workout1()//生成token序列函数，其实就是使用自动机的原理
{  //  cout<<"*********tokenxuliewei:" << endl;

  //  while(test[index] != '#')
	//{
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
			tag1++;}


	//	}}

	if (test[index] == '#')
		return ;
}
void output()
{
    int i=0;
    while(token[i].content[0]!='\0' )
    {
        cout<<'('<<token[i].content[0]<<" "<<token[i].code<<')'<<endl;
        i++;
    }

}
void outputchangshubiao()//输出常数表
{
	cout<< endl<<"*********常数表如下：" << endl;
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






void wenjianchuli()
{  ifstream file;
      file.open("C:\\bykcsj\\data.txt",ios::in);
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
	//cout<<test;

}

void zhongji1()
{
     changshubiaogoujian();
	biaoshifubiaogoujian();
	wenjianchuli();
//	cout<<"***************token序列为"<<endl;
}
/*void zhongji2()
{
   //  workout();  //生成token
     cout<<"*********token序列为:" << endl;
	while(test[index]!='#')
	{    workout();  //生成token
	    cout<<'('<<ttoken<<','<<number<<')'<<" ";
	    yy++;
	    //}
	if(yy==15)
    {
        cout<<endl;
        yy=0;
    }}
 //   output();
}
*/
void zhongji2()
{
    workout();
    output();
}



int ip=0;
int fun_code=-1;

//语法分析开始
int PROGRAM();
int SUB_PROGRAM();
int VARIABLE();
int ID_SEQUENCE();
int ARRAY();
int TYPE();
int ANOUNCE_FUNCTION();
int FUN_SENTENCE();
int RETURN();
int FUNCTION();
int COM_SENTENCE();
int SEN_SEQUENCE();
int CONDITION();
int CIRCLE();
int EVA_SENTENCE();
int EXPRESSION();
int TERM();
int FACTOR();
int BOOL();

//PROGRAM ->program id SUB_PROGRAM.
int PROGRAM()
{
    if((token[ip].content[0]=='k')&&(token[ip].code==0))//是programa
	{
	    //QUATFIRST();//生成第一个四元式
		ip++;
	}
	else
        return 0;
    if(token[ip].content[0]=='i')
    {
        //func0();
        ip++;
        if(SUB_PROGRAM()==1)
        {
            if((token[ip].content[0]=='p')&&(token[ip].code==8))
            {
                //QUATLAST();//生成最后一个四元式
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;

}

//SUB_PROGRAM ->VARIABLE  {ANOUNCE_FUNCTION;} COM_SENTENCE
int SUB_PROGRAM()
{
    if(!VARIABLE())
    {
       return 0;
    }
    else
    {
        while(ANOUNCE_FUNCTION())
        {
            if((token[ip].content[0]=='p')&&(token[ip].code==2))
            {
                ip++;
            }
            else
            {
                return 0;
            }
        }
        if(!COM_SENTENCE())
        {
            return 0;
        }
        else
            return 1;
    }
}

//VARIABLE ->var ID_SEQUENCE ：TYPE ；{ID_SEQUENCE ：TYPE ；}
int VARIABLE()
{
    if((token[ip].content[0]=='k')&&(token[ip].code==1))
    {
       // func1();
        ip++;
    }
    else
    {
        return 0;
    }
    if(!ID_SEQUENCE())
    {
        return 0;
    }
    if(!((token[ip].content[0]=='p')&&(token[ip].code==1)))
       return 0;
    else
    {
       // func7();
        ip++;
    }
    if(!TYPE())
        return 0;
    else
	{
		//func6();
	}
    if(!((token[ip].content[0]=='p')&&(token[ip].code==2)))
       return 0;
    else
        ip++;
    while(ID_SEQUENCE())
    {
          if(!((token[ip].content[0]=='p')&&(token[ip].code==1)))
            return 0;
          else
          {
             // func7();
              ip++;
          }
          if(!TYPE())
            return 0;
          else
	      {
		      //func6();
	      }
          if(!((token[ip].content[0]=='p')&&(token[ip].code==2)))
            return 0;
          else
            ip++;
    }
    return 1;

}



//ID_SEQUENCE ->id ARRAY{，id ARRAY}
int ID_SEQUENCE()
{
    if(!(token[ip].content[0]=='i'))
    {
        return 0;
    }
    else
    {
        //SEARCH1(biaoshifubiao[token[ip].code]);
		//func2();
        ip++;
    }
    if(!ARRAY())
    {
        return 0;
    }
    else
    {
        //func8(biaoshifubiao[token[ip - 4].code], str2int(changshubiao[token[ip - 2].code]));
    }
    while((token[ip].content[0]=='p')&&(token[ip].code==0))
    {
        ip++;
        if(token[ip].content[0]=='i')
        {
            //SEARCH1(biaoshifubiao[token[ip].code]);
		    //func2();
            ip++;
        }
        else
            return 0;
        int rn=ARRAY();
        if(rn==0)
            return 0;
        if(rn==2)
        {
            //func8(biaoshifubiao[token[ip - 4].code], str2int(changshubiao[token[ip - 2].code]));
        }
    }
    return 1;
}

//ARRAY->e|[cons]
int ARRAY()
{
    if((token[ip].content[0]=='p')&&(token[ip].code==14))
    {
        ip++;
    }
    else
    {
        return 1;
    }
    if(token[ip].content[0]=='c')
	{
		ip++;
	}
	else
    {
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==15))
    {
        ip++;
        return 2;
    }
    else
    {
        return 0;
    }
}

//TYPE ->integer| real| char
int TYPE()
{
    if(token[ip].content[0]=='k')
    {
        if (token[ip].code == 2)//k2为integer
		{
			//func3();
			ip++;
			return 1;
		}
		else if (token[ip].code == 3)//k3为real
		{
			//func4();
			ip++;
			return 2;

		}
		else if (token[ip].code == 4)//k4为char
		{
			//func5();
			ip++;
			return 3;
		}
		else
	    {
		    return 0;
	    }


    }
    else
        return 0;
}

//ANOUNCE_FUNCTION->var  id(id :TYPE {,id：TYPE }):TYPE FUN_SENTENCE
int ANOUNCE_FUNCTION()
{
    //string str_id, str_type;
	//function fun;//用于保存子程序信息
	if ((token[ip].content[0]=='k')&&(token[ip].code==1))/*是var*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	if (token[ip].content[0]=='i')/*正确识别一个标示符*/
	{
		/*str_id = biaoshifubiao[token[ip].code];
		SEARCH1(biaoshifubiao[token[ip].code]);
		fun.name = biaoshifubiao[token[ip].code];
		fun.fn = 0;
		for (int i=0;i<10;i++)
		{
			fun.params[i]="#";
			fun.types[i]="#";
			fun.lens[i]=0;
		}*/
		fun_code=token[ip].code;
		ip++;
	}
	else
	{
		return 0;
	}
	if ((token[ip].content[0]=='p')&&(token[ip].code ==9))/*是(*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	if(token[ip].content[0]=='i')/*正确识别一个标示符*/
	{
		/*int k = fun.fn;
		fun.params[k] = biaoshifubiao[token[ip].code];
		fun.fn++;*/
		ip++;
	}
	else
	{
		return 0;
	}
	if((token[ip].content[0] == 'p')&&(token[ip].code==1))/*是：*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	int rn=TYPE();
	//int k=fun.fn-1;
	if (rn==1)/*是type*/
	{
		//fun.types[k]="i";
		//fun.lens[k]=4;

	}
	else if(rn==2)
	{
		//fun.types[k]="r";
		//fun.lens[k]=8;

	}
	else if(rn==3)
	{
		//fun.types[k]="c";
		//fun.lens[k]=1;
	}
	else
	{
		return 0;
	}
	while (((token[ip].content[0]=='p')&&(token[ip].code==0)))//当是，时
	{
		ip++;
		if(token[ip].content[0]=='i')/*正确识别一个标示符*/
		{
			/*int k = fun.fn;
			fun.params[k] = biaoshifubiao[token[ip].code];
			fun.fn++;*/
			ip++;
		}
		else
		{
			return 0;
		}
		if ((token[ip].content[0]=='p')&&(token[ip].code==1))/*是：*/
		{
			ip++;
		}
		else
		{
			return 0;
		}
		rn= TYPE();
		//int k = fun.fn - 1;
		if (rn == 1)/*是type*/
		{
			/*fun.types[k] = "i";
			fun.lens[k] = 4;*/

		}
		else if (rn== 2)
		{
			/*fun.types[k] = "r";
			fun.lens[k] = 8;*/

		}
		else if (rn== 3)
		{
			/*fun.types[k] = "c";
			fun.lens[k] = 1;*/
		}
		else
		{
			return 0;
		}
	}
	if ((token[ip].content[0]=='p')&&(token[ip].code==10))/*是)*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 1))/*是：*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	rn= TYPE();
	if (rn== 1)/*是type*/
	{
		/*str_type = "interger";
		fun.type = "i";
		fun.len = 4;*/

	}
	else if (rn== 2)
	{
		/*str_type = "real";
		fun.type = "r";
		fun.len = 8;*/
	}
	else if (rn== 3)
	{
		/*str_type = "char";
		fun.type = "c";
		fun.len = 1;*/
	}
	else
	{
		return 0;
	}
	//QUATHANSHUSHENGMING(str_id, str_type);
	if (!FUN_SENTENCE())
    {
		return 0;
	}
	//func10(fun);
	return 1;
}

//FUN_SENTENCE->begin SEN_SEQUENCE|CONDITION|CIRCLE  {；SEN_SEQUENCE | CONDITION | CIRCLE} RETURN end
int FUN_SENTENCE()
{
	if ((token[ip].content[0] == 'k') && (token[ip].code == 5))/*是begin*/
	{
		//QUATBEGIN();
		ip++;
	}
	else
	{
		return 0;
	}

	int tp=ip;
	int fh=SEN_SEQUENCE();
	if(fh==0)
    {
        ip=tp;
        tp=ip;
        if(!CONDITION())
        {
           ip=tp;
           tp=ip;
           if(!CIRCLE())
           {
               return 0;
           }
        }
    }
	while (((token[ip].content[0]=='p')&&(token[ip].code==2)))
	{
		ip++;
        tp=ip;
        fh=SEN_SEQUENCE();
	if(fh==0)
    {
        ip=tp;
        tp=ip;
        if(!CONDITION())
        {
           ip=tp;
           tp=ip;
           if(!CIRCLE())
           {
               return 0;
           }
        }
    }
    }

	if (RETURN()== 1)
	{
		//QUATRETURN();
	}
	else
	{
		return 0;
	}
	if (!((token[ip].content[0] == 'k') && (token[ip].code == 6)))//k6为end
	{
		return 0;
	}
	else
	{
		//QUATLAST();
		ip++;

	}
	//cout<<token[ip].content[0]<<token[ip].code<<endl;
    return 1;
}

//RETURN->id:= FACTOR;
int RETURN()
{
	if ((token[ip].content[0]=='i'))/*是return*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	if((token[ip].content[0]=='p')&&(token[ip].code==1))
	{
		ip++;
	}
	else
    {
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==3))
	{
		ip++;
	}
	else
        return 0;
	if (!FACTOR())
	{
		return 0;
	}
	if((token[ip].content[0]=='p')&&(token[ip].code==2))/*是(*/
	{
		ip++;
	}
	else
    {
        return 0;
    }
    return 1;
}

//FUNCTION->id(id{,id})
int FUNCTION()
{
	//string str_id;
	if (token[ip].content[0] == 'i')/*正确识别第一个标示符*/
	{
		//str_id = biaoshifubiao[token[ip].code];
		ip++;
	}
	else
	{
		return 0;
	}
	if((token[ip].content[0]=='p')&&(token[ip].code==9))/*是(*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	if (token[ip].content[0] == 'i')/*正确识别第一个标示符*/
	{
		//?cout << "识别第一个参数" << endl;
		ip++;
	}
	else
	{
		return 0;
	}
	while (((token[ip].content[0] == 'p') && (token[ip].code == 0)))/*p1是逗号*/
	{
		ip++;
		if (token[ip].content[0] == 'i')
		{
			ip++;
		}
		else
		{
            return 0;
		}
	}
	if ((token[ip].content[0] == 'p') && (token[ip].code == 10))/*是)*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	//QUATDIAOYONG(str_id);
	return 1;
}

//COM_SENTENCE ->begin SEN_SEQUENCE|CONDITION|CIRCLE|FUNCTION {；SEN_SEQUENCE | CONDITION | CIRCLE|FUNCTION} end
int COM_SENTENCE()
{
	if ((token[ip].content[0]=='k')&&(token[ip].code==5))/*是begin*/
	{
		//QUATBEGIN();
		ip++;
	}
	else
	{
		return 0;
	}
	int tp=ip;
	int fh=SEN_SEQUENCE();
	if(fh==0)
    {
        ip=tp;
        tp=ip;
        if(!CONDITION())
        {
           ip=tp;
           tp=ip;
           if(!CIRCLE())
           {
              ip=tp;
              tp=ip;
              if(!FUNCTION())
              {
                 return 0;
              }
           }
        }
    }
	while (((token[ip].content[0]=='p')&&(token[ip].code==2)))
	{
		ip++;
        tp=ip;
        fh=SEN_SEQUENCE();
	if(fh==0)
    {
        ip=tp;
        tp=ip;
        if(!CONDITION())
        {
           ip=tp;
           tp=ip;
           if(!CIRCLE())
           {
              ip=tp;
              tp=ip;
              if(!FUNCTION())
              {
                 return 0;
              }
           }
        }
    }
    }
	if (!((token[ip].content[0]=='k')&&(token[ip].code==6)))//k6为end
	{
		return 0;
	}
	else
	{
		ip++;
	}
    return 1;
}

//SEN_SEQUENCE -> EVA_SENTENCE {；EVA_SENTENCE }
int SEN_SEQUENCE()
{
    if (EVA_SENTENCE()==0)
	{
		return 0;
	}
	while((token[ip].content[0]=='p')&&(token[ip].code==2)&&(token[ip+1].content[0]!='k')&&((token[ip+1].content[0]!='i')&&(token[ip+1].code==fun_code)))
    {
        ip++;
        if(!EVA_SENTENCE())
            return 0;

    }
    if(((token[ip+1].content[0]=='k')&&(token[ip+1].code==6))||((token[ip+1].content[0]=='i')&&(token[ip+1].code==fun_code)))
        ip++;
    return 1;
}
//条件语句和循环语句语法分析
//CONDITION  -> if  BOOL then  SEN_SEQUENCE else SEN_SEQUENCE ifend
int CONDITION()
{
	if((token[ip].content[0]=='k')&&(token[ip].code==7))
	{
		ip++;
	}
	else
	{
		return 0;
	}
	if(!BOOL())
	{
		return 0;
	}
	if((token[ip].content[0]=='k')&&(token[ip].code==8))//k8为then
	{
		//QUATTHEN();
		//jilu++;//很重要，不遗漏
		ip++;
	}
	else
	{
		return 0;
	}
	if(!SEN_SEQUENCE())
	{
		return 0;
	}

	if((token[ip].content[0]=='k')&&(token[ip].code==9))
	{
		//QUATELSE();
		ip++;
		if(!SEN_SEQUENCE())
		{
			return 0;
		}
		if((token[ip].content[0]=='k')&&(token[ip].code==12))
		{
			//QUATIFEND();
			ip++;
		}
		else
            return 0;
	}
	return 1;
}

//CIRCLE -> while BOOL do COM_SENTENCE
int CIRCLE()
{

	if((token[ip].content[0]=='k')&&(token[ip].code==10))//是while
	{
		//QUATWHILE();
		ip++;
	}
	else
	{
		return 0;
	}
	if(!BOOL())
	{
		return 0;
	}
	if ((token[ip].content[0]=='k')&&(token[ip].code==11))/*不是do*/
	{
		//QUATDO();
		//jilu++;//很重要，不遗漏
		ip++;
	}
	else
	{
		return 0;
	}
	if (!COM_SENTENCE())
	{
		return 0;
	}
	//QUATWHILEEND();
	return 1;
}

//EVA_SENTENCE -> id ARRAY := EXPRESSION
int EVA_SENTENCE()
{
	/*int temp;
	string length = "";
	int type = 0;*/
	if(token[ip].content[0]!='i')
	{
		return 0;
	}
	else
	{
		/*SEARCH2(biaoshifubiao[token[ip].code]);
		temp=searchfhb(biaoshifubiao[token[ip].code]);
		if(fhb[temp][1]=="i")
		{
			FUNC1();
		}
		if(fhb[temp][1]=="r")
		{
			FUNC2();
		}
		if(fhb[temp][1]=="c")
		{
			FUNC3();
		}
		tp=biaoshifubiao[token[ip].code];*/
		ip++;
	}
	int rn=ARRAY();
	if(rn==0)
	{
		return 0;
	}
	if(rn==2)
    {
		//length=changshubiao[token[ip-2].code];
		//type=1;
	}
	if((token[ip].content[0]=='p')&&(token[ip].code==1))
    {
        ip++;
    }
    else
    {
        return 0;
    }
	if((token[ip].content[0]=='p')&&(token[ip].code==3))
    {
        ip++;
	}
	else
	{
		return 0;
	}

	if(!EXPRESSION())
	{
		return 0;
	}
	//QUATFUZHI(length, type);
	return 1;
}

//EXPRESSION -> EXPRESSION + TERM | EXPRESSION - TERM | TERM
int EXPRESSION()
{
	if(!TERM())
	{
		return 0;
	}
	while (((token[ip].content[0]=='p')&&(token[ip].code==6))||((token[ip].content[0] == 'p')&&(token[ip].code==7)))
	{
		ip++;
		if(!TERM())
		{
			return 0;
		}
		/*if(((token[ip].content[0]=='p')&&(token[ip].code==6)))
			QUATJIA();
		else
			QUATJIAN();
		jilu++;*/
	}
	//FUNC5();
	//FUNC6();
    return 1;
}

//TERM -> TERM *  FACTOR | TERM /  FACTOR | FACTOR
int TERM()
{
	if(!FACTOR())
	{
		return 0;
	}
	while(((token[ip].content[0]=='p')&&(token[ip].code==4))||((token[ip].content[0]=='p')&&(token[ip].code==5)))
	{
		ip++;
		if(!FACTOR())
		{
			return 0;
		}
		/*if (((token[ip].content[0]=='p')&&(token[ip].code == 4)))
			QUATCHENGE();
		else
			QUATCHU();
		jilu++;*/
	}
    return 1;
}

//FACTOR -> id ARRAY | cons | ( EXPRESSION )
int FACTOR()
{
	//string str;
	if((token[ip].content[0]=='i')) /*是标识符*/
	{
       // str = biaoshifubiao[token[ip].code];
        ip++;
        int rn=ARRAY();
        if(rn==1||rn==2)
        {
            /*if(rn==2)
            {
                string length =changshubiao[token[ip-2].code];
                str += "[" + length + "]";
            }
            s.Push(str);*/
            return 1;
			/*else
				s.Push(str);*/
         }
         else
            return 0;
     }


    else if(token[ip].content[0]=='c')
    {
        //s.Push(changshubiao[token[ip].code]);
        ip++;
        return 1;
    }
    else if((token[ip].content[0]=='p')&&(token[ip].code==9))/*是左括号*/
	{
		ip++;
	}
	else
	{
		return 0;
	}
	if(!EXPRESSION())
	{
		return 0;
	}
	if((token[ip].content[0]=='p')&&(token[ip].code==10))/*是右括号*/
	{
		ip++;
	}
	else
    {
        return 0;
    }
    return 1;
}

//string bo;//存取bool的比较符，要插动作
//BOOL ->  FACTOR  <|>|@ FACTOR
int BOOL()
{
	if(!FACTOR())
	{
		return 0;
	}
	if (token[ip].content[0]!='p')
	{
		return 0;
	}
	if (!((token[ip].code==11)||(token[ip].code==12)||(token[ip].code==13)))
	{
		return 0;
	}
	else
	{
		/*if (token[ip].code == 11)//p12为小于号
		{
			bo="<";
		}
		if (token[ip].code == 12)//p13为大于号
		{
			bo=">";
		}
		if (token[ip].code == 13)//p14为判断是否相等
		{
			bo="@";
		}*/
		ip++;
	}
	if (!FACTOR())
	{
		return 0;
	}
	//QUATBOOL();
	return 1;
}

int main()
{

	zhongji1();
	    zhongji2();
	outputchangshubiao();
	outputbiaoshifubiao();
    int  rt;
    rt=PROGRAM();
    cout<<endl<<"语法分析结果："<<endl;
    if(rt==1)
        cout<<endl<<"right"<<endl;
    else
       {
        cout<<endl<<"false"<<endl;
        exit(0);
       }
    return 0;
}


