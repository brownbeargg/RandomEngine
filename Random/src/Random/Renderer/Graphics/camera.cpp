#include "Random/Renderer/Graphics/camera.hpp"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace Rand
{
    Camera::Camera()
        : m_ProjectionMatrix(glm::mat4(1.0f)), m_ViewProjectionMatrix(m_ViewMatrix * m_ProjectionMatrix)
    {
    }

    void Camera::setOrthoProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    }

    void Camera::calculateOrthoViewMatrix()
    {
        glm::mat4 rotationMatrix =
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * rotationMatrix;

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
} // namespace Rand
