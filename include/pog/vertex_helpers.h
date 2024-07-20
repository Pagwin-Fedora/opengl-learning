#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <functional>
namespace pog {
    class VertexBuffer{
        GLuint id;
        bool moved;
        public:
        VertexBuffer(void* data, std::size_t size, GLenum usage);
        VertexBuffer(VertexBuffer&& rhs);
        VertexBuffer(VertexBuffer&) = delete;
        ~VertexBuffer();
        GLuint get_id();
    };
    class VertexArray{
        GLuint id;
        bool moved;
        public:
        VertexArray(std::function<void()> within_array);
        VertexArray(VertexArray&& rhs);
        VertexArray(VertexBuffer&) = delete;
        ~VertexArray();
        void use(std::function<void()> ops);
    };
}
