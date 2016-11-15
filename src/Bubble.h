#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#pragma once

#include <PlayrixEngine.h>

class Bubble
{

private:

	enum LifeCycle{
		BORN = 0x1,
		LIVE = 0x2,
		DIE = 0x3
	};

	Render::Texture* m_texture;
	bool m_isFirstDraw;


	// Стартовые координаты центра объекта
	float m_start_x;
	float m_start_y;

	float m_scale;

	float m_timer;
	unsigned int m_lifeCycle;

	std::string m_color;
	float m_radius;

	float m_bornTime;
	float m_lifeTime;
	float m_maxScale;

	void Init();

public:

	explicit Bubble();
	Bubble(const std::string& color, const float& pos_x, const float& pos_y);
	~Bubble();

	bool isLive() const;
	void Draw();
	void Update(float dt);
	bool isClose(const float& pos_x, const float& pos_y, const float& mini_radius) const;

	std::string GetColor() const;
	void GetCurrentPosition(float& pos_x, float& pos_y) const;

};

#endif // __BUBBLE_H__