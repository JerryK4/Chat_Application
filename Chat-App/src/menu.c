#include "menu.h"

void display_menu()
{
    printf("\n");
    printf("┌──────────────────────────────────────────── Chat Application ────────────────────────────────────────────┐\n");
    printf("│ Use the commands below:                                                                                  │\n");
    printf("│ 1: help                                   → Display available commands                                   │\n");
    printf("│ 2: myip                                   → Show this machine's IP address                               │\n");
    printf("│ 3: myport                                 → Show this application's listening port                       │\n");
    printf("│ 4: connect <destination> <port>           → Connect to another chat client                               │\n");
    printf("│ 5: list                                   → List current connections                                     │\n");
    printf("│ 6: terminate <connection id>              → Terminate a connection                                       │\n");
    printf("│ 7: send <connection id> <message>         → Send message to a connection                                 │\n");
    printf("│ 8: ask <your question to AI>              → Ask AI a question (calls Gemini)                             │\n");
    printf("│ 9: exit                                   → Exit and close all connections                               │\n");
    printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
}

void display_options()
{
    printf("\n");
    printf("┌──────────────────────────────────────────── Chat Application Help ───────────────────────────────────────┐\n");
    printf("│ COMMAND                             │ DESCRIPTION                                                        │\n");
    printf("├─────────────────────────────────────┼────────────────────────────────────────────────────────────────────┤\n");
    printf("│ 1: help                             │ Display this help message                                          │\n");
    printf("│ 2: myip                             │ Display this machine's IP address                                  │\n");
    printf("│ 3: myport                           │ Show the listening port number                                     │\n");
    printf("│ 4: connect <ip> <port>              │ Connect to another machine on the given IP and port                │\n");
    printf("│ 5: list                             │ Show list of all active connections                                │\n");
    printf("│ 6: terminate <id>                   │ Close the connection with the given ID                             │\n");
    printf("│ 7: send <id> <msg>                  │ Send a message to a specific connection                            │\n");
    printf("│ 8: ask <question>                   │ Ask a question to AI (Gemini or GPT)                               │\n");
    printf("│ 9: exit                             │ Gracefully close all connections and exit the app                  │\n");
    printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
}
