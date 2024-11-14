#include "GeometryBuffer.h"
#include <stdexcept>

// factory method
std::shared_ptr<GeometryBuffer> GeometryBuffer::create(
    const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData,
    const std::vector<unsigned int>& indices,
    const std::string& name) {
    // factory implementation
    auto buffer = std::shared_ptr<GeometryBuffer>(new GeometryBuffer(name));
    // std::make_shared<GeometryBuffer>(name); <- this won't work
    // because even though std::make_shared is not restricted by the 
    // fact that create is static, it internally tries to access the 
    // constructor, and since the constructor is private, it can't.
    buffer->initializeBuffers(attributeData, indices);
    return buffer;
}

// default constructor
GeometryBuffer::GeometryBuffer(const std::string& name) :
    vao(0), vbo(0), ebo(0), vertexCount(0), indexCount(0), name(name) {}

// destructor
GeometryBuffer::~GeometryBuffer() {
    cleanupBuffers();
}

// move constructor
GeometryBuffer::GeometryBuffer(GeometryBuffer&& other) noexcept
    : vao(other.vao), vbo(other.vbo), ebo(other.ebo),
    vertexCount(other.vertexCount), indexCount(other.indexCount),
    attributeOffsets(std::move(other.attributeOffsets)),
    attributeInfos(std::move(other.attributeInfos)),
    name(std::move(other.name)) {

    other.vao = other.vbo = other.ebo = 0;
    other.vertexCount = other.indexCount = 0;
}

// move assignment operator
GeometryBuffer& GeometryBuffer::operator=(GeometryBuffer&& other) noexcept {
    if (this != &other) {
        // Clean up this object first
        cleanupBuffers();

        // Reassign the values from the other object
        vao = other.vao;
        vbo = other.vbo;
        ebo = other.ebo;
        vertexCount = other.vertexCount;
        indexCount = other.indexCount;
        attributeOffsets = std::move(other.attributeOffsets);
        attributeInfos = std::move(other.attributeInfos);
        name = std::move(other.name);

        // Reset other's resources
        other.vao = other.vbo = other.ebo = 0;
        other.vertexCount = other.indexCount = 0;
    }
    return *this;
}

// setup the buffers
void GeometryBuffer::initializeBuffers( 
    const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attributeData,
    const std::vector<unsigned int>& indices) {
    // 0. Pre-requisite: 
    // Since we don't know how many attributes, we have to calculate 
    // the total buffer size and attribute offsets
    GLsizeiptr totalSize = 0;
    unsigned int offset = 0;
    for (const auto& [attr, data] : attributeData) {
        attributeOffsets[attr] = offset;
        offset += data.second.size * sizeof(float);
        totalSize += data.first.size() * sizeof(float);
        attributeInfos[attr] = data.second;
    }
    // We also initialize the vertex count from attributeData and index count from indices vector size
    auto it = attributeData.begin();
    vertexCount = it->second.first.size() / it->second.second.size;
    indexCount = indices.size();
    
    // 1. Create the buffer and get the pointers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // 2. Bind the VAO. All setup below will be stored in the VAO
    glBindVertexArray(vao);

    // 4. Allocate the VBO. All setup below will be store in this VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, totalSize, it->second.first.data(), GL_STATIC_DRAW);

    // 5. Filling out the VBO. Each attribute at a time
    GLuint attrLocation = 0;
    for (const auto& [attr, data] : attributeData) {
        const auto& [attrData, attrInfo] = data;
        // subdata because we have sections of data (for positions, colors, etc)
       /* glBufferSubData(GL_ARRAY_BUFFER, attributeOffsets[attr], 
            attrData.size() * sizeof(float), attrData.data());*/
        glVertexAttribPointer(attrLocation, attrInfo.size, attrInfo.type,
            attrInfo.normalized, attrInfo.stride, (void*)attributeOffsets[attr]);
        glEnableVertexAttribArray(attrLocation);
        attrLocation++;
    }

    // 6. Setup EBO (index or element buffer)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    // 7. UnBind everything
    glBindVertexArray(0);

    // 8. store the index data to allow share the geometrybuffer completely
    this->indexData = indices;
}

// update the data in the vertex buffer in a specific attribute
void GeometryBuffer::updateVertexAttribute(Attribute attr, const std::vector<float>& newData) {
    if (!hasAttribute(attr)) {
        throw std::runtime_error("Attribute not found in buffer");
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, attributeOffsets[attr], newData.size() * sizeof(float), newData.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// update data of the indices buffer
void GeometryBuffer::updateIndices(const std::vector<unsigned int>& newIndices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, newIndices.size() * sizeof(unsigned int), newIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    indexCount = newIndices.size();
}

// attach the vao
void GeometryBuffer::bind() const {
    glBindVertexArray(vao);
}


// dettach the vao
void GeometryBuffer::unbind() const {
    glBindVertexArray(0);
}

bool GeometryBuffer::hasAttribute(Attribute attr) const {
    return attributeOffsets.find(attr) != attributeOffsets.end();
}

// delete the buffers from GPU
void GeometryBuffer::cleanupBuffers() {
    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
    if (vbo != 0) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }
    if (ebo != 0) {
        glDeleteBuffers(1, &ebo);
        ebo = 0;
    }
}