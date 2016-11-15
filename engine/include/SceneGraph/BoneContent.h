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
/// —одержимое кости (веса вершин конкретного меша).
/// ќпредел€ет прив€зку вершин меша к указанной кости.
///
class BoneContent : public RefCounter {
public:
	typedef std::pair<size_t, float> Weight;
	typedef std::vector<Weight> Weights;
	
	BoneContent(SceneNode* bone, const math::Matrix4& offset);
	
	virtual BoneContentPtr Clone() const;

	virtual size_t GetMemoryInUse() const;
	
	SceneNode* GetBone() const;
		/// ¬озвращает кость, к которой прив€заны вершины
	
	void SetBone(SceneNode* bone);
		/// ”станавливает кость, к которой прив€заны вершины
	
	const math::Matrix4& GetBoneOffset() const;
		/// ¬озвращает матрицу преобразовани€ из пространства меша в пространство кости в позе
	
	void SetBoneOffset(const math::Matrix4& offset);
		/// ”станавливает матрицу преобразовани€ из пространства меша в пространство кости в позе
	
	const Weights& GetWeights() const;
		/// ¬озвращает коллекцию весов вершин кости
	
	void AddWeight(const Weight& weight);
		/// ƒобавл€ет вес вершины к коллекции

	AxisAlignedBoundingBox& GetBoundingBox();
		/// ќграничивающий пр€моугольник кости. 
private:
	SceneNode* _bone;
		///  ость, к которой прив€заны вершины
	
	struct Content : public RefCounter {
		math::Matrix4 _offset;
			/// ћатрица обратного преобразовани€ из пространства меша в пространство позы кости
		
		Weights _weights;
			/// Ќабор весов вершин дл€ данной кости
		
		Content(const math::Matrix4& offset)
			: _offset(offset)
		{}
	};
	
	boost::intrusive_ptr<Content> _content;
		// Ќеизмен€емые данные при клонировании целесообразно копировать по ссылке, а не по значению

	AxisAlignedBoundingBox _box;
		/// ќграничивающий пр€моугольник кости. »спользуетс€ в проекте Gardenscapes, рассчитываетс€ извне движка
		// TODO: было бы круто если бы движок сам его поддерживал в актуальном состо€нии. Ќо € не разобралс€ в какой момент это нужно делать
};

} // namespace SceneGraph

#endif // __BONECONTENT_H__
