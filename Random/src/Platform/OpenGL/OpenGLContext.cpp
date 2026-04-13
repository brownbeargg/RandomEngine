#include "Platform/OpenGL/OpenGLContext.hpp"

#include "Random/Core/Core.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rand
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
    {
        RAND_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int gladLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RAND_CORE_ASSERT(gladLoadStatus, "Failed to initialize glad");
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);

        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
} // namespace Rand
