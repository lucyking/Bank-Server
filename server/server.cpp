#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "../include/error.h"
#include "postMsg.h"

int PORT_NO = 8080;

int char2num(char a[]);

int main()
{
    int clientSequence=1;
    int socket_fd, client_fd ;
    char buffer[256];
    struct sockaddr_in server_addr, client_addr;

    //create a socket listen any client
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( socket_fd < 0)
    {
        fail("create socket fail");
    }

    //configure the server
    bzero((char *)&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; /* Address to accept any incoming messages. */
    server_addr.sin_port = htons(PORT_NO);

    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) < 0)
    {
        fail("bind socket fail");
    }

    //listen the socket
    if(listen(socket_fd, 500))
    {
        fail("listen socket fail");
    }

    printf("the server started...\n");
    printf("listening: addr=%s, port=%d\n", inet_ntoa(server_addr.sin_addr), server_addr.sin_port);
    printf("waiting for client...\n");

    socklen_t length = sizeof(struct sockaddr_in);

        int new_server_socket = accept(socket_fd, (struct sockaddr *) &client_addr, &length);


        if(new_server_socket < 0)
        {
            fail("accept fail");
        }

        printf("accept client %s\n", inet_ntoa(client_addr.sin_addr));

    while(1)
    {
        char buffer_received[1024],buffer_post[1024];
        memset(buffer_received, '\0', 1024);
        memset(buffer_post, '\0', 1024);

        int length_received = recv(new_server_socket, buffer_received, sizeof(buffer_received), 0);
        if(length_received < 0)
        {
            fail("receive fail");
        }
        if(length_received > 0) {
            printf("get bytes length: %d\n", length_received);
            buffer_received[length_received] = '\0';
            printf("Received: %s\n", buffer_received);
            int tmp =char2num(buffer_received);
            printf("Received: %d\n",tmp);

//            int client_listenPort = atoi()

            memset(buffer_post, '\0', 1024);
            sprintf(buffer_post,"Your #ID is %d\n",clientSequence++);
            printf("[server]send msg content is:%s\n",buffer_post);
            sleep(1);
//            postMsg(inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buffer_received);
//            postMsg(inet_ntoa(client_addr.sin_addr),8100,buffer_post);
            if(send(new_server_socket,buffer_post, sizeof(buffer_post),0)<0){
                printf("[ERR]:react to Client failed\n");
                break;
            }
            printf("React to Client Success!\n");
//            break;
        }
    }
    return 0;
}

int char2num(char a[]){
    int sum=0;
    std::cout<< "char2num >>>";
    for(int i=0;a[i]!='\0';i++){
        std::cout << a[i];
        sum=sum*10+(a[i]-'0');
    }
    printf("char2num: %d\n",sum);
    return sum;
}

