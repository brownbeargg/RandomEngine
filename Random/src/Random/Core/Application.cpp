#include "Random/Core/Application.hpp"

#include "Random/Core/Log.hpp"

#include "Random/Layers/ImGuiLayer.hpp"
#include "Random/Layers/InputLayer.hpp"

#include "Random/Renderer/RenderCommand.hpp"
#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    /// @todo make code "cleaner" and less cluttered in application

    Application::Application() : m_LayerStack(*this), m_CoreLayerStack(*this)
    {
        m_Window.reset(Window::create());
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(Application::onEvent));

        m_InputLayer = new InputLayer(*this);
        m_CoreLayerStack.pushLayer(m_InputLayer);

        m_ImGuiLayer = new ImGuiLayer(*this);
        m_CoreLayerStack.pushOverlay(m_ImGuiLayer);

   }

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");

        /// @todo remove clutter
        while (m_Running)
        {
            for (Layer* layer : m_CoreLayerStack)
                layer->onUpdate();

            for (Layer* layer : m_LayerStack)
                layer->onUpdate();

            m_ImGuiLayer->begin();
            {
                for (Layer* layer : m_CoreLayerStack)
                    layer->onImGuiRender();

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

        for (auto it = m_CoreLayerStack.rbegin(); it != m_CoreLayerStack.rend(); ++it)
        {
            (*it)->onEvent(event);
            if (event.isHandled())
            {
                break;
            }
        }

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
