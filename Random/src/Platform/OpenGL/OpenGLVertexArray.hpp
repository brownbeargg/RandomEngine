#pragma once

#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Buffer/VertexArray.hpp"

namespace Rand
{
    class OpenGLVertexArray final : public VertexArray
    {
      public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() {}

        void bind() const override { glBindVertexArray(m_RendererID); }
        void unBind() const override { glBindVertexArray(0); }

        const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
        void addVertexBuffer(const Ref<VertexBuffer> vertexBuffer) override;

        const Ref<IndexBuffer>& getIndexBuffer() const override { return m_IndexBuffer; }
        void setIndexBuffer(const Ref<IndexBuffer> indexBuffer) override;

      private:
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;

        uint32_t m_RendererID;
    };
} // namespace Rand
