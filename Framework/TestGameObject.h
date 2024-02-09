#pragma once
#include "GameObject.h"

class TestGameObject : public GameObject
{
protected :

public :
	
	TestGameObject(const std::string& name = "");
	
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	std::string name;
	sf::Text text;
};