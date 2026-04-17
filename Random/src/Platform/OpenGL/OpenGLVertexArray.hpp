#pragma once

#include "Random/Renderer/VertexArray.hpp"

namespace Rand
{
    class OpenGLVertexArray final : public VertexArray
    {
      public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() {}

        void bind() const override { glBindVertexArray(m_RendererID); }
        void unBind() const override { glBindVertexArray(0); }

        const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

        const std::shared_ptr<IndexBuffer> getIndexBuffer() const override { return m_IndexBuffer; }
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

      private:
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

        uint32_t m_RendererID;
    };
} // namespace Rand
