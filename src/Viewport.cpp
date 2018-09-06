// File:    Viewport.cpp
// Author:  Danilo Peixoto
// Date:    06/09/2018

#include <Viewport.h>
#include <TriangleMesh.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

Viewport3D & Viewport3D::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderSceneViewport();
    renderAxisViewport();

    glfwSwapBuffers(window);
    glfwPollEvents();

    return *this;
}
Viewport3D & Viewport3D::resize(size_t width, size_t height) {
    this->width = width;
    this->height = height;

    return *this;
}
Viewport3D & Viewport3D::keyboard(size_t key, size_t code,
    size_t action, size_t modifier) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_D:
            resetView();
            break;
        case GLFW_KEY_G:
            grid ^= true;
            break;
        case GLFW_KEY_W:
            wireframe ^= true;
            break;
        case GLFW_KEY_S:
            shade ^= true;
            break;
        case GLFW_KEY_ESCAPE:
            close();
            break;
        default:
            break;
        }
    }

    return *this;
}
Viewport3D & Viewport3D::mouseButton(size_t button, size_t action, size_t modifier) {
    mouseData.button = (action == GLFW_PRESS) ? (button + 1) : 0;
    return *this;
}
Viewport3D & Viewport3D::cursor(double x, double y) {
    double dx = (x - mouseData.position.x) * sensitivity;
    double dy = (y - mouseData.position.y) * sensitivity;

    switch (mouseData.button) {
    case 1:
        rotation.x += dx;
        rotation.y += dy;

        break;
    case 2:
        translation.z += dx;
        translation.z += dy;

        break;
    case 3:
        translation.x += dx * 0.25;
        translation.y -= dy * 0.25;

        break;
    default:
        break;
    }

    mouseData.position = Vector2(x, y);

    return *this;
}
Viewport3D & Viewport3D::scroll(double x, double y) {
    translation.z += y * sensitivity * 5.0;
    return *this;
}

Viewport3D & Viewport3D::renderSceneViewport() {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(fieldOfView, width / (double)height, nearPlane, farPlane);

    glMatrixMode(GL_MODELVIEW);

    Vector3 yAxis(0, 1.0, 0);

    glLoadIdentity();
    glTranslated(translation.x, translation.y, translation.z);
    loadDefaultView();
    glRotated(rotation.x, yAxis.x, yAxis.y, yAxis.z);

    double viewMatrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, viewMatrix);

    Vector3 axis = yAxis.cross(Vector3(viewMatrix[2], viewMatrix[6], viewMatrix[10]));
    glRotated(rotation.y, axis.x, axis.y, axis.z);

    drawGrid();
    drawScene();
}
Viewport3D & Viewport3D::renderAxisViewport() {
    glViewport(0, 0, 80, 80);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -50, 50);

    glMatrixMode(GL_MODELVIEW);

    Vector3 yAxis(0, 1.0, 0);

    glLoadIdentity();
    glTranslated(0, 0, 0);
    loadDefaultView();
    glRotated(rotation.x, yAxis.x, yAxis.y, yAxis.z);

    double viewMatrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, viewMatrix);

    Vector3 axis = yAxis.cross(Vector3(viewMatrix[2], viewMatrix[6], viewMatrix[10]));
    glRotated(rotation.y, axis.x, axis.y, axis.z);

    drawAxis();
}

Viewport3D & Viewport3D::loadDefaultView() {
    gluLookAt(28.0, 21.0, 28.0, 0, 0, 0, 0, 1.0, 0);
    return *this;
}
Viewport3D & Viewport3D::loadScene() {
    size_t size = scene.size();

    index = glGenLists(size);

    for (size_t i = 0; i < size; i++) {
        const TriangleMesh * triangleMesh = scene[i];

        bool hasNormals = triangleMesh->hasNormals();
        bool hasTextureCoordinates = triangleMesh->hasTextureCoordinates();

        glNewList(index + i, GL_COMPILE);
        glBegin(GL_TRIANGLES);

        for (size_t j = 0; j < triangleMesh->getTriangleCount(); j++) {
            size_t indices[3];

            triangleMesh->getVertexIndices(j, indices[0], indices[1], indices[2]);

            const Vector3 & vertex0 = triangleMesh->getVertex(indices[0]);
            const Vector3 & vertex1 = triangleMesh->getVertex(indices[1]);
            const Vector3 & vertex2 = triangleMesh->getVertex(indices[2]);

            const Vector3 * normals[3];
            const Vector2 * textureCoordinates[3];

            if (hasNormals) {
                triangleMesh->getNormalIndices(j, indices[0], indices[1], indices[2]);

                normals[0] = &triangleMesh->getNormal(indices[0]);
                normals[1] = &triangleMesh->getNormal(indices[1]);
                normals[2] = &triangleMesh->getNormal(indices[2]);
            }

            if (hasTextureCoordinates) {
                triangleMesh->getTextureIndices(j, indices[0], indices[1], indices[2]);

                textureCoordinates[0] = &triangleMesh->getTextureCoordinates(indices[0]);
                textureCoordinates[1] = &triangleMesh->getTextureCoordinates(indices[1]);
                textureCoordinates[2] = &triangleMesh->getTextureCoordinates(indices[2]);
            }

            if (hasNormals)
                glNormal3d(normals[0]->x, normals[0]->y, normals[0]->z);

            if (hasTextureCoordinates)
                glTexCoord2d(textureCoordinates[0]->x, textureCoordinates[0]->y);

            glVertex3d(vertex0.x, vertex0.y, vertex0.z);

            if (hasNormals)
                glNormal3d(normals[1]->x, normals[1]->y, normals[1]->z);

            if (hasTextureCoordinates)
                glTexCoord2d(textureCoordinates[1]->x, textureCoordinates[1]->y);

            glVertex3d(vertex1.x, vertex1.y, vertex1.z);

            if (hasNormals)
                glNormal3d(normals[2]->x, normals[2]->y, normals[2]->z);

            if (hasTextureCoordinates)
                glTexCoord2d(textureCoordinates[2]->x, textureCoordinates[2]->y);

            glVertex3d(vertex2.x, vertex2.y, vertex2.z);
        }

        glEnd();
        glEndList();
    }

    return *this;
}
Viewport3D & Viewport3D::drawAxis() {
    glDisable(GL_DEPTH_TEST);
    glLineWidth(2.0);

    glBegin(GL_LINES);

    glColor4d(1.0, 0, 0, 1.0);
    glVertex3d(0, 0, 0);
    glVertex3d(1.0, 0, 0);

    glColor4d(0, 1.0, 0, 1.0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 1.0, 0);

    glColor4d(0, 0, 1.0, 1.0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 1.0);

    glEnd();
    glFlush();

    glEnable(GL_DEPTH_TEST);

    return *this;
}
Viewport3D & Viewport3D::drawGrid() {
    if (grid) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor4d(gridColor.r, gridColor.g, gridColor.b, gridColor.a);

        double size = gridSize;

        for (double i = -size; i <= size; i++) {
            glLineWidth(i != 0 ? lineWidth : 2.0 * lineWidth);

            glBegin(GL_LINES);

            glVertex3d(i, 0, -size);
            glVertex3d(i, 0, size);
            glVertex3d(-size, 0, i);
            glVertex3d(size, 0, i);

            glEnd();
        }

        glFlush();
    }

    return *this;
}
Viewport3D & Viewport3D::drawScene() {
    if (shade) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPolygonOffset(1.0, 1.0);

        for (size_t i = 0; i < scene.size(); i++)
            glCallList(index + i);
    }

    if (wireframe) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_POLYGON_OFFSET_FILL);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(lineWidth);
        glColor4d(wireframeColor.r, wireframeColor.g, wireframeColor.b, wireframeColor.a);

        for (size_t i = 0; i < scene.size(); i++)
            glCallList(index + i);
    }

    glFlush();

    return *this;
}

Viewport3D::Viewport3D() {
    window = nullptr;
    index = 0;

    mouseData.button = 0;

    reset();
}
Viewport3D::~Viewport3D() {}

Viewport3D & Viewport3D::setWidth(size_t width) {
    this->width = width;
    return *this;
}
Viewport3D & Viewport3D::setHeight(size_t height) {
    this->height = height;
    return *this;
}
Viewport3D & Viewport3D::setGridSize(size_t gridSize) {
    this->gridSize = gridSize;
    return *this;
}
Viewport3D & Viewport3D::setGrid(bool enable) {
    grid = enable;
    return *this;
}
Viewport3D & Viewport3D::setWireframe(bool enable) {
    wireframe = enable;
    return *this;
}
Viewport3D & Viewport3D::setShade(bool enable) {
    shade = enable;
    return *this;
}
Viewport3D & Viewport3D::setSensitivity(double sensitivity) {
    this->sensitivity = sensitivity;
    return *this;
}
Viewport3D & Viewport3D::setFieldOfView(double fieldOfView) {
    this->fieldOfView = fieldOfView;
    return *this;
}
Viewport3D & Viewport3D::setNearPlane(double nearPlane) {
    this->nearPlane = nearPlane;
    return *this;
}
Viewport3D & Viewport3D::setFarPlane(double farPlane) {
    this->farPlane = farPlane;
    return *this;
}
Viewport3D & Viewport3D::setLineWidth(double lineWidth) {
    this->lineWidth = lineWidth;
    return *this;
}
Viewport3D & Viewport3D::setBackgroundColor(const Color4 & backgroundColor) {
    this->backgroundColor = backgroundColor;
    return *this;
}
Viewport3D & Viewport3D::setGridColor(const Color4 & gridColor) {
    this->gridColor = gridColor;
    return *this;
}
Viewport3D & Viewport3D::setWireframeColor(const Color4 & wireframeColor) {
    this->wireframeColor = wireframeColor;
    return *this;
}
size_t Viewport3D::getWidth() const {
    return width;
}
size_t Viewport3D::getHeight() const {
    return height;
}
size_t Viewport3D::getGridSize() const {
    return gridSize;
}
bool Viewport3D::getGrid() const {
    return grid;
}
bool Viewport3D::getWireframe() const {
    return wireframe;
}
bool Viewport3D::getShade() const {
    return shade;
}
double Viewport3D::getSensitivity() const {
    return sensitivity;
}
double Viewport3D::getFieldOfView() const {
    return fieldOfView;
}
double Viewport3D::getNearPlane() const {
    return nearPlane;
}
double Viewport3D::getFarPlane() const {
    return farPlane;
}
double Viewport3D::getLineWidth() const {
    return lineWidth;
}
const Color4 & Viewport3D::getBackgroundColor() const {
    return backgroundColor;
}
const Color4 & Viewport3D::getGridColor() const {
    return gridColor;
}
const Color4 & Viewport3D::getWireframeColor() const {
    return wireframeColor;
}
bool Viewport3D::isEmpty() const {
    return scene.empty();
}
bool Viewport3D::isOpen() const {
    return window != nullptr;
}

Viewport3D & Viewport3D::add(const TriangleMesh * triangleMesh) {
    scene.push_back(triangleMesh);
    return *this;
}
Viewport3D & Viewport3D::clear() {
    scene.clear();
    return *this;
}
Viewport3D & Viewport3D::resetView() {
    translation = Vector3();
    rotation = Vector3();

    return *this;
}
Viewport3D & Viewport3D::reset() {
    width = 700;
    height = 500;
    gridSize = 10;
    grid = true;
    wireframe = true;
    shade = true;
    sensitivity = 0.25;
    fieldOfView = 45.0;
    nearPlane = 0.001;
    farPlane = 1000.0;
    lineWidth = 1.0;
    backgroundColor = Color4(0.35, 0.35, 0.35, 1.0);
    gridColor = Color4(0.25, 0.25, 0.25, 1.0);
    wireframeColor = Color4(0, 0, 0.35, 1.0);

    resetView();

    return *this;
}
Viewport3D & Viewport3D::show() {
    if (!glfwInit())
        return *this;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 16);

    window = glfwCreateWindow(width, height, "Viewport 3D", nullptr, nullptr);

    if (window) {
        glfwSetWindowUserPointer(window, this);

        GLFWmonitor * monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode * mode = glfwGetVideoMode(monitor);

        size_t x = (mode->width - width) / 2;
        size_t y = (mode->height - height) / 2;

        glfwSetWindowPos(window, x, y);

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        glfwSetWindowSizeCallback(window,
            [](GLFWwindow * window, int width, int height) {
            Viewport3D * viewport = (Viewport3D *)glfwGetWindowUserPointer(window);
            viewport->resize(width, height);
        });
        glfwSetKeyCallback(window,
            [](GLFWwindow * window, int key, int code, int action, int modifier) {
            Viewport3D * viewport = (Viewport3D *)glfwGetWindowUserPointer(window);
            viewport->keyboard(key, code, action, modifier);
        });
        glfwSetMouseButtonCallback(window,
            [](GLFWwindow * window, int button, int action, int modifier) {
            Viewport3D * viewport = (Viewport3D *)glfwGetWindowUserPointer(window);
            viewport->mouseButton(button, action, modifier);
        });
        glfwSetCursorPosCallback(window,
            [](GLFWwindow * window, double x, double y) {
            Viewport3D * viewport = (Viewport3D *)glfwGetWindowUserPointer(window);
            viewport->cursor(x, y);
        });
        glfwSetScrollCallback(window,
            [](GLFWwindow * window, double x, double y) {
            Viewport3D * viewport = (Viewport3D *)glfwGetWindowUserPointer(window);
            viewport->scroll(x, y);
        });
        glfwSetWindowCloseCallback(window,
            [](GLFWwindow * window) {
            Viewport3D * viewport = (Viewport3D *)glfwGetWindowUserPointer(window);
            viewport->close();
        });

        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);

        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

        resize(width, height);
        glLoadIdentity();
        loadDefaultView();

        loadScene();

        while (!glfwWindowShouldClose(window))
            render();

        glfwDestroyWindow(window);
        window = nullptr;

        glDeleteLists(index, scene.size());
    }

    glfwTerminate();

    return *this;
}
Viewport3D & Viewport3D::close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    return *this;
}