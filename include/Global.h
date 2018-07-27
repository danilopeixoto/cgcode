// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_GLOBAL_H
#define CGC_GLOBAL_H

#include <ostream>
#include <cmath>
#include <stdexcept>

// Constantes numéricas
#define CGC_E 2.71828182845904523536
#define CGC_PI 3.14159265358979323846
#define CGC_INV_PI 0.31830988618379067154
#define CGC_EPSILON 2.2204460492503131e-016
#define CGC_INFINITY 1.7976931348623158e+308

// Converte ângulo de radiano para grau
double degrees(double radians) {
    return radians * 180.0 * CGC_INV_PI;
}
// Converte ângulo de grau para radiano
double radians(double degrees) {
    return degrees * CGC_PI / 180.0;
}

// Vetor real bidimensional
class Vector2 {
public:
    // Componentes do vetor
    double x, y;

    // Construtor padrão (vetor zero)
    Vector2() : x(0), y(0) {}
    // Construtor de valores iniciais
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
        return Vector2(x + rhs.x, y + rhs.y);
    }
    // Sobrecarga da operação "vetorA - vetorB"
    Vector2 operator -(const Vector2 & rhs) const {
        return Vector2(x - rhs.x, y - rhs.y);
    }
    // Sobrecarga da operação "vetor * escalar"
    Vector2 operator *(double rhs) const {
        return Vector2(x * rhs, y * rhs);
    }
    // Sobrecarga da operação "escalar * vetor"
    friend Vector2 operator *(double lhs, const Vector2 & rhs) {
        return rhs * lhs;
    }
    // Sobrecarga da operação "vetor / escalar"
    Vector2 operator /(double rhs) const {
        return Vector2(x / rhs, y / rhs);
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
    // Sobrecarga da operação "vetorA *= escalar"
    Vector2 & operator *=(double rhs) {
        x *= rhs;
        y *= rhs;

        return *this;
    }
    // Sobrecarga da operação "vetorA /= escalar"
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

        if (l2 < CGC_EPSILON * CGC_EPSILON)
            throw std::logic_error("Divide by zero exception");

        return *this /= std::sqrt(l2);
    }
    // Normaliza vetor evitando divisão por zero (vetor unitário)
    Vector2 & safeNormalize() {
        double l2 = length2();

        if (l2 >= CGC_EPSILON * CGC_EPSILON)
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

// Vetor real tridimensional
class Vector3 {
public:
    // Componentes do vetor
    double x, y, z;

    // Construtor padrão (vetor zero)
    Vector3() : x(0), y(0), z(0) {}
    // Construtor de valores iniciais
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
        return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    // Sobrecarga da operação "vetorA - vetorB"
    Vector3 operator -(const Vector3 & rhs) const {
        return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    // Sobrecarga da operação "vetor * escalar"
    Vector3 operator *(double rhs) const {
        return Vector3(x * rhs, y * rhs, z * rhs);
    }
    // Sobrecarga da operação "escalar * vetor"
    friend Vector3 operator *(double lhs, const Vector3 & rhs) {
        return rhs * lhs;
    }
    // Sobrecarga da operação "vetor / escalar"
    Vector3 operator /(double rhs) const {
        return Vector3(x / rhs, y / rhs, z / rhs);
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
    // Sobrecarga da operação "vetorA *= escalar"
    Vector3 & operator *=(double rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;

        return *this;
    }
    // Sobrecarga da operação "vetorA /= escalar"
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

        if (l2 < CGC_EPSILON * CGC_EPSILON)
            throw std::logic_error("Divide by zero exception");

        return *this /= std::sqrt(l2);
    }
    // Normaliza vetor evitando divisão por zero (vetor unitário)
    Vector3 & safeNormalize() {
        double l2 = length2();

        if (l2 >= CGC_EPSILON * CGC_EPSILON)
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