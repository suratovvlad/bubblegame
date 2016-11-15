#ifndef _GUIMANAGER_H_
#define _GUIMANAGER_H_

#include "Layer.h"
#include "EngineAssert.h"

namespace Core
{

	class GUIManager
	{
	public:
		typedef std::map<std::string, LayerPtr> LayerMap;

		GUIManager();
		~GUIManager();

		void addLayer(Layer* layer);

		const LayerMap& GetLayers() const;
		LayerMap& GetLayers();
		const LayerMap& GetLayersAlt() const;
		LayerMap& GetLayersAlt();
		Layer* getLayer(const std::string& name);
		Layer* getLayerAlt(const std::string& name, bool alt);

		void ReloadLayers(const std::string& filename);
		void LoadLayers(const std::string& filename);
		void LoadLayersScheduled(const std::string& filename);
		bool isLayerLoaded(const std::string& name);

		//
		// Очистить все слои
		// Должна вызываться из Application::Shutdown, таким образом,
		// все виджеты могут быть уверены, что их деструкторы вызовутся
		// _до_ разрушения статических объектов и вправе обращаться к ним.
		//
		void ClearLayers();

	private:
		LayerMap _layers;
		LayerMap _altlayers;
	};

	extern GUIManager guiManager;
}

#endif
