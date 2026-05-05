#include "Random/Renderer/Graphics/OrthographicCamera.hpp"

#include <glm/ext.hpp>

namespace Rand
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : Camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
    {
    }

    void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
    {
        setOrthoProjection(left, right, bottom, top);
    }
} // namespace Rand
