#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Diego Mendoza");
MODULE_DESCRIPTION("Ejemplo de Modulo de Kernel en Linux");
MODULE_VERSION("0.01");

static int __init example_init(void) {
 printk(KERN_INFO ".:Start Module:.\n");
 return 0;
}

static void __exit example_exit(void) {
 printk(KERN_INFO ".:Module End:.\n");
}

module_init(example_init);
module_exit(example_exit);
