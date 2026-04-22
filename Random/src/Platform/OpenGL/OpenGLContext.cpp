#include "Platform/OpenGL/OpenGLContext.hpp"

#include "Random/Core/Assert.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rand
{
    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
    {
        RAND_CORE_RELEASE_ASSERT(window, "Window handle is null");
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(m_Window);
        int gladLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RAND_CORE_RELEASE_ASSERT(gladLoadStatus, "Failed to initialize glad");
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
} // namespace Rand
