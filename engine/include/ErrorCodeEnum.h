#ifndef __ERRORCODEENUM_H__
#define __ERRORCODEENUM_H__

#pragma once

#include <system_error>

#include <boost/preprocessor.hpp>

/*
������� ������ ������������ � ������ � ���������� ������:

������������� X-Macros ��������� �������� ����� � �������� ������������ � ����� �����
� ����� �������������� ��������� ������ ��� ��������� ���������� �������� � ����, � �����
�������� ������ ���������������� �������� � �������� ��������� ���������� �������������
������� ��� � ���������� ������ ��� ���������� ��� �������� ��������.

#define ERROR_CODE_ENUM \
	(ErrorCode, \
	((Success, "success")) \
	((Error1, "error 1 description")) \
	((Error2, "error 2 description")) \
	((Error3, "error 3 description")) \
	((Error4, "error 4 description")) \
	((Error5, "error 5 description")))

����������:

��������� �������� 0 � std::error_code ������ ��������� ����������� ������,
�� ������ ��������� ������������ ������ ���� ���, ���������� ���������� ������,
�.�. �������� �������� �� ������������� ���� � ������ ������ ����� 0.

// � .h �����
DECLARE_ERROR_CODE_ENUM(ERROR_CODE_ENUM)

// � .cpp �����
IMPLEMENT_ERROR_CODE_ENUM(ERROR_CODE_ENUM)

// �������������:

void some_function(std::error_code& ec) {
	...
	ec = ErrorCode::Error3;
}

std::error_code ec;	
some_function(ec);

if (ec) {
	(1) puts(ec.message().c_str());

	try {
		(2.1) throw std::system_error(ec, "some_function() returned error!");
	} catch (const std::exception& ex) {
		(2.2) puts(ex.what());
	}
}

*/

// �������������� ������������ � ������ ������
#define DECLARE_ERROR_CODE_ENUM_HELPER(_Name, _Enumerators) \
	enum class _Name { \
		BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_WITH_DESCRIPTION_VALUE, _, _Enumerators) \
	}; \
	/* ����� MyEnumToString() */ \
	const char* BOOST_PP_CAT(_Name, ToString)(_Name e); \
	/* ��������� std::error_code */ \
	std::error_code make_error_code(_Name e); \
	std::error_condition make_error_condition(_Name e); \
	namespace std { \
		template <> struct is_error_code_enum<_Name> : public true_type{}; \
	}

// ���������� ������� ��������� std::error_code
#define IMPLEMENT_ERROR_CODE_ENUM_HELPER(_Name, _Enumerators) \
	const char* BOOST_PP_CAT(_Name, ToString)(_Name e) { \
		switch (e) { \
			BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_WITH_DESCRIPTION_TOSTRING_CASE, _Name, _Enumerators) \
			default: return "Unknown " BOOST_PP_STRINGIZE(_Name) " value"; \
		} \
	} \
	class BOOST_PP_CAT(_Name, CategoryImpl) : public std::error_category { \
	public: \
		virtual const char* name() const BOOST_NOEXCEPT override { return BOOST_PP_STRINGIZE(_Name); } \
		virtual std::string message(int ev) const override { return BOOST_PP_CAT(_Name, ToString)((_Name)ev); } \
	}; \
	const std::error_category& BOOST_PP_CAT(_Name, Category)() { \
		static BOOST_PP_CAT(_Name, CategoryImpl) instance; \
		return instance; \
	} \
	std::error_code make_error_code(_Name e) { return std::error_code(static_cast<int>(e), BOOST_PP_CAT(_Name, Category)()); } \
	std::error_condition make_error_condition(_Name e) { return std::error_condition(static_cast<int>(e), BOOST_PP_CAT(_Name, Category)()); }

#define DEFINE_ENUM_WITH_DESCRIPTION_VALUE(r, data, elem) \
	BOOST_PP_TUPLE_ELEM(2, 0, elem),

#define DEFINE_ENUM_WITH_DESCRIPTION_TOSTRING_CASE(r, data, elem) \
	case data::BOOST_PP_TUPLE_ELEM(2, 0, elem): return BOOST_PP_TUPLE_ELEM(2, 1, elem);

// ������� ��� �������������� � ���������� ������������ � ������ ������
#define DECLARE_ERROR_CODE_ENUM(ENUM) DECLARE_ERROR_CODE_ENUM_HELPER(BOOST_PP_TUPLE_ELEM(2, 0, ENUM), BOOST_PP_TUPLE_ELEM(2, 1, ENUM))
#define IMPLEMENT_ERROR_CODE_ENUM(ENUM) IMPLEMENT_ERROR_CODE_ENUM_HELPER(BOOST_PP_TUPLE_ELEM(2, 0, ENUM), BOOST_PP_TUPLE_ELEM(2, 1, ENUM))

#endif // __ERRORCODEENUM_H__
