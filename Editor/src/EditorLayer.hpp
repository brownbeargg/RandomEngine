#pragma once

#include <Random.hpp>

namespace Rand
{
    class EditorLayer : public Layer
    {
      public:
        EditorLayer(Rand::Application& app) : Rand::Layer("SceneLayer", app) {}
        ~EditorLayer() {}

        void onAttach() override;
        void onUpdate(float deltaTime) override;
        void onImGuiRender() override;
        void onEvent(Event& e) override;

      private:
        Ref<OrthographicCameraController> m_CameraController;

        Ref<Framebuffer> m_SceneFBO;
        ImVec2 m_ViewportSize = {0, 0};
        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;

        Ref<Scene> m_ActiveScene;
    };
} // namespace Rand
