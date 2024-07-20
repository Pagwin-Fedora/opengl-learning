#include "fmt/base.h"
#include <cstddef>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <pog/vertex_helpers.h>

pog::VertexBuffer::VertexBuffer(){
    moved = true;
}
pog::VertexBuffer::VertexBuffer(void* data, std::size_t size, GLenum usage){
    glGenBuffers(1, &id);
    moved = false;
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}
pog::VertexBuffer::VertexBuffer(VertexBuffer&& rhs):VertexArrayState(){
    id = rhs.id;
    moved = false;
    rhs.moved = true;
    fmt::println("Buffer moved");
}
pog::VertexBuffer& pog::VertexBuffer::operator=(VertexBuffer&& rhs){
    this->id = rhs.id;
    rhs.moved = true;
    this->moved = false;
    fmt::println("Buffer moved");
    return *this;
}
pog::VertexBuffer::~VertexBuffer(){
    fmt::println("Buffer {} moved? {} destructor", this->id, this->moved);
    if(!moved) glDeleteBuffers(1, &id);
}
GLuint pog::VertexBuffer::get_id(){
    return id;
}

pog::VertexArray::VertexArray(std::function<void(std::vector<std::unique_ptr<VertexArrayState>>&)> within_array):state{}{
    glGenVertexArrays(1, &id);
    moved = false;
    glBindVertexArray(id);
    within_array(state);
}
pog::VertexArray::VertexArray(VertexArray&& rhs){
    id = rhs.id;
    moved = false;
    rhs.moved = true;
}
pog::VertexArray& pog::VertexArray::operator=(VertexArray&& rhs){
    this->id = rhs.id;
    rhs.moved = true;
    this->moved = false;
    return *this;
}
pog::VertexArray::~VertexArray(){
    if(!moved) glDeleteBuffers(1, &id);
}
void pog::VertexArray::use(std::function<void(std::vector<std::unique_ptr<VertexArrayState>>&)> ops){
    glBindVertexArray(id);
    ops(this->state);
}
