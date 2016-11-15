#ifndef __SPRITEBATCH_H__
#define __SPRITEBATCH_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif // _MSC_VER

#include "RenderDevice.h"
#include "Utils/Color.h"
#include "Utils/IRect.h"
#include "RefCounter.h"

#include <boost/intrusive_ptr.hpp>

namespace math {
	class Vector3;
};

///
/// ����������� ������ ���������� ��������
///
enum class SpriteSortMode {
	// ����������� ������� �� ���������� ������, ��� ���������� ������������ ������
	Deferred,
	// ����� ������������ ������� �� ������
	Immediate,
	// ����������� ������� �� ���������� ������, ����� ��������� �� ���������
	Texture,
	// ����������� ������� �� ���������� ������, ����� ��������� �� ������ ����������
	Blend,
	// ����������� ������� �� ���������� ������, ����� ��������� �� �������� � ��������
	BackToFront,
	// ����������� ������� �� ���������� ������, ����� ��������� �� �������� � ��������
	FrontToBack
};

///
/// ����������� ������ ����������������� ��������
///
enum class SpriteTransformMode {
	// ��� �����������������
	None,
	// ��������� ������� ������������� �� ����������
	Auto
};

namespace Render {

///
/// ����� ��������
///
class SpriteBatch : public RefCounter {
public:
	SpriteBatch();
	~SpriteBatch();
	
	/// �������� ����� ��������
	virtual void Begin(SpriteSortMode sortMode = SpriteSortMode::Deferred, SpriteTransformMode transformMode = SpriteTransformMode::None);
	
	/// ������ ������, ����������� ���������� � ������� TranslateUV
	/// �������� textureRect ���������� ������������� �������� � �������� [0; width/height]
	virtual void DrawRect(Texture* texture, ShaderProgram* shader, BlendMode blend, const FRect& textureRect, const FRect& screenRect, float z = 0.0f);
	
	// ��� ��� ������ - �������� ������ ������������ ������
	void DrawRect(Texture* texture, BlendMode blend, const FRect& textureRect, const FRect& screenRect);
	void DrawRect(Texture* texture, BlendMode blend, const IRect& textureRect, const math::Vector3& position);
	void DrawRect(Texture* texture, BlendMode blend, const FPoint& position);

	/// ������ ������, �� ����������� ���������� � ������� TranslateUV
	/// �������� uv ���������� ������������� �������� � ��������������� ���������� ����������� [0; 1]
	virtual void Draw(Texture* texture, ShaderProgram* shader, BlendMode blend, const math::Vector3 vec[4], const Color color[4], const FPoint uvs[4]);

	// ��� ��� ������ - �������� ������ ������������ ������
	void Draw(Texture* texture, BlendMode blend, const math::Vector3 vec[4], const Color color[4], const FPoint uvs[4]);	
	void Draw(Texture* texture, BlendMode blend, const FRect& screenRect, const FRect& uv);
	void Draw(Texture* texture, BlendMode blend, const FRect& screenRect, const FRect& uv, Color color);
	void Draw(Texture* texture, BlendMode blend, const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, Color color, const FRect& uv);
	void Draw(Texture* texture, BlendMode blend, const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, const Color c[4], const FRect& uv);

	/// ������������� ������������ �������������� �������
	virtual void Flush();
	
	/// ����������� ����� ��������
	virtual void End();

	/// ����������� ���������� ����������� �������
	static void ResetBatches();
    
    static void Shutdown();

protected:
	class Impl;
	std::auto_ptr<Impl> _impl;
	
	SpriteTransformMode _transformMode;

private:
	SpriteBatch(const SpriteBatch&);
	SpriteBatch& operator=(const SpriteBatch&);
};

typedef boost::intrusive_ptr<SpriteBatch> SpriteBatchPtr;

} // namespace Render

#endif // __SPRITEBATCH_H__
