#include <GLFW/glfw3.h>
#include <iostream>
int main(void){
    if(!glfwInit()){
        std::cout << "init failed" << std::endl;
    }
    std::cout << "init success" << std::endl;
    GLFWwindow* window = glfwCreateWindow(100, 100, "My Title", nullptr, nullptr);
    if(!window){
        std::cout << "window create failed" << std::endl;
    }
    std::string s;
    std::cin >> s;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
