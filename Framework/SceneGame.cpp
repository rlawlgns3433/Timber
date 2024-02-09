#include "pch.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "BackgroundMovingGo.h"
#include "BackgroundBeeGo.h"

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

	SpriteGo* spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture(*textureManager.GetResource("graphics/background.png"));

	sf::FloatRect movingBounds({ -200.f, 0 }, { 1920.f + 400, 600.f });

	BackgroundMovingGo* backgoundGoCloud1 = new BackgroundMovingGo("Cloud1");
	backgoundGoCloud1->SetTexture(*textureManager.GetResource("graphics/cloud.png"));
	backgoundGoCloud1->SetOrigin(Origins::MC);
	backgoundGoCloud1->SetPosition({ 0.f, 1080.f / 2});
	backgoundGoCloud1->bounds = movingBounds;
	BackgroundMovingGo* backgoundGoCloud2 = new BackgroundMovingGo("Cloud2");
	backgoundGoCloud2->SetTexture(*textureManager.GetResource("graphics/cloud.png"));
	backgoundGoCloud2->SetOrigin(Origins::MC);
	backgoundGoCloud2->SetPosition({ 0.f, 1080.f / 2 });
	backgoundGoCloud2->bounds = movingBounds;
	BackgroundMovingGo* backgoundGoCloud3 = new BackgroundMovingGo("Cloud3");
	backgoundGoCloud3->SetTexture(*textureManager.GetResource("graphics/cloud.png"));
	backgoundGoCloud3->SetOrigin(Origins::MC);
	backgoundGoCloud3->SetPosition({ 0.f, 1080.f / 2 });
	backgoundGoCloud3->bounds = movingBounds;
	BackgroundBeeGo* backgroundGoBee = new BackgroundBeeGo("Bee");
	backgroundGoBee->SetTexture(*textureManager.GetResource("graphics/bee.png"));
	backgroundGoBee->SetOrigin(Origins::MC);
	backgroundGoBee->SetPosition({ 1920.f / 2, 800.f });
	backgroundGoBee->bounds = movingBounds;


	AddGameObject(spriteGoBackground);
	AddGameObject(backgoundGoCloud1);
	AddGameObject(backgoundGoCloud2);
	AddGameObject(backgoundGoCloud3);
	AddGameObject(backgroundGoBee);

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
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
