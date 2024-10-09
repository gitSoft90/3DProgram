#pragma once

class Water : public KdGameObject
{
public:
	Water() {}
	~Water() override {}

	void Update() override;

	void DrawLesson() override;

	void Init() override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector3 m_pos = Math::Vector3::Zero;
};