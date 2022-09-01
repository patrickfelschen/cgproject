//
// Created by Patrick on 01.08.2022.
// https://learnopengl.com/Getting-started/Hello-Window
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include "Game.h"
#include "managers/GUIManager.h"
#include "managers/SoundManager.h"
#include <irrKlang.h>

void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int modes);

void glfwCursorPosCallback(GLFWwindow *window, double xpos, double ypos);

void glfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

void glfwErrorCallback(int, const char *errorMsg);


void GLAPIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam);

const bool fullScreen = false;

const unsigned int SCR_WIDTH = fullScreen ? 1920 : 1920 / 2;
const unsigned int SCR_HEIGHT = fullScreen ?  1080 : 1080 / 2;

Camera *camera;
Game *game;
bool gameStarted = false;

int main(int argc, char **argv) {
    if (glfwInit() == GLFW_FALSE) {
        std::cerr << "ERROR::GLFW: Could not start GLFW3" << std::endl;
        exit(EXIT_FAILURE);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(
            SCR_WIDTH,
            SCR_HEIGHT,
            "CG Projekt",
            fullScreen ? glfwGetPrimaryMonitor() : nullptr, nullptr
    );
    if (window == nullptr) {
        std::cerr << "ERROR::GLFW: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, glfwCursorPosCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeCallback);
    glfwSetErrorCallback(glfwErrorCallback);

#if WIN32
    glewExperimental = GL_TRUE;
    GLenum msg = glewInit();
    if (msg != GLEW_OK) {
        std::cerr << "ERROR::GLEW: " << glewGetErrorString(msg) << std::endl;
        exit(EXIT_FAILURE);
    }
#endif

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glDebugMessageCallback(glErrorCallback, nullptr);

    SoundManager::getInstance().init(
            {
                "../assets/Sounds/getout.ogg",
                "../assets/Sounds/pop.mp3",
                "../assets/Sounds/gunshot.mp3",
                "../assets/Sounds/night-ambience-17064.mp3",
                "../assets/Sounds/step.mp3",
                "../assets/Sounds/magazinecase.mp3",
                "../assets/Sounds/reload.mp3",
                "../assets/Sounds/heal.mp3",
                "../assets/Sounds/damage.mp3",
                "../assets/Sounds/hit.mp3",
            }
    );
    GUIManager::getInstance().init(window, SCR_WIDTH, SCR_HEIGHT);
    GUIManager::getInstance().setFont("../assets/Fonts/font.ttf");

    camera = new Camera(window);
    game = new Game(camera);

    SoundManager::getInstance().play2DSound("../assets/Sounds/getout.ogg", true);

    {
        double lastTime = 0;
        while (!glfwWindowShouldClose(window)) {
            double now = glfwGetTime();
            double deltaTime = now - lastTime;
            lastTime = now;
            glfwPollEvents();

            GUIManager::getInstance().startDraw();

            // Render start
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2, 0.2, 0.2, 1.0);
//            printf("gameStarted: %i\n", gameStarted);

            if(gameStarted) {
                game->update((float) deltaTime);
                game->render();
            }
            else {
                GUIManager::getInstance().drawMainMenu(gameStarted, "Start Game", "Kleister", Color(1.0f));
            }

            GUIManager::getInstance().render();
            // Render end
            glfwSwapBuffers(window);
        }
    }

    GUIManager::getInstance().destroy();
    SoundManager::getInstance().destroy();
    glfwTerminate();
    delete game;
    delete camera;
    exit(EXIT_SUCCESS);
}

void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int modes) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    game->processKeyInput(key, action);
}

void glfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    game->processKeyInput(button, action);
}

void glfwCursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    game->processMouseInput((float) xpos, (float) ypos);
}

void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void glfwErrorCallback(int, const char *errorMsg) {
    std::cerr << "ERROR::GLFW: " << errorMsg << std::endl;
}

void GLAPIENTRY glErrorCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar *message,
                                const void *userParam) {
    if (type == GL_DEBUG_TYPE_ERROR) {
        std::cerr << message << std::endl;
    }
}
