#include "pch.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "BackgroundCloudGo.h"
#include "BackgroundBeeGo.h"
#include "TextGo.h"
#include "UIScore.h"
#include "TimebarGo.h"
#include "TreeGo.h"
#include "EffectLog.h"
#include "PlayerGo.h"

SceneGame::SceneGame(SceneIDs id) 
	: Scene(id)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	textureManager.Load(backgroundId);
	textureManager.Load(cloudId);
	textureManager.Load(beeId);
	textureManager.Load(treeId);
	textureManager.Load(branchId);
	textureManager.Load(logId);
	textureManager.Load(playerId);
	textureManager.Load(ripId);
	textureManager.Load(axeId);

	fontManager.Load(fontId);

	SpriteGo* spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource(backgroundId));
	AddGameObject(spriteGoBackground);

	sf::FloatRect cloudMovingBounds({ -200.f, 0 }, { 1920.f + 400, 600.f });
	sf::FloatRect beeMovingBounds({ 0.f, 540.f }, { 1920.f, 1080.f });

	for (int i = 1; i <= 3; ++i) {
		BackgroundCloudGo* backgroundGoCloud = new BackgroundCloudGo("Cloud" + std::to_string(i));
		backgroundGoCloud->SetTexture(*textureManager.GetResource(cloudId));
		backgroundGoCloud->SetOrigin(Origins::MC);
		backgroundGoCloud->SetPosition({ 0.f, 1080.f / 2 });
		backgroundGoCloud->SetBounds(cloudMovingBounds);
		AddGameObject(backgroundGoCloud);
	}

	sf::Vector2f treePos({ 960, 800 });

	tree = new TreeGo("Tree");
	tree->SetPosition(treePos);
	AddGameObject(tree);

	player = new PlayerGo("Player");
	AddGameObject(player);


	BackgroundBeeGo* backgroundGoBee = new BackgroundBeeGo("Bee");
	backgroundGoBee->SetTexture(*textureManager.GetResource(beeId));
	backgroundGoBee->SetOrigin(Origins::MC);
	backgroundGoBee->SetPosition({ 1920.f / 2, 800.f });
	backgroundGoBee->SetBounds(beeMovingBounds);
	AddGameObject(backgroundGoBee);



	// UI
	sf::Vector2f TimebarPos = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	TimebarPos.x *= 0.5f;
	TimebarPos.y *= 0.85f;

	timebar = new TimebarGo("Timebar");
	timebar->SetFillColor(sf::Color::Red);
	timebar->SetPosition(TimebarPos); // GameObject Ŭ���� �Լ� ȣ��� ���� �ʿ�
	timebar->SetOrigin(Origins::MC);

	AddGameObject(timebar);


	uiScore = new UIScore("uiScore");
	uiScore->Set(*fontManager.GetResource(fontId), "uiScore", 40, sf::Color::White);
	uiScore->SetOrigin(Origins::TL);
	uiScore->SetPosition({ 0,0 });
	AddGameObject(uiScore);

	uiIntro = new TextGo("uiIntro");
	uiIntro->Set(*fontManager.GetResource(fontId), "PRESS ENTER TO START!", 75, sf::Color::White);
	uiIntro->SetOrigin(Origins::MC);
	uiIntro->SetPosition({ 1920.f / 2, 1080.f / 2 });
	AddGameObject(uiIntro);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}
}

void SceneGame::Release()
{
	Scene::Release();

	uiScore = nullptr;
	uiIntro = nullptr;
}

void SceneGame::Enter()
{
	Scene::Enter();
	SetStatus(Status::Awake);
}

void SceneGame::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
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
	{
		if (InputManager::GetKeyDown(sf::Keyboard::Escape)) SetStatus(Status::Pause);

		if (InputManager::GetKeyDown(sf::Keyboard::LControl))
		{
			timebar->AddTime(50.f);

			if (timebar->GetCurrentRectSize().x >= timebar->GetRectSize().x)
			{
				timebar->SetRectSize(timebar->GetRectSize());
			}
		}

		if (InputManager::GetKeyDown(sf::Keyboard::Left))
		{
			tree->Chop(Sides::LEFT);
			PlayEffectLog(Sides::LEFT);
			player->UpdatePlayerSide(Sides::LEFT);
			uiScore->AddScore(10.f);
		}

		if (InputManager::GetKeyDown(sf::Keyboard::Right))
		{
			tree->Chop(Sides::RIGHT);
			PlayEffectLog(Sides::RIGHT);
			player->UpdatePlayerSide(Sides::RIGHT);
			uiScore->AddScore(10.f);
		}

		if ((player->GetPlayerSide() == tree->GetFirstBranch()) || (timebar->GetCurrentRectSize().x <= 0))
		{
			player->SetTexture(*TEXTURE_MANAGER.GetResource(ripId));
			player->SetDead();
			SetStatus(Status::GameOver);
		}

		auto it = useEffectList.begin();
		while (it != useEffectList.end())
		{
			auto effectGo = *it;

			if (!effectGo->GetActive())
			{
				RemoveGameObject(effectGo);
				it = useEffectList.erase(it); // �������� ��ġ�� ���� ��ġ�� iterator�� ��ȯ
				unuseEffectList.push_back(effectGo);
			}
			else
			{
				++it;
			}
		}

	}
	break;
	case SceneGame::Status::GameOver:
		if (InputManager::GetKeyDown(sf::Keyboard::Enter))
		{
			SetStatus(Status::Game);
			for (GameObject* obj : gameObjects)
			{
				obj->Reset();
			}
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
		uiIntro->SetText("PRESS ESC TO RESUME!");
		break;
	}
}

void SceneGame::PlayEffectLog(Sides side)
{
	EffectLog* effectLog = nullptr;

	if (unuseEffectList.empty())
	{
		effectLog = new EffectLog();
		effectLog->SetTexture(logId);
		effectLog->SetOrigin(Origins::BC);
		effectLog->Init();
	}
	else
	{
		effectLog = unuseEffectList.front();
		unuseEffectList.pop_front();
	}

	effectLog->SetActive(true);
	effectLog->Reset();
	effectLog->SetPosition({ tree->GetPosition() });

	sf::Vector2f velocity({ 700.f, -300.f });

	if (side == Sides::RIGHT)
	{
		velocity.x *= -1.f;
	}
	effectLog->Fire(velocity);

	useEffectList.push_back(effectLog);
	AddGameObject(effectLog);
}