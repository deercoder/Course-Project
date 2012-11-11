#include "list.h"

INTLIST::INTLIST(int s)
{
	list = (int *)malloc(s * sizeof(int));
	size = s;
	used = 0;
}

INTLIST::~INTLIST()
{
	free(list);
}

int INTLIST::insert(int v)
{
   if (size == 0) //已满，需要重新分配
   {
	   size += INCREMENT;
	   list = (int *)realloc(list,size * sizeof(int));
	   list[used] = v;
	   ++used;
	   --size;
	   return 1;
   }
	else  //假设数据可以重复
	{
	   list[used] = v;
	   ++used;
	   --size;
	   return 1;
	}
	return 0;
}

int INTLIST::remove(int v)
{
	if (find(v) == 1)
	{
		int tmp = 0;
		for (int i = 0; i < used; i++)
		{
			if (list[i] == v)
				tmp = i;
		}
		for (int i = tmp; i < used-1; i++)
		{
			list[i] = list[i+1];
		}
		--used;
		++size;
		return 1;
	}
	else
		return 0;
}
int INTLIST::find(int v)
{
	for (int i = 0; i < used; i++)
	{
		if (list[i] == v)
			return 1;
	}
	return 0;
}
int INTLIST::get(int k)
{
	return list[k-1];
}

void INTLIST::print()
{
	cout << "所有的元素如下所示：" << endl;
	for (int i = 0; i < used; i++)
	{
		cout << "i : " << i << "\t" <<"对应的取值为：" 
			<<list[i] <<"\t\t";
		cout << ((i%2 == 1) ? "\n" : "");
	}
	cout << endl;
}
