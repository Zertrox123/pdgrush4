#include "Modules/Disk.hpp"
#include "Displays/IDisplay.hpp"
#include <sstream>
#include <iostream>
#include <sys/statvfs.h>

Disk::Disk()
{}

void Disk::Draw(Krell::IDisplay *ui) {
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        _name = "Error";
        std::cerr << "Error while trying to read /" << std::endl;
        ui->NewSection("Disk");
        ui->drawText(_name);
        return;
    }
    double total = (stat.f_blocks * stat.f_frsize) / (1024 * 1024) * 1024;
    double available = stat.f_bfree * stat.f_frsize / (1024 * 1024) * 1024;
    double used = total - available;
    double finaltotal = total / 1024.0 / 1024.0;
    double finalused = used / 1024.0 / 1024.0;
    std::ostringstream stream;
    stream.precision(2);
    stream << std::fixed;
    stream << "Spaces: " << finalused << " GB / " << finaltotal << " GB";
    _name = stream.str();
    ui->NewSection("Disk");
    ui->drawText(_name);
}
