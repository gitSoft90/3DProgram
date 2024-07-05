#pragma once

#include "../CameraBase.h"

class CCTVCamera:public CameraBase
{
public:
	CCTVCamera() {}
	~CCTVCamera() {}

	void Init();
	void PostUpdate();

private:
	void UpdateLookAtRotate(const Math::Vector3& targetPos);

};
