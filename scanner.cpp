#include "scanner.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdlib>
#include <fstream>

std::mutex portMutex;

// ===== Banner =====
void showBanner() {
    std::cout << "\033[1;32m";
    std::cout <<
R"(██╗   ██╗███╗   ███╗ █████╗ ██████╗
██║   ██║████╗ ████║██╔══██╗██╔══██╗
██║   ██║██╔████╔██║███████║██████╔╝
██║   ██║██║╚██╔╝██║██╔══██║██╔══██╗
╚██████╔╝██║ ╚═╝ ██║██║  ██║██║  ██║
 ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝

Created by Umar Niaz ☠
Infogather++ Framework
------------------------------------------------
)";
    std::cout << "\033[0m";
}

// ===== Ping + TTL =====
void pingHost(const std::string& target, ReconResult& result) {
    system(("ping -c 1 " + target + " > ping.txt").c_str());
    std::ifstream f("ping.txt");
    std::string line;
    while (getline(f, line)) {
        if (line.find("ttl=") != std::string::npos) {
            int ttl = std::stoi(line.substr(line.find("ttl=") + 4));
            result.osGuess = (ttl <= 64) ? "Linux/Unix" :
                             (ttl <= 128) ? "Windows" :
                             "Network Device";
        }
    }
    remove("ping.txt");
}

// ===== OS Guess =====
void detectOS(ReconResult& result) {
    if (result.osGuess.empty())
        result.osGuess = "Unknown";
}

// ===== Multithreaded Scan =====
void scanPort(const std::string& target, int port, ReconResult& result) {
    usleep(10000 + rand() % 20000); // stealth timing

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, target.c_str(), &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0) {
        std::lock_guard<std::mutex> lock(portMutex);
        result.openPorts.push_back(port);
    }
    close(sock);
}

void scanPortsMT(const std::string& target, ReconResult& result) {
    int ports[] = {21,22,23,25,53,80,110,139,443,445,8080};
    std::vector<std::thread> threads;

    for (int p : ports)
        threads.emplace_back(scanPort, target, p, std::ref(result));

    for (auto& t : threads)
        t.join();
}

// ===== HTTP Banner =====
void grabHTTPBanner(const std::string& target, ReconResult& result) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, target.c_str(), &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0) {
        send(sock, "HEAD / HTTP/1.0\r\n\r\n", 19, 0);
        char buf[512]{};
        recv(sock, buf, sizeof(buf), 0);
        result.httpBanner = buf;
    }
    close(sock);
}

// ===== Whois =====
void runWhois(const std::string& target, ReconResult& result) {
    system(("whois " + target + " > whois.txt").c_str());
    std::ifstream f("whois.txt");
    result.whois.assign((std::istreambuf_iterator<char>(f)),
                         std::istreambuf_iterator<char>());
    remove("whois.txt");
}
