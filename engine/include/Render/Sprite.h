#ifndef __SPRITE_H__
#define __SPRITE_H__

#pragma once

#include "Core/Resource.h"
#include "Core/ResourceFactory.h"
#include "Render/Drawable.h"
#include "Render/Texture.h"
#include "Render/SpriteBatch.h"
#include "Utils/IPoint.h"
#include "Utils/Xml.h"

namespace Render {
class Sheet;

class Sprite : public Resource, public Drawable {
public:
	Sprite();

	explicit Sprite(rapidxml::xml_node<>* xe);

	explicit Sprite(Texture* tex);

	virtual const std::string& GetName() const override { return _id; }

	virtual size_t GetMemoryInUse() const override;

	virtual int Width() const override;

	virtual int Height() const override;

	virtual bool HitTest(int x, int y) const override;

	virtual void Draw(SpriteBatch* batch, const FPoint& position) override;

	using Drawable::HitTest;

	using Drawable::Draw;

    
    bool Empty() const;

	virtual void Load(ResourceLoadMode load_mode) override;

	virtual void Unload(ResourceLoadMode load_mode) override;

	virtual void GroupLoad(ResourceLoadManager& ldm) override;

	virtual void GroupUnload(ResourceLoadManager& ldm) override;

protected:
    friend void ResourceFactory::LoadResourcesXml(const std::string& filename);

    friend class Render::Sheet;
    
	void SetName(const std::string& name) { _id = name; }

	void SetTexture(Render::Texture* tex) { _texture = tex; }

protected:
	std::string _id;
    float _prescale;
	TexturePtr _texture;

private:
	Sprite(const Sprite&);
	Sprite& operator=(const Sprite&);
};

typedef boost::intrusive_ptr<Sprite> SpritePtr;


class PolygonalSprite : public Sprite {
public:
	PolygonalSprite(rapidxml::xml_node<>* xe);

	virtual size_t GetMemoryInUse() const override;

	virtual int Width() const override;

	virtual int Height() const override;

	virtual bool HitTest(int x, int y) const override;

	virtual void Draw(SpriteBatch* batch, const FPoint& position) override;

protected:
    friend class Render::Sheet;

private:
	typedef std::pair<int16_t, int16_t> Point;

	struct Triangle {
		Point a, b, c;
	};

	typedef std::vector<Triangle> Triangles;

	Triangles _triangles;
    
    struct CTriangle{
        math::Vector3 vec[4];
        FPoint uv[4];
    } ;
    
    typedef std::vector<CTriangle> CTriangles;
    
    CTriangles _c_triangles;
    
    

	Point _offset;

	int16_t _width, _height;
};

typedef boost::intrusive_ptr<PolygonalSprite> PolygonalSpritePtr;

} // namespace Render

#endif // __SPRITE_H__
