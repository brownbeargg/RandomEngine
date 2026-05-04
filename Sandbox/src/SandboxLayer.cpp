#include "SandboxLayer.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app)
    : Layer("SandboxLayer", app),
      m_Camera(new Rand::OrthographicCameraController(
          (float)m_App.getWindow()->getWidth() / (float)m_App.getWindow()->getHeight(), m_App.getInput()))
{
    RAND_PROFILE_FUNCTION();
}

void SandboxLayer::onAttach()
{
    RAND_PROFILE_FUNCTION();

    m_Camera->setZoomLevel(15.0f);
    m_TileMap = Rand::Texture2D::create("Assets/Rpg/Spritesheet/RPGpack_sheet_2X.png");
    m_StairSubTexture = Rand::SubTexture2D::createFromCoords(m_TileMap, {7, 6}, {128, 128});
    m_BarrelSubTexture = Rand::SubTexture2D::createFromCoords(m_TileMap, {8, 2}, {128, 128});
    m_TreeSubTexture = Rand::SubTexture2D::createFromCoords(m_TileMap, {2, 1}, {128, 128}, {1, 2});

    Rand::FramebufferSpecification fbSpec = {
        .Width = m_App.getWindow()->getWidth(), .Height = m_App.getWindow()->getHeight()};
    m_FrameBuffer = Rand::Framebuffer::Create(fbSpec);
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
        constexpr uint32_t size = 250;

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

                if (x % 3 == 0)
                    Rand::Renderer2D::drawQuad(transform, m_TreeSubTexture);
                else if (x % 2 && y % 2)
                    Rand::Renderer2D::drawQuad(transform, m_StairSubTexture);
                else
                    Rand::Renderer2D::drawQuad(transform, m_BarrelSubTexture);

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

    ImGui::Begin("Info");
    ImGui::TextColored({0.8f, 0.2f, 0.2f, 1.0f}, "Renderer statistics");
    ImGui::Text("draw calls: %i", renderer2DStats.DrawCalls);
    ImGui::Text("quad count: %i", renderer2DStats.QuadCount);
    ImGui::Text("vertex count: %i", renderer2DStats.getTotalVertexCount());
    ImGui::Text("index count: %i", renderer2DStats.getTotalIndexCount());
    ImGui::End();
}
