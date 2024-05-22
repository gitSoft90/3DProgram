#include "Moon.h"

#include "Earth.h"

Moon::Moon()
{
}

Moon::~Moon()
{
}

void Moon::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/moon.gltf");
}

void Moon::Update()
{
	// 月の行列
	// 拡縮（大きさ）
	Math::Matrix moonScaleMat;
	moonScaleMat = Math::Matrix::CreateScale(1);

	// 回転（自転用）
	/*Math::Matrix moonRotMatX;
	float _xDeg = 0;
	_xDeg += 2.0f;
	if (_xDeg > 360)
	{
		_xDeg = 0;
	}
	moonRotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(_xDeg));*/

	/*Math::Matrix moonRotMatSpinY;
	float _sYDeg = 0;
	_sYDeg += 2.0f;
	if (_sYDeg > 360)
	{
		_sYDeg = 0;
	}
	moonRotMatSpinY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_sYDeg));*/

	/*Math::Matrix moonRotMatZ;
	float _zDeg = 0;
	_zDeg += 2.0f;
	if (_zDeg > 360)
	{
		_zDeg = 0;
	}
	moonRotMatZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(_zDeg));*/

	// 回転（公転用）
	Math::Matrix moonRotMatRevoY;
	static float _rYDeg = 0;
	_rYDeg += 0.5f;
	if (_rYDeg > 360)
	{
		_rYDeg = 0;
	}
	moonRotMatRevoY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_rYDeg));

	// 移動
	Math::Matrix moonTransMat;	
	//Earth* earth;
	Earth earth;

	//moonTransMat = Math::Matrix::CreateTranslation(earth->GetPos().x + 5, earth->GetPos().y, earth->GetPos().z);
	moonTransMat = Math::Matrix::CreateTranslation(earth.GetPos().x + 5, earth.GetPos().y, earth.GetPos().z);

	// 合成行列
	//m_mat = moonScaleMat * moonRotMatRevoY * moonTransMat;
	m_mat = moonScaleMat * moonTransMat * moonRotMatRevoY;
	//m_mat = moonScaleMat * moonRotMatZ * moonTransMat * moonRotMatRevoY;
	//m_mat = moonScaleMat * moonRotMatSpinY * moonTransMat * moonRotMatRevoY;
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mat);
}