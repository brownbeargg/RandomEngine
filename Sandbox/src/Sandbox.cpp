#include "Sandbox.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app) : Layer("SandboxLayer", app)
{
    m_Camera = new Rand::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);

    float vertices[]{
        // clang-format off
            -0.5f, -0.5f, 0.0f, 0.8f, 0.4f, 0.1f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
        // clang-format on
    };

    uint32_t indices[]{0, 1, 2};

    m_VAO.reset(Rand::VertexArray::create());
    m_VAO->bind();
    m_VBO.reset(Rand::VertexBuffer::create(vertices, sizeof(vertices)));
    m_EBO.reset(Rand::IndexBuffer::create(indices, 3));

    std::string vertexSrc = R"(
            #version 330 core

            layout(location=0) in vec3 a_Pos;
            layout(location=1) in vec4 a_Color;
            out vec4 v_Color;

            uniform mat4 u_VP;

            void main()
            {
               v_Color = a_Color;
               gl_Position = u_VP * vec4(a_Pos, 1.0); 
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

    m_Shader.reset(new Rand::Shader(vertexSrc, fragmentSrc));

    Rand::BufferLayout layout = {{"a_Pos", Rand::ShaderDataType::Float3}, {"a_Color", Rand::ShaderDataType::Float4}};

    m_VBO->setLayout(layout);

    m_VAO->addVertexBuffer(Rand::Ref<Rand::VertexBuffer>(m_VBO.get()));
    m_VAO->setIndexBuffer(Rand::Ref<Rand::IndexBuffer>(m_EBO.get()));
}

void SandboxLayer::onUpdate()
{
    Rand::RenderCommand::clearColor({0.1, 0.1, 0.1, 1.0});
    Rand::RenderCommand::clear();

    Rand::Renderer::beginScene(*m_Camera.get());
    {
        m_Camera->setRotation(m_Camera->getRotation() + glm::vec3(0.2f, 0.01f, 0.09f));

        Rand::Renderer::submit(m_Shader, m_VAO);
    }
    Rand::Renderer::endScene();
}

void SandboxLayer::onEvent(Rand::Event& event) {}

void SandboxLayer::onImGuiRender() {}

Sandbox::Sandbox()
{
    pushLayer(new SandboxLayer(*this));
}

Sandbox::~Sandbox() {}
