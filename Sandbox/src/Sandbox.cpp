#include "Sandbox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app) : Layer("SandboxLayer", app)
{
    m_Camera = new Rand::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);

    float vertices[]{
        // clang-format off
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        // clang-format on
    };

    uint32_t indices[]{0, 1, 2, 2, 3, 0};

    m_VAO.reset(Rand::VertexArray::create());
    m_VAO->bind();
    m_VBO.reset(Rand::VertexBuffer::create(vertices, sizeof(vertices)));
    m_EBO.reset(Rand::IndexBuffer::create(indices, 6));

    std::string vertexSrc = R"(
        #version 330 core

        layout(location=0) in vec3 a_Pos;
        layout(location=1) in vec2 a_TexCoord;

        uniform mat4 u_MVP;

        out vec2 v_TexCoord;

        void main()
        {
           v_TexCoord = a_TexCoord;
           gl_Position = u_MVP * vec4(a_Pos, 1.0); 
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        out vec4 FragColor;

        in vec2 v_TexCoord;
        uniform sampler2D u_Texture;

        void main()
        {
            FragColor = texture(u_Texture, v_TexCoord);
        }
    )";

    m_Shader.reset(Rand::Shader::Create(vertexSrc, fragmentSrc));
    m_Shader->bind();

    m_GrassTexture = Rand::Texture2D::create("Assets/Grass.png");
    m_TreeTexture = Rand::Texture2D::create("Assets/Tree.png");

    dynamic_cast<Rand::OpenGLShader*>(m_Shader.get())->uInt("u_Texture", 0);

    Rand::BufferLayout layout = {{"a_Pos", Rand::ShaderDataType::Float3}, {"a_TexCoord", Rand::ShaderDataType::Float2}};

    m_VBO->setLayout(layout);

    m_VAO->addVertexBuffer(m_VBO);
    m_VAO->setIndexBuffer(m_EBO);
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
        m_Shader->bind();
        m_GrassTexture->bind();
        glm::mat4 transform(1.0f);
        Rand::Renderer::submit(m_Shader, m_VAO, transform);

        m_TreeTexture->bind();
        transform = glm::translate(transform, glm::vec3(0.0f, 0.5f, 0.0f));
        Rand::Renderer::submit(m_Shader, m_VAO, transform);
    }
    Rand::Renderer::endScene();
}

void SandboxLayer::onEvent(Rand::Event& event) {}

Sandbox::Sandbox()
{
    pushLayer(new SandboxLayer(*this));
}

Sandbox::~Sandbox() {}
