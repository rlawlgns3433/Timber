#include "Utils.h"
#include "Defines.h"

void Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	// Rect width, height

	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);
}

void Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	SetOrigin(obj, originPreset, obj.getLocalBounds());
}

void Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	SetOrigin(obj, originPreset, obj.getLocalBounds());

}

void Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	SetOrigin(obj, originPreset, obj.getLocalBounds());
}

// 두 Random 값은 같음
sf::Vector2f Utils::GetRandomVector2(float start, float end)
{
	float randVal = (rand() % ((int)(end * 100) - (int)(start*100))) + start * 100;
	return sf::Vector2f(randVal / 100, randVal / 100);
}


float Utils::GetRandomAngle()
{
	return (float)(rand() / RAND_MAX) * 360.f;
}