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

        float vertices[]{
            // clang-format off
            -0.5f, -0.5f, 0.0f, 0.8f, 0.4f, 0.1f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
            // clang-format on
        };

        uint32_t indices[]{0, 1, 2};

        m_VAO.reset(VertexArray::create());
        m_VAO->bind();
        m_VBO.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        m_EBO.reset(IndexBuffer::create(indices, 3));

        std::string vertexSrc = R"(
            #version 330 core

            layout(location=0) in vec3 a_Pos;
            layout(location=1) in vec4 a_Color;
            out vec4 v_Color;

            void main()
            {
               v_Color = a_Color;
               gl_Position = vec4(a_Pos, 1.0); 
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            out vec4 FragColor;
            in vec4 v_Color;

            void main()
            {
                FragColor = v_Color;
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        BufferLayout layout = {{"a_Pos", ShaderDataType::Float3}, {"a_Color", ShaderDataType::Float4}};

        m_VBO->setLayout(layout);

        m_VAO->addVertexBuffer(std::shared_ptr<VertexBuffer>(m_VBO.get()));
        m_VAO->setIndexBuffer(std::shared_ptr<IndexBuffer>(m_EBO.get()));
    }

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");

        while (m_Running)
        {
            m_Window->onUpdate();

            // FIXME: remove this from application class
            m_VAO->bind();
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

        for (auto it = m_CoreLayerStack.rbegin(); it != m_CoreLayerStack.rend(); ++it)
        {
            (*it)->onEvent(event);
            if (event.isHandled())
            {
                break;
            }
        }

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
