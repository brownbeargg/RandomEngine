#include "Platform/OpenGL/OpenGLContext.hpp"

#include "Random/Core/Assert.hpp"
#include "Random/Debug/Instrumentor.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rand
{
    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
    {
        RAND_CORE_RELEASE_ASSERT(window, "Window is null");
    }

    void OpenGLContext::init()
    {
        RAND_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_Window);
        int gladLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RAND_CORE_RELEASE_ASSERT(gladLoadStatus, "Failed to initialize glad");

        int versionMajor{}, versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
        RAND_CORE_RELEASE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
            "Random requires at least OpenGL version 4.5");
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
} // namespace Rand
