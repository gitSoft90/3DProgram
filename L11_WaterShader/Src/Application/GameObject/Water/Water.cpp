#include "Water.h"

void Water::Update()
{
}

void Water::DrawLesson()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_LessonShader.DrawModel(*m_spModel->GetData());
	}
}

void Water::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/LessonData/Stage/Water/Water.gltf");
		
		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Water", m_spModel, KdCollider::TypeGround);
	}
}
