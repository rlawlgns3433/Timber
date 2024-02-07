#pragma once
#include "GameObject.h"
class GameObjectBee : public GameObject
{
protected:
	GameObjectBee(const GameObjectBee&) = delete;
	GameObjectBee(GameObjectBee&&) = delete;
	GameObjectBee& operator=(const GameObjectBee&) = delete;
	GameObjectBee& operator=(GameObjectBee&&) = delete;

	std::string name;
	static std::string filePath;
	static sf::Texture textureBee;
	sf::Sprite spriteBee;

public:
	GameObjectBee(const std::string& name);
	GameObjectBee(const std::string& name, const std::string& filePath);

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

