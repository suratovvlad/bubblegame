#ifndef __CONTENTPROVIDER_H__
#define __CONTENTPROVIDER_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/ModelNode.h"
#include "RefCounter.h"

#include <boost/intrusive_ptr.hpp>

namespace Render {
	class Texture;
}

namespace SceneGraph {

class Scene;

///
/// Базовый класс для провайдеров контента.
///
class ContentProvider : public RefCounter {
public:
	typedef boost::intrusive_ptr<ContentProvider> HardPtr;
	
	ContentProvider();
	
	virtual ~ContentProvider();
	
	virtual ModelNode::HardPtr LoadModel(const std::string& filename) = 0;
		/// Загружает модель из файла
};

} // namespace SceneGraph

#endif // __CONTENTPROVIDER_H__
