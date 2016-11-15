#pragma once

#include <Particles/EffectsContainer.h>

#include "../core/FlashDisplayObject.hpp"
#include "../core/FlashUnknown.hpp"

#include "IFlashParticleEffect.h"

class FlashParticleEffect: public FlashDisplayObject<IFlashParticleEffect>
{
BEGIN_INTERFACE_MAP()
	INTERFACE_ENTRY(IFlashDisplayObject)
	INTERFACE_ENTRY(IFlashParticleEffect)
END_INTERFACE_MAP()

public:
	FlashParticleEffect();
	virtual ~FlashParticleEffect();

	void setEffectName(const std::string& _name);
	const std::string& getEffectName();

	//------------------------------------------------------------------------------
	//
	//                            IFlashDisplayObject
	//
	//------------------------------------------------------------------------------
	void render(FlashRender& render);
	bool hitTest(float x, float y, IHitTestDelegate* hitTestDelegate);
	bool getBounds(float &,float &,float &,float &,IFlashDisplayObject *);
	bool hasUpdate(){return true;};
	void update(float dt);

	//------------------------------------------------------------------------------
	//
	//                             IFlashParticleEffect
	//
	//------------------------------------------------------------------------------
	virtual bool isEnd();
	virtual void reset();
	virtual void finish();
	virtual void pause();
	virtual void resume();

private:
	EffectsContainer container;
	ParticleEffectPtr effect;
	std::string effectName;
	bool wasDrawn;
};
