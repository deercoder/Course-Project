#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct{
   ElmType *elem;
   int length;
   int listsize;
   }SqList;
   
Status InitList_Sq(SqList &L)
{//构造一个空的线性表L
  L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
  if(!L.elem) exit(OVERFLOW);
  L.length = 0;
  L.listsize = LIST_INIT_SIZE;
  return OK;
}//InitList_Sq

Status ListInsert_Sq(Sqlist &L,int i, ElemType e)
{ //在顺序表L中的第i个位置之前插入新的元素e；
	//i的合法值为1<=i<=ListLength_Sq(L)+1;
	if(i<1||i>L.length+1) return ERROR;
	if(L.length>=L.listsize){// 当前的存储空间已满，增加分配
		 newbase = ( ElemType *)realloc(L.elem,( L.listsize +LISTINCREMENT)*sizeof(ElemType));
		 if(!newbase) exit(OVERFLOW) ; //存储空间分配失败
		 L.elem = newbase;
		 L.listsize+=LISTINCREMENT;	 
   }
   q=&(L.elem[i-1]);
   for(p=&(L.elem[L.length-1]);p>=q;--p)  *(p+1)=*p;
                                       //插入位置及之后的元素右移            
   *q=e;
   ++L.length;
   return OK;
}//ListInsert_Sq;

Status ListDelete_Sq(SqList &L, int i, ElemType &e) {  // 算法2.5
  // 在顺序线性表L中删除第i个元素，并用e返回其值。
  // i的合法值为1≤i≤ListLength_Sq(L)。
  ElemType *p, *q;
  if (i<1 || i>L.length) return ERROR;  // i值不合法
  p = &(L.elem[i-1]);                   // p为被删除元素的位置
  e = *p;                               // 被删除元素的值赋给e
  q = L.elem+L.length-1;                // 表尾元素的位置
  for (++p; p<=q; ++p) *(p-1) = *p;     // 被删除元素之后的元素左移
  --L.length;                           // 表长减1
  return OK;
} // ListDelete_Sq

int LocateElem_Sq(SqList L, ElemType e,
        Status (*compare)(ElemType, ElemType)) {  // 算法2.6
  // 在顺序线性表L中查找第1个值与e满足compare()的元素的位序。
  // 若找到，则返回其在L中的位序，否则返回0。
  int i;
  ElemType *p;
  i = 1;        // i的初值为第1个元素的位序
  p = L.elem;   // p的初值为第1个元素的存储位置
  while (i <= L.length && !(*compare)(*p++, e)) 
    ++i;
  if (i <= L.length) return i;
  else return 0;
} // LocateElem_Sq

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc) {  // 算法2.7
  // 已知顺序线性表La和Lb的元素按值非递减排列。
  // 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列。
  ElemType *pa,*pb,*pc,*pa_last,*pb_last;
  pa = La.elem;  pb = Lb.elem;
  Lc.listsize = Lc.length = La.length+Lb.length;
  pc = Lc.elem = (ElemType *)malloc(Lc.listsize*sizeof(ElemType));
  if (!Lc.elem)
    exit(OVERFLOW);   // 存储分配失败
  pa_last = La.elem+La.length-1;
  pb_last = Lb.elem+Lb.length-1;
  while (pa <= pa_last && pb <= pb_last) {  // 归并
    if (*pa <= *pb) *pc++ = *pa++;
    else *pc++ = *pb++;
  }
  while (pa <= pa_last) *pc++ = *pa++;      // 插入La的剩余元素
  while (pb <= pb_last) *pc++ = *pb++;      // 插入Lb的剩余元素
} // MergeList
