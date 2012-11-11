#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>//原文遗漏，添加上。

int main(void)
{
  int fd;
  char buf[1024];
  char get[1024];
  fd=open("/dev/mytest", O_RDWR);
  if(fd != -1 )
 {
   read(fd, buf, sizeof(buf));
   printf("The message is %s\n", buf);
   printf("Please input the string\n");
   scanf("%s", get);
   write(fd, get, sizeof(get)); //将读入的信息get写入文件设备中
   read(fd, buf, sizeof(buf));  //将文件设备中字符读入到buf中
//注：根据前面的操作，buf的内容是本身设备的读取，而经过上面write和read操作后，buf的内容就是输入的内容，所以，这里
//根据输出的结果，来判断是否真正的写入和读出到设备，如果没有，那么输出的内容应该还是原始的数据，而不是输入的数据了。
   printf("The message is %s\n", buf);
   close(fd);
   return 0;
  }
 else
  {
    printf("Device open failure\n");
    return -1;
 }
} 
