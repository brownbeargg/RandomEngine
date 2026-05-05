#pragma once

#include "Random/Core/Memory/Weak.hpp"
#include "Random/Debug/Instrumentor.hpp"

#include "Random/Scene/Scene.hpp"

#include "entt.hpp"

namespace Rand
{
    class Entity final
    {
      public:
        Entity(entt::entity handle, const Weak<Scene>& scene);
        Entity(const Entity& other) = default;
        Entity(Entity&& rhs) = default;
        ~Entity() = default;

        operator bool() const { return (uint32_t)m_EntityHandle; }

        template <typename T, typename... Args>
        T& addComponent(Args&&... args);

        template <typename T>
        void removeComponent();

        template <typename T>
        T& getComponent();

        template <typename T>
        bool hasComponent();

      private:
        entt::entity m_EntityHandle{};
        Weak<Scene> m_Scene = nullptr;
    };

    template <typename T, typename... Args>
    T& Entity::addComponent(Args&&... args)
    {
        RAND_CORE_ASSERT(!hasComponent<T>(), "Entity already has component");
        return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
    }

    template <typename T>
    void Entity::removeComponent()
    {
        RAND_CORE_ASSERT(hasComponent<T>(), "Entity doesn't have component");
        m_Scene->m_Registry.remove<T>(m_EntityHandle);
    }

    template <typename T>
    T& Entity::getComponent()
    {
        RAND_CORE_ASSERT(hasComponent<T>(), "Entity doesn't have component");
        return m_Scene->m_Registry.get<T>(m_EntityHandle);
    }

    template <typename T>
    bool Entity::hasComponent()
    {
        return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
    }
} // namespace Rand
