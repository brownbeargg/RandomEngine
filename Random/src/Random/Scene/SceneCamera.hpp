#pragma once

#include "Random/Renderer/Graphics/camera.hpp"

namespace Rand
{
    class SceneCamera final : public Camera
    {
      public:
        SceneCamera(const glm::mat4& projection);
        SceneCamera() = default;
        ~SceneCamera() = default;

        void setOrtho(float size, float near, float far);

        void setViewportSize(uint32_t width, uint32_t height);

        float getOrthoSize() const { return m_OrthoSize; }
        void setOrthoSize(float size);

        float getAspectRatio() { return m_AspectRatio; }

      private:
        void calculateProjectionMatrix();

      private:
        float m_OrthoSize{};
        float m_OrthoNear = -1.0f, m_OrthoFar = 1.0f;

        float m_AspectRatio{};
    };
} // namespace Rand
