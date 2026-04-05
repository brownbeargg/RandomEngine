#include "Random/Application.hpp"

#include "Random/Log.hpp"
#include "Random/RandomPch.hpp"

#include <glad/glad.h>

namespace Rand
{
#define RAND_BIND_EVENT_FN(eventFn) std::bind(&Application::eventFn, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::create());
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(onEvent));
    }

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");

        while (m_Running)
        {
            m_Window->onUpdate();

            for (Layer* layer : m_LayerStack)
                layer->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(RAND_BIND_EVENT_FN(onWindowClose));

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
