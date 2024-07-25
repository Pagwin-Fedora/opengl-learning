#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <pog/vertex_helpers.h>
#include <pog/shader_helpers.h>

void framebuffer_size_callback(GLFWwindow*, int width, int height){
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    
    pog::VertexArray VAO{[](std::vector<pog::VertexArrayState>& state){
        GLfloat vertices[]{
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        auto VBO = pog::VertexBuffer(static_cast<void*>(vertices), 9*sizeof(GLfloat), GL_STATIC_DRAW);
        
        state.push_back(std::move(VBO));

        // tell opengl what the values received by the vertex are
        // first arg provides the location value that that shader uses
        // second arg is the size of each element
        // third argument specifies the type of the scalar values
        // fourth argument is whether we want stuff normalized
        // fifth is how many bytes OpenGL needs to step to get from one point to the next
        // and 6th is the offset from the start
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        // enables the array idk why that's necessary
        glEnableVertexAttribArray(0);
    }};

    
    // TODO: if reading this in the future split this shader into a separate file and use std::embed
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    auto vertexShader = pog::Shader(GL_VERTEX_SHADER, vertexShaderSource);

    const char* fragmentShaderSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "\n"
        "void main()\n"
        "{"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    //GLuint fragmentShader;
    auto fragmentShader = pog::Shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    std::vector<pog::Shader> shaders{};
    shaders.push_back(std::move(vertexShader));
    shaders.push_back(std::move(fragmentShader));
    // shader program
    // combines the above shaders into one thing
    //GLuint shaderProgram = glCreateProgram();
    auto shaderProgram = pog::ShaderProgram(std::move(shaders));

    while(!glfwWindowShouldClose(window)){
        process_input(window);

        // also change the background color because why not?
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // the triangle has finally materialized and oh my god I'm definitely not going to continue until I've written a utility library because that's about 121 lines of poorly documented poorly understood code that's such a pain in the ass to have written out
        shaderProgram.use();
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wunused-parameter"
        VAO.use([](auto& _state){
        #pragma clang diagnostic pop
            // first arg is thing we want to draw, second argument is the starting index of the array, last argument is number of vertices
            glDrawArrays(GL_TRIANGLES, 0, 3);
        });

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    fmt::println(std::cerr, "Window Closed");
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
