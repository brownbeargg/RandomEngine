#include "Platform/Windows/WindowsWindow.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

#include "Random/Debug/Instrumentor.hpp"
#include "Random/Events/ApplicationEvent.hpp"
#include "Random/Events/KeyEvent.hpp"
#include "Random/Events/MouseEvent.hpp"

#include <glad/glad.h>

namespace Rand
{
    static bool isGLFWInitialized = false;

    Window* Window::create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        close();
    }

    void WindowsWindow::onUpdate()
    {
        m_Context->swapBuffers();
        glfwPollEvents();
    }

    void WindowsWindow::init(const WindowProps& props)
    {
        RAND_PROFILE_FUNCTION();

        if (!isGLFWInitialized)
        {
            int glfwInitStatus = glfwInit();
            RAND_CORE_RELEASE_ASSERT(glfwInitStatus, "Failed to initialize GLFW");

            isGLFWInitialized = glfwInitStatus;
        }

        m_Data.Props = props;

        glfwWindowHint(GLFW_DECORATED, props.HasTitleBar ? GLFW_TRUE : GLFW_FALSE);

        m_Window =
            glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        setVSync(true);

        m_Context = new OpenGLContext(m_Window);
        m_Context->init();

        m_Data.Monitor = getMonitor();

        if (!props.XPos || props.YPos)
        {
            m_Data.Props.XPos = (m_Data.VidMode->width - m_Data.Props.Width) / 2;
            m_Data.Props.YPos = (m_Data.VidMode->height - m_Data.Props.Height) / 2;
        }

        glfwSetWindowPos(m_Window, m_Data.Props.XPos, m_Data.Props.YPos);
        setEventCallbacks();
    }

    void WindowsWindow::close()
    {
        RAND_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    GLFWmonitor* WindowsWindow::getMonitor()
    {
        RAND_PROFILE_FUNCTION();

        int count;
        GLFWmonitor** monitors = glfwGetMonitors(&count);

        for (int i{}; i < count; i++)
        {
            int monitorX, monitorY;
            glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

            m_Data.VidMode = const_cast<GLFWvidmode*>(glfwGetVideoMode(monitors[i]));

            // clang-format off
            if (m_Data.Props.XPos >= monitorX && m_Data.Props.XPos < monitorX + m_Data.VidMode->width &&
                m_Data.Props.YPos >= monitorY && m_Data.Props.YPos < monitorY + m_Data.VidMode->height)
                // clang-format on
                return monitors[i];
        }

        return glfwGetPrimaryMonitor();
    }

    void WindowsWindow::setEventCallbacks()
    {
        glfwSetErrorCallback([](int error, const char* description)
        { RAND_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description); });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data->EventCallback(event);
                    break;
                }
            case GLFW_REPEAT:

                {
                    KeyPressedEvent event(key, 1);
                    data->EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data->EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data->EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data->EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event(xPos, yPos);
            data->EventCallback(event);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(xOffset, yOffset);
            data->EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowCloseEvent event;
            data->EventCallback(event);
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowResizeEvent event(width, height);
            data->EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data->Props.Focus = focused;

            if (focused)
            {
                WindowFocusEvent event;
                data->EventCallback(event);
            }
            else
            {
                WindowLostFocusEvent event;
                data->EventCallback(event);
            }
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos)
        {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowMovedEvent event(xPos, yPos);
            data->EventCallback(event);
        });
    }
} // namespace Rand
