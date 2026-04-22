#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::init()
    {
        RenderCommand::init();
    }
} // namespace Rand
