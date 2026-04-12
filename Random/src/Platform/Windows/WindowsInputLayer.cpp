#include "Random/Core/Application.hpp"
#include "Random/Layers/InputLayer.hpp"

#include <GLFW/glfw3.h>

namespace Rand
{
    bool InputLayer::isKeyPressed(const int key) const
    {
        int state = glfwGetKey(static_cast<GLFWwindow*>(m_App.getWindow().getNativeWindow()), key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputLayer::isMouseButtonPressed(const int button) const
    {
        int state = glfwGetMouseButton(static_cast<GLFWwindow*>(m_App.getWindow().getNativeWindow()), button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    std::pair<float, float> InputLayer::getMousePos() const
    {
        double xPos, yPos;
        glfwGetCursorPos(static_cast<GLFWwindow*>(m_App.getWindow().getNativeWindow()), &xPos, &yPos);
        return std::make_pair(xPos, yPos);
    }
} // namespace Rand
