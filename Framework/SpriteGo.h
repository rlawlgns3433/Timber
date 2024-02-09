#pragma once
#include "GameObject.h"

class SpriteGo : public GameObject
{
protected :
	sf::Sprite __stdcall sprite;

public :
	SpriteGo(const std::string& name);
	void SetTexture(const sf::Texture& texture);
	void SetTexture(const std::string& textureId);

	void SetPosition(const sf::Vector2f pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f origin) override;


	void Draw(sf::RenderWindow& window);

};