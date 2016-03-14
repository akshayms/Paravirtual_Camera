import socket
import os, os.path
import time
 
if os.path.exists( "/tmp/python_unix_sockets_example" ):
  os.remove( "/tmp/python_unix_sockets_example" )
 
print "Opening socket..."
server = socket.socket( socket.AF_UNIX, socket.SOCK_STREAM )
server.bind("/tmp/python_unix_sockets_example")
 
print "Listening..."
while True:
  datagram = server.recv( 1024 )
  if not datagram:
    break
  else:
    print "-" * 20
    print datagram
    if "DONE" == datagram:
      break
print "-" * 20
print "Shutting down..."
server.close()
os.remove( "/tmp/python_unix_sockets_example" )
print "Done"