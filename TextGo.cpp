#include "pch.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& name)
	: GameObject(name)
{
}

std::string TextGo::GetText() const
{
	return text.getString();
}

void TextGo::SetText(const std::string& text)
{
	this->text.setString(text);
}

void TextGo::SetText(const sf::Text& text)
{
	this->text = text;
}

void TextGo::SetFont(const sf::Font& font)
{
	this->font = font;
	this->text.setFont(this->font);
}

void TextGo::SetFillColor(const sf::Color& color)
{
	this->textColor = color;
	this->text.setFillColor(this->textColor);
}

void TextGo::SetTextSize(const uint& textSize)
{
	this->textSize = textSize;
	this->text.setCharacterSize(this->textSize);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
