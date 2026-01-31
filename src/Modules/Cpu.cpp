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
    long long user = 0;
    long long nice = 0;
    long long system = 0;
    long long idle = 0;
    long long iowait = 0;
    long long irq = 0;
    long long softirq = 0;
    long long steal = 0;
    stream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    long long idletime = idle + iowait;
    long long totaltime = user + nice + system + idle + iowait + irq + softirq + steal;
    long long idledelta = idletime - _previdle;
    long long totaldelta = totaltime - _prevtotal;
    double usage = 0.0;
    if (totaldelta != 0)
        usage = 100.0 * (1.0 - (static_cast<double>(idledelta) / static_cast<double>(totaldelta)));
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
