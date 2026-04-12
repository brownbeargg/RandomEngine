#pragma once

#include "Random/Core/Window.hpp"

#include <GLFW/glfw3.h>

namespace Rand
{
    class WindowsWindow : public Window
    {
      private:
        struct WindowData
        {
            WindowProps Props{};
            GLFWmonitor* Monitor{};
            GLFWvidmode* VidMode{};
            bool VSync{};

            EventCallbackFn EventCallback = nullptr;
        };

      public:
        explicit WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void onUpdate() override;

        uint32_t getWidth() const override { return m_Data.Props.Width; }
        uint32_t getHeight() const override { return m_Data.Props.Height; }

        void setEventCallback(const EventCallbackFn& func) override { m_Data.EventCallback = func; };

        void setVSync(const bool enabled) override
        {
            m_Data.VSync = true;
            glfwSwapInterval(enabled);
        }

        bool isVSync() const override { return m_Data.VSync; }

        void* getNativeWindow() const override { return m_Window; }

      private:
        void init(const WindowProps& props);
        void shutdown();

        GLFWmonitor* getMonitor();
        void setEventCallbacks();

      private:
        GLFWwindow* m_Window;
        WindowData m_Data;
    };
} // namespace Rand
