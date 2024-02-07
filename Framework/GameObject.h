#pragma once
class GameObject
{
protected :
	GameObject(const GameObject&)			 = delete;
	GameObject(GameObject&&)				 = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&)		 = delete;

public :
	GameObject(const std::string& name = "");

	virtual ~GameObject();
	virtual void SetActive(bool active) { this->isActive = active; }
	virtual bool GetActive() const { return isActive; }

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);	

	// 이 부분 protected로 이동 후 get, set함수로 정의 필요
	bool isActive = true;
	std::string name = "";
	int sortLayer = 0; // 다른 레이어 간 순서
	int sortOrder = 0; // 동일 레이어 간 순서
};

