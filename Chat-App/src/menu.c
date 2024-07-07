#include "menu.h"

void display_menu()
{
    printf("\n************************************Chat Application****************************************\n");
    printf("\nUse the command below:\n");
    printf("1:help\n");
    printf("2:myip\n");
    printf("3:myport\n");
    printf("4:connect <destination> <port no>\n");
    printf("5:list\n");
    printf("6:terminate <connection id>\n");
    printf("7: send <connection id.> <message>\n");
    printf("8:exit\n");
    printf("\n************************************Thank you***********************************************\n");
}

void display_options()
{
    printf("\n************************************Chat Application********************************************************************\n");
    printf("\nUse the command below:\n");
    printf("1:help\t\t\t\t\t\t:display user interface options\n");
    printf("2:myip\t\t\t\t\t\t:display the IP address of this process\n");
    printf("3:myport\t\t\t\t\t:display the port on which this process is listening for incoming connections\n");
    printf("4:connect <destination> <port no>\t\t:connect to the app of another computer\n");
    printf("5:list\t\t\t\t\t\t:Display a numbered list of all the connections\n");
    printf("6:terminate <connection id>\t\t\t:terminate the connections\n");
    printf("7: send <connection id.> <message>\t\t:send a message to a connection\n");
    printf("8:exit\t\t\t\t\t\t:Close all connections and terminate this process\n");
    printf("\n************************************Thank you***************************************************************************\n");
}