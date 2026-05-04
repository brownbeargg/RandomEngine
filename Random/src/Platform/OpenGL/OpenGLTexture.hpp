#pragma once

#include "Random/Renderer/Graphics/Texture.hpp"

#include <glad/glad.h>

namespace Rand
{
    class OpenGLTexture2D final : public Texture2D
    {
      public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D();

        bool operator==(const Texture& other) const override
        {
            return m_RendererID == static_cast<const OpenGLTexture2D&>(other).m_RendererID;
        }

        void bind(uint32_t slot) const override { glBindTextureUnit(slot, m_RendererID); }

        void setData(void* data, uint32_t size) override;

        uint32_t getWidth() const override { return m_Width; }
        uint32_t getHeight() const override { return m_Height; }
        uint32_t getRendererID() const override { return m_RendererID; }

      private:
        std::string m_Path;
        uint32_t m_Width{}, m_Height{};
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };
} // namespace Rand
