#include "Random/Renderer/Graphics/OrthographicCameraController.hpp"

#include "Random/Core/App/Input.hpp"

#include "Random/Events/ApplicationEvent.hpp"
#include "Random/Events/MouseEvent.hpp"

#include "RandomPch.hpp"

namespace Rand
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, const Ref<Input>& input)
        : m_AspectRatio(aspectRatio), m_Input(input),
          m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {
    }

    void OrthographicCameraController::onUpdate(float deltaTime)
    {
        if (m_Input->isKeyPressed(Key::W))
            m_Camera.setPosition(
                m_Camera.getPosition() + glm::vec3(0.0f, MoveSpeed * m_ZoomLevel * deltaTime, 0.0f));
        else if (m_Input->isKeyPressed(Key::S))
            m_Camera.setPosition(
                m_Camera.getPosition() + glm::vec3(0.0f, -MoveSpeed * m_ZoomLevel * deltaTime, 0.0f));
        if (m_Input->isKeyPressed(Key::A))
            m_Camera.setPosition(
                m_Camera.getPosition() + glm::vec3(-MoveSpeed * m_ZoomLevel * deltaTime, 0.0f, 0.0f));
        else if (m_Input->isKeyPressed(Key::D))
            m_Camera.setPosition(
                m_Camera.getPosition() + glm::vec3(MoveSpeed * m_ZoomLevel * deltaTime, 0.0f, 0.0f));

        if (m_Input->isKeyPressed(Key::Q))
            m_Camera.setRotation(m_Camera.getRotation() + glm::vec3(0, 0, RotationSpeed * deltaTime));
        else if (m_Input->isKeyPressed(Key::E))
            m_Camera.setRotation(m_Camera.getRotation() - glm::vec3(0, 0, RotationSpeed * deltaTime));
    }

    void OrthographicCameraController::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(
            RAND_BIND_EVENT_FN(OrthographicCameraController::onMouseScroll));
        dispatcher.dispatch<WindowResizeEvent>(
            RAND_BIND_EVENT_FN(OrthographicCameraController::onWindowResize));
    }

    bool OrthographicCameraController::onMouseScroll(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.getYOffset() * ZoomStrength;
        m_ZoomLevel = std::clamp(m_ZoomLevel, 0.01f, 30.0f);
        m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::onWindowResize(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.getWidth() / (float)e.getHeight();
        m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
} // namespace Rand
