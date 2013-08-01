#include "scene.h"
#include "pipeline.h"

#include <math.h>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_1>
#include <QMatrix4x4>

/**
 * @brief Constructeur paramétré
 *
 * Permet d'initialiser le type des buffers
 *
 * @param parent Objet parent
 */
Scene::Scene(QObject *parent)
    : AbstractScene(parent),
      m_vertexPositionBuffer(QOpenGLBuffer::VertexBuffer),
      m_vertexColorBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{}

void Scene::initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Récupération des fonctions d'OpenGL 3.1
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_1>();

    if ( ! m_funcs )
    {
        qFatal("Requires OpenGL >= 3.1");
        exit(1);
    }

    m_funcs->initializeOpenGLFunctions();

    // Charge, compile et link le Vertex et Fragment Shader
    prepareShaderProgram();

    // Initialisation des buffers
    prepareVertexBuffers();
    prepareIndexBuffer();
}

void Scene::update(float t)
{
    Q_UNUSED(t);
}

void Scene::render()
{
    // Efface le tampon d'affichage
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.01f;

    Pipeline p;
    p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
    p.WorldPos(sinf(Scale), 0.0f, 0.0f);
    p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);

    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("gWorld", p.GetTrans());

    glDrawElements(GL_LINE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
}

void Scene::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Scene::prepareShaderProgram()
{
    // Charge et compile le Vertex Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resources/shaders/basic.vert") )
        qCritical() << "Could not compile vertex shader. Log : " << m_shaderProgram.log();

    // Charge et compile le Fragment Shader
    if( ! m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resources/shaders/basic.frag") )
        qCritical() << "Could not compile fragment shader. Log : " << m_shaderProgram.log();

    // Permet de linker les shaders (pipeline)
    if( ! m_shaderProgram.link() )
        qCritical() << "Could not link shader program. Log : " << m_shaderProgram.log();
}

void Scene::prepareVertexBuffers()
{
    m_positionVertices.push_back(QVector3D(-0.8f, -0.8f,  0.0f));
    m_positionVertices.push_back(QVector3D( 0.0f, -0.8f,  0.8f));
    m_positionVertices.push_back(QVector3D( 0.8f, -0.8f,  0.0f));
    m_positionVertices.push_back(QVector3D( 0.0f,  0.8f,  0.0f));
    m_positionVertices.push_back(QVector3D( 0.0f, -0.8f, -0.8f));

    m_vertexPositionBuffer.create();
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexPositionBuffer.bind();
    m_vertexPositionBuffer.allocate(m_positionVertices.constData(), m_positionVertices.size() * sizeof(QVector3D));

    m_colorVertices.push_back(QVector3D(1.0f, 0.0f, 0.0f));
    m_colorVertices.push_back(QVector3D(0.0f, 1.0f, 0.0f));
    m_colorVertices.push_back(QVector3D(0.0f, 0.0f, 1.0f));
    m_colorVertices.push_back(QVector3D(0.5f, 0.5f, 0.0f));

    m_vertexColorBuffer.create();
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexColorBuffer.bind();
    m_vertexColorBuffer.allocate(m_colorVertices.constData(), m_colorVertices.size() * sizeof(QVector3D));

    m_shaderProgram.bind();

    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);
}

void Scene::prepareIndexBuffer()
{
    m_indices.push_back(0); m_indices.push_back(2); m_indices.push_back(3);
    m_indices.push_back(0); m_indices.push_back(1); m_indices.push_back(3);
    m_indices.push_back(2); m_indices.push_back(1); m_indices.push_back(3);
    m_indices.push_back(1); m_indices.push_back(2); m_indices.push_back(0);
    m_indices.push_back(0); m_indices.push_back(4); m_indices.push_back(3);
    m_indices.push_back(4); m_indices.push_back(2); m_indices.push_back(3);
    m_indices.push_back(0); m_indices.push_back(4); m_indices.push_back(2);

    m_indexBuffer.create();
    m_indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer.bind();
    m_indexBuffer.allocate(m_indices.constData(), m_indices.size() * sizeof(GLuint));
}
