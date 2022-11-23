import socket

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_Adrees = socket.gethostbyname("sgfl.xyz")

print(str(IP_Adrees))

clientSocket.connect((IP_Adrees, 2001))

hello = clientSocket.recv(1024)

print(str(hello.decode()))

data = str(input() + "\n")

clientSocket.sendall(data.encode("utf-8"))

message = ""

while(len(message) == 0):
    
    message = clientSocket.recv(1024)
    
print(message.decode())