#include "pch.h"
#include "BackgroundMovingGo.h"

BackgroundMovingGo::BackgroundMovingGo(const std::string& name) : SpriteGo(name)
{
}

void BackgroundMovingGo::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

	if (position.x < bounds.left || position.x > bounds.left + bounds.width)
	{
		RePosition();
	}
}

void BackgroundMovingGo::Reset()
{
	speed = Utils::RandomRange(speedMin, speedMax);
	direction.x = Utils::RandomValue() > 0.5f ? 1.f : -1.f;

	sf::Vector2f newPos;
	newPos.x = Utils::RandomRange(bounds.left, bounds.left + bounds.width);
	newPos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);

	ReScale();
	SetPosition(newPos);
}

void BackgroundMovingGo::RePosition()
{
	speed = Utils::RandomRange(speedMin, speedMax);
	sf::Vector2f newPos;

	if (Utils::RandomValue() > 0.5f)
	{
		direction.x = 1.f;
		newPos.x = bounds.left;
	}
	else
	{
		direction.x = -1.f;
		newPos.x = bounds.left + bounds.width;
	}
	ReScale();
	newPos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);

	SetPosition(newPos);
}

void BackgroundMovingGo::ReScale()
{
	float newScale = Utils::RandomRange(0.7f, 1.f);
	scale.x = direction.x < 0 ? newScale : -newScale;
	scale.y = newScale;
	sprite.setScale(scale);
}
