#include "Platform/Windows/WindowsWindow.hpp"

#include "Random/Core.hpp"

namespace Rand
{
    static bool isGLFWInitialized = false;

    Window* Window::create(const WindowProps& props) { return new WindowsWindow(props); }

    WindowsWindow::WindowsWindow(const WindowProps& props) { init(props); }

    WindowsWindow::~WindowsWindow() { shutdown(); }

    void WindowsWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::init(const WindowProps& props)
    {
        if (!isGLFWInitialized)
        {
            int succes = glfwInit();
            RAND_CORE_ASSERT(succes, "Failed to initialize GLFW");

            isGLFWInitialized = succes;
        }

        m_Data.Props = props;

        m_Window = glfwCreateWindow((int)m_Data.Props.Width, (int)m_Data.Props.Height, m_Data.Props.Title.c_str(),
                                    nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        setVSync(true);

        m_Data.Monitor = getMonitor();

        if (!m_Data.Props.XPos || m_Data.Props.YPos)
        {
            m_Data.Props.XPos = (m_Data.VidMode->width - m_Data.Props.Width) / 2;
            m_Data.Props.YPos = (m_Data.VidMode->height - m_Data.Props.Height) / 2;
        }

        glfwSetWindowPos(m_Window, m_Data.Props.XPos, m_Data.Props.YPos);

        RAND_CORE_INFO("CREATING WINDOW {0} {1} by {2} pixels, at {3}, {4}", props.Title, props.Width, props.Height,
                       m_Data.Props.XPos, m_Data.Props.YPos);
    }

    void WindowsWindow::shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    GLFWmonitor* WindowsWindow::getMonitor()
    {
        int           count;
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

} // namespace Rand
