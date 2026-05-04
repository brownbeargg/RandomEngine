#include "Random/Core/App/Application.hpp"

#include "Random/Core/Config.hpp"

#include "Random/Debug/Instrumentor.hpp"
#include "Random/Layers/ImGuiLayer.hpp"

#include "Random/Renderer/Renderer.hpp"

namespace Rand
{
    Application::Application(const WindowProps& windowProps) : m_LayerStack(*this)
    {
        RAND_PROFILE_FUNCTION();

        m_Window = Window::create(windowProps);
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(Application::onEvent));

        Renderer::init();

        m_ImGuiLayer = new ImGuiLayer(*this);
        pushOverlay(m_ImGuiLayer);

        m_ImGuiProfileLayer = new ImGuiProfileLayer(*this);
        pushOverlay(m_ImGuiProfileLayer);
    }

    Application::~Application()
    {
        Renderer::shutdown();
    }

    void Application::run()
    {
        while (m_Running)
        {
            RAND_PROFILE_SCOPE("Main loop");

            m_Dt.recalculate(m_LastTime);

            for (Layer* layer : m_LayerStack)
                layer->onUpdate(m_Dt);

#if RAND_ENABLE_IMGUI
            if (!m_Minimized)
            {
                m_ImGuiLayer->begin();
                for (Layer* layer : m_LayerStack)
                    layer->onImGuiRender();
                m_ImGuiLayer->end();
            }
#endif

            m_Window->onUpdate();
        }
    }

    void Application::onEvent(Event& event)
    {
        RAND_PROFILE_FUNCTION();

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

    void Application::pushLayer(Layer* const layer)
    {
        m_LayerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* const overlay)
    {
        m_LayerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::popLayer(Layer* const layer)
    {
        m_LayerStack.popLayer(layer);
        layer->onDetach();
    }

    void Application::popOverlay(Layer* const overlay)
    {
        m_LayerStack.popOverlay(overlay);
        overlay->onDetach();
    }

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        close();
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
