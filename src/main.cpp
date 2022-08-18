//
// Created by Patrick on 01.08.2022.
// https://learnopengl.com/Getting-started/Hello-Window
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include "Game.h"

void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void glfwErrorCallback(int, const char *errorMsg);

void drawCrosshair();

void GLAPIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam);

const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

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

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CG Projekt", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "ERROR::GLFW: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glDebugMessageCallback(glErrorCallback, nullptr);

    Camera camera(*window);
    Game game(*window, camera);

    {
        double lastTime = 0;
        while (!glfwWindowShouldClose(window)) {
            double now = glfwGetTime();
            double deltaTime = now - lastTime;
            lastTime = now;
            processInput(window);
            glfwPollEvents();
            // Render start
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2, 0.2, 0.2, 1.0f);

            drawCrosshair();

            game.update((float) deltaTime);
            game.render();
            // Render end
            glfwSwapBuffers(window);
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void drawCrosshair()
{
    glPushMatrix();
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCR_WIDTH, SCR_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(240, 240, 240);//white
    glLineWidth(2.0);
    glBegin(GL_LINES);
    //horizontal line
    glVertex2i(SCR_WIDTH / 2 - 7, SCR_HEIGHT / 2);
    glVertex2i(SCR_WIDTH / 2 + 7, SCR_HEIGHT / 2);
    glEnd();
    //vertical line
    glBegin(GL_LINES);
    glVertex2i(SCR_WIDTH / 2, SCR_HEIGHT / 2 + 7);
    glVertex2i(SCR_WIDTH / 2, SCR_HEIGHT / 2 - 7);
    glEnd();

    glPopMatrix();


}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void glfwErrorCallback(int, const char *errorMsg) {
    std::cerr << "ERROR::GLFW: " << errorMsg << std::endl;
}

void GLAPIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
    if (type == GL_DEBUG_TYPE_ERROR) {
        std::cerr << message << std::endl;
    }
}
