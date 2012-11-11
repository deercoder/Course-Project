#include <stdio.h>
#include </usr/src/linux-2.6.31.12/arch/x86/include/asm/unistd_32.h>

void main()
{
  syscall(337,"./test.c","./destionation.c");
}
