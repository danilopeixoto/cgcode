// File:    Vector.h
// Author:  Danilo Peixoto
// Date:    12/08/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_VECTOR_H
#define CGC_VECTOR_H

#include <ostream>

// Declaração de tipo incompleto no cabeçalho evita dependência cíclica de arquivos
class Matrix2;
class Matrix3;
class Matrix4;

// Vetor real 1x2
class Vector2 {
public:
    // Componentes do vetor
    double x, y;

    // Construtor padrão (vetor zero)
    Vector2();
    // Construtor cópia
    Vector2(const Vector2 & vector2);
    // Construtor para valores iniciais
    Vector2(double x, double y);
    // Destrutor padrão
    ~Vector2();

    // Sobrecarga da operação "vetor[i]" (retorno mutável)
    double & operator [](size_t i);
    // Sobrecarga da operação "vetor[i]" (retorno imutável)
    const double & operator [](size_t i) const;
    // Sobrecarga da operação "+vetor"
    Vector2 operator +() const;
    // Sobrecarga da operação "-vetor"
    Vector2 operator -() const;
    // Sobrecarga da operação "vetorA + vetorB"
    Vector2 operator +(const Vector2 & rhs) const;
    // Sobrecarga da operação "vetorA - vetorB"
    Vector2 operator -(const Vector2 & rhs) const;
    // Sobrecarga da operação "vetor * matriz2"
    Vector2 operator *(const Matrix2 & rhs) const;
    // Sobrecarga da operação "matriz2 * vetor"
    friend Vector2 operator *(const Matrix2 & lhs, const Vector2 & rhs);
    // Sobrecarga da operação "vetor * matriz3"
    Vector2 operator *(const Matrix3 & rhs) const;
    // Sobrecarga da operação "matriz3 * vetor"
    friend Vector2 operator *(const Matrix3 & lhs, const Vector2 & rhs);
    // Sobrecarga da operação "vetor * escalar"
    Vector2 operator *(double rhs) const;
    // Sobrecarga da operação "escalar * vetor"
    friend Vector2 operator *(double lhs, const Vector2 & rhs);
    // Sobrecarga da operação "vetor / escalar"
    Vector2 operator /(double rhs) const;
    // Sobrecarga da operação "vetorA += vetorB"
    Vector2 & operator +=(const Vector2 & rhs);
    // Sobrecarga da operação "vetorA -= vetorB"
    Vector2 & operator -=(const Vector2 & rhs);
    // Sobrecarga da operação "vetor *= matrix2"
    Vector2 & operator *=(const Matrix2 & rhs);
    // Sobrecarga da operação "vetor *= matrix3"
    Vector2 & operator *=(const Matrix3 & rhs);
    // Sobrecarga da operação "vetor *= escalar"
    Vector2 & operator *=(double rhs);
    // Sobrecarga da operação "vetor /= escalar"
    Vector2 & operator /=(double rhs);
    // Sobrecarga da operação "vetorA == vetorB"
    bool operator ==(const Vector2 & rhs) const;
    // Sobrecarga da operação "vetorA != vetorB"
    bool operator !=(const Vector2 & rhs) const;
    // Sobrecarga da operação "saída << vetor" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Vector2 & rhs);

    // Retorna produto escalar
    double dot(const Vector2 & rhs) const;
    // Retorna produto vetorial
    double cross(const Vector2 & rhs) const;
    // Normaliza vetor (vetor unitário)
    Vector2 & normalize();
    // Retorna comprimento do vetor ao quadrado
    double length2() const;
    // Retorna comprimento do vetor
    double length() const;
};

// Vetor real 1x3
class Vector3 {
public:
    // Componentes do vetor
    double x, y, z;

    // Construtor padrão (vetor zero)
    Vector3();
    // Construtor cópia
    Vector3(const Vector3 & vector3);
    // Construtor para valores iniciais
    Vector3(double x, double y, double z);
    // Destrutor padrão
    ~Vector3();

    // Sobrecarga da operação "vetor[i]" (retorno mutável)
    double & operator [](size_t i);
    // Sobrecarga da operação "vetor[i]" (retorno imutável)
    const double & operator [](size_t i) const;
    // Sobrecarga da operação "+vetor"
    Vector3 operator +() const;
    // Sobrecarga da operação "-vetor"
    Vector3 operator -() const;
    // Sobrecarga da operação "vetorA + vetorB"
    Vector3 operator +(const Vector3 & rhs) const;
    // Sobrecarga da operação "vetorA - vetorB"
    Vector3 operator -(const Vector3 & rhs) const;
    // Sobrecarga da operação "vetor * matriz3"
    Vector3 operator *(const Matrix3 & rhs) const;
    // Sobrecarga da operação "matriz3 * vetor"
    friend Vector3 operator *(const Matrix3 & lhs, const Vector3 & rhs);
    // Sobrecarga da operação "vetor * matriz4"
    Vector3 operator *(const Matrix4 & rhs) const;
    // Sobrecarga da operação "matriz4 * vetor"
    friend Vector3 operator *(const Matrix4 & lhs, const Vector3 & rhs);
    // Sobrecarga da operação "vetor * escalar"
    Vector3 operator *(double rhs) const;
    // Sobrecarga da operação "escalar * vetor"
    friend Vector3 operator *(double lhs, const Vector3 & rhs);
    // Sobrecarga da operação "vetor / escalar"
    Vector3 operator /(double rhs) const;
    // Sobrecarga da operação "vetorA += vetorB"
    Vector3 & operator +=(const Vector3 & rhs);
    // Sobrecarga da operação "vetorA -= vetorB"
    Vector3 & operator -=(const Vector3 & rhs);
    // Sobrecarga da operação "vetor *= matrix3"
    Vector3 & operator *=(const Matrix3 & rhs);
    // Sobrecarga da operação "vetor *= matrix4"
    Vector3 & operator *=(const Matrix4 & rhs);
    // Sobrecarga da operação "vetor *= escalar"
    Vector3 & operator *=(double rhs);
    // Sobrecarga da operação "vetor /= escalar"
    Vector3 & operator /=(double rhs);
    // Sobrecarga da operação "vetorA == vetorB"
    bool operator ==(const Vector3 & rhs) const;
    // Sobrecarga da operação "vetorA != vetorB"
    bool operator !=(const Vector3 & rhs) const;
    // Sobrecarga da operação "saída << vetor" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Vector3 & rhs);

    // Retorna produto escalar
    double dot(const Vector3 & rhs) const;
    // Retorna produto triplo ou misto
    double triple(const Vector3 & a, const Vector3 & b) const;
    // Retorna produto vetorial
    Vector3 cross(const Vector3 & rhs) const;
    // Normaliza vetor (vetor unitário)
    Vector3 & normalize();
    // Retorna comprimento do vetor ao quadrado
    double length2() const;
    // Retorna comprimento do vetor
    double length() const;
};

#endif