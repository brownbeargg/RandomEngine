#include "EditorLayer.hpp"

namespace Rand
{
    void EditorLayer::onAttach()
    {
        FramebufferSpecification fbSpec{
            .Width = m_App.getWindow()->getWidth(), .Height = m_App.getWindow()->getHeight()};
        m_SceneFBO = Framebuffer::Create(fbSpec);

        m_ActiveScene = new Scene;

        m_Camera = m_ActiveScene->createEntity("Camera");
        m_Camera.addComponent<TransformComponent>();

        CameraComponent& cameraComponent = m_Camera.addComponent<CameraComponent>();
        cameraComponent.Camera.setOrtho(10, -1, 1);
        cameraComponent.Camera.setViewportSize(fbSpec.Width, fbSpec.Height);
        m_ActiveScene->setPrimaryCamera(&m_Camera);

        constexpr uint32_t QuadCount = 100;

        for (uint32_t x{}; x < QuadCount; ++x)
            for (uint32_t y{}; y < QuadCount; ++y)
            {
                glm::vec3 pos = glm::vec3(x / 2.0f, y / 2.0f, 0.0f);
                glm::vec2 scale = glm::vec2(0.45f, 0.45f);
                glm::vec4 color(x / (float)QuadCount, 0.0f, y / (float)QuadCount, 0.5f);

                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));

                Entity quad = m_ActiveScene->createEntity("Quad");
                quad.addComponent<TransformComponent>(transform);
                quad.addComponent<SpriteRendererComponent>(color);
            }
    }

    void EditorLayer::onUpdate(float deltaTime)
    {
        {
            ///@todo make fbo resizable

            uint32_t viewportWidth = (uint32_t)m_ViewportSize.x;
            uint32_t viewportHeight = (uint32_t)m_ViewportSize.y;

            if (FramebufferSpecification spec = m_SceneFBO->getSpecification(); viewportWidth > 0 &&
                viewportHeight > 0 && (spec.Width != viewportWidth || spec.Height != viewportHeight))
            {
                m_SceneFBO->resize(viewportWidth, viewportHeight);
                m_ActiveScene->onViewportResize(viewportWidth, viewportHeight);
            }
        }

        m_SceneFBO->bind();
        RenderCommand::clearColor({0.2f, 0.2f, 0.2f, 1.0f});
        RenderCommand::clear();

        RAND_CORE_WARN("Aspect ratio = {}",
            m_ActiveScene->getPrimaryCamera()->getComponent<CameraComponent>().Camera.getAspectRatio());
        RAND_CORE_TRACE("viewportwidth: {}", m_ViewportSize.x);

        Profiler::Timer renderer2DTimer("SceneLayer::onUpdate rendering");
        Renderer2D::beginScene(m_ActiveScene->getPrimaryCamera()->getComponent<CameraComponent>().Camera);
        {
            m_ActiveScene->onUpdate();
        }
        Renderer2D::endScene();
        m_App.pushProfileResult(renderer2DTimer.stop());
        m_SceneFBO->unbind();
    }

    void EditorLayer::onImGuiRender()
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
        ImGui::Begin("Viewport");

        const ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if (viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
            m_ViewportSize = viewportPanelSize;

        ImGui::Image(m_SceneFBO->getColorAttachmentRendererID(), m_ViewportSize, {0, 1}, {1, 0});

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        ImGui::End();
        ImGui::PopStyleVar();

        Renderer2D::Statistics renderer2DStats = Renderer2D::getStats();
        Renderer2D::resetStats();

        ImGui::Begin("settings");
        ImGui::TextColored({0.8f, 0.2f, 0.2f, 1.0f}, "Renderer statistics");
        ImGui::Text("draw calls: %i", renderer2DStats.DrawCalls);
        ImGui::Text("quad count: %i", renderer2DStats.QuadCount);
        ImGui::Text("vertex count: %i", renderer2DStats.getTotalVertexCount());
        ImGui::Text("index count: %i", renderer2DStats.getTotalIndexCount());

        ImGui::End();
    }

    void EditorLayer::onEvent(Event& e) {}
} // namespace Rand
