#pragma once

#include "Random/Renderer/Graphics/OrthographicCamera.hpp"
#include "Random/Renderer/RenderCommand.hpp"
#include "Random/Renderer/RendererAPI.hpp"

namespace Rand
{
    class Renderer
    {
      public:
        /**
         * @brief Starts current scene
         */
        static void beginScene(OrthographicCamera& camera)
        {
            s_SceneData->ViewProjectionMatrix = camera.getViewProjectionMatrix();
        }

        /**
         * @brief Ends current scene
         */
        static void endScene() {}

        /*
         * @brief Submits a draw command
         *
         * @param vertexArray a Ref (so it won't get destroyed on a different thread) to the object which contains the
         * state of what you want to draw
         */
        static void submit(const Ref<Shader> shader, const Ref<VertexArray> vertexArray)
        {
            shader->bind();
            shader->uMat4("u_VP", s_SceneData->ViewProjectionMatrix);

            vertexArray->bind();
            RenderCommand::drawIndexed(vertexArray);
        }

        /**
         * @return The currently used RenderAPI
         */
        static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

      private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix{};
        };

        static SceneData* s_SceneData;
    };
} // namespace Rand
