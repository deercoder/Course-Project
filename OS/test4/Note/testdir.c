//Linux下面如何读取一个文件目录下的所有文件名称信息,注意包括文件夹和文件，这些所有的都要读取出来

//那么如何读取数字文件夹呢？很奇妙的办法就是，将读取的字符串看看第一个字符是否数字(当然可能有意外，不过也可以不做考虑,因为即使是root用户
//也不会随便修改其中的文件和新建文件！)

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h> //没有这个printf函数会报错！
#include <stdio.h>  //没有这个printf函数会报错！
//信息为：incompatible implicit declaration of built-in function ‘printf’
void main()
{
  DIR *dir;
  struct dirent *ptr;
  int i;
  dir = opendir("/proc");
  while((ptr = readdir(dir)) != NULL)
  {
     printf("d_name:%s\n",ptr->d_name);
  }
  closedir(dir);
}
