#pragma once

#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Graphics/Texture.hpp"

#include <glm/glm.hpp>

namespace Rand
{
    class SubTexture2D : public RefCount
    {
      public:
        SubTexture2D(const Ref<Texture2D> texture, const glm::vec2& min, const glm::vec2& max);

        const Ref<Texture2D> getTexture() const { return m_Texture; }
        const glm::vec2* getTexCoords() const { return m_TexCoords; }

        static SubTexture2D* createFromCoords(Ref<Texture2D> texture, const glm::vec2& coords,
            const glm::vec2& cellSize, const glm::vec2& spriteSize = {1, 1});

      private:
        Ref<Texture2D> m_Texture;
        glm::vec2 m_TexCoords[4];
    };
} // namespace Rand
