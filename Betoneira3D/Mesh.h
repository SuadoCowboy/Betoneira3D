#pragma once

#include <bgfx/bgfx.h>
#include <vector>

namespace Betoneira::Graphics {
    struct VertexData2D {
        float x, y, z;

        static bgfx::VertexLayout layout;
        static void init();
    };

    struct VertexData2DTextured : VertexData2D {
        float u, v; // Texture coordinates
        static void init();
    };

    struct VertexData3D : VertexData2D {
        float nx, ny, nz; // Normal
        static void init();
    };

    struct VertexData3DTextured : VertexData3D, VertexData2DTextured {
        static void init();
    };

    class Mesh {
    private:
        bgfx::VertexBufferHandle m_vertexBuffer;
        bgfx::IndexBufferHandle m_indexBuffer;
        uint32_t m_numIndices;

    public:
        Mesh(const std::vector<VertexData2D>& vertices, const std::vector<uint16_t>& indices);
        Mesh(const std::vector<VertexData2DTextured>& vertices, const std::vector<uint16_t>& indices);
        Mesh(const std::vector<VertexData3D>& vertices, const std::vector<uint16_t>& indices);
        Mesh(const std::vector<VertexData3DTextured>& vertices, const std::vector<uint16_t>& indices);

        void render();
        ~Mesh();
    };
}