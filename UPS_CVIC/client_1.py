import socket

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_Adrees = socket.gethostbyname("sgfl.xyz")

print(str(IP_Adrees))

clientSocket.connect((IP_Adrees, 2000))

hello = clientSocket.recv(1024)

print(str(hello.decode()))

messege = clientSocket.recv(1024)

print(str(messege.decode()))

data = str(input() + "\n")
    
clientSocket.send(data.encode("utf-8"))
    
data = clientSocket.recv(1024)

print(str(data.decode()))