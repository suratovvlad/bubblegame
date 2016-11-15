#ifndef __CORE_APPLICATIONBASE_H__
#define __CORE_APPLICATIONBASE_H__

#pragma once

#include "Core/Timer.h"


namespace Core
{

enum class SleepPolicy
{
	Allow, // win, android - sleep используется для ограничения fps
	Disallow // ios, mac - ограничение fps делается без sleep
};

class Application;

class ApplicationBase
{
public:

	bool isPaused;

	Timer timer;

	ApplicationBase();
	virtual ~ApplicationBase();

	// Вызывается, когда загружена очередная порция ресурсов
	void UpdateLoadScreen();

	// Нарисовать один кадр
	void MainLoopContent();

	// вызвать задержку, чтобы ограничить fps до запланированного значения (для андроида и win)
	void WaitForFixedFpsOrLoadResources(SleepPolicy sleepPolicy);

	void Draw();

	// чистка ресурсов
	void Shutdown();

	// Вернуть текущий fps
	int GetCurrentFps() { return _currentFps; }

	// Установить(true)/снять(false) паузу
	void SetPause(bool pause);

	// Сказать, что приложение загружено.
	void SetLoaded() { _loading = false; }

	bool IsLoading() const { return _loading; } // устанавливается из игры, может устанавливаться после проверки доступности сервера и т.д.

	bool AllResourcesIsLoaded(); // формальная проверка загрузчика ресурсов

	uint32_t GetResourceCounter() const { return _resourceCounter; }
	uint32_t GetLoadingCounter() const { return _loadingCounter; }

	// выполнить функцию в главном потоке
	void RunInMainThread(boost::function<void()> func);

	void UpdateMessageQueue();
	void UpdateAsyncWorkingQueue();

	// дождаться загрузки запланированных ресурсов
	void WaitLoading();

	void RunMappedCommand(int key);

protected:

	int _currentFps;
	int _fpsCounter;
	float _fpsTimer;
	uint32_t _resourceCounter;
	uint32_t _loadingCounter;

	std::string _keyMap[91];

	void InitInternal();

	// регистрация lua-типов
	virtual void ScriptMap();
	// регистрация классов в фабрике
	virtual void RegisterTypes();

private:

	bool _loading;
		// Загружаемся ли;
		// этот флаг нужен во время загрузки, чтобы:
		// * игнорировать паузу;
		// * жестко выходить по требованию пользователя.

	float _dt_real;

	float _sleep_time;

	boost::asio::io_service _io_service;

	void LoadKeyMap();
};

extern Application *appInstance;

} // namespace Core

#endif // __CORE_APPLICATIONBASE_H__
