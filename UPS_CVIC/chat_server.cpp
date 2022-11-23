#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUF_LENGHT 4096

int main(int argc, char **argv) {

    int server_socket;
	int client_socket, fd, person;
	int return_value;
	socklen_t len_addr;
    std::vector<int>clients; 
	int a2read;
	struct sockaddr_in my_addr, peer_addr;
	fd_set client_socks, tests;
    std::string buffer;
    char charBuffer[MAX_BUF_LENGHT];
    char *command;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&my_addr, 0, sizeof(struct sockaddr_in));

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(10000);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    return_value = bind(server_socket, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in));

    if(return_value == 0) {
        std::cout << "Bind - OK" << std::endl;
    } else {
        std::cerr << "Bind - ERR" << std::endl;
        return -1;
    }

    return_value = listen(server_socket, 5);
     if(return_value == 0) {
        std::cout << "Listen - OK" << std::endl;
    } else {
        std::cerr << "Listen - ERR" << std::endl;
    }

    FD_ZERO(&client_socks);
    FD_SET(server_socket, &client_socks);

    while(1) {

        tests = client_socks;

        return_value = select(FD_SETSIZE, &tests, (fd_set *)0, (fd_set *)0, (struct timeval *)0);

        if(return_value < 0) {
            std::cerr << "Select - ERR" << std::endl;
            return -1;
        }

        for(fd = 3; fd < FD_SETSIZE; fd++) {

            if(FD_ISSET(fd, &tests)) {
                
                if(fd == server_socket) {
                    client_socket = accept(server_socket, (struct sockaddr *) &peer_addr, &len_addr);
                    FD_SET(client_socket, &client_socks);
                    clients.push_back(client_socket);
                    std::cout << "Connect new client and add to container to socket" << std::endl;
                    buffer = "Chat Server 2022";
                    send(client_socket, buffer.c_str(), buffer.length() * sizeof(char), 0);
                }
                else {

                    ioctl(fd, FIONREAD, &a2read);

                    if(a2read > 0) {
                        buffer.clear();
                        memset(&charBuffer, 0, MAX_BUF_LENGHT * sizeof(char));
                        recv(fd, &charBuffer, MAX_BUF_LENGHT*sizeof(char), 0);
                        buffer.assign(charBuffer);
                        for (size_t c = 0; c < clients.size(); c++)
                        {
                            int client = clients.at(c);
                            if(fd != client) {
                                send(client, buffer.c_str(), buffer.length() * sizeof(char), 0);
                            }
                        }
                    }
                    else {
                        close(fd);
                        FD_CLR(fd, &client_socks);
                        std::cout << "Client disconnect and remove from container of sockets" << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}