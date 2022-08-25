
#ifndef CG_GUIMANAGER_H
#define CG_GUIMANAGER_H

#include "../../libraries/win32/imgui/imgui.h"
#include "../../libraries/win32/imgui/imgui_impl_glfw.h"
#include "../../libraries/win32/imgui/imgui_impl_opengl3.h"

class GUIManager {
private:
    GUIManager() {}

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

    void setFont(const char* path, unsigned int size);

    void updateAmmoWindow(unsigned int ammoCount, unsigned int magazines);

    void updateScoreWindow(unsigned int score);

    void render();
};


#endif //CG_GUIMANAGER_H
