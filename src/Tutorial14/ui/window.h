#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>

class AbstractScene;
class QOpenGLContext;

/**
 * @class Window
 * @brief Classe representant la zone de rendu OpenGL
 *
 * Cette classe permet d'initialiser le contexte OpenGL et de
 * manipuler la scène de rendu.
 */
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

protected:
    void keyPressEvent(QKeyEvent* e);

private:
    QOpenGLContext* m_context;
    AbstractScene*  m_scene;
};

#endif // WINDOW_H
