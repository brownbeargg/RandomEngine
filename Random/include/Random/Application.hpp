#pragma once

#include "Random/Core.hpp"
#include "Random/events/Event.hpp"
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
        std::unique_ptr<Window> m_Window;
    };

    std::unique_ptr<Application> createApplication();
} // namespace Rand
