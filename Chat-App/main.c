#include<stdio.h>
#include "inc/menu.h"
#include "inc/socket.h"


int main(int argc,char *argv[])
{
    if(argc<2){
        printf("Command: ./chat <portnumber>\n");
    }else{
        port_no=atoi(argv[1]);
    }
    char cmd[MAX_MSG_CMD];

    pthread_t server_thread;
    pthread_create(&server_thread,NULL,start_server,NULL);

    display_menu();

    while(1){
        printf("Enter command: ");
        fgets(cmd,MAX_MSG_CMD,stdin);
        cmd[strcspn(cmd,"\n")]=0;

        if(strncmp(cmd,"help",4)==0){
            system("clear");
            display_options();
        }else if(strncmp(cmd,"myip",4)==0){
            display_ip();
        }else if(strncmp(cmd,"myport",6)==0){
            display_port();
        }else if(strncmp(cmd,"connect",7)==0){
            char ip[INET_ADDRSTRLEN];
            int port;
            sscanf(cmd+8,"%s %d",ip,&port);
            connect_to_peer(ip,port);
        }else if(strncmp(cmd,"list",4)==0){
            list_connections();
        }else if(strncmp(cmd,"terminate",9)==0){
            int id;
            sscanf(cmd+10,"%d",&id);
            terminate_connection(id);
        }else if(strncmp(cmd,"send",4)==0){
            int id;
            char message[BUFF_SIZE];
            sscanf(cmd+5,"%d %[^\n]",&id,message);
            send_message(id,message);
        }else if(strncmp(cmd,"exit",4)==0){
            for(int i=0;i<count_connect;i++)
            {
                close(connections[i].socket);
            }
            printf("Exiting ......\n");
            exit(0);
        }else if(strncmp(cmd, "ask ", 4) == 0){
            char *question = cmd + 4;

            // Ghi câu hỏi vào file tạm
            FILE *fp = fopen("ai_input.txt", "w");
            if(fp){
                fprintf(fp, "%s", question);
                fclose(fp);
            }

            // Gọi Python script xử lý AI
            int ret = system("python3 call_gemini.py < ai_input.txt");
            if(ret != 0){
                printf("Error: Failed to call AI.\n");
            }
        }// Nếu không phải lệnh hợp lệ, hiển thị thông báo lỗi
        else{
            printf("Invalid command.Type 'help' for a list of command\n");
            }
        }
        return 0;
}