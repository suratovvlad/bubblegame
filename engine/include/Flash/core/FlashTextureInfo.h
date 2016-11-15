#pragma once

#include "Utils/utils.hpp"

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

/**
* Объект, позволяющий узнать, является ли пиксель в точке текстуры прозрачным
*/
struct IFlashTextureHitTestDelegate
{
	virtual bool hitTest(float u, float v) = 0;
};

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

struct FlashTextureInfo
{
	FlashTextureInfo():
		top(0),
		left(0),
		right(0),
		bottom(0),
		textureHeight(0),
		textureWidth(0),
		textureData(nullptr)
	{
	}

	void* textureData;
	float textureWidth, textureHeight;
	float top, left;
	float right, bottom;
};
