#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x3bb98123, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x98ac23a8, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x57793513, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x9e2b878e, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x92428f4b, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x8d0d07af, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x7ba37b16, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xe16c6503, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xf52691cb, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x56d4ca56, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x8574f4e9, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D790B43624B87DB4A8F3667");
