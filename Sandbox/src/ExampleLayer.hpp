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
    Rand::ShaderLibrary m_ShaderLib;
    Rand::Ref<Rand::Texture2D> m_GrassTexture, m_TreeTexture;
    Rand::Ref<Rand::OrthographicCameraController> m_Camera;
};
