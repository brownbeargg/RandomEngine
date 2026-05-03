#pragma once

#include "Random/Core/App/Input.hpp"
#include "Random/Core/Memory/Ref.hpp"

#include "Random/Events/ApplicationEvent.hpp"
#include "Random/Events/MouseEvent.hpp"

#include "Random/Renderer/Graphics/OrthographicCamera.hpp"

namespace Rand
{
    class OrthographicCameraController : public RefCount
    {
      public:
        float MoveSpeed = 3;
        float RotationSpeed = 180;
        float ZoomStrength = 0.2;

      public:
        OrthographicCameraController(float aspectRatio, const Ref<Input>& input);

        void onUpdate(float deltaTime);
        void onEvent(Event& e);

        OrthographicCamera& getCamera() { return m_Camera; }

        void setZoomLevel(float zoomLevel)
        {
            m_ZoomLevel = std::max(zoomLevel, 0.01f);
            m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
        }

      private:
        bool onMouseScroll(MouseScrolledEvent& e);
        bool onWindowResize(WindowResizeEvent& e);

      private:
        float m_AspectRatio{};
        float m_ZoomLevel = 1;

        Ref<Input> m_Input{};
        OrthographicCamera m_Camera;
    };
} // namespace Rand
