#ifndef __BUBBLECOLOR_H__
#define __BUBBLECOLOR_H__

#pragma once

#include <map>
#include <singleton.hpp>

class BubbleColor : public Singleton<BubbleColor>
{
	enum Color{
		Black = 0,
		Blue,
		Green,
		Orange,
		Purple,
		Red,
		White,
		Yellow
	};

	std::map<unsigned int, std::string> m_colorsMap;
	std::map<std::string, std::string> m_explodeColorsMap;
	std::map<std::string, unsigned int> m_scoresMap;

public:
	
	BubbleColor();
	~BubbleColor();
	std::string GetRandomColor();
	std::string GetExplodeColor(const std::string&);
	unsigned int GetBubbleScore(const std::string&);
};

#endif // __BUBBLECOLOR_H__