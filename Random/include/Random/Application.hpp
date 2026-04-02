#pragma once

#include "Random/Core.hpp"
#include "Random/events/ApplicationEvent.hpp"
#include "Random/events/Event.hpp"
#include "Random/events/KeyEvent.hpp"
#include "Random/events/MouseEvent.hpp"
#include "Random/LayerStack.hpp"
#include "Random/Window.hpp"

namespace Rand
{
    class RAND_API Application
    {
      public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& event);

        void pushLayer(Layer* const layer) { m_LayerStack.pushLayer(layer); }
        void pushOverlay(Layer* const overlay) { m_LayerStack.pushOverlay(overlay); }

        void popLayer(Layer* const layer) { m_LayerStack.popLayer(layer); }
        void popOverlay(Layer* const overlay) { m_LayerStack.popOverlay(overlay); }

      private:
        bool onWindowClose(WindowCloseEvent& event);

      private:
        std::unique_ptr<Window> m_Window;
        LayerStack              m_LayerStack;
        bool                    m_Running = true;
    };

    std::unique_ptr<Application> createApplication();
} // namespace Rand
