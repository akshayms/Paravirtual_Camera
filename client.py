import socket
import os, os.path
 
print "Connecting..."
if os.path.exists( "/var/lib/libvirt/qemu/channel/target/Virtual.org.qemu.guest_agent.0" ):
  client = socket.socket( socket.AF_UNIX, socket.SOCK_STREAM )
  client.connect( "/var/lib/libvirt/qemu/channel/target/Virtual.org.qemu.guest_agent.0" )
  print "Ready."
  print "Ctrl-C to quit."
  print "Sending 'DONE' shuts down the server and quits."
  while True:
    try:
      x = raw_input( "> " )
      if "" != x:
        print "SEND:", x
        client.sendall( x )
        if "DONE" == x:
          print "Shutting down."
          break
    except KeyboardInterrupt, k:
      print "Shutting down."
  client.close()
else:
  print "Couldn't Connect!"
print "Done"
