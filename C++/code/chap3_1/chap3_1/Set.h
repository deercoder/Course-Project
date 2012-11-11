#define  INCRESEMENT 10

class SET{
	int *set;  //set用于存放集合元素
	int card;   //card为足够存放的元素个数
	int used;   //used为已经存放的元素个数
public:
	SET(int card);  //card为能够存放的个数
	~SET();
	int size();       //返回集合已经存放的元素个数
	int insert(int v);  //插入v成功后返回1，否则返回0
	int remove(int v);  //删除v成功时返回1，否则返回0
	int has(int v);     //元素v存在返回1，否则返回0；
	void print();   //输出集合所有元素，便于检验结果用的，可用于调试。
};
