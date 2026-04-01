#include "Random/Application.hpp"

#include "Random/Log.hpp"
#include "Random/RandomPch.hpp"

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

        while (true)
        {
        }
    }

    void Application::onEvent(Event& event) { RAND_CORE_TRACE("event is {0}", event.toString()); }
} // namespace Rand
