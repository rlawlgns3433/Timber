#pragma once
#include "GameObject.h"
class GameObjectBackground : public GameObject
{
protected :
	GameObjectBackground(const GameObjectBackground&) = delete;
	GameObjectBackground(GameObjectBackground&&) = delete;
	GameObjectBackground& operator=(const GameObjectBackground&) = delete;
	GameObjectBackground& operator=(GameObjectBackground&&) = delete;

	std::string name;
	std::string filePath;
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;

public :
	GameObjectBackground(const std::string& name, const std::string& filePath);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	const std::string& GetName() const;
	const std::string& GetFilePath() const;
	const sf::Texture& GetTexture() const;
	sf::Sprite& GetSprite();
	void SetName(const std::string& name);
	void SetTexture(const sf::Texture& texture);
};