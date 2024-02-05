#pragma once
#include <SFML/Graphics.hpp>
#include <list>

// 키보드 입력뿐 아니라 마우스 입력까지 추가 필요

class InputManager
{
private : 
	static std::list<sf::Keyboard::Key> downList; // 이번 프레임에 down인 키들을 담아두는 리스트, 눌린 키를 리스트에 모두 담아서 처리
	static std::list<sf::Keyboard::Key> upList; // ...
	static std::list<sf::Keyboard::Key> ingList; // ...

	// 한 프레임 내에서 keydown, keyup이 보장이 되어야 한다. 하나의 프레임 내에서만!
public :
	static void UpdateEvent(const sf::Event& event);
	static void Clear();
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

};