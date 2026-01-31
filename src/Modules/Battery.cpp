#include "Modules/Battery.hpp"
#include "Displays/IDisplay.hpp"
#include <sstream>
#include <string>
#include <fstream>

Battery::Battery()
{}

void Battery::Draw(Krell::IDisplay *ui) {
    std::string path;
    std::ifstream bat0("/sys/class/power_supply/BAT0/capacity");
    if (bat0.is_open()) {
        path = "/sys/class/power_supply/BAT0/";
    } else {
        std::ifstream bat1("/sys/class/power_supply/BAT1/capacity");
        if (bat1.is_open())
            path = "/sys/class/power_supply/BAT1/";
    }
    if (path.empty()) {
        _name = "no battery!";
        ui->NewSection("Battery");
        ui->drawText(_name);
        return;
    }
    std::ifstream capacity(path + "capacity");
    std::ifstream status(path + "status");
    std::string capacitynbr;
    std::string statusnbr;
    std::getline(capacity, capacitynbr);
    std::getline(status, statusnbr);
    _name = "charge: " + capacitynbr + "% \nStatus: " + statusnbr;
    ui->NewSection("Battery");
    ui->drawText(_name);
}
