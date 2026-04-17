#pragma once

#include "Random/Events/Event.hpp"

namespace Rand
{
    class Application;

    /**
     * @brief An interface for every layer
    */
    class Layer
    {
      public:
        virtual ~Layer() {}

        virtual void onAttach() {}
        virtual void onDetach() {}

        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}
        virtual void onImGuiRender() {}

        const std::string& getName() { return m_Name; }

      protected:
        Layer(const std::string_view name, const Application& app) : m_Name(name), m_App(app) {}

      protected:
        const Application& m_App;

      private:
        std::string m_Name;
    };
} // namespace Rand
