#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "Framework/Utils.h"

sf::Vector2f& RandomRotation(sf::Vector2f& v)
{
	sf::Transform rotation;
	float zeroToOne = (float)rand() / RAND_MAX; // 0.0 ~ 1.0
	float angle = zeroToOne * 360.f; // 0.0 ~ 360.0
	rotation.rotate(angle);

	return v;
}

// Framework 추가
float GetRandomAngle()
{
	return (float)rand() / RAND_MAX * 360.f;
}		   

// Framework 추가
float GetRandomSpeed()
{
	return (float)rand() / RAND_MAX * 100 + 200;
}


void ResetCloudInfo(sf::Sprite& const spriteCloud, sf::Texture& cloudTexture, sf::Vector2f& cloudPos, float& cloudSpeed)
{
	cloudPos.x = rand() % 1920;// 다시 나타나는 위치
	cloudSpeed = rand() % 2 ? (rand() % 201) + 100 : (rand() % 201) - 300;
	spriteCloud.setScale(Utils::GetRandomVector2(0.7f, 1.f)); // 크기
}



int main()
{
	srand(time(NULL));

	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Timber", sf::Style::Default); // 타이틀을 제외한 초기 사이즈, 타이틀

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

	// 폰트
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// 텍스트
	sf::Text textMessage;
	sf::Text textScore;
	sf::Text textGameover;

	// 도형
	sf::RectangleShape timeBar;
	sf::Vector2f timeBarSize = sf::Vector2f(400.f, 80.f);
	sf::Vector2f timeBarCurrentSize = timeBarSize;
	timeBar.setSize((timeBarSize));
	timeBar.setFillColor(sf::Color::Red);
	Utils::SetOrigin(timeBar, Origins::MC);
	timeBar.setPosition(vm.width / 2, vm.height - 90);

	float timeBarDuration = 5.f; // N초만에 timeBar가 줄어든다.
	float timeBarSpeed = -timeBarSize.x / timeBarDuration; // timeBar가 감소하기 때문에 음수

	textMessage.setFont(font);
	textMessage.setString("Press Enter to Start!");
	textMessage.setCharacterSize(75);
	textMessage.setFillColor(sf::Color::White);
	textMessage.setPosition(vm.width / 2, vm.height / 2);
	Utils::SetOrigin(textMessage, Origins::MC);

	textScore.setFont(font);
	textScore.setString("Score : 0");
	textScore.setCharacterSize(100);
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(10, 10);
	Utils::SetOrigin(textScore, Origins::TL);

	textGameover.setFont(font);
	textGameover.setString("Gameover!");
	textGameover.setCharacterSize(75);
	textGameover.setFillColor(sf::Color::White);
	textGameover.setPosition(vm.width / 2, vm.height / 2);
	Utils::SetOrigin(textGameover, Origins::MC);


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
	Utils::SetOrigin(spriteCloud1, Origins::TR); // 중앙으로 Origin 변경
	Utils::SetOrigin(spriteCloud2, Origins::TR); // 중앙으로 Origin 변경
	Utils::SetOrigin(spriteCloud3, Origins::TR); // 중앙으로 Origin 변경



	spriteBee.setTexture(textureBee); // 텍스쳐 적용하기
	spriteBee.setPosition(vm.width / 2 - 100, 650); // 그릴 위치를 정하기
	spriteBee.setOrigin(textureBee.getSize().x / 2, textureBee.getSize().y / 2);
	const sf::FloatRect& boundsBee = spriteBee.getLocalBounds(); // 로컬 좌표 좌상단이 (0,0)인 사각형, Origin 구할 때 사용
	Utils::SetOrigin(spriteBee, Origins::MC); // 중앙으로 Origin 변경
	

	//spriteBee.getGlobalBounds(); // 월드 좌표 좌상단이 (0,0)인 사각형


	spriteTree.setTexture(textureTree); // 텍스쳐 적용하기
	spriteTree.setPosition(vm.width * 0.5f, 0); // 그릴 위치를 정하기
	spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0);

	// 보통 속력, 방향을 나눠서 계산한다.
	float beeSpeed = 200.f; // 속력
	sf::Vector2f beeDirection(1.f, 0.f); // x축 단위 벡터 -> 방향
	spriteBee.setScale(-1.f, 1.f);

	float cloudSpeed2 = GetRandomSpeed();// (rand() % 200 + 100); 100 ~ 300
	float cloudSpeed1 = GetRandomSpeed();// (rand() % 200 + 100); 100 ~ 300
	float cloudSpeed3 = GetRandomSpeed();// (rand() % 200 + 100); 100 ~ 300

	sf::Vector2f cloudDirection1(-1.f, 0.f); // x축 단위 벡터 -> 방향
	sf::Vector2f cloudDirection2(-1.f, 0.f); // x축 단위 벡터 -> 방향
	sf::Vector2f cloudDirection3(-1.f, 0.f); // x축 단위 벡터 -> 방향

	unsigned long long score = 0;
	float span2 = 5.f;
	float time = 0.f;
	float deltaTime = 0.f;

	float realTime = 0.f;
	float realDeltaTime = 0.f;

	bool isPause = false;
	bool isGameover = false;

	float timeScale = isPause ? 0.f : 1.f;
	float beeLastTime = 0.f;
	float beeDirChangeDuration = 1.f;
	float beeChangeTime = beeDirChangeDuration;

	sf::Clock clock;
	///////////////////////////////////////////////////////////////
	///////////////////////////main loop///////////////////////////
	///////////////////////////////////////////////////////////////
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		realDeltaTime = dt.asSeconds();
		realTime += deltaTime;

		deltaTime = realDeltaTime * timeScale;
		time += deltaTime;

		sf::Event event; // 이벤트 : 어플리케이션이 os로부터 넘겨 받는 것

		// 이벤트는 Message Queue에 쌓이게 된다. 
		while (window.pollEvent(event)) // message loop
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased: // 키 입력
				if (event.key.code == sf::Keyboard::LControl && !isPause && !isGameover)
				{
					score += 10;
					textScore.setString("Score : " + std::to_string(score));
					break;
				}

				else if (event.key.code == sf::Keyboard::A && !isPause && !isGameover)
				{
					// 시간이 0이면 게임오버 메시지 & Pause
					// timebar 시간 추가(A 키), 최소 시간(음수 불가) 문제 해결
					if (timeBarCurrentSize.x - timeBarSpeed <= timeBarSize.x)
					{
						timeBarCurrentSize.x += -timeBarSpeed;
					}
					break;
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					if (isPause) break; // pause일 떄 return 하면 아무 것도 실행되지 않음
					if (isGameover)
					{
						timeScale = 1.f;
						isGameover = false;
						score = 0;
						timeBarCurrentSize = timeBarSize;
					}
					break;
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					if (!isGameover)
					{
						isPause = !isPause;
						timeScale = isPause ? 0.f : 1.f;
					}
					break;
				}
			}

			// Message Queue가 있는 동안 루프 실행
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
#pragma region Handle User Input
		///////////////////////////////////////////////////////////////
		/////////////////////// Handle User Input//////////////////////
		///////////////////////////////////////////////////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // ESC가 눌렸을 때 동작
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Left가 눌렸을 때 동작
		{
			beeDirection = sf::Vector2f(-1.0f, 0.0f);
			spriteBee.setScale(1.f, 1.f);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right가 눌렸을 때 동작
		{
			beeDirection = sf::Vector2f(1.0f, 0.0f);
			spriteBee.setScale(-1.f, 1.f);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Right가 눌렸을 때 동작
		{
			beeSpeed += 1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Right가 눌렸을 때 동작
		{
			if (beeSpeed > 2)
			{
				beeSpeed -= 1.f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) && !isPause)
		{
			timeScale = 0.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !isPause)
		{
			timeScale = 1.f;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !isPause)
		{
			timeScale = 2.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !isPause)
		{
			timeScale = 3.f;
		}

#pragma endregion


#pragma region Update
		///////////////////////////////////////////////////////////////
		////////////////////////////Update///////////////////////////// 시간을 이용해 이동량을 조정
		///////////////////////////////////////////////////////////////
		sf::Transform rotation;

		if (time > beeChangeTime)
		{
			//float zeroToOne = (float)rand() / RAND_MAX; // 0.0 ~ 1.0
			//float angle = zeroToOne * 360.f; // 0.0 ~ 360.0			
			rotation.rotate(GetRandomAngle());
			beeDirection = rotation * beeDirection;

			if (beeDirection.x > 0.f)
			{
				spriteBee.setScale(-1.f, 1.f);
			}
			else if (beeDirection.x < 0.f)
			{
				spriteBee.setScale(1.f, 1.f);
			}
			beeChangeTime = time + beeDirChangeDuration;
		}


		timeBar.setSize(timeBarCurrentSize);
		timeBarCurrentSize.x += timeBarSpeed * deltaTime;
		if (timeBarCurrentSize.x <= 0)
		{
			isGameover = true;
		}

		sf::Vector2f beePos = spriteBee.getPosition();
		beePos += beeDirection * beeSpeed * deltaTime; // (변위)d = vt 
		while (beePos.x < 0 || beePos.x > 1920 || beePos.y < vm.height * 0.3 || beePos.y > vm.height * 0.9)
		{
			rotation.rotate(GetRandomAngle());
			beeDirection = rotation * beeDirection;
			beePos += beeDirection * beeSpeed * deltaTime; // (변위)d = vt 
		}
		spriteBee.setPosition(beePos);

		sf::Vector2f cloudPos1 = spriteCloud1.getPosition();
		sf::Vector2f cloudPos2 = spriteCloud2.getPosition();
		sf::Vector2f cloudPos3 = spriteCloud3.getPosition();
		cloudPos1 += cloudDirection1 * cloudSpeed1 * deltaTime;
		cloudPos2 += cloudDirection2 * cloudSpeed2 * deltaTime;
		cloudPos3 += cloudDirection3 * cloudSpeed3 * deltaTime;


		if (cloudPos1.x < 0 || cloudPos1.x > vm.width + textureCloud.getSize().x)
		{
			ResetCloudInfo(spriteCloud1, textureCloud, cloudPos1, cloudSpeed1);

		}
		if (cloudPos2.x < 0 || cloudPos2.x > vm.width + textureCloud.getSize().x)
		{
			ResetCloudInfo(spriteCloud2, textureCloud, cloudPos2, cloudSpeed2);
		}
		if (cloudPos3.x < 0 || cloudPos3.x > vm.width + textureCloud.getSize().x)
		{
			ResetCloudInfo(spriteCloud3, textureCloud, cloudPos3, cloudSpeed3);
		}
		spriteCloud1.setPosition(cloudPos1); // 그릴 위치를 정하기
		spriteCloud2.setPosition(cloudPos2); // 그릴 위치를 정하기
		spriteCloud3.setPosition(cloudPos3); // 그릴 위치를 정하기


#pragma endregion


#pragma region Draw
		///////////////////////////////////////////////////////////////
		/////////////////////////////Draw//////////////////////////////
		///////////////////////////////////////////////////////////////
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);
		window.draw(textScore);

		if (isPause)
		{
			window.draw(textMessage);
		}
		window.draw(timeBar);

		if (isGameover)
		{
			timeScale = 0.f;
			window.draw(textGameover);
		}
#pragma endregion

		window.display();
	}

	return 0;

}