#include "Modules/Cpu.hpp"
#include "Displays/IDisplay.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

Cpu::Cpu() : _prevIdle(0), _prevTotal(0) {
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
    std::ifstream statfile("/proc/stat");
    std::string line;
    getline(statfile, line);
    
    std::istringstream ss(line);
    std::string cpu;
    long long user, nice, system, idle, iowait, irq, softirq, steal;
    
    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    
    long long idleTime = idle + iowait;
    long long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;
    
    long long idleDelta = idleTime - _prevIdle;
    long long totalDelta = totalTime - _prevTotal;
    
    double usage = 0.0;
    if (totalDelta != 0) {
        usage = 100.0 * (1.0 - (static_cast<double>(idleDelta) / static_cast<double>(totalDelta)));
    }
    
    _prevIdle = idleTime;
    _prevTotal = totalTime;
    
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
