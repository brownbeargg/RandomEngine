#include "Random/Renderer/Buffer/Buffer.hpp"

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

    VertexBuffer* VertexBuffer::create(uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:
            RAND_CORE_RELEASE_ASSERT(false, "No RendererAPI");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(size);
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown rendererAPI");
    }

    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:
            RAND_CORE_RELEASE_ASSERT(false, "No RendererAPI");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown rendererAPI");
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:
            RAND_CORE_RELEASE_ASSERT(false, "No RendererAPI");

        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, count);
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown rendererAPI");
    }
} // namespace Rand
