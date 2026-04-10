#include "Random/Application.hpp"

#include "Random/Log.hpp"
#include "Random/RandomPch.hpp"

#include <glad/glad.h>

#include <chrono>
using namespace std::chrono_literals;
#include <thread>

namespace Rand
{
    Application::Application() : m_LayerStack(*this)
    {
        m_Window = std::unique_ptr<Window>(Window::create());
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");

        while (m_Running)
        {
            glClearColor(0.5, 0.0, 0.2, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
                layer->onUpdate();

            m_Window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(RAND_BIND_EVENT_FN(Application::onWindowClose));

        RAND_CORE_TRACE("event is {0}", event.toString());

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            (*it)->onEvent(event);
            if (event.isHandled())
            {
                break;
            }
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
} // namespace Rand
