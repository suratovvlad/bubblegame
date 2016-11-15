#ifndef __TIMEPARAM_H__
#define __TIMEPARAM_H__

#pragma once

#include "Utils/Math.hpp"

class GradientSpline;

namespace IO {
	class BinaryReader;
	class BinaryWriter;
}

class TimeParam
{
public:
	TimeParam();
	
	bool operator==(const TimeParam& rhs) const;

	size_t MemoryInUse() const;

	void Load(IO::BinaryReader* reader);
	void Load(rapidxml::xml_node<>* elem);

	void Save(IO::BinaryWriter* writer, const char* name);
	void Save(rapidxml::xml_node<>* elem, const char* name);

	rapidxml::xml_node<>* ToXml(rapidxml::xml_node<>* parent, const char* name);

	void SetValue(float value, float variation = 0);
	void SetScale(float scale) { _scale = scale; }

	float Reset(GradientSpline *spline);
	float GetRemoval() const { return _removal; }

private:
	struct Variation {
		float lower;
		float upper;

		Variation() : lower(0), upper(0) { }

		bool operator==(const Variation& rhs) const {
			return
				math::IsEqualFloat(lower, rhs.lower, 0.01f) &&
				math::IsEqualFloat(upper, rhs.upper, 0.01f);
		}

		float Lerp(float t) const {
			if (t < 0.01f)
				return lower;
			if (t > 0.99f)
				return upper;

			return lower + (upper - lower) * t;
		}
	};

	struct SplineKey {
		float time;
		Variation value, lgrad, rgrad;
		bool fixed_grad;

		SplineKey() : time(0), fixed_grad(false) { }

		bool operator==(const SplineKey& rhs) const {
			return
				math::IsEqualFloat(time, rhs.time) &&
				fixed_grad == rhs.fixed_grad &&
				value == rhs.value &&
				lgrad == rhs.lgrad &&
				rgrad == rhs.rgrad;
		}
	};

	typedef std::vector<SplineKey> Keys;

	Keys _keys;

	bool _similar;
	float _scale;
	float _removal;
};

#endif // __TIMEPARAM_H__
