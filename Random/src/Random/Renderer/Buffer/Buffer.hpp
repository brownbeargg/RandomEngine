#pragma once

#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Buffer/Layout.hpp"

namespace Rand
{
    class VertexBuffer : public RefCount
    {
      public:
        virtual ~VertexBuffer() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const BufferLayout& getLayout() const = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;

        /**
         * @brief Sets data of an vertex buffer object
         *
         * @param vertices A pointer to the first index of an array of floats
         * @param size Size in bytes of the vertices array
         */
        virtual void setData(float* vertices, uint32_t size) = 0;

        virtual void setData(const void* data, uint32_t size)=0;

        static VertexBuffer* create(uint32_t size);

        /**
         * @brief Initializes and sets the data of an vertex buffer object
         *
         * @param vertices A pointer to the first index of an array of floats
         * @param size Size in bytes of the vertices array
         *
         * @return Pointer to a new vertex buffer object
         */
        static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer : public RefCount
    {
      public:
        virtual ~IndexBuffer() {}

        /**
         * @brief Sets data of an index buffer object
         *
         * @param indices A pointer to the first index of an array of uint32_t's
         * @param count Length of the array
         */
        virtual void setData(uint32_t* indices, uint32_t count) = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        /**
         * @brief Initialize and sets data of an index buffer object
         *
         * @param indices A pointer to the first index of an array of uint32_t's
         * @param count Length of the array
         *
         * @return Pointer to a new index buffer object
         */
        static IndexBuffer* create(uint32_t* indices, uint32_t count);
    };
} // namespace Rand
