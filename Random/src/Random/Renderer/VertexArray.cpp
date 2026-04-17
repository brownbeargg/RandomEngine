#include "Random/Renderer/VertexArray.hpp"

#include "Platform/OpenGL/OpenGLVertexArray.hpp"

#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    VertexArray* VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::None:
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexArray;
        }

        RAND_CORE_ASSERT(false, "Unknown render API")
    }
} // namespace Rand
