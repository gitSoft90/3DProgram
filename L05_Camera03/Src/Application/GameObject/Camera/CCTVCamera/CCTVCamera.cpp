#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	CameraBase::Init();

	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 1.5f, 0.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void CCTVCamera::PostUpdate()
{
}