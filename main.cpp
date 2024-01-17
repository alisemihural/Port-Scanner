#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    const std::string targetIP = "127.0.0.1";
    const int startPort = 1;
    const int endPort = 65535;

    for (int port = startPort; port <= endPort; ++port) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            std::cerr << "Failed to create socket" << std::endl;
            return 1;
        }

        struct sockaddr_in server = {};
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if (inet_pton(AF_INET, targetIP.c_str(), &server.sin_addr) <= 0) {
            std::cerr << "Invalid target IP address" << std::endl;
            close(sock);
            return 1;
        }

        if (connect(sock, reinterpret_cast<struct sockaddr*>(&server), sizeof(server)) < 0) {
            close(sock);
        } else {
            std::cout << "Port " << port << " is open" << std::endl;
            close(sock);
        }
    }

    return 0;
}
