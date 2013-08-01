#include "window.h"

#include "../objects/scene.h"

#include <QCoreApplication>
#include <QOpenGLContext>
#include <QTimer>

Window::Window(QScreen *screen) : QWindow(screen), m_scene(new Scene(this))
{
    setSurfaceType(OpenGLSurface);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);

    setFormat(format);
    create();
    resize(800, 600);

    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();

    m_context->makeCurrent(this);
    m_scene->setContext(m_context);
    initializeGL();

    connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGL()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGL()));
    resizeGL();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(16);
}

void Window::initializeGL()
{
    m_context->makeCurrent(this);
    m_scene->initialize();
}

void Window::paintGL()
{
    m_context->makeCurrent(this);
    m_scene->render();
    m_context->swapBuffers(this);
}

void Window::resizeGL()
{
    m_context->makeCurrent(this);
    m_scene->resize(width(), height());
}

void Window::updateScene()
{
    m_scene->update(0.0f);
    paintGL();
}
