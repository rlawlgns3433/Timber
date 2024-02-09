#pragma once
#include "Scene.h"
class SceneGame : public Scene
{
protected:

public :
	SceneGame(SceneIDs id);
	virtual ~SceneGame();

	
	// Scene��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};