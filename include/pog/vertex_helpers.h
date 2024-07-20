#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <functional>
#include <memory>
#include <vector>
namespace pog {
    // class that only exists so the VAO can own buffers and what not
    class VertexArrayState{
        public:
        VertexArrayState(){}
        virtual ~VertexArrayState(){};
        VertexArrayState(VertexArrayState&) = delete;
        VertexArrayState operator=(VertexArrayState&) = delete;
    };
    class VertexBuffer:public VertexArrayState{
        GLuint id;
        bool moved;
        public:
        VertexBuffer();
        VertexBuffer(void* data, std::size_t size, GLenum usage);
        VertexBuffer(VertexBuffer&& rhs);
        VertexBuffer& operator=(VertexBuffer&& rhs);
        VertexBuffer(VertexBuffer&) = delete;
        VertexBuffer operator=(VertexBuffer&) = delete;
        ~VertexBuffer() override;
        GLuint get_id();
    };
    VertexArrayState from_buffer(VertexBuffer);
    class VertexArray{
        GLuint id;
        bool moved;
        std::vector<std::unique_ptr<VertexArrayState>> state;
        public:
        VertexArray(std::function<void(std::vector<std::unique_ptr<VertexArrayState>>&)> initialize_state);
        VertexArray(VertexArray&& rhs);
        VertexArray& operator=(VertexArray&& rhs);
        VertexArray(VertexBuffer&) = delete;
        VertexBuffer operator=(VertexBuffer&) = delete;
        ~VertexArray();
        void use(std::function<void(std::vector<std::unique_ptr<VertexArrayState>>&)> ops);
    };
}
