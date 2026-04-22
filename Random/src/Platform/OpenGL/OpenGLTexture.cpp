#include "Platform/OpenGL/OpenGLTexture.hpp"

#include "Random/Core/Assert.hpp"

#include <stb_image.h>

namespace Rand
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
    {
        int width{}, height{}, channels{};
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data)
        {
            RAND_CORE_ERROR("Failed to load image");
            RAND_CORE_ERROR("Reason: {0}", stbi_failure_reason());
            RAND_CORE_RELEASE_ASSERT(false, "Failed to load image");
        }
        RAND_CORE_RELEASE_ASSERT(channels == 3, "Texture is not RGB, but Random only supports RGB textures");

        m_Width = width;
        m_Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }
} // namespace Rand
