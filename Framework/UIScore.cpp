#include "pch.h"
#include "UIScore.h"

UIScore::UIScore(const std::string& name)
	: TextGo(name)
{
}

void UIScore::SetScore(size_t score)
{
	this->score = score;
	text.setString(scoreFormat.append(std::to_string(score)));
}

void UIScore::AddScore(size_t score)
{
	this->score += score;
	text.setString(scoreFormat.append(std::to_string(score)));
}

void UIScore::Reset()
{
	SetScore(0);
}
