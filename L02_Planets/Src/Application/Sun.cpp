#include "Sun.h"

Sun::Sun()
{
}

Sun::~Sun()
{
}

void Sun::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/sun.gltf");
}

void Sun::Update()
{
	// 太陽の行列
	// 拡縮（大きさ）
	Math::Matrix sunScaleMat;
	sunScaleMat = Math::Matrix::CreateScale(1.5f);

	//// 回転（自転用）
	//Math::Matrix sunRotMatX;
	//float _xDeg = 0;
	//_xDeg += 2.0f;
	//if (_xDeg > 360)
	//{
	//	_xDeg = 0;
	//}
	//sunRotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(_xDeg));



	Math::Matrix sunRotMatSpinY;
	float _sYDeg = 0;
	_sYDeg += 2.0f;
	if (_sYDeg > 360)
	{
		_sYDeg = 0;
	}
	sunRotMatSpinY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_sYDeg));

	/*Math::Matrix earthRotMatZ;
	float _zDeg = 0;
	_zDeg += 2.0f;
	if (_zDeg > 360)
	{
		_zDeg = 0;
	}
	earthRotMatZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(_zDeg));*/

	// 回転（公転用）
	/*Math::Matrix sunRotMatRevoY;
	static float _rYDeg = 0;
	_rYDeg += 0.5f;
	if (_rYDeg > 360)
	{
		_rYDeg = 0;
	}
	sunRotMatRevoY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_rYDeg));*/

	// 移動
	Math::Matrix sunTransMat;
	Math::Vector3 _pos = { 0,0,0 };

	sunTransMat = Math::Matrix::CreateTranslation(0, 0, 0);

	// 合成行列
	//m_mat = sunScaleMat * sunRotMatX * sunTransMat;
	m_mWorld = sunScaleMat * sunRotMatSpinY * sunTransMat;
	//m_mat = sunScaleMat * sunTransMat;
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}