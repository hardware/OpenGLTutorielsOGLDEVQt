﻿#include "window.h"

#include "../objects/scene.h"
#include "../objects/camera.h"

#include <QCoreApplication>
#include <QOpenGLContext>
#include <QKeyEvent>
#include <QTimer>

/**
 * @brief Constructeur paramétré
 *
 * Permet d'initialiser la fenêtre et les propriétés de la zone de rendu OpenGL
 *
 * @param screen Propriétés de l'écran
 */
Window::Window(QScreen *screen) : QWindow(screen), m_scene(new Scene(this))
{
    // On définit le type de la zone de rendu, dans notre cas il
    // s'agit d'une zone OpenGL
    setSurfaceType(QSurface::OpenGLSurface);

    // Puis on définit les propriétés de la zone de rendu
    QSurfaceFormat format;

    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(4); // Multisampling x4
    format.setProfile(QSurfaceFormat::CoreProfile); // Fonctions obsolètes d'OpenGL non disponibles
    format.setOption(QSurfaceFormat::DebugContext);

    // On applique le format et on créer la fenêtre
    setFormat(format);
    create();
    resize(800, 600);

    // On créer le contexte OpenGL et on définit son format
    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();
    m_context->makeCurrent(this);

    // On définit le contexte OpenGL de la scène
    m_scene->setContext(m_context);

    initializeGL();

    connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGL()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGL()));

    resizeGL();

    // Création d'un timer permettant la mise à jour de la zone de rendu 60 fois par seconde
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(16); // f = 1 / 16.10e-3 = 60Hz
}

/**
 * @brief Initialisation de la zone de rendu
 */
void Window::initializeGL()
{
    m_context->makeCurrent(this);
    m_scene->initialize();
}

/**
 * @brief Mise à jour de la zone de rendu (redessine la scène)
 */
void Window::paintGL()
{
    m_context->makeCurrent(this);
    m_scene->render();
    m_context->swapBuffers(this);
}

/**
 * @brief Permet de redimensionner la zone de rendu
 */
void Window::resizeGL()
{
    m_context->makeCurrent(this);
    m_scene->resize(width(), height());
}

/**
 * @brief Mise à jour de la scène
 */
void Window::updateScene()
{
    m_scene->update(0.0f);
    paintGL();
}

void Window::keyPressEvent(QKeyEvent* e)
{
    Scene* scene = static_cast<Scene*>(m_scene);

    switch (e->key())
    {
    case Qt::Key_Left:

        scene->getCamera().moveLeft();
        break;

    case Qt::Key_Right:

        scene->getCamera().moveRight();
        break;

    case Qt::Key_Up:

        scene->getCamera().moveForward();
        break;

    case Qt::Key_Down:

        scene->getCamera().moveBack();
        break;

    case Qt::Key_Escape:

        QCoreApplication::instance()->quit();
        break;

    default:
        QWindow::keyPressEvent( e );
    }
}
