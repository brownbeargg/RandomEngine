#include "Random/Renderer/Buffer/Framebuffer.hpp"

#include "Platform/OpenGL/OpenGLFramebuffer.hpp"

#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    Framebuffer* Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:
            RAND_CORE_RELEASE_ASSERT(false, "Random doesn't support using no renderer API");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLFrameBuffer(spec);

            RAND_CORE_RELEASE_ASSERT(false, "Unknown Renderer API");
            return nullptr;
        }
    }
} // namespace Rand
