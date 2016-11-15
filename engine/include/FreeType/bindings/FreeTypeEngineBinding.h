#pragma once

#include <FreeType/FreeType.h>
#include <FreeType/TextStyle.h>
#include <FreeType/FreeTypeText.h>

extern float FONTS_PRESCALE, FONTS_INV_PRESCALE;

namespace Render
{
	class SpriteBatch;
};

namespace FreeType {

	void configure(int textureWidth, int textureHeight);
	void initialize();
	void reinitialize();
	void update();

	/*
	* Устанавливает какой набор символов в загружаемых текстах считать разделителем целой и дробной части
	* по умолчанию "."
	*/
	void setSourceDecimalPoint( const std::string &srcDecimalPoint);

	/*
	* Устанавливает нужно ли при отрисовке разделять у чисел тысячи по группам ( 1 000 000.00 )
	*/
	void setGroupThousands( bool groupThousands);

	/*
	* Устанавливает какой набор символов использовать в качестве разделителя при группировке по тысячам
	*/
	void setThousandsSeparator( const std::string &srcDecimalPoint);

	/*
	* Устанавливает какой набор символов использовать в качестве разделителя целой и дробной части
	* по умолчанию "."
	*/
	void setDecimalPoint( const std::string &srcDecimalPoint);

	/**
	* Устанавливает переменную в текстах.
	* Сбрасывает кэш текстов, поэтому менять часто не рекомендуется
	*/
	void setGlobalConstant(const std::string& id, const std::string& value);
	/**
	* Устанавливает переменную в текстах.
	* Работает только для простых текстов, внутри value строки не обрабатываются
	* специальные символы и подстановки. Зато данная конструкция не сбрасывает кэш
	* строк и эффективно работает для часто меняющихся элементов
	*/
	void setGlobalVariable(const std::string& id, const std::string& value);

	template<class T>
	char convT(T&);

	///Возвращает строковую ссылку на переменную.
	///С помощью этой функции можно подставить в текст непосредственно переменную, например:
	/// textField->setText("Score: " + ref(score));
	///И при каждом изменении score текст на экране будет обновлен.
	template<class T>
	std::string ref(T& val){
		char textual[1024];
		sprintf(textual, "{ref %c %p}", convT<T>(val), &val);
		return textual;
	}

	freetype::FontInstance* createFont(const freetype::TextStyle* style);
	freetype::Text* getText(const std::string& source, const freetype::TextStyle* textStyle);
	void render(freetype::Text* text, Color color);
	void renderInBatch(Render::SpriteBatch* _batch, freetype::Text* text, Color color);
	void getLettersCoords(freetype::Text* text, std::vector<IPoint>& coords);

	void applyFontEffectTemplate( const std::string &type, freetype::FontEffectTemplate *creator );

} // namespace FreeType
