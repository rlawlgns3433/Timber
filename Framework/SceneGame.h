#pragma once
#include "Scene.h"

class UIScore;
class TextGo;
class TimebarGo;

class SceneGame : public Scene
{
public :
	// Scene�� ����
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:
	SceneGame(const SceneGame&)				 = delete;
	SceneGame(SceneGame&&)					 = delete;
	SceneGame& operator=(const SceneGame&)	 = delete;
	SceneGame& operator=(SceneGame&&)		 = delete;

	UIScore* uiScore;
	TextGo* uiIntro;
	TimebarGo* timebar;
	Status currentStatus = Status::Awake;

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

	void SetStatus(Status newStatus);

};