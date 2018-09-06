// File:    Viewport.h
// Author:  Danilo Peixoto
// Date:    06/09/2018

// Evita redefinição de símbolos do arquivo de cabeçalho (caso já tenha sido incluído)
#ifndef CGC_VIEWPORT_H
#define CGC_VIEWPORT_H

#include <Vector.h>
#include <Color.h>

#include <vector>

// Declaração de tipo incompleto no cabeçalho evita dependência cíclica de arquivos
class TriangleMesh;

class GLFWwindow;

// Implementação de "viewport" 3D utilizando OpenGL e GLFW
class Viewport3D {
private:
    size_t width; // Resolução horizontal da janela
    size_t height; // Resolução vertical da janela
    size_t gridSize; // Tamanho da grade principal
    bool grid; // Estado de exibição da grade principal
    bool wireframe; // Estado do modo de exibição de grade de linha
    bool shade; // Estado do modo de exibição sombreado
    double sensitivity; // Sensibilidade dos movimentos de câmera
    double fieldOfView; // Ângulo de visão vertical da câmera em grau
    double nearPlane; // Distância mínima da câmera
    double farPlane; // Ditância máxima da câmera
    double lineWidth; // Espessura das linhas de grade
    Color4 backgroundColor; // Cor do plano de fundo
    Color4 gridColor; // Cor da grade principal
    Color4 wireframeColor; // Cor da grade de linha
    std::vector<const TriangleMesh *> scene; // Lista de ponteiros de geometria

    GLFWwindow * window; // Ponteiro de janela
    size_t index; // Índice inicial das listas de exibição de geometria

    // Informações atuais do mouse
    struct MouseData {
        int button; // Botão pressionado do mouse
        Vector2 position; // Posição do mouse
    } mouseData;

    Vector3 translation; // Vetor de translação da câmera
    Vector3 rotation; // Vetor de ângulos de Euler de rotação da câmera em grau

    // Rotina de renderização da janela
    Viewport3D & render();
    // Rotina de ajuste de tamanho da janela
    Viewport3D & resize(size_t width, size_t height);
    // Rotina de evento do teclado
    Viewport3D & keyboard(size_t key, size_t code, size_t action, size_t modifier);
    // Rotina de evento de botão do mouse
    Viewport3D & mouseButton(size_t button, size_t action, size_t modifier);
    // Rotina de evento de posição do cursor
    Viewport3D & cursor(double x, double y);
    // Rotina de evento de botão deslizante do mouse
    Viewport3D & scroll(double x, double y);

    // Renderiza "viewport" da cena
    Viewport3D & renderSceneViewport();
    // Renderiza "viewport" dos eixos do sistema cartesiano
    Viewport3D & renderAxisViewport();

    // Carrega matriz de transformação de visão padrão
    Viewport3D & loadDefaultView();
    // Carrega cena geométrica
    Viewport3D & loadScene();
    // Desenha eixos do sistema cartesiano
    Viewport3D & drawAxis();
    // Desenha grade principal
    Viewport3D & drawGrid();
    // Desenha cena geométrica
    Viewport3D & drawScene();

public:
    // Construtor padrão
    Viewport3D();
    // Destrutor padrão
    ~Viewport3D();

    // Configura tamanho horizontal da janela
    Viewport3D & setWidth(size_t width);
    // Configura tamanho vertical da janela
    Viewport3D & setHeight(size_t height);
    // Configura tamanho da grade principal
    Viewport3D & setGridSize(size_t gridSize);
    // Configura exibição da grade principal
    Viewport3D & setGrid(bool enable);
    // Configura ativação do modo de exibição de grade de linha
    Viewport3D & setWireframe(bool enable);
    // Configura ativação do modo de exibição sombreado
    Viewport3D & setShade(bool enable);
    // Configura sensibilidade dos movimentos de câmera
    Viewport3D & setSensitivity(double sensitivity);
    // Configura ângulo de visão vertical em grau
    Viewport3D & setFieldOfView(double fieldOfView);
    // Configura distância mínima da câmera
    Viewport3D & setNearPlane(double nearPlane);
    // Configura distância máxima da câmera
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
    // Retorna se grade principal está visível
    bool getGrid() const;
    // Retorna se o modo de exibição de grade de linha está ativo
    bool getWireframe() const;
    // Retorna se o modo de exibição sombreado está ativo
    bool getShade() const;
    // Retorna sensibilidade dos movimentos de câmera
    double getSensitivity() const;
    // Retorna ângulo de visão vertical em grau
    double getFieldOfView() const;
    // Retorna distância mínima da câmera
    double getNearPlane() const;
    // Retorna distância máxima da câmera
    double getFarPlane() const;
    // Retorna espessura das linhas de grade
    double getLineWidth() const;
    // Retorna cor do plano de fundo
    const Color4 & getBackgroundColor() const;
    // Retorna cor da grade principal
    const Color4 & getGridColor() const;
    // Retorna cor da grade de linha
    const Color4 & getWireframeColor() const;
    // Verifica se janela da "viewport" está aberta
    bool isOpen() const;
    // Verifica se existem objetos geométricos na cena
    bool isEmpty() const;

    // Adiciona objeto geométrico na cena
    Viewport3D & add(const TriangleMesh * triangleMesh);
    // Remove todos objetos geométricos da cena
    Viewport3D & clear();
    // Restora posição da câmera
    Viewport3D & resetView();
    // Restora configuração geral
    Viewport3D & reset();
    // Abre janela da "viewport"
    Viewport3D & show();
    // Fecha janela da "viewport"
    Viewport3D & close();
};

#endif