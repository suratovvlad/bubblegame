#ifndef __UTILS_XML_H__
#define __UTILS_XML_H__

#pragma once

#include "Utils/Color.h"
#include "Utils/IPoint.h"
#include "Utils/FPoint.h"
#include "Utils/IRect.h"
#include "Utils/FRect.h"

#include <pugixml.hpp>

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

#define QueryNvpAttribute(elem, attr) Xml::QueryAttribute(elem, #attr, attr)

//
// Функции для более удобной работы с TinyXml.
// (установка и получение XML-атрибутов)
//
namespace Xml {

// pugixml

// Есть ли у xe атрибут name.
bool HasAttribute(pugi::xml_node xe, const std::string& name);

// Получить из элемента xe атрибут типа float; атрибут с таким именем обязан существовать.
float GetFloatAttribute(pugi::xml_node xe, const std::string& name);

// Получить из элемента xe атрибут типа bool; атрибут с таким именем обязан существовать.
bool GetBoolAttribute(pugi::xml_node xe, const std::string& name);

// Получить из элемента xe атрибут типа int; атрибут с таким именем обязан существовать.
int GetIntAttribute(pugi::xml_node xe, const std::string& name);

// Получить из элемента xe атрибут типа color; атрибут с таким именем обязан существовать.
Color GetColorAttribute(pugi::xml_node xe, const std::string& name);

// Получить из элемента xe атрибут типа std::string; атрибут с таким именем обязан существовать.
std::string GetStringAttribute(pugi::xml_node xe, const std::string& name);

// Получить из элемента xe атрибут типа float или вернуть значение по умолчанию
float GetFloatAttributeOrDef(pugi::xml_node xe, const std::string& name, float defaultValue);

// Получить из элемента xe атрибут типа bool или вернуть значение по умолчанию
bool GetBoolAttributeOrDef(pugi::xml_node xe, const std::string& name, bool defaultValue);

// Получить из элемента xe атрибут типа int или вернуть значение по умолчанию
int GetIntAttributeOrDef(pugi::xml_node xe, const std::string& name, int defaultValue);

// Получить из элемента xe атрибут типа color или вернуть значение по умолчанию
Color GetColorAttributeOrDef(pugi::xml_node xe, const std::string& name, Color defaultValue);

// Получить из элемента xe атрибут типа std::string или вернуть значение по умолчанию
std::string GetStringAttributeOrDef(pugi::xml_node xe, const std::string& name, const std::string& defaultValue);

// Установить в элементе xe атрибут типа bool
void SetBoolAttribute(pugi::xml_node xe, const std::string& name, bool value);

// Установить в элементе xe атрибут типа int
void SetIntAttribute(pugi::xml_node xe, const std::string& name, int value);

// Установить в элементе xe атрибут типа float
void SetFloatAttribute(pugi::xml_node xe, const std::string& name, float value);

// Установить в элементе xe атрибут типа std::string
void SetStringAttribute(pugi::xml_node xe, const std::string& name, const std::string& value);

// Установить в элементе xe атрибут типа Color
void SetColorAttribute(pugi::xml_node xe, const std::string& name, const Color& value);

// Создать объект IPoint из xml атрибутов x, y
IPoint IPointFromXml(pugi::xml_node xe);

// Создать объект FPoint из xml атрибутов x, y
FPoint FPointFromXml(pugi::xml_node xe);

// Создать объект IRect из xml атрибутов x, y, width, height
IRect IRectFromXml(pugi::xml_node xe);

// Создать объект FRect из xml атрибутов xStart, yStart, xEnd, yEnd
FRect FRectFromXml(pugi::xml_node xe);

// Создаёт новый узел
pugi::xml_node NewNode(pugi::xml_node xe, const char* name, const char* value = NULL);

template <class T>
inline bool QueryAttribute(pugi::xml_node elem, const std::string& attrName, T& attrValue)
{
	if (elem.attribute(attrName.c_str())) {
		attrValue = utils::lexical_cast<T>(elem.attribute((pugi::char_t*)attrName.c_str()).value());
		return true;
	}

	return false;
}

template <>
inline bool QueryAttribute(pugi::xml_node elem, const std::string& attrName, std::string& attrValue)
{
	if (elem.attribute(attrName.c_str())) {
		attrValue = elem.attribute((pugi::char_t*)attrName.c_str()).value();
		return true;
	}
	return false;
}

// rapidxml

// Есть ли у xe атрибут name.
bool HasAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа float; атрибут с таким именем обязан существовать.
float GetFloatAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа bool; атрибут с таким именем обязан существовать.
bool GetBoolAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа int; атрибут с таким именем обязан существовать.
int GetIntAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа color; атрибут с таким именем обязан существовать.
Color GetColorAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа std::string; атрибут с таким именем обязан существовать.
std::string GetStringAttribute(rapidxml::xml_node<>* xe, const std::string& name);

// Получить из элемента xe атрибут типа float или вернуть значение по умолчанию
float GetFloatAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, float defaultValue);

// Получить из элемента xe атрибут типа bool или вернуть значение по умолчанию
bool GetBoolAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, bool defaultValue);

// Получить из элемента xe атрибут типа int или вернуть значение по умолчанию
int GetIntAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, int defaultValue);

// Получить из элемента xe атрибут типа color или вернуть значение по умолчанию
Color GetColorAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, Color defaultValue);

// Получить из элемента xe атрибут типа std::string или вернуть значение по умолчанию
std::string GetStringAttributeOrDef(rapidxml::xml_node<>* xe, const std::string& name, const std::string& defaultValue);

// Установить в элементе xe атрибут типа std::string
void SetStringAttribute(rapidxml::xml_node<>* xe, const std::string& name, const std::string& value);

// Установить в элементе xe атрибут типа bool
void SetBoolAttribute(rapidxml::xml_node<>* xe, const std::string& name, bool value);

// Установить в элементе xe атрибут типа int
void SetIntAttribute(rapidxml::xml_node<>* xe, const std::string& name, int value);

// Установить в элементе xe атрибут типа float
void SetFloatAttribute(rapidxml::xml_node<>* xe, const std::string& name, float value);

// Установить в элементе xe атрибут типа Color
void SetColorAttribute(rapidxml::xml_node<>* xe, const std::string& name, const Color& value);

// Создать объект IPoint из xml атрибутов x, y
IPoint IPointFromXml(rapidxml::xml_node<>* xe);

// Создать объект FPoint из xml атрибутов x, y
FPoint FPointFromXml(rapidxml::xml_node<>* xe);

// Создать объект IRect из xml атрибутов x, y, width, height
IRect IRectFromXml(rapidxml::xml_node<>* xe);

// Создать объект FRect из xml атрибутов xStart, yStart, xEnd, yEnd
FRect FRectFromXml(rapidxml::xml_node<>* xe);

// Создаёт новый узел
rapidxml::xml_node<>* NewNode(rapidxml::xml_node<>* xe, const char* name, const char* value = NULL);

template <class T>
inline bool QueryAttribute(rapidxml::xml_node<>* elem, const std::string& attrName, T& attrValue)
{
	if (elem->first_attribute(attrName.c_str())) {
		attrValue = utils::lexical_cast<T>(elem->first_attribute(attrName.c_str())->value());
		return true;
	}

	return false;
}

template <>
inline bool QueryAttribute(rapidxml::xml_node<>* elem, const std::string& attrName, std::string& attrValue)
{
	if (elem->first_attribute(attrName.c_str())) {
		attrValue = elem->first_attribute(attrName.c_str())->value();
		return true;
	}
	return false;
}

// Долгоживущий rapidxml::xml_document
struct RapidXmlDocument : public RefCounter
{
	std::string filename;
	rapidxml::file<char> file;
	rapidxml::xml_document<char> doc;

	RapidXmlDocument(const std::string &name)
		: filename(name)
		, file(filename.c_str())
	{
		doc.parse<rapidxml::parse_default>(file.data());
	}

	void Reload() {
		file = rapidxml::file<char>(filename.c_str());
		doc.parse<rapidxml::parse_default>(file.data());
	}

	rapidxml::xml_node<> *first_node() const {
		return doc.first_node();
	}
};

typedef boost::intrusive_ptr<RapidXmlDocument> RapidXmlDocumentPtr;

} // namespace Xml

#endif // __UTILS_XML_H__
