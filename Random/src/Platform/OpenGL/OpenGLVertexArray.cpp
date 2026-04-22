#include "Platform/OpenGL/OpenGLVertexArray.hpp"

#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Graphics/Shader.hpp"

namespace Rand
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer> vertexBuffer)
    {
        glBindVertexArray(m_RendererID);
        vertexBuffer->bind();

        BufferLayout layout = vertexBuffer->getLayout();
        RAND_CORE_RELEASE_ASSERT(layout.getElements().size(), "Vertex buffer has no elements");

        uint32_t index{};
        for (const BufferElement& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.getCount(), shaderDataTypeToGLDataType(element.Type),
                element.Normalized ? true : false, layout.getStride(), (const void*)element.Offset);
            ++index;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer> indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->bind();

        m_IndexBuffer = indexBuffer;
    }
} // namespace Rand
