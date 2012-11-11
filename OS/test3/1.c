#include "/usr/src/linux-2.6.31.12/include/linux/kernel.h"
#include "/usr/src/linux-2.6.31.12/include/config/modules.h"
#include "/usr/src/linux-2.6.31.12/include/linux/init.h" // init&exit相关宏
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
        printk(KERN_ALERT "Hello, world\n");
        return 0;
}
static void hello_exit(void)
{

        printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

