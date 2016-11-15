#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Utils/Vector3.h"
#include "Utils/Matrix4.h"
#include "RefCounter.h"

#include <boost/intrusive_ptr.hpp>

namespace SceneGraph {

///
/// ������.
///
/// ������������� �������������� �������� � ����, � ����� ���������
/// �������� ��������� ���� � ������������ (����������� ������).
///
class Camera : public RefCounter {
public:
	typedef boost::intrusive_ptr<Camera> HardPtr;
	
	Camera(const math::Vector3& eye = math::Vector3(0.0f, 0.0f, 0.0f), const math::Vector3& lookAt = math::Vector3(0.0f, 0.0f, 1.0f));
	
	virtual ~Camera();
	
	virtual Camera::HardPtr Clone();

	virtual size_t GetMemoryInUse() const;
	
	const math::Matrix4& GetView();
		/// ���������� ������� ����
	
	const math::Matrix4& GetProjection() const;
		/// ���������� ������� ��������
	
	const math::Matrix4& GetViewProjection();
		/// ���������� ��������������� ������� ����-��������
	
	const math::Vector3& GetRight() const;
		/// ���������� ������ ������ ������
	
	const math::Vector3& GetUp() const;
		/// ���������� ������� ������ ������
	
	const math::Vector3& GetLookAt() const;
		/// ���������� ������ ����������� ������� ������
	
	const math::Vector3& GetEye() const;
		/// ���������� ������� ������ � ������� ������������
	
	virtual void SetProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
		/// ������������� ��������� �������������
	
	virtual void SetView(const math::Vector3& eye, const math::Vector3& lookAt);
		/// ������������� ��������� ���� ������
	
	virtual void Yaw(float radians);
		/// ������������ ������ ������������ �������� ������� (��������)
	
	virtual void Pitch(float radians);
		/// ������������ ������ ������������ ������� ������� (������)
	
	virtual void Roll(float radians);
		/// ������������ ������ ������������ ������� ������� (��������)
	
	virtual void Walk(float units);
		/// ����������� ������ ������������ ������� ������� (�����-�����)
	
	virtual void Strafe(float units);
		/// ����������� ������ ������������ ������� ������� (������-�����)
	
	virtual void Fly(float units);
		/// ����������� ������ ������������ �������� ������� (�����-����)

protected:
	void RecalculateView();
		/// ������������� ������� ���� � ����-�������� ����� ��������� �������� ������

protected:
	math::Vector3 _right;
		/// ������ ������ ������
	
	math::Vector3 _up;
		/// ������� ������ ������
	
	math::Vector3 _lookAt;
		/// ������ ������� ������
	
	math::Vector3 _eye;
		/// ��������� ����������� � ������� ������������
	
	math::Matrix4 _view;
		/// ������� ����, ����������� �������
	
	math::Matrix4 _proj;
		/// ������� ��������, ����������� �������
	
	math::Matrix4 _viewProj;
		/// ��������������� ������� ����-��������
	
	bool _viewDirty;
		/// ����� �� ����������� ������� ���� � ����-��������
	
	float _fieldOfView;
		/// ���� ������ ������
	
	float _aspectRatio;
		/// ��������� ����������� �������������
	
	float _nearPlane;
		/// ��������� �������� ���������
	
	float _farPlane;
		/// ��������� �������� ���������
};

} // namespace SceneGraph

#endif // __CAMERA_H__
