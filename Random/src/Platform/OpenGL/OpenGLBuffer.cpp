#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Rand
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) : m_Layout({})
    {
        RAND_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID);
        setData(vertices, size);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
    {
        RAND_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID);
        setData(indices, count);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }
} // namespace Rand
