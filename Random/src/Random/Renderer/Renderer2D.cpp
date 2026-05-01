#include "Random/Renderer/Renderer2D.hpp"

#include "Random/Renderer/Buffer/VertexArray.hpp"
#include "Random/Renderer/Graphics/Shader.hpp"
#include "Random/Renderer/RenderCommand.hpp"

namespace Rand
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> FlatColorShader;
        OrthographicCamera* Camera;
    };

    static Renderer2DStorage* s_Data;

    /// @todo add more capabilities
    void Renderer2D::init()
    {
        s_Data = new Renderer2DStorage;
        s_Data->QuadVertexArray = VertexArray::create();

        float squareVertices[5 * 4]{
            // clang-format off
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
            // clang-format on
        };

        Ref<VertexBuffer> squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
        squareVB->setLayout({{"a_Position", ShaderDataType::Float3}});
        s_Data->QuadVertexArray->addVertexBuffer(squareVB);

        uint32_t squareIndices[6]{0, 1, 2, 2, 3, 0};
        Ref<IndexBuffer> squareIB = IndexBuffer::create(squareIndices, 6);
        s_Data->QuadVertexArray->setIndexBuffer(squareIB);

        const std::string flatColorVS = R"(
            #version 330 core

            layout(location=0) in vec3 a_Pos;
            layout(location=0) in vec2 a_TexCoord;
            
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

        s_Data->FlatColorShader = Shader::create(flatColorVS, flatColorFS);
    }

    void Renderer2D::shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::beginScene(OrthographicCamera* cam)
    {
        s_Data->Camera = cam;
    }

    void Renderer2D::endScene()
    {
        s_Data->FlatColorShader->unbind();
    }

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        s_Data->FlatColorShader->bind();
        s_Data->FlatColorShader->uMat4("u_MVP", s_Data->Camera->getViewProjectionMatrix() * transform);
        s_Data->FlatColorShader->uFloat4("u_Color", color);

        s_Data->QuadVertexArray->bind();
        RenderCommand::drawIndexed(s_Data->QuadVertexArray);
    }
} // namespace Rand
