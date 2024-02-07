#pragma once
class TimberScene : public Scene
{
protected :
	ResourceManager<sf::Sprite> spriteManager;
	ResourceManager<sf::Font> fontManager;

public :
	TimberScene(SceneIDs id);
	virtual ~TimberScene();

	TimberScene(const TimberScene&) = delete;
	TimberScene(TimberScene&&) = delete;
	TimberScene& operator=(const TimberScene&) = delete;
	TimberScene& operator=(TimberScene&&) = delete;


	// Scene을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;

};

