#ifndef PIPELINE_H
#define PIPELINE_H

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

    const QMatrix4x4 &GetTrans();

private:
    void InitScaleTransform(QMatrix4x4& m) const;
    void InitRotateTransform(QMatrix4x4& m) const;
    void InitTranslationTransform(QMatrix4x4& m) const;

    QVector3D m_scale;
    QVector3D m_worldPos;
    QVector3D m_rotateInfo;

    QMatrix4x4 m_transformation;
};

#endif // PIPELINE_H
