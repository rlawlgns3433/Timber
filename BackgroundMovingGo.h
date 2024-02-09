#pragma once
#include "SpriteGo.h"
class BackgroundMovingGo : public SpriteGo
{
protected :

public :
	sf::FloatRect bounds = { 0.f, 0.f, 1920.f, 1080.f };
	sf::Vector2f direction = { 1.f, 0.f };
	sf::Vector2f scale = { 1.f, 1.f };

	float speed = 100.f;
	float speedMin = 100.f;
	float speedMax = 200.f;

	BackgroundMovingGo(const std::string& name = "");
	void Update(float dt) override;
	void Reset() override; // �ʱ� ��ġ
	void RePosition(); // ��� ������ ���� ��� ��ġ �缳��
	void ReScale();
};