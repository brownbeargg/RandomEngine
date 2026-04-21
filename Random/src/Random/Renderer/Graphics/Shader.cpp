#include "Random/Renderer/Graphics/Shader.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"
#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:
            RAND_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        RAND_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Rand
