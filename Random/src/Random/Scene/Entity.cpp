#include "Random/Scene/Entity.hpp"

namespace Rand
{
    Entity::Entity(entt::entity handle, const Weak<Scene>& scene) : m_EntityHandle(handle), m_Scene(scene) {}
} // namespace Rand
