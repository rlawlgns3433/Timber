#include "pch.h"

int main()
{
    srand(time(NULL));

    //std::mt19937(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");


    ResourceManager<sf::Font>& resourceManager = ResourceManager<sf::Font>::Instance();
    resourceManager.Load("fonts/KOMIKAP_.ttf");

    SceneManager& sceneManager = SceneManager::Instance();

    sceneManager.Init();


    sf::Clock clock;
    float dt = 0.f;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        dt = deltaTime.asSeconds();

        InputManager::Clear(); // 키 입력 초기화

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputManager::UpdateEvent(event); // 키 입력 이벤트 처리
        }

        if (InputManager::GetKeyDown(sf::Keyboard::Escape))
        {
            window.close();
        }


        //Update
        sceneManager.Update(dt);

        // Draw

        window.clear();
        sceneManager.Draw(window);
        window.display();
    }

    sceneManager.Release();

    return 0;
}