#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
typedef struct sockaddr_in sockaddr_in;

DWORD WINAPI ReceiveThread(LPVOID param){
    SOCKET socket = *(SOCKET*)param;
    int bytes_received;
    char buffer[1024];
    while((bytes_received = recv(socket, buffer, sizeof(buffer) - 1, 0)) > 0){
        buffer[bytes_received] = '\0';
        printf("\nClient says: %s\n", buffer);
        fflush(stdout);
        if(strcasecmp(buffer, "quit") == 0){
            printf("Exiting the socket...");
            return 0;
        }
        printf("Enter your message: ");
    }
    return 0;
}
DWORD WINAPI SendThread(LPVOID param){
    SOCKET socket = *(SOCKET*)param;
    char buffer[1024];
    while(1){
        printf("\nEnter your message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if(send(socket, buffer, strlen(buffer), 0) == SOCKET_ERROR){
            printf("Send function failure. Errorcode: %d\n", WSAGetLastError());
            return 1;
        }
        if (strcasecmp(buffer, "quit") == 0){
            send(socket, buffer, strlen(buffer), 0);
            printf("Exiting the connection...\n");
            return 0;
        }
        fflush(stdout);
    }
    return 0;
}
int play(){
    HANDLE Thread1, Thread2;
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    sockaddr_in server, client;
    

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf("WSAStartup failure. Errorcode: %d\n", WSAGetLastError());
        return 1;
    }
    printf("WSAStartup has been done successfully\n");

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf("socket function failure. Errorcode: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Socket Creation has been done successfully\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");   //don't use INADDR_ANY
    server.sin_port = htons(12345);

    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        printf("Connection Failure. Errorcode: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Connection has been established successfully\n");
    Thread1 = CreateThread(NULL, 0, ReceiveThread, &client_socket,0, NULL);
    if(Thread1 == NULL){
        printf("Receive Thread Error. Errorcode: %d\n", GetLastError());
        return 1;
    }
    Thread2 = CreateThread(NULL, 0, SendThread, &client_socket,0, NULL);
    if(Thread2 == NULL){
        printf("Send Thread Error. Errorcode: %d\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(Thread1, INFINITE);
    WaitForSingleObject(Thread2, INFINITE);
    CloseHandle(Thread1);
    CloseHandle(Thread2);
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
}

int main(){
    int code = play();
    if(code == 1){
        return 1;
    }
    printf("Exiting the program\n");
    return 0;
}
