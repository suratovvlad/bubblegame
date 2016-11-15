#ifndef __SKINNEDMESH_H__
#define __SKINNEDMESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/Mesh.h"
#include "SceneGraph/BoneContent.h"
#include "Utils/Vector3.h"

#include <boost/intrusive_ptr.hpp>

namespace SceneGraph {

typedef boost::intrusive_ptr<class SkinnedMesh> SkinnedMeshPtr;

///
/// Скелетный меш.
///
class SkinnedMesh : public Mesh {
public:
	typedef std::vector<BoneContentPtr> BonesContent;
	typedef std::vector<BoneContent::Weights> VertexWeights;
	
	MeshPtr Clone();
		/// Клонирует экземпляр объекта
	
	size_t GetMemoryInUse() const;
	
	void AddBoneContent(BoneContentPtr content);
		/// Добавляет веса вершин для кости
	
	BonesContent& GetBonesContent();
		/// Возвращает коллекцию весов вершин меша
	
	void LoadData();
		/// Загружает данные меша в аппаратные буферы
	
	void UnloadData();
		/// Выгружает данные и освобождает аппаратные буферы
	
	void Draw();
		/// Рисует себя
	
	AxisAlignedBoundingBox GetBoundingBox() const;
		/// Возвращает ограничивающий параллелепипед
	
	static SkinnedMeshPtr Create();
		/// Создаёт объект меша, но не заполняет его данными

	boost::shared_ptr<VertexWeights>& GetVertexWeights();

protected:
	SkinnedMesh();
	
	SkinnedMesh(const SkinnedMesh& rhs);
	
	SkinnedMesh& operator=(const SkinnedMesh& rhs);
		/// Копирование запрещено
	
	void UpdateBoneMatrices() const;
		/// Обновляет матрицы смещения костей

protected:
	BonesContent _bonesContent;
		/// Кости, к которым привязан данный меш
	
	boost::shared_ptr<VertexWeights> _vertexWeights;
		/// Веса вершин, сформированные для блендинга костей
};

} // namespace SceneGraph

#endif // __SKINNEDMESH_H__
