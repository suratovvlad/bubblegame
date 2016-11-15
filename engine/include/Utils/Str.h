#ifndef _UTILS_STR_H_
#define _UTILS_STR_H_

namespace utils {

/// Статический класс, содержащий функции работы со значениями типа std::string
class String
{
public:
	/// Чтение строки из файла до перевода строки (который не возвращается частью строки)
	/// или до конца файла. Если уже конец файла - будет выдана пустая строка
	static std::string ReadLine(FILE *f);

	/// Если head является началом s, то оно отрезается и выдаётся true,
	/// в противном случае с s ничего не происходит и выдаётся false.
	static bool IsHeadCut(std::string &s, const char *head);

	/// заменяет слеши \ на вот такие / и убирает двойные, тройные и прочие
	static std::string SwapSlashes(const std::string& str);

	/// заменяет слеши / на вот такие \ и убирает двойные, тройные и прочие
	static std::string ReverseSwapSlashes(const std::string& str);

	/// возвращает имя файла без расширения 
	static std::string FilenameWithoutExtension(const std::string& filename);
	
	/// заменяет такие подстановки в имени пути, как . и ..
	static std::string CanonicalizePath(const std::string& path);

	static std::string ToLower(const std::string& str);

	static std::string ToUpper(const std::string& str);

	/// отсекание от концов строки пробелов (или других заданных символов)
	static std::string Trim(const std::string& str, char ch = ' ');

	/// разбивание одной строки на массив подстрок по указанному разделителю
	static std::vector<std::string> Split(const std::string& str, char ch, bool autotrim = false);

	static std::string Pad(const std::string& str, const std::string& pad, bool not_first_line = false);
    
    static std::string Replace( const std::string& str, const std::string& from, const std::string& to);
	
	/// заменяет в строке str все подстроки from на to
	static std::string ReplaceAll( const std::string& str, const std::string& from, const std::string& to);

	/// Возвращает true, если строка str начинается со строки start
	static bool StartsWith(const std::string &str, const std::string &start);

	/// Возвращает true, если строка str заканчивается строкой end
	static bool EndsWith(const std::string &str, const std::string &end);

	/// Добавляет перечисленные в строке группы ресурсов в коллекцию
	static void MergeGroups(const std::string& groups, std::set<std::string>& result);
};

} // namespace utils

#endif
