#include "Random/Renderer/Renderer2D.hpp"

#include "Random/Core/Config.hpp"
#include "Random/Debug/Instrumentor.hpp"

#include "Random/Renderer/Buffer/VertexArray.hpp"
#include "Random/Renderer/Graphics/Shader.hpp"
#include "Random/Renderer/RenderCommand.hpp"

static constexpr uint32_t MaxQuads = 8000;
static constexpr uint32_t MaxVertices = MaxQuads * 4;
static constexpr uint32_t MaxIndices = MaxQuads * 6;
static constexpr uint32_t MaxTextureSlots = 32; /// @todo renderer capabilities

namespace Rand
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
        float TexScale;
    };

    struct Renderer2DData
    {
        Ref<VertexArray> QuadVertexArray = nullptr;
        Ref<VertexBuffer> QuadVertexBuffer = nullptr;
        Ref<Shader> Shader = nullptr;
        Ref<Texture2D> WhiteTexture = nullptr;
        OrthographicCamera* Camera = nullptr;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // slot 0 = white texture

        glm::vec4 QuadVertexPositions[4];
        glm::vec2 QuadTexCoords[4];

        Renderer2D::Statistics Stats;
    };

    static Renderer2DData s_Data;

    void Renderer2D::init()
    {
        RAND_PROFILE_FUNCTION();

        s_Data.QuadVertexArray = VertexArray::create();

        s_Data.QuadVertexBuffer = VertexBuffer::create(nullptr, sizeof(QuadVertex) * MaxVertices);
        s_Data.QuadVertexBuffer->setLayout({{"a_Position", ShaderDataType::Float3},
            {"a_Color", ShaderDataType::Float4}, {"a_TexCoord", ShaderDataType::Float2},
            {"a_TexIndex", ShaderDataType::Float}, {"a_TexScale", ShaderDataType::Float}});
        s_Data.QuadVertexArray->addVertexBuffer(s_Data.QuadVertexBuffer);

        uint32_t* quadIndices = new uint32_t[MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i{}; i < MaxIndices; i += 6)
        {
            quadIndices[i] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> squareIB = IndexBuffer::create(quadIndices, MaxIndices);
        s_Data.QuadVertexArray->setIndexBuffer(squareIB);
        delete[] quadIndices;

        s_Data.QuadVertexBufferBase = new QuadVertex[MaxVertices];

        /// @ todo add texture scale to shader
        const std::string vs = R"(
            #version 450 core

            layout(location=0) in vec3 a_Position;
            layout(location=1) in vec4 a_Color;
            layout(location=2) in vec2 a_TexCoord;
            layout(location=3) in float a_TexIndex;
            layout(location=4) in float a_TexScale;

            uniform mat4 u_VP;

            out vec4 v_Color;
            out vec2 v_TexCoord;
            flat out float v_TexIndex;
            out float v_TexScale;

            void main(){
                v_Color = a_Color;
                v_TexCoord = a_TexCoord;
                v_TexIndex = a_TexIndex;
                v_TexScale = a_TexScale;
                gl_Position = u_VP * vec4(a_Position, 1.0); 
            }
        )";

        const std::string fs = R"(
            #version 450 core
            out vec4 FragColor;

            uniform sampler2D u_Textures[32];

            in vec4 v_Color;
            in vec2 v_TexCoord;
            flat in float v_TexIndex;
            in float v_TexScale;

            void main(){
                FragColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TexScale) * v_Color;
            }
        )";

        s_Data.Shader = Shader::create(vs, fs);
        s_Data.Shader->bind();

        s_Data.WhiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

        s_Data.TextureSlots.fill(nullptr);
        s_Data.TextureSlots[0] = s_Data.WhiteTexture;

        int samplers[MaxTextureSlots];
        for (int i{}; i < MaxTextureSlots; ++i)
            samplers[i] = i;

        s_Data.Shader->uIntArray("u_Textures", samplers, MaxTextureSlots);

        s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

        s_Data.QuadTexCoords[0] = {0.0f, 0.0f};
        s_Data.QuadTexCoords[1] = {1.0f, 0.0f};
        s_Data.QuadTexCoords[2] = {1.0f, 1.0f};
        s_Data.QuadTexCoords[3] = {0.0f, 1.0f};
    }

    void Renderer2D::shutdown()
    {
        RAND_PROFILE_FUNCTION();

        delete[] s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::beginScene(OrthographicCamera* cam)
    {
        RAND_PROFILE_FUNCTION();

        s_Data.Camera = cam;

        if (!s_Data.Shader->isBound())
            s_Data.Shader->bind();

        s_Data.Shader->uMat4("u_VP", s_Data.Camera->getViewProjectionMatrix());

        startBatch();
    }

    void Renderer2D::endScene()
    {
        RAND_PROFILE_FUNCTION();

        flush();
    }

    void Renderer2D::startBatch()
    {
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
        s_Data.TextureSlotIndex = 1;
        s_Data.TextureSlots.fill(nullptr);
        s_Data.TextureSlots[0] = s_Data.WhiteTexture;
    }

    void Renderer2D::nextBatch()
    {
        flush();
        startBatch();
    }

    void Renderer2D::flush()
    {
        RAND_PROFILE_FUNCTION();

        if (!s_Data.QuadIndexCount)
            return;

        uint32_t dataSize = (s_Data.QuadVertexBufferPtr - s_Data.QuadVertexBufferBase) * sizeof(QuadVertex);
        s_Data.QuadVertexBuffer->setData(s_Data.QuadVertexBufferBase, dataSize);

        if (!s_Data.Shader->isBound())
            s_Data.Shader->bind();

        for (int i{}; i < MaxTextureSlots; ++i)
            if (s_Data.TextureSlots[i])
                s_Data.TextureSlots[i]->bind(i);
            else
                break;

        RenderCommand::drawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

        ++s_Data.Stats.DrawCalls;
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        RAND_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= MaxIndices)
            nextBatch();

        constexpr uint8_t quadIndexCount = 6;
        constexpr uint8_t quadVertexCount = 4;

        constexpr float whiteTextureIndex = 0.0f;

        for (uint8_t i{}; i < quadVertexCount; ++i)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = whiteTextureIndex;
            s_Data.QuadVertexBufferPtr->TexScale = 1.0f;
            ++s_Data.QuadVertexBufferPtr;
        }

        s_Data.QuadIndexCount += quadIndexCount;

#if RAND_ENABLE_RENDERER2D_STATISTICS
        ++s_Data.Stats.QuadCount;
#endif
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const Ref<Texture2D> texture,
        const float textureScale, const glm::vec4& color)
    {
        RAND_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= MaxIndices)
            nextBatch();

        float textureIndex = -1.0f;
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i)
            if (*s_Data.TextureSlots[i] == *texture)
            {
                textureIndex = (float)i;
                break;
            }

        if (textureIndex == -1.0f)
        {
            if (s_Data.TextureSlotIndex >= MaxTextureSlots - 1)
                nextBatch();

            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            ++s_Data.TextureSlotIndex;
        }

        constexpr uint8_t quadVertexCount = 4;
        constexpr uint8_t quadIndexCount = 6;

        for (uint8_t i{}; i < quadVertexCount; ++i)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TexScale = textureScale;
            ++s_Data.QuadVertexBufferPtr;
        }

        s_Data.QuadIndexCount += quadIndexCount;

#if RAND_ENABLE_RENDERER2D_STATISTICS
        ++s_Data.Stats.QuadCount;
#endif
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const Ref<SubTexture2D> subTexture,
        const float textureScale, const glm::vec4& color)
    {
        RAND_PROFILE_FUNCTION();

        if (s_Data.QuadIndexCount >= MaxIndices)
            nextBatch();

        Ref<Texture2D> texture = subTexture->getTexture();

        float textureIndex = -1.0f;
        for (uint8_t i = 1; i < s_Data.TextureSlotIndex; ++i)
            if (*s_Data.TextureSlots[i] == *texture)
            {
                textureIndex = (float)i;
                break;
            }

        if (textureIndex == -1.0f)
        {
            if (s_Data.TextureSlotIndex >= MaxTextureSlots - 1)
                nextBatch();

            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            ++s_Data.TextureSlotIndex;
        }

        constexpr uint8_t quadVertexCount = 4;
        constexpr uint8_t quadIndexCount = 6;

        const glm::vec2* textureCoords = subTexture->getTexCoords();

        for (uint8_t i{}; i < quadVertexCount; ++i)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TexScale = textureScale;
            ++s_Data.QuadVertexBufferPtr;
        }

        s_Data.QuadIndexCount += quadIndexCount;

#if RAND_ENABLE_RENDERER2D_STATISTICS
        ++s_Data.Stats.QuadCount;
#endif
    }

    Renderer2D::Statistics Renderer2D::getStats()
    {
#if RAND_ENABLE_RENDERER2D_STATISTICS
        return s_Data.Stats;
#else
        return {.DrawCalls = 0, .QuadCount = 0};
#endif
    }

    void Renderer2D::resetStats()
    {
#if RAND_ENABLE_RENDERER2D_STATISTICS
        memset(&s_Data.Stats, 0, sizeof(Renderer2D::Statistics));
#endif
    }

} // namespace Rand
