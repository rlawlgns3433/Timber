#include "pch.h"
#include "SceneDev2.h"
#include "TestGameObject.h"
#include "ResourceManager.h"

SceneDev2::SceneDev2(SceneIDs id) : Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
	TestGameObject* obj = new TestGameObject();
	ResourceManager<sf::Font>& resourceManager = ResourceManager<sf::Font>::Instance();
	obj->text.setFont(*resourceManager.GetResource("fonts/KOMIKAP_.ttf"));
	obj->text.setFillColor(sf::Color::White);
	obj->text.setString("SceneDev2");
	gameObjects.push_back(obj);
}

void SceneDev2::Release()
{
}

void SceneDev2::Enter()
{

}

void SceneDev2::Exit()
{
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		SceneManager::Instance().ChangeScene(SceneIDs::SceneDev1);
	}
}
