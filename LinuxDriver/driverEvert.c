#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/types.h>    // for dev_t typedef
#include <linux/kdev_t.h>   // for format_dev_t
#include <linux/fs.h>       // for alloc_chrdev_region()
#include <linux/cdev.h>     // for "struct cdev"
#include <asm/uaccess.h>    // for user/kernel space copy routine

// Compile using make Makefile
//
// sudo insmod driverEvert.ko
// cat /proc/devices | grep devEvert  # Note Major device number and use in next command
// sudo mknod /dev/evert c <Major Dev> 0
// cat /dev/evert
// cat /proc/evert
// sudo rmmod driverEvert

static dev_t mydev;
static char buffer[64];

static char output[] = "Wat een weer weer.\n";

ssize_t my_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk(KERN_INFO "In chardrv read routine.\n");
    printk(KERN_INFO "Count field is %lu.\n", count);
    printk(KERN_INFO "Offset is %lu.\n", *f_pos);

    if (output[*f_pos] == '\0') {
        printk(KERN_INFO "End of string, returning zero.\n");
        return 0;
    }

    copy_to_user(buf, &output[*f_pos], 1);
    *f_pos += 1;
    return 1;  // returned a single character
}

struct cdev my_cdev;

struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .read = my_read,
};

////////////////////////////////////////////////////////////////////////////////////
static int hz_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Hertz=%d (Greatings Evert)\n", HZ);
    return 0;
}

static int hz_open(struct inode *inode, struct file *file)
{
    return single_open(file, hz_show, NULL);
}

static const struct file_operations hz_fops = {
    .owner      = THIS_MODULE,
    .open       = hz_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

////////////////////////////////////////////////////////////////////////////////////
static int __init hz_init(void)
{
    printk(KERN_INFO "Loading Evert module, HZ = %d.\n", HZ);
    proc_create("evert", 0, NULL, &hz_fops);

    // Character device initalization
    alloc_chrdev_region(&mydev, 0, 1, "devEvert");
    printk(KERN_INFO "%s\n", format_dev_t(buffer, mydev));

    cdev_init(&my_cdev, &my_fops);
    my_cdev.owner = THIS_MODULE;
    cdev_add(&my_cdev, mydev, 1);
    return 0;
}

static void __exit hz_exit(void)
{
    remove_proc_entry("evert", NULL);
    printk(KERN_INFO "Unloading Evert module.\n");

    // Uninstall device
    cdev_del(&my_cdev);
    unregister_chrdev_region(mydev, 1);
}

////////////////////////////////////////////////////////////////////////////////////
module_init(hz_init);
module_exit(hz_exit);

MODULE_AUTHOR("Evert Rozendaal");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Testing kernal programming");

