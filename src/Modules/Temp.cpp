#include "Modules/Temp.hpp"
#include "Displays/IDisplay.hpp"
#include <fstream>
#include <string>

Temp::Temp() {
}

void Temp::Draw(Krell::IDisplay *ui) {
    std::ifstream myfile("/sys/class/thermal/thermal_zone0/temp");
    std::string line;
    getline(myfile, line);
    
    if (!line.empty()) {
        int temp = std::stoi(line) / 1000;
        _name = std::to_string(temp) + "°C";
    }
    
    ui->NewSection("Temperature");
    ui->drawText(_name);
}
