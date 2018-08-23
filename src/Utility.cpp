// File:    Utility.cpp
// Author:  Danilo Peixoto
// Date:    15/08/2018

#include <Utility.h>
#include <Vector.h>
#include <TriangleMesh.h>
#include <Viewport.h>

#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

Viewport3D viewport3D;

TriangleMesh * readObject(const std::string & filename) {
    std::ifstream file(filename, std::ifstream::in);

    if (!file.is_open())
        return nullptr;

    std::vector<Vector3> vertices, normals;
    std::vector<Vector2> textureCoordinates;
    std::vector<size_t> vertexIndices, normalIndices, textureIndices;

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream attributes(line);

        std::string type;
        attributes >> type;

        if (type == "v") {
            Vector3 vertex;
            attributes >> vertex.x >> vertex.y >> vertex.z;

            vertices.push_back(vertex);
        }
        else if (type == "vt") {
            Vector2 uvCoordinates;
            attributes >> uvCoordinates.x >> uvCoordinates.y;

            textureCoordinates.push_back(uvCoordinates);
        }
        else if (type == "vn") {
            Vector3 normal;
            attributes >> normal.x >> normal.y >> normal.z;

            normals.push_back(normal);
        }
        else if (type == "f") {
            for (size_t i = 0; i < 3; i++) {
                std::string tokens;
                attributes >> tokens;

                std::replace(tokens.begin(), tokens.end(), '/', ' ');

                std::istringstream indices(tokens);
                size_t index;

                indices >> index;
                vertexIndices.push_back(index - 1);

                if (indices.peek() == ' ') {
                    indices.ignore();

                    if (indices.peek() == ' ') {
                        indices.ignore();

                        indices >> index;
                        normalIndices.push_back(index - 1);
                    }
                    else {
                        indices >> index;
                        textureIndices.push_back(index - 1);

                        if (indices.peek() == ' ') {
                            indices.ignore();

                            indices >> index;
                            normalIndices.push_back(index - 1);
                        }
                    }
                }
            }
        }
    }

    file.close();

    return new TriangleMesh(vertices, normals, textureCoordinates,
        vertexIndices, normalIndices, textureIndices);
}
bool writeObject(const std::string & filename, const TriangleMesh * triangleMesh) {
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open())
        return false;

    file.setf(std::ofstream::fixed);
    file.precision(5);

    for (size_t i = 0; i < triangleMesh->getVertexCount(); i++) {
        const Vector3 & vertex = triangleMesh->getVertex(i);
        file << "v " << vertex.x << ' ' << vertex.y << ' ' << vertex.z << std::endl;
    }

    for (size_t i = 0; i < triangleMesh->getTextureCoordinateCount(); i++) {
        const Vector2 & uvCoordinates = triangleMesh->getTextureCoordinates(i);
        file << "vt " << uvCoordinates.x << ' ' << uvCoordinates.y << std::endl;
    }

    for (size_t i = 0; i < triangleMesh->getNormalCount(); i++) {
        const Vector3 & normal = triangleMesh->getNormal(i);
        file << "vn " << normal.x << ' ' << normal.y << ' ' << normal.z << std::endl;
    }

    size_t triangleCount = triangleMesh->getTriangleCount();

    bool hasNormals = triangleMesh->hasNormals();
    bool hasTextureCoordinates = triangleMesh->hasTextureCoordinates();

    for (size_t i = 0; i < triangleCount; i++) {
        size_t vertexIndices[3], textureIndices[3], normalIndices[3];

        triangleMesh->getVertexIndices(i, vertexIndices[0], vertexIndices[1], vertexIndices[2]);

        if (hasTextureCoordinates)
            triangleMesh->getTextureIndices(i, textureIndices[0], textureIndices[1], textureIndices[2]);

        if (hasNormals)
            triangleMesh->getNormalIndices(i, normalIndices[0], normalIndices[1], normalIndices[2]);

        file << "f ";

        for (size_t j = 0; j < 3; j++) {
            file << vertexIndices[j] + 1;

            if (hasTextureCoordinates)
                file << '/' << textureIndices[j] + 1;

            if (hasNormals) {
                if (!hasTextureCoordinates)
                    file << '/';

                file << '/' << normalIndices[j] + 1;
            }

            if (j < 2)
                file << ' ';
        }

        if (i < triangleCount - 1)
            file << std::endl;
    }

    file.close();

    return true;
}
void showObject(const TriangleMesh * triangleMesh) {
    viewport3D.clear();
    viewport3D.add(triangleMesh);

    viewport3D.show();
}