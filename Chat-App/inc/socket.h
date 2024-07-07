#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<ifaddrs.h>
#include<sys/socket.h>
#include<pthread.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<netdb.h>


#define handle_error(msg) \
    do{perror(msg);exit(EXIT_FAILURE);} while(0)

#define MAX_SIZE_CONNECT 10
#define MAX_MSG_CMD 100
#define BUFF_SIZE 1024
#define MAX_LEN_IP 16
#define TERMINATE_MSG "TERMINATE"
#define LISTEN_BACKLOG 50

typedef struct{
    int socket;
    struct sockaddr_in address;
    int addr_len;
    char ip[INET_ADDRSTRLEN];
    int port;
}connection_t;
connection_t connections[MAX_SIZE_CONNECT];
int count_connect=0;
int port_no;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void display_ip();
void display_port();
void *handle_client(void *args);
void *start_server(void *args);
void connect_to_peer(char *ip,int port);
void list_connections();
void send_terminate_message(int socket);
void terminate_connection(int id);
void send_message(int id,char *message);
