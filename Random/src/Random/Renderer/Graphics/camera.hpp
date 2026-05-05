#pragma once

#include "Random/Core/Memory/RefCount.hpp"

#include "glm/glm.hpp"

namespace Rand
{
    /**
     * @todo Camera::setPerspective | Camera::setOrtho
     */
    class Camera : public RefCount
    {
      public:
        Camera()
            : m_ProjectionMatrix(glm::mat4(1.0f)), m_ViewProjectionMatrix(m_ViewMatrix * m_ProjectionMatrix)
        {
        }
        Camera(const glm::mat4& projectionMatrix) : m_ProjectionMatrix(projectionMatrix) {}

        const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

        void setOrthoProjection(float left, float right, float bottom, float top);

        const glm::vec3& getPosition() const { return m_Position; }
        void setPosition(const glm::vec3& position);

        const glm::vec3& getRotation() const { return m_Rotation; }
        void setRotation(const glm::vec3& rotation);

      protected:
        void calculateOrthoViewMatrix();

      protected:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position{};
        glm::vec3 m_Rotation{};
    };
} // namespace Rand
