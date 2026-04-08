#pragma once

#include "Random/events/Event.hpp"

namespace Rand
{
    class Application;

    class RAND_API Layer
    {
      public:
        Layer(const std::string_view name, const Application& app) : m_Name(name), m_App(app) {}
        virtual ~Layer() {}

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}

        const std::string& getName() { return m_Name; }

      protected:
        const Application& m_App;

      private:
        std::string m_Name;
    };
} // namespace Rand
