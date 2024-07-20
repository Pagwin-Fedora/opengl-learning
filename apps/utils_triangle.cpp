#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <pog/vertex_helpers.h>

#pragma clang diagnostic push
// ignoring the fact that window is not used
#pragma clang diagnostic ignored "-Wunused-parameter"
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
#pragma clang diagnostic pop
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

    

    pog::VertexArray VAO{[](){
        GLfloat vertices[]{
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        pog::VertexBuffer VBO{static_cast<void*>(vertices), 9*sizeof(GLfloat), GL_STATIC_DRAW};

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

    // see the vertex shader part of the above page
    
    // TODO: if reading this in the future split this shader into a separate file and use std::embed
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    // need to use opengl create shader function more silly ids
    // tutorial uses `unsigned int` instead of GLuint
    // the tutorial is wrong https://stackoverflow.com/a/12285564
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // compile the above shader source code into the shader we just made
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // get error info for the shader we compiled
    // the tutorial uses `int` instead of GLint
    // the tutorial is wrong https://stackoverflow.com/a/12285564
    GLint  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fmt::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
    }

    // repeat of the above for a fragment shader instead of a vertex shader
    const char* fragmentShaderSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "\n"
        "void main()\n"
        "{"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fmt::println("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
    }

    // shader program
    // combines the above shaders into one thing
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fmt::println("ERROR::SHADER::PROGRAM::LINK_FAILED\n{}", infoLog);
    }

    glUseProgram(shaderProgram);

    // shaders are now linked into program so we can yeet them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    while(!glfwWindowShouldClose(window)){
        process_input(window);

        // also change the background color because why not?
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // the triangle has finally materialized and oh my god I'm definitely not going to continue until I've written a utility library because that's about 121 lines of poorly documented poorly understood code that's such a pain in the ass to have written out
        glUseProgram(shaderProgram);
        VAO.use([](){
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
