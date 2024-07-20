#include <cstddef>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <pog/vertex_helpers.h>

pog::VertexBuffer::VertexBuffer(void* data, std::size_t size, GLenum usage){
    glGenBuffers(1, &id);
    moved = false;
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}
pog::VertexBuffer::VertexBuffer(VertexBuffer&& rhs){
    id = rhs.id;
    moved = false;
    rhs.moved = true;
}
pog::VertexBuffer::~VertexBuffer(){
    if(!moved) glDeleteBuffers(1, &id);
}
GLuint pog::VertexBuffer::get_id(){
    return id;
}

pog::VertexArray::VertexArray(std::function<void()> within_array){
    glGenVertexArrays(1, &id);
    moved = false;
    glBindVertexArray(id);
    within_array();
}
pog::VertexArray::VertexArray(VertexArray&& rhs){
    id = rhs.id;
    moved = false;
    rhs.moved = true;
}
pog::VertexArray::~VertexArray(){
    if(!moved) glDeleteBuffers(1, &id);
}
void pog::VertexArray::use(std::function<void()> ops){
    glBindVertexArray(id);
    ops();
}
