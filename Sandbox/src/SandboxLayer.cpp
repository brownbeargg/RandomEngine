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

    Rand::Profiler::Timer renderer2DTimer("SandboxLayer::onUpdate rendering");
    Rand::Renderer2D::beginScene(&m_Camera->getCamera());
    {
        constexpr uint32_t size = 400;

        glm::mat4 bgTransform = glm::translate(glm::mat4(1.0f), glm::vec3(size / 2.0f, size / 2.0f, -0.2)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(size));
        Rand::Renderer2D::drawQuad(bgTransform, m_GrassTexture, size / 10.0f);

        glm::vec2 scale(0.4f, 0.4f);

        for (uint32_t y{}; y < size; ++y)
            for (uint32_t x{}; x < size; ++x)
            {
                scale = glm::vec2(0.2f, 0.2f);

                glm::vec3 pos = glm::vec3(x / 2.0f, y / 2.0f, 0.1f);

                glm::mat4 rotation =
                    glm::rotate(glm::mat4(1.0f), glm::radians(20.0f * x), glm::vec3(0.0f, 0.0f, 1.0f));

                glm::mat4 transform =
                    glm::translate(glm::mat4(1.0f), pos) * glm::scale(rotation, glm::vec3(scale, 1.0f));
                Rand::Renderer2D::drawQuad(transform, m_TreeTexture);

                pos = glm::vec3(x / 2.0f, y / 2.0f, 0.0f);
                scale = glm::vec2(0.45f, 0.45f);
                glm::vec4 color(x / (float)size, 0.0f, y / (float)size, 0.5f);

                transform =
                    glm::translate(glm::mat4(1.0f), pos) * glm::scale(rotation, glm::vec3(scale, 1.0f));
                Rand::Renderer2D::drawQuad(transform, color);
            }
    }
    Rand::Renderer2D::endScene();
    m_App.pushProfileResult(renderer2DTimer.stop());
}

void SandboxLayer::onEvent(Rand::Event& event)
{
    m_Camera->onEvent(event);
}

void SandboxLayer::onImGuiRender()
{
    Rand::Renderer2D::Statistics renderer2DStats = Rand::Renderer2D::getStats();
    Rand::Renderer2D::resetStats();

    ImGui::Begin("Renderer2D statistics");
    ImGui::Text("draw calls: %i", renderer2DStats.DrawCalls);
    ImGui::Text("quad count: %i", renderer2DStats.QuadCount);
    ImGui::Text("vertex count: %i", renderer2DStats.getTotalVertexCount());
    ImGui::Text("index count: %i", renderer2DStats.getTotalIndexCount());
    ImGui::End();
}
