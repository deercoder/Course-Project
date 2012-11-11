#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
void hello( GtkWidget *widget, gpointer   data )
{
   g_print ("Hello World\n");
}

gint delete_event( GtkWidget *widget,GdkEvent  *event,
                    gpointer   data )
{	
   g_print ("delete event occurred\n");//打印信息
   //如果返回FALSE，GTK将发出"destroy"信号; 如果返回TRUE，则不让该窗口关闭
   return(TRUE);
}
void destroy( GtkWidget *widget, gpointer   data )
{
	gtk_main_quit();
}

void forkme( int   argc, char *argv[], char *pst)
{
   GtkWidget *window;
   GtkWidget *button;
   gtk_init(&argc, &argv);
   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);//建立新窗口
		//当使用窗口管理器关闭窗口时，将调用 delete_event() 函数
  gtk_signal_connect (GTK_OBJECT (window), "delete_event",GTK_SIGNAL_FUNC (delete_event), NULL);   
		//把 "destroy" 事件和信号处理器联系起来
  gtk_signal_connect (GTK_OBJECT (window), "destroy",GTK_SIGNAL_FUNC (destroy), NULL);    
		//设置窗口的边界宽度
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);    
  button = gtk_button_new_with_label (pst);	//建立指定内容的按钮    
  //当按钮被单击时，即接收到"clicked"信号，将调用 hello()函数
  gtk_signal_connect (GTK_OBJECT (button), "clicked",GTK_SIGNAL_FUNC (hello), NULL);
 //当按钮被单击时，调用 gtk_widget_destroy(window)关闭窗口。
  gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
	GTK_SIGNAL_FUNC (gtk_widget_destroy),GTK_OBJECT (window));    		
  gtk_container_add (GTK_CONTAINER (window), button);//把按钮加入顶级窗口中		
  gtk_widget_show (button);//显示按钮
  gtk_widget_show (window);	//显示顶级窗口
  gtk_main ();//进入事件循环
}

int main( int   argc, char *argv[])
{
 int p1,p2;
 while ((p1=fork())== -1);	//创建子进程直到创建成功
 if (p1 == 0)		//创建的第一个子进程中
 {
    forkme(argc,argv,"process2");
 }
 else		//否则的话就在父进程中
 {
  while ((p2 = fork())== -1);		//创建第二个子进程直到成功
  if (p2 == 0)			//创建的第二个子进程
        forkme(argc,argv,"process3");
  else
        forkme(argc,argv,"process1");	//父进程中
 }
  return 0;
}

