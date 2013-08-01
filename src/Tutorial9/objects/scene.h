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

    QOpenGLBuffer         m_vertexPositionBuffer;
    QOpenGLShaderProgram  m_shaderProgram;
    QVector<QVector3D>    m_positionVertices;
    QOpenGLFunctions_3_1* m_funcs;


};

#endif // SCENE_H
