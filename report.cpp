#include "report.h"
#include <fstream>
#include <ctime>

void saveReport(const ReconResult& r) {
    std::ofstream f("recon_report.json");

    f << "{\n";
    f << "  \"target\": \"" << r.target << "\",\n";
    f << "  \"os_guess\": \"" << r.osGuess << "\",\n";
    f << "  \"open_ports\": [";

    for (size_t i = 0; i < r.openPorts.size(); i++) {
        f << r.openPorts[i];
        if (i + 1 < r.openPorts.size()) f << ", ";
    }

    f << "],\n";
    f << "  \"http_banner\": \"" << r.httpBanner << "\"\n";
    f << "}\n";
}
