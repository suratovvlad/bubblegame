#ifndef __UTILS_UTILS_H__
#define __UTILS_UTILS_H__

#pragma once

#include "platform.h"
#include "Utils/IPoint.h"
#include "Utils/Color.h"
#include "Utils/Float.hpp"
#include "Utils/Int.h"
#include "EngineAssert.h"
#include "ThreadSupport.h"

#define DECLARE_ENUM_CLASS_FLAGS(Enum) \
	inline Enum operator|(Enum lhs, Enum rhs) { return (Enum)((__underlying_type(Enum))lhs | (__underlying_type(Enum))rhs); } \
	inline Enum operator&(Enum lhs, Enum rhs) { return (Enum)((__underlying_type(Enum))lhs & (__underlying_type(Enum))rhs); } \
	inline Enum operator~(Enum e) { return (Enum)~(__underlying_type(Enum))e; } \
	inline bool operator!(Enum e) { return !(__underlying_type(Enum))e; }

namespace utils {

	FILE* fopen(const std::string& filename, const std::string& mode);
	FILE* fopen(const std::wstring& filename, const std::wstring& mode);

    // это служит для открытия сайтов в системном браузере а не то что вы подумали
    // для iOS тело определёно в Platform/iphone.mm
	void OpenPath(const std::string& sitePath);
	void GetLocalTime(SYSTEMTIME& stm);
	/// Мультиплатформенный sleep, время в миллисекундах (в тысячных долях)
	void Sleep(uint32_t msec);

	//
	// Вероятно, переводится как "Read `name=value` pair";
	// парсит строку формата `name=value`, записывает имя в name и значение в value.
	// Возвращает true, если строка в нужном формате и false в противном случае.
	//
	bool ReadNvp(const std::string& str, std::string& name, std::string& value);

	template <class Coll>
	inline void tokenize(const std::string& str, Coll &token, const std::string& separators = std::string(" /\t:,()"))
	{
		std::string input(str);
		std::string::size_type idx = 0;
		
		if ((idx = input.find_first_not_of(separators)) == std::string::npos) {
			return;
		}
		
		input = input.substr(idx);
		while ((idx = input.find_first_of(separators)) != std::string::npos) {
			token.push_back(input.substr(0, idx));
			input = input.substr(idx + 1);
			idx = input.find_first_not_of(separators);
			if (idx == std::string::npos) {
				break;
			}
			input = input.substr(idx);
		}
		
		if ((input.find_first_of(separators)) == std::string::npos) {
			token.push_back(input);
		}
	}

	bool equals(const char* a, const char* b);
	bool iequals(const char* a, const char* b);

	template <class T>
	inline T lexical_cast(const char* str);

	template <class T>
	inline T lexical_cast(const std::string& str) { return lexical_cast<T>(str.c_str()); }

	template <>
	inline float lexical_cast(const char * str)
	{
		Assert(str != NULL);
		return Float::ParseFixed(str);
	}
	
	template <>
	inline double lexical_cast(const char * str)
	{
		Assert(str != NULL);
		return Float::ParseDouble(str);
	}
	
	template <>
	inline short lexical_cast(const char * str)
	{
		Assert(str != NULL);
		return (short)Int::Parse(str);
	}
	
	template <>
	inline int lexical_cast(const char * str)
	{
		Assert(str != NULL);
		return Int::Parse(str);
	}
	
	template <>
	inline unsigned int lexical_cast(const char * str)
	{
		Assert(str != NULL);
		return Int::ParseUint(str);
	}
	
	template <>
	inline long lexical_cast(const char * str)
	{
		Assert(str != NULL);
		return Int::ParseLong(str);
	}

    template <>
    inline unsigned long lexical_cast(const char * str)
    {
        Assert(str != NULL);
        return Int::ParseLong(str);
    }

	template <>
	inline unsigned char lexical_cast(const char * str)
	{
		Assert(str != NULL);
		return (unsigned char)Int::Parse(str);
	}

	template <>
	inline bool lexical_cast(const char * str)
	{
		Assert(str != NULL);
		if (iequals(str, "true") || iequals(str, "yes") || equals(str, "1")) {
			return true;
		}
		return false;
	}

	template <>
	inline __int64 lexical_cast(const char * str)
	{
		return Int::ParseLongLong(str);
	}

	template <>
	inline std::string lexical_cast(const char * value) 
	{
		return value;
	}

	inline std::string lexical_cast(const std::string& value) {
		return value;
	}
	
	inline std::string lexical_cast(double value, int precision = 16)
	{
		std::ostringstream ss;
		ss << std::setprecision(precision) << value;
		return ss.str();
	}

	inline std::string lexical_cast(float value, int precision = 16)
	{
		std::ostringstream ss;
		ss << std::setprecision(precision) << value;
		return ss.str();
	}

	inline std::string lexical_cast(char value)
	{
		std::ostringstream ss;
		ss << (int)value;
		return ss.str();
	}

	inline std::string lexical_cast(unsigned char value)
	{
		std::ostringstream ss;
		ss << (int)value;
		return ss.str();
	}
	
	template <class T>
	inline std::string lexical_cast(const T& value)
	{
		std::ostringstream ss;
		ss << value;
		return ss.str();
	}

	bool is_char(int code);
	std::string to_char(int code);

	bool AllowAllAccess(const std::string& theFileName);
	std::string RemoveTrailingSlash(const std::string& theDirectory);

#ifdef ENGINE_TARGET_WIN32
	bool CheckForVista();
	bool CheckFor98Mill();
#endif

	/// Выводит в лог список текстур и занимаемую ими память
	void DumpTextures();
}

#endif // __UTILS_UTILS_H__
