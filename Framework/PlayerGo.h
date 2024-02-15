#pragma once
#include "SpriteGo.h"
#include "AxeGo.h"

class PlayerGo : public SpriteGo
{
protected:
	PlayerGo(const PlayerGo&) = delete;
	PlayerGo(PlayerGo&&) = delete;
	PlayerGo& operator=(const PlayerGo&) = delete;
	PlayerGo& operator=(PlayerGo&&) = delete;

	Sides playerSide;
	AxeGo axe;

	bool isDead = false;

	float CenterX;
	float playerOffsetX = 200.f;

public:
	PlayerGo(const std::string& name = "");
	virtual ~PlayerGo() = default;


	void Init()							override;
	void Release()						override;
	void Reset()						override;
	void Update(float dt)				override;
	void Draw(sf::RenderWindow& window) override;

	Sides GetPlayerSide() const { return this->playerSide; }
	void UpdatePlayerSide(Sides Sides);
	void SetDead() { this->isDead = true; }
	bool IsDead() const { return this->isDead; }
};