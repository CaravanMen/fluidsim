
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

void error_callback(int err, const char* desc)
{
    fprintf(stderr, "[ERR] GLFW ERR CODE: %i\n DESC: %s\n", err, desc);
}

int main(int argc, char const *argv[])
{

    glfwSetErrorCallback(error_callback); /* set error callback */

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    GLFWwindow* window = glfwCreateWindow(500, 500, "fluid-simulation", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize OpenGL\n");
    }
    if (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
