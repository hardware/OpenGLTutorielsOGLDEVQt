#include "pipeline.h"

void Pipeline::InitScaleTransform(QMatrix4x4& m) const
{
    m.scale(m_scale.x(), m_scale.y(), m_scale.z());
}

void Pipeline::InitRotateTransform(QMatrix4x4& m) const
{
    m.rotate(m_rotateInfo.x(), QVector3D(1.0, 0.0, 0.0));
    m.rotate(m_rotateInfo.y(), QVector3D(0.0, 1.0, 0.0));
    m.rotate(m_rotateInfo.z(), QVector3D(0.0, 0.0, 1.0));
}

void Pipeline::InitTranslationTransform(QMatrix4x4& m) const
{
    m.translate(m_worldPos.x(), m_worldPos.y(), m_worldPos.z());
}

const QMatrix4x4& Pipeline::GetTrans()
{
    QMatrix4x4 ScaleTrans, RotateTrans, TranslationTrans;

    InitScaleTransform(ScaleTrans);
    InitRotateTransform(RotateTrans);
    InitTranslationTransform(TranslationTrans);

    m_transformation = TranslationTrans * RotateTrans * ScaleTrans;

    return m_transformation;
}
