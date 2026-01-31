#include "Modules/Users.hpp"
#include "Displays/IDisplay.hpp"
#include <utmp.h>
#include <string>
#include <set>

Users::Users() {
}

void Users::Draw(Krell::IDisplay *ui) {
    std::set<std::string> users;
    struct utmp *ut;
    
    setutent();
    while ((ut = getutent()) != nullptr) {
        if (ut->ut_type == USER_PROCESS) {
            users.insert(ut->ut_user);
        }
    }
    endutent();
    
    _name = "";
    for (const auto& user : users) {
        if (!_name.empty()) {
            _name += ", ";
        }
        _name += user;
    }
    
    if (_name.empty()) {
        _name = "None";
    }
    
    ui->NewSection("Logged Users");
    ui->drawText(_name);
}
