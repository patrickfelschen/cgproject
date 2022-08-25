#include <string>
#include "GUIManager.h"

GUIManager &GUIManager::getInstance() {
    static GUIManager instance;
    return instance;
}

void GUIManager::init(GLFWwindow *window, unsigned int width, unsigned int height) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    this->SCR_WIDTH = width;
    this->SCR_HEIGHT = height;
}

void GUIManager::setFont(const char *path, unsigned int size) {
    io.Fonts->AddFontFromFileTTF(path, size);
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
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::updateAmmoWindow(unsigned int ammoCount, unsigned int magazines) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f));
    ImGui::SetNextWindowPos(ImVec2(SCR_WIDTH - (250.0f * (SCR_WIDTH/SCR_HEIGHT)), SCR_HEIGHT - (150.0f * (SCR_WIDTH/SCR_HEIGHT))));
    ImGui::Begin("ammo", nullptr, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);
    ImGui::Text("%i | %i", ammoCount, magazines);
    ImGui::End();
    ImGui::PopStyleVar();
}

void GUIManager::updateScoreWindow(unsigned int score) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowSize(ImVec2(SCR_WIDTH, 100.0f));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::Begin("score", nullptr, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);
    ImGui::Text("Score: %i", score);
    ImGui::End();
    ImGui::PopStyleVar();
}
