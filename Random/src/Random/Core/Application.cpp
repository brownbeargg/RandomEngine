#include "Random/Core/Application.hpp"

#include "Random/Layers/ImGuiLayer.hpp"
#include "Random/Layers/InputLayer.hpp"
#include "Random/Core/Log.hpp"

// TEMP
#include <glad/glad.h>

namespace Rand
{
    // TODO:make code "cleaner" and less cluttered in application

    Application::Application() : m_LayerStack(*this), m_CoreLayerStack(*this)
    {
        m_Window = std::unique_ptr<Window>(Window::create());
        m_Window->setEventCallback(RAND_BIND_EVENT_FN(Application::onEvent));

        m_InputLayer = new InputLayer(*this);
        m_CoreLayerStack.pushLayer(m_InputLayer);

        m_ImGuiLayer = new ImGuiLayer(*this);
        m_CoreLayerStack.pushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        float vertices[3 * 3]{
            // clang-format off
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
            // clang-format on
        };

        uint32_t indices[]{0, 1, 2};

        m_VBO = std::unique_ptr<VertexBuffer>(VertexBuffer::create(vertices, sizeof(vertices)));
        m_EBO = std::unique_ptr<IndexBuffer>(IndexBuffer::create(indices, 3));

        RAND_CORE_TRACE("Vertex count: {0}", m_EBO->getCount());

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location=0) in vec3 a_Pos;
            out vec3 v_ColorPos;

            void main()
            {
               v_ColorPos=a_Pos;
               gl_Position = vec4(a_Pos, 1.0); 
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            out vec4 FragColor;
            in vec3 v_ColorPos;

            void main()
            {
                FragColor = vec4(v_ColorPos + 0.5, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");

        while (m_Running)
        {
            m_Window->onUpdate();

            // TEMP
            glBindVertexArray(m_VAO);
            m_Shader->bind();
            glDrawElements(GL_TRIANGLES, m_EBO->getCount(), GL_UNSIGNED_INT, nullptr);

            //
            // Main updates
            //

            for (Layer* layer : m_CoreLayerStack)
                layer->onUpdate();

            for (Layer* layer : m_LayerStack)
                layer->onUpdate();

            //
            // ImGui
            //

            m_ImGuiLayer->begin();

            for (Layer* layer : m_CoreLayerStack)
                layer->onImGuiRender();

            for (Layer* layer : m_LayerStack)
                layer->onImGuiRender();

            m_ImGuiLayer->end();
        }
    }

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(RAND_BIND_EVENT_FN(Application::onWindowClose));

        RAND_CORE_TRACE("event is {0}", event.toString());

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            (*it)->onEvent(event);
            if (event.isHandled())
            {
                break;
            }
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
} // namespace Rand
