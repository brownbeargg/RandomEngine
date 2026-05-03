#include "Random/Renderer/Graphics/SubTexture2D.hpp"

namespace Rand
{
    SubTexture2D::SubTexture2D(const Ref<Texture2D> texture, const glm::vec2& min, const glm::vec2& max)
        : m_Texture(texture)
    {
        m_TexCoords[0] = {min.x, min.y};
        m_TexCoords[1] = {max.x, min.y};
        m_TexCoords[2] = {max.x, max.y};
        m_TexCoords[3] = {min.x, max.y};
    }

    SubTexture2D* SubTexture2D::createFromCoords(Ref<Texture2D> texture, const glm::vec2& coords,
        const glm::vec2& cellSize, const glm::vec2& spriteSize)
    {
        glm::vec2 min = glm::vec2(
            (coords.x * cellSize.x) / texture->getWidth(), (coords.y * cellSize.y) / texture->getHeight());
        glm::vec2 max = glm::vec2(((coords.x + spriteSize.x) * cellSize.x) / texture->getWidth(),
            ((coords.y + spriteSize.y) * cellSize.y) / texture->getHeight());

        return new SubTexture2D(texture, min, max);
    }
} // namespace Rand
