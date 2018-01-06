import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 8000))

print "TCP client (Type q or Q to Quit)"
msg = client_socket.recv(256)
print msg
msg=0
data=0
while 1:
    
    data = raw_input ( ">" )
    if (data <> 'Q' and data <> 'q'):
        client_socket.send(data)
        msg = client_socket.recv(256)
        print msg
        data=0
        msg=0
    else:
        client_socket.send(data)
        client_socket.close()
        break;
