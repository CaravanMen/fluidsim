#include <errorhandler.h>
#include <GLFW/glfw3.h>

#define RAND_MAX 1
int main(int argc, char const *argv[])
{ 
    // ASSERT(glfwInit(), "Initialized GLFW", "Failed to initialize GLFW");
    // GLFWwindow* window = glfwCreateWindow(500, 500, "window", NULL, NULL);
    // ASSERT(window, "Created GLFW window", "Failed to create glfw window");

    FILE* stream = freopen("./output.txt", "a", stderr);
    // freopen("./output.txt", "a", stderr);
    log(stream, BLUE, "[TEST] ", "This is an output to file test");
    fclose(stream);
    TRACE("This is a test trace");
    ERROR("This is a test error");
    WARN("This is a test warning");
    ASSERT(1<2, "This is a test successful assertion ", "");
    ASSERT(1>2, "This is a test assertion ", "This is a test failed assertion");
    /* code */
    return 0;
}
