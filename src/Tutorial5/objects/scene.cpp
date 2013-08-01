#include "scene.h"

#include <math.h>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_1>

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

    m_shaderProgram.bind();

    // On définit une variable nommée gScale de type uniform
    m_shaderProgram.setUniformValue("gScale", sinf(scale)); // -1 < scale < +1
    /*
    Code OpenGL équivalent :

    GLuint gScaleLocation;
    gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");
    glUniform1f(gScaleLocation, sinf(scale));
    */

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
    m_positionVertices.push_back(QVector3D(-1.0f, -1.0f, 0.0f));
    m_positionVertices.push_back(QVector3D( 1.0f, -1.0f, 0.0f));
    m_positionVertices.push_back(QVector3D( 0.0f,  1.0f, 0.0f));

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

    /*
    Code OpenGL équivalent :

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    */

    m_shaderProgram.bind();

    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexPosition");
    m_shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertexColor");
    m_shaderProgram.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 3);

    /*
    Code OpenGL équivalent :

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    */
}
