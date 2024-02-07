#pragma once
#include "GameObject.h"
class GameObjectCloud : public GameObject
{
protected :
	GameObjectCloud(const GameObjectCloud&) = delete;
	GameObjectCloud(GameObjectCloud&&) = delete;
	GameObjectCloud& operator=(const GameObjectCloud&) = delete;
	GameObjectCloud& operator=(GameObjectCloud&&) = delete;

	std::string name;
	static std::string filePath;
	static sf::Texture textureCloud;
	sf::Sprite spriteCloud;

public :
	GameObjectCloud(const std::string& name);
	GameObjectCloud(const std::string& name, const std::string& filePath);
	GameObjectCloud(const std::string& name, sf::Texture& textureResource);

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