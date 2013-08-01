#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>

class AbstractScene;
class QOpenGLContext;

class Window : public QWindow
{
    Q_OBJECT

public:
    Window(QScreen *screen = 0);

private:
    void initializeGL();

protected slots:
    void resizeGL();
    void paintGL();
    void updateScene();

private:
    QOpenGLContext* m_context;
    AbstractScene*  m_scene;
};

#endif // WINDOW_H
