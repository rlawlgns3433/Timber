#include "pch.h"
#include "TestGameObject.h"

TestGameObject::TestGameObject(const std::string& name) : GameObject(name)
{

}

void TestGameObject::Init()
{
}

void TestGameObject::Release()
{
}

void TestGameObject::Reset()
{
}

void TestGameObject::Update(float dt)
{

}

void TestGameObject::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
