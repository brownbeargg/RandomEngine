#include "Random/Core/DeltaTime.hpp"

#include <GLFW/glfw3.h>

namespace Rand
{
    void DeltaTime::recalculate(float& lastTime)
    {
        float current = glfwGetTime();
        m_Time = current - lastTime;
        lastTime = current;
    }
} // namespace Rand
