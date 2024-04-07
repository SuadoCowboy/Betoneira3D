#include "Mesh.h"

using namespace Betoneira::Graphics;

bgfx::VertexLayout Betoneira::Graphics::VertexData2D::layout;

void VertexData2D::init() {
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .end();
}

void VertexData2DTextured::init() {
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
}

void VertexData3D::init() {
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
        .end();
}

void VertexData3DTextured::init() {
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
}

Mesh::Mesh(const std::vector<VertexData2D>& vertices, const std::vector<uint16_t>& indices) : m_numIndices(static_cast<uint32_t>(indices.size())) {
    m_vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(), vertices.size() * sizeof(VertexData2D)), VertexData2D::layout);
    m_indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size() * sizeof(uint16_t)));
}

Mesh::Mesh(const std::vector<VertexData2DTextured>& vertices, const std::vector<uint16_t>& indices) : m_numIndices(static_cast<uint32_t>(indices.size())) {
    m_vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(), vertices.size() * sizeof(VertexData2DTextured)), VertexData2DTextured::layout);
    m_indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size() * sizeof(uint16_t)));
}

Mesh::Mesh(const std::vector<VertexData3D>& vertices, const std::vector<uint16_t>& indices) : m_numIndices(static_cast<uint32_t>(indices.size())) {
    m_vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(), vertices.size() *sizeof(VertexData3D)), VertexData3D::layout);
    m_indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size() * sizeof(uint16_t)));
}

Mesh::Mesh(const std::vector<VertexData3DTextured>& vertices, const std::vector<uint16_t>& indices) : m_numIndices(static_cast<uint32_t>(indices.size())) {
    m_vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(), vertices.size() * sizeof(VertexData3DTextured)), VertexData3DTextured::layout);
    m_indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size() *sizeof(uint16_t)));
}

void Mesh::render() {
    bgfx::setVertexBuffer(0, m_vertexBuffer);
    bgfx::setIndexBuffer(m_indexBuffer);
}

Mesh::~Mesh() {
    bgfx::destroy(m_vertexBuffer);
    bgfx::destroy(m_indexBuffer);
}