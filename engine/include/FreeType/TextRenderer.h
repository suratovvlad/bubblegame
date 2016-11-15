#pragma once

#include <boost/intrusive_ptr.hpp>
#include <Render/SpriteBatch.h>

#include "FreeTypeText.h"
#include "FreeType.h"

namespace freetype
{
class FontInstance;
class CFontGlyphAtlasTexture;
class CTextRenderCache;

class TextRendererBase
{
public:
	TextRendererBase(Render::SpriteBatch* _batch, CFontGlyphAtlasTexture*);

	void getLettersCoords(Text* text, std::vector<IPoint>& coords);
	void render(Text* text, Color color);

protected:
	void __createRenderTarget(CTextRenderCache* _renderCache, TextRenderMetrics& _metrics);
	void __releaseRenderTarget(CTextRenderCache* _renderCache);

	void __render(Text* text, Color color);
	void __renderHelper(Text* text, Color color);
	virtual void getElements(Text* text, std::vector<LineElement>& line);

private:
	void __bufferString(FontInstance* fontInstance, const glyphindex* glyphs, int length, Color color, float& x, float& y, float letterSpacing);

protected:
	boost::intrusive_ptr<Render::SpriteBatch> __spriteBatch;
	CFontGlyphAtlasTexture* fontTexture;
};


class TextRenderer: public TextRendererBase
{
public:
	TextRenderer(CFontGlyphAtlasTexture* _glyphTexture);

public:
	void render(Text* text, Color color);
};

}
