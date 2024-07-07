#include "socket.h"

void get_ip(char *address)
{
    struct ifaddrs *ifaddr,*ifa;
    int family,s;
    char host[NI_MAXHOST];

    if(getifaddrs(&ifaddr)==-1)
        handle_error("getifaddrs()");

    for(ifa=ifaddr;ifa!=NULL;ifa=ifa->ifa_next)
    {
        if(ifa->ifa_addr==NULL)
            continue;
        
        family=ifa->ifa_addr->sa_family;

        /*Chỉ lấy điạ chỉ IPV4*/
        if(family==AF_INET){
            s=getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host,NI_MAXHOST,NULL,0,NI_NUMERICHOST);
        
            if (s != 0) 
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }

            if(strcmp(host,"127.0.0.0")!=0){
                strcpy(address,host);
            }
        }
    }

    freeifaddrs(ifaddr);
}

void display_ip()
{
    char address[MAX_LEN_IP];
    get_ip(address);
    printf("My IP: %s\n",address);
}

void display_port()
{
    printf("My Port:%d\n",port_no);
}

void *handle_client(void *args)
{
    connection_t *conn=(connection_t *)args;
    char buff[BUFF_SIZE];
    int numb_read;

    while((numb_read=read(conn->socket,buff,BUFF_SIZE))>0){
        buff[BUFF_SIZE-1]='\0';

        /*Check terminate message*/
        if(strncmp(buff,TERMINATE_MSG,sizeof(TERMINATE_MSG))==0){
            printf("Connection termianted by peer IP:%s  Port:%d\n",conn->ip,conn->port);
        }

        printf("\n***********************************************************\n");
        printf("Message received from IP: %s  Port: %d\n",conn->ip,conn->port);
        printf("Message:%s\n",buff);
        printf("***********************************************************\n");
    }
    close(conn->socket);
    pthread_mutex_lock(&lock);
    for(int i=0;i<count_connect;i++)
    {
        if(connections[i].socket==conn->socket){
            for(int j=i;j<count_connect-1;j++)
            {
                connections[j]=connections[j+1];
            }
            count_connect--;
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    free(conn);
    return NULL;
}
void *start_server(void *args)
{
    connection_t *conn=(connection_t *)args;
    int server_sd,client_sd;
    struct sockaddr_in server_addr,client_addr;
    int len,opt;
    int client_port;
    char client_ip[INET_ADDRSTRLEN];

    memset(&server_addr,0,sizeof(struct sockaddr_in));
    memset(&client_addr,0,sizeof(struct sockaddr_in));

    /*Create socket*/
    server_sd=socket(AF_INET,SOCK_STREAM,0);
    if(server_sd==-1)
        handle_error("socket()");
    
    /*Prevent errors*/
    if(setsockopt(server_sd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))==-1)
        handle_error("setsockopt()");

    /*Initialize server address*/
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port_no);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    /*Attach the socket to the address server*/
    if(bind(server_sd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in))==-1)
        handle_error("bind()");

    /*Listen for clients in the queue*/
    if(listen(server_sd,LISTEN_BACKLOG)==-1)
        handle_error("listen()");
    
    len=sizeof(client_addr);

    while(1){
        client_sd=accept(server_sd,(struct sockaddr*)&client_addr,(socklen_t *)&len);
        if(client_sd==-1)
            handle_error("accept()");

        inet_ntop(AF_INET,&client_addr.sin_family,client_ip,INET_ADDRSTRLEN);//convert IPv4 and IPv6 addresses from binary to text form
        client_port=ntohs(client_addr.sin_port);//convert giá trị sin_port từ địa chỉ mạng(network byte order)sang địa chỉ host(host byte order)

        printf("\nAccepted a new connection from address : %s, set up at port : %d\n",client_ip,client_port);

        connection_t *conn=(connection_t *)malloc(sizeof(connection_t));
        conn->socket=client_sd;
        conn->address=client_addr;
        conn->addr_len=len;
        strncpy(conn->ip,client_ip,INET_ADDRSTRLEN);
        conn->port=client_port;


        pthread_mutex_lock(&lock);
        connections[count_connect++]=*conn;
        pthread_mutex_unlock(&lock);

        pthread_t client_thread;
        pthread_create(&client_thread,NULL,handle_client,(void *)conn);
    }
    close(server_sd);
    return NULL;

}
void connect_to_peer(char *ip,int port)//Vai tro client 
{
    struct sockaddr_in client_addr;
    int client_sd,len;
    memset(&client_addr,'0',sizeof(struct sockaddr_in));
    
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(port);

    if(inet_pton(AF_INET,ip,&client_addr.sin_addr)==-1)//convert IPv4 and IPv6 addresses from text to binary form int inet_pton(int af, const char *restrict src, void *restrict dst);
        handle_error("inet_ptop()");

    client_sd=socket(AF_INET,SOCK_STREAM,0);
    if(client_sd<0)
        handle_error("socket()");

    len=sizeof(client_addr);
    if(connect(client_sd,(struct sockaddr*)&client_addr,len)==-1)
        handle_error("connect()");

    connection_t *conn=(connection_t *)malloc(sizeof(connection_t));
    conn->socket=client_sd;
    conn->address=client_addr;
    conn->addr_len=len;
    conn->port=port;
    strncpy(conn->ip,ip,INET_ADDRSTRLEN);

    pthread_mutex_lock(&lock);
    connections[count_connect++]=*conn;
    pthread_mutex_unlock(&lock);

    pthread_t client_thread;
    pthread_create(&client_thread,NULL,handle_client,(void *)conn);

    printf("\nConnected to IP:%s  Port:%d\n",ip,port);
}
void list_connections()
{
    pthread_mutex_lock(&lock);
    for(int i=0;i<count_connect;i++)
    {
        printf("ID : %d     IP : %s      Port:%d\n",i+1,connections[i].ip,connections[i].port);
    }
    pthread_mutex_unlock(&lock);
}
void send_terminate_message(int socket)
{
    if(write(socket,TERMINATE_MSG,strlen(TERMINATE_MSG))<0)
        handle_error("write()");
}
void terminate_connection(int id)
{
    if(id<1||id>count_connect)
    {
        printf("Invalid connection ID\n");
        return;
    }
    pthread_mutex_lock(&lock);
    send_terminate_message(connections[id-1].socket);
    printf("Terminated at IP : %s   Port : %d\n",connections[id-1].ip,connections[id-1].port);
    close(connections[id-1].socket);
    for(int i=id-1;i<count_connect;i++)
    {
        connections[i]=connections[i+1];
    }
    count_connect--;
    pthread_mutex_unlock(&lock);
    return;
}
void send_message(int id,char *message)
{
     if(id<1||id>count_connect)
    {
        printf("Invalid connection ID\n");
        return;
    }
    int socket=connections[id-1].socket;
    if(write(socket,message,BUFF_SIZE)<0){
        handle_error("write()");
    }else{
        printf("Message to ID : %d sucessfully\n",id);
    }
    return;
}
