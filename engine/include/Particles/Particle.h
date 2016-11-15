#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Spline.h"

class ParticleSystem;

//  ласс частицы с динамически измен€ющимис€ свойствами.
class Particle {
public:
	Particle();
	Particle(const Particle& rhs);
	
	void SetOwner(ParticleSystem* owner) { _owner = owner; }

	void Update(float dt);
	void Reset();

	float GetOrientationAngle() const;

	size_t MemoryInUse() const;

public:
	float localTime;

	float lifeTime;
	float spinStart;

	float emitX;
	float emitY;

	float xStart;
	float yStart;

	float x, y, size, angle, v, spin, ySize;
	float red, green, blue, alpha, fps;

	float _speed;
	float _progress;
	uint16_t _currentFrame, _firstFrame, _lastFrame;

	bool isVisible;

private:
	Particle& operator=(const Particle&) = delete;

	void UpdateFrames(float dt, float normTime);
	void ResetFrames();

private:
	ParticleSystem* _owner;
	GradientSpline xSpl, ySpl, sizeSpl, angleSpl, vSpl, spinSpl, redSpl, greenSpl, blueSpl, alphaSpl, fpsSpl, ySizeSpl;
};

#endif // __PARTICLE_H__
