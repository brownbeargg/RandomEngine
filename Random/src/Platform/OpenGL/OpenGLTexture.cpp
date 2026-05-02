#include "Platform/OpenGL/OpenGLTexture.hpp"

#include "Random/Core/Assert.hpp"
#include "Random/Debug/Instrumentor.hpp"

#include <stb_image.h>

namespace Rand
{
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

        GLenum internalFormat{}, dataFormat{};
        switch (channels)
        {
        case 4:
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
            break;
        case 3:
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
            break;
        case 2:
            internalFormat = GL_RG16;
            dataFormat = GL_RG;
            break;
        case 1:
            internalFormat = GL_R16;
            dataFormat = GL_RED;
        }

        RAND_CORE_RELEASE_ASSERT(channels, "Format not supported");

        m_Width = width;
        m_Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }
} // namespace Rand
