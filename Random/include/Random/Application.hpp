#pragma once

#include "Random/Core.hpp"
#include "Random/events/ApplicationEvent.hpp"
#include "Random/events/Event.hpp"
#include "Random/events/KeyEvent.hpp"
#include "Random/events/MouseEvent.hpp"
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

      private:
        bool onWindowClose(WindowCloseEvent& event);

      private:
        std::unique_ptr<Window> m_Window;
        bool                    m_Running = true;
    };

    std::unique_ptr<Application> createApplication();
} // namespace Rand
