#include "Random/Core/Application.hpp"

#include "Random/Layers/ImGuiLayer.hpp"
#include "Random/Layers/InputLayer.hpp"
#include "Random/Core/Log.hpp"
#include "RandomPch.hpp"

#include <glad/glad.h>

namespace Rand
{
    Application::Application() : m_LayerStack(*this), m_CoreLayerStack(*this)
    {
        m_Window = std::unique_ptr<Window>(Window::create());
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(Application::onEvent));

        m_ImGuiLayer = new ImGuiLayer(*this);
        m_CoreLayerStack.pushOverlay(m_ImGuiLayer);

        m_InputLayer = new InputLayer(*this);
        m_CoreLayerStack.pushLayer(m_InputLayer);
    }

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");

        while (m_Running)
        {
            m_Window->onUpdate();

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.5, 0.0, 0.2, 1.0);

            for (Layer* layer : m_CoreLayerStack)
                layer->onUpdate();

            for (Layer* layer : m_LayerStack)
                layer->onUpdate();
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
