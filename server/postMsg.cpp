//
// Created by xiadaqiang on 2017/5/10.
//
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>

#include "../include/error.h"

int postMsg(char *hostName, int hostPort, char *msg) {

    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(0);

    int time = 10;
    //create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        fail("create client socket fail");
    }

    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;

    struct hostent *server;
    server = gethostbyname(hostName);
    if (server == NULL) {
        fail("fail to get host name");
    }
    bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);

    //    server_addr.sin_port = htons( atoi("8080"));
    server_addr.sin_port = htons(hostPort);
    socklen_t server_addr_len = sizeof(server_addr);


    printf("connecting to %s, port=%d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    if (connect(client_socket, (struct sockaddr *) &server_addr, server_addr_len) == -1) {
        fail("connent to server fail");
    }

    char *content = "";
    content = (char *) malloc(sizeof(char) * 20);
//    sprintf(content, ">>> %d\n", time);
    sprintf(content, ">>> %s\n", msg);
    //    char* content = get_cpu_info_v2();
    send(client_socket, content, strlen(content), 0);

    printf("send completed, size = %d\n", strlen(content));
    free(content);
    close(client_socket);
    sleep(0.5);

    return 0;
}