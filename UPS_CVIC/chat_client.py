import socket
from threading import Thread

def listen_for_messages():
    while True:
        message = s.recv(1024).decode()
        nickname = message.split(";")[0]
        message = message.split(";")[1]
        print(nickname + ">" + message)

SERVER_HOST = "127.0.0.1"
SERVER_PORT = 10000

#---------------------------------------------
s = socket.socket()
print(f"[*] Connection to {SERVER_HOST} : {SERVER_PORT}....")

#----------------------------------------------------
s.connect((SERVER_HOST, SERVER_PORT))
print("[+] Connected.")

#-------------------------------------
data = s.recv(1024)

print(str(data.decode("utf-8")))

nickname = input("Get your nickname:")

t = Thread(target=listen_for_messages)

t.daemon = True

t. start()

print("For exit chat write 'exit'")

while True:
    
    messege = str(nickname + ";" + input())
    
    if "exit" in messege:
        break
    
    s.send(messege.encode())
    
s.close()


