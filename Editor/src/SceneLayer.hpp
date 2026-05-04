#pragma once

#include <Random.hpp>

namespace Rand
{
    class SceneLayer : public Layer
    {
      public:
        SceneLayer(Rand::Application& app) : Rand::Layer("SceneLayer", app) {}
        ~SceneLayer() {}

        void onAttach() override;
        void onUpdate(float deltaTime) override;
        void onImGuiRender() override;
        void onEvent(Event& e) override;

      private:
        Ref<OrthographicCameraController> m_CameraController;

        Ref<Framebuffer> m_SceneFBO;
        ImVec2 m_ViewportSize = {0, 0};
    };
} // namespace Rand
