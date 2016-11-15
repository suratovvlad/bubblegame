#ifndef __AUDIOMANAGER_H__
#define __AUDIOMANAGER_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "MM/AudioSample.h"
#include "MM/AudioResource.h"

#include "ThreadSupport.h"

#if defined(ENGINE_TARGET_IPHONE) || defined(ENGINE_TARGET_MACOS)
#	include <OpenAL/al.h>
#	include <OpenAL/alc.h>
#else
#	include <al.h>
#	include <alc.h>
#endif

#include <boost/function.hpp>

#ifdef _DEBUG
#define AL_ERRORS_CHECK AlErrorsCheck(__FILE__, __LINE__)
#else
#define AL_ERRORS_CHECK
#endif
#define AL_ERRORS_CLEAR AlErrorsClear();

void AlErrorsCheck(const char *filename, int line);
void AlErrorsClear();

namespace MM {

class AudioManager {
public:
	enum CallbackAction {
		OnStop
	};

	AudioManager();	
	~AudioManager();
	
	static AudioManager& Self();
	
	void Initialize();
	void Shutdown();

	bool IsDevicePresent() const;
	
	/// ��������� �������� �����.
	/// ���������� ���������� ������������� ������ ��������������� ��� -1 ��� ������.
	int PlaySample(const std::string& id, bool looping = false, float volume = 1.0f, float pitch = 1.0f);
	/// ��������� �������� ����. ���������� PlaySample.
	int PlayTrack(const std::string& id, bool looping = false, float volume = 1.0f, float pitch = 1.0f);
	/// ������ ���� � ������� �� ���������������.
	int QueueSample(const std::string& id, int sample, bool looping = false, float volume = 1.0f, float pitch = 1.0f);
	/// ������ ���� � ������� �� ���������������. ���������� QueueSample.
	int QueueTrack(const std::string& id, int sample, bool looping = false, float volume = 1.0f, float pitch = 1.0f);
	/// ��������� ������������� ������ �� ����������
	bool IsValid(int id) const;
	/// ���������� ������������� ������ ��� �������� ������������ ����� (��� -1 � ������ ���������� ��������)
	int GetTrackId() const;
	/// ��������� / ��������� ��� �������� ������ ����� [����� �����, ���� butTrack = true]
	void PauseAll(bool pause, bool butTrack = false);
	/// ���������/��������� �������� �������� �����
	void PauseSample(int id, bool pause);
	/// ��������� �������� �� �����
	bool IsPaused(int id) const;
	/// ���������� ���������������
	void StopAll();
	/// ���������� ��������������� ��������� ������
	void StopSample(int id);
	/// ���������� ��������������� �����
	void StopTrack();
	/// ���������� ������� ��������������� (0..1)
	void SetPos(int id, float position);
	/// ������� ������� ��������������� (0..1)
	float GetPos(int id) const;
	/// ���������� ��������� (��� ����� ����������� ������� ��������� ����� 1.0f)
	/// �������� ��������� ����� �������� �� SoundVolume.
	void SetVolume(int id, float volume);
	/// ���������� ��������� (��� ����� ����������� ������� ��������� ����� 1.0f)
	/// �������� ��������� ����� �������� �� MusicVolume.
	void SetTrackVolume(float volume);
	/// �������� ��������� ������
	float GetVolume(int id) const;
	/// ���������� �������� (-1.0f - ������ ����� �����, 0 - ��� ������, 1.0f - ������ ������ �����)
	void SetPan(int id, float pan);
	/// ������������� ������� ��������� ������, ������� ���������� ��� �������� �����
	void SetCallback(int id, boost::function<void(CallbackAction action)> callback);
	/// �������� ��� ������ �� �������� �����. ���� ������ targetVolume �������� �� ����, �� ��� ������ ����� ��������� � �������� ���������
	void FadeAll(float time, float targetVolume = 0.0f);
	/// �������� ��� ������, ����� ����� �� �������� �����.
	void FadeOutAllButTrack(float time);
	/// �������� ����� �� �������� �����. ���� ������ targetVolume �������� �� ����, �� ����� ����� ������� � �������� ���������
	void FadeSample(int id, float time, float targetVolume = 0.0f);
	/// �������� ������� ���� �� �������� �����
	void FadeOutTrack(float time);
	/// �������� ������� ���� �� �������� �����
	void FadeInTrack(const std::string& id, float time, bool looping = false);
	/// ������� ������� ���� ��������� �� �������� �����
	void ChangeTrack(const std::string& id, float time, float start_position = 0.0f);
	/// �������� ��������� ������. ���� ��������� ��������� � ������ ����.
	float GetMusicVolume() const;
	/// ���������� ��������� ������. ���� ��������� ��������� � ������ ����.
	void SetMusicVolume(float value);
	/// �������� ��������� ������. ���� ��������� ��������� � ������ �����.
	float GetSoundVolume() const;
	/// ���������� ��������� ������. ���� ��������� ��������� � ������ �����.
	void SetSoundVolume(float value);
	/// �������� ��������� ������ ���������. ���� ��������� ���������� � ������ ����� � ������������� ���������� volumeMode = "ambience"
	float GetAmbienceVolume() const;
	/// ���������� ��������� ������ ���������. ���� ��������� ���������� � ������ ����� � ������������� ���������� volumeMode = "ambience"
	void SetAmbienceVolume(float value);

	// �������� ������� ��������
	void SuspendContext();	
	// ������������ ������� ��������
	void ResumeContext();

	bool IsContextSuspended() const;
	
	/// �������� ���������
	void Update(float dt);

	/// ������ ������
	void DumpSamples() const;

private:
	/// ��������� ������� ����� ����������
	void StartUpdateThread();
	/// ������������� ������� ����� ����������
	void StopUpdateThread();

	/// ��������� ����� � ������ �� �������� ��-�� ������ �������
	void AddFailedBuffer(ALuint buffer);
	/// �������� ������� ������, ����������� � ������
	void DeleteFailedBuffers();

	/// ���������� ��������� �������� ��� �����
	ALuint GetTrackSource();
	/// ����������� �������� �����
	void FreeTrackSource(ALuint source);

	int DoPlaySample(int sampleId, const std::string& id, bool looping, float volume, float pitch, bool asTrack);
	int DoQueueSample(const std::string& id, int sampleId, bool looping, float volume, float pitch, bool asTrack);

	// �������� ������� ��������
	void DoSuspendContext();
	// ������������ ������� ��������
	void DoResumeContext();

private:
	ALCdevice* _device;
	ALCcontext* _context;
	
	typedef std::deque<ALuint> Buffers;
	Buffers _failedBuffers;

	typedef std::deque<ALuint> TrackSources;
	TrackSources _trackSources;
	
	float _musicVolume;
	float _soundVolume;
	float _ambienceVolume;
	
	int _trackId;
	
	std::string _nextTrackId;
	
	float _pauseBeforeNextTrack;
	float _timeFadeInNextTrack;
	float _startPositionNextTrack;
	
	bool _paused;
	int _suspension_count;

	static int _nextId;
	
	struct SampleInfo {
		std::string resource;
		int id;
		AudioSamplePtr sample;
		VolumeMode volumeMode;
		float position;
		float volumeFactor;
		float currentVolume;
		float targetVolume;
		float fadeTime;
		float targetFade;
		float pan;
		float pitch;
		bool looping;
		bool pausable;
		bool deferred;
		bool track;
		int next;

		typedef boost::function<void(CallbackAction action)> Callback;
		Callback callback;
		
		SampleInfo()
			: id(-1), volumeMode(VolumeMode::Sound), position(-1.0f), volumeFactor(1.0f), currentVolume(1.0f), targetVolume(1.0f), fadeTime(0.0f), targetFade(0.0f)
			, pan(0.0f), pitch(1.0f), looping(false), pausable(true), deferred(false), track(false), next(0)
		{}
		
		SampleInfo(int id)
			: id(id), volumeMode(VolumeMode::Sound), position(-1.0f), volumeFactor(1.0f), currentVolume(1.0f), targetVolume(1.0f), fadeTime(0.0f), targetFade(0.0f)
			, pan(0.0f), pitch(1.0f), looping(false), pausable(true), deferred(false), track(false), next(0)
		{}
	};
	
	typedef std::map<int, SampleInfo> Samples;
	Samples _samples;
	std::vector<SampleInfo> _lostSamples;
	
	typedef std::map<std::string, int> Mixes;
	Mixes _mixes;
	
#if !defined(ENGINE_TARGET_WINDOWS_METRO)
	boost::scoped_ptr<boost::thread> _thread;
#endif // ENGINE_TARGET_WINDOWS_METRO

	mutable MUTEX_TYPE _mutex;

private:
	friend class AudioSample;

	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);
	
	void SetupSampleVolume(SampleInfo& sample);
};

extern AudioManager& manager;

} // namespace MM

#endif // __AUDIOMANAGER_H__
