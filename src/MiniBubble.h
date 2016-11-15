#ifndef __MINIBUBBLE_H__
#define __MINIBUBBLE_H__

#pragma once

#include <PlayrixEngine.h>
#include <Utils\random.hpp>

class BubbleColor;

class MiniBubble
{

private:

	float speed_x;
	float speed_y;
	float m_maxSpeed;
	float m_minSpeed;
	
	float m_distance_x;
	float m_distance_y;

	Render::Texture* m_texture;

	bool m_isFirstDraw;

	EffectsContainer _effCont;

	std::string m_color;
	float m_scale;
	float m_radius;
	unsigned int m_thinningParticles;
	unsigned int m_thinningSettings;
	float m_particlesPositionCoef;

	std::list<ParticleEffectPtr> _eff_list;
public:
	explicit MiniBubble();
	~MiniBubble();

private:
	void CalculateDistanceX(const int width_max, const int width_min/*, const float dt*/);
	void CalculateDistanceY(const int height_max, const int height_min/*, const float dt*/);

public:
	void Draw();
	void Update(float dt);
	void GetCurrentPosition(float& pos_x, float& pos_y) const;
	std::string GetColor() const;
	float GetRadius() const;
};

#endif // __MINIBUBBLE_H__