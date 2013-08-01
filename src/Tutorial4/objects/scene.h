#ifndef SCENE_H
#define SCENE_H

#include "abstractscene.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

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

};

#endif // SCENE_H
