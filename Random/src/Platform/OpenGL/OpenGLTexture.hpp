#pragma once

#include "Random/Renderer/Graphics/Texture.hpp"

#include <glad/glad.h>

namespace Rand
{
    class OpenGLTexture2D final : public Texture2D
    {
      public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D();

        void bind(uint32_t slot) const override { glBindTextureUnit(slot, m_RendererID); }

        uint32_t getWidth() const override { return m_Width; }
        uint32_t getHeight() const override { return m_Height; }

      private:
        std::string m_Path;
        uint32_t m_Width{}, m_Height{};
        uint32_t m_RendererID;
    };
} // namespace Rand
