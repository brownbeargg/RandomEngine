#pragma once

#include "Random/Core/App/LayerStack.hpp"
#include "Random/Core/App/Window.hpp"
#include "Random/Core/DeltaTime.hpp"
#include "Random/Core/Memory/Ref.hpp"
#include "Random/Core/Event.hpp"
#include "Random/Events/ApplicationEvent.hpp"
#include "Random/Layers/ImGuiLayer.hpp"
#include "Random/Layers/ImGuiProfileLayer.hpp"

namespace Rand
{
    class Application : public RefCount
    {
      public:
        /**
         * @brief Initializes state of the Application object e.g. the window
         */
        Application();
        virtual ~Application();

        /**
         * @brief Contains the main application loop
         *
         * Calls onUpdate() on every layer
         * Calls onImGuiRender() on every layer
         */
        void run();

        /**
         * @brief Gets called on every event
         *
         * @param event A reference to the Event that just happened
         */
        void onEvent(Event& event);

        void pushLayer(Layer* const layer) { m_LayerStack.pushLayer(layer); }
        void pushOverlay(Layer* const overlay) { m_LayerStack.pushOverlay(overlay); }

        void popLayer(Layer* const layer) { m_LayerStack.popLayer(layer); }
        void popOverlay(Layer* const overlay) { m_LayerStack.popOverlay(overlay); }

        void pushProfileResult(Profiler::Result result) const { m_ImGuiProfileLayer->pushResult(result); }

        Ref<Input> getInput() const { return m_Window->getInput(); }
        const Window& getWindow() const { return *m_Window.get(); }

      private:
        bool onWindowClose(WindowCloseEvent& event);
        bool onWindowResize(WindowResizeEvent& event);

      private:
        Ref<Window> m_Window;

        bool m_Running = true;
        bool m_Minimized = false;

        DeltaTime m_Dt{};
        float m_LastTime{};

        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
        ImGuiProfileLayer* m_ImGuiProfileLayer;
    };

    /**
     * @brief Creates an application (this function will be defined in the client)
     *
     * @return A raw pointer to a new application object
     */
    Rand::Application* createApplication();
} // namespace Rand
