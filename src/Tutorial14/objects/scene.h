#ifndef SCENE_H
#define SCENE_H

#include "abstractscene.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class Camera;
class QOpenGLFunctions_3_1;

class Scene : public AbstractScene
{
public:
    Scene(QObject* parent = 0);

    virtual void initialize();
    virtual void update(float t);
    virtual void render();
    virtual void resize(int width, int height);

    Camera& getCamera() const;

private:
    void prepareShaderProgram();
    void prepareVertexBuffers();
    void prepareIndexBuffer();

    QOpenGLBuffer         m_vertexPositionBuffer;
    QOpenGLBuffer         m_vertexColorBuffer;
    QOpenGLBuffer         m_indexBuffer;
    QOpenGLShaderProgram  m_shaderProgram;
    QVector<QVector3D>    m_positionVertices, m_colorVertices;
    QVector<GLuint>       m_indices;
    QOpenGLFunctions_3_1* m_funcs;

    Camera* m_camera;
};

#endif // SCENE_H
