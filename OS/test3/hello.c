#include "/usr/src/linux-2.6.31.12/include/linux/kernel.h"
#include "/usr/src/linux-2.6.31.12/include/config/modules.h"

#if CONFIG_MODVERSIONS == 1
#define MODVERSIONS
#include "/usr/src/linux-2.6.31.12/include/linux/version.h"
#endif

int init_module()
{
  printk("Hello,world!\n");
  printk("I am running in a kernel mod!\n");
  return 0;
}

void cleanup_module()
{
  printk("I will shut down myself in kernel mod!\n");
}
