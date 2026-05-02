#include "Random/Renderer/Graphics/Texture.hpp"

#include "Platform/OpenGL/OpenGLTexture.hpp"

#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    Texture2D* Texture2D::create(uint32_t width, uint32_t height)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:

            RAND_CORE_RELEASE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLTexture2D(width, height);
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }

    Texture2D* Texture2D::create(const std::string& path)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:
            RAND_CORE_RELEASE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLTexture2D(path);
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }
} // namespace Rand
