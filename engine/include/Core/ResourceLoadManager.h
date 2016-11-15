#pragma once

#include "Core/Resource.h"
#include "ThreadSupport.h"

#include <boost/unordered_map.hpp>

///
/// Менеджер групповой загрузки/выгрузки ресурсов.
///	
/// Устраняет лишние выгрузки/загрузки во время массовой перезагрузки ресурсов.
///
/// Использование:
///
/// ResourceLoadManager lm;
/// lm.Load(...);
/// lm.Unload(...);
/// lm.Commit();
///
class ResourceLoadManager
{
public:
	ResourceLoadManager();

	explicit ResourceLoadManager(ResourceLoadMode mode);

	virtual ~ResourceLoadManager();

	/// Планирует ресурс на загрузку
	void Load(Resource* res);
	
	/// Планирует ресурс на выгрузку
	void Unload(Resource* res);
	
	/// Применяет изменения
	void Commit();

	/// Отменяет изменения
	void Rollback();

	/// Проверяет, находится ли указанный ресурс под управлением менеджера
	bool Find(Resource* res) const;

private:
	ResourceLoadManager(const ResourceLoadManager&);
	ResourceLoadManager& operator=(const ResourceLoadManager&);
	//
	// Запретить копирование и присваивание

	typedef boost::unordered_map<ResourcePtr, int> ResourceMap;

	ResourceMap _resources; ///< Словарь "ресурс -> суммарное значение счётчика использования"

	ResourceLoadMode _mode; ///< Режим загрузки (синхронный, асинхронный)

	mutable MUTEX_TYPE _mutex;
};

namespace Core {
	extern ResourceLoadManager resourceLoadManager;
}
