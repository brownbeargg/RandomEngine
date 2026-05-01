#include "ExampleLayer.hpp"

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

    Rand::Weak textureShader = m_ShaderLib.add("texture", Rand::Shader::create(vertexSrc, fragmentSrc));
    textureShader->bind();

    m_GrassTexture = Rand::Texture2D::create("Assets/Textures/Grass.png");
    m_TreeTexture = Rand::Texture2D::create("Assets/Textures/Tree.png");

    textureShader->uInt("u_Texture", 0);

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
        Rand::Weak textureShader = m_ShaderLib.get("texture");
        textureShader->bind();

        for (int y{}; y < 10; ++y)
            for (int x{}; x < 10; ++x)
            {
                // m_GrassTexture->bind();
                // glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
                // Rand::Renderer::submit(textureShader.lock(), m_VAO, transform);

                // m_TreeTexture->bind();
                // transform = glm::translate(transform, glm::vec3(0.0f, 0.5f, 0.0f));
                // Rand::Renderer::submit(textureShader.lock(), m_VAO, transform);
                // transform = glm::translate(transform, glm::vec3(0.1f, -0.3f, 0.0f));
                // Rand::Renderer::submit(textureShader.lock(), m_VAO, transform);
            }

        Rand::Renderer2D::beginScene(&m_Camera->getCamera());
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.2f, 0.5f));
            Rand::Renderer2D::drawQuad(transform, glm::vec4(1.0f, 0.0f, 0.5f, 1.0f));

            transform = glm::translate(glm::mat4(1.0f), glm::vec3(-0.8f, 0.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.7f, 1.0f));
            Rand::Renderer2D::drawQuad(transform, m_TreeTexture);

            transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.1f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 5.0f));
            Rand::Renderer2D::drawQuad(transform, m_GrassTexture);
        }
        Rand::Renderer2D::endScene();
    }
    Rand::Renderer::endScene();
}

void SandboxLayer::onEvent(Rand::Event& event)
{
    m_Camera->onEvent(event);
}
