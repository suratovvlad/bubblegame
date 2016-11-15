#pragma once

#include "Utils/Color.h"

#include <string>
#include <vector>

namespace freetype
{
/**
* Стиль текста (шрифт + эффекты). Используется для выбора шрифта, которым будет рисоваться текст
*/
struct TextStyle
{
	float fontSize;
	Color fontColor;
	float letterSpacing;
	float lineInterval;
	float spaceWidth;
	int align;
	int wordBreak;
	float prescale;

	std::string fontName;
	std::vector<std::string> effects;

	TextStyle()
		: fontSize(12)
		, fontColor(Color::WHITE)
		, letterSpacing(0)
		, lineInterval(0)
		, spaceWidth(1)
		, align(0)
		, wordBreak(0)
		, prescale(1)
	{
	}
};
};
