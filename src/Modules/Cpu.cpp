#include "Modules/Cpu.hpp"
#include "Displays/IDisplay.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

Cpu::Cpu() : _previdle(0), _prevtotal(0) {
    _cores = sysconf(_SC_NPROCESSORS_ONLN);
    
    std::ifstream myfile("/proc/cpuinfo");
    std::string line;
    while (getline(myfile, line)){
        if (line.find("model name") != std::string::npos) {
            size_t pos = line.find(':');
            _model = line.substr(pos + 2);
            break;
        }
    }
}

void Cpu::Draw(Krell::IDisplay *ui) {
    ui->NewSection("cpu");
    std::ifstream statfile("/proc/stat");
    std::string line;
    getline(statfile, line);
    std::istringstream stream(line);
    std::string cpu;
    double user = 0;
    double nice = 0;
    double system = 0;
    double idle = 0;
    double iowait = 0;
    double irq = 0;
    double softirq = 0;
    double steal = 0;
    stream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    double idletime = idle + iowait;
    double totaltime = user + nice + system + idle + iowait + irq + softirq + steal;
    double idledelta = idletime - _previdle;
    double totaldelta = totaltime - _prevtotal;
    double usage = 0.0;
    if (totaldelta != 0)
        usage = 100.0 * (1.0 - (idledelta / totaldelta));
    _previdle = idletime;
    _prevtotal = totaltime;
    std::ifstream freqfile("/proc/cpuinfo");
    std::string freq;
    while (getline(freqfile, line)){
        if (line.find("cpu MHz") != std::string::npos) {
            size_t pos = line.find(':');
            freq = line.substr(pos + 2);
            double mhz = std::stod(freq);
            freq = std::to_string(static_cast<int>(mhz / 1000)) + " GHz";
            break;
        }
    }
    ui->drawText(_model + "\n" + "Cores: " + std::to_string(_cores) + "\nFrequency: " + freq + "\nUsage: " + std::to_string(static_cast<int>(usage)) + "%");
}
