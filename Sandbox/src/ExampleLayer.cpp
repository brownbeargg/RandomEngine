#include "ExampleLayer.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app)
    : Layer("SandboxLayer", app),
      m_Camera(new Rand::OrthographicCameraController(
          (float)m_App.getWindow()->getWidth() / (float)m_App.getWindow()->getHeight(), m_App.getInput()))
{
    RAND_PROFILE_FUNCTION();

    m_GrassTexture = Rand::Texture2D::create("Assets/Textures/Grass.png");
    m_TreeTexture = Rand::Texture2D::create("Assets/Textures/Tree.png");
}

void SandboxLayer::onUpdate(float deltaTime)
{
    RAND_PROFILE_FUNCTION();

    Rand::RenderCommand::clearColor({0.1, 0.1, 0.1, 1.0});
    Rand::RenderCommand::clear();

    m_Camera->onUpdate(deltaTime);

    Rand::Profiler::Timer renderTimer("SandboxLayer::onUpdate rendering");
    Rand::Renderer::beginScene(m_Camera->getCamera());
    {
        Rand::Renderer2D::beginScene(&m_Camera->getCamera());
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.2f, 0.5f));
            Rand::Renderer2D::drawQuad(transform, glm::vec4(1.0f, 0.0f, 0.5f, 1.0f));

            transform = glm::translate(glm::mat4(1.0f), glm::vec3(-0.8f, 0.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.7f, 1.0f));
            Rand::Renderer2D::drawQuad(transform, m_TreeTexture);

            transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.1f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
            Rand::Renderer2D::drawQuad(transform, m_GrassTexture, 5, glm::vec4(1.0f, 0.0f, 0.2f, 1.0f));
        }
        Rand::Renderer2D::endScene();
    }
    Rand::Renderer::endScene();
    m_App.pushProfileResult(renderTimer.stop());
}

void SandboxLayer::onEvent(Rand::Event& event)
{
    RAND_PROFILE_FUNCTION();

    m_Camera->onEvent(event);
}
