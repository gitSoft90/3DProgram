﻿#pragma once

class CameraBase : public KdGameObject
{
public:
	CameraBase()						{}
	virtual ~CameraBase()	override	{}

	void Init()				override;
	void Update()			override;
	void PreDraw()			override;

	void SetTarget(const std::shared_ptr<KdGameObject>& target)
	{
		m_wpTarget = target;
	}

	const Math::Matrix GetRotationMatrix() const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_DegAng.y),
			DirectX::XMConvertToRadians(m_DegAng.x),
			DirectX::XMConvertToRadians(m_DegAng.z));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::
			CreateRotationY(DirectX::XMConvertToRadians(m_DegAng.y));
	}

	void RegistHitObject(const std::shared_ptr<KdGameObject>& object)
	{
		m_wpHitObjectList.push_back(object);
	}

private:
	// カメラの回転用角度
	Math::Vector3				m_DegAng = Math::Vector3::Zero;

protected:
	void UpdateRotateByMouse();

	std::shared_ptr<KdCamera>	m_spCamera = nullptr;
	std::weak_ptr<KdGameObject> m_wpTarget;
	std::vector<std::weak_ptr<KdGameObject>> m_wpHitObjectList{};

	Math::Matrix			  m_mLocalPos = Math::Matrix::Identity;
	Math::Matrix			  m_mRotation = Math::Matrix::Identity;

	// カメラ回転用マウス座標
	POINT						m_FixMousePos{};
};
