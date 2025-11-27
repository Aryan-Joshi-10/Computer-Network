#include<iostream>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
using namespace std;

# define PORT 8080

int main(){
    int server_fd, client_fd;

    struct sockaddr_in server_addr; // Socket Address Internet
    int addrlen = sizeof(server_addr);
    char buffer[1024] = {0};
    string message = "Hello from server";

    // 1. Creating Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 2. Bind
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 3. listen
    listen(server_fd, 3);
    cout<<"Server listening on port"<< PORT << "...\n";

    // 4. accept
    client_fd = accept(server_fd, (struct sockaddr*)&server_addr, (socklen_t *)&addrlen);
    cout<<"Client: " << buffer<<endl;

    
    send(client_fd, message.c_str(), message.length(), 0);
    cout<<"Server: Hello sent to client\n";

    close(client_fd);
    close(server_fd);
    return 0;
}