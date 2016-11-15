#ifndef _CORE_SCREEN_H_
#define _CORE_SCREEN_H_

#include <boost/function.hpp>

class Layer;
class Message;

namespace Core
{

///
/// Экран
///
class ScreenImpl 
{
public:
	/// тип эффекта замещения
	/// описание по битам:
    /// 11 \               | 000 - linear, 001 - bounce, 010 - quad, 011 - elastic, 
    /// 10  } easing curve | 100 - ?  , 101 - ?  , 110 - ?  , 111 - ? 
	/// 9  /               |
	/// 8 - time, 0 - 0.5s, 1 - 1.0s
	/// 7 - enable alpha
	/// 6 - enable zoom
	/// 5 - enable move
	/// 4 - reserved
	/// 3 - reserved
	///                  move enabled                                  zoom enabled
	/// 2 \  000 - move up, 001 - up-right, 010 - right    | 000 - zoom out, 001 - zoom in, 
	/// 1  } 011 - right-down, 100 - down, 101 - down-left | 010 - big zoom out, 011 - small zoom in
	/// 0 /  110 - left, 111 - left-up                     | 1xx - zoom with rotate
	enum {
        FADE_EASE_ELASTIC = 0x0600,
        FADE_EASE_QUAD = 0x0400,
        FADE_EASE_BOUNCE = 0x0200,
        FADE_EASE_LINEAR = 0x0000,
		FADE_EASING_MASK = 0x0e00,
		FADE_LONGTIME = 0x0100,
		FADE_ALPHA = 0x0080,
		FADE_ZOOM  = 0x0040,
		FADE_MOVE  = 0x0020,
		FADE_MODE_7 = 0x0007,
		FADE_MODE_6 = 0x0006,
		FADE_MODE_5 = 0x0005,
		FADE_MODE_4 = 0x0004,
		FADE_MODE_3 = 0x0003,
		FADE_MODE_2 = 0x0002,
		FADE_MODE_1 = 0x0001,
		FADE_MODE_0 = 0x0000,
		FADE_IMMEDIATELY = 0
	};

	ScreenImpl();
	
	void ProcessMessage(const Message& message); /// Обработать сообщение
	void ProcessMessages(); /// Обработать отложенные сообщения (вызывается из application)
	
	///
	/// Функция рисования
	///
	void Draw();
	
	/// Отрисовать только нижние слои
	void DrawLowerLayers();
	/// Отрисовать только верхние слои (те которые в эффектах, они рисуются без альфы и прочих бантиков)
	void DrawUpperLayers();
	
	///
	/// Вернуть следующий за верхним слой (проверка существует-ли он на совести вызывающего)
	///
	Layer* GetSecondLayer() const;
	
	///
	/// Вернуть верхний слой (проверка существует-ли он на совести вызывающего)
	///
	Layer* GetTopLayer() const;
	Layer* GetTopMouseOpaqueLayer() const;

    ///
	/// Вернуть слой следующий за текущим (проверка существует-ли он на совести вызывающего)
	///
	Layer* GetLayerNextTo(const std::string& layerName) const;

    ///
	/// Вернуть имя слоя следующего за текущим (проверка существует-ли он на совести вызывающего)
	///    
    std::string GetLayerNameNextTo(const std::string& layerName) const;
    
	///
	/// Очистить экран
	///
	void Clear();
	
	///
	/// Затолкать слой в стек
	///
	void pushLayer(Layer* layer);
	void pushLayer(const std::string& layerName);

	void pushLayerBefore(const std::string& layerName, const std::string& beforeLayerName);
	void pushLayerAfter(const std::string& layerName, const std::string& afterLayerName);


	/// Удалять слои с низа стека до тех пор, пока не встретится указанный слой
	void popBackgroundUntilLayer(Layer* layer);
	void popBackgroundUntilLayer(const std::string& layerName);
	
	/// Асинхронно загружает группы ресурсов слоя, после чего вызывает событие
	void loadGroupsAsync(Layer* layer, const boost::function<void(Layer*)>& callback);
	
	/// Заменить весь текущий стек на заданный слой (fadeType - эффект перехода)
	/// По окончании перехода вызывается заданная lua функция
	void fadeToLayer(Layer* layer, const std::string& luaFunc = "", int fadeType = 0);
	void fadeToLayer(const std::string& layerName, const std::string& luaFunc = "", int fadeType = 0);
	
	/// Асинхронный вариант функций. Не блокируют выполнение,
	/// а ставят фактический вызов функции в очередь после загрузки ресурсов
	void fadeToLayerAsync(Layer* layer, const std::string& luaFunc = "", int fadeType = 0);
	void fadeToLayerAsync(const std::string& layerName, const std::string& luaFunc = "", int fadeType = 0);
	
	/// Добавить в стек заданный слой (fadeType - эффект добавления)
	/// По окончании добавления вызывается заданная lua функция
	void appendLayer(Layer* layer, const std::string& luaFunc = "", int fadeType = 0);
	void appendLayer(const std::string& layerName, const std::string& luaFunc = "", int fadeType = 0);
	
	/// Асинхронный вариант функций. Не блокируют выполнение,
	/// а ставят фактический вызов функции в очередь после загрузки ресурсов
	void appendLayerAsync(Layer* layer, const std::string& luaFunc = "", int fadeType = 0);
	void appendLayerAsync(const std::string& layerName, const std::string& luaFunc = "", int fadeType = 0);
	
	/// Убрать из стека верхний слой (fadeType - эффект убирания)
	/// По окончании убирания вызывается заданная lua функция
	void eliminateLayer(const std::string& luaFunc = "", int fadeType = 0);

	/// Убрать из стека N верхних слоёв (fadeType - эффект убирания)
	/// По окончании убирания вызывается заданная lua функция
	void eliminateLayers(int n, const std::string& luaFunc = "", int fadeType = 0);

	/// Убрать из стека слой с заданным названием (fadeType - эффект убирания)
	/// По окончании убирания вызывается заданная lua функция
	void eliminateLayer(const std::string& layerName, const std::string& luaFunc = "", int fadeType = 0);
	
	/// Установить данный слой для отладочной информации. Этот слой будет получать копии всех сообщений.
	/// Допускается передавать null.
	void setDebugLayer(Layer* layer);
	void setDebugLayer(const std::string& layerName);
	///
	/// Вернуть имя верхнего лейера
	/// (не рекомендуется использовать,
	/// в большинствве случаев лучше вызывать GetTopLayer())
	///
	std::string getMainLayerName() const;
	
	///
	/// Выплюнуть слой
	///
	void popLayer();
	
	///
	/// Реакция на течение времени
	///
	void Update(float dt);

	///
	/// Удаляет первый (ближайший к игроку) лейер с таким именем
	///
	void RemoveLayer(const std::string& layerName);

	///
	/// сохранить слои, которые находятся на экране
	///
	void SaveLayers();

	///
	/// вернуть сохранённые слои
	///
	void RestoreLayers();
	
	void SetScaleToAllLayers(float scale);
	bool isLayerOnScreen(const std::string &layerName);
	
	/// Доступен ли слой для событий, то есть все слои над ним - transparent.
	bool isLayerAccessible(Layer* layer) const;
	bool isLayerAccessible(const std::string &layerName) const;
	
	/// Включён ли режим альтернативных слоёв
	bool isAlternative() const;
	/// Включить/выключить режим альтернативных слоёв
	void setAlternative(bool alternative);
	
	/// Обработка мышы и клавиатуры
	void MouseMove(const IPoint& mousePos);
	/// Обработка мышы и клавиатуры
	void MouseDown(const IPoint& mousePos);
	/// Обработка мышы и клавиатуры
	void KeyPress(int keyCode);
	/// Обработка мышы и клавиатуры
	void MouseUp(const IPoint& mousePos);
	/// Обработка мышы и клавиатуры
	void MouseWheel(int delta);
    /// Обработка мышы и клавиатуры
    void MouseCancel();
    
	void PinchBegan(float scale, const IPoint &position);
	void PinchChanged(float scale, const IPoint &position);
	void PinchEnded();
    
	/// Экран не реагирует на ввод пользователя
	bool isLocked() const;
	/// Ручная блокировка/разблокировка на ввод
	void Lock();
	void Unlock();

	// Возвращает информацию о текущих слоях (для отладки)
	std::string GetDebugInfo();
	
	// Устанавливает время эффекта перехода для добавления и удаления слоев
	void SetFadeTime(float fadeTime);
	
	float GetInactivityTime() { return _inactivity_t; }
	void ResetInactivityTime(float t = 0.f) { _inactivity_t = t; }
    
    int getLayersCount() const;
	Layer* getLayer(int index) const;

private:
	typedef std::list<Layer*> Layers;
	
	/// список слоёв
	Layers _layers;
	
	Layer* _debugLayer;
	
	/// Режим обработки пачки слоёв (LayerPack::mode)
	enum {
		/// Фейд замещает собой стек
		L_REPLACE = 0, 
		/// Фэйд добавляется в стек, а не замещают его
		L_APPEND, 
		/// Фэйд убирается
		L_REMOVE
	};

	struct LayerPack {
		float fadetime;
		/// тип эффекта замещения
		/// описание по битам:
		/// 15-12 - reserved
        /// 11 \               | 000 - linear, 001 - bounce, 010 - quad, 011 - elastic, 
        /// 10  } easing curve | 100 - ?  , 101 - ?  , 110 - ?  , 111 - ? 
        /// 9  /               |
		/// 8 - time, 0 - 0.5s, 1 - 1.0s
		/// 7 - enable alpha
		/// 6 - enable zoom
		/// 5 - enable move
		/// 4 - reserved
		/// 3 - reserved
		///                  move enabled                                  zoom enabled
		/// 2 \  000 - move up, 001 - up-right, 010 - right    | 000 - zoom out, 001 - zoom in, 
		/// 1  } 011 - right-down, 100 - down, 101 - down-left | 010 - big zoom out, 011 - small zoom in
		/// 0 /  110 - left, 111 - left-up                     | 1xx - zoom with rotate
		int fadeType;
		std::string luaFunc;
		int mode;
		Layers layers;
	};
	
	typedef std::list<LayerPack> LayerPacks;

	int _lockCounter;
	LayerPacks _fadelayers;

	/// сохранённые слои
	Layers _savedLayers;
	
	/// включены альтернативные слои
	bool _alternative; 
	/// процесс замены альтернативных слоёв
	bool _alternativing;
	bool _oldAlternative;
	bool _delayedAlternative;
	
	float _fadeTime; ///< Время эффекта перехода при добавлении и удалении слоев	
	float _inactivity_t; ///< Таймер для подсчёта времени, когда игрок ничего не делает

	mutable MUTEX_TYPE _mutex;

private:
	void queueLayer(Layer* layer, const std::string& luaFunc, int fadeType, int mode);

	static void InternalDraw(const Layers& layers, float scale = 1.f, float angle = .0f);
	static std::string GetDebugLine(const Layers& layers);
};

extern ScreenImpl mainScreen;

} // namespace Core

#endif
