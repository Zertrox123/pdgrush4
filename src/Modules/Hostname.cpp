#include "Modules/Hostname.hpp"
#include "Displays/IDisplay.hpp"
#include <fstream>
#include <string>

Hostname::Hostname() {
    std::ifstream myfile("/etc/hostname");
    std::string line;
    while (getline(myfile, line)){
        _name += line;
    }
}

void Hostname::Draw(Krell::IDisplay *ui) {
    ui->NewSection("Hostname");
    ui->drawText(_name);
}
