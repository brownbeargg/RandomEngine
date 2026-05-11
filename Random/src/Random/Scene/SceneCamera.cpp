#include "Random/Scene/SceneCamera.hpp"

#include "glm/ext.hpp"

namespace Rand
{
    SceneCamera::SceneCamera(const glm::mat4& projection) : Camera(projection)
    {
        calculateProjectionMatrix();
    }

    void SceneCamera::setOrtho(float size, float near, float far)
    {
        m_OrthoSize = size;
        m_OrthoNear = near;
        m_OrthoFar = far;
        calculateProjectionMatrix();
    }

    void SceneCamera::setViewportSize(uint32_t width, uint32_t height)
    {
        if (height == 0)
            return;

        m_AspectRatio = (float)width / (float)height;
        calculateProjectionMatrix();
    }

    void SceneCamera::calculateProjectionMatrix()
    {
        float orthoRight = m_OrthoSize * m_AspectRatio * 0.5f;
        float orthoTop = m_OrthoSize * 0.5f;

        m_ProjectionMatrix =
            glm::ortho(-orthoRight, orthoRight, -orthoTop, orthoTop, m_OrthoNear, m_OrthoFar);
    }

    void SceneCamera::setOrthoSize(float size)
    {
        m_OrthoSize = size;
        calculateProjectionMatrix();
    }
} // namespace Rand
