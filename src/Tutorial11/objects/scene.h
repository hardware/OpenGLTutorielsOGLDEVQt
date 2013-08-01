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
    void prepareIndexBuffer();

    QOpenGLBuffer         m_vertexPositionBuffer;
    QOpenGLBuffer         m_vertexColorBuffer;
    QOpenGLBuffer         m_indexBuffer;
    QOpenGLShaderProgram  m_shaderProgram;
    QVector<QVector3D>    m_positionVertices, m_colorVertices;
    QVector<GLuint>       m_indices;
    QOpenGLFunctions_3_1* m_funcs;

};

#endif // SCENE_H
