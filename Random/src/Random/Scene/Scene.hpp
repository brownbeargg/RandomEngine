#pragma once

#include "Random/Core/Memory/RefCount.hpp"

#include "entt.hpp"

namespace Rand
{
    class Entity;

    class Scene : public RefCount
    {
      public:
        Scene() = default;
        ~Scene() = default;

        [[nodiscard]] Entity createEntity(const std::string_view name = std::string());

        void onUpdate();
        void onViewportResize(uint32_t width, uint32_t height);

        Entity* getPrimaryCamera() { return m_PrimaryCamera; }
        void setPrimaryCamera(Entity* camera) { m_PrimaryCamera = camera; }

      private:
        entt::registry m_Registry;
        Entity* m_PrimaryCamera;

        uint32_t m_ViewportWidth{}, m_ViewportHeight{};

        friend class Entity;
    };
} // namespace Rand
