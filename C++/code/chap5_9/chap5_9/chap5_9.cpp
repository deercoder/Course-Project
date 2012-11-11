#include <iostream>
using namespace std;
class STATE;
class LIST{		//用作STATE变化的一个指标
	LIST *next;
	char input;
	STATE *output;
	LIST(char in,STATE *out);	//私有，仅供STATE 使用
	~LIST();
	friend STATE;	//定义为友元可以访问
};

class STATE{
	char *name;	//状态名
	LIST *list;	//输入输出列表
	static STATE *error;	//自动机陷阱
public:
	void enlist(char in,STATE *out);	//插入list
	const STATE *next(char in)const;	//插入in转移到下一个状态
	const STATE *start(char *)const;	//启动有限自动机
	STATE(char *name);
	~STATE();
};

LIST::LIST(char in,STATE *out){   
	input=in;   
	output=out;   
	next=NULL;	//将下一个指针域置为空，创建一个节点的LIST  
}   
LIST::~LIST(){   
	if(this->next != NULL){
		delete this->next;
	}   
}   
STATE   *STATE::error = NULL;   
STATE::STATE(char *name):name(0),list(0){ 
	if(name==0){
		error = this;	//出现自动机陷阱
		return;   
	}   
	STATE::name=new char[strlen(name)+1];   
	strcpy(this->name,name);   
}  

void STATE::enlist(char in,STATE *out){	//插入list   
	LIST *temp;   
	if(list==0){   
		list=new   LIST(in,   out);   
		return;   
	}   
	temp=new LIST(in,out);   
	temp->next=list;   
	list=temp;   
}   
const STATE *STATE::next(char in)const{	//输入in转移到下一个状态   
	LIST *temp=list;   
	if(this==error)   
		return   error;   
	while(temp){   
		if(temp->input==in)   
			return   temp->output;   
		else   
			temp=temp->next;   
		return   error;  
	}
}   
const STATE *STATE::start(char *s)const{	//启动有限自动机   
	const   STATE   *temp=this;   
	while(*s)   
		temp=temp->next(*s++);   
	return   temp;   
}   
STATE::~STATE(){   
	if(name){
		cout<<name<<"\n";  
		delete   name;  
		name=0;   
	}   
	if(list){
		delete   list;  
		list=0;  
	}   
}   
void   main(   ){   
	STATE   start("WSGM_");   //初始状态
	STATE   stop("_WSGM");   
	STATE   error(0);   
	STATE   WG_SM("WG_SM");   //人带狼过为W表示
	STATE   WGM_S("WGM_S");   //人带草过为G表示
	STATE   G_WSM("G_WSM");		//人自己过为M表示
	STATE   SGM_W("SGM_W");   
	STATE   W_SGM("W_SGM");   //左边定义的各个状态都是用相应的字符串表示
	STATE   WSM_G("WSM_G");   //表示进行的相关的表示，通过后面的enlist
	STATE   S_WGM("S_WGM");   //添加状态，然后实现自动机的切换
	STATE   SM_WG("SM_WG");   //动态地生成状态转换表并变化切换
	start.enlist('S',   &WG_SM);   
	WG_SM.enlist('S',   &start);   
	WG_SM.enlist('M',   &WGM_S);   
	WGM_S.enlist('M',   &WG_SM);   
	WGM_S.enlist('W',   &G_WSM);   
	WGM_S.enlist('G',   &W_SGM);   
	G_WSM.enlist('W',   &WGM_S);   
	W_SGM.enlist('G',   &WGM_S);   
	G_WSM.enlist('S',   &SGM_W);   
	SGM_W.enlist('S',   &G_WSM);   
	SGM_W.enlist('G',   &S_WGM);   
	S_WGM.enlist('G',   &SGM_W);   
	W_SGM.enlist('S',   &WSM_G);   
	WSM_G.enlist('S',   &W_SGM);   
	WSM_G.enlist('W',   &S_WGM);   
	S_WGM.enlist('W',   &WSM_G);   
	S_WGM.enlist('M',   &SM_WG);   
	SM_WG.enlist('M',   &S_WGM);   
	SM_WG.enlist('S',   &stop);   
	stop.enlist('S',   &SM_WG);   
	if(start.start("SMWSGMSSS")==&stop)  //过河成功
		cout<<"OK";   
}   