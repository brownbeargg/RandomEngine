#pragma once

#include "Random/Core/Core.hpp"
#include "Random/Core/LayerStack.hpp"
#include "Random/Core/Window.hpp"
#include "Random/Events/ApplicationEvent.hpp"
#include "Random/Events/Event.hpp"
#include "Random/Events/KeyEvent.hpp"
#include "Random/Events/MouseEvent.hpp"
#include "Random/Layers/ImGuiLayer.hpp"
#include "Random/Layers/InputLayer.hpp"

namespace Rand
{
    class  Application
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

        const InputLayer& getInputLayer() const { return *m_InputLayer; }

        Window& getWindow() const { return *m_Window; }

      private:
        bool onWindowClose(WindowCloseEvent& event);

      private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        LayerStack m_LayerStack;
        LayerStack m_CoreLayerStack;
        InputLayer* m_InputLayer;
        ImGuiLayer* m_ImGuiLayer;
    };

    std::unique_ptr<Application> createApplication();
} // namespace Rand
