#include "Character.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	if (!m_Tex)
	{
		m_Tex = std::make_shared<KdTexture>();
		m_Tex->Load("Asset/Textures/target.png");
	}
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;
	nowPos.y -= 0.01f;


	// マウス座標の取得
	GetCursorPos(&m_mousePos);

	ScreenToClient(APP.Instance().m_window.GetWndHandle(), &m_mousePos)


	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	std::shared_ptr<KdCamera> _camera = m_wpCamera.lock();
	if (_camera)
	{
		Math::Vector3 pos		 = GetPos();
		Math::Vector3 result	 = Math::Vector3::Zero;
		_camera->
			ConvertWorldToScreenDetail(pos,result);


		Math::Vector3 rayDir = result - Math::Vector3::Zero;
		float rayRange = 0.0f;
		_camera->GenerateRayInfoFromClientPos(m_mousePos, pos, rayDir, rayRange);


		KdShaderManager::Instance().
			m_spriteShader.DrawCircle(result.x, result.y, 10, &kRedColor);
	
		KdShaderManager::Instance().
			m_spriteShader.DrawTex(m_Tex,result.x,result.y);
	}
}
