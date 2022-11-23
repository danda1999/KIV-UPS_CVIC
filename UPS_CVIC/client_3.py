import socket

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_Adrees = socket.gethostbyname("sgfl.xyz")

print(str(IP_Adrees))

clientSocket.connect((IP_Adrees, 2002))

hello = clientSocket.recv(1024)

print(str(hello.decode()))

messege = clientSocket.recv(1024)

data = str(messege.decode())

reverse = ""
count = len(data) # Find length of a string and save in count variable  
while count > 0:   
    reverse += data[ count - 1 ] # save the value of str[count-1] in reverseString  
    count = count - 1 # decrement index  
clientSocket.sendall(reverse.encode("utf-8"))

messege = clientSocket.recv(1024)

print(str(messege.decode()))