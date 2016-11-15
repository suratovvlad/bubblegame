#ifndef __RENDER_FREETYPE__
#define __RENDER_FREETYPE__

#include <FreeType/TextStyle.h>

namespace Render { namespace FreeType {

	struct FreeTypeFont {
		std::string font;
		std::vector<std::string> effects;
		freetype::TextStyle style;
	};

	void ShowDebugInfo(bool enable);
	bool ShowDebugInfo();

	void BindFont(const std::string& font_name);
	bool isFontLoaded(const std::string &font_name);
	bool IsCharSet( const std::string& font_name, int code);

	FreeTypeFont getFont(const std::string &fontName);
	void addFont(const std::string &fontName, const FreeTypeFont &freeTypeFont);

	void PrintString(int x, int y, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, TextAlign valign = TopAlign, bool formatNumbers = true);
	void PrintString(float x, float y, float _width, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, TextAlign valign = TopAlign, bool formatNumbers = true);
	void PrintString(float x, float y, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, TextAlign valign = TopAlign, bool formatNumbers = true);
	void PrintString(const IPoint& pos, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, TextAlign valign = TopAlign, bool formatNumbers = true);
	void PrintString(const FPoint& pos, const std::string& str, float scale = 1.0f, TextAlign align = LeftAlign, TextAlign valign = TopAlign, bool formatNumbers = true);

	float getStringWidth(const std::string& str, freetype::TextStyle *textStyle);
	float getStringWidth(const std::string& str, const std::string& fontName);
	float getStringWidth(const std::string& str);

	float getFontHeight(freetype::TextStyle *textStyle);
	float getFontHeight(const std::string& fontName);
	float getFontHeight();

	float getFontDescender(freetype::TextStyle *textStyle);
	float getFontDescender(const std::string& fontName);
	float getFontDescender();

	float getLineSpacing(freetype::TextStyle *textStyle);
	float getLineSpacing(const std::string& fontName);
	float getLineSpacing();

	void LoadFont(rapidxml::xml_node<> *elem);
	void LoadStyledTextFromFont(rapidxml::xml_node<> *elem, std::string &font_style_id, std::string &font_style_description, std::string &font_style_atributes);

}} // namespace FreeType namespace Render

#endif