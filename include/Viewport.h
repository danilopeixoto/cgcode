// File:    Viewport.h
// Author:  Danilo Peixoto
// Date:    06/09/2018

// Evita redefini��o de s�mbolos do arquivo de cabe�alho (caso j� tenha sido inclu�do)
#ifndef CGC_VIEWPORT_H
#define CGC_VIEWPORT_H

#include <Vector.h>
#include <Color.h>

#include <vector>

// Declara��o de tipo incompleto no cabe�alho evita depend�ncia c�clica de arquivos
class TriangleMesh;

class GLFWwindow;

// Implementa��o de "viewport" 3D utilizando OpenGL e GLFW
class Viewport3D {
private:
    size_t width; // Resolu��o horizontal da janela
    size_t height; // Resolu��o vertical da janela
    size_t gridSize; // Tamanho da grade principal
    bool grid; // Estado de exibi��o da grade principal
    bool wireframe; // Estado do modo de exibi��o de grade de linha
    bool shade; // Estado do modo de exibi��o sombreado
    double sensitivity; // Sensibilidade dos movimentos de c�mera
    double fieldOfView; // �ngulo de vis�o vertical da c�mera em grau
    double nearPlane; // Dist�ncia m�nima da c�mera
    double farPlane; // Dit�ncia m�xima da c�mera
    double lineWidth; // Espessura das linhas de grade
    Color4 backgroundColor; // Cor do plano de fundo
    Color4 gridColor; // Cor da grade principal
    Color4 wireframeColor; // Cor da grade de linha
    std::vector<const TriangleMesh *> scene; // Lista de ponteiros de geometria

    GLFWwindow * window; // Ponteiro de janela
    size_t index; // �ndice inicial das listas de exibi��o de geometria

    // Informa��es atuais do mouse
    struct MouseData {
        int button; // Bot�o pressionado do mouse
        Vector2 position; // Posi��o do mouse
    } mouseData;

    Vector3 translation; // Vetor de transla��o da c�mera
    Vector3 rotation; // Vetor de �ngulos de Euler de rota��o da c�mera em grau

    // Rotina de renderiza��o da janela
    Viewport3D & render();
    // Rotina de ajuste de tamanho da janela
    Viewport3D & resize(size_t width, size_t height);
    // Rotina de evento do teclado
    Viewport3D & keyboard(size_t key, size_t code, size_t action, size_t modifier);
    // Rotina de evento de bot�o do mouse
    Viewport3D & mouseButton(size_t button, size_t action, size_t modifier);
    // Rotina de evento de posi��o do cursor
    Viewport3D & cursor(double x, double y);
    // Rotina de evento de bot�o deslizante do mouse
    Viewport3D & scroll(double x, double y);

    // Renderiza "viewport" da cena
    Viewport3D & renderSceneViewport();
    // Renderiza "viewport" dos eixos do sistema cartesiano
    Viewport3D & renderAxisViewport();

    // Carrega matriz de transforma��o de vis�o padr�o
    Viewport3D & loadDefaultView();
    // Carrega cena geom�trica
    Viewport3D & loadScene();
    // Desenha eixos do sistema cartesiano
    Viewport3D & drawAxis();
    // Desenha grade principal
    Viewport3D & drawGrid();
    // Desenha cena geom�trica
    Viewport3D & drawScene();

public:
    // Construtor padr�o
    Viewport3D();
    // Destrutor padr�o
    ~Viewport3D();

    // Configura tamanho horizontal da janela
    Viewport3D & setWidth(size_t width);
    // Configura tamanho vertical da janela
    Viewport3D & setHeight(size_t height);
    // Configura tamanho da grade principal
    Viewport3D & setGridSize(size_t gridSize);
    // Configura exibi��o da grade principal
    Viewport3D & setGrid(bool enable);
    // Configura ativa��o do modo de exibi��o de grade de linha
    Viewport3D & setWireframe(bool enable);
    // Configura ativa��o do modo de exibi��o sombreado
    Viewport3D & setShade(bool enable);
    // Configura sensibilidade dos movimentos de c�mera
    Viewport3D & setSensitivity(double sensitivity);
    // Configura �ngulo de vis�o vertical em grau
    Viewport3D & setFieldOfView(double fieldOfView);
    // Configura dist�ncia m�nima da c�mera
    Viewport3D & setNearPlane(double nearPlane);
    // Configura dist�ncia m�xima da c�mera
    Viewport3D & setFarPlane(double farPlane);
    // Configura espessura das linhas de grade
    Viewport3D & setLineWidth(double lineWidth);
    // Configura cor do plano de fundo
    Viewport3D & setBackgroundColor(const Color4 & backgroundColor);
    // Configura cor da grade principal
    Viewport3D & setGridColor(const Color4 & gridColor);
    // Configura cor da grade de linha
    Viewport3D & setWireframeColor(const Color4 & wireframeColor);
    // Retorna tamanho horizontal da janela
    size_t getWidth() const;
    // Retorna tamanho vertical da janela
    size_t getHeight() const;
    // Retorna tamanho da grade principal
    size_t getGridSize() const;
    // Retorna se grade principal est� vis�vel
    bool getGrid() const;
    // Retorna se o modo de exibi��o de grade de linha est� ativo
    bool getWireframe() const;
    // Retorna se o modo de exibi��o sombreado est� ativo
    bool getShade() const;
    // Retorna sensibilidade dos movimentos de c�mera
    double getSensitivity() const;
    // Retorna �ngulo de vis�o vertical em grau
    double getFieldOfView() const;
    // Retorna dist�ncia m�nima da c�mera
    double getNearPlane() const;
    // Retorna dist�ncia m�xima da c�mera
    double getFarPlane() const;
    // Retorna espessura das linhas de grade
    double getLineWidth() const;
    // Retorna cor do plano de fundo
    const Color4 & getBackgroundColor() const;
    // Retorna cor da grade principal
    const Color4 & getGridColor() const;
    // Retorna cor da grade de linha
    const Color4 & getWireframeColor() const;
    // Verifica se janela da "viewport" est� aberta
    bool isOpen() const;
    // Verifica se existem objetos geom�tricos na cena
    bool isEmpty() const;

    // Adiciona objeto geom�trico na cena
    Viewport3D & add(const TriangleMesh * triangleMesh);
    // Remove todos objetos geom�tricos da cena
    Viewport3D & clear();
    // Restora posi��o da c�mera
    Viewport3D & resetView();
    // Restora configura��o geral
    Viewport3D & reset();
    // Abre janela da "viewport"
    Viewport3D & show();
    // Fecha janela da "viewport"
    Viewport3D & close();
};

#endif