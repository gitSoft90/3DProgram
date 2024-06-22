﻿#include "FPSCamera.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0.f, 1.5f, 0.f);

	// マウスカーソルを画面中央に固定する
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void FPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転処理
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	m_mWorld = m_mRotation * m_mLocalPos * _targetMat;

	// 親クラスの初期化呼び出し		//m_mWorldの計算が終わった後に呼び出す
	CameraBase::Update();
}