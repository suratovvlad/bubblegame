#ifndef __BONECONTENT_H__
#define __BONECONTENT_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/SceneNode.h"
#include "Utils/Matrix4.h"
#include "RefCounter.h"

namespace SceneGraph {

typedef boost::intrusive_ptr<class BoneContent> BoneContentPtr;

///
/// ���������� ����� (���� ������ ����������� ����).
/// ���������� �������� ������ ���� � ��������� �����.
///
class BoneContent : public RefCounter {
public:
	typedef std::pair<size_t, float> Weight;
	typedef std::vector<Weight> Weights;
	
	BoneContent(SceneNode* bone, const math::Matrix4& offset);
	
	virtual BoneContentPtr Clone() const;

	virtual size_t GetMemoryInUse() const;
	
	SceneNode* GetBone() const;
		/// ���������� �����, � ������� ��������� �������
	
	void SetBone(SceneNode* bone);
		/// ������������� �����, � ������� ��������� �������
	
	const math::Matrix4& GetBoneOffset() const;
		/// ���������� ������� �������������� �� ������������ ���� � ������������ ����� � ����
	
	void SetBoneOffset(const math::Matrix4& offset);
		/// ������������� ������� �������������� �� ������������ ���� � ������������ ����� � ����
	
	const Weights& GetWeights() const;
		/// ���������� ��������� ����� ������ �����
	
	void AddWeight(const Weight& weight);
		/// ��������� ��� ������� � ���������

	AxisAlignedBoundingBox& GetBoundingBox();
		/// �������������� ������������� �����. 
private:
	SceneNode* _bone;
		/// �����, � ������� ��������� �������
	
	struct Content : public RefCounter {
		math::Matrix4 _offset;
			/// ������� ��������� �������������� �� ������������ ���� � ������������ ���� �����
		
		Weights _weights;
			/// ����� ����� ������ ��� ������ �����
		
		Content(const math::Matrix4& offset)
			: _offset(offset)
		{}
	};
	
	boost::intrusive_ptr<Content> _content;
		// ������������ ������ ��� ������������ ������������� ���������� �� ������, � �� �� ��������

	AxisAlignedBoundingBox _box;
		/// �������������� ������������� �����. ������������ � ������� Gardenscapes, �������������� ����� ������
		// TODO: ���� �� ����� ���� �� ������ ��� ��� ����������� � ���������� ���������. �� � �� ���������� � ����� ������ ��� ����� ������
};

} // namespace SceneGraph

#endif // __BONECONTENT_H__
