#include "InputManager.h"
#include <algorithm>

std::list<sf::Keyboard::Key> InputManager::downList; // static 변수 초기화
std::list<sf::Keyboard::Key> InputManager::upList; // ...
std::list<sf::Keyboard::Key> InputManager::ingList; // ...

void InputManager::UpdateEvent(const sf::Event& event)
{
	// 해당 키가 리스트에 없다면 눌린 첫 프레임
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		// ingList에 없는 경우가 필요하다.
		if (!GetKey(event.key.code))
		{
			ingList.push_back(event.key.code);
			downList.push_back(event.key.code);
		}
		break;

	case sf::Event::KeyReleased:
		ingList.remove(event.key.code);
		upList.push_back(event.key.code);
		break;

	default:
		break;
	}
}

void InputManager::Clear()
{
	downList.clear();
	upList.clear();
}

// GET 함수들을 모두 최적화 필요 (가능하면 hashmap)

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downList.begin(), downList.end(), key) != downList.end(); // 탐색
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(upList.begin(), upList.end(), key) != upList.end(); // 탐색
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return std::find(ingList.begin(), ingList.end(), key) != ingList.end(); // 탐색
}