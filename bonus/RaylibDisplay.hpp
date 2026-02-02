#pragma once
#include "../src/Displays/IDisplay.hpp"
#include "raylib.h"
#include <vector>
#include <string>

struct TextOverlay {
    std::string text;
    Vector3 position;
    Color color;
};

class RaylibDisplay : public Krell::IDisplay {
    private:
        Camera3D _camera;
        int _moduleCount;
        bool _isFrameStarted;
        std::vector<TextOverlay> _overlays;
    protected:
    public:
        RaylibDisplay();
        ~RaylibDisplay() override;
        bool init() override;
        void NewSection(std::string Name) override;
        bool drawText(std::string text) override;
        void refresh() override;
        void endFrame();
        bool shouldClose();
};
