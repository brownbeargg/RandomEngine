#pragma once

#include "Random/Renderer/Graphics/Shader.hpp"

namespace Rand
{
    class OpenGLShader : public Shader
    {
      public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const OpenGLShader&) = delete;
        OpenGLShader(OpenGLShader&&) = delete;
        OpenGLShader& operator=(const OpenGLShader&) = delete;
        OpenGLShader& operator=(OpenGLShader&&) = delete;
        ~OpenGLShader() { glDeleteProgram(m_RendererID); }

        void bind() const override { glUseProgram(m_RendererID); }
        void unbind() const override { glUseProgram(0); }

        void uInt(const char* name, const int value);

        void uFloat(const char* name, const float value);
        void uFloat2(const char* name, const glm::vec2& float2);
        void uFloat3(const char* name, const glm::vec3& float3);
        void uFloat4(const char* name, const glm::vec4& float4);

        void uMat3(const char* name, const glm::mat3& matrix);
        void uMat4(const char* name, const glm::mat4& matrix);
    };
} // namespace Rand
