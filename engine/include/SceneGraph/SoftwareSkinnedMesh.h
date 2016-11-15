#ifndef __SOFTWARESKINNEDMESH_H__
#define __SOFTWARESKINNEDMESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/SkinnedMesh.h"
#include "SceneGraph/MeshData.h"

namespace SceneGraph {

typedef boost::intrusive_ptr<class SoftwareSkinnedMesh> SoftwareSkinnedMeshPtr;

///
/// Скелетный меш с программным скиннингом.
///
class SoftwareSkinnedMesh : public SkinnedMesh {
public:
	MeshPtr Clone();
		/// Клонирует экземпляр объекта
	
	size_t GetMemoryInUse() const;
	
	void LoadData();
		/// Загружает данные меша в аппаратные буферы
	
	void UnloadData();
		/// Выгружает данные и освобождает аппаратные буферы
	
	void Draw();
		/// Рисует себя

	virtual bool Hit(const math::Vector3 &base, const math::Vector3 &dir) const;
		/// Проверка попадания в модель с учетом текущей анимации модели
	
	static SoftwareSkinnedMeshPtr Create();
		/// Создаёт объект меша, но не заполняет его данными

protected:
	SoftwareSkinnedMesh();
	
	SoftwareSkinnedMesh(const SoftwareSkinnedMesh& rhs);
	
	SoftwareSkinnedMesh& operator=(const SoftwareSkinnedMesh& rhs);
		// Копирование запрещено
	
	void UpdateSkin() const;
		/// Обновляет данные в буфере вершин для нового положения костей

	void UpdateBoneMatrices() const;

private:
	typedef std::vector<math::Matrix4> Matrices;

	mutable Matrices _matrices;
	mutable Matrices _matricesOld;
		/// Массив матриц костей
	
	mutable int _differenceOfMatrices;
		/// Количество несовпадающих матриц после обновления костей
	
	mutable MeshData::Vertices _verticesCache;
};

} // namespace SceneGraph

#endif // __SOFTWARESKINNEDMESH_H__
