#include "stdafx.h"
#include "BubbleColor.h"
#include <Utils\random.hpp>

BubbleColor::BubbleColor()
{
	m_colorsMap.insert(std::pair<unsigned int, std::string>(Black, "bubble_black"));
	m_colorsMap.insert(std::pair<unsigned int, std::string>(Blue, "bubble_blue"));
	m_colorsMap.insert(std::pair<unsigned int, std::string>(Green, "bubble_green"));
	m_colorsMap.insert(std::pair<unsigned int, std::string>(Orange, "bubble_orange"));
	m_colorsMap.insert(std::pair<unsigned int, std::string>(Purple, "bubble_purple"));
	m_colorsMap.insert(std::pair<unsigned int, std::string>(Red, "bubble_red"));
	m_colorsMap.insert(std::pair<unsigned int, std::string>(White, "bubble_white"));
	m_colorsMap.insert(std::pair<unsigned int, std::string>(Yellow, "bubble_yellow"));


	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_black", "explode_black"));
	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_blue", "explode_black"));
	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_green", "explode_black"));
	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_orange", "explode_black"));
	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_purple", "explode_black"));
	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_red", "explode_black"));
	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_white", "explode_black"));
	m_explodeColorsMap.insert(std::pair<std::string, std::string>("bubble_yellow", "explode_black"));


	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_black", 100));
	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_blue", 150));
	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_green", 200));
	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_orange", 300));
	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_purple", 800));
	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_red", 400));
	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_white", 1000));
	m_scoresMap.insert(std::pair<std::string, unsigned int>("bubble_yellow", 600));
}

BubbleColor::~BubbleColor()
{
	m_colorsMap.clear();
}

std::string BubbleColor::GetRandomColor()
{
	return m_colorsMap[math::random(Black, Yellow)];
}

std::string BubbleColor::GetExplodeColor(const std::string& color)
{
	return m_explodeColorsMap[color];
}

unsigned int BubbleColor::GetBubbleScore(const std::string& color)
{
	return m_scoresMap[color];
}