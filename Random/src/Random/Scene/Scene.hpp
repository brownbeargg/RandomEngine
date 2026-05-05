#pragma once

#include "Random/Core/Memory/RefCount.hpp"
#include "Random/Scene/Component.hpp"

#include "entt.hpp"

namespace Rand
{
    class Entity;

    class Scene : public RefCount
    {
      public:
        Scene() = default;
        ~Scene() = default;

        Entity createEntity(const std::string_view name = std::string());

        void onUpdate();

        CameraComponent* getPrimaryCamera() { return m_PrimaryCamera; }
        void setPrimaryCamera(CameraComponent* camera) { m_PrimaryCamera = camera; }

      private:
        entt::registry m_Registry;
        CameraComponent* m_PrimaryCamera;

        friend class Entity;
    };
} // namespace Rand
