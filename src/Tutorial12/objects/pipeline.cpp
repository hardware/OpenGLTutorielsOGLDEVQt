#include "pipeline.h"
#include "../math/math3D.h"

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

void Pipeline::InitPerspectiveProj(QMatrix4x4& m) const
{
    m.perspective(m_persProj.FOV, m_persProj.Width/m_persProj.Height, m_persProj.zNear, m_persProj.zFar);
}

const QMatrix4x4& Pipeline::GetTrans()
{
    QMatrix4x4 ScaleTrans, RotateTrans, TranslationTrans, PersProjTrans;

    InitScaleTransform(ScaleTrans);
    InitRotateTransform(RotateTrans);
    InitTranslationTransform(TranslationTrans);
    InitPerspectiveProj(PersProjTrans);

    m_transformation = PersProjTrans * TranslationTrans * RotateTrans * ScaleTrans;

    return m_transformation;
}
