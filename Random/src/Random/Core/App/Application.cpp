#include "Random/Core/App/Application.hpp"

#include "Random/Core/Log.hpp"

#include "Random/Layers/ImGuiLayer.hpp"

#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    Application::Application() : m_LayerStack(*this)
    {
        m_Window.reset(Window::create());
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(Application::onEvent));

        Renderer::init();

        m_ImGuiLayer = new ImGuiLayer(*this);
        m_LayerStack.pushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {}

    void Application::run()
    {
        while (m_Running)
        {
            m_Dt.recalculate(m_LastTime);

            for (Layer* layer : m_LayerStack)
                layer->onUpdate(m_Dt);

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
        dispatcher.dispatch<WindowResizeEvent>(RAND_BIND_EVENT_FN(Application::onWindowResize));

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

    bool Application::onWindowResize(WindowResizeEvent& event)
    {
        if (!event.getWidth() || !event.getHeight())
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;

        Renderer::onWindowResize(event.getWidth(), event.getHeight());

        return false;
    }
} // namespace Rand
