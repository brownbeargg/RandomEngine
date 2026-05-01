#include "Random/Renderer/Renderer.hpp"

#include "Random/Renderer/Renderer2D.hpp"

namespace Rand
{
    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::init()
    {
        RenderCommand::init();
        Renderer2D::init();
    }

    void Renderer::shutdown()
    {
        Renderer2D::shutdown();
    }
} // namespace Rand
