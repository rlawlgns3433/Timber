#pragma once
#include "Scene.h"

class UIScore;
class TextGo;

class SceneGame : public Scene
{
protected:
	UIScore* uiScore;
	TextGo* uiIntro;

public :
	SceneGame(SceneIDs id);
	virtual ~SceneGame();
	
	// Scene을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};