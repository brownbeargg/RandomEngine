#pragma once

#include <Random.hpp>

class SandboxLayer : public Rand::Layer
{
  public:
    SandboxLayer(const Rand::Application& app);

    void onUpdate(float deltaTime) override;
    void onEvent(Rand::Event& event) override;

  private:
    Rand::Ref<Rand::VertexArray> m_VAO;
    Rand::Ref<Rand::VertexBuffer> m_VBO;
    Rand::Ref<Rand::IndexBuffer> m_EBO;
    Rand::Ref<Rand::Shader> m_Shader;
    Rand::Ref<Rand::Texture2D> m_Texture;
    Rand::Ref<Rand::OrthographicCamera> m_Camera;
};

class Sandbox : public Rand::Application
{
  public:
    Sandbox();
    ~Sandbox();
};
