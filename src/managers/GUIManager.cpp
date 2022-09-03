
#include "GUIManager.h"

GUIManager &GUIManager::getInstance() {
    static GUIManager instance;
    return instance;
}

/**
 * Initialisert ImGui
 * @param window GLFWwindow Pointer
 * @param width Fensterbreite
 * @param height Fensterhöhe
 */
void GUIManager::init(GLFWwindow *window, unsigned int width, unsigned int height) {
    this->window = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 420");

    this->SCR_WIDTH = width;
    this->SCR_HEIGHT = height;
}

void GUIManager::setFont(const char *path) {
    float size = 50 * (SCR_WIDTH / SCR_HEIGHT);
    ImGui::GetIO().Fonts->AddFontFromFileTTF(path, size);
}

void GUIManager::startDraw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIManager::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUIManager::render() {
    // Show info text for x-seconds

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::drawAmmoWindow(unsigned int ammoCount, unsigned int magazines) {
    this->startNewWindow("ammo", ImVec2(200.0f, 100.0f), ImVec2(SCR_WIDTH - 150.0f, SCR_HEIGHT - 75.0f));
    ImGui::Text("%i | %i", ammoCount, magazines);
    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::drawScoreWindow(unsigned int score) {
    this->startNewWindow("score", ImVec2(SCR_WIDTH, 100.0f),ImVec2(0.0f, 0.0f));
    ImGui::Text("Punkte: %i", score);
    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::updateSpinner(float radius, float speed, float thickness) {
    this->startNewWindow("reloadIndicator", ImVec2(SCR_WIDTH, SCR_HEIGHT), ImVec2(0, 0));

    ImDrawList *drawList = ImGui::GetWindowDrawList();
    drawList->PathClear();

    const int numSegments = drawList->_CalcCircleAutoSegmentCount(radius);
    const float bg_angle_offset = std::numbers::pi * 2.f / numSegments;
    float start = (float) ImGui::GetTime() * speed;
    ImVec2 center(SCR_WIDTH / 2, SCR_HEIGHT / 2);
    for (size_t i = 0; i <= numSegments; i++) {
        const float a = start + (i * bg_angle_offset);
        drawList->PathLineTo(ImVec2(center.x + cos(a) * radius, center.y + sin(a) * radius));
    }
    drawList->PathClear();
    const float angle_offset = (std::numbers::pi * 0.5f) / numSegments;
    for (size_t i = 0; i < numSegments; i++) {
        const float a = start + (i * angle_offset);
        drawList->PathLineTo(ImVec2(center.x + cos(a) * radius, center.y + sin(a) * radius));
    }
    drawList->PathStroke(0xffffffff, false, thickness);

    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::drawCrosshair(float thickness, float size, Color color, bool isEmpty) {
    this->startNewWindow("crosshair", ImVec2(SCR_WIDTH, SCR_HEIGHT), ImVec2(0, 0));

    ImDrawList *drawlist = ImGui::GetForegroundDrawList();

    if (isEmpty) {
        drawlist->AddLine(ImVec2(SCR_WIDTH / 2 - size, SCR_HEIGHT / 2), ImVec2(SCR_WIDTH / 2 + size, SCR_HEIGHT / 2),
                          ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f)), thickness);
        drawlist->AddLine(ImVec2(SCR_WIDTH / 2, SCR_HEIGHT / 2 - size), ImVec2(SCR_WIDTH / 2, SCR_HEIGHT / 2 + size),
                          ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f)), thickness);
//        drawlist->AddText(ImVec2(SCR_WIDTH/2, SCR_HEIGHT/2), ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f)), "Reload");
    } else {
        drawlist->AddLine(ImVec2(SCR_WIDTH / 2 - size, SCR_HEIGHT / 2), ImVec2(SCR_WIDTH / 2 + size, SCR_HEIGHT / 2),
                          ImGui::ColorConvertFloat4ToU32(ImVec4(color.r, color.g, color.b, color.a)), thickness);
        drawlist->AddLine(ImVec2(SCR_WIDTH / 2, SCR_HEIGHT / 2 - size), ImVec2(SCR_WIDTH / 2, SCR_HEIGHT / 2 + size),
                          ImGui::ColorConvertFloat4ToU32(ImVec4(color.r, color.g, color.b, color.a)), thickness);
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::drawFPSCounter() {
    this->startNewWindow("fps", ImVec2(SCR_WIDTH, 100.0f), ImVec2(SCR_WIDTH - 150.0f, 0.0f));
    ImGui::Text("%f", ImGui::GetIO().Framerate);
    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::drawLifeWindow(const char* windowName, unsigned int currentLife, unsigned int maxLife, const Vector2f &pos , float barLength, float thickness) {
    this->startNewWindow(windowName, ImVec2(SCR_WIDTH, SCR_HEIGHT), ImVec2(0.0, 0.0));
    ImGui::GetWindowDrawList()->AddLine(
            ImVec2(pos.x - (barLength / 2), pos.y),
            ImVec2(pos.x + (barLength / 2), pos.y),
            ImGui::ColorConvertFloat4ToU32(ImVec4(255.0f, 0.0f, 0.0f, 255.0f)),
            thickness
    );
    ImGui::GetWindowDrawList()->AddLine(
            ImVec2(pos.x - (barLength / 2), pos.y),
            ImVec2((pos.x - (barLength / 2)) + ((float) currentLife * (barLength / maxLife)), pos.y),
            ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 255.0f, 0.0f, 255.0f)),
            thickness
    );
    char lifeText[16];
    sprintf(lifeText, "%i/%i", currentLife, maxLife);
    auto lifeTextWidth = ImGui::CalcTextSize(lifeText).x;
    ImGui::SetCursorPos(ImVec2(pos.x - lifeTextWidth * 0.5f, pos.y));
    ImGui::Text("%s", lifeText);
    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::drawMainMenu(bool &buttonClicked, const char *mainButtonText, const char *mainText,
                              const Color &mainTextColor, const char *secondaryText,
                              const Color &secondaryTextColor) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    Vector2f buttonSize(200.0f, 75.0f);

    this->startNewWindow("mainmenu", ImVec2(SCR_WIDTH, SCR_HEIGHT), ImVec2(0.0f, 0.0f), 1.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                                                                        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
    char score[32];
    sprintf(score, "Highscore: %i", Loader::getInstance().readScoreFromFile());
    auto mainTextWidth = ImGui::CalcTextSize(mainText).x;
    auto secondaryTextWidth = ImGui::CalcTextSize(secondaryText).x;
    auto highscoreTextWidth = ImGui::CalcTextSize(score).x;
    ImGui::SetCursorPos(ImVec2((SCR_WIDTH - mainTextWidth) * 0.5f, SCR_HEIGHT / 2 - buttonSize.y / 2 - 180.0f));
    ImGui::TextColored(ImVec4(mainTextColor.r, mainTextColor.g, mainTextColor.b, mainTextColor.a), "%s", mainText);
    ImGui::SetCursorPos(ImVec2((SCR_WIDTH - secondaryTextWidth) * 0.5f, SCR_HEIGHT / 2 - buttonSize.y / 2 - 120.0f));
    ImGui::TextColored(ImVec4(secondaryTextColor.r, secondaryTextColor.g, secondaryTextColor.b, secondaryTextColor.a),
                       "%s", secondaryText);
    ImGui::SetCursorPos(ImVec2((SCR_WIDTH - highscoreTextWidth) * 0.5f, SCR_HEIGHT / 2 - buttonSize.y / 2 - 60.0f));
    ImGui::Text("%s", score);
    ImGui::SetCursorPos(ImVec2(SCR_WIDTH / 2 - buttonSize.x / 2, SCR_HEIGHT / 2 - buttonSize.y / 2));
    if (ImGui::Button(mainButtonText, ImVec2(buttonSize.x, buttonSize.y))) {
        buttonClicked = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    ImGui::SetCursorPos(ImVec2(SCR_WIDTH / 2 - buttonSize.x / 2, SCR_HEIGHT / 2 + buttonSize.y / 2 + 20.0f));
    if (ImGui::Button("Beenden", ImVec2(buttonSize.x, buttonSize.y))) {
        exit(EXIT_SUCCESS);
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::drawInfo(const char *infoText, const Color &textColor) {
    this->startNewWindow("info", ImVec2(SCR_WIDTH, SCR_HEIGHT), ImVec2(0.0f, 0.0f));
    auto textWidth = ImGui::CalcTextSize(infoText).x;
    ImGui::SetCursorPos(ImVec2((SCR_WIDTH - textWidth) * 0.5f, SCR_HEIGHT / 2 + 50.0f));
    ImGui::TextColored(ImVec4(textColor.r, textColor.g, textColor.b, textColor.a), "%s", infoText);
    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::startNewWindow(const char *windowName, const ImVec2 &size, const ImVec2 &pos,float alpha, ImGuiWindowFlags flags) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::SetNextWindowBgAlpha(alpha);
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(ImVec2(pos));
    ImGui::Begin(windowName, nullptr, flags);
}
