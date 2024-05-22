#include "Earth.h"

Earth::Earth()
{
}

Earth::~Earth()
{
}

void Earth::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/earth.gltf");
}

void Earth::Update()
{
	// 地球の行列
	// 拡縮（大きさ）
	Math::Matrix earthScaleMat;
	earthScaleMat = Math::Matrix::CreateScale(1.5f);

	// 回転（自転用）
	/*Math::Matrix earthRotMatX;
	float _xDeg = 0;
	_xDeg += 2.0f;
	if (_xDeg > 360)
	{
		_xDeg = 0;
	}
	earthRotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(_xDeg));*/

	Math::Matrix earthRotMatSpinY;
	float _sYDeg = 0;
	_sYDeg += 2.0f;
	if (_sYDeg > 360)
	{
		_sYDeg = 0;
	}
	earthRotMatSpinY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_sYDeg));

	/*Math::Matrix earthRotMatZ;
	float _zDeg = 0;
	_zDeg += 2.0f;
	if (_zDeg > 360)
	{
		_zDeg = 0;
	}
	earthRotMatZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(_zDeg));*/

	// 回転（公転用）
	Math::Matrix earthRotMatRevoY;
	static float _rYDeg = 0;
	_rYDeg += 0.5f;
	if (_rYDeg > 360)
	{
		_rYDeg = 0;
	}
	earthRotMatRevoY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_rYDeg));

	// 移動
	Math::Matrix earthTransMat;

	earthTransMat = Math::Matrix::CreateTranslation(0, 0, -8);

	// 合成行列
	//m_mat = earthScaleMat * earthTransMat * earthRotMatRevoY;
	//m_mat = earthScaleMat * earthRotMatZ * earthTransMat * earthRotMatRevoY;
	m_mat = earthScaleMat * earthRotMatSpinY * earthTransMat * earthRotMatRevoY;
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mat);
}
