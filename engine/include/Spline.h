#ifndef __SPLINE_H__
#define __SPLINE_H__

#pragma once

#include "EngineAssert.h"
#include "Utils/FPoint.h"

float SplineInterpolation(float x1, float x2, float r1, float r2, float t);
float GetGradient(float x1, float x2, float r1, float r2, float t);
FPoint SplineInterpolation(FPoint v1, FPoint v2, FPoint g1, FPoint g2, float t);
FPoint GetGradient(FPoint v1, FPoint v2, FPoint g1, FPoint g2, float t);

// Этот класс едва ли где-нибудь используется.
template <class T>
class SplinePath {
public:
	typedef std::pair<T, T> KeyFrame;
	typedef std::vector<KeyFrame> Keys;

	Keys keys;

	void Clear() {
		Keys().swap(keys);
	}

	void addKey(const T& key) {
		keys.emplace_back(key, key);
	}

	T getFrame(int sector, float t) {
		size_t i = static_cast<size_t>(sector);
		return SplineInterpolation(keys[i].first, keys[i+1].first, keys[i].second, keys[i+1].second, t);
	}

	T getGradient(int sector, float t) {
		size_t i = static_cast<size_t>(sector);
		return GetGradient(keys[i].first, keys[i+1].first, keys[i].second, keys[i+1].second, t);
	}

	T getGlobalFrame(float t) {
		int sectors = getSectors();
//		Assert(sectors > 0);
		if (sectors <= 0) {
			return T();
		}
		float timeStep = (1.0f/sectors);
		int tessSector = static_cast<int>(t/timeStep);
		if (tessSector >= sectors) {
			return keys.back().first;
		}
		float tessLocalTime = (t-tessSector*timeStep)/timeStep;
		return getFrame(tessSector, tessLocalTime);
	}

	T getGlobalGradient(float t) {
		int sectors = getSectors();
		Assert(sectors > 0);
		if (sectors <= 0) {
			return T();
		}
		float timeStep = (1.0f/sectors);
		int tessSector = static_cast<int>(t/timeStep);
		if (tessSector >= sectors) {
			return keys.back().second;
		}
		float tessLocalTime = (t-tessSector*timeStep)/timeStep;
		return getGradient(tessSector, tessLocalTime);
	}

	int getSectors() {
		Assert(keys.size() > 0);
		return static_cast<int>(keys.size()-1);
	}

	void CalculateGradient(bool cycled = false)
	{
		if (cycled) {
			keys.push_back(keys[0]);
		}
		
		if (cycled) {
			keys[0].second = 0.5f*(keys[1].first - keys[keys.size() - 2].first);
			keys[keys.size() - 1].second = keys[0].second;
		} else {
			if (keys.size() > 1) {
				keys[0].second = keys[1].first-keys[0].first;
				keys[keys.size()-1].second = keys[keys.size()-1].first-keys[keys.size()-2].first;
			}
		}

		for (int i = 1; i < int(keys.size()-1); i++) {
			keys[i].second = 0.5f*(keys[i+1].first - keys[i-1].first);
		}
	}
};

// Этот класс используется во flash fx
class TimedSplinePath {
public:
	typedef std::pair<float, float> KeyValue;

	struct KeyFrame {
		KeyValue value;
		float time;
		float td, ts;

		KeyFrame(float key, float time)
			: value(key, key)
			, time(time)
			, td(0.0f)
			, ts(0.0f)
		{
		}
	};

	
	typedef std::vector<KeyFrame> Keys;

	Keys keys;

	size_t currentKeyFrame, currentKeyGradient;

	TimedSplinePath() : currentKeyFrame(1), currentKeyGradient(1) { }
	TimedSplinePath(rapidxml::xml_node<> *node, bool calculateGradient = true, bool cycled = false);
	/*
		<SomeSplineName>
			<key time="" value="" />
			...
			<key time="" value="" />
		</SomeSplineName>
	*/

	void Clear();

	void addKey(float time, float key);

	float getFrame(size_t sector, float t);

	float getGradient(int sector, float t);

	float getGlobalFrame(float t);

	float getGlobalGradient(float t);

	int getSectors();

	void CalculateGradient(bool cycled = false);
};


// Этот класс используется в эффектах.
class GradientSpline {
public:
	struct Key {
		float value;
		float left_gradient;
		float right_gradient;
		float time;
		bool fixed_gradient;
		
		Key() = default;

		Key(float t, float v, float lgrad, float rgrad, bool fixed)
			: time(t)
			, value(v)
			, left_gradient(lgrad)
			, right_gradient(rgrad)
			, fixed_gradient(fixed)
		{
		}
	};

	GradientSpline()
		: currentKeyFrame(1)
	{
	}

	size_t MemoryInUse() const;

	void Clear();
	
	void sizeHint(size_t size) { keys.reserve(size); }

	void addKey(float time, float value, float lgrad = 0, float rgrad = 0, bool fixed_grad = false);

	void deleteKey(size_t pos) { keys.erase(std::next(keys.begin(), pos)); }

	size_t size() const { return keys.size(); }

	void CalculateGradient();

	float getGlobalFrame(float time) const;
	float getGlobalGradient(float time) const;

private:
	static float interpolationValue(float time, const Key &key1, const Key &key2);
	static float interpolationGradient(float time, const Key &key1, const Key &key2);

private:
	typedef std::vector<Key> Keys;
	Keys keys;

	// Номер того элемента массива keys, который сейчас обрабатывается
	// в getGlobalFrame  в соответствии со временем.
	// Начинается от 1, так как нулевой элемент keys 
	// никогда не может быть искомым в поиске.
	mutable uint16_t currentKeyFrame;
};


// Этот класс разрабатывался для редактора эффектов, но сейчас не используется.
class TrackSpline {
public:
	TrackSpline()
		: _cycled(false)
	{
	}

	struct Key {
		float time;
		FPoint value, gradient_in, gradient_out;
		bool linear_in;
		bool linear_out;
	};

	typedef std::vector<Key> Keys;

	void Clear() {
		Keys().swap(_keys);
	}

	void addKey(float x, float y, bool linear_in = false, bool linear_out = false) {
		_keys.emplace_back();
		Key &key = _keys.back();
		key.value.x = x;
		key.value.y = y;
		key.linear_in = linear_in;
		key.linear_out = linear_out;
	}

	void deleteKey(size_t pos) {
		_keys.erase(std::next(_keys.begin(), pos));
	}

	size_t size() const {
		return _keys.size();
	}

	Key& operator[](size_t pos) {
		return _keys[pos];
	}

	void Calculate();

	FPoint getGlobalFrame(float time);

	FPoint getGlobalGradient(float time);

	FPoint interpolationValue(float time, size_t i, size_t j);

	FPoint interpolationGradient(float time, size_t i, size_t j);

	size_t Prev(size_t i);

	size_t Next(size_t i);

	float Length(const Key &key1 , const Key &key2);

	FPoint GradientIn(size_t i);

	FPoint GradientOut(size_t i);

private:
	Keys _keys;

	bool _cycled;
	
	float _length;
};

#endif // __SPLINE_H__
