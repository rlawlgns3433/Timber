#pragma once
class GameObject
{
protected :
	GameObject(const GameObject&)			 = delete;
	GameObject(GameObject&&)				 = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&)		 = delete;

	sf::Transform rotation;
	Origins originPreset = Origins::TL;
	std::string name = "";

	sf::Vector2f origin = {0.f, 0.f};
	sf::Vector2f position = {0.f, 0.f};
	sf::Vector2f scale = { 1.f, 1.f };

	bool isActive = true;

public :

	int sortLayer = 0; // �ٸ� ���̾� �� ����
	int sortOrder = 0; // ���� ���̾� �� ����

	GameObject(const std::string& name = "");

	virtual ~GameObject();
	
	bool GetActive() const { return this->isActive; }
	virtual void SetActive(bool active) { this->isActive = active; }

	sf::Vector2f GetPosition() const { return this->position; }
	virtual void SetPosition(const sf::Vector2f pos) { this->position = pos; }
	virtual void SetPosition(float x, float y) { this->position.x = x, this->position.y = y; }

	sf::Vector2f GetOrigin() const { return this->origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f origin) 
	{
		originPreset = Origins::CUSTOM;
		this->origin = origin;
	}
	// get �Լ� :  scale, rotation, name

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);	

	sf::Transform GetRotation() const { return this->rotation; }
	virtual void SetRotation(const sf::Transform& rot) { this->rotation = rot; }

	sf::Vector2f GetScale() const { return this->scale; }
	virtual void SetScale(const sf::Vector2f& scale) { this->scale = scale; }

	std::string GetName() const { return this->name; }
	virtual void SetName(std::string& name) { this->name = name; }
};

