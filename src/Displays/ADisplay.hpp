#include "IDisplay.hpp"

namespace Krell{ 
    class ADisplay : IDisplay{
private:

public:
        virtual bool init() = 0;

        virtual void NewSection(std::string Name) = 0;
        virtual bool drawText(std::string text) = 0;
    };
}
