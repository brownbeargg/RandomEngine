#pragma once

#include "Random/Renderer/Shader.hpp"

namespace Rand
{
    struct BufferElement final
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Count{};
        size_t Offset{};
        bool Normalized;

        BufferElement(const std::string& name, ShaderDataType type, bool normalized = false)
            : Name(name), Type(type), Size(shaderDataTypeSize(type)), Count(shaderDataTypeCount(type)),
              Normalized(normalized)
        {
        }

        uint32_t getCount() const { return Count; }
    };

    class BufferLayout : public RefCount
    {
      public:
        BufferLayout(const std::initializer_list<BufferElement> elements) : m_Elements(elements)
        {
            calculateOffsetAndStride();
        }

        ~BufferLayout() = default;

        const std::vector<BufferElement>& getElements() { return m_Elements; }
        const uint32_t getStride() { return m_Stride; }

        const std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        const std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

        const std::vector<BufferElement>::reverse_iterator rbegin() { return m_Elements.rbegin(); }
        const std::vector<BufferElement>::reverse_iterator rend() { return m_Elements.rend(); }

      private:
        void calculateOffsetAndStride();

      private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride{};
    };
} // namespace Rand
