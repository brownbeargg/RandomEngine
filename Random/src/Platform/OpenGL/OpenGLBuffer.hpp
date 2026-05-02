#include "Random/Debug/Instrumentor.hpp"
#include "Random/Renderer/Buffer/Buffer.hpp"

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

        void bind() const override { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
        void unbind() const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }

        const BufferLayout& getLayout() const override { return m_Layout; }
        void setLayout(const BufferLayout& layout) override { m_Layout = layout; }

        void setData(float* vertices, uint32_t size) override
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
        }

      private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
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
            RAND_PROFILE_FUNCTION();

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

            m_Count = count;
        }

        void bind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
        void unbind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

        uint32_t getCount() const override { return m_Count; }

      private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
} // namespace Rand
