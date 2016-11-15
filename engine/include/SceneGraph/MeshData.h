#ifndef __MESHDATA_H__
#define __MESHDATA_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Mesh.h"
#include "AxisAlignedBoundingBox.h"
#include "RefCounter.h"

namespace SceneGraph {

///
/// Данные меша.
///
class MeshData : public RefCounter {
public:
	typedef std::vector<StaticMeshVert> Vertices;
	typedef std::vector<uint16_t> Indices;
	
	MeshData();

	MeshData(const std::string& filename, size_t offset);
	
	MeshData(size_t verticesHint, size_t indicesHint);

	size_t GetMemoryInUse() const;

	const std::string& GetFilename() const { return _filename; }

	size_t GetOffset() const { return _offset; }

	bool IsEmpty() const { return _vertices.empty(); }

	void LoadFromFile();
		/// Загружает данные из файла _filename

	void Clear();
		/// Удаляет данные
	
	void AddVertex(const StaticMeshVert& vertex);
		/// Добавляет вершину в коллекцию
	
	void AddIndex(uint16_t index);
		/// Добавляет индекс в коллекцию
	
	const Vertices& GetVertexData() const { return _vertices; }
		/// Возвращает коллекцию вершин
	
	const Indices& GetIndexData() const { return _indices; }
		/// Возвращает коллекцию индексов
	
	const AxisAlignedBoundingBox& GetBoundingBox() const { return _aabbox; }
		/// Возвращает ограничивающий параллелепипед

private:
	std::string _filename;
		/// Имя бинарного файла данных

	size_t _offset;
		/// Смещение начала данных в файле

	Vertices _vertices;
		/// Данные буфера вершин
	
	Indices _indices;
		/// Данные буфера индексов
	
	AxisAlignedBoundingBox _aabbox;
		/// Ограничивающий параллелепипед для набора точек
};

typedef boost::intrusive_ptr<MeshData> MeshDataPtr;

} // namespace SceneGraph

#endif // __MESHDATA_H__
