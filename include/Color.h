// File:    Color.h
// Author:  Danilo Peixoto
// Date:    05/08/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_COLOR_H
#define CGC_COLOR_H

#include <ostream>

// Cor RGB linear
class Color3 {
public:
    // Componentes de cor
    double r, g, b;

    // Construtor padrão (cor preta)
    Color3();
    // Construtor cópia
    Color3(const Color3 & color3);
    // Construtor para valores iniciais
    Color3(double r, double g, double b);
    // Destrutor padrão
    ~Color3();

    // Sobrecarga da operação "cor[i]" (retorno mutável)
    double & operator [](size_t i);
    // Sobrecarga da operação "cor[i]" (retorno imutável)
    const double & operator [](size_t i) const;
    // Sobrecarga da operação "+cor"
    Color3 operator +() const;
    // Sobrecarga da operação "-cor"
    Color3 operator -() const;
    // Sobrecarga da operação "corA + corB"
    Color3 operator +(const Color3 & rhs) const;
    // Sobrecarga da operação "corA - corB"
    Color3 operator -(const Color3 & rhs) const;
    // Sobrecarga da operação "cor * escalar"
    Color3 operator *(double rhs) const;
    // Sobrecarga da operação "escalar * cor"
    friend Color3 operator *(double lhs, const Color3 & rhs);
    // Sobrecarga da operação "cor / escalar"
    Color3 operator /(double rhs) const;
    // Sobrecarga da operação "corA += corB"
    Color3 & operator +=(const Color3 & rhs);
    // Sobrecarga da operação "corA -= corB"
    Color3 & operator -=(const Color3 & rhs);
    // Sobrecarga da operação "cor *= escalar"
    Color3 & operator *=(double rhs);
    // Sobrecarga da operação "cor /= escalar"
    Color3 & operator /=(double rhs);
    // Sobrecarga da operação "corA == corB"
    bool operator ==(const Color3 & rhs) const;
    // Sobrecarga da operação "corA != corB"
    bool operator !=(const Color3 & rhs) const;
    // Sobrecarga da operação "saída << cor" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Color3 & rhs);

    // Aplica correção gamma à cor
    Color3 & applyGamma(double gamma);
    // Aplica correção de exposição à cor
    Color3 & applyExposure(double exposure);
    // Satura cor (linear)
    Color3 & saturate();
};

// Cor RGBA linear
class Color4 {
public:
    // Componentes de cor
    double r, g, b, a;

    // Construtor padrão (transparente)
    Color4();
    // Construtor cópia
    Color4(const Color4 & color4);
    // Construtor para valores iniciais
    Color4(double r, double g, double b, double a);
    // Destrutor padrão
    ~Color4();

    // Sobrecarga da operação "cor[i]" (retorno mutável)
    double & operator [](size_t i);
    // Sobrecarga da operação "cor[i]" (retorno imutável)
    const double & operator [](size_t i) const;
    // Sobrecarga da operação "+cor"
    Color4 operator +() const;
    // Sobrecarga da operação "-cor"
    Color4 operator -() const;
    // Sobrecarga da operação "corA + corB"
    Color4 operator +(const Color4 & rhs) const;
    // Sobrecarga da operação "corA - corB"
    Color4 operator -(const Color4 & rhs) const;
    // Sobrecarga da operação "cor * escalar"
    Color4 operator *(double rhs) const;
    // Sobrecarga da operação "escalar * cor"
    friend Color4 operator *(double lhs, const Color4 & rhs);
    // Sobrecarga da operação "cor / escalar"
    Color4 operator /(double rhs) const;
    // Sobrecarga da operação "corA += corB"
    Color4 & operator +=(const Color4 & rhs);
    // Sobrecarga da operação "corA -= corB"
    Color4 & operator -=(const Color4 & rhs);
    // Sobrecarga da operação "cor *= escalar"
    Color4 & operator *=(double rhs);
    // Sobrecarga da operação "cor /= escalar"
    Color4 & operator /=(double rhs);
    // Sobrecarga da operação "corA == corB"
    bool operator ==(const Color4 & rhs) const;
    // Sobrecarga da operação "corA != corB"
    bool operator !=(const Color4 & rhs) const;
    // Sobrecarga da operação "saída << cor" (imprimir saída de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Color4 & rhs);

    // Aplica correção gamma à cor
    Color4 & applyGamma(double gamma);
    // Aplica correção de exposição à cor
    Color4 & applyExposure(double exposure);
    // Satura cor (linear)
    Color4 & saturate();
};

#endif