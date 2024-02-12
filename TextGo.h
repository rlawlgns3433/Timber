#pragma once
#include "GameObject.h"

typedef unsigned int uint;

class TextGo : public GameObject
{
protected :
	TextGo(const TextGo&) = delete;
	TextGo(TextGo&&) = delete;
	TextGo& operator=(const TextGo&) = delete;
	TextGo& operator=(TextGo&&) = delete;

	sf::Color textColor = sf::Color::Black;
	sf::Font font;
	sf::Text text;
	uint textSize = 1;

public :
	TextGo(const std::string& name = "");

	std::string GetText() const;
	void SetText(const std::string& text);
	void SetText(const sf::Text& text);
	void SetFont(const sf::Font& font);
	void SetFillColor(const sf::Color& color);
	void SetTextSize(const uint& textSize);

	virtual void Draw(sf::RenderWindow& window);
};