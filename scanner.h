#pragma once
#include <string>
#include <vector>

struct ReconResult {
    std::string target;
    std::string osGuess;
    std::string httpBanner;
    std::string whois;
    std::vector<int> openPorts;
};

void showBanner();
void pingHost(const std::string&, ReconResult&);
void detectOS(ReconResult&);
void scanPortsMT(const std::string&, ReconResult&);
void grabHTTPBanner(const std::string&, ReconResult&);
void runWhois(const std::string&, ReconResult&);
