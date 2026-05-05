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

        auto spriteGroup = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto Entity : spriteGroup)
        {
            auto [transform, sprite] = spriteGroup.get<TransformComponent, SpriteRendererComponent>(Entity);
            Renderer2D::drawQuad(transform, sprite.Color);
        }
    }
} // namespace Rand
