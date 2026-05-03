#include <Random.hpp>

class SandboxLayer : public Rand::Layer
{
  public:
    SandboxLayer(const Rand::Application& app);

    void onUpdate(float deltaTime) override;
    void onEvent(Rand::Event& event) override;
    void onImGuiRender() override;

  private:
    Rand::ShaderLibrary m_ShaderLib;
    Rand::Ref<Rand::Texture2D> m_GrassTexture, m_TreeTexture;
    Rand::Ref<Rand::Texture2D> m_TileMap;
    Rand::Ref<Rand::SubTexture2D> m_StairSubTexture;
    Rand::Ref<Rand::SubTexture2D> m_BarrelSubTexture;
    Rand::Ref<Rand::SubTexture2D> m_TreeSubTexture;
    Rand::Ref<Rand::OrthographicCameraController> m_Camera;
};
