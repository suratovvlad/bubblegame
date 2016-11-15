#pragma once

#include "Resource.h"

#include <boost/unordered_set.hpp>

///
/// ������ ��������
///
class ResourceGroup : public Resource
{
public:
	ResourceGroup(const std::string& name);

	~ResourceGroup();

	const std::string& GetName() const { return _name; }

	size_t GetMemoryInUse() const { return sizeof(*this); }

	/// ��������� ������ � ������
	void Add(Resource* res);
	
	/// ������� ������ �� ������
	void Remove(Resource* res);
	
	/// ������� ��� ������� �� ������
	void RemoveAll();

	/// ���������, ���������� �� ��������� ������ � ������
	bool Contains(const Resource* res) const;

	/// ���������, ���������� �� ��������� �� ����� ������ � ������
	bool Contains(const std::string& name) const;

	/// ��������� ��������� ���������, �������������� ������
	template<typename Container>
	void GetResources(Container& resources) const {
		resources.reserve(resources.size() + _resources.size());
		for (Resources::const_iterator it = _resources.begin(); it != _resources.end(); ++it) {
			resources.push_back((*it).get());
		}
	}

protected:
	void GroupLoad(ResourceLoadManager& glm);

	void GroupUnload(ResourceLoadManager& glm);

	void Load(ResourceLoadMode load_mode = ResourceLoadMode::Post);

	void Unload(ResourceLoadMode load_mode = ResourceLoadMode::Post);

	void SetUseCount(int use_count, ResourceLoadMode load_mode);

private:
	std::string _name;

	typedef boost::unordered_set<ResourcePtr> Resources;

	Resources _resources; ///< ��������� �������� ��������
};

typedef boost::intrusive_ptr<ResourceGroup> ResourceGroupPtr;
