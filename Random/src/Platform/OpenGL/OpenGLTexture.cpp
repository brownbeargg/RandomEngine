#include "Platform/OpenGL/OpenGLTexture.hpp"

#include "Random/Core/Assert.hpp"
#include "Random/Debug/Instrumentor.hpp"

#include <stb_image.h>

namespace Rand
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
    {
        stbi_set_flip_vertically_on_load(true);

        int width{}, height{}, channels{};
        unsigned char* data = nullptr;
        {
            RAND_PROFILE_SCOPE("stbi_load OpenGLTexture2D::OpenGLTexture2D(const std::sring&)");
            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }
        if (!data)
        {
            RAND_CORE_ERROR("Failed to load image");
            RAND_CORE_ERROR("Reason: {0}", stbi_failure_reason());
            RAND_CORE_RELEASE_ASSERT(false, "Failed to load image");
        }

        switch (channels)
        {
        case 4:
            m_InternalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
            break;
        case 3:
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
            break;
        case 2:
            m_InternalFormat = GL_RG16;
            m_DataFormat = GL_RG;
            break;
        case 1:
            m_InternalFormat = GL_R16;
            m_DataFormat = GL_RED;
        }

        RAND_CORE_RELEASE_ASSERT(channels, "Format not supported");

        m_Width = width;
        m_Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::setData(void* data, uint32_t size)
    {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        RAND_CORE_RELEASE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }
} // namespace Rand
