#include "Modules/Date.hpp"
#include "Displays/IDisplay.hpp"
#include <iomanip>
#include <sstream>
#include <ctime>

Date::Date()
{}

void Date::Draw(Krell::IDisplay *ui) {
    std::time_t now = std::time(nullptr);
    std::tm *localtime = std::localtime(&now);

    std::ostringstream stream;
    stream << std::put_time(localtime, "%Y-%m-%d %H:%M:%S");
    _name = stream.str();
    ui->NewSection("Date");
    ui->drawText(_name);
}
