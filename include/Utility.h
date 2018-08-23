// File:    Utility.h
// Author:  Danilo Peixoto
// Date:    15/08/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_UTILITY_H
#define CGC_UTILITY_H

#include <string>

// Declaração de tipo incompleto no cabeçalho evita dependência cíclica de arquivos
class TriangleMesh;
class Viewport3D;

// Instância de "viewport" 3D padrão
extern Viewport3D viewport3D;

// Lê objeto geométrico triangulado de um arquivo Wavefront OBJ
TriangleMesh * readObject(const std::string & filename);
// Escreve objeto geométrico triangulado para um arquivo Wavefront OBJ
bool writeObject(const std::string & filename, const TriangleMesh * triangleMesh);
// Exibe objeto geométrico em uma "viewport" 3D
void showObject(const TriangleMesh * triangleMesh);

#endif