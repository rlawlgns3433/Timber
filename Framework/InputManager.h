#pragma once
#include <SFML/Graphics.hpp>
#include <list>

// Ű���� �Է»� �ƴ϶� ���콺 �Է±��� �߰� �ʿ�

class InputManager
{
private : 
	static std::list<sf::Keyboard::Key> downList; // �̹� �����ӿ� down�� Ű���� ��Ƶδ� ����Ʈ, ���� Ű�� ����Ʈ�� ��� ��Ƽ� ó��
	static std::list<sf::Keyboard::Key> upList; // ...
	static std::list<sf::Keyboard::Key> ingList; // ...

	// �� ������ ������ keydown, keyup�� ������ �Ǿ�� �Ѵ�. �ϳ��� ������ ��������!
public :
	static void UpdateEvent(const sf::Event& event);
	static void Clear();
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

};