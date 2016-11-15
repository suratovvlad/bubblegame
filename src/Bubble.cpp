#include "stdafx.h"
#include "Bubble.h"
#include "BubbleColor.h"
#include "SettingsManager.h"

Bubble::Bubble()
{
	m_start_x = 0.0f;
	m_start_y = 0.0f;
	m_isFirstDraw = true;

	m_color = BubbleColor::Instance()->GetRandomColor();
	Init();
}

Bubble::Bubble(const std::string& color, const float& pos_x, const float& pos_y)
{
	m_color = color;
	m_start_x = pos_x;
	m_start_y = pos_y;
	m_isFirstDraw = false;
	Init();
}

Bubble::~Bubble()
{
}

void Bubble::Init()
{
	m_texture = Core::resourceManager.Get<Render::Texture>(m_color);
	m_bornTime = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(BORN_TIME, "0.5"));
	m_lifeTime = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(LIFE_TIME, "1.0"));

	m_scale = 0.f;
	m_maxScale = utils::lexical_cast<float>(SettingsManager::Instance()->GetSettingByName(MAX_SCALE_MACRO_BUBBLE, "0.5"));

	m_lifeCycle = BORN;
	m_timer = 0.0f;
	m_radius = m_texture->getBitmapRect().width * 0.5f;
	
}

bool Bubble::isLive() const
{
	if ((m_lifeCycle & DIE) == DIE)
	{
		return false;
	}
	return true;
}

void Bubble::Draw()
{
	if ((m_lifeCycle & DIE) == DIE)
	{
		return;
	}

	//
	// ������������ � ���� ������� �������������� ���������, ����� � ����������
	// ����� ���� ������������ ��� �������������� ������� PopMatrix.
	//
	Render::device.PushMatrix();

	//
	// ��� ��������� �������� ����� ������� �������� UV ���������� ��� ����� ��������,
	// ������� ����� �������� �� ������� �������. UV ���������� ������ ���� �������������,
	// �.�., ��� ����������� �� ������� �������� � ��������, ������ ����� ��������
	// ����� 1 (UV ���������� �������� � ��������� 0..1, ���� ����� �� ������ ������ ��
	// ������ �������, ��� ���� � ������ ������������� ��������� �������� REPEAT, ��������
	// ����� ���������� �� ���� ������� ��������������� ���������� ���).
	//
	IRect texRect = m_texture->getBitmapRect();
	FRect rect(texRect);
	FRect uv(0, 1, 0, 1);

	m_texture->TranslateUV(rect, uv);

	if (m_isFirstDraw) {

		//
		// �������� ������� ��������� ������� ����.
		//
		IPoint mouse_pos = Core::mainInput.GetMousePos();

		m_start_x = (float)mouse_pos.x;
		m_start_y = (float)mouse_pos.y;

		m_isFirstDraw = false;
	}

	Render::device.MatrixTranslate(math::Vector3(m_start_x, m_start_y, 0.0f));
	Render::device.MatrixScale(m_scale);
	Render::device.MatrixTranslate(math::Vector3(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f));

	//
	// ����������� ��������.
	//
	m_texture->Bind();

	//
	// ����� DrawRect() ������� � ����������� ���������� ���������� ������, ��������� �� ����
	// ���������� - �������������, ��������� ��� ���� ������� ���� ��� ������ � ����������� (binded) ��������,
	// ���� ��������� ���������������.
	//
	// ����� ������� DrawRect() ������ ���� ����� Texture::Bind(), ���� SetTexturing(false),
	// ����� ���������� ��������� ����� ���������������.
	//
	Render::DrawRect(rect, uv);

	//
	// ��������������� ������� �������������� ���������, ������ �� ����� ��������� �����.
	//
	Render::device.PopMatrix();

}

void Bubble::Update(float dt)
{
	m_timer += dt;

	if (((m_lifeCycle & BORN) == BORN) 
		&& m_timer >= m_bornTime)
	{
		m_lifeCycle = LIVE;
		m_timer = 0.0f;
	}
	else if (((m_lifeCycle & LIVE) == LIVE)
		&& m_timer >= m_lifeTime)
	{
		m_lifeCycle = DIE;
		m_timer = 0.0f;
	}

	if (((m_lifeCycle & BORN) == BORN)) {
		if (m_scale < m_maxScale) {
			m_scale += 0.025f;
		}
		
	}

	if (((m_lifeCycle & DIE) == DIE)) {
			m_scale = 0.02f;
	}
}

bool Bubble::isClose(const float& pos_x, const float& pos_y, const float& mini_radius) const
{
	math::Vector3 mini_bubble = math::Vector3(pos_x, pos_y, 0.0f);
	math::Vector3 bubble = math::Vector3(m_start_x, m_start_y, 0.0f);

	float distance = (bubble - mini_bubble).Length();

	if (distance <= (m_radius*m_scale + mini_radius)) {
		return true;
	}

	return false;
}

std::string Bubble::GetColor() const
{
	return m_color;
}

void Bubble::GetCurrentPosition(float& pos_x, float& pos_y) const
{
	pos_x = m_start_x;
	pos_y = m_start_y;
}