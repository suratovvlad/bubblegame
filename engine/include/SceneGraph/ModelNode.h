#ifndef __MODELNODE_H__
#define __MODELNODE_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/SceneNode.h"
#include "SceneGraph/Mesh.h"
#include "SceneGraph/Animation.h"

#include <list>

namespace SceneGraph {

///
/// Модель, которая может состоять из нескольких мешей и скелета.
/// Содержит набор анимаций, которые могут комбинироваться друг с другом.
///
class ModelNode : public SceneNode {
public:
	typedef boost::intrusive_ptr<ModelNode> HardPtr;
	
	typedef std::map<std::string, Animation::HardPtr> Animations;

	ModelNode(const std::string& name, SceneNode* parent, Scene* scene);
	
	ModelNode::HardPtr CloneModel() const;
	
	SceneNode::HardPtr Clone();

	size_t GetMemoryInUse() const;
	
	unsigned int GetRenderPassMask() const;
		/// Возвращает типы проходов визуализации, при которых должна производиться отрисовка узла
	
	SceneNode::HardPtr FindFrame(const std::string& name) const;
		/// Рекурсивно ищет узел среди фреймов
	
	bool AddFrame(SceneNode::HardPtr bone);
		/// Добавляет фрейм в коллекцию
	
	const Animations& GetAnimations() const;
		/// Возвращает коллекцию анимаций
	
	Animation::HardPtr GetAnimation(const std::string& name) const;
		/// Находит анимацию по имени
	
	void AddAnimation(Animation::HardPtr animation);
		/// Добавляет анимацию в коллекцию

	void SetAnimations(const Animations& animations);
		/// Подключает адаптированную копию коллекции анимаций

	void UpdateTransform();
		/// Обновляет трансформацию узла

	void Update(float dt);
		/// Реакция на течение времени
	
	void Draw() const;
		/// Рисует модель
	
	void ShowSkeleton(bool show);
		/// Отображать ли скелет
	
	void ShowBoundingBox(bool show);
		/// Отображать ли ограничивающий прямоугольник

	bool HitBoundingBox(const IPoint &mouse_pos) const;
		/// Пересекает ли указанный луч из курсора BoundingBox модели 

	bool HitModel(const IPoint &mouse_pos) const;
		/// Пересекает ли указанный луч из курсора модель

	void AddFrameInAllFrames(SceneNode::HardPtr frame);
		/// Добавить фрейм в массив всех фреймов

	void FillAllFrames();

	SceneNode::HardPtr FindFrameInAllFrames(const std::string& name);
		/// ищем фрейм в массиве всех фреймов

	void initializeAligned16Matrices();
		/// Инициализация всех матриц

	void initializeHierarchy();
		/// Инициализация массива предков и всех матриц с их указателями

	size_t AddVertexIntoTree(SceneNode::HardPtr frame, int parent);
		/// Добавить вершину в дерево, привязывая её к родителю

	void UpdateAllAbsoluteTransforms();
		

protected:
	ModelNode(const ModelNode& rhs);
	
	ModelNode& operator = (const ModelNode& rhs);
	
	void DrawSkeleton() const;
		/// Рисует скелет
	
	void DrawSkeleton(SceneNode::HardPtr node, const math::Matrix4& matParent) const;
		/// Вспомогательный метод для рекурсивного рисования скелета
	
	void DrawBoundingBox() const;
		/// Рисует ограничивающий прямоугольник

protected:
	SceneNodesMap _frames;
		/// Иерархия фреймов модели
	
	SceneNodesMap _allFrames;
		/// Собираем все фреймы в один общий массив для более быстрого поиска фрейма по имени
	
	typedef std::list<SceneNode::HardPtr> SceneNodesList;

	SceneNodesList _allFramesList;
		/// Плоский список фреймов для последовательного обновления

	std::vector<uint8_t> _aligned16Memory;
		/// Область памяти для хранения последовательности матриц,
		/// в которую сохраняется несколько матриц подряд с выравниванием в 16 байт.
		/// Сам вектор при этом не обязательно выровнен.

	std::vector<math::Matrix4*> _allOriginalMatrices;
	std::vector<math::Matrix4*> _allRelativeMatrices;
	std::vector<math::Matrix4*> _allAbsoluteMatrices;
	//std::vector<math::Matrix4*> _allPreviousRelativeMatrices; // <-- Нужно для кэша.
	/// Массивы указателей на матрицы, расположенные в _aligned16Memory.	
	
	std::vector<uint8_t> isRelativeMatrixDirty, isAbsoluteMatrixDirty;
		/// Флаги, определяющие то, какие матрицы считать "грязными" по отношению к кэшу

	std::vector<int> _parent;
		/// Вся иерархия хранится в виде дерева здесь.
		/// _parent[i] - номер предка вершины i, или -1, если это корень.

	Animations _animations;
		/// Набор анимаций модели.
		/// Модель может состоять из нескольких мешей в иерархии фреймов.
		/// Каждая анимация может включать в себя трансформации нескольких фреймов.
	
	bool _showSkeleton;
		/// Отображать ли скелет
	
	bool _showBoundingBox;
		/// Отображать ли ограничивающий прямоугольник
};

} // namespace SceneGraph

#endif // __MODELNODE_H__
