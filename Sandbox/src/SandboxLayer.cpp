#include "SandboxLayer.hpp"

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

    Rand::Profiler::Timer render2DTextureTimer("SandboxLayer::onUpdate rendering 2D textures");
    Rand::Profiler::Timer render2DGeometryTimer("SandboxLayer::onUpdate rendering 2D colors");
    Rand::Renderer2D::beginScene(&m_Camera->getCamera());
    {
        glm::vec2 scale(0.4f, 0.4f);

        for (uint32_t y{}; y < 100; ++y)
            for (uint32_t x{}; x < 100; ++x)
            {
                glm::vec3 pos(x / 2.0f, y / 2.0f, 0.0f);
                glm::vec4 color(x / 100.0f, 0.0f, y / 100.0f, 1.0f);
                glm::mat4 rotation =
                    glm::rotate(glm::mat4(1.0f), glm::radians(20.0f * x), glm::vec3(0.0f, 0.0f, 1.0f));

                glm::mat4 transform =
                    glm::translate(glm::mat4(1.0f), pos) * glm::scale(rotation, glm::vec3(scale, 1.0f));
                Rand::Renderer2D::drawQuad(transform, color);
            }

        Rand::Renderer2D::nextBatch();
        m_App.pushProfileResult(render2DGeometryTimer.stop());
        render2DTextureTimer.start();

        scale = glm::vec2(0.2f, 0.2f);

        for (uint32_t y{}; y < 100; ++y)
        {
            for (uint32_t x{}; x < 100; ++x)
            {
                glm::vec3 pos(x / 2.0f, y / 2.0f, 0.1f);
                glm::vec4 color(x / 100.0f, 0.0f, y / 100.0f, 1.0f);
                glm::mat4 rotation =
                    glm::rotate(glm::mat4(1.0f), glm::radians(20.0f * x), glm::vec3(0.0f, 0.0f, 1.0f));

                glm::mat4 transform =
                    glm::translate(glm::mat4(1.0f), pos) * glm::scale(rotation, glm::vec3(scale, 1.0f));

                Rand::Renderer2D::drawQuad(transform, m_GrassTexture);
                pos.x += 0.1;
                transform =
                    glm::translate(glm::mat4(1.0f), pos) * glm::scale(rotation, glm::vec3(scale, 1.0f));

                Rand::Renderer2D::drawQuad(transform, m_TreeTexture);
            }
        }
    }
    Rand::Renderer2D::endScene();
    m_App.pushProfileResult(render2DTextureTimer.stop());
}

void SandboxLayer::onEvent(Rand::Event& event)
{
    m_Camera->onEvent(event);
}
