#include "scanner.h"
#include "report.h"
#include <iostream>

int main() {
    showBanner();

    std::string target;
    std::cout << "\nTarget (IP only): ";
    std::cin >> target;

    ReconResult result;
    result.target = target;

    pingHost(target, result);
    detectOS(result);
    scanPortsMT(target, result);
    grabHTTPBanner(target, result);
    runWhois(target, result);

    saveReport(result);

    std::cout << "\n[✔] Recon completed. Report saved.\n";
    return 0;
}
