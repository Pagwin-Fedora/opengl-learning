#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <string_view>
#include <pog/shader_helpers.h>

namespace pog{
    class ShaderCompilationError{
        public:
        std::string msg;
        ShaderCompilationError(std::string_view msg){
            this->msg = msg;
        }
    };
    class ShaderLinkError{
        public:
        std::string msg;
        ShaderLinkError(std::string_view msg){
            this->msg = msg;
        }
    };
    class Shader{
        GLuint id;
        bool moved;
        public:
        Shader(GLenum shaderType, const std::string& prog){
            moved = false;
            this->id = glCreateShader(shaderType);
            
            // for some reason we can't use prog.c_str directly
            const char* tmp = prog.c_str();
            glShaderSource(this->id, 1, &tmp, NULL);

            glCompileShader(this->id);

            GLint  success;
            glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);
            if(!success){
                char infoLog[512];
                glGetShaderInfoLog(this->id, 512, NULL, infoLog);
                throw ShaderCompilationError(infoLog);
            }
        }
        Shader(Shader&& rhs){
            this->id = rhs.id;
            this->moved = false;
            rhs.moved = true;
        }
        Shader& operator=(Shader&& rhs){
            this->id = rhs.id;
            this->moved = false;
            rhs.moved = true;
            return *this;
        }
        Shader(Shader&) = delete;
        Shader& operator=(Shader&) = delete;
        GLuint get_id(){
            return this->id;
        }
        ~Shader(){
            if(moved) return;
            glDeleteShader(id);
        }
    };
    class ShaderProgram{
        GLuint id;
        bool moved;
        public:
        ShaderProgram(std::vector<Shader> shaders){
            moved = false;
            id = glCreateProgram();
            for(auto& shader:shaders){
                glAttachShader(id, shader.get_id());
            }
            glLinkProgram(id);
            
            GLint  success;
            glGetShaderiv(this->id, GL_LINK_STATUS, &success);
            if(!success){
                char infoLog[512];
                glGetShaderInfoLog(this->id, 512, NULL, infoLog);
                throw ShaderCompilationError(infoLog);
            }
        }
        void use(){
            glUseProgram(id);
        }
        ShaderProgram(ShaderProgram&& rhs){
            this->id = rhs.id;
            this->moved = false;
            rhs.moved = true;
        }
        ShaderProgram& operator=(ShaderProgram&& rhs){
            this->id = rhs.id;
            this->moved = false;
            rhs.moved = true;
            return *this;
        }
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&) = delete;
        ~ShaderProgram(){
            if(moved) return;
            glDeleteProgram(id);
        }
    };
}
