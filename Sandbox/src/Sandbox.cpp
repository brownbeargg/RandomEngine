#include "Sandbox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

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

        uniform mat4 u_MVP;

        void main()
        {
           gl_Position = u_MVP * vec4(a_Pos, 1.0); 
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        out vec4 FragColor;
        uniform vec4 u_Color;

        void main()
        {
            FragColor = u_Color;
        }
    )";

    m_Shader.reset(Rand::Shader::Create(vertexSrc, fragmentSrc));

    Rand::BufferLayout layout = {{"a_Pos", Rand::ShaderDataType::Float3}, {"a_Color", Rand::ShaderDataType::Float4}};

    m_VBO->setLayout(layout);

    m_VAO->addVertexBuffer(Rand::Ref<Rand::VertexBuffer>(m_VBO.get()));
    m_VAO->setIndexBuffer(Rand::Ref<Rand::IndexBuffer>(m_EBO.get()));
}

void SandboxLayer::onUpdate(float deltaTime)
{
    Rand::RenderCommand::clearColor({0.1, 0.1, 0.1, 1.0});
    Rand::RenderCommand::clear();

    constexpr float camSpeed = 3.0f;
    if (m_App.getInput().isKeyPressed(Rand::Key::W))
        m_Camera->setPosition(m_Camera->getPosition() + glm::vec3(0.0f, camSpeed * deltaTime, 0.0f));
    else if (m_App.getInput().isKeyPressed(Rand::Key::S))
        m_Camera->setPosition(m_Camera->getPosition() + glm::vec3(0.0f, -camSpeed * deltaTime, 0.0f));
    if (m_App.getInput().isKeyPressed(Rand::Key::A))
        m_Camera->setPosition(m_Camera->getPosition() + glm::vec3(-camSpeed * deltaTime, 0.0f, 0.0f));
    else if (m_App.getInput().isKeyPressed(Rand::Key::D))
        m_Camera->setPosition(m_Camera->getPosition() + glm::vec3(camSpeed * deltaTime, 0.0f, 0.0f));

    Rand::Renderer::beginScene(*m_Camera.get());
    {
        dynamic_cast<Rand::OpenGLShader*>(m_Shader.get())->uFloat4("u_Color", glm::vec4(0.8, 0.2, 0.3, 1.0f));

        glm::mat4 transform(1.0f);
        transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f));
        transform = glm::translate(transform, glm::vec3(-1.0f));
        Rand::Renderer::submit(m_Shader, m_VAO, transform);

        dynamic_cast<Rand::OpenGLShader*>(m_Shader.get())->uFloat4("u_Color", glm::vec4(0.3, 0.2, 0.8, 1.0f));

        transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(60.0f), glm::vec3(0.5f, 0.5f, 0.0f));
        transform = glm::translate(transform, glm::vec3(0.5f));
        Rand::Renderer::submit(m_Shader, m_VAO, transform);
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
