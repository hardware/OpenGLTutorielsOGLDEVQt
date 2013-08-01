#include "scene.h"
#include "../math/math3D.h"

#include <QObject>
#include <QOpenGLContext>

Scene::Scene(QObject *parent)
    : AbstractScene(parent),
      m_shaderProgram(),
      m_vertexPositionBuffer(QOpenGLBuffer::VertexBuffer),
      m_vertexColorBuffer(QOpenGLBuffer::VertexBuffer)
{}

void Scene::initialize()
{
    // Load, compile and link the shader program
    prepareShaderProgram();

    // Prepare our geometry and associate it with shader program
    prepareVertexBuffers();
}

void Scene::update(float t)
{
    Q_UNUSED(t);
}

void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_shaderProgram.bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Scene::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Scene::prepareShaderProgram()
{
    // Load and compile the vertex shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resources/shaders/basic.vert") )
        qCritical() << "Could not compile vertex shader. Log : " << m_shaderProgram.log();

    // Load and compile the fragment shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resources/shaders/basic.frag") )
        qCritical() << "Could not compile fragment shader. Log : " << m_shaderProgram.log();

    // Link the shaders together into a complete shader program (pipeline)
    if( ! m_shaderProgram.link() )
        qCritical() << "Could not link shader program. Log : " << m_shaderProgram.log();
}

void Scene::prepareVertexBuffers()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f( 1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f( 0.0f,  1.0f, 0.0f);

    Vector3f colorVertices[3];
    colorVertices[0] = Vector3f(1.0f, 0.0f, 0.0f);
    colorVertices[1] = Vector3f(0.0f, 1.0f, 0.0f);
    colorVertices[2] = Vector3f(0.0f, 0.0f, 1.0f);

    m_vertexPositionBuffer.create();
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexPositionBuffer.bind();
    m_vertexPositionBuffer.allocate(Vertices, sizeof(Vertices));

    m_vertexColorBuffer.create();
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexColorBuffer.bind();
    m_vertexColorBuffer.allocate(colorVertices, sizeof(colorVertices));

    m_shaderProgram.bind();

    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);
}
