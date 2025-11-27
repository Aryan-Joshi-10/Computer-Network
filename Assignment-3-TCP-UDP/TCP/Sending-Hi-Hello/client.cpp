#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    string message = "Hello from client";
    char buffer[1024] = {0};

    // Socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // Change this for wireless use

    // Connect
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Write
    send(sock, message.c_str(), message.length(), 0);
    cout << "Client: Hello sent to server\n";

    // Read
    read(sock, buffer, 1024);
    cout << "Server: " << buffer << std::endl;

    close(sock);
    return 0;
}