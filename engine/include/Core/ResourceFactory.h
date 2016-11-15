#ifndef _RESOURCEFACTORY_H_
#define _RESOURCEFACTORY_H_

/*
 *  ResourceFactory.h
 *  Engine
 *
 */
namespace Render {
	class Texture;
}

/**
 * Наследуйте фабрику ресурсов, чтобы управлять созданием ресурсов.
 * Например, можно создавать свои анимации и текстуры, наследованные от стандартных.
 * 
 * @see resourceFactory = new ResourceFactory() в конструкторе Application.
 */
class ResourceFactory
{
public:
	virtual ~ResourceFactory() {}

	virtual void LoadResourcesXml(const std::string& filename);

	virtual void LoadFontsSwl(const std::string& itemId);

	virtual Render::Texture* CreateTexture(const std::string& filename);
};

namespace Core {
	extern ResourceFactory* resourceFactory;
}

#endif // _RESOURCEFACTORY_H_
