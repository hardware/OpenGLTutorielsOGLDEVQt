#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <QObject>

class QOpenGLContext;

class AbstractScene : public QObject
{
public:
    AbstractScene(QObject* parent = 0);

    void setContext(QOpenGLContext *context) { m_context = context; }
    QOpenGLContext* context() const { return m_context; }

    virtual void initialize() = 0;
    virtual void update(float t) = 0;
    virtual void render() = 0;
    virtual void resize(int width, int height) = 0;

protected:
    QOpenGLContext *m_context;

};

#endif // ABSTRACTSCENE_H
