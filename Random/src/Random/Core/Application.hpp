#pragma once

#include "Random/Core/LayerStack.hpp"
#include "Random/Core/Window.hpp"
#include "Random/Events/ApplicationEvent.hpp"
#include "Random/Events/Event.hpp"
#include "Random/Layers/ImGuiLayer.hpp"
#include "Random/Layers/InputLayer.hpp"
#include "Random/Renderer/Buffer.hpp"
#include "Random/Renderer/Shader.hpp"
#include "Random/Renderer/VertexArray.hpp"

namespace Rand
{
    class Application
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

        const InputLayer& getInputLayer() const { return *m_InputLayer; }

        Window& getWindow() const { return *m_Window; }

      private:
        bool onWindowClose(WindowCloseEvent& event);
        bool onWindowResize(WindowResizeEvent& event);

      private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        LayerStack m_LayerStack;
        LayerStack m_CoreLayerStack;
        InputLayer* m_InputLayer;
        ImGuiLayer* m_ImGuiLayer;

        // TODO: Remove this because this is temp
        std::shared_ptr<VertexArray> m_VAO;
        std::shared_ptr<VertexBuffer> m_VBO;
        std::shared_ptr<IndexBuffer> m_EBO;
        std::shared_ptr<Shader> m_Shader;
    };

    /**
     * @brief Creates an application (this function will be defined in the client)
     *
     * @return A raw pointer to a new application object
     */
    Rand::Application* createApplication();
} // namespace Rand
