#include "pipeline.h"

const QMatrix4x4& Pipeline::GetTrans()
{
    QMatrix4x4 ScaleTrans, RotateTrans, TranslationTrans, CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    ScaleTrans.scale(m_scale.x(), m_scale.y(), m_scale.z());

    RotateTrans.rotate(m_rotateInfo.x(), QVector3D(1.0, 0.0, 0.0));
    RotateTrans.rotate(m_rotateInfo.y(), QVector3D(0.0, 1.0, 0.0));
    RotateTrans.rotate(m_rotateInfo.z(), QVector3D(0.0, 0.0, 1.0));

    TranslationTrans.translate(m_worldPos.x(), m_worldPos.y(), m_worldPos.z());
    CameraTranslationTrans.translate(-m_camera.Pos.x(), -m_camera.Pos.y(), -m_camera.Pos.z());
    CameraRotateTrans.lookAt(m_camera.Pos, m_camera.Target, m_camera.Up);

    PersProjTrans.perspective(m_persProj.FOV, m_persProj.Width/m_persProj.Height, m_persProj.zNear, m_persProj.zFar);

    m_transformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * TranslationTrans * RotateTrans * ScaleTrans;

    //m_transformation = PersProjTrans * TranslationTrans * RotateTrans * ScaleTrans;

    return m_transformation;
}
