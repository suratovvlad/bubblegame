#include "stdafx.h"
#include "MiniBubble.h"
#include "BubbleColor.h"
#include "SettingsManager.h"

MiniBubble::MiniBubble()
{
	m_isFirstDraw = true;
	m_color = BubbleColor::Instance()->GetRandomColor();
	m_texture = Core::resourceManager.Get<Render::Texture>(m_color);

	m_maxSpeed = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(MAX_SPEED, "1.0"));
	m_minSpeed = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(MIN_SPEED, "1.0"));

	speed_x = math::random(m_minSpeed, m_maxSpeed) * math::random_sign();
	speed_y = math::random(m_minSpeed, m_maxSpeed) * math::random_sign();

	m_scale = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(SCALE_MINI_BUBBLE, "0.09"));

	m_radius = m_texture->getBitmapRect().width * 0.5f * m_scale;	

	m_distance_x = 0.0f;
	m_distance_y = 0.0f;

	m_thinningParticles = 0;
	m_thinningSettings = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(THINNIHG_PARTICLES, "10"));
	m_particlesPositionCoef = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(COEF_PARTICLES_POSITION, "1.4"));
}


MiniBubble::~MiniBubble()
{
	std::list<ParticleEffectPtr>::iterator iterator = _eff_list.begin();
	while (iterator != _eff_list.end()) {
		(*iterator)->Finish();
		++iterator;
	}
	_eff_list.clear();
}

void MiniBubble::CalculateDistanceX(const int width_max, const int width_min/*, const float dt*/)
{
	if (m_distance_x <= (width_min + m_radius)
		|| m_distance_x >= (width_max - m_radius)) {
		speed_x *= -1;
	}

	m_distance_x += speed_x;
}

void MiniBubble::CalculateDistanceY(const int height_max, const int height_min/*, const float dt*/)
{
	if (m_distance_y <= (height_min + m_radius)
		|| m_distance_y >= (height_max - m_radius)) {
		speed_y *= -1;
	}

	m_distance_y += speed_y;
}

void MiniBubble::Draw()
{
	//
	// Проталкиваем в стек текущее преобразование координат, чтобы в дальнейшем
	// можно было восстановить это преобразование вызовом PopMatrix.
	//
	Render::device.PushMatrix();

	IRect texRect = m_texture->getBitmapRect();
	FRect rect(texRect);
	FRect uv(0, 1, 0, 1);

	m_texture->TranslateUV(rect, uv);

	Render::device.MatrixTranslate(math::Vector3(m_distance_x, m_distance_y, 0.0f));
	Render::device.MatrixScale(m_scale);
	Render::device.MatrixTranslate(math::Vector3(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f));

	m_texture->Bind();
	m_texture->setAlphaLimit(255);
	Render::DrawRect(rect, uv);

	//
	// Воостанавливаем прежнее преобразование координат, снимая со стека изменённый фрейм.
	//
	Render::device.PopMatrix();

	
	//
	// Рисуем все эффекты, которые добавили в контейнер (Update() для контейнера вызывать не нужно).
	//
	_effCont.Draw();	
}

void MiniBubble::Update(float dt)
{
	//
	// Обновим контейнер с эффектами
	//
	_effCont.Update(dt);
	

	// Следим за "умершими" партикловыми эффектами
	std::list<ParticleEffectPtr>::iterator iterator = _eff_list.begin();
	while (iterator != _eff_list.end()) {
		if (!_effCont.IsEffectAlive((*iterator).get())) {
			(*iterator)->Finish();
			iterator = _eff_list.erase(iterator);
		}
		else {
			++iterator;
		}
	}

	int width_max = 0;
	int width_min = 0;
	int height_max = 0;
	int height_min = 0;

	Layer* topLayer = Core::mainScreen.GetTopLayer();
	if (NULL != topLayer) {
		math::Vector3 center = topLayer->centerRotation * 2;

		width_max = center.x;
		height_max = center.y;
	}

	// Если отрисовка первая, то пузырь должен появиться в случайном месте
	if (m_isFirstDraw) {
		m_distance_x = math::random(width_min + m_radius, width_max - m_radius);
		m_distance_y = math::random(height_max - m_radius, height_min + m_radius);
		m_isFirstDraw = false;
		return;
	}

	// Recalculate m_distance_x and m_distance_y
	CalculateDistanceX(width_max, width_min);
	CalculateDistanceY(height_max, height_min);
	
	// Прореживание для эффекта частиц шлейфа
	++m_thinningParticles;
	if (m_thinningParticles < m_thinningSettings) {
		return;
	}
	m_thinningParticles = 0;
	

	// Создаем эффект шлейфа и отрисовываем его за пузырем
	ParticleEffectPtr _eff = _effCont.AddEffect(m_color);

	if (speed_x < 0) {
		_eff->posX = m_distance_x + m_radius * m_particlesPositionCoef;
	}
	else {
		_eff->posX = m_distance_x - m_radius * m_particlesPositionCoef;
	}
	

	if (speed_y < 0) {
		_eff->posY = m_distance_y + m_radius * m_particlesPositionCoef;
	}
	else {
		_eff->posY = m_distance_y - m_radius * m_particlesPositionCoef;
	}
	
	_eff->Reset();
	
	// Сохраняем созданные эффекты, чтобы в будущем их плавно завершить перед удалением
	_eff_list.push_back(_eff);
}


void MiniBubble::GetCurrentPosition(float& pos_x, float& pos_y) const
{
	pos_x = m_distance_x;
	pos_y = m_distance_y;
}

std::string MiniBubble::GetColor() const
{
	return m_color;
}
float MiniBubble::GetRadius() const {
	return m_radius;
}