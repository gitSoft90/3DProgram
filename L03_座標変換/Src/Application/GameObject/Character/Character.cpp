#include "Character.h"
#include "../../main.h"

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
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		// ①マウス座標を取得する
		POINT _mousePos;
		GetCursorPos(&_mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

		std::shared_ptr<KdCamera> _camera = m_wpCamera.lock();
		if (_camera)
		{
			Math::Vector3	_camPos = _camera->GetCameraMatrix().Translation();
			Math::Vector3	_rayDir		= Math::Vector3::Zero;
			float			_rayRenge	= 1000.f;
			// ②レイの発射方向を求める(_rayDir)
			_camera->
				GenerateRayInfoFromClientPos(_mousePos, _camPos, _rayDir, _rayRenge);
			// ③実際にレイを飛ばして衝突位置を求める
			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				Math::Vector3		_endRayPos = _camPos + (_rayDir * _rayRenge);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, _camPos, _endRayPos);

				// 実際の当たり判定の処理
				std::list<KdCollider::CollisionResult> _results;
				_terrain->Intersects(_rayInfo, &_results);

				// 結果が一つでも返って来ていたら
				if (_results.size())
				{
					for (const KdCollider::CollisionResult result : _results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}
	}

	// キャラクターの移動速度(真似しちゃダメですよ)
	float		  moveSpd = 0.05f;
	Math::Vector3 nowPos  = GetPos();
	Math::Vector3 moveVec = m_TargetPos - nowPos;
	if (moveVec.Length() < moveSpd) moveSpd = moveVec.Length();
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

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


		//Math::Vector3 rayDir = result - Math::Vector3::Zero;
		//float rayRange = 0.0f;
		//_camera->GenerateRayInfoFromClientPos(m_mousePos, pos, rayDir, rayRange);


		KdShaderManager::Instance().
			m_spriteShader.DrawCircle(result.x, result.y, 10, &kRedColor);
	
		// 仮の照準器の表示
		//KdShaderManager::Instance().
			//m_spriteShader.DrawTex(m_Tex,result.x,result.y + 100);
	}

	// ２Ｄ座標を３Ｄ座標へ変換

}
