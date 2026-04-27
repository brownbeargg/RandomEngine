#pragma once

#include "glm/glm.hpp"

namespace Rand
{
    class Camera
    {
        virtual const glm::mat4& getViewMatrix() const = 0;
        virtual const glm::mat4& getProjectionMatrix() const = 0;
        virtual const glm::mat4& getViewProjectionMatrix() const = 0;
    };
} // namespace Rand
