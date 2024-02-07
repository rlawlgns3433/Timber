#include "pch.h"
#include "TimberScene.h"
#include "GameObjectBackground.h"
#include "GameObjectCloud.h"
#include "GameObjectBee.h"

TimberScene::TimberScene(SceneIDs id) : Scene(id)
{
}

TimberScene::~TimberScene()
{
}

void TimberScene::Init()
{
	ResourceManager<sf::Texture> textureManager;

	GameObjectBackground* backgroundObj = dynamic_cast<GameObjectBackground*>(AddGameObject(new GameObjectBackground("background", "graphics/background.png")));

	GameObjectCloud* cloudObj1 = dynamic_cast<GameObjectCloud*>(AddGameObject(new GameObjectCloud("cloud1", "graphics/cloud.png")));
	GameObjectCloud* cloudObj2 = dynamic_cast<GameObjectCloud*>(AddGameObject(new GameObjectCloud("cloud2")));
	GameObjectCloud* cloudObj3 = dynamic_cast<GameObjectCloud*>(AddGameObject(new GameObjectCloud("cloud3")));

	GameObjectBee* beeObj = dynamic_cast<GameObjectBee*>(AddGameObject(new GameObjectBee("bee", "graphics/bee.png")));

	cloudObj1->GetSprite().setPosition(sf::Vector2f(0, 0));
	cloudObj2->GetSprite().setPosition(sf::Vector2f(0, 200));
	cloudObj3->GetSprite().setPosition(sf::Vector2f(0, 400));

	beeObj->GetSprite().setPosition(sf::Vector2f(0, 800));

	//Utils::SetOrigin(cloudObj->GetSprite(), Origins::TL);

}

void TimberScene::Release()
{
}

void TimberScene::Enter()
{
}

void TimberScene::Exit()
{
}

void TimberScene::Update(float dt)
{
	Scene::Update(dt);
}
