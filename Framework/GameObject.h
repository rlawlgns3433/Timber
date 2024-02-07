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

	// �� �κ� protected�� �̵� �� get, set�Լ��� ���� �ʿ�
	bool isActive = true;
	std::string name = "";
	int sortLayer = 0; // �ٸ� ���̾� �� ����
	int sortOrder = 0; // ���� ���̾� �� ����
};

