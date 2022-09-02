#ifndef CG_GUIMANAGER_H
#define CG_GUIMANAGER_H

#include "../../libraries/win32/imgui/imgui.h"
#include "../../libraries/win32/imgui/imgui_impl_glfw.h"
#include "../../libraries/win32/imgui/imgui_impl_opengl3.h"
#include "../utils/Color.h"
#include "../maths/Vector2f.h"
#include "../utils/Loader.h"
#include "GLFW/glfw3.h"
#include "SoundManager.h"
#include <numbers>
#include <string>

#define WINDOW_FLAGS ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs

class GUIManager {
private:
    GUIManager() {}

    GLFWwindow *window;

    ImGuiIO io;

    float infoTextDuration = 2.0f;
    float infoTextTimer = 0.0f;
public:
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;

    static GUIManager &getInstance();

    GUIManager(GUIManager const &) = delete;

    void operator=(GUIManager const &) = delete;

    void init(GLFWwindow *window, unsigned int width, unsigned int height);

    void destroy();

    void startDraw();

    void setFont(const char *path);

    void updateAmmoWindow(unsigned int ammoCount, unsigned int magazines);

    void updateScoreWindow(unsigned int score);

    void updateLifeWindow(const char* windowName, unsigned int currentLife, unsigned int maxLife, const Vector2f &pos, float barLength = 300, float thickness = 20.0f);

    void updateSpinner(float radius, float speed, float thickness);

    void drawCrosshair(float thickness, float size, Color color, bool isEmpty);

    void drawInfo(const char *infoText, const Color &textColor = Color(1.0f));

    void drawFPSCounter();

    void drawMainMenu(bool &buttonClicked, const char *mainButtonText, const char *mainText, const Color &mainTextColor,
                      const char *secondaryText = "", const Color &secondaryTextColor = Color(1.0f)) const;

    void render();
};


#endif //CG_GUIMANAGER_H
