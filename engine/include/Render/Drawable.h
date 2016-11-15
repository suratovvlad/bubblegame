#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#pragma once

#include "Utils/FPoint.h"

namespace Render {

class SpriteBatch;

///
/// Базовый класс для рисуемых сущностей.
///
class Drawable {
public:
	virtual ~Drawable() { }

	virtual int Width() const = 0;

	virtual int Height() const = 0;

	virtual bool HitTest(int x, int y) const = 0;

	virtual void Draw(SpriteBatch* batch, const FPoint& position) = 0;
};

} // namespace Render

#endif // __DRAWABLE_H__
