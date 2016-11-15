#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Light.h"

#include <boost/intrusive_ptr.hpp>

namespace SceneGraph {

///
/// �������� �������� �����.
///
class PointLight : public Light {
public:
	typedef boost::intrusive_ptr<PointLight> HardPtr;
	
	Light::HardPtr Clone();

	float GetRange() const;
		/// ���������� ��������� �� ��������� �����, �� ������� �� ���������
	
	void SetRange(float range);
		/// ������������� ��������� �� ��������� �����, �� ������� �� ���������
	
	float GetConstantAttenuation() const;
		/// ���������� ����������� ����������� ����������
	
	void SetConstantAttenuation(float attenuation);
		/// ������������� ����������� ����������� ����������
	
	float GetLinearAttenuation() const;
		/// ���������� ����������� ��������� ����������
	
	void SetLinearAttenuation(float attenuation);
		/// ������������� ����������� ��������� ����������
	
	float GetQuadraticAttenuation() const;
		/// ���������� ����������� ������������� ����������
	
	void SetQuadraticAttenuation(float attenuation);
		/// ������������� ����������� ������������� ����������
	
	Type GetType() const;
		/// ���������� ��� ��������� �����
	
	static PointLight::HardPtr Create(const math::Vector3& position);

protected:
	float _range;
		/// ��������� �� ��������� �����, �� ������� �������� ���������
	
	float _attenuation0;
		/// ����������� ����������� ���������� �����
	
	float _attenuation1;
		/// ����������� ��������� ���������� �����
	
	float _attenuation2;
		/// ����������� ������������� ���������� �����
	
	PointLight(const math::Vector3& position);
};

} // namespace SceneGraph

#endif // __POINTLIGHT_H__
