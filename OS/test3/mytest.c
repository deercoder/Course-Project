#include "/usr/src/linux-2.6.31.12/include/linux/kernel.h"
#include "/usr/src/linux-2.6.31.12/include/linux/module.h"
#include "/usr/src/linux-2.6.31.12/include/linux/fs.h"
#include "/usr/src/linux-2.6.31.12/include/linux/init.h"
#include "/usr/src/linux-2.6.31.12/include/linux/errno.h"
#include "/usr/src/linux-2.6.31.12/include/linux/errno.h"
#include "/usr/src/linux-2.6.31.12/include/linux/types.h"
#include "/usr/src/linux-2.6.31.12/include/linux/errno.h"
#include "/usr/src/linux-2.6.31.12/include/linux/uaccess.h"
#include "/usr/src/linux-2.6.31.12/include/linux/kdev_t.h"

#if CONFIG_MODVERSIONS == 1
#define MODVERSIONS
#include "/usr/src/linux-2.6.31.12/include/linux/version.h"
#endif

#define DEVICE_NUM 0	//当用设备号为0创建时，表示随机产生一个可以用的设备号创建模块


static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f);
static ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f);
static int device_num = 0;	//用来保存模块创建成功的时候真正的设备号
static int counter = 0;		//定义模块使用的次数
static char msg_ptr[1024] = "mytest!";

struct file_operations test_fops=
{
   open:my_open,
   release:my_release,
   read:my_read,
   write:my_write,
};

int init_module()
{
  int ret ;
  ret= register_chrdev(DEVICE_NUM,"mytest",&test_fops);//向系统的字符登记表登记一个字符设备
  if( ret < 0){
	printk("register failure!\n");
 	return -1;
  }
  else{
  	printk("register success!\n");
	device_num = ret;
  	return 0;
    }
}

void cleanup_module()
{
  unregister_chrdev(device_num,"mytest");
  printk("unregister success!\n");
}

static int my_open(struct inode *inode, struct file *file)
{
  printk("main device is %d,and the slave device is %d\n",MAJOR(inode->i_rdev),MINOR(inode->i_rdev));
  if(counter)
       return -EBUSY;
  counter++;
  printk("the device has been called %d times\n",counter++);
  try_module_get(THIS_MODULE);
  return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
  counter--;
  printk("the device is released!\n");
  module_put(THIS_MODULE);
  return 0;
}

static ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f)
{
  if(copy_to_user(user,msg_ptr,sizeof(msg_ptr)))
  {
     return -EFAULT;
  }
  return sizeof(msg_ptr);
}

static ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f)
{
  if(copy_from_user(msg_ptr,user,sizeof(msg_ptr)))
  { 
     return -EFAULT;
  }
  return sizeof(msg_ptr);
}


