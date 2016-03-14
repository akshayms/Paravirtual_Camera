#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/init.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/un.h>
//#include <net/sock.h>
//#include <sys/socket.h>
//#include <sys/un.h>

#define SOCK_PATH   "/tmp/usocket"
#define LISTEN      10

char *socket_path = "/tmp/foo";

//struct socket *sock = NULL;
//struct socket *newsock = NULL;

static int __init server_module_init( void ) {
  struct sockaddr_un addr;
  char buf[100] = "Hello World!";
  int fd,rc;

  if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    printk(KERN_INFO "Failed to create the socket\n");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

  if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    printk(KERN_INFO "connect error\n");
    exit(-1);
  }

  oldfs = get_fs();
  set_fs(KERNEL_DS);

    if (write(fd, buf, rc) != rc) {
      if (rc > 0) printk(KERN_INFO "Partial Write\n");
      else {
        printk(KERN_INFO "write error\n");
        exit(-1);
      }
    }

  set_fs(oldfs);

  return 0;
}

static void __exit server_module_exit( void ) {
  printk(KERN_INFO "Exit usocket.");
}

module_init( server_module_init );
module_exit( server_module_exit );
MODULE_LICENSE("GPL");
