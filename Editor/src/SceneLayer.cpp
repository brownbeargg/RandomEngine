#include "SceneLayer.hpp"

namespace Rand
{
    void SceneLayer::onAttach()
    {
        FramebufferSpecification fbSpec{
            .Width = m_App.getWindow()->getWidth(), .Height = m_App.getWindow()->getHeight()};
        m_SceneFBO = Framebuffer::Create(fbSpec);

        m_CameraController = new OrthographicCameraController(
            (float)m_App.getWindow()->getWidth() / (float)m_App.getWindow()->getHeight(), m_App.getInput());
        m_CameraController->setZoomLevel(15.0f);
    }

    void SceneLayer::onUpdate(float deltaTime)
    {
        m_CameraController->onUpdate(deltaTime);

        m_SceneFBO->bind();
        RenderCommand::clearColor({0.2f, 0.2f, 0.2f, 1.0f});
        RenderCommand::clear();

        constexpr uint32_t QuadCount = 150;

        Rand::Profiler::Timer renderer2DTimer("SceneLayer::onUpdate rendering");
        Rand::Renderer2D::beginScene(&m_CameraController->getCamera());
        {
            for (uint32_t y{}; y < QuadCount; ++y)
                for (uint32_t x{}; x < QuadCount; ++x)
                {
                    glm::vec3 pos = glm::vec3(x / 2.0f, y / 2.0f, 0.0f);
                    glm::vec2 scale = glm::vec2(0.45f, 0.45f);
                    glm::vec4 color(x / (float)QuadCount, 0.0f, y / (float)QuadCount, 0.5f);

                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
                        glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
                    Rand::Renderer2D::drawQuad(transform, color);
                }
        }
        Rand::Renderer2D::endScene();
        m_App.pushProfileResult(renderer2DTimer.stop());
        m_SceneFBO->unbind();
    }

    void SceneLayer::onImGuiRender()
    {
        ImGui::DockSpaceOverViewport();

        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                const_cast<Application&>(m_App).close();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Scene");
        const ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
        {
            m_SceneFBO->resize(viewportPanelSize.x, viewportPanelSize.y);
            m_ViewportSize = viewportPanelSize;
        }
        ImGui::Image(m_SceneFBO->getColorAttachmentRendererID(),m_ViewportSize, {0, 1}, {1,0} );
        ImGui::End();
        ImGui::PopStyleVar();

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

    void SceneLayer::onEvent(Event& e)
    {
        m_CameraController->onEvent(e);
    }
} // namespace Rand
