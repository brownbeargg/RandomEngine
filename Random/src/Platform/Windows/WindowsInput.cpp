#include "Random/Core/App/Input.hpp"

#include "Platform/Windows/WindowsWindow.hpp"

#include <GLFW/glfw3.h>

namespace Rand
{
    bool Input::isKeyPressed(const Key key) const
    {
        int state = glfwGetKey(static_cast<const WindowsWindow*>(m_Window)->getWindowsWindow(), (int)key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(const Mouse button) const
    {
        int state = glfwGetMouseButton(static_cast<const WindowsWindow*>(m_Window)->getWindowsWindow(), (int)button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    glm::vec2 Input::getMousePos() const
    {
        double xPos, yPos;
        glfwGetCursorPos(static_cast<const WindowsWindow*>(m_Window)->getWindowsWindow(), &xPos, &yPos);
        return glm::vec2(xPos, yPos);
    }
} // namespace Rand
