#include "Random/Scene/Scene.hpp"

#include "Random/Debug/Instrumentor.hpp"

#include "Random/Scene/Component.hpp"
#include "Random/Scene/Entity.hpp"
#include "Random/Renderer/Renderer2D.hpp"

namespace Rand
{
    Entity Scene::createEntity(const std::string_view name)
    {
        RAND_PROFILE_FUNCTION();

        Entity entity = {m_Registry.create(), this};
        auto& tag = entity.addComponent<TagComponent>(name.empty() ? "Entity" : name);
        return entity;
    }

    void Scene::onUpdate()
    {
        RAND_PROFILE_FUNCTION();

        Camera* primaryCamera = nullptr;
        {
            auto cameraView = m_Registry.view<CameraComponent>();
            for (auto entity : cameraView)
            {
                CameraComponent& cameraComponent = cameraView->get(entity);

                if (&cameraComponent == m_PrimaryCamera)
                {
                    primaryCamera = &cameraComponent.Camera;
                    break;
                }
            }
        }

        if (primaryCamera)
        {
            auto spriteView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
            for (auto entity : spriteView)
            {
                const auto& [transform, sprite] = spriteView.get(entity);
                Renderer2D::drawQuad(transform, sprite.Color);
            }
        }
    }
} // namespace Rand
