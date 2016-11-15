#pragma once

#include "Core/Resource.h"
#include "ThreadSupport.h"

#include <boost/unordered_map.hpp>

///
/// �������� ��������� ��������/�������� ��������.
///	
/// ��������� ������ ��������/�������� �� ����� �������� ������������ ��������.
///
/// �������������:
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

	/// ��������� ������ �� ��������
	void Load(Resource* res);
	
	/// ��������� ������ �� ��������
	void Unload(Resource* res);
	
	/// ��������� ���������
	void Commit();

	/// �������� ���������
	void Rollback();

	/// ���������, ��������� �� ��������� ������ ��� ����������� ���������
	bool Find(Resource* res) const;

private:
	ResourceLoadManager(const ResourceLoadManager&);
	ResourceLoadManager& operator=(const ResourceLoadManager&);
	//
	// ��������� ����������� � ������������

	typedef boost::unordered_map<ResourcePtr, int> ResourceMap;

	ResourceMap _resources; ///< ������� "������ -> ��������� �������� �������� �������������"

	ResourceLoadMode _mode; ///< ����� �������� (����������, �����������)

	mutable MUTEX_TYPE _mutex;
};

namespace Core {
	extern ResourceLoadManager resourceLoadManager;
}
