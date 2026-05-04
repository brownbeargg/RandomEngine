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

      private:
        Ref<Framebuffer> m_FBO;
    };
} // namespace Rand
