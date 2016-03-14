#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/un.h>
#include <net/sock.h>

#define SOCK_PATH   "/tmp/usocket"
#define LISTEN      10

struct socket *sock = NULL;
struct socket *newsock = NULL;

static int __init server_module_init( void ) {

  int retval;
  char* string = "hello_world";

  struct sockaddr_un addr;
  struct msghdr msg;
  struct iovec iov;
  mm_segment_t oldfs;

  // create
  retval = sock_create(AF_UNIX, SOCK_STREAM, 0, &sock);

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SOCK_PATH);

  // bind
  retval = sock->ops->bind(sock,(struct sockaddr *)&addr, sizeof(addr));

  // listen
  retval = sock->ops->listen(sock, LISTEN);

  //accept
  retval = sock->ops->accept(sock, newsock, 0);

  //sendmsg
  memset(&msg, 0, sizeof(msg));
  memset(&iov, 0, sizeof(iov));

  msg.msg_name = 0;
  msg.msg_namelen = 0;
  msg.msg_iov = &iov;
  msg.msg_iov->iov_base = string;
  msg.msg_iov->iov_len = strlen(string)+1;
  msg.msg_iovlen = 1;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_flags = 0;

  oldfs = get_fs();
  set_fs(KERNEL_DS);

  retval = sock_sendmsg(newsock, &msg, strlen(string)+1);

  set_fs(oldfs);

  return 0;
}

static void __exit server_module_exit( void ) {
  printk(KERN_INFO "Exit usocket.");
}

module_init( server_module_init );
module_exit( server_module_exit );
MODULE_LICENSE("GPL");
