#include "Random/Renderer/Renderer2D.hpp"

#include "Random/Debug/Instrumentor.hpp"
#include "Random/Renderer/Buffer/VertexArray.hpp"
#include "Random/Renderer/Graphics/Shader.hpp"
#include "Random/Renderer/RenderCommand.hpp"

static constexpr uint32_t MaxQuads = 10000;
static constexpr uint32_t MaxVertices = 10000 * 4;
static constexpr uint32_t MaxIndices = 10000 * 6;

namespace Rand
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexID;
    };

    struct Renderer2DData
    {
        Ref<VertexArray> QuadVertexArray = nullptr;
        Ref<VertexBuffer> QuadVertexBuffer = nullptr;
        Ref<Shader> Shader = nullptr;
        Ref<Texture2D> WhiteTexture = nullptr;
        OrthographicCamera* Camera = nullptr;

        uint32_t QuadIndexCount = 0;
        QuadVertex* quadVertexBufferBase = nullptr;
        QuadVertex* quadVertexBufferPtr = nullptr;
    };

    static Renderer2DData s_Data;

    void Renderer2D::init()
    {
        RAND_PROFILE_FUNCTION();

        s_Data.QuadVertexArray = VertexArray::create();

        s_Data.QuadVertexBuffer = VertexBuffer::create(nullptr, sizeof(QuadVertex) * MaxVertices);
        s_Data.QuadVertexBuffer->setLayout(
            {{"a_Position", ShaderDataType::Float3}, {"a_Color", ShaderDataType::Float4},
                {"a_TexCoord", ShaderDataType::Float2}, {"a_TexID", ShaderDataType::Float}});
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

        s_Data.quadVertexBufferBase = new QuadVertex[MaxVertices];

        s_Data.WhiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

        const std::string vs = R"(
            #version 330 core

            layout(location=0) in vec3 a_Position;
            layout(location=1) in vec4 a_Color;
            layout(location=2) in vec2 a_TexCoord;
            layout(location=3) in int a_TexID;

            uniform mat4 u_VP;

            out vec4 v_Color;
            out vec2 v_TexCoord;

            void main(){
                v_Color = a_Color;
                v_TexCoord = a_TexCoord;
                gl_Position = u_VP * vec4(a_Position, 1.0); 
            }
        )";

        const std::string fs = R"(
            #version 330 core
            out vec4 FragColor;

            uniform sampler2D u_Texture;

            in vec4 v_Color;
            in vec2 v_TexCoord;

            uniform float u_TextureScale;
            uniform vec4 u_Color;

            void main(){
                FragColor = v_Color;/* texture(u_Texture, v_TexCoord * u_TextureScale) * u_Color; */
            }
        )";

        s_Data.Shader = Shader::create(vs, fs);
    }

    void Renderer2D::shutdown()
    {
        RAND_PROFILE_FUNCTION();

        delete[] s_Data.quadVertexBufferBase;
    }

    void Renderer2D::beginScene(OrthographicCamera* cam)
    {
        RAND_PROFILE_FUNCTION();

        s_Data.Camera = cam;
        s_Data.QuadIndexCount = 0;
        s_Data.quadVertexBufferPtr = s_Data.quadVertexBufferBase;
    }

    void Renderer2D::endScene()
    {
        RAND_PROFILE_FUNCTION();

        uint32_t dataSize = (s_Data.quadVertexBufferPtr - s_Data.quadVertexBufferBase) * sizeof(QuadVertex);
        s_Data.QuadVertexBuffer->setData(s_Data.quadVertexBufferBase, dataSize);

        flush();
    }

    void Renderer2D::flush()
    {
        RAND_PROFILE_FUNCTION();

        if (!s_Data.Shader->isBound())
            s_Data.Shader->bind();

        s_Data.Shader->uMat4("u_VP", s_Data.Camera->getViewProjectionMatrix());

        RenderCommand::drawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    }

    void Renderer2D::drawQuad(
        const glm::vec3& position, const glm::vec2& scale, const glm::mat4& rotation, const glm::vec4& color)
    {
        RAND_PROFILE_FUNCTION();

        s_Data.quadVertexBufferPtr->Position = position;
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.quadVertexBufferPtr->Position = {position.x + scale.x, position.y, position.z};
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.quadVertexBufferPtr->Position = {position.x + scale.x, position.y + scale.y, position.z};
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.quadVertexBufferPtr->Position = {position.x, position.y + scale.y, position.z};
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        // s_Data.WhiteTexture->bind();
        // s_Data.Shader->uInt("u_Texture", 0);
        // s_Data.Shader->uFloat("u_TextureScale", 1.0f);
        // s_Data.Shader->uFloat4("u_Color", color);

        // s_Data.QuadVertexArray->bind();
        // RenderCommand::drawIndexed(s_Data.QuadVertexArray);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const Ref<Texture2D> texture,
        const float textureScale, const glm::vec4& color, const glm::vec2& scale, const glm::mat4& rotation)
    {
        RAND_PROFILE_FUNCTION();

        s_Data.quadVertexBufferPtr->Position = position;
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.quadVertexBufferPtr->Position = {position.x + scale.x, position.y, position.z};
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.quadVertexBufferPtr->Position = {position.x + scale.x, position.y + scale.y, position.z};
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.quadVertexBufferPtr->Position = {position.x, position.y + scale.y, position.z};
        s_Data.quadVertexBufferPtr->Color = color;
        s_Data.quadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
        s_Data.quadVertexBufferPtr->TexID = 0;
        s_Data.quadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        // s_Data.QuadVertexArray->bind();

        if (!s_Data.Shader->isBound())
            s_Data.Shader->bind();

        s_Data.Shader->uMat4("u_MVP",
            s_Data.Camera->getViewProjectionMatrix() * glm::translate(rotation, position) *
                glm::scale(glm::mat4(1.0f), {scale, 1.0f}));

        // texture->bind();
        // s_Data.Shader->uInt("u_Texture", 0);
        // s_Data.Shader->uFloat("u_TextureScale", textureScale);
        // s_Data.Shader->uFloat4("u_Color", color);

        // s_Data.QuadVertexArray->bind();
        // RenderCommand::drawIndexed(s_Data.QuadVertexArray);
    }
} // namespace Rand
