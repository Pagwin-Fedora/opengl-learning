#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <string_view>
namespace pog{
    class ShaderCompilationError{
        public:
        std::string msg;
        ShaderCompilationError(std::string_view msg);
    };
    class ShaderLinkError{
        public:
        std::string msg;
        ShaderLinkError(std::string_view msg);
    };
    class Shader{
        GLuint id;
        bool moved;
        public:
        Shader(GLenum shaderType, const std::string& prog);
        Shader(Shader&& rhs);
        Shader& operator=(Shader&& rhs);
        Shader(Shader&) = delete;
        Shader& operator=(Shader&) = delete;
        GLuint get_id();
        ~Shader();
    };
    class ShaderProgram{
        GLuint id;
        bool moved;
        public:
        ShaderProgram(std::vector<Shader> shaders);
        void use();
        ShaderProgram(ShaderProgram&& rhs);
        ShaderProgram& operator=(ShaderProgram&& rhs);
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&) = delete;
        ~ShaderProgram();
    };
}
