#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <time.h>
/*=================================================================================================================
//CPU使用信息图
(上面一部分显示的是CPU绘图信息，下面的一部分显示的是占用率等等信息，即用文字的形式来展示)
//内存使用信息图
(上面一部分显示的是CPU绘图信息，下面的一部分显示的是占用率等等信息，即用文字的形式来展示)
//进程列表图List控件
//系统信息图
(拟定两部分，一个是利用cat /proc/versions，另外一个就是about，即关于作者的部分)
//状态信息图
//===================================================================================================================*/
//控件声明
GtkWidget *window;
GtkWidget *main_vbox;
GtkWidget *clist;	//进程时候需要的列表
GtkWidget *clist2;	//模块读取时需要的列表
GtkWidget *cpu_liyonglv;
GtkWidget *mem_liyonglv;
GdkPixmap *cpu_graph;
GdkPixmap *mem_graph;

static gint cpu_graph2[50];
static gint mem_graph2[50];
static gfloat cpu_rate = 1.0;
static float totalmem;
static float freemem;
static char buffer[256];
float zuser=0,ztotal=0;
//===================================================================================================================
void selection_made(){}		//某一列被选中的时候进行的操作

void read_info(char store[],int i,char get[])//表示读取第i个空格之前的一个字符串(此即获得的数据)
{
   int j = 0; 		//j表示的就是这个字符串的下标
   int k = 0;
   int cflags = 0;	//用来记录空格的个数
   char buf[20];	//用来保存需要的信息
   while(cflags < i-1){		//特别注意此处是i-1，否则输出的顺序都是乱的，因为需要在i之前的空格，所以是i-1，这样执行完才是i-1的空格
      if(store[j++] == ' ') 	cflags++;
   }
   while(store[j] != ' '){ //读取下一个空格之前的
   	buf[k++] = store[j];
	j++; 
   }
   buf[k] = '\0';	//字符串封口
   strcpy(get,buf);	//字符串拷贝
}

void add_proc_view(){	//读取当前进程信息，并显示到列表框中
  DIR *dir;
  struct dirent *ptr;
  int i = 0;
  dir = opendir("/proc");
  char path[20];	//记录pid的数字文件夹	
  int fd;		//文件描述，用于打开那些数字文件夹的stat文件
  char store[1000];	//将读取的stat文件内容暂时存放到store中
  char name[20];	//进程名
  char pid_num[20];	//pid号
  char stat[20];	//状态
  char memory[20];	//内存
  char priority[20];	//优先级
  while((ptr = readdir(dir)) != NULL)
  {
    if((ptr->d_name[0] >= '0') && (ptr->d_name[0] <= '9'))
    {
	sprintf(path,"/proc/%s/stat",ptr->d_name);	//将此文件的全部路径写入name中
	//打开这个文件，并且从中读取到有用的信息放在相应的数组中
	fd = open(path,O_RDONLY);
	read(fd,store,sizeof(store));
	//g_print(store);		//调试使用的，便于看到哪里出错了，开始的时候设置store大小出错，根本放不下文件导致“段错误”
	read_info(store,1,pid_num);	//进去的是字符串和号，出来对应信息修改
	read_info(store,2,name);	//读取名称,注意包含括号
	read_info(store,3,stat);	//直接一个字符
	read_info(store,18,priority);	//直接一个数字
	read_info(store,23,memory);	//注意是以B为单位，需要换算
	int mem_num = atoi(memory);	//转换成整数形式B为单位
	float real_mem = (float)mem_num /(1024*1024);  //得到MB为单位的信息
	char  convert_mem[25];
	gcvt(real_mem,5,convert_mem);	//浮点数转换成字符串
	gchar *list[1][5]={{name,pid_num,stat,convert_mem,priority}};
	gtk_clist_append((GtkCList*)clist,list[0]);
	gtk_clist_thaw((GtkCList *)clist);	//更新list列表显示
     }
  }
  closedir(dir);			
}

void read_module_info(char store[],int i,char name[],char mem[],char times[]){	//读取第i行的模块信息
    int j = 0;
    int cflags = 0;	//记录读取的回车键个数以便判断行数
    int k = 0;
    char name2[25];
    char mem2[20];
    char times2[5];
    while(cflags < i-1){
	if(store[j] == '\n')  cflags++;	//回车数加1
	j++;
    }
    while(store[j] != ' '){	//读取进程名
	name2[k++] = store[j];
	j++;
    }
    name2[k] = '\0';
    j++; //跳转到下一个不是空格的地方
    k = 0;
    while(store[j] != ' '){
	mem2[k++] = store[j];
	j++;
    }
    mem2[k] = '\0'; //封口
    j++;
    times2[0] = store[j];	//读取模块的使用次数
    times2[1] = '\0';	//封口
    strcpy(name,name2);
    strcpy(mem,mem2);
    strcpy(times,times2);
}

//注：开始以为是store数组太小而发生了段错误，后来看了看大小，没有65535这么大的字节，所以，应该是其它地方发生了溢出错误！排除此处。
void add_modules_view(){	//添加模块显示的代码
	char store[6000];	//暂存读取的modules文件内容
	int fd = open("/proc/modules",O_RDONLY);
	read(fd,store,sizeof(store));
/*	if(test > 0){
		gchar buf[20];
	   	sprintf(buf,"%d",test);
		g_print(buf);
		return ;
	}
*///调试输出，表示读取文件没有问题，和实际的大小相同
 	unsigned int ent = 0;	//表示总的行数
	unsigned int i = 0;
	while(i != sizeof(store)/sizeof(char)){
	   if(store[i] == '\n')	ent++;	
	   i++;		
	}
	i = 0;
	for(i = 1; i <= ent; i++){
	   char convert_mem[25];
  	   char name[25];		//模块名
	   char mem[20];		//内存量
	   char times[5];		//使用次数
	   int mem_num;
	   float real_mem;
	   read_module_info(store,i,name,mem,times);
	  // g_print(name);	
	   mem_num = atoi(mem);
	   real_mem = (float)mem_num / (1024);
	   gcvt(real_mem,3,convert_mem);
 	   gchar *list2[1][3]={{name,convert_mem,times}};
	   gtk_clist_append((GtkCList*)clist2,list2[0]);	
	   gtk_clist_thaw((GtkCList *)clist2);	//更新list列表显示
	} 
}

void get_sys_version(char sys_store[],char buffer1[]) //得到系统的版本信息
{
    int cflags = 0;	//记录空格的个数
    int j = 0;
    while(cflags < 3){
	if(sys_store[j++] == ' ')  cflags++;
    }
    int getnum = j;
   for(j = 0; j < getnum;j++)
	buffer1[j] = sys_store[j];
   buffer1[j] = '\0';
}

void get_mem_info(char path[],char total[],char free[])
{
   int fd = open(path,O_RDONLY);
   char store[2000];
   int k = 0;
   read(fd,store,sizeof(store));
   int cflags = 0;
   int i = 0;
   while((store[i] < '0') || (store[i] >'9'))
   {
      i++;
   }
   while((store[i] >= '0')&&(store[i] <= '9'))
   {
	total[k] = store[i];
	k++;	i++;
   }
   total[k] = '\0';
   while((store[i]< '0') || (store[i] >'9'))
   {
      i++;
   }
   k = 0;
   while((store[i] >= '0')&&(store[i]<='9')){
	free[k] = store[i];
	k++;	i++;
   }
   free[k] = '\0';
}

void get_cpu_info(char path[],char model_name[],char cache[])
{
   int fd = open(path,O_RDONLY);
   char store[2000];
   int k = 0;
   int i = 0;
   int cflags = 0;
   read(fd,store,sizeof(store));
   //第五行下面就是CPU的名称
   while(cflags < 4){
     if(store[i] == '\n') cflags++;
        i++;
   }
   while(store[i] != ':')
	i++;	//定位到冒号，这样就可以得到这部分名称的信息
   i++;
   while(store[i] != '\n'){
	model_name[k++] = store[i];
	i++;
   }
   cflags++;			//cflags ==5 ,第五行
   model_name[k] = '\0';	//一定记得封口，否则乱码
    k = 0;
   
     //第八行就是cache的信息
   while(cflags < 8){
     if(store[i] == '\n') cflags++;
        i++;
   }
   while(store[i] != ':')
	i++;	//定位到冒号，这样就可以得到这部分名称的信息
   i++;
   while(store[i] != '\n'){
	cache[k++] = store[i];
	i++;
   }
   cflags++;
   cache[k] = '\0';
   k = 0;
}

float get_cpu_liyong()
{
 FILE *fp;
char buffer[1024];
size_t buf;
float liyonglv;
float user=0,nice=0,sys=0,idle=0,iowait=0;//分别为用户模式，低优先级用户模式，内核模式，空闲的处理器时间

fp=fopen("/proc/stat","r");
buf=fread(buffer,1,sizeof(buffer),fp);//表示从fp中读取sizeof(buffer)块数据放入buffer，每次读一块
fclose(fp);
if(buf==0)
return 0;
buffer[buf]=='\0';
sscanf(buffer,"cpu %f %f %f %f %f",&user,&nice,&sys,&idle,&iowait);
if(idle<=0)
idle=0;
liyonglv=100*(user-zuser)/(user+nice+sys+idle-ztotal);
if(liyonglv>100)
liyonglv=100;
ztotal=user+nice+sys+idle;
zuser=user;
cpu_rate=liyonglv;
return liyonglv;
}

void draw_cpu_graph(){
   GdkGC *gc_chart = gdk_gc_new(cpu_liyonglv->window);
   GdkColor color;	//颜色
   color.red = 0xffff;
   color.green = 0xffff;
   color.blue = 0xffff;
   gdk_gc_set_rgb_fg_color(gc_chart,&color);
   
   int fd,i;
   gchar buffer[64];
   gint width,height,current,step;
   cpu_rate = get_cpu_liyong() / 100;
   if(cpu_rate == 0)		
	g_print("test");	//会循环调用的，验证作用^_^
   gdk_draw_rectangle (cpu_graph, gc_chart, TRUE, 0, 0,cpu_liyonglv->allocation.width,cpu_liyonglv->allocation.height);
   width = cpu_liyonglv->allocation.width;
   height = cpu_liyonglv->allocation.height;
   current = (int)(cpu_rate * (double)height);
   cpu_graph2[49] = height - current;  
   for ( i = 0 ; i < 49 ; i ++) 
   {
	cpu_graph2[i] = cpu_graph2[i+1];	//后一时刻的为前面取代
   }
   step = width / 49;
   for (i = 49; i >= 1;i--) 
   {
 	gdk_draw_line (GDK_DRAWABLE (cpu_graph), window->style->black_gc, i * step,cpu_graph2[i],(i - 1) * step,cpu_graph2[i-1]);
   }

   gtk_widget_queue_draw (cpu_liyonglv);	

}

static gboolean cpu_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
  gdk_draw_drawable (widget->window,
				widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		     	cpu_graph,
		     	event->area.x, event->area.y,
		     	event->area.x, event->area.y,
		        event->area.width, event->area.height);
  return FALSE;
}

static gboolean cpu_configure_event (GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
  if (cpu_graph) {
  		g_object_unref (cpu_graph);
  }
  cpu_graph = gdk_pixmap_new (widget->window,
  					widget->allocation.width, widget->allocation.height,-1);
  gdk_draw_rectangle (cpu_graph, widget->style->white_gc, TRUE, 0, 0,
					widget->allocation.width, widget->allocation.height);
  return TRUE;
}

gint timeout( gpointer status)
{
   get_cpu_liyong();
}

static gboolean mem_configure_event (GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
  if (mem_graph) {
  		g_object_unref (mem_graph);
  }
  mem_graph = gdk_pixmap_new (widget->window,widget->allocation.width, widget->allocation.height,-1);
  gdk_draw_rectangle (mem_graph, widget->style->white_gc, TRUE, 0, 0, widget->allocation.width, widget->allocation.height);
  return TRUE;
}

static gboolean mem_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
  gdk_draw_drawable (widget->window,widget->style->fg_gc[GTK_WIDGET_STATE (widget)],mem_graph,event->area.x, event->area.y,
		     	event->area.x, event->area.y,event->area.width, event->area.height);
  return TRUE;
}
void draw_mem_graph ()
{
  GdkGC *gc_chart=gdk_gc_new(mem_liyonglv->window);
  GdkColor color;
  color.red=0xffff;
  color.green=0xffff;
  color.blue=0xffff;
  gdk_gc_set_rgb_fg_color(gc_chart,&color);  
  int i;
  gint width,height,current,step;
  gdk_draw_rectangle (mem_graph, gc_chart, TRUE, 0, 0,mem_liyonglv->allocation.width,mem_liyonglv->allocation.height);
  width = mem_liyonglv->allocation.width;
  height = mem_liyonglv->allocation.height;
  current = ((float)(totalmem-freemem) / (float)totalmem) * height;
  mem_graph2[49] = height - current; 
  for ( i = 0 ; i < 49 ; i ++) {
	  	mem_graph2[i] = mem_graph2[i+1];
  }
  step = width / 50;  
  //draw the graph
  for (i = 49 ; i >= 1 ; i -- ) {
  		gdk_draw_line (mem_graph, window->style->black_gc,i * step,mem_graph2[i],(i - 1) * step,mem_graph2[i-1]);
  }
  gtk_widget_queue_draw (mem_liyonglv);	
}


int main(int argc ,char ** argv)
{
  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Linux System Moniter");//标题
 // gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);//默认窗口尺寸大小，有它的话设置不可变大小就有问题
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);//窗口不可改变
  gtk_widget_set_usize(GTK_WIDGET (window),400,415);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);  //将窗口关闭信息与destroy_window关联
  
  main_vbox = gtk_vbox_new (FALSE, 10); 		//创建一个竖直的布局容器
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 1);   //设定这个容器和周围的间距
  gtk_container_add (GTK_CONTAINER (window), main_vbox);	//将这个布局容器添加到整个视窗的容器中	
  gtk_widget_show (main_vbox);			

  GtkWidget *status_bar = gtk_statusbar_new ();      
  gtk_box_pack_end(GTK_BOX(main_vbox), status_bar, TRUE, TRUE, 0);	//将状态栏也加入到竖直控件中，end表示是在最底部添加的此控件
  gtk_widget_show (status_bar);

  GtkWidget *notebook = gtk_notebook_new ();
  gtk_box_pack_end(GTK_BOX(main_vbox),notebook,TRUE,TRUE,0);	//在顶部添加一个标签页，这样就可以实现多重标签了
  gtk_widget_show_all (window);	//显示所有的窗口和界面
//=========================================================第一个标签===========================================================
  GtkWidget *frame1 = gtk_frame_new ("CPU info");		//创建第一个简单的标签页
  gtk_container_set_border_width (GTK_CONTAINER (frame1), 10);
  gtk_widget_set_size_request (frame1, 100, 335);
  gtk_widget_show (frame1);
  gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame1, gtk_label_new("CPU"));

  GtkWidget *table1 = gtk_table_new(2,1,TRUE);
  GtkWidget *CPU_frame1 = gtk_frame_new("CPU曲线");
  gtk_container_add (GTK_CONTAINER (frame1), table1);
  gtk_table_attach_defaults (GTK_TABLE(table1),CPU_frame1, 0, 1, 0, 1);
  gtk_widget_show (CPU_frame1);

  cpu_liyonglv = gtk_drawing_area_new ();		//添加图形部分
  gtk_widget_set_app_paintable (cpu_liyonglv,TRUE);
 // gtk_drawing_area_size (GTK_DRAWING_AREA (cpu_liyonglv), 40, 40);
  gtk_container_add (GTK_CONTAINER (CPU_frame1), cpu_liyonglv);
  gtk_widget_show (cpu_liyonglv);
  g_signal_connect (cpu_liyonglv, "expose_event",G_CALLBACK (cpu_expose_event), NULL);
  g_signal_connect (cpu_liyonglv, "configure_event",G_CALLBACK (cpu_configure_event), NULL);
  gtk_widget_show (cpu_liyonglv);

  gtk_timeout_add (1000, (GtkFunction)draw_cpu_graph, NULL);

  char model_name[50],cache[20];
  get_cpu_info("/proc/cpuinfo",model_name,cache);
  char cpuBuffer[100];
  strcpy(cpuBuffer,"CPU型号和主频是:  ");
  strcat(cpuBuffer,model_name);
  strcat(cpuBuffer,"\n\n\nCache Size:  ");
  strcat(cpuBuffer,cache);
  
  GtkWidget *CPU_info_frame1 = gtk_frame_new("CPU infor description ");
  gtk_table_attach_defaults (GTK_TABLE(table1),CPU_info_frame1, 0, 1, 1, 2);
  gtk_widget_show (CPU_info_frame1);
  gtk_widget_show(table1);
  
  GtkWidget *label_cpu = gtk_label_new (cpuBuffer);	//显示CPU信息的label
  gtk_container_add (GTK_CONTAINER (CPU_info_frame1), label_cpu);		//将信息加入到上一级frame中,即sys_frame
  gtk_label_set_justify (GTK_LABEL (label_cpu), GTK_JUSTIFY_LEFT);	//设置label形式和显示方式
  gtk_widget_show (label_cpu); 	
//====================================================第二个标签页（内存）=========================================================
  GtkWidget *frame2 = gtk_frame_new("Memory info");	     //创建第二个标签页
  gtk_container_set_border_width(GTK_CONTAINER(frame2),10);
  gtk_widget_set_size_request(frame2,100,355);
  gtk_widget_show(frame2);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame2, gtk_label_new("Memory"));

  char total[20],free[20];
  get_mem_info("/proc/meminfo",total,free);  //将总共内存放在total，将空闲内存free
  float total_mem = (float)atoi(total);
  total_mem = total_mem / 1024;	//将单位化成MB
  gcvt(total_mem, 5, total);		//换算后的存放在total中
  float free_mem = (float)atoi(free);  
  free_mem = free_mem / 1024;
  totalmem = total_mem;
  freemem = free_mem;
  gcvt(free_mem,3,free);	//换算后的存放在free中
  
  char  mem_display[1000];  
  strcpy(mem_display,"总内存:  ");
  strcat(mem_display,total);
  strcat(mem_display," MB\n\n可用内存: ") ;
  strcat(mem_display,free);
  strcat(mem_display," MB");
 
  GtkWidget *table2 = gtk_table_new(2,1,TRUE);
  GtkWidget *mem_frame = gtk_frame_new("内存曲线");
  gtk_container_add (GTK_CONTAINER (frame2), table2);
  gtk_table_attach_defaults (GTK_TABLE(table2),mem_frame, 0, 1, 0, 1);
  gtk_widget_show (mem_frame);

  mem_liyonglv = gtk_drawing_area_new ();
  gtk_widget_set_app_paintable (mem_liyonglv,TRUE);
 // gtk_drawing_area_size (GTK_DRAWING_AREA (mem_liyonglv), 40, 40);
  gtk_container_add (GTK_CONTAINER (mem_frame), mem_liyonglv);
  gtk_widget_show (mem_liyonglv);
  g_signal_connect (mem_liyonglv, "expose_event",G_CALLBACK (mem_expose_event), NULL);
  g_signal_connect (mem_liyonglv, "configure_event",G_CALLBACK (mem_configure_event), NULL);
  gtk_widget_show (mem_liyonglv);

  gtk_timeout_add (1000, (GtkFunction)draw_mem_graph, NULL);

  GtkWidget *mem_info_frame = gtk_frame_new("Memory description");
  gtk_table_attach_defaults (GTK_TABLE(table2),mem_info_frame, 0, 1, 1, 2);
  gtk_widget_show (mem_info_frame);
  gtk_widget_show(table2);	

  GtkWidget *label_mem = gtk_label_new (mem_display);	//显示内存信息的label
  gtk_container_add (GTK_CONTAINER (mem_info_frame), label_mem);		//将信息加入到上一级frame中,即sys_frame
  gtk_label_set_justify (GTK_LABEL (label_mem), GTK_JUSTIFY_LEFT);	//设置label形式和显示方式
  gtk_widget_show (label_mem); 	
//===============================================第三个标签页（进程）==============================================================
  GtkWidget *frame3 = gtk_frame_new("Process info");	     //创建第三个标签页
  gtk_container_set_border_width(GTK_CONTAINER(frame3),10);
  gtk_widget_set_size_request(frame3,100,355);
  gtk_widget_show(frame3);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame3, gtk_label_new("Process"));
  GtkWidget *scrolled_window=gtk_scrolled_window_new(NULL,NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
  	GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
  gtk_container_add (GTK_CONTAINER (frame3), scrolled_window);
   	gtk_widget_show(scrolled_window);
  gchar *cols[5]={"进程名", "PID" , "进程状态",  "占用内存(MB)","优先级"};
  clist=gtk_clist_new_with_titles(5,cols);
  g_signal_connect(GTK_OBJECT(clist),"select_row",GTK_SIGNAL_FUNC(selection_made),NULL); //此处中的函数没有任何作用就设置未NULL，否则选中的就要发生对应的变化
  gtk_clist_set_shadow_type(GTK_CLIST(clist),GTK_SHADOW_OUT);
  gtk_clist_set_column_width(GTK_CLIST(clist),0,64);//设置某个列和对应的宽度,第一个数是列数，第二个是宽度
  gtk_clist_set_column_width(GTK_CLIST(clist),1,30);
  gtk_clist_set_column_width(GTK_CLIST(clist),2,55);
  gtk_clist_set_column_width(GTK_CLIST(clist),3,60);
  gtk_clist_set_column_width(GTK_CLIST(clist),4,80);
  gtk_container_add(GTK_CONTAINER(scrolled_window),clist);
  gtk_widget_show(clist);
  add_proc_view();	//读取当前进程信息，并显示到列表框中
//==================================================第四个标签页(模块)===========================================================
  GtkWidget *frame4 = gtk_frame_new("Modules info");	     //创建第四个标签页
  gtk_container_set_border_width(GTK_CONTAINER(frame4),10);
  gtk_widget_set_size_request(frame4,100,355);
  gtk_widget_show(frame4);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame4, gtk_label_new("Modules"));
  GtkWidget *scrolled_window2 = gtk_scrolled_window_new(NULL,NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window2),
  	GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
  gtk_container_add (GTK_CONTAINER (frame4), scrolled_window2);
   	gtk_widget_show(scrolled_window2);
  gchar *cols2[3]={"模块名", "占用内存" , "加载计数"};	//由于含有特殊情况，所以只读取通用格式的范例
  clist2 = gtk_clist_new_with_titles(3,cols2);
  gtk_clist_set_shadow_type(GTK_CLIST(clist2),GTK_SHADOW_OUT);
  gtk_clist_set_column_width(GTK_CLIST(clist2),0,70);//设置某个列和对应的宽度,第一个数是列数，第二个是宽度
  gtk_clist_set_column_width(GTK_CLIST(clist2),1,70);
  gtk_clist_set_column_width(GTK_CLIST(clist2),2,70);
  gtk_container_add(GTK_CONTAINER(scrolled_window2),clist2);
  
  add_modules_view();	//读取当前进程信息，并显示到列表框中
  gtk_widget_show(clist2);	//如果没有把这个放在add_modules_view后面，那么就会出错，因为此时没有添加完全
//=====================================================第五个标签页=========================================================
  GtkWidget *vbox = gtk_vbox_new (FALSE, 5);
  GtkWidget *frame5 = gtk_frame_new("System info");	     //创建第五个标签页
  gtk_container_set_border_width(GTK_CONTAINER(frame5),10);
  gtk_widget_set_size_request(frame5,100,355);
  gtk_widget_show(frame5);
  GtkWidget *label_system = gtk_label_new("System");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame5, label_system);
		//=============显示系统信息，系统菜单下面=============
  GtkWidget *table=gtk_table_new(2,1,TRUE);
  GtkWidget *sys_frame = gtk_frame_new("System information");
  gtk_container_add (GTK_CONTAINER (frame5), table);
  gtk_table_attach_defaults (GTK_TABLE(table),sys_frame, 0, 1, 0, 1);
  gtk_widget_show (sys_frame);

  int sys_fd = open("/proc/version",O_RDONLY); //打开文件以得到版本信息
  char sys_store[100];
  read(sys_fd,sys_store,sizeof(sys_store));
  close(sys_fd);	//关闭文件
  char buffer1[100];
  char buffer[10];
  get_sys_version(sys_store,buffer1);
  char bufversion[200] = "System Version: ";
  strcat(bufversion,buffer1);
  memset(buffer1,NULL,sizeof(buffer1));
  memset(sys_store,NULL,sizeof(sys_store));
  sys_fd = open("/proc/sys/kernel/hostname",O_RDONLY);
  read(sys_fd,sys_store,sizeof(sys_store));
  close(sys_fd);
  strcpy(buffer1,"\n\nHost Name : ");		//读取用户名
  strcat(buffer1,sys_store);	//将用户名放入buffer1中
  strcat(bufversion,buffer1);   //将该信息放入链接到总的输出信息中
  memset(buffer1,NULL,sizeof(buffer1));
  memset(sys_store,NULL,sizeof(sys_store));
  sys_fd = open("/proc/uptime",O_RDONLY);	//读取系统运行时间
  read(sys_fd,sys_store,sizeof(sys_store));
  close(sys_fd);
  int i = 0; 
  while(sys_store[i] != ' '){
	buffer[i] = sys_store[i];
 	i++;
  }
  float num = atof(buffer);
  num = num / (60 * 60 * 60);	//以小时计数
  memset(buffer,0,sizeof(buffer));
  gcvt(num,3,buffer);
  strcat(buffer,"h");
  strcpy(buffer1,"\nRunning Time: ");
  strcat(buffer1,buffer);
  strcat(bufversion,buffer1);
  GtkWidget *label_vr = gtk_label_new (bufversion);	//显示系统信息的label
  gtk_container_add (GTK_CONTAINER (sys_frame), label_vr);		//将信息加入到上一级frame中,即sys_frame
  gtk_label_set_justify (GTK_LABEL (label_vr), GTK_JUSTIFY_LEFT);	//设置label形式和显示方式
  gtk_widget_show (label_vr); 

		//============显示关于作者的信息，也是在系统菜单下面==============
  GtkWidget *author_frame=gtk_frame_new("About the author");
  gtk_table_attach_defaults (GTK_TABLE(table),author_frame, 0, 1, 1, 2);
  gtk_widget_show (author_frame);
  gtk_widget_show(table);	

  char author_info[] = "Author:  liuchang\n\nEmail:  lllccc2009@foxmail.com\n\nInfo:  资源管理器V1.0\n \t用于检测CPU和内存，模块等信息，并得到部分系统信息!";
  GtkWidget *label_vr2 = gtk_label_new (author_info);	//显示系统信息的label
  gtk_container_add (GTK_CONTAINER (author_frame), label_vr2);		//将信息加入到上一级frame中,即sys_frame
  gtk_label_set_justify (GTK_LABEL (label_vr2), GTK_JUSTIFY_LEFT);	//设置label形式和显示方式
  gtk_widget_show (label_vr2); 

//==================================================================================================================
  gtk_main(); 
  return 0;
}
