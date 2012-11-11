用于编辑更新源列表   sudo gedit /etc/apt/sources.list

如何设置VBOX的共享文件夹：
sudo makdir /mnt/shared
sudo mount -t vboxsf share /mnt/shared
其中，share是原来的那个文件夹的名字，而后来的在Linux下面的文件夹是/mnt/shared下面的。
当然，你可以在其他地方设置，名字也可以不一样，不过记住，数据区间要加入share才是共享的。


ssize_t  read(int fd, void *buffer,size_t count); 
ssize_t write(int fd, const void *buffer,size_t count); 

fd是我们要进行读写操作的文件描述符,buffer是我们要写入文件内容或读出文件内容的内存地址.count是我们要读写的字节数. 

对于普通的文件read从指定的文件(fd)中读取count字节到buffer缓冲区中(记住我们必须提供一个足够大的缓冲区),同时返回count. 

如果read读到了文件的结尾或者被一个信号所中断,返回值会小于count.如果是由信号中断引起返回,而且没有返回数据,read会返回-1,且设置errno为EINTR.

当程序读到了文件结尾的时候,read会返回0. 
write从buffer中写count字节到文件fd中,成功时返回实际所写的字节数. 

==============================================================================
读函数read  
ssize_t read(int fd,void *buf,size_t nbyte) 
read函数是负责从fd中读取内容.成功时,read返回实际所读的字节数,如果返回的值是0,表示已经读到文件的结束了.
小于0表示出现了错误.如果错误为EINTR说明读是由中断引起的, 如果是ECONNREST表示网络连接出了问题.

写函数write  
ssize_t write(int fd,const void *buf,size_t nbytes) 
 返回值：写入文件的字节数（成功）；-1（出错）
write函数将buf中的nbytes字节内容写入文件描述符fd.成功时返回写的字节数.失败时返回-1. 并设置errno变量. 在网络程序中,当我们向套接字文件描述符写时有俩种可能.  
1)write的返回值大于0,表示写了部分或者是全部的数据.  
2)返回的值小于0,此时出现了错误.我们要根据错误类型来处理.  如果错误为EINTR表示在写的时候出现了中断错误.  
如果为EPIPE表示网络连接出现了问题(对方已经关闭了连接).

