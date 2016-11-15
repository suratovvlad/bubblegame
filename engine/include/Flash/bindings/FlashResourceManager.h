#pragma once

#include <string>
#include <boost/intrusive_ptr.hpp>

#include "FlashEngineBinding.h"
#include "ResourceCleanup.h"

namespace Render
{
class Texture;
}

struct ISwlLibrary;
 
namespace Flash
{
struct FlashLibraryRecord;
typedef boost::intrusive_ptr<FlashLibraryRecord> FlashLibraryRecordPtr;

class FlashResourceManager: public ICleanable
{
public:
		FlashResourceManager();

		/**
		* Устанавливает путь для поиска библиотек
		*/
		void setSourcePath(const std::string& path);

		/**
		* Очищает все ресурсы, на которые больше нет ссылок
		*/
		void clean();

		/**
		* Добавляет новый источник клипов.
		* К источнику можно затем обращаться через точку "source.clip" 
		* в методах getLibraryItem и createItem
		*/
		void addSource(const std::string &_libpath, const std::string &_name);

		/**
		* Определяет, определен ли источник с именем name
		*/
		bool hasSource(const std::string& name);

		/**
		* Удаляем, для возможности пересбоки на лету
		*/
		void removeSource(const std::string& name);
		
		/**
		* Возвращает созданный по элементу библиотеки объект
		*/
		IFlashDisplayObject* createItem(const std::string& path);
		IFlashDisplayObject* maybecreateItem(const std::string& path);

		/**
		* Определяет, есть ли в билиотеке элемент path.
		* Приводит к загрузке источника.
		*/
		bool hasItem(const std::string& path);

		/**
		* Установить предел памяти для менеджера.
		* Тем не менее, менеджер может потреблять больше. Однако до заданного уровня
		* будет очищаться кэш при каждом releaseMemory
		*/
		void setMemoryLimit(int bytes);

		/**
		* Удалить неиспользуемые ресурсы
		* @param agressive уточняет, надо ли сохранять MemoryLimit неиспользуемых ресурсов
		* для дальнейшего использования
		*/
		void releaseMemory(bool agressive = false);

		void printUsed(const std::string& resourceId);

		static FlashResourceManager* instance;

private:
	FlashLibraryRecordPtr __addSource(const std::string &_libpath, const std::string &_name);
	ISwlLibrary* __getLib(const std::string& _libId);

private:
	int memoryLimit;
	int memoryConsumption;
	std::map<std::string, FlashLibraryRecordPtr> libraries;

	bool __m_hasSourcePath;
	std::string __m_sourcePath;
};

};
