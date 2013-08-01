#ifndef PIPELINE_H
#define PIPELINE_H

#include "../math/math3D.h"

#include <QVector3D>
#include <QMatrix4x4>

class Pipeline
{
public:
    Pipeline()
    {
        m_scale      = QVector3D(1.0f, 1.0f, 1.0f);
        m_worldPos   = QVector3D(0.0f, 0.0f, 0.0f);
        m_rotateInfo = QVector3D(0.0f, 0.0f, 0.0f);
    }

    void Scale(float ScaleX, float ScaleY, float ScaleZ)
    {
        m_scale.setX(ScaleX);
        m_scale.setY(ScaleY);
        m_scale.setZ(ScaleZ);
    }

    void WorldPos(float x, float y, float z)
    {
        m_worldPos.setX(x);
        m_worldPos.setY(y);
        m_worldPos.setZ(z);
    }

    void Rotate(float RotateX, float RotateY, float RotateZ)
    {
        m_rotateInfo.setX(RotateX);
        m_rotateInfo.setY(RotateY);
        m_rotateInfo.setZ(RotateZ);
    }

    void SetPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
    {
        m_persProj.FOV    = FOV;
        m_persProj.Width  = Width;
        m_persProj.Height = Height;
        m_persProj.zNear  = zNear;
        m_persProj.zFar   = zFar;
    }

    void SetCamera(const QVector3D& Pos, const QVector3D& Target, const QVector3D& Up)
    {
        m_camera.Pos    = Pos;
        m_camera.Target = Target;
        m_camera.Up     = Up;
    }

    const QMatrix4x4 &GetTrans();

private:
    QVector3D m_scale;
    QVector3D m_worldPos;
    QVector3D m_rotateInfo;

    struct {
        float FOV;
        float Width;
        float Height;
        float zNear;
        float zFar;
    } m_persProj;

    struct {
        QVector3D Pos;
        QVector3D Target;
        QVector3D Up;
    } m_camera;

    QMatrix4x4 m_transformation;
};

#endif // PIPELINE_H
