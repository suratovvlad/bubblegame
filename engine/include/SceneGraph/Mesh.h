#ifndef __MESH_H__
#define __MESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "SceneGraph/SceneNode.h"
#include "SceneGraph/Material.h"
#include "Utils/Vector3.h"
#include "RefCounter.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace SceneGraph {

typedef boost::intrusive_ptr<class MeshData> MeshDataPtr;
	// Здесь определяется дублирующий тип умного указателя для класса MeshData,
	// т.к. мы не можем включить здесь весь заголовочный файл во имя предотвращения
	// циклической зависимости.

typedef boost::intrusive_ptr<class Mesh> MeshPtr;

///
/// Меш.
///
class Mesh : public RefCounter {
public:
	virtual MeshPtr Clone();
		/// Клонирует экземпляр объекта
	
	virtual size_t GetMemoryInUse() const;
	
	boost::shared_ptr<Render::VertexBuffer> GetVertices() const;
		/// Возвращает буфер вершин
	
	boost::shared_ptr<Render::IndexBuffer> GetIndices() const;
		/// Возвращает буфер индексов
	
	MaterialPtr GetMaterial() const;
		/// Возвращает материал меша
	
	void SetMaterial(MaterialPtr material);
		/// Устанавливает материал меша
	
	const MeshDataPtr GetData() const;
		/// Возвращает данные меша
	
	void SetData(MeshDataPtr data);
		/// Устанавливает данные меша

	void SetRenderTarget(Render::Target *target);
	
	virtual void LoadData();
		/// Загружает данные меша в аппаратные буферы
	
	virtual void UnloadData();
		/// Выгружает данные и освобождает аппаратные буферы
	
	virtual void Draw();
		/// Отрисовывает себя

	virtual bool Hit(const math::Vector3 &base, const math::Vector3 &dir) const;
		/// Проверка попадания в меш

	virtual AxisAlignedBoundingBox GetBoundingBox() const;
		/// Возвращает ограничивающий параллелепипед
	
	static MeshPtr Create();
		/// Создаёт объект меша, но не заполняет его данными

protected:
	Mesh();
	
	Mesh(const Mesh& rhs);
	
	Mesh& operator=(const Mesh& rhs);
		// Копирование запрещено

protected:
	boost::shared_ptr<Render::VertexBuffer> _vertices;
		/// Буфер вершин
	
	boost::shared_ptr<Render::IndexBuffer> _indices;
		/// Буфер индексов
	
	MaterialPtr _material;
		/// Материал меша
	
	MeshDataPtr _data;
		/// Данные меша
};

} // namespace SceneGraph

#endif // __MESH_H__
