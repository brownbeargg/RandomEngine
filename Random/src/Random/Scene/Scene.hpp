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

        Entity createEntity(const std::string_view name = std::string());

        void onUpdate();

      private:
        entt::registry m_Registry;

        friend class Entity;
    };
} // namespace Rand
