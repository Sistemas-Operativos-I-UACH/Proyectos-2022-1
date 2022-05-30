#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Diego Mendoza");
MODULE_DESCRIPTION("Linux Kernel Module 'The Super Duper'");
MODULE_VERSION("0.01");

#define DEVICE_NAME "duper_d"

static int major;

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations fops = {
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

static int __init super_duper_Start(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        printk(KERN_ALERT "Super Duper load failed\n");
        return major;
    }

    printk(KERN_INFO "Inicializando Módulo Super Duper!!!\n");
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

    return 0;
}

static int dev_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Super Duper device --> Abierto\n");
   return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer,
                         size_t len, loff_t *offset) {

   printk(KERN_INFO "Sorry, Super Duper --> Es de Solo Lectura\n");
   return -EFAULT;
}

static int dev_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "Super Duper Device --> Finalizado\n");
   return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    char *message = "...Don't stop me, don't stop me...Don't stop me, hey, hey, hey...";
    int message_len = strlen(message);

    errors = copy_to_user(buffer, message, message_len);

    return errors == 0 ? message_len : -EFAULT;
    return 0;
}

static void __exit super_duper_Finish(void) {
    printk(KERN_INFO "Retirando Módulo Super Duper!\n");
}

module_init(super_duper_Start);
module_exit(super_duper_Finish);
