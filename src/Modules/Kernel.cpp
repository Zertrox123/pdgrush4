#include "Modules/Kernel.hpp"
#include "Displays/IDisplay.hpp"
#include <sys/utsname.h>

Kernel::Kernel() {
    struct utsname buffer;
    uname(&buffer);
    _name = buffer.release;
}

void Kernel::Draw(Krell::IDisplay *ui) {
    ui->NewSection("Kernel");
    ui->drawText(_name);
}
