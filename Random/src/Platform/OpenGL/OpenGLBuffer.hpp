#include "Random/Renderer/Buffer.hpp"

#include "Random/Core/Core.hpp"

#include <glad/glad.h>

namespace Rand
{
    class OpenGLVertexBuffer final : public VertexBuffer
    {
      public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
        OpenGLVertexBuffer(OpenGLVertexBuffer&&) = delete;
        OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;
        OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&&) = delete;
        ~OpenGLVertexBuffer();

        void setData(float* vertices, uint32_t size) override
        {
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }

        void bind() const override { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
        void unbind() const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }

      private:
        uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer final : public IndexBuffer
    {
      public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;
        OpenGLIndexBuffer(OpenGLIndexBuffer&&) = delete;
        OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;
        OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&&) = delete;
        ~OpenGLIndexBuffer();

        void setData(uint32_t* indices, uint32_t count) override
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        }

        void bind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
        void unbind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

        uint32_t getCount() const override { return m_Count; }

      private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
} // namespace Rand
