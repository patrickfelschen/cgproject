#ifndef CG_GUIMANAGER_H
#define CG_GUIMANAGER_H

#include "../../libraries/win32/imgui/imgui.h"
#include "../../libraries/win32/imgui/imgui_impl_glfw.h"
#include "../../libraries/win32/imgui/imgui_impl_opengl3.h"
#include "../utils/Color.h"
#include <numbers>

#define WINDOW_FLAGS ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs

class GUIManager {
private:
    GUIManager() {}

    GLFWwindow* window;

    ImGuiIO io;
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;

public:
    static GUIManager &getInstance();

    GUIManager(GUIManager const&)       = delete;
    void operator=(GUIManager const&)   = delete;

    void init(GLFWwindow *window, unsigned int width, unsigned int height);

    void destroy();

    void startDraw();

    void setFont(const char* path);

    void updateAmmoWindow(unsigned int ammoCount, unsigned int magazines);

    void updateScoreWindow(unsigned int score);

    void updateLifeWindow(unsigned int life);

    void updateSpinner(float radius, float speed, float thickness);

    void drawCrosshair(float thickness, float size, Color color, bool isEmpty);

    void drawFPSCounter();

    void render();
};


#endif //CG_GUIMANAGER_H
