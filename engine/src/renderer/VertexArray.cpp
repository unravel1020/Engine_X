#include "nebula/renderer/VertexArray.hpp"
#include <glad/glad.h>

namespace nebula
{

// 辅助函数：转换自定义类型到 OpenGL 类型
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    case ShaderDataType::Mat3:
        return GL_FLOAT;
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
        return GL_INT;
    case ShaderDataType::Int2:
        return GL_INT;
    case ShaderDataType::Int3:
        return GL_INT;
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    case ShaderDataType::None:
        break;
    }
    return 0;
}

VertexArray::VertexArray() { glGenVertexArrays(1, &m_RendererID); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_RendererID); }

void VertexArray::Bind() const { glBindVertexArray(m_RendererID); }

void VertexArray::Unbind() const { glBindVertexArray(0); }

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    // 这里的 GetLayout 现在可以被正常调用了
    const auto& layout = vertexBuffer->GetLayout();

    // 如果用户忘记设置 Layout，打印警告
    if (layout.GetElements().empty())
    {
        NEBULA_ERROR("Vertex Buffer has no layout!");
    }

    uint32_t index = 0;
    for (const auto& element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.GetComponentCount(), // 使用我们在 BufferElement 中新增的函数
                              ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(), (const void*)(uintptr_t)element.Offset);
        index++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
}

} // namespace nebula