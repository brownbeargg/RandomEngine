#pragma once

#include "Random/Core/Ref.hpp"

#include <glm/glm.hpp>

namespace Rand
{
    class OrthographicCamera : public RefCount
    {
      public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& getPosition() const { return m_Position; }

        void setPosition(const glm::vec3& position)
        {
            m_Position = position;
            calculateViewMatrix();
        }

        const glm::vec3& getRotation() const { return m_Rotation; }

        void setRotation(const glm::vec3& rotation)
        {
            m_Rotation = rotation;
            calculateViewMatrix();
        }

        const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

      private:
        void calculateViewMatrix();

      private:
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position{};
        glm::vec3 m_Rotation{};
    };
} // namespace Rand
