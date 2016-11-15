#pragma once

#include <vector>
#include <Utils/Color.h>

#define GLYPH_INDEX_MASK       0x0fffffff
#define GLYPH_ATTR_MASK        0xf0000000

#define GLYPH_ATTR_SPACE       0x10000000
#define GLYPH_ATTR_TAB         0x20000000
#define GLYPH_ATTR_NEWLINE     GLYPH_ATTR_SPACE | GLYPH_ATTR_TAB
#define GLYPH_ATTR_UNBREAKABLE 0x40000000

#define GET_GLYPH_INDEX(value) (value & GLYPH_INDEX_MASK)
#define GET_GLYPH_ATTR(value) (value & GLYPH_ATTR_MASK)

namespace freetype {
	struct glyphindex {
		uint32_t value;
		bool unbreakable;

		glyphindex() : value(), unbreakable(false) {}
		glyphindex(uint32_t index) : value(index), unbreakable(false) {}

		operator uint32_t() const { return value; }
	};

	const glyphindex USERGLYPHS = 0xffffff00;
	const glyphindex SPACE = 0xffffff10;
	const glyphindex TAB = 0xffffff20;
	const glyphindex NEWLINE = 0xffffff30;
	const glyphindex SOFT_HYPHEN = 0xffffff40;

	//представление глифа на текстуре
	struct GPUGlyph {
		float u1, v1, u2, v2;
		float width, height;
		float offsetX, offsetY;
		float advanceX, advanceY;
	};

	class FontReference;
	class CFontGlyphAtlasTexture;
	class FontInstance;
	class FontEffect;
	class FontEffectTemplate;

	void InitFreetype();
	void UninitFreetype();
	
	FontReference* createFontReference(const std::string& _fontname, uint8_t* data, int dataLength);
	CFontGlyphAtlasTexture* createFontTexture(int width, int height);
	FontInstance* createFontInstance(FontReference* reference, int size, float _prescale);
	
	void destroyFontReference(FontReference*);
	void destroyFontTexture(CFontGlyphAtlasTexture*);
	void destroyFontInstance(FontInstance*);

	void applyFontEffect(FontInstance* instance, FontEffect* effect);
	void setFontColor(FontInstance* instance, Color color);
	float getFontCharWidth(FontInstance* instance, uint32_t charcode);
	float getFontKerning(FontInstance* instance, uint32_t charcode, uint32_t next);
	float getFontSpaceWidth(FontInstance* instance);
	void setFontSpaceWidth(FontInstance* instance, float multiplier);

	struct DropShadow {
		int blurX;
		int blurY;
		int offset;
		float angle;
		float power;
		Color color;
		bool inner;
	};

	FontEffect* createDropShadowEffect(DropShadow* descriptor);
	
	struct GradientFill {
		Color colors[256];
		float ratios[256];
		int anchors;
	};

	FontEffect* createGradientFillEffect(GradientFill* descriptor);
	FontEffect* createSkewEffect(float angle);

	void destroyFontEffect(FontEffect* effect);
	
	FontReference* getReference(FontInstance* fontInstance);

	void resolveCharCodes(FontReference* reference, const uint32_t* charcodes, int count, std::vector<glyphindex>& glyphs);

	float calculateStringWidth(FontInstance* instance, const glyphindex* glyphs, int length, float letterSpacing = 0);
	float getStringHeight(FontInstance* instance);
	float getStringBearing(FontInstance* instance);
	float getStringAscender(FontInstance* instance);
	float getStringDescender(FontInstance* instance);
	float getLineSpacing(FontInstance* instance);

	void discardGlyphs(CFontGlyphAtlasTexture* texture);
	GPUGlyph* getGlyph(FontInstance* fontInstance, CFontGlyphAtlasTexture* texture, glyphindex glyph);
	float getKerning(FontInstance* fontInstance, glyphindex glyph1, glyphindex glyph2);
	float getSpaceWidth(FontInstance* fontInstance);

	//Костыльная функция для включение автохинтинга(антиалиасинга) для определенных шрифтов
	//Думаю что не стоит её использовать, и удовлетворится хинтингом который есть по умолчанию
	//Атохинтинг truetype дает более достенькие буквы, плюс он может себя вести некорректоно для bold шрифтов, дополнительно их утолщая
	void EnableAutoHint(const std::string& _fontname, bool _enable);
} // namespace freetype
