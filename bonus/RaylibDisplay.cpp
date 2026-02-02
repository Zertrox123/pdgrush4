#include "RaylibDisplay.hpp"
#include <iostream>

RaylibDisplay::RaylibDisplay() : _moduleCount(0), _isFrameStarted(false) {
}

RaylibDisplay::~RaylibDisplay() {
    CloseWindow();
}

bool RaylibDisplay::init() {
    // Initialisation fenêtre Raylib
    InitWindow(1000, 800, "MyGKrellm 3D - Bonus Mode");
    SetTargetFPS(60);
    _camera.position = (Vector3){ 15.0f, 15.0f, 15.0f };
    _camera.target = (Vector3){ 0.0f, 5.0f, 0.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;

    return true;
}

void RaylibDisplay::refresh() {
    _moduleCount = 0;
    _overlays.clear();
    UpdateCamera(&_camera, CAMERA_ORBITAL);
    BeginDrawing();
    ClearBackground(GetColor(0x181818FF));
    BeginMode3D(_camera);
    DrawGrid(20, 1.0f);
    DrawPlane((Vector3){0, -0.5f, 0}, (Vector2){40, 40}, GetColor(0x202020FF));
}

void RaylibDisplay::NewSection(std::string Name) {
    float yPos = _moduleCount * 2.5f;
    Vector3 pos = { 0.0f, yPos, 0.0f };
    Vector3 size = { 6.0f, 2.0f, 6.0f };
    Color rackColor = (Color){ 30, 30, 30, 200 };
    Color wireColor = GREEN;
    DrawCubeV(pos, size, rackColor);
    DrawCubeWiresV(pos, size, wireColor);
    Vector3 topPos = { pos.x, pos.y + 1.2f, pos.z + 3.0f };
    TextOverlay title;
    title.text = ":: " + Name + " ::";
    title.position = topPos;
    title.color = GREEN;
    _overlays.push_back(title);
    _moduleCount++;
}

bool RaylibDisplay::drawText(std::string text) {
    float yPos = (_moduleCount - 1) * 2.5f; 
    Vector3 textPos = { 0.0f, yPos, 3.1f };
    TextOverlay content;
    content.text = text;
    content.position = textPos;
    content.color = WHITE;
    _overlays.push_back(content);
    return true;
}

void RaylibDisplay::endFrame() {
    EndMode3D();
    for (const auto& item : _overlays) {
        Vector2 screenPos = GetWorldToScreen(item.position, _camera);
        int fontSize = 20;
        int textWidth = MeasureText(item.text.c_str(), fontSize);
        DrawText(item.text.c_str(), screenPos.x - textWidth/2, screenPos.y, fontSize, item.color);
    }
    DrawText("Souris: Tourner | Molette: Zoom", 10, 10, 20, DARKGRAY);
    EndDrawing();
}

bool RaylibDisplay::shouldClose() {
    return WindowShouldClose();
}