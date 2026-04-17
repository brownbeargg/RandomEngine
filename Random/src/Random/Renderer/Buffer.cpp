#include "Random/Renderer/Buffer.hpp"

#include "Platform/OpenGL/OpenGLBuffer.hpp"

#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    void BufferLayout::calculateOffsetAndStride()
    {
        uint32_t offset = 0;
        m_Stride = 0;

        for (BufferElement& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::None:
            RAND_CORE_ASSERT(false, "No RendererAPI");

        case RendererAPI::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }

        RAND_CORE_ASSERT(false, "Unknown rendererAPI");
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::None:
            RAND_CORE_ASSERT(false, "No RendererAPI");

        case RendererAPI::OpenGL:
            return new OpenGLIndexBuffer(indices, count);
        }

        RAND_CORE_ASSERT(false, "Unknown rendererAPI");
    }
} // namespace Rand
