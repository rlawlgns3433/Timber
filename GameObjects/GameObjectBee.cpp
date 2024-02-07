#include "pch.h"
#include "GameObjectBee.h"

GameObjectBee::GameObjectBee(const std::string& name)
	: name(name)
{
	if (name != "" && this->filePath != "")
	{
		textureBee.loadFromFile(filePath);
		spriteBee.setTexture(textureBee);
	}
}

GameObjectBee::GameObjectBee(const std::string& name, const std::string& filePath)
	: name(name)
{
	this->filePath = filePath;
	if (name != "" && filePath != "")
	{
		textureBee.loadFromFile(filePath);
		spriteBee.setTexture(textureBee);
	}
}

void GameObjectBee::Init()
{
}

void GameObjectBee::Release()
{
}

void GameObjectBee::Reset()
{
}

void GameObjectBee::Update(float dt)
{
}

void GameObjectBee::Draw(sf::RenderWindow& window)
{
	window.draw(spriteBee);
}

const std::string& GameObjectBee::GetName() const
{
	return this->name;
}

const std::string& GameObjectBee::GetFilePath() const
{
	return this->filePath;
}

const sf::Texture& GameObjectBee::GetTexture() const
{
	return this->textureBee;
}

sf::Sprite& GameObjectBee::GetSprite()
{
	return this->spriteBee;
}

void GameObjectBee::SetName(const std::string& name)
{
	this->name = name;
}

void GameObjectBee::SetTexture(const sf::Texture& texture)
{
	this->textureBee = texture;
	spriteBee.setTexture(this->textureBee);
}

std::string GameObjectBee::filePath;
sf::Texture GameObjectBee::textureBee;