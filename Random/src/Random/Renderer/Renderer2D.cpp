#include "Random/Renderer/Renderer2D.hpp"

#include "Random/Renderer/Buffer/VertexArray.hpp"
#include "Random/Renderer/Graphics/Shader.hpp"
#include "Random/Renderer/RenderCommand.hpp"

namespace Rand
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        ShaderLibrary Shaders;
        OrthographicCamera* Camera;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::init()
    {
        s_Data = new Renderer2DStorage;
        s_Data->QuadVertexArray = VertexArray::create();

        float squareVertices[5 * 4]{
            // clang-format off
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
            // clang-format on
        };

        Ref<VertexBuffer> squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
        squareVB->setLayout({{"a_Pos", ShaderDataType::Float3}, {"a_TexCoord", ShaderDataType::Float2}});
        s_Data->QuadVertexArray->addVertexBuffer(squareVB);

        uint32_t squareIndices[6]{0, 1, 2, 2, 3, 0};
        Ref<IndexBuffer> squareIB = IndexBuffer::create(squareIndices, 6);
        s_Data->QuadVertexArray->setIndexBuffer(squareIB);

        const std::string flatColorVS = R"(
            #version 330 core

            layout(location=0) in vec3 a_Pos;
            layout(location=1) in vec3 a_TexCoord;
            
            uniform mat4 u_MVP;

            void main(){
                gl_Position = u_MVP * vec4(a_Pos, 1.0); 
            }
        )";

        const std::string flatColorFS = R"(
            #version 330 core
            out vec4 FragColor;

            uniform vec4 u_Color;

            void main(){
                FragColor = u_Color;
            }
        )";

        const std::string TextureVS = R"(
            #version 330 core

            layout(location=0) in vec3 a_Pos;
            layout(location=1) in vec2 a_TexCoord;

            out vec2 v_TexCoord;
            
            uniform mat4 u_MVP;

            void main(){
                v_TexCoord = a_TexCoord;
                gl_Position = u_MVP * vec4(a_Pos, 1.0); 
            }
        )";

        const std::string textureFS = R"(
            #version 330 core
            out vec4 FragColor;

            in vec2 v_TexCoord;
            uniform sampler2D u_Texture;

            uniform int u_TextureScale ;
            uniform vec4 u_Tint;

            void main(){
                FragColor = texture(u_Texture, v_TexCoord * u_TextureScale) * u_Tint;
            }
        )";

        s_Data->Shaders.add("FlatColor", Shader::create(flatColorVS, flatColorFS));
        s_Data->Shaders.add("Texture", Shader::create(TextureVS, textureFS));
    }

    void Renderer2D::shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::beginScene(OrthographicCamera* cam)
    {
        s_Data->Camera = cam;
    }

    void Renderer2D::endScene() {}

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        s_Data->QuadVertexArray->bind();
        Ref<Shader> flatColorShader = s_Data->Shaders.get("FlatColor");

        flatColorShader->bind();
        flatColorShader->uMat4("u_MVP", s_Data->Camera->getViewProjectionMatrix() * transform);
        flatColorShader->uFloat4("u_Color", color);

        s_Data->QuadVertexArray->bind();
        RenderCommand::drawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const Ref<Texture2D> texture,
        const int textureScale, const glm::vec4& tint)
    {
        s_Data->QuadVertexArray->bind();
        Ref<Shader> textureShader = s_Data->Shaders.get("Texture");

        textureShader->bind();
        textureShader->uMat4("u_MVP", s_Data->Camera->getViewProjectionMatrix() * transform);

        texture->bind();
        textureShader->uInt("u_Texture", 0);
        textureShader->uInt("u_TextureScale", textureScale);
        textureShader->uFloat4("u_Tint", tint);

        s_Data->QuadVertexArray->bind();
        RenderCommand::drawIndexed(s_Data->QuadVertexArray);
    }

} // namespace Rand
