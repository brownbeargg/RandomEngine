#pragma once

#include "Random/Renderer/Buffer/Framebuffer.hpp"

#include "glad/glad.h"

namespace Rand
{
    class OpenGLFrameBuffer final : public Framebuffer
    {
      public:
        OpenGLFrameBuffer(const FramebufferSpecification& spec);
        ~OpenGLFrameBuffer();

        void invalidate();

        void bind() const override
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
            glViewport(0, 0, m_Spec.Width, m_Spec.Height);
        }

        void unbind() const override { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

        void resize(uint32_t width, uint32_t height) override;

        const FramebufferSpecification& getSpecification() const override { return m_Spec; }
        uint32_t getColorAttachmentRendererID() const override { return m_ColorAttachment; }

      private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
        FramebufferSpecification m_Spec;
    };
} // namespace Rand
