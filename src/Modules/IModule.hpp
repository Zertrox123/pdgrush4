#include <string>
#include "Displays/IDisplay.hpp"

namespace Krell {
    class IModule {
private:
    std::string _name;
public:
    virtual ~IModule() {};
    virtual void Draw(IDisplay winapi) = 0;
    };
}
