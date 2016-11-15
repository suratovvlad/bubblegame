#pragma once

#include <utility>

#include "FreeType.h"

namespace freetype
{

//Задает форматирование параграфа
struct Paragraph
{
	bool wordWrap;
    
    std::vector<uint32_t> sourceDecimalPoint;
    std::string sourceDecimalPointStr;
    bool groupThousands;
    std::vector<uint32_t> thousandsSeparator;
    std::vector<uint32_t> decimalPoint;

	enum tagWordBreak {
		Normal,
		BreakAll
	} wordBreak;

	enum tagAlign {
		LeftAlign,
		RightAlign,
		CenterAlign,
		WidthAlign
	} align;

	float lineInterval; // 0..1

	Paragraph()
		: align(LeftAlign)
		, wordBreak(BreakAll)
		, wordWrap(true)
		, lineInterval(0.0f)
        , groupThousands(true)
    {
        thousandsSeparator = {' '};
        decimalPoint = {'.'};
        sourceDecimalPoint = {'.'};
        sourceDecimalPointStr = ".";
	}

    Paragraph(bool wordWrap, tagWordBreak wordBreak, tagAlign align, float lineInterval
              , const std::vector<uint32_t>& sourceDecimalPoint
              , const std::string& sourceDecimalPointStr
              , bool groupThousands
              , const std::vector<uint32_t>& thousandsSeparator
              , const std::vector<uint32_t>& decimalPoint
              )
		: align(align)
		, wordBreak(wordBreak)
		, wordWrap(wordWrap)
		, lineInterval(lineInterval)
        , sourceDecimalPoint(sourceDecimalPoint)
        , sourceDecimalPointStr(sourceDecimalPointStr)
        , groupThousands(groupThousands)
        , thousandsSeparator(thousandsSeparator)
        , decimalPoint(decimalPoint)
	{
	}
    

};

//-----------------------------------------------------------------------------
//
//           Задает слово - участок текста с постоянным шрифтом.
//
//-----------------------------------------------------------------------------
class Word
{
public:
	Word(FontInstance* font, uint32_t* charcodes, int length, Color color, float letterSpacing = 0);
	virtual ~Word();

	FontInstance* getFont();
	Color getColor();
	float getLetterSpacing();
	virtual const std::vector<glyphindex>& getGlyphs();
	virtual bool update();

protected:
    virtual void setGlyphs(const std::vector<glyphindex>& glyphs);
	FontInstance* fontInstance;
	Color color;
	
	float letterSpacing;
	
    
private:
    std::vector<glyphindex> glyphs;
};

//-----------------------------------------------------------------------------
//
// Число в тексте - выделено в отдельную сущьность для авто форматирования
//
//-----------------------------------------------------------------------------
class Number: public Word
{
public:
	Number(FontInstance* font, uint32_t* charcodes, int length, const Color& color, float letterSpacing);
	Number(FontInstance* font, uint32_t* charcodes, int length, const Color& color, bool is_signed, float letterSpacing, int16_t _lGlue, int16_t _rGlue);
	virtual ~Number();
    
	void setSettings(bool groupThousands, const std::vector<uint32_t>& thousandsSeparator, const std::vector<uint32_t>& defDecimalPoint, const std::vector<uint32_t>& decimalPoint);
  virtual const std::vector<glyphindex>& getGlyphs();

	int16_t getlGlue(){ return __m_lGlue; }
	int16_t getrGlue(){ return __m_rGlue; }
    
protected:
    virtual void setGlyphs(const std::vector<glyphindex>& glyphs);

private:
	int16_t __m_lGlue;
	int16_t __m_rGlue;

	void updateNumberGlyphs();
	std::vector<glyphindex> grouped_glyphs;
	bool isSigned;
	bool groupThousands;
	std::vector<uint32_t> defDecimalPoint;
	std::vector<uint32_t> thousandsSeparator;
	std::vector<uint32_t> decimalPoint;
    
	std::vector<glyphindex> glyphThousandsSeparator;
	std::vector<glyphindex> glyphDecimalPoint;
	std::vector<glyphindex> glyphDefDecimalPoint;
};

//-----------------------------------------------------------------------------
//
// Динамическое слово - обращается к переменной для получения своего значения
//
//-----------------------------------------------------------------------------
template<class BaseClass, class T, typename Format, typename Mutation>
class DynamicWord : public BaseClass
{
public:
	DynamicWord(FontInstance* font, Color color, const T* _ref, float letterSpacing = 0): 
		BaseClass(font, 0, 0, color, letterSpacing),
		ref(_ref)
	{
		__update();
	}

	virtual ~DynamicWord()
	{
	}

	bool update()
	{
        if(__update())
        {
            BaseClass::update();
            return true;
        }
        return  false;
	}

private:
	bool __update()
	{
		bool l_retval = false;

		if (mutation(ref))
		{
			format(ref, chars);

			if (!chars.empty())
			{
				std::vector<glyphindex> new_glyphs;
				new_glyphs.reserve(chars.size());

				freetype::resolveCharCodes(freetype::getReference(BaseClass::fontInstance), &(chars[0]), chars.size(), new_glyphs);
				BaseClass::setGlyphs( new_glyphs );

				l_retval = true;
			};
		};

		return l_retval;
	}

private:
	std::vector<uint32_t> chars;

	Mutation mutation;
	Format format;
	const T* ref;
};

//---------------------------------------------------------------------------
//
//                     Встраиваемый объект (например, картинка)
//
//---------------------------------------------------------------------------
class InlinedObject
{
public:
	virtual ~InlinedObject(){}
	virtual void getSize(float& width, float& height) = 0;
	virtual void draw(float penX, float penY, Color color) = 0;
};

//---------------------------------------------------------------------------
//
//                                TextRenderMetrics
//
//---------------------------------------------------------------------------
struct TextRenderMetrics
{
	TextRenderMetrics()
	{
	}

	TextRenderMetrics(float _top, float  _left, float _width, float _height) :
		top(_top),
		left(_left),
		width(_width),
		height(_height)
	{
	}

	inline float getTop()
	{
		return top;
	};

	inline float getRigth()
	{
		return left + width;
	};

	inline float getBottom()
	{
		return top + height;
	};

	inline float getLeft()
	{
		return left;
	};

	inline float getWidth()
	{
		return width;
	};

	inline float getHeight()
	{
		return height;
	};

private:
	float top;
	float left;

	float width;
	float height;
};

//---------------------------------------------------------------------------
//
//                               LineElement
//
//---------------------------------------------------------------------------
struct LineElement
{
	float width;
	int spaces;
	int16_t leftGlue;
	int16_t rightGlue;
	
	enum {
		InlinedObject,
		Text,
		LineBreak,
		Paragraph
	} type;

	union {
		struct {
			float height;
			float spacing;
		};

		freetype::InlinedObject* object;
		freetype::Paragraph* paragraph;

		struct{
			FontInstance* font;
			const glyphindex* glyphs;
			int length;
			
			uint32_t color;
			float letterSpacing;
		} text;
	};
};

//---------------------------------------------------------------------------
//
//                                Text
//
//---------------------------------------------------------------------------
class Text
{
public:
	Text(float prescale);
	~Text();

	int addParagraph(Paragraph* paragraph);
	int addWord(Word* word);
    int addNumber(Number* number);
	int addObject(InlinedObject* object);

	float getLeft() { return left; }
	void setLeft(float left);

	float getTop() { return top; }
	void setTop(float top);

	float getRight() { return right; }
	void setRight(float right);

	float getBottom() { return bottom; }
	void setBottom(float bottom);

	float getWidth(){return right - left;};
	float getHeight(){return top - bottom;};

	float getPrescale() { return _prescale; }
	void setPrescale(float prescale);

	void move(float x, float y);

	Paragraph* getLastParagraph();
	void getMetrics(float _width, TextRenderMetrics* _metrics);
	const std::vector<LineElement>& getElements();
	bool isUpdated();

	void setRenderCache(RefCounter* _renderCache){ __m_RenderCache = _renderCache; }
	RefCounter* getRenderCache(){ return __m_RenderCache.get(); }

	static Paragraph DefaultParagraph;

private:
	bool __updateElements();
	float __getElements(float _width, std::vector<LineElement>& _line);
	LineElement __newLineElm(float& x, float& y, float &_lineBearing, float& lineSpacing, int& lineSpaces, bool& isLineEmpty);
	LineElement __breakLineElm(float& x, float& y, float &_lineBearing, float& lineSpacing, int& lineSpaces, bool& isLineEmpty);
	LineElement __paragraphElm(Paragraph* _paragraph);
	LineElement __inlineElm(InlinedObject* _inlineObj, float &lineBearing);
	LineElement __textElm(Word* _text, size_t _tbegin, size_t _tend, float _lineInterval, float &_lineBearing, float& lineSpacing, int& lineSpaces);

	LineElement& __wordWrap(const LineElement& _textElement, std::vector<LineElement>& _line, float _width, float& _x, float& _y, float& _lineBearing, float& _lineSpacing, int& _lineSpaces, bool& _isLineEmpty);
	LineElement& __wordBreak(LineElement& _textElement, std::vector<LineElement>& _line, float _width, float& _x, float& _y, float& _lineBearing, float& _lineSpacing, int& _lineSpaces, bool& _isLineEmpty);

private:
	float left, top, right, bottom, _prescale;

	struct TextElement{
		union {
			Paragraph* paragraph;
			Word* word;
			Number *number;
			InlinedObject* inlinedObject;
		};

		enum {
			PARAGRAPH,
			NUMBER,
			WORD,
			OBJECT
		} tag;
	};

	std::list<TextElement> elements;
	std::vector<LineElement> __m_line;
	Paragraph* lastParagraph;

	boost::intrusive_ptr<RefCounter> __m_RenderCache;
};

typedef std::vector<LineElement>::const_iterator LineElementConstIter;
typedef std::vector<LineElement>::iterator LineElementIter;

} // namespace freetype
