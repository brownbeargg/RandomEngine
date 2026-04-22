#include "Random/Renderer/Buffer/VertexArray.hpp"

#include "Platform/OpenGL/OpenGLVertexArray.hpp"

#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    VertexArray* VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None:
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexArray;
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown render API");
    }
} // namespace Rand
