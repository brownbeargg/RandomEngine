#include "Random/Core/App/Input.hpp"

#include "Random/Core/App/Window.hpp"

#include <GLFW/glfw3.h>

namespace Rand
{
    bool Input::isKeyPressed(const int key) const
    {
        int state =
            glfwGetKey(const_cast<GLFWwindow*>(static_cast<const GLFWwindow*>(m_Window->getNativeWindow())), key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(const int button) const
    {
        int state = glfwGetMouseButton(
            const_cast<GLFWwindow*>(static_cast<const GLFWwindow*>(m_Window->getNativeWindow())), button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    glm::vec2 Input::getMousePos() const
    {
        double xPos, yPos;
        glfwGetCursorPos(
            const_cast<GLFWwindow*>(static_cast<const GLFWwindow*>(m_Window->getNativeWindow())), &xPos, &yPos);
        return glm::vec2(xPos, yPos);
    }
} // namespace Rand
