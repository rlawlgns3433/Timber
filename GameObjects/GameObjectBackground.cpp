#include "pch.h"
#include "GameObjectBackground.h"

GameObjectBackground::GameObjectBackground(const std::string& name,const std::string& filePath)
	: name(name), filePath(filePath) 
{
	if (name != "" && filePath != "")
	{
		textureBackground.loadFromFile(filePath);
		spriteBackground.setTexture(textureBackground);
	}
}

void GameObjectBackground::Init()
{
}

void GameObjectBackground::Release()
{
}

void GameObjectBackground::Reset()
{
}

void GameObjectBackground::Update(float dt)
{
}

void GameObjectBackground::Draw(sf::RenderWindow& window)
{
	window.draw(spriteBackground);
}

const std::string& GameObjectBackground::GetName() const
{
	return this->name;
}

const std::string& GameObjectBackground::GetFilePath() const
{
	return this->filePath;
}

const sf::Texture& GameObjectBackground::GetTexture() const
{
	return this->textureBackground;
}

sf::Sprite& GameObjectBackground::GetSprite()
{
	return this->spriteBackground;
}

void GameObjectBackground::SetName(const std::string& name)
{
	this->name = name;
}

void GameObjectBackground::SetTexture(const sf::Texture& texture)
{
	this->textureBackground = texture;
	this->spriteBackground.setTexture(this->textureBackground);
}
