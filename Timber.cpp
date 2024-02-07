#include "pch.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    

    ResourceManager<sf::Texture>& textureManager = ResourceManager<sf::Texture>::Instance();
    textureManager.Load("graphics/background.png");

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

        //Update
        sceneManager.Update(dt);

        if (InputManager::GetKeyDown(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Draw

        window.clear();
        sceneManager.Draw(window);
        window.display();
    }

    sceneManager.Release();
    
    return 0;
}