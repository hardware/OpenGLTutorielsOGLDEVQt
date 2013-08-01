#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>

class Camera
{
public:

    Camera();

    const QVector3D& GetPos() const
    {
        return m_pos;
    }

    const QVector3D& GetTarget() const
    {
        return m_target;
    }

    const QVector3D& GetUp() const
    {
        return m_up;
    }

    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBack();

private:

    QVector3D m_pos;
    QVector3D m_target;
    QVector3D m_up;
};

#endif // CAMERA_H
