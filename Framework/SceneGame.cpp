#include "pch.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "BackgroundCloudGo.h"
#include "BackgroundBeeGo.h"
#include "BackgroundCloudGo.h"
#include "TextGo.h"
#include "UIScore.h"
#include "TimebarGo.h"

SceneGame::SceneGame(SceneIDs id) 
	: Scene(id)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	textureManager.Load("graphics/background.png");
	textureManager.Load("graphics/cloud.png");
	textureManager.Load("graphics/bee.png");

	fontManager.Load("fonts/KOMIKAP_.ttf");

	SpriteGo* spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource("graphics/background.png"));

	sf::FloatRect cloudMovingBounds({ -200.f, 0 }, { 1920.f + 400, 600.f });
	sf::FloatRect beeMovingBounds({ 0.f, 540.f }, { 1920.f, 1080.f });

	BackgroundCloudGo* backgoundGoCloud1 = new BackgroundCloudGo("Cloud2");
	backgoundGoCloud1->SetTexture(*textureManager.GetResource("graphics/cloud.png"));
	backgoundGoCloud1->SetOrigin(Origins::MC);
	backgoundGoCloud1->SetPosition({ 0.f, 1080.f / 2});
	backgoundGoCloud1->SetBounds(cloudMovingBounds);
	BackgroundCloudGo* backgoundGoCloud2 = new BackgroundCloudGo("Cloud2");
	backgoundGoCloud2->SetTexture(*textureManager.GetResource("graphics/cloud.png"));
	backgoundGoCloud2->SetOrigin(Origins::MC);
	backgoundGoCloud2->SetPosition({ 0.f, 1080.f / 2 });
	backgoundGoCloud2->SetBounds(cloudMovingBounds);
	BackgroundCloudGo* backgoundGoCloud3 = new BackgroundCloudGo("Cloud3");
	backgoundGoCloud3->SetTexture(*textureManager.GetResource("graphics/cloud.png"));
	backgoundGoCloud3->SetOrigin(Origins::MC);
	backgoundGoCloud3->SetPosition({ 0.f, 1080.f / 2 });
	backgoundGoCloud3->SetBounds(cloudMovingBounds);

	BackgroundBeeGo* backgroundGoBee = new BackgroundBeeGo("Bee");
	backgroundGoBee->SetTexture(*textureManager.GetResource("graphics/bee.png"));
	backgroundGoBee->SetOrigin(Origins::MC);
	backgroundGoBee->SetPosition({ 1920.f / 2, 800.f });
	backgroundGoBee->SetBounds(beeMovingBounds);

	
	AddGameObject(spriteGoBackground);
	AddGameObject(backgoundGoCloud1);
	AddGameObject(backgoundGoCloud2);
	AddGameObject(backgoundGoCloud3);
	AddGameObject(backgroundGoBee);

	sf::Vector2f TimebarPos = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	TimebarPos.x *= 0.5f;
	TimebarPos.y *= 0.85f;


	// UI
	timebar = new TimebarGo("Timebar");
	timebar->SetFillColor(sf::Color::Red);
	timebar->SetPosition(TimebarPos); // GameObject 클래스 함수 호출로 변경 필요
	timebar->SetOrigin(Origins::MC);

	AddGameObject(timebar);


	uiScore = new UIScore("uiScore");
	uiScore->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "uiScore", 40, sf::Color::White);
	uiScore->SetOrigin(Origins::TL);
	uiScore->SetPosition({ 0,0 });
	AddGameObject(uiScore);

	uiIntro = new TextGo("uiIntro");
	uiIntro->Set(*fontManager.GetResource("fonts/KOMIKAP_.ttf"), "PRESS ENTER TO START!", 75, sf::Color::White);
	uiIntro->SetOrigin(Origins::MC);
	uiIntro->SetPosition({ 1920.f / 2, 1080.f / 2 });
	AddGameObject(uiIntro);
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();
}

void SceneGame::Exit()
{
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		if (InputManager::GetKeyDown(sf::Keyboard::Enter)) SetStatus(Status::Game);

		break;
	case SceneGame::Status::Game:
		if (InputManager::GetKeyDown(sf::Keyboard::Escape)) SetStatus(Status::Pause);

		// timebar가 없어진다면 종료
		if (timebar->GetCurrentRectSize().x <= 0) SetStatus(Status::GameOver);

		if (InputManager::GetKeyDown(sf::Keyboard::LControl))
		{
			timebar->SetRectSize({ timebar->GetCurrentRectSize().x + 50.f, timebar->GetCurrentRectSize().y });


			// 수정 필요
			if (timebar->GetCurrentRectSize().x >= timebar->GetRectSize().x)
			{
				timebar->SetRectSize(timebar->GetRectSize());
			}
		}

		break;
	case SceneGame::Status::GameOver:
		if (InputManager::GetKeyDown(sf::Keyboard::Enter))
		{
			SetStatus(Status::Game);
			timebar->Reset();
		}
		break;
	case SceneGame::Status::Pause:
		if (InputManager::GetKeyDown(sf::Keyboard::Escape)) SetStatus(Status::Game);

		break;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;

	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ENTER TO START!");
		break;
	case SceneGame::Status::Game:
		FRAMEWORK.SetTimeScale(1.f);
		uiIntro->SetActive(false);
		break;
	case SceneGame::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("GAME OVER ^.^");
		break;
	case SceneGame::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		uiIntro->SetActive(true);
		uiIntro->SetText("PRESS ENTER TO RESUME!");
		break;
	}
}