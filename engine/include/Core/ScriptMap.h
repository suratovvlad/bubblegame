#ifndef _CORE_SCRIPTMAP_H_
#define _CORE_SCRIPTMAP_H_

#include "types.h"
#include "Spline.h"
//////////////////////////////////////
typedef SplinePath<float> FSpline;

void InitScriptMap();

// общесистемные биндинги к Lua
namespace LuaC
{
	void LoadResourceCallback(const std::string& filename);

	void LoadEffectsCallback(const std::string& filename);
	void LoadEffectsGroupCallback(const std::string& filename, const std::string& group);
	void UnloadEffectsGroupCallback(const std::string& group);

	void StopApplicationCallback();

	void Spline_CalculateGradiendCallback(FSpline* spline, bool cycled);

	float FlerpCallback(float a, float b, float t);

	float FPeriodCallback(float t, float period);

	void ReleaseResourceGroupCallback(const std::string& group);

	void UploadResourceGroupCallback(const std::string& group);

	void ReleaseResourceCallback(const std::string& resId);

	void UploadResourceCallback(const std::string& resId);

	void LoadTextCallback(const std::string& file, bool reload = false);
	void LoadFreeTypeTextCallback(const std::string& file, bool reload = false);
	void ReloadText(const std::string& file);
	void ClearTextsCallback();

	void SetFullscreenModeCallback();

	void SetWindowedModeCallback();

	std::string GetLocalText(const std::string& id);
}

#endif
