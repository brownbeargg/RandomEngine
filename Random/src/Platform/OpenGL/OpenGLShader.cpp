#include "Platform/OpenGL/OpenGLShader.hpp"

#include "Random/Debug/Instrumentor.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Rand
{
    /**
     * @brief Create shader from shader source code
     *
     * @param vertexSource Source code of the vertex shader
     * @param fragmentSource Source code of the fragment shader
     */
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        RAND_PROFILE_FUNCTION();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = (const GLchar*)vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            RAND_CORE_ERROR("{0}", infoLog.data());
            RAND_CORE_RELEASE_ASSERT(false, "Vertex shader compiling failure");
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar*)fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            RAND_CORE_ERROR("{0}", infoLog.data());
            RAND_CORE_RELEASE_ASSERT(false, "Fragment shader compiling failure");
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_RendererID = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);

        // Link our program
        glLinkProgram(m_RendererID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(m_RendererID);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            // Use the infoLog as you see fit.
            RAND_CORE_ERROR("Shader Lining failure");
            RAND_CORE_ERROR("{0}", infoLog.data());
        }
    }

    void OpenGLShader::uInt(const char* name, const int value)
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name), value);
    }

    void OpenGLShader::uIntArray(const char* name, const int* values, uint32_t count)
    {
        glUniform1iv(glGetUniformLocation(m_RendererID, name), count, values);
    }

    void OpenGLShader::uFloat(const char* name, const float value)
    {
        glUniform1f(glGetUniformLocation(m_RendererID, name), value);
    }

    void OpenGLShader::uFloat2(const char* name, const glm::vec2& float2)
    {
        glUniform2f(glGetUniformLocation(m_RendererID, name), float2.x, float2.y);
    }

    void OpenGLShader::uFloat3(const char* name, const glm::vec3& float3)
    {
        glUniform3f(glGetUniformLocation(m_RendererID, name), float3.x, float3.y, float3.z);
    }

    void OpenGLShader::uFloat4(const char* name, const glm::vec4& float4)
    {
        glUniform4f(glGetUniformLocation(m_RendererID, name), float4.x, float4.y, float4.z, float4.w);
    }

    void OpenGLShader::uMat3(const char* name, const glm::mat3& matrix)
    {
        glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::uMat4(const char* name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    uint32_t OpenGLShader::s_CurrentBound = 0;
} // namespace Rand
