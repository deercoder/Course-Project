#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xec5ba0f9, "module_layout" },
	{ 0xdc605d46, "register_chrdev" },
	{ 0x9ef749e2, "unregister_chrdev" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0xd6c963c, "copy_from_user" },
	{ 0x7ecb001b, "__per_cpu_offset" },
	{ 0x26fd80b9, "per_cpu__cpu_number" },
	{ 0xa11de823, "module_put" },
	{ 0xb72397d5, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "08F9BD9EBA3A3BA7C01D6AB");
