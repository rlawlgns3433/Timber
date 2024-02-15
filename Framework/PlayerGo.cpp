#include "pch.h"
#include "PlayerGo.h"

PlayerGo::PlayerGo(const std::string& name)
	: SpriteGo(name)
{
}

void PlayerGo::Init()
{
	CenterX = FRAMEWORK.GetWindowSize().x / 2;

	SetOrigin(Origins::BC);
	SetPosition({ CenterX + playerOffsetX, 600 });
	axe.SetPosition({ CenterX + playerOffsetX + 20, 720 });
	axe.SetActive(true);
	axe.SetFlipX(true);

	SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player.png"));
	axe.SetTexture(*TEXTURE_MANAGER.GetResource("graphics/axe.png"));
}

void PlayerGo::Release()
{
}

void PlayerGo::Reset()
{
	isDead = false;
	SetTexture(*TEXTURE_MANAGER.GetResource("graphics/player.png"));
	SetPosition({ CenterX + playerOffsetX, 600 });
	axe.SetPosition({ CenterX + playerOffsetX + 20, 720 });
	axe.SetFlipX(true);
	axe.SetActive(true);
	SetFlipX(false);
}

void PlayerGo::Update(float dt)
{
	if (playerSide == Sides::LEFT)
	{
		SetPosition({ CenterX - playerOffsetX, 600 });
		axe.SetPosition({ CenterX - playerOffsetX - 20, 720 });
		axe.SetFlipX(false);
		axe.SetSide(Sides::LEFT);
		SetFlipX(true);
	}
	else if (playerSide == Sides::RIGHT)
	{
		SetPosition({ CenterX + playerOffsetX, 600 });
		axe.SetPosition({ CenterX + playerOffsetX + 20, 720 });
		axe.SetFlipX(true);
		axe.SetSide(Sides::RIGHT);
		SetFlipX(false);
	}

	if (isDead)
	{
		axe.SetActive(false);
	}
}

void PlayerGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (axe.GetActive())
	{
		axe.Draw(window);
	}
}

void PlayerGo::UpdatePlayerSide(Sides side)
{
	playerSide = side;

}