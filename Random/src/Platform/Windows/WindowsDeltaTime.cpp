#include "Random/Core/DeltaTime.hpp"
#include "Random/Debug/Instrumentor.hpp"

#include <GLFW/glfw3.h>

namespace Rand
{
    void DeltaTime::recalculate(float& lastTime)
    {
        RAND_PROFILE_FUNCTION();

        float current = glfwGetTime();
        m_Time = current - lastTime;
        lastTime = current;
    }
} // namespace Rand
