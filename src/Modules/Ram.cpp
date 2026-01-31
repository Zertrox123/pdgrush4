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
    double total = 0;
    double free = 0;
    double buffers = 0;
    double cached = 0;
    while (std::getline(stream, line)) {
        double fetched = 0;
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
    double used = (total - free - buffers - cached);
    std::ostringstream ostream;
    ostream << "Current usage (mb): " << used / 1024 << "MB / " << total / 1024 << " MB";
    // TODO: do gb
    _name = ostream.str();
    ui->NewSection("ram");
    ui->drawText(_name);
}
