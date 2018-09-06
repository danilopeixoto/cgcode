// File:    TriangleMesh.h
// Author:  Danilo Peixoto
// Date:    06/08/2018

// Evita redefini��o de s�mbolos do arquivo de cabe�alho (caso j� tenha sido inclu�do)
#ifndef CGC_TRIANGLE_MESH_H
#define CGC_TRIANGLE_MESH_H

#include <vector>
#include <ostream>

// Declara��o de tipo incompleto no cabe�alho evita depend�ncia c�clica de arquivos
class Vector2;
class Vector3;
class Matrix4;

// Geometria representada por tri�ngulos (v�rtices em ordem anti-hor�ria)
class TriangleMesh {
private:
    std::vector<Vector3> vertices; // Lista de v�rtices
    std::vector<Vector3> normals; // Lista de vetores normais
    std::vector<Vector2> textureCoordinates; // Lista de coordenadas de textura
    std::vector<size_t> vertexIndices; // Lista de �ndices de v�rtices por tri�ngulo
    std::vector<size_t> normalIndices; // Lista de �ndices de vetores normais por tri�ngulo
    std::vector<size_t> textureIndices; // Lista de �ndices de coordenadas de textura por tri�ngulo

public:
    // Construtor padr�o (geometria nula)
    TriangleMesh();
    // Construtor c�pia
    TriangleMesh(const TriangleMesh & triangleMesh);
    // Construtor para aloca��o de par�metros
    TriangleMesh(size_t vertexCount, size_t triangleCount,
        size_t normalCount = 0, size_t textureCoordinateCount = 0);
    // Construtor simples para par�metros iniciais
    TriangleMesh(
        const std::vector<Vector3> & vertices,
        const std::vector<size_t> & vertexIndices);
    // Construtor completo para par�metros iniciais
    TriangleMesh(
        const std::vector<Vector3> & vertices,
        const std::vector<Vector3> & normals,
        const std::vector<Vector2> & textureCoordinates,
        const std::vector<size_t> & vertexIndices,
        const std::vector<size_t> & normalIndices,
        const std::vector<size_t> & textureIndices);
    // Destrutor padr�o
    ~TriangleMesh();

    // Sobrecarga da opera��o "geometriaA == geometriaB"
    bool operator ==(const TriangleMesh & rhs) const;
    // Sobrecarga da opera��o "geometriaA != geometriaB"
    bool operator !=(const TriangleMesh & rhs) const;
    // Sobrecarga da opera��o "sa�da << geometria" (imprimir informa��es na sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const TriangleMesh & rhs);

    // Configura um v�rtice pelo �ndice
    TriangleMesh & setVertex(size_t i, const Vector3 & vertex);
    // Configura vetor normal pelo �ndice
    TriangleMesh & setNormal(size_t i, const Vector3 & normal);
    // Configura coordenadas de textura pelo �ndice
    TriangleMesh & setTextureCoordinates(size_t i, const Vector2 & textureCoordinates);
    // Configura os �ndices dos v�rtices de um tri�ngulo
    TriangleMesh & setVertexIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Configura os �ndices dos vetores normais de um tri�ngulo
    TriangleMesh & setNormalIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Configura os �ndices das coordenadas de textura de um tri�ngulo
    TriangleMesh & setTextureIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Retorna lista de v�rtices
    const std::vector<Vector3> & getVertices() const;
    // Retorna lista de vetores normais
    const std::vector<Vector3> & getNormals() const;
    // Retorna lista de coordenadas de textura
    const std::vector<Vector2> & getTextureCoordinates() const;
    // Retorna lista de �ndices de v�rtices por tri�ngulo
    const std::vector<size_t> & getVertexIndices() const;
    // Retorna lista de �ndices de vetores normais por tri�ngulo
    const std::vector<size_t> & getNormalIndices() const;
    // Retorna lista de �ndices de coordenadas de textura por tri�ngulo
    const std::vector<size_t> & getTextureIndices() const;
    // Retorna v�rtice pelo �ndice
    const Vector3 & getVertex(size_t i) const;
    // Retorna vetor normal pelo �ndice
    const Vector3 & getNormal(size_t i) const;
    // Retorna coordenadas de textura pelo �ndice
    const Vector2 & getTextureCoordinates(size_t i) const;
    // Retorna �ndices dos v�rtices de um tri�ngulo
    void getVertexIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna �ndices dos vetores normais de um tri�ngulo
    void getNormalIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna �ndices das coordenadas de textura de um tri�ngulo
    void getTextureIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna n�mero de v�rtices
    size_t getVertexCount() const;
    // Retorna n�mero de vetores normais
    size_t getNormalCount() const;
    // Retorna n�mero de coordenadas de textura
    size_t getTextureCoordinateCount() const;
    // Retorna n�mero de tri�ngulos
    size_t getTriangleCount() const;
    // Verifica se geometria tem vetores normais
    bool hasNormals() const;
    // Verifica se geometria tem coordenadas de textura
    bool hasTextureCoordinates() const;

    // Cria geometria por c�pia
    TriangleMesh & create(const TriangleMesh & triangleMesh);
    // Cria geometria alocando mem�ria para atributos
    TriangleMesh & create(
        size_t vertexCount, size_t triangleCount,
        size_t normalCount = 0, size_t textureCoordinateCount = 0);
    // Cria geometria com atributos b�sicos
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