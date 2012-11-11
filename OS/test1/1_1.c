#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#define BUFFER_SIZE 1024

int main(int argc,char *argv[])
{
  int read_fd,write_fd;
  char buffer[BUFFER_SIZE];
  int read_byte,write_byte;
  char *ptr;
  if(argc != 3){
      printf("error:输入参数个数不对!\n");
      exit(0);	
   }
  else{
     read_fd = open(argv[1],O_RDONLY); //打开文件，返回文件描述符
     if(read_fd == -1){	  //打开文件出错
	  printf("error:打开文件出错!\n");
	  exit(0);
     }
     else{ //创建目的文件
	write_fd = open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	if(write_fd == -1){
	    printf("error:创建目的文件失败!\n"); //文件重名，路径不对等原因创建失败
 	    exit(0);	
	}
	else{    //打开和创建成功，进行拷贝操作
	  while((read_byte = read(read_fd,buffer,BUFFER_SIZE)) != 0){ //没有读到文件末尾，如果返回值为0则表示读到文件末尾
	     if((read_byte==-1)&&(errno==EINTR)){ //read函数发生错误
		printf("error:读文件发生错误!\n"); 
		exit(0);
	     }
	     else if(read_byte > 0){ //读入的数据成功了
		ptr = buffer;
		while((write_byte = write(write_fd,ptr,read_byte)) != 0){ //没有写入完毕
		   if(write_byte == -1 ){
			printf("error:写文件发生错误!\n");
			break;
		   }
		   else if(write_byte == read_byte)  //写完了所有的数据
			break;
 		   else if(write_byte < read_byte){//只写入了部分数据，不是将读取的数据全部写入
				ptr += write_byte;
				read_byte -= write_byte;
			}
		   }		
		} 
	     }
	  }	
	}
     }
  return 0;
}
