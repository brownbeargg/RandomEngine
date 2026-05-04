#pragma once

#include "Random/Core/Memory/RefCount.hpp"

namespace Rand
{
    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class Framebuffer : public RefCount
    {
      public:
        virtual const FramebufferSpecification& getSpecification() const = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getColorAttachmentRendererID() const = 0;

        static Framebuffer* Create(const FramebufferSpecification& spec);
    };
} // namespace Rand
