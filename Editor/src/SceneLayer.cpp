#include "SceneLayer.hpp"

namespace Rand
{
    void SceneLayer::onAttach()
    {
        FramebufferSpecification fbSpec{
            .Width = m_App.getWindow()->getWidth(), .Height = m_App.getWindow()->getHeight()};
        m_FBO = Framebuffer::Create(fbSpec);
    }

    void SceneLayer::onUpdate(float deltaTime)
    {
        m_FBO->bind();
        RenderCommand::clearColor({0.2f, 0.2f, 0.2f, 1.0f});
        RenderCommand::clear();

        m_FBO->unbind();
    }
} // namespace Rand
