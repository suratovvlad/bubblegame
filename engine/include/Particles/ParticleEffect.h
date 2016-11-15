#ifndef __PARTICLEEFFECT_H__
#define __PARTICLEEFFECT_H__

#pragma once

#include "Particles/ParticleSystem.h"

namespace IO {
	class BinaryReader;
	class BinaryWriter;
}

namespace Render {
	class Sheet;
}

/// Эффект из частиц.
/// Представляет собой набор систем частиц @see ParticleSystem
class ParticleEffect : public RefCounter {
public:
	ParticleEffect();
	ParticleEffect(const std::string& group);
	ParticleEffect(const ParticleEffect&);
	ParticleEffect& operator=(const ParticleEffect&);
	
	ParticleEffect* Clone() const { return new ParticleEffect(*this); }
	
	bool Load(IO::BinaryReader* d);
	bool Load(rapidxml::xml_node<>* elem);
	bool Load(rapidxml::xml_node<>* elem, int version);	// загрузка эффекта нужной версии
														// добавлено из-за загрузки эффектов НЕ через EffectPresets
	void Save(rapidxml::xml_node<>* elem);
	void Save(IO::BinaryWriter* d);

	void Update(float dt);

	void Draw(Render::SpriteBatch* batch = NULL);
	void DrawBlend(Render::SpriteBatch* batch = NULL);

	void Upload();
	void Release();

	bool isEnd() const { return ended; }
	void Kill(void) { ended = true; }
	void Finish();
	void Reset();

	// Устанавливает системам частиц флаг, с которым отключается туман на время
	// рисования частитц в режиме ADD. Флаг пока есть только для ParticleSystem
	void DisableFog(bool disable);

	float GetLocalTime() const { return localTime; }
	void SetLocalTime(float localTime_) { localTime = localTime_; }

	void Pause();
	void Continue();
	bool IsPermanent();
	void SetAlphaFactor(float alpha);
	void SetRGBFactor(float r, float g, float b);
	void SetPos(const FPoint& pos);
	void SetPos(float x, float y) { SetPos(FPoint(x, y)); }
	void SetScale(float scale_x, float scale_y = 0.0f);

public:
	int version;
	float posX, posY;
	float localTime;
	bool needTimeCount;
	bool ended;
	bool _paused;
	std::string name, group;
	Render::Sheet* sheet;

	//boost::object_pool<GradientSpline> _spline_pool;

	typedef std::vector<ParticleSystemPtr> ParticleSystems;
	ParticleSystems _systems;

public:
	static bool IsVersionSupported(int version);
};

typedef boost::intrusive_ptr<ParticleEffect> ParticleEffectPtr;

#endif // __PARTICLEEFFECT_H__
