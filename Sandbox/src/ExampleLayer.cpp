#include "ExampleLayer.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app)
    : Layer("SandboxLayer", app),
      m_Camera(new Rand::OrthographicCameraController(
          (float)m_App.getWindow()->getWidth() / (float)m_App.getWindow()->getHeight(), m_App.getInput()))
{
    RAND_PROFILE_FUNCTION();

    m_GrassTexture = Rand::Texture2D::create("Assets/Textures/Grass.png");
    m_TreeTexture = Rand::Texture2D::create("Assets/Textures/Tree.png");
}

void SandboxLayer::onUpdate(float deltaTime)
{
    RAND_PROFILE_FUNCTION();

    Rand::RenderCommand::clearColor({0.1, 0.1, 0.1, 1.0});
    Rand::RenderCommand::clear();

    m_Camera->onUpdate(deltaTime);

    Rand::Renderer2D::beginScene(&m_Camera->getCamera());
    {
        Rand::Profiler::Timer render2DGeometryTimer("SandboxLayer::onUpdate rendering 2D colors");

        glm::vec2 scale(0.4f, 0.4f);
        glm::mat4 rotation(1.0f);

        for (uint32_t y{}; y < 100; ++y)
            for (uint32_t x{}; x < 100; ++x)
            {
                glm::vec3 pos(x / 2.0f, y / 2.0f, 0.0f);
                glm::vec4 color(x / 100.0f, 0.0f, y / 100.0f, 1.0f);
                Rand::Renderer2D::drawQuad(pos, scale, rotation, color);
            }

        Rand::Renderer2D::flush();
        m_App.pushProfileResult(render2DGeometryTimer.stop());

        Rand::Profiler::Timer render2DTextureTimer("SandboxLayer::onUpdate rendering 2D textures");

        scale = glm::vec2(0.2f, 0.2f);

        for (uint32_t y{}; y < 100; ++y)
            for (uint32_t x{}; x < 100; ++x)
            {
                glm::vec3 pos(x / 2.0f, y / 2.0f, 0.0f);
                Rand::Renderer2D::drawQuad(pos, m_GrassTexture, 1.0f, glm::vec4(10.0f), scale);
            }
        m_App.pushProfileResult(render2DTextureTimer.stop());
    }
    Rand::Renderer2D::endScene();
}

void SandboxLayer::onEvent(Rand::Event& event)
{
    m_Camera->onEvent(event);
}
