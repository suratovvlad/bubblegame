#ifndef __VIRTUALFILESYSTEM_H__
#define __VIRTUALFILESYSTEM_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "IO/FileSystem.h"
#include "RefCounter.h"

namespace IO {

/// Виртуальная файловая система.
/// Предоставляет однородный способ доступа к ресурсам приложения.
///
/// Все пути указываются относительно корневой точки монтирования систем.
/// Недопустимо использованиt абсолютных путей. Для чтения произвольных файлов на диске
/// наподобие /Users/xxxx/Library/... следует использовать fopen и аналогичные функции.
class VirtualFileSystem : public RefCounter {
public:
	VirtualFileSystem();

	/// Устанавливает директорию для записи, с которой будут работать функции OpenWrite/OpenUpdate
	void SetWriteDirectory(const std::string& dir);

	/// Возвращает директорию для записи
	const std::string& GetWriteDirectory() const;

	/// Монтирует файловую систему.
	/// Поиск файла осуществляется в порядке монтирования файловых систем.
	void Mount(FileSystem* fs);

	/// Монтирует директорию с файлами на диске
	void MountDirectory(const std::string& path);

	/// Монтирует zip архив
	void MountZip(const std::string& filename, const std::string& innerPath);

	/// Проверяет существование файла
	bool FileExists(const std::string& filename) const;

	/// Ищет файлы по маске
	void FindFiles(const std::string& filespec, std::vector<std::string>& result) const;

	/// Возвращает время последней записи файла
	time_t GetLastWriteTime(const std::string& filename) const;

	/// Удаляет файл из директории для записи
	void RemoveFile(const std::string& filename);

	/// Открывает файл для чтения, сначала проверяя директорию для записи
	InputStreamPtr OpenRead(const std::string& filename);

	/// Открывает файл для записи в директории для записи
	OutputStreamPtr OpenWrite(const std::string& filename);

	/// Открывает файл для обновления (не удаляет содержимое) в директории для записи
	StreamPtr OpenUpdate(const std::string& filename);

private:
	typedef std::list<FileSystemPtr> FileSystems;

	FileSystems _systems;

private:
	DISALLOW_COPY_AND_ASSIGN(VirtualFileSystem);
};

} // namespace IO


namespace Core {
	extern IO::VirtualFileSystem fileSystem;
}

#endif // __VIRTUALFILESYSTEM_H__
