#pragma once

#include "Random/Core/Core.hpp"
#include "Random/Core/Memory/Ref.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Rand
{
    class Shader final : public RefCount
    {
      public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        Shader(const Shader&) = delete;
        Shader(Shader&&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = delete;
        ~Shader();

        void bind() const;
        void unbind() const;

        void uMat4(const char* name, const glm::mat4& matrix) const;

      private:
        uint32_t m_RendererID;
    };

    /**
     * @brief Possible shader data types
     */
    enum class ShaderDataType : uint8_t
    {
        None = 0,

        Bool,

        Int,
        Int2,
        Int3,
        Int4,

        Float,
        Float2,
        Float3,
        Float4,

        Mat3,
        Mat4
    };

    /**
     * @return Size of shader data type
     */
    constexpr uint32_t shaderDataTypeSize(const ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::None:
            return 0;
        case ShaderDataType::Bool:
            return 1;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Int2:
            return 4 * 2;
        case ShaderDataType::Int3:
            return 4 * 3;
        case ShaderDataType::Int4:
            return 4 * 4;
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Float2:
            return 4 * 2;
        case ShaderDataType::Float3:
            return 4 * 3;
        case ShaderDataType::Float4:
            return 4 * 4;
        case ShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown shader data type");
    }

    /**
     * @return The count of the shader data type
     */
    constexpr uint32_t shaderDataTypeCount(const ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::None:
            return 0;
        case ShaderDataType::Bool:
            return 1;
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Mat3:
            return 3;
        case ShaderDataType::Mat4:
            return 4;
        }

        RAND_CORE_RELEASE_ASSERT(false, "Unknown shader data type");
    }

    /**
     * @return The shader data type in OpenGL terms
     */
    constexpr GLenum shaderDataTypeToGLDataType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::None:
            return GL_NONE;
        case ShaderDataType::Bool:
            return GL_BOOL;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        }
    }

} // namespace Rand
