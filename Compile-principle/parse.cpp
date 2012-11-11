#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char prog[80], token[8];
char ch;
int syn, p, m, n, sum, kk=0;
char *rwtab[]={"main", "if", "else", "while", "do", "for"};

void scaner();
void lrparser();  
void yucu();    
void statement();	
void expression();	
void term();		
void factor();

void main()
{
	p=0;
	FILE *fp;
	if((fp=fopen("data.txt","r"))==NULL){
        printf("无法打开文件!");
        exit(0);
     }
	fscanf(fp,"%[^$]s",prog);		//从流中按格式读取
	fclose(fp);
	printf("Your words:\n%s\n",prog);
	scaner();
	lrparser();
	printf("\npress # to exit:");
	scanf("%[^#]s",prog); 
}

void scaner()
{
	for(n=0; n<8; n++) token[n]=NULL;
		ch=prog[p++];
	while(ch==' '||ch=='\n') ch=prog[p++];
	m=0;
	if((ch>='A'&&ch<='Z') || (ch>='a'&&ch<='z'))
	{
		while((ch>='A'&&ch<='Z') || (ch>='a'&&ch<='z')||(ch>='0'&&ch<='9'))
		{
			token[m++]=ch;
			ch=prog[p++];
		}
		token[m++]='\0';
		p--;
		syn=10;
		for(n=0; n<6; n++)
		{
			if(strcmp(token, rwtab[n])==0)
			{
				syn=n+1;
				break;
			}
		}
	}
	else if(ch>='0'&&ch<='9')
	{
		sum=0;
		while(ch>='0'&&ch<='9')
		{
			sum=sum*10+ch-'0';
			ch=prog[p++];
		}
		p--;
		syn=11;
	}
	else
	{
		switch(ch){
			case '<':
				m=0;
				token[m++]=ch;
				ch=prog[p++];
				if(ch=='>')
				{
					syn=21;
					token[m++]=ch;
				}
				else if(ch=='=')
				{
					syn=22;
					token[m++]=ch;
				}
				else
				{
					syn=20;
					p--;
				}
				break;
			case '>':
				token[m++]=ch;
				ch=prog[p++];
				if(ch=='=')
				{
					syn=24;
					token[m++]=ch;
				}
				else
				{
					syn=23;
					p--;
				}
				break;
			case '+':
				syn=13;
				token[m++]=ch;
				break;
			case '-':
				syn=14;
				token[m++]=ch;
				break;
			case '*':
				syn=15;
				token[m++]=ch;
				break;
			case '/':
				syn=16;
				token[m++]=ch;
				break;
			case '=':
				syn=18;
				token[m++]=ch;
				break;
			case ';':
				syn=26;
				token[m++]=ch;
				break;
			case '(':
				syn=27;
				token[m++]=ch;
				break;
			case ')':
				syn=28;
				token[m++]=ch;
				break;
			case '{':
				syn=29;
				token[m++]=ch;
				break;
			case '}':
				syn=0;
				token[m++]=ch;
				break;
			default:
				syn=-1;
		}
		token[m++]='\0';
	}
}

void factor()
{
	if(syn==10 || syn==11)   //字母或数字
	{
		scaner();
	}
	else 
		if(syn==27)      //'('
		{
			scaner();
			expression();
			if(syn==28)      //')'
				scaner();
			else
			{
				kk=1;
			}
		}
		else
		{
			kk=1;
		}
}

void term()
{
	factor();
	while(syn==15 || syn==16)   //'*'|'/'
	{
		scaner();
		factor();
	}
}

void expression()
{
	term();
	while(syn==13 || syn==14)   //'+'|'-'
	{
		scaner();
		term();
	}
}

void statement()
{
	if(syn==10)      //字母
	{
		scaner();
		if(syn==18)  //'='
		{
			scaner();
			expression();
		}
		else
		{
			kk=1;
			return;
		}
	}
	else
	{
		kk=1;
		return;
	}
}

void yucu()
{
	statement();
	while(syn==26)		//';'
	{
		scaner();
		statement();
	}
}

void lrparser()
{   
	if(syn==1)		//"main"
	{
		scaner();
		if(syn==27){	//'('
			scaner();
			if(syn==28){	//')'
				scaner();
				if(syn==29){	//'{
					scaner();
					yucu();
					int len = strlen(prog);
					if(syn==0 && kk==0&&prog[len-3]!='}'){
						printf("成功!\n");
						return;
					}
				}
			}
		}
	}
	printf("语法错误!\n");
}
