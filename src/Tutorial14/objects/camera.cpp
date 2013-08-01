#include "camera.h"

const static float StepScale = 0.001f;

Camera::Camera()
{
    m_pos    = QVector3D(0.0f, 0.0f, 1.1f);
    m_target = QVector3D(0.0f, 0.0f, 1.0f);
    m_up     = QVector3D(0.0f, 1.0f, 0.0f);
}

void Camera::moveLeft()
{
    QVector3D left = QVector3D::crossProduct(m_target, m_up);
    left *= StepScale;

    m_pos += left;
}

void Camera::moveRight()
{
    QVector3D right = QVector3D::crossProduct(m_up, m_target);
    right *= StepScale;

    m_pos += right;
}

void Camera::moveForward()
{
    m_pos += (m_target * StepScale);
}

void Camera::moveBack()
{
    m_pos -= (m_target * StepScale);
}
