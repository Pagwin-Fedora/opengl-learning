#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  
int main(void){
    if(!glfwInit()){
        std::cout << "init failed" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(100, 100, "My Title", nullptr, nullptr);
    if(!window){
        std::cout << "window create failed" << std::endl;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 100, 100);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    std::cerr << "how did we get here" << std::endl;
    std::string s;
    std::getline(std::cin, s);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
