#pragma once
class GameObject
{
protected :
	GameObject(const GameObject&)			 = delete;
	GameObject(GameObject&&)				 = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&)		 = delete;


	Origins originPreset = Origins::TL;
	sf::Vector2f origin = {0.f, 0.f};
	sf::Vector2f position = {0.f, 0.f};
	sf::Transform rotation;
	bool isActive = true;


public :
	// 이 부분 protected로 이동 후 get, set함수로 정의 필요


	std::string name = "";
	int sortLayer = 0; // 다른 레이어 간 순서
	int sortOrder = 0; // 동일 레이어 간 순서

	GameObject(const std::string& name = "");

	virtual ~GameObject();
	
	bool GetActive() const { return this->isActive; }
	virtual void SetActive(bool active) { this->isActive = active; }

	sf::Vector2f GetPosition() const { return this->position; }
	virtual void SetPosition(const sf::Vector2f pos) { this->position = pos; }

	sf::Vector2f GetOrigin() const { return this->origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f origin) 
	{
		originPreset = Origins::CUSTOM;
		this->origin = origin;
	}
	
	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);	


};

