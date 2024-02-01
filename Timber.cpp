#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

sf::Vector2f& RandomRotation(sf::Vector2f& v)
{
	sf::Transform rotation;
	float zeroToOne = (float)rand() / RAND_MAX; // 0.0 ~ 1.0
	float angle = zeroToOne * 360.f; // 0.0 ~ 360.0
	rotation.rotate(angle);

	return v;
}


int main()
{
	srand(time(NULL));

	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "SFML works!", sf::Style::Default); // 타이틀을 제외한 초기 사이즈, 타이틀

	// 이미지를 담는다.
	sf::Texture textureBackground;
	sf::Texture textureCloud;
	sf::Texture textureBee;
	sf::Texture textureTree;

	// 이미지를 통해 실제로 그릴 객체
	sf::Sprite spriteBackground;
	sf::Sprite spriteCloud1;
	sf::Sprite spriteCloud2;
	sf::Sprite spriteCloud3;
	sf::Sprite spriteBee;
	sf::Sprite spriteTree;

	textureBackground.loadFromFile("graphics/background.png");
	textureCloud.loadFromFile("graphics/cloud.png");
	textureBee.loadFromFile("graphics/bee.png");
	textureTree.loadFromFile("graphics/Tree.png");

	spriteBackground.setTexture(textureBackground); // 텍스쳐 적용하기
	spriteBackground.setPosition(0, 0); // 그릴 위치를 정하기

	spriteCloud1.setTexture(textureCloud); // 텍스쳐 적용하기
	spriteCloud1.setPosition(vm.width / 2 - 200, 0); // 그릴 위치를 정하기
	spriteCloud2.setTexture(textureCloud); // 텍스쳐 적용하기
	spriteCloud2.setPosition(vm.width / 2, 50); // 그릴 위치를 정하기
	spriteCloud3.setTexture(textureCloud); // 텍스쳐 적용하기
	spriteCloud3.setPosition(vm.width / 2 + 200, 100); // 그릴 위치를 정하기

	spriteBee.setTexture(textureBee); // 텍스쳐 적용하기
	spriteBee.setPosition(0, 800); // 그릴 위치를 정하기

	spriteTree.setTexture(textureTree); // 텍스쳐 적용하기
	spriteTree.setPosition(vm.width * 0.5f, 0); // 그릴 위치를 정하기
	spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0);

	// 보통 속력, 방향을 나눠서 계산한다.
	float beeSpeed = 100.f; // 속력
	sf::Vector2f beeDirection(1.f, 0.f); // x축 단위 벡터 -> 방향

	float cloudSpeed1 = (rand() % 200 + 100); // 100 ~ 300
	float cloudSpeed2 = (rand() % 200 + 100); // 100 ~ 300
	float cloudSpeed3 = (rand() % 200 + 100); // 100 ~ 300
	
	sf::Vector2f cloudDirection1(-1.f, 0.f); // x축 단위 벡터 -> 방향
	sf::Vector2f cloudDirection2(-1.f, 0.f); // x축 단위 벡터 -> 방향
	sf::Vector2f cloudDirection3(-1.f, 0.f); // x축 단위 벡터 -> 방향

	float span1 = 1.f;
	float span2 = 5.f;
	float deltaTime1 = 0.f;
	float deltaTime2 = 0.f;
	sf::Clock clock;

	/////////////////////
	//////main loop//////
	/////////////////////
	while (window.isOpen())
	{
		// 이동을 위한 시간 체크
		sf::Time dt = clock.restart();
		float deltaTime = dt.asSeconds();
		deltaTime1 = deltaTime1 + dt.asSeconds();
		deltaTime2 = deltaTime2 + dt.asSeconds();
		sf::Event event; // 이벤트 : 어플리케이션이 os로부터 넘겨 받는 것

		// 이벤트는 Message Queue에 쌓이게 된다. 
		while (window.pollEvent(event)) // message loop
		{
			// Message Queue가 있는 동안 루프 실행
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
#pragma region Handle User Input
		/////////////////////
		// Handle User Input/
		/////////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // ESC가 눌렸을 때 동작
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Left가 눌렸을 때 동작
		{
			beeDirection = sf::Vector2f(-1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right가 눌렸을 때 동작
		{
			beeDirection = sf::Vector2f(1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Right가 눌렸을 때 동작
		{
			beeSpeed += 1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Right가 눌렸을 때 동작
		{
			beeSpeed -= 1.f;
		}

		if (span1 <= deltaTime1)
		{
			beeSpeed *= -1;
			deltaTime1 = 0;
		}

#pragma endregion


#pragma region Update
		/////////////////////
		///////Update//////// 시간을 이용해 이동량을 조정
		/////////////////////
		sf::Vector2f beePos = spriteBee.getPosition();
		beePos += beeDirection * beeSpeed * deltaTime; // (변위)d = vt 
		spriteBee.setPosition(beePos);

		sf::Vector2f cloudPos1 = spriteCloud1.getPosition();
		sf::Vector2f cloudPos2 = spriteCloud2.getPosition();
		sf::Vector2f cloudPos3 = spriteCloud3.getPosition();
		cloudPos1 += cloudDirection1 * cloudSpeed1 * deltaTime;
		cloudPos2 += cloudDirection2 * cloudSpeed2 * deltaTime;
		cloudPos3 += cloudDirection3 * cloudSpeed3 * deltaTime;

		if (cloudPos1.x < 0) cloudPos1.x += 1920;
		if (cloudPos2.x < 0) cloudPos2.x += 1920;
		if (cloudPos3.x < 0) cloudPos3.x += 1920;

		spriteCloud1.setPosition(cloudPos1); // 그릴 위치를 정하기
		spriteCloud2.setPosition(cloudPos2); // 그릴 위치를 정하기
		spriteCloud3.setPosition(cloudPos3); // 그릴 위치를 정하기


#pragma endregion


#pragma region Draw
		/////////////////////
		////////Draw/////////
		/////////////////////
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);


#pragma endregion

		window.display();
	}

	return 0;

}