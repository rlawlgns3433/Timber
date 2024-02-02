#pragma once
#include <SFML/Graphics.hpp>
#include "Defines.h"

enum class Origins
{
	// enum class ���� Origins::TL
	// ���� ���� enum�� �����ϴ�.


	// T M B
	// L C R

	// TL TC TR
	// ML MC MR
	// BL BC BR

	TL, TC, TR, ML, MC, MR, BL, BC, BR,
};

class Utils
{
public : 
	static void SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static void SetOrigin(sf::Sprite& obj, Origins originPreset);
	static void SetOrigin(sf::Text& obj, Origins originPreset);
	static void SetOrigin(sf::Shape& obj, Origins originPreset);
	static sf::Vector2f GetRandomVector2(float start, float end);
};