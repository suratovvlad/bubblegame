#ifndef __GPUSKINNEDMESH_H__
#define __GPUSKINNEDMESH_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SkinnedMesh.h"
#include "Render/ShaderProgram.h"

#include <boost/intrusive_ptr.hpp>

namespace SceneGraph {

///
/// Специальная структура матрицы кости для аппаратного скиннинга.
/// За счёт удаления одного столбца можно вычислять больше костей в шейдере.
///
/** !!! Неудачное название матрицы !!! **/
/** !!! Реально она 3x4, а не 4x3  !!! **/
class Matrix4x3
{
public:
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
		};
		float m[3][4];
		float v[12];
	};

	// Оператор присваивания транспонирует матрицу 4x4 и берёт только верхние 3 ряда матрицы
	Matrix4x3& operator=(const math::Matrix4& source) {
		//_11 = source._11; _12 = source._21; _13 = source._31; _14 = source._41;
		//_21 = source._12; _22 = source._22; _23 = source._32; _24 = source._42;
		//_31 = source._13; _32 = source._23; _33 = source._33; _34 = source._43;
		for ( int j = 0; j < 4; j ++ )
			for ( int i = 0; i < 3; i ++ )
				m[i][j]=source.m[j][i];

		return (*this);
	}
		
};

// Функция перемножает A*B, затем транспонирует матрицу 4x4 и берёт только верхние 3 ряда матрицы
// Все это делается сразу, то есть сама результирующая матрица не расчитывается полностью
Matrix4x3 getMatrix4x3fromMatrix4Product(const math::Matrix4 &,const math::Matrix4 &);
//void getMatrix4x3fromMatrix4Product(const math::Matrix4 &, const math::Matrix4 &, Matrix4x3 &);

typedef boost::intrusive_ptr<class GPUSkinnedMesh> GPUSkinnedMeshPtr;

///
/// Скелетный меш с аппаратным скиннингом на GPU.
///
class GPUSkinnedMesh : public SkinnedMesh {
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
		/// проверка попадания в модель с учетом текущей анимации модели

	static GPUSkinnedMeshPtr Create();
		/// Создаёт объект меша, но не заполняет его данными
	
protected:
	GPUSkinnedMesh();
	
	GPUSkinnedMesh(const GPUSkinnedMesh& rhs);
	
	GPUSkinnedMesh& operator=(const GPUSkinnedMesh& rhs);
		// Запрещаем копирование
	
private:
	Render::ShaderProgram *_program;
		/// Шейдер для аппаратного скиннинга
	std::unique_ptr<Matrix4x3[]> _bones;
		/// Массив матриц костей
};

} // namespace SceneGraph

#endif // __GPUSKINNEDMESH_H__
