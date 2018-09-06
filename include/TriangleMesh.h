// File:    TriangleMesh.h
// Author:  Danilo Peixoto
// Date:    06/08/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_TRIANGLE_MESH_H
#define CGC_TRIANGLE_MESH_H

#include <vector>
#include <ostream>

// Declaração de tipo incompleto no cabeçalho evita dependência cíclica de arquivos
class Vector2;
class Vector3;
class Matrix4;

// Geometria representada por triângulos (vértices em ordem anti-horária)
class TriangleMesh {
private:
    std::vector<Vector3> vertices; // Lista de vértices
    std::vector<Vector3> normals; // Lista de vetores normais
    std::vector<Vector2> textureCoordinates; // Lista de coordenadas de textura
    std::vector<size_t> vertexIndices; // Lista de índices de vértices por triângulo
    std::vector<size_t> normalIndices; // Lista de índices de vetores normais por triângulo
    std::vector<size_t> textureIndices; // Lista de índices de coordenadas de textura por triângulo

public:
    // Construtor padrão (geometria nula)
    TriangleMesh();
    // Construtor cópia
    TriangleMesh(const TriangleMesh & triangleMesh);
    // Construtor para alocação de parâmetros
    TriangleMesh(size_t vertexCount, size_t triangleCount,
        size_t normalCount = 0, size_t textureCoordinateCount = 0);
    // Construtor simples para parâmetros iniciais
    TriangleMesh(
        const std::vector<Vector3> & vertices,
        const std::vector<size_t> & vertexIndices);
    // Construtor completo para parâmetros iniciais
    TriangleMesh(
        const std::vector<Vector3> & vertices,
        const std::vector<Vector3> & normals,
        const std::vector<Vector2> & textureCoordinates,
        const std::vector<size_t> & vertexIndices,
        const std::vector<size_t> & normalIndices,
        const std::vector<size_t> & textureIndices);
    // Destrutor padrão
    ~TriangleMesh();

    // Sobrecarga da operação "geometriaA == geometriaB"
    bool operator ==(const TriangleMesh & rhs) const;
    // Sobrecarga da operação "geometriaA != geometriaB"
    bool operator !=(const TriangleMesh & rhs) const;
    // Sobrecarga da operação "saída << geometria" (imprimir informações na saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const TriangleMesh & rhs);

    // Configura um vértice pelo índice
    TriangleMesh & setVertex(size_t i, const Vector3 & vertex);
    // Configura vetor normal pelo índice
    TriangleMesh & setNormal(size_t i, const Vector3 & normal);
    // Configura coordenadas de textura pelo índice
    TriangleMesh & setTextureCoordinates(size_t i, const Vector2 & textureCoordinates);
    // Configura os índices dos vértices de um triângulo
    TriangleMesh & setVertexIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Configura os índices dos vetores normais de um triângulo
    TriangleMesh & setNormalIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Configura os índices das coordenadas de textura de um triângulo
    TriangleMesh & setTextureIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Retorna lista de vértices
    const std::vector<Vector3> & getVertices() const;
    // Retorna lista de vetores normais
    const std::vector<Vector3> & getNormals() const;
    // Retorna lista de coordenadas de textura
    const std::vector<Vector2> & getTextureCoordinates() const;
    // Retorna lista de índices de vértices por triângulo
    const std::vector<size_t> & getVertexIndices() const;
    // Retorna lista de índices de vetores normais por triângulo
    const std::vector<size_t> & getNormalIndices() const;
    // Retorna lista de índices de coordenadas de textura por triângulo
    const std::vector<size_t> & getTextureIndices() const;
    // Retorna vértice pelo índice
    const Vector3 & getVertex(size_t i) const;
    // Retorna vetor normal pelo índice
    const Vector3 & getNormal(size_t i) const;
    // Retorna coordenadas de textura pelo índice
    const Vector2 & getTextureCoordinates(size_t i) const;
    // Retorna índices dos vértices de um triângulo
    void getVertexIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna índices dos vetores normais de um triângulo
    void getNormalIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna índices das coordenadas de textura de um triângulo
    void getTextureIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna número de vértices
    size_t getVertexCount() const;
    // Retorna número de vetores normais
    size_t getNormalCount() const;
    // Retorna número de coordenadas de textura
    size_t getTextureCoordinateCount() const;
    // Retorna número de triângulos
    size_t getTriangleCount() const;
    // Verifica se geometria tem vetores normais
    bool hasNormals() const;
    // Verifica se geometria tem coordenadas de textura
    bool hasTextureCoordinates() const;

    // Cria geometria por cópia
    TriangleMesh & create(const TriangleMesh & triangleMesh);
    // Cria geometria alocando memória para atributos
    TriangleMesh & create(
        size_t vertexCount, size_t triangleCount,
        size_t normalCount = 0, size_t textureCoordinateCount = 0);
    // Cria geometria com atributos básicos
    TriangleMesh & create(
        const std::vector<Vector3> & vertices,
        const std::vector<size_t> & vertexIndices);
    // Cria geometria com todos atributos
    TriangleMesh & create(
        const std::vector<Vector3> & vertices,
        const std::vector<Vector3> & normals,
        const std::vector<Vector2> & textureCoordinates,
        const std::vector<size_t> & vertexIndices,
        const std::vector<size_t> & normalIndices,
        const std::vector<size_t> & textureIndices);

    // Transforma geometria utilizando matriz 4x4
    TriangleMesh & transform(const Matrix4 & transformation);
};

#endif