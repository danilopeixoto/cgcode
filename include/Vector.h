// File:    Vector.h
// Author:  Danilo Peixoto
// Date:    02/08/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_VECTOR_H
#define CGC_VECTOR_H

// Bibliotecas
#include <ostream>
#include <cmath>
#include <Matrix.h>

// Vetor real 1x2
class Vector2 {
public:
    // Componentes do vetor
    double x, y;

    // Construtor padrão (vetor zero)
    Vector2() : x(0), y(0) {}
    // Construtor cópia
    Vector2(const Vector2 & vector2) : x(vector2.x), y(vector2.y) {}
    // Construtor para valores iniciais
    Vector2(double x, double y) : x(x), y(y) {}

    // Sobrecarga da operação "vetor[i]" (retorno mutável)
    double & operator [](unsigned int i) {
        return (&x)[i];
    }
    // Sobrecarga da operação "vetor[i]" (retornon imutável)
    const double & operator [](unsigned int i) const {
        return (&x)[i];
    }
    // Sobrecarga da operação "+vetor"
    Vector2 operator +() const {
        return *this;
    }
    // Sobrecarga da operação "-vetor"
    Vector2 operator -() const {
        return Vector2(-x, -y);
    }
    // Sobrecarga da operação "vetorA + vetorB"
    Vector2 operator +(const Vector2 & rhs) const {
        return Vector2(*this) += rhs;
    }
    // Sobrecarga da operação "vetorA - vetorB"
    Vector2 operator -(const Vector2 & rhs) const {
        return Vector2(*this) -= rhs;
    }
    // Sobrecarga da operação "vetor * matriz2"
    Vector2 operator *(const Matrix2 & rhs) const {
        return Vector2(*this) *= rhs;
    }
    // Sobrecarga da operação "matriz2 * vetor"
    friend Vector2 operator *(const Matrix2 & lhs, const Vector2 & rhs) {
        return Vector2(
            rhs.x * lhs[0][0] + rhs.y * lhs[0][1],
            rhs.x * lhs[1][0] + rhs.y * lhs[1][1]);
    }
    // Sobrecarga da operação "vetor * matriz3"
    Vector2 operator *(const Matrix3 & rhs) const {
        return Vector2(*this) *= rhs;
    }
    // Sobrecarga da operação "matriz3 * vetor"
    friend Vector2 operator *(const Matrix3 & lhs, const Vector2 & rhs) {
        return Vector2(
            rhs.x * lhs[0][0] + rhs.y * lhs[0][1] + lhs[0][2],
            rhs.x * lhs[1][0] + rhs.y * lhs[1][1] + lhs[1][2]);
    }
    // Sobrecarga da operação "vetor * escalar"
    Vector2 operator *(double rhs) const {
        return Vector2(*this) *= rhs;
    }
    // Sobrecarga da operação "escalar * vetor"
    friend Vector2 operator *(double lhs, const Vector2 & rhs) {
        return rhs * lhs;
    }
    // Sobrecarga da operação "vetor / escalar"
    Vector2 operator /(double rhs) const {
        return Vector2(*this) /= rhs;
    }
    // Sobrecarga da operação "vetorA += vetorB"
    Vector2 & operator +=(const Vector2 & rhs) {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }
    // Sobrecarga da operação "vetorA -= vetorB"
    Vector2 & operator -=(const Vector2 & rhs) {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }
    // Sobrecarga da operação "vetor *= matrix2"
    Vector2 & operator *=(const Matrix2 & rhs) {
        double t = x;

        x = x * rhs[0][0] + y * rhs[1][0];
        y = t * rhs[0][1] + y * rhs[1][1];

        return *this;
    }
    // Sobrecarga da operação "vetor *= matrix3"
    Vector2 & operator *=(const Matrix3 & rhs) {
        double t = x;

        x = x * rhs[0][0] + y * rhs[1][0] + rhs[2][0];
        y = t * rhs[0][1] + y * rhs[1][1] + rhs[2][1];

        return *this;
    }
    // Sobrecarga da operação "vetor *= escalar"
    Vector2 & operator *=(double rhs) {
        x *= rhs;
        y *= rhs;

        return *this;
    }
    // Sobrecarga da operação "vetor /= escalar"
    Vector2 & operator /=(double rhs) {
        x /= rhs;
        y /= rhs;

        return *this;
    }
    // Sobrecarga da operação "vetorA == vetorB"
    bool operator ==(const Vector2 & rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    // Sobrecarga da operação "vetorA != vetorB"
    bool operator !=(const Vector2 & rhs) const {
        return !(*this == rhs);
    }
    // Sobrecarga da operação "stream << vetor" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Vector2 & rhs) {
        return lhs << '(' << rhs.x << ' ' << rhs.y << ')';
    }

    // Retorna produto escalar
    double dot(const Vector2 & rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    // Retorna produto vetorial
    double cross(const Vector2 & rhs) const {
        return x * rhs.y - y * rhs.x;
    }
    // Normaliza vetor (vetor unitário)
    Vector2 & normalize() {
        double l2 = length2();

        if (l2 > 0)
            *this /= std::sqrt(l2);

        return *this;
    }
    // Retorna comprimento do vetor ao quadrado
    double length2() const {
        return dot(*this);
    }
    // Retorna comprimento do vetor
    double length() const {
        return std::sqrt(length2());
    }
};

// Vetor real 1x3
class Vector3 {
public:
    // Componentes do vetor
    double x, y, z;

    // Construtor padrão (vetor zero)
    Vector3() : x(0), y(0), z(0) {}
    // Construtor cópia
    Vector3(const Vector3 & vector3) : x(vector3.x), y(vector3.y), z(vector3.z) {}
    // Construtor para valores iniciais
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    // Sobrecarga da operação "vetor[i]" (retorno mutável)
    double & operator [](unsigned int i) {
        return (&x)[i];
    }
    // Sobrecarga da operação "vetor[i]" (retornon imutável)
    const double & operator [](unsigned int i) const {
        return (&x)[i];
    }
    // Sobrecarga da operação "+vetor"
    Vector3 operator +() const {
        return *this;
    }
    // Sobrecarga da operação "-vetor"
    Vector3 operator -() const {
        return Vector3(-x, -y, -z);
    }
    // Sobrecarga da operação "vetorA + vetorB"
    Vector3 operator +(const Vector3 & rhs) const {
        return Vector3(*this) += rhs;
    }
    // Sobrecarga da operação "vetorA - vetorB"
    Vector3 operator -(const Vector3 & rhs) const {
        return Vector3(*this) -= rhs;
    }
    // Sobrecarga da operação "vetor * matriz3"
    Vector3 operator *(const Matrix3 & rhs) const {
        return Vector3(*this) *= rhs;
    }
    // Sobrecarga da operação "matriz3 * vetor"
    friend Vector3 operator *(const Matrix3 & lhs, const Vector3 & rhs) {
        return Vector3(
            rhs.x * lhs[0][0] + rhs.y * lhs[0][1] + rhs.z * lhs[0][2],
            rhs.x * lhs[1][0] + rhs.y * lhs[1][1] + rhs.z * lhs[1][2],
            rhs.x * lhs[2][0] + rhs.y * lhs[2][1] + rhs.z * lhs[2][2]);
    }
    // Sobrecarga da operação "vetor * matriz4"
    Vector3 operator *(const Matrix4 & rhs) const {
        return Vector3(*this) *= rhs;
    }
    // Sobrecarga da operação "matriz4 * vetor"
    friend Vector3 operator *(const Matrix4 & lhs, const Vector3 & rhs) {
        return Vector3(
            rhs.x * lhs[0][0] + rhs.y * lhs[0][1] + rhs.z * lhs[0][2] + lhs[0][3],
            rhs.x * lhs[1][0] + rhs.y * lhs[1][1] + rhs.z * lhs[1][2] + lhs[1][3],
            rhs.x * lhs[2][0] + rhs.y * lhs[2][1] + rhs.z * lhs[2][2] + lhs[2][3]);
    }
    // Sobrecarga da operação "vetor * escalar"
    Vector3 operator *(double rhs) const {
        return Vector3(*this) *= rhs;
    }
    // Sobrecarga da operação "escalar * vetor"
    friend Vector3 operator *(double lhs, const Vector3 & rhs) {
        return rhs * lhs;
    }
    // Sobrecarga da operação "vetor / escalar"
    Vector3 operator /(double rhs) const {
        return Vector3(*this) /= rhs;
    }
    // Sobrecarga da operação "vetorA += vetorB"
    Vector3 & operator +=(const Vector3 & rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }
    // Sobrecarga da operação "vetorA -= vetorB"
    Vector3 & operator -=(const Vector3 & rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }
    // Sobrecarga da operação "vetor *= matrix3"
    Vector3 & operator *=(const Matrix3 & rhs) {
        Vector3 t(*this);

        x = t.x * rhs[0][0] + t.y * rhs[1][0] + t.z * rhs[2][0];
        y = t.x * rhs[0][1] + t.y * rhs[1][1] + t.z * rhs[2][1];
        z = t.x * rhs[0][2] + t.y * rhs[1][2] + t.z * rhs[2][2];

        return *this;
    }
    // Sobrecarga da operação "vetor *= matrix4"
    Vector3 & operator *=(const Matrix4 & rhs) {
        Vector3 t(*this);

        x = t.x * rhs[0][0] + t.y * rhs[1][0] + t.z * rhs[2][0] + rhs[3][0];
        y = t.x * rhs[0][1] + t.y * rhs[1][1] + t.z * rhs[2][1] + rhs[3][1];
        z = t.x * rhs[0][2] + t.y * rhs[1][2] + t.z * rhs[2][2] + rhs[3][2];

        return *this;
    }
    // Sobrecarga da operação "vetor *= escalar"
    Vector3 & operator *=(double rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;

        return *this;
    }
    // Sobrecarga da operação "vetor /= escalar"
    Vector3 & operator /=(double rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;

        return *this;
    }
    // Sobrecarga da operação "vetorA == vetorB"
    bool operator ==(const Vector3 & rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    // Sobrecarga da operação "vetorA != vetorB"
    bool operator !=(const Vector3 & rhs) const {
        return !(*this == rhs);
    }
    // Sobrecarga da operação "stream << vetor" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Vector3 & rhs) {
        return lhs << '(' << rhs.x << ' ' << rhs.y << ' ' << rhs.z << ')';
    }

    // Retorna produto escalar
    double dot(const Vector3 & rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    // Retorna produto vetorial
    Vector3 cross(const Vector3 & rhs) const {
        return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }
    // Normaliza vetor (vetor unitário)
    Vector3 & normalize() {
        double l2 = length2();

        if (l2 > 0)
            *this /= std::sqrt(l2);

        return *this;
    }
    // Retorna comprimento do vetor ao quadrado
    double length2() const {
        return dot(*this);
    }
    // Retorna comprimento do vetor
    double length() const {
        return std::sqrt(length2());
    }
};

#endif