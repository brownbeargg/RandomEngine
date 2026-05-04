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

        const FramebufferSpecification& getSpecification() const override { return m_Spec; }

        void bind() const override { glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID); }
        void unbind() const override { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

        uint32_t getColorAttachmentRendererID() const override { return m_ColorAttachment; }

      private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        FramebufferSpecification m_Spec;
    };
} // namespace Rand
