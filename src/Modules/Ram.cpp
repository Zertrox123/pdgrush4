#include "Modules/Ram.hpp"
#include "Displays/IDisplay.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

Ram::Ram()
{}

void Ram::Draw(Krell::IDisplay *ui) {
    std::ifstream stream("/proc/meminfo");
    if (!stream.is_open()) {
        _name = "Error";
        std::cerr << "cannot read memeinfo" << std::endl;
        ui->NewSection("ram");
        ui->drawText(_name);
        return;
    }
    std::string line;
    long total = 0;
    long free = 0;
    long buffers = 0;
    long cached = 0;
    while (std::getline(stream, line)) {
        long fetched = 0;
        std::istringstream istream(line);
        std::string key;
        std::string unit;
        istream >> key >> fetched >> unit;
        if (key == "MemTotal:")
            total = fetched;
        else if (key == "MemFree:")
            free = fetched;
        else if (key == "Buffers:")
            buffers = fetched;
        else if (key == "Cached:")
            cached = fetched;
    }
    long used = (total - free - buffers - cached);
    std::ostringstream ostream;
    ostream << "Current usage: " << used / 1024 << "MB / " << total / 1024 << " MB";
    _name = ostream.str();
    ui->NewSection("ram");
    ui->drawText(_name);
}
