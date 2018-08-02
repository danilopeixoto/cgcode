// File:	Matrix.h
// Author:	Danilo Peixoto
// Date:	02/08/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_MATRIX_H
#define CGC_MATRIX_H

// Bibliotecas
#include <ostream>
#include <cmath>
#include <Vector.h>

// Matriz real 2x2
class Matrix2 {
private:
    // Elementos da matriz
    double m[2][2];

public:
    // Construtor padrão (matriz zero)
    Matrix2() {
        m[0][0] = 0; m[0][1] = 0;
        m[1][0] = 0; m[1][1] = 0;
    }
    // Construtor cópia
    Matrix2(const Matrix2 & matrix2) {
        m[0][0] = matrix2[0][0]; m[0][1] = matrix2[0][1];
        m[1][0] = matrix2[1][0]; m[1][1] = matrix2[1][1];
    }
    // Construtor para valores iniciais
    Matrix2(
        double m00, double m01,
        double m10, double m11) {
        m[0][0] = m00; m[0][1] = m01;
        m[1][0] = m10; m[1][1] = m11;
    }

    // Sobrecarga da operação "matriz[i]" permite operação "matriz[i][j]" (retorno mutável)
    double * operator [](unsigned int i) {
        return m[i];
    }
    // Sobrecarga da operação "matriz[i]" permite operação "matriz[i][j]" (retorno imutável)
    const double * operator [](unsigned int i) const {
        return m[i];
    }
    // Sobrecarga da operação "+matriz"
    Matrix2 operator +() const {
        return *this;
    }
    // Sobrecarga da operação "-matriz"
    Matrix2 operator -() const {
        return Matrix2(
            -m[0][0], -m[0][1],
            -m[1][0], -m[1][1]);
    }
    // Sobrecarga da operação "matrizA + matrizB"
    Matrix2 operator +(const Matrix2 & rhs) const {
        return Matrix2(*this) += rhs;
    }
    // Sobrecarga da operação "matrizA - matrizB"
    Matrix2 operator -(const Matrix2 & rhs) const {
        return Matrix2(*this) -= rhs;
    }
    // Sobrecarga da operação "matrizA * matrizB"
    Matrix2 operator *(const Matrix2 & rhs) const {
        return Matrix2(*this) *= rhs;
    }
    // Sobrecarga da operação "matriz * escalar"
    Matrix2 operator *(double rhs) const {
        return Matrix2(*this) *= rhs;
    }
    // Sobrecarga da operação "escalar * matriz"
    friend Matrix2 operator *(double lhs, const Matrix2 & rhs) {
        return rhs * lhs;
    }
    // Sobrecarga da operação "matrizA / matrizB" realiza operação "matrizA.inverse(matrizB)"
    Matrix2 operator /(const Matrix2 & rhs) const {
        return Matrix2(*this) /= rhs;
    }
    // Sobrecarga da operação "matriz / escalar"
    Matrix2 operator /(double rhs) const {
        return Matrix2(*this) /= rhs;
    }
    // Sobrecarga da operação "matrizA += matrizB"
    Matrix2 & operator +=(const Matrix2 & rhs) {
        m[0][0] += rhs[0][0]; m[0][1] += rhs[0][1];
        m[1][0] += rhs[1][0]; m[1][1] += rhs[1][1];

        return *this;
    }
    // Sobrecarga da operação "matrizA -= matrizB"
    Matrix2 & operator -=(const Matrix2 & rhs) {
        m[0][0] -= rhs[0][0]; m[0][1] -= rhs[0][1];
        m[1][0] -= rhs[1][0]; m[1][1] -= rhs[1][1];

        return *this;
    }
    // Sobrecarga da operação "matrizA *= matrizB"
    Matrix2 & operator *=(const Matrix2 & rhs) {
        double t0 = m[0][0], t1 = m[0][1];

        m[0][0] = t0 * rhs[0][0] + t1 * rhs[1][0];
        m[0][1] = t0 * rhs[0][1] + t1 * rhs[1][1];

        t0 = m[1][0]; t1 = m[1][1];

        m[1][0] = t0 * rhs[0][0] + t1 * rhs[1][0];
        m[1][1] = t0 * rhs[0][1] + t1 * rhs[1][1];

        return *this;
    }
    // Sobrecarga da operação "matriz *= escalar"
    Matrix2 & operator *=(double rhs) {
        m[0][0] *= rhs; m[0][1] *= rhs;
        m[1][0] *= rhs; m[1][1] *= rhs;

        return *this;
    }
    // Sobrecarga da operação "matrizA /= matrizB" realiza operação "matrizA = matrizA.inverse(matrizB)"
    Matrix2 & operator /=(const Matrix2 & rhs) {
        return *this *= rhs.inverse();
    }
    // Sobrecarga da operação "matriz /= escalar"
    Matrix2 & operator /=(double rhs) {
        m[0][0] /= rhs; m[0][1] /= rhs;
        m[1][0] /= rhs; m[1][1] /= rhs;

        return *this;
    }
    // Sobrecarga da operação "matrizA == matrizB"
    bool operator ==(const Matrix2 & rhs) const {
        return m[0][0] == rhs[0][0] && m[0][1] == rhs[0][1]
            && m[1][0] == rhs[1][0] && m[1][1] == rhs[1][1];
    }
    // Sobrecarga da operação "matrizA != matrizB"
    bool operator !=(const Matrix2 & rhs) const {
        return !(*this == rhs);
    }
    // Sobrecarga da operação "stream << matriz" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Matrix2 & rhs) {
        return lhs << '('
            << rhs[0][0] << ' ' << rhs[0][1] << ' ' << std::endl
            << rhs[1][0] << ' ' << rhs[1][1] << ')';
    }

    // Retorna determinante
    double determinant() const {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
    // Retorna traço
    double trace() const {
        return m[0][0] + m[1][1];
    }
    // Retorna menor da submatriz sem a linha "i" e coluna "j"
    double minor(unsigned int i, unsigned int j) const {
        unsigned int i0 = i < 1 ? 1 : 0;
        unsigned int j0 = j < 1 ? 1 : 0;

        return m[i0][j0];
    }
    // Transpõe matriz (matriz transposta)
    Matrix2 & transpose() {
        double t01 = m[0][1];

        m[0][1] = m[1][0];
        m[1][0] = t01;

        return *this;
    }
    // Retorna inversa
    Matrix2 inverse() const {
        return adjugate() / determinant();
    }
    // Retorna adjunta
    Matrix2 adjugate() const {
        return Matrix2(
            minor(0, 0), -minor(1, 0),
            -minor(0, 1), minor(1, 1));
    }
};

// Matriz real 3x3
class Matrix3 {
private:
    // Elementos da matriz
    double m[3][3];

public:
    // Construtor padrão (matriz zero)
    Matrix3() {
        m[0][0] = 0; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = 0; m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 0;
    }
    // Construtor cópia
    Matrix3(const Matrix3 & matrix3) {
        m[0][0] = matrix3[0][0]; m[0][1] = matrix3[0][1]; m[0][2] = matrix3[0][2];
        m[1][0] = matrix3[1][0]; m[1][1] = matrix3[1][1]; m[1][2] = matrix3[1][2];
        m[2][0] = matrix3[2][0]; m[2][1] = matrix3[2][1]; m[2][2] = matrix3[2][2];
    }
    // Construtor para valores iniciais
    Matrix3(
        double m00, double m01, double m02,
        double m10, double m11, double m12,
        double m20, double m21, double m22) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
    }

    // Sobrecarga da operação "matriz[i]" permite operação "matriz[i][j]" (retorno mutável)
    double * operator [](unsigned int i) {
        return m[i];
    }
    // Sobrecarga da operação "matriz[i]" permite operação "matriz[i][j]" (retorno imutável)
    const double * operator [](unsigned int i) const {
        return m[i];
    }
    // Sobrecarga da operação "+matriz"
    Matrix3 operator +() const {
        return *this;
    }
    // Sobrecarga da operação "-matriz"
    Matrix3 operator -() const {
        return Matrix3(
            -m[0][0], -m[0][1], -m[0][2],
            -m[1][0], -m[1][1], -m[1][2],
            -m[2][0], -m[2][1], -m[2][2]);
    }
    // Sobrecarga da operação "matrizA + matrizB"
    Matrix3 operator +(const Matrix3 & rhs) const {
        return Matrix3(*this) += rhs;
    }
    // Sobrecarga da operação "matrizA - matrizB"
    Matrix3 operator -(const Matrix3 & rhs) const {
        return Matrix3(*this) -= rhs;
    }
    // Sobrecarga da operação "matrizA * matrizB"
    Matrix3 operator *(const Matrix3 & rhs) const {
        return Matrix3(*this) *= rhs;
    }
    // Sobrecarga da operação "matriz * escalar"
    Matrix3 operator *(double rhs) const {
        return Matrix3(*this) *= rhs;
    }
    // Sobrecarga da operação "escalar * matriz"
    friend Matrix3 operator *(double lhs, const Matrix3 & rhs) {
        return rhs * lhs;
    }
    // Sobrecarga da operação "matrizA / matrizB" realiza operação "matrizA.inverse(matrizB)"
    Matrix3 operator /(const Matrix3 & rhs) const {
        return Matrix3(*this) /= rhs;
    }
    // Sobrecarga da operação "matriz / escalar"
    Matrix3 operator /(double rhs) const {
        return Matrix3(*this) /= rhs;
    }
    // Sobrecarga da operação "matrizA += matrizB"
    Matrix3 & operator +=(const Matrix3 & rhs) {
        m[0][0] += rhs[0][0]; m[0][1] += rhs[0][1]; m[0][2] += rhs[0][2];
        m[1][0] += rhs[1][0]; m[1][1] += rhs[1][1]; m[1][2] += rhs[1][2];
        m[2][0] += rhs[2][0]; m[2][1] += rhs[2][1]; m[2][2] += rhs[2][2];

        return *this;
    }
    // Sobrecarga da operação "matrizA -= matrizB"
    Matrix3 & operator -=(const Matrix3 & rhs) {
        m[0][0] -= rhs[0][0]; m[0][1] -= rhs[0][1]; m[0][2] -= rhs[0][2];
        m[1][0] -= rhs[1][0]; m[1][1] -= rhs[1][1]; m[1][2] -= rhs[1][2];
        m[2][0] -= rhs[2][0]; m[2][1] -= rhs[2][1]; m[2][2] -= rhs[2][2];

        return *this;
    }
    // Sobrecarga da operação "matrizA *= matrizB"
    Matrix3 & operator *=(const Matrix3 & rhs) {
        double t0 = m[0][0], t1 = m[0][1], t2 = m[0][2];

        m[0][0] = t0 * rhs[0][0] + t1 * rhs[1][0] + t2 * rhs[2][0];
        m[0][1] = t0 * rhs[0][1] + t1 * rhs[1][1] + t2 * rhs[2][1];
        m[0][2] = t0 * rhs[0][2] + t1 * rhs[1][2] + t2 * rhs[2][2];

        t0 = m[1][0]; t1 = m[1][1]; t2 = m[1][2];

        m[1][0] = t0 * rhs[0][0] + t1 * rhs[1][0] + t2 * rhs[2][0];
        m[1][1] = t0 * rhs[0][1] + t1 * rhs[1][1] + t2 * rhs[2][1];
        m[1][2] = t0 * rhs[0][2] + t1 * rhs[1][2] + t2 * rhs[2][2];

        t0 = m[2][0]; t1 = m[2][1]; t2 = m[2][2];

        m[2][0] = t0 * rhs[0][0] + t1 * rhs[1][0] + t2 * rhs[2][0];
        m[2][1] = t0 * rhs[0][1] + t1 * rhs[1][1] + t2 * rhs[2][1];
        m[2][2] = t0 * rhs[0][2] + t1 * rhs[1][2] + t2 * rhs[2][2];

        return *this;
    }
    // Sobrecarga da operação "matriz *= escalar"
    Matrix3 & operator *=(double rhs) {
        m[0][0] *= rhs; m[0][1] *= rhs; m[0][2] *= rhs;
        m[1][0] *= rhs; m[1][1] *= rhs; m[1][2] *= rhs;
        m[2][0] *= rhs; m[2][1] *= rhs; m[2][2] *= rhs;

        return *this;
    }
    // Sobrecarga da operação "matrizA /= matrizB" realiza operação "matrizA = matrizA.inverse(matrizB)"
    Matrix3 & operator /=(const Matrix3 & rhs) {
        return *this *= rhs.inverse();
    }
    // Sobrecarga da operação "matriz /= escalar"
    Matrix3 & operator /=(double rhs) {
        m[0][0] /= rhs; m[0][1] /= rhs; m[0][2] /= rhs;
        m[1][0] /= rhs; m[1][1] /= rhs; m[1][2] /= rhs;
        m[2][0] /= rhs; m[2][1] /= rhs; m[2][2] /= rhs;

        return *this;
    }
    // Sobrecarga da operação "matrizA == matrizB"
    bool operator ==(const Matrix3 & rhs) const {
        return m[0][0] == rhs[0][0] && m[0][1] == rhs[0][1] && m[0][2] == rhs[0][2]
            && m[1][0] == rhs[1][0] && m[1][1] == rhs[1][1] && m[1][2] == rhs[1][2]
            && m[2][0] == rhs[2][0] && m[2][1] == rhs[2][1] && m[2][2] == rhs[2][2];
    }
    // Sobrecarga da operação "matrizA != matrizB"
    bool operator !=(const Matrix3 & rhs) const {
        return !(*this == rhs);
    }
    // Sobrecarga da operação "stream << matriz" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Matrix3 & rhs) {
        return lhs << '('
            << rhs[0][0] << ' ' << rhs[0][1] << ' ' << rhs[0][2] << ' ' << std::endl
            << rhs[1][0] << ' ' << rhs[1][1] << ' ' << rhs[1][2] << ' ' << std::endl
            << rhs[2][0] << ' ' << rhs[2][1] << ' ' << rhs[2][2] << ')';
    }

    // Retorna determinante
    double determinant() const {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
            + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2])
            + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }
    // Retorna traço
    double trace() const {
        return m[0][0] + m[1][1] + m[2][2];
    }
    // Retorna menor da submatriz sem a linha "i" e coluna "j"
    double minor(unsigned int i, unsigned int j) const {
        unsigned int i0 = i < 1 ? 1 : 0;
        unsigned int i1 = i < 2 ? 2 : 1;

        unsigned int j0 = j < 1 ? 1 : 0;
        unsigned int j1 = j < 2 ? 2 : 1;

        return m[i0][j0] * m[i1][j1] - m[i0][j1] * m[i1][j0];
    }
    // Transpõe matriz (matriz transposta)
    Matrix3 & transpose() {
        Matrix3 t(*this);

        m[0][1] = t[1][0]; m[0][2] = t[2][0];
        m[1][0] = t[0][1]; m[1][2] = t[2][1];
        m[2][0] = t[0][2]; m[2][1] = t[1][2];

        return *this;
    }
    // Retorna inversa
    Matrix3 inverse() const {
        return adjugate() / determinant();
    }
    // Retorna adjunta
    Matrix3 adjugate() const {
        return Matrix3(
            minor(0, 0), -minor(1, 0), minor(2, 0),
            -minor(0, 1), minor(1, 1), -minor(2, 1),
            minor(0, 2), -minor(1, 2), minor(2, 2));
    }
};

// Matriz real 4x4
class Matrix4 {
private:
    // Elementos da matriz
    double m[4][4];

public:
    // Construtor padrão (matriz zero)
    Matrix4() {
        m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
    }
    // Construtor cópia
    Matrix4(const Matrix4 & matrix4) {
        m[0][0] = matrix4[0][0]; m[0][1] = matrix4[0][1]; m[0][2] = matrix4[0][2]; m[0][3] = matrix4[0][3];
        m[1][0] = matrix4[1][0]; m[1][1] = matrix4[1][1]; m[1][2] = matrix4[1][2]; m[1][3] = matrix4[1][3];
        m[2][0] = matrix4[2][0]; m[2][1] = matrix4[2][1]; m[2][2] = matrix4[2][2]; m[2][3] = matrix4[2][3];
        m[3][0] = matrix4[3][0]; m[3][1] = matrix4[3][1]; m[3][2] = matrix4[3][2]; m[3][3] = matrix4[3][3];
    }
    // Construtor para valores iniciais
    Matrix4(
        double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    // Sobrecarga da operação "matriz[i]" permite operação "matriz[i][j]" (retorno mutável)
    double * operator [](unsigned int i) {
        return m[i];
    }
    // Sobrecarga da operação "matriz[i]" permite operação "matriz[i][j]" (retorno imutável)
    const double * operator [](unsigned int i) const {
        return m[i];
    }
    // Sobrecarga da operação "+matriz"
    Matrix4 operator +() const {
        return *this;
    }
    // Sobrecarga da operação "-matriz"
    Matrix4 operator -() const {
        return Matrix4(
            -m[0][0], -m[0][1], -m[0][2], -m[0][3],
            -m[1][0], -m[1][1], -m[1][2], -m[1][3],
            -m[2][0], -m[2][1], -m[2][2], -m[2][3],
            -m[3][0], -m[3][1], -m[3][2], -m[3][3]);
    }
    // Sobrecarga da operação "matrizA + matrizB"
    Matrix4 operator +(const Matrix4 & rhs) const {
        return Matrix4(*this) += rhs;
    }
    // Sobrecarga da operação "matrizA - matrizB"
    Matrix4 operator -(const Matrix4 & rhs) const {
        return Matrix4(*this) -= rhs;
    }
    // Sobrecarga da operação "matrizA * matrizB"
    Matrix4 operator *(const Matrix4 & rhs) const {
        return Matrix4(*this) *= rhs;
    }
    // Sobrecarga da operação "matriz * escalar"
    Matrix4 operator *(double rhs) const {
        return Matrix4(*this) *= rhs;
    }
    // Sobrecarga da operação "escalar * matriz"
    friend Matrix4 operator *(double lhs, const Matrix4 & rhs) {
        return rhs * lhs;
    }
    // Sobrecarga da operação "matrizA / matrizB" realiza operação "matrizA.inverse(matrizB)"
    Matrix4 operator /(const Matrix4 & rhs) const {
        return Matrix4(*this) /= rhs;
    }
    // Sobrecarga da operação "matriz / escalar"
    Matrix4 operator /(double rhs) const {
        return Matrix4(*this) /= rhs;
    }
    // Sobrecarga da operação "matrizA += matrizB"
    Matrix4 & operator +=(const Matrix4 & rhs) {
        m[0][0] += rhs[0][0]; m[0][1] += rhs[0][1]; m[0][2] += rhs[0][2]; m[0][3] += rhs[0][3];
        m[1][0] += rhs[1][0]; m[1][1] += rhs[1][1]; m[1][2] += rhs[1][2]; m[1][3] += rhs[1][3];
        m[2][0] += rhs[2][0]; m[2][1] += rhs[2][1]; m[2][2] += rhs[2][2]; m[2][3] += rhs[2][3];
        m[3][0] += rhs[3][0]; m[3][1] += rhs[3][1]; m[3][2] += rhs[3][2]; m[3][3] += rhs[3][3];

        return *this;
    }
    // Sobrecarga da operação "matrizA -= matrizB"
    Matrix4 & operator -=(const Matrix4 & rhs) {
        m[0][0] -= rhs[0][0]; m[0][1] -= rhs[0][1]; m[0][2] -= rhs[0][2]; m[0][3] -= rhs[0][3];
        m[1][0] -= rhs[1][0]; m[1][1] -= rhs[1][1]; m[1][2] -= rhs[1][2]; m[1][3] -= rhs[1][3];
        m[2][0] -= rhs[2][0]; m[2][1] -= rhs[2][1]; m[2][2] -= rhs[2][2]; m[2][3] -= rhs[2][3];
        m[3][0] -= rhs[3][0]; m[3][1] -= rhs[3][1]; m[3][2] -= rhs[3][2]; m[3][3] -= rhs[3][3];

        return *this;
    }
    // Sobrecarga da operação "matrizA *= matrizB"
    Matrix4 & operator *=(const Matrix4 & rhs) {
        double t0 = m[0][0], t1 = m[0][1], t2 = m[0][2], t3 = m[0][3];

        m[0][0] = t0 * rhs[0][0] + t1 * rhs[1][0] + t2 * rhs[2][0] + t3 * rhs[3][0];
        m[0][1] = t0 * rhs[0][1] + t1 * rhs[1][1] + t2 * rhs[2][1] + t3 * rhs[3][1];
        m[0][2] = t0 * rhs[0][2] + t1 * rhs[1][2] + t2 * rhs[2][2] + t3 * rhs[3][2];
        m[0][3] = t0 * rhs[0][3] + t1 * rhs[1][3] + t2 * rhs[2][3] + t3 * rhs[3][3];

        t0 = m[1][0]; t1 = m[1][1]; t2 = m[1][2]; t3 = m[1][3];

        m[1][0] = t0 * rhs[0][0] + t1 * rhs[1][0] + t2 * rhs[2][0] + t3 * rhs[3][0];
        m[1][1] = t0 * rhs[0][1] + t1 * rhs[1][1] + t2 * rhs[2][1] + t3 * rhs[3][1];
        m[1][2] = t0 * rhs[0][2] + t1 * rhs[1][2] + t2 * rhs[2][2] + t3 * rhs[3][2];
        m[1][3] = t0 * rhs[0][3] + t1 * rhs[1][3] + t2 * rhs[2][3] + t3 * rhs[3][3];

        t0 = m[2][0]; t1 = m[2][1]; t2 = m[2][2]; t3 = m[2][3];

        m[2][0] = t0 * rhs[0][0] + t1 * rhs[1][0] + t2 * rhs[2][0] + t3 * rhs[3][0];
        m[2][1] = t0 * rhs[0][1] + t1 * rhs[1][1] + t2 * rhs[2][1] + t3 * rhs[3][1];
        m[2][2] = t0 * rhs[0][2] + t1 * rhs[1][2] + t2 * rhs[2][2] + t3 * rhs[3][2];
        m[2][3] = t0 * rhs[0][3] + t1 * rhs[1][3] + t2 * rhs[2][3] + t3 * rhs[3][3];

        t0 = m[3][0]; t1 = m[3][1]; t2 = m[3][2]; t3 = m[3][3];

        m[3][0] = t0 * rhs[0][0] + t1 * rhs[1][0] + t2 * rhs[2][0] + t3 * rhs[3][0];
        m[3][1] = t0 * rhs[0][1] + t1 * rhs[1][1] + t2 * rhs[2][1] + t3 * rhs[3][1];
        m[3][2] = t0 * rhs[0][2] + t1 * rhs[1][2] + t2 * rhs[2][2] + t3 * rhs[3][2];
        m[3][3] = t0 * rhs[0][3] + t1 * rhs[1][3] + t2 * rhs[2][3] + t3 * rhs[3][3];

        return *this;
    }
    // Sobrecarga da operação "matriz *= escalar"
    Matrix4 & operator *=(double rhs) {
        m[0][0] *= rhs; m[0][1] *= rhs; m[0][2] *= rhs; m[0][3] *= rhs;
        m[1][0] *= rhs; m[1][1] *= rhs; m[1][2] *= rhs; m[1][3] *= rhs;
        m[2][0] *= rhs; m[2][1] *= rhs; m[2][2] *= rhs; m[2][3] *= rhs;
        m[3][0] *= rhs; m[3][1] *= rhs; m[3][2] *= rhs; m[3][3] *= rhs;

        return *this;
    }
    // Sobrecarga da operação "matrizA /= matrizB" realiza operação "matrizA = matrizA.inverse(matrizB)"
    Matrix4 & operator /=(const Matrix4 & rhs) {
        return *this *= rhs.inverse();
    }
    // Sobrecarga da operação "matriz /= escalar"
    Matrix4 & operator /=(double rhs) {
        m[0][0] /= rhs; m[0][1] /= rhs; m[0][2] /= rhs; m[0][3] /= rhs;
        m[1][0] /= rhs; m[1][1] /= rhs; m[1][2] /= rhs; m[1][3] /= rhs;
        m[2][0] /= rhs; m[2][1] /= rhs; m[2][2] /= rhs; m[2][3] /= rhs;
        m[3][0] /= rhs; m[3][1] /= rhs; m[3][2] /= rhs; m[3][3] /= rhs;

        return *this;
    }
    // Sobrecarga da operação "matrizA == matrizB"
    bool operator ==(const Matrix4 & rhs) const {
        return m[0][0] == rhs[0][0] && m[0][1] == rhs[0][1] && m[0][2] == rhs[0][2] && m[0][3] == rhs[0][3]
            && m[1][0] == rhs[1][0] && m[1][1] == rhs[1][1] && m[1][2] == rhs[1][2] && m[1][3] == rhs[1][3]
            && m[2][0] == rhs[2][0] && m[2][1] == rhs[2][1] && m[2][2] == rhs[2][2] && m[2][3] == rhs[2][3]
            && m[3][0] == rhs[3][0] && m[3][1] == rhs[3][1] && m[3][2] == rhs[3][2] && m[3][3] == rhs[3][3];
    }
    // Sobrecarga da operação "matrizA != matrizB"
    bool operator !=(const Matrix4 & rhs) const {
        return !(*this == rhs);
    }
    // Sobrecarga da operação "stream << matriz" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Matrix4 & rhs) {
        return lhs << '('
            << rhs[0][0] << ' ' << rhs[0][1] << ' ' << rhs[0][2] << ' ' << rhs[0][3] << ' ' << std::endl
            << rhs[1][0] << ' ' << rhs[1][1] << ' ' << rhs[1][2] << ' ' << rhs[1][3] << ' ' << std::endl
            << rhs[2][0] << ' ' << rhs[2][1] << ' ' << rhs[2][2] << ' ' << rhs[2][3] << ' ' << std::endl
            << rhs[3][0] << ' ' << rhs[3][1] << ' ' << rhs[3][2] << ' ' << rhs[3][3] << ')';
    }

    // Retorna determinante
    double determinant() const {
        double d = 0;

        if (m[0][0] != 0) d += m[0][0] * minor(0, 0);
        if (m[0][1] != 0) d -= m[0][1] * minor(0, 1);
        if (m[0][2] != 0) d += m[0][2] * minor(0, 2);
        if (m[0][3] != 0) d -= m[0][3] * minor(0, 3);

        return d;
    }
    // Retorna traço
    double trace() const {
        return m[0][0] + m[1][1] + m[2][2] + m[3][3];
    }
    // Retorna menor da submatriz sem a linha "i" e coluna "j"
    double minor(unsigned int i, unsigned int j) const {
        unsigned int i0 = i < 1 ? 1 : 0;
        unsigned int i1 = i < 2 ? 2 : 1;
        unsigned int i2 = i < 3 ? 3 : 2;

        unsigned int j0 = j < 1 ? 1 : 0;
        unsigned int j1 = j < 2 ? 2 : 1;
        unsigned int j2 = j < 3 ? 3 : 2;

        return m[i0][j0] * (m[i1][j1] * m[i2][j2] - m[i1][j2] * m[i2][j1])
            + m[i0][j1] * (m[i1][j2] * m[i2][j0] - m[i1][j0] * m[i2][j2])
            + m[i0][j2] * (m[i1][j0] * m[i2][j1] - m[i1][j1] * m[i2][j0]);
    }
    // Transpõe matriz (matriz transposta)
    Matrix4 & transpose() {
        Matrix4 t(*this);

        m[0][1] = t[1][0]; m[0][2] = t[2][0]; m[0][3] = t[3][0];
        m[1][0] = t[0][1]; m[1][2] = t[2][1]; m[1][3] = t[3][1];
        m[2][0] = t[0][2]; m[2][1] = t[1][2]; m[2][3] = t[3][2];
        m[3][0] = t[0][3]; m[3][1] = t[1][3]; m[3][2] = t[2][3];

        return *this;
    }
    // Retorna inversa
    Matrix4 inverse() const {
        return adjugate() / determinant();
    }
    // Retorna adjunta
    Matrix4 adjugate() const {
        return Matrix4(
            minor(0, 0), -minor(1, 0), minor(2, 0), -minor(3, 0),
            -minor(0, 1), minor(1, 1), -minor(2, 1), minor(3, 1),
            minor(0, 2), -minor(1, 2), minor(2, 2), -minor(3, 2),
            -minor(0, 3), minor(1, 3), -minor(2, 3), minor(3, 3));
    }
};

#endif