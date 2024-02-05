#include "InputManager.h"
#include <algorithm>

std::list<sf::Keyboard::Key> InputManager::downList; // static ���� �ʱ�ȭ
std::list<sf::Keyboard::Key> InputManager::upList; // ...
std::list<sf::Keyboard::Key> InputManager::ingList; // ...

void InputManager::UpdateEvent(const sf::Event& event)
{
	// �ش� Ű�� ����Ʈ�� ���ٸ� ���� ù ������
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		// ingList�� ���� ��찡 �ʿ��ϴ�.
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

// GET �Լ����� ��� ����ȭ �ʿ� (�����ϸ� hashmap)

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downList.begin(), downList.end(), key) != downList.end(); // Ž��
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(upList.begin(), upList.end(), key) != upList.end(); // Ž��
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return std::find(ingList.begin(), ingList.end(), key) != ingList.end(); // Ž��
}