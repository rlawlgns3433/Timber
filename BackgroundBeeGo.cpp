#include "pch.h"
#include "BackgroundBeeGo.h"

BackgroundBeeGo::BackgroundBeeGo(const std::string& name)
	: BackgroundMovingGo(name)
{
}

void BackgroundBeeGo::Update(float dt)
{
	time += dt;

	position += direction * speed * dt;


	if (time > beeChangeTime)
	{
		ReDirection();
	}
	sprite.setPosition(position);
}

void BackgroundBeeGo::Reset()
{
}

void BackgroundBeeGo::ReDirection()
{
	float angle = Utils::GetRandomAngle();
	std::cout << angle << std::endl;

	rotation.rotate(angle);
	direction = rotation * direction;
	std::cout << direction.x << " : " << direction.y << std::endl;


	if (direction.x > 0.f) { sprite.setScale(-1.f, 1.f); }
	else if (direction.x < 0.f) { sprite.setScale(1.f, 1.f); }

	beeChangeTime = time + beeChangeDuration;
}
