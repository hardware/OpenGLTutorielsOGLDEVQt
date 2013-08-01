#ifndef SCENE_H
#define SCENE_H

#include "abstractscene.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class QOpenGLFunctions_3_1;

class Scene : public AbstractScene
{
public:
    Scene(QObject* parent = 0);

    virtual void initialize();
    virtual void update(float t);
    virtual void render();
    virtual void resize(int width, int height);

private:
    void prepareShaderProgram();
    void prepareVertexBuffers();

    QOpenGLBuffer        m_vertexPositionBuffer;
    QOpenGLBuffer        m_vertexColorBuffer;
    QOpenGLShaderProgram m_shaderProgram;

    QOpenGLFunctions_3_1* m_funcs;
    QVector<QVector3D>    m_positionVertices, m_colorVertices;

};

#endif // SCENE_H
