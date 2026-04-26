#include "Sandbox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app) : Layer("SandboxLayer", app)
{
    m_Camera = new Rand::OrthographicCameraController(
        (float)m_App.getWindow().getWidth() / (float)m_App.getWindow().getHeight(), m_App.getInput());

    float vertices[]{
        // clang-format off
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        // clang-format on
    };

    uint32_t indices[]{0, 1, 2, 2, 3, 0};

    m_VAO = Rand::VertexArray::create();
    m_VAO->bind();
    m_VBO = Rand::VertexBuffer::create(vertices, sizeof(vertices));
    m_EBO = Rand::IndexBuffer::create(indices, 6);

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

    Rand::Weak basicShader = m_ShaderLib.add("basic", Rand::Shader::Create(vertexSrc, fragmentSrc));
    basicShader->bind();

    m_GrassTexture = Rand::Texture2D::create("Assets/Textures/Grass.png");
    m_TreeTexture = Rand::Texture2D::create("Assets/Textures/Tree.png");

    dynamic_cast<Rand::OpenGLShader*>(basicShader.get())->uInt("u_Texture", 0);

    Rand::BufferLayout layout = {
        {"a_Pos", Rand::ShaderDataType::Float3}, {"a_TexCoord", Rand::ShaderDataType::Float2}};

    m_VBO->setLayout(layout);

    m_VAO->addVertexBuffer(m_VBO);
    m_VAO->setIndexBuffer(m_EBO);
}

void SandboxLayer::onUpdate(float deltaTime)
{
    Rand::RenderCommand::clearColor({0.1, 0.1, 0.1, 1.0});
    Rand::RenderCommand::clear();

    m_Camera->onUpdate(deltaTime);

    Rand::Renderer::beginScene(m_Camera->getCamera());
    {
        Rand::Weak basicShader = m_ShaderLib.get("basic");
        basicShader->bind();
        m_GrassTexture->bind();
        glm::mat4 transform(1.0f);
        Rand::Renderer::submit(basicShader.lock(), m_VAO, transform);

        m_TreeTexture->bind();
        transform = glm::translate(transform, glm::vec3(0.0f, 0.5f, 0.0f));
        Rand::Renderer::submit(basicShader.lock(), m_VAO, transform);
    }
    Rand::Renderer::endScene();
}

void SandboxLayer::onEvent(Rand::Event& event)
{
    m_Camera->onEvent(event);
}

Sandbox::Sandbox()
{
    pushLayer(new SandboxLayer(*this));
}

Sandbox::~Sandbox() {}
