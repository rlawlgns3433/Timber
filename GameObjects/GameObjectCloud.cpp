#include "pch.h"
#include "GameObjectCloud.h"

GameObjectCloud::GameObjectCloud(const std::string& name)
    : name(name)
{
    if (name != "" && this->filePath != "")
    {
        textureCloud.loadFromFile(filePath);
        spriteCloud.setTexture(textureCloud);
    }
}

GameObjectCloud::GameObjectCloud(const std::string& name, const std::string& filePath)
    : name(name)
{
    this->filePath = filePath;
    if (name != "" && filePath != "")
    {
        textureCloud.loadFromFile(filePath);
        spriteCloud.setTexture(textureCloud);
    }
}

GameObjectCloud::GameObjectCloud(const std::string& name, sf::Texture& textureResource)
    :name(name)
{
    if (name != "" && filePath != "")
    {
        textureCloud.loadFromFile(filePath);
        spriteCloud.setTexture(textureResource);
    }
}

void GameObjectCloud::Init()
{
}

void GameObjectCloud::Release()
{
}

void GameObjectCloud::Reset()
{
}

void GameObjectCloud::Update(float dt)
{
}

void GameObjectCloud::Draw(sf::RenderWindow& window)
{
    window.draw(spriteCloud);
}

const std::string& GameObjectCloud::GetName() const
{
    return this->name;
}

const std::string& GameObjectCloud::GetFilePath() const
{
    return this->filePath;
}

const sf::Texture& GameObjectCloud::GetTexture() const
{
    return this->textureCloud;
}

sf::Sprite& GameObjectCloud::GetSprite()
{
    return this->spriteCloud;
}

void GameObjectCloud::SetName(const std::string& name)
{
    this->name = name;
}

void GameObjectCloud::SetTexture(const sf::Texture& texture)
{
    this->textureCloud = texture;
    spriteCloud.setTexture(this->textureCloud);
}

std::string GameObjectCloud::filePath;
sf::Texture GameObjectCloud::textureCloud;