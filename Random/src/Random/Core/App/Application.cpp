#include "Random/Core/App/Application.hpp"

#include "Random/Core/Log.hpp"

#include "Random/Layers/ImGuiLayer.hpp"

namespace Rand
{
    Application::Application() : m_LayerStack(*this)
    {
        m_Window.reset(Window::create());
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(Application::onEvent));

        m_ImGuiLayer = new ImGuiLayer(*this);
        m_LayerStack.pushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");

        /// @todo remove clutter
        while (m_Running)
        {
            for (Layer* layer : m_LayerStack)
                layer->onUpdate();

            m_ImGuiLayer->begin();
            {
                for (Layer* layer : m_LayerStack)
                    layer->onImGuiRender();
            }
            m_ImGuiLayer->end();

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
