#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "shader.hpp"

// OK boi start banging https://learnopengl.com/
// https://www.glfw.org/docs/3.3/quick.html

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

constexpr int window_width{800};
constexpr int window_height{600};

int main()
{
    printf("Starting the program\n");

    if (!glfwInit())
    {
        return -1;
    }

    // Set GLFW to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set profile (a compatibility thing)
    // Telling GLFW we want to use the core-profile means
    // we'll get access to a smaller subset of OpenGL features
    // without backwards-compatible features we no longer need
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "openGL is fun", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD before calling any openGL function
    // Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the viewport
    glViewport(0, 0, window_width, window_height);

    // Adjust the viewport if user resizes the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Build and compile the shader program
    Shader shader("vert.glsl", "frag.glsl");  

    float vertices[] =
    {
        // positions        // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
    };

    // unsigned int indices[] =
    // {
    //     0, 1, 3,   // first triangle
    //     1, 2, 3    // second triangle
    // };

    // Reserve the buffer in GPU memory
    uint32_t VBO{0};
    uint32_t VAO{0};
    // uint32_t EBO{0};
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    

    // Copy the vertices to the array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copy our index array in a element buffer for OpenGL to use
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret vertex buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO
    // as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Activate the shader program
    //glUseProgram(shaderProgram);
    shader.use();
    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        // float timeValue = glfwGetTime();
        // float greenValue = sin(timeValue);
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "dynamicColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        


        glDrawArrays(GL_TRIANGLES, 0, 3); // use this when not rendering from index buffer
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // use this when rendering from index buffer

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);
    shader.destroy();

    printf("Successfully exited the program!\n");
    
    glfwTerminate();
    return 0;
}