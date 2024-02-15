#pragma once
#include "SpriteGo.h"
class AxeGo : public SpriteGo
{
protected:
	Sides axeSide = Sides::NONE;
	Sides originalAxeSide = Sides::RIGHT;

public:
	AxeGo(const std::string& name = "");
	virtual ~AxeGo() = default;

	Sides GetSide() const { return this->axeSide; }
	void SetSide(Sides side) { this->axeSide = side; }

};

