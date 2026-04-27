#pragma once

#include "Random/Renderer/Graphics/Material.hpp"
#include "Random/Renderer/Graphics/Mesh.hpp"
#include "Random/Renderer/Graphics/camera.hpp"
#include "RandomPch.hpp"
#include "glm/glm.hpp"

namespace Rand
{
    struct RenderInfo
    {
        Ref<Mesh> Mesh;
        Ref<Material> Material;
        glm::mat4 transform;
    };

    class RenderQueues
    {
      public:
        void swap() { std::swap(m_Front, m_Back); }
        bool isBackEmpty() { return m_Back.empty(); }
        void clearBack() { m_Back.clear(); }

        std::vector<RenderInfo>& getActiveCommandInfos() { return m_Front; }

      private:
        std::vector<RenderInfo> m_Front;
        std::vector<RenderInfo> m_Back;
    };

    class Renderer3D
    {
      public:
        void flush(Camera& cam)
        {
            if (m_Queues.isBackEmpty())
                return;

            m_Queues.swap();
            m_Queues.clearBack();

            for (RenderInfo& cmd : m_Queues.getActiveCommandInfos())
            {
                cmd.Material->Shader->bind();
                cmd.Material->Shader->uMat4("u_Model", cmd.transform);
                cmd.Material->Shader->uMat4("u_VP", cam.getViewProjectionMatrix());
                cmd.Material->Texture
            }
        }

      private:
        RenderQueues m_Queues;
    };
} // namespace Rand
