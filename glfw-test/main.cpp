#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "matutils.hpp"
#include "shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define RES_PATH(FILE) (std::string(RES_DIR)+std::string("/")+std::string(FILE)).c_str()

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
    // TODO: use RES_PATH macro
    // TODO: move shaders to res
    Shader shader("vert.glsl", "frag.glsl");  

    float vertices[] =
    {
        // positions                    // colors           // texture coords
        -1.0f,  -1.0f,  -1.0f, 1.0f,    0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        1.0f,   -1.0f,  -1.0f, 1.0f,    1.0f, 0.0f, 0.0f,   1.0, 0.0f,
        -1.0f,  1.0f,   -1.0f, 1.0f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        1.0f,   1.0f,   -1.0f, 1.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.0f,

        -1.0f,  -1.0f,  1.0f, 1.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        1.0f,   -1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 1.0f,   1.0, 0.0f,
        -1.0f,  1.0f,   1.0f, 1.0f,     0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
        1.0f,   1.0f,   1.0f, 1.0f,     1.0f, 1.0f, 1.0f,   0.0f, 0.0f
    };


    constexpr auto fovRad = M_PI * 0.5;
    constexpr auto near = 0.1;
    constexpr auto far = 10.0;
    const Mat4d perspective = perspectiveMatrix(fovRad, near, far);
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *imageData = stbi_load(RES_PATH("container.jpg"), &width, &height, &nrChannels, 0); 
    if (imageData == nullptr)
    {
        printf("Image load failed\n");
        return 4;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);

    unsigned int indices[] =
    {
        4, 7, 6, // front
        4, 5, 7, // front
        0, 6, 2, // left
        0, 4, 6, // left
        1, 3, 7, // right
        1, 7, 5, // right
        0, 2, 3, // back 
        0, 3, 1, // back
        0, 1, 5, // bottom
        0, 5, 4, // bottom
        2, 7, 3, // top
        2, 6, 7 // top
    };

    // Reserve the buffer in GPU memory
    uint32_t VBO{0};
    uint32_t VAO{0};
    uint32_t EBO{0};
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    

    // Copy the vertices to the array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret vertex buffer data
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);   // pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(4 * sizeof(float))); // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float))); // tex
    glEnableVertexAttribArray(2);  

    // note that this is allowed, the call to glVertexAttribPointer registered VBO
    // as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Activate the shader program
    //glUseProgram(shaderProgram);
    shader.use();

    double t{0.0};
    constexpr auto fps{60.0};
    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        float timeValue = glfwGetTime();
        float greenValue = 0.5f+0.5f*sin(timeValue*2.0f);
        shader.setFloat("pylly", greenValue);

        shader.setMat4f("perspective", perspective.cast<float>());

        // std::cout << camera << std::endl << std::endl;


        const Vec3d from{2.0, 1.0, 4.0};
        const Vec3d to{0.0, 0.0, 0.0};
        const Vec3d up{0.0, 1.0, 0.0};
        
        const Mat4d camera = cameraMatrix(from, to, up);
        shader.setMat4f("camera", camera.cast<float>());

        const Mat4d model = transformationMatrix(Vec3d(0.0, 0.0, 0.0), Vec3d(sin(t), 1.0 - sin(t), cos(t)));
        shader.setMat4f("model", model.cast<float>());

        // glDrawArrays(GL_TRIANGLES, 0, 36); // use this when not rendering from index buffer
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0); // use this when rendering from index buffer

        glfwSwapBuffers(window);
        glfwPollEvents();

        t += 1.0 / fps;
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