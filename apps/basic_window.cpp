#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <fmt/ostream.h>

#pragma clang diagnostic push 
// ignoring the fact that window is not used
#pragma clang diagnostic ignored "-Wunused-parameter"
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
#pragma clang diagnostic pop
    glViewport(0, 0, width, height);
}  
int main(void){
    if(!glfwInit()){
        fmt::println("init failed");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(100, 100, "My Title", nullptr, nullptr);
    if(!window){
        fmt::println("window create failed");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        fmt::println("Failed to initialize GLAD");
        return -1;
    }
    glViewport(0, 0, 100, 100);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    fmt::println(std::cerr, "Window Closed");
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
