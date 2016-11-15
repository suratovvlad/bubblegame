#pragma once

#include "RefCounter.h"
#include "AsyncWorkingQueue.h"

class Resource;

///
/// ����� �������� ��������
///
enum class ResourceLoadMode {
	Sync, ///< ����������
	Async, ///< �����������
	Post ///< ����������
};

///
/// ��������� ��������.
///
/// ��������� ���������� ���������� � ����������� �������� ��������.
///
/// � ������-���������� ���������� ����������� ��� ������:
///	\DoLoadData ��� ����������� �������� ���������� �� ��������������� ������, ��� ���������� - �� ���������
///	\DoLoadObject ������ ���������� �� ��������� ������, �� ���� ������� ���������� � ������������ API
///	\DoUnload ������ ���������� �� ��������� ������
///
class ResourceLoader : public RefCounter
{
public:
	ResourceLoader();

	/// ���������� true �� ����� ��������
	bool IsLoading() const { return _is_loading; }

	/// ��������� ������
	void Load(Resource* resource, ResourceLoadMode mode);

	/// ��������� ������
	void Unload(Resource* resource, ResourceLoadMode mode);

	/// ��������� ����������� ��������
	void CancelLoading();

protected:
	/// ���������� (��� ����������� �������� �� ��������������� ������) ��� ������ ��������
	virtual void DoLoadData(Resource* resource) = 0;

	/// ���������� �� ��������� ������ ��� ���������� ��������
	virtual void DoLoadObject(Resource* resource) = 0;

	/// ���������� �� ��������� ������ ��� ��������
	virtual void DoUnload(Resource* resource) = 0;

private:
	/// ����������� �� ��������� ��� ��������������� ������ ��� ����������� ��������
	void StartLoad(Resource* resource);

	/// ����������� ������ �� ��������� ������
	void EndLoad(Resource* resource, bool error, const char* what);
	
	/// ����������� ������ �� ��������� ������
	void EndUnload(Resource* resource);

protected:
	AsyncWorkingQueue::ItemID _queueItemId; ///< ������������� �������� � ����������� �������

	ResourceLoadMode _mode; ///< � ����� ������ ���� ������ ��������

	bool _is_loading; ///< ���������� �� �������� ����� ������ (��������, �����������)

private:
	ResourceLoader(const ResourceLoader&);
	ResourceLoader& operator=(const ResourceLoader&);
};

typedef boost::intrusive_ptr<ResourceLoader> ResourceLoaderPtr;
