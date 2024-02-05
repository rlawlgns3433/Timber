#pragma once
#include <vector>

enum class Origins
{
	// enum class 사용법 Origins::TL
	// 값은 기존 enum과 동일하다.


	// T M B
	// L C R

	// TL TC TR
	// ML MC MR
	// BL BC BR

	TL, TC, TR, ML, MC, MR, BL, BC, BR,
};

enum class Sides
{
	LEFT, RIGHT, NONE
};