#pragma once

#include "Random/Core/Core.hpp"
#include "Random/Events/ApplicationEvent.hpp"
#include "Random/Events/Event.hpp"
#include "Random/Events/KeyEvent.hpp"
#include "Random/Events/MouseEvent.hpp"
#include "Random/Core/LayerStack.hpp"
#include "Random/Core/Window.hpp"

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

        Window& getWindow() const { return *m_Window; }

      private:
        bool onWindowClose(WindowCloseEvent& event);

      private:
        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
        bool m_Running = true;
    };

    std::unique_ptr<Application> createApplication();
} // namespace Rand
