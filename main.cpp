#include "pch.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cmath>

sf::Vector2f& RandomRotation(sf::Vector2f& v);
float GetRandomAngle();
float GetRandomSpeed();
void ResetCloudInfo(sf::Sprite& const spriteCloud, sf::Texture& cloudTexture, sf::Vector2f& cloudPos, float& cloudSpeed);
void UpdateBranches();
void InitGame();

const int NUM_OF_BRANCHES = 6;
unsigned long long score = 0;
sf::Sprite spriteBranches[NUM_OF_BRANCHES];
Sides branchSides[NUM_OF_BRANCHES];
Sides playerSide;

sf::RectangleShape timeBar;
sf::Vector2f timeBarSize = sf::Vector2f(400.f, 80.f);
sf::Vector2f timeBarCurrentSize = timeBarSize;

int main()
{
	srand(time(NULL));

	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Timber", sf::Style::Default); // 타이틀을 제외한 초기 사이즈, 타이틀

	ResourceManager<sf::Texture> textureManager;
	ResourceManager<sf::Font> fontManager;

	// 이미지를 담는다.
	sf::Texture textureBackground;
	sf::Texture textureCloud;
	sf::Texture textureBee;
	sf::Texture textureTree;
	sf::Texture textureBranch;
	sf::Texture texturePlayer;
	sf::Texture textureAxe;

	// 이미지를 통해 실제로 그릴 객체
	sf::Sprite spriteBackground;
	sf::Sprite spriteCloud1;
	sf::Sprite spriteCloud2;
	sf::Sprite spriteCloud3;
	sf::Sprite spriteBee;
	sf::Sprite spriteTree;
	sf::Sprite spritePlayer;
	sf::Sprite spriteAxe;

	// 폰트
	sf::Font font;

	// 텍스트
	sf::Text textMessage;
	sf::Text textScore;
	sf::Text textGameover;

	// 도형

	timeBar.setSize((timeBarSize));
	timeBar.setFillColor(sf::Color::Red);
	Utils::SetOrigin(timeBar, Origins::MC);
	timeBar.setPosition(vm.width / 2, vm.height - 90);

	float timeBarDuration = 10.f; // N초만에 timeBar가 줄어든다.
	float timeBarSpeed = -timeBarSize.x / timeBarDuration; // timeBar가 감소하기 때문에 음수

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

	std::string textureBackgroundName = "graphics/background.png";
	std::string textureCloudName = "graphics/cloud.png";
	std::string textureBeeName = "graphics/bee.png";
	std::string textureTreeName = "graphics/tree.png";
	std::string textureBranchName = "graphics/branch.png";
	std::string texturePlayerName = "graphics/player.png";
	std::string textureAxeName = "graphics/axe.png";
	std::string fontName = "fonts/KOMIKAP_.ttf";

	textureManager.Instance().Load(textureBackgroundName);
	textureManager.Instance().Load(textureCloudName);
	textureManager.Instance().Load(textureBeeName);
	textureManager.Instance().Load(textureTreeName);
	textureManager.Instance().Load(textureBranchName);
	textureManager.Instance().Load(texturePlayerName);
	textureManager.Instance().Load(textureAxeName);
	fontManager.Instance().Load(fontName);


	float span2 = 5.f;
	float time = 0.f;
	float deltaTime = 0.f;

	float realTime = 0.f;
	float realDeltaTime = 0.f;

	bool isPause = true;
	bool isGameover = false;

	float timeScale = isPause ? 0.f : 1.f;
	float beeLastTime = 0.f;
	float beeDirChangeDuration = 1.f;
	float beeChangeTime = beeDirChangeDuration;

	sf::Clock clock;

	textMessage.setFont(*fontManager.Instance().GetResource(fontName));
	textMessage.setString("Press Enter to Start!");
	textMessage.setCharacterSize(75);
	textMessage.setFillColor(sf::Color::White);
	textMessage.setPosition(vm.width / 2, vm.height / 2);
	Utils::SetOrigin(textMessage, Origins::MC);

	textScore.setFont(*fontManager.Instance().GetResource(fontName));
	textScore.setString("Score : 0");
	textScore.setCharacterSize(100);
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(10, 10);
	Utils::SetOrigin(textScore, Origins::TL);

	textGameover.setFont(*fontManager.Instance().GetResource(fontName));
	textGameover.setString("Game Over. Press Enter to Restart!");
	textGameover.setCharacterSize(75);
	textGameover.setFillColor(sf::Color::White);
	textGameover.setPosition(vm.width / 2, vm.height / 2);
	Utils::SetOrigin(textGameover, Origins::MC);


	//textureBackground.loadFromFile("graphics/background.png");
	//textureCloud.loadFromFile("graphics/cloud.png");
	//textureBee.loadFromFile("graphics/bee.png");
	//textureTree.loadFromFile("graphics/Tree.png");
	//textureBranch.loadFromFile("graphics/branch.png");
	//texturePlayer.loadFromFile("graphics/player.png");
	//textureAxe.loadFromFile("graphics/axe.png");


	spriteBackground.setTexture(*textureManager.Instance().GetResource(textureBackgroundName)); // 텍스쳐 적용하기
	spriteBackground.setPosition(0, 0); // 그릴 위치를 정하기

	spriteCloud1.setTexture(*textureManager.Instance().GetResource(textureCloudName)); // 텍스쳐 적용하기
	spriteCloud1.setPosition(vm.width / 2 - 200, 0); // 그릴 위치를 정하기
	spriteCloud2.setTexture(*textureManager.Instance().GetResource(textureCloudName)); // 텍스쳐 적용하기
	spriteCloud2.setPosition(vm.width / 2, 50); // 그릴 위치를 정하기
	spriteCloud3.setTexture(*textureManager.Instance().GetResource(textureCloudName)); // 텍스쳐 적용하기
	spriteCloud3.setPosition(vm.width / 2 + 200, 100); // 그릴 위치를 정하기
	Utils::SetOrigin(spriteCloud1, Origins::TR); // 중앙으로 Origin 변경
	Utils::SetOrigin(spriteCloud2, Origins::TR); // 중앙으로 Origin 변경
	Utils::SetOrigin(spriteCloud3, Origins::TR); // 중앙으로 Origin 변경



	spriteBee.setTexture(*textureManager.Instance().GetResource(textureBeeName)); // 텍스쳐 적용하기
	spriteBee.setPosition(vm.width / 2 - 100, 650); // 그릴 위치를 정하기
	spriteBee.setOrigin(textureBee.getSize().x / 2, textureBee.getSize().y / 2);
	const sf::FloatRect& boundsBee = spriteBee.getLocalBounds(); // 로컬 좌표 좌상단이 (0,0)인 사각형, Origin 구할 때 사용
	Utils::SetOrigin(spriteBee, Origins::MC); // 중앙으로 Origin 변경
	

	//spriteBee.getGlobalBounds(); // 월드 좌표 좌상단이 (0,0)인 사각형

	spriteTree.setTexture(*textureManager.Instance().GetResource(textureTreeName)); // 텍스쳐 적용하기
	spriteTree.setPosition(vm.width * 0.5f, 0); // 그릴 위치를 정하기
	spriteTree.setOrigin((textureManager).Instance().GetResource(textureTreeName)->getSize().x * 0.5f, 0);


	for (int i = 0; i < NUM_OF_BRANCHES; ++i)
	{
		spriteBranches[i].setTexture(*textureManager.Instance().GetResource(textureBranchName));
		spriteBranches[i].setPosition(-2000, -2000);
		Utils::SetOrigin(spriteBranches[i], Origins::ML);
	}

	for (int i = 0; i < NUM_OF_BRANCHES; ++i)
	{
		branchSides[i] = (Sides)(rand() % 3);
	}


	InitGame();



	sf::Vector2f playerPos[2] = 
	{ 
		{
		vm.width * 0.5f - 300,
		spriteTree.getLocalBounds().height
		},
		{
		vm.width * 0.5f + 300,
		spriteTree.getLocalBounds().height
		}
	};
	
	sf::Vector2f axePos[2] =
	{
		{
		vm.width * 0.5f - 100,
		spriteTree.getLocalBounds().height - 90
		},
		{
		vm.width * 0.5f + 100,
		spriteTree.getLocalBounds().height - 90
		}
	};

	sf::Vector2f playerScale[2] =
	{
		{-1.f, 1.f},
		{1.f, 1.f}
	};

	Sides playerSides = Sides::RIGHT;

	spritePlayer.setTexture(*textureManager.Instance().GetResource(texturePlayerName));
	Utils::SetOrigin(spritePlayer, Origins::BC);
	spritePlayer.setPosition(playerPos[(int)playerSides]);


	spriteAxe.setTexture(*textureManager.Instance().GetResource(textureAxeName));
	spriteAxe.setScale(playerScale[(int)playerSides]);
	spriteAxe.setPosition(axePos[(int)playerSides]);


	///////////////////////////////////////////////////////////////
	///////////////////////////main loop///////////////////////////
	///////////////////////////////////////////////////////////////
	while (window.isOpen())
	{
		InputManager::Clear(); // InputManager Clear()

		sf::Time dt = clock.restart();
		realDeltaTime = dt.asSeconds();
		realTime += deltaTime;

		deltaTime = realDeltaTime * timeScale;
		time += deltaTime;

		sf::Event event; // 이벤트 : 어플리케이션이 os로부터 넘겨 받는 것

		// 이벤트는 Message Queue에 쌓이게 된다. 
		while (window.pollEvent(event)) // message loop
		{
			InputManager::UpdateEvent(event); // InputManager UpdateEvent

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased: // 키 입력
				if (event.key.code == sf::Keyboard::Return)
				{
					if (isPause) break; // pause일 떄 return 하면 아무 것도 실행되지 않음
					if (isGameover)
					{
						timeScale = 1.f;
						isGameover = false;
						score = 0;
						timeBarCurrentSize = timeBarSize;
						InitGame();
					}
					break;
				}
				else if (event.key.code == sf::Keyboard::P)
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


		if (InputManager::GetKeyDown(sf::Keyboard::Enter))
		{
			if (!isGameover)
			{
				isPause = !isPause;
				timeScale = isPause ? 0.f : 1.f;
			}
			else if (isGameover && (playerSides == branchSides[NUM_OF_BRANCHES - 1] || timeBarCurrentSize.x <= 0))
			{
				score = 0;
				textScore.setString("Score : " + std::to_string(score));
				InitGame();

			}
		}

		if (!isPause)
		{
			bool isMove = false;
			Sides prevPlayerSide = playerSides;

			if (InputManager::GetKeyDown(sf::Keyboard::Left) && !isPause && !isGameover)
			{
				playerSides = Sides::LEFT;
				isMove = true;
				std::cout << "Lef" << std::endl;
				UpdateBranches();
			}
			else if (InputManager::GetKeyDown(sf::Keyboard::Right) && !isPause && !isGameover)
			{
				playerSides = Sides::RIGHT;
				isMove = true;
				std::cout << "rig" << std::endl;

				UpdateBranches();
			}

			if (prevPlayerSide != playerSides) // 변했을 때만 호출
			{
				spritePlayer.setPosition(playerPos[(int)playerSides]);
				spritePlayer.setScale(playerScale[(int)playerSides]);
				spriteAxe.setPosition(axePos[(int)playerSides]);
				spriteAxe.setScale(playerScale[(int)playerSides]);
			}
			if (isMove)
			{
				if (branchSides[NUM_OF_BRANCHES - 1] == playerSides)
				{
					isGameover = true;
					textGameover.setString("Game Over. Press Enter to Restart!");
					Utils::SetOrigin(textGameover, Origins::MC);
				}
				else
				{
					score += 10;
					timeBarCurrentSize.x += 50;
					if (timeBarCurrentSize.x > timeBarSize.x)
					{
						timeBarCurrentSize.x = timeBarSize.x;
					}
					textScore.setString("Score : " + std::to_string(score));
				}
			}
		}
		


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

		float treeHalfWidth = spriteTree.getLocalBounds().width * 0.5f;

		

		for (int i = 0; i < NUM_OF_BRANCHES; ++i)
		{
			float y = i * 150.f;
			float centerX = vm.width * 0.5f;

			switch (branchSides[i])
			{
			case Sides::LEFT :
				spriteBranches[i].setScale(-1.f, 1.f);
				spriteBranches[i].setPosition(centerX - treeHalfWidth, y);
				break;

			case Sides::RIGHT:
				spriteBranches[i].setScale(1.f, 1.f);
				spriteBranches[i].setPosition(centerX + treeHalfWidth, y);
				break;
			default:
				spriteBranches[i].setPosition(-2000,-2000);
				break;
			}
		}


#pragma endregion


#pragma region Draw
		///////////////////////////////////////////////////////////////
		/////////////////////////////Draw//////////////////////////////
		///////////////////////////////////////////////////////////////
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Tree, Branch Layer
		window.draw(spriteTree);
		for (int i = 0; i < NUM_OF_BRANCHES; ++i)
		{
			window.draw(spriteBranches[i]);
		}
		window.draw(spritePlayer);
		window.draw(spriteAxe);
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
			timeBarCurrentSize.x = 0;
			window.draw(textGameover);
		}
#pragma endregion

		window.display();
	}

	return 0;

}

void UpdateBranches()
{
	for (int i = NUM_OF_BRANCHES - 1; i > 0; --i)
	{
		branchSides[i] = branchSides[i - 1];
	}

	float value = (float)(rand() / RAND_MAX);

	int side = rand() % 5;
	std::cout << side << std::endl;

	switch (side)
	{
	case 0 : 
		branchSides[0] = Sides::LEFT;
		break;
	case 1 : 
		branchSides[0] = Sides::RIGHT;
		break;
	default:
		branchSides[0] = Sides::NONE;
		break;
	}
}

void InitGame()
{
	for (int i = 0; i < NUM_OF_BRANCHES; ++i)
	{
		UpdateBranches();
	}
	branchSides[NUM_OF_BRANCHES - 1] = Sides::NONE;
	branchSides[NUM_OF_BRANCHES - 2] = Sides::NONE;
	playerSide = Sides::RIGHT;

	timeBarCurrentSize.x = timeBarSize.x;
}

sf::Vector2f& RandomRotation(sf::Vector2f& v)
{
	sf::Transform rotation;
	float zeroToOne = (float)rand() / RAND_MAX; // 0.0 ~ 1.0
	float angle = zeroToOne * 360.f; // 0.0 ~ 360.0
	rotation.rotate(angle);

	return v;
}

float GetRandomAngle()
{
	return (float)rand() / RAND_MAX * 360.f;
}

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