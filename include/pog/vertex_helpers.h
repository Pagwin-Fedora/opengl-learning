#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <functional>
#include <memory>
#include <variant>
#include <vector>
namespace pog {
    // class that only exists so the VAO can own buffers and what not
    class VertexBuffer{
        GLuint id;
        bool moved;
        public:
        VertexBuffer();
        VertexBuffer(void* data, std::size_t size, GLenum usage);
        VertexBuffer(VertexBuffer&& rhs);
        VertexBuffer& operator=(VertexBuffer&& rhs);
        VertexBuffer(VertexBuffer&) = delete;
        VertexBuffer operator=(VertexBuffer&) = delete;
        ~VertexBuffer();
        GLuint get_id();
    };
    using VertexArrayState = std::variant<VertexBuffer>;
    class VertexArray{
        GLuint id;
        bool moved;
        std::vector<VertexArrayState> state;
        public:
        VertexArray(std::function<void(std::vector<VertexArrayState>&)> initialize_state);
        VertexArray(VertexArray&& rhs);
        VertexArray& operator=(VertexArray&& rhs);
        VertexArray(VertexBuffer&) = delete;
        VertexBuffer operator=(VertexBuffer&) = delete;
        ~VertexArray();
        void use(std::function<void(std::vector<VertexArrayState>&)> ops);
    };
}
