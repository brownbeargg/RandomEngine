#include "Random/Renderer/RenderCommand.hpp"

namespace Rand
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
