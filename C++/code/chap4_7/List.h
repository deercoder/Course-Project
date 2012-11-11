#define MAX 25
class Student{
	char name[MAX];
	char password[MAX];
	float English;
	float Math;
	float Physics;
	float Chemistry;
public:
	Student();				//默认构造一个空的记录
	Student(char *nam,char *psw);		//构造一个含有姓名和密码的记录
	Student(char *name,char *psw,float Eng,float Math,float phy,float chem); //构造完整的记录
	~Student();
	float getEnglish();				//得到英语成绩
	float getMath();			//得到数学成绩
	float getPhysics();			//得到物理成绩
	float getChemistry();		//得到化学成绩
	void changeName(char *newname);		//更改姓名
	void changePassword(char *newpassword);    //更改密码
	void setEnglish(float Englishscore);	//  设定/修改英语成绩
	void setMath(float Mathscore);			//  设定/修改数学成绩
	void setPhysics(float Physicscore);		//  设定/修改物理成绩
	void setChemistry(float Chemistryscore);		//  设定/修改化学成绩
	int enterPsw(char *input);			//输入密码，成功匹配返回1，否则返回0
	void print();			//输出所有信息，便于调试使用
};