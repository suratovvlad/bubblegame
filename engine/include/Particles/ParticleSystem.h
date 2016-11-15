#ifndef PARTICLE_SYSTEM_VER2_H
#define PARTICLE_SYSTEM_VER2_H

#include "Particles/Particle.h"
#include "Particles/EmitterMask.h"
#include "Particles/TimeParam.h"
#include "Render/Texture.h"
#include "Spline.h"
#include "ThreadSupport.h"

#include <boost/unordered_set.hpp>

namespace IO {
	class BianryReader;
	class BinaryWriter;
}

namespace Render {
	class SpriteBatch;
}

class ParticleEffect;

enum class EmitterType : uint8_t {
	Point,
	Line,
	Area,
	Circle,
	Mask
};

/// Система частиц.
/// Представляет собой управляемое множество одинаковых частиц.
class ParticleSystem : public RefCounter, public boost::intrusive::list_base_hook<> {
public:
	ParticleSystem();
	~ParticleSystem();
	
	ParticleSystem *Clone() const;

	bool Load(IO::BinaryReader *reader);
	bool Load(rapidxml::xml_node<> *elem);
	void Save(IO::BinaryWriter *writer);
	void Save(rapidxml::xml_node<> *elem);

	void Reset();
	void Update(float dt);
	void Draw(Render::SpriteBatch* batch = NULL);
	void DrawBlend(Render::SpriteBatch* batch = NULL);

	void SetAdditive(bool additive) { _addBlend = additive; }

	bool IsAdditive() const { return _addBlend; }
	bool IsDead() const { return _isDead; }
	bool IsPermanent() const { return !_needStartDeadCounter; }
	bool IsVelocity() const { return isVelocity; }
	bool IsAnimation() const { return _isAnimation; }

	void Finish();
	void SetScale(float scale_x, float scale_y = 0);
	void SetPositionOffset(float x, float y);
	void SetAlphaFactor(float alpha);
	void SetRGBFactor(float r, float g, float b);

	int FrameWidth() const { return _frameWidth; }
	int FrameHeight() const { return _frameHeight; }
	
	void DisableFog(bool disable);

	float GetLocalTime() const { return _localTime; }
	void SetLocalTime(float localTime) { _localTime = localTime; }
	
	const std::string& GetTextureName() const { return _texName; }
	Render::Texture* GetTexture() const { return _tex; }

	void Upload();
	void Release();

	size_t MemoryInUse() const;

	void SetOwnerEffect(ParticleEffect* effect) { _effect = effect; }
	
	float emitterAngle, emitterRange, emitterOrientation;
	float emitterSizeX, emitterSizeY, emitterFactor;
	float _lifeInitial;
	
private:
	friend class EffectManager;
	friend class EffectTree;

	ParticleSystem(const ParticleSystem&);
	ParticleSystem& operator=(const ParticleSystem&);

	rapidxml::xml_node<>* GetParamElement(rapidxml::xml_node<> *elem, const std::string& name);
	void LinkFlameEmitter(ParticleSystem* ps);
	void RebornParticle(Particle& part, int index);
	void LoadTexture(const std::string& filename);
	void LoadTextureMask(const std::string& filename);
	void InternalDraw(Render::SpriteBatch* batch, float alpha);

private:
	ParticleEffect* _effect;

	typedef std::vector<Particle> Particles;
	Particles _particles;

	bool _isVisible;
	bool _isAnimation;
	short _numOfParticles;

	float _scale_x, _scale_y;
	float _localTime;
	float _lifeVariation;
	float _startTime;

	std::string name;

	std::string _texName;
	Render::Texture* _tex;

	ParticleSystem* _flameLink;
	
	short _frameWidth, _frameHeight;

	bool _isScaledNonproportional;
	bool _isEqualCreateTime;

	bool _needParticleReborn;
	bool _needDeadCount;
	size_t _deadParticleCounter;
	bool _allParticlesIsDead;
	bool _addBlend;

	bool showEmitter;
	
	EmitterType emitType;
	
	EmitterMask* emitterMask;
	Render::Texture *emitterTex;

	// для копирования в ParticleSystemComposite
	float bornTime;
	float _deadCountTime;
	bool _needStartDeadCounter;
	bool _isFreeze;
	bool _isDead;

	bool _disableFog;	//флаг, с которым отключается туман на время рисования частитц в режиме ADD

	friend class Particle;
	TimeParam x, y, size, angle, v, spin, colorRed, colorGreen, colorBlue, colorAlpha, fps, ySize;
	
	float redFactor, greenFactor, blueFactor, alphaFactor;

	float posX, posY;

	bool linkParticles;
	bool orientParticles;
	bool isVelocity;
	bool fixedAngleStep;

	FPoint _hotPoint;

public:
	static std::string NormalizeTextureName(const std::string &name);
	static void SetTexturesPath(const std::string &path);
	static const std::string& GetTexturesPath();
	static void SetErrorMessage(const std::string &msg);
	static std::string ErrorMessage();
	static void CreateTexturePlug();
	static void DestroyTexturePlug();
	static size_t TotalMemoryInUse();

protected:
	static Render::TexturePtr _texture_plug;
	static std::string _error_message;
	static std::string _textures_path;

private:
	void InsertThisToList();
	void RemoveThisFromList();
};

typedef boost::intrusive_ptr<ParticleSystem> ParticleSystemPtr;

#endif