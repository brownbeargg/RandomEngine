#pragma once

#include "Random/events/Event.hpp"

namespace Rand
{
    class Layer
    {
      public:
        Layer(const std::string_view name) : m_Name(name) {}
        virtual ~Layer() {}

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}

        const std::string& getName() { return m_Name; }

      private:
        std::string m_Name;
    };
} // namespace Rand
