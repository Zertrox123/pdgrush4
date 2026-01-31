#include "Modules/Network.hpp"
#include "Displays/IDisplay.hpp"
#include <sstream>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <iostream>
#include <arpa/inet.h>

Network::Network()
{}

void Network::Draw(Krell::IDisplay *ui) {
    struct ifaddrs *ifaddr;
    struct ifaddrs *ifa;
    std::ostringstream stream;

    if (getifaddrs(&ifaddr) == -1) {
        std::cerr << "Error while trying to get infos" << std::endl;
        _name = "Error";
    } else {
        bool first = true;
        for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == nullptr)
                continue;
            if (ifa->ifa_addr->sa_family == AF_INET) {
                sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(ifa->ifa_addr);
                std::string ip = inet_ntoa(addr->sin_addr);
                if (!first)
                    stream << "\n";
                stream << ifa->ifa_name << ": " << ip;
                first = false;
            }
        }
        freeifaddrs(ifaddr);
        freeifaddrs(ifa);
        _name = stream.str();
        if (_name.empty())
            _name = "no interfaces found?";
    }
    ui->NewSection("Network Info");
    ui->drawText(_name);
}
