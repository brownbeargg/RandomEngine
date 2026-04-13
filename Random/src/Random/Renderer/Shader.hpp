#pragma once

namespace Rand
{
    class Shader final
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

      private:
        uint32_t m_RendererID;
    };
} // namespace Rand
