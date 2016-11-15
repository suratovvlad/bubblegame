#ifndef __EMITTERMASK_H__
#define __EMITTERMASK_H__

#pragma once

#include "Core/Resource.h"
#include "Core/ResourceLoader.h"
#include "Utils/random.hpp"

/// Маска эмиттера
class EmitterMask : public Resource {
public:
	EmitterMask(const std::string& filename);

	const std::string& GetName() const { return filename; }

	size_t GetMemoryInUse() const;

	const std::string& GetFileName() const { return filename; }

	FPoint RandomPoint(float scale = 1.0f) const;

	// !!! При изменении этих параметров требуется пересчитывать функцию распределения
	void SetAlphaMin(uint8_t min) { luminanceMin = min; }
	void SetAlphaMax(uint8_t max) { luminanceMax = max; }
	
	void SetScaleX(float scale) { scaleX = std::max(0.0f, scale); }
	void SetScaleY(float scale) { scaleY = std::max(0.0f, scale); }
		
	uint8_t AlphaMin() const { return luminanceMin; }
	uint8_t AlphaMax() const { return luminanceMax; }
	
	float ScaleX() const { return scaleX; }
	float ScaleY() const { return scaleY; }

private:	
	std::string filename;		
	float scaleX, scaleY;
	uint8_t luminanceMin, luminanceMax;
	std::vector<int32_t> distrFunction;	
	int32_t normFactor;
	// Яркость каждого пикселя (от 0 до 255)
	std::vector<uint8_t> luminance;
	// Ширина и высота изображения
	int32_t width, height;

	// Простой, но быстрый генератор псевдослучайных чисел
	class Rnd {
		static const uint32_t A = 19993;
		static const uint32_t B = 1;
		uint32_t x;
	public:
		static const uint32_t MAX_RND = 0xFFFFFFFFu;
		float INV_MAX_RND;
		Rnd()
			: x(static_cast<uint32_t>(math::random(static_cast<size_t>(MAX_RND))))
			, INV_MAX_RND (1.0f / MAX_RND)
		{ 
		}

		uint32_t operator()() {
			return x = A * x + B;
		}

	};	

	mutable Rnd rnd;
		
private:
	friend class EmitterMaskLoader;

	void GetLuminanceData();
	void CalcDistrFunction();

	void LoadMask();
	void UnloadMask();

private:
	EmitterMask(const EmitterMask&);
	EmitterMask& operator=(const EmitterMask&);
};

/// Загрузчик маски эмиттера
class EmitterMaskLoader : public ResourceLoader {
protected:
	void DoLoadData(Resource* resource);

	void DoLoadObject(Resource* resource);

	void DoUnload(Resource* resource);
};

#endif // __EMITTERMASK_H__
