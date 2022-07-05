//
//  main.cpp
//
//  Created by Patrick Felschen on 12.05.22.
//  Quelle: https://www.glfw.org/documentation.html
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include "FreeImage.h"
#include "GLincludes.hpp"
#include "RenderEngine/Loader.hpp"
#include "RenderEngine/Renderer.hpp"
#include "Models/RawModel.hpp"
#include "Shaders/StaticShader.hpp"
#include "Shaders/ShaderProgram.hpp"
#include "Models/TexturedModel.hpp"

static const int window_width = 640;
static const int window_height = 480;
Camera camera(Vector(0,0,5));

static void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}
 

static void print_opengl_version()
{
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.move(GLFW_KEY_W);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.move(GLFW_KEY_A);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.move(GLFW_KEY_S);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.move(GLFW_KEY_D);
    }
}

int main(int argc, char *argv[])
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);
    
    /* Initialize the library */
    if (!glfwInit())
    {
        // Initialization failed
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "Computergrafik Projekt", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
#if _WIN32
    glewExperimental = GL_TRUE;
    glewInit();
#endif
    
    print_opengl_version();

    Loader loader;
    StaticShader shader;
    Renderer renderer(window_width, window_height, shader);

    std::vector<float> vertices = {
	    -0.5f,0.5f,-0.5f,	
	    -0.5f,-0.5f,-0.5f,	
	    0.5f,-0.5f,-0.5f,	
	    0.5f,0.5f,-0.5f,		
				
	    -0.5f,0.5f,0.5f,	
	    -0.5f,-0.5f,0.5f,	
	    0.5f,-0.5f,0.5f,	
	    0.5f,0.5f,0.5f,
				
	    0.5f,0.5f,-0.5f,	
	    0.5f,-0.5f,-0.5f,	
	    0.5f,-0.5f,0.5f,	
	    0.5f,0.5f,0.5f,
				
	    -0.5f,0.5f,-0.5f,	
	    -0.5f,-0.5f,-0.5f,	
	    -0.5f,-0.5f,0.5f,	
	    -0.5f,0.5f,0.5f,
				
	    -0.5f,0.5f,0.5f,
	    -0.5f,0.5f,-0.5f,
	    0.5f,0.5f,-0.5f,
	    0.5f,0.5f,0.5f,
				
	    -0.5f,-0.5f,0.5f,
	    -0.5f,-0.5f,-0.5f,
	    0.5f,-0.5f,-0.5f,
	    0.5f,-0.5f,0.5f
    };

    std::vector<int> indices = {
        0,1,3,
        3,1,2,
        4,5,7,
        7,5,6,
        8,9,11,
        11,9,10,
        12,13,15,
        15,13,14,
        16,17,19,
        19,17,18,
        20,21,23,
        23,21,22
    };

    std::vector<float> textureCoords = {
        0,1,
        0,0,
        1,0,
        1,1,
        0,1,
        0,0,
        1,0,
        1,1,
        0,1,
        0,0,
        1,0,
        1,1,
        0,1,
        0,0,
        1,0,
        1,1,
        0,1,
        0,0,
        1,0,
        1,1,
        0,1,
        0,0,
        1,0,
        1,1,
    };

    RawModel model = loader.loadToVAO(vertices, textureCoords, indices);
    ModelTexture texture(loader.loadTexture(ASSET_DIRECTORY "Images/colorchess.bmp"));
    TexturedModel* texturedModel = new TexturedModel(model, texture);

    Entity entity1(texturedModel, Vector(-1, 0.5, -3), 0, 0, 0, 1);
    Entity entity2(texturedModel, Vector(1, 0.5, -3), 0, 0, 0, 0.5);
    Entity entity3(texturedModel, Vector(0, -0.5, -3), 0, 0, 0, 2);

    std::vector<Entity> entities;
    for (int i = 0; i < 10; i++) {
        entities.push_back(Entity(texturedModel, Vector(i,i,0), 0,0,0,1));
    }
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        entity1.increaseRotation(1, 1, 0);
        entity2.increaseRotation(-1, -1, 0);
        entity3.increaseRotation(0, 3, 0);
        processInput(window);
        //entity.increasePosition(0, 0, -0.002f);
        /* Render here */
        renderer.prepare();
        shader.start();
        shader.loadViewMatrix(camera);
        renderer.render(entity1, shader);
        renderer.render(entity2, shader);
        renderer.render(entity3, shader);
        shader.stop();

        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.cleanUp();
    loader.cleanUp();

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
