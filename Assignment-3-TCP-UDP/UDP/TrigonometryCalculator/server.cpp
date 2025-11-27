#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cmath>
#include <sstream>

using namespace std;

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    cout << "Trigonometry Server running on port " << PORT << "...\n";

    socklen_t len = sizeof(cliaddr);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';

    string input(buffer);
    string func;
    double value, result = 0.0;

    stringstream ss(input);
    ss >> func >> value;

    // Convert degrees to radians
    double radians = value * M_PI / 180.0;

    if (func == "sin") result = sin(radians);
    else if (func == "cos") result = cos(radians);
    else if (func == "tan") result = tan(radians);
    else {
        string err = "Invalid function";
        sendto(sockfd, err.c_str(), err.size(), 0, (struct sockaddr *)&cliaddr, len);
        close(sockfd);
        return 0;
    }

    string reply = func + "(" + to_string(value) + ") = " + to_string(result);
    sendto(sockfd, reply.c_str(), reply.size(), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
