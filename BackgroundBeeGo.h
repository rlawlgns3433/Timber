#pragma once
#include "BackgroundMovingGo.h"
class BackgroundBeeGo : public BackgroundMovingGo
{
protected:
	float time = 0.f;
	float beeChangeDuration = 1.f;
	float beeChangeTime = beeChangeDuration;

public:
	BackgroundBeeGo(const std::string& name);

	void Update(float dt) override;
	void Reset() override; // 초기 위치
	void ReDirection();
};