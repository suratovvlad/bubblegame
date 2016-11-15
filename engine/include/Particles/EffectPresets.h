#ifndef __EFFECTPRESETS_H__
#define __EFFECTPRESETS_H__

#pragma once

#include "Particles/ParticleEffect.h"

/// Загруженные эффекты частиц, готовые для клонирования.
class EffectPresets {
public:
	void UploadEffect(const std::string& name);
	void ReleaseEffect(const std::string& name);

	bool LoadEffects(const std::string& filename, const std::string& group = "Common");

	bool LoadFromXml(const std::string& filename, const std::string& group);
	bool LoadFromBin(const std::string& filename, const std::string& group);

	bool SaveToXml(const std::string& filename);
	bool SaveToBin(const std::string& filename);
	
	/// Выгрузка эффектов заданной группы
	void UnloadEffectsGroup(const std::string& group);
	void ReloadBinaryEffects(const std::string& filename, const std::string& group = "Common");

	/// Возвращает прототип эффекта, если есть, иначе возвращает NULL
	ParticleEffectPtr FindEffect(const std::string &name) const;
	/// Клонирует эффект
	ParticleEffectPtr CreateEffect(const std::string& name) const;
	ParticleEffectPtr CreateEffect(const std::string& name, const FPoint& position) const;
	
	std::vector<ParticleEffectPtr>& GetEffects() { return _effects; }

    void Shutdown();

private:
	typedef std::vector<ParticleEffectPtr> Effects;

	Effects _effects;

	Render::Sheet* current_sheet;
};

extern EffectPresets effectPresets;

#endif // __EFFECTPRESETS_H__
