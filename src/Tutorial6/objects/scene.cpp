#include "scene.h"

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
      m_vertexColorBuffer(QOpenGLBuffer::VertexBuffer)
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

    // Initialiser les VBOs pour les associer avec les shaders
    prepareVertexBuffers();
}

void Scene::update(float t)
{
    Q_UNUSED(t);
}

void Scene::render()
{
    // Efface le tampon d'affichage
    glClear(GL_COLOR_BUFFER_BIT);

    static float scale = 0.0f;
    scale += 0.01f;

    static float theta = 0.0f;
    theta += 0.8f;

    QMatrix4x4 worldMatrix;

    /*
    [ TRANSLATION MATRIX ]
        | 1  0  0  X |
        | 0  1  0  Y |
        | 0  0  1  Z |
        | 0  0  0  1 |
    */

    worldMatrix.translate(sinf(scale) * 0.6, 0.0f, 0.0f);

    /*
    [ ROTATION MATRIX (X-axis) ]		[ ROTATION MATRIX (Y-axis) ]		[ ROTATION MATRIX (Z-axis) ]
     |  1     0       0     0 |			 |  cos(α)  0   sin(α)  0 |			 |  cos(α) -sin(α) 0    0 |
     |  0   cos(α) -sin(α)  0 |			 |    0     1     0     0 |			 |  sin(α)  cos(α) 0    0 |
     |  0   sin(α)  cos(α)  0 |			 | -sin(α)  0   cos(α)  0 |			 |    0      0     1    0 |
     |  0     0       0     1 |			 |    0     0     0     1 |			 |    0      0     0    1 |
    */

    worldMatrix.rotate(theta, 0.0f, 0.0f, 0.1f);

    /*
    [ SCALING MATRIX ]
      | X  0  0  0 |
      | 0  Y  0  0 |
      | 0  0  Z  0 |
      | 0  0  0  1 |
    */

    worldMatrix.scale(fabs(sinf(scale))+0.2);

    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("gWorld", worldMatrix);

    glDrawArrays(GL_TRIANGLES, 0, m_positionVertices.size());
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
    // 3 vertices représentant les 3 points du triangle
    m_positionVertices.push_back(QVector3D(-0.5f, -0.5f, 0.0f));
    m_positionVertices.push_back(QVector3D( 0.5f, -0.5f, 0.0f));
    m_positionVertices.push_back(QVector3D( 0.0f,  0.5f, 0.0f));

    // 3 vertices représentant les 3 couleurs du triangle
    m_colorVertices.push_back(QVector3D(1.0f, 0.0f, 0.0f));
    m_colorVertices.push_back(QVector3D(0.0f, 1.0f, 0.0f));
    m_colorVertices.push_back(QVector3D(0.0f, 0.0f, 1.0f));

    // Création des VertexBufferObjects pour stocker les vertices dans le GPU
    m_vertexPositionBuffer.create();
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexPositionBuffer.bind();
    m_vertexPositionBuffer.allocate(m_positionVertices.constData(), m_positionVertices.size() * sizeof(QVector3D));

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
