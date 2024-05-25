#pragma once

class Earth;

class Moon :public KdGameObject
{
public:
	Moon();
	~Moon()override;

	void Init()override;
	void Update()override;
	void DrawLit()override;

	//void SetOwner(Earth* a_pOwner) { m_pOwner = a_pOwner; }

private:
	std::shared_ptr<KdModelData> m_spModel = nullptr;

	std::shared_ptr<Earth> m_earth;
	//Earth* m_pOwner;
};