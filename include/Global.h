// File:    Global.h
// Author:  Danilo Peixoto
// Date:    02/08/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_GLOBAL_H
#define CGC_GLOBAL_H

// Constantes numéricas
#define CGC_E 2.71828182845904523536
#define CGC_PI 3.14159265358979323846
#define CGC_INV_PI 0.31830988618379067154
#define CGC_EPSILON 2.2204460492503131e-016
#define CGC_INFINITY 1.7976931348623158e+308

// Converte ângulo de radiano para grau
double degrees(double radians);
// Converte ângulo de grau para radiano
double radians(double degrees);
// Retorna valor delimitado por mínimo e máximo
double clamp(double value, double minimum, double maximum);

#endif