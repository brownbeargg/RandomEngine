#pragma once

#include "Random/Core/Memory/RefCount.hpp"
#include "Random/Renderer/Graphics/camera.hpp"

#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace Rand
{
    class OrthographicCamera final : public Camera
    {
      public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void setProjection(float left, float right, float bottom, float top);
    };
} // namespace Rand
