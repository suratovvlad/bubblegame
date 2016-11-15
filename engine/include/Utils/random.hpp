#ifndef _UTILS_RANDOM_HPP_
#define _UTILS_RANDOM_HPP_

#include "Utils/FPoint.h"
#include "Utils/Color.h"
#include "Utils/Vector3.h"
#include "Utils/Math.hpp"

namespace math
{
	/// random seed
	void random_seed(size_t value);

	/// [min; max]
	int random(int min, int max);

	/// [min; max]
	size_t random(size_t min, size_t max);

	/// [min; max)
	float random(float min, float max);

	/// ���������� true ��� false
	inline bool random_bool() { return random(0, 1) != 0; }

	/// ���������� 1 ��� -1
	inline int random_sign() { return random_bool() ? 1 : -1; }

	/// [0; max]
	inline int random(int max) { return random(0, max); }

	/// [0; max]
	inline size_t random(size_t max) { return random(0u, max); }

	/// [0; max)
	inline float random(float max) { return random(0.0f, max); }

	template <class T>
	inline T lerp(const T& v1, const T& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return (v1+static_cast<T>((v2-v1)*t));
	}

	template <>
	inline float lerp(const float& v1, const float& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return (v1+(v2-v1)*t);
	}

	template <>
	inline Vector3 lerp(const Vector3& v1, const Vector3& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return (v1+(v2-v1)*t);
	}

	template <>
	inline IPoint lerp(const IPoint& v1, const IPoint& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return IPoint(lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t));
	}

	template <>
	inline FPoint lerp(const FPoint& v1, const FPoint& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;
		
		return FPoint(lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t));
	}
	
	template <>
	inline Color lerp(const Color& v1, const Color& v2, const float t)
	{
		if (t <= 0.f) return v1;
		if (t >= 1.f) return v2;

		return Color(	
			lerp<int>(v1.red, v2.red, t), 
			lerp<int>(v1.green, v2.green, t), 
			lerp<int>(v1.blue, v2.blue, t),
			lerp<int>(v1.alpha, v2.alpha, t)
			);
	}

	/// ���������� �������� ������������������ ������
	inline math::Vector3 random(const math::Vector3& max)
	{
		return lerp(math::Vector3::Zero, max, random(0.0f, 1.0f));
	}

	/// ���������� ������ ���������� ������� �� ��������� [min; max)
	inline math::Vector3 random(const math::Vector3& min, const math::Vector3& max)
	{
		return lerp(min, max, random(0.0f, 1.0f));
	}

	/// ��� ���������� �������� [min; max)
	inline Color random(const Color& min, const Color& max)
	{
		return lerp(min, max, random(0.0f, 1.0f));
	}

	/// ���������� ����� �� ����� [min; max)
	inline FPoint random(const FPoint& min, const FPoint& max)
	{
		return lerp(min, max, random(0.0f, 1.0f));
	}

	inline float ease(float t, float a, float b) 
	{
		float k;
		float s = a + b;

		if (s == 0.0f) return t;
		if (s > 1.0f) 
		{
			a = a / s;
			b = b / s;
		}
		k = 1.0f / (2.0f - a - b);
		if (t < a)
		{
			return ((k / a) * t * t);
		}
		else 
		{
			if (t <= 1.0f - b)
			{
				return (k * (2 * t - a));
			} 
			else 
			{
				t = 1.0f - t;
				return (1.0f - (k / b) * t * t);
			}
		}
	}

	// ����������� ��� ease()
	inline float ease_deriv(float t, float a, float b) 
	{
		if (t < 0.0f || t > 1.0f || a < 0.0f || b < 0.0f) return 1.0f;

		float k;
		float s = a + b;

		if (s == 0.0f) return 1.0f;
		if (s > 1.0f) 
		{
			a /= s;
			b /= s;
		}
		k = 1.0f / (2.0f - a - b);
		if (t < a)
			return 2*k/a*t;
		else if (t <= 1.0f - b)
			return 2*k;
		else
			return 2*k/b*(1-t);
	}

	// �������, �������� � ease (���������, ������������ � ���������� � ������ �����)
	inline float ease_inv(float y, float a, float b) 
	{
		if (y < 0.0f || y > 1.0f || a < 0.0f || b < 0.0f) return y;

		float s = a + b;
		if (s == 0.0f) return y;

		if (s > 1.0f) 
		{
			a /= s;
			b /= s;
		}
		
		float k = 1.0f / (2.0f - a - b);
		if (y < k*a) 
			return math::sqrt(a*y/k);
		else if (y < 1-k*b) 
			return (y+a*k)/(2.0f*k);
		else
			return 1.0f - math::sqrt(b*(1-y)/k);
	}

	/** 
	 * ���������� ����� �� ������ �����
	 * ���������:
	 * start, end, control - ���������, �������� � ����������� �����
	 * time - ����� �� 0 �� 1
	 */
	inline FPoint simpleBezier(const FPoint &start, const FPoint &end, const FPoint &control, float time)
	{
		time = math::clamp(0.0f, 1.0f, time);

		const float invertedTime = 1.0f - time;
		const float timePower2 = time * time;
		const float invertedTimePower2 = invertedTime * invertedTime;

		return FPoint(
				invertedTimePower2 * start.x + 2.0f * time * invertedTime * control.x + timePower2 * end.x,
				invertedTimePower2 * start.y + 2.0f * time * invertedTime * control.y + timePower2 * end.y
			);
	}

	template <class T>
	class RandomValue
	{
		T _value;
		T _v1, _v2;
		T _limit;
		float _local_time;
		float _period;
		float _startPeriod, _endPeriod;

	public:
		RandomValue(T limit, float startPeriod, float endPeriod)
			: _limit(limit)
			, _local_time(0.0f)
			, _startPeriod(startPeriod)
			, _endPeriod(endPeriod)
		{
			_period = math::random(_startPeriod, _endPeriod);
			_v1 = math::random(T(), _limit);
			_v2 = math::random(T(), _limit);
		}

		void Update(float dt)
		{
			if (_local_time >= _period)
			{
				_local_time -= _period;
				_period = math::random(_startPeriod, _endPeriod);
				_v1 = _v2;
				_v2 = math::random(T(), _limit);
			}
			_value = lerp(_v1, _v2, _local_time/_period);
			_local_time += dt;
		}

		T get()
		{
			return _value;
		}
	};

} // namespace math

#endif
